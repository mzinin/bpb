CXX = g++
CXXFLAGS = -O3 -c
SOURCE = ../Source
BINARY = .

all: bjb

clear:
	@rm $(BINARY)/*.o
	@rm $(BINARY)/bjb

bjb:    timer.o \
        variables.o \
        fast_allocator.o \
        monom.o \
        polynom.o \
        triple.o \
        janettree.o \
        tset.o \
        qset.o \
        groebner_basis.o \
        resource_counter.o \
        settings_manager.o \
        version.o \
        launcher.o \
        main.o
	$(CXX) \
            $(BINARY)/timer.o \
            $(BINARY)/variables.o \
            $(BINARY)/fast_allocator.o \
            $(BINARY)/monom.o \
            $(BINARY)/polynom.o \
            $(BINARY)/triple.o \
            $(BINARY)/janettree.o \
            $(BINARY)/tset.o \
            $(BINARY)/qset.o \
            $(BINARY)/groebner_basis.o \
            $(BINARY)/resource_counter.o \
            $(BINARY)/settings_manager.o \
            $(BINARY)/version.o \
            $(BINARY)/launcher.o \
            $(BINARY)/main.o \
            -o $(BINARY)/bjb
	@rm $(BINARY)/*.o

main.o: $(SOURCE)/launcher.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/main.cpp -o $(BINARY)/main.o

launcher.o: $(SOURCE)/fast_allocator.h \
            $(SOURCE)/polynom.h \
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

groebner_basis.o: $(SOURCE)/groebner_basis.h \
                  $(SOURCE)/pcomparator.h \
                  $(SOURCE)/timer.h \
                  $(SOURCE)/tset.h \
                  $(SOURCE)/qset.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/groebner_basis.cpp -o $(BINARY)/groebner_basis.o

tset.o: $(SOURCE)/tset.h \
        $(SOURCE)/janettree.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/tset.cpp -o $(BINARY)/tset.o

qset.o: $(SOURCE)/qset.h \
        $(SOURCE)/triple.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/qset.cpp -o $(BINARY)/qset.o

janettree.o: $(SOURCE)/janettree.h \
             $(SOURCE)/triple.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/janettree.cpp -o $(BINARY)/janettree.o

triple.o: $(SOURCE)/triple.h \
          $(SOURCE)/polynom.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/triple.cpp -o $(BINARY)/triple.o

polynom.o: $(SOURCE)/polynom.h \
           $(SOURCE)/monom.h \
           $(SOURCE)/fast_allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/polynom.cpp -o $(BINARY)/polynom.o

monom.o: $(SOURCE)/monom.h \
         $(SOURCE)/variables.h \
         $(SOURCE)/fast_allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/monom.cpp -o $(BINARY)/monom.o

fast_allocator.o: $(SOURCE)/fast_allocator.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/fast_allocator.cpp -o $(BINARY)/fast_allocator.o

variables.o: $(SOURCE)/variables.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/variables.cpp -o $(BINARY)/variables.o

timer.o: $(SOURCE)/timer.h
	$(CXX) $(CXXFLAGS) $(SOURCE)/timer.cpp -o $(BINARY)/timer.o
