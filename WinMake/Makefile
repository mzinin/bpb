CXX = @cl.exe
COMPILE_FLAGS = /c /EHsc /Ox \
                -I "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\include" \
                -I "C:\Program Files\Microsoft SDKs\Windows\v7.1\Include"
LINK_FLAGS = /link \
             /LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib\amd64" \
             /LIBPATH:"C:\Program Files\Microsoft SDKs\Windows\v7.1\Lib\x64"
SOURCE = ..\Source
BINARY = .\


all: myginv.exe

myginv.exe: myginv.obj involutive.obj qset.obj tset.obj janettree.obj triple.obj polynom.obj monomOld.obj monomLex.obj monomDL.obj monomDRL.obj allocator.obj variables.obj timer.obj
    @del $(BINARY)\*.exe 2> NUL
    $(CXX) /Fe$(BINARY)\myginv.exe \
            $(BINARY)\myginv.obj \
            $(BINARY)\involutive.obj \
            $(BINARY)\qset.obj \
            $(BINARY)\tset.obj \
            $(BINARY)\janettree.obj \
            $(BINARY)\triple.obj \
            $(BINARY)\polynom.obj \
            $(BINARY)\monomOld.obj \
            $(BINARY)\monomLex.obj \
            $(BINARY)\monomDL.obj \
            $(BINARY)\monomDRL.obj \
            $(BINARY)\allocator.obj \
            $(BINARY)\variables.obj \
            $(BINARY)\timer.obj \
            $(LINK_FLAGS) 2> NUL
    @del $(BINARY)\*.obj
    @echo ***** Building successfully completed *****

myginv.obj: $(SOURCE)\timer.h $(SOURCE)\involutive.h
    $(CXX) $(COMPILE_FLAGS) $(SOURCE)\myginv.cpp /Fo$(BINARY)\myginv.obj 2> NUL

involutive.obj: $(SOURCE)\involutive.h $(SOURCE)\pcomparator.h
    $(CXX) $(COMPILE_FLAGS) $(SOURCE)\involutive.cpp /Fo$(BINARY)\involutive.obj 2> NUL

tset.obj: $(SOURCE)\tset.h
    $(CXX) $(COMPILE_FLAGS) $(SOURCE)\tset.cpp /Fo$(BINARY)\tset.obj 2> NUL

qset.obj: $(SOURCE)\qset.h
    $(CXX) $(COMPILE_FLAGS) $(SOURCE)\qset.cpp /Fo$(BINARY)\qset.obj 2> NUL

janettree.obj: $(SOURCE)\janettree.h
    $(CXX) $(COMPILE_FLAGS) $(SOURCE)\janettree.cpp /Fo$(BINARY)\janettree.obj 2> NUL

triple.obj: $(SOURCE)\triple.h
    $(CXX) $(COMPILE_FLAGS) $(SOURCE)\triple.cpp /Fo$(BINARY)\triple.obj 2> NUL

polynom.obj: $(SOURCE)\polynom.h $(SOURCE)\monom.h
    $(CXX) $(COMPILE_FLAGS) $(SOURCE)\polynom.cpp /Fo$(BINARY)\polynom.obj 2> NUL

monomDRL.obj: $(SOURCE)\monomDRL.h
    $(CXX) $(COMPILE_FLAGS) $(SOURCE)\monomDRL.cpp /Fo$(BINARY)\monomDRL.obj 2> NUL

monomDL.obj: $(SOURCE)\monomDL.h
    $(CXX) $(COMPILE_FLAGS) $(SOURCE)\monomDL.cpp /Fo$(BINARY)\monomDL.obj 2> NUL

monomLex.obj: $(SOURCE)\monomLex.h
    $(CXX) $(COMPILE_FLAGS) $(SOURCE)\monomLex.cpp /Fo$(BINARY)\monomLex.obj 2> NUL

monomOld.obj: $(SOURCE)\monomOld.h
    $(CXX) $(COMPILE_FLAGS) $(SOURCE)\monomOld.cpp /Fo$(BINARY)\monomOld.obj 2> NUL

allocator.obj: $(SOURCE)\util.h
    $(CXX) $(COMPILE_FLAGS) $(SOURCE)\allocator.cpp /Fo$(BINARY)\allocator.obj 2> NUL

variables.obj: $(SOURCE)\util.h
    $(CXX) $(COMPILE_FLAGS) $(SOURCE)\variables.cpp /Fo$(BINARY)\variables.obj 2> NUL

timer.obj:
    $(CXX) $(COMPILE_FLAGS) $(SOURCE)\timer.cpp /Fo$(BINARY)\timer.obj 2> NUL
