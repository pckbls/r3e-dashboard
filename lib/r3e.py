import mmap
import psutil
import random
from construct import *

dummy = False

shm = None

tagname = "$Race$"

process_name = "RRRE.exe"

shared_size = 624

shared_parser = Struct("r3e_shared",
    Array(6, LFloat32("user_input")),
    
    LFloat32("engine_rps"),
    LFloat32("max_engine_rps"),
    LFloat32("fuel_pressure"),
    LFloat32("fuel_left"),
    LFloat32("fuel_capacity"),
    LFloat32("engine_water_temp"),
    LFloat32("engine_oil_temp"),
    LFloat32("engine_oil_pressure"),
    LFloat32("car_speed"),
    SLInt32("number_of_laps"),
    SLInt32("completed_laps"),
    LFloat32("lap_time_best_self"),
    LFloat32("lap_time_previous_self"),
    LFloat32("lap_time_current_self"),
    SLInt32("position"),
    SLInt32("num_cars"),
    SLInt32("gear"),
    
    Struct("tire_temps",
        LFloat32("frontleft_left"),
        LFloat32("frontleft_center"),
        LFloat32("frontleft_right"),
        
        LFloat32("frontright_left"),
        LFloat32("frontright_center"),
        LFloat32("frontright_right"),
        
        LFloat32("rearleft_left"),
        LFloat32("rearleft_center"),
        LFloat32("rearleft_right"),
        
        LFloat32("rearright_left"),
        LFloat32("rearright_center"),
        LFloat32("rearright_right"),
    ),

    SLInt32("num_penalties"),

    Struct("car_cg_location",
        LFloat32("x"),
        LFloat32("y"),
        LFloat32("z")
    ),
    
    Struct("car_orientation",
        LFloat32("pitch"),
        LFloat32("yaw"),
        LFloat32("roll"),
    ),

    Struct("local_acceleration",
        LFloat32("x"),
        LFloat32("y"),
        LFloat32("z")
    ),
    
    SLInt32("drs_available"),
    SLInt32("drs_engaged"),

    SLInt32("_padding1"),

    Struct("player",
        SLInt32("game_simulation_ticks"),
        LFloat64("game_simulation_time"),

        SLInt32("_padding1"),

        Struct("position",
            LFloat64("x"),
            LFloat64("y"),
            LFloat64("z")
        ),
        Struct("velocity",
            LFloat64("x"),
            LFloat64("y"),
            LFloat64("z")
        ),
        Struct("acceleration",
            LFloat64("x"),
            LFloat64("y"),
            LFloat64("z")
        ),
        Struct("local_acceleration",
            LFloat64("x"),
            LFloat64("y"),
            LFloat64("z")
        ),
        Struct("orientation",
            LFloat64("x"),
            LFloat64("y"),
            LFloat64("z")
        ),
        Struct("rotation",
            LFloat64("x"),
            LFloat64("y"),
            LFloat64("z")
        ),
        Struct("angular_acceleration",
            LFloat64("x"),
            LFloat64("y"),
            LFloat64("z")
        ),

        Struct("reserved1",
            LFloat64("x"),
            LFloat64("y"),
            LFloat64("z")
        )
    ),

    SLInt32("event_index"),
    SLInt32("session_type"),
    SLInt32("session_phase"),
    SLInt32("session_iteration"),
    SLInt32("control_type"),

    LFloat32("throttle_pedal"),
    LFloat32("brake_pedal"),
    LFloat32("clutch_pedal"),
    LFloat32("brake_bias"),

    Struct("tire_pressure",
        LFloat32("front_left"),
        LFloat32("front_right"),
        LFloat32("rear_left"),
        LFloat32("rear_right")
    ),

    SLInt32("tire_wear_active"),
    SLInt32("tire_type"),

    Struct("brake_temps",
        LFloat32("front_left"),
        LFloat32("front_right"),
        LFloat32("rear_left"),
        LFloat32("rear_right")
    ),

    SLInt32("fuel_use_active"),
    LFloat32("session_time_remaining"),
    LFloat32("lap_time_best_leader"),
    LFloat32("lap_time_best_leader_class"),
    LFloat32("reserved1"),
    LFloat32("lap_time_delta_leader"),
    LFloat32("lap_time_delta_leader_class"),

    Array(3, LFloat32("reserved2")),
    Array(3, LFloat32("reserved3")),
    Array(3, LFloat32("reserved4")),

    LFloat32("time_delta_front"),
    LFloat32("time_delta_behind"),

    SLInt32("pit_window_status"),
    SLInt32("pit_window_start"),
    SLInt32("pit_window_end"),

    SLInt32("cut_track_warnings"),

    Struct("penalties",
        SLInt32("drive_through"),
        SLInt32("stop_and_go"),
        SLInt32("pit_stop"),
        SLInt32("time_deduction"),
        SLInt32("slow_down")
    ),

    Struct("flags",
        SLInt32("yellow"),
        SLInt32("blue"),
        SLInt32("black")
    ),

    Struct("car_damage",
        LFloat32("engine"),
        LFloat32("transmission"),
        LFloat32("aerodynamics"),

        LFloat32("tire_front_left"),
        LFloat32("tire_front_right"),
        LFloat32("tire_rear_left"),
        LFloat32("tire_rear_right")
    )
)

def is_r3e_running():
    global process_name

    if dummy:
        return True
    
    for p in psutil.process_iter():
        try:
            if p.name() == process_name:
                return True
        except psutil.Error:
            break

    return False

def init_mmap():
    global shm

    if dummy:
        return

    shm = mmap.mmap(0, shared_size, tagname, mmap.ACCESS_READ)

def read_mem():
    global shm

    if dummy:
        return bytes(str(random.randint(40, 128)) * shared_size, "ascii")

    shm.seek(0)
    return shm.read(shared_size)

def parse(data):
    global shared_parser
    return shared_parser.parse(data)

