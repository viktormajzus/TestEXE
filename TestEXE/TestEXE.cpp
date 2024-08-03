#include "pch.h"
#include "Process.h"
#include "Offsets.h"

using namespace std::string_literals;

int main()
{
  std::wstring procName{ L"ac_client.exe"s };
  Process process(procName);

  std::wstring moduleName{ L"ac_client.exe"s };
  process.moduleBase = process.SetModuleBase(moduleName);

  if (!process.moduleBase)
  {
    std::cerr << process.moduleBase.error();
    std::exit(EXIT_FAILURE);
  }

  std::uintptr_t localPlayer{ process.Read<std::uintptr_t>(*process.moduleBase + Offsets::playerBase) };

  int newHealth{ 1000 };

  while (!GetAsyncKeyState(VK_DELETE) & 1)
  {
    process.Write<int>(localPlayer + Offsets::i_Health, newHealth);

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }

  std::exit(EXIT_SUCCESS);
}