# cython: language_level = 3
# distutils: language = c++

from libcpp.vector cimport vector

cdef extern from "population.hpp" namespace "genalg":
    cdef cppclass Population[I]:
        Population() except +
        Population(
            size_t capacity
        ) except +

        # accessors
        size_t capacity() const
        const vector[I]& individuals() const

        void append(const I& individual)
