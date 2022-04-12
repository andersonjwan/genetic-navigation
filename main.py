"""Mobile robot simulation for Genetic Algorithm based Navigation."""

from robot import Robot
from simulator import Simulator
from environment import Env
from plotter import plot_fitness


if __name__ == '__main__':
    # --------------------------------------------------------------------------
    # Parameters
    # --------------------------------------------------------------------------
    num_generations = 10                                  # Total number of generations
    num_robots = 6                                        # Total number of robots (population size)

    # --------------------------------------------------------------------------
    # Training
    # --------------------------------------------------------------------------
    env = Env()                                           # Define the environment
    sim = Simulator(env)                                  # Define the simulator
    population_fitness_history = []                       # Stores the fitness for each individual in every generation

    for i in range(num_generations):
        print('Generation: {}'.format(i + 1))
        print('='*30)

        robots = [Robot(env) for _ in range(num_robots)]  # Define the robots/individuals of current generation
        sim.set_population(robots)                        # Set the current population of robots in the simulator
        sim.run_episode()                                 # Run one navigation episode

        population_fitness_history.append([r.fitness for r in robots])  # Save current population's fitness for plotting

        print('Maximum fitness: {}'.format(max(population_fitness_history[-1])))
        print('='*30)

    # --------------------------------------------------------------------------
    # Display animation and results
    # --------------------------------------------------------------------------
    sim.display_env()                                     # Display the environment
    plot_fitness(population_fitness_history)              # Plot fitness per generation
