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

from environment import Env
from robot import Robot
from simulator import Simulator

def construct(population: Population, env: Env) -> List[Robot]:
    """Create a Robot list from a Population.
    """

    robots = []
    for individual in population.individuals:
        robots.append(
            Robot(env, "".join("1" if x else "0" for x in individual.genome))
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
    K_GENERATIONS = 5
    K_INDIVIDUALS = 10

    options = Options(
        population_capacity=K_INDIVIDUALS,
        p_mutation=0.1
    )

    # genetic algorithm
    selection = TournamentSelection(size=2, prob=0.85)
    crossover = MultiPointCrossover(n_crossovers=2)
    mutation = BitFlipMutation(p_inversion=0.5)

    ga = GeneticAlgorithm(
        selection, crossover, mutation, fitness, options
    )

    # simulation
    env = Env()
    sim = Simulator(env)


    # initialize population
    population = Population(options.population_capacity)

    for i in range(options.population_capacity):
        genome = random.choices([0, 1], k=(2 ** 9) * 3)

        population.append(
            Individual(genome, fitness(genome))
        )

    robots = construct(population, env)

    # simulation
    for i in range(K_GENERATIONS):
        sim.set_population(robots)
        sim.run_episode(disp_results=True)

        population = deconstruct(robots)
        population = ga.update(population)

        robots = construct(population, env)

    # results statistics
    sim.display_env()
