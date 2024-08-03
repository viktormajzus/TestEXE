#include "pch.h"
#include "Process.h"

Process::Process(std::wstring_view processName)
{
  processId = Memory::FetchProcessId(processName);
  if (!processId)
  {
    std::cerr << processId.error() << "\n";
    std::exit(EXIT_FAILURE);
  }

  process = OpenProcess(PROCESS_ALL_ACCESS, false, *processId);
  if (process == INVALID_HANDLE_VALUE)
  {
    std::cerr << Errors::error_handle_failure << "\n";
    std::exit(EXIT_FAILURE);
  }
}

Process::~Process()
{
  if (process != INVALID_HANDLE_VALUE)
  {
    CloseHandle(process);
  }
}

std::expected<std::uintptr_t, Errors> Process::SetModuleBase(std::wstring_view moduleBase)
{
  HANDLE snapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, *processId) };
  if (snapshot == INVALID_HANDLE_VALUE)
    return std::unexpected(Errors::error_failed_snapshot);

  MODULEENTRY32 moduleEntry{ .dwSize = sizeof(MODULEENTRY32) };

  Module32First(snapshot, &moduleEntry);

  do
  {
    if (moduleBase.compare(moduleEntry.szModule)) // If not 0
      continue;

    CloseHandle(snapshot);
    return reinterpret_cast<std::uintptr_t>(moduleEntry.modBaseAddr);
  } while (Module32Next(snapshot, &moduleEntry));

  CloseHandle(snapshot);

  return std::unexpected(Errors::error_module_not_found);
}

std::expected<std::uint32_t, Errors> Memory::FetchProcessId(std::wstring_view processName)
{
  HANDLE snapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
  if (snapshot == INVALID_HANDLE_VALUE)
    return std::unexpected(Errors::error_failed_snapshot);

  PROCESSENTRY32 processEntry{ .dwSize = sizeof(PROCESSENTRY32) };

  Process32First(snapshot, &processEntry);

  do
  {
    if (processName.compare(processEntry.szExeFile)) // If not 0 (which is the return value of a successful comparison)
      continue;

    CloseHandle(snapshot);
    return static_cast<std::uint32_t>(processEntry.th32ProcessID);

  } while (Process32Next(snapshot, &processEntry));

  CloseHandle(snapshot);

  return std::unexpected(Errors::error_process_not_found);
}