#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage $0 <build dir>" 1>&2
  exit 1
fi

script=`dirname $0`/run_single_benchmarks.sh
$script "$1" \
        "btree_seq segmented_tree_seq" \
        "" \
        "btree_seq segmented_tree_seq" \
        ""

