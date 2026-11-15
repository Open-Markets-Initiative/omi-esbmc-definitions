// nse/nsecd/recovery/NseCd_Recovery_v6_9_Tcp.c
/*
 * National Stock Exchange of India Ltd Mtbt Tick Data Recovery
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
 *   - the dispatch that chooses a message by its type
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

/* ---- Stream Header: 8 bytes -------------------------------------------------- */

/* STREAM_HEADER */
typedef struct {
  uint8_t message_length[2];   /* bytes 0 to 1 */
  uint8_t stream_id[2];        /* bytes 2 to 3 */
  uint8_t sequence_number[4];  /* bytes 4 to 7 */
} StreamHeader;

/* any Stream Header at all: every byte one the checker chooses */
static void any_stream_header(StreamHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Stream Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_stream_header(const StreamHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stream_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Stream Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_stream_header(StreamHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Stream Header is what was written, byte for byte */
static void equal_stream_header(const StreamHeader *read, const StreamHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->stream_id[i] == written->stream_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Stream Header: written and read back, then read and written back */
static void check_stream_header(void) {
  StreamHeader sent;
  StreamHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_stream_header(&sent);
  assert(encode_stream_header(&sent, wire, 0) == 8);
  assert(decode_stream_header(&got, wire, 0) == 8);
  equal_stream_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_stream_header(&got, wire, 0) == 8);
  assert(encode_stream_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat Message: 4 bytes ---------------------------------------------- */

/* Heartbeat message will be sent when there is no data available for a few seconds. Only applicable for UDP TBT multicast channels. */
typedef struct {
  uint8_t last_sequence_no[4];  /* bytes 0 to 3 */
} HeartbeatMessage;

/* any Heartbeat Message at all: every byte one the checker chooses */
static void any_heartbeat_message(HeartbeatMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->last_sequence_no[i] = arbitrary(); }
}

/* Heartbeat Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat_message(const HeartbeatMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_sequence_no[i]; }

  return at;
}

/* Heartbeat Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat_message(HeartbeatMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_sequence_no[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat Message is what was written, byte for byte */
static void equal_heartbeat_message(const HeartbeatMessage *read, const HeartbeatMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_sequence_no[i] == written->last_sequence_no[i]); }
}

/* Heartbeat Message: written and read back, then read and written back */
static void check_heartbeat_message(void) {
  HeartbeatMessage sent;
  HeartbeatMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_heartbeat_message(&sent);
  assert(encode_heartbeat_message(&sent, wire, 0) == 4);
  assert(decode_heartbeat_message(&got, wire, 0) == 4);
  equal_heartbeat_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat_message(&got, wire, 0) == 4);
  assert(encode_heartbeat_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Data Recovery Response Message: 1 byte ----------------------------- */

/* First message sent by the Recovery Server, indicating whether the request was processed successfully. */
typedef struct {
  uint8_t request_status;  /* byte 0 */
} TickDataRecoveryResponseMessage;

/* any Tick Data Recovery Response Message at all: every byte one the checker chooses */
static void any_tick_data_recovery_response_message(TickDataRecoveryResponseMessage *record) {
  record->request_status = arbitrary();
}

/* Tick Data Recovery Response Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_tick_data_recovery_response_message(const TickDataRecoveryResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->request_status;

  return at;
}

/* Tick Data Recovery Response Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_tick_data_recovery_response_message(TickDataRecoveryResponseMessage *record, const uint8_t *wire, size_t at) {
  record->request_status = wire[at++];

  return at;
}

/* what was read of Tick Data Recovery Response Message is what was written, byte for byte */
static void equal_tick_data_recovery_response_message(const TickDataRecoveryResponseMessage *read, const TickDataRecoveryResponseMessage *written) {
  assert(read->request_status == written->request_status);
}

/* Tick Data Recovery Response Message: written and read back, then read and written back */
static void check_tick_data_recovery_response_message(void) {
  TickDataRecoveryResponseMessage sent;
  TickDataRecoveryResponseMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_tick_data_recovery_response_message(&sent);
  assert(encode_tick_data_recovery_response_message(&sent, wire, 0) == 1);
  assert(decode_tick_data_recovery_response_message(&got, wire, 0) == 1);
  equal_tick_data_recovery_response_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_data_recovery_response_message(&got, wire, 0) == 1);
  assert(encode_tick_data_recovery_response_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_stream_header();
  check_heartbeat_message();
  check_tick_data_recovery_response_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
