# Microsoft Developer Studio Project File - Name="PlatformSupport" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=PlatformSupport - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PlatformSupport.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PlatformSupport.mak" CFG="PlatformSupport - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PlatformSupport - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PlatformSupport - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PlatformSupport - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\Build\Win32\VC6\Release"
# PROP Intermediate_Dir "..\..\..\..\Build\Win32\VC6\Release\PlatformSupport"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XALAN_PLATFORMSUPPORT_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W4 /GR /GX /O2 /Ob2 /I "..\..\..\..\..\..\xml-xerces\c\src" /I "..\..\..\..\src\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XALAN_PLATFORMSUPPORT_BUILD_DLL" /D "XALAN_XERCES" /FD /I /xml4c/include" /I /xml4c/include" " " " " " " /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 ..\..\..\..\..\..\xml-xerces\c\Build\Win32\VC6\Release\xerces-c_1.lib /nologo /dll /pdb:none /machine:I386
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "PlatformSupport - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\Build\Win32\VC6\Debug"
# PROP Intermediate_Dir "..\..\..\..\Build\Win32\VC6\Debug\PlatformSupport"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PlatformSupport_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /Gi /GR /GX /Zi /Od /I "..\..\..\..\..\..\xml-xerces\c\src" /I "..\..\..\..\src\\" /D "_WINDOWS" /D "_USRDLL" /D "XALAN_PLATFORMSUPPORT_BUILD_DLL" /D "XALAN_XERCES" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "XML_DEBUG" /YX /FD /I /xml4c/include" /I /lotusxsl4c/stl" /I /lotusxsl4c/src/include" /I /xml4c/include" /GZ " " " " " " /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\..\..\..\xml-xerces\c\Build\Win32\VC6\Debug\xerces-c_1.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "PlatformSupport - Win32 Release"
# Name "PlatformSupport - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\AttributeListImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\Cloneable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\DecimalFormat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\DecimalFormatSymbols.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\DOMStringHelper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\DOMStringPrintWriter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\DoubleSupport.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\ExecutionContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\Factory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\FactoryObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\NamedNodeMapAttributeList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\NullPrintWriter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\NumberFormat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\PrintWriter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\Resettable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\StdBinInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\StringTokenizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\TextOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\Writer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\XSLException.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\AttributeListImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\Cloneable.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\DecimalFormat.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\DecimalFormatSymbols.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\DirectoryEnumerator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\DOMStringHelper.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\DOMStringPrintWriter.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\DoubleSupport.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\ExecutionContext.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\Factory.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\FactoryObject.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\NamedNodeMapAttributeList.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\NullPrintWriter.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\NumberFormat.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\PlatformSupportDefinitions.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\PrintWriter.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\Resettable.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\StdBinInputStream.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\STLHelper.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\StringTokenizer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\TextOutputStream.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\Writer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\PlatformSupport\XSLException.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
