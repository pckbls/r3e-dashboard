#!/usr/bin/python3

import asyncio
from aiohttp import web
import aiohttp
import json
import lib.r3e as r3e
import math
import sys

ws_clients = []

def convert_r3e_data(data):
    result = {
        "ticks": data.player.game_simulation_ticks,
        "time": data.player.game_simulation_time,
        "engine_rpm": data.engine_rps * (60 / (2 * math.pi)),
        "engine_oil_pressure": data.engine_oil_pressure,
        "max_engine_rpm": data.max_engine_rps * (60 / (2 * math.pi)),
        "car_speed": data.car_speed * 3.6,
        "gear": data.gear,
        "throttle_pedal": data.throttle_pedal,
        "brake_pedal": data.brake_pedal,
        "clutch_pedal": data.clutch_pedal,
        "lap_time_current_self": data.lap_time_current_self,
        "lap_time_best_self": data.lap_time_best_self
    }

    return result

@asyncio.coroutine
def redirect_index(request):
    return web.HTTPFound("/index.html")

@asyncio.coroutine
def ws_handler(request):
    global ws_clients
    
    print("Web socket request")

    ws = web.WebSocketResponse()
    ws.start(request)

    ws_clients.append(ws)

    while True:
        msg = yield from ws.receive()

        if msg.tp == aiohttp.MsgType.text and msg.data == "close":
           break
        elif msg.tp == aiohttp.MsgType.closed:
            break
        elif msg.tp == aiohttp.MsgType.error:
            break

    yield from ws.close()

    ws_clients.remove(ws)
    print("Removed web socket connection")

    return ws

@asyncio.coroutine
def r3e_task():
    print("Waiting for R3E to start...")
    while not r3e.is_r3e_running():
        yield from asyncio.sleep(1)

    print("Initializing memory map...")
    r3e.init_mmap()

    print("Fetching data...")
    while True:
        binary = r3e.read_mem()
        data = r3e.parse(binary)
        converted = convert_r3e_data(data)
        
        for client in ws_clients:
            client.send_str(json.dumps(converted))
        
        yield from asyncio.sleep(0.1)

@asyncio.coroutine
def playback_task(path):
    print("Playback task...")
    with open(path, "rb") as f:
        print("Opened file", path)
        while True:
            binary = f.read(r3e.shared_size)
            if not binary:
                break

            data = r3e.parse(binary)
            converted = convert_r3e_data(data)

            for client in ws_clients:
                client.send_str(json.dumps(converted))
            
            yield from asyncio.sleep(0.1)

if __name__ == '__main__':
    try:
        loop = asyncio.get_event_loop()

        app = web.Application(loop = loop)
        app.router.add_route("GET", "/", redirect_index)
        app.router.add_route("GET", "/ws", ws_handler)
        app.router.add_static("/", "public_html")
        http_server = loop.create_server(app.make_handler(), "0.0.0.0", 8080)

        loop.run_until_complete(http_server)
        print("HTTP server running at http://127.0.0.1:8080")

        if len(sys.argv) == 2:
            loop.run_until_complete(playback_task(sys.argv[1]))
        else:
            loop.run_until_complete(r3e_task())

        loop.run_forever()
    except KeyboardInterrupt as e:
        print("Shutting down...")

