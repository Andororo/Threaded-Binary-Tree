#!/bin/bash

# To more easily compile and run this program on CSS Linux Lab
# Lines starting with '$' indicate what is typed on command line

# if you get the following error:
# -bash: ./simplecompile.sh: /bin/bash^M: bad interpreter: No such file or directory
# run dos2unix to fix it
# $ dos2unix simplecompile.sh

# make this file executable
# $ chmod 700 simplecompile.sh
# redirect the output and stderr from this file to output.txt
# $ ./simplecompile.sh > output.txt 2>&1


date

echo "*** compiling with clang++ to create an executable called myprogram"
clang++ --version
clang++ -std=c++11 -Wall -Wextra -Wno-sign-compare main.cpp tree.cpp treeNode.cpp -g -o myprogram


echo "*** running myprogram"
./myprogram

# valgrind will detect memory leaks
echo "*** running with valgrind"
valgrind --track-origins=yes --leak-check=full ./myprogram 

echo "*** cleaning up, deleting myprogram"
rm myprogram




date
