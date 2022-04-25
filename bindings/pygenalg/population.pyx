# cython: language_level = 3
# distutils: language = c++

from .populationcpp cimport Population as cppPopulation

cdef class Population:
    cdef cppPopulation[double]* _objcpp

    def __cinit__(self, capacity: int) -> None:
        self._objcpp = new cppPopulation[double](capacity)
        print("cython: cppPopulation allocated...")

    def __dealloc__(self) -> None:
        del self._objcpp
        print("cython: cppPopulation deallocated...")
