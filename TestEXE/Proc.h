#pragma once
#include "pch.h"

#include "error.h"

class Proc
{
private:
  std::expected<std::uint32_t, Errors> processId{};
  HANDLE processHandle{};

public:
  Proc(std::wstring_view processName);
  ~Proc();

public:
  template<typename T>
  std::expected<T, Errors> Read(std::uintptr_t address)
  {
    T temp{};
    if (!ReadProcessMemory(this->processHandle,
                           reinterpret_cast<LPCVOID>(address),
                           &temp,
                           sizeof(T),
                           0))
    { // If statement
      std::cerr << Errors::error_read_memory << "\n";
      return std::unexpected(Errors::error_read_memory);
    }

    return temp;
  }

  template<typename T>
  std::expected<T, Errors> Write(std::uintptr_t address, const T& value)
  {
    if (!WriteProcessMemory(this->processHandle,
                            reinterpret_cast<LPVOID>(address),
                            &value,
                            sizeof(value),
                            0))
    { // If statement
      std::cerr << Errors::error_write_memory << "\n";
      return std::unexpected(Errors::error_write_memory);
    }

    return 0;
  }
};

namespace MemFuncs
{
std::expected<std::uint32_t, Errors> FetchProcessId(std::wstring_view processName);
}
