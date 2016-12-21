CFLAGS=-O2 -Wall

LOGGERCENTRAL_SOURCE=LoggerCentral.cpp

MOCK_SOURCE=MockServer.cpp

GPP=g++

.PHONY: loggercentral mock

loggercentral: 
	$(GPP) $(CFLAGS) $(LOGGERCENTRAL_SOURCE) -o loggercentral -lrt -pthread

mock: 
	$(GPP) $(CFLAGS) -Wno-write-strings $(MOCK_SOURCE) -o mock -lrt  -pthread

clean:
	@rm -rf loggercentral mock
