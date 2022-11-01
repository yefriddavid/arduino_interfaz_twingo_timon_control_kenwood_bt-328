
ROOT_DIR:=$(shell basename "$$PWD")
project :=$(ROOT_DIR)
#project := arduino_interfaz_twingo_timon_control_kenwood_bt-328
#project := home_inspector
port := /dev/ttyUSB0
# port := /dev/ttyACM0
dev-type := esp8266:esp8266:nodemcuv2
#dev-type := arduino:avr:uno

# basename "$PWD"


compile:
compile:
	arduino-cli compile --fqbn $(dev-type) $(project)

upload:
upload: compile
	arduino-cli upload --port $(port) --fqbn $(dev-type) $(project)

just-upload:
just-upload:
	arduino-cli upload --port $(port) --fqbn $(dev-type) $(project)

monitor:
monitor:
	arduino-cli monitor -p $(port)
