cdef extern from "algorithm/options.hpp" namespace "genalg::algorithm":
    cdef cppclass Options:
        const size_t population_capacity;
        const double p_mutation;
        unsigned long int seed;

        Options(size_t p, double m) except +
        Options(size_t p, double m, unsigned long int s) except +
