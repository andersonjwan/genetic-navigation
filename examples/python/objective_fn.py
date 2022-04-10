from pygenalg.genalgplusplus import Options

if __name__ == "__main__":
    options = Options(
        population_size=50,
        n_generations=100,
        mutation_chance=0.01
    )

    print(options.seed)
