#!/bin/bash

SERVER="http://localhost:8080"
TEST_CGI="42lWatch.ch"
NUM_REQUESTS=100000

function stress_test() {
  for i in $(seq 1 $NUM_REQUESTS); do
    echo "Request $i"
    curl -s -X GET "$SERVER/$TEST_CGI" > /dev/null &
  done
}

# Run stress tests in parallel
echo "Starting stress test with $NUM_REQUESTS requests."
time {
  stress_test
  wait
}
echo "Stress test completed."