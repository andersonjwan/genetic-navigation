#ifndef GENALG_OPERATORS_MUTATION_HPP
#define GENALG_OPERATORS_MUTATION_HPP

namespace genalg {
    namespace operators {
        template<typename I>
        class MutationOperator {
        public:
            virtual I mutate(const I& individual) const = 0;
        };
    }
}

#endif
