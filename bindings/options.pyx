# distutils: language = c++

from typing import Optional
from cpp_options cimport Options as cppOptions

cdef class Options:
    cdef cppOptions* cpp_options

    def __cinit__(
            self,
            population_size,
            n_generations,
            mutation_chance,
            seed:
            Optional[int]=None
    ):
        """Create a new Options interface.
        """

        if seed is not None:
            self.cpp_options = new cppOptions(
                population_size,
                n_generations,
                mutation_chance,
                seed
            )
        else:
            self.cpp_options = new cppOptions(
                population_size,
                n_generations,
                mutation_chance
            )


    @property
    def seed(self):
        return self.cpp_options.seed

    def __dealloc__(self):
        """Destroy previously allocated Options interface.
        """

        del self.cpp_options
