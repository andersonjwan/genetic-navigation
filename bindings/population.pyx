# cython: language_level = 3
# distutils: language = c++

from typing import Optional

from libcpp cimport bool
from libcpp.vector cimport vector
from libcpp.utility cimport pair

from cython.operator cimport dereference as deref

from individual_cpp cimport BinaryIndividual as cppBinaryIndividual
from population_cpp cimport Population as cppPopulation

cdef class Population:
    """A list of solutions (i.e., BinaryIndividual) with associated fitness (i.e., double).

    Attributes:
        cpp_population: An instance of a genalg::Population object.
    """

    cdef cppPopulation[cppBinaryIndividual, double]* cpp_population
    cdef size_t n

    def __cinit__(self, size_t capacity):
        """Allocate a new Population of BinaryIndividual's (C++).
        """

        self.cpp_population = new cppPopulation[cppBinaryIndividual, double](capacity)

    def add(self, individual, fitness: Optional[float]=None):
        """Add a new individual to the population.
        """

        # copy genome to C++ data structure
        cdef vector[bool] cpp_genome = individual.genome

        # create a new C++ BinaryIndividual
        # Note: It will be destroyed once the function exits by __dealloc__
        cdef cppBinaryIndividual* cpp_individual = new cppBinaryIndividual(cpp_genome)

        # add to population
        if fitness:
            self.cpp_population.add(deref(cpp_individual), fitness)
        else:
            self.cpp_population.add(deref(cpp_individual))


    def __len__(self):
        """Return the current number of individuals in the population.
        """

        return self.cpp_population.size()


    def __iter__(self):
        """Return an iterator to the object.
        """
        self.n = 0
        return self

    def __next__(self):
        """Return the next item in the object.
        """

        if self.n < self.__len__():
            self.n += 1
            return self.__getitem__(self.n - 1)
        else:
            raise StopIteration


    def __setitem__(self, index, value):
        """Set a particular fitness for an individual in the population.
        """

        if index >= self.__len__():
            raise IndexError("population index access out of range")

        cdef pair[cppBinaryIndividual, double]* solution = &deref(self.cpp_population)[index]
        solution.second = value

    def __getitem__(self, index):
        """Get a particular individual/fitness pair in the population.
        """

        if index >= self.__len__():
            raise IndexError("population index access out of range")

        # convert a solution and associated fitness
        cdef pair[cppBinaryIndividual, double]* solution = &deref(self.cpp_population)[index]

        return [
            solution.first.get_genome(),
            solution.second
        ]

    def __dealloc__(self):
        """Deallocate Population (C++).
        """

        del self.cpp_population
