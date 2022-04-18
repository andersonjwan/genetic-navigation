#ifndef GENALG_POPULATION_INDIVIDUAL_HPP
#define GENALG_POPULATION_INDIVIDUAL_HPP

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
            G genome_;
            F fitness_;

        public:
            explicit Individual() {}
            explicit Individual(const G& g, const F& f)
                : genome_{g}, fitness_{f} {}

            // accessors
            const G& genome() const { return this->genome_; }
            const F& fitness() const { return this->fitness_; }

            // mutators
            void fitness(const F& fitness) {
                this->fitness_ = fitness;
            }

            // copy operations
            Individual(const Individual& other);
            Individual& operator=(const Individual& other);

            // operators
            bool operator<(const Individual<G, F>& other) const {
                return this->fitness_ < other.fitness_;
            }

            bool operator==(const Individual<G, F>& other) const {
                return this->genome_ == other.genome_ &&
                    this->fitness_ == other.fitness_;
            }
        };
    }
}

namespace genalg {
    namespace population {
        template<typename G, typename F>
        Individual<G, F>::Individual(const Individual& other)
            : genome_{other.genome_}, fitness_{other.fitness_} {}

        template<typename G, typename F>
        Individual<G, F>& Individual<G, F>::operator=(const Individual& other) {
            this->genome_ = other.genome_;
            this->fitness_ = other.fitness_;

            return *this;
        }
    }
}

#endif
