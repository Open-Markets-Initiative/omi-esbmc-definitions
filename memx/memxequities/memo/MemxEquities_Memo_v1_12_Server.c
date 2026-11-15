// memx/memxequities/memo/MemxEquities_Memo_v1_12_Server.c
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

/* ---- Execution Report Rejected Message: 58 bytes ----------------------------- */

/* ExecutionReport_RejectedMessage */
typedef struct {
  uint8_t sending_time[8];      /* bytes 0 to 7 */
  uint8_t cl_ord_id[16];        /* bytes 8 to 23 */
  uint8_t exec_id[8];           /* bytes 24 to 31 */
  uint8_t ord_status;           /* byte 32 */
  uint8_t symbol[6];            /* bytes 33 to 38 */
  uint8_t symbol_sfx[6];        /* bytes 39 to 44 */
  uint8_t leaves_qty[4];        /* bytes 45 to 48 */
  uint8_t cum_qty[4];           /* bytes 49 to 52 */
  uint8_t order_reject_reason;  /* byte 53 */
  uint8_t link_id_optional[4];  /* bytes 54 to 57 */
} ExecutionReportRejectedMessage;

/* any Execution Report Rejected Message at all: every byte one the checker chooses */
static void any_execution_report_rejected_message(ExecutionReportRejectedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  record->order_reject_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = arbitrary(); }
}

/* Execution Report Rejected Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_rejected_message(const ExecutionReportRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_sfx[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  wire[at++] = record->order_reject_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->link_id_optional[i]; }

  return at;
}

/* Execution Report Rejected Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_rejected_message(ExecutionReportRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  record->order_reject_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Rejected Message is what was written, byte for byte */
static void equal_execution_report_rejected_message(const ExecutionReportRejectedMessage *read, const ExecutionReportRejectedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_sfx[i] == written->symbol_sfx[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  assert(read->order_reject_reason == written->order_reject_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->link_id_optional[i] == written->link_id_optional[i]); }
}

/* Execution Report Rejected Message: written and read back, then read and written back */
static void check_execution_report_rejected_message(void) {
  ExecutionReportRejectedMessage sent;
  ExecutionReportRejectedMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_execution_report_rejected_message(&sent);
  assert(encode_execution_report_rejected_message(&sent, wire, 0) == 58);
  assert(decode_execution_report_rejected_message(&got, wire, 0) == 58);
  equal_execution_report_rejected_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_rejected_message(&got, wire, 0) == 58);
  assert(encode_execution_report_rejected_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Trade Message: 84 bytes -------------------------------- */

/* ExecutionReport_TradeMessage */
typedef struct {
  uint8_t sending_time[8];      /* bytes 0 to 7 */
  uint8_t order_id[8];          /* bytes 8 to 15 */
  uint8_t cl_ord_id[16];        /* bytes 16 to 31 */
  uint8_t exec_id[8];           /* bytes 32 to 39 */
  uint8_t ord_status;           /* byte 40 */
  uint8_t last_qty[4];          /* bytes 41 to 44 */
  uint8_t last_px[8];           /* bytes 45 to 52 */
  uint8_t leaves_qty[4];        /* bytes 53 to 56 */
  uint8_t cum_qty[4];           /* bytes 57 to 60 */
  uint8_t transact_time[8];     /* bytes 61 to 68 */
  uint8_t last_liquidity_ind;   /* byte 69 */
  uint8_t last_mkt;             /* byte 70 */
  uint8_t trd_matching_id[8];   /* bytes 71 to 78 */
  uint8_t link_id_optional[4];  /* bytes 79 to 82 */
  uint8_t security_group;       /* byte 83 */
} ExecutionReportTradeMessage;

/* any Execution Report Trade Message at all: every byte one the checker chooses */
static void any_execution_report_trade_message(ExecutionReportTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  record->last_liquidity_ind = arbitrary();
  record->last_mkt = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trd_matching_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = arbitrary(); }
  record->security_group = arbitrary();
}

