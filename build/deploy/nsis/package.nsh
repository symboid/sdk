
!ifndef __SYMBOID_PLATFORM_DEPLOY_PACKAGE_NSH__
!define __SYMBOID_PLATFORM_DEPLOY_PACKAGE_NSH__

!addincludedir ${__FILEDIR__}

!include config.nsh
!include arch.nsh
!include component_props.nsh
!include MUI2.nsh
!include links.nsh
!include echo.nsh
!include qt.nsh
!include crt.nsh
!include envvar.nsh
!include launcher.nsh
!include FileFunc.nsh
!include module.nsh

BrandingText "www.symboid.com"

!macro PackageCommonPages

!ifdef COMPONENT_EULA_VERSION
Function RegEulaVersion
	WriteRegDWORD HKCU "Software\Symboid\Components\${COMPONENT_NAME}" "eula_version" "${COMPONENT_EULA_VERSION}"
FunctionEnd
	!define MUI_PAGE_CUSTOMFUNCTION_LEAVE RegEulaVersion
	!insertmacro MUI_PAGE_LICENSE "${RootDir}\${COMPONENT_NAME}\deploy\eula.rtf"
!endif
!ifdef _Config_Components
	!insertmacro MUI_PAGE_COMPONENTS
!endif
Function PurgeIfExists
!if `${COMPONENT_NAME}` == `kirkoszkop`
	; if obsolete instance of KirkoSzkop found	
	IfFileExists "${ProgramFilesDir}\KirkoSzkop\KirkoSzkop-uninst.exe" 0 skip_purge_old_kirkoszkop
	
	; moving list of open documents into new dir of app data
	CreateDirectory "$LOCALAPPDATA\Symboid\kirkoszkop"
	CopyFiles "$LOCALAPPDATA\KirkoSzkop\settings.user" "$LOCALAPPDATA\Symboid\kirkoszkop"
	
	; cleaning up old app data dir
	RMDir /r "$LOCALAPPDATA\KirkoSzkop"
	
	; copying symboid documents into new document dir (with leaving in older one)
	CreateDirectory "$DOCUMENTS\Symboid\KirkoSzkop"
	CopyFiles "$DOCUMENTS\KirkoSzkop\*.syd" "$DOCUMENTS\Symboid\KirkoSzkop"
	
	; purging obsolete installation of KirkoSzkop
	!insertmacro ExecUninstaller "${ProgramFilesDir}\KirkoSzkop\KirkoSzkop-uninst.exe"
	skip_purge_old_kirkoszkop:
!endif
!ifdef PurgingExistingInstance
	; purging existing instance of component if specified
	IfFileExists "$INSTDIR\${PackageUninstallerExe}" 0 skip_purge_existing
	!insertmacro ExecUninstaller "$INSTDIR\${PackageUninstallerExe}"
	skip_purge_existing:
!endif
FunctionEnd
	!define MUI_PAGE_CUSTOMFUNCTION_PRE PurgeIfExists
	!insertmacro MUI_PAGE_INSTFILES

!macroend

!macro PackageTexts

	!insertmacro MUI_LANGUAGE "Hungarian"
	!insertmacro MUI_LANGUAGE "English"

	!include texts.nsh
	
!macroend

!macro ExecUninstaller _UninstallerPath
	ExecWait '${_UninstallerPath} /S --keep-reg:1' $0
	; waiting for quit of uninst process
	; or else unist process can block $INSTDIR for a little while
	Sleep 1000
	DetailPrint "${_UninstallerPath} returns: $0"
!macroend
	
!macro PackageBasics _PackageName _InstFolder

	${EchoHeader} "PACKING"
	!define PackageId ${_PackageName}

	; name of installer
	!searchreplace PackageRawName "${_PackageName}" " " "-"
	!ifndef PackageInstallerExe
	!define PackageInstallerExe "${PackageDir}\${PackageRawName}-pkg.exe"
	!endif
	!define PackageUninstallerExe "uninst-${PackageRawName}.exe"

	${EchoItem} "Package name         : ${_PackageName}"
	${EchoItem} "Installer exe        : ${PackageInstallerExe}"
	${EchoItem} "Installation folder  : ${_InstFolder}"

	Name "${COMPONENT_TITLE}"
	OutFile "${PackageInstallerExe}"
	InstallDir "${_InstFolder}"
	RequestExecutionLevel admin

	Function .OnInit
		
		; checking for architecture compatibility
		!insertmacro Arch64Check
		
	FunctionEnd
	
