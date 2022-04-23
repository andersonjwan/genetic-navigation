# cython: language_level = 3
# distutils: language = c++

from .optionscpp cimport Options as cppOptions

cdef class Options:
    cdef cppOptions* cpp_obj

    def __cinit__(self, population_capacity: int, p_mutation: float) -> None:
        self.cpp_obj = new cppOptions(population_capacity, p_mutation)
        print("cython: cppOptions allocated...")

    def __dealloc__(self) -> None:
        del self.cpp_obj
        print("cython: cppOptions deallocated...")
