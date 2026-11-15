// jse/itac/marketdata/Jse_Itac_MarketData_v4_07.c
/*
 * JSE Limited Market Data
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

/* Jse Mitch Udp Unit Header */
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

/* Jse Mitch Udp Message Header */
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

/* ---- Login Request Message: 16 bytes ----------------------------------------- */

/* Sent by the client to log in to the market data gateway. */
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

/* ---- Replay Request Message: 7 bytes ----------------------------------------- */

/* Sent by the client on the replay channel to request retransmission of a range of messages. */
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

/* ---- Login Response Message: 1 byte ------------------------------------------ */

/* Sent by the server in response to a Login Request. */
typedef struct {
  uint8_t status;  /* byte 0 */
} LoginResponseMessage;

/* any Login Response Message at all: every byte one the checker chooses */
static void any_login_response_message(LoginResponseMessage *record) {
  record->status = arbitrary();
}

/* Login Response Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_login_response_message(const LoginResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status;

  return at;
}

/* Login Response Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_login_response_message(LoginResponseMessage *record, const uint8_t *wire, size_t at) {
  record->status = wire[at++];

  return at;
}

/* what was read of Login Response Message is what was written, byte for byte */
static void equal_login_response_message(const LoginResponseMessage *read, const LoginResponseMessage *written) {
  assert(read->status == written->status);
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

/* ---- Replay Response Message: 8 bytes ---------------------------------------- */

/* Sent by the server in response to a Replay Request. */
typedef struct {
  uint8_t market_data_group;  /* byte 0 */
  uint8_t first_message[4];   /* bytes 1 to 4 */
  uint8_t count[2];           /* bytes 5 to 6 */
  uint8_t status;             /* byte 7 */
} ReplayResponseMessage;

/* any Replay Response Message at all: every byte one the checker chooses */
static void any_replay_response_message(ReplayResponseMessage *record) {
  record->market_data_group = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->first_message[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->count[i] = arbitrary(); }
  record->status = arbitrary();
}

/* Replay Response Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_replay_response_message(const ReplayResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_data_group;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_message[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->count[i]; }
  wire[at++] = record->status;

  return at;
}

/* Replay Response Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_replay_response_message(ReplayResponseMessage *record, const uint8_t *wire, size_t at) {
  record->market_data_group = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->first_message[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->count[i] = wire[at++]; }
  record->status = wire[at++];

  return at;
}

/* what was read of Replay Response Message is what was written, byte for byte */
static void equal_replay_response_message(const ReplayResponseMessage *read, const ReplayResponseMessage *written) {
  assert(read->market_data_group == written->market_data_group);
  for (size_t i = 0; i < 4; i++) { assert(read->first_message[i] == written->first_message[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->count[i] == written->count[i]); }
  assert(read->status == written->status);
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

/* ---- Snapshot Response Message: 14 bytes ------------------------------------- */

/* Sent by the server in response to a Snapshot Request. */
typedef struct {
  uint8_t sequence_number[4];  /* bytes 0 to 3 */
  uint8_t order_count[4];      /* bytes 4 to 7 */
  uint8_t status;              /* byte 8 */
  uint8_t snapshot_type;       /* byte 9 */
  uint8_t request_id[4];       /* bytes 10 to 13 */
} SnapshotResponseMessage;

/* any Snapshot Response Message at all: every byte one the checker chooses */
static void any_snapshot_response_message(SnapshotResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_count[i] = arbitrary(); }
  record->status = arbitrary();
  record->snapshot_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
}

/* Snapshot Response Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_response_message(const SnapshotResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_count[i]; }
  wire[at++] = record->status;
  wire[at++] = record->snapshot_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }

  return at;
}

/* Snapshot Response Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_response_message(SnapshotResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_count[i] = wire[at++]; }
  record->status = wire[at++];
  record->snapshot_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot Response Message is what was written, byte for byte */
static void equal_snapshot_response_message(const SnapshotResponseMessage *read, const SnapshotResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_count[i] == written->order_count[i]); }
  assert(read->status == written->status);
  assert(read->snapshot_type == written->snapshot_type);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
}

