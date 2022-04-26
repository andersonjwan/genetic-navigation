#ifndef GENALG_OPERATORS_SELECTION_HPP
#define GENALG_OPERATORS_SELECTION_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <random>
#include <vector>

#include "population.hpp"

namespace genalg {
    namespace operators {
        /// Interface for Genetic Algorithm selection operations.
        ///
        /// @tparam I An individual
        template<typename I>
        class SelectionOperator {
        public:
            virtual I select(const Population<I>& population,
                             std::default_random_engine& rng) const = 0;
        };

        /// Selection using a tournament selection process.
        ///
        /// Selection through tournament selection involves including
        /// a specified amount of individuals to compete and selecting
        /// the most fit individual with a defined probability.
        ///
        /// @tparam I An individual
        template<typename I>
        class TournamentSelection : public SelectionOperator<I> {
        private:
            const std::size_t pool_size_;
            const double p_fittest_;

        public:
            explicit TournamentSelection(std::size_t size=2, double prob=0.5)
                : pool_size_{size}, p_fittest_{prob} {
                assert(this->pool_size_ > 0);
            }

            I select(const Population<I>& population,
                     std::default_random_engine& rng) const override;
        };
    }
}

namespace genalg {
    namespace operators {
        /// Select an individual using tournament selection technique.
        ///
        /// @param population A \ref Population to select from
        /// @param rng The Random Number Generator engine
        /// @return An individual
        template<typename I>
        I TournamentSelection<I>::select(const Population<I>& population,
                                         std::default_random_engine& rng) const {
            assert(population.size() > 0);
            assert(this->pool_size_ <= population.size());

            // randomly select individuals
            std::vector<I> pool;

            std::sample(population.begin(), population.end(),
                        std::back_inserter(pool), this->pool_size_, rng);

            if(this->pool_size_ == 1) {
                return pool.back();
            }

            auto fittest = std::max_element(pool.begin(), pool.end());

            std::uniform_real_distribution<double> rdistr(0.0, 1.0);
            if(rdistr(rng) < this->p_fittest_) {
                return *fittest;
            } else {
                pool.erase(fittest);
                std::sample(pool.begin(), pool.end(),
                            std::back_inserter(pool), 1, rng);

                return pool.back();
            }
        }
    }
}

#endif
