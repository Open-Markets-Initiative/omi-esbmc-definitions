// lseg/tradeecho/level2incrementalreplay/TradeEcho_Level2IncrementalReplay_v26_1_2.c
/*
 * London Stock Exchange Level 2 Incremental Replay
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

/* Used by the client to log in to the replay or recovery channel */
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

/* Used by the client to request a retransmission of messages on the replay channel */
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

/* Used by the server to accept or reject a login request to the replay or recovery channel */
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

/* Used by the server to respond to a retransmission request on the replay channel */
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

/* Used by the server to indicate the successful completion of servicing a message replay or a recovery request */
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

/* Broadcast at the start and end of day on TRADEcho. Customers should consider the SI Quote book to be empty following receipt of this message; no explicit Order Book Clear or delete order messages will be sent */
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

/* Used to communicate status of an instrument. Instrument status messages are disseminated prior to system event start of day message */
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

/* ---- Delete Order Message: 52 bytes ------------------------------------------ */

/* Sent to instruct recipients to delete a quote */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t order_id[8];           /* bytes 8 to 15 */
  uint8_t instrument[8];         /* bytes 16 to 23 */
  uint8_t side;                  /* byte 24 */
  uint8_t order_book_type;       /* byte 25 */
  uint8_t source_venue[2];       /* bytes 26 to 27 */
  uint8_t previous_price[8];     /* bytes 28 to 35 */
  uint8_t previous_quantity[8];  /* bytes 36 to 43 */
  uint8_t internal_id[8];        /* bytes 44 to 51 */
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
  for (size_t i = 0; i < 8; i++) { record->internal_id[i] = arbitrary(); }
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
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->internal_id[i]; }

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
  for (size_t i = 0; i < 8; i++) { record->internal_id[i] = wire[at++]; }

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
  for (size_t i = 0; i < 8; i++) { assert(read->internal_id[i] == written->internal_id[i]); }
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

/* Sent to instruct recipients to remove all quotes from the book for the specified instrument */
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

/* ---- Si Quote Message: 81 bytes ---------------------------------------------- */

/* Publishing Systematic Internaliser (SI) Quotes */
typedef struct {
  uint8_t timestamp[8];             /* bytes 0 to 7 */
  uint8_t order_id[8];              /* bytes 8 to 15 */
  uint8_t side;                     /* byte 16 */
  uint8_t size[8];                  /* bytes 17 to 24 */
  uint8_t instrument[8];            /* bytes 25 to 32 */
  uint8_t price[8];                 /* bytes 33 to 40 */
  uint8_t internal_id[8];           /* bytes 41 to 48 */
  uint8_t source_venue[2];          /* bytes 49 to 50 */
  uint8_t order_book_type;          /* byte 51 */
  uint8_t participant[11];          /* bytes 52 to 62 */
  uint8_t order_type;               /* byte 63 */
  uint8_t reserved_10[10];          /* bytes 64 to 73 */
  uint8_t currency[3];              /* bytes 74 to 76 */
  uint8_t venue_of_publication[4];  /* bytes 77 to 80 */
} SiQuoteMessage;

/* any Si Quote Message at all: every byte one the checker chooses */
static void any_si_quote_message(SiQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->internal_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  record->order_book_type = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->participant[i] = arbitrary(); }
  record->order_type = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->venue_of_publication[i] = arbitrary(); }
}

/* Si Quote Message to the wire: 81 bytes from at, returning where the next byte goes */
static size_t encode_si_quote_message(const SiQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->internal_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  wire[at++] = record->order_book_type;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->participant[i]; }
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_of_publication[i]; }

  return at;
}

/* Si Quote Message off the wire: 81 bytes from at, returning where the next byte lies */
static size_t decode_si_quote_message(SiQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->internal_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  record->order_book_type = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->participant[i] = wire[at++]; }
  record->order_type = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->venue_of_publication[i] = wire[at++]; }

  return at;
}

/* what was read of Si Quote Message is what was written, byte for byte */
static void equal_si_quote_message(const SiQuoteMessage *read, const SiQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->size[i] == written->size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->internal_id[i] == written->internal_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  assert(read->order_book_type == written->order_book_type);
  for (size_t i = 0; i < 11; i++) { assert(read->participant[i] == written->participant[i]); }
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->venue_of_publication[i] == written->venue_of_publication[i]); }
}

/* Si Quote Message: written and read back, then read and written back */
static void check_si_quote_message(void) {
  SiQuoteMessage sent;
  SiQuoteMessage got;
  uint8_t wire[81];
  uint8_t again[81];

  any_si_quote_message(&sent);
  assert(encode_si_quote_message(&sent, wire, 0) == 81);
  assert(decode_si_quote_message(&got, wire, 0) == 81);
  equal_si_quote_message(&got, &sent);

  for (size_t i = 0; i < 81; i++) { wire[i] = arbitrary(); }
  assert(decode_si_quote_message(&got, wire, 0) == 81);
  assert(encode_si_quote_message(&got, again, 0) == 81);
  for (size_t i = 0; i < 81; i++) { assert(again[i] == wire[i]); }
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
  check_delete_order_message();
  check_order_book_clear_message();
  check_si_quote_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
