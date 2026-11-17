// memx/memxoptions/riskcontrol/MemxOptions_RiskControl_v1_7_Server.c
/*
 * The Members Exchange Risk Control
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
 *   - the dispatch that chooses a message by its type
 *   - a block whose stated length holds more than its fields
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

/* ---- Login Accepted Message: 1 byte ------------------------------------------ */

/* Memx Tcp Login Accepted Message */
typedef struct {
  uint8_t supported_request_mode;  /* byte 0 */
} LoginAcceptedMessage;

/* any Login Accepted Message at all: every byte one the checker chooses */
static void any_login_accepted_message(LoginAcceptedMessage *record) {
  record->supported_request_mode = arbitrary();
}

/* Login Accepted Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_login_accepted_message(const LoginAcceptedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->supported_request_mode;

  return at;
}

/* Login Accepted Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_login_accepted_message(LoginAcceptedMessage *record, const uint8_t *wire, size_t at) {
  record->supported_request_mode = wire[at++];

  return at;
}

/* what was read of Login Accepted Message is what was written, byte for byte */
static void equal_login_accepted_message(const LoginAcceptedMessage *read, const LoginAcceptedMessage *written) {
  assert(read->supported_request_mode == written->supported_request_mode);
}

/* Login Accepted Message: written and read back, then read and written back */
static void check_login_accepted_message(void) {
  LoginAcceptedMessage sent;
  LoginAcceptedMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_login_accepted_message(&sent);
  assert(encode_login_accepted_message(&sent, wire, 0) == 1);
  assert(decode_login_accepted_message(&got, wire, 0) == 1);
  equal_login_accepted_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_login_accepted_message(&got, wire, 0) == 1);
  assert(encode_login_accepted_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Rejected Message: 1 byte ------------------------------------------ */

/* Memx Tcp Login Rejected Message */
typedef struct {
  uint8_t login_reject_code;  /* byte 0 */
} LoginRejectedMessage;

/* any Login Rejected Message at all: every byte one the checker chooses */
static void any_login_rejected_message(LoginRejectedMessage *record) {
  record->login_reject_code = arbitrary();
}

/* Login Rejected Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_login_rejected_message(const LoginRejectedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->login_reject_code;

  return at;
}

/* Login Rejected Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_login_rejected_message(LoginRejectedMessage *record, const uint8_t *wire, size_t at) {
  record->login_reject_code = wire[at++];

  return at;
}

/* what was read of Login Rejected Message is what was written, byte for byte */
static void equal_login_rejected_message(const LoginRejectedMessage *read, const LoginRejectedMessage *written) {
  assert(read->login_reject_code == written->login_reject_code);
}

/* Login Rejected Message: written and read back, then read and written back */
static void check_login_rejected_message(void) {
  LoginRejectedMessage sent;
  LoginRejectedMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_login_rejected_message(&sent);
  assert(encode_login_rejected_message(&sent, wire, 0) == 1);
  assert(decode_login_rejected_message(&got, wire, 0) == 1);
  equal_login_rejected_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_login_rejected_message(&got, wire, 0) == 1);
  assert(encode_login_rejected_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Session Message: 8 bytes --------------------------------------- */

/* Memx Tcp Start of Session Message */
typedef struct {
  uint8_t session_id[8];  /* bytes 0 to 7 */
} StartOfSessionMessage;

/* any Start Of Session Message at all: every byte one the checker chooses */
static void any_start_of_session_message(StartOfSessionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = arbitrary(); }
}

/* Start Of Session Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_start_of_session_message(const StartOfSessionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_id[i]; }

  return at;
}

/* Start Of Session Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_start_of_session_message(StartOfSessionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Start Of Session Message is what was written, byte for byte */
static void equal_start_of_session_message(const StartOfSessionMessage *read, const StartOfSessionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session_id[i] == written->session_id[i]); }
}

/* Start Of Session Message: written and read back, then read and written back */
static void check_start_of_session_message(void) {
  StartOfSessionMessage sent;
  StartOfSessionMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_start_of_session_message(&sent);
  assert(encode_start_of_session_message(&sent, wire, 0) == 8);
  assert(decode_start_of_session_message(&got, wire, 0) == 8);
  equal_start_of_session_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_session_message(&got, wire, 0) == 8);
  assert(encode_start_of_session_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay Begin Message: 12 bytes ------------------------------------------ */

/* Memx Tcp Replay Begin Message */
typedef struct {
  uint8_t next_sequence_number[8];   /* bytes 0 to 7 */
  uint8_t pending_message_count[4];  /* bytes 8 to 11 */
} ReplayBeginMessage;

/* any Replay Begin Message at all: every byte one the checker chooses */
static void any_replay_begin_message(ReplayBeginMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pending_message_count[i] = arbitrary(); }
}

/* Replay Begin Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_replay_begin_message(const ReplayBeginMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pending_message_count[i]; }

  return at;
}

/* Replay Begin Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_replay_begin_message(ReplayBeginMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pending_message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Replay Begin Message is what was written, byte for byte */
static void equal_replay_begin_message(const ReplayBeginMessage *read, const ReplayBeginMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->next_sequence_number[i] == written->next_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pending_message_count[i] == written->pending_message_count[i]); }
}

/* Replay Begin Message: written and read back, then read and written back */
static void check_replay_begin_message(void) {
  ReplayBeginMessage sent;
  ReplayBeginMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_replay_begin_message(&sent);
  assert(encode_replay_begin_message(&sent, wire, 0) == 12);
  assert(decode_replay_begin_message(&got, wire, 0) == 12);
  equal_replay_begin_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_begin_message(&got, wire, 0) == 12);
  assert(encode_replay_begin_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay Rejected Message: 1 byte ----------------------------------------- */

/* Memx Tcp Replay Rejected Message */
typedef struct {
  uint8_t replay_reject_code;  /* byte 0 */
} ReplayRejectedMessage;

/* any Replay Rejected Message at all: every byte one the checker chooses */
static void any_replay_rejected_message(ReplayRejectedMessage *record) {
  record->replay_reject_code = arbitrary();
}

/* Replay Rejected Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_replay_rejected_message(const ReplayRejectedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->replay_reject_code;

  return at;
}

/* Replay Rejected Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_replay_rejected_message(ReplayRejectedMessage *record, const uint8_t *wire, size_t at) {
  record->replay_reject_code = wire[at++];

  return at;
}

/* what was read of Replay Rejected Message is what was written, byte for byte */
static void equal_replay_rejected_message(const ReplayRejectedMessage *read, const ReplayRejectedMessage *written) {
  assert(read->replay_reject_code == written->replay_reject_code);
}

/* Replay Rejected Message: written and read back, then read and written back */
static void check_replay_rejected_message(void) {
  ReplayRejectedMessage sent;
  ReplayRejectedMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_replay_rejected_message(&sent);
  assert(encode_replay_rejected_message(&sent, wire, 0) == 1);
  assert(decode_replay_rejected_message(&got, wire, 0) == 1);
  equal_replay_rejected_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_rejected_message(&got, wire, 0) == 1);
  assert(encode_replay_rejected_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay Complete Message: 8 bytes ---------------------------------------- */

/* Memx Tcp Replay Complete Message */
typedef struct {
  uint8_t message_count[8];  /* bytes 0 to 7 */
} ReplayCompleteMessage;

/* any Replay Complete Message at all: every byte one the checker chooses */
static void any_replay_complete_message(ReplayCompleteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_count[i] = arbitrary(); }
}

/* Replay Complete Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_replay_complete_message(const ReplayCompleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_count[i]; }

  return at;
}

/* Replay Complete Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_replay_complete_message(ReplayCompleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Replay Complete Message is what was written, byte for byte */
static void equal_replay_complete_message(const ReplayCompleteMessage *read, const ReplayCompleteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_count[i] == written->message_count[i]); }
}

/* Replay Complete Message: written and read back, then read and written back */
static void check_replay_complete_message(void) {
  ReplayCompleteMessage sent;
  ReplayCompleteMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_replay_complete_message(&sent);
  assert(encode_replay_complete_message(&sent, wire, 0) == 8);
  assert(decode_replay_complete_message(&got, wire, 0) == 8);
  equal_replay_complete_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_complete_message(&got, wire, 0) == 8);
  assert(encode_replay_complete_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stream Begin Message: 16 bytes ------------------------------------------ */

/* Memx Tcp Stream Begin Message */
typedef struct {
  uint8_t next_sequence_number[8];  /* bytes 0 to 7 */
  uint8_t max_sequence_number[8];   /* bytes 8 to 15 */
} StreamBeginMessage;

/* any Stream Begin Message at all: every byte one the checker chooses */
static void any_stream_begin_message(StreamBeginMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_sequence_number[i] = arbitrary(); }
}

/* Stream Begin Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_stream_begin_message(const StreamBeginMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_sequence_number[i]; }

  return at;
}

/* Stream Begin Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_stream_begin_message(StreamBeginMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Stream Begin Message is what was written, byte for byte */
static void equal_stream_begin_message(const StreamBeginMessage *read, const StreamBeginMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->next_sequence_number[i] == written->next_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_sequence_number[i] == written->max_sequence_number[i]); }
}

/* Stream Begin Message: written and read back, then read and written back */
static void check_stream_begin_message(void) {
  StreamBeginMessage sent;
  StreamBeginMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_stream_begin_message(&sent);
  assert(encode_stream_begin_message(&sent, wire, 0) == 16);
  assert(decode_stream_begin_message(&got, wire, 0) == 16);
  equal_stream_begin_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_stream_begin_message(&got, wire, 0) == 16);
  assert(encode_stream_begin_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stream Rejected Message: 1 byte ----------------------------------------- */

/* Memx Tcp Stream Rejected Message */
typedef struct {
  uint8_t stream_reject_code;  /* byte 0 */
} StreamRejectedMessage;

/* any Stream Rejected Message at all: every byte one the checker chooses */
static void any_stream_rejected_message(StreamRejectedMessage *record) {
  record->stream_reject_code = arbitrary();
}

/* Stream Rejected Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_stream_rejected_message(const StreamRejectedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->stream_reject_code;

  return at;
}

/* Stream Rejected Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_stream_rejected_message(StreamRejectedMessage *record, const uint8_t *wire, size_t at) {
  record->stream_reject_code = wire[at++];

  return at;
}

/* what was read of Stream Rejected Message is what was written, byte for byte */
static void equal_stream_rejected_message(const StreamRejectedMessage *read, const StreamRejectedMessage *written) {
  assert(read->stream_reject_code == written->stream_reject_code);
}

/* Stream Rejected Message: written and read back, then read and written back */
static void check_stream_rejected_message(void) {
  StreamRejectedMessage sent;
  StreamRejectedMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_stream_rejected_message(&sent);
  assert(encode_stream_rejected_message(&sent, wire, 0) == 1);
  assert(decode_stream_rejected_message(&got, wire, 0) == 1);
  equal_stream_rejected_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_stream_rejected_message(&got, wire, 0) == 1);
  assert(encode_stream_rejected_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stream Complete Message: 8 bytes ---------------------------------------- */

/* Memx Tcp Stream Complete Message */
typedef struct {
  uint8_t total_sequence_count[8];  /* bytes 0 to 7 */
} StreamCompleteMessage;

/* any Stream Complete Message at all: every byte one the checker chooses */
static void any_stream_complete_message(StreamCompleteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->total_sequence_count[i] = arbitrary(); }
}

/* Stream Complete Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_stream_complete_message(const StreamCompleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_sequence_count[i]; }

  return at;
}

/* Stream Complete Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_stream_complete_message(StreamCompleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->total_sequence_count[i] = wire[at++]; }

  return at;
}

/* what was read of Stream Complete Message is what was written, byte for byte */
static void equal_stream_complete_message(const StreamCompleteMessage *read, const StreamCompleteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->total_sequence_count[i] == written->total_sequence_count[i]); }
}

