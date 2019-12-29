
;!define _Config_x86
;!define _Config_Debug

!include envvar.nsh
!include package.nsh

!define COMPONENT_TITLE "Symboid Home"
!define HomeInstallDir "${ProgramFilesDir}\Symboid"

Section "Un.UninstallQtRE"

	!define _UninstallerPath "$INSTDIR\QtRE\$1\uninst-qtre.exe"

	FindFirst $0 $1 "$INSTDIR\QtRE\*"
	loop_qt:
	
		StrCmp $1 "" nomore_qt
		
		IfFileExists "${_UninstallerPath}" 0 next_qt
			ExecWait '"${_UninstallerPath}" /S'
			
		next_qt:
		FindNext $0 $1
		Goto loop_qt
	
	nomore_qt:
	FindClose $0
	
	!undef _UninstallerPath
	
SectionEnd

Section "Un.UninstallComponents"

	FindFirst $0 $1 "$INSTDIR\*"
	loop_component:

		StrCmp $1 "." next_component
		StrCmp $1 ".." next_component
		
		StrCmp $1 "" nomore_component

		FindFirst $2 $3 "$INSTDIR\$1\uninst-*.exe"
		FindClose $2
		StrCmp $3 "" no_component_uninstaller
			
			ExecWait '"$INSTDIR\$1\$3" /S'
			
		no_component_uninstaller:
		
		next_component:
		FindNext $0 $1
		Goto loop_component
		
	nomore_component:
	FindClose $0
	
SectionEnd

; installer of 'home' does not depend on 'home' and Qt
!define DontCheckHome
!define DontCheckQt

!insertmacro SubPackage "home" "${HomeInstallDir}"
!insertmacro PackageIcon "build\deploy\home.ico"

!insertmacro IncludeVcRedist

!insertmacro StartMenuFolder "Symboid"
!insertmacro StartMenuLink "$(TextUninstallHome)" "$INSTDIR\${PackageUninstallerExe}" "" ""

!insertmacro UserVar SYMBOID_HOME "${HomeInstallDir}"