/* Execution Report Trade Message to the wire: 84 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_trade_message(const ExecutionReportTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  wire[at++] = record->last_liquidity_ind;
  wire[at++] = record->last_mkt;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_matching_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->link_id_optional[i]; }
  wire[at++] = record->security_group;

  return at;
}

/* Execution Report Trade Message off the wire: 84 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_trade_message(ExecutionReportTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  record->last_liquidity_ind = wire[at++];
  record->last_mkt = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trd_matching_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = wire[at++]; }
  record->security_group = wire[at++];

  return at;
}

/* what was read of Execution Report Trade Message is what was written, byte for byte */
static void equal_execution_report_trade_message(const ExecutionReportTradeMessage *read, const ExecutionReportTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  assert(read->last_liquidity_ind == written->last_liquidity_ind);
  assert(read->last_mkt == written->last_mkt);
  for (size_t i = 0; i < 8; i++) { assert(read->trd_matching_id[i] == written->trd_matching_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->link_id_optional[i] == written->link_id_optional[i]); }
  assert(read->security_group == written->security_group);
}

/* Execution Report Trade Message: written and read back, then read and written back */
static void check_execution_report_trade_message(void) {
  ExecutionReportTradeMessage sent;
  ExecutionReportTradeMessage got;
  uint8_t wire[84];
  uint8_t again[84];

  any_execution_report_trade_message(&sent);
  assert(encode_execution_report_trade_message(&sent, wire, 0) == 84);
  assert(decode_execution_report_trade_message(&got, wire, 0) == 84);
  equal_execution_report_trade_message(&got, &sent);

  for (size_t i = 0; i < 84; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_trade_message(&got, wire, 0) == 84);
  assert(encode_execution_report_trade_message(&got, again, 0) == 84);
  for (size_t i = 0; i < 84; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Pending Cancel Message: 81 bytes ----------------------- */

/* ExecutionReport_PendingCancelMessage */
typedef struct {
  uint8_t sending_time[8];              /* bytes 0 to 7 */
  uint8_t order_id[8];                  /* bytes 8 to 15 */
  uint8_t cl_ord_id[16];                /* bytes 16 to 31 */
  uint8_t orig_cl_ord_id_optional[16];  /* bytes 32 to 47 */
  uint8_t exec_id[8];                   /* bytes 48 to 55 */
  uint8_t symbol[6];                    /* bytes 56 to 61 */
  uint8_t symbol_sfx[6];                /* bytes 62 to 67 */
  uint8_t ord_status;                   /* byte 68 */
  uint8_t leaves_qty[4];                /* bytes 69 to 72 */
  uint8_t cum_qty[4];                   /* bytes 73 to 76 */
  uint8_t link_id_optional[4];          /* bytes 77 to 80 */
} ExecutionReportPendingCancelMessage;

/* any Execution Report Pending Cancel Message at all: every byte one the checker chooses */
static void any_execution_report_pending_cancel_message(ExecutionReportPendingCancelMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->orig_cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = arbitrary(); }
}

/* Execution Report Pending Cancel Message to the wire: 81 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_pending_cancel_message(const ExecutionReportPendingCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->orig_cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_sfx[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->link_id_optional[i]; }

  return at;
}

/* Execution Report Pending Cancel Message off the wire: 81 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_pending_cancel_message(ExecutionReportPendingCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->orig_cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Pending Cancel Message is what was written, byte for byte */
static void equal_execution_report_pending_cancel_message(const ExecutionReportPendingCancelMessage *read, const ExecutionReportPendingCancelMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->orig_cl_ord_id_optional[i] == written->orig_cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_sfx[i] == written->symbol_sfx[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->link_id_optional[i] == written->link_id_optional[i]); }
}

/* Execution Report Pending Cancel Message: written and read back, then read and written back */
static void check_execution_report_pending_cancel_message(void) {
  ExecutionReportPendingCancelMessage sent;
  ExecutionReportPendingCancelMessage got;
  uint8_t wire[81];
  uint8_t again[81];

  any_execution_report_pending_cancel_message(&sent);
  assert(encode_execution_report_pending_cancel_message(&sent, wire, 0) == 81);
  assert(decode_execution_report_pending_cancel_message(&got, wire, 0) == 81);
  equal_execution_report_pending_cancel_message(&got, &sent);

  for (size_t i = 0; i < 81; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_pending_cancel_message(&got, wire, 0) == 81);
  assert(encode_execution_report_pending_cancel_message(&got, again, 0) == 81);
  for (size_t i = 0; i < 81; i++) { assert(again[i] == wire[i]); }
}

/* ---- Pending Mass Cancel Message: 55 bytes ----------------------------------- */

