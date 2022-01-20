#! /bin/zsh

##########################################################
#  creates "result.txt" and stores all the output there  #
#                                                        #
#  this test can be run with                             #
#  'make test' command                                   #
#  or                                                    #
#  './test.sh' also works                                #
#  make sure to set the mode to executable (chmod u+x)   # 
##########################################################

test() {
    echo "\n" 'test #' "$1"
    echo '  ./ex5.exe' "$2" "$3" "$4" "\n"
    echo 'input: '
    cat $2
    echo "\n"
    ./ex5.exe $2 $3 $4 # $4 = extra unnecessary argument
    if (($? == 0))
    then
        echo ' output: '
        cat $3
    else
        echo '  ' "$3" 'was not created'
    fi
    echo "\n\n"
}

test1() { # for ARG_TOO_FEW error test
    echo "\n" 'test #' "$1"
    echo '  ./ex5.exe' "$2" "$3" "\n"
    echo 'input: '
    cat $2
    echo "\n"
    ./ex5.exe $2 $3 $4 # $4 = extra unnecessary argument
    if (($? == 0))
    then
        echo ' output: '
        cat $3
    else
        echo '  ' "$3" 'was not created'
    fi
    echo "\n\n"
}

mkdir outputs # just in case
touch result.txt
test  1  inputs/input00.txt      outputs/output00.txt >> result.txt                  # success case
# test  2  inputs/input01.txt      outputs/output01.txt >> result.txt                # success case
# test  3  inputs/input02.txt      outputs/output02.txt >> result.txt                # Error: DATA_FORMAT
# test  4  inputs/input03.txt      outputs/output03.txt >> result.txt                # Error: DATA_FORMAT
# test  5  inputs/input04.txt      outputs/output04.txt >> result.txt                # Error: DATA_FORMAT
# test  6  inputs/input05.txt      outputs/output05.txt >> result.txt                # Error: DATA_FORMAT
# test  7  inputs/DOESNT_EXIST.txt outputs/output06.txt >> result.txt                # Error: FILE_LOAD_FAILED
# test  8  inputs/input06.txt      outputs/output06.txt extra_argument >> result.txt # Error: ARG_TOO_MANY
# test1 9  inputs/input07.txt      outputs/output07.txt >> result.txt                # Error: ARG_TOO_FEW
# test  10 inputs/input08.txt      outputs/output08.txt >> result.txt                # Two inputs are equal
# test  11 inputs/input09.txt      outputs/output09.txt >> result.txt                # Two inputs are equal according to the 
#                                                                                    # torelance, even though they are actualy not equal
cat result.txt | more
