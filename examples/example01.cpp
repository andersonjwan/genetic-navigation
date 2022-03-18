/**
 * This example (example01) demonstrates the selection method
 * within Genetic Algorithms (GAs) formally known
 * as Tournament Selection.
 *
 * The default values are a population size of 15 and a tournament
 * selection size of 5.
 *
 * - The greater the tournament size, the less chance for less
 * fit individuals to be selected.
 **/

#include "operators/selection.hpp"

#include <map>
#include <random>
#include <string>
#include <iomanip>
#include <iostream>

int
main(void) {
    std::map<int, double> population;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(1, 1000);

    for(int i = 0; i < 15; ++i) {
	population[i] = distr(gen);
    }

    genalg::operators::TournamentSelection<int, double> ts(5, 0.5);
    std::vector<int> wins(population.size());

    for(int i = 0; i < 500; ++i) {
	wins[ts.select(population)]++;
    }

    for(int i = 0; i < wins.size(); ++i) {
	std::cout << "{"
		  << std::setw(3) << std::setfill('0') << i << " , "
		  << std::setw(3) << std::setfill('0') << population[i] << "}" << ": ";

	int j;
	for(j = 0; j < wins[i]; ++j) {
	    std::cout << "*";
	}

	if(j == 0) {
	    std::cout << "(" << wins[i] << ")\n";
	} else {
	    std::cout << " (" << wins[i] << ")\n";
	}
    }
}
