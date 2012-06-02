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


all: buhberger.exe

buhberger.exe: buhberger.res main.obj version.obj igroebner64.obj poly64.obj monom64.obj iallocator.obj ivariables.obj timer.obj
    @del $(BINARY)\*.exe 2> NUL
    $(LINK) $(LINKFLAGS) /OUT:$(BINARY)\buhberger.exe \
            $(BINARY)\buhberger.res \
            $(BINARY)\main.obj \
            $(BINARY)\version.obj \
            $(BINARY)\igroebner64.obj \
            $(BINARY)\poly64.obj \
            $(BINARY)\monom64.obj \
            $(BINARY)\iallocator.obj \
            $(BINARY)\ivariables.obj \
            $(BINARY)\timer.obj 2> NUL
    @del $(BINARY)\*.obj
    @del $(BINARY)\*.res
    @echo ***** Building successfully completed *****
    
buhberger.res: buhberger.rc $(SOURCE)\version.h
    $(RC) /fo buhberger.res buhberger.rc 2> NUL

main.obj: $(SOURCE)\init64.h $(SOURCE)\ivariables.h $(SOURCE)\igroebner64.h $(SOURCE)\version.h $(SOURCE)\timer.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\main.cpp /Fo $(BINARY)\main.obj 2> NUL

version.obj: $(SOURCE)\version.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\version.cpp /Fo $(BINARY)\version.obj 2> NUL

igroebner64.obj: $(SOURCE)\igroebner64.h $(SOURCE)\poly64.h $(SOURCE)\timer.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\igroebner64.cpp /Fo $(BINARY)\igroebner64.obj 2> NUL

poly64.obj: $(SOURCE)\poly64.h $(SOURCE)\monom64.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\poly64.cpp /Fo $(BINARY)\poly64.obj 2> NUL

monom64.obj: $(SOURCE)\monom64.h $(SOURCE)\ivariables.h $(SOURCE)\iallocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\monom64.cpp /Fo $(BINARY)\monom64.obj 2> NUL

iallocator.obj: $(SOURCE)\iallocator.h $(SOURCE)\iutil.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\iallocator.cpp /Fo $(BINARY)\iallocator.obj 2> NUL

ivariables.obj: $(SOURCE)\ivariables.h $(SOURCE)\iutil.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\ivariables.cpp /Fo $(BINARY)\ivariables.obj 2> NUL

timer.obj: $(SOURCE)\timer.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\timer.cpp /Fo $(BINARY)\timer.obj 2> NUL
