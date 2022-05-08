Welcome to Genetic Navigation's documentation!
==============================================

The *Genetic Navigation* uses a **Genetic Algorithm (GA)** to learn a **controller**
for a wheeled mobile robot in order to successfully navigate in an environment.
The objective is for the robot to reach a goal location while avoiding
collisions with obstacles.

For more information on Genetic Algorithms, please visit the :doc:`genetic_algos` section.

This algorithm utilizes four custom environments, where each environment consists
of a goal position (indicated by the green circle), a set of obstacles, and the
list of robots that are candidate solutions.

.. figure:: /images/envs.png
   :align: center
   :alt: environments
   :scale: 40%

   The custom environments


These are the results for each environment after a few generations:

.. figure:: /images/env1.gif
   :align: center
   :alt: Environment 1
   :scale: 50%

   Environment 1

.. figure:: /images/env2.gif
   :align: center
   :alt: Environment 2
   :scale: 50%

   Environment 2

.. figure:: /images/env3.gif
   :align: center
   :alt: Environment 3
   :scale: 50%

   Environment 3


A solution that enables the robot to navigate to the goal while avoiding
collisions is always found.




Check out the :doc:`implementation` section for further information and the
:doc:`usage` section for instructions on how to use *Genetic Navigation*.


.. toctree::
   :maxdepth: 2
   :caption: Contents:
   :hidden:

   Home <self>
   genetic_algos
   implementation
   usage
   modules

