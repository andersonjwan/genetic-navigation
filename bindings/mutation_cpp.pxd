cdef extern from "operators/mutation.hpp" namespace "genalg::operators":
    cdef cppclass MutationOperator[I]

    cdef cppclass InversionMutation[I]:
        InversionMutation() except +
