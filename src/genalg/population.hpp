#ifndef GENALG_POPULATION_HPP
#define GENALG_POPULATION_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <vector>

namespace genalg {
    /// A list of individuals.
    ///
    /// A \ref Population stores a set of potential solutions for a
    /// given generation and provides some functionality for statistics
    /// on said individuals.
    ///
    /// @tparam I An individual
    template<typename I>
    class Population {
    private:
        typedef std::vector<I> IndividualList;

        std::size_t capacity_;
        IndividualList individuals_;

    public:
        typedef typename IndividualList::iterator iterator;
        typedef typename IndividualList::const_iterator const_iterator;

        explicit Population()
            : capacity_{0} {}

        explicit Population(std::size_t capacity)
            : capacity_{capacity} {}

        // accessors
        std::size_t capacity() const { return this->capacity_; }
        const std::vector<I>& individuals() const { return this->individuals_; }

        void append(const I& individual);

        // statistics
        inline const I& best() const;
        inline const I& worst() const;

        // operations
        std::size_t size() const { return this->individuals_.size(); }

        iterator begin() { return this->individuals_.begin(); }
        iterator end() { return this->individuals_.end(); }
        const_iterator begin() const { return this->individuals_.begin(); }
        const_iterator end() const { return this->individuals_.end(); }
    };
}

namespace genalg {
    /// Append an individual to the population.
    ///
    /// @param individual A new individual to append to the \ref Population
    template<typename I>
    void Population<I>::append(const I& individual) {
        assert(this->size() < this->capacity_);

        // add individual to population
        this->individuals_.push_back(individual);
    }

    /// Find the best individual in the \ref Population.
    ///
    /// @return An individual with the best fitness
    template<typename I>
    const I& Population<I>::best() const {
        return *std::max_element
            (this->individuals_.begin(), this->individuals_.end());
    }

    /// Find the worst individual in the \ref Population.
    ///
    /// @return An individual with the worst fitness
    template<typename I>
    const I& Population<I>::worst() const {
        return *std::min_element
            (this->individuals_.begin(), this->individuals_.end());
    }
}

#endif
