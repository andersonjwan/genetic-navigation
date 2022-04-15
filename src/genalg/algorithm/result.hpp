#ifndef GENALG_ALGORITHM_RESULT_HPP
#define GENALG_ALGORITHM_RESULT_HPP

#include <utility>
#include <vector>

#include "population.hpp"

namespace genalg {
    namespace algorithm {
        /// The result created after running the \ref GeneticAlgorithm.
        ///
        /// @tparam I An individual
        /// @tparam F The metric used to evaluate the fitness of an individual
        template<typename I, typename F>
        class Result {
        public:
            /// The set of populations for each generation
            const std::vector<Population<I, F>> generations;

            Result(std::vector<Population<I, F>> gens)
                : generations{gens} {}

            std::vector<std::pair<I, F>> best() const;
            std::vector<std::pair<I, F>> worst() const;
        };
    }
}

namespace genalg {
    namespace algorithm {
        /// Calculate the best individual for each generation.
        ///
        /// @return The list of best individuals per generation.
        template<typename I, typename F>
        std::vector<std::pair<I, F>> Result<I, F>::best() const {
            std::vector<std::pair<I, F>> maximums;

            for(auto& x : this->generations) {
                maximums.push_back(x.best());
            }

            return maximums;
        }

        /// Calculate the worst individual for each generation.
        ///
        /// @return The list of worst individuals per generation.
        template<typename I, typename F>
        std::vector<std::pair<I, F>> Result<I, F>::worst() const {
            std::vector<std::pair<I, F>> minimums;

            for(auto& x : this->generations) {
                minimums.push_back(x.worst());
            }

            return minimums;
        }
    }
}

#endif
