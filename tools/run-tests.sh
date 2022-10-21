#!/usr/bin/env bash

# https://stackoverflow.com/a/246128/8662931
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

ret=0
source=$(find $SCRIPT_DIR/.. -regex '.*\/build\/tests\/.*\/test')

count=0
for test in $source
do
  let "count+=1"
done
echo ""
echo "$count tests discovered"
echo ""
echo ""

run=0
failed=0
for test in $source
do
  eval $test
  status=$?
  let "run+=1"
  if [ $status -ne 0 ]; then
    ret=$status
    let "failed+=1"
    echo "$test FAILED"
  fi
done
echo ""
echo "$run tests run, $failed failed"
exit $ret
