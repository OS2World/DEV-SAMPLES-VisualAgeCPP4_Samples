#*******************************************************************************
#* SAMPLE PROJECT: Lancelot makefile for OS/2                                  *
#*                                                                             *
#* COPYRIGHT:                                                                  *
#* ----------                                                                  *
#* Copyright (C) International Business Machines Corp., 1992,1995.             *
#*                                                                             *
#* DISCLAIMER OF WARRANTIES:                                                   *
#* -------------------------                                                   *
#* The following [enclosed] code is sample code created by IBM                 *
#* Corporation. This sample code is not part of any standard IBM product       *
#* and is provided to you solely for the purpose of assisting you in the       *
#* development of your applications.  The code is provided "AS IS",            *
#* without warranty of any kind.  IBM shall not be liable for any damages      *
#* arising out of your use of the sample code, even if they have been          *
#* advised of the possibility of such damages.                                 *
#*                                                                             *
#*******************************************************************************

ERASE=erase
GCPPC=icc
GLINK=icc

ICLCPPOPTS=/GM /GD /Q /DIC_TRACE_ALL /DIC_DEVELOP
GCPPFLAGS=$(LOCALOPTS) $(ICLCPPOPTS)
GCPPLFLAGS=/Tdp /Q /B"/pmtype:pm"
EXEFLAGS=/Ge+ /Fttincexe
DLLFLAGS=/Ge- /Fttincdll

DLLOBJS =\
 lmainwin.obj\
 linfowin.obj\
 lperswin.obj\
 linfonb.obj\
 lcnrobj.obj\
 lpagectl.obj\
 lacct.obj\
 lstatus.obj\
 lbadge.obj\
 lskill.obj\
 lgenl.obj\
 lgoodies.obj\
 ldbase.obj\
 lproject.obj\
 ltask.obj\
 ltimec.obj\
 ltimepie.obj\
 lperswdm.obj\
 lgeneric.obj\
 ldbqry.obj

all: lancelot.inf lancelot.exe lance.dll lancres.dll lanchelp.hlp

lancelot.exe:  lancelot.obj lance.lib
        $(GLINK) $(GCPPLFLAGS) $(GCPPFLAGS) $(EXEFLAGS) /Fe"lancelot.exe" \
                lancelot.obj lance.lib

lance.dll: $(DLLOBJS) lance.def
        $(GLINK) $(GCPPLFLAGS) $(GCPPFLAGS) $(DLLFLAGS) /Fe"lance.dll" \
                $(DLLOBJS) lance.def

lancres.dll: lstub.obj lancelot.res
        echo LIBRARY lancres > lancres.def
        $(GLINK) /Fe"lancres.dll" lstub.obj lancres.def
        rc lancelot.res lancres.dll

lance.lib: lance.def
        implib /nologo lance.lib lance.def

lstub.obj: lstub.cpp
      $(GCPPC) /C+ lstub.cpp

lancelot.obj:  lancelot.cpp lancelot.h
        $(GCPPC) /C+ $(EXEFLAGS) $(GCPPFLAGS) lancelot.cpp

lpagectl.obj:  lpagectl.cpp  lpagectl.hpp lancelot.h
       $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) lpagectl.cpp

lacct.obj:  lacct.cpp  lacct.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) lacct.cpp

lstatus.obj:  lstatus.cpp lstatus.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) lstatus.cpp

lbadge.obj:  lbadge.cpp lbadge.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) lbadge.cpp

lskill.obj:  lskill.cpp lskill.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) lskill.cpp

lgenl.obj:  lgenl.cpp lgenl.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) lgenl.cpp

lgoodies.obj: lgoodies.cpp lgoodies.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) lgoodies.cpp

ldbqry.obj:  ldbqry.cpp ldbqry.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) ldbqry.cpp

ldbase.obj:  ldbase.cpp ldbase.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) ldbase.cpp

lgeneric.obj:  lgeneric.cpp lgeneric.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) lgeneric.cpp

lcnrobj.obj:  lcnrobj.cpp lcnrobj.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) lcnrobj.cpp

linfonb.obj:  linfonb.cpp linfonb.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) linfonb.cpp

lperswin.obj:  lperswin.cpp lperswin.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) lperswin.cpp

linfowin.obj:  linfowin.cpp linfowin.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) linfowin.cpp

lmainwin.obj:  lmainwin.cpp lmainwin.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) lmainwin.cpp

lproject.obj:  lproject.cpp lproject.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) lproject.cpp

ltask.obj:  ltask.cpp ltask.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) ltask.cpp

ltimec.obj:  ltimec.cpp ltimec.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) ltimec.cpp

ltimepie.obj:  ltimepie.cpp ltimepie.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) ltimepie.cpp

lperswdm.obj:  lperswdm.cpp lperswdm.hpp lancelot.h
        $(GCPPC) /C+ $(DLLFLAGS) $(GCPPFLAGS) lperswdm.cpp

lancelot.res:  lancelot.rc lancelot.h \
               lancelot.ico query.ico query2.ico \
               person1.ico person2.ico person3.ico person4.ico personu.ico \
               add.ico change.ico help.ico next.ico previous.ico \
               remove.ico save.ico undo.ico \
               arrange.bmp boot.bmp create.bmp deselall.bmp \
               opendeta.bmp openicon.bmp opentree.bmp selall.bmp \
               sortasc.bmp sortdesc.bmp transfer.bmp
        rc -r lancelot.rc

lanchelp.hlp:  lanchelp.ipf
        ipfc lanchelp.ipf

lancelot.inf:  lancelot.ipf
        ipfc lancelot.ipf /inf

clean:
        $(ERASE) lstub.obj
        $(ERASE) lancelot.obj
        $(ERASE) lmainwin.obj
        $(ERASE) linfowin.obj
        $(ERASE) lperswin.obj
        $(ERASE) linfonb.obj
        $(ERASE) lcnrobj.obj
        $(ERASE) lpagectl.obj
        $(ERASE) lacct.obj
        $(ERASE) lstatus.obj
        $(ERASE) lbadge.obj
        $(ERASE) lskill.obj
        $(ERASE) lgenl.obj
        $(ERASE) ldbase.obj
        $(ERASE) ldbqry.obj
        $(ERASE) lproject.obj
        $(ERASE) ltask.obj
        $(ERASE) ltimec.obj
        $(ERASE) ltimepie.obj
        $(ERASE) lgeneric.obj
        $(ERASE) lgoodies.obj
        $(ERASE) lperswdm.obj
        $(ERASE) lancelot.res
        $(ERASE) lancelot.inf
        $(ERASE) lanchelp.hlp
