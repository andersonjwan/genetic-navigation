import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle, Circle
from matplotlib.animation import FuncAnimation, PillowWriter
import seaborn as sns
from multiprocessing import Pool

import config


class Simulator:
    def __init__(self, env, disp_results=False, nthreads=1):
        self.env = env                     # Environment class instance
        self.max_steps = config.max_steps  # The maximum number of steps for one episode
        self.v = config.v                  # Constant linear velocity
        self.robots = None                 # The population of robots (list of robot class instances)

        self._disp_results = disp_results  # Whether to display results during training
        self._nthreads = nthreads          # Number of threads for multiprocessing

    def set_population(self, robots):
        """Sets the current population of robots for the simulation.

        Inputs:
          - robots(list): The population of robots
        """
        self.robots = robots

    def simulate(self):
        with Pool(processes=self._nthreads) as pool:
            return pool.map(self.run_episode, self.robots)

    def run_episode(self, robot):
        """Runs one episode where the current population navigates in the environment.

        Inputs:
          - robot(Robot class): The robot for which to run the simulation
        """

        # for robot in self.robots:
        episode_reward = 0                                  # Initialize score
        self.store_state(robot)                             # Store robot's initial state (pose & obst detection)
        termination_reason = 'Time-out'                     # Initialize reason for robot's episode termination

        # Navigate until collision, reaching goal or max steps
        for i in range(self.max_steps):

            # 1. Get action from GA controller
            omega = robot.get_action()

            # 2. Take action and transition to the next state
            robot.step(self.v, omega)
            self.store_state(robot)                         # Store robot's state (pose & obst detection)

            # 3. Get reward + info
            reward, has_collided, goal_reached = self.env.get_reward(*robot.get_pose())
            episode_reward += reward                        # Update episode reward

            # If collision or goal reached, stop moving
            if has_collided or goal_reached:
                if goal_reached:
                    termination_reason = 'Goal reached!'
                else:
                    termination_reason = 'Collision'
                for j in range(i, self.max_steps):
                    self.store_state(robot)
                break

        robot.set_fitness(episode_reward)                   # Update fitness of individual

        if self._disp_results:
            print('> Individual: {:03d} | Chromosome: [{}..]'.format(self.robots.index(robot)+1, robot.chromosome[:100]), end=' ')
            print('| {} '.format(termination_reason + ' '*(13-len(termination_reason))), end=' ')
            print('| Fitness: {}'.format(robot.fitness))

        return robot

    def store_state(self, robot):
        """Stores the current robot state (pose & obstacle detection results).

        Inputs:
          - robot(Robot class): The robot for which to store the state
        """
        x, y, theta = robot.get_pose()         # Get robot's pose
        robot.q_history.append([x, y, theta])  # Store robot's pose

        # Store obstacle detection results
        obs_history = []
        for sensor_angle in robot.sensors:
            obs_history.append(self.env.obstacle_detection(x, y, theta, sensor_angle))
        robot.obs_detection_history.append(obs_history)

    def display_env(self, filename: str):
        """Displays the environment."""

        global ax
        sns.set_style("white")

        fig, ax = plt.subplots(figsize=(12, 9))
        ax.set_title('Robot Navigation')
        plt.axis('equal')

        # Walls
        ax.hlines(y=0, xmin=0, xmax=self.env.env_dimension, linewidth=10, color='k')
        ax.hlines(y=self.env.env_dimension, xmin=0, xmax=self.env.env_dimension, linewidth=10, color='k')
        ax.vlines(x=0, ymin=-self.env.wall_width, ymax=self.env.env_dimension+self.env.wall_width, linewidth=10, color='k')
        ax.vlines(x=self.env.env_dimension, ymin=-self.env.wall_width, ymax=self.env.env_dimension+self.env.wall_width, linewidth=10, color='k')

        # Obstacles
        for _, _, [x, y, dx, dy] in self.env.obstacles:
            ax.add_patch(Rectangle((x, y), dx, dy, color='k'))

        # Goal
        ax.add_patch(Circle((self.env.goal[0], self.env.goal[1]), self.env.goal_radius, color='r', alpha=0.3))

        # Robot
        for robot in self.robots:
            robot_ind = str(self.robots.index(robot))  # Robot index
            x_rob, y_rob, theta = robot.q_history[0]   # Initial robot position

            # Robot's sensors
            for i in range(len(config.sensors)):
                # Sensor ray
                dx, dy, c, obs_detected = self.env.obstacle_detection(x_rob, y_rob, theta, config.sensors[i])
                globals()['sensor%s' % i+robot_ind] = plt.Arrow(x=x_rob, y=y_rob, dx=dx, dy=dy, color=c, width=0)
                ax.add_patch(globals()['sensor%s' % i+robot_ind])

                # Circle on obstacle-ray intersection points
                globals()['sensor_tip%s' % i+robot_ind] = plt.plot([], [], 'r', marker='o')

            # Robot's heading indicator
            globals()['heading%s' % robot_ind] = plt.Arrow(x=x_rob,
                                                           y=y_rob,
                                                           dx=np.cos(theta)/2,
                                                           dy=np.sin(theta)/2,
                                                           color='k',
                                                           width=0.01,
                                                           linewidth=2)
            ax.add_patch(globals()['heading%s' % robot_ind])

            # Robot's base
            globals()['base%s' % robot_ind] = Circle((x_rob, y_rob), config.robot_radius, color='b')
            ax.add_patch(globals()['base%s' % robot_ind])

        # Run the animation
        ani = FuncAnimation(fig, self.animate, frames=self.max_steps, interval=config.dt*1000, repeat=False)
        plt.show()

        # Save animation as gif
        ani.save(filename, writer=PillowWriter(fps=1/config.dt))

    def animate(self, i):
        """Draws each frame of the animation."""

        for robot in self.robots:
            robot_ind = str(self.robots.index(robot))     # Robot index
            x_rob, y_rob, theta_rob = robot.q_history[i]  # Robot's pose at i-th time step

            # Robot's sensors
            for k in range(len(config.sensors)):
                ax.patches.remove(globals()['sensor%s' % k+robot_ind])
                dx, dy, c, obs_detected = robot.obs_detection_history[i][k]
                globals()['sensor%s' % k+robot_ind] = plt.Arrow(x=x_rob, y=y_rob, dx=dx, dy=dy, color=c, width=0)
                ax.add_patch(globals()['sensor%s' % k+robot_ind])

                if obs_detected:
                    globals()['sensor_tip%s' % k+robot_ind][0].set_data(dx + x_rob, dy + y_rob)
                else:
                    globals()['sensor_tip%s' % k+robot_ind][0].set_data([], [])

            # Robot's heading
            ax.patches.remove(globals()['heading%s' % robot_ind])
            globals()['heading%s' % robot_ind] = plt.Arrow(x=x_rob,
                                                           y=y_rob,
                                                           dx=np.cos(theta_rob)/2,
                                                           dy=np.sin(theta_rob)/2,
                                                           color='k',
                                                           width=0.1,
                                                           linewidth=1)
            ax.add_patch(globals()['heading%s' % robot_ind])

            # Robot's base
            ax.patches.remove(globals()['base%s' % robot_ind])
            globals()['base%s' % robot_ind] = Circle((x_rob, y_rob), config.robot_radius, color='b')
            ax.add_patch(globals()['base%s' % robot_ind])

        return
