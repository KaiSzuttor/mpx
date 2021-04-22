# mpx

`mpx` is a light-wright for the C API of the message passing interface (MPI).

## Goals

- Provide a safer interface to MPI
- Reduce boilerplate by using type information
- Provide tools to improve testability of MPI code

## Non-Goals

- Adding functionality, this library is only syntactic sugar
  for the C API
- Support transmission of complex types, e.g. via serialization:
  this should/could be implemented on top of mpx.
