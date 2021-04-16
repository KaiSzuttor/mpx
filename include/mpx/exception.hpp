#ifndef MPX_EXCEPTION_HPP
#define MPX_EXCEPTION_HPP

#include <mpi.h>

#include <stdexcept>

namespace mpx {
struct exception : std::exception {
  exception(int error_code) : error_code(error_code) {}
  int error_code;
};

void check_error_code(int return_code) {
  if (MPI_SUCCESS == return_code)
    return;

  throw exception{return_code};
}
} // namespace mpx

#endif // MPX_EXCEPTION_HPP
