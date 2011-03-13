CXX = g++
CXXFLAGS = -O3 -c
SOURCE = ../Source
BINARY = .

all: myginv

clear:
	@rm $(BINARY)/*.o
	@rm $(BINARY)/myginv

myginv: myginv.o \
        launcher.o \
        version.o \
        groebner_basis.o \
        qset.o \
        tset.o \
        janettree.o \
        triple.o \
        settings_manager.o \
        resource_counter.o \
        polynom.o \
        monom.o \
        fast_allocator.o \
        variables.o \
        timer.o
	$(CXX) \
            $(BINARY)/myginv.o \
            $(BINARY)/launcher.o \
            $(BINARY)/version.o \
            $(BINARY)/groebner_basis.o \
            $(BINARY)/qset.o \
            $(BINARY)/tset.o \
            $(BINARY)/janettree.o \
            $(BINARY)/triple.o \
            $(BINARY)/settings_manager.o \
            $(BINARY)/resource_counter.o \
            $(BINARY)/polynom.o \
            $(BINARY)/monom.o \
            $(BINARY)/fast_allocator.o \
            $(BINARY)/variables.o \
            $(BINARY)/timer.o \
            -o $(BINARY)/myginv
	@rm $(BINARY)/*.o

myginv.o: $(SOURCE)/launcher.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/myginv.cpp -o $(BINARY)/myginv.o

launcher.o: $(SOURCE)/groebner_basis.h $(SOURCE)/polynom.h $(SOURCE)/fast_allocator.h $(SOURCE)/launcher.h $(SOURCE)/resource_counter.h $(SOURCE)/settings_manager.h $(SOURCE)/version.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/launcher.cpp -o $(BINARY)/launcher.o

version.o: $(SOURCE)/version.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/version.cpp -o $(BINARY)/version.o

groebner_basis.o: $(SOURCE)/qset.h $(SOURCE)/tset.h $(SOURCE)/groebner_basis.h $(SOURCE)/pcomparator.h $(SOURCE)/resource_counter.h $(SOURCE)/settings_manager.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/groebner_basis.cpp -o $(BINARY)/groebner_basis.o

tset.o: $(SOURCE)/tset.h $(SOURCE)/janettree.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/tset.cpp -o $(BINARY)/tset.o

qset.o: $(SOURCE)/qset.h $(SOURCE)/triple.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/qset.cpp -o $(BINARY)/qset.o

janettree.o: $(SOURCE)/janettree.h $(SOURCE)/triple.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/janettree.cpp -o $(BINARY)/janettree.o

triple.o: $(SOURCE)/triple.h $(SOURCE)/polynom.h $(SOURCE)/fast_allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/triple.cpp -o $(BINARY)/triple.o

settings_manager.o: $(SOURCE)/settings_manager.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/settings_manager.cpp  -o $(BINARY)/settings_manager.o

resource_counter.o: $(SOURCE)/timer.h $(SOURCE)/fast_allocator.h $(SOURCE)/resource_counter.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/resource_counter.cpp  -o $(BINARY)/resource_counter.o

polynom.o: $(SOURCE)/polynom.h $(SOURCE)/monom.h $(SOURCE)/fast_allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/polynom.cpp -o $(BINARY)/polynom.o

monom.o: $(SOURCE)/monom.h $(SOURCE)/variables.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/monom.cpp -o $(BINARY)/monom.o

fast_allocator.o: $(SOURCE)/fast_allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/fast_allocator.cpp -o $(BINARY)/fast_allocator.o

variables.o: $(SOURCE)/variables.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/variables.cpp -o $(BINARY)/variables.o

timer.o: $(SOURCE)/timer.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/timer.cpp  -o $(BINARY)/timer.o
