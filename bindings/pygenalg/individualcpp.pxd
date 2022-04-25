# cython: language_level = 3
# distutils: language = c++

cdef extern from "population/individual.hpp" namespace "genalg::population":
    cdef cppclass Individual[G, F]:
        Individual(
            const G& genome,
            const F& fitness
        ) except +

        # accessors
        const G& genome() const
        const F& fitness() const

        # mutators
        void fitness(const F& fitness)
