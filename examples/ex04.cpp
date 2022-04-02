#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <random>
#include <string>
#include <vector>

#include "operators/selection.hpp"
#include "population.hpp"
#include "population/individual.hpp"

using genalg::operators::SelectionOperator;
using genalg::operators::TournamentSelection;
using genalg::population::Individual;
using genalg::population::IndividualFactory;
using genalg::Population;

using Genome = double;
using Fitness = double;

#define POPULATION_SIZE 10

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

std::ostream& operator<<(std::ostream& os, const Species& s) {
    return os << "{" << std::setprecision(3) << std::fixed << std::setfill(' ')
              << std::setw(6) << s.get_genome() << ", "
              << std::setw(6) << s.fitness() << "}";
}

bool operator<(const Species& lhs, const Species& rhs) {
    return lhs.get_genome() < rhs.get_genome();
}

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
    std::shared_ptr<SelectionOperator<Species, Fitness>> sop =
        std::make_shared<TournamentSelection<
            Species, Fitness, std::mt19937>>(*rng, 3, 0.5, true);

    Population<Species, Fitness>
        population(POPULATION_SIZE,
                   SpeciesFactory<std::mt19937>(*rng), sop);

    for(int i = 0; i < POPULATION_SIZE; ++i) {
        std::cout << population[i].first << "\n";
    }

    auto best = population.best();
    std::cout << "\nBEST SOLUTION:  " << best.first << "\n";

    auto worst = population.worst();
    std::cout << "WORST SOLUTION: " << worst.first << "\n";

    std::map<Species, int> selections;
    for(int i = 0; i < 500; ++i) {
        Species s = population.select();
        selections[s]++;
    }

    std::cout << "\nTOURNAMENT SELECTION RESULTS (N=500):\n";
    for(auto& iter : selections) {
        std::cout  << iter.first << ": ";

        for(int i = 0; i < iter.second; ++i) {
            std::cout << "*";
        }

        std::cout << "(" << iter.second << ")\n";
    }
}
