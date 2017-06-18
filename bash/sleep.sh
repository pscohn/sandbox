#!/bin/bash

function ex {
  echo 'exiting'
  exit 0
}

while true; do
  echo Hello
  sleep 1
  echo Hello
  sleep 1
  ex
  echo Hello
  sleep 1
  echo Hello
  exit 1
done

