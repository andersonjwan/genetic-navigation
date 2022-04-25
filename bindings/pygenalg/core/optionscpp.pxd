# cython: language_level = 3
# distutils: language = c++

cdef extern from "algorithm/options.hpp" namespace "genalg::algorithm":
    cdef cppclass Options:
        Options(
            size_t population_cap,
            double p_mutation
        ) except +
