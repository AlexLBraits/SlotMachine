PROJECT_NAME=SlotMachine
SOIL=3rdparty/soil/lib/libSOIL.a
SRC=$(wildcard *.cpp)

CXXFLAGS += -std=c++11 -g
LDFLAGS += -L3rdparty/soil/lib -lSOIL

ifeq ($(OS),Windows_NT)
	CXXFLAGS += -I3rdparty/glut/include
	LDFLAGS += -L3rdparty/glut/lib -lopengl32 -lglu32 -lglut32
else
	UNAME=$(shell uname)
	ifeq ($(UNAME), Darwin)
	CXXFLAGS += -Wno-deprecated-declarations
	LDFLAGS += -framework GLUT -framework OpenGL
	endif
endif

all: $(SOIL) $(PROJECT_NAME) test

$(SOIL):
	mkdir 3rdparty/soil/lib || \
	cd 3rdparty/soil/projects/makefile && $(MAKE)

$(PROJECT_NAME): $(SRC)
	g++ -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

test:
	./$(PROJECT_NAME)

clean:
	rm -f $(PROJECT_NAME)
	rm -f $(SOIL)
	rm -f 3rdparty/soil/obj/*.o
