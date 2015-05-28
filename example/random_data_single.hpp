#pragma once

#include <array>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include <type_traits>

template <typename T>
class random_data_single {
  static_assert(std::is_trivial<T>::value, "T must be trivial");
  static_assert(std::is_integral<T>::value, "T must be integral");
  static_assert(std::is_unsigned<T>::value, "T must be unsigned");

 private:
  std::vector<std::size_t> indexes_;
  std::vector<T> ordered_;
  std::vector<T> inserted_;

 public:
  random_data_single(std::size_t count) {
    std::random_device device;
    std::default_random_engine engine{device()};
    std::uniform_int_distribution<T> dist;
    indexes_.reserve(count);
    ordered_.reserve(count);
    inserted_.reserve(count);

    for (std::size_t i = 0; i != count; ++i) {
      std::uniform_int_distribution<std::size_t> index_dist{0, i};
      std::size_t index = index_dist(engine);
      T data = dist(engine);
      indexes_.push_back(index);
      ordered_.push_back(data);
      inserted_.insert(inserted_.begin() + index, data);
    }
  }

  random_data_single(std::string const &path) {
    std::ifstream in{path};
    std::size_t count;
    in.read(reinterpret_cast<char *>(&count), sizeof(std::size_t));
    indexes_.resize(count);
    ordered_.resize(count);
    inserted_.resize(count);
    in.read(reinterpret_cast<char *>(indexes_.data()),
            count * sizeof(std::size_t));
    in.read(reinterpret_cast<char *>(ordered_.data()), count * sizeof(T));
    in.read(reinterpret_cast<char *>(inserted_.data()), count * sizeof(T));
  }

  void save(std::string const &path) {
    std::ofstream out{path};
    std::size_t size = indexes_.size();
    out.write(reinterpret_cast<char *>(&size), sizeof(std::size_t));
    out.write(reinterpret_cast<char *>(indexes_.data()),
              size * sizeof(std::size_t));
    out.write(reinterpret_cast<char *>(ordered_.data()), size * sizeof(T));
    out.write(reinterpret_cast<char *>(inserted_.data()), size * sizeof(T));
  }

  std::size_t get_count() const { return indexes_.size(); }
  std::vector<std::size_t> const &get_indexes() const { return indexes_; }
  std::vector<T> const &get_inserted() const { return inserted_; }
  std::vector<T> const &get_ordered() const { return ordered_; }
};