/* Stream Complete Message: written and read back, then read and written back */
static void check_stream_complete_message(void) {
  StreamCompleteMessage sent;
  StreamCompleteMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_stream_complete_message(&sent);
  assert(encode_stream_complete_message(&sent, wire, 0) == 8);
  assert(decode_stream_complete_message(&got, wire, 0) == 8);
  equal_stream_complete_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_stream_complete_message(&got, wire, 0) == 8);
  assert(encode_stream_complete_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sbe Header: 6 bytes ----------------------------------------------------- */

/* Sbe Header */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id;      /* byte 2 */
  uint8_t schema_id;        /* byte 3 */
  uint8_t version[2];       /* bytes 4 to 5 */
} SbeHeader;

/* any Sbe Header at all: every byte one the checker chooses */
static void any_sbe_header(SbeHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->template_id = arbitrary();
  record->schema_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Sbe Header to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_sbe_header(const SbeHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->template_id;
  wire[at++] = record->schema_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Sbe Header off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_sbe_header(SbeHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->template_id = wire[at++];
  record->schema_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Sbe Header is what was written, byte for byte */
static void equal_sbe_header(const SbeHeader *read, const SbeHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->template_id == written->template_id);
  assert(read->schema_id == written->schema_id);
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Sbe Header: written and read back, then read and written back */
static void check_sbe_header(void) {
  SbeHeader sent;
  SbeHeader got;
  uint8_t wire[6];
  uint8_t again[6];

  any_sbe_header(&sent);
  assert(encode_sbe_header(&sent, wire, 0) == 6);
  assert(decode_sbe_header(&got, wire, 0) == 6);
  equal_sbe_header(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_sbe_header(&got, wire, 0) == 6);
  assert(encode_sbe_header(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Active Risk Threshold State Message: 38 bytes --------------------------- */

/* ActiveRiskThresholdStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];  /* bytes 0 to 19 */
  uint8_t underlier[6];            /* bytes 20 to 25 */
  uint8_t efid[4];                 /* bytes 26 to 29 */
  uint8_t threshold_quantity[4];   /* bytes 30 to 33 */
  uint8_t unacked_quantity[4];     /* bytes 34 to 37 */
} ActiveRiskThresholdStateMessage;

/* any Active Risk Threshold State Message at all: every byte one the checker chooses */
static void any_active_risk_threshold_state_message(ActiveRiskThresholdStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->threshold_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->unacked_quantity[i] = arbitrary(); }
}

/* Active Risk Threshold State Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_active_risk_threshold_state_message(const ActiveRiskThresholdStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->threshold_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unacked_quantity[i]; }

  return at;
}

/* Active Risk Threshold State Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_active_risk_threshold_state_message(ActiveRiskThresholdStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->threshold_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->unacked_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Active Risk Threshold State Message is what was written, byte for byte */
static void equal_active_risk_threshold_state_message(const ActiveRiskThresholdStateMessage *read, const ActiveRiskThresholdStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier[i] == written->underlier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid[i] == written->efid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->threshold_quantity[i] == written->threshold_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->unacked_quantity[i] == written->unacked_quantity[i]); }
}

/* Active Risk Threshold State Message: written and read back, then read and written back */
static void check_active_risk_threshold_state_message(void) {
  ActiveRiskThresholdStateMessage sent;
  ActiveRiskThresholdStateMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_active_risk_threshold_state_message(&sent);
  assert(encode_active_risk_threshold_state_message(&sent, wire, 0) == 38);
  assert(decode_active_risk_threshold_state_message(&got, wire, 0) == 38);
  equal_active_risk_threshold_state_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_active_risk_threshold_state_message(&got, wire, 0) == 38);
  assert(encode_active_risk_threshold_state_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Active Risk Threshold Change Rejected Message: 36 bytes ----------------- */

/* ActiveRiskThresholdChangeRejectedMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
  uint8_t threshold_quantity[4];  /* bytes 30 to 33 */
  uint8_t reject_reason[2];       /* bytes 34 to 35 */
} ActiveRiskThresholdChangeRejectedMessage;

/* any Active Risk Threshold Change Rejected Message at all: every byte one the checker chooses */
static void any_active_risk_threshold_change_rejected_message(ActiveRiskThresholdChangeRejectedMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->threshold_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = arbitrary(); }
}

/* Active Risk Threshold Change Rejected Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_active_risk_threshold_change_rejected_message(const ActiveRiskThresholdChangeRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->threshold_quantity[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reject_reason[i]; }

  return at;
}

/* Active Risk Threshold Change Rejected Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_active_risk_threshold_change_rejected_message(ActiveRiskThresholdChangeRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->threshold_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Active Risk Threshold Change Rejected Message is what was written, byte for byte */
static void equal_active_risk_threshold_change_rejected_message(const ActiveRiskThresholdChangeRejectedMessage *read, const ActiveRiskThresholdChangeRejectedMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->threshold_quantity[i] == written->threshold_quantity[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reject_reason[i] == written->reject_reason[i]); }
}

/* Active Risk Threshold Change Rejected Message: written and read back, then read and written back */
static void check_active_risk_threshold_change_rejected_message(void) {
  ActiveRiskThresholdChangeRejectedMessage sent;
  ActiveRiskThresholdChangeRejectedMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_active_risk_threshold_change_rejected_message(&sent);
  assert(encode_active_risk_threshold_change_rejected_message(&sent, wire, 0) == 36);
  assert(decode_active_risk_threshold_change_rejected_message(&got, wire, 0) == 36);
  equal_active_risk_threshold_change_rejected_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_active_risk_threshold_change_rejected_message(&got, wire, 0) == 36);
  assert(encode_active_risk_threshold_change_rejected_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Active Risk Acknowledged Message: 38 bytes ------------------------------ */

/* ActiveRiskAcknowledgedMessage */
typedef struct {
  uint8_t cl_ord_id[20];        /* bytes 0 to 19 */
  uint8_t underlier[6];         /* bytes 20 to 25 */
  uint8_t efid[4];              /* bytes 26 to 29 */
  uint8_t quantity[4];          /* bytes 30 to 33 */
  uint8_t unacked_quantity[4];  /* bytes 34 to 37 */
} ActiveRiskAcknowledgedMessage;

/* any Active Risk Acknowledged Message at all: every byte one the checker chooses */
static void any_active_risk_acknowledged_message(ActiveRiskAcknowledgedMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->unacked_quantity[i] = arbitrary(); }
}

/* Active Risk Acknowledged Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_active_risk_acknowledged_message(const ActiveRiskAcknowledgedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unacked_quantity[i]; }

  return at;
}

/* Active Risk Acknowledged Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_active_risk_acknowledged_message(ActiveRiskAcknowledgedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->unacked_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Active Risk Acknowledged Message is what was written, byte for byte */
static void equal_active_risk_acknowledged_message(const ActiveRiskAcknowledgedMessage *read, const ActiveRiskAcknowledgedMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier[i] == written->underlier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid[i] == written->efid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->unacked_quantity[i] == written->unacked_quantity[i]); }
}

/* Active Risk Acknowledged Message: written and read back, then read and written back */
static void check_active_risk_acknowledged_message(void) {
  ActiveRiskAcknowledgedMessage sent;
  ActiveRiskAcknowledgedMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_active_risk_acknowledged_message(&sent);
  assert(encode_active_risk_acknowledged_message(&sent, wire, 0) == 38);
  assert(decode_active_risk_acknowledged_message(&got, wire, 0) == 38);
  equal_active_risk_acknowledged_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_active_risk_acknowledged_message(&got, wire, 0) == 38);
  assert(encode_active_risk_acknowledged_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Active Risk Acknowledge Rejected Message: 36 bytes ---------------------- */

/* ActiveRiskAcknowledgeRejectedMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier[6];           /* bytes 20 to 25 */
  uint8_t efid[4];                /* bytes 26 to 29 */
  uint8_t threshold_quantity[4];  /* bytes 30 to 33 */
  uint8_t reject_reason[2];       /* bytes 34 to 35 */
} ActiveRiskAcknowledgeRejectedMessage;

/* any Active Risk Acknowledge Rejected Message at all: every byte one the checker chooses */
static void any_active_risk_acknowledge_rejected_message(ActiveRiskAcknowledgeRejectedMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->threshold_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = arbitrary(); }
}

/* Active Risk Acknowledge Rejected Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_active_risk_acknowledge_rejected_message(const ActiveRiskAcknowledgeRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->threshold_quantity[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reject_reason[i]; }

  return at;
}

/* Active Risk Acknowledge Rejected Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_active_risk_acknowledge_rejected_message(ActiveRiskAcknowledgeRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->threshold_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Active Risk Acknowledge Rejected Message is what was written, byte for byte */
static void equal_active_risk_acknowledge_rejected_message(const ActiveRiskAcknowledgeRejectedMessage *read, const ActiveRiskAcknowledgeRejectedMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier[i] == written->underlier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid[i] == written->efid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->threshold_quantity[i] == written->threshold_quantity[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reject_reason[i] == written->reject_reason[i]); }
}

