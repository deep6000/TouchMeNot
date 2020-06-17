INCLUDE_DIRS = 
LIB_DIRS = 
CXX=g++-7

CDEFS=
CXXFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS) -w
LIBS=  -pthread 	
CPPLIBS= -L/usr/lib -lopencv_core -lopencv_flann -lopencv_video 


HFILES:= -I../inc/

CPPFILES= $(wildcard *.cpp)

CPPOBJS= $(CPPFILES:.cpp=.o)

all:	main


clean:
	-rm -f *.o
	-rm -f main

distclean:
	-rm -f *.o *.d


main: $(CPPOBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(CPPOBJS) `pkg-config --libs opencv` $(CPPLIBS) $(HFILES)  $(LIBS) -lrt


%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@  $(HFILES) $(LIBS)  -lrt 


