#include "pch.h"
#include "Process.h"

using namespace std::string_literals;

int main()
{
  std::wstring procName{ L"ac_client.exe"s };

  Process process(procName);

  // Magic numbers only used for testing
  // Didn't implement a function to get the module address yet
  std::cout << "Player health: " << process.Read<std::int32_t>(0x00FBA478) << "\n";

  process.Write<std::int32_t>(0x00FBA478, 500);

  std::exit(EXIT_SUCCESS);
}