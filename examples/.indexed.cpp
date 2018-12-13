#include <benchmark/benchmark.h>

#include <algorithm>
#include <iterator>
#include <limits>
#include <random>
#include <string>
#include <vector>

namespace {

template <typename Container, typename ValueType = typename Container::value_type>
void fillrnd(Container&& c, ValueType min, ValueType max) {
    std::random_device rnd_device;
    std::mt19937 rnd_engine{rnd_device()};
    std::uniform_int_distribution<ValueType> rnd_dist{min, max};
    std::generate(std::begin(c), std::end(c),
                  [&rnd_dist, &rnd_engine]() { return rnd_dist(rnd_engine); });
}

}  // namespace

// Mimic linked lists/std::unordered_* memory access pattern
static void bench_indexed(benchmark::State& state) {
    int bytes = 1 << state.range(0);
    int count = (bytes / sizeof(int)) / 2;

    // Data vector
    std::vector<int> v(count);
    fillrnd(v, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    // Indices vector
    std::vector<int> indices(count);
    fillrnd(indices, 0, count - 1);

    // Hotspot
    for (auto _ : state) {
        long sum = 0;
        for (auto i : indices) {
            sum += v[i];
        }
        benchmark::DoNotOptimize(sum);
    }

    // Measurements
    state.SetBytesProcessed(state.iterations() * static_cast<long>(bytes));
    state.SetLabel(std::to_string(bytes / 1024) + "kb");
}
BENCHMARK(bench_indexed)->DenseRange(13, 26);

BENCHMARK_MAIN();
