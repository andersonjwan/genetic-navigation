..    include:: <isonum.txt>

Implementation Details
----------------------
The system architectural overview is illustrated in the following figure:

.. figure:: /images/overview.png
   :align: center
   :alt: overview
   :scale: 90%

   Architectural overview


Observations
^^^^^^^^^^^^
The mobile robot is equipped with five range sensors that can detect obstacles
and provide an output of either 1 or 0, depending on whether an obstacle was
detected or not, respectively. Moreover, the space around the robot is divided
into eight sections of 45 degrees each and it checks in which of these sections
the angle to the goal belongs to.


.. figure:: /images/obs.png
   :align: center
   :alt: Observation space
   :scale: 70%

   Observation space

A sample input to the controller consists of:

=== === === === === === === === === === === === ===
Angle-to-Goal                   Sensors
------------------------------- -------------------
A_0 A_1 A_2 A_3 A_4 A_5 A_6 A_7 S_0 S_1 S_2 S_3 S_4
=== === === === === === === === === === === === ===
 1   0   0   0   0   0   0   0   0   1   0   0   1
=== === === === === === === === === === === === ===

indicating that the angle to the goal lies within the first interval of
[0\ :sup:`◦`\ , 45\ :sup:`◦`\ ] and that sensors s1 and s4 have detected an obstacle.


Actions
^^^^^^^
The robot uses the unicycle model. It is provided with a constant linear velocity
and the angular velocity is computed by the controller. So, the robot can take
eight different actions that correspond to the following angular velocities:


.. figure:: /images/actions.png
   :align: center
   :alt: actions
   :scale: 70%

   The robot's actions

.. figure:: /images/actions_encoding.png
   :align: center
   :alt: actions encoding
   :scale: 50%

   The encoding of the actions




Chromosome Encoding
^^^^^^^^^^^^^^^^^^^
To ensure that the GA chromosome always comprises of a valid solution,
the algorithm uses a binary encoding with 2\ :sup:`13`\  possible input observations
and 2\ :sup:`3`\  possible actions.

The encoding procedure consists of:

**Step 1**
    Assume that the observation ‘0000000100000’ corresponds to the optimal action ‘001’.

    E.g., ‘0000000100000’ |rarr| ‘001’

**Step 2**
    Convert the observation bit sequence into a decimal value.

    (0000000100000)\ :sub:`2`\ = (32)\ :sub:`10`\

    So, 32 |rarr| ‘001’

    This decimal value corresponds to a position in the chromosome.

**Step 3**
    This position encodes the optimal action (consisting of a sequence of 3 bits)
    for that particular input combination.

    So, in the position 32 of the chromosome, the sequence ‘001’ will be present
    which represents the action to take (action 1).

    xxx xxx xxx xxx xxx xxx xxx xxx xxx ... 001 ... xxx xxx xxx



Genetic Algorithm Elements
^^^^^^^^^^^^^^^^^^^^^^^^^^
For the elements of the GA, the following operations are utilized:

* Selection: Tournament Selection
             Selects the fittest individual with probability p from a tournament size S
* Recombination: Multi-Point Crossover
                 Swaps two chromosomes at N different points
* Mutation: Bit Flip Inversion
            Randomly flips M bits with probability p of each bit being flipped


.. figure:: /images/GA_diagram.png
   :align: center
   :alt: GA_diagram
   :scale: 30%

   Genetic Algorithm diagram
