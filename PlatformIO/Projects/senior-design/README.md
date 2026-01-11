# ESP32 PlatformIO (WSL) – Single Command Reference

# 1. Windows PowerShell (run when ESP32 is plugged in or reconnects)
usbipd list
DO ONCE: usbipd bind --busid (bus id) 
usbipd attach --wsl --busid (bus id)

# 2. WSL: build, upload, run
cd ~/College-Coding/PlatformIO/Projects/senior-design
pio run
pio run -t upload --upload-port /dev/ttyUSB0
pio device monitor --port /dev/ttyUSB0 --baud 115200

# Press EN to reset and see output
