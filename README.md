# RESTfan

A REST controllable wall fan

We bought a cheap wall mount fan which had pull strings for control. Big no no for a Hackerspace :sunglasses:

So we created a small PCB with a 230VAC to 5VDC converter, a Wemos D1 mini and 4 relays on it that allows us to control the fan over a REST API.

# Hardware

We use these components in this project:
 - Fan: [Tristar VE-5874 wall mount ventilator](https://www.tristar.eu/de-de/tristar-ve-5874-wandventilator-ve--5874)
 - AC/DC converter: [HiLink HLK-PM01](http://www.hlktech.net/product_detail.php?ProId=54)
 - Relays: [Finder 30.22](https://www.finder-relais.net/de/finder-relais-serie-30.pdf)
 - ESP8266 Board: [Wemos D1 mini](https://www.wemos.cc/en/latest/d1/d1_mini.html)


# UI

We use [ESPHome](https://esphome.io/) to control the fan as it integrates nicely with [Home Assistant](https://www.home-assistant.io/) which powers our PowerCommander. 
 
