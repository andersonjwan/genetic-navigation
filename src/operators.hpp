#ifndef GENALG_OPERATORS_HPP
#define GENALG_OPERATORS_HPP

#include <array>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "operators/selection.hpp"
#include "operators/crossover.hpp"
#include "operators/mutation.hpp"

namespace genalg {
    template<typename I,
             typename F,
             typename S,
             typename C,
             typename M>
    class Operators {
    private:
        const S& selection;
        const C& crossover;
        const M& mutation;

    public:
        Operators(S& s, C& c, M& m)
            : selection{s}, crossover{c}, mutation{m} {}

        I select(const std::vector<std::pair<I, F>>& population) const;
        std::array<I, 2> cross(const I& p1, const I& p2) const;
        I mutate(const I& individual) const;
    };
}

namespace genalg {
    template<typename I,
             typename F,
             typename S,
             typename C,
             typename M>
    I Operators<I, F, S, C, M>::select(const std::vector<std::pair<I, F>> &population) const {
        return this->selection.select(population);
    }

    template<typename I,
             typename F,
             typename S,
             typename C,
             typename M>
    std::array<I, 2> Operators<I, F, S, C, M>::cross(const I &p1, const I &p2) const {
        return this->crossover.cross(p1, p2);
    }

    template<typename I,
             typename F,
             typename S,
             typename C,
             typename M>
    I Operators<I, F, S, C, M>::mutate(const I &individual) const {
        return this->mutation.mutate(individual);
    }
}

#endif
