CXX = g++
CXXFLAGS = -O3 -c
SOURCE = ../Source
BINARY = .

all: myginv

myginv: myginv.o involutive64.o janettree64.o poly64.o monom64.o allocator.o variables.o timer.o
	$(CXX) \
            $(BINARY)/myginv.o \
            $(BINARY)/involutive64.o \
            $(BINARY)/janettree64.o \
            $(BINARY)/poly64.o \
            $(BINARY)/monom64.o \
            $(BINARY)/allocator.o \
            $(BINARY)/variables.o \
            $(BINARY)/timer.o \
            -o $(BINARY)/myginv
	@rm $(BINARY)/*.o

myginv.o: $(SOURCE)/init64.h $(SOURCE)/variables.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/myginv.cpp -o $(BINARY)/myginv.o

involutive64.o: $(SOURCE)/involutive64.h $(SOURCE)/janettree64.h $(SOURCE)/timer.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/involutive64.cpp -o $(BINARY)/involutive64.o

janettree64.o: $(SOURCE)/janettree64.h $(SOURCE)/poly64.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/janettree64.cpp -o $(BINARY)/janettree64.o

poly64.o: $(SOURCE)/poly64.h $(SOURCE)/monom64.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/poly64.cpp -o $(BINARY)/poly64.o

monom64.o: $(SOURCE)/monom64.h $(SOURCE)/variables.h $(SOURCE)/allocator.h $(SOURCE)/util.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/monom64.cpp -o $(BINARY)/monom64.o

allocator.o: $(SOURCE)/allocator.h $(SOURCE)/util.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/allocator.cpp -o $(BINARY)/allocator.o

variables.o: $(SOURCE)/variables.h $(SOURCE)/util.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/variables.cpp -o $(BINARY)/variables.o

timer.o: $(SOURCE)/timer.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/timer.cpp  -o $(BINARY)/timer.o
