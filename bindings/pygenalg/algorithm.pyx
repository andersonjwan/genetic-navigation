# cython: language_level = 3
# distutils: language = c++

from typing import List

from cython.operator cimport dereference

from libcpp cimport bool
from libcpp.vector cimport vector

from .algorithmcpp cimport GeneticAlgorithm as cppGeneticAlgorithm

from .core.fitnesscpp cimport FitnessFunction as cppFitnessFunction
from .core.optionscpp cimport Options as cppOptions

from .individualcpp cimport Individual as cppIndividual

from .operators.crossovercpp cimport CrossoverOperator as cppCrossoverOperator
from .operators.mutationcpp cimport MutationOperator as cppMutationOperator
from .operators.selectioncpp cimport SelectionOperator as cppSelectionOperator

from .populationcpp cimport Population as cppPopulation

from .individual import Individual as pyIndividual
from .population import Population as pyPopulation

# Forward declarations for polymorphic behavior
cdef class SelectionOperator:
    cdef cppSelectionOperator[cppIndividual[vector[bool], double]]* _objcpp

cdef class CrossoverOperator:
    cdef cppCrossoverOperator[vector[bool]]* _objcpp

cdef class MutationOperator:
    cdef cppMutationOperator[vector[bool]]* _objcpp

cdef class FitnessFunction:
    cdef cppFitnessFunction[vector[bool], double]* _objcpp

cdef class Options:
    cdef cppOptions* _objcpp

cdef class Population:
    cdef cppPopulation[cppIndividual[vector[bool], double]]* _objcpp

cdef class GeneticAlgorithm:
    cdef cppGeneticAlgorithm[cppIndividual[vector[bool], double], vector[bool], double]* _objcpp
    _generations: List[pyPopulation]=[]

    def __cinit__(self, selection, crossover, mutation, fitness, options) -> None:
        self._objcpp = new cppGeneticAlgorithm[
            cppIndividual[vector[bool], double],
            vector[bool],
            double] (
                (<SelectionOperator>selection)._objcpp,
                (<CrossoverOperator>crossover)._objcpp,
                (<MutationOperator>mutation)._objcpp,
                (<FitnessFunction>fitness)._objcpp,
                dereference((<Options>options)._objcpp)
            )

        print("cython: cppGeneticAlgorithm allocated...")

    def __dealloc__(self) -> None:
        del self._objcpp
        print("cython: cppGeneticAlgorithm deallocated...")

    @property
    def seed(self) -> int:
        return self._objcpp.seed()

    @property
    def generations(self) -> List[pyPopulation]:
        return self._generations

    def initialize(self, population: pyPopulation) -> None:
        self._objcpp.initialize(dereference((<Population>population)._objcpp))
        self._generations.append(population)

    def update(self, population: pyPopulation) -> pyPopulation:
        cdef cppPopulation[cppIndividual[vector[bool], double]] new_populationcpp
        new_populationcpp = self._objcpp.update(dereference((<Population>population)._objcpp))

        cdef vector[cppIndividual[vector[bool], double]] new_individualscpp
        new_individualscpp = new_populationcpp.individuals()

        new_population = pyPopulation(new_populationcpp.capacity())

        for i in range(new_populationcpp.capacity()):
            new_population.append(
                pyIndividual(
                    new_individualscpp[i].genome(),
                    new_individualscpp[i].fitness()
                )
            )

        self._generations.append(new_population)
        return new_population

    def next(self) -> pyPopulation:
        cdef cppPopulation[cppIndividual[vector[bool], double]] new_populationcpp
        new_populationcpp = self._objcpp.update(dereference((<Population>self._generations[-1])._objcpp))

        cdef vector[cppIndividual[vector[bool], double]] new_individualscpp
        new_individualscpp = new_populationcpp.individuals()

        new_population = pyPopulation(new_populationcpp.capacity())

        for i in range(new_populationcpp.capacity()):
            new_population.append(
                pyIndividual(
                    new_individualscpp[i].genome(),
                    new_individualscpp[i].fitness()
                )
            )

        self._generations.append(new_population)
        return new_population

    def __len__(self) -> int:
        return len(self._generations)
