# cython: language_level = 3
# distutils: language = c++

from typing import Optional
from options_cpp cimport Options as cppOptions

cdef class Options:
    cdef cppOptions* cpp_options

    tournament_size: int
    p_fittest: float
    replacement: bool
    n_crossovers: int

    def __cinit__(
            self,
            population_capacity,
            p_mutation,
            tournament_size=2,
            p_fittest=0.5,
            replacement=True,
            n_crossovers=2,
            seed: Optional[int]=None
    ):
        """Create a new Options interface.

        Arguments:
            capacity: The number of individuals per population.
            n_generations: The number of generations to create.
            p_mutation: The probability of a mutation occuring in a given individual.
            seed: A selected seed for RNG engine.
        """

        self.tournament_size = tournament_size
        self.p_fittest = p_fittest
        self.replacement = replacement
        self.n_crossovers = n_crossovers

        if seed is not None:
            self.cpp_options = new cppOptions(
                population_capacity,
                p_mutation,
                seed
            )
        else:
            self.cpp_options = new cppOptions(
                population_capacity,
                p_mutation
            )

    @property
    def tournament_size(self):
        return self.tournament_size

    @property
    def p_fittest(self):
        return self.p_fittest

    @property
    def replacement(self):
        return self.replacement

    @property
    def n_crossovers(self):
        return self.n_crossovers

    @property
    def population_capacity(self):
        return self.cpp_options.population_capacity

    @property
    def p_mutation(self):
        return self.cpp_options.p_mutation

    @property
    def seed(self):
        return self.cpp_options.seed

    def __dealloc__(self):
        """Destroy previously allocated Options interface.
        """

        del self.cpp_options
