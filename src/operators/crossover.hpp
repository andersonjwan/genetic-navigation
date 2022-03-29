#ifndef GENALG_OPERATORS_CROSSOVER_HPP
#define GENALG_OPERATORS_CROSSOVER_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <random>
#include <utility>
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

	template<typename T>
	class MultiPointCrossover : public CrossoverOperator<T> {
	private:
	    std::size_t n_points;

	public:
	    MultiPointCrossover(std::size_t n)
		: n_points {n} { assert(n_points > 0); }

	    virtual std::array<T, 2> crossover(const T& p1, const T& p2) override;
	};
    }
}

namespace genalg {
    namespace operators {
	template<typename T>
	std::array<T, 2> SinglePointCrossover<T>::crossover(const T& p1, const T& p2) {
	    assert(p1.size() == p2.size());

	    std::random_device rd;
	    std::mt19937 gen(rd());
	    std::uniform_int_distribution<int> distr(1, p1.size());

	    int index = distr(gen);

	    T child_genome1(p1);
	    T child_genome2(p2);

	    for(int i = index; i < child_genome1.size(); ++i) {
		std::swap(child_genome1[i], child_genome2[i]);
	    }

	    return std::array<T, 2> {child_genome1, child_genome2};
	}

	template<typename T>
	std::array<T, 2> MultiPointCrossover<T>::crossover(const T& p1, const T& p2) {
	    assert(p1.size() == p2.size());
	    assert(this->n_points <= p1.size());

	    std::random_device rd;
	    std::mt19937 gen(rd());

	    std::vector<std::size_t> indices(p1.size() - 1);
	    std::iota(indices.begin(), indices.end(), 1);

	    std::shuffle(indices.begin(), indices.end(), gen);

	    std::vector<std::size_t> points(this->n_points);
	    for(int i = 0; i < this->n_points; ++i) {
		points[i] = indices[i];
	    }

	    T child_genome1(p1);
	    T child_genome2(p2);

	    std::sort(points.begin(), points.end());
	    for(int i = 0; i < points.size(); ++i) {
		for(int j = points[i]; j < child_genome1.size(); ++j) {
		    std::swap(child_genome1[j], child_genome2[j]);
		}
	    }

	    return std::array<T, 2> {child_genome1, child_genome2};
	}
    }
}

#endif