/* Active Risk Acknowledge Rejected Message: written and read back, then read and written back */
static void check_active_risk_acknowledge_rejected_message(void) {
  ActiveRiskAcknowledgeRejectedMessage sent;
  ActiveRiskAcknowledgeRejectedMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_active_risk_acknowledge_rejected_message(&sent);
  assert(encode_active_risk_acknowledge_rejected_message(&sent, wire, 0) == 36);
  assert(decode_active_risk_acknowledge_rejected_message(&got, wire, 0) == 36);
  equal_active_risk_acknowledge_rejected_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_active_risk_acknowledge_rejected_message(&got, wire, 0) == 36);
  assert(encode_active_risk_acknowledge_rejected_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Active Risk Quantity Update Notification Message: 67 bytes -------------- */

/* ActiveRiskQuantityUpdateNotificationMessage */
typedef struct {
  uint8_t sending_time[8];        /* bytes 0 to 7 */
  uint8_t transact_time[8];       /* bytes 8 to 15 */
  uint8_t order_id[8];            /* bytes 16 to 23 */
  uint8_t trd_match_id[8];        /* bytes 24 to 31 */
  uint8_t efid[4];                /* bytes 32 to 35 */
  uint8_t underlier[6];           /* bytes 36 to 41 */
  uint8_t option_security_id[8];  /* bytes 42 to 49 */
  uint8_t side;                   /* byte 50 */
  uint8_t last_px[8];             /* bytes 51 to 58 */
  uint8_t last_qty[4];            /* bytes 59 to 62 */
  uint8_t unacked_quantity[4];    /* bytes 63 to 66 */
} ActiveRiskQuantityUpdateNotificationMessage;

/* any Active Risk Quantity Update Notification Message at all: every byte one the checker chooses */
static void any_active_risk_quantity_update_notification_message(ActiveRiskQuantityUpdateNotificationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trd_match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->option_security_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->unacked_quantity[i] = arbitrary(); }
}

/* Active Risk Quantity Update Notification Message to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_active_risk_quantity_update_notification_message(const ActiveRiskQuantityUpdateNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_match_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->option_security_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unacked_quantity[i]; }

  return at;
}

/* Active Risk Quantity Update Notification Message off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_active_risk_quantity_update_notification_message(ActiveRiskQuantityUpdateNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trd_match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->option_security_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->unacked_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Active Risk Quantity Update Notification Message is what was written, byte for byte */
static void equal_active_risk_quantity_update_notification_message(const ActiveRiskQuantityUpdateNotificationMessage *read, const ActiveRiskQuantityUpdateNotificationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trd_match_id[i] == written->trd_match_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid[i] == written->efid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier[i] == written->underlier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->option_security_id[i] == written->option_security_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->unacked_quantity[i] == written->unacked_quantity[i]); }
}

/* Active Risk Quantity Update Notification Message: written and read back, then read and written back */
static void check_active_risk_quantity_update_notification_message(void) {
  ActiveRiskQuantityUpdateNotificationMessage sent;
  ActiveRiskQuantityUpdateNotificationMessage got;
  uint8_t wire[67];
  uint8_t again[67];

  any_active_risk_quantity_update_notification_message(&sent);
  assert(encode_active_risk_quantity_update_notification_message(&sent, wire, 0) == 67);
  assert(decode_active_risk_quantity_update_notification_message(&got, wire, 0) == 67);
  equal_active_risk_quantity_update_notification_message(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_active_risk_quantity_update_notification_message(&got, wire, 0) == 67);
  assert(encode_active_risk_quantity_update_notification_message(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Volume Threshold State Message: 44 bytes ----------------------------- */

/* CPVolumeThresholdStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];      /* bytes 0 to 19 */
  uint8_t underlier_optional[6];       /* bytes 20 to 25 */
  uint8_t efid_optional[4];            /* bytes 26 to 29 */
  uint8_t risk_group_id[2];            /* bytes 30 to 31 */
  uint8_t volume[8];                   /* bytes 32 to 39 */
  uint8_t period_in_milli_seconds[4];  /* bytes 40 to 43 */
} CpVolumeThresholdStateMessage;

/* any Cp Volume Threshold State Message at all: every byte one the checker chooses */
static void any_cp_volume_threshold_state_message(CpVolumeThresholdStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = arbitrary(); }
}

/* Cp Volume Threshold State Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_cp_volume_threshold_state_message(const CpVolumeThresholdStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->period_in_milli_seconds[i]; }

  return at;
}

/* Cp Volume Threshold State Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_cp_volume_threshold_state_message(CpVolumeThresholdStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Volume Threshold State Message is what was written, byte for byte */
static void equal_cp_volume_threshold_state_message(const CpVolumeThresholdStateMessage *read, const CpVolumeThresholdStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->period_in_milli_seconds[i] == written->period_in_milli_seconds[i]); }
}

/* Cp Volume Threshold State Message: written and read back, then read and written back */
static void check_cp_volume_threshold_state_message(void) {
  CpVolumeThresholdStateMessage sent;
  CpVolumeThresholdStateMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_cp_volume_threshold_state_message(&sent);
  assert(encode_cp_volume_threshold_state_message(&sent, wire, 0) == 44);
  assert(decode_cp_volume_threshold_state_message(&got, wire, 0) == 44);
  equal_cp_volume_threshold_state_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_volume_threshold_state_message(&got, wire, 0) == 44);
  assert(encode_cp_volume_threshold_state_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Executed Notional Threshold State Message: 44 bytes ------------------ */

/* CPExecutedNotionalThresholdStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];      /* bytes 0 to 19 */
  uint8_t underlier_optional[6];       /* bytes 20 to 25 */
  uint8_t efid_optional[4];            /* bytes 26 to 29 */
  uint8_t risk_group_id[2];            /* bytes 30 to 31 */
  uint8_t price_in_dollars[8];         /* bytes 32 to 39 */
  uint8_t period_in_milli_seconds[4];  /* bytes 40 to 43 */
} CpExecutedNotionalThresholdStateMessage;

/* any Cp Executed Notional Threshold State Message at all: every byte one the checker chooses */
static void any_cp_executed_notional_threshold_state_message(CpExecutedNotionalThresholdStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = arbitrary(); }
}

/* Cp Executed Notional Threshold State Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_cp_executed_notional_threshold_state_message(const CpExecutedNotionalThresholdStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_in_dollars[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->period_in_milli_seconds[i]; }

  return at;
}

/* Cp Executed Notional Threshold State Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_cp_executed_notional_threshold_state_message(CpExecutedNotionalThresholdStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Executed Notional Threshold State Message is what was written, byte for byte */
static void equal_cp_executed_notional_threshold_state_message(const CpExecutedNotionalThresholdStateMessage *read, const CpExecutedNotionalThresholdStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_in_dollars[i] == written->price_in_dollars[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->period_in_milli_seconds[i] == written->period_in_milli_seconds[i]); }
}

/* Cp Executed Notional Threshold State Message: written and read back, then read and written back */
static void check_cp_executed_notional_threshold_state_message(void) {
  CpExecutedNotionalThresholdStateMessage sent;
  CpExecutedNotionalThresholdStateMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_cp_executed_notional_threshold_state_message(&sent);
  assert(encode_cp_executed_notional_threshold_state_message(&sent, wire, 0) == 44);
  assert(decode_cp_executed_notional_threshold_state_message(&got, wire, 0) == 44);
  equal_cp_executed_notional_threshold_state_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_executed_notional_threshold_state_message(&got, wire, 0) == 44);
  assert(encode_cp_executed_notional_threshold_state_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Total Executions Threshold State Message: 40 bytes ------------------- */

/* CPTotalExecutionsThresholdStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];      /* bytes 0 to 19 */
  uint8_t underlier_optional[6];       /* bytes 20 to 25 */
  uint8_t efid_optional[4];            /* bytes 26 to 29 */
  uint8_t risk_group_id[2];            /* bytes 30 to 31 */
  uint8_t total_executions[4];         /* bytes 32 to 35 */
  uint8_t period_in_milli_seconds[4];  /* bytes 36 to 39 */
} CpTotalExecutionsThresholdStateMessage;

/* any Cp Total Executions Threshold State Message at all: every byte one the checker chooses */
static void any_cp_total_executions_threshold_state_message(CpTotalExecutionsThresholdStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_executions[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = arbitrary(); }
}

/* Cp Total Executions Threshold State Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cp_total_executions_threshold_state_message(const CpTotalExecutionsThresholdStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_executions[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->period_in_milli_seconds[i]; }

  return at;
}

/* Cp Total Executions Threshold State Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cp_total_executions_threshold_state_message(CpTotalExecutionsThresholdStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_executions[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Total Executions Threshold State Message is what was written, byte for byte */
static void equal_cp_total_executions_threshold_state_message(const CpTotalExecutionsThresholdStateMessage *read, const CpTotalExecutionsThresholdStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_executions[i] == written->total_executions[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->period_in_milli_seconds[i] == written->period_in_milli_seconds[i]); }
}

/* Cp Total Executions Threshold State Message: written and read back, then read and written back */
static void check_cp_total_executions_threshold_state_message(void) {
  CpTotalExecutionsThresholdStateMessage sent;
  CpTotalExecutionsThresholdStateMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cp_total_executions_threshold_state_message(&sent);
  assert(encode_cp_total_executions_threshold_state_message(&sent, wire, 0) == 40);
  assert(decode_cp_total_executions_threshold_state_message(&got, wire, 0) == 40);
  equal_cp_total_executions_threshold_state_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_total_executions_threshold_state_message(&got, wire, 0) == 40);
  assert(encode_cp_total_executions_threshold_state_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Percent Outstanding Contracts Threshold State Message: 38 bytes ------ */

/* CPPercentOutstandingContractsThresholdStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];      /* bytes 0 to 19 */
  uint8_t underlier_optional[6];       /* bytes 20 to 25 */
  uint8_t efid_optional[4];            /* bytes 26 to 29 */
  uint8_t percent[4];                  /* bytes 30 to 33 */
  uint8_t period_in_milli_seconds[4];  /* bytes 34 to 37 */
} CpPercentOutstandingContractsThresholdStateMessage;

/* any Cp Percent Outstanding Contracts Threshold State Message at all: every byte one the checker chooses */
static void any_cp_percent_outstanding_contracts_threshold_state_message(CpPercentOutstandingContractsThresholdStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->percent[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = arbitrary(); }
}

/* Cp Percent Outstanding Contracts Threshold State Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_cp_percent_outstanding_contracts_threshold_state_message(const CpPercentOutstandingContractsThresholdStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->percent[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->period_in_milli_seconds[i]; }

  return at;
}

/* Cp Percent Outstanding Contracts Threshold State Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_cp_percent_outstanding_contracts_threshold_state_message(CpPercentOutstandingContractsThresholdStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->percent[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Percent Outstanding Contracts Threshold State Message is what was written, byte for byte */
static void equal_cp_percent_outstanding_contracts_threshold_state_message(const CpPercentOutstandingContractsThresholdStateMessage *read, const CpPercentOutstandingContractsThresholdStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->percent[i] == written->percent[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->period_in_milli_seconds[i] == written->period_in_milli_seconds[i]); }
}

