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

test.exe:   variables.obj \
            fast_allocator.obj \
            monom.obj \
            polynom.obj \
            triple.obj \
            janettree.obj \
            main.obj
    @del $(BINARY)\*.exe 2> NUL
    $(LINK) $(LINKFLAGS) /OUT:$(BINARY)\test.exe \
            $(BINARY)\variables.obj \
            $(BINARY)\fast_allocator.obj \
            $(BINARY)\monom.obj \
            $(BINARY)\polynom.obj \
            $(BINARY)\triple.obj \
            $(BINARY)\janettree.obj \
            $(BINARY)\main.obj 2> NUL
    @del $(BINARY)\*.obj
    @echo ***** Building successfully completed *****
    
variables.obj: $(SOURCE)\variables.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\variables.cpp /Fo $(BINARY)\variables.obj 2> NUL
    
fast_allocator.obj: $(SOURCE)\fast_allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\fast_allocator.cpp /Fo $(BINARY)\fast_allocator.obj 2> NUL
    
monom.obj: $(SOURCE)\monom.h \
           $(SOURCE)\variables.h \
           $(SOURCE)\fast_allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\monom.cpp /Fo $(BINARY)\monom.obj 2> NUL
    
polynom.obj: $(SOURCE)\monom.h \
             $(SOURCE)\polynom.h \
             $(SOURCE)\fast_allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\polynom.cpp /Fo $(BINARY)\polynom.obj 2> NUL
    
triple.obj: $(SOURCE)\fast_allocator.h \
            $(SOURCE)\polynom.h \
            $(SOURCE)\triple.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\triple.cpp /Fo $(BINARY)\triple.obj 2> NUL
    
janettree.obj: $(SOURCE)\triple.h \
               $(SOURCE)\janettree.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\janettree.cpp /Fo $(BINARY)\janettree.obj 2> NUL
    
main.obj:
    $(CXX) $(CXXFLAGS) $(BINARY)\main.cpp /Fo $(BINARY)\main.obj 2> NUL

