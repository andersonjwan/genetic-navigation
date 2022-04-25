# cython: language_level = 3
# distutils: language = c++

from cython.operator cimport dereference

from libcpp cimport bool
from libcpp.vector cimport vector

from .algorithmcpp cimport GeneticAlgorithm as cppGeneticAlgorithm

from .core.fitnesscpp cimport FitnessFunction as cppFitnessFunction
from .core.optionscpp cimport Options as cppOptions

from .operators.crossovercpp cimport CrossoverOperator as cppCrossoverOperator
from .operators.mutationcpp cimport MutationOperator as cppMutationOperator
from .operators.selectioncpp cimport SelectionOperator as cppSelectionOperator

# Forward declarations for polymorphic behavior
cdef class SelectionOperator:
    cdef cppSelectionOperator[double]* _objcpp

cdef class CrossoverOperator:
    cdef cppCrossoverOperator[vector[bool]]* _objcpp

cdef class MutationOperator:
    cdef cppMutationOperator[vector[bool]]* _objcpp

cdef class FitnessFunction:
    cdef cppFitnessFunction[vector[bool], double]* _objcpp

cdef class Options:
    cdef cppOptions* _objcpp

cdef class GeneticAlgorithm:
    cdef cppGeneticAlgorithm[double, vector[bool], double]* cpp_obj

    def __cinit__(self, selection, crossover, mutation, fitness, options) -> None:
        self.cpp_obj = new cppGeneticAlgorithm[double, vector[bool], double](
            (<SelectionOperator>selection)._objcpp,
            (<CrossoverOperator>crossover)._objcpp,
            (<MutationOperator>mutation)._objcpp,
            (<FitnessFunction>fitness)._objcpp,
            dereference((<Options>options)._objcpp)
        )

        print("cython: cppGeneticAlgorithm allocated...")

    def __dealloc__(self) -> None:
        del self.cpp_obj
        print("cython: cppGeneticAlgorithm deallocated...")