/* PendingMassCancelMessage */
typedef struct {
  uint8_t sending_time[8];       /* bytes 0 to 7 */
  uint8_t cl_ord_id[16];         /* bytes 8 to 23 */
  uint8_t symbol[6];             /* bytes 24 to 29 */
  uint8_t symbol_sfx[6];         /* bytes 30 to 35 */
  uint8_t side_optional;         /* byte 36 */
  uint8_t lower_than_price[8];   /* bytes 37 to 44 */
  uint8_t higher_than_price[8];  /* bytes 45 to 52 */
  uint8_t cancel_group_id[2];    /* bytes 53 to 54 */
} PendingMassCancelMessage;

/* any Pending Mass Cancel Message at all: every byte one the checker chooses */
static void any_pending_mass_cancel_message(PendingMassCancelMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = arbitrary(); }
  record->side_optional = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->lower_than_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->higher_than_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->cancel_group_id[i] = arbitrary(); }
}

/* Pending Mass Cancel Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_pending_mass_cancel_message(const PendingMassCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_sfx[i]; }
  wire[at++] = record->side_optional;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_than_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->higher_than_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->cancel_group_id[i]; }

  return at;
}

/* Pending Mass Cancel Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_pending_mass_cancel_message(PendingMassCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = wire[at++]; }
  record->side_optional = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->lower_than_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->higher_than_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->cancel_group_id[i] = wire[at++]; }

  return at;
}

/* what was read of Pending Mass Cancel Message is what was written, byte for byte */
static void equal_pending_mass_cancel_message(const PendingMassCancelMessage *read, const PendingMassCancelMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_sfx[i] == written->symbol_sfx[i]); }
  assert(read->side_optional == written->side_optional);
  for (size_t i = 0; i < 8; i++) { assert(read->lower_than_price[i] == written->lower_than_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->higher_than_price[i] == written->higher_than_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->cancel_group_id[i] == written->cancel_group_id[i]); }
}

/* Pending Mass Cancel Message: written and read back, then read and written back */
static void check_pending_mass_cancel_message(void) {
  PendingMassCancelMessage sent;
  PendingMassCancelMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_pending_mass_cancel_message(&sent);
  assert(encode_pending_mass_cancel_message(&sent, wire, 0) == 55);
  assert(decode_pending_mass_cancel_message(&got, wire, 0) == 55);
  equal_pending_mass_cancel_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_pending_mass_cancel_message(&got, wire, 0) == 55);
  assert(encode_pending_mass_cancel_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Canceled Message: 78 bytes ----------------------------- */

/* ExecutionReport_CanceledMessage */
typedef struct {
  uint8_t sending_time[8];              /* bytes 0 to 7 */
  uint8_t cl_ord_id[16];                /* bytes 8 to 23 */
  uint8_t orig_cl_ord_id_optional[16];  /* bytes 24 to 39 */
  uint8_t order_id[8];                  /* bytes 40 to 47 */
  uint8_t exec_id[8];                   /* bytes 48 to 55 */
  uint8_t ord_status;                   /* byte 56 */
  uint8_t leaves_qty[4];                /* bytes 57 to 60 */
  uint8_t cum_qty[4];                   /* bytes 61 to 64 */
  uint8_t cancel_reason;                /* byte 65 */
  uint8_t transact_time[8];             /* bytes 66 to 73 */
  uint8_t link_id_optional[4];          /* bytes 74 to 77 */
} ExecutionReportCanceledMessage;

/* any Execution Report Canceled Message at all: every byte one the checker chooses */
static void any_execution_report_canceled_message(ExecutionReportCanceledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->orig_cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = arbitrary(); }
}

/* Execution Report Canceled Message to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_canceled_message(const ExecutionReportCanceledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->orig_cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  wire[at++] = record->cancel_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->link_id_optional[i]; }

  return at;
}

/* Execution Report Canceled Message off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_canceled_message(ExecutionReportCanceledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->orig_cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  record->cancel_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Canceled Message is what was written, byte for byte */
static void equal_execution_report_canceled_message(const ExecutionReportCanceledMessage *read, const ExecutionReportCanceledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->orig_cl_ord_id_optional[i] == written->orig_cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  assert(read->cancel_reason == written->cancel_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->link_id_optional[i] == written->link_id_optional[i]); }
}

