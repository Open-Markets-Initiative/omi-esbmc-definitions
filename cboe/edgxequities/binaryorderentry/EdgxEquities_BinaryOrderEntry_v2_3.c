// cboe/edgxequities/binaryorderentry/EdgxEquities_BinaryOrderEntry_v2_3.c
/*
 * Chicago Board Options Exchange Binary Order Entry
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
 *   - a length prefix framing what follows
 *   - a run counted by a field
 *   - a field present only on a condition
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

/* ---- Message Header: 10 bytes ------------------------------------------------ */

/* 10-byte BOE v2 message header. Every message starts with StartOfMessage = 0xBA 0xBA. */
typedef struct {
  uint8_t start_of_message[2];  /* bytes 0 to 1 */
  uint8_t message_length[2];    /* bytes 2 to 3 */
  uint8_t message_type;         /* byte 4 */
  uint8_t matching_unit;        /* byte 5 */
  uint8_t sequence_number[4];   /* bytes 6 to 9 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->start_of_message[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->message_type = arbitrary();
  record->matching_unit = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Message Header to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->start_of_message[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->message_type;
  wire[at++] = record->matching_unit;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Message Header off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->start_of_message[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->message_type = wire[at++];
  record->matching_unit = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->start_of_message[i] == written->start_of_message[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  assert(read->message_type == written->message_type);
  assert(read->matching_unit == written->matching_unit);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[10];
  uint8_t again[10];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 10);
  assert(decode_message_header(&got, wire, 0) == 10);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 10);
  assert(encode_message_header(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
