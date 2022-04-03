#ifndef GENALG_ALGORITHM_RESULT_HPP
#define GENALG_ALGORITHM_RESULT_HPP

#include <utility>
#include <vector>

#include "population.hpp"

namespace genalg {
    namespace algorithm {
        template<typename I, typename F>
        class Result {
        private:
            std::vector<Population<I, F>> generations;

        public:
            Result(std::vector<Population<I, F>> gens)
                : generations{gens} {}

            std::vector<std::pair<I, F>> best();
            std::vector<std::pair<I, F>> worst();
        };
    }
}

namespace genalg {
    namespace algorithm {
        template<typename I, typename F>
        std::vector<std::pair<I, F>> Result<I, F>::best() {
            std::vector<std::pair<I, F>> maximums;

            for(auto& x : this->generations) {
                maximums.push_back(x.best());
            }

            return maximums;
        }

        template<typename I, typename F>
        std::vector<std::pair<I, F>> Result<I, F>::worst() {
            std::vector<std::pair<I, F>> minimums;

            for(auto& x : this->generations) {
                minimums.push_back(x.best());
            }

            return minimums;
        }
    }
}

#endif
