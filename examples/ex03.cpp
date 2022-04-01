#include <cmath>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "population.hpp"
#include "population/individual.hpp"

using genalg::population::Individual;
using genalg::population::IndividualFactory;
using genalg::Population;

using Genome = double;
using Fitness = double;

#define POPULATION_SIZE 25

class Species : public Individual<Genome, Fitness> {
public:
    Species(Genome g)
        : Individual<Genome, Fitness>(g) {}

    Genome fitness(void) const override {
        return std::sin(this->genome) - 0.2 * std::abs(this->genome);
    }
};

template<typename R>
class SpeciesFactory : public IndividualFactory<Species> {
private:
    R& rng;

public:
    SpeciesFactory(R& r)
        : rng{r} {}

    Species make_individual(void) const override {
        std::uniform_real_distribution<double> uniform(-10.0, 10.0);
        return Species(uniform(this->rng));
    }
};

int
main(int argc, char **argv) {
    std::unique_ptr<std::mt19937> rng;

    if(argc == 2) {
        rng = std::make_unique<std::mt19937>(std::stoi(argv[1]));
    } else {
        std::random_device rd;
        rng = std::make_unique<std::mt19937>(rd());
    }

    // initialize population
    Population<Species, Fitness> population(POPULATION_SIZE,
                                            SpeciesFactory<std::mt19937>(*rng));

    for(int i = 0; i < POPULATION_SIZE; ++i) {
        std::cout << "{"
                  << population[i].first.get_genome()
                  << " , "
                  << population[i].second
                  << "}\n";
    }

    auto best = population.best();
    std::cout << "\nBEST SOLUTION:  " << "{"
              << best.first.get_genome()
              << " , "
              << best.second
              << "}\n";

    auto worst = population.worst();
    std::cout << "WORST SOLUTION: " << "{"
              << worst.first.get_genome()
              << " , "
              << worst.second
              << "}\n";
}
