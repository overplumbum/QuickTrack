set QTDIR=C:\Qt\2010.04\qt

@mkdir dist
copy /Y ..\QuickTrack-build-desktop\release\QuickTrack.exe dist\

copy /Y %QTDIR%\mingw\bin\libgcc_s_dw2-1.dll dist\
copy /Y %QTDIR%\mingw\bin\mingwm10.dll dist\
copy /Y %QTDIR%\bin\phonon4.dll dist\
copy /Y %QTDIR%\bin\QtCore4.dll dist\
copy /Y %QTDIR%\bin\QtGui4.dll dist\
copy /Y %QTDIR%\bin\QtNetwork4.dll dist\
copy /Y %QTDIR%\bin\QtWebKit4.dll dist\
copy /Y %QTDIR%\bin\QtXml4.dll dist\
copy /Y %QTDIR%\bin\QtXmlPatterns4.dll dist\

@mkdir dist\imageformats
copy /Y %QTDIR%\plugins\imageformats\qjpeg4.dll dist\imageformats\

touch QuickTrack.nsi
"%PROGRAMFILES%\NSIS\makensis.exe" QuickTrack.nsi

PAUSE
