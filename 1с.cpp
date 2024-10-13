#include <iostream>
#include <vector>
#include <stack>

struct State {
 public: 
  std::vector<std::vector<uint16_t>> state;
  bool used = false;

  explicit State(std::vector<std::vector<uint16_t>>& matrix) : state(matrix) {};

  State() = default;

  std::vector<State> Neighbour() {
    std::vector<State> neighbours;
    neighbours.reserve(50);
    for (auto  i = 0; i < 8; ++i) { 
      for (auto j = 0; j < 8; ++j) {
        if (state[i].size()) { 
          if (!state[j].size() or state[i].back() < state[j].back()) {
            State new_ = *this;
              new_.used = 0;
              new_.state[j].push_back(new_.state[i].back());
              new_.state[i].pop_back();
              neighbours.push_back(new_);
          }
        }
      }
    }
    return neighbours;
  }

  void calc() {
    for (auto  i = 0; i < 8; ++i) {
      bool full = 1;
      for (auto j = 0; j < 9; ++j) {
        auto size = state[i].size();
        if ((size <= j) or (size > j and state[i][size - 1 - j] != j)) {
          full = 0;
          break;
        }
      }
      if (full) {
        for (auto j = 0; j < 9; ++j) {
          state[i].pop_back();
        }
      }
    }
  }

  bool Check_empty() {
    for (auto i = 0; i < 8; ++i) {
      if (state[i].size()) {
        return false;
      }
    }
    return true;
  }
};

int DFS(State& v, int num) {
  v.calc();
  if (v.Check_empty()) {
    return num;
  }
  v.used = 1;
  std::vector<State> neighbours = v.Neighbour();
  for (auto u : neighbours) {
    if (!u.used) {
      int a = DFS(u, num + 1);
      if (a != -1) {
        return a;
      }
    }
  }
  return -1;
}

int main() {
  std::vector<std::vector<uint16_t>> matrix(8, std::vector<uint16_t>(9));
  for (auto i = 0; i < 8; ++i) {
    for (auto j = 0; j < 9; ++j) {
      std::cin >> matrix[i][j];
    }
  }
  State matr(matrix);
  std::cout << DFS(matr, 0);
}

// можно добавить различные эвристики выбора наилучшего варианта