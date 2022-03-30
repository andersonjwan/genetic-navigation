#ifndef GENALG_ALGORITHM_RESULT_HPP
#define GENALG_ALGORITHM_RESULT_HPP

#include <utility>
#include <vector>
#include "algorithm/solution.hpp"

namespace genalg {
    namespace algorithm {
	template<typename T, typename F>
	class Result {
	public:
	    Result(std::vector<SolutionSet<T, F>> g)
		: generations{g} {}

	    std::vector<SolutionSet<T, F>> generations;

	    std::vector<std::pair<T, F>> max_per_generation();
	    std::vector<std::pair<T, F>> min_per_generation();
	};
    }
}

namespace genalg {
    namespace algorithm {
	template<typename T, typename F>
        std::vector<std::pair<T, F>> Result<T, F>::max_per_generation() {
	    std::vector<std::pair<T, F>> maximums;

	    for(auto& g : generations) {
		maximums.push_back(g.max());
	    }

	    return maximums;
	}

	template<typename T, typename F>
        std::vector<std::pair<T, F>> Result<T, F>::min_per_generation() {
	    std::vector<std::pair<T, F>> minimums;

	    for(auto& g : generations) {
		minimums.push_back(g.min());
	    }

	    return minimums;
	}
    }
}

#endif
