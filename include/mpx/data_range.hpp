#ifndef MPX_DATA_RANGE_HPP
#define MPX_DATA_RANGE_HPP

#include <mpx/data_type.hpp>

#include <type_traits>

namespace mpx {
template <bool Const> struct DataRange {
  std::conditional_t<Const, const void, void> *data;
  DataType type;

  bool operator==(DataRange const &rhs) const {
    return std::tie(data, type) == std::tie(rhs.data, rhs.type);
  }
  bool operator!=(DataRange const &rhs) const { return not(*this == rhs); }
};

using MutableDataRange = DataRange<false>;
using ConstDataRange = DataRange<true>;

template <class T>
std::conditional_t<std::is_const_v<T>, ConstDataRange, MutableDataRange>
make_data_range(T *data, size_t size) {
  static auto const element_type = data_type_for<std::remove_cv_t<T>>::get();
  return {data,
          {element_type.type, static_cast<int>(size) * element_type.count}};
}

template <class T, class = void> struct data_range_for {
  static MutableDataRange get(T &value) {
    return make_data_range(std::addressof(value), 1);
  }
  static ConstDataRange get(T const &value) {
    return make_data_range(std::addressof(value), 1);
  }
};

template <bool Const> struct data_range_for<DataRange<Const>> {
  static DataRange<Const> get(DataRange<Const> data_range) {
    return data_range;
  }
};
} // namespace mpx

#endif