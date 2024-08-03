#include "pch.h"
#include "error.h"

std::string_view ErrorParser(Errors e)
{
  switch (e)
  {
  case Errors::error_process_not_found:
    return "ERROR: Failed to find process!";
  case Errors::error_failed_snapshot:
    return "ERROR: Failed to create snapshot!";
  case Errors::error_handle_failure:
    return "ERROR: Failed to open handle!";
  case Errors::error_read_memory:
    return "ERROR: Failed to read memory!";
  case Errors::error_write_memory:
    return "ERROR: Failed to write memory!";
  default:
    return "ERROR: Unknown error!";
  }
}

std::ostream& operator<<(std::ostream& out, Errors error)
{
  out << ErrorParser(error);
  return out;
}