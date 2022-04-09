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
        std::size_t capacity;
        std::vector<std::pair<I, F>> individuals;

    public:
        explicit Population(std::size_t s)
            : capacity{s} {}

        explicit Population(std::size_t s,
                            const population::IndividualFactory<I>& factory)
            : capacity{s} {
            for(int i = 0; i < this->capacity; ++i) {
                add(factory.make_individual());
            }
        }

        void add(const I& individual);

        inline const std::pair<I, F>& best(void) const;
        inline const std::pair<I, F>& worst(void) const;

        const std::vector<std::pair<I, F>>& solutions() const { return this->individuals; }

        // operators
        std::size_t size() const { return this->individuals.size(); }
        std::pair<I, F>& operator[](int i);
    };
}

namespace genalg {
    template<typename I, typename F>
    void Population<I, F>::add(const I& individual) {
        assert(this->individuals.size() < this->capacity);

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