/* Execution Report Canceled Message: written and read back, then read and written back */
static void check_execution_report_canceled_message(void) {
  ExecutionReportCanceledMessage sent;
  ExecutionReportCanceledMessage got;
  uint8_t wire[78];
  uint8_t again[78];

  any_execution_report_canceled_message(&sent);
  assert(encode_execution_report_canceled_message(&sent, wire, 0) == 78);
  assert(decode_execution_report_canceled_message(&got, wire, 0) == 78);
  equal_execution_report_canceled_message(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_canceled_message(&got, wire, 0) == 78);
  assert(encode_execution_report_canceled_message(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Done Message: 24 bytes -------------------------------------- */

/* MassCancelDoneMessage */
typedef struct {
  uint8_t sending_time[8];  /* bytes 0 to 7 */
  uint8_t cl_ord_id[16];    /* bytes 8 to 23 */
} MassCancelDoneMessage;

/* any Mass Cancel Done Message at all: every byte one the checker chooses */
static void any_mass_cancel_done_message(MassCancelDoneMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
}

/* Mass Cancel Done Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_done_message(const MassCancelDoneMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }

  return at;
}

/* Mass Cancel Done Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_done_message(MassCancelDoneMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Done Message is what was written, byte for byte */
static void equal_mass_cancel_done_message(const MassCancelDoneMessage *read, const MassCancelDoneMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
}

/* Mass Cancel Done Message: written and read back, then read and written back */
static void check_mass_cancel_done_message(void) {
  MassCancelDoneMessage sent;
  MassCancelDoneMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_mass_cancel_done_message(&sent);
  assert(encode_mass_cancel_done_message(&sent, wire, 0) == 24);
  assert(decode_mass_cancel_done_message(&got, wire, 0) == 24);
  equal_mass_cancel_done_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_done_message(&got, wire, 0) == 24);
  assert(encode_mass_cancel_done_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Pending Replace Message: 104 bytes --------------------- */

/* ExecutionReport_PendingReplaceMessage */
typedef struct {
  uint8_t sending_time[8];              /* bytes 0 to 7 */
  uint8_t order_id[8];                  /* bytes 8 to 15 */
  uint8_t cl_ord_id[16];                /* bytes 16 to 31 */
  uint8_t orig_cl_ord_id_optional[16];  /* bytes 32 to 47 */
  uint8_t exec_id[8];                   /* bytes 48 to 55 */
  uint8_t symbol[6];                    /* bytes 56 to 61 */
  uint8_t symbol_sfx[6];                /* bytes 62 to 67 */
  uint8_t side;                         /* byte 68 */
  uint8_t order_qty[4];                 /* bytes 69 to 72 */
  uint8_t ord_type;                     /* byte 73 */
  uint8_t price[8];                     /* bytes 74 to 81 */
  uint8_t display_qty[4];               /* bytes 82 to 85 */
  uint8_t locate_reqd;                  /* byte 86 */
  uint8_t ord_status;                   /* byte 87 */
  uint8_t leaves_qty[4];                /* bytes 88 to 91 */
  uint8_t cum_qty[4];                   /* bytes 92 to 95 */
  uint8_t link_id_optional[4];          /* bytes 96 to 99 */
  uint8_t locate_broker_optional[4];    /* bytes 100 to 103 */
} ExecutionReportPendingReplaceMessage;

/* any Execution Report Pending Replace Message at all: every byte one the checker chooses */
static void any_execution_report_pending_replace_message(ExecutionReportPendingReplaceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->orig_cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  record->locate_reqd = arbitrary();
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->locate_broker_optional[i] = arbitrary(); }
}

/* Execution Report Pending Replace Message to the wire: 104 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_pending_replace_message(const ExecutionReportPendingReplaceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->orig_cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_sfx[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  wire[at++] = record->locate_reqd;
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->link_id_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->locate_broker_optional[i]; }

  return at;
}

/* Execution Report Pending Replace Message off the wire: 104 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_pending_replace_message(ExecutionReportPendingReplaceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->orig_cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  record->locate_reqd = wire[at++];
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->locate_broker_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Pending Replace Message is what was written, byte for byte */
static void equal_execution_report_pending_replace_message(const ExecutionReportPendingReplaceMessage *read, const ExecutionReportPendingReplaceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->orig_cl_ord_id_optional[i] == written->orig_cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_sfx[i] == written->symbol_sfx[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  assert(read->locate_reqd == written->locate_reqd);
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->link_id_optional[i] == written->link_id_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->locate_broker_optional[i] == written->locate_broker_optional[i]); }
}

/* Execution Report Pending Replace Message: written and read back, then read and written back */
static void check_execution_report_pending_replace_message(void) {
  ExecutionReportPendingReplaceMessage sent;
  ExecutionReportPendingReplaceMessage got;
  uint8_t wire[104];
  uint8_t again[104];

  any_execution_report_pending_replace_message(&sent);
  assert(encode_execution_report_pending_replace_message(&sent, wire, 0) == 104);
  assert(decode_execution_report_pending_replace_message(&got, wire, 0) == 104);
  equal_execution_report_pending_replace_message(&got, &sent);

  for (size_t i = 0; i < 104; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_pending_replace_message(&got, wire, 0) == 104);
  assert(encode_execution_report_pending_replace_message(&got, again, 0) == 104);
  for (size_t i = 0; i < 104; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Replaced Message: 112 bytes ---------------------------- */

/* ExecutionReport_ReplacedMessage */
typedef struct {
  uint8_t sending_time[8];              /* bytes 0 to 7 */
  uint8_t order_id[8];                  /* bytes 8 to 15 */
  uint8_t cl_ord_id[16];                /* bytes 16 to 31 */
  uint8_t orig_cl_ord_id_optional[16];  /* bytes 32 to 47 */
  uint8_t exec_id[8];                   /* bytes 48 to 55 */
  uint8_t symbol[6];                    /* bytes 56 to 61 */
  uint8_t symbol_sfx[6];                /* bytes 62 to 67 */
  uint8_t side;                         /* byte 68 */
  uint8_t order_qty[4];                 /* bytes 69 to 72 */
  uint8_t ord_type;                     /* byte 73 */
  uint8_t price[8];                     /* bytes 74 to 81 */
  uint8_t display_qty[4];               /* bytes 82 to 85 */
  uint8_t locate_reqd;                  /* byte 86 */
  uint8_t ord_status;                   /* byte 87 */
  uint8_t leaves_qty[4];                /* bytes 88 to 91 */
  uint8_t cum_qty[4];                   /* bytes 92 to 95 */
  uint8_t transact_time[8];             /* bytes 96 to 103 */
  uint8_t link_id_optional[4];          /* bytes 104 to 107 */
  uint8_t locate_broker_optional[4];    /* bytes 108 to 111 */
} ExecutionReportReplacedMessage;

/* any Execution Report Replaced Message at all: every byte one the checker chooses */
static void any_execution_report_replaced_message(ExecutionReportReplacedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->orig_cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  record->locate_reqd = arbitrary();
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->locate_broker_optional[i] = arbitrary(); }
}

/* Execution Report Replaced Message to the wire: 112 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_replaced_message(const ExecutionReportReplacedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->orig_cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_sfx[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  wire[at++] = record->locate_reqd;
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->link_id_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->locate_broker_optional[i]; }

  return at;
}

/* Execution Report Replaced Message off the wire: 112 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_replaced_message(ExecutionReportReplacedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->orig_cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  record->locate_reqd = wire[at++];
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->locate_broker_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Replaced Message is what was written, byte for byte */
static void equal_execution_report_replaced_message(const ExecutionReportReplacedMessage *read, const ExecutionReportReplacedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->orig_cl_ord_id_optional[i] == written->orig_cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_sfx[i] == written->symbol_sfx[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  assert(read->locate_reqd == written->locate_reqd);
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->link_id_optional[i] == written->link_id_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->locate_broker_optional[i] == written->locate_broker_optional[i]); }
}

/* Execution Report Replaced Message: written and read back, then read and written back */
static void check_execution_report_replaced_message(void) {
  ExecutionReportReplacedMessage sent;
  ExecutionReportReplacedMessage got;
  uint8_t wire[112];
  uint8_t again[112];

  any_execution_report_replaced_message(&sent);
  assert(encode_execution_report_replaced_message(&sent, wire, 0) == 112);
  assert(decode_execution_report_replaced_message(&got, wire, 0) == 112);
  equal_execution_report_replaced_message(&got, &sent);

  for (size_t i = 0; i < 112; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_replaced_message(&got, wire, 0) == 112);
  assert(encode_execution_report_replaced_message(&got, again, 0) == 112);
  for (size_t i = 0; i < 112; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Trade Correction Message: 82 bytes --------------------- */

/* ExecutionReport_TradeCorrectionMessage */
typedef struct {
  uint8_t sending_time[8];       /* bytes 0 to 7 */
  uint8_t order_id[8];           /* bytes 8 to 15 */
  uint8_t cl_ord_id[16];         /* bytes 16 to 31 */
  uint8_t exec_id[8];            /* bytes 32 to 39 */
  uint8_t exec_ref_id[8];        /* bytes 40 to 47 */
  uint8_t trd_match_id[8];       /* bytes 48 to 55 */
  uint8_t ord_status;            /* byte 56 */
  uint8_t last_px[8];            /* bytes 57 to 64 */
  uint8_t last_qty_optional[4];  /* bytes 65 to 68 */
  uint8_t leaves_qty[4];         /* bytes 69 to 72 */
  uint8_t cum_qty[4];            /* bytes 73 to 76 */
  uint8_t link_id_optional[4];   /* bytes 77 to 80 */
  uint8_t security_group;        /* byte 81 */
} ExecutionReportTradeCorrectionMessage;

/* any Execution Report Trade Correction Message at all: every byte one the checker chooses */
static void any_execution_report_trade_correction_message(ExecutionReportTradeCorrectionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trd_match_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = arbitrary(); }
  record->security_group = arbitrary();
}

/* Execution Report Trade Correction Message to the wire: 82 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_trade_correction_message(const ExecutionReportTradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_ref_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_match_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->link_id_optional[i]; }
  wire[at++] = record->security_group;

  return at;
}

/* Execution Report Trade Correction Message off the wire: 82 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_trade_correction_message(ExecutionReportTradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trd_match_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = wire[at++]; }
  record->security_group = wire[at++];

  return at;
}

/* what was read of Execution Report Trade Correction Message is what was written, byte for byte */
static void equal_execution_report_trade_correction_message(const ExecutionReportTradeCorrectionMessage *read, const ExecutionReportTradeCorrectionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_ref_id[i] == written->exec_ref_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trd_match_id[i] == written->trd_match_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty_optional[i] == written->last_qty_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->link_id_optional[i] == written->link_id_optional[i]); }
  assert(read->security_group == written->security_group);
}

/* Execution Report Trade Correction Message: written and read back, then read and written back */
static void check_execution_report_trade_correction_message(void) {
  ExecutionReportTradeCorrectionMessage sent;
  ExecutionReportTradeCorrectionMessage got;
  uint8_t wire[82];
  uint8_t again[82];

  any_execution_report_trade_correction_message(&sent);
  assert(encode_execution_report_trade_correction_message(&sent, wire, 0) == 82);
  assert(decode_execution_report_trade_correction_message(&got, wire, 0) == 82);
  equal_execution_report_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 82; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_trade_correction_message(&got, wire, 0) == 82);
  assert(encode_execution_report_trade_correction_message(&got, again, 0) == 82);
  for (size_t i = 0; i < 82; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Trade Break Message: 70 bytes -------------------------- */

/* ExecutionReport_TradeBreakMessage */
typedef struct {
  uint8_t sending_time[8];      /* bytes 0 to 7 */
  uint8_t order_id[8];          /* bytes 8 to 15 */
  uint8_t cl_ord_id[16];        /* bytes 16 to 31 */
  uint8_t exec_id[8];           /* bytes 32 to 39 */
  uint8_t exec_ref_id[8];       /* bytes 40 to 47 */
  uint8_t trd_match_id[8];      /* bytes 48 to 55 */
  uint8_t ord_status;           /* byte 56 */
  uint8_t leaves_qty[4];        /* bytes 57 to 60 */
  uint8_t cum_qty[4];           /* bytes 61 to 64 */
  uint8_t link_id_optional[4];  /* bytes 65 to 68 */
  uint8_t security_group;       /* byte 69 */
} ExecutionReportTradeBreakMessage;

/* any Execution Report Trade Break Message at all: every byte one the checker chooses */
static void any_execution_report_trade_break_message(ExecutionReportTradeBreakMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trd_match_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = arbitrary(); }
  record->security_group = arbitrary();
}

/* Execution Report Trade Break Message to the wire: 70 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_trade_break_message(const ExecutionReportTradeBreakMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_ref_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_match_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->link_id_optional[i]; }
  wire[at++] = record->security_group;

  return at;
}

/* Execution Report Trade Break Message off the wire: 70 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_trade_break_message(ExecutionReportTradeBreakMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trd_match_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = wire[at++]; }
  record->security_group = wire[at++];

  return at;
}

/* what was read of Execution Report Trade Break Message is what was written, byte for byte */
static void equal_execution_report_trade_break_message(const ExecutionReportTradeBreakMessage *read, const ExecutionReportTradeBreakMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_ref_id[i] == written->exec_ref_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trd_match_id[i] == written->trd_match_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->link_id_optional[i] == written->link_id_optional[i]); }
  assert(read->security_group == written->security_group);
}

