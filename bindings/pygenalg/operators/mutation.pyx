# cython: language_level = 3
# distutils: language = c++

from libcpp cimport bool
from libcpp.vector cimport vector

from .mutationcpp cimport BitFlipMutation as cppBitFlipMutation

cdef class BitFlipMutation:
    cdef cppBitFlipMutation[vector[bool]]* _objcpp

    def __cinit__(self, p_inversion: float) -> None:
        self._objcpp = new cppBitFlipMutation[vector[bool]](p_inversion)

    def __dealloc__(self) -> None:
        del self._objcpp
