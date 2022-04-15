#ifndef GENALG_ALGORITHM_TERMINATION_HPP
#define GENALG_ALGORITHM_TERMINATION_HPP

#include <cstddef>
#include <utility>
#include <vector>

namespace genalg {
    namespace algorithm {
        /// Interface for a terminating the Genetic Algorithm (GA).
        ///
        /// @tparam I An individual
        /// @tparam F the metric used to evaluate fitness
        template<typename I, typename F>
        class TerminationCondition {
        public:
            virtual bool terminate(const std::vector<std::pair<I, F>>& population) = 0;
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

            bool terminate(const std::vector<std::pair<I, F>>& population) override;
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
        bool GenerationLimit<I, F>::terminate(const std::vector<std::pair<I, F>>& population) {
            this->current_++;
            return this->current_ >= (this->limit_ - 1);
        }
    }
}

#endif
