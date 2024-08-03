#include "pch.h"
#include "Process.h"
#include "Offsets.h"

using namespace std::string_literals;

/*
# Changes to implement:
- Initialize moduleBase in constructor
- Move error checking to constructor
- Clear up main()
- Use a struct with padding instead of individual offsets
- Add more utility functions
- Create a struct to hold process name and module name
- Use said struct in constructor
- Maybe move infinite game loop to separate class?
- Maybe add an InputManager?
*/

int main()
{
  // Struct for process and module names?
  std::wstring procName{ L"ac_client.exe"s };
  Process process(procName);

  std::wstring moduleName{ L"ac_client.exe"s };
  process.moduleBase = process.SetModuleBase(moduleName);

  if (!process.moduleBase) // Add error checking to constructor to clean up main()?
  {
    std::cerr << process.moduleBase.error();
    std::exit(EXIT_FAILURE);
  }

  std::uintptr_t localPlayer{ process.Read<std::uintptr_t>(*process.moduleBase + Offsets::playerBase) };

  int newHealth{ 1000 };

  // Move game loop to a separate class?
  while (!GetAsyncKeyState(VK_DELETE) & 1)
  {
    process.Write<int>(localPlayer + Offsets::i_Health, newHealth);

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }

  std::exit(EXIT_SUCCESS);
}