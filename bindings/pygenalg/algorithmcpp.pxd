# cython: language_level = 3
# distutils: language = c++

from .core.fitnesscpp cimport FitnessFunction
from .core.optionscpp cimport Options
from .core.terminationcpp cimport TerminationCondition

from .operators.crossovercpp cimport CrossoverOperator
from .operators.mutationcpp cimport MutationOperator
from .operators.selectioncpp cimport SelectionOperator

from .populationcpp cimport Population

cdef extern from "algorithm.hpp" namespace "genalg":
    cdef cppclass GeneticAlgorithm[I, G, F]:
        GeneticAlgorithm(
            SelectionOperator[I]* selection,
            CrossoverOperator[G]* crossover,
            MutationOperator[G]* mutation,
            FitnessFunction[G, F]* fitness,
            Options options
        ) except +

        # accessors
        size_t seed() const

        void initialize(const Population[I]& population)
        Population[I] update(const Population[I]& population)
