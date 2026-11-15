// nairobi/nairobiequities/replay/NairobiEquities_Replay_v1_22.c
/*
 * Nairobi Securities Exchange Nairobi Equities Replay
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

/* Nairobi Mitch Unit Header, defining the length of a unit, its message count, market data group and first sequence number */
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

/* Nairobi Mitch Tcp Message Header */
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

/* Used by the client to login to the Replay or Snapshot channel. */
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

/* Used by the server to accept or reject a login request to the Replay or Snapshot channel. */
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

/* Used by the client to request a retransmission of messages on the Replay channel. */
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

/* Used by the server to respond to a retransmission request on the Replay channel. */
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

/* Sent by the server for every second for which at least one application message is generated; its time is the reference for the nanosecond offsets of every other application message. */
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

/* ---- Order Deleted Message: 12 bytes ----------------------------------------- */

/* Sent to indicate that the remainder of a displayed order is cancelled. */
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

/* ---- Order Book Clear Message: 18 bytes -------------------------------------- */

/* Sent to instruct recipients to remove all orders from the order book for the specified instrument. */
typedef struct {
  uint8_t nanosecond[4];  /* bytes 0 to 3 */
  uint8_t symbol[12];     /* bytes 4 to 15 */
  uint8_t sub_book;       /* byte 16 */
  uint8_t book_type;      /* byte 17 */
} OrderBookClearMessage;

/* any Order Book Clear Message at all: every byte one the checker chooses */
static void any_order_book_clear_message(OrderBookClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  record->sub_book = arbitrary();
  record->book_type = arbitrary();
}

/* Order Book Clear Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_order_book_clear_message(const OrderBookClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->sub_book;
  wire[at++] = record->book_type;

  return at;
}

/* Order Book Clear Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_order_book_clear_message(OrderBookClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  record->sub_book = wire[at++];
  record->book_type = wire[at++];

  return at;
}

/* what was read of Order Book Clear Message is what was written, byte for byte */
static void equal_order_book_clear_message(const OrderBookClearMessage *read, const OrderBookClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->sub_book == written->sub_book);
  assert(read->book_type == written->book_type);
}

