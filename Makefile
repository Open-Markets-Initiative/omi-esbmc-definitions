# Check every definition, and both claims of every record within it.
#
#   make             check everything with esbmc
#   make concrete    run everything with a C compiler instead
#
# The work is in check.sh, which tries each definition in a directory of its own, so
# there is nothing left here to clean.

all: check

check:
	sh ./check.sh

concrete:
	sh ./check.sh --concrete

.PHONY: all check concrete
