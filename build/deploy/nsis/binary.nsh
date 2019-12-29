
!ifndef __SYMBOID_PLATFORM_DEPLOY_BINARY_NSH__
!define __SYMBOID_PLATFORM_DEPLOY_BINARY_NSH__

!include config.nsh
!include qt.nsh

!macro DeployBinaryPdb _BinaryBaseName

	!searchparse ">${_BinaryBasename}" ">" _BinaryFileName "."
	!define _BinaryPdb "${_BinaryFileName}.pdb"
	
	Section "Binary ${_BinaryPdb}"
		SetOutPath "$INSTDIR"
		File "${InstallDir}\bin\${_BinaryPdb}"
	SectionEnd

	Section "Un.Binary ${_BinaryPdb}"
		Delete "$INSTDIR\${_BinaryPdb}"
		RMDir "$INSTDIR"
	SectionEnd
	
	!undef _BinaryFileName
	!undef _BinaryPdb

!macroend

!macro DeployBinary _BinaryBasename

	${EchoItem} "Binary               : ${InstallDir}\bin\${_BinaryBasename}"

	Section "Binary ${_BinaryBasename}"
		SetOutPath "$INSTDIR"
		File "${InstallDir}\bin\${_BinaryBasename}"
	SectionEnd

	Section "Un.Binary ${_BinaryBasename}"
		Delete "$INSTDIR\${_BinaryBasename}"
		RMDir "$INSTDIR"
	SectionEnd
	
	!if `${BuildConfig}` == `debug`
		!insertmacro DeployBinaryPdb "${_BinaryBaseName}"
	!endif
	
	!insertmacro GenQtDeps ${_BinaryBaseName}

!macroend

!endif ; __SYMBOID_PLATFORM_DEPLOY_BINARY_NSH__
