CXX = g++
CXXFLAGS = -O3 -c
SOURCE = ../Source
BINARY = .

all: bpb

clear:
	@rm $(BINARY)/*.o
	@rm $(BINARY)/bpb

bpb:    main.o \
        launcher.o \
        version.o \
        settings_manager.o \
        resource_counter.o \
        monomLex.o \
        monomDL.o \
        monomDRL.o \
        monom.o \
        fast_allocator.o \
        variables.o \
        timer.o
	$(CXX) \
            $(BINARY)/main.o \
            $(BINARY)/launcher.o \
            $(BINARY)/version.o \
            $(BINARY)/settings_manager.o \
            $(BINARY)/resource_counter.o \
            $(BINARY)/monomLex.o \
            $(BINARY)/monomDL.o \
            $(BINARY)/monomDRL.o \
            $(BINARY)/monom.o \
            $(BINARY)/fast_allocator.o \
            $(BINARY)/variables.o \
            $(BINARY)/timer.o \
            -o $(BINARY)/bpb
	@rm $(BINARY)/*.o

main.o: $(SOURCE)/launcher.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/main.cpp -o $(BINARY)/main.o

launcher.o: $(SOURCE)/fast_allocator.h \
            $(SOURCE)/polynom.h \
            $(SOURCE)/triple.h \
            $(SOURCE)/janettree.h \
            $(SOURCE)/qset.h \
            $(SOURCE)/tset.h \
            $(SOURCE)/pcomparator.h \
            $(SOURCE)/groebner_basis.h \
            $(SOURCE)/launcher.h \
            $(SOURCE)/resource_counter.h \
            $(SOURCE)/settings_manager.h \
            $(SOURCE)/version.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/launcher.cpp -o $(BINARY)/launcher.o

version.o: $(SOURCE)/version.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/version.cpp -o $(BINARY)/version.o

settings_manager.o: $(SOURCE)/settings_manager.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/settings_manager.cpp  -o $(BINARY)/settings_manager.o

resource_counter.o: $(SOURCE)/timer.h \
                    $(SOURCE)/fast_allocator.h \
                    $(SOURCE)/resource_counter.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/resource_counter.cpp  -o $(BINARY)/resource_counter.o

monomDRL.o: $(SOURCE)/monom.h \
            $(SOURCE)/monomDRL.h \
            $(SOURCE)/fast_allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/monomDRL.cpp -o $(BINARY)/monomDRL.o

monomDL.o: $(SOURCE)/monom.h \
           $(SOURCE)/monomDL.h \
           $(SOURCE)/fast_allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/monomDL.cpp  -o $(BINARY)/monomDL.o

monomLex.o: $(SOURCE)/monom.h \
            $(SOURCE)/monomLex.h \
            $(SOURCE)/fast_allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/monomLex.cpp -o $(BINARY)/monomLex.o

monom.o: $(SOURCE)/monom.h \
         $(SOURCE)/variables.h \
         $(SOURCE)/fast_allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/monom.cpp -o $(BINARY)/monom.o

fast_allocator.o: $(SOURCE)/fast_allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/fast_allocator.cpp -o $(BINARY)/fast_allocator.o

variables.o: $(SOURCE)/variables.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/variables.cpp -o $(BINARY)/variables.o

timer.o: $(SOURCE)/timer.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/timer.cpp  -o $(BINARY)/timer.o
