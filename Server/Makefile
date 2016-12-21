CFLAGS=-O2 -Wall

SERVER_SOURCE=server.cpp

MOCK_SOURCE=MockModule.cpp

GPP=g++

.PHONY: server mock

server: 
	$(GPP) -O2 -Wall $(SERVER_SOURCE) Auxiliary.c -o server -pthread

mock: 
	$(GPP) -O2 -Wall $(MOCK_SOURCE) Auxiliary.c CreateTCPClientSocket.c -o mock 

clean:
	@rm -rf server mock