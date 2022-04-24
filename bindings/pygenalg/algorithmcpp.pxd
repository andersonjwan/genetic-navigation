# cython: language_level = 3
# distutils: language = c++

from .core.fitnesscpp cimport FitnessFunction
from .core.optionscpp cimport Options

from .operators.crossovercpp cimport CrossoverOperator
from .operators.mutationcpp cimport MutationOperator
from .operators.selectioncpp cimport SelectionOperator

cdef extern from "algorithm.hpp" namespace "genalg":
    cdef cppclass GeneticAlgorithm[I, G, F]:
        GeneticAlgorithm(
            SelectionOperator[I]* selection,
            CrossoverOperator[G]* crossover,
            MutationOperator[G]* mutation,
            FitnessFunction[G, F]* fitness,
            Options options
        ) except +
