#ifndef GENALG_POPULATION_HPP
#define GENALG_POPULATION_HPP

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
	Population(std::size_t s)
	    : size{s} {}

	void add(const I& individual);

	// operations
	const std::pair<I, F>& operator[](int i) const;
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
    const std::pair<I, F>& Population<I, F>::operator[](int i) const {
	assert(i >= 0);
	return individuals[i];
    }
}

#endif