/* Cp Percent Outstanding Contracts Threshold State Message: written and read back, then read and written back */
static void check_cp_percent_outstanding_contracts_threshold_state_message(void) {
  CpPercentOutstandingContractsThresholdStateMessage sent;
  CpPercentOutstandingContractsThresholdStateMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_cp_percent_outstanding_contracts_threshold_state_message(&sent);
  assert(encode_cp_percent_outstanding_contracts_threshold_state_message(&sent, wire, 0) == 38);
  assert(decode_cp_percent_outstanding_contracts_threshold_state_message(&got, wire, 0) == 38);
  equal_cp_percent_outstanding_contracts_threshold_state_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_percent_outstanding_contracts_threshold_state_message(&got, wire, 0) == 38);
  assert(encode_cp_percent_outstanding_contracts_threshold_state_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Breach Count Threshold State Message: 40 bytes ----------------------- */

/* CPBreachCountThresholdStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];      /* bytes 0 to 19 */
  uint8_t underlier_optional[6];       /* bytes 20 to 25 */
  uint8_t efid_optional[4];            /* bytes 26 to 29 */
  uint8_t risk_group_id[2];            /* bytes 30 to 31 */
  uint8_t count[4];                    /* bytes 32 to 35 */
  uint8_t period_in_milli_seconds[4];  /* bytes 36 to 39 */
} CpBreachCountThresholdStateMessage;

/* any Cp Breach Count Threshold State Message at all: every byte one the checker chooses */
static void any_cp_breach_count_threshold_state_message(CpBreachCountThresholdStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = arbitrary(); }
}

/* Cp Breach Count Threshold State Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cp_breach_count_threshold_state_message(const CpBreachCountThresholdStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->period_in_milli_seconds[i]; }

  return at;
}

/* Cp Breach Count Threshold State Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cp_breach_count_threshold_state_message(CpBreachCountThresholdStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Breach Count Threshold State Message is what was written, byte for byte */
static void equal_cp_breach_count_threshold_state_message(const CpBreachCountThresholdStateMessage *read, const CpBreachCountThresholdStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count[i] == written->count[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->period_in_milli_seconds[i] == written->period_in_milli_seconds[i]); }
}

/* Cp Breach Count Threshold State Message: written and read back, then read and written back */
static void check_cp_breach_count_threshold_state_message(void) {
  CpBreachCountThresholdStateMessage sent;
  CpBreachCountThresholdStateMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cp_breach_count_threshold_state_message(&sent);
  assert(encode_cp_breach_count_threshold_state_message(&sent, wire, 0) == 40);
  assert(decode_cp_breach_count_threshold_state_message(&got, wire, 0) == 40);
  equal_cp_breach_count_threshold_state_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_breach_count_threshold_state_message(&got, wire, 0) == 40);
  assert(encode_cp_breach_count_threshold_state_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Manual Cp Breach Trigger Pending Message: 32 bytes ---------------------- */

/* ManualCPBreachTriggerPendingMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
  uint8_t risk_group_id[2];       /* bytes 30 to 31 */
} ManualCpBreachTriggerPendingMessage;

/* any Manual Cp Breach Trigger Pending Message at all: every byte one the checker chooses */
static void any_manual_cp_breach_trigger_pending_message(ManualCpBreachTriggerPendingMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
}

/* Manual Cp Breach Trigger Pending Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_manual_cp_breach_trigger_pending_message(const ManualCpBreachTriggerPendingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }

  return at;
}

/* Manual Cp Breach Trigger Pending Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_manual_cp_breach_trigger_pending_message(ManualCpBreachTriggerPendingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }

  return at;
}

/* what was read of Manual Cp Breach Trigger Pending Message is what was written, byte for byte */
static void equal_manual_cp_breach_trigger_pending_message(const ManualCpBreachTriggerPendingMessage *read, const ManualCpBreachTriggerPendingMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
}

/* Manual Cp Breach Trigger Pending Message: written and read back, then read and written back */
static void check_manual_cp_breach_trigger_pending_message(void) {
  ManualCpBreachTriggerPendingMessage sent;
  ManualCpBreachTriggerPendingMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_manual_cp_breach_trigger_pending_message(&sent);
  assert(encode_manual_cp_breach_trigger_pending_message(&sent, wire, 0) == 32);
  assert(decode_manual_cp_breach_trigger_pending_message(&got, wire, 0) == 32);
  equal_manual_cp_breach_trigger_pending_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_manual_cp_breach_trigger_pending_message(&got, wire, 0) == 32);
  assert(encode_manual_cp_breach_trigger_pending_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Manual Cp Breach Trigger Done Message: 44 bytes ------------------------- */

/* ManualCPBreachTriggerDoneMessage */
typedef struct {
  uint8_t cl_ord_id[20];             /* bytes 0 to 19 */
  uint8_t underlier_optional[6];     /* bytes 20 to 25 */
  uint8_t efid_optional[4];          /* bytes 26 to 29 */
  uint8_t risk_group_id[2];          /* bytes 30 to 31 */
  uint8_t breach_id[8];              /* bytes 32 to 39 */
  uint8_t total_affected_orders[4];  /* bytes 40 to 43 */
} ManualCpBreachTriggerDoneMessage;

/* any Manual Cp Breach Trigger Done Message at all: every byte one the checker chooses */
static void any_manual_cp_breach_trigger_done_message(ManualCpBreachTriggerDoneMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->breach_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_affected_orders[i] = arbitrary(); }
}

/* Manual Cp Breach Trigger Done Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_manual_cp_breach_trigger_done_message(const ManualCpBreachTriggerDoneMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->breach_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_affected_orders[i]; }

  return at;
}

/* Manual Cp Breach Trigger Done Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_manual_cp_breach_trigger_done_message(ManualCpBreachTriggerDoneMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->breach_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_affected_orders[i] = wire[at++]; }

  return at;
}

/* what was read of Manual Cp Breach Trigger Done Message is what was written, byte for byte */
static void equal_manual_cp_breach_trigger_done_message(const ManualCpBreachTriggerDoneMessage *read, const ManualCpBreachTriggerDoneMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->breach_id[i] == written->breach_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_affected_orders[i] == written->total_affected_orders[i]); }
}

/* Manual Cp Breach Trigger Done Message: written and read back, then read and written back */
static void check_manual_cp_breach_trigger_done_message(void) {
  ManualCpBreachTriggerDoneMessage sent;
  ManualCpBreachTriggerDoneMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_manual_cp_breach_trigger_done_message(&sent);
  assert(encode_manual_cp_breach_trigger_done_message(&sent, wire, 0) == 44);
  assert(decode_manual_cp_breach_trigger_done_message(&got, wire, 0) == 44);
  equal_manual_cp_breach_trigger_done_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_manual_cp_breach_trigger_done_message(&got, wire, 0) == 44);
  assert(encode_manual_cp_breach_trigger_done_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Risk Threshold Update Rejected Message: 23 bytes ------------------------ */

/* RiskThresholdUpdateRejectedMessage */
typedef struct {
  uint8_t cl_ord_id[20];     /* bytes 0 to 19 */
  uint8_t risk_type;         /* byte 20 */
  uint8_t reject_reason[2];  /* bytes 21 to 22 */
} RiskThresholdUpdateRejectedMessage;

/* any Risk Threshold Update Rejected Message at all: every byte one the checker chooses */
static void any_risk_threshold_update_rejected_message(RiskThresholdUpdateRejectedMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->risk_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = arbitrary(); }
}

/* Risk Threshold Update Rejected Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_risk_threshold_update_rejected_message(const RiskThresholdUpdateRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->risk_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reject_reason[i]; }

  return at;
}

/* Risk Threshold Update Rejected Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_risk_threshold_update_rejected_message(RiskThresholdUpdateRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->risk_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Risk Threshold Update Rejected Message is what was written, byte for byte */
static void equal_risk_threshold_update_rejected_message(const RiskThresholdUpdateRejectedMessage *read, const RiskThresholdUpdateRejectedMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->risk_type == written->risk_type);
  for (size_t i = 0; i < 2; i++) { assert(read->reject_reason[i] == written->reject_reason[i]); }
}

