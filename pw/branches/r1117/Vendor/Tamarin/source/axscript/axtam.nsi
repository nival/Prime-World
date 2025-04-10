; This is the NSIS installation script for the Script Engine.
;

; NOTE: this .NSI script is designed for NSIS v1.8+
!include "MUI2.nsh"

!define /date DATESTAMP "%Y%m%d"

Name "Tamarin Script Engine"
OutFile "setup-axtam-${DATESTAMP}.exe"

;Pages
  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  
    # These indented statements modify settings for MUI_PAGE_FINISH
     !define MUI_FINISHPAGE_NOAUTOCLOSE
    !define MUI_FINISHPAGE_SHOWREADME $INSTDIR\readme.hta
  !insertmacro MUI_PAGE_FINISH

;Languages
!insertmacro MUI_LANGUAGE "English"

; Some default compiler settings (uncomment and change at will):
; SetCompress auto ; (can be off or force)
; SetDatablockOptimize on ; (can be off)
; CRCCheck on ; (can be off)
; AutoCloseWindow false ; (can be true for the window go away automatically at end)
; ShowInstDetails hide ; (can be show to have them shown, or nevershow to disable)
; SetDateSave off ; (can be on to have files restored to their orginal date)

InstallDir "$PROGRAMFILES\TamarinScriptEngine"
InstallDirRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Tamarin Script Engine" ""
;DirShow show ; (make this hide to not let the user change it)
DirText "Select the directory to install the Tamarin Script Engine in:"

Section "" ; (default section)
    SetOutPath "$INSTDIR"
    ; add files / whatever that need to be installed here.
    file README.hta
    createShortCut "$SMPROGRAMS\Tamarin Script Engine Readme.lnk" "$INSTDIR\README.hta"
    ; The ESC .abc files - shipping them is a temporary solution, so
    ; we use a wildcard.
    file ..\ESC\bin\*.abc
    ; The DLL
    file vc2008\obj\Release_Debugger\axtam.dll
    RegDll axtam.dll
    ; samples
    SetOutPath $INSTDIR\test
    file test\*.html
    file test\*.js
    file test\*.es4
    file test\README.txt
    SetOutPath $INSTDIR\test\unittests
    file test\unittests\*.py
    SetOutPath $INSTDIR
    WriteRegStr HKEY_LOCAL_MACHINE "SOFTWARE\Tamarin Script Engine" "" "$INSTDIR"
    WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Tamarin Script Engine" "DisplayName" "Tamarin Script Engine (remove only)"
    WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Tamarin Script Engine" "UninstallString" '"$INSTDIR\uninst-axtam.exe"'
    ; write out uninstaller
    WriteUninstaller "$INSTDIR\uninst-axtam.exe"
SectionEnd ; end of default section


; begin uninstall settings/section
UninstallText "This will uninstall the Tamarin Script Engine from your system"

Section Uninstall
    ; add delete commands to delete whatever files/registry keys/etc you installed here.
    ; tests
    Delete "$INSTDIR\test\unittests\*.py"
    RMDir "$INSTDIR\test\unittests"
    Delete "$INSTDIR\test\*.html"
    Delete "$INSTDIR\test\*.js"
    Delete "$INSTDIR\test\*.es4"
    Delete "$INSTDIR\test\README.txt"
    RMDir "$INSTDIR\test"

    Delete "$SMPROGRAMS\Tamarin Script Engine Readme.lnk"
    Delete "$INSTDIR\README.hta"
    Delete "$INSTDIR\*.abc"
    UnRegDll "$INSTDIR\axtam.dll"
    Delete "$INSTDIR\axtam.dll"
    Delete "$INSTDIR\uninst-axtam.exe"
    DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Tamarin Script Engine"
    DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\Tamarin Script Engine"
    RMDir "$INSTDIR"
SectionEnd ; end of uninstall section
