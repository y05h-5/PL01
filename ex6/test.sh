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
    echo '  ./ex6.exe' "$2" "$3" "$4" "$5"
	echo
    echo 'input: '
    cat $2
	cat $3
    echo
    ./ex6.exe $2 $3 $4 $5 # $5 = extra unnecessary argument
    echo
	echo
}

mkdir outputs # just in case
touch result.txt
test  1  inputs/arrival.txt       inputs/departure.txt  found.txt  >  result.txt                # success case
test  2  inputs/arrival1.txt      inputs/departure1.txt found1.txt >> result.txt                # success case
test  3  inputs/arrival2.txt      inputs/departure2.txt found2.txt >> result.txt                # Error: DATA_TYPE
test  4  inputs/arrival3.txt      inputs/departure3.txt found3.txt >> result.txt                # Error: DATA_TYPE
test  5  inputs/arrival4.txt      inputs/departure4.txt found4.txt >> result.txt                # Error: DATA_FORMAT
test  6  inputs/arrival5.txt      inputs/departure5.txt found5.txt >> result.txt                # Error: DATA_FORMAT
test  7  inputs/DOESNT_EXIST.txt  inputs/departure6.txt found6.txt >> result.txt                # Error: FILE_LOAD_FAILED
test  8  inputs/arrival6.txt      inputs/departure7.txt found7.txt extra_argument >> result.txt # Error: ARG_TOO_MANY

cat result.txt | more
