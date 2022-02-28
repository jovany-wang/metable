  #!/usr/bin/env bash

CURR_DIR=$(cd `dirname $0`; pwd)

clang-format -i $CURR_DIR/../src/*/*.h
clang-format -i $CURR_DIR/../src/*/*.cc
clang-format -i $CURR_DIR/../tests/*

echo "============ Code formatted! ============="
