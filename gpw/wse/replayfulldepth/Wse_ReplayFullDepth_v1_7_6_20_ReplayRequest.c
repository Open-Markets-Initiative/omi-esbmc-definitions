// gpw/wse/replayfulldepth/Wse_ReplayFullDepth_v1_7_6_20_ReplayRequest.c
/*
 * Giełda Papierów Wartościowych w Warszawie Warsaw Stock Exchange Full Depth Replay
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

/* ---- Replay Request Header: 4 bytes ------------------------------------------ */

/* The replay request carries a four byte header of its own, not the 42 byte market data header */
typedef struct {
  uint8_t replay_message_length[2];  /* bytes 0 to 1 */
  uint8_t replay_message_type[2];    /* bytes 2 to 3 */
} ReplayRequestHeader;

/* any Replay Request Header at all: every byte one the checker chooses */
static void any_replay_request_header(ReplayRequestHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->replay_message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->replay_message_type[i] = arbitrary(); }
}

/* Replay Request Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_replay_request_header(const ReplayRequestHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->replay_message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->replay_message_type[i]; }

  return at;
}

/* Replay Request Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_replay_request_header(ReplayRequestHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->replay_message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->replay_message_type[i] = wire[at++]; }

  return at;
}

/* what was read of Replay Request Header is what was written, byte for byte */
static void equal_replay_request_header(const ReplayRequestHeader *read, const ReplayRequestHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->replay_message_length[i] == written->replay_message_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->replay_message_type[i] == written->replay_message_type[i]); }
}

/* Replay Request Header: written and read back, then read and written back */
static void check_replay_request_header(void) {
  ReplayRequestHeader sent;
  ReplayRequestHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_replay_request_header(&sent);
  assert(encode_replay_request_header(&sent, wire, 0) == 4);
  assert(decode_replay_request_header(&got, wire, 0) == 4);
  equal_replay_request_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_request_header(&got, wire, 0) == 4);
  assert(encode_replay_request_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay Request: 9 bytes ------------------------------------------------- */

/* Message replay request */
typedef struct {
  uint8_t seq_num[4];      /* bytes 0 to 3 */
  uint8_t end_seq_num[4];  /* bytes 4 to 7 */
  uint8_t stream_id;       /* byte 8 */
} ReplayRequest;

/* any Replay Request at all: every byte one the checker chooses */
static void any_replay_request(ReplayRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = arbitrary(); }
  record->stream_id = arbitrary();
}

/* Replay Request to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_replay_request(const ReplayRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_seq_num[i]; }
  wire[at++] = record->stream_id;

  return at;
}

/* Replay Request off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_replay_request(ReplayRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = wire[at++]; }
  record->stream_id = wire[at++];

  return at;
}

/* what was read of Replay Request is what was written, byte for byte */
static void equal_replay_request(const ReplayRequest *read, const ReplayRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_seq_num[i] == written->end_seq_num[i]); }
  assert(read->stream_id == written->stream_id);
}

/* Replay Request: written and read back, then read and written back */
static void check_replay_request(void) {
  ReplayRequest sent;
  ReplayRequest got;
  uint8_t wire[9];
  uint8_t again[9];

  any_replay_request(&sent);
  assert(encode_replay_request(&sent, wire, 0) == 9);
  assert(decode_replay_request(&got, wire, 0) == 9);
  equal_replay_request(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_request(&got, wire, 0) == 9);
  assert(encode_replay_request(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_replay_request_header();
  check_replay_request();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
