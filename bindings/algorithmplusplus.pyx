# distutils: language = c++

from cython.operator cimport dereference as deref

from cpp_algorithm cimport GeneticAlgorithm as cppGeneticAlgorithm
from cpp_individual cimport BinaryIndividual

from cpp_options cimport Options as cppOptions

from cpp_selection cimport TournamentSelection as cppTournamentSelection
from cpp_crossover cimport MultiPointCrossover as cppMultiPointCrossover
from cpp_mutation cimport InversionMutation as cppInversionMutation

cdef class GeneticAlgorithm:
    cdef cppGeneticAlgorithm[BinaryIndividual, double]* cpp_ga

    cdef cppTournamentSelection[BinaryIndividual, double]* cpp_selection
    cdef cppMultiPointCrossover[BinaryIndividual]* cpp_crossover
    cdef cppInversionMutation[BinaryIndividual]* cpp_mutation
    cdef cppOptions* cpp_options;

    def __cinit__(self, capacity, n_generations, p_mutation, seed=None):
        """Create Genetic Algorithm interface.
        """

        self.cpp_options = new cppOptions(capacity, n_generations, p_mutation, seed)
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
