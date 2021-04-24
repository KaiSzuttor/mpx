#include <doctest/doctest.h>

#include <mpx/data_type.hpp>

TEST_CASE("supported types are mapped to build-in mpi types") {
  auto const expected = mpx::DataType{MPI_INT, 1};
  auto const result = mpx::data_type_for<int>::get();

  CHECK_EQ(expected, result);
}