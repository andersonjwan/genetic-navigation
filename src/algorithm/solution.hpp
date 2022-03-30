#ifndef GENALG_ALGORITHM_SOLUTION_HPP
#define GENALG_ALGORITHM_SOLUTION_HPP

#include <cassert>
#include <map>
#include <utility>

#include "population/individual.hpp"

namespace genalg {
    namespace algorithm {
	template<typename T, typename F>
	class SolutionSet {
	private:
	    std::map<population::Individual<T>, F> solutions;

	public:
	    SolutionSet(std::map<population::Individual<T>, F> s)
		: solutions{s} {}

	    std::pair<T, F> max();
	    std::pair<T, F> min();
	};
    }
}

namespace genalg {
    namespace algorithm {
	template<typename T, typename F>
	std::pair<T, F> SolutionSet<T, F>::max() {
	    assert(this->solutions.size() > 0);

	    std::pair<T, F> maximum =
		std::make_pair(solutions.begin()->first.genome,
			       solutions.begin()->second);

	    for(auto& it : this->solutions) {
		if(it.second > maximum.second) {
		    maximum = std::make_pair(it.first.genome, it.second);
		}
	    }

	    return maximum;
	}

	template<typename T, typename F>
	std::pair<T, F> SolutionSet<T, F>::min() {
	    assert(this->solutions.size() > 0);

	    std::pair<T, F> minimum =
		std::make_pair(solutions.begin()->first.genome,
			       solutions.begin()->second);

	    for(auto& it : this->solutions) {
		if(it.second < minimum.second) {
		    minimum = std::make_pair(it.first.genome, it.second);
		}
	    }

	    return minimum;
	}
    }
}

#endif
