#include <benchmark/benchmark.h>
#include <numeric>

void bench_accumulate(benchmark::State& state) {
    std::vector<int> v(state.range(0));
    // fill...
    for(auto _: state) {
        const auto sum = std::accumulate(std::begin(v), std::end(v), 0);
        (void)sum;
    }
    const auto bytes = state.iterations() * v.size() * sizeof(int);
    state.SetBytesProcessed(bytes);
}

BENCHMARK(bench_accumulate)->Range(8, 1024);

BENCHMARK_MAIN();
