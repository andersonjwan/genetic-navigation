#include <cmath>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "genalgorithm.hpp"

#include "options.hpp"
#include "algorithm/termination.hpp"

#include "population/individual.hpp"

using genalg::Options;
using genalg::algorithm::GenerationLimit;

using genalg::population::Individual;
using genalg::population::IndividualFactory;

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

    Options options(25, 100);
    SpeciesFactory<std::mt19937> generator(*rng);
    GenerationLimit<Species, Fitness> termination(options.n_generations);

    genalg::genalgorithm<Species,
                         Fitness,
                         SpeciesFactory<std::mt19937>,
                         double,
                         double,
                         double,
                         GenerationLimit<Species, Fitness>>
        (options, generator, termination);
}
