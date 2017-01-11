CFLAGS=-O2 -Wall

LEDCONTROLLER_SOURCE=ServerMock.cpp

GPP=arm-linux-g++

.PHONY: controller

controller:
	$(GPP) $(CFLAGS) $(LEDCONTROLLER_SOURCE) -o controller

clean:
	@rm -rf controller