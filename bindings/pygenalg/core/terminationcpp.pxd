# cython: language_level = 3
# distutils: language = c++

cdef extern from "algorithm/termination.hpp" namespace "genalg::algorithm":
    cdef cppclass TerminationCondition[I]:
        pass

    cdef cppclass GenerationLimit[I]:
        GenerationLimit(
            size_t limit
        ) except +

    cdef cppclass BestLimit[I]:
        BestLimit(
            size_t limit
        ) except +
