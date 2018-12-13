+++
title = "Understand performance with Google Benchmark"
outputs = ["Reveal"]
[reveal_hugo]
theme = "white"
highlight_theme = "color-brewer"
transition = "slide"
transition_speed = "fast"
+++

# Understanding performance with Google Benchmark

Federico Ficarelli @ Meetup C++ 2018-12-13

---

# Disclaimer #1

![Optimization](optimization.png)

[xkcd.com/1691](https://xkcd.com/1691/)

---

# Disclaimer #1

1. Get your design right
2. Use efficient algorithms, fast data structures and idioms
3. **Measure** and **understand** performance
4. **Possibly consider** fine grained optimization **only when needed**

---

# Disclaimer #2

1. **Concepts** are **portable**, their **application** is **not**
2. Some degree of **knowledge** of **your architecture** is required
3. Profiling at low level can be **frustrating**, prepare yourself to some **interpretation** of data

---

# Does performance matter anymore?

---

# Measure or it doesn't count

---

## Measure and understand

1. Profile your application as a whole
2. Identify hotspots
3. Understand what's going on in your hottest code

---

# Macro benchmarks

---

## Macro benchmarks

- Whole application
- Similar as much as possible to a production scenario 

---

# Micro benchmarks

---

## Micro benchmarks

![IsItWorth](is_it_worth_the_time.png)

[xkcd.com/1205](https://xkcd.com/1205/)

---

## Micro benchmarks

- The smallest possible hotspot
- As much isolation as you can get
- The goal is to **analyze**, **understand** and **reproduce**

---

# Google Benchmark

---

## Google Benchmark: getting started

1. Define a free function accepting a `benchmark::State&`
2. Measured code loops over `benchmark::State&`
3. Register it with `BENCHMARK(...)` macro
4. Add runner with `BENCHMARK_MAIN()` macro

---

{{% section %}}

## Google Benchmark: how it works

1. Warms up the caches
2. Runs the benchmark
3. Stops when the measurement is *statistically stable*

---

## Computer latencies

<img src="latencies.png" height="550">

{{% /section %}}

---

{{% section %}}

# Parametric benchmarks: values

---

### Single argument: `Arg(n)`

```cpp
static void bench(benchmark::State& state) {
    for(auto _: state) {
        std::vector<std::int32_t> v(state.range(0));
    }
}
BENCHMARK(bench)
    ->Arg(1)
    ->Arg(2)
    // ...
    ->Arg(10);
```

---

### Single argument: `Range(n, m)`

```cpp
static void bench(benchmark::State& state) {
    for(auto _: state) {
        std::vector<std::int32_t> v(state.range(0));
    }
}
BENCHMARK(bench)->Range(1, 10);
```

---

### Single argument: `RangeMultiplier(n)`

```cpp
static void bench(benchmark::State& state) {
    for(auto _: state) {
        std::vector<std::int32_t> v(state.range(0));
    }
}
BENCHMARK(bench)->RangeMultiplier(2)->Range(1, 10);
```
---

### Single argument: `DenseRange(n, m)`

```cpp
static void bench(benchmark::State& state) {
    for(auto _: state) {
        std::vector<std::int32_t> v(state.range(0));
    }
}
BENCHMARK(bench)->DenseRange(1, 10);
```

---

### Multiple arguments: `Args({...})`

```cpp
static void bench(benchmark::State& state) {
    for(auto _: state) {
        std::vector<std::int32_t> v(state.range(0),
                                    state.range(1));
    }
}
BENCHMARK(bench)->Args({1<<10, 128})->Args({2<<10, 256});
```

---

### Multiple arguments: `Args({...})`

```cpp
static void bench(benchmark::State& state) {
    for(auto _: state) {
        std::vector<std::int32_t> v(state.range(0),
                                    state.range(1));
    }
}
BENCHMARK(bench)
    ->Args({0, 0})->Args({0, 1}) ... ->Args({0, 10})
    ->Args({1, 0})->Args({1, 1}) ... ->Args({1, 10})
    // ...
    ->Args({10, 0})->Args({10, 1}) ... ->Args({10, 10});
```

---

### Multiple arguments: `Ranges({...}, {...}, ...)`

```cpp
static void bench(benchmark::State& state) {
    for(auto _: state) {
        std::vector<std::int32_t> v(state.range(0),
                                    state.range(1));
    }
}
BENCHMARK(bench)->Ranges({0, 10}, {0, 10});
```

---

### Custom arguments: `Apply(<callable>)`

```cpp
static void args(benchmark::internal::Benchmark* b) {
    for(auto i = 0; i <= 10; ++i)
        for(auto j = 32; j <= 1024 * 1024; j *= 8)
            b->Args({i, j});
}

static void bench(benchmark::State& state) {
    for(auto _: state) {
        std::vector<std::int32_t> v(state.range(0),
                                    state.range(1));
    }
}
BENCHMARK(bench)->Apply(args);
```

{{% /section %}}

---
{{% section %}}

# Parametric benchmarks: types

---

### Templated benchmarks

```cpp
template <typename T>
void bench(benchmark::State& state) {
    for(auto _: state) {
        std::vector<T> v(256);
    }
}
BENCHMARK_TEMPLATE(bench, std::int8_t);
BENCHMARK_TEMPLATE(bench, std::int16_t);
BENCHMARK_TEMPLATE(bench, std::int32_t);
```

{{% /section %}}

---

{{% section %}}

# Custom statistics

---

### Raw data: `SetBytesProcessed(n)`

```cpp
void bench(benchmark::State& state) {
    std::vector<int> v(state.range(0));
    for(auto _: state) {
        const auto sum = 
            std::accumulate(std::begin(v), std::end(v), 0);
    }
    const auto bytes = 
        state.iterations() * v.size() * sizeof(int);
    
    state.SetBytesProcessed(bytes);
}
BENCHMARK(bench)->Range(8, 1024);
```

---

### User data: `SetItemsProcessed(n)`

```cpp
void bench(benchmark::State& state) {
    std::vector<int> v(state.range(0));
    for(auto _: state) {
        const auto sum = 
            std::accumulate(std::begin(v), std::end(v), 0);
    }
    const auto items = 
        state.iterations() * v.size();
    
    state.SetItemsProcessed(items);
}
BENCHMARK(bench)->Range(8, 1024);
```

---

### Custom counters: `state.counters[<id>]`

```cpp
void bench(benchmark::State& state) {
    std::vector<int> v(state.range(0));
    for(auto _: state) {
        const auto sum = 
            std::accumulate(std::begin(v), std::end(v), 0);
    }
    const auto units = 
        state.iterations() * v.size() / 2;
    
    state.counters["Units"] = units;
}
BENCHMARK(bench)->Range(8, 1024);
```

---

### Asymptotic complexity

```cpp
void bench(benchmark::State& state) {
    std::vector<int> v(state.range(0));
    for(auto _: state) {
        const auto sum = 
            std::accumulate(std::begin(v), std::end(v), 0);
    }
    
    state.SetComplexityN(v.size());
}
BENCHMARK(bench)->Range(8, 1024)->Complexity(benchmark::oN);
```

{{% /section %}}

---

# Thank you!

[nazavode.github.io](https://nazavode.github.io)

![Link](nazavode.github.io.svg)

