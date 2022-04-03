#ifndef GENALG_OPERATORS_CROSSOVER_HPP
#define GENALG_OPERATORS_CROSSOVER_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <vector>

namespace genalg {
    namespace operators {
        template<typename I>
        class CrossoverOperator {
        public:
            virtual std::array<I, 2> cross(const I& p1, const I& p2) const = 0;
        };

        template<typename I, typename R>
        class MultiPointCrossover : public CrossoverOperator<I> {
        private:
            R& rng;
            std::size_t n_points;

        public:
            MultiPointCrossover(R& r, std::size_t n)
                : rng{r}, n_points{n} {}

            std::array<I, 2> cross(const I& p1, const I& p2) const override;
        };

        template<typename I, typename R>
        class SinglePointCrossover : public MultiPointCrossover<I, R> {
        public:
            SinglePointCrossover(R& r)
                : MultiPointCrossover<I, R>(r, 1) {}

            std::array<I, 2> cross(const I& p1, const I& p2) const override {
                MultiPointCrossover<I, R>::crossover(p1, p2);
            }
        };
    }
}

namespace genalg {
    namespace operators {
        template<typename I, typename R>
        std::array<I, 2> MultiPointCrossover<I, R>::cross(const I &p1, const I &p2) const {
            assert(p1.get_genome().size() == p2.get_genome().size());
            assert(this->n_points <= p1.get_genome().size());

            auto genome1 = p1.get_genome();
            auto genome2 = p2.get_genome();

            std::vector<std::size_t> indexes(p1.get_genome().size() - 1);
            std::iota(indexes.begin(), indexes.end(), 1);

            std::vector<std::size_t> points(this->n_points);
            std::sample(indexes.begin(), indexes.end(),
                        std::back_inserter(points), this->n_points, this->rng);

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