/* Order Book Clear Message: written and read back, then read and written back */
static void check_order_book_clear_message(void) {
  OrderBookClearMessage sent;
  OrderBookClearMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_order_book_clear_message(&sent);
  assert(encode_order_book_clear_message(&sent, wire, 0) == 18);
  assert(decode_order_book_clear_message(&got, wire, 0) == 18);
  equal_order_book_clear_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_clear_message(&got, wire, 0) == 18);
  assert(encode_order_book_clear_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 60 bytes ---------------------------------------- */

/* Indicates that the displayed portion of an order is fully or partially filled at its displayed price. The executed quantity is included in the message. */
typedef struct {
  uint8_t nanosecond[4];                  /* bytes 0 to 3 */
  uint8_t order_id[8];                    /* bytes 4 to 11 */
  uint8_t executed_quantity[4];           /* bytes 12 to 15 */
  uint8_t trade_id[8];                    /* bytes 16 to 23 */
  uint8_t buy_firm[6];                    /* bytes 24 to 29 */
  uint8_t sell_firm[6];                   /* bytes 30 to 35 */
  uint8_t last_opt_px[8];                 /* bytes 36 to 43 */
  uint8_t volatility[8];                  /* bytes 44 to 51 */
  uint8_t underlying_reference_price[8];  /* bytes 52 to 59 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->buy_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->sell_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->buy_firm[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->sell_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_opt_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying_reference_price[i]; }

  return at;
}

/* Order Executed Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->buy_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->sell_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->buy_firm[i] == written->buy_firm[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->sell_firm[i] == written->sell_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_opt_px[i] == written->last_opt_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->underlying_reference_price[i] == written->underlying_reference_price[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 60);
  assert(decode_order_executed_message(&got, wire, 0) == 60);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 60);
  assert(encode_order_executed_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed With Price Size Message: 69 bytes ------------------------ */

/* Sent if a displayed order is fully or partially filled at a price that is different from its displayed price, with an indication of whether the trade should update time and sales and statistics displays. */
typedef struct {
  uint8_t nanosecond[4];                  /* bytes 0 to 3 */
  uint8_t order_id[8];                    /* bytes 4 to 11 */
  uint8_t executed_quantity[4];           /* bytes 12 to 15 */
  uint8_t display_quantity[4];            /* bytes 16 to 19 */
  uint8_t trade_id[8];                    /* bytes 20 to 27 */
  uint8_t printable;                      /* byte 28 */
  uint8_t price[4];                       /* bytes 29 to 32 */
  uint8_t buy_firm[6];                    /* bytes 33 to 38 */
  uint8_t sell_firm[6];                   /* bytes 39 to 44 */
  uint8_t last_opt_px[8];                 /* bytes 45 to 52 */
  uint8_t volatility[8];                  /* bytes 53 to 60 */
  uint8_t underlying_reference_price[8];  /* bytes 61 to 68 */
} OrderExecutedWithPriceSizeMessage;

/* any Order Executed With Price Size Message at all: every byte one the checker chooses */
static void any_order_executed_with_price_size_message(OrderExecutedWithPriceSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->buy_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->sell_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = arbitrary(); }
}

/* Order Executed With Price Size Message to the wire: 69 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_with_price_size_message(const OrderExecutedWithPriceSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->buy_firm[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->sell_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_opt_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying_reference_price[i]; }

  return at;
}

/* Order Executed With Price Size Message off the wire: 69 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_with_price_size_message(OrderExecutedWithPriceSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->buy_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->sell_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = wire[at++]; }

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
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->buy_firm[i] == written->buy_firm[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->sell_firm[i] == written->sell_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_opt_px[i] == written->last_opt_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->underlying_reference_price[i] == written->underlying_reference_price[i]); }
}

/* Order Executed With Price Size Message: written and read back, then read and written back */
static void check_order_executed_with_price_size_message(void) {
  OrderExecutedWithPriceSizeMessage sent;
  OrderExecutedWithPriceSizeMessage got;
  uint8_t wire[69];
  uint8_t again[69];

  any_order_executed_with_price_size_message(&sent);
  assert(encode_order_executed_with_price_size_message(&sent, wire, 0) == 69);
  assert(decode_order_executed_with_price_size_message(&got, wire, 0) == 69);
  equal_order_executed_with_price_size_message(&got, &sent);

  for (size_t i = 0; i < 69; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_with_price_size_message(&got, wire, 0) == 69);
  assert(encode_order_executed_with_price_size_message(&got, again, 0) == 69);
  for (size_t i = 0; i < 69; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 69 bytes ------------------------------------------------- */

/* Sent if the non-displayed portion of an iceberg order or a reserve order is fully or partially filled, or if the negotiated non-disclosed order in the block trade order book is executed. */
typedef struct {
  uint8_t nanosecond[4];                  /* bytes 0 to 3 */
  uint8_t executed_quantity[4];           /* bytes 4 to 7 */
  uint8_t symbol[12];                     /* bytes 8 to 19 */
  uint8_t price[4];                       /* bytes 20 to 23 */
  uint8_t trade_id[8];                    /* bytes 24 to 31 */
  uint8_t sub_book;                       /* byte 32 */
  uint8_t buy_firm[6];                    /* bytes 33 to 38 */
  uint8_t sell_firm[6];                   /* bytes 39 to 44 */
  uint8_t last_opt_px[8];                 /* bytes 45 to 52 */
  uint8_t volatility[8];                  /* bytes 53 to 60 */
  uint8_t underlying_reference_price[8];  /* bytes 61 to 68 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  record->sub_book = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->buy_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->sell_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = arbitrary(); }
}

/* Trade Message to the wire: 69 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->sub_book;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->buy_firm[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->sell_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_opt_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying_reference_price[i]; }

  return at;
}

/* Trade Message off the wire: 69 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  record->sub_book = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->buy_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->sell_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->sub_book == written->sub_book);
  for (size_t i = 0; i < 6; i++) { assert(read->buy_firm[i] == written->buy_firm[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->sell_firm[i] == written->sell_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_opt_px[i] == written->last_opt_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->underlying_reference_price[i] == written->underlying_reference_price[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[69];
  uint8_t again[69];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 69);
  assert(decode_trade_message(&got, wire, 0) == 69);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 69; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 69);
  assert(encode_trade_message(&got, again, 0) == 69);
  for (size_t i = 0; i < 69; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Trade Message: 57 bytes ----------------------------------------- */

/* Sent to report details of an auction (e.g. opening, closing, intra-day, etc.). */
typedef struct {
  uint8_t nanosecond[4];                  /* bytes 0 to 3 */
  uint8_t executed_quantity[4];           /* bytes 4 to 7 */
  uint8_t symbol[12];                     /* bytes 8 to 19 */
  uint8_t price[4];                       /* bytes 20 to 23 */
  uint8_t trade_id[8];                    /* bytes 24 to 31 */
  uint8_t auction_type;                   /* byte 32 */
  uint8_t last_opt_px[8];                 /* bytes 33 to 40 */
  uint8_t volatility[8];                  /* bytes 41 to 48 */
  uint8_t underlying_reference_price[8];  /* bytes 49 to 56 */
} AuctionTradeMessage;

/* any Auction Trade Message at all: every byte one the checker chooses */
static void any_auction_trade_message(AuctionTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = arbitrary(); }
}

/* Auction Trade Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_auction_trade_message(const AuctionTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_opt_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying_reference_price[i]; }

  return at;
}

/* Auction Trade Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_auction_trade_message(AuctionTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Trade Message is what was written, byte for byte */
static void equal_auction_trade_message(const AuctionTradeMessage *read, const AuctionTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->last_opt_px[i] == written->last_opt_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->underlying_reference_price[i] == written->underlying_reference_price[i]); }
}

/* Auction Trade Message: written and read back, then read and written back */
static void check_auction_trade_message(void) {
  AuctionTradeMessage sent;
  AuctionTradeMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_auction_trade_message(&sent);
  assert(encode_auction_trade_message(&sent, wire, 0) == 57);
  assert(decode_auction_trade_message(&got, wire, 0) == 57);
  equal_auction_trade_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_trade_message(&got, wire, 0) == 57);
  assert(encode_auction_trade_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Off Book Trade Message: 76 bytes ---------------------------------------- */

/* Sent to report the details of an off-book trade. */
typedef struct {
  uint8_t nanosecond[4];                  /* bytes 0 to 3 */
  uint8_t executed_quantity[4];           /* bytes 4 to 7 */
  uint8_t symbol[12];                     /* bytes 8 to 19 */
  uint8_t price[4];                       /* bytes 20 to 23 */
  uint8_t trade_id[8];                    /* bytes 24 to 31 */
  uint8_t off_book_trade_type[4];         /* bytes 32 to 35 */
  uint8_t trade_time[8];                  /* bytes 36 to 43 */
  uint8_t trade_date[8];                  /* bytes 44 to 51 */
  uint8_t last_opt_px[8];                 /* bytes 52 to 59 */
  uint8_t volatility[8];                  /* bytes 60 to 67 */
  uint8_t underlying_reference_price[8];  /* bytes 68 to 75 */
} OffBookTradeMessage;

/* any Off Book Trade Message at all: every byte one the checker chooses */
static void any_off_book_trade_message(OffBookTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->off_book_trade_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = arbitrary(); }
}

/* Off Book Trade Message to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_off_book_trade_message(const OffBookTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->off_book_trade_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_opt_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying_reference_price[i]; }

  return at;
}

/* Off Book Trade Message off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_off_book_trade_message(OffBookTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->off_book_trade_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = wire[at++]; }

  return at;
}

/* what was read of Off Book Trade Message is what was written, byte for byte */
static void equal_off_book_trade_message(const OffBookTradeMessage *read, const OffBookTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->off_book_trade_type[i] == written->off_book_trade_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_opt_px[i] == written->last_opt_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->underlying_reference_price[i] == written->underlying_reference_price[i]); }
}

