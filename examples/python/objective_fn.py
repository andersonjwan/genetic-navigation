from pygenalg.algorithm import GeneticAlgorithm
from pygenalg.options import Options

if __name__ == "__main__":
    ga = GeneticAlgorithm(
        capacity=50,
        n_generations=100,
        p_mutation=0.01
    )

    options = Options(
        capacity=50,
        n_generations=100,
        p_mutation=0.01
    )

    print(options.seed)
