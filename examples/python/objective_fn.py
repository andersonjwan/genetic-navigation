from pygenalg.algorithm import GeneticAlgorithm
from pygenalg.options import Options
from pygenalg.population import Population
from pygenalg.individual import BinaryIndividual

import math
import random

def fraction(genome):
    """Convert genome (represented as a binary number) to an equivalent fraction.
    """

    sign = genome[0]

    maximum = 0
    value = 0

    for i, bit in list(enumerate(genome)):
        if i > 0:
            exp = (len(genome) - i) - 1

            value += (math.pow(2, exp) * bit)
            maximum += (math.pow(2, exp))

    value = (value / maximum) * 10.0

    return -value if sign else value

def fitness(genome):
    x = fraction(genome)
    return math.sin(x) - 0.2 * abs(x)

def evaluate(population):
    """Evaluate the fitness of each individual.
    """

    new_population = Population(len(population))
    for individual in population:
        new_population.add(
            BinaryIndividual(individual[0]),
            fitness(individual[0])
        )

    return new_population

if __name__ == "__main__":
    """Optimize the maximum value for sin(x) - 0.2 * abs(x) within
    the range [-10, 10].
    """

    options = Options(
        capacity=25,
        n_generations=500,
        p_mutation=0.01,
        tournament_size=2,
        p_fittest=0.85
    )

    ga = GeneticAlgorithm(options=options)

    # initialize a random population
    population = Population(options.capacity)

    for i in range(options.capacity):
        genome = random.choices([0, 1], k=20)
        population.add(BinaryIndividual(genome), fitness(genome))

    for i in range(options.n_generations):
        population = ga.update(population)

        # update the fitness of each individual based on an external
        # metric (e.g., an environmental input)
        population = evaluate(population)

        best = max(population, key=lambda x: x[1])
        print(f"GENERATION {i + 1:03d} BEST: ({round(fraction(best[0]), 3):.3f}, {round(best[1], 3):.3f})")
