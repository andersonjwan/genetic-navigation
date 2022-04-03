#ifndef GENALG_GENALGORITHM_HPP
#define GENALG_GENALGORITHM_HPP

#include <vector>

#include "options.hpp"
#include "operators.hpp"
#include "population.hpp"
#include "population/individual.hpp"

namespace genalg {
    template<typename I,
             typename F,
             typename G,
             typename S,
             typename C,
             typename M,
             typename X>
    double genalgorithm(Options& options,
                        // Operators<I, F, S, C, M>& operators,
                        G& generator,
                        X& termination) {
        std::vector<Population<I, F>> generations;
        generations.push_back(Population<I, F>(options.population_size, generator));

        while(!termination.terminate(generations.back().solutions())) {
            std::cout << "GENERATION " << generations.size() << "\n";
            generations.push_back(Population<I, F>(options.population_size, generator));
        }

        // std::vector<P> generations;

        // initialize random population
        // generations.push_back();

        // while(generations.size() < options.n_generations) {
        //     // select breeders

        //     // perform crossover

        //     // perform mutation

        //     // add population to generations
        // }

        return 0.0;
    }
}

#endif