/* Risk Threshold Update Rejected Message: written and read back, then read and written back */
static void check_risk_threshold_update_rejected_message(void) {
  RiskThresholdUpdateRejectedMessage sent;
  RiskThresholdUpdateRejectedMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_risk_threshold_update_rejected_message(&sent);
  assert(encode_risk_threshold_update_rejected_message(&sent, wire, 0) == 23);
  assert(decode_risk_threshold_update_rejected_message(&got, wire, 0) == 23);
  equal_risk_threshold_update_rejected_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_risk_threshold_update_rejected_message(&got, wire, 0) == 23);
  assert(encode_risk_threshold_update_rejected_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Passive Risk Threshold Notification Message: 30 bytes ------------------- */

/* PassiveRiskThresholdNotificationMessage */
typedef struct {
  uint8_t underlier_optional[6];  /* bytes 0 to 5 */
  uint8_t efid_optional[4];       /* bytes 6 to 9 */
  uint8_t risk_group_id[2];       /* bytes 10 to 11 */
  uint8_t rule_type;              /* byte 12 */
  uint8_t latest_percentage;      /* byte 13 */
  uint8_t breach_id_optional[8];  /* bytes 14 to 21 */
  uint8_t transact_time[8];       /* bytes 22 to 29 */
} PassiveRiskThresholdNotificationMessage;

/* any Passive Risk Threshold Notification Message at all: every byte one the checker chooses */
static void any_passive_risk_threshold_notification_message(PassiveRiskThresholdNotificationMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->rule_type = arbitrary();
  record->latest_percentage = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->breach_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Passive Risk Threshold Notification Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_passive_risk_threshold_notification_message(const PassiveRiskThresholdNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->rule_type;
  wire[at++] = record->latest_percentage;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->breach_id_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Passive Risk Threshold Notification Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_passive_risk_threshold_notification_message(PassiveRiskThresholdNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->rule_type = wire[at++];
  record->latest_percentage = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->breach_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Passive Risk Threshold Notification Message is what was written, byte for byte */
static void equal_passive_risk_threshold_notification_message(const PassiveRiskThresholdNotificationMessage *read, const PassiveRiskThresholdNotificationMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->rule_type == written->rule_type);
  assert(read->latest_percentage == written->latest_percentage);
  for (size_t i = 0; i < 8; i++) { assert(read->breach_id_optional[i] == written->breach_id_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Passive Risk Threshold Notification Message: written and read back, then read and written back */
static void check_passive_risk_threshold_notification_message(void) {
  PassiveRiskThresholdNotificationMessage sent;
  PassiveRiskThresholdNotificationMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_passive_risk_threshold_notification_message(&sent);
  assert(encode_passive_risk_threshold_notification_message(&sent, wire, 0) == 30);
  assert(decode_passive_risk_threshold_notification_message(&got, wire, 0) == 30);
  equal_passive_risk_threshold_notification_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_passive_risk_threshold_notification_message(&got, wire, 0) == 30);
  assert(encode_passive_risk_threshold_notification_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Order Allow Iso Orders State Message: 33 bytes ------------------- */

/* SingleOrderAllowISOOrdersStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];  /* bytes 0 to 19 */
  uint8_t underlier_optional[6];   /* bytes 20 to 25 */
  uint8_t efid_optional[4];        /* bytes 26 to 29 */
  uint8_t risk_group_id[2];        /* bytes 30 to 31 */
  uint8_t allow_iso_orders;        /* byte 32 */
} SingleOrderAllowIsoOrdersStateMessage;

/* any Single Order Allow Iso Orders State Message at all: every byte one the checker chooses */
static void any_single_order_allow_iso_orders_state_message(SingleOrderAllowIsoOrdersStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->allow_iso_orders = arbitrary();
}

/* Single Order Allow Iso Orders State Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_single_order_allow_iso_orders_state_message(const SingleOrderAllowIsoOrdersStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->allow_iso_orders;

  return at;
}

/* Single Order Allow Iso Orders State Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_single_order_allow_iso_orders_state_message(SingleOrderAllowIsoOrdersStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->allow_iso_orders = wire[at++];

  return at;
}

/* what was read of Single Order Allow Iso Orders State Message is what was written, byte for byte */
static void equal_single_order_allow_iso_orders_state_message(const SingleOrderAllowIsoOrdersStateMessage *read, const SingleOrderAllowIsoOrdersStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->allow_iso_orders == written->allow_iso_orders);
}

/* Single Order Allow Iso Orders State Message: written and read back, then read and written back */
static void check_single_order_allow_iso_orders_state_message(void) {
  SingleOrderAllowIsoOrdersStateMessage sent;
  SingleOrderAllowIsoOrdersStateMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_single_order_allow_iso_orders_state_message(&sent);
  assert(encode_single_order_allow_iso_orders_state_message(&sent, wire, 0) == 33);
  assert(decode_single_order_allow_iso_orders_state_message(&got, wire, 0) == 33);
  equal_single_order_allow_iso_orders_state_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_single_order_allow_iso_orders_state_message(&got, wire, 0) == 33);
  assert(encode_single_order_allow_iso_orders_state_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Order Allow Orders In Crossed Market State Message: 33 bytes ----- */

/* SingleOrderAllowOrdersInCrossedMarketStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];  /* bytes 0 to 19 */
  uint8_t underlier_optional[6];   /* bytes 20 to 25 */
  uint8_t efid_optional[4];        /* bytes 26 to 29 */
  uint8_t risk_group_id[2];        /* bytes 30 to 31 */
  uint8_t allow_orders;            /* byte 32 */
} SingleOrderAllowOrdersInCrossedMarketStateMessage;

/* any Single Order Allow Orders In Crossed Market State Message at all: every byte one the checker chooses */
static void any_single_order_allow_orders_in_crossed_market_state_message(SingleOrderAllowOrdersInCrossedMarketStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->allow_orders = arbitrary();
}

/* Single Order Allow Orders In Crossed Market State Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_single_order_allow_orders_in_crossed_market_state_message(const SingleOrderAllowOrdersInCrossedMarketStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->allow_orders;

  return at;
}

/* Single Order Allow Orders In Crossed Market State Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_single_order_allow_orders_in_crossed_market_state_message(SingleOrderAllowOrdersInCrossedMarketStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->allow_orders = wire[at++];

  return at;
}

/* what was read of Single Order Allow Orders In Crossed Market State Message is what was written, byte for byte */
static void equal_single_order_allow_orders_in_crossed_market_state_message(const SingleOrderAllowOrdersInCrossedMarketStateMessage *read, const SingleOrderAllowOrdersInCrossedMarketStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->allow_orders == written->allow_orders);
}

/* Single Order Allow Orders In Crossed Market State Message: written and read back, then read and written back */
static void check_single_order_allow_orders_in_crossed_market_state_message(void) {
  SingleOrderAllowOrdersInCrossedMarketStateMessage sent;
  SingleOrderAllowOrdersInCrossedMarketStateMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_single_order_allow_orders_in_crossed_market_state_message(&sent);
  assert(encode_single_order_allow_orders_in_crossed_market_state_message(&sent, wire, 0) == 33);
  assert(decode_single_order_allow_orders_in_crossed_market_state_message(&got, wire, 0) == 33);
  equal_single_order_allow_orders_in_crossed_market_state_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_single_order_allow_orders_in_crossed_market_state_message(&got, wire, 0) == 33);
  assert(encode_single_order_allow_orders_in_crossed_market_state_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Order Max Notional Threshold State Message: 40 bytes ------------- */

/* SingleOrderMaxNotionalThresholdStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];      /* bytes 0 to 19 */
  uint8_t underlier_optional[6];       /* bytes 20 to 25 */
  uint8_t efid_optional[4];            /* bytes 26 to 29 */
  uint8_t risk_group_id[2];            /* bytes 30 to 31 */
  uint8_t max_notional_in_dollars[8];  /* bytes 32 to 39 */
} SingleOrderMaxNotionalThresholdStateMessage;

/* any Single Order Max Notional Threshold State Message at all: every byte one the checker chooses */
static void any_single_order_max_notional_threshold_state_message(SingleOrderMaxNotionalThresholdStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_notional_in_dollars[i] = arbitrary(); }
}

/* Single Order Max Notional Threshold State Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_single_order_max_notional_threshold_state_message(const SingleOrderMaxNotionalThresholdStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_notional_in_dollars[i]; }

  return at;
}

/* Single Order Max Notional Threshold State Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_single_order_max_notional_threshold_state_message(SingleOrderMaxNotionalThresholdStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_notional_in_dollars[i] = wire[at++]; }

  return at;
}

/* what was read of Single Order Max Notional Threshold State Message is what was written, byte for byte */
static void equal_single_order_max_notional_threshold_state_message(const SingleOrderMaxNotionalThresholdStateMessage *read, const SingleOrderMaxNotionalThresholdStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_notional_in_dollars[i] == written->max_notional_in_dollars[i]); }
}

/* Single Order Max Notional Threshold State Message: written and read back, then read and written back */
static void check_single_order_max_notional_threshold_state_message(void) {
  SingleOrderMaxNotionalThresholdStateMessage sent;
  SingleOrderMaxNotionalThresholdStateMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_single_order_max_notional_threshold_state_message(&sent);
  assert(encode_single_order_max_notional_threshold_state_message(&sent, wire, 0) == 40);
  assert(decode_single_order_max_notional_threshold_state_message(&got, wire, 0) == 40);
  equal_single_order_max_notional_threshold_state_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_single_order_max_notional_threshold_state_message(&got, wire, 0) == 40);
  assert(encode_single_order_max_notional_threshold_state_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Order Max Contracts Threshold State Message: 36 bytes ------------ */

/* SingleOrderMaxContractsThresholdStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];  /* bytes 0 to 19 */
  uint8_t underlier_optional[6];   /* bytes 20 to 25 */
  uint8_t efid_optional[4];        /* bytes 26 to 29 */
  uint8_t risk_group_id[2];        /* bytes 30 to 31 */
  uint8_t max_contracts[4];        /* bytes 32 to 35 */
} SingleOrderMaxContractsThresholdStateMessage;

/* any Single Order Max Contracts Threshold State Message at all: every byte one the checker chooses */
static void any_single_order_max_contracts_threshold_state_message(SingleOrderMaxContractsThresholdStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_contracts[i] = arbitrary(); }
}

/* Single Order Max Contracts Threshold State Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_single_order_max_contracts_threshold_state_message(const SingleOrderMaxContractsThresholdStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_contracts[i]; }

  return at;
}

/* Single Order Max Contracts Threshold State Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_single_order_max_contracts_threshold_state_message(SingleOrderMaxContractsThresholdStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_contracts[i] = wire[at++]; }

  return at;
}

/* what was read of Single Order Max Contracts Threshold State Message is what was written, byte for byte */
static void equal_single_order_max_contracts_threshold_state_message(const SingleOrderMaxContractsThresholdStateMessage *read, const SingleOrderMaxContractsThresholdStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_contracts[i] == written->max_contracts[i]); }
}

/* Single Order Max Contracts Threshold State Message: written and read back, then read and written back */
static void check_single_order_max_contracts_threshold_state_message(void) {
  SingleOrderMaxContractsThresholdStateMessage sent;
  SingleOrderMaxContractsThresholdStateMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_single_order_max_contracts_threshold_state_message(&sent);
  assert(encode_single_order_max_contracts_threshold_state_message(&sent, wire, 0) == 36);
  assert(decode_single_order_max_contracts_threshold_state_message(&got, wire, 0) == 36);
  equal_single_order_max_contracts_threshold_state_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_single_order_max_contracts_threshold_state_message(&got, wire, 0) == 36);
  assert(encode_single_order_max_contracts_threshold_state_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Order Allow Market Orders State Message: 33 bytes ---------------- */

/* SingleOrderAllowMarketOrdersStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];  /* bytes 0 to 19 */
  uint8_t underlier_optional[6];   /* bytes 20 to 25 */
  uint8_t efid_optional[4];        /* bytes 26 to 29 */
  uint8_t risk_group_id[2];        /* bytes 30 to 31 */
  uint8_t market_orders;           /* byte 32 */
} SingleOrderAllowMarketOrdersStateMessage;

/* any Single Order Allow Market Orders State Message at all: every byte one the checker chooses */
static void any_single_order_allow_market_orders_state_message(SingleOrderAllowMarketOrdersStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->market_orders = arbitrary();
}

/* Single Order Allow Market Orders State Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_single_order_allow_market_orders_state_message(const SingleOrderAllowMarketOrdersStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->market_orders;

  return at;
}

/* Single Order Allow Market Orders State Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_single_order_allow_market_orders_state_message(SingleOrderAllowMarketOrdersStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->market_orders = wire[at++];

  return at;
}

/* what was read of Single Order Allow Market Orders State Message is what was written, byte for byte */
static void equal_single_order_allow_market_orders_state_message(const SingleOrderAllowMarketOrdersStateMessage *read, const SingleOrderAllowMarketOrdersStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->market_orders == written->market_orders);
}

/* Single Order Allow Market Orders State Message: written and read back, then read and written back */
static void check_single_order_allow_market_orders_state_message(void) {
  SingleOrderAllowMarketOrdersStateMessage sent;
  SingleOrderAllowMarketOrdersStateMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_single_order_allow_market_orders_state_message(&sent);
  assert(encode_single_order_allow_market_orders_state_message(&sent, wire, 0) == 33);
  assert(decode_single_order_allow_market_orders_state_message(&got, wire, 0) == 33);
  equal_single_order_allow_market_orders_state_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_single_order_allow_market_orders_state_message(&got, wire, 0) == 33);
  assert(encode_single_order_allow_market_orders_state_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Order Restricted Underlier State Message: 33 bytes --------------- */

/* SingleOrderRestrictedUnderlierStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];  /* bytes 0 to 19 */
  uint8_t underlier[6];            /* bytes 20 to 25 */
  uint8_t efid_optional[4];        /* bytes 26 to 29 */
  uint8_t risk_group_id[2];        /* bytes 30 to 31 */
  uint8_t restricted;              /* byte 32 */
} SingleOrderRestrictedUnderlierStateMessage;

