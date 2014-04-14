:userdoc.
:docprof toc=123456.
:title.C++ Message Box Help
:h1.C++ Message Box Help
:p.This file contains the help for the C++ Message Box sample application.
:h2 res=100.C++ Message Box Sample - Message Box Help
:i1.message box help
:p.This is the help panel for helpId=100.
The message box help button is connected to this help panel by the following
steps within the AMsgBoxDemo class implementation in the msgbox.cpp file&colon.
:ul compact.
:li.The message box and help window are owned by the same frame window.
:li.The IHelpWindow&colon.&colon.addLibraries function is used to identify
the appropriate help library file, msgbox.hlp.
:li.The helpId, 100, is specified, using a symbolic definition, on the
message box show function.
:eul.
:euserdoc.
