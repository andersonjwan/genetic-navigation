from libcpp cimport bool
from libcpp.vector cimport vector

cdef extern from "population/individual.hpp" namespace "genalg::population":
    cdef cppclass BinaryIndividual:
        BinaryIndividual(vector[bool] genome)
