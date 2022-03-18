#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

namespace genalg {
    namespace operators {
	template<typename T, typename F>
	T TournamentSelection<T, F>::select(std::map<T, F> population) {
	    if(this->tournament_size > population.size()) {
		throw std::out_of_range("tournament size must be less than or equal to population size");
	    }

	    using competitor = std::pair<T, F>;

	    std::random_device rd;
	    std::mt19937 gen(rd());

	    std::vector<std::size_t> indices(population.size());
	    std::iota(indices.begin(), indices.end(), 0);

	    std::shuffle(indices.begin(), indices.end(), gen);

	    // select individuals to compete
	    auto cmp = [](competitor c1, competitor c2) { return c1.second < c2.second; };
	    std::priority_queue<competitor, std::vector<competitor>, decltype(cmp)> selections(cmp);

	    auto iter_begin = population.begin();
	    for(std::size_t i = 0; i < this->tournament_size; ++i) {
		auto iter = population.begin();
		std::advance(iter, indices[i]);

		auto sel = iter;
		selections.push(std::make_pair(sel->first, sel->second));
	    }

	    // select top two competitors
	    std::array<T, 2> matchup;
	    matchup[0] = (selections.top()).first;
	    selections.pop();
	    matchup[1] = (selections.top()).first;
	    selections.pop();

	    std::uniform_real_distribution<double> distr(0.0, 1.0);

	    if(distr(gen) <= this->p) {
		return matchup[0]; // return most fit
	    } else {
		return matchup[1]; // return second-most fit
	    }
	}
    }
}
