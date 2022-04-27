import numpy as np

import config


class Environment:
    def __init__(self):
        self.goal = config.goal                                           # Goal position
        self.goal_radius = config.goal_radius                             # Radius of goal circle
        self.env_dimension = config.env_dimension                         # Workspace dimensions
        self.wall_width = config.wall_width                               # Workspace wall half-width
        self.obstacles = []                                               # List of all obstacles
        self.goal_reward = config.goal_reward                             # Reward for reaching the goal
        self.collision_reward = config.collision_reward                   # Reward for collision
        self.choose_env(config.env_id)                                    # Choose an environment layout

    def choose_env(self, env_id):
        """Sets the layout of obstacles for the selected environment.

        Inputs:
          - env_id(int):  The predefined environment layout id
        """
        assert env_id in range(4)

        if env_id == 0:  # No obstacles
            return

        elif env_id == 1:
            self.obstacles = [self.define_obstacle(x=10, y=7, dx=5, dy=0.5),
                              self.define_obstacle(x=0, y=4, dx=6, dy=0.5),
                              self.define_obstacle(x=6, y=4, dx=0.5, dy=2),
                              self.define_obstacle(x=6, y=10, dx=0.5, dy=5),
                              self.define_obstacle(x=11, y=3, dx=1, dy=1.5),
                              self.define_obstacle(x=1, y=7.5, dx=1, dy=1)]
        elif env_id == 2:
            self.obstacles = [self.define_obstacle(x=2, y=3, dx=1, dy=1),
                              self.define_obstacle(x=8, y=1, dx=2, dy=1),
                              self.define_obstacle(x=3, y=4, dx=5, dy=1),
                              self.define_obstacle(x=6, y=6, dx=1, dy=1),
                              self.define_obstacle(x=0, y=8, dx=4, dy=1),
                              self.define_obstacle(x=6, y=13, dx=1, dy=2),
                              self.define_obstacle(x=6, y=9, dx=1, dy=1)]
        elif env_id == 3:
            self.obstacles = [self.define_obstacle(x=2, y=0, dx=0.5, dy=4),
                              self.define_obstacle(x=2, y=6, dx=0.5, dy=3),
                              self.define_obstacle(x=0, y=9, dx=6, dy=0.5),
                              self.define_obstacle(x=4.5, y=3, dx=2, dy=0.5),
                              self.define_obstacle(x=5, y=3.5, dx=0.5, dy=5.5),
                              self.define_obstacle(x=1, y=12.5, dx=1, dy=1),
                              self.define_obstacle(x=11, y=0, dx=0.5, dy=5.5),
                              self.define_obstacle(x=8, y=5, dx=3, dy=0.5),
                              self.define_obstacle(x=8, y=5, dx=0.5, dy=6),
                              self.define_obstacle(x=4, y=11, dx=4.5, dy=0.5),
                              self.define_obstacle(x=10, y=9.5, dx=1, dy=1),
                              self.define_obstacle(x=10, y=12, dx=1, dy=1),
                              self.define_obstacle(x=13, y=9.5, dx=1, dy=1),
                              self.define_obstacle(x=13, y=12, dx=1, dy=1),
                              self.define_obstacle(x=6, y=12, dx=1, dy=1),
                              self.define_obstacle(x=9, y=1, dx=1, dy=1)]

    @staticmethod
    def define_obstacle(x, y, dx, dy):
        """Defines a rectangular obstacle as a convex polygon with half-space representation (AX<=B).

        Inputs:
          - x(float):      x-position of bottom-left corner of rectangular
          - y(float):      y-position of bottom-left corner of rectangular
          - dx(float):     Width of rectangular
          - dy(float):     Height of rectangular
        Returns:
          - A(np.ndarray): Coefficient matrix of obstacle half-space representation [4x2]
          - B(np.ndarray): Constant vector of obstacle half-space representation    [4x1]
          - (list):        List with the x,y position of bottom-left corner and obstacle width,height
        """
        A = np.array([[1, 0],
                      [-1, 0],
                      [0, 1],
                      [0, -1]]).reshape(4, 2)
        B = np.array([x+dx, -x, y+dy, -y]).reshape(4, 1)
        return A, B, [x, y, dx, dy]

    @staticmethod
    def is_obstacle_detected(A, B, x_rob, y_rob, X_sensor):
        """Whether the given obstacle is detected by the sensor.

        Detects whether any of 5 points on sensor ray (starting from the end-point) intersect the obstacle
        (which is given by the half-space representation matrices A,B).

        Inputs:
          - A(np.ndarray):         Coefficient matrix of obstacle half-space representation [4x2]
          - B(np.ndarray):         Constant vector of obstacle half-space representation    [4x1]
          - x_rob(float):          Robot's x-position
          - y_rob(float):          Robot's y-position
          - X_sensor(np.ndarray):  Sensor ray end-point
        Returns:
          - (bool):                Whether the obstacle is detected or not
        """
        for i in range(5, -1, -1):
            u = i/5
            x = X_sensor[0].item() * u + x_rob * (1 - u)
            y = X_sensor[1].item() * u + y_rob * (1 - u)
            X = np.array([round(x, 2), round(y, 2)]).reshape(2, 1)
            if np.all(np.dot(A, X) <= B):
                return True

    def is_wall_detected(self, x, y):
        """Whether a wall is detected by the sensor.

        Detects whether the given point goes beyond the walls.

        Inputs:
          - x(float): x-position of point to check
          - y(float): y-position of point to check
        Returns:
          - (bool):   Whether a wall is detected or not
        """
        return (x < self.wall_width) or (x > self.env_dimension - self.wall_width) or \
               (y < self.wall_width) or (y > self.env_dimension - self.wall_width)

    @staticmethod
    def find_detected_obs_point(A, B, x_rob, y_rob, x_sensor, y_sensor):
        """Finds the point where the sensor ray detects the obstacle.

        Inputs:
          - A(np.ndarray):   Coefficient matrix of obstacle half-space representation [4x2]
          - B(np.ndarray):   Constant vector of obstacle half-space representation    [4x1]
          - x_rob(float):    Robot's x-position
          - y_rob(float):    Robot's y-position
          - x_sensor(float): x-position of sensor ray end-point
          - y_sensor(float): y-position of sensor ray end-point
        Returns:
          - dx(float):       The x-position offset wrt the robot of the ray point that intersects with the obstacle
          - dy(float):       The y-position offset wrt the robot of the ray point that intersects with the obstacle
        """
        num_of_points = 500
        for i in range(num_of_points+1):
            u = i / num_of_points
            x = x_sensor * u + x_rob * (1 - u)
            y = y_sensor * u + y_rob * (1 - u)
            X = np.array([round(x, 2), round(y, 2)]).reshape(2, 1)
            if np.all(np.dot(A, X) <= B):       # If point intersects obstacle
                dx = x - x_rob
                dy = y - y_rob
                break
        return dx, dy

    def find_detected_wall_point(self, x_sensor, y_sensor, x_rob, y_rob):
        """Finds the point where the sensor ray detects the wall.

        Inputs:
          - x_sensor(float): x-position of sensor ray end-point
          - y_sensor(float): y-position of sensor ray end-point
          - x_rob(float):    Robot's x-position
          - y_rob(float):    Robot's y-position
        Returns:
          - dx(float):       The x-position offset wrt the robot of the ray point that intersects with the obstacle
          - dy(float):       The y-position offset wrt the robot of the ray point that intersects with the obstacle
        """
        num_of_points = 500
        for i in range(num_of_points+1):
            u = i / num_of_points
            x = x_sensor * u + x_rob * (1 - u)
            y = y_sensor * u + y_rob * (1 - u)
            if self.is_wall_detected(x, y):  # If point is beyond walls
                dx = x - x_rob
                dy = y - y_rob
                break
        return dx, dy

    def obstacle_detection(self, x_rob, y_rob, theta, sensor_angle):
        """Detects whether a wall or obstacle is detected by the sensor and computes the intersection point, if any.

        Inputs:
          - x_rob(float):        Robot's x-position
          - y_rob(float):        Robot's y-position
          - theta(float):        Robot's heading angle
          - sensor_angle(float): The sensor angle wrt to the robot's heading
        Returns:
          - dx(float):          The x-position offset wrt the robot of the ray point  (sensor end-point or intersection)
          - dy(float):          The y-position offset wrt the robot of the ray point  (sensor end-point or intersection)
          - c(str):             The sensor's color
          - obs_detected(bool): Whether an obstacle or wall was detected
        """
        dx = np.cos(theta + sensor_angle) * config.sensor_range                  # x-position offset of sensor end-point
        dy = np.sin(theta + sensor_angle) * config.sensor_range                  # y-position offset of sensor end-point
        x_sensor = x_rob + dx                                                    # x-position of sensor end-point
        y_sensor = y_rob + dy                                                    # y-position of sensor end-point
        X_sensor = np.array([x_sensor, y_sensor]).reshape(2, 1)                  # Sensor ray end-point
        c = 'g'                                                                  # Default sensor color (green)
        obs_detected = False                                                     # Whether an obstacle/wall is detected

        # Check if wall is detected by sensor
        if self.is_wall_detected(x_sensor, y_sensor):
            dx, dy = self.find_detected_wall_point(x_sensor, y_sensor, x_rob, y_rob)  # Compute intersection point
            c = 'r'                                                                   # Turn sensor color to red
            obs_detected = True

        # Check if obstacle detected by sensor
        for A, B, _ in self.obstacles:
            if self.is_obstacle_detected(A, B, x_rob, y_rob, X_sensor):
                dx, dy = self.find_detected_obs_point(A, B, x_rob, y_rob, x_sensor, y_sensor)  # Compute intersection point
                c = 'r'                                                                # Turn sensor color to red
                obs_detected = True

        return dx, dy, c, obs_detected

    def is_collision(self, x_rob, y_rob):
        """Detects whether the robot has collided with a wall or obstacle.

        Inputs:
          - x_rob(float): Robot's x-position
          - y_rob(float): Robot's y-position
        Returns:
          - (bool): Whether there is a collision
        """
        # Check collision with walls
        walls = [(1, 0, 0), (1, 0, -self.env_dimension), (0, 1, 0), (0, 1, -self.env_dimension)]  # Line coeff ax+by+c=0
        for a, b, c in walls:
            # Distance between line and robot's center
            dist = ((abs(a*x_rob + b*y_rob + c))/np.sqrt(a**2 + b**2))
            if dist <= config.robot_radius + config.wall_width:
                return True

        # Check collision with obstacles
        for _, _, [x, y, dx, dy] in self.obstacles:
            # Find the nearest point on the rectangle to the center of the circle
            xn = max(x, min(x_rob, x+dx))
            yn = max(y, min(y_rob, y+dy))

            # Check distance between the nearest point and the center of the circle
            if ((xn-x_rob)**2 + (yn-y_rob)**2) <= config.robot_radius**2:
                return True
        return False

    def is_goal_reached(self, x_rob, y_rob):
        """Detects whether the robot has reached the goal.

        Inputs:
          - x_rob(float): Robot's x-position
          - y_rob(float): Robot's y-position
        Returns:
          - (bool): Whether the robot has reached the goal
        """
        # Distance between circle centers
        dist = np.sqrt((self.goal[0]-x_rob)**2 + (self.goal[1]-y_rob)**2)
        if dist <= self.goal_radius - config.robot_radius:  # Robot is entirely inside the goal region
            return True
        return False

    def read_sensors(self, x_rob, y_rob, theta):
        """Returns the current sensor readings in binary format.

        0: No obstacle detected
        1: Obstacle detected

        Inputs:
          - x_rob(float): Robot's x-position
          - y_rob(float): Robot's y-position
          - theta(float): Robot's heading angle
        Returns:
          - sensor_readings(list):  The sensor readings in binary format
        """
        sensor_readings = [0]*len(config.sensors)                    # Initialize sensor values to 0
        for sensor_angle in config.sensors:
            dx = np.cos(theta + sensor_angle) * config.sensor_range
            dy = np.sin(theta + sensor_angle) * config.sensor_range
            x_sensor = x_rob + dx                                    # x-position of sensor end-point
            y_sensor = y_rob + dy                                    # y-position of sensor end-point
            X_sensor = np.array([x_sensor, y_sensor]).reshape(2, 1)  # Sensor ray end-point

            # If obstacle detected by sensor, set sensor value to 1
            for A, B, _ in self.obstacles:
                if self.is_obstacle_detected(A, B, x_rob, y_rob, X_sensor):
                    sensor_readings[config.sensors.index(sensor_angle)] = 1

            # If wall detected by sensor, set sensor value to 1
            if self.is_wall_detected(x_sensor, y_sensor):
                sensor_readings[config.sensors.index(sensor_angle)] = 1

        return sensor_readings

    def get_angle_area(self, x_rob, y_rob, theta):
        """Computes the interval in which the angle to the goal belongs to (one-hot encoding).

        0: Angle does not belong in this interval
        1: Angle belongs in this interval
        E.g. If angle ∈ interval_1, then:
        angle_area = [in interval_0, in interval_1, in interval_2, in interval_3] = [0,1,0,0]

        Inputs:
          - x_rob(float): Robot's x-position
          - y_rob(float): Robot's y-position
          - theta(float): Robot's heading angle
        Returns:
          - angle_area(list): The intervals in one-hot encoding
        """
        theta_goal = np.arctan2(self.goal[1] - y_rob, self.goal[0] - x_rob)                 # Actual goal angle
        heading_error = np.arctan2(np.sin(theta_goal - theta), np.cos(theta_goal - theta))  # Relative goal angle

        # angle_area = 4*[0]  # One-hot encoding of 2pi divided into 4 intervals
        # if -np.pi <= heading_error <= -np.pi/2 or 3*np.pi/4 <= heading_error <= np.pi:
        #     angle_area[0] = 1
        # elif np.pi/2 <= heading_error <= 3*np.pi/4:
        #     angle_area[1] = 1
        # elif np.pi/4 <= heading_error <= np.pi/2:
        #     angle_area[2] = 1
        # else:
        #     angle_area[3] = 1

        # One-hot encoding of 2pi divided into 12 intervals of pi/6 (30 deg)
        # angle_area = 12*[0]
        # if 0 <= heading_error <= np.pi/6:
        #     angle_area[0] = 1
        # elif np.pi/6 <= heading_error <= 2*np.pi/6:
        #     angle_area[1] = 1
        # elif 2*np.pi/6 <= heading_error <= np.pi/2:
        #     angle_area[2] = 1
        # elif np.pi/2 <= heading_error <= 4*np.pi/6:
        #     angle_area[3] = 1
        # elif 4*np.pi/6 <= heading_error <= 5*np.pi/6:
        #     angle_area[4] = 1
        # elif 5*np.pi/6 <= heading_error <= np.pi:
        #     angle_area[5] = 1
        # elif -np.pi <= heading_error <= -5*np.pi/6:
        #     angle_area[6] = 1
        # elif -5*np.pi/6 <= heading_error <= -4*np.pi/6:
        #     angle_area[7] = 1
        # elif -4*np.pi/6 <= heading_error <= -np.pi/2:
        #     angle_area[8] = 1
        # elif -np.pi/2 <= heading_error <= -2*np.pi/6:
        #     angle_area[9] = 1
        # elif -2*np.pi/6 <= heading_error <= -np.pi/6:
        #     angle_area[10] = 1
        # else:
        #     angle_area[11] = 1

        # One-hot encoding of 2pi divided into 8 intervals of pi/4 (45 deg)
        angle_area = 8*[0]
        if 0 <= heading_error and heading_error <= np.pi/4:
            angle_area[0] = 1
        elif np.pi/4 <= heading_error and heading_error <= np.pi/2:
            angle_area[1] = 1
        elif np.pi/2 <= heading_error and heading_error <= 3*np.pi/4:
            angle_area[2] = 1
        elif 3*np.pi/4 <= heading_error and heading_error <= np.pi:
            angle_area[3] = 1
        elif -np.pi <= heading_error and heading_error <= -3*np.pi/4:
            angle_area[4] = 1
        elif -3*np.pi/4 <= heading_error and heading_error <= -np.pi/2:
            angle_area[5] = 1
        elif -np.pi/2 <= heading_error and heading_error <= -np.pi/4:
            angle_area[6] = 1
        else:
            angle_area[7] = 1

        return angle_area

    def get_reward(self, x_rob, y_rob, theta):
        """Computes the reward at the current time-step and informs whether a
        collision or reaching the goal event occurred.

        Inputs:
          - x_rob(float): Robot's x-position
          - y_rob(float): Robot's y-position
          - theta(float): Robot's heading angle
        Returns:
          - reward(float):      The reward at the current time-step
          - has_collided(bool): Whether a collision occurred
          - goal_reached(bool): Whether the goal is reached
        """
        has_collided = False
        goal_reached = False

        if self.is_collision(x_rob, y_rob):
            has_collided = True
            reward = self.collision_reward
        elif self.is_goal_reached(x_rob, y_rob):
            goal_reached = True
            reward = self.goal_reward
        else:

            # Reward weights
            dist_weight = config.dist_weight        # Distance weight
            heading_weight = config.heading_weight  # Heading weight
            time_weight = config.time_weight        # Time weight

            # Distance to goal
            dist = np.sqrt((self.goal[0] - x_rob)**2 + (self.goal[1] - y_rob)**2)

            if dist <= 0.05:
                dist = 0.05                         # Bound value for appropriate reward

            # Heading error
            theta_goal = np.arctan2(self.goal[1] - y_rob, self.goal[0] - x_rob)
            heading_error = abs(np.arctan2(np.sin(theta_goal - theta), np.cos(theta_goal - theta)))

            if heading_error <= 0.1:
                heading_error = 0.1                 # Bound value for appropriate reward

            # Compute current reward
            reward = dist_weight*1/dist + heading_weight*1/heading_error**0.5 - time_weight

        return reward, has_collided, goal_reached
