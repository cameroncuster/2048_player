COMMON_SRC = board.cpp game.cpp greedyPlayer.cpp

CONSOLE_SRC = driver.cpp

GRAPHICS_SRC = main.cpp event.cpp util.cpp loadBMP.cpp graphics.cpp

CONSOLE_OBJS = $(CONSOLE_SRC:.cpp=.o) $(COMMON_SRC:.cpp=.o)
GRAPHICS_OBJS = $(GRAPHICS_SRC:.cpp=.o) $(COMMON_SRC:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
INC =
CFLAGS = -Wall -O3 -std=c++11
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
	rm -rf *.o *.d core graphics console

graphics: CXXFLAGS = -DGRAPHICS -O3 -Wall -std=c++11

debug: CXXFLAGS = -DDEBUG -g -std=c++11
debug: OBJS += $(CONSOLE_OBJS)
debug: console

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
