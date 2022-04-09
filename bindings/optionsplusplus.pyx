# distutils: language = c++

from typing import Optional
from cppoptions cimport Options

cdef class PyOptions:
    cdef Options* cpp_options

    def __cinit__(
            self,
            population_size,
            n_generations,
            mutation_chance,
            seed:
            Optional[int]=None
    ):
        """Dynamically instantiate a new Python GA options interface.

        Arguments:
            population_size: The number of individuals per generation
            n_generations: The total number of generations
            mutation_chance: The probability of an individual mutating
            seed: The seed to provide to the random number generator engine
        """

        if seed is not None:
            self.cpp_options = new Options(
                population_size,
                n_generations,
                mutation_chance,
                seed
            )
        else:
            self.cpp_options = new Options(
                population_size,
                n_generations,
                mutation_chance
            )


    @property
    def seed(self):
        return self.cpp_options.seed

    def __dealloc__(self):
        """Deallocate dynamically instantiated options interface.
        """

        del self.cpp_options
