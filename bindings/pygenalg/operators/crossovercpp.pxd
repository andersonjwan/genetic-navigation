# cython: language_level = 3
# distutils: language = c++

cdef extern from "operators/crossover.hpp" namespace "genalg::operators":
    cdef cppclass CrossoverOperator[G]:
        pass

    cdef cppclass MultiPointCrossover[G]:
        MultiPointCrossover(
            size_t n_crossovers,
            size_t gene_size
        ) except +

    cdef cppclass SinglePointCrossover[G]:
        SinglePointCrossover(
            size_t gene_size
        ) except +
