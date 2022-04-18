#ifndef GENALG_ALGORITHM_FITNESS_HPP
#define GENALG_ALGORITHM_FITNESS_HPP

namespace genalg {
    namespace algorithm {
        template<typename G, typename F>
        class FitnessFunction {
        public:
            virtual inline F evaluate(const G& genome) const = 0;
        };
    }
}

#endif
