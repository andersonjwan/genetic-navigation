from pygenalg.genalgplusplus import Options

if __name__ == "__main__":
    options = Options(
        capacity=50,
        n_generations=100,
        p_mutation=0.01
    )

    print(options.seed)
