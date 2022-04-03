"""Mobile robot simulation for Genetic Algorithm based Navigation."""

from robot import Robot
from simulator import Simulator
from environment import Env


if __name__ == '__main__':
    num_robots = 6                                    # Total number of robots (population size)
    env = Env()                                       # Define the environment
    robots = [Robot(env) for _ in range(num_robots)]  # Define the robots
    sim = Simulator(robots, env)                      # Define the simulator

    sim.run_episode()                                 # Run one navigation episode
    sim.display_env()                                 # Display the environment
