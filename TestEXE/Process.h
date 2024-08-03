#pragma once
#include "pch.h"

#include "error.h"

struct TargetProcess
{
  std::wstring processName{};
  std::wstring moduleName{};
};

class Process
{
private:
  std::expected<std::uint32_t, Errors> processId{};
  HANDLE process{};
  std::expected<std::uintptr_t, Errors> moduleBase{};

private:
  std::expected<std::uint32_t, Errors> FetchProcessId(std::wstring_view processName);
  std::expected<std::uintptr_t, Errors> SetModuleBase(std::wstring_view moduleBaseAddress);

public:
  Process(const TargetProcess& targetProcess);
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

  std::uint32_t GetProcessId();

  std::uintptr_t GetModuleBase();
};
