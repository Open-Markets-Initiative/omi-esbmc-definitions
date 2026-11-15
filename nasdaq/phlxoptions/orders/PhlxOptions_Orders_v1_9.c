// nasdaq/phlxoptions/orders/PhlxOptions_Orders_v1_9.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) PHLX Orders
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
 *   - the dispatch that chooses a message by its type
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

/* ---- Packet Header: 16 bytes ------------------------------------------------- */

typedef struct {
  uint8_t session[10];         /* bytes 0 to 9 */
  uint8_t sequence_number[4];  /* bytes 10 to 13 */
  uint8_t message_count[2];    /* bytes 14 to 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = arbitrary(); }
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_count[i]; }

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_count[i] == written->message_count[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[16];
  uint8_t again[16];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 16);
  assert(decode_packet_header(&got, wire, 0) == 16);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 16);
  assert(encode_packet_header(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 1 byte -------------------------------------------------- */

typedef struct {
  uint8_t message_type;  /* byte 0 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->message_type = arbitrary();
}

/* Message Header to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[1];
  uint8_t again[1];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 1);
  assert(decode_message_header(&got, wire, 0) == 1);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 1);
  assert(encode_message_header(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Timestamp: 8 bytes ------------------------------------------------------ */

/* Time the message was sent: seconds after midnight and the nanosecond portion, U.S. Eastern Time */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} Timestamp;

/* any Timestamp at all: every byte one the checker chooses */
static void any_timestamp(Timestamp *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Timestamp to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_timestamp(const Timestamp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Timestamp off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_timestamp(Timestamp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Timestamp is what was written, byte for byte */
static void equal_timestamp(const Timestamp *read, const Timestamp *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Timestamp: written and read back, then read and written back */
static void check_timestamp(void) {
  Timestamp sent;
  Timestamp got;
  uint8_t wire[8];
  uint8_t again[8];

  any_timestamp(&sent);
  assert(encode_timestamp(&sent, wire, 0) == 8);
  assert(decode_timestamp(&got, wire, 0) == 8);
  equal_timestamp(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_timestamp(&got, wire, 0) == 8);
  assert(encode_timestamp(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 10 bytes ------------------------------------------ */

/* The system event message type is used to signal a market or data feed handler event. */
typedef struct {
  Timestamp timestamp;  /* bytes 0 to 7 */
  uint8_t event_code;   /* byte 8 */
  uint8_t version;      /* byte 9 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  any_timestamp(&record->timestamp);
  record->event_code = arbitrary();
  record->version = arbitrary();
}

/* System Event Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  at = encode_timestamp(&record->timestamp, wire, at);
  wire[at++] = record->event_code;
  wire[at++] = record->version;

  return at;
}

/* System Event Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  at = decode_timestamp(&record->timestamp, wire, at);
  record->event_code = wire[at++];
  record->version = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  equal_timestamp(&read->timestamp, &written->timestamp);
  assert(read->event_code == written->event_code);
  assert(read->version == written->version);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 10);
  assert(decode_system_event_message(&got, wire, 0) == 10);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 10);
  assert(encode_system_event_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Trading Action Message: 13 bytes -------------------------------- */

/* PHLX uses this administrative message to indicate the current trading status of a strategy within the PHLX Options Market. */
typedef struct {
  Timestamp timestamp;            /* bytes 0 to 7 */
  uint8_t strategy_id[4];         /* bytes 8 to 11 */
  uint8_t current_trading_state;  /* byte 12 */
} ComplexTradingActionMessage;

/* any Complex Trading Action Message at all: every byte one the checker chooses */
static void any_complex_trading_action_message(ComplexTradingActionMessage *record) {
  any_timestamp(&record->timestamp);
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  record->current_trading_state = arbitrary();
}

/* Complex Trading Action Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_complex_trading_action_message(const ComplexTradingActionMessage *record, uint8_t *wire, size_t at) {
  at = encode_timestamp(&record->timestamp, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  wire[at++] = record->current_trading_state;

  return at;
}

/* Complex Trading Action Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_complex_trading_action_message(ComplexTradingActionMessage *record, const uint8_t *wire, size_t at) {
  at = decode_timestamp(&record->timestamp, wire, at);
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  record->current_trading_state = wire[at++];

  return at;
}

/* what was read of Complex Trading Action Message is what was written, byte for byte */
static void equal_complex_trading_action_message(const ComplexTradingActionMessage *read, const ComplexTradingActionMessage *written) {
  equal_timestamp(&read->timestamp, &written->timestamp);
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  assert(read->current_trading_state == written->current_trading_state);
}

/* Complex Trading Action Message: written and read back, then read and written back */
static void check_complex_trading_action_message(void) {
  ComplexTradingActionMessage sent;
  ComplexTradingActionMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_complex_trading_action_message(&sent);
  assert(encode_complex_trading_action_message(&sent, wire, 0) == 13);
  assert(decode_complex_trading_action_message(&got, wire, 0) == 13);
  equal_complex_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_trading_action_message(&got, wire, 0) == 13);
  assert(encode_complex_trading_action_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strategy Open Closed Message: 13 bytes ---------------------------------- */

/* PHLX uses this administrative message to indicate when a strategy has completed the opening process or when the strategy has closed and is no longer available for auto execution. */
typedef struct {
  Timestamp timestamp;     /* bytes 0 to 7 */
  uint8_t strategy_id[4];  /* bytes 8 to 11 */
  uint8_t open_state;      /* byte 12 */
} StrategyOpenClosedMessage;

/* any Strategy Open Closed Message at all: every byte one the checker chooses */
static void any_strategy_open_closed_message(StrategyOpenClosedMessage *record) {
  any_timestamp(&record->timestamp);
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  record->open_state = arbitrary();
}

/* Strategy Open Closed Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_strategy_open_closed_message(const StrategyOpenClosedMessage *record, uint8_t *wire, size_t at) {
  at = encode_timestamp(&record->timestamp, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  wire[at++] = record->open_state;

  return at;
}

/* Strategy Open Closed Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_strategy_open_closed_message(StrategyOpenClosedMessage *record, const uint8_t *wire, size_t at) {
  at = decode_timestamp(&record->timestamp, wire, at);
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  record->open_state = wire[at++];

  return at;
}

/* what was read of Strategy Open Closed Message is what was written, byte for byte */
static void equal_strategy_open_closed_message(const StrategyOpenClosedMessage *read, const StrategyOpenClosedMessage *written) {
  equal_timestamp(&read->timestamp, &written->timestamp);
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  assert(read->open_state == written->open_state);
}

/* Strategy Open Closed Message: written and read back, then read and written back */
static void check_strategy_open_closed_message(void) {
  StrategyOpenClosedMessage sent;
  StrategyOpenClosedMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_strategy_open_closed_message(&sent);
  assert(encode_strategy_open_closed_message(&sent, wire, 0) == 13);
  assert(decode_strategy_open_closed_message(&got, wire, 0) == 13);
  equal_strategy_open_closed_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_strategy_open_closed_message(&got, wire, 0) == 13);
  assert(encode_strategy_open_closed_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Auction Notification Message: 27 bytes -------------------------- */

/* When a Complex Order Live Auction (COLA) or PIXL/Solicitation auction starts for a strategy of an underlying, a COLA/PIXL/Solicitation notification message containing the auction information will be sent. */
typedef struct {
  Timestamp timestamp;      /* bytes 0 to 7 */
  uint8_t strategy_id[4];   /* bytes 8 to 11 */
  uint8_t auction_id[4];    /* bytes 12 to 15 */
  uint8_t auction_type;     /* byte 16 */
  uint8_t price[4];         /* bytes 17 to 20 */
  uint8_t auction_side;     /* byte 21 */
  uint8_t debit_or_credit;  /* byte 22 */
  uint8_t volume[4];        /* bytes 23 to 26 */
} ComplexAuctionNotificationMessage;

/* any Complex Auction Notification Message at all: every byte one the checker chooses */
static void any_complex_auction_notification_message(ComplexAuctionNotificationMessage *record) {
  any_timestamp(&record->timestamp);
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->auction_side = arbitrary();
  record->debit_or_credit = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
}

/* Complex Auction Notification Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_complex_auction_notification_message(const ComplexAuctionNotificationMessage *record, uint8_t *wire, size_t at) {
  at = encode_timestamp(&record->timestamp, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->auction_side;
  wire[at++] = record->debit_or_credit;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }

  return at;
}

/* Complex Auction Notification Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_complex_auction_notification_message(ComplexAuctionNotificationMessage *record, const uint8_t *wire, size_t at) {
  at = decode_timestamp(&record->timestamp, wire, at);
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->auction_side = wire[at++];
  record->debit_or_credit = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Auction Notification Message is what was written, byte for byte */
static void equal_complex_auction_notification_message(const ComplexAuctionNotificationMessage *read, const ComplexAuctionNotificationMessage *written) {
  equal_timestamp(&read->timestamp, &written->timestamp);
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->auction_side == written->auction_side);
  assert(read->debit_or_credit == written->debit_or_credit);
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
}

/* Complex Auction Notification Message: written and read back, then read and written back */
static void check_complex_auction_notification_message(void) {
  ComplexAuctionNotificationMessage sent;
  ComplexAuctionNotificationMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_complex_auction_notification_message(&sent);
  assert(encode_complex_auction_notification_message(&sent, wire, 0) == 27);
  assert(decode_complex_auction_notification_message(&got, wire, 0) == 27);
  equal_complex_auction_notification_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_auction_notification_message(&got, wire, 0) == 27);
  assert(encode_complex_auction_notification_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_timestamp();
  check_system_event_message();
  check_complex_trading_action_message();
  check_strategy_open_closed_message();
  check_complex_auction_notification_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
