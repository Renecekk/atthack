# RasPi image

Info for curious attendees who wonder what exact changes were done to the Raspberry Pi OS they're handed.

## Getting an image

SD cards are pre-flashed by the mentors.  
Need a fresh image or a replacement card? Come to the **HW Koutek** and we'll replace it for you.

## What's on the image

Raspberry Pi OS **Lite** (64-bit, Debian 13 trixie), no desktop. There are two images: one for the Raspberry Pi 3 and one for the Raspberry Pi 5 (with or without the AI HAT+).

### Both images

* user `pi`, password `att4hack`, has `sudo` (also in the `gpio`, `i2c`, `spi`, `dialout` groups)
* `root` password is locked
* SSH enabled, password login allowed
* no desktop, so there is no VNC
* I2C and SPI enabled, camera auto-detect on
* stock clock speeds, no overclocking
* timezone Europe/Prague, US keyboard, `en_US.UTF-8` locale, Wi-Fi country CZ
* Wi-Fi `hackathon` on `wlan0`, DHCP on both `wlan0` and `eth0` (DHCP client ID = MAC)
* hostname `hack-XXXX` (last 4 hex digits of the Pi serial number), set on every boot as a transient hostname, so a hostname from DHCP wins
* mDNS via `systemd-resolved` (`hack-XXXX.local`), LLMNR off
* Python 3.13 with `gpiozero`, `lgpio`, `smbus2`, `spidev`
* `/etc/pip.conf`: `break-system-packages = true`, so `pip install` works without a venv
* `i2c-dev` module loaded
* zram swap (zstd), `vm.swappiness = 180`
* journal is volatile (RAM only, max 32 MB), so logs are lost on reboot
* no man pages or docs (`/etc/dpkg/dpkg.cfg.d/01-nodoc`)

Custom boot services (`/usr/local/sbin` + `/etc/systemd/system`):

* `set-hostname` - sets the `hack-XXXX` hostname
* `expand-rootfs` - grows the root partition to fill the SD card, every boot, no-op when already full
* `ssh-hostkeys` - generates unique SSH host keys on first boot
* `bt-retry` - re-binds the Bluetooth UART driver when the controller doesn't show up
* `audio-autodetect` - looks for I2C audio shields without an ID EEPROM on bus 1 (`0x1a` WM8960 / Codec Zero, `0x4c`/`0x4d` HiFiBerry DAC+, `0x3b` HiFiBerry Digi), writes the matching `dtoverlay` into `config.txt` and **reboots** when it changes

### Raspberry Pi 3 image extras

* `i2c-tools` (`i2cdetect`)
* `python3-pip`
* zram size = RAM

### Raspberry Pi 5 image extras

* Hailo 4.23.0: `hailort` (incl. `hailortcli` and `hailort.service`), `hailort-pcie-driver` (DKMS), `python3-hailort`, `hailo-models` (Hailo-10 models excluded)
* `rpicam-apps-lite` (camera CLI tools, e.g. `rpicam-hello`, `rpicam-still`)
* `python3-numpy`
* build tools: `build-essential`, kernel headers, `dkms`
* `pciutils`, `usbutils`, `net-tools`, `wget`, `rpi-eeprom`
* PCIe Gen 3 enabled for the HAT (`dtparam=pciex1_gen=3` in `config.txt`)
* zram size = min(RAM / 2, 4 GB)
* **not installed:** `i2c-tools`, `python3-pip`. Install them with `sudo apt install i2c-tools python3-pip`

## Useful commands

### List installed packages by their size

`dpkg-query --show --showformat='${Package;-50}\t${Installed-Size} ${Status}\n' | sort -k 2 -n |grep -v deinstall`

```sh
apt remove <pkg>
apt purge <pkg>
apt autoremove
```

### Network configuration

The Lite image uses `systemd-networkd` + `wpa_supplicant`, not NetworkManager.

* Wired / wireless DHCP: `/etc/systemd/network/20-wired.network`, `/etc/systemd/network/25-wireless.network`
* Wi-Fi credentials: `/etc/wpa_supplicant/wpa_supplicant-wlan0.conf`

Apply changes with `sudo systemctl restart systemd-networkd wpa_supplicant@wlan0`.
