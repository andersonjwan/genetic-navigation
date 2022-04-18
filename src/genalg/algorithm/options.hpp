#ifndef GENALG_OPTIONS_HPP
#define GENALG_OPTIONS_HPP

#include <cstddef>
#include <random>

namespace genalg {
    namespace algorithm {
        /// Set of options to provide to \ref GeneticAlgorithm interface.
        ///
        /// The population size and the chance of mutation must be defined
        /// for the options. If no seed is provided, a randomly generated seed
        /// will be set.
        class Options {
        public:
            /// The number of individuals per \ref Population
            const std::size_t population_capacity;

            /// The probability of a mutation occurring for an individual
            const double p_mutation = 0.01;

            /// A optional value to seed the random number generator engine
            unsigned long int seed;

            /// Initialize the options with a randomly generated seed.
            ///
            /// @param p The \ref Population capacity
            /// @param m The probability of a mutation occurring in an offspring
            Options(std::size_t p, double m)
                : population_capacity{p}, p_mutation{m} {
                // randomly generate a seed
                std::random_device rd;
                std::uniform_int_distribution<unsigned long int> distr(0, std::pow(2, 32) - 1);

                seed = distr(rd);
            }

            /// Initialize the options with a provided seed.
            ///
            /// @param p The \ref Population capacity
            /// @param m The probability of a mutation occurring in an offspring
            /// @param s A number to seed the program.
            Options(std::size_t p, double m, unsigned long int s)
                : population_capacity{p}, p_mutation{m}, seed{s} {}

        };
    }
}

#endif
