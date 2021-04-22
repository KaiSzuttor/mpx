#ifndef MPX_DATA_RANGE_HPP
#define MPX_DATA_RANGE_HPP

#include <mpx/data_type.hpp>

#include <type_traits>

namespace mpx {
template <class T> struct DataRange {
  T *data;
  DataType type;
};

template <class T, class = void> struct data_range_for {
  DataRange<T> operator()(T &e) const {
    return {std::addressof(e), data_type_for<std::remove_cv_t<T>>::get()};
  }
};

template <class T> struct data_range_for<DataRange<T>> {
  DataRange<T> operator()(DataRange<T> data_range) const { return data_range; }
};
} // namespace mpx

#endif