# Microsoft Developer Studio Project File - Name="perf" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=perf - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "perf.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "perf.mak" CFG="perf - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "perf - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "perf - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "perf - Win32 Release with symbols" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "perf - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Build\Win32\VC6\Release"
# PROP Intermediate_Dir "..\..\Build\Win32\VC6\Release\Performance"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W4 /GR /GX /O2 /Ob2 /I "..\..\..\..\xml-xerces\c\src" /I "..\..\src\\" /I "..\harness\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ..\..\..\..\xml-xerces\c\Build\Win32\VC6\Release\xerces-c_1.lib ..\..\Build\Win32\VC6\Release\*.lib /nologo /subsystem:console /pdb:none /machine:I386 /libpath:"..\Harness\Release\\"

!ELSEIF  "$(CFG)" == "perf - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Build\Win32\VC6\Debug"
# PROP Intermediate_Dir "..\..\Build\Win32\VC6\Debug\Performance"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /Zi /Od /Gf /Gy /I "..\..\src\\" /I "..\..\..\..\xml-xerces\c\src\\" /I "..\harness\\" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\..\xml-xerces\c\Build\Win32\VC6\Debug\xerces-c_1D.lib ..\..\Build\Win32\VC6\Debug\*.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"..\Harness\Debug\\"
# SUBTRACT LINK32 /incremental:no

!ELSEIF  "$(CFG)" == "perf - Win32 Release with symbols"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "perf___Win32_Release_with_symbols"
# PROP BASE Intermediate_Dir "perf___Win32_Release_with_symbols"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Build\Win32\VC6\Release.symbols"
# PROP Intermediate_Dir "..\..\Build\Win32\VC6\Release.symbols\Performance"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GR /GX /O2 /Ob2 /I "..\..\..\..\xml-xerces\c\src" /I "..\..\src\\" /I "..\harness\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W4 /GR /GX /Zi /O2 /Ob2 /I "..\..\..\..\xml-xerces\c\src" /I "..\..\src\\" /I "..\harness\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\Build\Win32\VC6\Release\Harness.lib ..\..\..\..\xml-xerces\c\Build\Win32\VC6\Release\xerces-c_1.lib ..\..\Build\Win32\VC6\Release\*.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /pdb:none /machine:I386 /libpath:"..\Harness\Release\\"
# ADD LINK32 ..\..\..\..\xml-xerces\c\Build\Win32\VC6\Release\xerces-c_1.lib ..\..\Build\Win32\VC6\Release.symbols\*.lib /nologo /subsystem:console /debug /machine:I386 /libpath:"..\Harness\Release\\"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "perf - Win32 Release"
# Name "perf - Win32 Debug"
# Name "perf - Win32 Release with symbols"
# Begin Source File

SOURCE=.\perf.cpp
# End Source File
# End Target
# End Project
