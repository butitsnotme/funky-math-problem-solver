#ifndef SOLVER_H_INCLUDED
#define SOLVER_H_INCLUDED

#include <vector>

#include "Rule.h"

class Solver {
public:
  Solver(int size, std::vector<Rule> ruleset);
  ~Solver();
  std::vector<std::vector<int>> solve();
  void print() const;
private:
  bool step(int x, int y);
  int size;
  std::vector<Rule> ruleset;
  std::vector<std::vector<int>> matrix;
};

#endif //SOLVER_H_INCLUDED