/* any Single Order Restricted Underlier State Message at all: every byte one the checker chooses */
static void any_single_order_restricted_underlier_state_message(SingleOrderRestrictedUnderlierStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->restricted = arbitrary();
}

/* Single Order Restricted Underlier State Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_single_order_restricted_underlier_state_message(const SingleOrderRestrictedUnderlierStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->restricted;

  return at;
}

/* Single Order Restricted Underlier State Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_single_order_restricted_underlier_state_message(SingleOrderRestrictedUnderlierStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->restricted = wire[at++];

  return at;
}

/* what was read of Single Order Restricted Underlier State Message is what was written, byte for byte */
static void equal_single_order_restricted_underlier_state_message(const SingleOrderRestrictedUnderlierStateMessage *read, const SingleOrderRestrictedUnderlierStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier[i] == written->underlier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->restricted == written->restricted);
}

/* Single Order Restricted Underlier State Message: written and read back, then read and written back */
static void check_single_order_restricted_underlier_state_message(void) {
  SingleOrderRestrictedUnderlierStateMessage sent;
  SingleOrderRestrictedUnderlierStateMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_single_order_restricted_underlier_state_message(&sent);
  assert(encode_single_order_restricted_underlier_state_message(&sent, wire, 0) == 33);
  assert(decode_single_order_restricted_underlier_state_message(&got, wire, 0) == 33);
  equal_single_order_restricted_underlier_state_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_single_order_restricted_underlier_state_message(&got, wire, 0) == 33);
  assert(encode_single_order_restricted_underlier_state_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Risk Settings Query Done Message: 24 bytes ------------------------------ */

/* RiskSettingsQueryDoneMessage */
typedef struct {
  uint8_t cl_ord_id[20];        /* bytes 0 to 19 */
  uint8_t number_msgs_sent[4];  /* bytes 20 to 23 */
} RiskSettingsQueryDoneMessage;

/* any Risk Settings Query Done Message at all: every byte one the checker chooses */
static void any_risk_settings_query_done_message(RiskSettingsQueryDoneMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_msgs_sent[i] = arbitrary(); }
}

/* Risk Settings Query Done Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_risk_settings_query_done_message(const RiskSettingsQueryDoneMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_msgs_sent[i]; }

  return at;
}

/* Risk Settings Query Done Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_risk_settings_query_done_message(RiskSettingsQueryDoneMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_msgs_sent[i] = wire[at++]; }

  return at;
}

/* what was read of Risk Settings Query Done Message is what was written, byte for byte */
static void equal_risk_settings_query_done_message(const RiskSettingsQueryDoneMessage *read, const RiskSettingsQueryDoneMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_msgs_sent[i] == written->number_msgs_sent[i]); }
}

/* Risk Settings Query Done Message: written and read back, then read and written back */
static void check_risk_settings_query_done_message(void) {
  RiskSettingsQueryDoneMessage sent;
  RiskSettingsQueryDoneMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_risk_settings_query_done_message(&sent);
  assert(encode_risk_settings_query_done_message(&sent, wire, 0) == 24);
  assert(decode_risk_settings_query_done_message(&got, wire, 0) == 24);
  equal_risk_settings_query_done_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_risk_settings_query_done_message(&got, wire, 0) == 24);
  assert(encode_risk_settings_query_done_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Risk Settings Query Rejected Message: 22 bytes -------------------------- */

/* RiskSettingsQueryRejectedMessage */
typedef struct {
  uint8_t cl_ord_id[20];     /* bytes 0 to 19 */
  uint8_t reject_reason[2];  /* bytes 20 to 21 */
} RiskSettingsQueryRejectedMessage;

/* any Risk Settings Query Rejected Message at all: every byte one the checker chooses */
static void any_risk_settings_query_rejected_message(RiskSettingsQueryRejectedMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = arbitrary(); }
}

/* Risk Settings Query Rejected Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_risk_settings_query_rejected_message(const RiskSettingsQueryRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reject_reason[i]; }

  return at;
}

/* Risk Settings Query Rejected Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_risk_settings_query_rejected_message(RiskSettingsQueryRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Risk Settings Query Rejected Message is what was written, byte for byte */
static void equal_risk_settings_query_rejected_message(const RiskSettingsQueryRejectedMessage *read, const RiskSettingsQueryRejectedMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reject_reason[i] == written->reject_reason[i]); }
}

/* Risk Settings Query Rejected Message: written and read back, then read and written back */
static void check_risk_settings_query_rejected_message(void) {
  RiskSettingsQueryRejectedMessage sent;
  RiskSettingsQueryRejectedMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_risk_settings_query_rejected_message(&sent);
  assert(encode_risk_settings_query_rejected_message(&sent, wire, 0) == 22);
  assert(decode_risk_settings_query_rejected_message(&got, wire, 0) == 22);
  equal_risk_settings_query_rejected_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_risk_settings_query_rejected_message(&got, wire, 0) == 22);
  assert(encode_risk_settings_query_rejected_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Manual Cp Breach Trigger Rejected Message: 34 bytes --------------------- */

/* ManualCPBreachTriggerRejectedMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
  uint8_t risk_group_id[2];       /* bytes 30 to 31 */
  uint8_t reject_reason[2];       /* bytes 32 to 33 */
} ManualCpBreachTriggerRejectedMessage;

/* any Manual Cp Breach Trigger Rejected Message at all: every byte one the checker chooses */
static void any_manual_cp_breach_trigger_rejected_message(ManualCpBreachTriggerRejectedMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = arbitrary(); }
}

/* Manual Cp Breach Trigger Rejected Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_manual_cp_breach_trigger_rejected_message(const ManualCpBreachTriggerRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reject_reason[i]; }

  return at;
}

/* Manual Cp Breach Trigger Rejected Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_manual_cp_breach_trigger_rejected_message(ManualCpBreachTriggerRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Manual Cp Breach Trigger Rejected Message is what was written, byte for byte */
static void equal_manual_cp_breach_trigger_rejected_message(const ManualCpBreachTriggerRejectedMessage *read, const ManualCpBreachTriggerRejectedMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reject_reason[i] == written->reject_reason[i]); }
}

/* Manual Cp Breach Trigger Rejected Message: written and read back, then read and written back */
static void check_manual_cp_breach_trigger_rejected_message(void) {
  ManualCpBreachTriggerRejectedMessage sent;
  ManualCpBreachTriggerRejectedMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_manual_cp_breach_trigger_rejected_message(&sent);
  assert(encode_manual_cp_breach_trigger_rejected_message(&sent, wire, 0) == 34);
  assert(decode_manual_cp_breach_trigger_rejected_message(&got, wire, 0) == 34);
  equal_manual_cp_breach_trigger_rejected_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_manual_cp_breach_trigger_rejected_message(&got, wire, 0) == 34);
  assert(encode_manual_cp_breach_trigger_rejected_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Breach Clear Rejected Message: 30 bytes --------------------------------- */

/* BreachClearRejectedMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t breach_id_optional[8];  /* bytes 20 to 27 */
  uint8_t reject_reason[2];       /* bytes 28 to 29 */
} BreachClearRejectedMessage;

/* any Breach Clear Rejected Message at all: every byte one the checker chooses */
static void any_breach_clear_rejected_message(BreachClearRejectedMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->breach_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = arbitrary(); }
}

/* Breach Clear Rejected Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_breach_clear_rejected_message(const BreachClearRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->breach_id_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reject_reason[i]; }

  return at;
}

/* Breach Clear Rejected Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_breach_clear_rejected_message(BreachClearRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->breach_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Breach Clear Rejected Message is what was written, byte for byte */
static void equal_breach_clear_rejected_message(const BreachClearRejectedMessage *read, const BreachClearRejectedMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->breach_id_optional[i] == written->breach_id_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reject_reason[i] == written->reject_reason[i]); }
}

/* Breach Clear Rejected Message: written and read back, then read and written back */
static void check_breach_clear_rejected_message(void) {
  BreachClearRejectedMessage sent;
  BreachClearRejectedMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_breach_clear_rejected_message(&sent);
  assert(encode_breach_clear_rejected_message(&sent, wire, 0) == 30);
  assert(decode_breach_clear_rejected_message(&got, wire, 0) == 30);
  equal_breach_clear_rejected_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_breach_clear_rejected_message(&got, wire, 0) == 30);
  assert(encode_breach_clear_rejected_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Breach Cleared Message: 28 bytes ---------------------------------------- */

/* BreachClearedMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];  /* bytes 0 to 19 */
  uint8_t breach_id_optional[8];   /* bytes 20 to 27 */
} BreachClearedMessage;

/* any Breach Cleared Message at all: every byte one the checker chooses */
static void any_breach_cleared_message(BreachClearedMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->breach_id_optional[i] = arbitrary(); }
}

/* Breach Cleared Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_breach_cleared_message(const BreachClearedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->breach_id_optional[i]; }

  return at;
}

/* Breach Cleared Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_breach_cleared_message(BreachClearedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->breach_id_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Breach Cleared Message is what was written, byte for byte */
static void equal_breach_cleared_message(const BreachClearedMessage *read, const BreachClearedMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->breach_id_optional[i] == written->breach_id_optional[i]); }
}

/* Breach Cleared Message: written and read back, then read and written back */
static void check_breach_cleared_message(void) {
  BreachClearedMessage sent;
  BreachClearedMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_breach_cleared_message(&sent);
  assert(encode_breach_cleared_message(&sent, wire, 0) == 28);
  assert(decode_breach_cleared_message(&got, wire, 0) == 28);
  equal_breach_cleared_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_breach_cleared_message(&got, wire, 0) == 28);
  assert(encode_breach_cleared_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Breach Clear All Accepted Message: 20 bytes ----------------------------- */

/* BreachClearAllAcceptedMessage */
typedef struct {
  uint8_t cl_ord_id[20];  /* bytes 0 to 19 */
} BreachClearAllAcceptedMessage;

/* any Breach Clear All Accepted Message at all: every byte one the checker chooses */
static void any_breach_clear_all_accepted_message(BreachClearAllAcceptedMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
}

/* Breach Clear All Accepted Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_breach_clear_all_accepted_message(const BreachClearAllAcceptedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }

  return at;
}

/* Breach Clear All Accepted Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_breach_clear_all_accepted_message(BreachClearAllAcceptedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }

  return at;
}

/* what was read of Breach Clear All Accepted Message is what was written, byte for byte */
static void equal_breach_clear_all_accepted_message(const BreachClearAllAcceptedMessage *read, const BreachClearAllAcceptedMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
}

/* Breach Clear All Accepted Message: written and read back, then read and written back */
static void check_breach_clear_all_accepted_message(void) {
  BreachClearAllAcceptedMessage sent;
  BreachClearAllAcceptedMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_breach_clear_all_accepted_message(&sent);
  assert(encode_breach_clear_all_accepted_message(&sent, wire, 0) == 20);
  assert(decode_breach_clear_all_accepted_message(&got, wire, 0) == 20);
  equal_breach_clear_all_accepted_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_breach_clear_all_accepted_message(&got, wire, 0) == 20);
  assert(encode_breach_clear_all_accepted_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Breach Clear All Rejected Message: 22 bytes ----------------------------- */

/* BreachClearAllRejectedMessage */
typedef struct {
  uint8_t cl_ord_id[20];     /* bytes 0 to 19 */
  uint8_t reject_reason[2];  /* bytes 20 to 21 */
} BreachClearAllRejectedMessage;

/* any Breach Clear All Rejected Message at all: every byte one the checker chooses */
static void any_breach_clear_all_rejected_message(BreachClearAllRejectedMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = arbitrary(); }
}

/* Breach Clear All Rejected Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_breach_clear_all_rejected_message(const BreachClearAllRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reject_reason[i]; }

  return at;
}

/* Breach Clear All Rejected Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_breach_clear_all_rejected_message(BreachClearAllRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Breach Clear All Rejected Message is what was written, byte for byte */
static void equal_breach_clear_all_rejected_message(const BreachClearAllRejectedMessage *read, const BreachClearAllRejectedMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reject_reason[i] == written->reject_reason[i]); }
}

