import numpy as np

# Environment
env_dimension = 15                                   # The dimensions of the workspace
goal_radius = 0.8                                    # Radius of goal circle
wall_width = 0.15                                    # Workspace wall half-width
env_id = 0                                           # The predefined environment layout id [0-1]

if env_id == 0:
    goal = (8.0, 10.5)                               # Goal position for env 0
elif env_id == 1:
    goal = (2.0, 13.5)                               # Goal position for env 1
elif env_id == 2:
    goal = (2.0, 13.5)                               # Goal position for env 2
elif env_id == 3:
    # Difficult layout for final testing!!!
    goal = (12.0, 11.25)                             # Goal position for env 3

# Robot
robot_radius = 0.35                                  # Robot's radius
sensor_range = 2                                     # Sensor range [m]
sensors = [np.pi/2, np.pi/4, 0, -np.pi/4, -np.pi/2]  # Sensor angles wrt robot heading angle [rad]
actions = {'000': round(-np.pi/2, 2),
           '001': round(-np.pi/3, 2),
           '010': round(-np.pi/6, 2),
           '011': 0,
           '100': round(np.pi/6, 2),
           '101': round(np.pi/3, 2),
           '110': round(np.pi/2, 2),
           '111': round(np.pi, 2)}                   # Actions encoding (binary->angular velocity)

# Simulator
dt = 0.1                                             # Sample time
max_steps = 1000                                     # The maximum number of steps for one episode
v = 0.5                                              # Constant linear velocity
goal_reward = 1000                                   # Reward for reaching the goal
collision_reward = -100                             # Reward for collision
dist_weight = 1                                      # Distance weight
heading_weight = 1                                   # Heading weight
time_weight = 0.01                                    # Time weight
