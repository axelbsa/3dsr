CC=g++
CFLAGS=-O2 -Wall -std=c++11 -Wno-missing-braces

#Windows Flags
#LFLAGS=-lraylib -lopengl32 -lraylib -lglfw3 -lgdi32

# Linux flags
LFLAGS=-lraylib -lglfw3 -lX11 -lXxf86vm -lXrandr -ldl -lXinerama -lXcursor -lGL -lGLU -lpthread

SOURCES=main.cpp

all:
	$(CC) $(SOURCES) $(CFLAGS) $(LFLAGS) -o ray.exe

debug:
	$(CC) -DDEBUG $(SOURCES) $(CFLAGS) $(LFLAGS) -o ray.exe

clean:
	del ray.exe
