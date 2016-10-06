#ifndef SOLVER_H_INCLUDED
#define SOLVER_H_INCLUDED

#include <vector>

#include "Rule.h"

class Solver {
public:
  Solver(int size, std::vector<Rule> ruleset);
  ~Solver();
  void solve();
  void print() const;
  void findAll(bool all);
  void countOnly(bool count);
private:
  bool step(int x, int y);
  bool all = false;
  bool onlyCount = false;
  int size;
  std::vector<Rule> ruleset;
  std::vector<std::vector<int>> matrix;
  int found = 0;
};

#endif //SOLVER_H_INCLUDED
