# cython: language_level = 3
# distutils: language = c++

cdef extern from "operators/mutation.hpp" namespace "genalg::operators":
    cdef cppclass MutationOperator[G]:
        pass

    cdef cppclass BitFlipMutation[G]:
        BitFlipMutation(
            double p_inversion
        ) except +
