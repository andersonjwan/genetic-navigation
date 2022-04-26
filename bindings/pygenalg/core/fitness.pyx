# cython: language_level = 3
# distutils: language = c++

from libcpp cimport bool
from libcpp.vector cimport vector

from .fitnesscpp cimport ZeroFitnessFunction as cppZeroFitnessFunction

cdef class ZeroFitnessFunction:
    cdef cppZeroFitnessFunction[vector[bool], double]* _objcpp

    def __cinit__(self) -> None:
        self._objcpp = new cppZeroFitnessFunction[vector[bool], double]()

    def __dealloc__(self) -> None:
        del self._objcpp
