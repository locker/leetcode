CXXFLAGS := -Wall -Werror -std=c++17

all: solution

solution: solution.cpp

clean:
	$(RM) solution

.PHONY: clean
