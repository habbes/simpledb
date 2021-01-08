TARGET=bin/simpledb

all: $(TARGET)

$(TARGET): build
	$(CXX) -std=c++11 -o bin/simpledb src/simpledb.cpp

build:
	@mkdir -p bin