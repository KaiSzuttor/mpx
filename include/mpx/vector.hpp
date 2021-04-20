#ifndef MPX_VECTOR_HPP
#define MPX_VECTOR_HPP

#include <mpx/data_range.hpp>

#include <vector>

namespace mpx {
template <class T> struct data_range_for<std::vector<T>> {
  DataRange<T> operator()(std::vector<T> &e) const {
    auto const element_type = data_type_for<std::remove_cv_t<T>>{}();

    return {e.data(),
            DataType{element_type.type,
                     static_cast<int>(e.size() * element_type.count)}};
  }

  DataRange<const T> operator()(std::vector<T> const &e) const {
    auto const element_type = data_type_for<std::remove_cv_t<T>>{}();

    return {e.data(),
            DataType{element_type.type,
                     static_cast<int>(e.size() * element_type.count)}};
  }
};
} // namespace mpx

#endif