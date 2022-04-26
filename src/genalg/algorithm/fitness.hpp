#ifndef GENALG_ALGORITHM_FITNESS_HPP
#define GENALG_ALGORITHM_FITNESS_HPP

#include <functional>

namespace genalg {
    namespace algorithm {
        template<typename G, typename F>
        class FitnessFunction {
        private:
            std::function<F(const G&)> fn_;

        public:
            explicit FitnessFunction(std::function<F(const G& )> fn)
                : fn_{fn} {}

            F evaluate(const G& genome) const {
                return this->fn_(genome);
            }
        };

        template<typename G, typename F>
        class ZeroFitnessFunction : public FitnessFunction<G, F> {
        public:
            ZeroFitnessFunction()
                : FitnessFunction<G, F>([](const G& genome) { return 0; }) {}
        };
    }
}

#endif
