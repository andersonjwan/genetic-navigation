#ifndef GENALG_OPERATORS_SELECTION_HPP
#define GENALG_OPERATORS_SELECTION_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <random>
#include <utility>
#include <vector>

namespace genalg {
    namespace operators {
        /// Interface for GA selection operations.
        ///
        /// @tparam I An individual
        /// @tparam F The metric used to evaluate the fitness of an individual
        template<typename I, typename F>
        class SelectionOperator {
        public:
            virtual I select(const std::vector<std::pair<I, F>>& population,
                             std::default_random_engine& rng) const = 0;
        };

        /// Selection using tournament-style operations.
        ///
        /// The tournament selection process involves a tournament size
        /// (i.e., how many individuals to compete), the chance of selecting
        /// the best fit, and whether that selected individual gets replaced
        /// to be picked again.
        ///
        /// @tparam I An individual
        /// @tparam F The metric used to evaluate the fitness of an individual
        template<typename I, typename F>
        class TournamentSelection : public SelectionOperator<I, F> {
        private:
            const std::size_t tournament_size_;
            const double prob_;
            const bool replacement_;

        public:
            TournamentSelection(std::size_t s=2, double p=0.5, bool rep=true)
                : tournament_size_{s}, prob_{p}, replacement_{rep} {}

            I select(const std::vector<std::pair<I, F>>& population,
                     std::default_random_engine& rng) const override;
        };
    }
}

namespace genalg {
    namespace operators {
        /// Select the tournament size of individuals to compete.
        ///
        /// @param population The population fitness list
        /// @param rng The Random Number Generator engine
        /// @return The selected individual (i.e, the winner)
        template<typename I, typename F>
        I TournamentSelection<I, F>::select(const std::vector<std::pair<I, F>>& population,
                                            std::default_random_engine& rng) const {
            assert(population.size() >= 1);
            assert(this->tournament_size_ <= population.size());

            // randomly select individuals
            std::vector<std::pair<I, F>> pool;

            if(this->replacement_) {
                for(int i = 0; i < this->tournament_size_; ++i) {
                    std::sample(population.begin(), population.end(),
                                std::back_inserter(pool), 1, rng);
                }
            } else {
                std::sample(population.begin(), population.end(),
                            std::back_inserter(pool), this->tournament_size_, rng);
            }

            // find best from pool
            auto winner = std::max_element(pool.begin(), pool.end(),
                                           [](const auto& lhs, const auto& rhs) {
                                               return lhs.second < rhs.second;
                                           });

            // select best with probability p
            std::uniform_real_distribution<double> rdistr(0.0, 1.0);
            if(rdistr(rng) <= this->prob_) {
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