/* Breach Clear All Rejected Message: written and read back, then read and written back */
static void check_breach_clear_all_rejected_message(void) {
  BreachClearAllRejectedMessage sent;
  BreachClearAllRejectedMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_breach_clear_all_rejected_message(&sent);
  assert(encode_breach_clear_all_rejected_message(&sent, wire, 0) == 22);
  assert(decode_breach_clear_all_rejected_message(&got, wire, 0) == 22);
  equal_breach_clear_all_rejected_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_breach_clear_all_rejected_message(&got, wire, 0) == 22);
  assert(encode_breach_clear_all_rejected_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Breach Clear All By Efid Or Underlier Accepted Message: 30 bytes -------- */

/* BreachClearAllByEFIDOrUnderlierAcceptedMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
} BreachClearAllByEfidOrUnderlierAcceptedMessage;

/* any Breach Clear All By Efid Or Underlier Accepted Message at all: every byte one the checker chooses */
static void any_breach_clear_all_by_efid_or_underlier_accepted_message(BreachClearAllByEfidOrUnderlierAcceptedMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
}

/* Breach Clear All By Efid Or Underlier Accepted Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_breach_clear_all_by_efid_or_underlier_accepted_message(const BreachClearAllByEfidOrUnderlierAcceptedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }

  return at;
}

/* Breach Clear All By Efid Or Underlier Accepted Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_breach_clear_all_by_efid_or_underlier_accepted_message(BreachClearAllByEfidOrUnderlierAcceptedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Breach Clear All By Efid Or Underlier Accepted Message is what was written, byte for byte */
static void equal_breach_clear_all_by_efid_or_underlier_accepted_message(const BreachClearAllByEfidOrUnderlierAcceptedMessage *read, const BreachClearAllByEfidOrUnderlierAcceptedMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
}

/* Breach Clear All By Efid Or Underlier Accepted Message: written and read back, then read and written back */
static void check_breach_clear_all_by_efid_or_underlier_accepted_message(void) {
  BreachClearAllByEfidOrUnderlierAcceptedMessage sent;
  BreachClearAllByEfidOrUnderlierAcceptedMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_breach_clear_all_by_efid_or_underlier_accepted_message(&sent);
  assert(encode_breach_clear_all_by_efid_or_underlier_accepted_message(&sent, wire, 0) == 30);
  assert(decode_breach_clear_all_by_efid_or_underlier_accepted_message(&got, wire, 0) == 30);
  equal_breach_clear_all_by_efid_or_underlier_accepted_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_breach_clear_all_by_efid_or_underlier_accepted_message(&got, wire, 0) == 30);
  assert(encode_breach_clear_all_by_efid_or_underlier_accepted_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Breach Clear All By Efid Or Underlier Rejected Message: 32 bytes -------- */

/* BreachClearAllByEFIDOrUnderlierRejectedMessage */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t underlier_optional[6];  /* bytes 20 to 25 */
  uint8_t efid_optional[4];       /* bytes 26 to 29 */
  uint8_t reject_reason[2];       /* bytes 30 to 31 */
} BreachClearAllByEfidOrUnderlierRejectedMessage;

/* any Breach Clear All By Efid Or Underlier Rejected Message at all: every byte one the checker chooses */
static void any_breach_clear_all_by_efid_or_underlier_rejected_message(BreachClearAllByEfidOrUnderlierRejectedMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = arbitrary(); }
}

/* Breach Clear All By Efid Or Underlier Rejected Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_breach_clear_all_by_efid_or_underlier_rejected_message(const BreachClearAllByEfidOrUnderlierRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reject_reason[i]; }

  return at;
}

/* Breach Clear All By Efid Or Underlier Rejected Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_breach_clear_all_by_efid_or_underlier_rejected_message(BreachClearAllByEfidOrUnderlierRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reject_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Breach Clear All By Efid Or Underlier Rejected Message is what was written, byte for byte */
static void equal_breach_clear_all_by_efid_or_underlier_rejected_message(const BreachClearAllByEfidOrUnderlierRejectedMessage *read, const BreachClearAllByEfidOrUnderlierRejectedMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reject_reason[i] == written->reject_reason[i]); }
}

/* Breach Clear All By Efid Or Underlier Rejected Message: written and read back, then read and written back */
static void check_breach_clear_all_by_efid_or_underlier_rejected_message(void) {
  BreachClearAllByEfidOrUnderlierRejectedMessage sent;
  BreachClearAllByEfidOrUnderlierRejectedMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_breach_clear_all_by_efid_or_underlier_rejected_message(&sent);
  assert(encode_breach_clear_all_by_efid_or_underlier_rejected_message(&sent, wire, 0) == 32);
  assert(decode_breach_clear_all_by_efid_or_underlier_rejected_message(&got, wire, 0) == 32);
  equal_breach_clear_all_by_efid_or_underlier_rejected_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_breach_clear_all_by_efid_or_underlier_rejected_message(&got, wire, 0) == 32);
  assert(encode_breach_clear_all_by_efid_or_underlier_rejected_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Gross Notional Threshold State Message: 40 bytes --------------------- */

/* CPGrossNotionalThresholdStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];  /* bytes 0 to 19 */
  uint8_t underlier_optional[6];   /* bytes 20 to 25 */
  uint8_t efid_optional[4];        /* bytes 26 to 29 */
  uint8_t risk_group_id[2];        /* bytes 30 to 31 */
  uint8_t price_in_dollars[8];     /* bytes 32 to 39 */
} CpGrossNotionalThresholdStateMessage;

/* any Cp Gross Notional Threshold State Message at all: every byte one the checker chooses */
static void any_cp_gross_notional_threshold_state_message(CpGrossNotionalThresholdStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = arbitrary(); }
}

/* Cp Gross Notional Threshold State Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cp_gross_notional_threshold_state_message(const CpGrossNotionalThresholdStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_in_dollars[i]; }

  return at;
}

/* Cp Gross Notional Threshold State Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cp_gross_notional_threshold_state_message(CpGrossNotionalThresholdStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Gross Notional Threshold State Message is what was written, byte for byte */
static void equal_cp_gross_notional_threshold_state_message(const CpGrossNotionalThresholdStateMessage *read, const CpGrossNotionalThresholdStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_in_dollars[i] == written->price_in_dollars[i]); }
}

/* Cp Gross Notional Threshold State Message: written and read back, then read and written back */
static void check_cp_gross_notional_threshold_state_message(void) {
  CpGrossNotionalThresholdStateMessage sent;
  CpGrossNotionalThresholdStateMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cp_gross_notional_threshold_state_message(&sent);
  assert(encode_cp_gross_notional_threshold_state_message(&sent, wire, 0) == 40);
  assert(decode_cp_gross_notional_threshold_state_message(&got, wire, 0) == 40);
  equal_cp_gross_notional_threshold_state_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_gross_notional_threshold_state_message(&got, wire, 0) == 40);
  assert(encode_cp_gross_notional_threshold_state_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Market Order Gross Notional Threshold State Message: 40 bytes -------- */

/* CPMarketOrderGrossNotionalThresholdStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];  /* bytes 0 to 19 */
  uint8_t underlier_optional[6];   /* bytes 20 to 25 */
  uint8_t efid_optional[4];        /* bytes 26 to 29 */
  uint8_t risk_group_id[2];        /* bytes 30 to 31 */
  uint8_t price_in_dollars[8];     /* bytes 32 to 39 */
} CpMarketOrderGrossNotionalThresholdStateMessage;

/* any Cp Market Order Gross Notional Threshold State Message at all: every byte one the checker chooses */
static void any_cp_market_order_gross_notional_threshold_state_message(CpMarketOrderGrossNotionalThresholdStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = arbitrary(); }
}

/* Cp Market Order Gross Notional Threshold State Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cp_market_order_gross_notional_threshold_state_message(const CpMarketOrderGrossNotionalThresholdStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_in_dollars[i]; }

  return at;
}

/* Cp Market Order Gross Notional Threshold State Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cp_market_order_gross_notional_threshold_state_message(CpMarketOrderGrossNotionalThresholdStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Market Order Gross Notional Threshold State Message is what was written, byte for byte */
static void equal_cp_market_order_gross_notional_threshold_state_message(const CpMarketOrderGrossNotionalThresholdStateMessage *read, const CpMarketOrderGrossNotionalThresholdStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_in_dollars[i] == written->price_in_dollars[i]); }
}

/* Cp Market Order Gross Notional Threshold State Message: written and read back, then read and written back */
static void check_cp_market_order_gross_notional_threshold_state_message(void) {
  CpMarketOrderGrossNotionalThresholdStateMessage sent;
  CpMarketOrderGrossNotionalThresholdStateMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cp_market_order_gross_notional_threshold_state_message(&sent);
  assert(encode_cp_market_order_gross_notional_threshold_state_message(&sent, wire, 0) == 40);
  assert(decode_cp_market_order_gross_notional_threshold_state_message(&got, wire, 0) == 40);
  equal_cp_market_order_gross_notional_threshold_state_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_market_order_gross_notional_threshold_state_message(&got, wire, 0) == 40);
  assert(encode_cp_market_order_gross_notional_threshold_state_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Net Notional Threshold State Message: 40 bytes ----------------------- */

/* CPNetNotionalThresholdStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];  /* bytes 0 to 19 */
  uint8_t underlier_optional[6];   /* bytes 20 to 25 */
  uint8_t efid_optional[4];        /* bytes 26 to 29 */
  uint8_t risk_group_id[2];        /* bytes 30 to 31 */
  uint8_t price_in_dollars[8];     /* bytes 32 to 39 */
} CpNetNotionalThresholdStateMessage;

