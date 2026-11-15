// tmx/tsxalpha/quantumfeedlevel2recovery/TsxAlpha_QuantumFeedLevel2Recovery_v2_1_Client.c
/*
 * TMX Group Quantum Feed Level 2 Recovery
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
 *   - a run filling what frames it
 *   - a length prefix framing what follows
 *   - a run counted by a field
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

/* ---- Frame Header: 11 bytes -------------------------------------------------- */

/* XMT frame prefix and outer header. */
typedef struct {
  uint8_t start_of_frame;         /* byte 0 */
  uint8_t protocol_name;          /* byte 1 */
  uint8_t protocol_version;       /* byte 2 */
  uint8_t message_length[2];      /* bytes 3 to 4 */
  uint8_t session_id[4];          /* bytes 5 to 8 */
  uint8_t ack_required_poss_dup;  /* byte 9 */
  uint8_t num_body;               /* byte 10 */
} FrameHeader;

/* any Frame Header at all: every byte one the checker chooses */
static void any_frame_header(FrameHeader *record) {
  record->start_of_frame = arbitrary();
  record->protocol_name = arbitrary();
  record->protocol_version = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  record->ack_required_poss_dup = arbitrary();
  record->num_body = arbitrary();
}

/* Frame Header to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_frame_header(const FrameHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->start_of_frame;
  wire[at++] = record->protocol_name;
  wire[at++] = record->protocol_version;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  wire[at++] = record->ack_required_poss_dup;
  wire[at++] = record->num_body;

  return at;
}

/* Frame Header off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_frame_header(FrameHeader *record, const uint8_t *wire, size_t at) {
  record->start_of_frame = wire[at++];
  record->protocol_name = wire[at++];
  record->protocol_version = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  record->ack_required_poss_dup = wire[at++];
  record->num_body = wire[at++];

  return at;
}

/* what was read of Frame Header is what was written, byte for byte */
static void equal_frame_header(const FrameHeader *read, const FrameHeader *written) {
  assert(read->start_of_frame == written->start_of_frame);
  assert(read->protocol_name == written->protocol_name);
  assert(read->protocol_version == written->protocol_version);
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  assert(read->ack_required_poss_dup == written->ack_required_poss_dup);
  assert(read->num_body == written->num_body);
}

/* Frame Header: written and read back, then read and written back */
static void check_frame_header(void) {
  FrameHeader sent;
  FrameHeader got;
  uint8_t wire[11];
  uint8_t again[11];

  any_frame_header(&sent);
  assert(encode_frame_header(&sent, wire, 0) == 11);
  assert(decode_frame_header(&got, wire, 0) == 11);
  equal_frame_header(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_frame_header(&got, wire, 0) == 11);
  assert(encode_frame_header(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Body Header: 3 bytes ---------------------------------------------------- */

/* Xmt Body Header */
typedef struct {
  uint8_t msg_length[2];  /* bytes 0 to 1 */
  uint8_t msg_type;       /* byte 2 */
} BodyHeader;

/* any Body Header at all: every byte one the checker chooses */
static void any_body_header(BodyHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = arbitrary(); }
  record->msg_type = arbitrary();
}

/* Body Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_body_header(const BodyHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_length[i]; }
  wire[at++] = record->msg_type;

  return at;
}

/* Body Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_body_header(BodyHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = wire[at++]; }
  record->msg_type = wire[at++];

  return at;
}

/* what was read of Body Header is what was written, byte for byte */
static void equal_body_header(const BodyHeader *read, const BodyHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->msg_length[i] == written->msg_length[i]); }
  assert(read->msg_type == written->msg_type);
}

/* Body Header: written and read back, then read and written back */
static void check_body_header(void) {
  BodyHeader sent;
  BodyHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_body_header(&sent);
  assert(encode_body_header(&sent, wire, 0) == 3);
  assert(decode_body_header(&got, wire, 0) == 3);
  equal_body_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_body_header(&got, wire, 0) == 3);
  assert(encode_body_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_frame_header();
  check_body_header();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
