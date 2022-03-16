#ifndef GENALGNAV_POPULATION_HPP
#define GENALGNAV_POPULATION_HPP

#include <cstdlib>
#include <vector>

#include "individual.hpp"

namespace genalg {
    template<typename T, typename F>
    class Population {
    private:
	std::vector<Individual<T>> individuals;

    public:
	const Individual<T>& select() const;
	F fitness(const T& genome);

	size_t size(void) {
	    return individuals.size();
	}
    };
}

#endif
