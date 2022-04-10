# distutils: language = c++

from population_cpp cimport Population as cppPopulation

cdef class Population:
    cdef cppPopulation[double, double]* cpp_population

    def __cinit__(self, capacity):
        """
        """

        self.cpp_population = new cppPopulation[double, double](capacity)

    def __dealloc__(self):
        """
        """

        del self.cpp_population
