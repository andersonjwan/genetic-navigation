"""Mobile robot simulation for Genetic Algorithm based Navigation."""

import random

from typing import List

from pygenalg.algorithm import GeneticAlgorithm
from pygenalg.core.options import Options
from pygenalg.individual import Individual
from pygenalg.operators.crossover import MultiPointCrossover
from pygenalg.operators.mutation import BitFlipMutation
from pygenalg.operators.selection import TournamentSelection
from pygenalg.population import Population

from plotter import Plotter
from environment import Environment
from robot import Robot
from simulator import Simulator


def construct(population: Population, environment: Environment) -> List[Robot]:
    """Create a Robot list from a Population.
    """

    robots = []
    for individual in population.individuals:
        robots.append(
            Robot(environment, "".join("1" if x else "0" for x in individual.genome))
        )

    return robots


def deconstruct(robots: List[Robot]) -> Population:
    """Create a population from a Robot list.
    """

    population = Population(len(robots))

    for i, robot in enumerate(robots):
        genome = [x == "1" for x in robot.chromosome]

        population.append(
            Individual(genome, robot.fitness)
        )

    return population


def fitness(genome) -> float:
    return -1000.0


if __name__ == "__main__":
    K_GENERATIONS = 25
    K_INDIVIDUALS = 16
    load_population = False     # Whether to load a saved solution
    population_fname = 'S1692676949_G1000_solutions.txt'

    options = Options(
        population_capacity=K_INDIVIDUALS,
        p_mutation=0.1
    )

    # genetic algorithm
    selection = TournamentSelection(size=4, prob=0.95)
    crossover = MultiPointCrossover(n_crossovers=100, gene_size=3)
    mutation = BitFlipMutation(p_inversion=0.5)

    ga = GeneticAlgorithm(
        selection, crossover, mutation, fitness, options
    )

    # simulation
    environment = Environment()
    simulator = Simulator(
        environment,
        disp_results=True,
        nthreads=16
    )

    # initialize population
    population = Population(options.population_capacity)

    if load_population:
        # Load an already trained population
        with open(population_fname) as f:
            lines = f.readlines()

        assert len(lines) >= K_INDIVIDUALS

        # Keep only K_INDIVIDUALS from the saved population
        for i in range(K_INDIVIDUALS):
            genome, g_fitness = lines[i].split(',')
            genome = [x == "1" for x in genome]
            population.append(Individual(genome, float(g_fitness)))
    else:
        # Initialize with a random population
        for i in range(options.population_capacity):
            genome = random.choices([0, 1], k=(2 ** 13) * 3)

            population.append(Individual(genome, fitness(genome)))

    robots = construct(population, environment)

    # simulation
    for i in range(K_GENERATIONS):
        print(f"GENERATION {i:000d}")

        simulator.set_population(robots)
        simulator.set_population(simulator.simulate())

        population = deconstruct(robots)
        population = ga.update(population)

        for i, individual in enumerate(population.individuals):
            individual.fitness = simulator.robots[i].fitness

        robots = construct(population, environment)

    # results statistics
    plot = Plotter(ga)
    plot.fitness(show=False, save=True)

    simulator.display_env(f"img/S{ga.seed}_G{K_GENERATIONS}_animation.gif", show=False, save=True)

    # save last population
    with open(f"S{ga.seed}_G{K_GENERATIONS}_solutions.txt", "w") as outfile:
        for solution in simulator.robots:
            outfile.write(f"{solution.chromosome},{solution.fitness}\n")
