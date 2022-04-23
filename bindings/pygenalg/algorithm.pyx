# cython: language_level = 3
# distutils: language = c++

from .algorithmcpp cimport GeneticAlgorithm as cppGeneticAlgorithm

cdef class GeneticAlgorithm:
    def __cinit__(self):
        """GeneticAlgorithm constructor.
        """

        print("GeneticAlgorithm initialized...")
