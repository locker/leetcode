CXXFLAGS := -Wall

all: solution

solution: solution.cpp

clean:
	$(RM) solution

.PHONY: clean
