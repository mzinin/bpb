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

myginv.exe: myginv.res \
            myginv.obj \
            launcher.obj \
            version.obj \
            involutive.obj \
            qset.obj \
            tset.obj \
            janettree.obj \
            triple.obj \
            settings_manager.obj \
            polynom.obj \
            monomOld.obj \
            monomLex.obj \
            monomDL.obj \
            monomDRL.obj \
            allocator.obj \
            variables.obj \
            timer.obj
    @del $(BINARY)\*.exe 2> NUL
    $(LINK) $(LINKFLAGS) /OUT:$(BINARY)\myginv.exe \
            $(BINARY)\myginv.res \
            $(BINARY)\myginv.obj \
            $(BINARY)\launcher.obj \
            $(BINARY)\version.obj \
            $(BINARY)\involutive.obj \
            $(BINARY)\qset.obj \
            $(BINARY)\tset.obj \
            $(BINARY)\janettree.obj \
            $(BINARY)\triple.obj \
            $(BINARY)\settings_manager.obj \
            $(BINARY)\polynom.obj \
            $(BINARY)\monomOld.obj \
            $(BINARY)\monomLex.obj \
            $(BINARY)\monomDL.obj \
            $(BINARY)\monomDRL.obj \
            $(BINARY)\allocator.obj \
            $(BINARY)\variables.obj \
            $(BINARY)\timer.obj 2> NUL
    @del $(BINARY)\*.obj
    @del $(BINARY)\*.res
    @echo ***** Building successfully completed *****

myginv.res: myginv.rc $(SOURCE)\version.h
    $(RC) /fo myginv.res myginv.rc 2> NUL

myginv.obj: $(SOURCE)\launcher.h $(SOURCE)\settings_manager.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\myginv.cpp /Fo $(BINARY)\myginv.obj 2> NUL

launcher.obj: $(SOURCE)\launcher.h $(SOURCE)\polynom.h $(SOURCE)\involutive.h $(SOURCE)\version.h $(SOURCE)\timer.h $(SOURCE)\settings_manager.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\launcher.cpp /Fo $(BINARY)\launcher.obj 2> NUL

version.obj: $(SOURCE)\version.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\version.cpp /Fo $(BINARY)\version.obj 2> NUL

involutive.obj: $(SOURCE)\involutive.h $(SOURCE)\pcomparator.h $(SOURCE)\timer.h $(SOURCE)\tset.h $(SOURCE)\qset.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\involutive.cpp /Fo $(BINARY)\involutive.obj 2> NUL

tset.obj: $(SOURCE)\tset.h $(SOURCE)\janettree.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\tset.cpp /Fo $(BINARY)\tset.obj 2> NUL

qset.obj: $(SOURCE)\qset.h $(SOURCE)\triple.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\qset.cpp /Fo $(BINARY)\qset.obj 2> NUL

janettree.obj: $(SOURCE)\janettree.h $(SOURCE)\triple.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\janettree.cpp /Fo $(BINARY)\janettree.obj 2> NUL

triple.obj: $(SOURCE)\triple.h $(SOURCE)\polynom.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\triple.cpp /Fo $(BINARY)\triple.obj 2> NUL

settings_manager.obj: $(SOURCE)\settings_manager.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\settings_manager.cpp /Fo $(BINARY)\settings_manager.obj 2> NUL

polynom.obj: $(SOURCE)\polynom.h $(SOURCE)\monom.h $(SOURCE)\monomDRL.h $(SOURCE)\monomDL.h $(SOURCE)\monomLex.h $(SOURCE)\monomOld.h $(SOURCE)\allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\polynom.cpp /Fo $(BINARY)\polynom.obj 2> NUL

monomDRL.obj: $(SOURCE)\monomDRL.h $(SOURCE)\variables.h $(SOURCE)\allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\monomDRL.cpp /Fo $(BINARY)\monomDRL.obj 2> NUL

monomDL.obj: $(SOURCE)\monomDL.h $(SOURCE)\variables.h $(SOURCE)\allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\monomDL.cpp /Fo $(BINARY)\monomDL.obj 2> NUL

monomLex.obj: $(SOURCE)\monomLex.h $(SOURCE)\variables.h $(SOURCE)\allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\monomLex.cpp /Fo $(BINARY)\monomLex.obj 2> NUL

monomOld.obj: $(SOURCE)\monomOld.h $(SOURCE)\variables.h $(SOURCE)\allocator.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\monomOld.cpp /Fo $(BINARY)\monomOld.obj 2> NUL

allocator.obj: $(SOURCE)\allocator.h $(SOURCE)\util.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\allocator.cpp /Fo $(BINARY)\allocator.obj 2> NUL

variables.obj: $(SOURCE)\variables.h $(SOURCE)\util.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\variables.cpp /Fo $(BINARY)\variables.obj 2> NUL

timer.obj: $(SOURCE)\timer.h
    $(CXX) $(CXXFLAGS) $(SOURCE)\timer.cpp /Fo $(BINARY)\timer.obj 2> NUL
