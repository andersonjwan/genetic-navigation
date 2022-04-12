#ifndef GENALG_OPERATORS_MUTATION_HPP
#define GENALG_OPERATORS_MUTATION_HPP

#include <cassert>
#include <random>

namespace genalg {
    namespace operators {
        template<typename I>
        class MutationOperator {
        public:
            virtual I mutate(const I& individual,
                             std::default_random_engine& rng) const = 0;
        };

        template<typename I>
        class InversionMutation : public MutationOperator<I> {
        public:
            I mutate(const I& individual,
                     std::default_random_engine& rng) const override;
        };
    }
}

namespace genalg {
    namespace operators {
        template<typename I>
        I InversionMutation<I>::mutate(const I& individual,
                                       std::default_random_engine& rng) const {
            auto mutated = individual.get_genome();
            assert(mutated.size() == individual.get_genome().size());

            std::uniform_real_distribution<double> rdistr(0.0, 1.0);
            double inversion_chance = 1.0 / mutated.size();

            for(int i = 0; i < mutated.size(); ++i) {
                if(rdistr(rng) < inversion_chance) {
                    mutated[i] = !(mutated[i] == 1);
                }
            }

            return I(mutated);
        }
    }
}
#endif
