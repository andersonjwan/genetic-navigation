#ifndef GENALG_OPERATORS_CROSSOVER_HPP
#define GENALG_OPERATORS_CROSSOVER_HPP

#include <array>
#include <cassert>
#include <cstddef>
#include <vector>

namespace genalg {
    namespace operators {
	template<typename T>
	class CrossoverOperator {
	public:
	    virtual std::array<T, 2> crossover(const T& p1, const T& p2) = 0;
	};

	template<typename T>
	class SinglePointCrossover : public CrossoverOperator<T> {
	public:
	    virtual std::array<T, 2> crossover(const T& p1, const T& p2) override;
	};
    }
}

#include "crossover.tpp"
#endif
