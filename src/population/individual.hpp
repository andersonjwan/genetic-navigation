#ifndef GENALG_POPULATION_INDIVIDUAL_HPP
#define GENALG_POPULATION_INDIVIDUAL_HPP

#include <cstddef>
#include <vector>

namespace genalg {
    namespace population {
        template<typename G, typename F>
        class Individual {
        protected:
            G genome;
            std::size_t age = 0;

        public:
            explicit Individual(const G& g)
                : genome{g} {}

            G get_genome(void) const;
            virtual F fitness(void) const = 0;
        };

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
        template<typename G, typename F>
        G Individual<G, F>::get_genome(void) const { return this->genome; }
    }
}

#endif
