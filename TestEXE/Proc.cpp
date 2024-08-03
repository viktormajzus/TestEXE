#include "pch.h"
#include "Proc.h"

Proc::Proc(std::wstring_view processName)
{
  this->processId = MemFuncs::FetchProcessId(processName);
  if (!processId)
  {
    std::cerr << this->processId.error() << "\n";
    std::exit(EXIT_FAILURE);
  }

  this->processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, *this->processId);
  if (this->processHandle == INVALID_HANDLE_VALUE)
  {
    std::cerr << Errors::error_handle_failure << "\n";
    std::exit(EXIT_FAILURE);
  }
}

Proc::~Proc()
{
  if (this->processHandle != INVALID_HANDLE_VALUE)
  {
    CloseHandle(this->processHandle);
  }
}

std::expected<std::uint32_t, Errors> MemFuncs::FetchProcessId(std::wstring_view processName)
{
  HANDLE hSnapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
  if (hSnapshot == INVALID_HANDLE_VALUE)
    return std::unexpected(Errors::error_failed_snapshot);

  PROCESSENTRY32 PE32{ .dwSize = sizeof(PROCESSENTRY32) };

  Process32First(hSnapshot, &PE32);

  do
  {
    if (processName.compare(PE32.szExeFile)) // If not 0 (which is the return value of a successful comparison)
      continue;

    CloseHandle(hSnapshot);
    return static_cast<std::uint32_t>(PE32.th32ProcessID);

  } while (Process32Next(hSnapshot, &PE32));

  CloseHandle(hSnapshot);

  return std::unexpected(Errors::error_process_not_found);
}