#!/bin/sh
#
# Check every definition in this repository.
#
#   ./check.sh                        check all of them with esbmc
#   ./check.sh nasdaq                 check the ones under a directory
#   ./check.sh path/to.c              check one
#   ./check.sh --concrete [target]    run them with a C compiler instead
#
# Given to esbmc, a definition is checked for every value its records can hold: any record
# written and read back is that record, any bytes read and written back are those bytes, and
# nothing is written or read outside its buffer.
#
# Run concretely, the same file is compiled with CONCRETE defined and executed: the bytes are
# drawn from four patterns rather than chosen by the checker. That needs only a C compiler
# (CC, or cc), and is a test of the definition rather than the claim about it.
#
# Definitions are tried side by side, as many at once as JOBS says or the machine has
# processors, each in a directory of its own.

set -u

mode=esbmc

if [ "${1:-}" = "--concrete" ]; then
  mode=concrete
  shift
fi

target=${1:-.}

if [ -f "$target" ]; then
  definitions=$target
else
  definitions=$(find "$target" -name '*.c' | sort)
fi

if [ -z "$definitions" ]; then
  echo "no definitions under $target"
  exit 1
fi

failures=$(mktemp -d)
jobs=${JOBS:-$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 1)}
count=$(echo "$definitions" | wc -l)

export mode failures

# one definition: tried in a directory of its own, and its log kept only when it fails
echo "$definitions" | xargs -P "$jobs" -n 1 sh -c '
  definition=$1
  work=$(mktemp -d)
  passed=0

  if [ "$mode" = concrete ]; then
    if ${CC:-cc} -std=c99 -DCONCRETE -o "$work/run" "$definition" > "$work/log" 2>&1 && "$work/run" >> "$work/log" 2>&1; then
      passed=1
    fi
  else
    if esbmc "$definition" > "$work/log" 2>&1 && grep -q "VERIFICATION SUCCESSFUL" "$work/log"; then
      passed=1
    fi
  fi

  if [ "$passed" -ne 1 ]; then
    report="$failures/$(echo "$definition" | tr "/" "_")"
    echo "FAIL $definition" > "$report"
    tail -n 40 "$work/log" | sed "s/^/      /" >> "$report"
  fi

  rm -rf "$work"
' check

# the failures together and in the order of their names, whatever order they finished in:
# each was written under its own path, so listing them is sorting them
failed=$(find "$failures" -type f | wc -l)

if [ "$failed" -gt 0 ]; then
  cat "$failures"/*
fi

rm -rf "$failures"

echo "$mode: tried $count definitions, $failed failed"
[ "$failed" -eq 0 ]
