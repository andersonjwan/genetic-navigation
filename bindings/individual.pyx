# cython: language_level = 3
# distutils: language = c++

from individual_cpp cimport BinaryIndividual as cppBinaryIndividual

cdef class BinaryIndividual:
    """A solution encoded as a string of 1's or 0's.
    """

    cdef cppBinaryIndividual* cpp_individual

    def __cinit__(self, genome):
        """Allocate a new BinaryIndividual (C++).
        """

        self.cpp_individual = new cppBinaryIndividual(genome)


    def fitness(self):
        """Compute the fitness of the individual.
        """

        return self.cpp_individual.fitness()


    @property
    def genome(self):
        return self.cpp_individual.get_genome()


    def __dealloc__(self):
        """Deallocate BinaryIndividual (C++).
        """

        del self.cpp_individual
