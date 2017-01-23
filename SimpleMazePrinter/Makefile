CFLAGS=-O2 -Wall

SOURCES=SimpleMazePrinter.cpp \
    ../maze_parser/MazeMessage.cpp \
    ../maze_parser/MazeParser.cpp \
    ../SocketUtils/SocketUtils.cpp \
    ../Generic\ Module\ Client/ModuleClient.cpp

GPP=g++

solver: $(SOURCES)
	$(GPP) $(CFLAGS) $(SOURCES) -o SimpleMazePrinter -pthread

clean:
	@rm -rf SimpleMazePrinter
