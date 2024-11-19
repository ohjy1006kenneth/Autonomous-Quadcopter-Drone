BOARD?=arduino:megaavr:nona4809
PORT=$(shell ls /dev/ttyACM* | head -n 1)
BUILD=build/

.PHONY: default all flash clean

default: all flash clean

all:
	arduino-cli compile --fqbn $(BOARD) --output-dir $(BUILD) --libraries=/home/juyoungoh/sdk/Arduino/libraries ./

flash:
	arduino-cli upload --fqbn $(BOARD) --port $(PORT) --input-dir $(BUILD)

clean:
	rm -rf $(BUILD)