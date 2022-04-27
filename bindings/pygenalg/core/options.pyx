# cython: language_level = 3
# distutils: language = c++

from .optionscpp cimport Options as cppOptions

cdef class Options:
    cdef cppOptions* _objcpp

    def __cinit__(self, population_capacity: int, p_mutation: float, seed: int=None) -> None:
        if seed:
            self._objcpp = new cppOptions(population_capacity, p_mutation, seed)
        else:
            self._objcpp = new cppOptions(population_capacity, p_mutation)

    def __dealloc__(self) -> None:
        del self._objcpp

    @property
    def population_capacity(self) -> int:
        return self._objcpp.population_capacity

    @property
    def p_mutation(self) -> float:
        return self._objcpp.p_mutation

    @property
    def seed(self) -> int:
        return self._objcpp.seed
