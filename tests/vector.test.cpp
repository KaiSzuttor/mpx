#include <doctest/doctest.h>

#include <mpx/vector.hpp>

TEST_CASE("data range for vectors of built-in type") {
  std::vector<int> vec(4);

  auto const result = mpx::data_range_for<decltype(vec)>{}(vec);

  CHECK(result.data == vec.data());
  CHECK(result.type == mpx::DataType{MPI_INT, static_cast<int>(vec.size())});
}

struct Trivial {
  int i;
} trivial;

namespace mpx {
template <> struct trivial_opt_in<Trivial> : std::true_type {};
} // namespace mpx

TEST_CASE("data range for vectors of trivial type") {
  std::vector<Trivial> vec(4);

  auto const element_type = mpx::data_type_for<decltype(vec)::value_type>{}();

  auto const result = mpx::data_range_for<decltype(vec)>{}(vec);

  CHECK(result.data == vec.data());
  CHECK(result.type ==
        mpx::DataType{element_type.type,
                      static_cast<int>(element_type.count * vec.size())});
}
