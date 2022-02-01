UNAME= $(shell uname -s)

VERSION=311

##########FLAGS
CXXFLAGS=-fopenmp
CXX=g++
OBLIB= -fopenmp
LDFLAGS= $(OBLIB) -lboost_serialization

all: main


dev-src=\
./dev-src/emptynode.cpp \
./dev-src/node.cpp \
./dev-src/nodelist.cpp \
./dev-src/lattice.cpp \

OBJ=$(addsuffix .o , $(basename $(dev-src)))
OBJDEBUG=$(addsuffix _debug.o , $(basename $(dev-src)))

CXXFLAGS += -std=gnu++11 -Idev-src  -c -pipe  -O2   -Wall -Wextra -Wno-unused-parameter


%o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

main : main.o $(OBJ)
	$(CXX) $^ -o $@  $(LDFLAGS)





#-stdlib=libc++ -O2 


LDFLAGS= $(OBLIB) -lboost_serialization
 


%_debug.o:%.cpp 
	$(CXX) -o $@ -c $< $(CXXFLAGSDEBUG)

%o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)




clean :
	rm -f $(OBJ) $(OBJDEBUG)  *.o  main


depend:
	$(MAKEDEPEND) -- $(CXXFLAGS) -- $(dev-src)

main.cpp: dev-src/lattice.hpp

dev-src/emptynode.o: dev-src/emptynode.cpp dev-src/emptynode.hpp
dev-src/emptynode.hpp:

dev-src/node.o: dev-src/node.cpp dev-src/node.hpp dev-src/emptynode.hpp dev-src/layout.hpp dev-src/intent.hpp
dev-src/node.hpp: dev-src/emptynode.hpp dev-src/layout.hpp dev-src/intent.hpp

dev-src/nodelist.o: dev-src/nodelist.cpp dev-src/nodelist.hpp dev-src/node.hpp
dev-src/nodelist.hpp: dev-src/node.hpp

dev-src/lattice.o: dev-src/lattice.cpp dev-src/lattice.hpp dev-src/nodelist.hpp
dev-src/lattice.hpp: dev-src/nodelist.hpp
