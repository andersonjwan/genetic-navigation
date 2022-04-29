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
    K_GENERATIONS = 20
    K_INDIVIDUALS = 16
    load_population = False     # Whether to load a saved solution
    population_fname = 'S1692676949_G1000_solutions.txt'

    options = Options(
        population_capacity=K_INDIVIDUALS,
        p_mutation=0.15
    )

    # genetic algorithm
    selection = TournamentSelection(size=4, prob=0.85)
    crossover = MultiPointCrossover(n_crossovers=1000, gene_size=3)
    mutation = BitFlipMutation(p_inversion=0.5)

    ga = GeneticAlgorithm(
        selection, crossover, mutation, fitness, options
    )

    environment = Environment()
    simulator = Simulator(
        environment,
        nthreads=16
    )

    # INITIALIZATION
    population = Population(options.population_capacity)

    if load_population:
        with open(population_fname, "r") as infile:
            lines = infile.readlines()
            assert len(lines) >= options.population_capacity

            for solution in lines:
                genome, fitness = solution.split(',')
                population.append(Individual([x == "1" for x in genome], float(fitness)))
    else:
        for i in range(options.population_capacity):
            genome = random.choices([0, 1], k=(2 ** 13) * 3)
            population.append(Individual(genome, fitness(genome)))

    # SIMULATION
    for i in range(K_GENERATIONS + 1):
        print(f"GENERATION {(i):04d}")

        simulator.robots = construct(population, environment)
        simulator.simulate(debug=True)

        population = deconstruct(simulator.robots)
        for j, individual in enumerate(population.individuals):
            individual.fitness = simulator.robots[j].fitness

        population = ga.update(population)
        for j, individual in enumerate(population.individuals):
            individual.fitness = simulator.robots[j].fitness

        if i % (int(K_GENERATIONS / 4)) == 0:
            simulator.display_env(
                filename=f"img/S{ga.seed}_G{i:04d}_animation.gif",
                title=f"Genetic Navigation at Generation {i}",
                show=False,
                save=True
            )

    # results statistics
    plot = Plotter(ga)
    plot.fitness(show=False, save=True)
    plot.average(show=False, save=True)

    # save last population
    with open(f"S{ga.seed}_G{K_GENERATIONS}_solutions.txt", "w") as outfile:
        for solution in simulator.robots:
            outfile.write(f"{solution.chromosome},{solution.fitness}\n")
