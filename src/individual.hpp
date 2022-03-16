#ifndef GENALGNAV_INDIVIDUAL_HPP
#define GENALGNAV_INDIVIDUAL_HPP

#include <array>
#include <memory>

namespace genalg {
    template <typename T>
    class Individual {
    private:
	std::unique_ptr<T> genome;

    public:
	std::array<Individual<T>, 2> crossover(const Individual<T>& other) const;
	void mutate(void);
    };
}

#endif
