"""Mobile robot simulation for Genetic Algorithm based Navigation."""

import math
import random

from typing import List

from pygenalg.algorithm import GeneticAlgorithm
from pygenalg.individual import BinaryIndividual
from pygenalg.options import Options
from pygenalg.population import Population

from environment import Env
from plotter import plot_fitness
from robot import Robot
from simulator import Simulator


def transfer(robots: List[Robot]) -> Population:
    """Transfer the genome/fitness to the GA Population interface.
    """

    transplant = Population(len(population))

    for i, robot in list(enumerate(robots)):
        genome = [bit == "1" for bit in robot.chromosome]

        transplant.add(
            BinaryIndividual(genome),
            robot.fitness
        )

    return transplant

def build_robots(population: Population, env: Env) -> List[Robot]:
    """Transfer the genome/fitness to the GA Population interface.
    """

    robots = []
    for individual in population:
        chromosome = ""
        for bit in individual[0]:
            chromosome += str(1) if bit else str(0)

        robots.append(
            Robot(env, chromosome)
        )

    return robots

if __name__ == '__main__':
    # --------------------------------------------------------------------------
    # Parameters
    # --------------------------------------------------------------------------

    disp_results = True                                   # Display results during training

    options = Options(
        capacity=25,      # Total number of robots (population size)
        n_generations=25, # Total number of generations
        p_mutation=0.01,
        p_fittest=0.85,
        n_crossovers=100
    )

    ga = GeneticAlgorithm(options)
    population = Population(options.capacity)

    env = Env()                                           # Define the environment
    sim = Simulator(env)                                  # Define the simulator
    population_fitness_history = []                       # Stores the fitness for each individual in every generation

    # initial population
    robots = []
    for individual in range(options.capacity):
        genome = random.choices([0, 1], k=((2 ** 9) * 3))
        population.add(BinaryIndividual(genome))

        chromosome = ""
        for bit in genome:
            chromosome += str(bit)

        robots.append(Robot(env, chromosome))


    # --------------------------------------------------------------------------
    # Training
    # --------------------------------------------------------------------------

    # population_fitness_history.append([r.fitness for r in robots])  # Save current population's fitness for plotting
    # episode: one iteration
    # print('Generation: {}'.format(i + 1))
    # print('='*30)

    # print('Maximum fitness: {}'.format(max(population_fitness_history[-1])))
    # print('='*30)

    for i in range(options.n_generations):
        print(f"Generation: {i:02d}")

        sim.set_population(robots)  # Set the current population of robots in the simulator
        sim.run_episode(disp_results) # Run one navigation episode

        population = transfer(robots)
        population = ga.update(population) # ga.update(population: Population) -> Population

        robots = build_robots(population, env)


    # --------------------------------------------------------------------------
    # Display animation and results
    # --------------------------------------------------------------------------
    sim.display_env()                                     # Display the environment
    plot_fitness(population_fitness_history)              # Plot fitness per generation
