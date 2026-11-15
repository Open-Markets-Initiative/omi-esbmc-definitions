// nse/nsecm/snapshot/NseCm_Snapshot_v7_1_Client.c
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
 *   - the dispatch that chooses a message by its type
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

/* ---- Order Book Snapshot Recovery Request Message: 10 bytes ------------------ */

/* Sent to the Orderbook Snapshot Recovery Server to request the order book snapshot. */
typedef struct {
  uint8_t stream_id[2];              /* bytes 0 to 1 */
  uint8_t start_sequence_number[4];  /* bytes 2 to 5 */
  uint8_t end_sequence_number[4];    /* bytes 6 to 9 */
} OrderBookSnapshotRecoveryRequestMessage;

/* any Order Book Snapshot Recovery Request Message at all: every byte one the checker chooses */
static void any_order_book_snapshot_recovery_request_message(OrderBookSnapshotRecoveryRequestMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->start_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_sequence_number[i] = arbitrary(); }
}

/* Order Book Snapshot Recovery Request Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_order_book_snapshot_recovery_request_message(const OrderBookSnapshotRecoveryRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stream_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->start_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_sequence_number[i]; }

  return at;
}

/* Order Book Snapshot Recovery Request Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_order_book_snapshot_recovery_request_message(OrderBookSnapshotRecoveryRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->start_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Book Snapshot Recovery Request Message is what was written, byte for byte */
static void equal_order_book_snapshot_recovery_request_message(const OrderBookSnapshotRecoveryRequestMessage *read, const OrderBookSnapshotRecoveryRequestMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stream_id[i] == written->stream_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->start_sequence_number[i] == written->start_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_sequence_number[i] == written->end_sequence_number[i]); }
}

/* Order Book Snapshot Recovery Request Message: written and read back, then read and written back */
static void check_order_book_snapshot_recovery_request_message(void) {
  OrderBookSnapshotRecoveryRequestMessage sent;
  OrderBookSnapshotRecoveryRequestMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_order_book_snapshot_recovery_request_message(&sent);
  assert(encode_order_book_snapshot_recovery_request_message(&sent, wire, 0) == 10);
  assert(decode_order_book_snapshot_recovery_request_message(&got, wire, 0) == 10);
  equal_order_book_snapshot_recovery_request_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_snapshot_recovery_request_message(&got, wire, 0) == 10);
  assert(encode_order_book_snapshot_recovery_request_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_order_book_snapshot_recovery_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
