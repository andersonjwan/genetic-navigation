/**
 * This example (example03) demonstrates one of the recombination methods
 * within Genetic Algorithms (GAs) formally known
 * as Multi-Point Crossover.
 *
 **/

#include "operators/crossover.hpp"

#include <bitset>
#include <iostream>

using genome = std::vector<int>;

std::string
printout(genome& g) {
    std::string s = "";
    for(auto& x : g) {
	s += std::to_string(x);
    }

    return s;
}

int
main(void) {
    genome p1 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    genome p2 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    genalg::operators::MultiPointCrossover<genome> spc(5);
    std::array<genome, 2> children = spc.crossover(p1, p2);

    std::cout << "P1: " << printout(p1) << "\n";
    std::cout << "P2: " << printout(p2) << "\n";
    std::cout << "C1: " << printout(children[0]) << "\n";
    std::cout << "C2: " << printout(children[1]) << "\n";
}