!macroend

!macro PackageIcon _IconPath

	${EchoItem} "Package icon         : ${_IconPath}"

	Icon "${RootDir}\${_IconPath}"
	
!macroend

!macro PackageRegComponent _ComponentId _ComponentInstDir

	Section "Component Reg"
		WriteRegExpandStr HKLM "Software\Symboid\Components\${_ComponentId}" "install_dir" "${_ComponentInstDir}"
	SectionEnd
	
	Section "Un.Component Reg"
		${GetOptions} $CMDLINE "--keep-reg:" $0
		StrCmp $0 "1" end_reg_delete
		DeleteRegKey HKLM "Software\Symboid\Components\${_ComponentId}"
		DeleteRegKey /ifempty HKLM "Software\Symboid\Components"
		DeleteRegKey /ifempty HKLM "Software\Symboid"
		end_reg_delete:
	SectionEnd
	
!macroend

!macro PackageTrialStamp _ComponentId

	Section "Trial Stamp"
	
		ExecWait '"$INSTDIR\launcher.exe" --tool:boot --trial-stamp:${_ComponentId}'
		
	SectionEnd
	
!macroend

!macro DeployUninstaller

	Section "Write Uninst"
		SetOutPath "$INSTDIR"
		WriteUninstaller "${PackageUninstallerExe}"
	SectionEnd

	Section "Un.Write Uninst"
		Delete "$INSTDIR\${PackageUninstallerExe}"
		RMDir "$INSTDIR"
	SectionEnd

!macroend

!macro UninstallRemovesUserData _FolderId

	!define _AppDataFolder "$LOCALAPPDATA\Symboid\${_FolderId}"
	!define _DocumentsFolder "$DOCUMENTS\Symboid\${_FolderId}"

	UninstPage Custom Un.QuestionUserData Un.RemoveUserData
	
	Var RemoveAppDataCheckBox
	Var RemoveDocumentsCheckBox
	
	Var RemoveAppData
	Var RemoveDocuments
	
	Function Un.QuestionUserData
		nsDialogs::Create  /NOUNLOAD 1018
		
		; information text
		${NSD_CreateLabel} 0 10 100% 40 "$(TextCleanupOnUninstall)"
		
		; check box for AppData folder
		${NSD_CreateCheckBox} 30 60 100% 20 "$(TextRemoveAppData)"
		Pop $RemoveAppDataCheckBox
		${NSD_Check} $RemoveAppDataCheckBox
		${NSD_CreateLabel} 45 80 100% 20 "$(TextFolder): ${_AppDataFolder}"
		
		; check box for Documents folder
		${NSD_CreateCheckBox} 30 110 100% 20 "$(TextRemoveDocuments)"
		Pop $RemoveDocumentsCheckBox
		${NSD_UnCheck} $RemoveDocumentsCheckBox
		${NSD_CreateLabel} 45 130 100% 20 "$(TextFolder): ${_DocumentsFolder}"
		
		nsDialogs::Show
	FunctionEnd
	
	Function Un.RemoveUserData
		; removing AppData folder
		${NSD_GetState} $RemoveAppDataCheckBox $0
		${If} $0 == ${BST_CHECKED}
			StrCpy $RemoveAppData "1"
		${Endif}
		
		; removing Documents folder
		${NSD_GetState} $RemoveDocumentsCheckBox $1
		${If} $1 == ${BST_CHECKED}
			StrCpy $RemoveDocuments "1"
		${Endif}
	FunctionEnd
	
	Section "Un.CleanupUserData"
		${If} $RemoveAppData == "1"
			RMDir /r "${_AppDataFolder}"
		${Endif}
		${If} $RemoveDocuments == "1"
			RMDir /r "${_DocumentsFolder}"
		${Endif}
	SectionEnd
	
	!undef _AppDataFolder
	!undef _DocumentsFolder
	
!macroend