/* Execution Report Trade Break Message: written and read back, then read and written back */
static void check_execution_report_trade_break_message(void) {
  ExecutionReportTradeBreakMessage sent;
  ExecutionReportTradeBreakMessage got;
  uint8_t wire[70];
  uint8_t again[70];

  any_execution_report_trade_break_message(&sent);
  assert(encode_execution_report_trade_break_message(&sent, wire, 0) == 70);
  assert(decode_execution_report_trade_break_message(&got, wire, 0) == 70);
  equal_execution_report_trade_break_message(&got, &sent);

  for (size_t i = 0; i < 70; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_trade_break_message(&got, wire, 0) == 70);
  assert(encode_execution_report_trade_break_message(&got, again, 0) == 70);
  for (size_t i = 0; i < 70; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Restatement Message: 75 bytes -------------------------- */

/* ExecutionReport_RestatementMessage */
typedef struct {
  uint8_t sending_time[8];              /* bytes 0 to 7 */
  uint8_t order_id[8];                  /* bytes 8 to 15 */
  uint8_t cl_ord_id[16];                /* bytes 16 to 31 */
  uint8_t exec_id[8];                   /* bytes 32 to 39 */
  uint8_t ord_status;                   /* byte 40 */
  uint8_t last_px_optional[8];          /* bytes 41 to 48 */
  uint8_t leaves_qty[4];                /* bytes 49 to 52 */
  uint8_t cum_qty[4];                   /* bytes 53 to 56 */
  uint8_t last_shares[4];               /* bytes 57 to 60 */
  uint8_t exec_restatement_reason;      /* byte 61 */
  uint8_t transact_time[8];             /* bytes 62 to 69 */
  uint8_t extended_restatement_reason;  /* byte 70 */
  uint8_t link_id_optional[4];          /* bytes 71 to 74 */
} ExecutionReportRestatementMessage;

/* any Execution Report Restatement Message at all: every byte one the checker chooses */
static void any_execution_report_restatement_message(ExecutionReportRestatementMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  record->exec_restatement_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  record->extended_restatement_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = arbitrary(); }
}

/* Execution Report Restatement Message to the wire: 75 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_restatement_message(const ExecutionReportRestatementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  wire[at++] = record->exec_restatement_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  wire[at++] = record->extended_restatement_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->link_id_optional[i]; }

  return at;
}

/* Execution Report Restatement Message off the wire: 75 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_restatement_message(ExecutionReportRestatementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  record->exec_restatement_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  record->extended_restatement_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Restatement Message is what was written, byte for byte */
static void equal_execution_report_restatement_message(const ExecutionReportRestatementMessage *read, const ExecutionReportRestatementMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px_optional[i] == written->last_px_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  assert(read->exec_restatement_reason == written->exec_restatement_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  assert(read->extended_restatement_reason == written->extended_restatement_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->link_id_optional[i] == written->link_id_optional[i]); }
}

/* Execution Report Restatement Message: written and read back, then read and written back */
static void check_execution_report_restatement_message(void) {
  ExecutionReportRestatementMessage sent;
  ExecutionReportRestatementMessage got;
  uint8_t wire[75];
  uint8_t again[75];

  any_execution_report_restatement_message(&sent);
  assert(encode_execution_report_restatement_message(&sent, wire, 0) == 75);
  assert(decode_execution_report_restatement_message(&got, wire, 0) == 75);
  equal_execution_report_restatement_message(&got, &sent);

  for (size_t i = 0; i < 75; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_restatement_message(&got, wire, 0) == 75);
  assert(encode_execution_report_restatement_message(&got, again, 0) == 75);
  for (size_t i = 0; i < 75; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Reject Message: 30 bytes ----------------------------------- */

/* OrderCancelRejectMessage */
typedef struct {
  uint8_t sending_time[8];      /* bytes 0 to 7 */
  uint8_t cl_ord_id[16];        /* bytes 8 to 23 */
  uint8_t cxl_rej_response_to;  /* byte 24 */
  uint8_t cxl_rej_reason;       /* byte 25 */
  uint8_t link_id_optional[4];  /* bytes 26 to 29 */
} OrderCancelRejectMessage;

/* any Order Cancel Reject Message at all: every byte one the checker chooses */
static void any_order_cancel_reject_message(OrderCancelRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->cxl_rej_response_to = arbitrary();
  record->cxl_rej_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = arbitrary(); }
}

/* Order Cancel Reject Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_reject_message(const OrderCancelRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->cxl_rej_response_to;
  wire[at++] = record->cxl_rej_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->link_id_optional[i]; }

  return at;
}

/* Order Cancel Reject Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_reject_message(OrderCancelRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->cxl_rej_response_to = wire[at++];
  record->cxl_rej_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->link_id_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Reject Message is what was written, byte for byte */
static void equal_order_cancel_reject_message(const OrderCancelRejectMessage *read, const OrderCancelRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->cxl_rej_response_to == written->cxl_rej_response_to);
  assert(read->cxl_rej_reason == written->cxl_rej_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->link_id_optional[i] == written->link_id_optional[i]); }
}

