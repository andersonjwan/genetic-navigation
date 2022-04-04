#ifndef GENALG_ALGORITHM_RESULT_HPP
#define GENALG_ALGORITHM_RESULT_HPP

#include <utility>
#include <vector>

#include "population.hpp"

namespace genalg {
    namespace algorithm {
        template<typename I, typename F>
        class Result {
        public:
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
        template<typename I, typename F>
        std::vector<std::pair<I, F>> Result<I, F>::best() const {
            std::vector<std::pair<I, F>> maximums;

            for(auto& x : this->generations) {
                maximums.push_back(x.best());
            }

            return maximums;
        }

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
