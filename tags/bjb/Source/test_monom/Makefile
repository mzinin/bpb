CXX = @cl.exe
CXXFLAGS = /c /EHsc /Ox \
                -I "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\include" \
                -I "C:\Program Files\Microsoft SDKs\Windows\v7.1\Include"
LINK = @link.exe
LINKFLAGS = /LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib\amd64" \
            /LIBPATH:"C:\Program Files\Microsoft SDKs\Windows\v7.1\Lib\x64" \
            /RELEASE
RC = @rc.exe
SOURCE = ..
BINARY = .


all: test.exe

clear:
    @del $(BINARY)\*.exe 2> NUL
    @del $(BINARY)\*.obj 2> NUL

test.exe:   main.obj \
            monom.obj \
            fast_allocator.obj \
            variables.obj
    @del $(BINARY)\*.exe 2> NUL
    $(LINK) $(LINKFLAGS) /OUT:$(BINARY)\test.exe \
            $(BINARY)\main.obj \
            $(BINARY)\monom.obj \
            $(BINARY)\fast_allocator.obj \
            $(BINARY)\variables.obj 2> NUL
    @del $(BINARY)\*.obj
    @echo ***** Building successfully completed *****
    
main.obj:
    $(CXX) $(CXXFLAGS) $(BINARY)\main.cpp /Fo $(BINARY)\main.obj 2> NUL

monom.obj: $(SOURCE)\monom.h \
           $(SOURCE)\variables.h \
           $(SOURCE)\fast_allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\monom.cpp /Fo $(BINARY)\monom.obj 2> NUL

fast_allocator.obj: $(SOURCE)\fast_allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\fast_allocator.cpp /Fo $(BINARY)\fast_allocator.obj 2> NUL

variables.obj: $(SOURCE)\variables.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\variables.cpp /Fo $(BINARY)\variables.obj 2> NUL
