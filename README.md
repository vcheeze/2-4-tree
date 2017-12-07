# 2-4-tree
Operating Systems Project 1 in C++14

## How to run
Run `make` to compile the files. This will allow you to enter a small shell, in
which you can execute the following commands.

1. `init`:
initialize all structures of your program. You should allocate all space-needed
dynamically and on per-need basis. You should not use any statically structures
defined up-front.
2. `ins <studID><courseID><courseName><Grade>`:
insert all pertitnent data for a specific course that a student (with <studID>)
has taken.
3. `load inputFile`:
bulk load a number of records; each record follows the format indicated in the
previous instruction.
4. `find <studID>`:
lookup all information found on the 2-4 tree-based structure regarding student
with <studID>.
5. `range <studIDa> <studIDb>`:
fetch and display all information for students whose IDs fall in the (numeric)
interval <studIDa> to <studIDb>.
6. `gpa <studID> or gpa <studIDa> <studIDb>`:
compute the GPA of a specific student or the average GPA of students in the
range <studIDa> to <studIDb>.
7. `top k`:
compute the k (number) more popular courses taken by all students in the
semester.
8. `verify`:
check all nodes of the indexing structure and verify that they comply with the
2-4 tree properties.
9. `del <studID><courseID>`:
delete the specific course for the student indicated by <studID>.
10. `sdel <studID>`:
delete all the information regarding student <studID> along with her courses
found on the structure.
11. `exit`:
free all space allocated gracefully and exit the application.
