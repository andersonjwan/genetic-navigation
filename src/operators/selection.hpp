#ifndef GENALG_OPERATORS_SELECTION_HPP
#define GENALG_OPERATORS_SELECTION_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <random>
#include <utility>
#include <vector>

#include <iostream>

namespace genalg {
    namespace operators {
        template<typename I, typename F>
        class SelectionOperator {
        public:
            virtual I select(const std::vector<std::pair<I, F>>& population,
                             std::default_random_engine& rng) const = 0;
        };

        template<typename I, typename F>
        class TournamentSelection : public SelectionOperator<I, F> {
        private:
            std::size_t tournament_size;
            double prob;
            bool replacement;

        public:
            TournamentSelection(std::size_t s=2, double p=0.5, bool rep=true)
                : tournament_size{s}, prob{p}, replacement{rep} {}

            I select(const std::vector<std::pair<I, F>>& population,
                     std::default_random_engine& rng) const override;
        };
    }
}

namespace genalg {
    namespace operators {
        template<typename I, typename F>
        I TournamentSelection<I, F>::select(const std::vector<std::pair<I, F>>& population,
                                            std::default_random_engine& rng) const {
            assert(population.size() >= 1);
            assert(this->tournament_size <= population.size());

            // randomly select individuals
            std::vector<std::pair<I, F>> pool;

            if(this->replacement) {
                for(int i = 0; i < this->tournament_size; ++i) {
                    std::sample(population.begin(), population.end(),
                                std::back_inserter(pool), 1, rng);
                }
            } else {
                std::sample(population.begin(), population.end(),
                            std::back_inserter(pool), this->tournament_size, rng);
            }

            // find best from pool
            auto winner = std::max_element(pool.begin(), pool.end(),
                                           [](const auto& lhs, const auto& rhs) {
                                               return lhs.second < rhs.second;
                                           });

            // select best with probability p
            std::uniform_real_distribution<double> rdistr(0.0, 1.0);
            if(rdistr(rng) <= this->prob) {
                return (*winner).first;
            } else {
                pool.erase(winner);
                std::sample(pool.begin(), pool.end(),
                            std::back_inserter(pool), 1, rng);

                return pool.back().first;
            }
        }
    }
}

#endif
