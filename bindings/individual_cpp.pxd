from libcpp cimport bool
from libcpp.vector cimport vector

cdef extern from "population/individual.hpp" namespace "genalg::population":
    cdef cppclass BinaryIndividual:
        BinaryIndividual(vector[bool] genome)

        # methods
        vector[bool] get_genome() const
        double fitness() const
