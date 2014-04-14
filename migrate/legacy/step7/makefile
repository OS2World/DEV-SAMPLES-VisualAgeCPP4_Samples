# makefile
# The actions included in this make file are:
#  Compile
#  Make exp and lib files
#  Link exe & dll
#  Clean

.SUFFIXES:

.all: payroll.dll main.exe


payroll.obj: payroll.cpp payclass.hpp payfunc.hpp payroll.hpp title.h
    icc.exe /Gd /Ge- /C payroll.cpp

payroll.lib: payroll.def
    implib.exe /nologo payroll.lib payroll.def

payroll.dll: payroll.lib payroll.obj title.lib payroll.def
    icc.exe /Gd+ /B" /pmtype:vio /nologo /def" /Fepayroll.dll payroll.obj title.lib payroll.def

main.exe: main.obj payroll.lib
    icc.exe /Gd /B" /pmtype:vio" /Femain.exe main.obj payroll.lib

main.obj: main.cpp payroll.hpp
    icc.exe /Gd /C main.cpp

title.obj: title.c title.h
    icc.exe /Gd /C title.c

title.lib: title.obj
    ilib /NOBACKUP /QUIET title.lib -+title.obj,,

clean:
    -del main.exe payroll.dll *.obj *.lib

