  #!/usr/bin/env bash

set -x
# Cause the script to exit if a single command fails.
set -e

bazel build //:all
