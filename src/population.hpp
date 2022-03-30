#ifndef GENALG_POPULATION_HPP
#define GENALG_POPULATION_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

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

	void add(const I& individual);

	// analytics
	const std::pair<I, F>& best(void) const;
	const std::pair<I, F>& worst(void) const;

	// operations
	const std::pair<I, F>& operator[](int i) const;

	// custom comparators
	static
	bool _cmp_individuals(const std::pair<I, F>& lhs,
			      const std::pair<I, F>& rhs);
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
				 Population<I, F>::_cmp_individuals);
    }

    template<typename I, typename F>
    const std::pair<I, F>& Population<I, F>::worst() const {
	return *std::min_element(this->individuals.begin(),
				 this->individuals.end(),
				 Population<I, F>::_cmp_individuals);
    }

    template<typename I, typename F>
    const std::pair<I, F>& Population<I, F>::operator[](int i) const {
	assert(i >= 0);
	return individuals[i];
    }

    template<typename I, typename F>
    bool Population<I, F>::_cmp_individuals(const std::pair<I, F>& lhs,
						  const std::pair<I, F>& rhs) {
	return lhs.second < rhs.second;
    }
}

#endif
