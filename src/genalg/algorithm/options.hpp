#ifndef GENALG_OPTIONS_HPP
#define GENALG_OPTIONS_HPP

#include <cstddef>
#include <random>

namespace genalg {
    namespace algorithm {
        class Options {
        public:
            const std::size_t population_size;
            const std::size_t n_generations;
            const double mutation_chance = 0.01;
            unsigned long int seed;

            Options(std::size_t p, std::size_t g, double m)
                : population_size{p}, n_generations{g}, mutation_chance{m} {
                std::random_device rd;
                std::uniform_int_distribution<unsigned long int> distr(0, std::pow(2, 32) - 1);

                seed = distr(rd);
            }

            Options(std::size_t p, std::size_t g, double m, unsigned long int s)
                : population_size{p}, n_generations{g}, mutation_chance{m},
                  seed{s} {}

        };
    }
}

#endif
