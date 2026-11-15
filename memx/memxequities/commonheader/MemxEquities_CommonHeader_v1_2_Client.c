// memx/memxequities/commonheader/MemxEquities_CommonHeader_v1_2_Client.c
/*
 * The Members Exchange Common Header
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

/* ---- Common Header: 3 bytes -------------------------------------------------- */

/* Tcp Common Header */
typedef struct {
  uint8_t message_type;       /* byte 0 */
  uint8_t message_length[2];  /* bytes 1 to 2 */
} CommonHeader;

/* any Common Header at all: every byte one the checker chooses */
static void any_common_header(CommonHeader *record) {
  record->message_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
}

/* Common Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_common_header(const CommonHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }

  return at;
}

/* Common Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_common_header(CommonHeader *record, const uint8_t *wire, size_t at) {
  record->message_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }

  return at;
}

/* what was read of Common Header is what was written, byte for byte */
static void equal_common_header(const CommonHeader *read, const CommonHeader *written) {
  assert(read->message_type == written->message_type);
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
}

/* Common Header: written and read back, then read and written back */
static void check_common_header(void) {
  CommonHeader sent;
  CommonHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_common_header(&sent);
  assert(encode_common_header(&sent, wire, 0) == 3);
  assert(decode_common_header(&got, wire, 0) == 3);
  equal_common_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_common_header(&got, wire, 0) == 3);
  assert(encode_common_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request Message: 2 bytes ------------------------------------------ */

/* Memx Tcp Login message */
typedef struct {
  uint8_t token_type;  /* byte 0 */
  uint8_t token;       /* byte 1 */
} LoginRequestMessage;

/* any Login Request Message at all: every byte one the checker chooses */
static void any_login_request_message(LoginRequestMessage *record) {
  record->token_type = arbitrary();
  record->token = arbitrary();
}

/* Login Request Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_login_request_message(const LoginRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->token_type;
  wire[at++] = record->token;

  return at;
}

/* Login Request Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_login_request_message(LoginRequestMessage *record, const uint8_t *wire, size_t at) {
  record->token_type = wire[at++];
  record->token = wire[at++];

  return at;
}

/* what was read of Login Request Message is what was written, byte for byte */
static void equal_login_request_message(const LoginRequestMessage *read, const LoginRequestMessage *written) {
  assert(read->token_type == written->token_type);
  assert(read->token == written->token);
}

/* Login Request Message: written and read back, then read and written back */
static void check_login_request_message(void) {
  LoginRequestMessage sent;
  LoginRequestMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_login_request_message(&sent);
  assert(encode_login_request_message(&sent, wire, 0) == 2);
  assert(decode_login_request_message(&got, wire, 0) == 2);
  equal_login_request_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_message(&got, wire, 0) == 2);
  assert(encode_login_request_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay Request Message: 20 bytes ---------------------------------------- */

/* Memx Tcp Replay Request message */
typedef struct {
  uint8_t session_id[8];            /* bytes 0 to 7 */
  uint8_t next_sequence_number[8];  /* bytes 8 to 15 */
  uint8_t count[4];                 /* bytes 16 to 19 */
} ReplayRequestMessage;

/* any Replay Request Message at all: every byte one the checker chooses */
static void any_replay_request_message(ReplayRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count[i] = arbitrary(); }
}

/* Replay Request Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_replay_request_message(const ReplayRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count[i]; }

  return at;
}

/* Replay Request Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_replay_request_message(ReplayRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count[i] = wire[at++]; }

  return at;
}

/* what was read of Replay Request Message is what was written, byte for byte */
static void equal_replay_request_message(const ReplayRequestMessage *read, const ReplayRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->next_sequence_number[i] == written->next_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count[i] == written->count[i]); }
}

/* Replay Request Message: written and read back, then read and written back */
static void check_replay_request_message(void) {
  ReplayRequestMessage sent;
  ReplayRequestMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_replay_request_message(&sent);
  assert(encode_replay_request_message(&sent, wire, 0) == 20);
  assert(decode_replay_request_message(&got, wire, 0) == 20);
  equal_replay_request_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_request_message(&got, wire, 0) == 20);
  assert(encode_replay_request_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay All Request Message: 8 bytes ------------------------------------- */

/* Memx Tcp Replay All Request message */
typedef struct {
  uint8_t session_id[8];  /* bytes 0 to 7 */
} ReplayAllRequestMessage;

/* any Replay All Request Message at all: every byte one the checker chooses */
static void any_replay_all_request_message(ReplayAllRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = arbitrary(); }
}

/* Replay All Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_replay_all_request_message(const ReplayAllRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_id[i]; }

  return at;
}

/* Replay All Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_replay_all_request_message(ReplayAllRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Replay All Request Message is what was written, byte for byte */
static void equal_replay_all_request_message(const ReplayAllRequestMessage *read, const ReplayAllRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session_id[i] == written->session_id[i]); }
}

/* Replay All Request Message: written and read back, then read and written back */
static void check_replay_all_request_message(void) {
  ReplayAllRequestMessage sent;
  ReplayAllRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_replay_all_request_message(&sent);
  assert(encode_replay_all_request_message(&sent, wire, 0) == 8);
  assert(decode_replay_all_request_message(&got, wire, 0) == 8);
  equal_replay_all_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_all_request_message(&got, wire, 0) == 8);
  assert(encode_replay_all_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stream Request Message: 16 bytes ---------------------------------------- */

/* Memx Tcp Stream Request message */
typedef struct {
  uint8_t session_id[8];            /* bytes 0 to 7 */
  uint8_t next_sequence_number[8];  /* bytes 8 to 15 */
} StreamRequestMessage;

/* any Stream Request Message at all: every byte one the checker chooses */
static void any_stream_request_message(StreamRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = arbitrary(); }
}

/* Stream Request Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_stream_request_message(const StreamRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_sequence_number[i]; }

  return at;
}

/* Stream Request Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_stream_request_message(StreamRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Stream Request Message is what was written, byte for byte */
static void equal_stream_request_message(const StreamRequestMessage *read, const StreamRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->next_sequence_number[i] == written->next_sequence_number[i]); }
}

/* Stream Request Message: written and read back, then read and written back */
static void check_stream_request_message(void) {
  StreamRequestMessage sent;
  StreamRequestMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_stream_request_message(&sent);
  assert(encode_stream_request_message(&sent, wire, 0) == 16);
  assert(decode_stream_request_message(&got, wire, 0) == 16);
  equal_stream_request_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_stream_request_message(&got, wire, 0) == 16);
  assert(encode_stream_request_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_common_header();
  check_login_request_message();
  check_replay_request_message();
  check_replay_all_request_message();
  check_stream_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
