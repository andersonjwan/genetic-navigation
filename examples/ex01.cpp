#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "population/individual.hpp"

using genalg::population::Individual;

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

int
main(int argc, char **argv) {
    std::vector<Species<genome, fitness>> population;

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
	population.push_back(Species<genome, fitness>(uniform(*rng)));
    }

    for(int i = 0; i < POPULATION_SIZE; ++i) {
	std::cout << "{"
		  << population[i].get_genome()
		  << " , "
		  << population[i].fitness()
		  << "}\n";
    }

    delete rng;
}
