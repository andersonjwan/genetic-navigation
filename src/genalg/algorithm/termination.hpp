#ifndef GENALG_ALGORITHM_TERMINATION_HPP
#define GENALG_ALGORITHM_TERMINATION_HPP

#include <cstddef>
#include <utility>
#include <vector>

namespace genalg {
    namespace algorithm {
        template<typename I, typename F>
        class TerminationCondition {
        public:
            virtual bool terminate(std::vector<std::pair<I, F>>& population) = 0;
        };

        template<typename I, typename F>
        class GenerationLimit : public TerminationCondition<I, F> {
        private:
            std::size_t limit;
            std::size_t current = 0;

        public:
            GenerationLimit(std::size_t l)
                : limit{l} {}

            bool terminate(std::vector<std::pair<I, F>>& population) override;
        };
    }
}

namespace genalg {
    namespace algorithm {
        template<typename I, typename F>
        bool GenerationLimit<I, F>::terminate(std::vector<std::pair<I, F>>& population) {
            this->current++;
            return this->current >= this->limit;
        }
    }
}

#endif
