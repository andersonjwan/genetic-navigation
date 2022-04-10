# distutils: language = c++

from cpp_individual cimport BinaryIndividual
from cpp_mutation cimport InversionMutation as cppInversionMutation

cdef class InversionMutation:
    cdef cppInversionMutation[BinaryIndividual]* cpp_mutation

    def __cinit__(self):
        """
        """

        self.cpp_mutation = new cppInversionMutation[BinaryIndividual]()

    def __dealloc__(self):
        """
        """

        del self.cpp_mutation

