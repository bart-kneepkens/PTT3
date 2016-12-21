CFLAGS=-O2 -Wall

LOGGERCENTRAL_SOURCE=LoggerCentral.cpp

MOCK_SOURCE=MockServer.cpp

GPP=g++

.PHONY: loggerCentral mock

loggerCentral: 
	$(GPP) $(CFLAGS) $(LOGGERCENTRAL_SOURCE) -o loggerCentral -lrt

mock: 
	$(GPP) $(CFLAGS) -Wno-write-strings $(MOCK_SOURCE) -o mock -lrt 

clean:
	@rm -rf loggerCentral mock
