#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <string>

#include "algorithm.hpp"
#include "algorithm/options.hpp"

#include "operators/crossover.hpp"
#include "operators/mutation.hpp"
#include "operators/selection.hpp"

#include "population.hpp"
#include "population/individual.hpp"

using genalg::algorithm::Options;

using genalg::operators::MultiPointCrossover;
using genalg::operators::TournamentSelection;
using genalg::operators::InversionMutation;

using genalg::Population;
using genalg::population::Individual;

using Genome = std::vector<bool>;
using Fitness = double;

// #define PLOT
#ifdef PLOT
#include <matplot/matplot.h>
#endif

#define POPULATION_SIZE 50
#define K_GENERATIONS 20
#define P_MUTATION 0.01

class Solution : public Individual<Genome, Fitness> {
public:
    static int capacity;
    static int bounds;

    explicit Solution(const Genome& g)
        : Individual<Genome, Fitness>(g) {}

    double decimal() const {
        bool sign = this->genome[0];
        double value = 0;

        // right to left
        for(int i = this->genome.size() - 1; i > 0; --i) {
            value += std::pow(2, (this->genome.size() - 1) - i) * this->genome[i];
        }

        // maximum
        double max = 0;
        for(std::size_t i = 0; i < this->genome.size(); ++i) {
            max += std::pow(2, i);
        }

        // normalize
        value = (value / max) * this->bounds;

        if(sign) {
            return -value;
        } else {
            return value;
        }
    }

    Fitness fitness() const override {
        double x = this->decimal();
        return std::sin(x) - 0.2 * std::abs(x);
    }
};

int Solution::capacity = 10;
int Solution::bounds = 10;

int
main(int argc, char** argv) {
    std::unique_ptr<Options> options;

    if(argc == 2) {
        // seed provided
        options = std::make_unique<Options>
            (POPULATION_SIZE, K_GENERATIONS, P_MUTATION, std::stoul(argv[1]));
    } else {
        options = std::make_unique<Options>
            (POPULATION_SIZE, K_GENERATIONS, P_MUTATION);
    }

    // GA operations
    TournamentSelection<Solution, Fitness> selection(2, 0.85);
    MultiPointCrossover<Solution> crossover(2);
    InversionMutation<Solution> mutation;

    genalg::GeneticAlgorithm<Solution, Fitness>
        ga(&selection, &crossover, &mutation, *options);

    // create a random initial population
    std::default_random_engine engine(options->seed);
    std::uniform_int_distribution<int> idistr(0, 1);
    Population<Solution, Fitness> initial_population(options->population_size);

    for(std::size_t i = 0; i < options->population_size; ++i) {
        std::vector<bool> genome;

        for(int j = 0; j < Solution::capacity; ++j) {
            genome.push_back(idistr(engine));
        }

        initial_population.add(Solution(genome));
    }

    std::vector<double> index;
    std::vector<double> best;
    std::vector<double> worst;
    std::vector<double> average;

    ga.initialize(initial_population);

    index.push_back(0);
    best.push_back(initial_population.best().second);
    worst.push_back(initial_population.worst().second);
    average.push_back(initial_population.average());

    for(std::size_t i = 1; i < options->n_generations; ++i) {
        auto next = ga.next();
        std::cout << "GENERATION " << std::setw(3) << std::setfill('0') << i
                  << " BEST: "
                  << "{" << next.best().first.decimal() << ", "
                  << next.best().second << "}\n";

        // plotting statistics
        index.push_back(i);
        best.push_back(next.best().second);
        worst.push_back(next.worst().second);
        average.push_back(next.average());
    }

    #ifdef PLOT
    matplot::title("Best, Worst, and Average Fitness per Generation");
    matplot::xlabel("Generation");
    matplot::ylabel("Fitness");

    matplot::hold(matplot::on);
    matplot::plot(index, best);
    matplot::plot(index, worst);
    matplot::plot(index, average);

    auto l = matplot::legend({"best", "worst", "avg"});
    l->location(matplot::legend::general_alignment::bottomright);

    matplot::show();
    #endif
}
