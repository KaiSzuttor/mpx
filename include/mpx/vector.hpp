#ifndef MPX_VECTOR_HPP
#define MPX_VECTOR_HPP

#include <mpx/data_range.hpp>

#include <vector>

namespace mpx {
template <class T> struct data_range_for<std::vector<T>> {  
  static MutableDataRange get(std::vector<T> &v) {
    return make_data_range(v.data(), v.size());
  }

  static ConstDataRange get(std::vector<T> const&v) {
    return make_data_range(v.data(), v.size());
  }
};
} // namespace mpx

#endif