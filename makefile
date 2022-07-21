CC = g++

TARGET = robotspoofenabled
SRC_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp, obj/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	g++ -o $@ $^

obj/%.o: src/%.cpp | obj
	g++ -Iinclude -c -o $@ $<

obj:
	mkdir -p $@

clean:
	rm -f obj/*
	rm -f $(TARGET)