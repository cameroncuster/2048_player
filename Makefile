COMMON_SRC = src/board.cpp src/game.cpp src/player.cpp src/btoi.cpp

CONSOLE_SRC = src/driver.cpp

GRAPHICS_SRC = src/main.cpp src/event.cpp src/util.cpp src/loadBMP.cpp src/graphics.cpp

CONSOLE_OBJS = $(CONSOLE_SRC:.cpp=.o) $(COMMON_SRC:.cpp=.o)
GRAPHICS_OBJS = $(GRAPHICS_SRC:.cpp=.o) $(COMMON_SRC:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
INC =
CFLAGS = -Wall -O3 -std=c++11 -I inc
CXXFLAGS = $(CFLAGS)

# Fill in special libraries needed here
LIBS = -lglut -lGL -lGLU -lpthread

.PHONY: clean

# Targets include all, clean, debug, tar

all : help

graphics: $(GRAPHICS_OBJS)
	$(LINK) -o $@ $^ $(LIBS)

console: $(CONSOLE_OBJS)
	$(LINK) -o $@ $^ $(LIBS)

clean:
	rm -rf src/*.o src/*.d core graphics console

graphics: CXXFLAGS = -DGRAPHICS -O3 -Wall -std=c++11 -I inc

debug: CXXFLAGS = -DDEBUG -g -std=c++11 -I inc
debug: OBJS += $(CONSOLE_OBJS)
debug: console

tar: clean
	tar zcvf 2048_player.tgz $(SOURCE) inc/*.h Makefile

help:
	@echo "You can build the game either with graphics (make graphics)"
	@echo "or in console (make console) mode"
	@echo ""
	@echo "Graphics will display the game board for every move"
	@echo "You can set the play speed by adding a millisecond value"
	@echo "On the command line:"
	@echo ""
	@echo "% graphics 50"
	@echo "% console"
	@echo ""
	@echo "In console mode, the game will play to completion and report"
	@echo "The score, the average time per turn, and the max tile achieved"

-include $(CONSOLE_SRC:.cpp=.d) $(COMMON_SRC:.cpp=.d) $(GRAPHICS_SRC:.cpp=.d)

%.d: %.cpp
	@set -e; /bin/rm -rf $@;$(GCC) -MM $< $(CXXFLAGS) > $@
