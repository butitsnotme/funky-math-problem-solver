# FMPS - Funky Math Problem Solver
solves the new funky math problem found in uWaterloo mathNEWS publication.
Pass the program the size (defaults to 6) and the set of rules/restrictions,
if there is a valid solution, it will be printed out.

## Rules
Rules are in the following format:
  <x1>:<y1>:<x2>:<y2>:<rule>

Where:
 - <x1> - The horizontal index of the first box affected by the rule.
 - <y1> - The vertical index of the first box affected by the rule.
 - <x2> - The horizontal index of the second box affected by the rule.
 - <y2> - The vertical index of the second box affected by the rule.
 - <rule> - The rule, either "<", ">" or a number for the absolute difference

Note: Boxes are zero indexed, beggining with the upper left box.

## Examples
  - 0:1:0:2:3 - The first two boxes of the first column must have a difference
              of 3
