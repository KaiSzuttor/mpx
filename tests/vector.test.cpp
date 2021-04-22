#include <doctest/doctest.h>

#include <mpx/vector.hpp>

TEST_CASE("data range for vectors of built-in type") {
  std::vector<int> vec(4);

  CHECK(mpx::data_range_for<decltype(vec)>::get(vec) ==
        mpx::make_data_range(vec.data(), vec.size()));
}
