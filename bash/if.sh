#!/bin/bash

if [ 'true' = 'true' ]; then
  echo '1'
fi

if [[ 'true' = 'true' ]]; then
  echo '2'
fi


if [[ 'true' ]]; then
  echo '3'
fi

if [[ SOME_VAR ]]; then
  echo '4'
fi

SOME_VAR=''

if [[ $SOME_VAR ]]; then
  echo '5'
fi

SOME_VAR='thing'

if [[ $SOME_VAR ]]; then
  echo '6'
fi

if [[ false = true ]]; then
  echo '7'
fi

if [ $SOME_VAR ]; then
  echo '8'
fi

re='^[0-9]+$'
num=523
if [[ "$num" =~ $re ]]; then
  # single brackets don't work
  echo '9'
fi

if [[ 'null124' =~ $re ]]; then
  echo '10'
fi

if [[ 'foo' == 'foo' ]]; then
  if_var=foo
else
  if_var=bar
fi
echo "${if_var}"
