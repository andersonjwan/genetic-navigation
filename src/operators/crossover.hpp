#ifndef GENALG_OPERATORS_CROSSOVER_HPP
#define GENALG_OPERATORS_CROSSOVER_HPP

namespace genalg {
    namespace operators {
        template<typename I>
        class CrossoverOperator {
        public:
            virtual std::array<I, 2> crossover(const I& p1, const I& p2) const = 0;
        };
    }
}

#endif
