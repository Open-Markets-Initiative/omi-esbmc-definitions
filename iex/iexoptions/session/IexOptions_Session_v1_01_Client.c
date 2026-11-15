// iex/iexoptions/session/IexOptions_Session_v1_01_Client.c
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

/* ---- Login Request Message: 48 bytes ----------------------------------------- */

/* LoginRequestMessage */
typedef struct {
  uint8_t logon_id[16];  /* bytes 0 to 15 */
  uint8_t token[32];     /* bytes 16 to 47 */
} LoginRequestMessage;

/* any Login Request Message at all: every byte one the checker chooses */
static void any_login_request_message(LoginRequestMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->logon_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->token[i] = arbitrary(); }
}

/* Login Request Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_login_request_message(const LoginRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->logon_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->token[i]; }

  return at;
}

/* Login Request Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_login_request_message(LoginRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->logon_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->token[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request Message is what was written, byte for byte */
static void equal_login_request_message(const LoginRequestMessage *read, const LoginRequestMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->logon_id[i] == written->logon_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->token[i] == written->token[i]); }
}

/* Login Request Message: written and read back, then read and written back */
static void check_login_request_message(void) {
  LoginRequestMessage sent;
  LoginRequestMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_login_request_message(&sent);
  assert(encode_login_request_message(&sent, wire, 0) == 48);
  assert(decode_login_request_message(&got, wire, 0) == 48);
  equal_login_request_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_message(&got, wire, 0) == 48);
  assert(encode_login_request_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
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

/* ---- Subsession Join Message: 16 bytes --------------------------------------- */

/* SubsessionJoinMessage */
typedef struct {
  uint8_t subsession_id[8];   /* bytes 0 to 7 */
  uint8_t start_sequence[4];  /* bytes 8 to 11 */
  uint8_t end_sequence[4];    /* bytes 12 to 15 */
} SubsessionJoinMessage;

/* any Subsession Join Message at all: every byte one the checker chooses */
static void any_subsession_join_message(SubsessionJoinMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->start_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_sequence[i] = arbitrary(); }
}

/* Subsession Join Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_subsession_join_message(const SubsessionJoinMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->subsession_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->start_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_sequence[i]; }

  return at;
}

/* Subsession Join Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_subsession_join_message(SubsessionJoinMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->start_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Subsession Join Message is what was written, byte for byte */
static void equal_subsession_join_message(const SubsessionJoinMessage *read, const SubsessionJoinMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->subsession_id[i] == written->subsession_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->start_sequence[i] == written->start_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_sequence[i] == written->end_sequence[i]); }
}

/* Subsession Join Message: written and read back, then read and written back */
static void check_subsession_join_message(void) {
  SubsessionJoinMessage sent;
  SubsessionJoinMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_subsession_join_message(&sent);
  assert(encode_subsession_join_message(&sent, wire, 0) == 16);
  assert(decode_subsession_join_message(&got, wire, 0) == 16);
  equal_subsession_join_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_subsession_join_message(&got, wire, 0) == 16);
  assert(encode_subsession_join_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Subsession Leave Message: 8 bytes --------------------------------------- */

/* SubsessionLeaveMessage */
typedef struct {
  uint8_t subsession_id[8];  /* bytes 0 to 7 */
} SubsessionLeaveMessage;

/* any Subsession Leave Message at all: every byte one the checker chooses */
static void any_subsession_leave_message(SubsessionLeaveMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = arbitrary(); }
}

/* Subsession Leave Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_subsession_leave_message(const SubsessionLeaveMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->subsession_id[i]; }

  return at;
}

/* Subsession Leave Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_subsession_leave_message(SubsessionLeaveMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = wire[at++]; }

  return at;
}

/* what was read of Subsession Leave Message is what was written, byte for byte */
static void equal_subsession_leave_message(const SubsessionLeaveMessage *read, const SubsessionLeaveMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->subsession_id[i] == written->subsession_id[i]); }
}

/* Subsession Leave Message: written and read back, then read and written back */
static void check_subsession_leave_message(void) {
  SubsessionLeaveMessage sent;
  SubsessionLeaveMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_subsession_leave_message(&sent);
  assert(encode_subsession_leave_message(&sent, wire, 0) == 8);
  assert(decode_subsession_leave_message(&got, wire, 0) == 8);
  equal_subsession_leave_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_subsession_leave_message(&got, wire, 0) == 8);
  assert(encode_subsession_leave_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_login_request_message();
  check_sequenced_message_header_message();
  check_subsession_join_message();
  check_subsession_leave_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
