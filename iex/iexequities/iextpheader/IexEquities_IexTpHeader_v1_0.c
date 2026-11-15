// iex/iexequities/iextpheader/IexEquities_IexTpHeader_v1_0.c
/*
 * Investors Exchange IexTp Header
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

/* ---- Iextp Header: 40 bytes -------------------------------------------------- */

/* IexTp packet header */
typedef struct {
  uint8_t version;                           /* byte 0 */
  uint8_t reserved;                          /* byte 1 */
  uint8_t message_protocol_id[2];            /* bytes 2 to 3 */
  uint8_t channel_id[4];                     /* bytes 4 to 7 */
  uint8_t session_id[4];                     /* bytes 8 to 11 */
  uint8_t payload_length[2];                 /* bytes 12 to 13 */
  uint8_t message_count[2];                  /* bytes 14 to 15 */
  uint8_t stream_offset[8];                  /* bytes 16 to 23 */
  uint8_t first_message_sequence_number[8];  /* bytes 24 to 31 */
  uint8_t send_time[8];                      /* bytes 32 to 39 */
} IextpHeader;

/* any Iextp Header at all: every byte one the checker chooses */
static void any_iextp_header(IextpHeader *record) {
  record->version = arbitrary();
  record->reserved = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->message_protocol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->payload_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stream_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->first_message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = arbitrary(); }
}

/* Iextp Header to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_iextp_header(const IextpHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->version;
  wire[at++] = record->reserved;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_protocol_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->channel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->payload_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stream_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->first_message_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->send_time[i]; }

  return at;
}

/* Iextp Header off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_iextp_header(IextpHeader *record, const uint8_t *wire, size_t at) {
  record->version = wire[at++];
  record->reserved = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->message_protocol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->channel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->payload_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stream_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->first_message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = wire[at++]; }

  return at;
}

/* what was read of Iextp Header is what was written, byte for byte */
static void equal_iextp_header(const IextpHeader *read, const IextpHeader *written) {
  assert(read->version == written->version);
  assert(read->reserved == written->reserved);
  for (size_t i = 0; i < 2; i++) { assert(read->message_protocol_id[i] == written->message_protocol_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->channel_id[i] == written->channel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->payload_length[i] == written->payload_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_count[i] == written->message_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stream_offset[i] == written->stream_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->first_message_sequence_number[i] == written->first_message_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->send_time[i] == written->send_time[i]); }
}

/* Iextp Header: written and read back, then read and written back */
static void check_iextp_header(void) {
  IextpHeader sent;
  IextpHeader got;
  uint8_t wire[40];
  uint8_t again[40];

  any_iextp_header(&sent);
  assert(encode_iextp_header(&sent, wire, 0) == 40);
  assert(decode_iextp_header(&got, wire, 0) == 40);
  equal_iextp_header(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_iextp_header(&got, wire, 0) == 40);
  assert(encode_iextp_header(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* IexTp message header */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t message_type;       /* byte 2 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 3);
  assert(decode_message_header(&got, wire, 0) == 3);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 3);
  assert(encode_message_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_iextp_header();
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
