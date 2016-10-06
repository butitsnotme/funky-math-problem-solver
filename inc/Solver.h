#ifndef SOLVER_H_INCLUDED
#define SOLVER_H_INCLUDED

#include <vector>
#include <chrono>
#include <ctime>

#include "Rule.h"

class Solver {
public:
  Solver(int size, std::vector<Rule> ruleset);
  ~Solver();
  void solve();
  void print();
  void findAll(bool all);
  void countOnly(bool count);
  void enableMetrics(bool metrics);
private:
  bool step(int x, int y);
  bool all = false;
  bool onlyCount = false;
  bool metrics = false;
  int size;
  int backtracks = 0;
  int backtracks_total = 0;
  std::vector<Rule> ruleset;
  std::vector<std::vector<int>> matrix;
  int found = 0;
  std::chrono::steady_clock::time_point start;
  std::chrono::steady_clock::time_point start_total;
};

#endif //SOLVER_H_INCLUDED
