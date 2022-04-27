# cython: language_level = 3
# distutils: language = c++

cdef extern from "algorithm/options.hpp" namespace "genalg::algorithm":
    cdef cppclass Options:
        const size_t population_capacity
        const double p_mutation
        unsigned long int seed

        Options(
            size_t population_cap,
            double p_mutation
        ) except +

        Options(
            size_t population_cap,
            double p_mutation,
            unsigned long int seed
        ) except +
