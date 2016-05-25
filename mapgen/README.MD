Map Generator utility:

Build
=====
Just run 'make'

Run
===
1. run the checker
2. run the mapgen tool similar to the checker

e.g.
cat inputGenerator/ref_file.txt | ./a.out
cd mapgen
cat ../inputGenerator/ref_file.txt | ./a.out

Result
======
each time a task with opCode=17 is found in ref_file.txt,
a map#.html file is generated
