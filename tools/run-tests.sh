#!/usr/bin/env bash

# https://stackoverflow.com/a/246128/8662931
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

ret=0
source=$(find $SCRIPT_DIR/.. -regex '.*\/build\/test_[^\.]*$')

echo $SCRIPT_DIR

for test in $source
do
  echo $test
  eval $test
  status=$?
  if [ $status -ne 0 ]; then
    ret=$status
    echo "$test FAILED"
  fi
done
exit $ret
