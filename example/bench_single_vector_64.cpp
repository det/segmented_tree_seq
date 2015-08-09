#include "bench_single.hpp"

#include <vector>

template <typename T>
using Container = std::vector<T>;

int main(int argc, char** argv) {
  return bench_single<Container, std::uint64_t>(argc, argv);
}
