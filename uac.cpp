#include <Windows.h>

int main()
{
    // Elevate the process to require UAC elevation
    if (!SetTokenInformation(GetCurrentProcessToken(), TokenElevationType, TokenElevationTypeFull, sizeof(TOKEN_ELEVATION_TYPE)))
    {
        std::cerr << "Error: SetTokenInformation failed, error code: " << GetLastError() << std::endl;
        return 1;
    }

    // Check if the process is already elevated
    TOKEN_ELEVATION_TYPE elevationType;
    DWORD dwSize;
    if (!GetTokenInformation(GetCurrentProcessToken(), TokenElevationType, &elevationType, sizeof(elevationType), &dwSize))
    {
        std::cerr << "Error: GetTokenInformation failed, error code: " << GetLastError() << std::endl;
        return 1;
    }

    if (elevationType == TokenElevationTypeFull)
    {
        std::cout << "Process is already elevated" << std::endl;
        return 0;
    }

    // Launch a new instance of the process with UAC prompt
    SHELLEXECUTEINFO sei = { sizeof(sei) };
    sei.lpVerb = "runas";
    sei.lpFile = "C:\\Path\\To\\ElevatedProcess.exe";
    sei.nShow = SW_SHOWNORMAL;
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;

    if (!ShellExecuteEx(&sei))
    {
        std::cerr << "Error: ShellExecuteEx failed, error code: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "UAC prompt shown, waiting for elevated process to finish..." << std::endl;

    // Wait for the elevated process to finish
    WaitForSingleObject(sei.hProcess, INFINITE);

    // Get the exit code of the elevated process
    DWORD dwExitCode;
    GetExitCodeProcess(sei.hProcess, &dwExitCode);

    // Close the handle to the elevated process
    CloseHandle(sei.hProcess);

    std::cout << "Elevated process finished with exit code: " << dwExitCode << std::endl;

    return 0;
}
