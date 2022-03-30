#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "population.hpp"
#include "population/individual.hpp"

using genalg::population::Individual;
using genalg::Population;

using genome = double;
using fitness = double;

#define POPULATION_SIZE 25

// custom individual
template<typename G, typename F>
class Species : public Individual<G, F> {
public:
    Species(G g)
	: Individual<G, F>(g) {}

    F fitness(void) const override {
	return std::sin(this->genome) - 0.2 * std::abs(this->genome);
    }
};

using MyIndividual = Species<genome, fitness>;

int
main(int argc, char **argv) {
    Population<MyIndividual, fitness> population(POPULATION_SIZE);

    std::mt19937* rng;
    if(argc == 2) {
	// use provided SEED
	rng = new std::mt19937(std::stoi(argv[1]));
    } else {
	std::random_device rd;
	rng = new std::mt19937(rd());
    }

    std::uniform_real_distribution<double> uniform(-10.0, 10.0);

    // randomly initialize population
    for(int i = 0; i < POPULATION_SIZE; ++i) {
	population.add(MyIndividual(uniform(*rng)));
    }

    for(int i = 0; i < POPULATION_SIZE; ++i) {
	std::cout << "{"
		  << population[i].first.get_genome()
		  << " , "
		  << population[i].second
		  << "}\n";
    }

    delete rng;
}
