# Understanding performance with Google Benchmark

This repo contains all the stuff used during the talk I gave at the [Italian C++ Community](https://www.italiancpp.org/) meetup in [Modena, 2018/12/13](https://www.italiancpp.org/event/meetup-dicembre2018/). Please feel free to steal everything you want, if you think you're going to use it.

## Contents

Please note that some submodules are needed to have all the stuff working properly, be sure to `git clone --recursive`.

| Path        | What to expect                                                                                                                 |
| ----------- | ------------------------------------------------------------------------------------------------------------------------------ |
| `slides/`   | The [hugo](https://gohugo.io/) site that generates the full slide deck. Just `cd` into it and launch `hugo server`. |
| `examples/` | Show me the code. |
| `scripts/`  | Helper scripts to carry out some tedious stuff during the live coding. Not interesting unless you are *very* lazy (like me). |

## Toolbox

During the talk we saw a bunch of Linux tools, summarizing all of them here as a reference:

| Tool     | What???                                      |
|----------|----------------------------------------------|
| `perf`   | The definitive profiling toolbox. Seriously. |
| `lstopo` | Show the `NUMA` topology of your system.     |

## Credits

The most interesting examples I'm using are inspred by [this talk](https://youtu.be/nXaxk27zwlk) by Chandler Carruth. You should watch it now. Seriously.

## Resources

* [Optimized C++, Kurt Guntheroth](http://shop.oreilly.com/product/0636920038030.do) - a monumental overview of whys and wherefores of optimization, entirely focused on `C++`.
* [Brendan Gregg's blog](http://www.brendangregg.com) - methodologies, flamegraphs and a great `perf` guide, definitely a must.
* [Profiling & tracing with `perf`, zine by Julia Evans](https://jvns.ca/blog/2018/04/16/new-perf-zine/) - great summary of `perf` capabilities plus it looks great, nice to have it hanging around on the desk.
* [Computer latencies in human terms by Matt Godbolt](https://docs.google.com/presentation/d/17ggR5-2ujJ4VMOGgaWC593d-QU-m0BQVFUMm7UtmJw4) - when you need to know how many coffees you can brew while paying the toll for an L3 miss.
* [Operation costs in CPU clock cycles](http://ithare.com/infographics-operation-costs-in-cpu-clock-cycles/) - a nice infographic about this crazy topic.
* All the conference talks by Chandler Carruth, seriously. If you want some titles to start with, [Tuning C++: Benchmarks, and CPUs, and Compilers! Oh My!](https://youtu.be/nXaxk27zwlk) and [Going Nowhere Faster](https://youtu.be/2EWejmkKlxs) are a must.
* All the conference talks by Matt Godbolt, seriously. If you want some titles to start with (you lazy lad), [Memory and Caches](https://youtu.be/vDns3Um39l0) and [What Has My Compiler Done for Me Lately?](https://youtu.be/bSkpMdDe4g4) are a must.
