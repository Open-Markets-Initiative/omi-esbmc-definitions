// siac/opra/headers/Siac_Opra_Headers_v1.c
/*
 * The Securities Industry Automation Corporation Headers
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
 *   - a Integrity rule
 *   - a run counted by a field
 *   - a length prefix framing what follows
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

/* ---- Block Timestamp: 8 bytes ------------------------------------------------ */

/* Opra packet timestamp */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} BlockTimestamp;

/* any Block Timestamp at all: every byte one the checker chooses */
static void any_block_timestamp(BlockTimestamp *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Block Timestamp to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_block_timestamp(const BlockTimestamp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Block Timestamp off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_block_timestamp(BlockTimestamp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Block Timestamp is what was written, byte for byte */
static void equal_block_timestamp(const BlockTimestamp *read, const BlockTimestamp *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Block Timestamp: written and read back, then read and written back */
static void check_block_timestamp(void) {
  BlockTimestamp sent;
  BlockTimestamp got;
  uint8_t wire[8];
  uint8_t again[8];

  any_block_timestamp(&sent);
  assert(encode_block_timestamp(&sent, wire, 0) == 8);
  assert(decode_block_timestamp(&got, wire, 0) == 8);
  equal_block_timestamp(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_block_timestamp(&got, wire, 0) == 8);
  assert(encode_block_timestamp(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Control Message: 10 bytes ----------------------------------------------- */

/* Control message */
typedef struct {
  uint8_t control_message_type;             /* byte 0 */
  uint8_t message_indicator;                /* byte 1 */
  uint8_t transaction_id[4];                /* bytes 2 to 5 */
  uint8_t participant_reference_number[4];  /* bytes 6 to 9 */
} ControlMessage;

/* any Control Message at all: every byte one the checker chooses */
static void any_control_message(ControlMessage *record) {
  record->control_message_type = arbitrary();
  record->message_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Control Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_control_message(const ControlMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->control_message_type;
  wire[at++] = record->message_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Control Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_control_message(ControlMessage *record, const uint8_t *wire, size_t at) {
  record->control_message_type = wire[at++];
  record->message_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Control Message is what was written, byte for byte */
static void equal_control_message(const ControlMessage *read, const ControlMessage *written) {
  assert(read->control_message_type == written->control_message_type);
  assert(read->message_indicator == written->message_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Control Message: written and read back, then read and written back */
static void check_control_message(void) {
  ControlMessage sent;
  ControlMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_control_message(&sent);
  assert(encode_control_message(&sent, wire, 0) == 10);
  assert(decode_control_message(&got, wire, 0) == 10);
  equal_control_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_control_message(&got, wire, 0) == 10);
  assert(encode_control_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_block_timestamp();
  check_control_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
