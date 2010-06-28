CXX = g++
COMPILE_FLAGS = -O3 -c
LINK_FLAGS =
SOURCE = ../Source
BINARY = ./

all: myginv

myginv: myginv.o involutive.o qset.o tset.o janettree.o triple.o polynom.o monomOld.o monomLex.o monomDL.o monomDRL.o allocator.o variables.o timer.o
	$(CXX) $(LINK_FLAGS) \
	    $(BINARY)/myginv.o \
	    $(BINARY)/involutive.o \
	    $(BINARY)/qset.o \
	    $(BINARY)/tset.o \
	    $(BINARY)/janettree.o \
	    $(BINARY)/triple.o \
	    $(BINARY)/polynom.o \
	    $(BINARY)/monomOld.o \
	    $(BINARY)/monomLex.o \
	    $(BINARY)/monomDL.o \
	    $(BINARY)/monomDRL.o \
	    $(BINARY)/allocator.o \
	    $(BINARY)/variables.o \
	    $(BINARY)/timer.o \
	    -o $(BINARY)/myginv
	@rm $(BINARY)/*.o

myginv.o: $(SOURCE)/timer.h $(SOURCE)/involutive.h
	$(CXX) $(COMPILE_FLAGS) $(SOURCE)/myginv.cpp -o $(BINARY)/myginv.o

involutive.o: $(SOURCE)/involutive.h $(SOURCE)/pcomparator.h
	$(CXX) $(COMPILE_FLAGS) $(SOURCE)/involutive.cpp -o $(BINARY)/involutive.o

tset.o: $(SOURCE)/tset.h
	$(CXX) $(COMPILE_FLAGS) $(SOURCE)/tset.cpp -o $(BINARY)/tset.o

qset.o: $(SOURCE)/qset.h
	$(CXX) $(COMPILE_FLAGS) $(SOURCE)/qset.cpp -o $(BINARY)/qset.o

janettree.o: $(SOURCE)/janettree.h
	$(CXX) $(COMPILE_FLAGS) $(SOURCE)/janettree.cpp -o $(BINARY)/janettree.o

triple.o: $(SOURCE)/triple.h
	$(CXX) $(COMPILE_FLAGS) $(SOURCE)/triple.cpp -o $(BINARY)/triple.o

polynom.o: $(SOURCE)/polynom.h $(SOURCE)/monom.h
	$(CXX) $(COMPILE_FLAGS) $(SOURCE)/polynom.cpp -o $(BINARY)/polynom.o

monomDRL.o: $(SOURCE)/monomDRL.h
	$(CXX) $(COMPILE_FLAGS) $(SOURCE)/monomDRL.cpp -o $(BINARY)/monomDRL.o

monomDL.o: $(SOURCE)/monomDL.h
	$(CXX) $(COMPILE_FLAGS) $(SOURCE)/monomDL.cpp  -o $(BINARY)/monomDL.o

monomLex.o: $(SOURCE)/monomLex.h
	$(CXX) $(COMPILE_FLAGS) $(SOURCE)/monomLex.cpp -o $(BINARY)/monomLex.o

monomOld.o: $(SOURCE)/monomOld.h
	$(CXX) $(COMPILE_FLAGS) $(SOURCE)/monomOld.cpp -o $(BINARY)/monomOld.o

allocator.o: $(SOURCE)/util.h
	$(CXX) $(COMPILE_FLAGS) $(SOURCE)/allocator.cpp -o $(BINARY)/allocator.o

variables.o: $(SOURCE)/util.h
	$(CXX) $(COMPILE_FLAGS) $(SOURCE)/variables.cpp -o $(BINARY)/variables.o

timer.o:
	$(CXX) $(COMPILE_FLAGS) $(SOURCE)/timer.cpp  -o $(BINARY)/timer.o
