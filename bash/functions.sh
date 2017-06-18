#!/bin/bash

VALUE=foo
testy # command not found

function testy {
  echo $VALUE
}

VALUE=bar
testy # bar
VALUE=baz
testy # baz
