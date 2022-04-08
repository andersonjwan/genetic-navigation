#ifndef GENALG_OPERATORS_CROSSOVER_HPP
#define GENALG_OPERATORS_CROSSOVER_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <random>
#include <numeric>
#include <vector>

namespace genalg {
    namespace operators {
        template<typename I>
        class CrossoverOperator {
        public:
            virtual std::array<I, 2> cross(const I& p1, const I& p2,
                                           std::default_random_engine& rng) const = 0;
        };

        template<typename I>
        class MultiPointCrossover : public CrossoverOperator<I> {
        private:
            std::size_t n_crossovers;

        public:
            explicit MultiPointCrossover(std::size_t n)
                : n_crossovers{n} {}

            std::array<I, 2> cross(const I& p1, const I& p2,
                                   std::default_random_engine& rng) const override;
        };

        template<typename I>
        class SinglePointCrossover : public MultiPointCrossover<I> {
        public:
            SinglePointCrossover()
                : MultiPointCrossover<I>(1) {}

            std::array<I, 2> cross(const I& p1, const I& p2,
                                   std::default_random_engine& rng) const override {
                return MultiPointCrossover<I>::cross(p1, p2, rng);
            }
        };
    }
}

namespace genalg {
    namespace operators {
        template<typename I>
        std::array<I, 2> MultiPointCrossover<I>::cross(const I &p1, const I &p2,
                                                       std::default_random_engine& rng) const {
            assert(p1.get_genome().size() == p2.get_genome().size());
            assert(this->n_crossovers <= p1.get_genome().size());

            auto genome1 = p1.get_genome();
            auto genome2 = p2.get_genome();

            std::vector<std::size_t> indexes(p1.get_genome().size() - 1);
            std::iota(indexes.begin(), indexes.end(), 1);

            std::vector<std::size_t> points;
            std::sample(indexes.begin(), indexes.end(),
                        std::back_inserter(points), this->n_crossovers, rng);

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
