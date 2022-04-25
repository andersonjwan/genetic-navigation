# cython: language_level = 3
# distutils: language = c++

from .selectioncpp cimport TournamentSelection as cppTournamentSelection

cdef class TournamentSelection:
    cdef cppTournamentSelection[double]* _objcpp

    def __cinit__(self, size: int, prob: float) -> None:
        self._objcpp = new cppTournamentSelection[double](size, prob)
        print("cython: cppTournamentSelection allocated...")

    def __dealloc__(self) -> None:
        del self._objcpp
        print("cython: cppTournamentSelection deallocated...")
