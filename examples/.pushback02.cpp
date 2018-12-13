#include <benchmark/benchmark.h>
#include <vector>

static void bench_create(benchmark::State& state) {
    for(auto _: state) {
        std::vector<int> v;
    }
}
BENCHMARK(bench_create);

static void bench_reserve(benchmark::State& state) {
    for(auto _: state) {
        std::vector<int> v;
        v.reserve(1);
    }
}
BENCHMARK(bench_reserve);

static void bench_pushback(benchmark::State& state) {
    for(auto _: state) {
        std::vector<int> v;
        v.reserve(1);
        v.push_back(1);
    }
}
BENCHMARK(bench_pushback);

BENCHMARK_MAIN();
