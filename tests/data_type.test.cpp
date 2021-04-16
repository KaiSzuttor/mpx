#include <doctest/doctest.h>

#include <mpx/data_type.hpp>

struct Trivial {
  int i;
} trivial;

namespace mpx {
template <> struct trivial_opt_in<Trivial> : std::true_type {};
} // namespace mpx

TEST_CASE("trivial types are arrays of bytes") {
  auto const expected = mpx::DataType{MPI_BYTE, sizeof(Trivial)};
  auto const result = mpx::data_type_for<Trivial>{}();

  CHECK_EQ(expected, result);
}

TEST_CASE("supported types are mapped to build-in mpi types") {
  auto const expected = mpx::DataType{MPI_INT, 1};
  auto const result = mpx::data_type_for<int>{}();

  CHECK_EQ(expected, result);
}