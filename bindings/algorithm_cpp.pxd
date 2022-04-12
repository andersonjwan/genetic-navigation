from individual_cpp cimport BinaryIndividual

from selection_cpp cimport SelectionOperator, TournamentSelection
from crossover_cpp cimport CrossoverOperator, MultiPointCrossover
from mutation_cpp cimport MutationOperator, InversionMutation

from options_cpp cimport Options
from population_cpp cimport Population

cdef extern from "algorithm.hpp" namespace "genalg":
    cdef cppclass GeneticAlgorithm[I, F]:
        GeneticAlgorithm(
            TournamentSelection[BinaryIndividual, double]* s,
            MultiPointCrossover[BinaryIndividual]* c,
            InversionMutation[BinaryIndividual]* m,
            Options o
        ) except +

        Population[BinaryIndividual, double] update(const Population[BinaryIndividual, double]& population)
