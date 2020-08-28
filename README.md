# RESTfan

A REST controllable wall fan

We bought a cheap wall mount fan which had pull strings for control. Big no no for a Hackerspace :sunglasses:

So we created a small PCB with a 230VAC to 5VDC converter, a Wemos D1 mini and 4 relays on it that allows us to control the fan over a REST API.

# Hardware

The fan is a [Tristar VE-5874 wall mount ventilator](https://www.tristar.eu/de-de/tristar-ve-5874-wandventilator-ve--5874)

# API

- `http://<ip>/off` Fan and oscillation off
- `http://<ip>/state` JSON object with the current state

## Speed control

 - `http://<ip>/speed/1` Fan speed 1
 - `http://<ip>/speed/2` Fan speed 2
 - `http://<ip>/speed/3` Fan speed 3

## Oscillation

 - `http://<ip>/oscillation/on` Oscillation on
 - `http://<ip>/oscillation/off` Oscillation off
 
 
