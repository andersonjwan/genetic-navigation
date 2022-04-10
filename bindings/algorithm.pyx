# distutils: language = c++

from typing import Optional

from cython.operator cimport dereference as deref

from algorithm_cpp cimport GeneticAlgorithm as cppGeneticAlgorithm
from individual_cpp cimport BinaryIndividual

from options_cpp cimport Options as cppOptions

from selection_cpp cimport TournamentSelection as cppTournamentSelection
from crossover_cpp cimport MultiPointCrossover as cppMultiPointCrossover
from mutation_cpp cimport InversionMutation as cppInversionMutation

cdef class GeneticAlgorithm:
    cdef cppGeneticAlgorithm[BinaryIndividual, double]* cpp_ga

    cdef cppTournamentSelection[BinaryIndividual, double]* cpp_selection
    cdef cppMultiPointCrossover[BinaryIndividual]* cpp_crossover
    cdef cppInversionMutation[BinaryIndividual]* cpp_mutation
    cdef cppOptions* cpp_options;

    def __cinit__(self, capacity, n_generations, p_mutation, seed: Optional[int]=None):
        """Create Genetic Algorithm interface.
        """

        if seed is not None:
            self.cpp_options = new cppOptions(capacity, n_generations, p_mutation, seed)
        else:
            self.cpp_options = new cppOptions(capacity, n_generations, p_mutation)

        print(deref(self.cpp_options).seed)

        self.cpp_selection = new cppTournamentSelection[BinaryIndividual, double](2, 0.5, True)
        self.cpp_crossover = new cppMultiPointCrossover[BinaryIndividual](2)
        self.cpp_mutation = new cppInversionMutation[BinaryIndividual]()

        self.cpp_ga = new cppGeneticAlgorithm[BinaryIndividual, double](
            self.cpp_selection,
            self.cpp_crossover,
            self.cpp_mutation,
            deref(self.cpp_options)
        )


    # def update(self, population):
    #     """
    #     """

    #     return self.cpp_ga.update(population)


    def __dealloc__(self):
        """Destroy Genetic Algorithm interface.
        """

        del self.cpp_ga
        del self.cpp_mutation
        del self.cpp_crossover
        del self.cpp_selection
        del self.cpp_options
