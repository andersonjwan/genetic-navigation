#ifndef GENALG_OPERATORS_SELECTION_HPP
#define GENALG_OPERATORS_SELECTION_HPP

#include <cstddef>
#include <map>

namespace genalg {
    namespace operators {
	template<typename T, typename F>
	class SelectionOperator {
	public:
	    virtual T select(std::map<T, F>) = 0;
	};

	template<typename T, typename F>
	class TournamentSelection : public SelectionOperator<T, F>{
	private:
	    std::size_t tournament_size;
	    double p = 0.5;

	public:
	    TournamentSelection<T, F>(std::size_t size)
		: tournament_size {size} {}

	    TournamentSelection<T, F>(std::size_t size, double prob)
		: tournament_size {size}, p {prob} {}

	    // virtual T select(std::map<T, F>) override;
	    T select(std::map<T, F>);
	};
    }
}

#include "operators/selection.tpp"
#endif
