#ifndef MPX_DATA_TYPE_HPP
#define MPX_DATA_TYPE_HPP

#include <type_traits>

#include <mpi.h>

namespace mpx {
struct DataType {
  MPI_Datatype type = MPI_DATATYPE_NULL;
  size_t count = 0;

  bool operator==(DataType const &rhs) const {
    return std::tie(type, count) == std::tie(rhs.type, rhs.count);
  }
  bool operator!=(DataType const &rhs) const { return not(*this == rhs); }
};

template <class T, class = void> struct data_type_for {};

template <class T, class = void> struct trivial_opt_in : std::false_type {};
template <class T>
struct data_type_for<T, std::enable_if_t<std::is_trivially_copyable_v<T> and
                                         trivial_opt_in<T>::value>> {
  DataType operator()() const { return {MPI_BYTE, sizeof(T)}; }
};

/**
 * @brief Type traits marking built-in mpi types.
 */
template <class T> struct is_builtin_type : std::false_type {};

template <> struct is_builtin_type<char> : std::true_type {
  static auto mpi_type() { return MPI_CHAR; }
};

template <> struct is_builtin_type<short> : std::true_type {
  static auto mpi_type() { return MPI_SHORT; }
};

template <> struct is_builtin_type<int> : std::true_type {
  static auto mpi_type() { return MPI_INT; }
};

template <> struct is_builtin_type<long> : std::true_type {
  static auto mpi_type() { return MPI_LONG; }
};

template <> struct is_builtin_type<float> : std::true_type {
  static auto mpi_type() { return MPI_FLOAT; }
};

template <> struct is_builtin_type<double> : std::true_type {
  static auto mpi_type() { return MPI_DOUBLE; }
};

template <> struct is_builtin_type<long double> : std::true_type {
  static auto mpi_type() { return MPI_LONG_DOUBLE; }
};

template <> struct is_builtin_type<unsigned char> : std::true_type {
  static auto mpi_type() { return MPI_UNSIGNED_CHAR; }
};

template <> struct is_builtin_type<unsigned short> : std::true_type {
  static auto mpi_type() { return MPI_UNSIGNED_SHORT; }
};

template <> struct is_builtin_type<unsigned> : std::true_type {
  static auto mpi_type() { return MPI_UNSIGNED; }
};

template <> struct is_builtin_type<unsigned long> : std::true_type {
  static auto mpi_type() { return MPI_UNSIGNED_LONG; }
};

template <> struct is_builtin_type<unsigned long long> : std::true_type {
  static auto mpi_type() { return MPI_UNSIGNED_LONG_LONG; }
};

template <class T>
struct data_type_for<T, std::enable_if_t<is_builtin_type<T>::value>> {
  DataType operator()() const { return {is_builtin_type<T>::mpi_type(), 1}; }
};
} // namespace mpx

#endif // MPX_DATATYPE_HPP
