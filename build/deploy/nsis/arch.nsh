
!ifndef __SYMBOID_PLATFORM_DEPLOY_ARCH_NSH__
!define __SYMBOID_PLATFORM_DEPLOY_ARCH_NSH__

!include X64.nsh

; Type of binary architecture excpected:
!ifdef _Config_AllArch
	!define BuildArch All
!else ifdef _Config_x86
	!define BuildArch x86
	!define BuildArchNum 32
!else
	!define BuildArch x64
	!define BuildArchNum 64
!endif

;-------------------------------------------------------------------------------
; Toolchain selected:
;
!ifdef _Config_Toolchain
	!define Toolchain "${_Config_Toolchain}"
!else
	!define Toolchain "msvc2017"
!endif

!if `${Toolchain}` == `msvc2017`
	!define ToolchainNum "15"
!else if `${Toolchain}` == `msvc2015`
	!define ToolchainNum "14"
!else if  `${Toolchain}` == `msvc2013`
	!define ToolchainNum "12"
!else
	!define ToolchainNum "??"
!endif


;-------------------------------------------------------------------------------
; Directory of Program Files:
;
!if `${BuildArch}` == `x86`
	!define ProgramFilesDir $PROGRAMFILES32
!else
	!define ProgramFilesDir $PROGRAMFILES64
!endif

; validation of running architecture
!macro Arch64Check
	; when package is 64 bit and OS is 32 bit
	; installation cannot be executed
	!if `${BuildArch}` == `x64`
		${If} ${RunningX64}
		${Else}
			MessageBox MB_OK|MB_ICONSTOP "$(TextCannotExecute64BitInstaller)"
			Abort
		${EndIf}
	!endif

	; when package is 32 bit and OS is 64 bit
	; the 64 bit compilation will be recommended
	!if `${BuildArch}` == `x86`
		${If} ${RunningX64}
			IfSilent continue
			MessageBox MB_YESNO|MB_ICONQUESTION  "$(TextRecommend64BitInstaller)" IDYES continue
			Abort
			continue:
		${EndIf}
	!endif
!macroend

!endif ; __SYMBOID_PLATFORM_DEPLOY_ARCH_NSH__
