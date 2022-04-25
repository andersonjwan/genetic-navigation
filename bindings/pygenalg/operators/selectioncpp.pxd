# cython: language_level = 3
# distutils: language = c++

cdef extern from "operators/selection.hpp" namespace "genalg::operators":
    cdef cppclass SelectionOperator[I]:
        pass

    cdef cppclass TournamentSelection[I]:
        TournamentSelection(
            size_t size,
            double prob
        ) except +
