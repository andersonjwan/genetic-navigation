import numpy as np

env_dimension = 15                                   # The dimensions of the workspace
goal = (6.5, 8.5)                                    # Goal position
goal_radius = 0.8                                    # Radius of goal circle
wall_width = 0.15                                     # Workspace wall half-width
robot_radius = 0.35                                  # Robot's radius
sensor_range = 2                                     # Sensor range [m]
sensors = [np.pi/2, np.pi/4, 0, -np.pi/4, -np.pi/2]  # Sensor angles wrt robot heading angle [rad]
dt = 0.1                                             # Sample time
