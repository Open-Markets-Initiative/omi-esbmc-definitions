// lseg/tradeecho/mifid2posttraderecovery/TradeEcho_Mifid2PostTradeRecovery_v27_2_2.c
/*
 * London Stock Exchange MiFID II Post Trade Recovery
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

/* ---- Recovery Request Message: 27 bytes -------------------------------------- */

/* Used by the client to request data on the recovery channel. */
typedef struct {
  uint8_t request_level;            /* byte 0 */
  uint8_t instrument[8];            /* bytes 1 to 8 */
  uint8_t group_id[6];              /* bytes 9 to 14 */
  uint8_t request_order_book_type;  /* byte 15 */
  uint8_t source_venue[2];          /* bytes 16 to 17 */
  uint8_t recovery_type;            /* byte 18 */
  uint8_t sequence_number[4];       /* bytes 19 to 22 */
  uint8_t request_id[4];            /* bytes 23 to 26 */
} RecoveryRequestMessage;

/* any Recovery Request Message at all: every byte one the checker chooses */
static void any_recovery_request_message(RecoveryRequestMessage *record) {
  record->request_level = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->group_id[i] = arbitrary(); }
  record->request_order_book_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  record->recovery_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
}

/* Recovery Request Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_recovery_request_message(const RecoveryRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->request_level;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->group_id[i]; }
  wire[at++] = record->request_order_book_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  wire[at++] = record->recovery_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }

  return at;
}

/* Recovery Request Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_recovery_request_message(RecoveryRequestMessage *record, const uint8_t *wire, size_t at) {
  record->request_level = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->group_id[i] = wire[at++]; }
  record->request_order_book_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  record->recovery_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }

  return at;
}

/* what was read of Recovery Request Message is what was written, byte for byte */
static void equal_recovery_request_message(const RecoveryRequestMessage *read, const RecoveryRequestMessage *written) {
  assert(read->request_level == written->request_level);
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->group_id[i] == written->group_id[i]); }
  assert(read->request_order_book_type == written->request_order_book_type);
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  assert(read->recovery_type == written->recovery_type);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
}

/* Recovery Request Message: written and read back, then read and written back */
static void check_recovery_request_message(void) {
  RecoveryRequestMessage sent;
  RecoveryRequestMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_recovery_request_message(&sent);
  assert(encode_recovery_request_message(&sent, wire, 0) == 27);
  assert(decode_recovery_request_message(&got, wire, 0) == 27);
  equal_recovery_request_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_recovery_request_message(&got, wire, 0) == 27);
  assert(encode_recovery_request_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
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

/* ---- Recovery Response Message: 13 bytes ------------------------------------- */

/* Used by the server to respond to a snapshot request on the recovery channel. */
typedef struct {
  uint8_t sequence_number[4];  /* bytes 0 to 3 */
  uint8_t count[4];            /* bytes 4 to 7 */
  uint8_t recovery_status;     /* byte 8 */
  uint8_t request_id[4];       /* bytes 9 to 12 */
} RecoveryResponseMessage;

/* any Recovery Response Message at all: every byte one the checker chooses */
static void any_recovery_response_message(RecoveryResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count[i] = arbitrary(); }
  record->recovery_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
}

/* Recovery Response Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_recovery_response_message(const RecoveryResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count[i]; }
  wire[at++] = record->recovery_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }

  return at;
}

/* Recovery Response Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_recovery_response_message(RecoveryResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count[i] = wire[at++]; }
  record->recovery_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }

  return at;
}

/* what was read of Recovery Response Message is what was written, byte for byte */
static void equal_recovery_response_message(const RecoveryResponseMessage *read, const RecoveryResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count[i] == written->count[i]); }
  assert(read->recovery_status == written->recovery_status);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
}

/* Recovery Response Message: written and read back, then read and written back */
static void check_recovery_response_message(void) {
  RecoveryResponseMessage sent;
  RecoveryResponseMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_recovery_response_message(&sent);
  assert(encode_recovery_response_message(&sent, wire, 0) == 13);
  assert(decode_recovery_response_message(&got, wire, 0) == 13);
  equal_recovery_response_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_recovery_response_message(&got, wire, 0) == 13);
  assert(encode_recovery_response_message(&got, again, 0) == 13);
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

/* Broadcast at the start and end of day on TRADEcho. Session transition is advertised via one system event message for all instruments allocated to the same multicast channel */
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

