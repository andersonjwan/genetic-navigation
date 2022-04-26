# cython: language_level = 3
# distutils: language = c++

from typing import List

from cython.operator cimport dereference

from libcpp cimport bool
from libcpp.vector cimport vector

from .individualcpp cimport Individual as cppIndividual
from .populationcpp cimport Population as cppPopulation

from .individual import Individual as pyIndividual

cdef class Individual:
    cdef cppIndividual[vector[bool], double]* _objcpp

cdef class Population:
    cdef cppPopulation[cppIndividual[vector[bool], double]]* _objcpp

    _capacity: int
    _individuals: List[pyIndividual]

    def __cinit__(self, capacity: int) -> None:
        self._capacity = capacity
        self._individuals = []

        self._objcpp = new cppPopulation[cppIndividual[vector[bool], double]](capacity)

    def __dealloc__(self) -> None:
        del self._objcpp

    @property
    def capacity(self) -> int:
        return self._objcpp.capacity()

    @property
    def individuals(self) -> List[pyIndividual]:
        return self._individuals

    def append(self, individual: pyIndividual) -> None:
        assert(len(self._individuals) < self._capacity)

        self._objcpp.append(dereference((<Individual>individual)._objcpp))
        self._individuals.append(individual)

    def best(self) -> pyIndividual:
        return max(self._individuals, key=lambda x: x.fitness)

    def worst(self) -> pyIndividual:
        return min(self._individuals, key=lambda x: x.fitness)

    def __len__(self) -> int:
        return len(self._individuals)
