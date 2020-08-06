
!include build\deploy\nsis\api.nsh

!insertmacro ComponentApiBegin sdk
!insertmacro ModuleApi arch
!insertmacro ModuleApi dox-qt
!insertmacro ModuleApi network-qt
!insertmacro ModuleApi uicontrols-qt
!insertmacro FolderApi build *.*
