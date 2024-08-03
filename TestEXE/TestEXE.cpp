#include "pch.h"
#include "Proc.h"

using namespace std::string_literals;

int main()
{
  std::wstring procName{ L"ac_client.exe"s };

  Proc process(procName);

  // Magic numbers only used for testing
  // Didn't implement a function to get the module address yet
  std::cout << "Player health: " << *process.Read<std::int32_t>(0x0108A478) << "\n";

  process.Write<std::int32_t>(0x0108A478, 500);

  std::exit(EXIT_SUCCESS);
}