# Getting started with our Raspberry Pi

Hello, in front of you is a Raspberry Pi (3 or 5) with a pre-flashed SD card running Raspberry Pi OS.  
Need a fresh image or a new SD card? Come to the **HW Koutek** and we'll replace it for you.

What's on the image is described in [raspberry_image_prep.md](raspberry_image_prep.md).

## Network / How to connect

### Wi-Fi

Raspberry is set to connect automatically to the `hackathon` wifi network. Ethernet uses DHCP too.  
IP address is assigned by our DHCP server and should match the number on the label of the board:  
RasPi01 = 10.10.1.1  
RasPi02 = 10.10.1.2  
and so on...

**Exception:** the Raspberry Pi 5 8 GB boards with the AI HAT+ (Hailo) are not in the DHCP bindings. Ask at the HW Koutek for their IP.

Each Pi also names itself `hack-XXXX` (last 4 hex digits of its serial number) and answers mDNS, so `ssh pi@hack-XXXX.local` works too.

## Access & Passwords

Available connections:

* SSH for CLI.
* SFTP/SCP for file transfer.
* No VNC / GUI. The image is Raspberry Pi OS Lite without a desktop.

The same credentials are on all the boards.  
**Change the password (`passwd`) as a first step** so other teams can't get into your device.

| Account | Password |
| ------- | -------- |
| pi      | att4hack |

The `root` account is locked. The `pi` user has `sudo`.

I2C and SPI are already enabled. Other interfaces (serial port, 1-Wire, ...) can be enabled with `sudo raspi-config` → Interface Options.

## Good to know

* `pip install` works system-wide, no venv needed.
* Raspberry Pi 5 image: `i2c-tools` and `pip` are not installed. Run `sudo apt install i2c-tools python3-pip`.
* **Audio shield auto-detect:** on boot the Pi scans I2C bus 1. If something answers on `0x1a`, `0x4c`, `0x4d` or `0x3b`, it gets treated as an audio shield: an overlay is written into `config.txt` and **the Pi reboots**. If your sensor uses one of these addresses (e.g. an INA219 with its address jumpers set) and the Pi reboots on its own:
  1. disable it with `sudo systemctl disable audio-autodetect`
  2. delete the `# audio-autodetect begin` … `# audio-autodetect end` block from `/boot/firmware/config.txt`
  3. reboot
* Logs (`journalctl`) are kept in RAM only and are lost on reboot.
* No man pages are installed. Use `--help` or the web.
* The root filesystem grows to fill the SD card automatically.

Full list of what's on the image: [raspberry_image_prep.md](raspberry_image_prep.md).

## Connectivity

Schematics: https://www.jameco.com/Jameco/workshop/circuitnotes/raspberry-pi-circuit-note.html  
GPIO pinout details: https://pinout.xyz

## Raspberry Pi 5

8 GB RAM version.  
Specs: https://www.raspberrypi.com/products/raspberry-pi-5/  
Docs: https://www.raspberrypi.com/documentation/computers/raspberry-pi.html

Use the official 27 W USB-C power supply. Weaker supplies cause throttling and limit USB power.  
The camera connectors are the smaller 22-pin type, so older Pi cameras need an adapter cable.

## AI HAT+

Some of our Raspberry Pi 5 boards come with the AI HAT+, a 26 TOPS Hailo-8 AI accelerator connected over PCIe.  
It runs neural network inference such as object detection, pose estimation and segmentation on the camera stream.

The HailoRT runtime (`hailortcli`), PCIe driver, Python bindings (`python3-hailort`) and Hailo models are pre-installed on the Pi 5 image.

Product page: https://www.raspberrypi.com/products/ai-hat/  
Docs: https://www.raspberrypi.com/documentation/accessories/ai-hat-plus.html  
Examples: https://github.com/hailo-ai/hailo-rpi5-examples

Quick check that the accelerator is detected:

```sh
hailortcli fw-control identify
```

## Sense HAT

Python library is **not** pre-installed. Install it with `sudo apt install python3-sense-hat`.  
Sense HAT provides following for the Raspberry:  

* Temperature
* Humidity
* Barometric pressure
* Gyroscope
* Acceletometer
* Magnetometer
* Joystick
* 8x8 RGB LED matrix

API reference: https://pythonhosted.org/sense-hat/api/  
Tutorial: https://www.raspberrypi.com/documentation/accessories/sense-hat.html
  
## Pi AI Camera

**Specs:**  
https://www.raspberrypi.com/products/ai-camera/

* 12MP sensor Sony IMX500
* Video modes:
  * 4056×3040 @ 10fps
  * 2028×1520 @ 30fps

**How to:**

The IMX500 firmware and models are **not** pre-installed. Install them first, then reboot:  
`sudo apt install imx500-all`

https://www.raspberrypi.com/news/how-to-get-started-with-your-raspberry-pi-ai-camera/

## Pi Camera

Camera is connected over the CSI interface on the mainboard.  
The camera tools (`rpicam-apps`) are pre-installed on the Raspberry Pi 5 image.  
Docs: https://www.raspberrypi.com/documentation/computers/camera_software.html

```sh
# list detected cameras
rpicam-hello --list-cameras

# check the camera works (no preview window on a headless Pi, runs for 5 s)
rpicam-hello -n -t 5000

# take a still image
rpicam-still -n -o test.jpg
```

Copy the image to your laptop with `scp pi@<ip>:test.jpg .`

**Tech. specs**:

* Still images: 8 Mpx (3280x2464)
* Video modes:
  * 1920x1080 @ 30 fps
  * 1280x720 @ 60 fps
  * 640x480 @ 90 fps

## Speaker pHAT

Audio HAT containing amplifier, speaker and LED bar graph for projects requiring audio output.  
Pi Zero form factor.  
Tech. details: https://web.archive.org/web/20210725202304/https://shop.pimoroni.com/products/speaker-phat  
HAT installer: https://github.com/pimoroni/speaker-phat

## Explorer pHAT

HAT to extend Pi with 5V input/output, analog input,  
Pi Zero form factor.  
Installer: https://github.com/pimoroni/explorer-hat  
Documentation: https://github.com/pimoroni/explorer-hat/blob/master/documentation/Function-reference.md
