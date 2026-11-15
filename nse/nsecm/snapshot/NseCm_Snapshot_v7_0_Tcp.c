// nse/nsecm/snapshot/NseCm_Snapshot_v7_0_Tcp.c
/*
 * National Stock Exchange of India Ltd Mtbt Order Book Snapshot Recovery
 *
 * Generated from the binary model. Every record is a run of fields, and esbmc checks two
 * claims of each, for every value its bytes can take rather than for chosen ones: that any
 * record written to the wire and read back is that record, and that any bytes read off the
 * wire and written back are those bytes. Each takes exactly the record's width, and no
 * write or read leaves the buffer it is made on.
 *
 * A field is the bytes it occupies. Nothing is read as an integer, so nothing is read in a
 * byte order, and no rule stated here depends on a value.
 *
 * Check the whole file:   esbmc <file>
 * Check one record:       esbmc <file> --function check_<record>
 *
 * Built with -DCONCRETE it is an ordinary program any C compiler runs: the bytes the
 * checker would choose are drawn from four patterns instead, so the definition can be
 * tried without the checker. That run is a test, and the checker's is the claim.
 *
 * What this definition does not state, and the model does:
 *   - a Reassemble rule
 *   - a run counted by a field
 *   - a Composite rule
 *
 * License: MIT No Attribution
 */

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

/* ---- Any byte ---------------------------------------------------------------- */

#ifdef CONCRETE

/* which pattern the bytes are drawn from, and how many have been drawn */
static unsigned pattern;
static size_t drawn;

/* a byte of the pattern: zero, a space, every bit set, or one more than the last */
static uint8_t arbitrary(void) {
  drawn++;

  switch (pattern) {
    case 0: return 0;
    case 1: return 32;
    case 2: return 255;
    default: return (uint8_t)(drawn % 256);
  }
}

#else

/* declared and never defined: a value the checker chooses */
unsigned char __VERIFIER_nondet_uchar(void);

/* a byte nobody chose, so what holds of it holds of all of them */
static uint8_t arbitrary(void) {
  return __VERIFIER_nondet_uchar();
}

#endif

/* ---- Snapshot Header: 16 bytes ----------------------------------------------- */

/* Snapshot header has a size of 16 bytes */
typedef struct {
  uint8_t trans_code[2];            /* bytes 0 to 1 */
  uint8_t size[4];                  /* bytes 2 to 5 */
  uint8_t number_of_records[4];     /* bytes 6 to 9 */
  uint8_t last_sequence_number[4];  /* bytes 10 to 13 */
  uint8_t stream_id[2];             /* bytes 14 to 15 */
} SnapshotHeader;

/* any Snapshot Header at all: every byte one the checker chooses */
static void any_snapshot_header(SnapshotHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->trans_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_records[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->stream_id[i] = arbitrary(); }
}

/* Snapshot Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_header(const SnapshotHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trans_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_records[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stream_id[i]; }

  return at;
}

/* Snapshot Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_header(SnapshotHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->trans_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_records[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->stream_id[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot Header is what was written, byte for byte */
static void equal_snapshot_header(const SnapshotHeader *read, const SnapshotHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->trans_code[i] == written->trans_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_records[i] == written->number_of_records[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_sequence_number[i] == written->last_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->stream_id[i] == written->stream_id[i]); }
}

/* Snapshot Header: written and read back, then read and written back */
static void check_snapshot_header(void) {
  SnapshotHeader sent;
  SnapshotHeader got;
  uint8_t wire[16];
  uint8_t again[16];

  any_snapshot_header(&sent);
  assert(encode_snapshot_header(&sent, wire, 0) == 16);
  assert(decode_snapshot_header(&got, wire, 0) == 16);
  equal_snapshot_header(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_header(&got, wire, 0) == 16);
  assert(encode_snapshot_header(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_snapshot_header();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
