#ifndef GENALG_POPULATION_HPP
#define GENALG_POPULATION_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

#include "operators/selection.hpp"
#include "population/individual.hpp"

namespace genalg {
    template<typename I, typename F>
    class Population {
    private:
        std::size_t size;
        std::vector<std::pair<I, F>> individuals;

    public:
        explicit Population(std::size_t s)
            : size{s} {}

        explicit Population(std::size_t s,
                            const population::IndividualFactory<I>& factory)
            : size{s} {
            for(int i = 0; i < this->size; ++i) {
                add(factory.make_individual());
            }
        }

        void add(const I& individual);

        inline const std::pair<I, F>& best(void) const;
        inline const std::pair<I, F>& worst(void) const;

        // operators
        std::pair<I, F>& operator[](int i);
    };
}

namespace genalg {
    template<typename I, typename F>
    void Population<I, F>::add(const I& individual) {
        assert(this->individuals.size() < this->size);

        // add individual and computed fitness
        this->individuals.push_back(std::make_pair(individual,
                                                   individual.fitness()));
    }

    template<typename I, typename F>
    const std::pair<I, F>& Population<I, F>::best() const {
        return *std::max_element(this->individuals.begin(),
                                 this->individuals.end(),
                                 [](const auto& lhs, const auto& rhs) {
                                     return lhs.second < rhs.second;
                                 });
    }

    template<typename I, typename F>
    const std::pair<I, F>& Population<I, F>::worst() const {
        return *std::min_element(this->individuals.begin(),
                                 this->individuals.end(),
                                 [](const auto& lhs, const auto& rhs) {
                                     return lhs.second < rhs.second;
                                 });
    }

    template<typename I, typename F>
    std::pair<I, F>& Population<I, F>::operator[](int i) {
        assert(i >= 0);
        return individuals[i];
    }
}

#endif
