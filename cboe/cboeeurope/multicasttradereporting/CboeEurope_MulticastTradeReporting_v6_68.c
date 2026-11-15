// cboe/cboeeurope/multicasttradereporting/CboeEurope_MulticastTradeReporting_v6_68.c
/*
 * Chicago Board Options Exchange Multicast Trade Reporting
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
 *   - a run filling what frames it
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

/* ---- Packet Header: 8 bytes -------------------------------------------------- */

typedef struct {
  uint8_t length[2];      /* bytes 0 to 1 */
  uint8_t message_count;  /* byte 2 */
  uint8_t unit;           /* byte 3 */
  uint8_t sequence[4];    /* bytes 4 to 7 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->message_count = arbitrary();
  record->unit = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
}

/* Packet Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->message_count;
  wire[at++] = record->unit;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Packet Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->message_count = wire[at++];
  record->unit = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->message_count == written->message_count);
  assert(read->unit == written->unit);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 8);
  assert(decode_packet_header(&got, wire, 0) == 8);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 8);
  assert(encode_packet_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 2 bytes ------------------------------------------------- */

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

/* ---- Time Message: 4 bytes --------------------------------------------------- */

/* A Time message is immediately generated and sent when there is a PITCH event for a given clock second */
typedef struct {
  uint8_t time[4];  /* bytes 0 to 3 */
} TimeMessage;

/* any Time Message at all: every byte one the checker chooses */
static void any_time_message(TimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
}

/* Time Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_time_message(const TimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }

  return at;
}

/* Time Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_time_message(TimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }

  return at;
}

/* what was read of Time Message is what was written, byte for byte */
static void equal_time_message(const TimeMessage *read, const TimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
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

/* ---- Unit Clear Message: 4 bytes --------------------------------------------- */

/* The Unit Clear message instructs feed recipients to clear all orders for the Cboe book in the unit specified in the Sequenced Unit Header */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} UnitClearMessage;

/* any Unit Clear Message at all: every byte one the checker chooses */
static void any_unit_clear_message(UnitClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* Unit Clear Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_unit_clear_message(const UnitClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* Unit Clear Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_unit_clear_message(UnitClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Unit Clear Message is what was written, byte for byte */
static void equal_unit_clear_message(const UnitClearMessage *read, const UnitClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* Unit Clear Message: written and read back, then read and written back */
static void check_unit_clear_message(void) {
  UnitClearMessage sent;
  UnitClearMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_unit_clear_message(&sent);
  assert(encode_unit_clear_message(&sent, wire, 0) == 4);
  assert(decode_unit_clear_message(&got, wire, 0) == 4);
  equal_unit_clear_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_unit_clear_message(&got, wire, 0) == 4);
  assert(encode_unit_clear_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Long Message: 31 bytes ---------------------------------------- */

/* An Add Order message represents a newly accepted visible order on the Cboe book */
typedef struct {
  uint8_t time_offset[4];   /* bytes 0 to 3 */
  uint8_t order_id[8];      /* bytes 4 to 11 */
  uint8_t side_indicator;   /* byte 12 */
  uint8_t quantity[4];      /* bytes 13 to 16 */
  uint8_t symbol_short[6];  /* bytes 17 to 22 */
  uint8_t price_long[8];    /* bytes 23 to 30 */
} AddOrderLongMessage;

/* any Add Order Long Message at all: every byte one the checker chooses */
static void any_add_order_long_message(AddOrderLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
}

/* Add Order Long Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_add_order_long_message(const AddOrderLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }

  return at;
}

/* Add Order Long Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_add_order_long_message(AddOrderLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Long Message is what was written, byte for byte */
static void equal_add_order_long_message(const AddOrderLongMessage *read, const AddOrderLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
}

/* Add Order Long Message: written and read back, then read and written back */
static void check_add_order_long_message(void) {
  AddOrderLongMessage sent;
  AddOrderLongMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_add_order_long_message(&sent);
  assert(encode_add_order_long_message(&sent, wire, 0) == 31);
  assert(decode_add_order_long_message(&got, wire, 0) == 31);
  equal_add_order_long_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_long_message(&got, wire, 0) == 31);
  assert(encode_add_order_long_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Short Message: 23 bytes --------------------------------------- */

/* An Add Order message represents a newly accepted visible order on the Cboe book. */
typedef struct {
  uint8_t time_offset[4];     /* bytes 0 to 3 */
  uint8_t order_id[8];        /* bytes 4 to 11 */
  uint8_t side_indicator;     /* byte 12 */
  uint8_t quantity_short[2];  /* bytes 13 to 14 */
  uint8_t symbol_short[6];    /* bytes 15 to 20 */
  uint8_t price_short[2];     /* bytes 21 to 22 */
} AddOrderShortMessage;

/* any Add Order Short Message at all: every byte one the checker chooses */
static void any_add_order_short_message(AddOrderShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
}

/* Add Order Short Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_add_order_short_message(const AddOrderShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }

  return at;
}

/* Add Order Short Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_add_order_short_message(AddOrderShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Short Message is what was written, byte for byte */
static void equal_add_order_short_message(const AddOrderShortMessage *read, const AddOrderShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
}

/* Add Order Short Message: written and read back, then read and written back */
static void check_add_order_short_message(void) {
  AddOrderShortMessage sent;
  AddOrderShortMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_add_order_short_message(&sent);
  assert(encode_add_order_short_message(&sent, wire, 0) == 23);
  assert(decode_add_order_short_message(&got, wire, 0) == 23);
  equal_add_order_short_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_short_message(&got, wire, 0) == 23);
  assert(encode_add_order_short_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Flags: 4 bytes ------------------------------------------------ */

/* Execution Flags */
typedef struct {
  uint8_t market_mechanism;   /* byte 0 */
  uint8_t trading_mode;       /* byte 1 */
  uint8_t ex_cum_dividend;    /* byte 2 */
  uint8_t algorithmic_trade;  /* byte 3 */
} ExecutionFlags;

/* any Execution Flags at all: every byte one the checker chooses */
static void any_execution_flags(ExecutionFlags *record) {
  record->market_mechanism = arbitrary();
  record->trading_mode = arbitrary();
  record->ex_cum_dividend = arbitrary();
  record->algorithmic_trade = arbitrary();
}

/* Execution Flags to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_execution_flags(const ExecutionFlags *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_mechanism;
  wire[at++] = record->trading_mode;
  wire[at++] = record->ex_cum_dividend;
  wire[at++] = record->algorithmic_trade;

  return at;
}

/* Execution Flags off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_execution_flags(ExecutionFlags *record, const uint8_t *wire, size_t at) {
  record->market_mechanism = wire[at++];
  record->trading_mode = wire[at++];
  record->ex_cum_dividend = wire[at++];
  record->algorithmic_trade = wire[at++];

  return at;
}

/* what was read of Execution Flags is what was written, byte for byte */
static void equal_execution_flags(const ExecutionFlags *read, const ExecutionFlags *written) {
  assert(read->market_mechanism == written->market_mechanism);
  assert(read->trading_mode == written->trading_mode);
  assert(read->ex_cum_dividend == written->ex_cum_dividend);
  assert(read->algorithmic_trade == written->algorithmic_trade);
}

/* Execution Flags: written and read back, then read and written back */
static void check_execution_flags(void) {
  ExecutionFlags sent;
  ExecutionFlags got;
  uint8_t wire[4];
  uint8_t again[4];

  any_execution_flags(&sent);
  assert(encode_execution_flags(&sent, wire, 0) == 4);
  assert(decode_execution_flags(&got, wire, 0) == 4);
  equal_execution_flags(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_flags(&got, wire, 0) == 4);
  assert(encode_execution_flags(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 28 bytes ---------------------------------------- */

/* Order Executed messages are sent when a visible order on the Cboe book is executed in whole or in part */
typedef struct {
  uint8_t time_offset[4];          /* bytes 0 to 3 */
  uint8_t order_id[8];             /* bytes 4 to 11 */
  uint8_t executed_shares[4];      /* bytes 12 to 15 */
  uint8_t execution_id[8];         /* bytes 16 to 23 */
  ExecutionFlags execution_flags;  /* bytes 24 to 27 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  any_execution_flags(&record->execution_flags);
}

/* Order Executed Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  at = encode_execution_flags(&record->execution_flags, wire, at);

  return at;
}

/* Order Executed Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  at = decode_execution_flags(&record->execution_flags, wire, at);

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_shares[i] == written->executed_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  equal_execution_flags(&read->execution_flags, &written->execution_flags);
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 28);
  assert(decode_order_executed_message(&got, wire, 0) == 28);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 28);
  assert(encode_order_executed_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed At Price Size Message: 40 bytes -------------------------- */

/* Order Executed at Price/Size messages are sent when a visible order on the Cboe book is executed in whole or in part at a different price than the limit price on the original Add Order message or the limit order price in the latest Modify Order message referencing the Order Id. */
typedef struct {
  uint8_t time_offset[4];          /* bytes 0 to 3 */
  uint8_t order_id[8];             /* bytes 4 to 11 */
  uint8_t executed_shares[4];      /* bytes 12 to 15 */
  uint8_t remaining_shares[4];     /* bytes 16 to 19 */
  uint8_t execution_id[8];         /* bytes 20 to 27 */
  uint8_t price_long[8];           /* bytes 28 to 35 */
  ExecutionFlags execution_flags;  /* bytes 36 to 39 */
} OrderExecutedAtPriceSizeMessage;

/* any Order Executed At Price Size Message at all: every byte one the checker chooses */
static void any_order_executed_at_price_size_message(OrderExecutedAtPriceSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->remaining_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  any_execution_flags(&record->execution_flags);
}

/* Order Executed At Price Size Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_at_price_size_message(const OrderExecutedAtPriceSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->remaining_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  at = encode_execution_flags(&record->execution_flags, wire, at);

  return at;
}

/* Order Executed At Price Size Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_at_price_size_message(OrderExecutedAtPriceSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->remaining_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  at = decode_execution_flags(&record->execution_flags, wire, at);

  return at;
}

/* what was read of Order Executed At Price Size Message is what was written, byte for byte */
static void equal_order_executed_at_price_size_message(const OrderExecutedAtPriceSizeMessage *read, const OrderExecutedAtPriceSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_shares[i] == written->executed_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->remaining_shares[i] == written->remaining_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  equal_execution_flags(&read->execution_flags, &written->execution_flags);
}

/* Order Executed At Price Size Message: written and read back, then read and written back */
static void check_order_executed_at_price_size_message(void) {
  OrderExecutedAtPriceSizeMessage sent;
  OrderExecutedAtPriceSizeMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_order_executed_at_price_size_message(&sent);
  assert(encode_order_executed_at_price_size_message(&sent, wire, 0) == 40);
  assert(decode_order_executed_at_price_size_message(&got, wire, 0) == 40);
  equal_order_executed_at_price_size_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_at_price_size_message(&got, wire, 0) == 40);
  assert(encode_order_executed_at_price_size_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reduce Size Long Message: 16 bytes -------------------------------------- */

/* Reduce Size messages are sent when a visible order on the Cboe book is partially reduced. */
typedef struct {
  uint8_t time_offset[4];           /* bytes 0 to 3 */
  uint8_t order_id[8];              /* bytes 4 to 11 */
  uint8_t canceled_shares_long[4];  /* bytes 12 to 15 */
} ReduceSizeLongMessage;

/* any Reduce Size Long Message at all: every byte one the checker chooses */
static void any_reduce_size_long_message(ReduceSizeLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->canceled_shares_long[i] = arbitrary(); }
}

/* Reduce Size Long Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_reduce_size_long_message(const ReduceSizeLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->canceled_shares_long[i]; }

  return at;
}

/* Reduce Size Long Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_reduce_size_long_message(ReduceSizeLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->canceled_shares_long[i] = wire[at++]; }

  return at;
}

/* what was read of Reduce Size Long Message is what was written, byte for byte */
static void equal_reduce_size_long_message(const ReduceSizeLongMessage *read, const ReduceSizeLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->canceled_shares_long[i] == written->canceled_shares_long[i]); }
}

/* Reduce Size Long Message: written and read back, then read and written back */
static void check_reduce_size_long_message(void) {
  ReduceSizeLongMessage sent;
  ReduceSizeLongMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_reduce_size_long_message(&sent);
  assert(encode_reduce_size_long_message(&sent, wire, 0) == 16);
  assert(decode_reduce_size_long_message(&got, wire, 0) == 16);
  equal_reduce_size_long_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_reduce_size_long_message(&got, wire, 0) == 16);
  assert(encode_reduce_size_long_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reduce Size Short Message: 14 bytes ------------------------------------- */

/* Reduce Size messages are sent when a visible order on the Cboe book is partially reduced */
typedef struct {
  uint8_t time_offset[4];            /* bytes 0 to 3 */
  uint8_t order_id[8];               /* bytes 4 to 11 */
  uint8_t canceled_shares_short[2];  /* bytes 12 to 13 */
} ReduceSizeShortMessage;

/* any Reduce Size Short Message at all: every byte one the checker chooses */
static void any_reduce_size_short_message(ReduceSizeShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->canceled_shares_short[i] = arbitrary(); }
}

/* Reduce Size Short Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_reduce_size_short_message(const ReduceSizeShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->canceled_shares_short[i]; }

  return at;
}

/* Reduce Size Short Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_reduce_size_short_message(ReduceSizeShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->canceled_shares_short[i] = wire[at++]; }

  return at;
}

/* what was read of Reduce Size Short Message is what was written, byte for byte */
static void equal_reduce_size_short_message(const ReduceSizeShortMessage *read, const ReduceSizeShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->canceled_shares_short[i] == written->canceled_shares_short[i]); }
}

/* Reduce Size Short Message: written and read back, then read and written back */
static void check_reduce_size_short_message(void) {
  ReduceSizeShortMessage sent;
  ReduceSizeShortMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_reduce_size_short_message(&sent);
  assert(encode_reduce_size_short_message(&sent, wire, 0) == 14);
  assert(decode_reduce_size_short_message(&got, wire, 0) == 14);
  equal_reduce_size_short_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_reduce_size_short_message(&got, wire, 0) == 14);
  assert(encode_reduce_size_short_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Long Message: 24 bytes ------------------------------------- */

/* The Modify Order message is sent whenever an open order is visibly modified. The Order Id refers to the Order Id of the original Add Order message. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
  uint8_t order_id[8];     /* bytes 4 to 11 */
  uint8_t shares_long[4];  /* bytes 12 to 15 */
  uint8_t price_long[8];   /* bytes 16 to 23 */
} ModifyOrderLongMessage;

/* any Modify Order Long Message at all: every byte one the checker chooses */
static void any_modify_order_long_message(ModifyOrderLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
}

/* Modify Order Long Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_long_message(const ModifyOrderLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }

  return at;
}

/* Modify Order Long Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_long_message(ModifyOrderLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Order Long Message is what was written, byte for byte */
static void equal_modify_order_long_message(const ModifyOrderLongMessage *read, const ModifyOrderLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares_long[i] == written->shares_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
}

/* Modify Order Long Message: written and read back, then read and written back */
static void check_modify_order_long_message(void) {
  ModifyOrderLongMessage sent;
  ModifyOrderLongMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_modify_order_long_message(&sent);
  assert(encode_modify_order_long_message(&sent, wire, 0) == 24);
  assert(decode_modify_order_long_message(&got, wire, 0) == 24);
  equal_modify_order_long_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_long_message(&got, wire, 0) == 24);
  assert(encode_modify_order_long_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Short Message: 16 bytes ------------------------------------ */

/* The Modify Order message is sent whenever an open order is visibly modified. The Order Id refers to the Order Id of the original Add Order message. */
typedef struct {
  uint8_t time_offset[4];   /* bytes 0 to 3 */
  uint8_t order_id[8];      /* bytes 4 to 11 */
  uint8_t shares_short[2];  /* bytes 12 to 13 */
  uint8_t price_short[2];   /* bytes 14 to 15 */
} ModifyOrderShortMessage;

/* any Modify Order Short Message at all: every byte one the checker chooses */
static void any_modify_order_short_message(ModifyOrderShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->shares_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
}

/* Modify Order Short Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_short_message(const ModifyOrderShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->shares_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }

  return at;
}

/* Modify Order Short Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_short_message(ModifyOrderShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->shares_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Order Short Message is what was written, byte for byte */
static void equal_modify_order_short_message(const ModifyOrderShortMessage *read, const ModifyOrderShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->shares_short[i] == written->shares_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
}

/* Modify Order Short Message: written and read back, then read and written back */
static void check_modify_order_short_message(void) {
  ModifyOrderShortMessage sent;
  ModifyOrderShortMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_modify_order_short_message(&sent);
  assert(encode_modify_order_short_message(&sent, wire, 0) == 16);
  assert(decode_modify_order_short_message(&got, wire, 0) == 16);
  equal_modify_order_short_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_short_message(&got, wire, 0) == 16);
  assert(encode_modify_order_short_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Order Message: 12 bytes ------------------------------------------ */

/* The Delete Order message is sent whenever an open order is completely canceled. The Order Id refers to the Order Id of the original Add Order message. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
  uint8_t order_id[8];     /* bytes 4 to 11 */
} DeleteOrderMessage;

/* any Delete Order Message at all: every byte one the checker chooses */
static void any_delete_order_message(DeleteOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Delete Order Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_delete_order_message(const DeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Delete Order Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_delete_order_message(DeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Order Message is what was written, byte for byte */
static void equal_delete_order_message(const DeleteOrderMessage *read, const DeleteOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Delete Order Message: written and read back, then read and written back */
static void check_delete_order_message(void) {
  DeleteOrderMessage sent;
  DeleteOrderMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_delete_order_message(&sent);
  assert(encode_delete_order_message(&sent, wire, 0) == 12);
  assert(decode_delete_order_message(&got, wire, 0) == 12);
  equal_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_order_message(&got, wire, 0) == 12);
  assert(encode_delete_order_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Flags: 5 bytes ---------------------------------------------------- */

/* Trade Flags */
typedef struct {
  uint8_t market_mechanism;      /* byte 0 */
  uint8_t trading_mode;          /* byte 1 */
  uint8_t transaction_category;  /* byte 2 */
  uint8_t trade_types;           /* byte 3 */
  uint8_t algorithmic_trade;     /* byte 4 */
} TradeFlags;

/* any Trade Flags at all: every byte one the checker chooses */
static void any_trade_flags(TradeFlags *record) {
  record->market_mechanism = arbitrary();
  record->trading_mode = arbitrary();
  record->transaction_category = arbitrary();
  record->trade_types = arbitrary();
  record->algorithmic_trade = arbitrary();
}

/* Trade Flags to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_trade_flags(const TradeFlags *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_mechanism;
  wire[at++] = record->trading_mode;
  wire[at++] = record->transaction_category;
  wire[at++] = record->trade_types;
  wire[at++] = record->algorithmic_trade;

  return at;
}

/* Trade Flags off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_trade_flags(TradeFlags *record, const uint8_t *wire, size_t at) {
  record->market_mechanism = wire[at++];
  record->trading_mode = wire[at++];
  record->transaction_category = wire[at++];
  record->trade_types = wire[at++];
  record->algorithmic_trade = wire[at++];

  return at;
}

/* what was read of Trade Flags is what was written, byte for byte */
static void equal_trade_flags(const TradeFlags *read, const TradeFlags *written) {
  assert(read->market_mechanism == written->market_mechanism);
  assert(read->trading_mode == written->trading_mode);
  assert(read->transaction_category == written->transaction_category);
  assert(read->trade_types == written->trade_types);
  assert(read->algorithmic_trade == written->algorithmic_trade);
}

/* Trade Flags: written and read back, then read and written back */
static void check_trade_flags(void) {
  TradeFlags sent;
  TradeFlags got;
  uint8_t wire[5];
  uint8_t again[5];

  any_trade_flags(&sent);
  assert(encode_trade_flags(&sent, wire, 0) == 5);
  assert(decode_trade_flags(&got, wire, 0) == 5);
  equal_trade_flags(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_flags(&got, wire, 0) == 5);
  assert(encode_trade_flags(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Long Message: 44 bytes -------------------------------------------- */

/* The Trade message provides information about executions of complex order auctions on the Cboe complex book. */
typedef struct {
  uint8_t time_offset[4];   /* bytes 0 to 3 */
  uint8_t order_id[8];      /* bytes 4 to 11 */
  uint8_t side_indicator;   /* byte 12 */
  uint8_t shares_long[4];   /* bytes 13 to 16 */
  uint8_t symbol_short[6];  /* bytes 17 to 22 */
  uint8_t price_long[8];    /* bytes 23 to 30 */
  uint8_t execution_id[8];  /* bytes 31 to 38 */
  TradeFlags trade_flags;   /* bytes 39 to 43 */
} TradeLongMessage;

/* any Trade Long Message at all: every byte one the checker chooses */
static void any_trade_long_message(TradeLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->shares_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  any_trade_flags(&record->trade_flags);
}

/* Trade Long Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_trade_long_message(const TradeLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  at = encode_trade_flags(&record->trade_flags, wire, at);

  return at;
}

/* Trade Long Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_trade_long_message(TradeLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->shares_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  at = decode_trade_flags(&record->trade_flags, wire, at);

  return at;
}

/* what was read of Trade Long Message is what was written, byte for byte */
static void equal_trade_long_message(const TradeLongMessage *read, const TradeLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->shares_long[i] == written->shares_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  equal_trade_flags(&read->trade_flags, &written->trade_flags);
}

/* Trade Long Message: written and read back, then read and written back */
static void check_trade_long_message(void) {
  TradeLongMessage sent;
  TradeLongMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_trade_long_message(&sent);
  assert(encode_trade_long_message(&sent, wire, 0) == 44);
  assert(decode_trade_long_message(&got, wire, 0) == 44);
  equal_trade_long_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_long_message(&got, wire, 0) == 44);
  assert(encode_trade_long_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Short Message: 36 bytes ------------------------------------------- */

/* The Trade message provides information about executions of non-displayed orders on the Cboe book and routed executions to other trading centers. */
typedef struct {
  uint8_t time_offset[4];            /* bytes 0 to 3 */
  uint8_t order_id[8];               /* bytes 4 to 11 */
  uint8_t side_indicator;            /* byte 12 */
  uint8_t contracts_short[2];        /* bytes 13 to 14 */
  uint8_t symbol_alphanumeric_6[6];  /* bytes 15 to 20 */
  uint8_t price_short[2];            /* bytes 21 to 22 */
  uint8_t execution_id[8];           /* bytes 23 to 30 */
  TradeFlags trade_flags;            /* bytes 31 to 35 */
} TradeShortMessage;

/* any Trade Short Message at all: every byte one the checker chooses */
static void any_trade_short_message(TradeShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->contracts_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_alphanumeric_6[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  any_trade_flags(&record->trade_flags);
}

/* Trade Short Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_trade_short_message(const TradeShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->contracts_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_alphanumeric_6[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  at = encode_trade_flags(&record->trade_flags, wire, at);

  return at;
}

/* Trade Short Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_trade_short_message(TradeShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->contracts_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_alphanumeric_6[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  at = decode_trade_flags(&record->trade_flags, wire, at);

  return at;
}

/* what was read of Trade Short Message is what was written, byte for byte */
static void equal_trade_short_message(const TradeShortMessage *read, const TradeShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->contracts_short[i] == written->contracts_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_alphanumeric_6[i] == written->symbol_alphanumeric_6[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  equal_trade_flags(&read->trade_flags, &written->trade_flags);
}

/* Trade Short Message: written and read back, then read and written back */
static void check_trade_short_message(void) {
  TradeShortMessage sent;
  TradeShortMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_trade_short_message(&sent);
  assert(encode_trade_short_message(&sent, wire, 0) == 36);
  assert(decode_trade_short_message(&got, wire, 0) == 36);
  equal_trade_short_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_short_message(&got, wire, 0) == 36);
  assert(encode_trade_short_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Extended Trade Flags: 14 bytes ------------------------------------------ */

/* Extended Trade Flags */
typedef struct {
  uint8_t market_mechanism;                     /* byte 0 */
  uint8_t trading_mode;                         /* byte 1 */
  uint8_t transaction_category;                 /* byte 2 */
  uint8_t negotiated_trade;                     /* byte 3 */
  uint8_t crossing_trade;                       /* byte 4 */
  uint8_t modification_indicator;               /* byte 5 */
  uint8_t benchmark_reference_price_indicator;  /* byte 6 */
  uint8_t special_dividend;                     /* byte 7 */
  uint8_t off_book_automated_indicator;         /* byte 8 */
  uint8_t price_formation_discovery_process;    /* byte 9 */
  uint8_t algorithmic_indicator;                /* byte 10 */
  uint8_t publication_mode_deferral_reason;     /* byte 11 */
  uint8_t deferral_or_enrichment_type;          /* byte 12 */
  uint8_t duplicative_indicator;                /* byte 13 */
} ExtendedTradeFlags;

/* any Extended Trade Flags at all: every byte one the checker chooses */
static void any_extended_trade_flags(ExtendedTradeFlags *record) {
  record->market_mechanism = arbitrary();
  record->trading_mode = arbitrary();
  record->transaction_category = arbitrary();
  record->negotiated_trade = arbitrary();
  record->crossing_trade = arbitrary();
  record->modification_indicator = arbitrary();
  record->benchmark_reference_price_indicator = arbitrary();
  record->special_dividend = arbitrary();
  record->off_book_automated_indicator = arbitrary();
  record->price_formation_discovery_process = arbitrary();
  record->algorithmic_indicator = arbitrary();
  record->publication_mode_deferral_reason = arbitrary();
  record->deferral_or_enrichment_type = arbitrary();
  record->duplicative_indicator = arbitrary();
}

/* Extended Trade Flags to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_extended_trade_flags(const ExtendedTradeFlags *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_mechanism;
  wire[at++] = record->trading_mode;
  wire[at++] = record->transaction_category;
  wire[at++] = record->negotiated_trade;
  wire[at++] = record->crossing_trade;
  wire[at++] = record->modification_indicator;
  wire[at++] = record->benchmark_reference_price_indicator;
  wire[at++] = record->special_dividend;
  wire[at++] = record->off_book_automated_indicator;
  wire[at++] = record->price_formation_discovery_process;
  wire[at++] = record->algorithmic_indicator;
  wire[at++] = record->publication_mode_deferral_reason;
  wire[at++] = record->deferral_or_enrichment_type;
  wire[at++] = record->duplicative_indicator;

  return at;
}

/* Extended Trade Flags off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_extended_trade_flags(ExtendedTradeFlags *record, const uint8_t *wire, size_t at) {
  record->market_mechanism = wire[at++];
  record->trading_mode = wire[at++];
  record->transaction_category = wire[at++];
  record->negotiated_trade = wire[at++];
  record->crossing_trade = wire[at++];
  record->modification_indicator = wire[at++];
  record->benchmark_reference_price_indicator = wire[at++];
  record->special_dividend = wire[at++];
  record->off_book_automated_indicator = wire[at++];
  record->price_formation_discovery_process = wire[at++];
  record->algorithmic_indicator = wire[at++];
  record->publication_mode_deferral_reason = wire[at++];
  record->deferral_or_enrichment_type = wire[at++];
  record->duplicative_indicator = wire[at++];

  return at;
}

/* what was read of Extended Trade Flags is what was written, byte for byte */
static void equal_extended_trade_flags(const ExtendedTradeFlags *read, const ExtendedTradeFlags *written) {
  assert(read->market_mechanism == written->market_mechanism);
  assert(read->trading_mode == written->trading_mode);
  assert(read->transaction_category == written->transaction_category);
  assert(read->negotiated_trade == written->negotiated_trade);
  assert(read->crossing_trade == written->crossing_trade);
  assert(read->modification_indicator == written->modification_indicator);
  assert(read->benchmark_reference_price_indicator == written->benchmark_reference_price_indicator);
  assert(read->special_dividend == written->special_dividend);
  assert(read->off_book_automated_indicator == written->off_book_automated_indicator);
  assert(read->price_formation_discovery_process == written->price_formation_discovery_process);
  assert(read->algorithmic_indicator == written->algorithmic_indicator);
  assert(read->publication_mode_deferral_reason == written->publication_mode_deferral_reason);
  assert(read->deferral_or_enrichment_type == written->deferral_or_enrichment_type);
  assert(read->duplicative_indicator == written->duplicative_indicator);
}

/* Extended Trade Flags: written and read back, then read and written back */
static void check_extended_trade_flags(void) {
  ExtendedTradeFlags sent;
  ExtendedTradeFlags got;
  uint8_t wire[14];
  uint8_t again[14];

  any_extended_trade_flags(&sent);
  assert(encode_extended_trade_flags(&sent, wire, 0) == 14);
  assert(decode_extended_trade_flags(&got, wire, 0) == 14);
  equal_extended_trade_flags(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_extended_trade_flags(&got, wire, 0) == 14);
  assert(encode_extended_trade_flags(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Extended Message: 64 bytes ---------------------------------------- */

/* The Trade message provides information about executions of complex order auctions on the Cboe complex book. */
typedef struct {
  uint8_t time_offset[4];                   /* bytes 0 to 3 */
  uint8_t shares_extended[8];               /* bytes 4 to 11 */
  uint8_t symbol_short[6];                  /* bytes 12 to 17 */
  uint8_t price_long[8];                    /* bytes 18 to 25 */
  uint8_t trade_id[8];                      /* bytes 26 to 33 */
  uint8_t trade_timestamp[8];               /* bytes 34 to 41 */
  uint8_t execution_venue[4];               /* bytes 42 to 45 */
  uint8_t currency[3];                      /* bytes 46 to 48 */
  uint8_t cboe_trade_flags;                 /* byte 49 */
  ExtendedTradeFlags extended_trade_flags;  /* bytes 50 to 63 */
} TradeExtendedMessage;

/* any Trade Extended Message at all: every byte one the checker chooses */
static void any_trade_extended_message(TradeExtendedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->shares_extended[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  record->cboe_trade_flags = arbitrary();
  any_extended_trade_flags(&record->extended_trade_flags);
}

/* Trade Extended Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_trade_extended_message(const TradeExtendedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->shares_extended[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_venue[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->cboe_trade_flags;
  at = encode_extended_trade_flags(&record->extended_trade_flags, wire, at);

  return at;
}

/* Trade Extended Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_trade_extended_message(TradeExtendedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->shares_extended[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  record->cboe_trade_flags = wire[at++];
  at = decode_extended_trade_flags(&record->extended_trade_flags, wire, at);

  return at;
}

/* what was read of Trade Extended Message is what was written, byte for byte */
static void equal_trade_extended_message(const TradeExtendedMessage *read, const TradeExtendedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->shares_extended[i] == written->shares_extended[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_timestamp[i] == written->trade_timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_venue[i] == written->execution_venue[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->cboe_trade_flags == written->cboe_trade_flags);
  equal_extended_trade_flags(&read->extended_trade_flags, &written->extended_trade_flags);
}

/* Trade Extended Message: written and read back, then read and written back */
static void check_trade_extended_message(void) {
  TradeExtendedMessage sent;
  TradeExtendedMessage got;
  uint8_t wire[64];
  uint8_t again[64];

  any_trade_extended_message(&sent);
  assert(encode_trade_extended_message(&sent, wire, 0) == 64);
  assert(decode_trade_extended_message(&got, wire, 0) == 64);
  equal_trade_extended_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_extended_message(&got, wire, 0) == 64);
  assert(encode_trade_extended_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Unknown Symbol Message: 70 bytes ---------------------------------- */

/* This message provides details of trades reported to Cboe, but traded on a symbol not currently known to Cboe */
typedef struct {
  uint8_t time_offset[4];                   /* bytes 0 to 3 */
  uint8_t shares_extended[8];               /* bytes 4 to 11 */
  uint8_t symbol_long[12];                  /* bytes 12 to 23 */
  uint8_t price_long[8];                    /* bytes 24 to 31 */
  uint8_t trade_id[8];                      /* bytes 32 to 39 */
  uint8_t trade_timestamp[8];               /* bytes 40 to 47 */
  uint8_t execution_venue[4];               /* bytes 48 to 51 */
  uint8_t currency[3];                      /* bytes 52 to 54 */
  uint8_t cboe_trade_flags;                 /* byte 55 */
  ExtendedTradeFlags extended_trade_flags;  /* bytes 56 to 69 */
} TradeUnknownSymbolMessage;

/* any Trade Unknown Symbol Message at all: every byte one the checker chooses */
static void any_trade_unknown_symbol_message(TradeUnknownSymbolMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->shares_extended[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  record->cboe_trade_flags = arbitrary();
  any_extended_trade_flags(&record->extended_trade_flags);
}

/* Trade Unknown Symbol Message to the wire: 70 bytes from at, returning where the next byte goes */
static size_t encode_trade_unknown_symbol_message(const TradeUnknownSymbolMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->shares_extended[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_venue[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->cboe_trade_flags;
  at = encode_extended_trade_flags(&record->extended_trade_flags, wire, at);

  return at;
}

/* Trade Unknown Symbol Message off the wire: 70 bytes from at, returning where the next byte lies */
static size_t decode_trade_unknown_symbol_message(TradeUnknownSymbolMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->shares_extended[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  record->cboe_trade_flags = wire[at++];
  at = decode_extended_trade_flags(&record->extended_trade_flags, wire, at);

  return at;
}

/* what was read of Trade Unknown Symbol Message is what was written, byte for byte */
static void equal_trade_unknown_symbol_message(const TradeUnknownSymbolMessage *read, const TradeUnknownSymbolMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->shares_extended[i] == written->shares_extended[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_timestamp[i] == written->trade_timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_venue[i] == written->execution_venue[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->cboe_trade_flags == written->cboe_trade_flags);
  equal_extended_trade_flags(&read->extended_trade_flags, &written->extended_trade_flags);
}

/* Trade Unknown Symbol Message: written and read back, then read and written back */
static void check_trade_unknown_symbol_message(void) {
  TradeUnknownSymbolMessage sent;
  TradeUnknownSymbolMessage got;
  uint8_t wire[70];
  uint8_t again[70];

  any_trade_unknown_symbol_message(&sent);
  assert(encode_trade_unknown_symbol_message(&sent, wire, 0) == 70);
  assert(decode_trade_unknown_symbol_message(&got, wire, 0) == 70);
  equal_trade_unknown_symbol_message(&got, &sent);

  for (size_t i = 0; i < 70; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_unknown_symbol_message(&got, wire, 0) == 70);
  assert(encode_trade_unknown_symbol_message(&got, again, 0) == 70);
  for (size_t i = 0; i < 70; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Session: 4 bytes ------------------------------------------------- */

/* The End of Session message is sent for each unit when the unit shuts down */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} EndOfSession;

/* any End Of Session at all: every byte one the checker chooses */
static void any_end_of_session(EndOfSession *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* End Of Session to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_end_of_session(const EndOfSession *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* End Of Session off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_end_of_session(EndOfSession *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Session is what was written, byte for byte */
static void equal_end_of_session(const EndOfSession *read, const EndOfSession *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* End Of Session: written and read back, then read and written back */
static void check_end_of_session(void) {
  EndOfSession sent;
  EndOfSession got;
  uint8_t wire[4];
  uint8_t again[4];

  any_end_of_session(&sent);
  assert(encode_end_of_session(&sent, wire, 0) == 4);
  assert(decode_end_of_session(&got, wire, 0) == 4);
  equal_end_of_session(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_session(&got, wire, 0) == 4);
  assert(encode_end_of_session(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Transaction Begin Message: 4 bytes -------------------------------------- */

/* The Transaction Begin message indicates any subsequent messages, up to the accompanying Transaction End message, are all part of the same transaction block */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} TransactionBeginMessage;

/* any Transaction Begin Message at all: every byte one the checker chooses */
static void any_transaction_begin_message(TransactionBeginMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* Transaction Begin Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_transaction_begin_message(const TransactionBeginMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* Transaction Begin Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_transaction_begin_message(TransactionBeginMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Transaction Begin Message is what was written, byte for byte */
static void equal_transaction_begin_message(const TransactionBeginMessage *read, const TransactionBeginMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* Transaction Begin Message: written and read back, then read and written back */
static void check_transaction_begin_message(void) {
  TransactionBeginMessage sent;
  TransactionBeginMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_transaction_begin_message(&sent);
  assert(encode_transaction_begin_message(&sent, wire, 0) == 4);
  assert(decode_transaction_begin_message(&got, wire, 0) == 4);
  equal_transaction_begin_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_transaction_begin_message(&got, wire, 0) == 4);
  assert(encode_transaction_begin_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Transaction End Message: 4 bytes ---------------------------------------- */

/* The Transaction End message indicates that a transaction indicated by a previous Transaction Begin message has completed */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} TransactionEndMessage;

/* any Transaction End Message at all: every byte one the checker chooses */
static void any_transaction_end_message(TransactionEndMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* Transaction End Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_transaction_end_message(const TransactionEndMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* Transaction End Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_transaction_end_message(TransactionEndMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Transaction End Message is what was written, byte for byte */
static void equal_transaction_end_message(const TransactionEndMessage *read, const TransactionEndMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* Transaction End Message: written and read back, then read and written back */
static void check_transaction_end_message(void) {
  TransactionEndMessage sent;
  TransactionEndMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_transaction_end_message(&sent);
  assert(encode_transaction_end_message(&sent, wire, 0) == 4);
  assert(decode_transaction_end_message(&got, wire, 0) == 4);
  equal_transaction_end_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_transaction_end_message(&got, wire, 0) == 4);
  assert(encode_transaction_end_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 14 bytes ---------------------------------------- */

/* The Trading Status message is used to indicate the current trading status of a complex instrument. */
typedef struct {
  uint8_t time_offset[4];   /* bytes 0 to 3 */
  uint8_t symbol_short[6];  /* bytes 4 to 9 */
  uint8_t trading_status;   /* byte 10 */
  uint8_t reserved_3[3];    /* bytes 11 to 13 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = arbitrary(); }
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Trading Status Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_short[i]; }
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Trading Status Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = wire[at++]; }
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 14);
  assert(decode_trading_status_message(&got, wire, 0) == 14);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 14);
  assert(encode_trading_status_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Statistics Message: 20 bytes -------------------------------------------- */

/* The Statistics Message is used to disseminate the statistics prices: opening, closing, high, low */
typedef struct {
  uint8_t time_offset[4];       /* bytes 0 to 3 */
  uint8_t symbol_short[6];      /* bytes 4 to 9 */
  uint8_t price_long[8];        /* bytes 10 to 17 */
  uint8_t statistic_type;       /* byte 18 */
  uint8_t price_determination;  /* byte 19 */
} StatisticsMessage;

/* any Statistics Message at all: every byte one the checker chooses */
static void any_statistics_message(StatisticsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  record->statistic_type = arbitrary();
  record->price_determination = arbitrary();
}

/* Statistics Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_statistics_message(const StatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  wire[at++] = record->statistic_type;
  wire[at++] = record->price_determination;

  return at;
}

/* Statistics Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_statistics_message(StatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  record->statistic_type = wire[at++];
  record->price_determination = wire[at++];

  return at;
}

/* what was read of Statistics Message is what was written, byte for byte */
static void equal_statistics_message(const StatisticsMessage *read, const StatisticsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  assert(read->statistic_type == written->statistic_type);
  assert(read->price_determination == written->price_determination);
}

/* Statistics Message: written and read back, then read and written back */
static void check_statistics_message(void) {
  StatisticsMessage sent;
  StatisticsMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_statistics_message(&sent);
  assert(encode_statistics_message(&sent, wire, 0) == 20);
  assert(decode_statistics_message(&got, wire, 0) == 20);
  equal_statistics_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_statistics_message(&got, wire, 0) == 20);
  assert(encode_statistics_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Update Message: 33 bytes ---------------------------------------- */

/* Auction Update messages are used to disseminate indicative price and size information during auctions for Cboe auction eligible securities */
typedef struct {
  uint8_t time_offset[4];        /* bytes 0 to 3 */
  uint8_t symbol_short[6];       /* bytes 4 to 9 */
  uint8_t auction_type;          /* byte 10 */
  uint8_t reference_price[8];    /* bytes 11 to 18 */
  uint8_t indicative_price[8];   /* bytes 19 to 26 */
  uint8_t indicative_shares[4];  /* bytes 27 to 30 */
  uint8_t outside_tolerance;     /* byte 31 */
  uint8_t includes_primary;      /* byte 32 */
} AuctionUpdateMessage;

/* any Auction Update Message at all: every byte one the checker chooses */
static void any_auction_update_message(AuctionUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->indicative_shares[i] = arbitrary(); }
  record->outside_tolerance = arbitrary();
  record->includes_primary = arbitrary();
}

/* Auction Update Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_auction_update_message(const AuctionUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_short[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indicative_shares[i]; }
  wire[at++] = record->outside_tolerance;
  wire[at++] = record->includes_primary;

  return at;
}

/* Auction Update Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_auction_update_message(AuctionUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->indicative_shares[i] = wire[at++]; }
  record->outside_tolerance = wire[at++];
  record->includes_primary = wire[at++];

  return at;
}

/* what was read of Auction Update Message is what was written, byte for byte */
static void equal_auction_update_message(const AuctionUpdateMessage *read, const AuctionUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_price[i] == written->indicative_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->indicative_shares[i] == written->indicative_shares[i]); }
  assert(read->outside_tolerance == written->outside_tolerance);
  assert(read->includes_primary == written->includes_primary);
}

/* Auction Update Message: written and read back, then read and written back */
static void check_auction_update_message(void) {
  AuctionUpdateMessage sent;
  AuctionUpdateMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_auction_update_message(&sent);
  assert(encode_auction_update_message(&sent, wire, 0) == 33);
  assert(decode_auction_update_message(&got, wire, 0) == 33);
  equal_auction_update_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_update_message(&got, wire, 0) == 33);
  assert(encode_auction_update_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Summary Message: 23 bytes --------------------------------------- */

/* Auction Summary messages are used to disseminate the results of an auction in a Cboe auction eligible security */
typedef struct {
  uint8_t time_offset[4];   /* bytes 0 to 3 */
  uint8_t symbol_short[6];  /* bytes 4 to 9 */
  uint8_t auction_type;     /* byte 10 */
  uint8_t price_long[8];    /* bytes 11 to 18 */
  uint8_t shares_long[4];   /* bytes 19 to 22 */
} AuctionSummaryMessage;

/* any Auction Summary Message at all: every byte one the checker chooses */
static void any_auction_summary_message(AuctionSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares_long[i] = arbitrary(); }
}

/* Auction Summary Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_auction_summary_message(const AuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_short[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares_long[i]; }

  return at;
}

/* Auction Summary Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_auction_summary_message(AuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares_long[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Summary Message is what was written, byte for byte */
static void equal_auction_summary_message(const AuctionSummaryMessage *read, const AuctionSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares_long[i] == written->shares_long[i]); }
}

/* Auction Summary Message: written and read back, then read and written back */
static void check_auction_summary_message(void) {
  AuctionSummaryMessage sent;
  AuctionSummaryMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_auction_summary_message(&sent);
  assert(encode_auction_summary_message(&sent, wire, 0) == 23);
  assert(decode_auction_summary_message(&got, wire, 0) == 23);
  equal_auction_summary_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_summary_message(&got, wire, 0) == 23);
  assert(encode_auction_summary_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Quote Message: 27 bytes ------------------------------------------- */

/* Index Quote Messages are sent every second */
typedef struct {
  uint8_t index_timestamp[8];  /* bytes 0 to 7 */
  uint8_t index_ticker[10];    /* bytes 8 to 17 */
  uint8_t index_price[8];      /* bytes 18 to 25 */
  uint8_t index_status;        /* byte 26 */
} IndexQuoteMessage;

/* any Index Quote Message at all: every byte one the checker chooses */
static void any_index_quote_message(IndexQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->index_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->index_ticker[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_price[i] = arbitrary(); }
  record->index_status = arbitrary();
}

/* Index Quote Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_index_quote_message(const IndexQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_timestamp[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->index_ticker[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_price[i]; }
  wire[at++] = record->index_status;

  return at;
}

/* Index Quote Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_index_quote_message(IndexQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->index_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->index_ticker[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_price[i] = wire[at++]; }
  record->index_status = wire[at++];

  return at;
}

/* what was read of Index Quote Message is what was written, byte for byte */
static void equal_index_quote_message(const IndexQuoteMessage *read, const IndexQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->index_timestamp[i] == written->index_timestamp[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->index_ticker[i] == written->index_ticker[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_price[i] == written->index_price[i]); }
  assert(read->index_status == written->index_status);
}

/* Index Quote Message: written and read back, then read and written back */
static void check_index_quote_message(void) {
  IndexQuoteMessage sent;
  IndexQuoteMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_index_quote_message(&sent);
  assert(encode_index_quote_message(&sent, wire, 0) == 27);
  assert(decode_index_quote_message(&got, wire, 0) == 27);
  equal_index_quote_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_index_quote_message(&got, wire, 0) == 27);
  assert(encode_index_quote_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Quote Edsp Message: 26 bytes -------------------------------------- */

/* Index Quote EDSP Messages are sent at end of day */
typedef struct {
  uint8_t index_timestamp[8];  /* bytes 0 to 7 */
  uint8_t index_ticker[10];    /* bytes 8 to 17 */
  uint8_t index_price[8];      /* bytes 18 to 25 */
} IndexQuoteEdspMessage;

/* any Index Quote Edsp Message at all: every byte one the checker chooses */
static void any_index_quote_edsp_message(IndexQuoteEdspMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->index_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->index_ticker[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_price[i] = arbitrary(); }
}

/* Index Quote Edsp Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_index_quote_edsp_message(const IndexQuoteEdspMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_timestamp[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->index_ticker[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_price[i]; }

  return at;
}

/* Index Quote Edsp Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_index_quote_edsp_message(IndexQuoteEdspMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->index_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->index_ticker[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_price[i] = wire[at++]; }

  return at;
}

/* what was read of Index Quote Edsp Message is what was written, byte for byte */
static void equal_index_quote_edsp_message(const IndexQuoteEdspMessage *read, const IndexQuoteEdspMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->index_timestamp[i] == written->index_timestamp[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->index_ticker[i] == written->index_ticker[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_price[i] == written->index_price[i]); }
}

/* Index Quote Edsp Message: written and read back, then read and written back */
static void check_index_quote_edsp_message(void) {
  IndexQuoteEdspMessage sent;
  IndexQuoteEdspMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_index_quote_edsp_message(&sent);
  assert(encode_index_quote_edsp_message(&sent, wire, 0) == 26);
  assert(decode_index_quote_edsp_message(&got, wire, 0) == 26);
  equal_index_quote_edsp_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_index_quote_edsp_message(&got, wire, 0) == 26);
  assert(encode_index_quote_edsp_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_time_message();
  check_unit_clear_message();
  check_add_order_long_message();
  check_add_order_short_message();
  check_execution_flags();
  check_order_executed_message();
  check_order_executed_at_price_size_message();
  check_reduce_size_long_message();
  check_reduce_size_short_message();
  check_modify_order_long_message();
  check_modify_order_short_message();
  check_delete_order_message();
  check_trade_flags();
  check_trade_long_message();
  check_trade_short_message();
  check_extended_trade_flags();
  check_trade_extended_message();
  check_trade_unknown_symbol_message();
  check_end_of_session();
  check_transaction_begin_message();
  check_transaction_end_message();
  check_trading_status_message();
  check_statistics_message();
  check_auction_update_message();
  check_auction_summary_message();
  check_index_quote_message();
  check_index_quote_edsp_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
