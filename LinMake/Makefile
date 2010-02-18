CXX = g++
CXXFLAGS = -O3 -c
SOURCE = ../Source
BINARY = .

all: myginv

myginv: myginv.o involutive.o qset.o tset.o janettree.o triple.o polynom.o monomDL.o monomDRL.o monomLex.o monomOld.o allocator.o variables.o timer.o
	$(CXX) \
            $(BINARY)/myginv.o \
            $(BINARY)/involutive.o \
            $(BINARY)/qset.o \
            $(BINARY)/tset.o \
            $(BINARY)/janettree.o \
            $(BINARY)/triple.o \
            $(BINARY)/polynom.o \
            $(BINARY)/monomDL.o \
            $(BINARY)/monomDRL.o \
            $(BINARY)/monomLex.o \
            $(BINARY)/monomOld.o \
            $(BINARY)/allocator.o \
            $(BINARY)/variables.o \
            $(BINARY)/timer.o \
            -o $(BINARY)/myginv
	@rm $(BINARY)/*.o

myginv.o: $(SOURCE)/involutive.h $(SOURCE)/timer.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/myginv.cpp -o $(BINARY)/myginv.o

involutive.o: $(SOURCE)/involutive.h $(SOURCE)/qset.h $(SOURCE)/tset.h $(SOURCE)/timer.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/involutive.cpp -o $(BINARY)/involutive.o

qset.o: $(SOURCE)/qset.h $(SOURCE)/triple.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/qset.cpp -o $(BINARY)/qset.o

tset.o: $(SOURCE)/tset.h $(SOURCE)/janettree.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/tset.cpp -o $(BINARY)/tset.o

janettree.o: $(SOURCE)/janettree.h $(SOURCE)/triple.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/janettree.cpp -o $(BINARY)/janettree.o

triple.o: $(SOURCE)/triple.h $(SOURCE)/polynom.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/triple.cpp -o $(BINARY)/triple.o

polynom.o: $(SOURCE)/polynom.h $(SOURCE)/monomDL.h $(SOURCE)/monomDRL.h $(SOURCE)/monomLex.h $(SOURCE)/monomOld.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/polynom.cpp -o $(BINARY)/polynom.o

monomDL.o: $(SOURCE)/monomDL.h $(SOURCE)/variables.h $(SOURCE)/allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/monomDL.cpp -o $(BINARY)/monomDL.o

monomDRL.o: $(SOURCE)/monomDRL.h $(SOURCE)/variables.h $(SOURCE)/allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/monomDRL.cpp -o $(BINARY)/monomDRL.o

monomLex.o: $(SOURCE)/monomLex.h $(SOURCE)/variables.h $(SOURCE)/allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/monomLex.cpp -o $(BINARY)/monomLex.o

monomOld.o: $(SOURCE)/monomOld.h $(SOURCE)/variables.h $(SOURCE)/allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/monomOld.cpp -o $(BINARY)/monomOld.o

allocator.o: $(SOURCE)/allocator.h $(SOURCE)/util.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/allocator.cpp -o $(BINARY)/allocator.o

variables.o: $(SOURCE)/variables.h $(SOURCE)/util.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/variables.cpp -o $(BINARY)/variables.o

timer.o: $(SOURCE)/timer.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/timer.cpp  -o $(BINARY)/timer.o
