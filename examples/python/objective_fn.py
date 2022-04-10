from pygenalg.algorithmplusplus import GeneticAlgorithm

if __name__ == "__main__":
    ga = GeneticAlgorithm(
        capacity=50,
        n_generations=100,
        p_mutation=0.01,
        seed=12345
    )
