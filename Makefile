CXX = g++
CXXFLAGS = -I/usr/include/eigen3 -std=c++11 -O2
TARGET = main
SOURCES = main.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: clean
