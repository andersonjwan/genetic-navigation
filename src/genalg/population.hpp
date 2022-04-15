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
    /// A collection of individuals and their associated fitness.
    ///
    /// A \ref Population stores a set of potential solutions for a
    /// given generation and provides some functionality for statistics
    /// on said individuals.
    ///
    /// @tparam I An individual
    /// @tparam F The metric used to evaluate the fitness of an individual
    template<typename I, typename F>
    class Population {
    private:
        const std::size_t capacity_;
        std::vector<std::pair<I, F>> individuals_;

    public:
        explicit Population()
            : capacity_{0} {}

        explicit Population(std::size_t s)
            : capacity_{s} {}

        explicit Population(std::size_t s,
                            const population::IndividualFactory<I>& factory)
            : capacity_{s} {
            for(int i = 0; i < this->capacity; ++i) {
                this->add(factory.make_individual());
            }
        }

        // accessors
        std::size_t capacity() const { return this->capacity_; }
        const std::vector<std::pair<I, F>>& individuals() const { return this->individuals_; }

        void add(const I& individual);
        void add(const I& individual, const F& fitness);

        const F average(void) const;
        inline const std::pair<I, F>& best(void) const;
        inline const std::pair<I, F>& worst(void) const;

        // operators
        std::size_t size() const { return this->individuals_.size(); }

        Population<I, F>& operator=(const Population& population); // copy assignment
        const std::pair<I, F>& operator[](const int i) const;
        std::pair<I, F>& operator[](const int i);

    };
}

namespace genalg {
    /// Add an individual and calculate the individuals fitness.
    ///
    /// @param individual A new individual to add to the \ref Population
    template<typename I, typename F>
    void Population<I, F>::add(const I& individual) {
        assert(this->individuals_.size() < this->capacity_);

        // add individual and computed fitness
        this->individuals_.push_back
            (std::make_pair(individual, individual.fitness()));
    }

    /// Add an individual and its explictly associated fitness.
    ///
    /// @param individual A new individual to add to the \ref Population
    /// @param fitness The fitness of the new individual
    template<typename I, typename F>
    void Population<I, F>::add(const I& individual, const F& fitness) {
        assert(this->individuals_.size() < this->capacity_);

        // add individual and computed fitness
        this->individuals_.push_back
            (std::make_pair(individual, fitness));
    }

    /// Calculate the average fitness of the \ref Population.
    ///
    /// @return The average fitness as denoted by the F template parameter
    template<typename I, typename F>
    const F Population<I, F>::average() const {
        double sum = std::accumulate
            (this->individuals_.begin(), this->individuals_.end(), 0,
             [](double sum, const auto& op){
                return std::move(sum) + op.second;
            });

        return sum / (double)this->capacity_;
    }

    /// Find the best individual, fitness pair in the \ref Population.
    ///
    /// @return An individual/fitness pair with the best fitness
    template<typename I, typename F>
    const std::pair<I, F>& Population<I, F>::best() const {
        return *std::max_element(this->individuals_.begin(),
                                 this->individuals_.end(),
                                 [](const auto& lhs, const auto& rhs) {
                                     return lhs.second < rhs.second;
                                 });
    }

    /// Find the worst individual, fitness pair in the \ref Population.
    ///
    /// @return An individual/fitness pair with the worst fitness
    template<typename I, typename F>
    const std::pair<I, F>& Population<I, F>::worst() const {
        return *std::min_element(this->individuals_.begin(),
                                 this->individuals_.end(),
                                 [](const auto& lhs, const auto& rhs) {
                                     return lhs.second < rhs.second;
                                 });
    }

    /// Copy assignment of a \ref Population.
    ///
    /// @return The newly copied \ref Population
    template<typename I, typename F>
    Population<I, F>& Population<I, F>::operator=(const Population& population) {
        this->capacity_ = population.size();

        this->individuals_.clear();
        for(int i = 0; i < population.size(); ++i) {
            this->add(population[i].first, population[i].second);
        }

        return *this;
    }

    /// Accessor to an individual, fitness pair in the \ref Population.
    ///
    /// Used primarily for read instructions.
    ///
    /// @param i The index of the \ref Population.
    /// @return If in range, returns the individual, fitness pair.
    template<typename I, typename F>
    const std::pair<I, F>& Population<I, F>::operator[](int i) const {
        assert(i >= 0);
        return this->individuals_[i];
    }

    /// Accessor to an individual, fitness pair in the \ref Population.
    ///
    /// Used primarily for write instructions.
    ///
    /// @param i The index of the \ref Population.
    /// @return If in range, returns the individual, fitness pair.
    template<typename I, typename F>
    std::pair<I, F>& Population<I, F>::operator[](int i) {
        assert(i >= 0);
        return this->individuals_[i];
    }
}

#endif
