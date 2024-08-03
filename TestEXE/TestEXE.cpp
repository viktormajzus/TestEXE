#include "pch.h"
#include "Process.h"
#include "Offsets.h"

using namespace std::string_literals;

/*
# Changes to implement:
[DONE] Initialize moduleBase in constructor
[DONE] Move error checking to constructor
- Clear up main()
- Use a struct with padding instead of individual offsets
- Add more utility functions
[DONE] Create a struct to hold process name and module name
[DONE] Use said struct in constructor
- Maybe move infinite game loop to separate class?
- Maybe add an InputManager?
*/

int main()
{
  TargetProcess targetProcess{ L"ac_client.exe", L"ac_client.exe" };
  Process process(targetProcess);

  std::uintptr_t localPlayer{ process.Read<std::uintptr_t>(process.GetModuleBase() + Offsets::playerBase)};

  int newHealth{ 1000 };

  // Move game loop to a separate class?
  while (!GetAsyncKeyState(VK_DELETE) & 1)
  {
    process.Write<int>(localPlayer + Offsets::i_Health, newHealth);

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }

  std::exit(EXIT_SUCCESS);
}