/* Snapshot Response Message: written and read back, then read and written back */
static void check_snapshot_response_message(void) {
  SnapshotResponseMessage sent;
  SnapshotResponseMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_snapshot_response_message(&sent);
  assert(encode_snapshot_response_message(&sent, wire, 0) == 14);
  assert(decode_snapshot_response_message(&got, wire, 0) == 14);
  equal_snapshot_response_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_response_message(&got, wire, 0) == 14);
  assert(encode_snapshot_response_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Time Message: 4 bytes --------------------------------------------------- */

/* Sent for every second in which at least one application message is generated. All subsequent messages carry a nanosecond offset from this time. */
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

/* Sent to signal the start and end of the trading day. */
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

/* ---- Order Deleted Message: 12 bytes ----------------------------------------- */

/* Sent when an order is removed from the order book. */
typedef struct {
  uint8_t nanosecond[4];  /* bytes 0 to 3 */
  uint8_t order_id[8];    /* bytes 4 to 11 */
} OrderDeletedMessage;

/* any Order Deleted Message at all: every byte one the checker chooses */
static void any_order_deleted_message(OrderDeletedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Order Deleted Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_order_deleted_message(const OrderDeletedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Order Deleted Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_order_deleted_message(OrderDeletedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Deleted Message is what was written, byte for byte */
static void equal_order_deleted_message(const OrderDeletedMessage *read, const OrderDeletedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Order Deleted Message: written and read back, then read and written back */
static void check_order_deleted_message(void) {
  OrderDeletedMessage sent;
  OrderDeletedMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_order_deleted_message(&sent);
  assert(encode_order_deleted_message(&sent, wire, 0) == 12);
  assert(decode_order_deleted_message(&got, wire, 0) == 12);
  equal_order_deleted_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_order_deleted_message(&got, wire, 0) == 12);
  assert(encode_order_deleted_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book Clear Message: 10 bytes -------------------------------------- */

/* Sent to instruct the recipient to discard every order held for an instrument on the named book. */
typedef struct {
  uint8_t nanosecond[4];     /* bytes 0 to 3 */
  uint8_t instrument_id[4];  /* bytes 4 to 7 */
  uint8_t sub_book;          /* byte 8 */
  uint8_t book_level;        /* byte 9 */
} OrderBookClearMessage;

/* any Order Book Clear Message at all: every byte one the checker chooses */
static void any_order_book_clear_message(OrderBookClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->sub_book = arbitrary();
  record->book_level = arbitrary();
}

/* Order Book Clear Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_order_book_clear_message(const OrderBookClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->sub_book;
  wire[at++] = record->book_level;

  return at;
}

/* Order Book Clear Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_order_book_clear_message(OrderBookClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->sub_book = wire[at++];
  record->book_level = wire[at++];

  return at;
}

/* what was read of Order Book Clear Message is what was written, byte for byte */
static void equal_order_book_clear_message(const OrderBookClearMessage *read, const OrderBookClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->sub_book == written->sub_book);
  assert(read->book_level == written->book_level);
}

/* Order Book Clear Message: written and read back, then read and written back */
static void check_order_book_clear_message(void) {
  OrderBookClearMessage sent;
  OrderBookClearMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_order_book_clear_message(&sent);
  assert(encode_order_book_clear_message(&sent, wire, 0) == 10);
  assert(decode_order_book_clear_message(&got, wire, 0) == 10);
  equal_order_book_clear_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_clear_message(&got, wire, 0) == 10);
  assert(encode_order_book_clear_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 52 bytes ---------------------------------------- */

/* Sent when an order on the book executes in full or in part at its display price. */
typedef struct {
  uint8_t nanosecond[4];                  /* bytes 0 to 3 */
  uint8_t order_id[8];                    /* bytes 4 to 11 */
  uint8_t executed_quantity[4];           /* bytes 12 to 15 */
  uint8_t trade_id[8];                    /* bytes 16 to 23 */
  uint8_t last_opt_px[8];                 /* bytes 24 to 31 */
  uint8_t volatility[8];                  /* bytes 32 to 39 */
  uint8_t underlying_reference_price[8];  /* bytes 40 to 47 */
  uint8_t venue_of_execution[4];          /* bytes 48 to 51 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_opt_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying_reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_of_execution[i]; }

  return at;
}

/* Order Executed Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_opt_px[i] == written->last_opt_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->underlying_reference_price[i] == written->underlying_reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->venue_of_execution[i] == written->venue_of_execution[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 52);
  assert(decode_order_executed_message(&got, wire, 0) == 52);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 52);
  assert(encode_order_executed_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed With Price Size Message: 65 bytes ------------------------ */

/* Sent when an order on the book executes at a price other than its display price, or when the execution is not printable. */
typedef struct {
  uint8_t nanosecond[4];                  /* bytes 0 to 3 */
  uint8_t order_id[8];                    /* bytes 4 to 11 */
  uint8_t executed_quantity[4];           /* bytes 12 to 15 */
  uint8_t display_quantity[4];            /* bytes 16 to 19 */
  uint8_t trade_id[8];                    /* bytes 20 to 27 */
  uint8_t printable;                      /* byte 28 */
  uint8_t price[8];                       /* bytes 29 to 36 */
  uint8_t last_opt_px[8];                 /* bytes 37 to 44 */
  uint8_t volatility[8];                  /* bytes 45 to 52 */
  uint8_t underlying_reference_price[8];  /* bytes 53 to 60 */
  uint8_t venue_of_execution[4];          /* bytes 61 to 64 */
} OrderExecutedWithPriceSizeMessage;

/* any Order Executed With Price Size Message at all: every byte one the checker chooses */
static void any_order_executed_with_price_size_message(OrderExecutedWithPriceSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = arbitrary(); }
}

/* Order Executed With Price Size Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_with_price_size_message(const OrderExecutedWithPriceSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_opt_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying_reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_of_execution[i]; }

  return at;
}

/* Order Executed With Price Size Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_with_price_size_message(OrderExecutedWithPriceSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed With Price Size Message is what was written, byte for byte */
static void equal_order_executed_with_price_size_message(const OrderExecutedWithPriceSizeMessage *read, const OrderExecutedWithPriceSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_quantity[i] == written->display_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->printable == written->printable);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_opt_px[i] == written->last_opt_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->underlying_reference_price[i] == written->underlying_reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->venue_of_execution[i] == written->venue_of_execution[i]); }
}

/* Order Executed With Price Size Message: written and read back, then read and written back */
static void check_order_executed_with_price_size_message(void) {
  OrderExecutedWithPriceSizeMessage sent;
  OrderExecutedWithPriceSizeMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_order_executed_with_price_size_message(&sent);
  assert(encode_order_executed_with_price_size_message(&sent, wire, 0) == 65);
  assert(decode_order_executed_with_price_size_message(&got, wire, 0) == 65);
  equal_order_executed_with_price_size_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_with_price_size_message(&got, wire, 0) == 65);
  assert(encode_order_executed_with_price_size_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Trade Message: 67 bytes ----------------------------------------- */

/* Sent for a trade that results from an auction uncrossing. */
typedef struct {
  uint8_t nanosecond[4];                  /* bytes 0 to 3 */
  uint8_t quantity[4];                    /* bytes 4 to 7 */
  uint8_t instrument_id[4];               /* bytes 8 to 11 */
  uint8_t reserved_a;                     /* byte 12 */
  uint8_t reserved_b;                     /* byte 13 */
  uint8_t price[8];                       /* bytes 14 to 21 */
  uint8_t trade_id[8];                    /* bytes 22 to 29 */
  uint8_t auction_type;                   /* byte 30 */
  uint8_t last_opt_px[8];                 /* bytes 31 to 38 */
  uint8_t volatility[8];                  /* bytes 39 to 46 */
  uint8_t underlying_reference_price[8];  /* bytes 47 to 54 */
  uint8_t pt_cancellation_flag[4];        /* bytes 55 to 58 */
  uint8_t pt_amendment_flag[4];           /* bytes 59 to 62 */
  uint8_t venue_of_execution[4];          /* bytes 63 to 66 */
} AuctionTradeMessage;

/* any Auction Trade Message at all: every byte one the checker chooses */
static void any_auction_trade_message(AuctionTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->reserved_a = arbitrary();
  record->reserved_b = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_cancellation_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_amendment_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = arbitrary(); }
}

/* Auction Trade Message to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_auction_trade_message(const AuctionTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->reserved_a;
  wire[at++] = record->reserved_b;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_opt_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying_reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_cancellation_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_amendment_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_of_execution[i]; }

  return at;
}

/* Auction Trade Message off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_auction_trade_message(AuctionTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->reserved_a = wire[at++];
  record->reserved_b = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_cancellation_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_amendment_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Trade Message is what was written, byte for byte */
static void equal_auction_trade_message(const AuctionTradeMessage *read, const AuctionTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->reserved_a == written->reserved_a);
  assert(read->reserved_b == written->reserved_b);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->last_opt_px[i] == written->last_opt_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->underlying_reference_price[i] == written->underlying_reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_cancellation_flag[i] == written->pt_cancellation_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_amendment_flag[i] == written->pt_amendment_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->venue_of_execution[i] == written->venue_of_execution[i]); }
}