/* Order Cancel Reject Message: written and read back, then read and written back */
static void check_order_cancel_reject_message(void) {
  OrderCancelRejectMessage sent;
  OrderCancelRejectMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_order_cancel_reject_message(&sent);
  assert(encode_order_cancel_reject_message(&sent, wire, 0) == 30);
  assert(decode_order_cancel_reject_message(&got, wire, 0) == 30);
  equal_order_cancel_reject_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_reject_message(&got, wire, 0) == 30);
  assert(encode_order_cancel_reject_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Reject Message: 56 bytes ------------------------------------ */

/* MassCancelRejectMessage */
typedef struct {
  uint8_t sending_time[8];            /* bytes 0 to 7 */
  uint8_t cl_ord_id[16];              /* bytes 8 to 23 */
  uint8_t symbol[6];                  /* bytes 24 to 29 */
  uint8_t symbol_sfx[6];              /* bytes 30 to 35 */
  uint8_t side_optional;              /* byte 36 */
  uint8_t lower_than_price[8];        /* bytes 37 to 44 */
  uint8_t higher_than_price[8];       /* bytes 45 to 52 */
  uint8_t cancel_group_id[2];         /* bytes 53 to 54 */
  uint8_t mass_cancel_reject_reason;  /* byte 55 */
} MassCancelRejectMessage;

/* any Mass Cancel Reject Message at all: every byte one the checker chooses */
static void any_mass_cancel_reject_message(MassCancelRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = arbitrary(); }
  record->side_optional = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->lower_than_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->higher_than_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->cancel_group_id[i] = arbitrary(); }
  record->mass_cancel_reject_reason = arbitrary();
}

