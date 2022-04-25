# cython: language_level = 3
# distutils: language = c++

from .optionscpp cimport Options as cppOptions

cdef class Options:
    cdef cppOptions* _objcpp

    def __cinit__(self, population_capacity: int, p_mutation: float) -> None:
        self._objcpp = new cppOptions(population_capacity, p_mutation)
        print("cython: cppOptions allocated...")

    def __dealloc__(self) -> None:
        del self._objcpp
        print("cython: cppOptions deallocated...")
