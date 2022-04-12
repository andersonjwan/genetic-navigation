import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd


def plot_fitness(population_fitness_history):
    """Plots the average & maximum fitness for each generation.

    Inputs:
      - population_fitness_history(list):  Fitness of each individual in every generation
    """
    print('\nTraining done. Generating figures..')
    num_generations = len(population_fitness_history)  # Total number of generations
    num_robots = len(population_fitness_history[0])    # Total number of robots (population size)

    # Store fitness values in a dataframe
    data = {'Generation': [i for i in range(1, num_generations+1) for _ in range(num_robots)],
            'Fitness': sum(population_fitness_history, [])}
    df = pd.DataFrame(data)

    # Plot average fitness per generation (with standard deviation shade)
    sns.set_theme()
    plt.figure(figsize=(12, 9))
    sns.relplot(x="Generation", y="Fitness", kind="line", ci="sd", data=df)
    plt.title('Average fitness')
    plt.tight_layout()
    plt.savefig("images/Average_fitness.png")
    plt.show()

    # Plot maximum fitness per generation
    plt.figure(figsize=(12, 9))
    sns.lineplot(x="Generation", y="Fitness", data=df.groupby(['Generation']).max())
    plt.xlabel('Generation')
    plt.ylabel('Fitness')
    plt.title('Maximum fitness')
    plt.tight_layout()
    plt.savefig("images/Maximum_fitness.png")
    plt.show()
