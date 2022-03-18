/**
 * This example (example04) demonstrates one of the mutation methods
 * within Genetic Algorithms (GAs) known
 * as Gene Replacement.
 *
 **/

#include "operators/mutation.hpp"

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

    genalg::operators::GeneReplacement<genome, int> rg({0, 1}, 5);
    genome p1_mutated = rg.mutate(p1);

    std::cout << "P1 BEFORE: " << printout(p1) << "\n";
    std::cout << "P1 AFTER : " << printout(p1_mutated) << "\n";
}
