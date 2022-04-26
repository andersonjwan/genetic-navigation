# cython: language_level = 3
# distutils: language = c++

from libcpp cimport bool
from libcpp.vector cimport vector

from ..individualcpp cimport Individual as cppIndividual
from .selectioncpp cimport TournamentSelection as cppTournamentSelection

cdef class TournamentSelection:
    cdef cppTournamentSelection[cppIndividual[vector[bool], double]]* _objcpp

    def __cinit__(self, size: int, prob: float) -> None:
        self._objcpp = new cppTournamentSelection[cppIndividual[vector[bool], double]](size, prob)

    def __dealloc__(self) -> None:
        del self._objcpp
