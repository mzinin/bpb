CXX = @cl.exe
CXXFLAGS = /c /EHsc /Ox \
                -I "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\include" \
                -I "C:\Program Files\Microsoft SDKs\Windows\v7.1\Include"
LINK = @link.exe
LINKFLAGS = /LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib\amd64" \
            /LIBPATH:"C:\Program Files\Microsoft SDKs\Windows\v7.1\Lib\x64" \
            /RELEASE
RC = @rc.exe
SOURCE = ..\Source
BINARY = .\


all: myginv.exe

myginv.exe: timer.obj \
            variables.obj \
            fast_allocator.obj \
            monom.obj \
            polynom.obj \
            triple.obj \
            janettree.obj \
            tset.obj \
            qset.obj \
            groebner_basis.obj \
            resource_counter.obj \
            settings_manager.obj \
            version.obj \
            launcher.obj \
            myginv.obj \
            myginv.res
    @del $(BINARY)\*.exe 2> NUL
    $(LINK) $(LINKFLAGS) /OUT:$(BINARY)\myginv.exe \
            $(BINARY)\timer.obj \
            $(BINARY)\variables.obj \
            $(BINARY)\fast_allocator.obj \
            $(BINARY)\monom.obj \
            $(BINARY)\polynom.obj \
            $(BINARY)\triple.obj \
            $(BINARY)\janettree.obj \
            $(BINARY)\tset.obj \
            $(BINARY)\qset.obj \
            $(BINARY)\groebner_basis.obj \
            $(BINARY)\resource_counter.obj \
            $(BINARY)\settings_manager.obj \
            $(BINARY)\version.obj \
            $(BINARY)\launcher.obj \
            $(BINARY)\myginv.obj \
            $(BINARY)\myginv.res 2> NUL
    @del $(BINARY)\*.obj
    @del $(BINARY)\*.res
    @echo ***** Building successfully completed *****
    
myginv.res: myginv.rc $(SOURCE)\version.h
    $(RC) /fo myginv.res myginv.rc 2> NUL

myginv.obj: $(SOURCE)\launcher.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\myginv.cpp /Fo $(BINARY)\myginv.obj 2> NUL

launcher.obj: $(SOURCE)\fast_allocator.h \
              $(SOURCE)\polynom.h \
              $(SOURCE)\groebner_basis.h \
              $(SOURCE)\launcher.h \
              $(SOURCE)\resource_counter.h \
              $(SOURCE)\settings_manager.h \
              $(SOURCE)\version.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\launcher.cpp /Fo $(BINARY)\launcher.obj 2> NUL  

version.obj: $(SOURCE)\version.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\version.cpp /Fo $(BINARY)\version.obj 2> NUL    

settings_manager.obj: $(SOURCE)\settings_manager.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\settings_manager.cpp /Fo $(BINARY)\settings_manager.obj 2> NUL

resource_counter.obj: $(SOURCE)\timer.h \
                      $(SOURCE)\fast_allocator.h \
                      $(SOURCE)\resource_counter.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\resource_counter.cpp /Fo $(BINARY)\resource_counter.obj 2> NUL   
    
groebner_basis.obj: $(SOURCE)\groebner_basis.h \
                    $(SOURCE)\pcomparator.h \
                    $(SOURCE)\timer.h \
                    $(SOURCE)\tset.h \
                    $(SOURCE)\qset.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\groebner_basis.cpp /Fo $(BINARY)\groebner_basis.obj 2> NUL

tset.obj: $(SOURCE)\tset.h \
          $(SOURCE)\janettree.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\tset.cpp /Fo $(BINARY)\tset.obj 2> NUL

qset.obj: $(SOURCE)\qset.h \
          $(SOURCE)\triple.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\qset.cpp /Fo $(BINARY)\qset.obj 2> NUL

janettree.obj: $(SOURCE)\janettree.h \
               $(SOURCE)\triple.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\janettree.cpp /Fo $(BINARY)\janettree.obj 2> NUL

triple.obj: $(SOURCE)\triple.h \
            $(SOURCE)\polynom.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\triple.cpp /Fo $(BINARY)\triple.obj 2> NUL

polynom.obj: $(SOURCE)\polynom.h \
             $(SOURCE)\monom.h \
             $(SOURCE)\fast_allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\polynom.cpp /Fo $(BINARY)\polynom.obj 2> NUL

monom.obj: $(SOURCE)\monom.h \
           $(SOURCE)\variables.h \
           $(SOURCE)\fast_allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\monom.cpp /Fo $(BINARY)\monom.obj 2> NUL

fast_allocator.obj: $(SOURCE)\fast_allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\fast_allocator.cpp /Fo $(BINARY)\fast_allocator.obj 2> NUL

variables.obj: $(SOURCE)\variables.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\variables.cpp /Fo $(BINARY)\variables.obj 2> NUL

timer.obj: $(SOURCE)\timer.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\timer.cpp /Fo $(BINARY)\timer.obj 2> NUL
