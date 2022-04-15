#ifndef GENALG_POPULATION_INDIVIDUAL_HPP
#define GENALG_POPULATION_INDIVIDUAL_HPP

#include <cstddef>
#include <vector>

namespace genalg {
    namespace population {
        /// Base for GA individual representation.
        ///
        /// An individual has two main attributes: (1) the genome
        /// representation and (2) the fitness metric.
        ///
        /// @tparam G The genome
        /// @tparam F The metric used to evaluate the fitness of an individual
        template<typename G, typename F>
        class Individual {
        protected:
            G genome_;
            std::size_t age_ = 0;

        public:
            explicit Individual(const G& g)
                : genome_{g} {}

            G genome(void) const;
            virtual F fitness(void) const = 0;
        };

        /// Individual with a binary representation of a genome.
        ///
        /// The BinaryIndividual uses a vector of booleans to represent
        /// the genome/solution.
        class BinaryIndividual : public Individual<std::vector<bool>, double> {
        public:
            explicit BinaryIndividual(const std::vector<bool>& g)
                : Individual<std::vector<bool>, double>(g) {}

            double fitness() const override { return 0.0; }

        };

        template<typename I>
        class IndividualFactory {
        public:
            virtual I make_individual() const = 0;
        };
    }
}

namespace genalg {
    namespace population {
        /// Access the genome of the individual.
        ///
        /// @return A genome of type G
        template<typename G, typename F>
        G Individual<G, F>::genome(void) const { return this->genome_; }
    }
}

#endif
