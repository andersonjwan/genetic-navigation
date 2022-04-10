from libcpp cimport bool

cdef extern from "operators/selection.hpp" namespace "genalg::operators":
    cdef cppclass SelectionOperator[I, F]

    cdef cppclass TournamentSelection[I, F]:
        TournamentSelection(size_t s, double p, bool r) except +
