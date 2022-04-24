# cython: language_level = 3
# distutils: language = c++

from libcpp cimport bool
from libcpp.vector cimport vector

from .fitnesscpp cimport FitnessFunction as cppFitnessFunction

cdef class FitnessFunction:
    cdef cppFitnessFunction[vector[bool], double]* _objcpp

    def __cinit__(self) -> None:
        self._objcpp = new cppFitnessFunction[vector[bool], double]()
        print("cython: cppFitnessFunction allocated...")

    def __dealloc__(self) -> None:
        del self._objcpp
        print("cython: cppFitnessFunction deallocated...")
