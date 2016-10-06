#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "Info.h"
#include "Rule.h"
#include "Solver.h"
#include "args.hxx"
#include "data.h"

using namespace std;

DATA_FILE(description)

struct RulesReader {
  void operator()(const std::string &name, const std::string &value,
      Rule &destination) {
    vector<string> items;
    istringstream iss(value);

    for (string token; getline(iss, token, ':'); ) {
      items.push_back(move(token));
    }

    int x1(atoi(items[0].c_str()));
    int y1(atoi(items[1].c_str()));
    int x2(atoi(items[2].c_str()));
    int y2(atoi(items[3].c_str()));
    
    if ("<" == items[4] || ">" == items[4]) {
      destination.set(x1, y1, x2, y2, ('>' == *(items[4].c_str())));
    } else {
      int diff(atoi(items[4].c_str()));
      destination.set(x1, y1, x2, y2, diff);
    }
  }
};

ostream& operator<<(ostream& out, const Rule& r) {
  return out << r.to_string();
}
  

int main(int argc, char** argv) {

  string prog_name = "fmps";

  string description(&description_begin);

  args::ArgumentParser p(description);
  args::Flag license(p, "license", "Show the license", {"license"});
  args::Flag help(p, "help", "Display this help text", {'h', "help"});
  args::Flag version(p, "version", "Show the program version", {"version"});
  args::ValueFlag<int> size(p, "size", "Set the size of the grid",
      {'s', "size"}, 6);
  args::Flag allSolutions(p, "all", "Find all solutions, not just the first",
      {'a', "all"});
  args::Flag countOnly(p, "count", "Only count the solutions, do not print them",
      {'c', "count"});
  args::PositionalList<Rule, vector, RulesReader> rules(p, "rules",
      "The list of constraints/rules");

  Info info(prog_name);

  try {
    p.ParseCLI(argc, argv);
  } catch (args::Help) {
    stringstream help;
    help << p;
    info.setHelp(help.str());
    info.showHelp();
    cout << info.display();
    return 0;
  } catch (args::ParseError e) {
    cerr << e.what() << endl;
    stringstream help;
    help << p;
    info.setHelp(help.str());
    info.showHelp();
    cerr << info.display();
    return 0;
  }

  bool display = false;
  if (license) {
    info.showLicense();
    display = true;
  }
  if (help) {
    stringstream help;
    help << p;
    info.setHelp(help.str());
    info.showHelp();
    display = true;
  }
  if (version) {
    info.showVersion();
    display = true;
  }
  if (display) {
    cout << info.display();
    return 0;
  }

  cout << "Size: " << args::get(size) << endl;

  if (rules) {
    cout << " Rule | x   | y" << endl;
    cout << " ----------------" << endl;
    for (const auto r: args::get(rules)) {
      cout << " " << r.rule() << "    | " << setw(3) << r.xpos() << " | "
        << setw(3) << r.ypos() << endl;
    }
    cout << endl;
  }

  int nSize = args::get(size);

  Solver s(nSize, args::get(rules));

  if (allSolutions) {
    cout << "Finding all solutions\n" << endl;
    s.findAll(true);
  }

  if (countOnly) {
    cout << "Only counting solutions\n" << endl;
    s.countOnly(true);
  }

  s.solve();

  return 0;

}
