#ifndef GENALG_OPERATORS_CROSSOVER_HPP
#define GENALG_OPERATORS_CROSSOVER_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <random>
#include <numeric>
#include <vector>

namespace genalg {
    namespace operators {
        /// Interface for a crossover operator.
        ///
        /// @tparam I An individual
        template<typename I>
        class CrossoverOperator {
        public:
            virtual std::array<I, 2> cross(const I& p1, const I& p2,
                                           std::default_random_engine& rng) const = 0;
        };

        /// Recombination technique for crossing over at multiple points.
        ///
        /// This operation is used primarily for sequences of items (e.g., an
        /// array or vector of booleans). As long as the Genome of the individual
        /// is iterable, it can be crossed.
        ///
        /// @tparam I An individual
        template<typename I>
        class MultiPointCrossover : public CrossoverOperator<I> {
        private:
            const std::size_t n_crossovers_;

        public:
            explicit MultiPointCrossover(std::size_t n)
                : n_crossovers_{n} {}

            std::array<I, 2> cross(const I& p1, const I& p2,
                                   std::default_random_engine& rng) const override;
        };

        /// Recombination technique for crossing over at a single point.
        ///
        /// This operation is used for recombining two individuals at one
        /// point.
        ///
        /// @tparam I An individual
        template<typename I>
        class SinglePointCrossover : public MultiPointCrossover<I> {
        public:
            SinglePointCrossover()
                : MultiPointCrossover<I>(1) {}

            /// Cross two individuals at one point.
            ///
            /// @param p1 The first parent
            /// @param p2 The second parent
            /// @return Two newly crossed individuals
            std::array<I, 2> cross(const I& p1, const I& p2,
                                   std::default_random_engine& rng) const override {
                return MultiPointCrossover<I>::cross(p1, p2, rng);
            }
        };
    }
}

namespace genalg {
    namespace operators {
        /// Cross two individuals at multiple points.
        ///
        /// @param p1 The first parent
        /// @param p2 The second parent
        /// @return Two newly crossed individuals
        template<typename I>
        std::array<I, 2> MultiPointCrossover<I>::cross(const I &p1, const I &p2,
                                                       std::default_random_engine& rng) const {
            assert(p1.get_genome().size() == p2.get_genome().size());
            assert(this->n_crossovers_ <= p1.get_genome().size());

            auto genome1 = p1.get_genome();
            auto genome2 = p2.get_genome();

            std::vector<std::size_t> indexes(p1.get_genome().size() - 1);
            std::iota(indexes.begin(), indexes.end(), 1);

            std::vector<std::size_t> points;
            std::sample(indexes.begin(), indexes.end(),
                        std::back_inserter(points), this->n_crossovers_, rng);

            std::sort(points.begin(), points.end());

            for(int i = 0; i < points.size(); ++i) {
                for(int j = points[i]; j < genome1.size(); ++j) {
                    std::swap(genome1[j], genome2[j]);
                }
            }

            return std::array<I, 2> {
                I(genome1),
                I(genome2)
            };
        }
    }
}

#endif