/* Off Book Trade Message: written and read back, then read and written back */
static void check_off_book_trade_message(void) {
  OffBookTradeMessage sent;
  OffBookTradeMessage got;
  uint8_t wire[76];
  uint8_t again[76];

  any_off_book_trade_message(&sent);
  assert(encode_off_book_trade_message(&sent, wire, 0) == 76);
  assert(decode_off_book_trade_message(&got, wire, 0) == 76);
  equal_off_book_trade_message(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_off_book_trade_message(&got, wire, 0) == 76);
  assert(encode_off_book_trade_message(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Break Message: 13 bytes ------------------------------------------- */

/* Sent to indicate that a previously reported trade is cancelled. */
typedef struct {
  uint8_t nanosecond[4];  /* bytes 0 to 3 */
  uint8_t trade_id[8];    /* bytes 4 to 11 */
  uint8_t trade_type;     /* byte 12 */
} TradeBreakMessage;

/* any Trade Break Message at all: every byte one the checker chooses */
static void any_trade_break_message(TradeBreakMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  record->trade_type = arbitrary();
}

/* Trade Break Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_trade_break_message(const TradeBreakMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->trade_type;

  return at;
}

/* Trade Break Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_trade_break_message(TradeBreakMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  record->trade_type = wire[at++];

  return at;
}

/* what was read of Trade Break Message is what was written, byte for byte */
static void equal_trade_break_message(const TradeBreakMessage *read, const TradeBreakMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->trade_type == written->trade_type);
}

/* Trade Break Message: written and read back, then read and written back */
static void check_trade_break_message(void) {
  TradeBreakMessage sent;
  TradeBreakMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_trade_break_message(&sent);
  assert(encode_trade_break_message(&sent, wire, 0) == 13);
  assert(decode_trade_break_message(&got, wire, 0) == 13);
  equal_trade_break_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_break_message(&got, wire, 0) == 13);
  assert(encode_trade_break_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 45 bytes -------------------------------------- */

/* Sent to report the correction of the executed quantity of a trade. */
typedef struct {
  uint8_t nanosecond[4];  /* bytes 0 to 3 */
  uint8_t trade_id[8];    /* bytes 4 to 11 */
  uint8_t symbol[12];     /* bytes 12 to 23 */
  uint8_t price[4];       /* bytes 24 to 27 */
  uint8_t quantity[4];    /* bytes 28 to 31 */
  uint8_t sub_book;       /* byte 32 */
  uint8_t buy_firm[6];    /* bytes 33 to 38 */
  uint8_t sell_firm[6];   /* bytes 39 to 44 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->sub_book = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->buy_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->sell_firm[i] = arbitrary(); }
}

/* Trade Correction Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->sub_book;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->buy_firm[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->sell_firm[i]; }

  return at;
}

/* Trade Correction Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->sub_book = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->buy_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->sell_firm[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->sub_book == written->sub_book);
  for (size_t i = 0; i < 6; i++) { assert(read->buy_firm[i] == written->buy_firm[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->sell_firm[i] == written->sell_firm[i]); }
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 45);
  assert(decode_trade_correction_message(&got, wire, 0) == 45);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 45);
  assert(encode_trade_correction_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Recovery Trade Message: 92 bytes ---------------------------------------- */

/* Sent on the Snapshot channel to retransmit the trades published on the Real-Time channel. */
typedef struct {
  uint8_t nanosecond[4];                  /* bytes 0 to 3 */
  uint8_t executed_quantity[4];           /* bytes 4 to 7 */
  uint8_t symbol[12];                     /* bytes 8 to 19 */
  uint8_t price[4];                       /* bytes 20 to 23 */
  uint8_t trade_id[8];                    /* bytes 24 to 31 */
  uint8_t auction_type;                   /* byte 32 */
  uint8_t off_book_trade_type[4];         /* bytes 33 to 36 */
  uint8_t trade_time[8];                  /* bytes 37 to 44 */
  uint8_t trade_date[8];                  /* bytes 45 to 52 */
  uint8_t action_type;                    /* byte 53 */
  uint8_t sub_book;                       /* byte 54 */
  uint8_t buy_firm[6];                    /* bytes 55 to 60 */
  uint8_t sell_firm[6];                   /* bytes 61 to 66 */
  uint8_t last_opt_px[8];                 /* bytes 67 to 74 */
  uint8_t volatility[8];                  /* bytes 75 to 82 */
  uint8_t underlying_reference_price[8];  /* bytes 83 to 90 */
  uint8_t auction_trade_type;             /* byte 91 */
} RecoveryTradeMessage;

/* any Recovery Trade Message at all: every byte one the checker chooses */
static void any_recovery_trade_message(RecoveryTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->off_book_trade_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  record->action_type = arbitrary();
  record->sub_book = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->buy_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->sell_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = arbitrary(); }
  record->auction_trade_type = arbitrary();
}

/* Recovery Trade Message to the wire: 92 bytes from at, returning where the next byte goes */
static size_t encode_recovery_trade_message(const RecoveryTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->off_book_trade_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  wire[at++] = record->action_type;
  wire[at++] = record->sub_book;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->buy_firm[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->sell_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_opt_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying_reference_price[i]; }
  wire[at++] = record->auction_trade_type;

  return at;
}

/* Recovery Trade Message off the wire: 92 bytes from at, returning where the next byte lies */
static size_t decode_recovery_trade_message(RecoveryTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->off_book_trade_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  record->action_type = wire[at++];
  record->sub_book = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->buy_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->sell_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_opt_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->underlying_reference_price[i] = wire[at++]; }
  record->auction_trade_type = wire[at++];

  return at;
}

/* what was read of Recovery Trade Message is what was written, byte for byte */
static void equal_recovery_trade_message(const RecoveryTradeMessage *read, const RecoveryTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->off_book_trade_type[i] == written->off_book_trade_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  assert(read->action_type == written->action_type);
  assert(read->sub_book == written->sub_book);
  for (size_t i = 0; i < 6; i++) { assert(read->buy_firm[i] == written->buy_firm[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->sell_firm[i] == written->sell_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_opt_px[i] == written->last_opt_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->underlying_reference_price[i] == written->underlying_reference_price[i]); }
  assert(read->auction_trade_type == written->auction_trade_type);
}

/* Recovery Trade Message: written and read back, then read and written back */
static void check_recovery_trade_message(void) {
  RecoveryTradeMessage sent;
  RecoveryTradeMessage got;
  uint8_t wire[92];
  uint8_t again[92];

  any_recovery_trade_message(&sent);
  assert(encode_recovery_trade_message(&sent, wire, 0) == 92);
  assert(decode_recovery_trade_message(&got, wire, 0) == 92);
  equal_recovery_trade_message(&got, &sent);

  for (size_t i = 0; i < 92; i++) { wire[i] = arbitrary(); }
  assert(decode_recovery_trade_message(&got, wire, 0) == 92);
  assert(encode_recovery_trade_message(&got, again, 0) == 92);
  for (size_t i = 0; i < 92; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Info Message: 30 bytes ------------------------------------------ */

/* Indicative auction information for an instrument; the document labels the message type Indicative Auction Info. */
typedef struct {
  uint8_t nanosecond[4];          /* bytes 0 to 3 */
  uint8_t paired_quantity[4];     /* bytes 4 to 7 */
  uint8_t imbalance_quantity[4];  /* bytes 8 to 11 */
  uint8_t imbalance_direction;    /* byte 12 */
  uint8_t symbol[12];             /* bytes 13 to 24 */
  uint8_t price[4];               /* bytes 25 to 28 */
  uint8_t auction_type;           /* byte 29 */
} AuctionInfoMessage;

/* any Auction Info Message at all: every byte one the checker chooses */
static void any_auction_info_message(AuctionInfoMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->paired_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->imbalance_quantity[i] = arbitrary(); }
  record->imbalance_direction = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->auction_type = arbitrary();
}

/* Auction Info Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_auction_info_message(const AuctionInfoMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->paired_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->imbalance_quantity[i]; }
  wire[at++] = record->imbalance_direction;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->auction_type;

  return at;
}

/* Auction Info Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_auction_info_message(AuctionInfoMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->paired_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->imbalance_quantity[i] = wire[at++]; }
  record->imbalance_direction = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->auction_type = wire[at++];

  return at;
}

/* what was read of Auction Info Message is what was written, byte for byte */
static void equal_auction_info_message(const AuctionInfoMessage *read, const AuctionInfoMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->paired_quantity[i] == written->paired_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->imbalance_quantity[i] == written->imbalance_quantity[i]); }
  assert(read->imbalance_direction == written->imbalance_direction);
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->auction_type == written->auction_type);
}

/* Auction Info Message: written and read back, then read and written back */
static void check_auction_info_message(void) {
  AuctionInfoMessage sent;
  AuctionInfoMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_auction_info_message(&sent);
  assert(encode_auction_info_message(&sent, wire, 0) == 30);
  assert(decode_auction_info_message(&got, wire, 0) == 30);
  equal_auction_info_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_info_message(&got, wire, 0) == 30);
  assert(encode_auction_info_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Statistics Message: 23 bytes -------------------------------------------- */

/* Sent to disseminate the opening, closing and previous closing prices of an instrument. */
typedef struct {
  uint8_t nanosecond[4];         /* bytes 0 to 3 */
  uint8_t symbol[12];            /* bytes 4 to 15 */
  uint8_t statistic_type;        /* byte 16 */
  uint8_t price[4];              /* bytes 17 to 20 */
  uint8_t open_close_indicator;  /* byte 21 */
  uint8_t sub_book;              /* byte 22 */
} StatisticsMessage;

/* any Statistics Message at all: every byte one the checker chooses */
static void any_statistics_message(StatisticsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  record->statistic_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->open_close_indicator = arbitrary();
  record->sub_book = arbitrary();
}

/* Statistics Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_statistics_message(const StatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->statistic_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->open_close_indicator;
  wire[at++] = record->sub_book;

  return at;
}

/* Statistics Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_statistics_message(StatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  record->statistic_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->open_close_indicator = wire[at++];
  record->sub_book = wire[at++];

  return at;
}

/* what was read of Statistics Message is what was written, byte for byte */
static void equal_statistics_message(const StatisticsMessage *read, const StatisticsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->statistic_type == written->statistic_type);
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->open_close_indicator == written->open_close_indicator);
  assert(read->sub_book == written->sub_book);
}

