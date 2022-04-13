from libcpp.vector cimport vector
from libcpp.utility cimport pair

from individual_cpp cimport BinaryIndividual

cdef extern from "population.hpp" namespace "genalg":
    cdef cppclass Population[I, F]:
        Population()
        Population(size_t s)

        # methods
        void add(const BinaryIndividual& individual)
        void add(const BinaryIndividual& individual, double fitness)

        size_t size() const
        pair[BinaryIndividual, double]& operator[](int i)
