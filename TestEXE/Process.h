#pragma once
#include "pch.h"

#include "error.h"

class Process
{
private:
  std::expected<std::uint32_t, Errors> processId{};
  HANDLE process{};

public:
  std::expected<std::uintptr_t, Errors> moduleBase{};

public:
  Process(std::wstring_view processName);
  ~Process();

public:
  template<typename T>
  T Read(std::uintptr_t address)
  {
    T temp{};
    ReadProcessMemory(process,
                      reinterpret_cast<LPCVOID>(address),
                      &temp,
                      sizeof(T),
                      0);

      return temp;
    }

  template<typename T>
  void Write(std::uintptr_t address, const T& value)
  {
    WriteProcessMemory(process,
                       reinterpret_cast<LPVOID>(address),
                       &value,
                       sizeof(value),
                       0);
  }

  std::uint32_t GetProcId()
  {
    if (!processId)
    {
      std::cerr << Errors::error_process_not_found << "\n";
      return 0;
    }

    return *processId;
  }

  std::expected<std::uintptr_t, Errors> SetModuleBase(std::wstring_view moduleBaseAddress);
};

namespace Memory
{
std::expected<std::uint32_t, Errors> FetchProcessId(std::wstring_view processName);
}
