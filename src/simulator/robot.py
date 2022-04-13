import numpy as np

import config


class Robot:
    robot_radius = config.robot_radius                             # Robot's radius
    sensor_range = config.sensor_range                             # Sensor range
    sensors = config.sensors                                       # Sensor angles wrt robot heading angle [rad]
    dt = config.dt                                                 # Sample time [s]
    actions = config.actions                                       # Actions encoding (binary->angular velocity)
    num_actions = len(actions)                                     # Number of actions

    def __init__(self, env):
        self.env = env                                             # Environment class instance
        self.x_robot = None                                        # Robot's x-position
        self.y_robot = None                                        # Robot's y-position
        self.theta = None                                          # Robot's heading angle
        self.set_initial_pose()                                    # Set initial pose at random
        self.q_history = []                                        # Robot's pose history
        self.obs_detection_history = []                            # Robot's obstacle detection history
        self.fitness = None                                        # Robot's fitness

        self.chromosome = ''.join(str(i) for i in np.random.randint(2, size=2**9*3))  # ToDO Get it from GA

    def set_initial_pose(self):
        """Sets robot's initial pose at random within the workspace."""

        # Define lower and upper bounds on position and heading
        pos_min = config.wall_width + self.robot_radius
        pos_max = config.env_dimension - config.wall_width - self.robot_radius
        theta_min, theta_max = 0, 2*np.pi

        # Sample random, obstacle free positions within the workspace bounds
        is_obstacle_free = False
        while not is_obstacle_free:
            self.x_robot, self.y_robot = np.round_((pos_max - pos_min)*np.random.random_sample(size=2) + pos_min, decimals=1)
            if not self.env.is_collision(self.x_robot, self.y_robot):
                is_obstacle_free = True
        self.theta = np.round_((theta_max - theta_min)*np.random.random_sample() + theta_min, decimals=2)

    def step(self, v, omega):
        """Simulates robot motion over one time interval step and sets the new pose.

        Uses the unicycle model.

        Inputs:
          - v(float):     The desired linear velocity
          - omega(float): The desired angular velocity
        """
        self.x_robot = self.x_robot + v*np.cos(self.theta)*Robot.dt
        self.y_robot = self.y_robot + v*np.sin(self.theta)*Robot.dt
        self.theta = self.theta + omega*Robot.dt

    def get_pose(self):
        """Gets robot's current pose.

        Returns:
          - x_robot(float): Robot's current x-position
          - y_robot(float): Robot's current y-position
          - theta(float):   Robot's current heading angle
        """
        return self.x_robot, self.y_robot, self.theta

    def set_fitness(self, fitness):
        """Sets robot's fitness score.

        Inputs:
          - fitness(float): The individual's fitness
        """
        self.fitness = int(fitness)

    def get_action(self):
        """Get the next action by decoding the chromosome.

        Returns:
          - action(float):  The next action to take (angular velocity)
        """

        # Get extended sensor inputs as a binary string
        encoded_input = self.env.read_sensors(*self.get_pose()) + self.env.get_angle_area(*self.get_pose())
        encoded_input_string = ''.join(str(i) for i in encoded_input)

        # Find position in chromosome that represents the binary input (by converting binary to decimal)
        pos = int(encoded_input_string, 2)

        # Get the action in that position (as binary string)
        binary_action = self.chromosome[pos: pos + int(np.log2(self.num_actions))]

        # Decode binary action into angular velocity
        action = self.actions[binary_action]

        return action
