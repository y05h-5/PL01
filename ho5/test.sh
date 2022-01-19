#! /bin/zsh

#######################################################
# this test can be run with                           #
# 'make test' command                                 #
# or                                                  #
# './test.sh' also works                              #
# make sure to set the mode to executable (chmod u+x) #
#######################################################

test() {
    echo 'test #' "$4"
    echo '  ./ho5.exe' "$1" "$2" "$3" "\n"
    echo '  input: ' $(cat $1)
    echo '  tolerance: ' "$3"
    ./ho5.exe $1 $2 $3 $5 # $5 = extra unnecessary argument
    if (($? == 0))
    then
        echo '  output: ' $(cat $2)
    else
        echo '  ' "$2" 'was not created'
    fi
    echo "\n\n"
}

test1() { # for ARG_TOO_FEW error test
    echo 'test #' "$4"
    echo '  ./ho5.exe' "$1" "$2" "$3" "\n"
    echo '  input: ' $(cat $1)
    echo '  tolerance: ' "$3"
    ./ho5.exe $1 $2
    if (($? == 0))
    then
        echo '  output: ' $(cat $2)
    else
        echo '  ' "$2" 'was not created'
    fi
    echo "\n\n"
}

mkdir outputs # just in case
test inputs/input00.txt outputs/output00.txt 1e-5 1 # success case
test inputs/input01.txt outputs/output01.txt 1e-5 2 # success case
test inputs/input02.txt outputs/output02.txt 1e-5 3 # Error: DATA_FORMAT
test inputs/input03.txt outputs/output03.txt 1e-5 4 # Error: DATA_FORMAT
test inputs/input04.txt outputs/output04.txt 1e-5 5 # Error: DATA_FORMAT
test inputs/input05.txt outputs/output05.txt 1e-5 6 # Error: DATA_FORMAT
test inputs/DOESNT_EXIST.txt outputs/output06.txt 1e-5 6 # Error: FILE_LOAD_FAILED
test inputs/input06.txt outputs/output06.txt 1e-5 7 extra_argument # Error: ARG_TOO_MANY
test1 inputs/input07.txt outputs/output07.txt 1e-5 8 # Error: ARG_TOO_FEW
test inputs/input08.txt outputs/output08.txt 1e-5 9 # Two inputs are equal
test inputs/input09.txt outputs/output09.txt 0.1 10 # Two inputs are equal according to the 
                                                    # torelance, even though they are actualy not equal
