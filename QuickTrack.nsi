!include "FileAssociation.nsh"

Name "QuickTrack ${__DATE__}"
OutFile "dist\QuickTrack-Setup-${__DATE__}.exe"

; The default installation directory
InstallDir $PROGRAMFILES\QuickTrack

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\overplumbum\QuickTrack" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

;Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "QuickTrack (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File /r "dist\*.dll"
  File "dist\QuickTrack.exe"

  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\overplumbum\QuickTrack "Install_Dir" "$INSTDIR"
  DeleteRegKey HKLM SOFTWARE\QuickTrack

  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickTrack" "DisplayName" "QuickTrack"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickTrack" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickTrack" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickTrack" "NoRepair" 1
  WriteUninstaller "uninstall.exe"

  ; Associations
  ${registerExtension} "$INSTDIR\QuickTrack.exe" ".gpx" "GPX track"
  
SectionEnd

Section "Start Menu Shortcuts"
  CreateDirectory "$SMPROGRAMS\QuickTrack"
  CreateShortCut "$SMPROGRAMS\QuickTrack\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\QuickTrack\QuickTrack.lnk" "$INSTDIR\QuickTrack.exe" "" "$INSTDIR\QuickTrack.exe" 0
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickTrack"
  DeleteRegKey HKLM SOFTWARE\overplumbum\QuickTrack

  ; Remove assotiations
  ${unregisterExtension} ".gpx" "GPX track"

  ; Remove files and uninstaller
  Delete $INSTDIR\QuickTrack.exe
  Delete $INSTDIR\uninstall.exe

  ; remove libs
  Delete "$INSTDIR\*.dll"
  Delete "$INSTDIR\imageformats\*.dll"
  RMDir "$INSTDIR\imageformatsg"

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\QuickTrack\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\QuickTrack"
  RMDir "$INSTDIR"

SectionEnd
