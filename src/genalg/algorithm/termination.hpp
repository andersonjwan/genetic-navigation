#ifndef GENALG_ALGORITHM_TERMINATION_HPP
#define GENALG_ALGORITHM_TERMINATION_HPP

#include <cstddef>
#include "population.hpp"

namespace genalg {
    namespace algorithm {
        /// Interface for a terminating the Genetic Algorithm.
        ///
        /// @tparam I An individual
        template<typename I>
        class TerminationCondition {
        public:
            virtual bool terminate(const Population<I>& population) = 0;
        };

        /// Termination condition for Genetic Algorithm based on the generation count.
        ///
        /// The Genetic Algorithm will terminate after the specified generation
        /// limit is reached.
        ///
        /// @tparam I An individual
        template<typename I>
        class GenerationLimit : public TerminationCondition<I> {
        private:
            const std::size_t limit_;
            std::size_t current_;

        public:
            explicit GenerationLimit(std::size_t l)
                : limit_{l}, current_{0} {}

            bool terminate(const Population<I>& population) override;
        };

        /// Termination condition for Genetic Algorithm based on the best fitness.
        ///
        /// The Genetic Algorithm will terminate after seeing the best solution
        /// plateau for a specified number of generations.
        ///
        /// @tparam I An individual
        template<typename I>
        class BestLimit : public TerminationCondition<I> {
        private:
            const std::size_t limit_;
            std::size_t current_;
            I fittest_;

        public:
            explicit BestLimit(std::size_t l)
                : limit_{l}, current_{0} {}

            bool terminate(const Population<I>& population) override;
        };
    }
}

namespace genalg {
    namespace algorithm {
        /// Check if the generation limit has been reached.
        ///
        /// The \ref GenerationLimit keeps track of the total number
        /// of generations and checks at each episode whether that limit
        /// has been reached. If so, it returns True.
        ///
        /// @param population The latest \ref Population
        /// @return To terminate or not
        template<typename I>
        bool GenerationLimit<I>::terminate(const Population<I>& population) {
            this->current_++;
            return this->current_ >= (this->limit_ - 1);
        }

        /// Check if the fittest individual has plateaued.
        ///
        /// The \ref BestLimit keeps track of how many sequential occurrences
        /// the fittest individual has remained unchanged.
        ///
        /// @param population The latest \ref Population
        /// @return To terminate or not
        template<typename I>
        bool BestLimit<I>::terminate(const Population<I>& population) {
            if(this->current_ == 0) {
                this->fittest_ = population.best();
            }

            if(this->fittest_ == population.best()) {
                this->current_++;
            } else {
                this->current_ = 0;
            }

            return this->current_ >= (this->limit_ - 1);
        }
    }
}

#endif