/* any Cp Net Notional Threshold State Message at all: every byte one the checker chooses */
static void any_cp_net_notional_threshold_state_message(CpNetNotionalThresholdStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = arbitrary(); }
}

/* Cp Net Notional Threshold State Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cp_net_notional_threshold_state_message(const CpNetNotionalThresholdStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_in_dollars[i]; }

  return at;
}

/* Cp Net Notional Threshold State Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cp_net_notional_threshold_state_message(CpNetNotionalThresholdStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Net Notional Threshold State Message is what was written, byte for byte */
static void equal_cp_net_notional_threshold_state_message(const CpNetNotionalThresholdStateMessage *read, const CpNetNotionalThresholdStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_in_dollars[i] == written->price_in_dollars[i]); }
}

/* Cp Net Notional Threshold State Message: written and read back, then read and written back */
static void check_cp_net_notional_threshold_state_message(void) {
  CpNetNotionalThresholdStateMessage sent;
  CpNetNotionalThresholdStateMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cp_net_notional_threshold_state_message(&sent);
  assert(encode_cp_net_notional_threshold_state_message(&sent, wire, 0) == 40);
  assert(decode_cp_net_notional_threshold_state_message(&got, wire, 0) == 40);
  equal_cp_net_notional_threshold_state_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_net_notional_threshold_state_message(&got, wire, 0) == 40);
  assert(encode_cp_net_notional_threshold_state_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Market Order Net Notional Threshold State Message: 40 bytes ---------- */

/* CPMarketOrderNetNotionalThresholdStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];  /* bytes 0 to 19 */
  uint8_t underlier_optional[6];   /* bytes 20 to 25 */
  uint8_t efid_optional[4];        /* bytes 26 to 29 */
  uint8_t risk_group_id[2];        /* bytes 30 to 31 */
  uint8_t price_in_dollars[8];     /* bytes 32 to 39 */
} CpMarketOrderNetNotionalThresholdStateMessage;

/* any Cp Market Order Net Notional Threshold State Message at all: every byte one the checker chooses */
static void any_cp_market_order_net_notional_threshold_state_message(CpMarketOrderNetNotionalThresholdStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = arbitrary(); }
}

/* Cp Market Order Net Notional Threshold State Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cp_market_order_net_notional_threshold_state_message(const CpMarketOrderNetNotionalThresholdStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_in_dollars[i]; }

  return at;
}

/* Cp Market Order Net Notional Threshold State Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cp_market_order_net_notional_threshold_state_message(CpMarketOrderNetNotionalThresholdStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_in_dollars[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Market Order Net Notional Threshold State Message is what was written, byte for byte */
static void equal_cp_market_order_net_notional_threshold_state_message(const CpMarketOrderNetNotionalThresholdStateMessage *read, const CpMarketOrderNetNotionalThresholdStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_in_dollars[i] == written->price_in_dollars[i]); }
}

/* Cp Market Order Net Notional Threshold State Message: written and read back, then read and written back */
static void check_cp_market_order_net_notional_threshold_state_message(void) {
  CpMarketOrderNetNotionalThresholdStateMessage sent;
  CpMarketOrderNetNotionalThresholdStateMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cp_market_order_net_notional_threshold_state_message(&sent);
  assert(encode_cp_market_order_net_notional_threshold_state_message(&sent, wire, 0) == 40);
  assert(decode_cp_market_order_net_notional_threshold_state_message(&got, wire, 0) == 40);
  equal_cp_market_order_net_notional_threshold_state_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_market_order_net_notional_threshold_state_message(&got, wire, 0) == 40);
  assert(encode_cp_market_order_net_notional_threshold_state_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Duplicate Order Threshold State Message: 41 bytes -------------------- */

/* CPDuplicateOrderThresholdStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];        /* bytes 0 to 19 */
  uint8_t underlier_optional[6];         /* bytes 20 to 25 */
  uint8_t efid_optional[4];              /* bytes 26 to 29 */
  uint8_t risk_group_id[2];              /* bytes 30 to 31 */
  uint8_t max_dup_orders[4];             /* bytes 32 to 35 */
  uint8_t use_order_price_in_dup_check;  /* byte 36 */
  uint8_t period_in_milli_seconds[4];    /* bytes 37 to 40 */
} CpDuplicateOrderThresholdStateMessage;

/* any Cp Duplicate Order Threshold State Message at all: every byte one the checker chooses */
static void any_cp_duplicate_order_threshold_state_message(CpDuplicateOrderThresholdStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_dup_orders[i] = arbitrary(); }
  record->use_order_price_in_dup_check = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = arbitrary(); }
}

/* Cp Duplicate Order Threshold State Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_cp_duplicate_order_threshold_state_message(const CpDuplicateOrderThresholdStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_dup_orders[i]; }
  wire[at++] = record->use_order_price_in_dup_check;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->period_in_milli_seconds[i]; }

  return at;
}

/* Cp Duplicate Order Threshold State Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_cp_duplicate_order_threshold_state_message(CpDuplicateOrderThresholdStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_dup_orders[i] = wire[at++]; }
  record->use_order_price_in_dup_check = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Duplicate Order Threshold State Message is what was written, byte for byte */
static void equal_cp_duplicate_order_threshold_state_message(const CpDuplicateOrderThresholdStateMessage *read, const CpDuplicateOrderThresholdStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_dup_orders[i] == written->max_dup_orders[i]); }
  assert(read->use_order_price_in_dup_check == written->use_order_price_in_dup_check);
  for (size_t i = 0; i < 4; i++) { assert(read->period_in_milli_seconds[i] == written->period_in_milli_seconds[i]); }
}

/* Cp Duplicate Order Threshold State Message: written and read back, then read and written back */
static void check_cp_duplicate_order_threshold_state_message(void) {
  CpDuplicateOrderThresholdStateMessage sent;
  CpDuplicateOrderThresholdStateMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_cp_duplicate_order_threshold_state_message(&sent);
  assert(encode_cp_duplicate_order_threshold_state_message(&sent, wire, 0) == 41);
  assert(decode_cp_duplicate_order_threshold_state_message(&got, wire, 0) == 41);
  equal_cp_duplicate_order_threshold_state_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_duplicate_order_threshold_state_message(&got, wire, 0) == 41);
  assert(encode_cp_duplicate_order_threshold_state_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cp Order Rate Threshold State Message: 40 bytes ------------------------- */

/* CPOrderRateThresholdStateMessage */
typedef struct {
  uint8_t cl_ord_id_optional[20];      /* bytes 0 to 19 */
  uint8_t underlier_optional[6];       /* bytes 20 to 25 */
  uint8_t efid_optional[4];            /* bytes 26 to 29 */
  uint8_t risk_group_id[2];            /* bytes 30 to 31 */
  uint8_t max_order_msgs[4];           /* bytes 32 to 35 */
  uint8_t period_in_milli_seconds[4];  /* bytes 36 to 39 */
} CpOrderRateThresholdStateMessage;

/* any Cp Order Rate Threshold State Message at all: every byte one the checker chooses */
static void any_cp_order_rate_threshold_state_message(CpOrderRateThresholdStateMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_order_msgs[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = arbitrary(); }
}

/* Cp Order Rate Threshold State Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_cp_order_rate_threshold_state_message(const CpOrderRateThresholdStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->efid_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_order_msgs[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->period_in_milli_seconds[i]; }

  return at;
}

/* Cp Order Rate Threshold State Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_cp_order_rate_threshold_state_message(CpOrderRateThresholdStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->efid_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_order_msgs[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->period_in_milli_seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Cp Order Rate Threshold State Message is what was written, byte for byte */
static void equal_cp_order_rate_threshold_state_message(const CpOrderRateThresholdStateMessage *read, const CpOrderRateThresholdStateMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id_optional[i] == written->cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier_optional[i] == written->underlier_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->efid_optional[i] == written->efid_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_order_msgs[i] == written->max_order_msgs[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->period_in_milli_seconds[i] == written->period_in_milli_seconds[i]); }
}

/* Cp Order Rate Threshold State Message: written and read back, then read and written back */
static void check_cp_order_rate_threshold_state_message(void) {
  CpOrderRateThresholdStateMessage sent;
  CpOrderRateThresholdStateMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_cp_order_rate_threshold_state_message(&sent);
  assert(encode_cp_order_rate_threshold_state_message(&sent, wire, 0) == 40);
  assert(decode_cp_order_rate_threshold_state_message(&got, wire, 0) == 40);
  equal_cp_order_rate_threshold_state_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_cp_order_rate_threshold_state_message(&got, wire, 0) == 40);
  assert(encode_cp_order_rate_threshold_state_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_common_header();
  check_login_accepted_message();
  check_login_rejected_message();
  check_start_of_session_message();
  check_replay_begin_message();
  check_replay_rejected_message();
  check_replay_complete_message();
  check_stream_begin_message();
  check_stream_rejected_message();
  check_stream_complete_message();
  check_sbe_header();
  check_active_risk_threshold_state_message();
  check_active_risk_threshold_change_rejected_message();
  check_active_risk_acknowledged_message();
  check_active_risk_acknowledge_rejected_message();
  check_active_risk_quantity_update_notification_message();
  check_cp_volume_threshold_state_message();
  check_cp_executed_notional_threshold_state_message();
  check_cp_total_executions_threshold_state_message();
  check_cp_percent_outstanding_contracts_threshold_state_message();
  check_cp_breach_count_threshold_state_message();
  check_manual_cp_breach_trigger_pending_message();
  check_manual_cp_breach_trigger_done_message();
  check_risk_threshold_update_rejected_message();
  check_passive_risk_threshold_notification_message();
  check_single_order_allow_iso_orders_state_message();
  check_single_order_allow_orders_in_crossed_market_state_message();
  check_single_order_max_notional_threshold_state_message();
  check_single_order_max_contracts_threshold_state_message();
  check_single_order_allow_market_orders_state_message();
  check_single_order_restricted_underlier_state_message();
  check_risk_settings_query_done_message();
  check_risk_settings_query_rejected_message();
  check_manual_cp_breach_trigger_rejected_message();
  check_breach_clear_rejected_message();
  check_breach_cleared_message();
  check_breach_clear_all_accepted_message();
  check_breach_clear_all_rejected_message();
  check_breach_clear_all_by_efid_or_underlier_accepted_message();
  check_breach_clear_all_by_efid_or_underlier_rejected_message();
  check_cp_gross_notional_threshold_state_message();
  check_cp_market_order_gross_notional_threshold_state_message();
  check_cp_net_notional_threshold_state_message();
  check_cp_market_order_net_notional_threshold_state_message();
  check_cp_duplicate_order_threshold_state_message();
  check_cp_order_rate_threshold_state_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
