# Microsoft Developer Studio Project File - Name="Gandalf_TestSuite" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Gandalf_TestSuite - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Gandalf_TestSuite.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Gandalf_TestSuite.mak" CFG="Gandalf_TestSuite - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Gandalf_TestSuite - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Gandalf_TestSuite - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Gandalf_TestSuite - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 gandalf.lib libpng.lib libz.lib glut32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Gandalf_TestSuite - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I "s:\\" /I "$(libpng)" /I "$(zlib)" /I "$(libpng)\..\Include" /I "..\..\3rd_party" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 gandalf.lib libpng.lib libz.lib glut32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"LIBCD" /nodefaultlib:"msvcrt" /nodefaultlib:"libcd" /pdbtype:sept /libpath:"$(libpng)\Debug" /libpath:"$(zlib)\Debug" /libpath:"..\..\gandalf\Debug" /libpath:"..\..\3rd_party\gl"

!ENDIF 

# Begin Target

# Name "Gandalf_TestSuite - Win32 Release"
# Name "Gandalf_TestSuite - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "image"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\image\bitmap_test.c
# End Source File
# Begin Source File

SOURCE=..\..\gandalf\image\image_test.c
# End Source File
# End Group
# Begin Group "linalg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\gandalf\linalg\linalg_test.c
# End Source File
# Begin Source File

SOURCE=..\..\gandalf\linalg\matrixf_eigen_test.c
# End Source File
# End Group
# Begin Group "vision"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\vision\camera_test.c
# End Source File
# Begin Source File

SOURCE=..\..\gandalf\vision\hough_transform_test.c
# End Source File
# Begin Source File

SOURCE=..\..\gandalf\vision\vision_test.c
# End Source File
# End Group
# Begin Group "common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\gandalf\common\common_test.h
# End Source File
# Begin Source File

SOURCE=..\..\gandalf\common\list_test.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\gandalf\testframework\cUnit.c
# End Source File
# Begin Source File

SOURCE=.\path_builder.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "image_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\image\bitmap_test.h
# End Source File
# Begin Source File

SOURCE=..\..\gandalf\image\image_test.h
# End Source File
# End Group
# Begin Group "linalg_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\gandalf\linalg\linalg_test.h
# End Source File
# Begin Source File

SOURCE=..\..\gandalf\linalg\matrixf_eigen_test.h
# End Source File
# End Group
# Begin Group "vision_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\vision\camera_test.h
# End Source File
# Begin Source File

SOURCE=..\..\gandalf\vision\vision_test.h
# End Source File
# End Group
# Begin Group "common_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\gandalf\common\common_test.c
# End Source File
# Begin Source File

SOURCE=..\..\gandalf\common\list_test.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\gandalf\testframework\cUnit.h
# End Source File
# Begin Source File

SOURCE=.\path_builder.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