/* Auction Trade Message: written and read back, then read and written back */
static void check_auction_trade_message(void) {
  AuctionTradeMessage sent;
  AuctionTradeMessage got;
  uint8_t wire[67];
  uint8_t again[67];

  any_auction_trade_message(&sent);
  assert(encode_auction_trade_message(&sent, wire, 0) == 67);
  assert(decode_auction_trade_message(&got, wire, 0) == 67);
  equal_auction_trade_message(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_trade_message(&got, wire, 0) == 67);
  assert(encode_auction_trade_message(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Off Book Trade Message: 78 bytes ---------------------------------------- */

/* Sent for a trade agreed away from the order book and reported to the exchange. */
typedef struct {
  uint8_t nanosecond[4];                  /* bytes 0 to 3 */
  uint8_t executed_quantity[4];           /* bytes 4 to 7 */
  uint8_t instrument_id[4];               /* bytes 8 to 11 */
  uint8_t reserved_a;                     /* byte 12 */
  uint8_t reserved_b;                     /* byte 13 */
  uint8_t price[8];                       /* bytes 14 to 21 */
  uint8_t trade_id[8];                    /* bytes 22 to 29 */
  uint8_t off_book_trade_type[4];         /* bytes 30 to 33 */
  uint8_t trade_time[8];                  /* bytes 34 to 41 */
  uint8_t trade_date[8];                  /* bytes 42 to 49 */
  uint8_t last_opt_px[8];                 /* bytes 50 to 57 */
  uint8_t volatility[8];                  /* bytes 58 to 65 */
  uint8_t underlying_reference_price[8];  /* bytes 66 to 73 */
  uint8_t pt_cancellation_flag[4];        /* bytes 74 to 77 */
} OffBookTradeMessage;

/* any Off Book Trade Message at all: every byte one the checker chooses */
static void any_off_book_trade_message(OffBookTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->reserved_a = arbitrary();
  record->reserved_b = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->off_book_trade_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_cancellation_flag[i] = arbitrary(); }
}

/* Off Book Trade Message to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_off_book_trade_message(const OffBookTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->reserved_a;
  wire[at++] = record->reserved_b;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->off_book_trade_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_opt_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying_reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_cancellation_flag[i]; }

  return at;
}

/* Off Book Trade Message off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_off_book_trade_message(OffBookTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->reserved_a = wire[at++];
  record->reserved_b = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->off_book_trade_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_cancellation_flag[i] = wire[at++]; }

  return at;
}

/* what was read of Off Book Trade Message is what was written, byte for byte */
static void equal_off_book_trade_message(const OffBookTradeMessage *read, const OffBookTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->reserved_a == written->reserved_a);
  assert(read->reserved_b == written->reserved_b);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->off_book_trade_type[i] == written->off_book_trade_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_opt_px[i] == written->last_opt_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->underlying_reference_price[i] == written->underlying_reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_cancellation_flag[i] == written->pt_cancellation_flag[i]); }
}

