// lseg/millennium/level2replay/Lseg_Millennium_Level2Replay_v11_9.c
/*
 * London Stock Exchange
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

/* ---- Message Header: 2 bytes ------------------------------------------------- */

/* Mitch Tcp Message Header */
typedef struct {
  uint8_t message_length;  /* byte 0 */
  uint8_t message_type;    /* byte 1 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->message_length = arbitrary();
  record->message_type = arbitrary();
}

/* Message Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_length;
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->message_length = wire[at++];
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->message_length == written->message_length);
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[2];
  uint8_t again[2];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 2);
  assert(decode_message_header(&got, wire, 0) == 2);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 2);
  assert(encode_message_header(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request Message: 16 bytes ----------------------------------------- */

/* Used by the client to log in to the replay channel. */
typedef struct {
  uint8_t username[6];   /* bytes 0 to 5 */
  uint8_t password[10];  /* bytes 6 to 15 */
} LoginRequestMessage;

/* any Login Request Message at all: every byte one the checker chooses */
static void any_login_request_message(LoginRequestMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
}

/* Login Request Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_login_request_message(const LoginRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }

  return at;
}

/* Login Request Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_login_request_message(LoginRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request Message is what was written, byte for byte */
static void equal_login_request_message(const LoginRequestMessage *read, const LoginRequestMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
}

/* Login Request Message: written and read back, then read and written back */
static void check_login_request_message(void) {
  LoginRequestMessage sent;
  LoginRequestMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_login_request_message(&sent);
  assert(encode_login_request_message(&sent, wire, 0) == 16);
  assert(decode_login_request_message(&got, wire, 0) == 16);
  equal_login_request_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_message(&got, wire, 0) == 16);
  assert(encode_login_request_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response Message: 1 byte ------------------------------------------ */

/* Used by the server to accept or reject a login request. */
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

/* ---- Replay Request Message: 7 bytes ----------------------------------------- */

/* Used by the client to request the retransmission of messages published on the multicast channel. */
typedef struct {
  uint8_t market_data_group;  /* byte 0 */
  uint8_t first_message[4];   /* bytes 1 to 4 */
  uint8_t count[2];           /* bytes 5 to 6 */
} ReplayRequestMessage;

/* any Replay Request Message at all: every byte one the checker chooses */
static void any_replay_request_message(ReplayRequestMessage *record) {
  record->market_data_group = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->first_message[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->count[i] = arbitrary(); }
}

/* Replay Request Message to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_replay_request_message(const ReplayRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_data_group;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_message[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->count[i]; }

  return at;
}

/* Replay Request Message off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_replay_request_message(ReplayRequestMessage *record, const uint8_t *wire, size_t at) {
  record->market_data_group = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->first_message[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->count[i] = wire[at++]; }

  return at;
}

/* what was read of Replay Request Message is what was written, byte for byte */
static void equal_replay_request_message(const ReplayRequestMessage *read, const ReplayRequestMessage *written) {
  assert(read->market_data_group == written->market_data_group);
  for (size_t i = 0; i < 4; i++) { assert(read->first_message[i] == written->first_message[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->count[i] == written->count[i]); }
}

/* Replay Request Message: written and read back, then read and written back */
static void check_replay_request_message(void) {
  ReplayRequestMessage sent;
  ReplayRequestMessage got;
  uint8_t wire[7];
  uint8_t again[7];

  any_replay_request_message(&sent);
  assert(encode_replay_request_message(&sent, wire, 0) == 7);
  assert(decode_replay_request_message(&got, wire, 0) == 7);
  equal_replay_request_message(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_request_message(&got, wire, 0) == 7);
  assert(encode_replay_request_message(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay Response Message: 8 bytes ---------------------------------------- */

/* Used by the server to accept or reject a replay request. */
typedef struct {
  uint8_t market_data_group;  /* byte 0 */
  uint8_t first_message[4];   /* bytes 1 to 4 */
  uint8_t count[2];           /* bytes 5 to 6 */
  uint8_t replay_status;      /* byte 7 */
} ReplayResponseMessage;

/* any Replay Response Message at all: every byte one the checker chooses */
static void any_replay_response_message(ReplayResponseMessage *record) {
  record->market_data_group = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->first_message[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->count[i] = arbitrary(); }
  record->replay_status = arbitrary();
}

/* Replay Response Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_replay_response_message(const ReplayResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_data_group;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_message[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->count[i]; }
  wire[at++] = record->replay_status;

  return at;
}

/* Replay Response Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_replay_response_message(ReplayResponseMessage *record, const uint8_t *wire, size_t at) {
  record->market_data_group = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->first_message[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->count[i] = wire[at++]; }
  record->replay_status = wire[at++];

  return at;
}

/* what was read of Replay Response Message is what was written, byte for byte */
static void equal_replay_response_message(const ReplayResponseMessage *read, const ReplayResponseMessage *written) {
  assert(read->market_data_group == written->market_data_group);
  for (size_t i = 0; i < 4; i++) { assert(read->first_message[i] == written->first_message[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->count[i] == written->count[i]); }
  assert(read->replay_status == written->replay_status);
}

/* Replay Response Message: written and read back, then read and written back */
static void check_replay_response_message(void) {
  ReplayResponseMessage sent;
  ReplayResponseMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_replay_response_message(&sent);
  assert(encode_replay_response_message(&sent, wire, 0) == 8);
  assert(decode_replay_response_message(&got, wire, 0) == 8);
  equal_replay_response_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_response_message(&got, wire, 0) == 8);
  assert(encode_replay_response_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Time Message: 4 bytes --------------------------------------------------- */

/* Sent by the server for every second for which at least one application message is generated. */
typedef struct {
  uint8_t seconds[4];  /* bytes 0 to 3 */
} TimeMessage;

/* any Time Message at all: every byte one the checker chooses */
static void any_time_message(TimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
}

/* Time Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_time_message(const TimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }

  return at;
}

/* Time Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_time_message(TimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Time Message is what was written, byte for byte */
static void equal_time_message(const TimeMessage *read, const TimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
}

/* Time Message: written and read back, then read and written back */
static void check_time_message(void) {
  TimeMessage sent;
  TimeMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_time_message(&sent);
  assert(encode_time_message(&sent, wire, 0) == 4);
  assert(decode_time_message(&got, wire, 0) == 4);
  equal_time_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_time_message(&got, wire, 0) == 4);
  assert(encode_time_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 5 bytes ------------------------------------------- */

/* Sent to indicate the start and end of the day. */
typedef struct {
  uint8_t nanosecond[4];  /* bytes 0 to 3 */
  uint8_t event_code;     /* byte 4 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  assert(read->event_code == written->event_code);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 5);
  assert(decode_system_event_message(&got, wire, 0) == 5);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 5);
  assert(encode_system_event_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Directory Message: 63 bytes -------------------------------------- */

/* Used to disseminate information (symbol, segment, ISIN, underlying, etc.) on each instrument */
typedef struct {
  uint8_t nanosecond[4];            /* bytes 0 to 3 */
  uint8_t instrument_id[4];         /* bytes 4 to 7 */
  uint8_t reserved_a;               /* byte 8 */
  uint8_t reserved_b;               /* byte 9 */
  uint8_t symbol_status;            /* byte 10 */
  uint8_t isin[12];                 /* bytes 11 to 22 */
  uint8_t sedol[12];                /* bytes 23 to 34 */
  uint8_t segment[6];               /* bytes 35 to 40 */
  uint8_t underlying[6];            /* bytes 41 to 46 */
  uint8_t currency[3];              /* bytes 47 to 49 */
  uint8_t reserved_byte;            /* byte 50 */
  uint8_t reserved_4[4];            /* bytes 51 to 54 */
  uint8_t previous_close_price[8];  /* bytes 55 to 62 */
} SymbolDirectoryMessage;

/* any Symbol Directory Message at all: every byte one the checker chooses */
static void any_symbol_directory_message(SymbolDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->reserved_a = arbitrary();
  record->reserved_b = arbitrary();
  record->symbol_status = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->sedol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->segment[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlying[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  record->reserved_byte = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_close_price[i] = arbitrary(); }
}

/* Symbol Directory Message to the wire: 63 bytes from at, returning where the next byte goes */
static size_t encode_symbol_directory_message(const SymbolDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->reserved_a;
  wire[at++] = record->reserved_b;
  wire[at++] = record->symbol_status;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->sedol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->segment[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlying[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->reserved_byte;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_close_price[i]; }

  return at;
}

/* Symbol Directory Message off the wire: 63 bytes from at, returning where the next byte lies */
static size_t decode_symbol_directory_message(SymbolDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->reserved_a = wire[at++];
  record->reserved_b = wire[at++];
  record->symbol_status = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->sedol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->segment[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlying[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  record->reserved_byte = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_close_price[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Directory Message is what was written, byte for byte */
static void equal_symbol_directory_message(const SymbolDirectoryMessage *read, const SymbolDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->reserved_a == written->reserved_a);
  assert(read->reserved_b == written->reserved_b);
  assert(read->symbol_status == written->symbol_status);
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->sedol[i] == written->sedol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->segment[i] == written->segment[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlying[i] == written->underlying[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->reserved_byte == written->reserved_byte);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_close_price[i] == written->previous_close_price[i]); }
}

/* Symbol Directory Message: written and read back, then read and written back */
static void check_symbol_directory_message(void) {
  SymbolDirectoryMessage sent;
  SymbolDirectoryMessage got;
  uint8_t wire[63];
  uint8_t again[63];

  any_symbol_directory_message(&sent);
  assert(encode_symbol_directory_message(&sent, wire, 0) == 63);
  assert(decode_symbol_directory_message(&got, wire, 0) == 63);
  equal_symbol_directory_message(&got, &sent);

  for (size_t i = 0; i < 63; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_directory_message(&got, wire, 0) == 63);
  assert(encode_symbol_directory_message(&got, again, 0) == 63);
  for (size_t i = 0; i < 63; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 24 bytes ---------------------------------------- */

/* Indicates that the displayed portion of an order is fully or partially filled at its displayed price. */
typedef struct {
  uint8_t nanosecond[4];         /* bytes 0 to 3 */
  uint8_t order_id[8];           /* bytes 4 to 11 */
  uint8_t executed_quantity[4];  /* bytes 12 to 15 */
  uint8_t trade_match_id[8];     /* bytes 16 to 23 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_match_id[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_match_id[i]; }

  return at;
}

/* Order Executed Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_match_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_match_id[i] == written->trade_match_id[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 24);
  assert(decode_order_executed_message(&got, wire, 0) == 24);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 24);
  assert(encode_order_executed_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed With Price Size Message: 37 bytes ------------------------ */

/* Sent if a displayed order is fully or partially filled at a price that is different from its displayed price. */
typedef struct {
  uint8_t nanosecond[4];         /* bytes 0 to 3 */
  uint8_t order_id[8];           /* bytes 4 to 11 */
  uint8_t executed_quantity[4];  /* bytes 12 to 15 */
  uint8_t display_quantity[4];   /* bytes 16 to 19 */
  uint8_t trade_match_id[8];     /* bytes 20 to 27 */
  uint8_t printable;             /* byte 28 */
  uint8_t price[8];              /* bytes 29 to 36 */
} OrderExecutedWithPriceSizeMessage;

/* any Order Executed With Price Size Message at all: every byte one the checker chooses */
static void any_order_executed_with_price_size_message(OrderExecutedWithPriceSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_match_id[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Order Executed With Price Size Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_with_price_size_message(const OrderExecutedWithPriceSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_match_id[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Executed With Price Size Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_with_price_size_message(OrderExecutedWithPriceSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_match_id[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed With Price Size Message is what was written, byte for byte */
static void equal_order_executed_with_price_size_message(const OrderExecutedWithPriceSizeMessage *read, const OrderExecutedWithPriceSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_quantity[i] == written->display_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_match_id[i] == written->trade_match_id[i]); }
  assert(read->printable == written->printable);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Executed With Price Size Message: written and read back, then read and written back */
static void check_order_executed_with_price_size_message(void) {
  OrderExecutedWithPriceSizeMessage sent;
  OrderExecutedWithPriceSizeMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_order_executed_with_price_size_message(&sent);
  assert(encode_order_executed_with_price_size_message(&sent, wire, 0) == 37);
  assert(decode_order_executed_with_price_size_message(&got, wire, 0) == 37);
  equal_order_executed_with_price_size_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_with_price_size_message(&got, wire, 0) == 37);
  assert(encode_order_executed_with_price_size_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Info Message: 28 bytes ------------------------------------------ */

/* 9 Used to disseminate the indicative auction price and the tradable quantity and imbalance at this price. */
typedef struct {
  uint8_t nanosecond[4];       /* bytes 0 to 3 */
  uint8_t paired_quantity[4];  /* bytes 4 to 7 */
  uint8_t reserved_4[4];       /* bytes 8 to 11 */
  uint8_t reserved_1;          /* byte 12 */
  uint8_t instrument_id[4];    /* bytes 13 to 16 */
  uint8_t reserved_a;          /* byte 17 */
  uint8_t reserved_b;          /* byte 18 */
  uint8_t price[8];            /* bytes 19 to 26 */
  uint8_t auction_type;        /* byte 27 */
} AuctionInfoMessage;

/* any Auction Info Message at all: every byte one the checker chooses */
static void any_auction_info_message(AuctionInfoMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->paired_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->reserved_a = arbitrary();
  record->reserved_b = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->auction_type = arbitrary();
}

/* Auction Info Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_auction_info_message(const AuctionInfoMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->paired_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->reserved_a;
  wire[at++] = record->reserved_b;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->auction_type;

  return at;
}

/* Auction Info Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_auction_info_message(AuctionInfoMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->paired_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->reserved_a = wire[at++];
  record->reserved_b = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->auction_type = wire[at++];

  return at;
}

/* what was read of Auction Info Message is what was written, byte for byte */
static void equal_auction_info_message(const AuctionInfoMessage *read, const AuctionInfoMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->paired_quantity[i] == written->paired_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->reserved_a == written->reserved_a);
  assert(read->reserved_b == written->reserved_b);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->auction_type == written->auction_type);
}

/* Auction Info Message: written and read back, then read and written back */
static void check_auction_info_message(void) {
  AuctionInfoMessage sent;
  AuctionInfoMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_auction_info_message(&sent);
  assert(encode_auction_info_message(&sent, wire, 0) == 28);
  assert(decode_auction_info_message(&got, wire, 0) == 28);
  equal_auction_info_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_info_message(&got, wire, 0) == 28);
  assert(encode_auction_info_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Of Book Message: 32 bytes ------------------------------------------- */

/* Used to disseminate top of book changes when the instrument is in a scheduled level 1 only auction. */
typedef struct {
  uint8_t nanosecond[4];        /* bytes 0 to 3 */
  uint8_t instrument_id[4];     /* bytes 4 to 7 */
  uint8_t buy_limit_price[8];   /* bytes 8 to 15 */
  uint8_t buy_limit_size[4];    /* bytes 16 to 19 */
  uint8_t sell_limit_price[8];  /* bytes 20 to 27 */
  uint8_t sell_limit_size[4];   /* bytes 28 to 31 */
} TopOfBookMessage;

/* any Top Of Book Message at all: every byte one the checker chooses */
static void any_top_of_book_message(TopOfBookMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_limit_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_limit_size[i] = arbitrary(); }
}

/* Top Of Book Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_top_of_book_message(const TopOfBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_limit_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_limit_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_limit_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_limit_size[i]; }

  return at;
}

/* Top Of Book Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_top_of_book_message(TopOfBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_limit_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_limit_size[i] = wire[at++]; }

  return at;
}

/* what was read of Top Of Book Message is what was written, byte for byte */
static void equal_top_of_book_message(const TopOfBookMessage *read, const TopOfBookMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_limit_price[i] == written->buy_limit_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_limit_size[i] == written->buy_limit_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_limit_price[i] == written->sell_limit_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_limit_size[i] == written->sell_limit_size[i]); }
}

/* Top Of Book Message: written and read back, then read and written back */
static void check_top_of_book_message(void) {
  TopOfBookMessage sent;
  TopOfBookMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_top_of_book_message(&sent);
  assert(encode_top_of_book_message(&sent, wire, 0) == 32);
  assert(decode_top_of_book_message(&got, wire, 0) == 32);
  equal_top_of_book_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_top_of_book_message(&got, wire, 0) == 32);
  assert(encode_top_of_book_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_unit_header();
  check_message_header();
  check_login_request_message();
  check_login_response_message();
  check_replay_request_message();
  check_replay_response_message();
  check_time_message();
  check_system_event_message();
  check_symbol_directory_message();
  check_order_executed_message();
  check_order_executed_with_price_size_message();
  check_auction_info_message();
  check_top_of_book_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
