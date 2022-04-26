# cython: language_level = 3
# distutils: language = c++

from libcpp cimport bool
from ..populationcpp cimport Population

cdef extern from "algorithm/termination.hpp" namespace "genalg::algorithm":
    cdef cppclass TerminationCondition[I]:
        bool terminate(const Population[I]& population)

    cdef cppclass GenerationLimit[I]:
        GenerationLimit(
            size_t limit
        ) except +

        bool terminate(const Population[I]& population)

    cdef cppclass BestLimit[I]:
        BestLimit(
            size_t limit
        ) except +

        bool terminate(const Population[I]& population)
