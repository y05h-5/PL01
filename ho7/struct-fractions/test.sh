#! /bin/bash

#######################################################
# this test can be run with                           #
# 'make test' command                                 #
# or                                                  #
# './test.sh' also works                              #
# make sure to set the mode to executable (chmod u+x) #
#######################################################

test() {
    echo 'test #' "$4"
    echo '  ./ho7.exe' "$1" "$2"
    echo
    echo '  input: '
    cat $1
    echo
    echo
    echo "$3" | ./ho7.exe $1 $2
    if (($? == 1))
    then
        echo "program failed" > $2
    fi    
    echo
}

mkdir outputs # just in case
test inputs/input.txt outputs/output.txt n 1 # success case with rational output
test inputs/input.txt outputs/output1.txt y 2 # success case with floating point output
test inputs/DOESNOTEXIST.txt outputs/output2.txt n 3 # input file won't open
test inputs/input_fail1.txt outputs/output3.txt n 4 # Error: DATA_FORMAT
test inputs/input_fail2.txt outputs/output4.txt n 5 # Error: DATA_FORMAT
test inputs/input_fail3.txt outputs/output5.txt n 6 # Error: DATA_FORMAT
test inputs/input_fail4.txt outputs/output6.txt n 7 # Error: DATA_FORMAT
