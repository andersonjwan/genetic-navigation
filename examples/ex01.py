import math
import numpy as np
import random

from typing import List, Union

from pygenalg.algorithm import GeneticAlgorithm

from pygenalg.core.options import Options

from pygenalg.operators.selection import TournamentSelection
from pygenalg.operators.crossover import MultiPointCrossover
from pygenalg.operators.mutation import BitFlipMutation

from pygenalg.population import Population
from pygenalg.individual import Individual

def decimal(genome: List[bool]) -> float:
    maximum = sum(v << i for i, v in enumerate(reversed([1 for i in range(len(genome))])))
    value = sum(v << i for i, v in enumerate(reversed(np.array(genome).astype(int).tolist())))

    return (value / maximum) * 10

def evaluate(genome: List[bool]) -> float:
    x = decimal(genome)
    return math.sin(x) - 0.2 * abs(x)

if __name__ == "__main__":
    options = Options(
        population_capacity=25,
        p_mutation=0.1
    )

    selection = TournamentSelection(size=2, prob=0.85)
    crossover = MultiPointCrossover(n_crossovers=2)
    mutation = BitFlipMutation(p_inversion=0.5)

    ga = GeneticAlgorithm(selection, crossover, mutation, evaluate, options)

    population = Population(options.population_capacity)
    for i in range(options.population_capacity):
        genome = random.choices([True, False], k=25)

        population.append(
            Individual(
                genome,
                evaluate(genome)
            )
        )

    ga.initialize(population)

    for i in range(100):
        population = ga.update(population)

    print(f"GENERATION 100 BEST: {ga.generations[-1].best().fitness}")
