// iex/iexoptions/session/IexOptions_Session_v1_01_Server.c
/*
 * Investors Exchange Session
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

/* ---- Message Header: 8 bytes ------------------------------------------------- */

/* Iex Options Sbe message header — message identifiers and length of message root */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id[2];   /* bytes 2 to 3 */
  uint8_t schema_id[2];     /* bytes 4 to 5 */
  uint8_t version[2];       /* bytes 6 to 7 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Message Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->schema_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Message Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->schema_id[i] == written->schema_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 8);
  assert(decode_message_header(&got, wire, 0) == 8);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 8);
  assert(encode_message_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response Message: 17 bytes ---------------------------------------- */

/* LoginResponseMessage */
typedef struct {
  uint8_t logon_id[16];  /* bytes 0 to 15 */
  uint8_t status;        /* byte 16 */
} LoginResponseMessage;

/* any Login Response Message at all: every byte one the checker chooses */
static void any_login_response_message(LoginResponseMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->logon_id[i] = arbitrary(); }
  record->status = arbitrary();
}

/* Login Response Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_login_response_message(const LoginResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->logon_id[i]; }
  wire[at++] = record->status;

  return at;
}

/* Login Response Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_login_response_message(LoginResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->logon_id[i] = wire[at++]; }
  record->status = wire[at++];

  return at;
}

/* what was read of Login Response Message is what was written, byte for byte */
static void equal_login_response_message(const LoginResponseMessage *read, const LoginResponseMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->logon_id[i] == written->logon_id[i]); }
  assert(read->status == written->status);
}