!macro PackageBegin _RelFolder

	!define PurgingExistingInstance
	
	!insertmacro PackageBasics "${COMPONENT_NAME}" "${ProgramFilesDir}\${_RelFolder}"
	!insertmacro PackageRegComponent "${COMPONENT_NAME}" "${ProgramFilesDir}\${_RelFolder}"
	!insertmacro PackageCommonPages

	!insertmacro MUI_UNPAGE_CONFIRM
	!insertmacro UninstallRemovesUserData "${_RelFolder}"
	!insertmacro MUI_UNPAGE_INSTFILES

!macroend

!macro PackageEnd
	
	!insertmacro PackageTexts
	!insertmacro DeployUninstaller

!macroend

!macro Package _RelFolder
	
	!insertmacro PackageBegin ${_RelFolder}
	!insertmacro PackageEnd

!macroend

!macro PackageWithRun _RelFolder _RunFunction

	!insertmacro PackageBegin ${_RelFolder}
	
	!define MUI_FINISHPAGE_RUN
	!define MUI_FINISHPAGE_RUN_FUNCTION ${_RunFunction}
	!define MUI_PAGE_CUSTOMFUNCTION_PRE RunAndExit
	!insertmacro MUI_PAGE_FINISH

	Function RunAndExit
		${GetOptions} $CMDLINE "--autorun:" $0
		${If} $0 == "1"
			Call ${_RunFunction}
			Quit
		${Endif}
	FunctionEnd

	!insertmacro PackageEnd

!macroend

!macro SubPackage _PackageName _AbsFolder

	!insertmacro PackageBasics "${_PackageName}" "${_AbsFolder}"
	!insertmacro PackageCommonPages

	!insertmacro PackageEnd

!macroend

!macro DeployApi _BinaryName _IncludePath

	${EchoItem} "Module API           : ${_BinaryName}"

	!define _RuntimeBinary "${InstallDir}\bin\${_BinaryName}.dll"
	!define _StaticBinary "${InstallDir}\lib\${_BinaryName}.lib"
	
!if /FileExists "${_RuntimeBinary}"
	!define _IsRuntimeModule 1
!else if /FileExists "${_StaticBinary}"
	!define _IsRuntimeModule 0
!else
	!error "Module '${_BinaryName}' not found!"
!endif
	
	Section "${_BinaryName}-API"
		; module binary
!if ${_IsRuntimeModule}
		SetOutPath "$INSTDIR\bin"
		File "${_RuntimeBinary}"
		
		; module library archive
		SetOutPath "$INSTDIR\lib"
		File "${InstallDir}\bin\${_BinaryName}.lib"
!else
		SetOutPath "$INSTDIR\lib"
		File "${InstallDir}\lib\${_BinaryName}.lib"
!endif		
		; module interface
		SetOutPath "$INSTDIR\include\${_IncludePath}"
		File /r "${InstallDir}\include\${_IncludePath}\*.h"
	SectionEnd
	
	Section "Un.${_BinaryName}-API"
		; module binary
!if ${_IsRuntimeModule}
		Delete "$INSTDIR\bin\${_BinaryName}.dll"
		RMDir "$INSTDIR\bin"
!endif		
		; module library archive
		Delete "$INSTDIR\lib\${_BinaryName}.lib"
		RMDir "$INSTDIR\lib"
		
		; module interface
		RMDir /r "$INSTDIR\include\${_IncludePath}"
		RMDir "$INSTDIR\include"
		
		RMDir "$INSTDIR"
	SectionEnd
	
	!undef _RuntimeBinary
	!undef _StaticBinary
	!undef _IsRuntimeModule
	
!macroend

!macro DeploySdkApi _SdkModuleName
	!insertmacro DeployApi "${_SdkModuleName}" "${_SdkModuleName}"
!macroend

!macro DeployModuleApi _ModuleName
	!insertmacro DeployApi "${COMPONENT_NAME}${_ModuleName}" "${COMPONENT_NAME}\${_ModuleName}"
	Section "Un.SDK-interface"
		RMDir "$INSTDIR\include\sdk"
		RMDir "$INSTDIR\include"
		RMDir "$INSTDIR"
	SectionEnd
!macroend

!endif ; __SYMBOID_PLATFORM_DEPLOY_PACKAGE_NSH__
