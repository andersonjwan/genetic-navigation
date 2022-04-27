# cython: language_level = 3
# distutils: language = c++

from libcpp cimport bool
from libcpp.vector cimport vector

from .crossovercpp cimport MultiPointCrossover as cppMultiPointCrossover
from .crossovercpp cimport SinglePointCrossover as cppSinglePointCrossover

cdef class MultiPointCrossover:
    cdef cppMultiPointCrossover[vector[bool]]* _objcpp

    def __cinit__(self, n_crossovers: int, gene_size: int=1) -> None:
        self._objcpp = new cppMultiPointCrossover[vector[bool]](
            n_crossovers,
            gene_size
        )

    def __dealloc__(self) -> None:
        del self._objcpp

cdef class SinglePointCrossover:
    cdef cppSinglePointCrossover[vector[bool]]* _objcpp

    def __cinit__(self, gene_size: int=1) -> None:
        self._objcpp = new cppSinglePointCrossover[vector[bool]](gene_size)

    def __dealloc__(self) -> None:
        del self._objcpp
