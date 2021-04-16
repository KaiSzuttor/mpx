#ifndef MPX_API_HPP
#define MPX_API_HPP

#include <mpi.h>

namespace mpx {
struct api {
  static constexpr auto rank = &MPI_Comm_rank;
};
} // namespace mpx

#endif