/* Should a specific instrument be subject to individual status change, such as suspension or halt, this will be communicated by the instrument status message */
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

/* ---- Statistics Snapshot Message: 270 bytes ---------------------------------- */

/* A snapshot of an instrument's statistics that is used for recovery */
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
  uint8_t official_opening_price[8];         /* bytes 74 to 81 */
  uint8_t official_closing_price[8];         /* bytes 82 to 89 */
  uint8_t trade_high_on_book_only[8];        /* bytes 90 to 97 */
  uint8_t trade_low_on_book_only[8];         /* bytes 98 to 105 */
  uint8_t trade_high[8];                     /* bytes 106 to 113 */
  uint8_t trade_low[8];                      /* bytes 114 to 121 */
  uint8_t fifty_two_week_trade_high[8];      /* bytes 122 to 129 */
  uint8_t fifty_two_week_trade_low[8];       /* bytes 130 to 137 */
  uint8_t opening_price_indicator;           /* byte 138 */
  uint8_t closing_price_indicator;           /* byte 139 */
  uint8_t iau_price[8];                      /* bytes 140 to 147 */
  uint8_t iau_paired_size[8];                /* bytes 148 to 155 */
  uint8_t imbalance_quantity[8];             /* bytes 156 to 163 */
  uint8_t imbalance_direction;               /* byte 164 */
  uint8_t best_closing_bid_price[8];         /* bytes 165 to 172 */
  uint8_t best_closing_ask_price[8];         /* bytes 173 to 180 */
  uint8_t best_closing_bid_size[8];          /* bytes 181 to 188 */
  uint8_t best_closing_ask_size[8];          /* bytes 189 to 196 */
  uint8_t trade_high_off_book[8];            /* bytes 197 to 204 */
  uint8_t trade_low_off_book[8];             /* bytes 205 to 212 */
  uint8_t reserved_8[8];                     /* bytes 213 to 220 */
  uint8_t second_reserved_8[8];              /* bytes 221 to 228 */
  uint8_t auction_type;                      /* byte 229 */
  uint8_t last_trade_price[8];               /* bytes 230 to 237 */
  uint8_t last_trade_quantity[8];            /* bytes 238 to 245 */
  uint8_t last_trade_time[8];                /* bytes 246 to 253 */
  uint8_t static_reference_price[8];         /* bytes 254 to 261 */
  uint8_t dynamic_reference_price[8];        /* bytes 262 to 269 */
} StatisticsSnapshotMessage;

