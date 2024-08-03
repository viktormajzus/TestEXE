#pragma once

enum class Errors
{
  error_unknown,
  error_process_not_found,
  error_failed_snapshot,
  error_handle_failure,
  error_read_memory,
  error_write_memory
};

std::string_view ErrorParser(Errors e);

std::ostream& operator<<(std::ostream& out, Errors error);