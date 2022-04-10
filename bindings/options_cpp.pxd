cdef extern from "algorithm/options.hpp" namespace "genalg::algorithm":
    cdef cppclass Options:
        const size_t population_size;
        const size_t n_generations;
        const double mutation_chance;
        unsigned long int seed;

        Options(size_t p, size_t g, double m) except +
        Options(size_t p, size_t g, double m, unsigned long int s) except +
