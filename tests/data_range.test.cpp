#include <doctest/doctest.h>

#include <mpx/data_range.hpp>

TEST_CASE("scalar types are a range of one") {
  int i;
  auto const result = mpx::data_range_for<int>{}(i);
  auto const expected = mpx::DataRange<int>{&i, mpx::data_type_for<int>::get()};

  CHECK_EQ(result.data, expected.data);
  CHECK_EQ(result.type, expected.type);
}