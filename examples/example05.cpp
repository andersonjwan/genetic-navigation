#include <cmath>
#include <iostream>
#include <vector>

#include "population/individual.hpp"

#define POPULATION_SIZE 25

using genalg::population::Individual;

using genome = double;
using metric = double;

template<typename T, typename F>
class MyIndividual : public Individual<T, F> {
public:
    MyIndividual(T g)
	: Individual<T, F>(g) {}

    F fitness() override {
	return std::abs(this->m_genome) * this->m_genome;
    }
};

int
main() {
    std::vector<MyIndividual<genome, metric>> population;

    for(int i = 0; i < POPULATION_SIZE; ++i) {
	population.push_back(MyIndividual<genome, metric>(i));
	std::cout << "{" << i << " , " << population[i].fitness() << "}\n";
    }
}
