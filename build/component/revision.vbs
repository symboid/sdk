
dim Shell, Fs
set Shell = WScript.CreateObject("WScript.Shell")
set Fs = WScript.CreateObject("Scripting.FileSystemObject")
const ForReading = 1


ScriptDir = Fs.GetParentFolderName(WScript.ScriptFullName)

if WScript.Arguments.Count < 1 then
	WScript.Echo "!!! Component name must be specified! Exiting..."
	WScript.Quit 1
end if

ComponentName = WScript.Arguments(0)
ComponentHome = Fs.GetAbsolutePathName(ScriptDir & "\..\..\" & ComponentName)
ComponentRevId  = Shell.Exec("hg id --id " & ComponentHome).StdOut.ReadLine()

RevisionStamp = ComponentHome & "\.revision.stamp"
if Fs.FileExists(RevisionStamp) then
	set TsFile = Fs.GetFile(RevisionStamp)
	TsRevId = Fs.OpenTextFile(RevisionStamp,ForReading).ReadLine()
	if TsRevId = ComponentRevId then
                WScript.Echo "No changed in component revision."
		WScript.Quit 0
	end if
end if

dim ComponentTs
set ComponentTs = Fs.CreateTextFile(RevisionStamp, true)
ComponentTs.WriteLine ComponentRevId
ComponentTs.Close
set ComponentTs = nothing
WScript.Echo "Component revision stamp '" & RevisionStamp & "' updated."
