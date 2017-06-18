#!/bin/bash

./sleep.sh 2>&1 |
  tee teeout.txt; test ${PIPESTATUS[0]} -eq 0
