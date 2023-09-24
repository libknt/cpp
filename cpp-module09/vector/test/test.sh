#!/bin/bash

# RESULT=./log/result.log
# ERROR=./log/error.log
# mkdir -p log

# make -C ..

# cp ../PmergeMe ./

# chmod +x PmergeMe

# ./PmergeMe $(python -c "import random; nums = range(1, 101); random.shuffle(nums); count = random.randint(1, 100); print(' '.join(str(nums[i]) for i in range(count)))") >> $RESULT 2>> $ERROR

# echo "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" >> $RESULT
# echo >> $RESULT
# echo "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" >> $ERROR
# echo >> $ERROR
# make clean


mkdir -p log

make -C ..

cp ../PmergeMe ./

chmod +x PmergeMe

# ./PmergeMe 46 3 91 99 79 74 32 97 96
# ./PmergeMe 6 19 17 8 61 90 60
# ./PmergeMe 38 68 2 86 36 27 60 16 9 97 31 13 10 92 64 44 75 19 20 22 39 52 62 24 51 43 49 45 58 6
# ./PmergeMe 23 82 49 34 46 69 22 84 65 73 48 91 24 5 9 44 7 10 35 42 70 55 40 4 79 41 56 60 92 63 66 81 76 21 31 95 77 33 2 53 62 96 25 72 47 54 45 19 17 75 83 14
# ./PmergeMe 49 45 6 94 95 79 91 8 9 28 48 76 100 31 26 13 21 11 61 4 86 32 7 25 30 85 51 92 78 12 59 75 46 50 81 5 60 35 63 47 2 57 87 77 27 84 69 58 97 56 64 70 22 42 89 74 23 62 18 41 96 67 37 17 82 65 93 88 44 33 68 98 99 36 40 24
# ./PmergeMe 31 44 48 17 73 16 15 6 70 75 47 80 37 34 13 30 9 50 35 18 59 60 29 55 72 63 77 56 22 20 24 94 7 98 64 90 81 23 40 11 52 78 39 41 61 51 43 58 53 85 45 21 3 54 36 10 86 82 27 99 92 83 68 100 95 74 26 4 46 33 8 97 69 38 79 96 88
# ./PmergeMe $(python -c "import random; nums = range(1, 101); random.shuffle(nums); count = random.randint(1, 100); print(' '.join(str(nums[i]) for i in range(count)))")

./PmergeMe $(python3 -c "import random; nums = list(range(1, 101)); random.shuffle(nums); count = random.randint(1, 100); print(' '.join(str(nums[i]) for i in range(count)))")
echo "-------------------------------------------------------------------------------------------------------------------------------"
echo 
make clean