/* any Statistics Snapshot Message at all: every byte one the checker chooses */
static void any_statistics_snapshot_message(StatisticsSnapshotMessage *record) {
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
  for (size_t i = 0; i < 8; i++) { record->official_opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->official_closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_high_on_book_only[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_low_on_book_only[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fifty_two_week_trade_high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->fifty_two_week_trade_low[i] = arbitrary(); }
  record->opening_price_indicator = arbitrary();
  record->closing_price_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->iau_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->iau_paired_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->imbalance_quantity[i] = arbitrary(); }
  record->imbalance_direction = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->best_closing_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_closing_ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_closing_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_closing_ask_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_high_off_book[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_low_off_book[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->second_reserved_8[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_trade_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->static_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->dynamic_reference_price[i] = arbitrary(); }
}

/* Statistics Snapshot Message to the wire: 270 bytes from at, returning where the next byte goes */
static size_t encode_statistics_snapshot_message(const StatisticsSnapshotMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->official_opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->official_closing_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_high_on_book_only[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_low_on_book_only[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fifty_two_week_trade_high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->fifty_two_week_trade_low[i]; }
  wire[at++] = record->opening_price_indicator;
  wire[at++] = record->closing_price_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->iau_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->iau_paired_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->imbalance_quantity[i]; }
  wire[at++] = record->imbalance_direction;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_closing_bid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_closing_ask_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_closing_bid_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_closing_ask_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_high_off_book[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_low_off_book[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->second_reserved_8[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_trade_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_trade_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->static_reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->dynamic_reference_price[i]; }

  return at;
}

/* Statistics Snapshot Message off the wire: 270 bytes from at, returning where the next byte lies */
static size_t decode_statistics_snapshot_message(StatisticsSnapshotMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 8; i++) { record->official_opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->official_closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_high_on_book_only[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_low_on_book_only[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fifty_two_week_trade_high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->fifty_two_week_trade_low[i] = wire[at++]; }
  record->opening_price_indicator = wire[at++];
  record->closing_price_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->iau_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->iau_paired_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->imbalance_quantity[i] = wire[at++]; }
  record->imbalance_direction = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->best_closing_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_closing_ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_closing_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_closing_ask_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_high_off_book[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_low_off_book[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->second_reserved_8[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_trade_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->static_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->dynamic_reference_price[i] = wire[at++]; }

  return at;
}

/* what was read of Statistics Snapshot Message is what was written, byte for byte */
static void equal_statistics_snapshot_message(const StatisticsSnapshotMessage *read, const StatisticsSnapshotMessage *written) {
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
  for (size_t i = 0; i < 8; i++) { assert(read->official_opening_price[i] == written->official_opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->official_closing_price[i] == written->official_closing_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_high_on_book_only[i] == written->trade_high_on_book_only[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_low_on_book_only[i] == written->trade_low_on_book_only[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_high[i] == written->trade_high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_low[i] == written->trade_low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fifty_two_week_trade_high[i] == written->fifty_two_week_trade_high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->fifty_two_week_trade_low[i] == written->fifty_two_week_trade_low[i]); }
  assert(read->opening_price_indicator == written->opening_price_indicator);
  assert(read->closing_price_indicator == written->closing_price_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->iau_price[i] == written->iau_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->iau_paired_size[i] == written->iau_paired_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->imbalance_quantity[i] == written->imbalance_quantity[i]); }
  assert(read->imbalance_direction == written->imbalance_direction);
  for (size_t i = 0; i < 8; i++) { assert(read->best_closing_bid_price[i] == written->best_closing_bid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_closing_ask_price[i] == written->best_closing_ask_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_closing_bid_size[i] == written->best_closing_bid_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_closing_ask_size[i] == written->best_closing_ask_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_high_off_book[i] == written->trade_high_off_book[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_low_off_book[i] == written->trade_low_off_book[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->second_reserved_8[i] == written->second_reserved_8[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->last_trade_price[i] == written->last_trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_trade_quantity[i] == written->last_trade_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_trade_time[i] == written->last_trade_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->static_reference_price[i] == written->static_reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->dynamic_reference_price[i] == written->dynamic_reference_price[i]); }
}

/* Statistics Snapshot Message: written and read back, then read and written back */
static void check_statistics_snapshot_message(void) {
  StatisticsSnapshotMessage sent;
  StatisticsSnapshotMessage got;
  uint8_t wire[270];
  uint8_t again[270];

  any_statistics_snapshot_message(&sent);
  assert(encode_statistics_snapshot_message(&sent, wire, 0) == 270);
  assert(decode_statistics_snapshot_message(&got, wire, 0) == 270);
  equal_statistics_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 270; i++) { wire[i] = arbitrary(); }
  assert(decode_statistics_snapshot_message(&got, wire, 0) == 270);
  assert(encode_statistics_snapshot_message(&got, again, 0) == 270);
  for (size_t i = 0; i < 270; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mifid Ii Trade Report Message: 533 bytes -------------------------------- */

/* Sent to report the MiFID compliant details of a privately negotiated trade */
typedef struct {
  uint8_t timestamp[8];                                      /* bytes 0 to 7 */
  uint8_t instrument[8];                                     /* bytes 8 to 15 */
  uint8_t transaction_identification_code[52];               /* bytes 16 to 67 */
  uint8_t total_number_of_transactions[4];                   /* bytes 68 to 71 */
  uint8_t reserved_8[8];                                     /* bytes 72 to 79 */
  uint8_t source_venue[2];                                   /* bytes 80 to 81 */
  uint8_t price[20];                                         /* bytes 82 to 101 */
  uint8_t quantity[20];                                      /* bytes 102 to 121 */
  uint8_t trading_date_and_time[27];                         /* bytes 122 to 148 */
  uint8_t instrument_identification_code_type[4];            /* bytes 149 to 152 */
  uint8_t instrument_identification_code[12];                /* bytes 153 to 164 */
  uint8_t price_notation[4];                                 /* bytes 165 to 168 */
  uint8_t price_major_currency_price_currency[3];            /* bytes 169 to 171 */
  uint8_t notional_amount[20];                               /* bytes 172 to 191 */
  uint8_t notional_currency[3];                              /* bytes 192 to 194 */
  uint8_t venue_of_execution[4];                             /* bytes 195 to 198 */
  uint8_t publication_date_and_time[27];                     /* bytes 199 to 225 */
  uint8_t benchmark_transaction_flag[4];                     /* bytes 226 to 229 */
  uint8_t agency_cross_trade_flag[4];                        /* bytes 230 to 233 */
  uint8_t non_price_forming_transactions_flag[4];            /* bytes 234 to 237 */
  uint8_t non_price_contribution_to_discovery[4];            /* bytes 238 to 241 */
  uint8_t special_dividend_flag[4];                          /* bytes 242 to 245 */
  uint8_t pt_deferral_reason_flag[4];                        /* bytes 246 to 249 */
  uint8_t reference_price_transaction_flag[4];               /* bytes 250 to 253 */
  uint8_t nt_liquidity_flag[4];                              /* bytes 254 to 257 */
  uint8_t nt_price_conditions_flag[4];                       /* bytes 258 to 261 */
  uint8_t algo_transaction_flag[4];                          /* bytes 262 to 265 */
  uint8_t pt_illiquid_flag[4];                               /* bytes 266 to 269 */
  uint8_t price_improvement_flag[4];                         /* bytes 270 to 273 */
  uint8_t cancellation_flag[4];                              /* bytes 274 to 277 */
  uint8_t amendment_flag[4];                                 /* bytes 278 to 281 */
  uint8_t duplicate_flag[4];                                 /* bytes 282 to 285 */
  uint8_t exchange_for_physicals_flag[4];                    /* bytes 286 to 289 */
  uint8_t limited_details_flag[4];                           /* bytes 290 to 293 */
  uint8_t ld_full_details_flag[4];                           /* bytes 294 to 297 */
  uint8_t daily_aggregated_transaction_flag[4];              /* bytes 298 to 301 */
  uint8_t da_full_details_flag[4];                           /* bytes 302 to 305 */
  uint8_t volume_omission_flag[4];                           /* bytes 306 to 309 */
  uint8_t vo_full_details_flag[4];                           /* bytes 310 to 313 */
  uint8_t four_weeks_aggregation_flag[4];                    /* bytes 314 to 317 */
  uint8_t fa_full_details_flag[4];                           /* bytes 318 to 321 */
  uint8_t indefinite_aggregation_flag[4];                    /* bytes 322 to 325 */
  uint8_t volume_omission_for_sovereign_debt_flag[4];        /* bytes 326 to 329 */
  uint8_t consecutive_aggregation_flag[4];                   /* bytes 330 to 333 */
  uint8_t reserved_1;                                        /* byte 334 */
  uint8_t venue_type;                                        /* byte 335 */
  uint8_t venue_book_definition_id;                          /* byte 336 */
  uint8_t notation_of_the_quantity_in_measurement_unit[25];  /* bytes 337 to 361 */
  uint8_t quantity_in_measurement_unit[20];                  /* bytes 362 to 381 */
  uint8_t transaction_to_be_cleared;                         /* byte 382 */
  uint8_t emission_allowance_type[4];                        /* bytes 383 to 386 */
  uint8_t venue_of_publication[4];                           /* bytes 387 to 390 */
  uint8_t market_mechanism;                                  /* byte 391 */
  uint8_t trading_mode;                                      /* byte 392 */
  uint8_t transaction_category;                              /* byte 393 */
  uint8_t negotiation_indicator;                             /* byte 394 */
  uint8_t agency_cross_indicator;                            /* byte 395 */
  uint8_t modification_indicator;                            /* byte 396 */
  uint8_t reference_price_indicator;                         /* byte 397 */
  uint8_t special_dividend_indicator;                        /* byte 398 */
  uint8_t off_book_automated_indicator;                      /* byte 399 */
  uint8_t price_formation_indicator;                         /* byte 400 */
  uint8_t algorithmic_indicator;                             /* byte 401 */
  uint8_t post_trade_deferral_reason;                        /* byte 402 */
  uint8_t deferral_enrichment_type;                          /* byte 403 */
  uint8_t duplicative_indicator;                             /* byte 404 */
  uint8_t third_country_trading_venue_of_execution[4];       /* bytes 405 to 408 */
  uint8_t portfolio_transaction_flag[4];                     /* bytes 409 to 412 */
  uint8_t contingent_transaction_flag[4];                    /* bytes 413 to 416 */
  uint8_t missing_price_price_conditions[4];                 /* bytes 417 to 420 */
  uint8_t market_closing_price_flag[4];                      /* bytes 421 to 424 */
  uint8_t nt_large_in_scale_flag[4];                         /* bytes 425 to 428 */
  uint8_t nt_pre_trade_transparency_flag[4];                 /* bytes 429 to 432 */
  uint8_t effective_date_of_the_contract[10];                /* bytes 433 to 442 */
  uint8_t maturity_date_of_the_contract[10];                 /* bytes 443 to 452 */
  uint8_t spread[20];                                        /* bytes 453 to 472 */
  uint8_t upfront_payment[20];                               /* bytes 473 to 492 */
  uint8_t lei_of_clearing_house[20];                         /* bytes 493 to 512 */
  uint8_t matched_principal_trade_flag[4];                   /* bytes 513 to 516 */
  uint8_t esma_standard_deferral_flags[4];                   /* bytes 517 to 520 */
  uint8_t negotiation_trade_flag[4];                         /* bytes 521 to 524 */
  uint8_t esma_supplementary_deferral_flags[4];              /* bytes 525 to 528 */
  uint8_t trading_system[4];                                 /* bytes 529 to 532 */
} MifidIiTradeReportMessage;

/* any Mifid Ii Trade Report Message at all: every byte one the checker chooses */
static void any_mifid_ii_trade_report_message(MifidIiTradeReportMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->transaction_identification_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_number_of_transactions[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 27; i++) { record->trading_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_identification_code_type[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->instrument_identification_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->price_major_currency_price_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->notional_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = arbitrary(); }
  for (size_t i = 0; i < 27; i++) { record->publication_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->benchmark_transaction_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->agency_cross_trade_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->non_price_forming_transactions_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->non_price_contribution_to_discovery[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->special_dividend_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_deferral_reason_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_price_transaction_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nt_liquidity_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nt_price_conditions_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->algo_transaction_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_illiquid_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_improvement_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancellation_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->amendment_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->duplicate_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->exchange_for_physicals_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->limited_details_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ld_full_details_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->daily_aggregated_transaction_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->da_full_details_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_omission_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->vo_full_details_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->four_weeks_aggregation_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fa_full_details_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->indefinite_aggregation_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_omission_for_sovereign_debt_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->consecutive_aggregation_flag[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->venue_type = arbitrary();
  record->venue_book_definition_id = arbitrary();
  for (size_t i = 0; i < 25; i++) { record->notation_of_the_quantity_in_measurement_unit[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->quantity_in_measurement_unit[i] = arbitrary(); }
  record->transaction_to_be_cleared = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->emission_allowance_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->venue_of_publication[i] = arbitrary(); }
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
  for (size_t i = 0; i < 4; i++) { record->third_country_trading_venue_of_execution[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->portfolio_transaction_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contingent_transaction_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->missing_price_price_conditions[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_closing_price_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nt_large_in_scale_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nt_pre_trade_transparency_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->effective_date_of_the_contract[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->maturity_date_of_the_contract[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->spread[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->upfront_payment[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->lei_of_clearing_house[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->matched_principal_trade_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->esma_standard_deferral_flags[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->negotiation_trade_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->esma_supplementary_deferral_flags[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_system[i] = arbitrary(); }
}

/* Mifid Ii Trade Report Message to the wire: 533 bytes from at, returning where the next byte goes */
static size_t encode_mifid_ii_trade_report_message(const MifidIiTradeReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->transaction_identification_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_number_of_transactions[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 27; i++) { wire[at++] = record->trading_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_identification_code_type[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->instrument_identification_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_notation[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->price_major_currency_price_currency[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->notional_amount[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->notional_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_of_execution[i]; }
  for (size_t i = 0; i < 27; i++) { wire[at++] = record->publication_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->benchmark_transaction_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->agency_cross_trade_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->non_price_forming_transactions_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->non_price_contribution_to_discovery[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->special_dividend_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_deferral_reason_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_price_transaction_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nt_liquidity_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nt_price_conditions_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->algo_transaction_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_illiquid_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_improvement_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancellation_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->amendment_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->duplicate_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_for_physicals_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->limited_details_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ld_full_details_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->daily_aggregated_transaction_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->da_full_details_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_omission_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->vo_full_details_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->four_weeks_aggregation_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fa_full_details_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indefinite_aggregation_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_omission_for_sovereign_debt_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->consecutive_aggregation_flag[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->venue_type;
  wire[at++] = record->venue_book_definition_id;
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->notation_of_the_quantity_in_measurement_unit[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->quantity_in_measurement_unit[i]; }
  wire[at++] = record->transaction_to_be_cleared;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->emission_allowance_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_of_publication[i]; }
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->third_country_trading_venue_of_execution[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->portfolio_transaction_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contingent_transaction_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->missing_price_price_conditions[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_closing_price_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nt_large_in_scale_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nt_pre_trade_transparency_flag[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->effective_date_of_the_contract[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->maturity_date_of_the_contract[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->spread[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->upfront_payment[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->lei_of_clearing_house[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->matched_principal_trade_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->esma_standard_deferral_flags[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->negotiation_trade_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->esma_supplementary_deferral_flags[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_system[i]; }

  return at;
}

/* Mifid Ii Trade Report Message off the wire: 533 bytes from at, returning where the next byte lies */
static size_t decode_mifid_ii_trade_report_message(MifidIiTradeReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->transaction_identification_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_number_of_transactions[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 27; i++) { record->trading_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_identification_code_type[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->instrument_identification_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->price_major_currency_price_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->notional_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = wire[at++]; }
  for (size_t i = 0; i < 27; i++) { record->publication_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->benchmark_transaction_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->agency_cross_trade_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->non_price_forming_transactions_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->non_price_contribution_to_discovery[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->special_dividend_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_deferral_reason_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_price_transaction_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nt_liquidity_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nt_price_conditions_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->algo_transaction_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_illiquid_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_improvement_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancellation_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->amendment_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->duplicate_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->exchange_for_physicals_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->limited_details_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ld_full_details_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->daily_aggregated_transaction_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->da_full_details_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_omission_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->vo_full_details_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->four_weeks_aggregation_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fa_full_details_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->indefinite_aggregation_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_omission_for_sovereign_debt_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->consecutive_aggregation_flag[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->venue_type = wire[at++];
  record->venue_book_definition_id = wire[at++];
  for (size_t i = 0; i < 25; i++) { record->notation_of_the_quantity_in_measurement_unit[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->quantity_in_measurement_unit[i] = wire[at++]; }
  record->transaction_to_be_cleared = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->emission_allowance_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->venue_of_publication[i] = wire[at++]; }
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
  for (size_t i = 0; i < 4; i++) { record->third_country_trading_venue_of_execution[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->portfolio_transaction_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contingent_transaction_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->missing_price_price_conditions[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_closing_price_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nt_large_in_scale_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nt_pre_trade_transparency_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->effective_date_of_the_contract[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->maturity_date_of_the_contract[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->spread[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->upfront_payment[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->lei_of_clearing_house[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->matched_principal_trade_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->esma_standard_deferral_flags[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->negotiation_trade_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->esma_supplementary_deferral_flags[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_system[i] = wire[at++]; }

  return at;
}

/* what was read of Mifid Ii Trade Report Message is what was written, byte for byte */
static void equal_mifid_ii_trade_report_message(const MifidIiTradeReportMessage *read, const MifidIiTradeReportMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->transaction_identification_code[i] == written->transaction_identification_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_number_of_transactions[i] == written->total_number_of_transactions[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 27; i++) { assert(read->trading_date_and_time[i] == written->trading_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_identification_code_type[i] == written->instrument_identification_code_type[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->instrument_identification_code[i] == written->instrument_identification_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_notation[i] == written->price_notation[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->price_major_currency_price_currency[i] == written->price_major_currency_price_currency[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->notional_amount[i] == written->notional_amount[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->notional_currency[i] == written->notional_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->venue_of_execution[i] == written->venue_of_execution[i]); }
  for (size_t i = 0; i < 27; i++) { assert(read->publication_date_and_time[i] == written->publication_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->benchmark_transaction_flag[i] == written->benchmark_transaction_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->agency_cross_trade_flag[i] == written->agency_cross_trade_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->non_price_forming_transactions_flag[i] == written->non_price_forming_transactions_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->non_price_contribution_to_discovery[i] == written->non_price_contribution_to_discovery[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->special_dividend_flag[i] == written->special_dividend_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_deferral_reason_flag[i] == written->pt_deferral_reason_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_price_transaction_flag[i] == written->reference_price_transaction_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nt_liquidity_flag[i] == written->nt_liquidity_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nt_price_conditions_flag[i] == written->nt_price_conditions_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->algo_transaction_flag[i] == written->algo_transaction_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_illiquid_flag[i] == written->pt_illiquid_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_improvement_flag[i] == written->price_improvement_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancellation_flag[i] == written->cancellation_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->amendment_flag[i] == written->amendment_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->duplicate_flag[i] == written->duplicate_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_for_physicals_flag[i] == written->exchange_for_physicals_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->limited_details_flag[i] == written->limited_details_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ld_full_details_flag[i] == written->ld_full_details_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->daily_aggregated_transaction_flag[i] == written->daily_aggregated_transaction_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->da_full_details_flag[i] == written->da_full_details_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_omission_flag[i] == written->volume_omission_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->vo_full_details_flag[i] == written->vo_full_details_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->four_weeks_aggregation_flag[i] == written->four_weeks_aggregation_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fa_full_details_flag[i] == written->fa_full_details_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->indefinite_aggregation_flag[i] == written->indefinite_aggregation_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_omission_for_sovereign_debt_flag[i] == written->volume_omission_for_sovereign_debt_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->consecutive_aggregation_flag[i] == written->consecutive_aggregation_flag[i]); }
  assert(read->reserved_1 == written->reserved_1);
  assert(read->venue_type == written->venue_type);
  assert(read->venue_book_definition_id == written->venue_book_definition_id);
  for (size_t i = 0; i < 25; i++) { assert(read->notation_of_the_quantity_in_measurement_unit[i] == written->notation_of_the_quantity_in_measurement_unit[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->quantity_in_measurement_unit[i] == written->quantity_in_measurement_unit[i]); }
  assert(read->transaction_to_be_cleared == written->transaction_to_be_cleared);
  for (size_t i = 0; i < 4; i++) { assert(read->emission_allowance_type[i] == written->emission_allowance_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->venue_of_publication[i] == written->venue_of_publication[i]); }
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
  for (size_t i = 0; i < 4; i++) { assert(read->third_country_trading_venue_of_execution[i] == written->third_country_trading_venue_of_execution[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->portfolio_transaction_flag[i] == written->portfolio_transaction_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contingent_transaction_flag[i] == written->contingent_transaction_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->missing_price_price_conditions[i] == written->missing_price_price_conditions[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_closing_price_flag[i] == written->market_closing_price_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nt_large_in_scale_flag[i] == written->nt_large_in_scale_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nt_pre_trade_transparency_flag[i] == written->nt_pre_trade_transparency_flag[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->effective_date_of_the_contract[i] == written->effective_date_of_the_contract[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->maturity_date_of_the_contract[i] == written->maturity_date_of_the_contract[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->spread[i] == written->spread[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->upfront_payment[i] == written->upfront_payment[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->lei_of_clearing_house[i] == written->lei_of_clearing_house[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->matched_principal_trade_flag[i] == written->matched_principal_trade_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->esma_standard_deferral_flags[i] == written->esma_standard_deferral_flags[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->negotiation_trade_flag[i] == written->negotiation_trade_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->esma_supplementary_deferral_flags[i] == written->esma_supplementary_deferral_flags[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_system[i] == written->trading_system[i]); }
}

/* Mifid Ii Trade Report Message: written and read back, then read and written back */
static void check_mifid_ii_trade_report_message(void) {
  MifidIiTradeReportMessage sent;
  MifidIiTradeReportMessage got;
  uint8_t wire[533];
  uint8_t again[533];

  any_mifid_ii_trade_report_message(&sent);
  assert(encode_mifid_ii_trade_report_message(&sent, wire, 0) == 533);
  assert(decode_mifid_ii_trade_report_message(&got, wire, 0) == 533);
  equal_mifid_ii_trade_report_message(&got, &sent);

  for (size_t i = 0; i < 533; i++) { wire[i] = arbitrary(); }
  assert(decode_mifid_ii_trade_report_message(&got, wire, 0) == 533);
  assert(encode_mifid_ii_trade_report_message(&got, again, 0) == 533);
  for (size_t i = 0; i < 533; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_unit_header();
  check_message_header();
  check_login_request_message();
  check_recovery_request_message();
  check_login_response_message();
  check_recovery_response_message();
  check_replay_and_recovery_complete_message();
  check_system_event_message();
  check_instrument_status_message();
  check_statistics_snapshot_message();
  check_mifid_ii_trade_report_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
