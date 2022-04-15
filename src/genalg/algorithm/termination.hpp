#ifndef GENALG_ALGORITHM_TERMINATION_HPP
#define GENALG_ALGORITHM_TERMINATION_HPP

#include <cstddef>
#include <utility>
#include <vector>

#include "population.hpp"

namespace genalg {
    namespace algorithm {
        /// Interface for a terminating the Genetic Algorithm (GA).
        ///
        /// @tparam I An individual
        /// @tparam F the metric used to evaluate fitness
        template<typename I, typename F>
        class TerminationCondition {
        public:
            virtual bool terminate(const Population<I, F>& population) = 0;
        };

        /// Termination condition for GA based on the generation count.
        ///
        /// The GA will terminate after the defined generation limit is
        /// reached.
        ///
        /// @tparam I An individual
        /// @tparam F the metric used to evaluate fitness
        template<typename I, typename F>
        class GenerationLimit : public TerminationCondition<I, F> {
        private:
            const std::size_t limit_;
            std::size_t current_;

        public:
            explicit GenerationLimit(std::size_t l)
                : limit_{l}, current_{0} {}

            bool terminate(const Population<I, F>& population) override;
        };

        /// Termination condition for GA based on the best fitness count.
        ///
        /// The GA will terminate after seeing the best fitness not change for
        /// a defined amount.
        ///
        /// @tparam I An individual
        /// @tparam F the metric used to evaluate fitness
        template<typename I, typename F>
        class BestLimit : public TerminationCondition<I, F> {
        private:
            const std::size_t limit_;
            std::size_t current_;
            F best_;

        public:
            explicit BestLimit(std::size_t l)
                : limit_{l}, current_{0} {}

            bool terminate(const Population<I, F>& population) override;
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
        template<typename I, typename F>
        bool GenerationLimit<I, F>::terminate(const Population<I, F>& population) {
            this->current_++;
            return this->current_ >= (this->limit_ - 1);
        }

        /// Check if the best limit has been reached.
        ///
        /// The \ref BestLimit keeps track of how many times in a row
        /// the best fitness has remained unchanged.
        ///
        /// @param population The latest \ref Population
        /// @return To terminate or not
        template<typename I, typename F>
        bool BestLimit<I, F>::terminate(const Population<I, F>& population) {
            if(this->current_ == 0) {
                this->best_ = population.best().second;
            }

            if(this->best_ == population.best().second) {
                this->current_++;
            } else {
                this->current_ = 0;
            }

            return this->current_ >= (this->limit_ - 1);
        }
    }
}

#endif
