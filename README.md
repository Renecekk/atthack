# AT&T Hackathon Junior 2026

This repository aims to provide basic info about hardware which is available to participants of AT&T Brno Hackathons.

> Lovingly yoinked from [neaxi/atthackbrno](https://github.com/neaxi/atthackbrno). Big thanks to neaxi, who built and maintained the hackathon HW before handing it over.

## Platforms

* [Raspberry Pi 5 (8 GB)](raspberry.md#raspberry-pi-5)
  * [AI HAT+](raspberry.md#ai-hat)
* [Raspberry Pi 3](raspberry.md)
  * [Sense HAT](raspberry.md#sense-hat)
  * [Pi Cam](raspberry.md#pi-camera)
  * [Speaker pHAT](raspberry.md#speaker-phat)
  * [Explorer pHAT](raspberry.md#explorer-phat)

* [Texas Instruments MSP430](TI_MSP430.md)

* [ESP32 - LILYGO, Pycom, LaskaKit](esp32.md)

## Sensors & peripherals

List of components, sensors and peripherals which can be borrowed from us.  
**List is non-exhaustive - feel free to ask for anything else coming up to your mind.**  
 We might have it and it's just not listed or we can help you to figure out a workaround.

Generic electro:

* [breadboard kits](https://dratek.cz/martin/7321-lafvin-elektro-soucastky-rozsirujici-kit-s-nepajivym-polem.html)
* 3.3V <> 5V logic convertors
* ADC convertors
* voltage stepdown regulators

For tutorial links and datasheets for some of our sensors, please see following page with [details](sensors.md)  

What needs to be done? And what can we offer:

**Signalization?**

* Addressable LEDs (WS2813), OLED displays
  * WS2813 - https://www.sdiplight.com/ws2813-led-strip/
  * OLED - https://learn.adafruit.com/monochrome-oled-breakouts/python-wiring
* E-Ink display 12956

**Temperature, humidity and atmospheric pressure?**

* DHT22, BME280

**Air, water and colors, lights?**

* Dust sensor (SHARP GP2Y1010AU0F)
* Water flow (YF-S201, YF-B1)
* photoresistors, color detector HW-067
* [MQ2-MQ135 gas sensor kit](https://dratek.cz/arduino/1616-sada-mq2-mq135-senzoru-snimacu-detekce-plynu-pro-mini-5v-controller.html)

**Distance and surrounding?**

* Ultrasound range (HC-SR04), MW radar (RCWL-0516)
* distance & gesture sensor (GY-9960-LLC), Magnetic relays

**Movement?**

* PIR motion sensor (HC SR501)
* Gyro and accelerometer (MPU-6050, BMI270)
* servos, H-bridges, ...

**Access identification?**

* RFID - RC512, YSoft keyboard reader

**Generic 37 pcs sensor kit?**

* [sellers info](https://www.laskakit.cz/laskkit-37-sada-senzoru-37-v-1/)
* check our [details page](sensors.md) for description of the sensors and basic documentation  
* [37 pcs sensor kit photo leaflet](sensor_kit_leaflet.pdf)

**Power? Voltage? Current?**

* INA219 + INA3221 - https://learn.adafruit.com/adafruit-ina219-current-sensor-breakout/python-circuitpython

* Debugging?
  * Stabilized power supply, oscilloscope, voltmeters, ...
