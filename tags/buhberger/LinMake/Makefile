CXX = g++
CXXFLAGS = -O3 -c
SOURCE = ../Source
BINARY = .

all: buhberger

buhberger: main.o version.o igroebner64.o poly64.o monom64.o iallocator.o ivariables.o timer.o
	$(CXX) \
            $(BINARY)/main.o \
            $(BINARY)/version.o \
            $(BINARY)/igroebner64.o \
            $(BINARY)/poly64.o \
            $(BINARY)/monom64.o \
            $(BINARY)/iallocator.o \
            $(BINARY)/ivariables.o \
            $(BINARY)/timer.o \
            -o $(BINARY)/buhberger
	@rm $(BINARY)/*.o

main.o: $(SOURCE)/init64.h $(SOURCE)/ivariables.h $(SOURCE)/igroebner64.h $(SOURCE)/version.h $(SOURCE)/timer.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/main.cpp -o $(BINARY)/main.o

version.o: $(SOURCE)/version.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/version.cpp -o $(BINARY)/version.o

igroebner64.o: $(SOURCE)/igroebner64.h $(SOURCE)/poly64.h $(SOURCE)/timer.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/igroebner64.cpp -o $(BINARY)/igroebner64.o

poly64.o: $(SOURCE)/poly64.h $(SOURCE)/monom64.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/poly64.cpp -o $(BINARY)/poly64.o

monom64.o: $(SOURCE)/monom64.h $(SOURCE)/ivariables.h $(SOURCE)/iallocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/monom64.cpp -o $(BINARY)/monom64.o

iallocator.o: $(SOURCE)/iallocator.h $(SOURCE)/iutil.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/iallocator.cpp -o $(BINARY)/iallocator.o

ivariables.o: $(SOURCE)/ivariables.h $(SOURCE)/iutil.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/ivariables.cpp -o $(BINARY)/ivariables.o

timer.o: $(SOURCE)/timer.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/timer.cpp  -o $(BINARY)/timer.o
