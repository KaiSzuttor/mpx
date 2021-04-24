#include <doctest/doctest.h>

#include <mpx/data_range.hpp>

TEST_CASE("scalar types are a range of one") {
  int i;

  CHECK(mpx::data_range_for<int>::get(i) ==
        mpx::MutableDataRange{&i, 1, mpx::data_type_for<int>::get()});
  CHECK(mpx::data_range_for<int>::get(std::as_const(i)) ==
        mpx::ConstDataRange{&i, 1, mpx::data_type_for<int>::get()});
}

TEST_CASE("data ranges are passed-thru") {
  {
    auto in_range = mpx::MutableDataRange{(void *)0xdeadbeef, {}};
    CHECK(mpx::data_range_for<mpx::MutableDataRange>::get(in_range) ==
          in_range);
  }

  {
    auto in_range = mpx::ConstDataRange{(void *)0xdeadbeef, {}};
    CHECK(mpx::data_range_for<mpx::ConstDataRange>::get(in_range) == in_range);
  }
}

TEST_CASE("make_data_range") {
  const int i = 5;
  CHECK(mpx::make_data_range(&i, 5) ==
        mpx::ConstDataRange{reinterpret_cast<const void *>(&i), 5, MPI_INT});
}