Genetic Algorithms (GA)
=======================

.. figure:: /images/evolution.jpg
   :align: center
   :alt: Darwinian evolution
   :width: 60%

   Darwinian evolution


A Genetic Algorithm, part of the larger class of Evolutionary Algorithms (EA),
is a heuristic search method that is inspired by Charles Darwin's theory of
evolution. According to this theory, evolution happens by natural selection,
meaning that the fittest individuals are the ones that can adapt to changes
in their environment and therefore are able to survive and reproduce.

Genetic algorithms simulate the **"Survival of the Fittest"**, where the
fittest individuals are chosen for reproduction and hence only their offspring
survive through the next generations.

Each generation consist of a population of individuals and each individual
represents a point in the search space that is a possible solution.

Genetic algorithms are used to solve optimization problems that are not well
suited for standard optimization algorithms. These include problems in which the
objective function is discontinuous, non-differentiable, stochastic or
highly non-linear.

GA Advantages:
 * Does not require the computation of derivatives
 * Works on discontinuous, non-differentiable, stochastic or highly non-linear functions
 * Is efficient for large search spaces and large number of parameters
 * Provides a set of good solutions instead of a single solution

GA Disadvantages:
 * No guarantees on the optimality of the solution since it is a stochastic method
 * Choice of hyper-parameters can affect the convergence to the optimal solution
 * Repeated calls to the fitness function might be computationally expensive
 * The formulation of the fitness function is critical for convergence


**Elements of GA**

The key elements of this method are the following:

 * **Selection**: Select the fittest individuals for reproduction to pass their
   genes to the next generation
 * **Recombination**: Pair the best candidates to yield better individuals/offspring
 * **Mutation**: Randomly perturb an individual to maintain diversity and prevent
   premature convergence to a non-optimal solution

