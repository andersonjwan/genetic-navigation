# distutils: language = c++

from individual_cpp cimport BinaryIndividual as cppBinaryIndividual

cdef class BinaryIndividual:
    cdef cppBinaryIndividual* cpp_individual

    def __cinit__(self, genome):
        """
        """

        self.cpp_individual = new cppBinaryIndividual(genome)

    def __dealloc__(self):
        """
        """

        del self.cpp_individual
