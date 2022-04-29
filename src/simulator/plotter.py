import numpy as np
import pandas as pd
import plotly.graph_objs as go

from pygenalg.algorithm import GeneticAlgorithm
from typing import Dict

class Plotter:
    """Plot results of Genetic Algorithm.
    """

    _ga: GeneticAlgorithm

    def __init__(self, ga: GeneticAlgorithm) -> None:
        self._ga = ga

    def average(self, show=True, save=False) -> None:
        data = {
            "Generation": [],
            "Fitness": [],
            "StandardDeviation": []
        }

        for i, population in enumerate(self._ga.generations):
            fitnesses = [x.fitness for x in population.individuals]

            data["Generation"].append(i + 1)
            data["Fitness"].append(np.average(fitnesses))
            data["StandardDeviation"].append(np.std(fitnesses))

        fig = go.Figure([
            go.Scatter(
                name="Average",
                x=data["Generation"],
                y=data["Fitness"],
                line=dict(color="rgb(0, 100, 80)"),
                mode="lines",
                showlegend=False
            ),
            go.Scatter(
                x=data["Generation"] + data["Generation"][::-1],
                y=(
                    (np.array(data["Fitness"]) + np.array(data["StandardDeviation"])).tolist() +
                    (np.array(data["Fitness"]) + (-1 * np.array(data["StandardDeviation"]))).tolist()[::-1]
                ),
                fill="toself",
                fillcolor="rgba(0, 100, 80, 0.2)",
                line=dict(color="rgba(255, 255, 255, 0)"),
                hoverinfo="skip",
                showlegend=False
            )
        ])

        fig.update_layout(
            title="Average Fitness per Generation",
            xaxis_title="Generation",
            yaxis_title="Fitness"
        )

        fig.write_image(f"img/{self._ga.seed}_average_fitness_per_generation.svg") if save else None
        fig.show() if show else None


    def best(self, show=True, save=False) -> Dict:
        data = {
            "Generation": [],
            "Fitness": []
        }

        for i, population in enumerate(self._ga.generations):
            data["Generation"].append(i + 1)
            data["Fitness"].append(population.best().fitness)

        fig = go.Figure([
            go.Scatter(
                name="Best",
                x=data["Generation"],
                y=data["Fitness"],
                line=dict(color="rgb(99, 110, 250)"),
                mode="lines",
                showlegend=False
            )
        ])

        fig.update_layout(
            title="Best Fitness per Generation",
            xaxis_title="Generation",
            yaxis_title="Fitness"
        )

        fig.write_image(f"img/{self._ga.seed}_best_fitness_per_generation.svg") if save else None
        fig.show() if show else None

        return data

    def worst(self, show=True, save=False) -> Dict:
        data = {
            "Generation": [],
            "Fitness": []
        }

        for i, population in enumerate(self._ga.generations):
            data["Generation"].append(i + 1)
            data["Fitness"].append(population.worst().fitness)

        df = pd.DataFrame.from_dict(data)

        fig = go.Figure([
            go.Scatter(
                name="Worst",
                x=data["Generation"],
                y=data["Fitness"],
                line=dict(color="rgb(99, 110, 250)"),
                mode="lines",
                showlegend=False
            )
        ])

        fig.update_layout(
            title="Worst Fitness per Generation",
            xaxis_title="Generation",
            yaxis_title="Fitness"
        )

        fig.write_image(f"img/{self._ga.seed}_worst_fitness_per_generation.svg") if save else None
        fig.show() if show else None

        return data

    def fitness(self, show=True, save=False):
        best = self.best(show=False, save=False)
        worst = self.worst(show=False, save=False)

        fig = go.Figure([
            go.Scatter(
                name="Best",
                x=best["Generation"],
                y=best["Fitness"],
                line=dict(color="rgb(99, 110, 250)"),
                mode="lines",
                showlegend=True
            ),
            go.Scatter(
                name="Worst",
                x=worst["Generation"],
                y=worst["Fitness"],
                line=dict(color="rgb(239, 85, 59)"),
                mode="lines",
                showlegend=True
            )
        ])

        fig.update_layout(
            title="Best and Worst Fitness per Generation",
            xaxis_title="Generation",
            yaxis_title="Fitness",
            legend_title="Fitness Type"
        )

        fig.write_image(f"img/{self._ga.seed}_best_worst_fitness_per_generation.svg") if save else None
        fig.show() if show else None
