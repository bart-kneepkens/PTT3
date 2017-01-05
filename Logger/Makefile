CFLAGS=-O2 -Wall

LOGGERCENTRAL_SOURCE=LoggerCentral.cpp

MOCK_SOURCE=MockServer.cpp

MOCK_CENTRAL_SOURCE=MockCentral.cpp

GPP=g++

.PHONY: loggercentral mock mockcentral

loggercentral: 
	$(GPP) $(CFLAGS) -Wno-write-strings $(LOGGERCENTRAL_SOURCE) -o loggercentral -lrt -pthread

mock: 
	$(GPP) $(CFLAGS) -Wno-write-strings $(MOCK_SOURCE) -o mock -lrt  -pthread

mockcentral: 
	$(GPP) $(CFLAGS) -Wno-write-strings $(MOCK_CENTRAL_SOURCE) -o mockcentral -lrt  -pthread

clean:
	@rm -rf loggercentral mock mockcentral
