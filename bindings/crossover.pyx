# distutils: language = c++

from individual_cpp cimport BinaryIndividual
from crossover_cpp cimport MultiPointCrossover as cppMultiPointCrossover

cdef class MultiPointCrossover:
    cdef cppMultiPointCrossover[BinaryIndividual]* cpp_crossover

    def __cinit__(self, n_crossovers):
        """
        """

        self.cpp_crossover = new cppMultiPointCrossover[BinaryIndividual](
            n_crossovers=n_crossovers
        )

    def __dealloc__(self):
        """
        """

        del self.cpp_crossover