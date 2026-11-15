// lseg/turquoise/replay/Turquoise_Replay_v26_3.c
/*
 * London Stock Exchange Replay
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
 *   - a run counted by a field
 *   - a field read in bits
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

/* ---- Unit Header: 8 bytes ---------------------------------------------------- */

/* Gtp Tcp Unit Header */
typedef struct {
  uint8_t length[2];           /* bytes 0 to 1 */
  uint8_t message_count;       /* byte 2 */
  uint8_t market_data_group;   /* byte 3 */
  uint8_t sequence_number[4];  /* bytes 4 to 7 */
} UnitHeader;

/* any Unit Header at all: every byte one the checker chooses */
static void any_unit_header(UnitHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->message_count = arbitrary();
  record->market_data_group = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Unit Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_unit_header(const UnitHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->message_count;
  wire[at++] = record->market_data_group;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Unit Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_unit_header(UnitHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->message_count = wire[at++];
  record->market_data_group = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Unit Header is what was written, byte for byte */
static void equal_unit_header(const UnitHeader *read, const UnitHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->message_count == written->message_count);
  assert(read->market_data_group == written->market_data_group);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Unit Header: written and read back, then read and written back */
static void check_unit_header(void) {
  UnitHeader sent;
  UnitHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_unit_header(&sent);
  assert(encode_unit_header(&sent, wire, 0) == 8);
  assert(decode_unit_header(&got, wire, 0) == 8);
  equal_unit_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_unit_header(&got, wire, 0) == 8);
  assert(encode_unit_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* Gtp Tcp Message Header */
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

/* ---- Login Request Message: 8 bytes ------------------------------------------ */

/* Used by the client to log in to the replay or recovery channel. */
typedef struct {
  uint8_t username[8];  /* bytes 0 to 7 */
} LoginRequestMessage;

/* any Login Request Message at all: every byte one the checker chooses */
static void any_login_request_message(LoginRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->username[i] = arbitrary(); }
}

/* Login Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_login_request_message(const LoginRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->username[i]; }

  return at;
}

/* Login Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_login_request_message(LoginRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->username[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request Message is what was written, byte for byte */
static void equal_login_request_message(const LoginRequestMessage *read, const LoginRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->username[i] == written->username[i]); }
}

/* Login Request Message: written and read back, then read and written back */
static void check_login_request_message(void) {
  LoginRequestMessage sent;
  LoginRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_login_request_message(&sent);
  assert(encode_login_request_message(&sent, wire, 0) == 8);
  assert(decode_login_request_message(&got, wire, 0) == 8);
  equal_login_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_message(&got, wire, 0) == 8);
  assert(encode_login_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay Request Message: 12 bytes ---------------------------------------- */

/* Used by the client to request a retransmission of messages on the replay channel. */
typedef struct {
  uint8_t first_message[4];  /* bytes 0 to 3 */
  uint8_t count[4];          /* bytes 4 to 7 */
  uint8_t request_id[4];     /* bytes 8 to 11 */
} ReplayRequestMessage;

/* any Replay Request Message at all: every byte one the checker chooses */
static void any_replay_request_message(ReplayRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->first_message[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
}

/* Replay Request Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_replay_request_message(const ReplayRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_message[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }

  return at;
}

/* Replay Request Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_replay_request_message(ReplayRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->first_message[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }

  return at;
}

/* what was read of Replay Request Message is what was written, byte for byte */
static void equal_replay_request_message(const ReplayRequestMessage *read, const ReplayRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->first_message[i] == written->first_message[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count[i] == written->count[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
}

/* Replay Request Message: written and read back, then read and written back */
static void check_replay_request_message(void) {
  ReplayRequestMessage sent;
  ReplayRequestMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_replay_request_message(&sent);
  assert(encode_replay_request_message(&sent, wire, 0) == 12);
  assert(decode_replay_request_message(&got, wire, 0) == 12);
  equal_replay_request_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_request_message(&got, wire, 0) == 12);
  assert(encode_replay_request_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response Message: 1 byte ------------------------------------------ */

/* Used by the server to accept or reject a login request to the replay or recovery channel. */
typedef struct {
  uint8_t login_status;  /* byte 0 */
} LoginResponseMessage;

/* any Login Response Message at all: every byte one the checker chooses */
static void any_login_response_message(LoginResponseMessage *record) {
  record->login_status = arbitrary();
}

/* Login Response Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_login_response_message(const LoginResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->login_status;

  return at;
}

/* Login Response Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_login_response_message(LoginResponseMessage *record, const uint8_t *wire, size_t at) {
  record->login_status = wire[at++];

  return at;
}

/* what was read of Login Response Message is what was written, byte for byte */
static void equal_login_response_message(const LoginResponseMessage *read, const LoginResponseMessage *written) {
  assert(read->login_status == written->login_status);
}

/* Login Response Message: written and read back, then read and written back */
static void check_login_response_message(void) {
  LoginResponseMessage sent;
  LoginResponseMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_login_response_message(&sent);
  assert(encode_login_response_message(&sent, wire, 0) == 1);
  assert(decode_login_response_message(&got, wire, 0) == 1);
  equal_login_response_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response_message(&got, wire, 0) == 1);
  assert(encode_login_response_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay Response Message: 13 bytes --------------------------------------- */

/* Used by the server to respond to a retransmission request on the replay channel. */
typedef struct {
  uint8_t first_message[4];  /* bytes 0 to 3 */
  uint8_t count[4];          /* bytes 4 to 7 */
  uint8_t replay_status;     /* byte 8 */
  uint8_t request_id[4];     /* bytes 9 to 12 */
} ReplayResponseMessage;

/* any Replay Response Message at all: every byte one the checker chooses */
static void any_replay_response_message(ReplayResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->first_message[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count[i] = arbitrary(); }
  record->replay_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
}

/* Replay Response Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_replay_response_message(const ReplayResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_message[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count[i]; }
  wire[at++] = record->replay_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }

  return at;
}

/* Replay Response Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_replay_response_message(ReplayResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->first_message[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count[i] = wire[at++]; }
  record->replay_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }

  return at;
}

/* what was read of Replay Response Message is what was written, byte for byte */
static void equal_replay_response_message(const ReplayResponseMessage *read, const ReplayResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->first_message[i] == written->first_message[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count[i] == written->count[i]); }
  assert(read->replay_status == written->replay_status);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
}

/* Replay Response Message: written and read back, then read and written back */
static void check_replay_response_message(void) {
  ReplayResponseMessage sent;
  ReplayResponseMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_replay_response_message(&sent);
  assert(encode_replay_response_message(&sent, wire, 0) == 13);
  assert(decode_replay_response_message(&got, wire, 0) == 13);
  equal_replay_response_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_response_message(&got, wire, 0) == 13);
  assert(encode_replay_response_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay And Recovery Complete Message: 5 bytes --------------------------- */

/* Used by the server to indicate the successful completion of servicing a message replay or a recovery request. */
typedef struct {
  uint8_t request_id[4];   /* bytes 0 to 3 */
  uint8_t trading_status;  /* byte 4 */
} ReplayAndRecoveryCompleteMessage;

/* any Replay And Recovery Complete Message at all: every byte one the checker chooses */
static void any_replay_and_recovery_complete_message(ReplayAndRecoveryCompleteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  record->trading_status = arbitrary();
}

/* Replay And Recovery Complete Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_replay_and_recovery_complete_message(const ReplayAndRecoveryCompleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  wire[at++] = record->trading_status;

  return at;
}

/* Replay And Recovery Complete Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_replay_and_recovery_complete_message(ReplayAndRecoveryCompleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  record->trading_status = wire[at++];

  return at;
}

/* what was read of Replay And Recovery Complete Message is what was written, byte for byte */
static void equal_replay_and_recovery_complete_message(const ReplayAndRecoveryCompleteMessage *read, const ReplayAndRecoveryCompleteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  assert(read->trading_status == written->trading_status);
}

/* Replay And Recovery Complete Message: written and read back, then read and written back */
static void check_replay_and_recovery_complete_message(void) {
  ReplayAndRecoveryCompleteMessage sent;
  ReplayAndRecoveryCompleteMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_replay_and_recovery_complete_message(&sent);
  assert(encode_replay_and_recovery_complete_message(&sent, wire, 0) == 5);
  assert(decode_replay_and_recovery_complete_message(&got, wire, 0) == 5);
  equal_replay_and_recovery_complete_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_and_recovery_complete_message(&got, wire, 0) == 5);
  assert(encode_replay_and_recovery_complete_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 11 bytes ------------------------------------------ */

/* Sent to indicate the start and end of the day. */
typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t event_code;       /* byte 8 */
  uint8_t source_venue[2];  /* bytes 9 to 10 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
}

/* System Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }

  return at;
}

/* System Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event_code == written->event_code);
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 11);
  assert(decode_system_event_message(&got, wire, 0) == 11);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 11);
  assert(encode_system_event_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Status Message: 27 bytes ------------------------------------- */

/* Used to communicate scheduled and unscheduled session changes */
typedef struct {
  uint8_t timestamp[8];           /* bytes 0 to 7 */
  uint8_t instrument[8];          /* bytes 8 to 15 */
  uint8_t source_venue[2];        /* bytes 16 to 17 */
  uint8_t trading_status;         /* byte 18 */
  uint8_t session_change_reason;  /* byte 19 */
  uint8_t new_end_time[6];        /* bytes 20 to 25 */
  uint8_t order_book_type;        /* byte 26 */
} InstrumentStatusMessage;

/* any Instrument Status Message at all: every byte one the checker chooses */
static void any_instrument_status_message(InstrumentStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->session_change_reason = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->new_end_time[i] = arbitrary(); }
  record->order_book_type = arbitrary();
}

/* Instrument Status Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_instrument_status_message(const InstrumentStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->session_change_reason;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->new_end_time[i]; }
  wire[at++] = record->order_book_type;

  return at;
}

/* Instrument Status Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_instrument_status_message(InstrumentStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->session_change_reason = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->new_end_time[i] = wire[at++]; }
  record->order_book_type = wire[at++];

  return at;
}

/* what was read of Instrument Status Message is what was written, byte for byte */
static void equal_instrument_status_message(const InstrumentStatusMessage *read, const InstrumentStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->session_change_reason == written->session_change_reason);
  for (size_t i = 0; i < 6; i++) { assert(read->new_end_time[i] == written->new_end_time[i]); }
  assert(read->order_book_type == written->order_book_type);
}

/* Instrument Status Message: written and read back, then read and written back */
static void check_instrument_status_message(void) {
  InstrumentStatusMessage sent;
  InstrumentStatusMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_instrument_status_message(&sent);
  assert(encode_instrument_status_message(&sent, wire, 0) == 27);
  assert(decode_instrument_status_message(&got, wire, 0) == 27);
  equal_instrument_status_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_status_message(&got, wire, 0) == 27);
  assert(encode_instrument_status_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Incremental Message: 74 bytes --------------------------------- */

/* Sent to instruct recipients to add a new displayable order to the retrospective order book */
typedef struct {
  uint8_t timestamp[8];         /* bytes 0 to 7 */
  uint8_t order_id[8];          /* bytes 8 to 15 */
  uint8_t side;                 /* byte 16 */
  uint8_t size[8];              /* bytes 17 to 24 */
  uint8_t instrument[8];        /* bytes 25 to 32 */
  uint8_t price_price_8[8];     /* bytes 33 to 40 */
  uint8_t transaction_time[8];  /* bytes 41 to 48 */
  uint8_t source_venue[2];      /* bytes 49 to 50 */
  uint8_t order_book_type;      /* byte 51 */
  uint8_t participant[11];      /* bytes 52 to 62 */
  uint8_t order_type;           /* byte 63 */
  uint8_t rfq_id[10];           /* bytes 64 to 73 */
} AddOrderIncrementalMessage;

/* any Add Order Incremental Message at all: every byte one the checker chooses */
static void any_add_order_incremental_message(AddOrderIncrementalMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_price_8[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  record->order_book_type = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->participant[i] = arbitrary(); }
  record->order_type = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->rfq_id[i] = arbitrary(); }
}

/* Add Order Incremental Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_add_order_incremental_message(const AddOrderIncrementalMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_price_8[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  wire[at++] = record->order_book_type;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->participant[i]; }
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->rfq_id[i]; }

  return at;
}

/* Add Order Incremental Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_add_order_incremental_message(AddOrderIncrementalMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_price_8[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  record->order_book_type = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->participant[i] = wire[at++]; }
  record->order_type = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->rfq_id[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Incremental Message is what was written, byte for byte */
static void equal_add_order_incremental_message(const AddOrderIncrementalMessage *read, const AddOrderIncrementalMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->size[i] == written->size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_price_8[i] == written->price_price_8[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  assert(read->order_book_type == written->order_book_type);
  for (size_t i = 0; i < 11; i++) { assert(read->participant[i] == written->participant[i]); }
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 10; i++) { assert(read->rfq_id[i] == written->rfq_id[i]); }
}

/* Add Order Incremental Message: written and read back, then read and written back */
static void check_add_order_incremental_message(void) {
  AddOrderIncrementalMessage sent;
  AddOrderIncrementalMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_add_order_incremental_message(&sent);
  assert(encode_add_order_incremental_message(&sent, wire, 0) == 74);
  assert(decode_add_order_incremental_message(&got, wire, 0) == 74);
  equal_add_order_incremental_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_incremental_message(&got, wire, 0) == 74);
  assert(encode_add_order_incremental_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Order Message: 52 bytes ------------------------------------------ */

/* Sent to instruct recipients to delete an order from the retrospective order book */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t order_id[8];           /* bytes 8 to 15 */
  uint8_t instrument[8];         /* bytes 16 to 23 */
  uint8_t side;                  /* byte 24 */
  uint8_t order_book_type;       /* byte 25 */
  uint8_t source_venue[2];       /* bytes 26 to 27 */
  uint8_t previous_price[8];     /* bytes 28 to 35 */
  uint8_t previous_quantity[8];  /* bytes 36 to 43 */
  uint8_t transaction_time[8];   /* bytes 44 to 51 */
} DeleteOrderMessage;

/* any Delete Order Message at all: every byte one the checker chooses */
static void any_delete_order_message(DeleteOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  record->side = arbitrary();
  record->order_book_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
}

/* Delete Order Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_delete_order_message(const DeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  wire[at++] = record->side;
  wire[at++] = record->order_book_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }

  return at;
}

/* Delete Order Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_delete_order_message(DeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  record->side = wire[at++];
  record->order_book_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Order Message is what was written, byte for byte */
static void equal_delete_order_message(const DeleteOrderMessage *read, const DeleteOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  assert(read->side == written->side);
  assert(read->order_book_type == written->order_book_type);
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_price[i] == written->previous_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_quantity[i] == written->previous_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
}

/* Delete Order Message: written and read back, then read and written back */
static void check_delete_order_message(void) {
  DeleteOrderMessage sent;
  DeleteOrderMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_delete_order_message(&sent);
  assert(encode_delete_order_message(&sent, wire, 0) == 52);
  assert(decode_delete_order_message(&got, wire, 0) == 52);
  equal_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_order_message(&got, wire, 0) == 52);
  assert(encode_delete_order_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book Clear Message: 19 bytes -------------------------------------- */

/* Sent to instruct recipients to remove all orders from the order book for the specified instrument */
typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t source_venue[2];  /* bytes 8 to 9 */
  uint8_t instrument[8];    /* bytes 10 to 17 */
  uint8_t order_book_type;  /* byte 18 */
} OrderBookClearMessage;

/* any Order Book Clear Message at all: every byte one the checker chooses */
static void any_order_book_clear_message(OrderBookClearMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  record->order_book_type = arbitrary();
}

/* Order Book Clear Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_order_book_clear_message(const OrderBookClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  wire[at++] = record->order_book_type;

  return at;
}

/* Order Book Clear Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_order_book_clear_message(OrderBookClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  record->order_book_type = wire[at++];

  return at;
}

/* what was read of Order Book Clear Message is what was written, byte for byte */
static void equal_order_book_clear_message(const OrderBookClearMessage *read, const OrderBookClearMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  assert(read->order_book_type == written->order_book_type);
}

/* Order Book Clear Message: written and read back, then read and written back */
static void check_order_book_clear_message(void) {
  OrderBookClearMessage sent;
  OrderBookClearMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_order_book_clear_message(&sent);
  assert(encode_order_book_clear_message(&sent, wire, 0) == 19);
  assert(decode_order_book_clear_message(&got, wire, 0) == 19);
  equal_order_book_clear_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_clear_message(&got, wire, 0) == 19);
  assert(encode_order_book_clear_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Statistics Message: 74 bytes -------------------------------------------- */

/* Contains a set of statistics that are updated frequently, usually as a result of executions */
typedef struct {
  uint8_t timestamp[8];                      /* bytes 0 to 7 */
  uint8_t instrument[8];                     /* bytes 8 to 15 */
  uint8_t source_venue[2];                   /* bytes 16 to 17 */
  uint8_t volume[8];                         /* bytes 18 to 25 */
  uint8_t volume_on_book_only[8];            /* bytes 26 to 33 */
  uint8_t vwap[8];                           /* bytes 34 to 41 */
  uint8_t vwap_on_book_only[8];              /* bytes 42 to 49 */
  uint8_t number_of_trades[4];               /* bytes 50 to 53 */
  uint8_t number_of_trades_on_book_only[4];  /* bytes 54 to 57 */
  uint8_t turnover[8];                       /* bytes 58 to 65 */
  uint8_t turnover_on_book_only[8];          /* bytes 66 to 73 */
} StatisticsMessage;

/* any Statistics Message at all: every byte one the checker chooses */
static void any_statistics_message(StatisticsMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_on_book_only[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap_on_book_only[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_trades_on_book_only[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover_on_book_only[i] = arbitrary(); }
}

/* Statistics Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_statistics_message(const StatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_on_book_only[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap_on_book_only[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_trades[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_trades_on_book_only[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover_on_book_only[i]; }

  return at;
}

/* Statistics Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_statistics_message(StatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_on_book_only[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap_on_book_only[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_trades_on_book_only[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover_on_book_only[i] = wire[at++]; }

  return at;
}

/* what was read of Statistics Message is what was written, byte for byte */
static void equal_statistics_message(const StatisticsMessage *read, const StatisticsMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_on_book_only[i] == written->volume_on_book_only[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap_on_book_only[i] == written->vwap_on_book_only[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_trades[i] == written->number_of_trades[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_trades_on_book_only[i] == written->number_of_trades_on_book_only[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover_on_book_only[i] == written->turnover_on_book_only[i]); }
}

/* Statistics Message: written and read back, then read and written back */
static void check_statistics_message(void) {
  StatisticsMessage sent;
  StatisticsMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_statistics_message(&sent);
  assert(encode_statistics_message(&sent, wire, 0) == 74);
  assert(decode_statistics_message(&got, wire, 0) == 74);
  equal_statistics_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_statistics_message(&got, wire, 0) == 74);
  assert(encode_statistics_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Statistics Update Message: 47 bytes ------------------------------------- */

/* Contains a set of statistics that are not updated frequently */
typedef struct {
  uint8_t timestamp[8];                     /* bytes 0 to 7 */
  uint8_t instrument[8];                    /* bytes 8 to 15 */
  uint8_t source_venue[2];                  /* bytes 16 to 17 */
  uint8_t statistic_type[2];                /* bytes 18 to 19 */
  uint8_t statistic_price[8];               /* bytes 20 to 27 */
  uint8_t statistic_size[8];                /* bytes 28 to 35 */
  uint8_t auction_type;                     /* byte 36 */
  uint8_t imbalance_quantity[8];            /* bytes 37 to 44 */
  uint8_t auction_info;                     /* byte 45 */
  uint8_t opening_closing_price_indicator;  /* byte 46 */
} StatisticsUpdateMessage;

/* any Statistics Update Message at all: every byte one the checker chooses */
static void any_statistics_update_message(StatisticsUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->statistic_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->statistic_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->statistic_size[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->imbalance_quantity[i] = arbitrary(); }
  record->auction_info = arbitrary();
  record->opening_closing_price_indicator = arbitrary();
}

/* Statistics Update Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_statistics_update_message(const StatisticsUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->statistic_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->statistic_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->statistic_size[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->imbalance_quantity[i]; }
  wire[at++] = record->auction_info;
  wire[at++] = record->opening_closing_price_indicator;

  return at;
}

/* Statistics Update Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_statistics_update_message(StatisticsUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->statistic_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->statistic_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->statistic_size[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->imbalance_quantity[i] = wire[at++]; }
  record->auction_info = wire[at++];
  record->opening_closing_price_indicator = wire[at++];

  return at;
}

/* what was read of Statistics Update Message is what was written, byte for byte */
static void equal_statistics_update_message(const StatisticsUpdateMessage *read, const StatisticsUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->statistic_type[i] == written->statistic_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->statistic_price[i] == written->statistic_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->statistic_size[i] == written->statistic_size[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->imbalance_quantity[i] == written->imbalance_quantity[i]); }
  assert(read->auction_info == written->auction_info);
  assert(read->opening_closing_price_indicator == written->opening_closing_price_indicator);
}

/* Statistics Update Message: written and read back, then read and written back */
static void check_statistics_update_message(void) {
  StatisticsUpdateMessage sent;
  StatisticsUpdateMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_statistics_update_message(&sent);
  assert(encode_statistics_update_message(&sent, wire, 0) == 47);
  assert(decode_statistics_update_message(&got, wire, 0) == 47);
  equal_statistics_update_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_statistics_update_message(&got, wire, 0) == 47);
  assert(encode_statistics_update_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mifid Ii Trade Message: 289 bytes --------------------------------------- */

/* Sent to represent different types of MiFID compliant trades published by markets */
typedef struct {
  uint8_t timestamp[8];                            /* bytes 0 to 7 */
  uint8_t source_venue[2];                         /* bytes 8 to 9 */
  uint8_t instrument[8];                           /* bytes 10 to 17 */
  uint8_t transaction_identification_code[52];     /* bytes 18 to 69 */
  uint8_t trade_type;                              /* byte 70 */
  uint8_t auction_type;                            /* byte 71 */
  uint8_t mi_fid_price[20];                        /* bytes 72 to 91 */
  uint8_t mi_fid_quantity[20];                     /* bytes 92 to 111 */
  uint8_t trading_date_and_time[30];               /* bytes 112 to 141 */
  uint8_t instrument_identification_code_type[4];  /* bytes 142 to 145 */
  uint8_t instrument_identification_code[12];      /* bytes 146 to 157 */
  uint8_t price_notation[4];                       /* bytes 158 to 161 */
  uint8_t price_major_currency[3];                 /* bytes 162 to 164 */
  uint8_t notional_amount[20];                     /* bytes 165 to 184 */
  uint8_t notional_currency[3];                    /* bytes 185 to 187 */
  uint8_t venue_of_execution_alpha_4[4];           /* bytes 188 to 191 */
  uint8_t publication_date_and_time[30];           /* bytes 192 to 221 */
  uint8_t pt_ref_price_waiver_flag[4];             /* bytes 222 to 225 */
  uint8_t trading_system[4];                       /* bytes 226 to 229 */
  uint8_t market_closing_price_flag[4];            /* bytes 230 to 233 */
  uint8_t pt_algo_trade[4];                        /* bytes 234 to 237 */
  uint8_t pt_cancellation_flag[4];                 /* bytes 238 to 241 */
  uint8_t pt_amendment_flag[4];                    /* bytes 242 to 245 */
  uint8_t reserved_1;                              /* byte 246 */
  uint8_t reserved_3[3];                           /* bytes 247 to 249 */
  uint8_t reserved_20[20];                         /* bytes 250 to 269 */
  uint8_t reserved_4[4];                           /* bytes 270 to 273 */
  uint8_t trade_qualifier;                         /* byte 274 */
  uint8_t market_mechanism;                        /* byte 275 */
  uint8_t trading_mode;                            /* byte 276 */
  uint8_t transaction_category;                    /* byte 277 */
  uint8_t negotiation_indicator;                   /* byte 278 */
  uint8_t agency_cross_indicator;                  /* byte 279 */
  uint8_t modification_indicator;                  /* byte 280 */
  uint8_t reference_price_indicator;               /* byte 281 */
  uint8_t special_dividend_indicator;              /* byte 282 */
  uint8_t off_book_automated_indicator;            /* byte 283 */
  uint8_t price_formation_indicator;               /* byte 284 */
  uint8_t algorithmic_indicator;                   /* byte 285 */
  uint8_t post_trade_deferral_reason;              /* byte 286 */
  uint8_t deferral_enrichment_type;                /* byte 287 */
  uint8_t duplicative_indicator;                   /* byte 288 */
} MifidIiTradeMessage;

/* any Mifid Ii Trade Message at all: every byte one the checker chooses */
static void any_mifid_ii_trade_message(MifidIiTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->transaction_identification_code[i] = arbitrary(); }
  record->trade_type = arbitrary();
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->mi_fid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mi_fid_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->trading_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_identification_code_type[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->instrument_identification_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->price_major_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->notional_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution_alpha_4[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->publication_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_ref_price_waiver_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_closing_price_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_algo_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_cancellation_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_amendment_flag[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->reserved_20[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  record->trade_qualifier = arbitrary();
  record->market_mechanism = arbitrary();
  record->trading_mode = arbitrary();
  record->transaction_category = arbitrary();
  record->negotiation_indicator = arbitrary();
  record->agency_cross_indicator = arbitrary();
  record->modification_indicator = arbitrary();
  record->reference_price_indicator = arbitrary();
  record->special_dividend_indicator = arbitrary();
  record->off_book_automated_indicator = arbitrary();
  record->price_formation_indicator = arbitrary();
  record->algorithmic_indicator = arbitrary();
  record->post_trade_deferral_reason = arbitrary();
  record->deferral_enrichment_type = arbitrary();
  record->duplicative_indicator = arbitrary();
}

/* Mifid Ii Trade Message to the wire: 289 bytes from at, returning where the next byte goes */
static size_t encode_mifid_ii_trade_message(const MifidIiTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->transaction_identification_code[i]; }
  wire[at++] = record->trade_type;
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mi_fid_price[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mi_fid_quantity[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->trading_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_identification_code_type[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->instrument_identification_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_notation[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->price_major_currency[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->notional_amount[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->notional_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_of_execution_alpha_4[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->publication_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_ref_price_waiver_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_system[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_closing_price_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_algo_trade[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_cancellation_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_amendment_flag[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->reserved_20[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  wire[at++] = record->trade_qualifier;
  wire[at++] = record->market_mechanism;
  wire[at++] = record->trading_mode;
  wire[at++] = record->transaction_category;
  wire[at++] = record->negotiation_indicator;
  wire[at++] = record->agency_cross_indicator;
  wire[at++] = record->modification_indicator;
  wire[at++] = record->reference_price_indicator;
  wire[at++] = record->special_dividend_indicator;
  wire[at++] = record->off_book_automated_indicator;
  wire[at++] = record->price_formation_indicator;
  wire[at++] = record->algorithmic_indicator;
  wire[at++] = record->post_trade_deferral_reason;
  wire[at++] = record->deferral_enrichment_type;
  wire[at++] = record->duplicative_indicator;

  return at;
}

/* Mifid Ii Trade Message off the wire: 289 bytes from at, returning where the next byte lies */
static size_t decode_mifid_ii_trade_message(MifidIiTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->transaction_identification_code[i] = wire[at++]; }
  record->trade_type = wire[at++];
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->mi_fid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mi_fid_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->trading_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_identification_code_type[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->instrument_identification_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->price_major_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->notional_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution_alpha_4[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->publication_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_ref_price_waiver_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_closing_price_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_algo_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_cancellation_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_amendment_flag[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->reserved_20[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  record->trade_qualifier = wire[at++];
  record->market_mechanism = wire[at++];
  record->trading_mode = wire[at++];
  record->transaction_category = wire[at++];
  record->negotiation_indicator = wire[at++];
  record->agency_cross_indicator = wire[at++];
  record->modification_indicator = wire[at++];
  record->reference_price_indicator = wire[at++];
  record->special_dividend_indicator = wire[at++];
  record->off_book_automated_indicator = wire[at++];
  record->price_formation_indicator = wire[at++];
  record->algorithmic_indicator = wire[at++];
  record->post_trade_deferral_reason = wire[at++];
  record->deferral_enrichment_type = wire[at++];
  record->duplicative_indicator = wire[at++];

  return at;
}

/* what was read of Mifid Ii Trade Message is what was written, byte for byte */
static void equal_mifid_ii_trade_message(const MifidIiTradeMessage *read, const MifidIiTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->transaction_identification_code[i] == written->transaction_identification_code[i]); }
  assert(read->trade_type == written->trade_type);
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 20; i++) { assert(read->mi_fid_price[i] == written->mi_fid_price[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mi_fid_quantity[i] == written->mi_fid_quantity[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->trading_date_and_time[i] == written->trading_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_identification_code_type[i] == written->instrument_identification_code_type[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->instrument_identification_code[i] == written->instrument_identification_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_notation[i] == written->price_notation[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->price_major_currency[i] == written->price_major_currency[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->notional_amount[i] == written->notional_amount[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->notional_currency[i] == written->notional_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->venue_of_execution_alpha_4[i] == written->venue_of_execution_alpha_4[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->publication_date_and_time[i] == written->publication_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_ref_price_waiver_flag[i] == written->pt_ref_price_waiver_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_system[i] == written->trading_system[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_closing_price_flag[i] == written->market_closing_price_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_algo_trade[i] == written->pt_algo_trade[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_cancellation_flag[i] == written->pt_cancellation_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_amendment_flag[i] == written->pt_amendment_flag[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->reserved_20[i] == written->reserved_20[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  assert(read->trade_qualifier == written->trade_qualifier);
  assert(read->market_mechanism == written->market_mechanism);
  assert(read->trading_mode == written->trading_mode);
  assert(read->transaction_category == written->transaction_category);
  assert(read->negotiation_indicator == written->negotiation_indicator);
  assert(read->agency_cross_indicator == written->agency_cross_indicator);
  assert(read->modification_indicator == written->modification_indicator);
  assert(read->reference_price_indicator == written->reference_price_indicator);
  assert(read->special_dividend_indicator == written->special_dividend_indicator);
  assert(read->off_book_automated_indicator == written->off_book_automated_indicator);
  assert(read->price_formation_indicator == written->price_formation_indicator);
  assert(read->algorithmic_indicator == written->algorithmic_indicator);
  assert(read->post_trade_deferral_reason == written->post_trade_deferral_reason);
  assert(read->deferral_enrichment_type == written->deferral_enrichment_type);
  assert(read->duplicative_indicator == written->duplicative_indicator);
}

/* Mifid Ii Trade Message: written and read back, then read and written back */
static void check_mifid_ii_trade_message(void) {
  MifidIiTradeMessage sent;
  MifidIiTradeMessage got;
  uint8_t wire[289];
  uint8_t again[289];

  any_mifid_ii_trade_message(&sent);
  assert(encode_mifid_ii_trade_message(&sent, wire, 0) == 289);
  assert(decode_mifid_ii_trade_message(&got, wire, 0) == 289);
  equal_mifid_ii_trade_message(&got, &sent);

  for (size_t i = 0; i < 289; i++) { wire[i] = arbitrary(); }
  assert(decode_mifid_ii_trade_message(&got, wire, 0) == 289);
  assert(encode_mifid_ii_trade_message(&got, again, 0) == 289);
  for (size_t i = 0; i < 289; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mifid Ii Trade Cross Message: 307 bytes --------------------------------- */

/* Sent to indicate a MiFID compliant cross trade */
typedef struct {
  uint8_t timestamp[8];                            /* bytes 0 to 7 */
  uint8_t source_venue[2];                         /* bytes 8 to 9 */
  uint8_t instrument[8];                           /* bytes 10 to 17 */
  uint8_t transaction_identification_code[52];     /* bytes 18 to 69 */
  uint8_t cross_id[20];                            /* bytes 70 to 89 */
  uint8_t cross_type;                              /* byte 90 */
  uint8_t mi_fid_price[20];                        /* bytes 91 to 110 */
  uint8_t mi_fid_quantity[20];                     /* bytes 111 to 130 */
  uint8_t trading_date_and_time[30];               /* bytes 131 to 160 */
  uint8_t instrument_identification_code_type[4];  /* bytes 161 to 164 */
  uint8_t instrument_identification_code[12];      /* bytes 165 to 176 */
  uint8_t price_notation[4];                       /* bytes 177 to 180 */
  uint8_t price_major_currency[3];                 /* bytes 181 to 183 */
  uint8_t notional_amount[20];                     /* bytes 184 to 203 */
  uint8_t notional_currency[3];                    /* bytes 204 to 206 */
  uint8_t venue_of_execution_alpha_4[4];           /* bytes 207 to 210 */
  uint8_t publication_date_and_time[30];           /* bytes 211 to 240 */
  uint8_t reserved_4[4];                           /* bytes 241 to 244 */
  uint8_t nt_pre_trade_waiver_flag[4];             /* bytes 245 to 248 */
  uint8_t pt_algo_trade[4];                        /* bytes 249 to 252 */
  uint8_t second_reserved_4[4];                    /* bytes 253 to 256 */
  uint8_t pt_cancellation_flag[4];                 /* bytes 257 to 260 */
  uint8_t pt_amendment_flag[4];                    /* bytes 261 to 264 */
  uint8_t reserved_1;                              /* byte 265 */
  uint8_t reserved_3[3];                           /* bytes 266 to 268 */
  uint8_t reserved_20[20];                         /* bytes 269 to 288 */
  uint8_t trading_system[4];                       /* bytes 289 to 292 */
  uint8_t market_mechanism;                        /* byte 293 */
  uint8_t trading_mode;                            /* byte 294 */
  uint8_t transaction_category;                    /* byte 295 */
  uint8_t negotiation_indicator;                   /* byte 296 */
  uint8_t agency_cross_indicator;                  /* byte 297 */
  uint8_t modification_indicator;                  /* byte 298 */
  uint8_t reference_price_indicator;               /* byte 299 */
  uint8_t special_dividend_indicator;              /* byte 300 */
  uint8_t off_book_automated_indicator;            /* byte 301 */
  uint8_t price_formation_indicator;               /* byte 302 */
  uint8_t algorithmic_indicator;                   /* byte 303 */
  uint8_t post_trade_deferral_reason;              /* byte 304 */
  uint8_t deferral_enrichment_type;                /* byte 305 */
  uint8_t duplicative_indicator;                   /* byte 306 */
} MifidIiTradeCrossMessage;

/* any Mifid Ii Trade Cross Message at all: every byte one the checker chooses */
static void any_mifid_ii_trade_cross_message(MifidIiTradeCrossMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->transaction_identification_code[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cross_id[i] = arbitrary(); }
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->mi_fid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mi_fid_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->trading_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_identification_code_type[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->instrument_identification_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->price_major_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->notional_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution_alpha_4[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->publication_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nt_pre_trade_waiver_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_algo_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->second_reserved_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_cancellation_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_amendment_flag[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->reserved_20[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_system[i] = arbitrary(); }
  record->market_mechanism = arbitrary();
  record->trading_mode = arbitrary();
  record->transaction_category = arbitrary();
  record->negotiation_indicator = arbitrary();
  record->agency_cross_indicator = arbitrary();
  record->modification_indicator = arbitrary();
  record->reference_price_indicator = arbitrary();
  record->special_dividend_indicator = arbitrary();
  record->off_book_automated_indicator = arbitrary();
  record->price_formation_indicator = arbitrary();
  record->algorithmic_indicator = arbitrary();
  record->post_trade_deferral_reason = arbitrary();
  record->deferral_enrichment_type = arbitrary();
  record->duplicative_indicator = arbitrary();
}

/* Mifid Ii Trade Cross Message to the wire: 307 bytes from at, returning where the next byte goes */
static size_t encode_mifid_ii_trade_cross_message(const MifidIiTradeCrossMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->transaction_identification_code[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cross_id[i]; }
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mi_fid_price[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mi_fid_quantity[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->trading_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_identification_code_type[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->instrument_identification_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_notation[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->price_major_currency[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->notional_amount[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->notional_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_of_execution_alpha_4[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->publication_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nt_pre_trade_waiver_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_algo_trade[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second_reserved_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_cancellation_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_amendment_flag[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->reserved_20[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_system[i]; }
  wire[at++] = record->market_mechanism;
  wire[at++] = record->trading_mode;
  wire[at++] = record->transaction_category;
  wire[at++] = record->negotiation_indicator;
  wire[at++] = record->agency_cross_indicator;
  wire[at++] = record->modification_indicator;
  wire[at++] = record->reference_price_indicator;
  wire[at++] = record->special_dividend_indicator;
  wire[at++] = record->off_book_automated_indicator;
  wire[at++] = record->price_formation_indicator;
  wire[at++] = record->algorithmic_indicator;
  wire[at++] = record->post_trade_deferral_reason;
  wire[at++] = record->deferral_enrichment_type;
  wire[at++] = record->duplicative_indicator;

  return at;
}

/* Mifid Ii Trade Cross Message off the wire: 307 bytes from at, returning where the next byte lies */
static size_t decode_mifid_ii_trade_cross_message(MifidIiTradeCrossMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->transaction_identification_code[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cross_id[i] = wire[at++]; }
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->mi_fid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mi_fid_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->trading_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_identification_code_type[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->instrument_identification_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->price_major_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->notional_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution_alpha_4[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->publication_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nt_pre_trade_waiver_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_algo_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->second_reserved_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_cancellation_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_amendment_flag[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->reserved_20[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_system[i] = wire[at++]; }
  record->market_mechanism = wire[at++];
  record->trading_mode = wire[at++];
  record->transaction_category = wire[at++];
  record->negotiation_indicator = wire[at++];
  record->agency_cross_indicator = wire[at++];
  record->modification_indicator = wire[at++];
  record->reference_price_indicator = wire[at++];
  record->special_dividend_indicator = wire[at++];
  record->off_book_automated_indicator = wire[at++];
  record->price_formation_indicator = wire[at++];
  record->algorithmic_indicator = wire[at++];
  record->post_trade_deferral_reason = wire[at++];
  record->deferral_enrichment_type = wire[at++];
  record->duplicative_indicator = wire[at++];

  return at;
}

/* what was read of Mifid Ii Trade Cross Message is what was written, byte for byte */
static void equal_mifid_ii_trade_cross_message(const MifidIiTradeCrossMessage *read, const MifidIiTradeCrossMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->transaction_identification_code[i] == written->transaction_identification_code[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 20; i++) { assert(read->mi_fid_price[i] == written->mi_fid_price[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mi_fid_quantity[i] == written->mi_fid_quantity[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->trading_date_and_time[i] == written->trading_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_identification_code_type[i] == written->instrument_identification_code_type[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->instrument_identification_code[i] == written->instrument_identification_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_notation[i] == written->price_notation[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->price_major_currency[i] == written->price_major_currency[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->notional_amount[i] == written->notional_amount[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->notional_currency[i] == written->notional_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->venue_of_execution_alpha_4[i] == written->venue_of_execution_alpha_4[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->publication_date_and_time[i] == written->publication_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nt_pre_trade_waiver_flag[i] == written->nt_pre_trade_waiver_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_algo_trade[i] == written->pt_algo_trade[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->second_reserved_4[i] == written->second_reserved_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_cancellation_flag[i] == written->pt_cancellation_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_amendment_flag[i] == written->pt_amendment_flag[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->reserved_20[i] == written->reserved_20[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_system[i] == written->trading_system[i]); }
  assert(read->market_mechanism == written->market_mechanism);
  assert(read->trading_mode == written->trading_mode);
  assert(read->transaction_category == written->transaction_category);
  assert(read->negotiation_indicator == written->negotiation_indicator);
  assert(read->agency_cross_indicator == written->agency_cross_indicator);
  assert(read->modification_indicator == written->modification_indicator);
  assert(read->reference_price_indicator == written->reference_price_indicator);
  assert(read->special_dividend_indicator == written->special_dividend_indicator);
  assert(read->off_book_automated_indicator == written->off_book_automated_indicator);
  assert(read->price_formation_indicator == written->price_formation_indicator);
  assert(read->algorithmic_indicator == written->algorithmic_indicator);
  assert(read->post_trade_deferral_reason == written->post_trade_deferral_reason);
  assert(read->deferral_enrichment_type == written->deferral_enrichment_type);
  assert(read->duplicative_indicator == written->duplicative_indicator);
}

/* Mifid Ii Trade Cross Message: written and read back, then read and written back */
static void check_mifid_ii_trade_cross_message(void) {
  MifidIiTradeCrossMessage sent;
  MifidIiTradeCrossMessage got;
  uint8_t wire[307];
  uint8_t again[307];

  any_mifid_ii_trade_cross_message(&sent);
  assert(encode_mifid_ii_trade_cross_message(&sent, wire, 0) == 307);
  assert(decode_mifid_ii_trade_cross_message(&got, wire, 0) == 307);
  equal_mifid_ii_trade_cross_message(&got, &sent);

  for (size_t i = 0; i < 307; i++) { wire[i] = arbitrary(); }
  assert(decode_mifid_ii_trade_cross_message(&got, wire, 0) == 307);
  assert(encode_mifid_ii_trade_cross_message(&got, again, 0) == 307);
  for (size_t i = 0; i < 307; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Summary Message: 91 bytes ----------------------------------------- */

/* Trade Summary message is used to disseminate results of multi and single fill trade events */
typedef struct {
  uint8_t timestamp[8];                       /* bytes 0 to 7 */
  uint8_t instrument[8];                      /* bytes 8 to 15 */
  uint8_t source_venue[2];                    /* bytes 16 to 17 */
  uint8_t transaction_time[8];                /* bytes 18 to 25 */
  uint8_t far_price[8];                       /* bytes 26 to 33 */
  uint8_t total_executed_quantity[8];         /* bytes 34 to 41 */
  uint8_t total_hidden_executed_quantity[8];  /* bytes 42 to 49 */
  uint8_t deleted_order_quantity[8];          /* bytes 50 to 57 */
  uint8_t side;                               /* byte 58 */
  uint8_t best_bid_size[8];                   /* bytes 59 to 66 */
  uint8_t best_bid_price[8];                  /* bytes 67 to 74 */
  uint8_t best_offer_size[8];                 /* bytes 75 to 82 */
  uint8_t best_offer_price[8];                /* bytes 83 to 90 */
} TradeSummaryMessage;

/* any Trade Summary Message at all: every byte one the checker chooses */
static void any_trade_summary_message(TradeSummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->far_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_hidden_executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->deleted_order_quantity[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->best_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_offer_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_offer_price[i] = arbitrary(); }
}

/* Trade Summary Message to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_trade_summary_message(const TradeSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->far_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_hidden_executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->deleted_order_quantity[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_bid_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_bid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_offer_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_offer_price[i]; }

  return at;
}

/* Trade Summary Message off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_trade_summary_message(TradeSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->far_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_hidden_executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->deleted_order_quantity[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->best_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_offer_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_offer_price[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Summary Message is what was written, byte for byte */
static void equal_trade_summary_message(const TradeSummaryMessage *read, const TradeSummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->far_price[i] == written->far_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_executed_quantity[i] == written->total_executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_hidden_executed_quantity[i] == written->total_hidden_executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->deleted_order_quantity[i] == written->deleted_order_quantity[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->best_bid_size[i] == written->best_bid_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_bid_price[i] == written->best_bid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_offer_size[i] == written->best_offer_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_offer_price[i] == written->best_offer_price[i]); }
}

/* Trade Summary Message: written and read back, then read and written back */
static void check_trade_summary_message(void) {
  TradeSummaryMessage sent;
  TradeSummaryMessage got;
  uint8_t wire[91];
  uint8_t again[91];

  any_trade_summary_message(&sent);
  assert(encode_trade_summary_message(&sent, wire, 0) == 91);
  assert(decode_trade_summary_message(&got, wire, 0) == 91);
  equal_trade_summary_message(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_summary_message(&got, wire, 0) == 91);
  assert(encode_trade_summary_message(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Analytics Message: 106 bytes -------------------------------------------- */

/* Used to disseminate additional statistics including order book activity statistics */
typedef struct {
  uint8_t timestamp[8];                        /* bytes 0 to 7 */
  uint8_t instrument[8];                       /* bytes 8 to 15 */
  uint8_t source_venue[2];                     /* bytes 16 to 17 */
  uint8_t start_time[8];                       /* bytes 18 to 25 */
  uint8_t end_time[8];                         /* bytes 26 to 33 */
  uint8_t buy_order_count[4];                  /* bytes 34 to 37 */
  uint8_t sell_order_count[4];                 /* bytes 38 to 41 */
  uint8_t buy_order_size[8];                   /* bytes 42 to 49 */
  uint8_t sell_order_size[8];                  /* bytes 50 to 57 */
  uint8_t buy_order_cancellations[4];          /* bytes 58 to 61 */
  uint8_t sell_order_cancellations[4];         /* bytes 62 to 65 */
  uint8_t buy_limit_order_cancellations[4];    /* bytes 66 to 69 */
  uint8_t buy_market_order_cancellations[4];   /* bytes 70 to 73 */
  uint8_t sell_limit_order_cancellations[4];   /* bytes 74 to 77 */
  uint8_t sell_market_order_cancellations[4];  /* bytes 78 to 81 */
  uint8_t bid_ask_spread[8];                   /* bytes 82 to 89 */
  uint8_t vwap_buy[8];                         /* bytes 90 to 97 */
  uint8_t vwap_sell[8];                        /* bytes 98 to 105 */
} AnalyticsMessage;

/* any Analytics Message at all: every byte one the checker chooses */
static void any_analytics_message(AnalyticsMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->start_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_order_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_order_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_order_cancellations[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_order_cancellations[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_limit_order_cancellations[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_market_order_cancellations[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_limit_order_cancellations[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_market_order_cancellations[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_ask_spread[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap_buy[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap_sell[i] = arbitrary(); }
}

/* Analytics Message to the wire: 106 bytes from at, returning where the next byte goes */
static size_t encode_analytics_message(const AnalyticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->start_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_order_count[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_order_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_order_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_order_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_order_cancellations[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_order_cancellations[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_limit_order_cancellations[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_market_order_cancellations[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_limit_order_cancellations[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_market_order_cancellations[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_ask_spread[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap_buy[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap_sell[i]; }

  return at;
}

/* Analytics Message off the wire: 106 bytes from at, returning where the next byte lies */
static size_t decode_analytics_message(AnalyticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->start_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_order_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_order_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_order_cancellations[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_order_cancellations[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_limit_order_cancellations[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_market_order_cancellations[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_limit_order_cancellations[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_market_order_cancellations[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_ask_spread[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap_buy[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap_sell[i] = wire[at++]; }

  return at;
}

/* what was read of Analytics Message is what was written, byte for byte */
static void equal_analytics_message(const AnalyticsMessage *read, const AnalyticsMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->start_time[i] == written->start_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_time[i] == written->end_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_order_count[i] == written->buy_order_count[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_order_count[i] == written->sell_order_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_order_size[i] == written->buy_order_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_order_size[i] == written->sell_order_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_order_cancellations[i] == written->buy_order_cancellations[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_order_cancellations[i] == written->sell_order_cancellations[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_limit_order_cancellations[i] == written->buy_limit_order_cancellations[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_market_order_cancellations[i] == written->buy_market_order_cancellations[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_limit_order_cancellations[i] == written->sell_limit_order_cancellations[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_market_order_cancellations[i] == written->sell_market_order_cancellations[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_ask_spread[i] == written->bid_ask_spread[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap_buy[i] == written->vwap_buy[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap_sell[i] == written->vwap_sell[i]); }
}

/* Analytics Message: written and read back, then read and written back */
static void check_analytics_message(void) {
  AnalyticsMessage sent;
  AnalyticsMessage got;
  uint8_t wire[106];
  uint8_t again[106];

  any_analytics_message(&sent);
  assert(encode_analytics_message(&sent, wire, 0) == 106);
  assert(decode_analytics_message(&got, wire, 0) == 106);
  equal_analytics_message(&got, &sent);

  for (size_t i = 0; i < 106; i++) { wire[i] = arbitrary(); }
  assert(decode_analytics_message(&got, wire, 0) == 106);
  assert(encode_analytics_message(&got, again, 0) == 106);
  for (size_t i = 0; i < 106; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_unit_header();
  check_message_header();
  check_login_request_message();
  check_replay_request_message();
  check_login_response_message();
  check_replay_response_message();
  check_replay_and_recovery_complete_message();
  check_system_event_message();
  check_instrument_status_message();
  check_add_order_incremental_message();
  check_delete_order_message();
  check_order_book_clear_message();
  check_statistics_message();
  check_statistics_update_message();
  check_mifid_ii_trade_message();
  check_mifid_ii_trade_cross_message();
  check_trade_summary_message();
  check_analytics_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
