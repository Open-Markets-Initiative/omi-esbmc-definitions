// memx/memxoptions/memo/MemxOptions_Memo_v1_10_Server.c
/*
 * The Members Exchange Members Orders
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
 *   - a field read in bits
 *   - a block whose stated length holds more than its fields
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

/* ---- Sbe Header: 7 bytes ----------------------------------------------------- */

/* Sbe Header */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id;      /* byte 2 */
  uint8_t schema_id;        /* byte 3 */
  uint8_t version[2];       /* bytes 4 to 5 */
  uint8_t num_groups;       /* byte 6 */
} SbeHeader;

/* any Sbe Header at all: every byte one the checker chooses */
static void any_sbe_header(SbeHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->template_id = arbitrary();
  record->schema_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
  record->num_groups = arbitrary();
}

/* Sbe Header to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_sbe_header(const SbeHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->template_id;
  wire[at++] = record->schema_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }
  wire[at++] = record->num_groups;

  return at;
}

/* Sbe Header off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_sbe_header(SbeHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->template_id = wire[at++];
  record->schema_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }
  record->num_groups = wire[at++];

  return at;
}

/* what was read of Sbe Header is what was written, byte for byte */
static void equal_sbe_header(const SbeHeader *read, const SbeHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->template_id == written->template_id);
  assert(read->schema_id == written->schema_id);
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
  assert(read->num_groups == written->num_groups);
}

