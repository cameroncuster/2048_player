SOURCE_DIR = src

INCLUDE_DIR = inc

COMMON_SRC = $(SOURCE_DIR)/board.cpp $(SOURCE_DIR)/game.cpp $(SOURCE_DIR)/player.cpp $(SOURCE_DIR)/btoi.cpp

CONSOLE_SRC = $(SOURCE_DIR)/driver.cpp

GRAPHICS_SRC = $(SOURCE_DIR)/main.cpp $(SOURCE_DIR)/event.cpp $(SOURCE_DIR)/util.cpp $(SOURCE_DIR)/loadBMP.cpp $(SOURCE_DIR)/graphics.cpp

CONSOLE_OBJS = $(CONSOLE_SRC:.cpp=.o) $(COMMON_SRC:.cpp=.o)
GRAPHICS_OBJS = $(GRAPHICS_SRC:.cpp=.o) $(COMMON_SRC:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
CFLAGS = -Wall -O3 -std=c++11 -I $(INCLUDE_DIR)
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
	rm -rf $(SOURCE_DIR)/*.o $(SOURCE_DIR)/*.d core graphics console

graphics: CXXFLAGS = -DGRAPHICS -O3 -Wall -std=c++11 -I $(INCLUDE_DIR)

debug: CXXFLAGS = -DDEBUG -g -std=c++11 -I $(INCLUDE_DIR)
debug: OBJS += $(CONSOLE_OBJS)
debug: console

tar: clean
	tar zcvf 2048_player.tgz $(SOURCE) $(INCLUDE_DIR)/*.h Makefile

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
