#include <bitset>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <string>

#include "algorithm.hpp"
#include "algorithm/fitness.hpp"
#include "algorithm/options.hpp"
#include "algorithm/termination.hpp"

#include "operators/crossover.hpp"
#include "operators/mutation.hpp"
#include "operators/selection.hpp"

#include "population.hpp"
#include "population/individual.hpp"

// #define PLOT

#ifdef PLOT
#include <matplot/matplot.h>
#endif

using genalg::GeneticAlgorithm;

using genalg::algorithm::FitnessFunction;
using genalg::algorithm::BestLimit;
using genalg::algorithm::GenerationLimit;
using genalg::algorithm::Options;

using genalg::operators::TournamentSelection;
using genalg::operators::MultiPointCrossover;
using genalg::operators::BitFlipMutation;

using genalg::Population;
using genalg::population::Individual;

using Genome = std::bitset<25>;
using Fitness = double;

using Solution = Individual<Genome, Fitness>;

using TerminationMethod = BestLimit<Solution>;

using SelectionMethod = TournamentSelection<Solution>;
using CrossoverMethod = MultiPointCrossover<Genome>;
using MutationMethod = BitFlipMutation<Genome>;

template<>
void std::swap<Genome::reference>
(Genome::reference &lhs, Genome::reference &rhs) noexcept {
    Genome::reference& tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

#define K_INDIVIDUALS 25

int
main() {
    std::random_device rd;
    std::default_random_engine rng(rd());

    Population<Solution> population(K_INDIVIDUALS);
    FitnessFunction<Genome, Fitness> fitness
        ([](const Genome& genome) {
            double x = (static_cast<double>(genome.to_ulong()) / 33554431.0) * 10.0;
            return std::sin(x) - 0.2 * std::abs(x);
        });

    // initial population
    std::uniform_int_distribution<int> idistr(0, 170);
    for(int i = 0; i < K_INDIVIDUALS; ++i) {
        Genome genome(idistr(rng));
        population.append(Solution(genome, fitness.evaluate(genome)));
    }

    SelectionMethod selection(2, 0.85);
    CrossoverMethod crossover(2);
    MutationMethod mutation(0.5);
    Options options(K_INDIVIDUALS, 0.1);

    GeneticAlgorithm<Solution, Genome, Fitness>
        ga(&selection, &crossover, &mutation, &fitness, options);

    ga.initialize(population);

    TerminationMethod termination(100);
    ga.run(termination);

    std::cout << "GENERATION " << ga.generations().size()
              << " BEST: " << ga.generations().back().best().fitness() << "\n";

    #ifdef PLOT
    std::vector<double> index(ga.generations().size());
    std::vector<double> best;
    std::vector<double> worst;
    std::vector<double> average;

    std::iota(index.begin(), index.end(), 1);

    for(const auto& p : ga.generations()) {
        best.push_back(p.best().fitness());
        worst.push_back(p.worst().fitness());
    }

    matplot::title("Best and Worst Fitness per Generation");
    matplot::xlabel("Generation");
    matplot::ylabel("Fitness");

    matplot::hold(matplot::on);
    matplot::plot(index, best);
    matplot::plot(index, worst);

    auto l = matplot::legend({"best", "worst"});
    l->location(matplot::legend::general_alignment::bottomright);

    matplot::show();
    #endif
}