/* Sbe Header: written and read back, then read and written back */
static void check_sbe_header(void) {
  SbeHeader sent;
  SbeHeader got;
  uint8_t wire[7];
  uint8_t again[7];

  any_sbe_header(&sent);
  assert(encode_sbe_header(&sent, wire, 0) == 7);
  assert(decode_sbe_header(&got, wire, 0) == 7);
  equal_sbe_header(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_sbe_header(&got, wire, 0) == 7);
  assert(encode_sbe_header(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Repeating Group Dimensions: 2 bytes ------------------------------------- */

/* RepeatingGroupDimensions */
typedef struct {
  uint8_t block_length_short;  /* byte 0 */
  uint8_t num_in_group;        /* byte 1 */
} RepeatingGroupDimensions;

/* any Repeating Group Dimensions at all: every byte one the checker chooses */
static void any_repeating_group_dimensions(RepeatingGroupDimensions *record) {
  record->block_length_short = arbitrary();
  record->num_in_group = arbitrary();
}

/* Repeating Group Dimensions to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_repeating_group_dimensions(const RepeatingGroupDimensions *record, uint8_t *wire, size_t at) {
  wire[at++] = record->block_length_short;
  wire[at++] = record->num_in_group;

  return at;
}

/* Repeating Group Dimensions off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_repeating_group_dimensions(RepeatingGroupDimensions *record, const uint8_t *wire, size_t at) {
  record->block_length_short = wire[at++];
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Repeating Group Dimensions is what was written, byte for byte */
static void equal_repeating_group_dimensions(const RepeatingGroupDimensions *read, const RepeatingGroupDimensions *written) {
  assert(read->block_length_short == written->block_length_short);
  assert(read->num_in_group == written->num_in_group);
}

/* Repeating Group Dimensions: written and read back, then read and written back */
static void check_repeating_group_dimensions(void) {
  RepeatingGroupDimensions sent;
  RepeatingGroupDimensions got;
  uint8_t wire[2];
  uint8_t again[2];

  any_repeating_group_dimensions(&sent);
  assert(encode_repeating_group_dimensions(&sent, wire, 0) == 2);
  assert(decode_repeating_group_dimensions(&got, wire, 0) == 2);
  equal_repeating_group_dimensions(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_repeating_group_dimensions(&got, wire, 0) == 2);
  assert(encode_repeating_group_dimensions(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Bulk Quote Component New Message: 83 bytes ------------- */

/* ExecutionReport_BulkQuote_ComponentNewMessage */
typedef struct {
  uint8_t order_id[8];        /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];      /* bytes 8 to 27 */
  uint8_t list_seq_no;        /* byte 28 */
  uint8_t exec_id[8];         /* bytes 29 to 36 */
  uint8_t ord_status;         /* byte 37 */
  uint8_t security_id[8];     /* bytes 38 to 45 */
  uint8_t side;               /* byte 46 */
  uint8_t order_qty[4];       /* bytes 47 to 50 */
  uint8_t price_optional[8];  /* bytes 51 to 58 */
  uint8_t leaves_qty[4];      /* bytes 59 to 62 */
  uint8_t cum_qty[4];         /* bytes 63 to 66 */
  uint8_t sending_time[8];    /* bytes 67 to 74 */
  uint8_t transact_time[8];   /* bytes 75 to 82 */
} ExecutionReportBulkQuoteComponentNewMessage;

/* any Execution Report Bulk Quote Component New Message at all: every byte one the checker chooses */
static void any_execution_report_bulk_quote_component_new_message(ExecutionReportBulkQuoteComponentNewMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->list_seq_no = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Execution Report Bulk Quote Component New Message to the wire: 83 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_bulk_quote_component_new_message(const ExecutionReportBulkQuoteComponentNewMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->list_seq_no;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Execution Report Bulk Quote Component New Message off the wire: 83 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_bulk_quote_component_new_message(ExecutionReportBulkQuoteComponentNewMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->list_seq_no = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Bulk Quote Component New Message is what was written, byte for byte */
static void equal_execution_report_bulk_quote_component_new_message(const ExecutionReportBulkQuoteComponentNewMessage *read, const ExecutionReportBulkQuoteComponentNewMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->list_seq_no == written->list_seq_no);
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_optional[i] == written->price_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Execution Report Bulk Quote Component New Message: written and read back, then read and written back */
static void check_execution_report_bulk_quote_component_new_message(void) {
  ExecutionReportBulkQuoteComponentNewMessage sent;
  ExecutionReportBulkQuoteComponentNewMessage got;
  uint8_t wire[83];
  uint8_t again[83];

  any_execution_report_bulk_quote_component_new_message(&sent);
  assert(encode_execution_report_bulk_quote_component_new_message(&sent, wire, 0) == 83);
  assert(decode_execution_report_bulk_quote_component_new_message(&got, wire, 0) == 83);
  equal_execution_report_bulk_quote_component_new_message(&got, &sent);

  for (size_t i = 0; i < 83; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_bulk_quote_component_new_message(&got, wire, 0) == 83);
  assert(encode_execution_report_bulk_quote_component_new_message(&got, again, 0) == 83);
  for (size_t i = 0; i < 83; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Rejected Message: 57 bytes ----------------------------- */

/* ExecutionReport_RejectedMessage */
typedef struct {
  uint8_t cl_ord_id[20];           /* bytes 0 to 19 */
  uint8_t list_seq_no;             /* byte 20 */
  uint8_t exec_id[8];              /* bytes 21 to 28 */
  uint8_t ord_status;              /* byte 29 */
  uint8_t order_reject_reason[2];  /* bytes 30 to 31 */
  uint8_t security_id[8];          /* bytes 32 to 39 */
  uint8_t side;                    /* byte 40 */
  uint8_t leaves_qty[4];           /* bytes 41 to 44 */
  uint8_t cum_qty[4];              /* bytes 45 to 48 */
  uint8_t sending_time[8];         /* bytes 49 to 56 */
} ExecutionReportRejectedMessage;

/* any Execution Report Rejected Message at all: every byte one the checker chooses */
static void any_execution_report_rejected_message(ExecutionReportRejectedMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->list_seq_no = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->order_reject_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
}

/* Execution Report Rejected Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_rejected_message(const ExecutionReportRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->list_seq_no;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->order_reject_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }

  return at;
}

/* Execution Report Rejected Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_rejected_message(ExecutionReportRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->list_seq_no = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->order_reject_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Rejected Message is what was written, byte for byte */
static void equal_execution_report_rejected_message(const ExecutionReportRejectedMessage *read, const ExecutionReportRejectedMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->list_seq_no == written->list_seq_no);
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 2; i++) { assert(read->order_reject_reason[i] == written->order_reject_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
}

/* Execution Report Rejected Message: written and read back, then read and written back */
static void check_execution_report_rejected_message(void) {
  ExecutionReportRejectedMessage sent;
  ExecutionReportRejectedMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_execution_report_rejected_message(&sent);
  assert(encode_execution_report_rejected_message(&sent, wire, 0) == 57);
  assert(decode_execution_report_rejected_message(&got, wire, 0) == 57);
  equal_execution_report_rejected_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_rejected_message(&got, wire, 0) == 57);
  assert(encode_execution_report_rejected_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Pending Cancel Message: 75 bytes ----------------------- */

/* ExecutionReport_PendingCancelMessage */
typedef struct {
  uint8_t order_id[8];         /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];       /* bytes 8 to 27 */
  uint8_t list_seq_no;         /* byte 28 */
  uint8_t orig_cl_ord_id[20];  /* bytes 29 to 48 */
  uint8_t ord_status;          /* byte 49 */
  uint8_t security_id[8];      /* bytes 50 to 57 */
  uint8_t side_optional;       /* byte 58 */
  uint8_t leaves_qty[4];       /* bytes 59 to 62 */
  uint8_t cum_qty[4];          /* bytes 63 to 66 */
  uint8_t sending_time[8];     /* bytes 67 to 74 */
} ExecutionReportPendingCancelMessage;

/* any Execution Report Pending Cancel Message at all: every byte one the checker chooses */
static void any_execution_report_pending_cancel_message(ExecutionReportPendingCancelMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->list_seq_no = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  record->side_optional = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
}

/* Execution Report Pending Cancel Message to the wire: 75 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_pending_cancel_message(const ExecutionReportPendingCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->list_seq_no;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side_optional;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }

  return at;
}

/* Execution Report Pending Cancel Message off the wire: 75 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_pending_cancel_message(ExecutionReportPendingCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->list_seq_no = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  record->side_optional = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Pending Cancel Message is what was written, byte for byte */
static void equal_execution_report_pending_cancel_message(const ExecutionReportPendingCancelMessage *read, const ExecutionReportPendingCancelMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->list_seq_no == written->list_seq_no);
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side_optional == written->side_optional);
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
}

/* Execution Report Pending Cancel Message: written and read back, then read and written back */
static void check_execution_report_pending_cancel_message(void) {
  ExecutionReportPendingCancelMessage sent;
  ExecutionReportPendingCancelMessage got;
  uint8_t wire[75];
  uint8_t again[75];

  any_execution_report_pending_cancel_message(&sent);
  assert(encode_execution_report_pending_cancel_message(&sent, wire, 0) == 75);
  assert(decode_execution_report_pending_cancel_message(&got, wire, 0) == 75);
  equal_execution_report_pending_cancel_message(&got, &sent);

  for (size_t i = 0; i < 75; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_pending_cancel_message(&got, wire, 0) == 75);
  assert(encode_execution_report_pending_cancel_message(&got, again, 0) == 75);
  for (size_t i = 0; i < 75; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Canceled Message: 93 bytes ----------------------------- */

/* ExecutionReport_CanceledMessage */
typedef struct {
  uint8_t order_id[8];                  /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];                /* bytes 8 to 27 */
  uint8_t list_seq_no;                  /* byte 28 */
  uint8_t orig_cl_ord_id_optional[20];  /* bytes 29 to 48 */
  uint8_t exec_id[8];                   /* bytes 49 to 56 */
  uint8_t ord_status;                   /* byte 57 */
  uint8_t cancel_reason;                /* byte 58 */
  uint8_t security_id[8];               /* bytes 59 to 66 */
  uint8_t side_optional;                /* byte 67 */
  uint8_t leaves_qty[4];                /* bytes 68 to 71 */
  uint8_t cum_qty[4];                   /* bytes 72 to 75 */
  uint8_t sending_time[8];              /* bytes 76 to 83 */
  uint8_t transact_time[8];             /* bytes 84 to 91 */
  uint8_t orig_list_seq_no;             /* byte 92 */
} ExecutionReportCanceledMessage;

/* any Execution Report Canceled Message at all: every byte one the checker chooses */
static void any_execution_report_canceled_message(ExecutionReportCanceledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->list_seq_no = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->cancel_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  record->side_optional = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  record->orig_list_seq_no = arbitrary();
}

/* Execution Report Canceled Message to the wire: 93 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_canceled_message(const ExecutionReportCanceledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->list_seq_no;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->cancel_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side_optional;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  wire[at++] = record->orig_list_seq_no;

  return at;
}

/* Execution Report Canceled Message off the wire: 93 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_canceled_message(ExecutionReportCanceledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->list_seq_no = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->cancel_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  record->side_optional = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  record->orig_list_seq_no = wire[at++];

  return at;
}

/* what was read of Execution Report Canceled Message is what was written, byte for byte */
static void equal_execution_report_canceled_message(const ExecutionReportCanceledMessage *read, const ExecutionReportCanceledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->list_seq_no == written->list_seq_no);
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id_optional[i] == written->orig_cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->cancel_reason == written->cancel_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side_optional == written->side_optional);
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  assert(read->orig_list_seq_no == written->orig_list_seq_no);
}

/* Execution Report Canceled Message: written and read back, then read and written back */
static void check_execution_report_canceled_message(void) {
  ExecutionReportCanceledMessage sent;
  ExecutionReportCanceledMessage got;
  uint8_t wire[93];
  uint8_t again[93];

  any_execution_report_canceled_message(&sent);
  assert(encode_execution_report_canceled_message(&sent, wire, 0) == 93);
  assert(decode_execution_report_canceled_message(&got, wire, 0) == 93);
  equal_execution_report_canceled_message(&got, &sent);

  for (size_t i = 0; i < 93; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_canceled_message(&got, wire, 0) == 93);
  assert(encode_execution_report_canceled_message(&got, again, 0) == 93);
  for (size_t i = 0; i < 93; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Pending Replace Message: 96 bytes ---------------------- */

/* ExecutionReport_PendingReplaceMessage */
typedef struct {
  uint8_t order_id[8];         /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];       /* bytes 8 to 27 */
  uint8_t list_seq_no;         /* byte 28 */
  uint8_t orig_cl_ord_id[20];  /* bytes 29 to 48 */
  uint8_t exec_id[8];          /* bytes 49 to 56 */
  uint8_t ord_status;          /* byte 57 */
  uint8_t security_id[8];      /* bytes 58 to 65 */
  uint8_t side;                /* byte 66 */
  uint8_t order_qty[4];        /* bytes 67 to 70 */
  uint8_t ord_type;            /* byte 71 */
  uint8_t price_optional[8];   /* bytes 72 to 79 */
  uint8_t leaves_qty[4];       /* bytes 80 to 83 */
  uint8_t cum_qty[4];          /* bytes 84 to 87 */
  uint8_t sending_time[8];     /* bytes 88 to 95 */
} ExecutionReportPendingReplaceMessage;

/* any Execution Report Pending Replace Message at all: every byte one the checker chooses */
static void any_execution_report_pending_replace_message(ExecutionReportPendingReplaceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->list_seq_no = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
}

/* Execution Report Pending Replace Message to the wire: 96 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_pending_replace_message(const ExecutionReportPendingReplaceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->list_seq_no;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }

  return at;
}

/* Execution Report Pending Replace Message off the wire: 96 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_pending_replace_message(ExecutionReportPendingReplaceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->list_seq_no = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Pending Replace Message is what was written, byte for byte */
static void equal_execution_report_pending_replace_message(const ExecutionReportPendingReplaceMessage *read, const ExecutionReportPendingReplaceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->list_seq_no == written->list_seq_no);
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price_optional[i] == written->price_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
}

/* Execution Report Pending Replace Message: written and read back, then read and written back */
static void check_execution_report_pending_replace_message(void) {
  ExecutionReportPendingReplaceMessage sent;
  ExecutionReportPendingReplaceMessage got;
  uint8_t wire[96];
  uint8_t again[96];

  any_execution_report_pending_replace_message(&sent);
  assert(encode_execution_report_pending_replace_message(&sent, wire, 0) == 96);
  assert(decode_execution_report_pending_replace_message(&got, wire, 0) == 96);
  equal_execution_report_pending_replace_message(&got, &sent);

  for (size_t i = 0; i < 96; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_pending_replace_message(&got, wire, 0) == 96);
  assert(encode_execution_report_pending_replace_message(&got, again, 0) == 96);
  for (size_t i = 0; i < 96; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Replaced Message: 105 bytes ---------------------------- */

/* ExecutionReport_ReplacedMessage */
typedef struct {
  uint8_t order_id[8];         /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];       /* bytes 8 to 27 */
  uint8_t list_seq_no;         /* byte 28 */
  uint8_t orig_cl_ord_id[20];  /* bytes 29 to 48 */
  uint8_t exec_id[8];          /* bytes 49 to 56 */
  uint8_t ord_status;          /* byte 57 */
  uint8_t security_id[8];      /* bytes 58 to 65 */
  uint8_t side;                /* byte 66 */
  uint8_t order_qty[4];        /* bytes 67 to 70 */
  uint8_t ord_type;            /* byte 71 */
  uint8_t price_optional[8];   /* bytes 72 to 79 */
  uint8_t leaves_qty[4];       /* bytes 80 to 83 */
  uint8_t cum_qty[4];          /* bytes 84 to 87 */
  uint8_t sending_time[8];     /* bytes 88 to 95 */
  uint8_t transact_time[8];    /* bytes 96 to 103 */
  uint8_t orig_list_seq_no;    /* byte 104 */
} ExecutionReportReplacedMessage;

/* any Execution Report Replaced Message at all: every byte one the checker chooses */
static void any_execution_report_replaced_message(ExecutionReportReplacedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->list_seq_no = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  record->orig_list_seq_no = arbitrary();
}

/* Execution Report Replaced Message to the wire: 105 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_replaced_message(const ExecutionReportReplacedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->list_seq_no;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  wire[at++] = record->orig_list_seq_no;

  return at;
}

/* Execution Report Replaced Message off the wire: 105 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_replaced_message(ExecutionReportReplacedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->list_seq_no = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  record->orig_list_seq_no = wire[at++];

  return at;
}

/* what was read of Execution Report Replaced Message is what was written, byte for byte */
static void equal_execution_report_replaced_message(const ExecutionReportReplacedMessage *read, const ExecutionReportReplacedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->list_seq_no == written->list_seq_no);
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price_optional[i] == written->price_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  assert(read->orig_list_seq_no == written->orig_list_seq_no);
}

/* Execution Report Replaced Message: written and read back, then read and written back */
static void check_execution_report_replaced_message(void) {
  ExecutionReportReplacedMessage sent;
  ExecutionReportReplacedMessage got;
  uint8_t wire[105];
  uint8_t again[105];

  any_execution_report_replaced_message(&sent);
  assert(encode_execution_report_replaced_message(&sent, wire, 0) == 105);
  assert(decode_execution_report_replaced_message(&got, wire, 0) == 105);
  equal_execution_report_replaced_message(&got, &sent);

  for (size_t i = 0; i < 105; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_replaced_message(&got, wire, 0) == 105);
  assert(encode_execution_report_replaced_message(&got, again, 0) == 105);
  for (size_t i = 0; i < 105; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Trade Correction Message: 91 bytes --------------------- */

/* ExecutionReport_TradeCorrectionMessage */
typedef struct {
  uint8_t order_id[8];      /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];    /* bytes 8 to 27 */
  uint8_t list_seq_no;      /* byte 28 */
  uint8_t trd_match_id[8];  /* bytes 29 to 36 */
  uint8_t exec_id[8];       /* bytes 37 to 44 */
  uint8_t exec_ref_id[8];   /* bytes 45 to 52 */
  uint8_t ord_status;       /* byte 53 */
  uint8_t security_id[8];   /* bytes 54 to 61 */
  uint8_t side;             /* byte 62 */
  uint8_t last_qty[4];      /* bytes 63 to 66 */
  uint8_t last_px[8];       /* bytes 67 to 74 */
  uint8_t leaves_qty[4];    /* bytes 75 to 78 */
  uint8_t cum_qty[4];       /* bytes 79 to 82 */
  uint8_t sending_time[8];  /* bytes 83 to 90 */
} ExecutionReportTradeCorrectionMessage;

/* any Execution Report Trade Correction Message at all: every byte one the checker chooses */
static void any_execution_report_trade_correction_message(ExecutionReportTradeCorrectionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->list_seq_no = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trd_match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
}

/* Execution Report Trade Correction Message to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_trade_correction_message(const ExecutionReportTradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->list_seq_no;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_match_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_ref_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }

  return at;
}

/* Execution Report Trade Correction Message off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_trade_correction_message(ExecutionReportTradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->list_seq_no = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trd_match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Trade Correction Message is what was written, byte for byte */
static void equal_execution_report_trade_correction_message(const ExecutionReportTradeCorrectionMessage *read, const ExecutionReportTradeCorrectionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->list_seq_no == written->list_seq_no);
  for (size_t i = 0; i < 8; i++) { assert(read->trd_match_id[i] == written->trd_match_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_ref_id[i] == written->exec_ref_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
}

/* Execution Report Trade Correction Message: written and read back, then read and written back */
static void check_execution_report_trade_correction_message(void) {
  ExecutionReportTradeCorrectionMessage sent;
  ExecutionReportTradeCorrectionMessage got;
  uint8_t wire[91];
  uint8_t again[91];

  any_execution_report_trade_correction_message(&sent);
  assert(encode_execution_report_trade_correction_message(&sent, wire, 0) == 91);
  assert(decode_execution_report_trade_correction_message(&got, wire, 0) == 91);
  equal_execution_report_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_trade_correction_message(&got, wire, 0) == 91);
  assert(encode_execution_report_trade_correction_message(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Trade Break Message: 79 bytes -------------------------- */

/* ExecutionReport_TradeBreakMessage */
typedef struct {
  uint8_t order_id[8];      /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];    /* bytes 8 to 27 */
  uint8_t list_seq_no;      /* byte 28 */
  uint8_t trd_match_id[8];  /* bytes 29 to 36 */
  uint8_t exec_id[8];       /* bytes 37 to 44 */
  uint8_t exec_ref_id[8];   /* bytes 45 to 52 */
  uint8_t ord_status;       /* byte 53 */
  uint8_t security_id[8];   /* bytes 54 to 61 */
  uint8_t side;             /* byte 62 */
  uint8_t leaves_qty[4];    /* bytes 63 to 66 */
  uint8_t cum_qty[4];       /* bytes 67 to 70 */
  uint8_t sending_time[8];  /* bytes 71 to 78 */
} ExecutionReportTradeBreakMessage;

/* any Execution Report Trade Break Message at all: every byte one the checker chooses */
static void any_execution_report_trade_break_message(ExecutionReportTradeBreakMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->list_seq_no = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trd_match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
}

/* Execution Report Trade Break Message to the wire: 79 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_trade_break_message(const ExecutionReportTradeBreakMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->list_seq_no;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_match_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_ref_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }

  return at;
}

/* Execution Report Trade Break Message off the wire: 79 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_trade_break_message(ExecutionReportTradeBreakMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->list_seq_no = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trd_match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Trade Break Message is what was written, byte for byte */
static void equal_execution_report_trade_break_message(const ExecutionReportTradeBreakMessage *read, const ExecutionReportTradeBreakMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->list_seq_no == written->list_seq_no);
  for (size_t i = 0; i < 8; i++) { assert(read->trd_match_id[i] == written->trd_match_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_ref_id[i] == written->exec_ref_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
}

/* Execution Report Trade Break Message: written and read back, then read and written back */
static void check_execution_report_trade_break_message(void) {
  ExecutionReportTradeBreakMessage sent;
  ExecutionReportTradeBreakMessage got;
  uint8_t wire[79];
  uint8_t again[79];

  any_execution_report_trade_break_message(&sent);
  assert(encode_execution_report_trade_break_message(&sent, wire, 0) == 79);
  assert(decode_execution_report_trade_break_message(&got, wire, 0) == 79);
  equal_execution_report_trade_break_message(&got, &sent);

  for (size_t i = 0; i < 79; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_trade_break_message(&got, wire, 0) == 79);
  assert(encode_execution_report_trade_break_message(&got, again, 0) == 79);
  for (size_t i = 0; i < 79; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Restatement Message: 85 bytes -------------------------- */

/* ExecutionReport_RestatementMessage */
typedef struct {
  uint8_t order_id[8];                  /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];                /* bytes 8 to 27 */
  uint8_t list_seq_no;                  /* byte 28 */
  uint8_t exec_id[8];                   /* bytes 29 to 36 */
  uint8_t ord_status;                   /* byte 37 */
  uint8_t security_id[8];               /* bytes 38 to 45 */
  uint8_t exec_restatement_reason;      /* byte 46 */
  uint8_t extended_restatement_reason;  /* byte 47 */
  uint8_t side;                         /* byte 48 */
  uint8_t last_px[8];                   /* bytes 49 to 56 */
  uint8_t last_qty_optional[4];         /* bytes 57 to 60 */
  uint8_t leaves_qty[4];                /* bytes 61 to 64 */
  uint8_t cum_qty[4];                   /* bytes 65 to 68 */
  uint8_t sending_time[8];              /* bytes 69 to 76 */
  uint8_t transact_time[8];             /* bytes 77 to 84 */
} ExecutionReportRestatementMessage;

/* any Execution Report Restatement Message at all: every byte one the checker chooses */
static void any_execution_report_restatement_message(ExecutionReportRestatementMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->list_seq_no = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  record->exec_restatement_reason = arbitrary();
  record->extended_restatement_reason = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Execution Report Restatement Message to the wire: 85 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_restatement_message(const ExecutionReportRestatementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->list_seq_no;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->exec_restatement_reason;
  wire[at++] = record->extended_restatement_reason;
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Execution Report Restatement Message off the wire: 85 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_restatement_message(ExecutionReportRestatementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->list_seq_no = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  record->exec_restatement_reason = wire[at++];
  record->extended_restatement_reason = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Restatement Message is what was written, byte for byte */
static void equal_execution_report_restatement_message(const ExecutionReportRestatementMessage *read, const ExecutionReportRestatementMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->list_seq_no == written->list_seq_no);
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->exec_restatement_reason == written->exec_restatement_reason);
  assert(read->extended_restatement_reason == written->extended_restatement_reason);
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty_optional[i] == written->last_qty_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Execution Report Restatement Message: written and read back, then read and written back */
static void check_execution_report_restatement_message(void) {
  ExecutionReportRestatementMessage sent;
  ExecutionReportRestatementMessage got;
  uint8_t wire[85];
  uint8_t again[85];

  any_execution_report_restatement_message(&sent);
  assert(encode_execution_report_restatement_message(&sent, wire, 0) == 85);
  assert(decode_execution_report_restatement_message(&got, wire, 0) == 85);
  equal_execution_report_restatement_message(&got, &sent);

  for (size_t i = 0; i < 85; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_restatement_message(&got, wire, 0) == 85);
  assert(encode_execution_report_restatement_message(&got, again, 0) == 85);
  for (size_t i = 0; i < 85; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Done Message: 40 bytes -------------------------------------- */

/* MassCancelDoneMessage */
typedef struct {
  uint8_t cl_ord_id[20];             /* bytes 0 to 19 */
  uint8_t total_affected_orders[4];  /* bytes 20 to 23 */
  uint8_t sending_time[8];           /* bytes 24 to 31 */
  uint8_t transact_time[8];          /* bytes 32 to 39 */
} MassCancelDoneMessage;

/* any Mass Cancel Done Message at all: every byte one the checker chooses */
static void any_mass_cancel_done_message(MassCancelDoneMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_affected_orders[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Mass Cancel Done Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_done_message(const MassCancelDoneMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_affected_orders[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Mass Cancel Done Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_done_message(MassCancelDoneMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_affected_orders[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Done Message is what was written, byte for byte */
static void equal_mass_cancel_done_message(const MassCancelDoneMessage *read, const MassCancelDoneMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_affected_orders[i] == written->total_affected_orders[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Mass Cancel Done Message: written and read back, then read and written back */
static void check_mass_cancel_done_message(void) {
  MassCancelDoneMessage sent;
  MassCancelDoneMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_mass_cancel_done_message(&sent);
  assert(encode_mass_cancel_done_message(&sent, wire, 0) == 40);
  assert(decode_mass_cancel_done_message(&got, wire, 0) == 40);
  equal_mass_cancel_done_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_done_message(&got, wire, 0) == 40);
  assert(encode_mass_cancel_done_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Reject Message: 41 bytes ----------------------------------- */

/* OrderCancelRejectMessage */
typedef struct {
  uint8_t cl_ord_id[20];                    /* bytes 0 to 19 */
  uint8_t list_seq_no;                      /* byte 20 */
  uint8_t cxl_rej_response_to;              /* byte 21 */
  uint8_t cxl_rej_reason[2];                /* bytes 22 to 23 */
  uint8_t options_security_id_optional[8];  /* bytes 24 to 31 */
  uint8_t side_optional;                    /* byte 32 */
  uint8_t sending_time[8];                  /* bytes 33 to 40 */
} OrderCancelRejectMessage;

/* any Order Cancel Reject Message at all: every byte one the checker chooses */
static void any_order_cancel_reject_message(OrderCancelRejectMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->list_seq_no = arbitrary();
  record->cxl_rej_response_to = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->cxl_rej_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->options_security_id_optional[i] = arbitrary(); }
  record->side_optional = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
}

/* Order Cancel Reject Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_reject_message(const OrderCancelRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->list_seq_no;
  wire[at++] = record->cxl_rej_response_to;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->cxl_rej_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->options_security_id_optional[i]; }
  wire[at++] = record->side_optional;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }

  return at;
}

/* Order Cancel Reject Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_reject_message(OrderCancelRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->list_seq_no = wire[at++];
  record->cxl_rej_response_to = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->cxl_rej_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->options_security_id_optional[i] = wire[at++]; }
  record->side_optional = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Reject Message is what was written, byte for byte */
static void equal_order_cancel_reject_message(const OrderCancelRejectMessage *read, const OrderCancelRejectMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->list_seq_no == written->list_seq_no);
  assert(read->cxl_rej_response_to == written->cxl_rej_response_to);
  for (size_t i = 0; i < 2; i++) { assert(read->cxl_rej_reason[i] == written->cxl_rej_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->options_security_id_optional[i] == written->options_security_id_optional[i]); }
  assert(read->side_optional == written->side_optional);
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
}

/* Order Cancel Reject Message: written and read back, then read and written back */
static void check_order_cancel_reject_message(void) {
  OrderCancelRejectMessage sent;
  OrderCancelRejectMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_order_cancel_reject_message(&sent);
  assert(encode_order_cancel_reject_message(&sent, wire, 0) == 41);
  assert(decode_order_cancel_reject_message(&got, wire, 0) == 41);
  equal_order_cancel_reject_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_reject_message(&got, wire, 0) == 41);
  assert(encode_order_cancel_reject_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Notification Message: 9 bytes -------------------------------------- */

/* UserNotificationMessage */
typedef struct {
  uint8_t sending_time[8];  /* bytes 0 to 7 */
  uint8_t user_status;      /* byte 8 */
} UserNotificationMessage;

/* any User Notification Message at all: every byte one the checker chooses */
static void any_user_notification_message(UserNotificationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  record->user_status = arbitrary();
}

/* User Notification Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_user_notification_message(const UserNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  wire[at++] = record->user_status;

  return at;
}

/* User Notification Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_user_notification_message(UserNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  record->user_status = wire[at++];

  return at;
}

/* what was read of User Notification Message is what was written, byte for byte */
static void equal_user_notification_message(const UserNotificationMessage *read, const UserNotificationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  assert(read->user_status == written->user_status);
}

/* User Notification Message: written and read back, then read and written back */
static void check_user_notification_message(void) {
  UserNotificationMessage sent;
  UserNotificationMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_user_notification_message(&sent);
  assert(encode_user_notification_message(&sent, wire, 0) == 9);
  assert(decode_user_notification_message(&got, wire, 0) == 9);
  equal_user_notification_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_user_notification_message(&got, wire, 0) == 9);
  assert(encode_user_notification_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Clear Lockout Reject Message: 44 bytes ---------------------- */

/* MassCancelClearLockoutRejectMessage */
typedef struct {
  uint8_t cl_ord_id[20];    /* bytes 0 to 19 */
  uint8_t underlier[6];     /* bytes 20 to 25 */
  uint8_t lockout_id[8];    /* bytes 26 to 33 */
  uint8_t rej_reason[2];    /* bytes 34 to 35 */
  uint8_t sending_time[8];  /* bytes 36 to 43 */
} MassCancelClearLockoutRejectMessage;

/* any Mass Cancel Clear Lockout Reject Message at all: every byte one the checker chooses */
static void any_mass_cancel_clear_lockout_reject_message(MassCancelClearLockoutRejectMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lockout_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->rej_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
}

/* Mass Cancel Clear Lockout Reject Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_clear_lockout_reject_message(const MassCancelClearLockoutRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lockout_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->rej_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }

  return at;
}

/* Mass Cancel Clear Lockout Reject Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_clear_lockout_reject_message(MassCancelClearLockoutRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lockout_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->rej_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Clear Lockout Reject Message is what was written, byte for byte */
static void equal_mass_cancel_clear_lockout_reject_message(const MassCancelClearLockoutRejectMessage *read, const MassCancelClearLockoutRejectMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier[i] == written->underlier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lockout_id[i] == written->lockout_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->rej_reason[i] == written->rej_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
}

/* Mass Cancel Clear Lockout Reject Message: written and read back, then read and written back */
static void check_mass_cancel_clear_lockout_reject_message(void) {
  MassCancelClearLockoutRejectMessage sent;
  MassCancelClearLockoutRejectMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_mass_cancel_clear_lockout_reject_message(&sent);
  assert(encode_mass_cancel_clear_lockout_reject_message(&sent, wire, 0) == 44);
  assert(decode_mass_cancel_clear_lockout_reject_message(&got, wire, 0) == 44);
  equal_mass_cancel_clear_lockout_reject_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_clear_lockout_reject_message(&got, wire, 0) == 44);
  assert(encode_mass_cancel_clear_lockout_reject_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Clear Lockout Done Message: 50 bytes ------------------------ */

/* MassCancelClearLockoutDoneMessage */
typedef struct {
  uint8_t cl_ord_id[20];     /* bytes 0 to 19 */
  uint8_t underlier[6];      /* bytes 20 to 25 */
  uint8_t lockout_id[8];     /* bytes 26 to 33 */
  uint8_t sending_time[8];   /* bytes 34 to 41 */
  uint8_t transact_time[8];  /* bytes 42 to 49 */
} MassCancelClearLockoutDoneMessage;

/* any Mass Cancel Clear Lockout Done Message at all: every byte one the checker chooses */
static void any_mass_cancel_clear_lockout_done_message(MassCancelClearLockoutDoneMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lockout_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Mass Cancel Clear Lockout Done Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_clear_lockout_done_message(const MassCancelClearLockoutDoneMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lockout_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Mass Cancel Clear Lockout Done Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_clear_lockout_done_message(MassCancelClearLockoutDoneMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lockout_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Clear Lockout Done Message is what was written, byte for byte */
static void equal_mass_cancel_clear_lockout_done_message(const MassCancelClearLockoutDoneMessage *read, const MassCancelClearLockoutDoneMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlier[i] == written->underlier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lockout_id[i] == written->lockout_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Mass Cancel Clear Lockout Done Message: written and read back, then read and written back */
static void check_mass_cancel_clear_lockout_done_message(void) {
  MassCancelClearLockoutDoneMessage sent;
  MassCancelClearLockoutDoneMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_mass_cancel_clear_lockout_done_message(&sent);
  assert(encode_mass_cancel_clear_lockout_done_message(&sent, wire, 0) == 50);
  assert(decode_mass_cancel_clear_lockout_done_message(&got, wire, 0) == 50);
  equal_mass_cancel_clear_lockout_done_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_clear_lockout_done_message(&got, wire, 0) == 50);
  assert(encode_mass_cancel_clear_lockout_done_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Bulk Clear Lockout Reject Message: 30 bytes ----------------- */

/* MassCancelBulkClearLockoutRejectMessage */
typedef struct {
  uint8_t cl_ord_id[20];    /* bytes 0 to 19 */
  uint8_t rej_reason[2];    /* bytes 20 to 21 */
  uint8_t sending_time[8];  /* bytes 22 to 29 */
} MassCancelBulkClearLockoutRejectMessage;

/* any Mass Cancel Bulk Clear Lockout Reject Message at all: every byte one the checker chooses */
static void any_mass_cancel_bulk_clear_lockout_reject_message(MassCancelBulkClearLockoutRejectMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->rej_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
}

/* Mass Cancel Bulk Clear Lockout Reject Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_bulk_clear_lockout_reject_message(const MassCancelBulkClearLockoutRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->rej_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }

  return at;
}

/* Mass Cancel Bulk Clear Lockout Reject Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_bulk_clear_lockout_reject_message(MassCancelBulkClearLockoutRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->rej_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Bulk Clear Lockout Reject Message is what was written, byte for byte */
static void equal_mass_cancel_bulk_clear_lockout_reject_message(const MassCancelBulkClearLockoutRejectMessage *read, const MassCancelBulkClearLockoutRejectMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->rej_reason[i] == written->rej_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
}

/* Mass Cancel Bulk Clear Lockout Reject Message: written and read back, then read and written back */
static void check_mass_cancel_bulk_clear_lockout_reject_message(void) {
  MassCancelBulkClearLockoutRejectMessage sent;
  MassCancelBulkClearLockoutRejectMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_mass_cancel_bulk_clear_lockout_reject_message(&sent);
  assert(encode_mass_cancel_bulk_clear_lockout_reject_message(&sent, wire, 0) == 30);
  assert(decode_mass_cancel_bulk_clear_lockout_reject_message(&got, wire, 0) == 30);
  equal_mass_cancel_bulk_clear_lockout_reject_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_bulk_clear_lockout_reject_message(&got, wire, 0) == 30);
  assert(encode_mass_cancel_bulk_clear_lockout_reject_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Bulk Clear Lockout Accepted Message: 28 bytes --------------- */

/* MassCancelBulkClearLockoutAcceptedMessage */
typedef struct {
  uint8_t cl_ord_id[20];    /* bytes 0 to 19 */
  uint8_t sending_time[8];  /* bytes 20 to 27 */
} MassCancelBulkClearLockoutAcceptedMessage;

/* any Mass Cancel Bulk Clear Lockout Accepted Message at all: every byte one the checker chooses */
static void any_mass_cancel_bulk_clear_lockout_accepted_message(MassCancelBulkClearLockoutAcceptedMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
}

/* Mass Cancel Bulk Clear Lockout Accepted Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_bulk_clear_lockout_accepted_message(const MassCancelBulkClearLockoutAcceptedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }

  return at;
}

/* Mass Cancel Bulk Clear Lockout Accepted Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_bulk_clear_lockout_accepted_message(MassCancelBulkClearLockoutAcceptedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Bulk Clear Lockout Accepted Message is what was written, byte for byte */
static void equal_mass_cancel_bulk_clear_lockout_accepted_message(const MassCancelBulkClearLockoutAcceptedMessage *read, const MassCancelBulkClearLockoutAcceptedMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
}

/* Mass Cancel Bulk Clear Lockout Accepted Message: written and read back, then read and written back */
static void check_mass_cancel_bulk_clear_lockout_accepted_message(void) {
  MassCancelBulkClearLockoutAcceptedMessage sent;
  MassCancelBulkClearLockoutAcceptedMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_mass_cancel_bulk_clear_lockout_accepted_message(&sent);
  assert(encode_mass_cancel_bulk_clear_lockout_accepted_message(&sent, wire, 0) == 28);
  assert(decode_mass_cancel_bulk_clear_lockout_accepted_message(&got, wire, 0) == 28);
  equal_mass_cancel_bulk_clear_lockout_accepted_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_bulk_clear_lockout_accepted_message(&got, wire, 0) == 28);
  assert(encode_mass_cancel_bulk_clear_lockout_accepted_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
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
  check_repeating_group_dimensions();
  check_execution_report_bulk_quote_component_new_message();
  check_execution_report_rejected_message();
  check_execution_report_pending_cancel_message();
  check_execution_report_canceled_message();
  check_execution_report_pending_replace_message();
  check_execution_report_replaced_message();
  check_execution_report_trade_correction_message();
  check_execution_report_trade_break_message();
  check_execution_report_restatement_message();
  check_mass_cancel_done_message();
  check_order_cancel_reject_message();
  check_user_notification_message();
  check_mass_cancel_clear_lockout_reject_message();
  check_mass_cancel_clear_lockout_done_message();
  check_mass_cancel_bulk_clear_lockout_reject_message();
  check_mass_cancel_bulk_clear_lockout_accepted_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
