#include <benchmark/benchmark.h>
#include <vector>

static void bench_create(benchmark::State& state) {
    for(auto _: state) {
        std::vector<int> v;
    }
}
BENCHMARK(bench_create);

static void bench_push_back(benchmark::State& state) {
    for(auto _: state) {
        std::vector<int> v;
        v.push_back(1);
    }
}
BENCHMARK(bench_push_back);

BENCHMARK_MAIN();
