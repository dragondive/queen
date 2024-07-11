#!/bin/bash

display_help()
{
cat << EOF
Usage: $0 [OPTION]...

-h, --help
    Display this help and exit.

-c, --compile
    Compile the solutions before execution, if applicable.

-e, --execute
    Execute all the solutions.

-p, --plot
    Plot the solution execution times.

-n, --maximum-n N
    The Queen problem solutions will be executed for values from 0 to 'N'.
    [default: 10]

-r, --results-file
    The file to which solution execution times will be written in CSV format.
    [default: queen.csv]

-d, --plot-directory
    The directory in which solution execution times plots will be written in SVG format.
    [default: .]
EOF
}

IS_COMPILE=0
IS_EXECUTE=1
IS_PLOT=1
MAXIMUM_N=10
RESULTS_FILE="queen.csv"
PLOT_DIRECTORY="."

options=$(getopt \
    -l "help,compile,execute,plot,maximum-n:,results-file:plot-directory:", \
    -o "hcepn:r:d:" -- \
    "$@")

eval set -- "$options"

while true
do
case "$1" in
-h|--help)
    display_help
    exit 0
    ;;
-c|--compile)
    IS_COMPILE=1
    shift
    ;;
-e|--execute)
    IS_EXECUTE=1
    shift
    ;;
-p|--plot)
    IS_PLOT=1
    shift
    ;;
-n|--maximum-n)
    MAXIMUM_N=$2
    shift 2
    ;;
-r|--results-file)
    RESULTS_FILE="$2"
    shift 2
    ;;
-d|--plot-directory)
    PLOT_DIRECTORY="$2"
    shift 2
    ;;
--)
    shift
    break
    ;;
esac
done

if [ $IS_COMPILE -eq 1 ];
then
    # compile the C++ solution
    clang++ -Wall -std=c++23 -O3 ./c++/queen.cc -o ./c++/queen

    # compile the Rust solution
    rustc -O ./rust/queen.rs -o ./rust/queen
fi

if [ $IS_EXECUTE -eq 1 ];
then
    version_tag=$(git describe --tags --abbrev=0 develop/queen)
    for ((n = 0; n <= $MAXIMUM_N; n++))
    do
        start_time=$(date +%s%3N)
        ./c++/queen $n
        if [ $? -eq 0 ]; then
            end_time=$(date +%s%3N)
            printf "C++ ($version_tag),%d,%d\n" \
                "$n" "$(($end_time - $start_time))" >> $RESULTS_FILE
        fi

        start_time=$(date +%s%3N)
        ./rust/queen $n
        if [ $? -eq 0 ]; then
            end_time=$(date +%s%3N)
            printf "Rust ($version_tag),%d,%d\n" \
                "$n" "$(($end_time - $start_time))" >> $RESULTS_FILE
        fi

        start_time=$(date +%s%3N)
        python3 ./python/queen.py -n $n
        if [ -$? -eq 0 ]; then
            end_time=$(date +%s%3N)
            printf "Python ($version_tag),%d,%d\n" \
                "$n" "$(($end_time - $start_time))" >> $RESULTS_FILE
        fi
    done
fi

if [ $IS_PLOT -eq 1 ];
then
    python3 -m venv venv
    source ./venv/bin/activate
    python -m pip install pandas matplotlib
    python3 ./scripts/plot.py \
        --input-csv-file "$RESULTS_FILE" \
        --output-svg-files-path "$PLOT_DIRECTORY"
    deactivate
fi
