#include "Solver.h"

#include <iomanip>
#include <iostream>
#include <map>

using namespace std;

Solver::Solver(int size, vector<Rule> ruleset):
    size(size),
    ruleset(ruleset) {
}

Solver::~Solver() {
}

void Solver::solve() {
  matrix.reserve(size);
  for (int x = 0; x < size; x++) {
    vector<int> ys;
    ys.reserve(size);
    for (int y = 0; y < size; y++) {
      ys.push_back(0);
    }
    matrix.push_back(ys);
  }

  start = chrono::steady_clock::now();
  start_total = chrono::steady_clock::now();
  step(0, 0);
  if (!all && 0 < found) {
    cout << "Solution found" << endl;
  } else if (0 < found) {
    cout << found << " solutions found" << endl;
  } else {
    cout << "No solutions found" << endl;
  }

  if (metrics) {
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Total duration: "
      << chrono::duration_cast<chrono::seconds>(end - start_total).count()
      << " seconds" << endl;
    cout << "Total backtracks taken: " << backtracks_total << endl;
  }
}

bool Solver::step(int x, int y) {
  map<int, bool> nums;
  for (int i = 1; i <= size; i++) {
    nums[i] = true;
  }

  for (int i = 0; i < x; i++) {
    nums[matrix[i][y]] = false;
  }

  for (int i = 0; i < y; i++) {
    nums[matrix[x][i]] = false;
  }

  for (const auto item: nums) {
    if (item.second) {
      matrix[x][y] = item.first;
      bool failed = false;
      for (const auto r: ruleset) {
        if (r.valid(x, y, size, size)) {
          if (!r.check(matrix)) {
            failed = true;
          }
        }
      }
      if (!failed) {
        // Check if this is the last cell
        int max = size - 1;
        if (x == max && y == max) {
          // We have a valid solution
          ++found;
          print();
          if (!all) {
            return true;
          }
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
  ++backtracks;
  return false;
}

void Solver::print() {
  if (onlyCount) {
    return;
  }
  cout << "Solution: " << found << endl;

  if (metrics) {
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Solution took "
      << chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
      << " milliseconds to find." <<endl;
    cout << "Took " << backtracks << " backtracks to find the solution" << endl;
    backtracks_total += backtracks;
    backtracks = 0;
    start = chrono::steady_clock::now();
  }

  vector<vector<string>> display;
  display.reserve(size*2);
  for (int x = 0; x < size *2; x++) {
    vector<string> v;
    v.reserve(size*2);
    for (int y = 0; y < size *2; y++) {
      v.push_back(" ");
    }
    display.push_back(v);
  }

  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      display[x*2][y*2] = std::to_string(matrix[x][y]);
    }
  }

  for (const auto r: ruleset) {
    display[r.xpos()*2][r.ypos()*2] = r.rule();
  }

  for (int y = 0; y < (size*2 - 1); y++) {
    for (int x = 0; x < (size*2 - 1); x++) {
      cout << display[x][y] << " ";
    }
    cout << endl;
  }
}

void Solver::findAll(bool all) {
  this->all = all;
}

void Solver::countOnly(bool count) {
  this->onlyCount = count;
}

void Solver::enableMetrics(bool metrics) {
  this->metrics = metrics;
}

