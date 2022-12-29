# simple-uac-prompt
UAC (User Account Control) prompt in C++ for Windows 10


This code first sets the elevation type of the current process to TokenElevationTypeFull, which causes a UAC prompt to be shown when the process is launched. It then checks if the process is already elevated using the GetTokenInformation function, and if it is, it simply prints a message and exits. If the process is not already elevated, it uses the ShellExecuteEx function to launch a new instance of the process with a UAC prompt. The new instance of the process is specified in the lpFile parameter of the SHELLEXECUTEINFO structure, and the lpVerb parameter is set to "runas" to trigger the UAC prompt.

The main process then waits for the elevated process to finish using the WaitForSingleObject function
