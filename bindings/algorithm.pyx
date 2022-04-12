# cython: language_level = 3
# distutils: language = c++

from typing import Optional

from libcpp cimport bool
from libcpp.vector cimport vector
from libcpp.utility cimport pair

from cython.operator cimport dereference as deref

from algorithm_cpp cimport GeneticAlgorithm as cppGeneticAlgorithm
from individual_cpp cimport BinaryIndividual as cppBinaryIndividual
from population_cpp cimport Population as cppPopulation

from options_cpp cimport Options as cppOptions

from selection_cpp cimport TournamentSelection as cppTournamentSelection
from crossover_cpp cimport MultiPointCrossover as cppMultiPointCrossover
from mutation_cpp cimport InversionMutation as cppInversionMutation

from .population import Population
from .individual import BinaryIndividual

cdef class GeneticAlgorithm:
    cdef cppGeneticAlgorithm[cppBinaryIndividual, double]* cpp_ga

    cdef cppTournamentSelection[cppBinaryIndividual, double]* cpp_selection
    cdef cppMultiPointCrossover[cppBinaryIndividual]* cpp_crossover
    cdef cppInversionMutation[cppBinaryIndividual]* cpp_mutation
    cdef cppOptions* cpp_options

    def __cinit__(self, capacity, n_generations, p_mutation, seed: Optional[int]=None):
        """Create Genetic Algorithm interface.
        """

        if seed is not None:
            self.cpp_options = new cppOptions(capacity, n_generations, p_mutation, seed)
        else:
            self.cpp_options = new cppOptions(capacity, n_generations, p_mutation)

        self.cpp_selection = new cppTournamentSelection[cppBinaryIndividual, double](2, 0.5, True)
        self.cpp_crossover = new cppMultiPointCrossover[cppBinaryIndividual](2)
        self.cpp_mutation = new cppInversionMutation[cppBinaryIndividual]()

        self.cpp_ga = new cppGeneticAlgorithm[cppBinaryIndividual, double](
            self.cpp_selection,
            self.cpp_crossover,
            self.cpp_mutation,
            deref(self.cpp_options)
        )


    def update(self, population):
        """Run one sequence of the GA on the provided population and return the next.

        Arguments:
            population: The population to evolve from.
        """

        cdef cppPopulation[cppBinaryIndividual, double]* cpp_population
        cpp_population = new cppPopulation[cppBinaryIndividual, double](len(population))

        cdef cppBinaryIndividual* cpp_individual

        for individual in population:
            cpp_individual = new cppBinaryIndividual(individual[0])
            cpp_population.add(deref(cpp_individual), individual[1])

        cdef cppPopulation[cppBinaryIndividual, double] cpp_new_population
        cpp_new_population = self.cpp_ga.update(deref(cpp_population))

        new_population = Population(len(population))

        for i in range(cpp_new_population.size()):
            new_population.add(
                BinaryIndividual(cpp_new_population[i].first.get_genome()),
                cpp_new_population[i].second
            )

        return new_population


    def __dealloc__(self):
        """Destroy Genetic Algorithm interface.
        """

        del self.cpp_ga
        del self.cpp_mutation
        del self.cpp_crossover
        del self.cpp_selection
        del self.cpp_options
