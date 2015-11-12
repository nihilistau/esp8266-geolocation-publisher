#!/bin/bash
set -e

cd ./test/
cmake .
make
bin/Tests