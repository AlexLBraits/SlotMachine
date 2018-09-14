PROJECT_NAME := SlotMachine

ifeq ($(OS),Windows_NT)
	CXXFLAGS += -Iglut/include
	LDFLAGS += -L3rdparty/glut/lib -lopengl32 -lglu32 -lglut32
else
	UNAME := $(shell uname)
	ifeq ($(UNAME), Darwin)
	CXXFLAGS += -Wno-deprecated-declarations
	LDFLAGS += -framework GLUT -framework OpenGL
	endif
endif

all: $(PROJECT_NAME) test

$(PROJECT_NAME): main.cpp
	g++ -o $(PROJECT_NAME) main.cpp $(LDFLAGS)

test:
	./$(PROJECT_NAME)

clean:
	rm -f $(PROJECT_NAME)