/* Statistics Message: written and read back, then read and written back */
static void check_statistics_message(void) {
  StatisticsMessage sent;
  StatisticsMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_statistics_message(&sent);
  assert(encode_statistics_message(&sent, wire, 0) == 23);
  assert(decode_statistics_message(&got, wire, 0) == 23);
  equal_statistics_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_statistics_message(&got, wire, 0) == 23);
  assert(encode_statistics_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Extended Statistics Message: 93 bytes ----------------------------------- */

/* Sent to disseminate the high, low, VWAP, volume, turnover and other statistics of an instrument for a sub book. */
typedef struct {
  uint8_t nanosecond[4];                /* bytes 0 to 3 */
  uint8_t symbol[12];                   /* bytes 4 to 15 */
  uint8_t high_price[4];                /* bytes 16 to 19 */
  uint8_t low_price[4];                 /* bytes 20 to 23 */
  uint8_t vwap[4];                      /* bytes 24 to 27 */
  uint8_t volume[4];                    /* bytes 28 to 31 */
  uint8_t turnover[8];                  /* bytes 32 to 39 */
  uint8_t trades[4];                    /* bytes 40 to 43 */
  uint8_t reserved_8[8];                /* bytes 44 to 51 */
  uint8_t sub_book;                     /* byte 52 */
  uint8_t notional_exposure[8];         /* bytes 53 to 60 */
  uint8_t notional_delta_exposure[8];   /* bytes 61 to 68 */
  uint8_t daily_foreign_buy_value[8];   /* bytes 69 to 76 */
  uint8_t daily_foreign_sell_value[8];  /* bytes 77 to 84 */
  uint8_t market_capitalization[8];     /* bytes 85 to 92 */
} ExtendedStatisticsMessage;

/* any Extended Statistics Message at all: every byte one the checker chooses */
static void any_extended_statistics_message(ExtendedStatisticsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  record->sub_book = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->notional_exposure[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->notional_delta_exposure[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->daily_foreign_buy_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->daily_foreign_sell_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_capitalization[i] = arbitrary(); }
}

/* Extended Statistics Message to the wire: 93 bytes from at, returning where the next byte goes */
static size_t encode_extended_statistics_message(const ExtendedStatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  wire[at++] = record->sub_book;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notional_exposure[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notional_delta_exposure[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->daily_foreign_buy_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->daily_foreign_sell_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_capitalization[i]; }

  return at;
}

/* Extended Statistics Message off the wire: 93 bytes from at, returning where the next byte lies */
static size_t decode_extended_statistics_message(ExtendedStatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  record->sub_book = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->notional_exposure[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->notional_delta_exposure[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->daily_foreign_buy_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->daily_foreign_sell_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_capitalization[i] = wire[at++]; }

  return at;
}

/* what was read of Extended Statistics Message is what was written, byte for byte */
static void equal_extended_statistics_message(const ExtendedStatisticsMessage *read, const ExtendedStatisticsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trades[i] == written->trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  assert(read->sub_book == written->sub_book);
  for (size_t i = 0; i < 8; i++) { assert(read->notional_exposure[i] == written->notional_exposure[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->notional_delta_exposure[i] == written->notional_delta_exposure[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->daily_foreign_buy_value[i] == written->daily_foreign_buy_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->daily_foreign_sell_value[i] == written->daily_foreign_sell_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_capitalization[i] == written->market_capitalization[i]); }
}

/* Extended Statistics Message: written and read back, then read and written back */
static void check_extended_statistics_message(void) {
  ExtendedStatisticsMessage sent;
  ExtendedStatisticsMessage got;
  uint8_t wire[93];
  uint8_t again[93];

  any_extended_statistics_message(&sent);
  assert(encode_extended_statistics_message(&sent, wire, 0) == 93);
  assert(decode_extended_statistics_message(&got, wire, 0) == 93);
  equal_extended_statistics_message(&got, &sent);

  for (size_t i = 0; i < 93; i++) { wire[i] = arbitrary(); }
  assert(decode_extended_statistics_message(&got, wire, 0) == 93);
  assert(encode_extended_statistics_message(&got, again, 0) == 93);
  for (size_t i = 0; i < 93; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Statistics Message: 57 bytes ------------------------------- */

/* Sent to disseminate the volume, turnover and trades of a market, sector or instrument type. */
typedef struct {
  uint8_t nanosecond[4];                /* bytes 0 to 3 */
  uint8_t statistics_type;              /* byte 4 */
  uint8_t symbol[12];                   /* bytes 5 to 16 */
  uint8_t volume[4];                    /* bytes 17 to 20 */
  uint8_t turnover[8];                  /* bytes 21 to 28 */
  uint8_t trades[4];                    /* bytes 29 to 32 */
  uint8_t daily_foreign_buy_value[8];   /* bytes 33 to 40 */
  uint8_t daily_foreign_sell_value[8];  /* bytes 41 to 48 */
  uint8_t market_capitalization[8];     /* bytes 49 to 56 */
} ConsolidatedStatisticsMessage;

/* any Consolidated Statistics Message at all: every byte one the checker chooses */
static void any_consolidated_statistics_message(ConsolidatedStatisticsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  record->statistics_type = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->daily_foreign_buy_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->daily_foreign_sell_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_capitalization[i] = arbitrary(); }
}

/* Consolidated Statistics Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_statistics_message(const ConsolidatedStatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  wire[at++] = record->statistics_type;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->daily_foreign_buy_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->daily_foreign_sell_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_capitalization[i]; }

  return at;
}

/* Consolidated Statistics Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_statistics_message(ConsolidatedStatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  record->statistics_type = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->daily_foreign_buy_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->daily_foreign_sell_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_capitalization[i] = wire[at++]; }

  return at;
}

/* what was read of Consolidated Statistics Message is what was written, byte for byte */
static void equal_consolidated_statistics_message(const ConsolidatedStatisticsMessage *read, const ConsolidatedStatisticsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  assert(read->statistics_type == written->statistics_type);
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trades[i] == written->trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->daily_foreign_buy_value[i] == written->daily_foreign_buy_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->daily_foreign_sell_value[i] == written->daily_foreign_sell_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_capitalization[i] == written->market_capitalization[i]); }
}

/* Consolidated Statistics Message: written and read back, then read and written back */
static void check_consolidated_statistics_message(void) {
  ConsolidatedStatisticsMessage sent;
  ConsolidatedStatisticsMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_consolidated_statistics_message(&sent);
  assert(encode_consolidated_statistics_message(&sent, wire, 0) == 57);
  assert(decode_consolidated_statistics_message(&got, wire, 0) == 57);
  equal_consolidated_statistics_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_statistics_message(&got, wire, 0) == 57);
  assert(encode_consolidated_statistics_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Message: 25 bytes ------------------------------------------------- */

/* Sent to disseminate the value of an index. */
typedef struct {
  uint8_t nanosecond[4];                /* bytes 0 to 3 */
  uint8_t symbol[12];                   /* bytes 4 to 15 */
  uint8_t index_value[4];               /* bytes 16 to 19 */
  uint8_t update_type;                  /* byte 20 */
  uint8_t perctg_diff_from_closing[4];  /* bytes 21 to 24 */
} IndexMessage;

/* any Index Message at all: every byte one the checker chooses */
static void any_index_message(IndexMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->index_value[i] = arbitrary(); }
  record->update_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->perctg_diff_from_closing[i] = arbitrary(); }
}

/* Index Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_index_message(const IndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_value[i]; }
  wire[at++] = record->update_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->perctg_diff_from_closing[i]; }

  return at;
}

/* Index Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_index_message(IndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->index_value[i] = wire[at++]; }
  record->update_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->perctg_diff_from_closing[i] = wire[at++]; }

  return at;
}

/* what was read of Index Message is what was written, byte for byte */
static void equal_index_message(const IndexMessage *read, const IndexMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->index_value[i] == written->index_value[i]); }
  assert(read->update_type == written->update_type);
  for (size_t i = 0; i < 4; i++) { assert(read->perctg_diff_from_closing[i] == written->perctg_diff_from_closing[i]); }
}

/* Index Message: written and read back, then read and written back */
static void check_index_message(void) {
  IndexMessage sent;
  IndexMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_index_message(&sent);
  assert(encode_index_message(&sent, wire, 0) == 25);
  assert(decode_index_message(&got, wire, 0) == 25);
  equal_index_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_index_message(&got, wire, 0) == 25);
  assert(encode_index_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Aon Info Message: 34 bytes ---------------------------------------------- */

/* Sent to disseminate the details of an All or None auction. */
typedef struct {
  uint8_t nanosecond[4];  /* bytes 0 to 3 */
  uint8_t symbol[12];     /* bytes 4 to 15 */
  uint8_t price[4];       /* bytes 16 to 19 */
  uint8_t side;           /* byte 20 */
  uint8_t quantity[4];    /* bytes 21 to 24 */
  uint8_t aon_status;     /* byte 25 */
  uint8_t date[8];        /* bytes 26 to 33 */
} AonInfoMessage;

/* any Aon Info Message at all: every byte one the checker chooses */
static void any_aon_info_message(AonInfoMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->aon_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
}

/* Aon Info Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_aon_info_message(const AonInfoMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->aon_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }

  return at;
}

/* Aon Info Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_aon_info_message(AonInfoMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->aon_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }

  return at;
}

/* what was read of Aon Info Message is what was written, byte for byte */
static void equal_aon_info_message(const AonInfoMessage *read, const AonInfoMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->aon_status == written->aon_status);
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
}

/* Aon Info Message: written and read back, then read and written back */
static void check_aon_info_message(void) {
  AonInfoMessage sent;
  AonInfoMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_aon_info_message(&sent);
  assert(encode_aon_info_message(&sent, wire, 0) == 34);
  assert(decode_aon_info_message(&got, wire, 0) == 34);
  equal_aon_info_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_aon_info_message(&got, wire, 0) == 34);
  assert(encode_aon_info_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- News Message: 1063 bytes ------------------------------------------------ */

/* Sent to disseminate an announcement. */
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
  check_order_deleted_message();
  check_order_book_clear_message();
  check_order_executed_message();
  check_order_executed_with_price_size_message();
  check_trade_message();
  check_auction_trade_message();
  check_off_book_trade_message();
  check_trade_break_message();
  check_trade_correction_message();
  check_recovery_trade_message();
  check_auction_info_message();
  check_statistics_message();
  check_extended_statistics_message();
  check_consolidated_statistics_message();
  check_index_message();
  check_aon_info_message();
  check_news_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
