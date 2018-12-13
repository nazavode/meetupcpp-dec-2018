#include<benchmark/benchmark.h>
#include <vector>
#include <cstdint>

template <typename T>
void bench(benchmark::State& state) {
    for(auto _: state) {
        std::vector<T>(64);
    }
}
BENCHMARK_TEMPLATE(bench, std::int8_t);
BENCHMARK_TEMPLATE(bench, std::int16_t);
BENCHMARK_TEMPLATE(bench, std::int32_t);
BENCHMARK_TEMPLATE(bench, std::int64_t);


BENCHMARK_MAIN();
