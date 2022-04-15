#ifndef GENALG_OPERATORS_MUTATION_HPP
#define GENALG_OPERATORS_MUTATION_HPP

#include <cassert>
#include <random>

namespace genalg {
    namespace operators {
        /// Interface for GA mutation operations.
        ///
        /// @tparam I An individual
        template<typename I>
        class MutationOperator {
        public:
            virtual I mutate(const I& individual,
                             std::default_random_engine& rng) const = 0;
        };

        /// Mutation operation to invert a specified number of bits.
        ///
        /// @tparam I An individual
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
        /// Mutate an individual by inverting its bits.
        ///
        /// The number of bits to flip is randomly selected from
        /// 1 to the size of the individual's genome.
        ///
        /// @param individual The individual to mutate
        /// @param rng The Random Number Generator engine
        /// @return A newly mutated individual
        template<typename I>
        I InversionMutation<I>::mutate(const I& individual,
                                       std::default_random_engine& rng) const {
            auto genome = individual.get_genome();
            assert(genome.size() == individual.get_genome().size());

            std::uniform_real_distribution<double> rdistr(0.0, 1.0);
            double inversion_chance = 1.0 / genome.size();

            for(int i = 0; i < genome.size(); ++i) {
                if(rdistr(rng) < inversion_chance) {
                    genome[i] = !(genome[i] == 1);
                }
            }

            return I(genome);
        }
    }
}
#endif
