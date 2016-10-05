#include "Rule.h"

#include <cstdlib>
#include <sstream>

using namespace std;

Rule::Rule() {
}

Rule::~Rule() {
}

void Rule::set(int x1, int y1, int x2, int y2, int diff) {
  this->x1 = x1;
  this->y1 = y1;
  this->x2 = x2;
  this->y2 = y2;
  this->diff = diff;
  this->num = true;
}

void Rule::set(int x1, int y1, int x2, int y2, bool greater) {
  this->x1 = x1;
  this->y1 = y1;
  this->x2 = x2;
  this->y2 = y2;
  this->greater = greater;
  this->num = false;
}

bool Rule::check(vector<vector<int>> matrix) const {
  if (num) {
    return diff == abs(matrix[x1][y1] - matrix[x2][y2]);
  } else if(greater) {
    return matrix[x1][y1] > matrix[x2][y2];
  } else {
    return matrix[x1][y1] < matrix[x2][y2];
  }
}

bool Rule::valid(int x, int y, int sx, int sy) const {
  int cp = y * sx + x;
  int p1 = y1 * sx + x1;
  int p2 = y2 * sx + x2;

  return (p1 <= cp) && (p2 <= cp);
}

string Rule::to_string() const {
  stringstream ss;
  ss << "Rule: ";
  if (num) {
    ss << diff << endl;
  } else {
    ss << (greater ? ">" : "<") << endl;
  }
  ss << "Box 1: (" << x1 << "," << y1 << ")" << endl;
  ss << "Box 2: (" << x2 << "," << y2 << ")" << endl;
  return ss.str();
}

