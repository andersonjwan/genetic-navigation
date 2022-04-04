#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "genalgorithm.hpp"

#include "options.hpp"
#include "algorithm/result.hpp"
#include "algorithm/termination.hpp"

#include "population/individual.hpp"

using genalg::Options;
using genalg::Operators;
using genalg::algorithm::GenerationLimit;

using genalg::operators::TournamentSelection;
using genalg::operators::MultiPointCrossover;
using genalg::operators::MutationOperator;

using genalg::population::Individual;
using genalg::population::IndividualFactory;

using Genome = std::vector<int>;
using Fitness = double;

#define POPULATION_SIZE 25
// #define PLOT

#ifdef PLOT
#include <matplot/matplot.h>
#endif

class Species : public Individual<Genome, Fitness> {
public:
    static std::size_t length;

    Species(Genome g)
        : Individual<Genome, Fitness>(g) {}

    std::size_t size() const { return this->genome.size(); }

    double decimal() const {
        int sign = this->genome[0];

        double value = 0;
        int i = 0;

        for(auto iter = this->genome.rbegin(); iter != this->genome.rend() + 1; ++iter) {
            value += std::pow(2, i) * (*iter);
            ++i;
        }

        double max = 0;
        for(int i = 1; i < this->genome.size(); ++i) {
            max += std::pow(2, i);
        }

        if(sign) {
            return -((value / max) * 10.0);
        } else {
            return (value / max) * 10.0;
        }
    }


    Fitness fitness(void) const override {
        double x = this->decimal();
        return std::sin(x) - 0.2 * std::abs(x);
    }
};

std::size_t Species::length = 10;

template<typename R>
class SpeciesFactory : public IndividualFactory<Species> {
private:
    R& rng;

public:
    SpeciesFactory(R& r)
        : rng{r} {}

    Species make_individual(void) const override {
        std::uniform_int_distribution<int> idistr(0, 1);
        Genome genome;

        for(int i = 0; i < Species::length; ++i) {
            genome.push_back(idistr(this->rng));
        }

        return Species(genome);
    }
};


template<typename R>
class MutationOperation : public MutationOperator<Species> {
private:
    R& rng;

public:
    MutationOperation(R& r)
        : rng{r} {}

    Species mutate(const Species& individual) const {
        std::uniform_int_distribution<int> idistr(1, individual.size());
        Genome mutated;

        for(auto& x : individual.get_genome()) {
            mutated.push_back(x);
        }

        std::vector<int> indices(individual.size());
        std::iota(indices.begin(), indices.end(), 0);

        std::vector<int> genes;

        std::sample(indices.begin(), indices.end(),
                    std::back_inserter(genes), idistr(this->rng), this->rng);

        for(int i = 0; i < genes.size(); ++i) {
            if(mutated[genes[i]] == 0) {
                mutated[genes[i]] = 1;
            } else {
                mutated[genes[i]] = 0;
            }
        }

        return mutated;
    }
};

int
main(int argc, char **argv) {
    std::unique_ptr<std::mt19937> rng;

    if(argc == 2) {
        rng = std::make_unique<std::mt19937>(std::stoi(argv[1]));
    } else {
        std::random_device rd;
        rng = std::make_unique<std::mt19937>(rd());
    }

    Options options(50, 50, 0.01);
    SpeciesFactory<std::mt19937> generator(*rng);
    GenerationLimit<Species, Fitness> termination(options.n_generations);

    TournamentSelection<Species, Fitness, std::mt19937> selection(*rng, 2, 1.0);
    MultiPointCrossover<Species, std::mt19937> crossover(*rng, 2);
    MutationOperation<std::mt19937> mutation(*rng);

    Operators<Species,
              Fitness,
              TournamentSelection<Species, Fitness, std::mt19937>,
              MultiPointCrossover<Species, std::mt19937>,
              MutationOperation<std::mt19937>>
        operators(selection, crossover, mutation);

    auto res = genalg::genalgorithm<Species,
                                    Fitness,
                                    SpeciesFactory<std::mt19937>,
                                    TournamentSelection<Species, Fitness, std::mt19937>,
                                    MultiPointCrossover<Species, std::mt19937>,
                                    MutationOperation<std::mt19937>,
                                    GenerationLimit<Species, Fitness>,
                                    std::mt19937>
        (options, operators, generator, termination, *rng);

    int i = 1;
    for(auto& x : res.best()) {
        std::cout << "GENERATION "
                  << std::setw(3) << std::setfill('0') << i << " BEST: "
                  << "(" << x.first.decimal() << ", " << x.second << ")\n";
        ++i;
    }

#ifdef PLOT
    std::vector<double> x(options.n_generations);
    std::iota(x.begin(), x.end(), 0);

    std::vector<double> best;
    std::vector<double> worst;

    for(auto& b : res.best()) {
        best.push_back(b.second);
    }

    for(auto& w : res.worst()) {
        worst.push_back(w.second);
    }

    matplot::plot(x, best);
    matplot::hold(matplot::on);

    matplot::plot(x, worst);
    matplot::hold(matplot::off);

    matplot::save("img/fitness", "svg");

    for(int i = 0; i < options.n_generations; ++i) {
        matplot::fplot([](double x) { return std::sin(x) - 0.2 * std::abs(x); },
                       std::array<double, 2>{-10.0, 10.0});
        matplot::hold(matplot::on);

        for(int j = 0; j < options.population_size; ++j) {
            matplot::plot({((res[i])[j]).first.decimal()}, {((res[i])[j]).second}, ".");
        }

        std::ostringstream ss;
        ss << std::setw(3) << std::setfill('0') << i + 1;
        std::string s(ss.str());

        matplot::title("Generation " + s);
        matplot::save("img/generation_" + std::to_string(i), "svg");
        matplot::hold(matplot::off);
    }

#endif
}
