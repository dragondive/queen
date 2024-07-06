#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 <command> [args...]"
    exit 1
fi

COMMAND=("$@")

start_time=$(date +%s%3N)
"${COMMAND[@]}"
exit_code=$?
end_time=$(date +%s%3N)

if [ $exit_code -ne 0 ]; then
    echo "Command failed with exit code $exit_code."
    exit $exit_code
fi

elapsed_time=$(($end_time - $start_time))
echo "$elapsed_time"
exit 0