/* Off Book Trade Message: written and read back, then read and written back */
static void check_off_book_trade_message(void) {
  OffBookTradeMessage sent;
  OffBookTradeMessage got;
  uint8_t wire[78];
  uint8_t again[78];

  any_off_book_trade_message(&sent);
  assert(encode_off_book_trade_message(&sent, wire, 0) == 78);
  assert(decode_off_book_trade_message(&got, wire, 0) == 78);
  equal_off_book_trade_message(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_off_book_trade_message(&got, wire, 0) == 78);
  assert(encode_off_book_trade_message(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Info Message: 28 bytes ------------------------------------------ */

/* Disseminates the indicative price and paired quantity of an instrument in an auction call. */
typedef struct {
  uint8_t nanosecond[4];        /* bytes 0 to 3 */
  uint8_t paired_quantity[4];   /* bytes 4 to 7 */
  uint8_t reserved_4[4];        /* bytes 8 to 11 */
  uint8_t imbalance_direction;  /* byte 12 */
  uint8_t instrument_id[4];     /* bytes 13 to 16 */
  uint8_t reserved_a;           /* byte 17 */
  uint8_t reserved_b;           /* byte 18 */
  uint8_t price[8];             /* bytes 19 to 26 */
  uint8_t auction_type;         /* byte 27 */
} AuctionInfoMessage;

/* any Auction Info Message at all: every byte one the checker chooses */
static void any_auction_info_message(AuctionInfoMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->paired_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  record->imbalance_direction = arbitrary();
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
  wire[at++] = record->imbalance_direction;
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
  record->imbalance_direction = wire[at++];
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
  assert(read->imbalance_direction == written->imbalance_direction);
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

/* ---- Statistics Message: 21 bytes -------------------------------------------- */

/* Disseminates the opening or closing price of an instrument. */
typedef struct {
  uint8_t nanosecond[4];         /* bytes 0 to 3 */
  uint8_t instrument_id[4];      /* bytes 4 to 7 */
  uint8_t reserved_a;            /* byte 8 */
  uint8_t reserved_b;            /* byte 9 */
  uint8_t statistic_type;        /* byte 10 */
  uint8_t price[8];              /* bytes 11 to 18 */
  uint8_t open_close_indicator;  /* byte 19 */
  uint8_t sub_book;              /* byte 20 */
} StatisticsMessage;

/* any Statistics Message at all: every byte one the checker chooses */
static void any_statistics_message(StatisticsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->reserved_a = arbitrary();
  record->reserved_b = arbitrary();
  record->statistic_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->open_close_indicator = arbitrary();
  record->sub_book = arbitrary();
}

/* Statistics Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_statistics_message(const StatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->reserved_a;
  wire[at++] = record->reserved_b;
  wire[at++] = record->statistic_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->open_close_indicator;
  wire[at++] = record->sub_book;

  return at;
}

/* Statistics Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_statistics_message(StatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->reserved_a = wire[at++];
  record->reserved_b = wire[at++];
  record->statistic_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->open_close_indicator = wire[at++];
  record->sub_book = wire[at++];

  return at;
}

/* what was read of Statistics Message is what was written, byte for byte */
static void equal_statistics_message(const StatisticsMessage *read, const StatisticsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->reserved_a == written->reserved_a);
  assert(read->reserved_b == written->reserved_b);
  assert(read->statistic_type == written->statistic_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->open_close_indicator == written->open_close_indicator);
  assert(read->sub_book == written->sub_book);
}

/* Statistics Message: written and read back, then read and written back */
static void check_statistics_message(void) {
  StatisticsMessage sent;
  StatisticsMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_statistics_message(&sent);
  assert(encode_statistics_message(&sent, wire, 0) == 21);
  assert(decode_statistics_message(&got, wire, 0) == 21);
  equal_statistics_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_statistics_message(&got, wire, 0) == 21);
  assert(encode_statistics_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Extended Statistics Message: 137 bytes ---------------------------------- */

/* Disseminates the intraday statistics of an instrument. Values that are not set or have been withdrawn are negative, except Volume and Number of Trades which are zero. */
typedef struct {
  uint8_t nanosecond[4];               /* bytes 0 to 3 */
  uint8_t instrument_id[4];            /* bytes 4 to 7 */
  uint8_t high_price[8];               /* bytes 8 to 15 */
  uint8_t low_price[8];                /* bytes 16 to 23 */
  uint8_t vwap[8];                     /* bytes 24 to 31 */
  uint8_t volume[4];                   /* bytes 32 to 35 */
  uint8_t turnover[8];                 /* bytes 36 to 43 */
  uint8_t number_of_trades[4];         /* bytes 44 to 47 */
  uint8_t reserved_8[8];               /* bytes 48 to 55 */
  uint8_t sub_book;                    /* byte 56 */
  uint8_t notional_exposure[8];        /* bytes 57 to 64 */
  uint8_t notional_delta_exposure[8];  /* bytes 65 to 72 */
  uint8_t open_interest[8];            /* bytes 73 to 80 */
  uint8_t theoretical_price[8];        /* bytes 81 to 88 */
  uint8_t delta[8];                    /* bytes 89 to 96 */
  uint8_t gamma[8];                    /* bytes 97 to 104 */
  uint8_t vega[8];                     /* bytes 105 to 112 */
  uint8_t theta[8];                    /* bytes 113 to 120 */
  uint8_t rho[8];                      /* bytes 121 to 128 */
  uint8_t volatility[8];               /* bytes 129 to 136 */
} ExtendedStatisticsMessage;

/* any Extended Statistics Message at all: every byte one the checker chooses */
static void any_extended_statistics_message(ExtendedStatisticsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  record->sub_book = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->notional_exposure[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->notional_delta_exposure[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->theoretical_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->delta[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->gamma[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vega[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->theta[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->rho[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
}

/* Extended Statistics Message to the wire: 137 bytes from at, returning where the next byte goes */
static size_t encode_extended_statistics_message(const ExtendedStatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  wire[at++] = record->sub_book;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notional_exposure[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notional_delta_exposure[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_interest[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->theoretical_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->delta[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->gamma[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vega[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->theta[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->rho[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }

  return at;
}

/* Extended Statistics Message off the wire: 137 bytes from at, returning where the next byte lies */
static size_t decode_extended_statistics_message(ExtendedStatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  record->sub_book = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->notional_exposure[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->notional_delta_exposure[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->theoretical_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->delta[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->gamma[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vega[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->theta[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->rho[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }

  return at;
}

/* what was read of Extended Statistics Message is what was written, byte for byte */
static void equal_extended_statistics_message(const ExtendedStatisticsMessage *read, const ExtendedStatisticsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_trades[i] == written->number_of_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  assert(read->sub_book == written->sub_book);
  for (size_t i = 0; i < 8; i++) { assert(read->notional_exposure[i] == written->notional_exposure[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->notional_delta_exposure[i] == written->notional_delta_exposure[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->theoretical_price[i] == written->theoretical_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->delta[i] == written->delta[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->gamma[i] == written->gamma[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vega[i] == written->vega[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->theta[i] == written->theta[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->rho[i] == written->rho[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
}

/* Extended Statistics Message: written and read back, then read and written back */
static void check_extended_statistics_message(void) {
  ExtendedStatisticsMessage sent;
  ExtendedStatisticsMessage got;
  uint8_t wire[137];
  uint8_t again[137];

  any_extended_statistics_message(&sent);
  assert(encode_extended_statistics_message(&sent, wire, 0) == 137);
  assert(decode_extended_statistics_message(&got, wire, 0) == 137);
  equal_extended_statistics_message(&got, &sent);

  for (size_t i = 0; i < 137; i++) { wire[i] = arbitrary(); }
  assert(decode_extended_statistics_message(&got, wire, 0) == 137);
  assert(encode_extended_statistics_message(&got, again, 0) == 137);
  for (size_t i = 0; i < 137; i++) { assert(again[i] == wire[i]); }
}

/* ---- News Message: 1063 bytes ------------------------------------------------ */

/* Carries an exchange announcement and the instruments it relates to. */
typedef struct {
  uint8_t nanosecond[4];     /* bytes 0 to 3 */
  uint8_t time[8];           /* bytes 4 to 11 */
  uint8_t urgency;           /* byte 12 */
  uint8_t headline[100];     /* bytes 13 to 112 */
  uint8_t text[750];         /* bytes 113 to 862 */
  uint8_t instruments[100];  /* bytes 863 to 962 */
  uint8_t underlyings[100];  /* bytes 963 to 1062 */
} NewsMessage;

/* any News Message at all: every byte one the checker chooses */
static void any_news_message(NewsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time[i] = arbitrary(); }
  record->urgency = arbitrary();
  for (size_t i = 0; i < 100; i++) { record->headline[i] = arbitrary(); }
  for (size_t i = 0; i < 750; i++) { record->text[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->instruments[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->underlyings[i] = arbitrary(); }
}

/* News Message to the wire: 1063 bytes from at, returning where the next byte goes */
static size_t encode_news_message(const NewsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time[i]; }
  wire[at++] = record->urgency;
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->headline[i]; }
  for (size_t i = 0; i < 750; i++) { wire[at++] = record->text[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->instruments[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->underlyings[i]; }

  return at;
}

/* News Message off the wire: 1063 bytes from at, returning where the next byte lies */
static size_t decode_news_message(NewsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time[i] = wire[at++]; }
  record->urgency = wire[at++];
  for (size_t i = 0; i < 100; i++) { record->headline[i] = wire[at++]; }
  for (size_t i = 0; i < 750; i++) { record->text[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->instruments[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->underlyings[i] = wire[at++]; }

  return at;
}

/* what was read of News Message is what was written, byte for byte */
static void equal_news_message(const NewsMessage *read, const NewsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time[i] == written->time[i]); }
  assert(read->urgency == written->urgency);
  for (size_t i = 0; i < 100; i++) { assert(read->headline[i] == written->headline[i]); }
  for (size_t i = 0; i < 750; i++) { assert(read->text[i] == written->text[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->instruments[i] == written->instruments[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->underlyings[i] == written->underlyings[i]); }
}

/* News Message: written and read back, then read and written back */
static void check_news_message(void) {
  NewsMessage sent;
  NewsMessage got;
  uint8_t wire[1063];
  uint8_t again[1063];

  any_news_message(&sent);
  assert(encode_news_message(&sent, wire, 0) == 1063);
  assert(decode_news_message(&got, wire, 0) == 1063);
  equal_news_message(&got, &sent);

  for (size_t i = 0; i < 1063; i++) { wire[i] = arbitrary(); }
  assert(decode_news_message(&got, wire, 0) == 1063);
  assert(encode_news_message(&got, again, 0) == 1063);
  for (size_t i = 0; i < 1063; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indicative Quote Info Message: 34 bytes --------------------------------- */

/* Disseminates the indicative bid and offer of a request for quote. */
typedef struct {
  uint8_t nanosecond[4];              /* bytes 0 to 3 */
  uint8_t instrument_id[4];           /* bytes 4 to 7 */
  uint8_t rfq_id[10];                 /* bytes 8 to 17 */
  uint8_t indicative_bid_price[8];    /* bytes 18 to 25 */
  uint8_t indicative_offer_price[8];  /* bytes 26 to 33 */
} IndicativeQuoteInfoMessage;

/* any Indicative Quote Info Message at all: every byte one the checker chooses */
static void any_indicative_quote_info_message(IndicativeQuoteInfoMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->rfq_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_offer_price[i] = arbitrary(); }
}

/* Indicative Quote Info Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_indicative_quote_info_message(const IndicativeQuoteInfoMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->rfq_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_bid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_offer_price[i]; }

  return at;
}

/* Indicative Quote Info Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_indicative_quote_info_message(IndicativeQuoteInfoMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->rfq_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_offer_price[i] = wire[at++]; }

  return at;
}

/* what was read of Indicative Quote Info Message is what was written, byte for byte */
static void equal_indicative_quote_info_message(const IndicativeQuoteInfoMessage *read, const IndicativeQuoteInfoMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->rfq_id[i] == written->rfq_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_bid_price[i] == written->indicative_bid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_offer_price[i] == written->indicative_offer_price[i]); }
}

/* Indicative Quote Info Message: written and read back, then read and written back */
static void check_indicative_quote_info_message(void) {
  IndicativeQuoteInfoMessage sent;
  IndicativeQuoteInfoMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_indicative_quote_info_message(&sent);
  assert(encode_indicative_quote_info_message(&sent, wire, 0) == 34);
  assert(decode_indicative_quote_info_message(&got, wire, 0) == 34);
  equal_indicative_quote_info_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_indicative_quote_info_message(&got, wire, 0) == 34);
  assert(encode_indicative_quote_info_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
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
  check_snapshot_response_message();
  check_time_message();
  check_system_event_message();
  check_order_deleted_message();
  check_order_book_clear_message();
  check_order_executed_message();
  check_order_executed_with_price_size_message();
  check_auction_trade_message();
  check_off_book_trade_message();
  check_auction_info_message();
  check_statistics_message();
  check_extended_statistics_message();
  check_news_message();
  check_indicative_quote_info_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
