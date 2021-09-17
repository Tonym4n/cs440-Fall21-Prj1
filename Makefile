CXX := 		g++
CXXFLAGS :=	-g -Wall -std=c++17
VPATH :=	.

test:		test.o
			$(CXX) $^ -o $@

template:	template.cpp
			$(CXX) $^ -o $@

clean:	
			rm -f *.o *~ *.gch test template

#dependencies
test.o:		test.cpp Deque.hpp
			$(CXX) $(CXXFLAGS) -c $^
template.o:	template.cpp