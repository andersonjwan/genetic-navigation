#ifndef GENALG_OPTIONS_HPP
#define GENALG_OPTIONS_HPP

#include <cstddef>

namespace genalg {
    class Options {
    public:
        std::size_t population_size;
        std::size_t n_generations;
        double mutation_chance = 0.01;

        Options(std::size_t p, std::size_t g, double m)
            : population_size{p}, n_generations{g}, mutation_chance{m} {}
    };
}

#endif