/* Login Response Message: written and read back, then read and written back */
static void check_login_response_message(void) {
  LoginResponseMessage sent;
  LoginResponseMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_login_response_message(&sent);
  assert(encode_login_response_message(&sent, wire, 0) == 17);
  assert(decode_login_response_message(&got, wire, 0) == 17);
  equal_login_response_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response_message(&got, wire, 0) == 17);
  assert(encode_login_response_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Session Info Group Encoding: 2 bytes ------------------------------------ */

/* sessionInfoGroupEncoding */
typedef struct {
  uint8_t block_length_short;  /* byte 0 */
  uint8_t num_in_group;        /* byte 1 */
} SessionInfoGroupEncoding;

/* any Session Info Group Encoding at all: every byte one the checker chooses */
static void any_session_info_group_encoding(SessionInfoGroupEncoding *record) {
  record->block_length_short = arbitrary();
  record->num_in_group = arbitrary();
}

/* Session Info Group Encoding to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_session_info_group_encoding(const SessionInfoGroupEncoding *record, uint8_t *wire, size_t at) {
  wire[at++] = record->block_length_short;
  wire[at++] = record->num_in_group;

  return at;
}

/* Session Info Group Encoding off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_session_info_group_encoding(SessionInfoGroupEncoding *record, const uint8_t *wire, size_t at) {
  record->block_length_short = wire[at++];
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Session Info Group Encoding is what was written, byte for byte */
static void equal_session_info_group_encoding(const SessionInfoGroupEncoding *read, const SessionInfoGroupEncoding *written) {
  assert(read->block_length_short == written->block_length_short);
  assert(read->num_in_group == written->num_in_group);
}

/* Session Info Group Encoding: written and read back, then read and written back */
static void check_session_info_group_encoding(void) {
  SessionInfoGroupEncoding sent;
  SessionInfoGroupEncoding got;
  uint8_t wire[2];
  uint8_t again[2];

  any_session_info_group_encoding(&sent);
  assert(encode_session_info_group_encoding(&sent, wire, 0) == 2);
  assert(decode_session_info_group_encoding(&got, wire, 0) == 2);
  equal_session_info_group_encoding(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_session_info_group_encoding(&got, wire, 0) == 2);
  assert(encode_session_info_group_encoding(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Terminate Message: 1 byte ----------------------------------------------- */

/* TerminateMessage */
typedef struct {
  uint8_t reason;  /* byte 0 */
} TerminateMessage;

/* any Terminate Message at all: every byte one the checker chooses */
static void any_terminate_message(TerminateMessage *record) {
  record->reason = arbitrary();
}

/* Terminate Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_terminate_message(const TerminateMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reason;

  return at;
}

/* Terminate Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_terminate_message(TerminateMessage *record, const uint8_t *wire, size_t at) {
  record->reason = wire[at++];

  return at;
}

/* what was read of Terminate Message is what was written, byte for byte */
static void equal_terminate_message(const TerminateMessage *read, const TerminateMessage *written) {
  assert(read->reason == written->reason);
}

/* Terminate Message: written and read back, then read and written back */
static void check_terminate_message(void) {
  TerminateMessage sent;
  TerminateMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_terminate_message(&sent);
  assert(encode_terminate_message(&sent, wire, 0) == 1);
  assert(decode_terminate_message(&got, wire, 0) == 1);
  equal_terminate_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_terminate_message(&got, wire, 0) == 1);
  assert(encode_terminate_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequenced Message Header Message: 20 bytes ------------------------------ */

/* SequencedMessageHeaderMessage */
typedef struct {
  uint8_t subsession_id[8];  /* bytes 0 to 7 */
  uint8_t sequence[4];       /* bytes 8 to 11 */
  uint8_t timestamp[8];      /* bytes 12 to 19 */
} SequencedMessageHeaderMessage;

/* any Sequenced Message Header Message at all: every byte one the checker chooses */
static void any_sequenced_message_header_message(SequencedMessageHeaderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* Sequenced Message Header Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_sequenced_message_header_message(const SequencedMessageHeaderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->subsession_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* Sequenced Message Header Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_sequenced_message_header_message(SequencedMessageHeaderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Sequenced Message Header Message is what was written, byte for byte */
static void equal_sequenced_message_header_message(const SequencedMessageHeaderMessage *read, const SequencedMessageHeaderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->subsession_id[i] == written->subsession_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
}

/* Sequenced Message Header Message: written and read back, then read and written back */
static void check_sequenced_message_header_message(void) {
  SequencedMessageHeaderMessage sent;
  SequencedMessageHeaderMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_sequenced_message_header_message(&sent);
  assert(encode_sequenced_message_header_message(&sent, wire, 0) == 20);
  assert(decode_sequenced_message_header_message(&got, wire, 0) == 20);
  equal_sequenced_message_header_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_sequenced_message_header_message(&got, wire, 0) == 20);
  assert(encode_sequenced_message_header_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Subsession Join Response Message: 9 bytes ------------------------------- */

/* SubsessionJoinResponseMessage */
typedef struct {
  uint8_t subsession_id[8];  /* bytes 0 to 7 */
  uint8_t status;            /* byte 8 */
} SubsessionJoinResponseMessage;

/* any Subsession Join Response Message at all: every byte one the checker chooses */
static void any_subsession_join_response_message(SubsessionJoinResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = arbitrary(); }
  record->status = arbitrary();
}

/* Subsession Join Response Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_subsession_join_response_message(const SubsessionJoinResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->subsession_id[i]; }
  wire[at++] = record->status;

  return at;
}

/* Subsession Join Response Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_subsession_join_response_message(SubsessionJoinResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = wire[at++]; }
  record->status = wire[at++];

  return at;
}

/* what was read of Subsession Join Response Message is what was written, byte for byte */
static void equal_subsession_join_response_message(const SubsessionJoinResponseMessage *read, const SubsessionJoinResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->subsession_id[i] == written->subsession_id[i]); }
  assert(read->status == written->status);
}

/* Subsession Join Response Message: written and read back, then read and written back */
static void check_subsession_join_response_message(void) {
  SubsessionJoinResponseMessage sent;
  SubsessionJoinResponseMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_subsession_join_response_message(&sent);
  assert(encode_subsession_join_response_message(&sent, wire, 0) == 9);
  assert(decode_subsession_join_response_message(&got, wire, 0) == 9);
  equal_subsession_join_response_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_subsession_join_response_message(&got, wire, 0) == 9);
  assert(encode_subsession_join_response_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Subsession Leave Response Message: 9 bytes ------------------------------ */

/* SubsessionLeaveResponseMessage */
typedef struct {
  uint8_t subsession_id[8];  /* bytes 0 to 7 */
  uint8_t reason;            /* byte 8 */
} SubsessionLeaveResponseMessage;

/* any Subsession Leave Response Message at all: every byte one the checker chooses */
static void any_subsession_leave_response_message(SubsessionLeaveResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = arbitrary(); }
  record->reason = arbitrary();
}

/* Subsession Leave Response Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_subsession_leave_response_message(const SubsessionLeaveResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->subsession_id[i]; }
  wire[at++] = record->reason;

  return at;
}

/* Subsession Leave Response Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_subsession_leave_response_message(SubsessionLeaveResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = wire[at++]; }
  record->reason = wire[at++];

  return at;
}

/* what was read of Subsession Leave Response Message is what was written, byte for byte */
static void equal_subsession_leave_response_message(const SubsessionLeaveResponseMessage *read, const SubsessionLeaveResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->subsession_id[i] == written->subsession_id[i]); }
  assert(read->reason == written->reason);
}

/* Subsession Leave Response Message: written and read back, then read and written back */
static void check_subsession_leave_response_message(void) {
  SubsessionLeaveResponseMessage sent;
  SubsessionLeaveResponseMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_subsession_leave_response_message(&sent);
  assert(encode_subsession_leave_response_message(&sent, wire, 0) == 9);
  assert(decode_subsession_leave_response_message(&got, wire, 0) == 9);
  equal_subsession_leave_response_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_subsession_leave_response_message(&got, wire, 0) == 9);
  assert(encode_subsession_leave_response_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_login_response_message();
  check_session_info_group_encoding();
  check_terminate_message();
  check_sequenced_message_header_message();
  check_subsession_join_response_message();
  check_subsession_leave_response_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
