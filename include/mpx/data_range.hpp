#ifndef MPX_DATA_RANGE_HPP
#define MPX_DATA_RANGE_HPP

#include <mpx/data_type.hpp>

#include <type_traits>

namespace mpx {
struct MutableDataRange {
  void *data;
  DataType type;

  bool operator==(MutableDataRange const &rhs) const {
    return std::tie(data, type) == std::tie(rhs.data, rhs.type);
  }
  bool operator!=(MutableDataRange const &rhs) const {
    return not(*this == rhs);
  }
};
struct ConstDataRange {
  const void *data;
  DataType type;

  bool operator==(ConstDataRange const &rhs) const {
    return std::tie(data, type) == std::tie(rhs.data, rhs.type);
  }
  bool operator!=(ConstDataRange const &rhs) const { return not(*this == rhs); }
};

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

template <class T>
struct data_range_for<
    T, std::enable_if_t<std::disjunction_v<std::is_same<T, MutableDataRange>,
                                           std::is_same<T, ConstDataRange>>>> {
  static auto get(T data_range) { return data_range; }
};
} // namespace mpx

#endif