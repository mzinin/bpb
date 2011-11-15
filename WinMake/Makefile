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


all: bpb.exe

clear:
    @del $(BINARY)\*.exe 2> NUL
    @del $(BINARY)\*.obj 2> NUL
    @del $(BINARY)\*.res 2> NUL

bpb.exe:    bpb.res \
            main.obj \
            launcher.obj \
            version.obj \
            settings_manager.obj \
            resource_counter.obj \
            monomLex.obj \
            monomDL.obj \
            monomDRL.obj \
            monom.obj \
            fast_allocator.obj \
            variables.obj \
            timer.obj
    @del $(BINARY)\*.exe 2> NUL
    $(LINK) $(LINKFLAGS) /OUT:$(BINARY)\bpb.exe \
            $(BINARY)\bpb.res \
            $(BINARY)\main.obj \
            $(BINARY)\launcher.obj \
            $(BINARY)\version.obj \
            $(BINARY)\settings_manager.obj \
            $(BINARY)\resource_counter.obj \
            $(BINARY)\monomLex.obj \
            $(BINARY)\monomDL.obj \
            $(BINARY)\monomDRL.obj \
            $(BINARY)\monom.obj \
            $(BINARY)\fast_allocator.obj \
            $(BINARY)\variables.obj \
            $(BINARY)\timer.obj 2> NUL
    @del $(BINARY)\*.obj
    @del $(BINARY)\*.res
    @echo ***** Building successfully completed *****

bpb.res: bpb.rc $(SOURCE)\version.h
    $(RC) /fo bpb.res bpb.rc 2> NUL

main.obj: $(SOURCE)\launcher.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\main.cpp /Fo $(BINARY)\main.obj 2> NUL

launcher.obj: $(SOURCE)\fast_allocator.h \
              $(SOURCE)\polynom.h \
              $(SOURCE)\triple.h \
              $(SOURCE)\janettree.h \
              $(SOURCE)\qset.h \
              $(SOURCE)\tset.h \
              $(SOURCE)\pcomparator.h \
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

monomDRL.obj: $(SOURCE)\monom.h \
              $(SOURCE)\monomDRL.h \
              $(SOURCE)\fast_allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\monomDRL.cpp /Fo $(BINARY)\monomDRL.obj 2> NUL

monomDL.obj: $(SOURCE)\monom.h \
             $(SOURCE)\monomDL.h \
             $(SOURCE)\fast_allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\monomDL.cpp /Fo $(BINARY)\monomDL.obj 2> NUL

monomLex.obj: $(SOURCE)\monom.h \
              $(SOURCE)\monomLex.h \
              $(SOURCE)\fast_allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\monomLex.cpp /Fo $(BINARY)\monomLex.obj 2> NUL

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
