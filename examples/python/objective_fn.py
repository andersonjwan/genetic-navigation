from pygenalg.algorithm import GeneticAlgorithm
from pygenalg.options import Options
from pygenalg.population import Population
from pygenalg.individual import BinaryIndividual

def rank(population: Population):
    """Adjust individual fitness based on combination.
    """
    adjusted = Population(len(population))

    for individual in population:
        adjusted.add(BinaryIndividual(individual[0]), individual[0].count(1))

    return adjusted

if __name__ == "__main__":
    ga = GeneticAlgorithm(
        capacity=4,
        n_generations=100,
        p_mutation=0.01
    )

    population = Population(4)

    population.add(BinaryIndividual([1, 1, 1, 1, 0, 1, 0, 1, 0]), 3.0)
    population.add(BinaryIndividual([1, 1, 1, 1, 0, 0, 0, 0, 0]), 2.0)
    population.add(BinaryIndividual([1, 1, 1, 1, 1, 1, 1, 1, 1]), 1.0)
    population.add(BinaryIndividual([0, 0, 0, 0, 0, 0, 0, 0, 0]), 0.0)

    for i in range(100):
        population = ga.update(population)

        # update the fitness of each individual based on an external
        # metric (e.g., environmental factors)
        population = rank(population)

        for individual in population:
            print(f"({individual[0]}, {individual[1]})")
