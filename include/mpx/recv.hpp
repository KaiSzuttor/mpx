#ifndef MPX_RECV_HPP
#define MPX_RECV_HPP

#include <mpx/communicator.hpp>
#include <mpx/data_range.hpp>
#include <mpx/request.hpp>

#include <mpi.h>

namespace mpx {
template <class T>
void recv(communicator const &comm, Rank to, Tag tag, T &data) {
  auto const data_range = data_range_for<T>{}(data);

  check_error_code(MPI_recv(data_range.data, data_range.type.count,
                            data_range.type.type, static_cast<int>(to),
                            static_cast<int>(tag), comm));
}
} // namespace mpx

#endif