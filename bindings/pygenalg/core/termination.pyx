# cython: language_level = 3
# distutils: language = c++

from libcpp cimport bool
from libcpp.vector cimport vector

from ..individualcpp cimport Individual as cppIndividual

from .terminationcpp cimport BestLimit as cppBestLimit
from .terminationcpp cimport GenerationLimit as cppGenerationLimit

cdef class GenerationLimit:
    cdef cppGenerationLimit[cppIndividual[vector[bool], double]]* _objcpp

    def __cinit__(self, limit: int) -> None:
        self._objcpp = new cppGenerationLimit[cppIndividual[vector[bool], double]](
            limit
        )

    def __dealloc__(self) -> None:
        del self._objcpp

cdef class BestLimit:
    cdef cppBestLimit[cppIndividual[vector[bool], double]]* _objcpp

    def __cinit__(self, limit: int) -> None:
        self._objcpp = new cppBestLimit[cppIndividual[vector[bool], double]](
            limit
        )

    def __dealloc__(self) -> None:
        del self._objcpp
