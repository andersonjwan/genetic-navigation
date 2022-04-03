#ifndef GENALG_GENALGORITHM_HPP
#define GENALG_GENALGORITHM_HPP

#include <array>
#include <vector>

#include "options.hpp"
#include "operators.hpp"
#include "population.hpp"

namespace genalg {
    template<typename I,
             typename O,
             typename R>
    std::array<I, 2> breed(const I& p1,
                           const I& p2,
                           O& operators,
                           double mutation_chance,
                           R& rng) {
        std::uniform_real_distribution<double> rdistr(0.0, 1.0);

        std::array<I, 2> offspring = operators.cross(p1, p2);
        for(int i = 0; i < 2; ++i) {
            if(rdistr(rng) < mutation_chance) {
                std::cout << "mutating...\n";
                offspring[i] = operators.mutate(offspring[i]);
            }
        }

        return offspring;
    }

    template<typename I,
             typename F,
             typename G,
             typename S,
             typename C,
             typename M,
             typename X,
             typename R>
    double genalgorithm(Options& options,
                        Operators<I, F, S, C, M>& operators,
                        G& generator,
                        X& termination,
                        R& rng) {
        std::vector<Population<I, F>> generations;
        generations.push_back(Population<I, F>(options.population_size, generator));

        while(!termination.terminate(generations.back().solutions())) {
            std::cout << "GENERATION " << generations.size() << "\n";

            // generate a new population
            generations.push_back(Population<I, F>(options.population_size));

            // breed offspring
            while(generations.back().solutions().size() < options.population_size) {

                I p1 = operators.select(generations.end()[-2].solutions());
                I p2 = operators.select(generations.end()[-2].solutions());

                std::array<I, 2> offspring =
                    breed<I,
                          Operators<I, F, S, C, M>,
                          R>(p1, p2,
                             operators,
                             options.mutation_chance,
                             rng);

                for(int i = 0; i < 2; ++i) {
                    if(generations.back().solutions().size() >= options.population_size) {
                        break;
                    }

                    std::cout << "added... ";
                    std::cout << (offspring[i].get_genome()[0] == 1 ? "NEGATIVE " : "POSITIVE ");
                    for(int j = 0; j < offspring[i].get_genome().size(); ++j) {
                        std::cout << offspring[i].get_genome()[j];
                    }
                    std::cout << ": " << offspring[i].decimal() << "\n";

                    generations.back().add(offspring[i]);
                }
            }
        }

        for(int i = 0; i < generations.size(); ++i) {
            std::cout << "BEST: " << "(" << generations[i].best().first.decimal() << ", "
                      << generations[i].best().second << ")\n";
        }

        return 0.0;
    }
}

#endif
