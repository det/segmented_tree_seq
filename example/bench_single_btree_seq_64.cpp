#include "bench_single.hpp"
#include "array/trunk/btree_seq.h"

template <typename T>
using Container = btree_seq<T>;

int main(int argc, char** argv) {
  return bench_single<Container, std::uint64_t>(argc, argv);
}
