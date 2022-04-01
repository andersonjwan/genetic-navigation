#include <cmath>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "population/individual.hpp"

using genalg::population::Individual;

using Genome = double;
using Fitness = double;

#define POPULATION_SIZE 25

// custom individual
class Species : public Individual<Genome, Fitness> {
public:
    Species(Genome g)
        : Individual<Genome, Fitness>(g) {}

    Fitness fitness(void) const override {
        return std::sin(this->genome) - 0.2 * std::abs(this->genome);
    }
};

int
main(int argc, char **argv) {
    std::vector<Species> population;
    std::unique_ptr<std::mt19937> rng;

    if(argc == 2) {
        rng = std::make_unique<std::mt19937>(std::stoi(argv[1]));
    } else {
        std::random_device rd;
        rng = std::make_unique<std::mt19937>(rd());
    }

    // randomly initialize population
    std::uniform_real_distribution<double> uniform(-10.0, 10.0);

    for(int i = 0; i < POPULATION_SIZE; ++i) {
        population.push_back(Species(uniform(*rng)));
    }

    for(int i = 0; i < POPULATION_SIZE; ++i) {
        std::cout << "{"
                  << population[i].get_genome()
                  << " , "
                  << population[i].fitness()
                  << "}\n";
    }
}
