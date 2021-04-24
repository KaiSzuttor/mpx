#include <doctest/doctest.h>

#include <mpx/data_type.hpp>

TEST_CASE("supported types are mapped to build-in mpi types") {
  auto const expected = MPI_INT;
  auto const result = mpx::data_type_for<int>::get();

  CHECK_EQ(expected, result);
}