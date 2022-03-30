#ifndef GENALG_OPERATORS_SELECTION_HPP
#define GENALG_OPERATORS_SELECTION_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <map>
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
	class SelectionOperator {
	public:
	    virtual T select(std::map<T, F>) = 0;
	};

	template<typename R, typename T, typename F>
	class TournamentSelection : public SelectionOperator<T, F>{
	private:
	    R rng;

	    std::size_t tournament_size;
	    double p = 0.5;

	public:
	    TournamentSelection<R, T, F>(R r, std::size_t size)
		: rng{r}, tournament_size{size} {}

	    TournamentSelection<R, T, F>(R r, std::size_t size, double prob)
		: rng{r}, tournament_size{size}, p{prob} {}

	    virtual T select(std::map<T, F>) override;
	};
    }
}

namespace genalg {
    namespace operators {
	template<typename R, typename T, typename F>
	T TournamentSelection<R, T, F>::select(std::map<T, F> population) {
	    if(this->tournament_size > population.size()) {
		throw std::out_of_range("tournament size must be less than or equal to population size");
	    }

	    using competitor = std::pair<T, F>;

	    std::vector<std::size_t> indices(population.size());
	    std::iota(indices.begin(), indices.end(), 0);

	    std::shuffle(indices.begin(), indices.end(), rng);

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
	    T c1 = (selections.top()).first;
	    selections.pop();
	    T c2 = (selections.top()).first;
	    selections.pop();

	    std::array<T, 2> matchup = {c1, c2};

	    std::uniform_real_distribution<double> distr(0.0, 1.0);

	    if(distr(rng) <= this->p) {
		return matchup[0]; // return most fit
	    } else {
		return matchup[1]; // return second-most fit
	    }
	}
    }
}

#endif
