cdef extern from "operators/crossover.hpp" namespace "genalg::operators":
    cdef cppclass CrossoverOperator[I]

    cdef cppclass MultiPointCrossover[I]:
        MultiPointCrossover(size_t n_crossovers) except +

    cdef cppclass SinglePointCrossover[I]:
        SinglePointCrossover() except +
