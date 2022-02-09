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
    echo '  echo' "$2" "$3" '| ./main.exe' "$4" "$5" "$6" "$7"
	echo
    echo 'input: '
    cat $4
    echo
	cat $5
    echo
    echo $2 $3 | ./main.exe $4 $5 $6 $7 # $7 = extra unnecessary argument
    echo
}

mkdir outputs # just in case
touch result.txt
test 1 "Petersburg\n" "Tokyo\n" 	inputs/arrival.txt       inputs/departure.txt  outputs/found.txt  >  result.txt                # success case
test 2 "London\n" 	  "Frankfurt\n" inputs/arrival.txt       inputs/departure.txt  outputs/found1.txt >> result.txt                # success case
test 3 "Petersburg\n" "Tokyo\n" 	inputs/arrival1.txt      inputs/departure.txt  outputs/found2.txt >> result.txt                # Error: DATA_FORMAT
test 4 "Petersburg\n" "Tokyo\n" 	inputs/arrival.txt       inputs/departure1.txt outputs/found3.txt >> result.txt                # Error: DATA_FORMAT
test 5 "Petersburg\n" "Tokyo\n"		inputs/arrival2.txt      inputs/departure.txt  outputs/found4.txt >> result.txt                # Error: DATA_TYPE
test 6 "Petersburg\n" "Tokyo\n" 	inputs/arrival3.txt      inputs/departure.txt  outputs/found5.txt >> result.txt                # Error: DATA_FORMAT
test 7 "Petersburg\n" "Tokyo\n"		inputs/DOESNT_EXIST.txt  inputs/departure.txt  outputs/found6.txt >> result.txt                # Error: FILE_LOAD_FAILED
test 8 "Petersburg\n" "Tokyo\n"	 	inputs/arrival6.txt      inputs/departure7.txt outputs/found7.txt extra_argument >> result.txt # Error: ARG_TOO_MANY

cat result.txt | more
