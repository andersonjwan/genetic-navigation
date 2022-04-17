#ifndef GENALG_POPULATION_INDIVIDUAL_HPP
#define GENALG_POPULATION_INDIVIDUAL_HPP

#include <cstddef>
#include <vector>

namespace genalg {
    namespace population {
        /// Base representation of a solution within the GA.
        ///
        /// An \ref Individual has two main attributes: (1) the genome
        /// representation and (2) the fitness metric.
        ///
        /// @tparam G The genome
        /// @tparam F The metric used to evaluate the fitness of an individual
        template<typename G, typename F>
        class Individual {
        protected:
            const G genome_;
            F fitness_;

        public:
            explicit Individual(const G& g, const F& f)
                : genome_{g}, fitness_{f} {}

            // accessors
            const G& genome() const { return this->genome_; }
            const F& fitness() const { return this->fitness_; }

            // mutators
            void fitness(const F& fitness) {
                this->fitness_ = fitness;
            }
        };
    }
}

#endif
