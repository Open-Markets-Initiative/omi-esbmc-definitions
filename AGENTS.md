# Agent Notes

Every file in this repository is generated from the Open Markets Initiative binary data
models. Editing one here is lost on the next generation: the change belongs in the generator
or in the model it reads.

## What is here

- `<organization>/<division>/<protocol>/<Name>.c` — one definition per protocol framing: a
  struct per record, an encoder, a decoder, and a check that the two agree. Each definition
  is self contained, so esbmc reads one without reading any other.
- `check.sh`, `Makefile` — what a check runs.

## Checking it

```sh
sh ./check.sh                           # every definition, with esbmc
sh ./check.sh nasdaq                    # the ones under a directory
sh ./check.sh path/to/Definition.c      # one
sh ./check.sh --concrete                # every definition, with a C compiler instead
```

Each definition is tried in a directory of its own and several are tried at once, so
nothing a checker or a compiler leaves behind is shared between two of them.

A definition that does not check is a generator defect, not a file to patch.

## What a check here claims

For each record, and for every value its bytes can take:

- any record written to the wire and read back is that record, byte for byte, taking
  exactly the record's width each way;
- any bytes read off the wire and written back are those bytes;
- no write or read leaves the buffer it is made on, which is exactly the record's width.

That is the claim when the definition is given to esbmc. Built with `CONCRETE` defined the
same file is an ordinary program whose bytes come from four patterns — zero, `32`, `255`, and
a ramp in which each byte differs from the one before — and that run is a test, not the
claim: it needs only a C compiler, and it is what says a definition is C that runs at all.

A field is the bytes it occupies. Nothing is read as an integer, so nothing is read in a
byte order.

A definition's header says what of its model it does **not** state — the framing, the
dispatch, a counted run — so nothing here is read as a claim about a whole packet.

## The same protocols, elsewhere

The Open Markets Initiative provides protocol definitions in several formats:

- [Kaitai Struct Definitions][Kaitai.Definitions.Repository] — Cross language binary parsers with the kaitai struct compiler
- [DFDL Definitions][Dfdl.Definitions.Repository] — Declarative DFDL schemas for cross language parsing
- [P4 Definitions][P4.Definitions.Repository] — P4 programs for software and hardware data planes
- [Spicy Definitions][Spicy.Definitions.Repository] — Declarative Spicy grammars for the spicy toolchain and the zeek network security monitor
- [Lean Definitions][Lean.Definitions.Repository] — Lean 4 definitions with machine checked encode and decode proofs
- [Rocq Definitions][Rocq.Definitions.Repository] — Rocq Prover definitions whose encode and decode proofs the prover checks
- [TLA+ Definitions][Tla.Definitions.Repository] — TLA+ modules whose encode and decode are model checked with TLC
- [Promela Definitions][Promela.Definitions.Repository] — Promela models whose encode and decode are checked by the spin model checker
- [FIX Dictionaries][Fix.Dictionaries.Repository] — QuickFIX format xml data dictionaries, one per FIX version
- [Xml Specifications][Xml.Specifications.Repository] — Formatted exchange specification xmls

[Kaitai.Definitions.Repository]: https://github.com/Open-Markets-Initiative/omi-kaitai-struct-definitions "Omi Kaitai Struct Definitions"
[Dfdl.Definitions.Repository]: https://github.com/Open-Markets-Initiative/omi-dfdl-definitions "Omi DFDL Definitions"
[P4.Definitions.Repository]: https://github.com/Open-Markets-Initiative/omi-p4-definitions "Omi P4 Definitions"
[Spicy.Definitions.Repository]: https://github.com/Open-Markets-Initiative/omi-spicy-definitions "Omi Spicy Definitions"
[Lean.Definitions.Repository]: https://github.com/Open-Markets-Initiative/omi-lean4-definitions "Omi Lean Definitions"
[Rocq.Definitions.Repository]: https://github.com/Open-Markets-Initiative/omi-rocq-definitions "Omi Rocq Definitions"
[Tla.Definitions.Repository]: https://github.com/Open-Markets-Initiative/omi-tlaplus-definitions "Omi TLA+ Definitions"
[Promela.Definitions.Repository]: https://github.com/Open-Markets-Initiative/omi-promela-definitions "Omi Promela Definitions"
[Fix.Dictionaries.Repository]: https://github.com/Open-Markets-Initiative/omi-fix-dictionaries "Omi FIX Dictionaries"
[Xml.Specifications.Repository]: https://github.com/Open-Markets-Initiative/omi-xml-specifications "Omi Xml Specifications"
