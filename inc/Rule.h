#ifndef RULE_H_INCLUDED
#define RULE_H_INCLUDED

#include <vector>
#include <string>

class Rule {
public:
  Rule();
  ~Rule();
  void set(int x1, int y1, int x2, int y2, int diff);
  void set(int x1, int y1, int x2, int y2, bool greater);

  bool check(std::vector<std::vector<int>> matrix) const;
  bool valid(int x, int y, int sx, int sy) const;
  std::string to_string() const;
private:
  bool num;
  int diff;
  bool greater;
  int x1;
  int y1;
  int x2;
  int y2;
};

#endif //RULE_H_INCLUDED
