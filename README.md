# About

r3e-dashboard is a simple Web based dashboard for RaceRoom Racing Experience.
It is more or less an incomplete proof of concept that has mainly been created for learning purposes but I might use it as a starting point for future projects.
It is likely that the code no longer works since the R3E shared data structure might have been updated already.

The server tool is written in Python and uses asyncio and aiohttp for asynchronous tasks and HTTP stuff.
On the browser side jQuery Mobile, jQuery Flot and Backbone.js are used.

# Screenshots

![Overview](https://github.com/pckbls/r3e-dashboard/raw/master/img/screenshot_overview.png)
![Charts](https://github.com/pckbls/r3e-dashboard/raw/master/img/screenshot_charts.png)

# How to run

Simply run `dashboard.py`, launch R3E and open `http://localhost:8080` in your browser.
Instead of using live data from R3E you can use recorded data for testing purposes, e.g.:
```sh
dashboard.py ./recordings/norisring.data
```

