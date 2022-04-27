#ifndef GENALG_OPERATORS_CROSSOVER_HPP
#define GENALG_OPERATORS_CROSSOVER_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <random>
#include <vector>

namespace genalg {
    namespace operators {
        /// Interface for Genetic Algorithm crossover (recombination) operation.
        ///
        /// @tparam G A genome representation of an individual
        template<typename G>
        class CrossoverOperator {
        public:
            virtual std::array<G, 2> cross(const G& g1, const G& g2,
                                           std::default_random_engine& rng) const = 0;
        };

        /// Recombination technique for crossing over at multiple points.
        ///
        /// The std::swap function is used for crossing over genes. Therefore,
        /// the selected representation of a genome should be supported
        /// through the swap function.
        ///
        /// @tparam G A genome representation of an individual
        template<typename G>
        class MultiPointCrossover : public CrossoverOperator<G> {
        private:
            const std::size_t n_crossovers_;
            const std::size_t gene_size_;

        public:
            explicit MultiPointCrossover(std::size_t n_crossovers, std::size_t gene_size=1)
                : n_crossovers_{n_crossovers}, gene_size_{gene_size} {}

            std::array<G, 2> cross(const G& g1, const G& g2,
                                   std::default_random_engine& rng) const override;
        };

        /// Recombination technique for crossing over at a single point.
        ///
        /// This technique is a specialization of the \ref MultiPointCrossover
        /// method with a single point of crossover.
        ///
        /// @tparam G A genome representation of an individual
        template<typename G>
        class SinglePointCrossover : public MultiPointCrossover<G> {
        public:
            explicit SinglePointCrossover(std::size_t gene_size=1)
                : MultiPointCrossover<G>(1, gene_size) {}

            /// Cross two individuals using single point crossover technique.
            ///
            /// @param g1 The first genome
            /// @param g2 The second genome
            /// @param rng A random number generator engine
            /// @return Two newly crossed genomes
            std::array<G, 2> cross(const G& g1, const G& g2,
                                   std::default_random_engine& rng) const override {
                return MultiPointCrossover<G>::cross(g1, g2, rng);
            }
        };
    }
}

namespace genalg {
    namespace operators {
        /// Cross two individuals using multi-point crossover technique.
        ///
        /// @param g1 The first genome
        /// @param g2 The second genome
        /// @param rng A random number generator engine
        /// @return Two newly crossed genomes
        template<typename G>
        std::array<G, 2> MultiPointCrossover<G>::cross(const G &g1, const G &g2,
                                                       std::default_random_engine& rng) const {
            assert(g1.size() % this->gene_size_ == 0);
            assert(g1.size() == g2.size());
            assert(this->n_crossovers_ <= g1.size());

            G genome1 = g1;
            G genome2 = g2;

            std::vector<std::size_t> indexes(g1.size() / this->gene_size_);
            for(int i = 0; i < indexes.size(); ++i) {
                indexes[i] = i * this->gene_size_;
            }

            std::vector<std::size_t> crossovers;
            std::sample(indexes.begin(), indexes.end(),
                        std::back_inserter(crossovers), this->n_crossovers_, rng);

            std::sort(crossovers.begin(), crossovers.end());

            for(int i = 0; i < crossovers.size(); ++i) {
                for(int j = crossovers[i]; j < genome1.size(); ++j) {
                    auto gene1 = genome1[j];
                    auto gene2 = genome2[j];

                    std::swap(gene1, gene2);
                }
            }

            return std::array<G, 2> {
                genome1,
                genome2
            };
        }
    }
}

#endif
