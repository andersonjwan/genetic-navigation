#ifndef GENALG_POPULATION_HPP
#define GENALG_POPULATION_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <memory>
#include <numeric>
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
        explicit Population()
            : capacity{0} {}

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
        void add(const I& individual, F fitness);

        const F average(void) const;
        inline const std::pair<I, F>& best(void) const;
        inline const std::pair<I, F>& worst(void) const;

        const std::vector<std::pair<I, F>>& solutions() const { return this->individuals; }

        // operators
        std::size_t size() const { return this->individuals.size(); }

        Population<I, F>& operator=(const Population& population); // copy assignment

        const std::pair<I, F>& operator[](const int i) const;
        std::pair<I, F>& operator[](const int i);

    };
}

namespace genalg {
    template<typename I, typename F>
    void Population<I, F>::add(const I& individual) {
        assert(this->individuals.size() < this->capacity);

        // add individual and computed fitness
        this->individuals.push_back
            (std::make_pair(individual, individual.fitness()));
    }

    template<typename I, typename F>
    void Population<I, F>::add(const I& individual, F fitness) {
        assert(this->individuals.size() < this->capacity);

        // add individual and computed fitness
        this->individuals.push_back
            (std::make_pair(individual, fitness));
    }

    template<typename I, typename F>
    const F Population<I, F>::average() const {
        double sum = std::accumulate
            (this->individuals.begin(), this->individuals.end(), 0,
             [](double sum, const auto& op){
                return std::move(sum) + op.second;
            });

        return sum / (double)capacity;
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
    Population<I, F>& Population<I, F>::operator=(const Population& population) {
        this->capacity = population.size();

        this->individuals.clear();
        for(int i = 0; i < population.size(); ++i) {
            this->add(population[i].first, population[i].second);
        }

        return *this;
    }

    template<typename I, typename F>
    const std::pair<I, F>& Population<I, F>::operator[](int i) const {
        assert(i >= 0);
        return individuals[i];
    }

    template<typename I, typename F>
    std::pair<I, F>& Population<I, F>::operator[](int i) {
        assert(i >= 0);
        return individuals[i];
    }
}

#endif