/* Mass Cancel Reject Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_reject_message(const MassCancelRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_sfx[i]; }
  wire[at++] = record->side_optional;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_than_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->higher_than_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->cancel_group_id[i]; }
  wire[at++] = record->mass_cancel_reject_reason;

  return at;
}

/* Mass Cancel Reject Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_reject_message(MassCancelRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_sfx[i] = wire[at++]; }
  record->side_optional = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->lower_than_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->higher_than_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->cancel_group_id[i] = wire[at++]; }
  record->mass_cancel_reject_reason = wire[at++];

  return at;
}

/* what was read of Mass Cancel Reject Message is what was written, byte for byte */
static void equal_mass_cancel_reject_message(const MassCancelRejectMessage *read, const MassCancelRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_sfx[i] == written->symbol_sfx[i]); }
  assert(read->side_optional == written->side_optional);
  for (size_t i = 0; i < 8; i++) { assert(read->lower_than_price[i] == written->lower_than_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->higher_than_price[i] == written->higher_than_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->cancel_group_id[i] == written->cancel_group_id[i]); }
  assert(read->mass_cancel_reject_reason == written->mass_cancel_reject_reason);
}

/* Mass Cancel Reject Message: written and read back, then read and written back */
static void check_mass_cancel_reject_message(void) {
  MassCancelRejectMessage sent;
  MassCancelRejectMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_mass_cancel_reject_message(&sent);
  assert(encode_mass_cancel_reject_message(&sent, wire, 0) == 56);
  assert(decode_mass_cancel_reject_message(&got, wire, 0) == 56);
  equal_mass_cancel_reject_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_reject_message(&got, wire, 0) == 56);
  assert(encode_mass_cancel_reject_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
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
  check_execution_report_rejected_message();
  check_execution_report_trade_message();
  check_execution_report_pending_cancel_message();
  check_pending_mass_cancel_message();
  check_execution_report_canceled_message();
  check_mass_cancel_done_message();
  check_execution_report_pending_replace_message();
  check_execution_report_replaced_message();
  check_execution_report_trade_correction_message();
  check_execution_report_trade_break_message();
  check_execution_report_restatement_message();
  check_order_cancel_reject_message();
  check_mass_cancel_reject_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
