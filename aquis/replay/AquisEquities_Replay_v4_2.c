// aquis/replay/AquisEquities_Replay_v4_2.c
/*
 * Aquis Exchange Market Data Replay
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

/* ---- Message Header: 6 bytes ------------------------------------------------- */

/* Aquis market data message header */
typedef struct {
  uint8_t msg_type;    /* byte 0 */
  uint8_t msg_length;  /* byte 1 */
  uint8_t seq_no[4];   /* bytes 2 to 5 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->msg_type = arbitrary();
  record->msg_length = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->seq_no[i] = arbitrary(); }
}

/* Message Header to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->msg_type;
  wire[at++] = record->msg_length;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_no[i]; }

  return at;
}

/* Message Header off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->msg_type = wire[at++];
  record->msg_length = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->msg_type == written->msg_type);
  assert(read->msg_length == written->msg_length);
  for (size_t i = 0; i < 4; i++) { assert(read->seq_no[i] == written->seq_no[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[6];
  uint8_t again[6];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 6);
  assert(decode_message_header(&got, wire, 0) == 6);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 6);
  assert(encode_message_header(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Message: 20 bytes ------------------------------------------------- */

/* If a recipient wishes to use the message replay service, they must first be authenticated by sending a Login message to the relevant replay server. */
typedef struct {
  uint8_t username[10];  /* bytes 0 to 9 */
  uint8_t password[10];  /* bytes 10 to 19 */
} LoginMessage;

/* any Login Message at all: every byte one the checker chooses */
static void any_login_message(LoginMessage *record) {
  for (size_t i = 0; i < 10; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
}

/* Login Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_login_message(const LoginMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }

  return at;
}

/* Login Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_login_message(LoginMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }

  return at;
}

/* what was read of Login Message is what was written, byte for byte */
static void equal_login_message(const LoginMessage *read, const LoginMessage *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
}

/* Login Message: written and read back, then read and written back */
static void check_login_message(void) {
  LoginMessage sent;
  LoginMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_login_message(&sent);
  assert(encode_login_message(&sent, wire, 0) == 20);
  assert(decode_login_message(&got, wire, 0) == 20);
  equal_login_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_login_message(&got, wire, 0) == 20);
  assert(encode_login_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay Request Message: 8 bytes ----------------------------------------- */

/* The recipient sends a Replay Request message to request a particular message or range of messages from the replay server. */
typedef struct {
  uint8_t begin_seq_no[4];  /* bytes 0 to 3 */
  uint8_t end_seq_no[4];    /* bytes 4 to 7 */
} ReplayRequestMessage;

/* any Replay Request Message at all: every byte one the checker chooses */
static void any_replay_request_message(ReplayRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_seq_no[i] = arbitrary(); }
}

/* Replay Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_replay_request_message(const ReplayRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->begin_seq_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_seq_no[i]; }

  return at;
}

/* Replay Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_replay_request_message(ReplayRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Replay Request Message is what was written, byte for byte */
static void equal_replay_request_message(const ReplayRequestMessage *read, const ReplayRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->begin_seq_no[i] == written->begin_seq_no[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_seq_no[i] == written->end_seq_no[i]); }
}

/* Replay Request Message: written and read back, then read and written back */
static void check_replay_request_message(void) {
  ReplayRequestMessage sent;
  ReplayRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_replay_request_message(&sent);
  assert(encode_replay_request_message(&sent, wire, 0) == 8);
  assert(decode_replay_request_message(&got, wire, 0) == 8);
  equal_replay_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_request_message(&got, wire, 0) == 8);
  assert(encode_replay_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay Response Message: 1 byte ----------------------------------------- */

/* Aquis will send a Replay Response message to the recipient to acknowledge a successful Login or to report problems with a Resend Request. */
typedef struct {
  uint8_t response_code;  /* byte 0 */
} ReplayResponseMessage;

/* any Replay Response Message at all: every byte one the checker chooses */
static void any_replay_response_message(ReplayResponseMessage *record) {
  record->response_code = arbitrary();
}

/* Replay Response Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_replay_response_message(const ReplayResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->response_code;

  return at;
}

/* Replay Response Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_replay_response_message(ReplayResponseMessage *record, const uint8_t *wire, size_t at) {
  record->response_code = wire[at++];

  return at;
}

/* what was read of Replay Response Message is what was written, byte for byte */
static void equal_replay_response_message(const ReplayResponseMessage *read, const ReplayResponseMessage *written) {
  assert(read->response_code == written->response_code);
}

/* Replay Response Message: written and read back, then read and written back */
static void check_replay_response_message(void) {
  ReplayResponseMessage sent;
  ReplayResponseMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_replay_response_message(&sent);
  assert(encode_replay_response_message(&sent, wire, 0) == 1);
  assert(decode_replay_response_message(&got, wire, 0) == 1);
  equal_replay_response_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_response_message(&got, wire, 0) == 1);
  assert(encode_replay_response_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_login_message();
  check_replay_request_message();
  check_replay_response_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
