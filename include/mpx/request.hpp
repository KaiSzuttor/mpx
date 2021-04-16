#ifndef MPX_FUTURE_HPP
#define MPX_FUTURE_HPP

#include <mpx/exception.hpp>

#include <mpi.h>

#include <utility>

namespace mpx {
using request = MPI_Request;

bool test(request &req) {
  int ret = 0;
  check_error_code(
      MPI_Test(std::addressof(req), std::addressof(ret), MPI_STATUS_IGNORE));

  return ret != 0;
}

void wait(request &req) {
  check_error_code(MPI_Wait(std::addressof(req), MPI_STATUS_IGNORE));
}
} // namespace mpx

#endif