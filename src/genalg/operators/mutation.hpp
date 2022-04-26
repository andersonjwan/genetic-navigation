#ifndef GENALG_OPERATORS_MUTATION_HPP
#define GENALG_OPERATORS_MUTATION_HPP

#include <cassert>
#include <random>

namespace genalg {
    namespace operators {
        /// Interface for Genetic Algorithm mutation operation.
        ///
        /// @tparam G A genome representation of an individual
        template<typename G>
        class MutationOperator {
        public:
            virtual G mutate(const G& genome,
                             std::default_random_engine& rng) const = 0;
        };

        /// Mutation operation to invert a specified number of bits.
        ///
        /// @tparam G A genome representation of an individual
        template<typename G>
        class BitFlipMutation : public MutationOperator<G> {
        private:
            const double p_inversion_;

        public:
            explicit BitFlipMutation(double p_inversion)
                : p_inversion_{p_inversion} {}

            G mutate(const G& genome,
                     std::default_random_engine& rng) const override;
        };
    }
}

namespace genalg {
    namespace operators {
        /// Mutate a genome by inverting its bits.
        ///
        /// The number of bits to flip is randomly selected from
        /// 1 to the size of the genome.
        ///
        /// @param genome The genome to mutate
        /// @param rng The random number generator engine
        /// @return A newly mutated genome
        template<typename G>
        G BitFlipMutation<G>::mutate(const G& genome,
                                       std::default_random_engine& rng) const {
            G mutated = genome;
            assert(mutated.size() == genome.size());

            std::uniform_real_distribution<double> rdistr(0.0, 1.0);

            for(int i = 0; i < mutated.size(); ++i) {
                if(rdistr(rng) < this->p_inversion_) {
                    mutated[i] = !(mutated[i] == 1);
                }
            }

            return mutated;
        }
    }
}
#endif
