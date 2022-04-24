# cython: language_level = 3
# distutils: language = c++

from cython.operator cimport dereference as deref

from .algorithmcpp cimport GeneticAlgorithm as cppGeneticAlgorithm
from .core.optionscpp cimport Options as cppOptions

from .core.options import Options

# cdef class GeneticAlgorithm:
    # cdef cppGeneticAlgorithm[double, double, double]* cpp_obj

    # def __cinit__(self, options: Options):
    #     self.cpp_obj = new cppGeneticAlgorithm[double, double, double](
    #         NULL, NULL, NULL, NULL, deref(<cppOptions?>(options._cpp_obj))
    #     )

    #     print("cython: cppGeneticAlgorithm allocated...")

    # def __dealloc__(self) -> None:
    #     del self.cpp_obj
    #     print("cython: cppGeneticAlgorithm deallocated...")
