#include "Solver.h"

#include <map>
#include <iostream>

using namespace std;

Solver::Solver(int size, vector<Rule> ruleset):
    size(size),
    ruleset(ruleset) {
}

Solver::~Solver() {
}

vector<vector<int>> Solver::solve() {
  matrix.reserve(size);
  for (int x = 0; x < size; x++) {
    vector<int> ys;
    ys.reserve(size);
    for (int y = 0; y < size; y++) {
      ys.push_back(0);
    }
    matrix.push_back(ys);
  }

  if (step(0, 0)) {
    cout << "Solution found" << endl;
  } else {
    cout << "No solution found" << endl;
  }

  return matrix;
}

bool Solver::step(int x, int y) {
  map<int, bool> nums;
  for (int i = 1; i <= size; i++) {
    nums[i] = true;
  }

  for (int i = 0; i < x; i++) {
    nums[matrix[i][y]] = false;
    nums[matrix[x][i]] = false;
  }

  for (const auto item: nums) {
    if (item.second) {
      matrix[x][y] = item.first;
      for (const auto r: ruleset) {
        if (r.valid(x, y, size, size)) {
          if (!r.check(matrix)) {
            continue;
          }
        }
        // Check if this is the last cell
        int max = size - 1;
        if (x == max && y == max) {
          // We have a valid solution
          return true;
        } else if (x == max) {
          // We are at the end of the row
          if (step(0, y + 1)) {
            return true;
          }
        } else {
          if (step(x + 1, y)) {
            return true;
          }
        }
      }
    }
  }

  // We did not find a valid solution with our givens
  matrix[x][y] = 0;
  return false;
}

void Solver::print() const {
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      cout << " " << matrix[x][y];
    }
    cout << endl;
  }
}
