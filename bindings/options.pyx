# distutils: language = c++

from typing import Optional
from options_cpp cimport Options as cppOptions

cdef class Options:
    cdef cppOptions* cpp_options

    def __cinit__(
            self,
            capacity,
            n_generations,
            p_mutation,
            seed:
            Optional[int]=None
    ):
        """Create a new Options interface.

        Arguments:
            capacity: The number of individuals per population.
            n_generations: The number of generations to create.
            p_mutation: The probability of a mutation occuring in a given individual.
            seed: A selected seed for RNG engine.
        """

        if seed is not None:
            self.cpp_options = new cppOptions(
                capacity,
                n_generations,
                p_mutation,
                seed
            )
        else:
            self.cpp_options = new cppOptions(
                capacity,
                n_generations,
                p_mutation
            )


    @property
    def seed(self):
        return self.cpp_options.seed

    def __dealloc__(self):
        """Destroy previously allocated Options interface.
        """

        del self.cpp_options
