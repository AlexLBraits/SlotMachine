PROJECT_NAME=SlotMachine
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

all: $(PROJECT_NAME) test

$(PROJECT_NAME): $(SRC)
	g++ -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

test:
	./$(PROJECT_NAME)

clean:
	rm -f $(PROJECT_NAME)