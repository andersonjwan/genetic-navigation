# cython: language_level = 3
# distutils: language = c++

from .selectioncpp cimport TournamentSelection as cppTournamentSelection

cdef class TournamentSelection:
    cdef cppTournamentSelection[double]* _cpp_obj

    def __cinit__(self, size: int, prob: float):
        _cpp_obj = new cppTournamentSelection[double](size, prob)
        print("cython: cppTournamentSelection allocated...")

    def __dealloc__(self) -> None:
        del self._cpp_obj
        print("cython: cppTournamentSelection deallocated...")
