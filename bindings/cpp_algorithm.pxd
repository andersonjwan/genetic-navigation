from cpp_individual cimport BinaryIndividual

from cpp_selection cimport SelectionOperator, TournamentSelection
from cpp_crossover cimport CrossoverOperator, MultiPointCrossover
from cpp_mutation cimport MutationOperator, InversionMutation

from cpp_options cimport Options
from cpp_population cimport Population

cdef extern from "algorithm.hpp" namespace "genalg":
    cdef cppclass GeneticAlgorithm[I, F]:
        GeneticAlgorithm(
            TournamentSelection[BinaryIndividual, double]* s,
            MultiPointCrossover[BinaryIndividual]* c,
            InversionMutation[BinaryIndividual]* m,
            Options o
        ) except +

        Population[BinaryIndividual, double] update(const Population[BinaryIndividual, double]& population)
