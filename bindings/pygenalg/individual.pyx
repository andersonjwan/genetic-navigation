# cython: language_level = 3
# distutils: language = c++

from typing import List, Union

from libcpp cimport bool
from libcpp.vector cimport vector

from .individualcpp cimport Individual as cppIndividual

cdef class Individual:
    cdef cppIndividual[vector[bool], double]* _objcpp
    fitness: float

    def __cinit__(self, genome, fitness) -> None:
        self._objcpp = new cppIndividual[vector[bool], double](genome, fitness)

    def __dealloc__(self) -> None:
        del self._objcpp

    @property
    def genome(self) -> List[Union[True, False]]:
        return self._objcpp.genome()

    @property
    def fitness(self) -> float:
        return self._objcpp.fitness()

    @fitness.setter
    def fitness(self, fitness: float) -> None:
        self._objcpp.fitness(fitness)
