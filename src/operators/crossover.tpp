#include <array>
#include <cassert>
#include <random>
#include <utility>

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
    }
}
