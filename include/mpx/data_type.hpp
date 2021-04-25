#ifndef MPX_DATA_TYPE_HPP
#define MPX_DATA_TYPE_HPP

#include <type_traits>

#include <mpi.h>

namespace mpx {
using DataType = MPI_Datatype;

template <class T, class = void> struct data_type_for {};

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
  static DataType get() { return is_builtin_type<T>::mpi_type(); }
};
} // namespace mpx

#endif // MPX_DATATYPE_HPP
