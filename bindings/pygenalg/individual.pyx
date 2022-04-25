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
        print("cython: cppIndividual allocated...")

    def __dealloc__(self) -> None:
        del self._objcpp
        print("cython: cppIndividual deallocated...")

    @property
    def genome(self) -> List[Union[True, False]]:
        return self._objcpp.genome()

    @property
    def fitness(self) -> float:
        return self._objcpp.fitness()

    @fitness.setter
    def fitness(self, fitness: float) -> None:
        self._objcpp.fitness(fitness)

    def __lt__(self, other):
        return self.fitness < other.fitness

    def __eq__(self, other):
        return self.genome == other.genome and self.fitness == other.fitness
