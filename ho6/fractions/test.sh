#! /bin/bash

#######################################################
# this test can be run with                           #
# 'make test' command                                 #
# or                                                  #
# './test.sh' also works                              #
# make sure to set the mode to executable (chmod u+x) #
#######################################################

test() {
    echo 'test #' "$3"
    echo '  ./ho6.exe' "$1" "$2" "\n"
    echo '  input: ' $(cat $1)
    ./ho6.exe $1 $2
    echo "\n\n"
}

mkdir outputs # just in case
test inputs/input.txt outputs/output.txt 1 # success case
test inputs/DOESNOTEXIST.txt outputs/output1.txt 2 # input file won't open
test inputs/input_fail1.txt outputs/output2.txt 2 # Error: DATA_FORMAT
test inputs/input_fail2.txt outputs/output3.txt 3 # Error: DATA_FORMAT
test inputs/input_fail3.txt outputs/output4.txt 4 # Error: DATA_FORMAT
test inputs/input_fail4.txt outputs/output5.txt 5 # Error: DATA_FORMAT
