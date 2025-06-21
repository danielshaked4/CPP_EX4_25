#  Email: sone0149@gmail.com


CXX = g++
CXXFLAGS = -Wall -std=c++17

# make Main - run the demo file
Main: Demo.cpp MyContainer.hpp
	$(CXX) $(CXXFLAGS) Demo.cpp -o demo
	./demo

# make test - run unit tests
test: test_mycontainer.cpp MyContainer.hpp
	$(CXX) $(CXXFLAGS) test_mycontainer.cpp -o test
	./test

# make valgrind - check memory leaks using valgrind
valgrind: Demo.cpp MyContainer.hpp
	$(CXX) $(CXXFLAGS) -g Demo.cpp -o demo
	valgrind --leak-check=full ./demo

# make clean - remove all files after execution
clean:
	rm -f demo test *.o

.PHONY: Main test valgrind clean