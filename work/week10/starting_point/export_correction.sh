#!/bin/bash

mkdir starting_point
dir=$1

for file in $(ls $dir); do

  if [ -f $file ]; then
    echo "$file"
    sed -e '/^\s*EXERCISE_BEGIN_CORRECTION/,/EXERCISE_END_CORRECTION/d' $dir/$file \
      > starting_point/$file
  fi
done
