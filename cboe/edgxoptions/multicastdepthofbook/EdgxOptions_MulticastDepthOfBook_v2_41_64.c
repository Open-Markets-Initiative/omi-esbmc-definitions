// cboe/edgxoptions/multicastdepthofbook/EdgxOptions_MulticastDepthOfBook_v2_41_64.c
/*
 * Chicago Board Options Exchange Multicast Depth Of Book
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

/* ---- Ox Time Message: 4 bytes ------------------------------------------------ */

/* A Time message is immediately generated and sent when there is a PITCH event for a given clock second */
typedef struct {
  uint8_t time[4];  /* bytes 0 to 3 */
} OxTimeMessage;

/* any Ox Time Message at all: every byte one the checker chooses */
static void any_ox_time_message(OxTimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
}

/* Ox Time Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_ox_time_message(const OxTimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }

  return at;
}

/* Ox Time Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_ox_time_message(OxTimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Time Message is what was written, byte for byte */
static void equal_ox_time_message(const OxTimeMessage *read, const OxTimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
}

/* Ox Time Message: written and read back, then read and written back */
static void check_ox_time_message(void) {
  OxTimeMessage sent;
  OxTimeMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_ox_time_message(&sent);
  assert(encode_ox_time_message(&sent, wire, 0) == 4);
  assert(decode_ox_time_message(&got, wire, 0) == 4);
  equal_ox_time_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_time_message(&got, wire, 0) == 4);
  assert(encode_ox_time_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Unit Clear Message: 4 bytes ------------------------------------------ */

/* The Unit Clear message instructs feed recipients to clear all orders for the Cboe book in the unit specified in the Sequenced Unit Header */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} OxUnitClearMessage;

/* any Ox Unit Clear Message at all: every byte one the checker chooses */
static void any_ox_unit_clear_message(OxUnitClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* Ox Unit Clear Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_ox_unit_clear_message(const OxUnitClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* Ox Unit Clear Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_ox_unit_clear_message(OxUnitClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Unit Clear Message is what was written, byte for byte */
static void equal_ox_unit_clear_message(const OxUnitClearMessage *read, const OxUnitClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* Ox Unit Clear Message: written and read back, then read and written back */
static void check_ox_unit_clear_message(void) {
  OxUnitClearMessage sent;
  OxUnitClearMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_ox_unit_clear_message(&sent);
  assert(encode_ox_unit_clear_message(&sent, wire, 0) == 4);
  assert(decode_ox_unit_clear_message(&got, wire, 0) == 4);
  equal_ox_unit_clear_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_unit_clear_message(&got, wire, 0) == 4);
  assert(encode_ox_unit_clear_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Transaction Begin Message: 4 bytes ----------------------------------- */

/* The Transaction Begin message indicates any subsequent messages, up to the accompanying Transaction End message, are all part of the same transaction block. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} OxTransactionBeginMessage;

/* any Ox Transaction Begin Message at all: every byte one the checker chooses */
static void any_ox_transaction_begin_message(OxTransactionBeginMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* Ox Transaction Begin Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_ox_transaction_begin_message(const OxTransactionBeginMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* Ox Transaction Begin Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_ox_transaction_begin_message(OxTransactionBeginMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Transaction Begin Message is what was written, byte for byte */
static void equal_ox_transaction_begin_message(const OxTransactionBeginMessage *read, const OxTransactionBeginMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* Ox Transaction Begin Message: written and read back, then read and written back */
static void check_ox_transaction_begin_message(void) {
  OxTransactionBeginMessage sent;
  OxTransactionBeginMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_ox_transaction_begin_message(&sent);
  assert(encode_ox_transaction_begin_message(&sent, wire, 0) == 4);
  assert(decode_ox_transaction_begin_message(&got, wire, 0) == 4);
  equal_ox_transaction_begin_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_transaction_begin_message(&got, wire, 0) == 4);
  assert(encode_ox_transaction_begin_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Transaction End Message: 4 bytes ------------------------------------- */

/* The Transaction End message indicates that a transaction indicated by a previous Transaction Begin message has completed. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} OxTransactionEndMessage;

/* any Ox Transaction End Message at all: every byte one the checker chooses */
static void any_ox_transaction_end_message(OxTransactionEndMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* Ox Transaction End Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_ox_transaction_end_message(const OxTransactionEndMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* Ox Transaction End Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_ox_transaction_end_message(OxTransactionEndMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Transaction End Message is what was written, byte for byte */
static void equal_ox_transaction_end_message(const OxTransactionEndMessage *read, const OxTransactionEndMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* Ox Transaction End Message: written and read back, then read and written back */
static void check_ox_transaction_end_message(void) {
  OxTransactionEndMessage sent;
  OxTransactionEndMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_ox_transaction_end_message(&sent);
  assert(encode_ox_transaction_end_message(&sent, wire, 0) == 4);
  assert(decode_ox_transaction_end_message(&got, wire, 0) == 4);
  equal_ox_transaction_end_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_transaction_end_message(&got, wire, 0) == 4);
  assert(encode_ox_transaction_end_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Order Executed Message: 25 bytes ------------------------------------- */

/* Order Executed messages are sent when a visible order on the Cboe book is executed in whole or in part */
typedef struct {
  uint8_t time_offset[4];        /* bytes 0 to 3 */
  uint8_t order_id[8];           /* bytes 4 to 11 */
  uint8_t executed_quantity[4];  /* bytes 12 to 15 */
  uint8_t execution_id[8];       /* bytes 16 to 23 */
  uint8_t trade_condition;       /* byte 24 */
} OxOrderExecutedMessage;

/* any Ox Order Executed Message at all: every byte one the checker chooses */
static void any_ox_order_executed_message(OxOrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Ox Order Executed Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_ox_order_executed_message(const OxOrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Ox Order Executed Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_ox_order_executed_message(OxOrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Ox Order Executed Message is what was written, byte for byte */
static void equal_ox_order_executed_message(const OxOrderExecutedMessage *read, const OxOrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Ox Order Executed Message: written and read back, then read and written back */
static void check_ox_order_executed_message(void) {
  OxOrderExecutedMessage sent;
  OxOrderExecutedMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_ox_order_executed_message(&sent);
  assert(encode_ox_order_executed_message(&sent, wire, 0) == 25);
  assert(decode_ox_order_executed_message(&got, wire, 0) == 25);
  equal_ox_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_order_executed_message(&got, wire, 0) == 25);
  assert(encode_ox_order_executed_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Order Executed At Price Size Message: 37 bytes ----------------------- */

/* Order Executed at Price/Size messages are sent when a visible order on the Cboe book is executed in whole or in part at a different price than the limit price on the original Add Order message or the limit order price in the latest Modify Order message referencing the Order Id */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t order_id[8];            /* bytes 4 to 11 */
  uint8_t executed_quantity[4];   /* bytes 12 to 15 */
  uint8_t remaining_quantity[4];  /* bytes 16 to 19 */
  uint8_t execution_id[8];        /* bytes 20 to 27 */
  uint8_t price_long[8];          /* bytes 28 to 35 */
  uint8_t trade_condition;        /* byte 36 */
} OxOrderExecutedAtPriceSizeMessage;

/* any Ox Order Executed At Price Size Message at all: every byte one the checker chooses */
static void any_ox_order_executed_at_price_size_message(OxOrderExecutedAtPriceSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Ox Order Executed At Price Size Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_ox_order_executed_at_price_size_message(const OxOrderExecutedAtPriceSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->remaining_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Ox Order Executed At Price Size Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_ox_order_executed_at_price_size_message(OxOrderExecutedAtPriceSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Ox Order Executed At Price Size Message is what was written, byte for byte */
static void equal_ox_order_executed_at_price_size_message(const OxOrderExecutedAtPriceSizeMessage *read, const OxOrderExecutedAtPriceSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->remaining_quantity[i] == written->remaining_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Ox Order Executed At Price Size Message: written and read back, then read and written back */
static void check_ox_order_executed_at_price_size_message(void) {
  OxOrderExecutedAtPriceSizeMessage sent;
  OxOrderExecutedAtPriceSizeMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_ox_order_executed_at_price_size_message(&sent);
  assert(encode_ox_order_executed_at_price_size_message(&sent, wire, 0) == 37);
  assert(decode_ox_order_executed_at_price_size_message(&got, wire, 0) == 37);
  equal_ox_order_executed_at_price_size_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_order_executed_at_price_size_message(&got, wire, 0) == 37);
  assert(encode_ox_order_executed_at_price_size_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Reduce Size Long Message: 16 bytes ----------------------------------- */

/* Reduce Size messages are sent when a visible order on the Cboe book is partially reduced */
typedef struct {
  uint8_t time_offset[4];             /* bytes 0 to 3 */
  uint8_t order_id[8];                /* bytes 4 to 11 */
  uint8_t canceled_quantity_long[4];  /* bytes 12 to 15 */
} OxReduceSizeLongMessage;

/* any Ox Reduce Size Long Message at all: every byte one the checker chooses */
static void any_ox_reduce_size_long_message(OxReduceSizeLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->canceled_quantity_long[i] = arbitrary(); }
}

/* Ox Reduce Size Long Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_ox_reduce_size_long_message(const OxReduceSizeLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->canceled_quantity_long[i]; }

  return at;
}

/* Ox Reduce Size Long Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_ox_reduce_size_long_message(OxReduceSizeLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->canceled_quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Reduce Size Long Message is what was written, byte for byte */
static void equal_ox_reduce_size_long_message(const OxReduceSizeLongMessage *read, const OxReduceSizeLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->canceled_quantity_long[i] == written->canceled_quantity_long[i]); }
}

/* Ox Reduce Size Long Message: written and read back, then read and written back */
static void check_ox_reduce_size_long_message(void) {
  OxReduceSizeLongMessage sent;
  OxReduceSizeLongMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_ox_reduce_size_long_message(&sent);
  assert(encode_ox_reduce_size_long_message(&sent, wire, 0) == 16);
  assert(decode_ox_reduce_size_long_message(&got, wire, 0) == 16);
  equal_ox_reduce_size_long_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_reduce_size_long_message(&got, wire, 0) == 16);
  assert(encode_ox_reduce_size_long_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Reduce Size Short Message: 14 bytes ---------------------------------- */

/* Reduce Size messages are sent when a visible order on the Cboe book is partially reduced */
typedef struct {
  uint8_t time_offset[4];              /* bytes 0 to 3 */
  uint8_t order_id[8];                 /* bytes 4 to 11 */
  uint8_t canceled_quantity_short[2];  /* bytes 12 to 13 */
} OxReduceSizeShortMessage;

/* any Ox Reduce Size Short Message at all: every byte one the checker chooses */
static void any_ox_reduce_size_short_message(OxReduceSizeShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->canceled_quantity_short[i] = arbitrary(); }
}

/* Ox Reduce Size Short Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_ox_reduce_size_short_message(const OxReduceSizeShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->canceled_quantity_short[i]; }

  return at;
}

/* Ox Reduce Size Short Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_ox_reduce_size_short_message(OxReduceSizeShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->canceled_quantity_short[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Reduce Size Short Message is what was written, byte for byte */
static void equal_ox_reduce_size_short_message(const OxReduceSizeShortMessage *read, const OxReduceSizeShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->canceled_quantity_short[i] == written->canceled_quantity_short[i]); }
}

/* Ox Reduce Size Short Message: written and read back, then read and written back */
static void check_ox_reduce_size_short_message(void) {
  OxReduceSizeShortMessage sent;
  OxReduceSizeShortMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_ox_reduce_size_short_message(&sent);
  assert(encode_ox_reduce_size_short_message(&sent, wire, 0) == 14);
  assert(decode_ox_reduce_size_short_message(&got, wire, 0) == 14);
  equal_ox_reduce_size_short_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_reduce_size_short_message(&got, wire, 0) == 14);
  assert(encode_ox_reduce_size_short_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Delete Order Message: 12 bytes --------------------------------------- */

/* The Delete Order message is sent whenever a booked order is cancelled or leaves the order book */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
  uint8_t order_id[8];     /* bytes 4 to 11 */
} OxDeleteOrderMessage;

/* any Ox Delete Order Message at all: every byte one the checker chooses */
static void any_ox_delete_order_message(OxDeleteOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Ox Delete Order Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_ox_delete_order_message(const OxDeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Ox Delete Order Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_ox_delete_order_message(OxDeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Delete Order Message is what was written, byte for byte */
static void equal_ox_delete_order_message(const OxDeleteOrderMessage *read, const OxDeleteOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Ox Delete Order Message: written and read back, then read and written back */
static void check_ox_delete_order_message(void) {
  OxDeleteOrderMessage sent;
  OxDeleteOrderMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_ox_delete_order_message(&sent);
  assert(encode_ox_delete_order_message(&sent, wire, 0) == 12);
  assert(decode_ox_delete_order_message(&got, wire, 0) == 12);
  equal_ox_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_delete_order_message(&got, wire, 0) == 12);
  assert(encode_ox_delete_order_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Trade Long Message: 40 bytes ----------------------------------------- */

/* The Trade message provides information about executions of non-displayed orders on the Cboe book and routed executions to other trading centers */
typedef struct {
  uint8_t time_offset[4];    /* bytes 0 to 3 */
  uint8_t order_id[8];       /* bytes 4 to 11 */
  uint8_t side_indicator;    /* byte 12 */
  uint8_t quantity_long[4];  /* bytes 13 to 16 */
  uint8_t symbol[6];         /* bytes 17 to 22 */
  uint8_t price_long[8];     /* bytes 23 to 30 */
  uint8_t execution_id[8];   /* bytes 31 to 38 */
  uint8_t trade_condition;   /* byte 39 */
} OxTradeLongMessage;

/* any Ox Trade Long Message at all: every byte one the checker chooses */
static void any_ox_trade_long_message(OxTradeLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Ox Trade Long Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_ox_trade_long_message(const OxTradeLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Ox Trade Long Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_ox_trade_long_message(OxTradeLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Ox Trade Long Message is what was written, byte for byte */
static void equal_ox_trade_long_message(const OxTradeLongMessage *read, const OxTradeLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Ox Trade Long Message: written and read back, then read and written back */
static void check_ox_trade_long_message(void) {
  OxTradeLongMessage sent;
  OxTradeLongMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_ox_trade_long_message(&sent);
  assert(encode_ox_trade_long_message(&sent, wire, 0) == 40);
  assert(decode_ox_trade_long_message(&got, wire, 0) == 40);
  equal_ox_trade_long_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_trade_long_message(&got, wire, 0) == 40);
  assert(encode_ox_trade_long_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Trade Short Message: 32 bytes ---------------------------------------- */

/* The Trade message provides information about executions of non-displayed orders on the Cboe book and routed executions to other trading centers */
typedef struct {
  uint8_t time_offset[4];     /* bytes 0 to 3 */
  uint8_t order_id[8];        /* bytes 4 to 11 */
  uint8_t side_indicator;     /* byte 12 */
  uint8_t quantity_short[2];  /* bytes 13 to 14 */
  uint8_t symbol[6];          /* bytes 15 to 20 */
  uint8_t price_short[2];     /* bytes 21 to 22 */
  uint8_t execution_id[8];    /* bytes 23 to 30 */
  uint8_t trade_condition;    /* byte 31 */
} OxTradeShortMessage;

/* any Ox Trade Short Message at all: every byte one the checker chooses */
static void any_ox_trade_short_message(OxTradeShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Ox Trade Short Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_ox_trade_short_message(const OxTradeShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Ox Trade Short Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_ox_trade_short_message(OxTradeShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Ox Trade Short Message is what was written, byte for byte */
static void equal_ox_trade_short_message(const OxTradeShortMessage *read, const OxTradeShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Ox Trade Short Message: written and read back, then read and written back */
static void check_ox_trade_short_message(void) {
  OxTradeShortMessage sent;
  OxTradeShortMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_ox_trade_short_message(&sent);
  assert(encode_ox_trade_short_message(&sent, wire, 0) == 32);
  assert(decode_ox_trade_short_message(&got, wire, 0) == 32);
  equal_ox_trade_short_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_trade_short_message(&got, wire, 0) == 32);
  assert(encode_ox_trade_short_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Trade Expanded Message: 42 bytes ------------------------------------- */

/* The Trade message provides information about executions of non-displayed orders on the Cboe book and routed executions to other trading centers. Expanded version accommodates larger symbol sizes possible through the ISRA plan. */
typedef struct {
  uint8_t time_offset[4];      /* bytes 0 to 3 */
  uint8_t order_id[8];         /* bytes 4 to 11 */
  uint8_t side_indicator;      /* byte 12 */
  uint8_t quantity_long[4];    /* bytes 13 to 16 */
  uint8_t expanded_symbol[8];  /* bytes 17 to 24 */
  uint8_t price_long[8];       /* bytes 25 to 32 */
  uint8_t execution_id[8];     /* bytes 33 to 40 */
  uint8_t trade_condition;     /* byte 41 */
} OxTradeExpandedMessage;

/* any Ox Trade Expanded Message at all: every byte one the checker chooses */
static void any_ox_trade_expanded_message(OxTradeExpandedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expanded_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Ox Trade Expanded Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_ox_trade_expanded_message(const OxTradeExpandedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expanded_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Ox Trade Expanded Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_ox_trade_expanded_message(OxTradeExpandedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expanded_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Ox Trade Expanded Message is what was written, byte for byte */
static void equal_ox_trade_expanded_message(const OxTradeExpandedMessage *read, const OxTradeExpandedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expanded_symbol[i] == written->expanded_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Ox Trade Expanded Message: written and read back, then read and written back */
static void check_ox_trade_expanded_message(void) {
  OxTradeExpandedMessage sent;
  OxTradeExpandedMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_ox_trade_expanded_message(&sent);
  assert(encode_ox_trade_expanded_message(&sent, wire, 0) == 42);
  assert(decode_ox_trade_expanded_message(&got, wire, 0) == 42);
  equal_ox_trade_expanded_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_trade_expanded_message(&got, wire, 0) == 42);
  assert(encode_ox_trade_expanded_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Trade Break Message: 12 bytes ---------------------------------------- */

/* The Trade Break message is sent whenever an execution on Cboe is broken */
typedef struct {
  uint8_t time_offset[4];   /* bytes 0 to 3 */
  uint8_t execution_id[8];  /* bytes 4 to 11 */
} OxTradeBreakMessage;

/* any Ox Trade Break Message at all: every byte one the checker chooses */
static void any_ox_trade_break_message(OxTradeBreakMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Ox Trade Break Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_ox_trade_break_message(const OxTradeBreakMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Ox Trade Break Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_ox_trade_break_message(OxTradeBreakMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Trade Break Message is what was written, byte for byte */
static void equal_ox_trade_break_message(const OxTradeBreakMessage *read, const OxTradeBreakMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Ox Trade Break Message: written and read back, then read and written back */
static void check_ox_trade_break_message(void) {
  OxTradeBreakMessage sent;
  OxTradeBreakMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_ox_trade_break_message(&sent);
  assert(encode_ox_trade_break_message(&sent, wire, 0) == 12);
  assert(decode_ox_trade_break_message(&got, wire, 0) == 12);
  equal_ox_trade_break_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_trade_break_message(&got, wire, 0) == 12);
  assert(encode_ox_trade_break_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox End Of Session: 4 bytes ---------------------------------------------- */

/* The End of Session message is sent for each unit when the unit shuts down */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} OxEndOfSession;

/* any Ox End Of Session at all: every byte one the checker chooses */
static void any_ox_end_of_session(OxEndOfSession *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* Ox End Of Session to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_ox_end_of_session(const OxEndOfSession *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* Ox End Of Session off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_ox_end_of_session(OxEndOfSession *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Ox End Of Session is what was written, byte for byte */
static void equal_ox_end_of_session(const OxEndOfSession *read, const OxEndOfSession *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* Ox End Of Session: written and read back, then read and written back */
static void check_ox_end_of_session(void) {
  OxEndOfSession sent;
  OxEndOfSession got;
  uint8_t wire[4];
  uint8_t again[4];

  any_ox_end_of_session(&sent);
  assert(encode_ox_end_of_session(&sent, wire, 0) == 4);
  assert(decode_ox_end_of_session(&got, wire, 0) == 4);
  equal_ox_end_of_session(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_end_of_session(&got, wire, 0) == 4);
  assert(encode_ox_end_of_session(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Symbol Mapping Message: 36 bytes ------------------------------------- */

/* A Symbol Mapping message is used to map the 6 character multicast feed symbol field to an OSI symbol and Underlying. These messages are not sequenced and are sent continuously through the day at variable rates as bandwidth allows. */
typedef struct {
  uint8_t feed_symbol[6];    /* bytes 0 to 5 */
  uint8_t osi_symbol[21];    /* bytes 6 to 26 */
  uint8_t symbol_condition;  /* byte 27 */
  uint8_t underlying[8];     /* bytes 28 to 35 */
} OxSymbolMappingMessage;

/* any Ox Symbol Mapping Message at all: every byte one the checker chooses */
static void any_ox_symbol_mapping_message(OxSymbolMappingMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 21; i++) { record->osi_symbol[i] = arbitrary(); }
  record->symbol_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = arbitrary(); }
}

/* Ox Symbol Mapping Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_ox_symbol_mapping_message(const OxSymbolMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->feed_symbol[i]; }
  for (size_t i = 0; i < 21; i++) { wire[at++] = record->osi_symbol[i]; }
  wire[at++] = record->symbol_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying[i]; }

  return at;
}

/* Ox Symbol Mapping Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_ox_symbol_mapping_message(OxSymbolMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 21; i++) { record->osi_symbol[i] = wire[at++]; }
  record->symbol_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Symbol Mapping Message is what was written, byte for byte */
static void equal_ox_symbol_mapping_message(const OxSymbolMappingMessage *read, const OxSymbolMappingMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->feed_symbol[i] == written->feed_symbol[i]); }
  for (size_t i = 0; i < 21; i++) { assert(read->osi_symbol[i] == written->osi_symbol[i]); }
  assert(read->symbol_condition == written->symbol_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->underlying[i] == written->underlying[i]); }
}

/* Ox Symbol Mapping Message: written and read back, then read and written back */
static void check_ox_symbol_mapping_message(void) {
  OxSymbolMappingMessage sent;
  OxSymbolMappingMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_ox_symbol_mapping_message(&sent);
  assert(encode_ox_symbol_mapping_message(&sent, wire, 0) == 36);
  assert(decode_ox_symbol_mapping_message(&got, wire, 0) == 36);
  equal_ox_symbol_mapping_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_symbol_mapping_message(&got, wire, 0) == 36);
  assert(encode_ox_symbol_mapping_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Trading Status Message: 16 bytes ------------------------------------- */

/* The Trading Status message is used to indicate the current trading status of a security */
typedef struct {
  uint8_t time_offset[4];      /* bytes 0 to 3 */
  uint8_t symbol[6];           /* bytes 4 to 9 */
  uint8_t reserved_2[2];       /* bytes 10 to 11 */
  uint8_t trading_status;      /* byte 12 */
  uint8_t reserved_1;          /* byte 13 */
  uint8_t gth_trading_status;  /* byte 14 */
  uint8_t second_reserved_1;   /* byte 15 */
} OxTradingStatusMessage;

/* any Ox Trading Status Message at all: every byte one the checker chooses */
static void any_ox_trading_status_message(OxTradingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->reserved_1 = arbitrary();
  record->gth_trading_status = arbitrary();
  record->second_reserved_1 = arbitrary();
}

/* Ox Trading Status Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_ox_trading_status_message(const OxTradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->reserved_1;
  wire[at++] = record->gth_trading_status;
  wire[at++] = record->second_reserved_1;

  return at;
}

/* Ox Trading Status Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_ox_trading_status_message(OxTradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->reserved_1 = wire[at++];
  record->gth_trading_status = wire[at++];
  record->second_reserved_1 = wire[at++];

  return at;
}

/* what was read of Ox Trading Status Message is what was written, byte for byte */
static void equal_ox_trading_status_message(const OxTradingStatusMessage *read, const OxTradingStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->reserved_1 == written->reserved_1);
  assert(read->gth_trading_status == written->gth_trading_status);
  assert(read->second_reserved_1 == written->second_reserved_1);
}

/* Ox Trading Status Message: written and read back, then read and written back */
static void check_ox_trading_status_message(void) {
  OxTradingStatusMessage sent;
  OxTradingStatusMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_ox_trading_status_message(&sent);
  assert(encode_ox_trading_status_message(&sent, wire, 0) == 16);
  assert(decode_ox_trading_status_message(&got, wire, 0) == 16);
  equal_ox_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_trading_status_message(&got, wire, 0) == 16);
  assert(encode_ox_trading_status_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Width Update Message: 17 bytes --------------------------------------- */

/* The Width Update message is used to communicate opening quote width multiplier. This message will be sent in the event that the exchange decides to change the quote width multiplier on a per underlying basis. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
  uint8_t underlying[8];   /* bytes 4 to 11 */
  uint8_t width_type;      /* byte 12 */
  uint8_t multiplier[4];   /* bytes 13 to 16 */
} OxWidthUpdateMessage;

/* any Ox Width Update Message at all: every byte one the checker chooses */
static void any_ox_width_update_message(OxWidthUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = arbitrary(); }
  record->width_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->multiplier[i] = arbitrary(); }
}

/* Ox Width Update Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_ox_width_update_message(const OxWidthUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying[i]; }
  wire[at++] = record->width_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->multiplier[i]; }

  return at;
}

/* Ox Width Update Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_ox_width_update_message(OxWidthUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = wire[at++]; }
  record->width_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->multiplier[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Width Update Message is what was written, byte for byte */
static void equal_ox_width_update_message(const OxWidthUpdateMessage *read, const OxWidthUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->underlying[i] == written->underlying[i]); }
  assert(read->width_type == written->width_type);
  for (size_t i = 0; i < 4; i++) { assert(read->multiplier[i] == written->multiplier[i]); }
}

/* Ox Width Update Message: written and read back, then read and written back */
static void check_ox_width_update_message(void) {
  OxWidthUpdateMessage sent;
  OxWidthUpdateMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_ox_width_update_message(&sent);
  assert(encode_ox_width_update_message(&sent, wire, 0) == 17);
  assert(decode_ox_width_update_message(&got, wire, 0) == 17);
  equal_ox_width_update_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_width_update_message(&got, wire, 0) == 17);
  assert(encode_ox_width_update_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Options Auction Update Message: 62 bytes ----------------------------- */

/* Options Auction Update messages are used to disseminate price and size information and Composite Market bid and offer prices during Opening and Re-Opening (halt) auctions on the Cboe Options Exchange. */
typedef struct {
  uint8_t time_offset[4];                   /* bytes 0 to 3 */
  uint8_t expanded_symbol[8];               /* bytes 4 to 11 */
  uint8_t auction_type;                     /* byte 12 */
  uint8_t reference_price[8];               /* bytes 13 to 20 */
  uint8_t buy_contracts[4];                 /* bytes 21 to 24 */
  uint8_t sell_contracts[4];                /* bytes 25 to 28 */
  uint8_t indicative_price[8];              /* bytes 29 to 36 */
  uint8_t auction_only_price[8];            /* bytes 37 to 44 */
  uint8_t opening_condition;                /* byte 45 */
  uint8_t composite_market_bid_price[8];    /* bytes 46 to 53 */
  uint8_t composite_market_offer_price[8];  /* bytes 54 to 61 */
} OxOptionsAuctionUpdateMessage;

/* any Ox Options Auction Update Message at all: every byte one the checker chooses */
static void any_ox_options_auction_update_message(OxOptionsAuctionUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expanded_symbol[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_contracts[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_contracts[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_only_price[i] = arbitrary(); }
  record->opening_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->composite_market_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->composite_market_offer_price[i] = arbitrary(); }
}

/* Ox Options Auction Update Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_ox_options_auction_update_message(const OxOptionsAuctionUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expanded_symbol[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_contracts[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_contracts[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_only_price[i]; }
  wire[at++] = record->opening_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->composite_market_bid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->composite_market_offer_price[i]; }

  return at;
}

/* Ox Options Auction Update Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_ox_options_auction_update_message(OxOptionsAuctionUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expanded_symbol[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_contracts[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_contracts[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_only_price[i] = wire[at++]; }
  record->opening_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->composite_market_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->composite_market_offer_price[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Options Auction Update Message is what was written, byte for byte */
static void equal_ox_options_auction_update_message(const OxOptionsAuctionUpdateMessage *read, const OxOptionsAuctionUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expanded_symbol[i] == written->expanded_symbol[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_contracts[i] == written->buy_contracts[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_contracts[i] == written->sell_contracts[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_price[i] == written->indicative_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_only_price[i] == written->auction_only_price[i]); }
  assert(read->opening_condition == written->opening_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->composite_market_bid_price[i] == written->composite_market_bid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->composite_market_offer_price[i] == written->composite_market_offer_price[i]); }
}

/* Ox Options Auction Update Message: written and read back, then read and written back */
static void check_ox_options_auction_update_message(void) {
  OxOptionsAuctionUpdateMessage sent;
  OxOptionsAuctionUpdateMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_ox_options_auction_update_message(&sent);
  assert(encode_ox_options_auction_update_message(&sent, wire, 0) == 62);
  assert(decode_ox_options_auction_update_message(&got, wire, 0) == 62);
  equal_ox_options_auction_update_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_options_auction_update_message(&got, wire, 0) == 62);
  assert(encode_ox_options_auction_update_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Auction Summary Message: 25 bytes ------------------------------------ */

/* Auction Summary messages are used to disseminate the results of an auction, including Opening and Re-Opening on the Cboe Options Exchange */
typedef struct {
  uint8_t time_offset[4];       /* bytes 0 to 3 */
  uint8_t stock_symbol[8];      /* bytes 4 to 11 */
  uint8_t auction_type;         /* byte 12 */
  uint8_t price_long[8];        /* bytes 13 to 20 */
  uint8_t shares_contracts[4];  /* bytes 21 to 24 */
} OxAuctionSummaryMessage;

/* any Ox Auction Summary Message at all: every byte one the checker chooses */
static void any_ox_auction_summary_message(OxAuctionSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares_contracts[i] = arbitrary(); }
}

/* Ox Auction Summary Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_ox_auction_summary_message(const OxAuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares_contracts[i]; }

  return at;
}

/* Ox Auction Summary Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_ox_auction_summary_message(OxAuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares_contracts[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Auction Summary Message is what was written, byte for byte */
static void equal_ox_auction_summary_message(const OxAuctionSummaryMessage *read, const OxAuctionSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares_contracts[i] == written->shares_contracts[i]); }
}

/* Ox Auction Summary Message: written and read back, then read and written back */
static void check_ox_auction_summary_message(void) {
  OxAuctionSummaryMessage sent;
  OxAuctionSummaryMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_ox_auction_summary_message(&sent);
  assert(encode_ox_auction_summary_message(&sent, wire, 0) == 25);
  assert(decode_ox_auction_summary_message(&got, wire, 0) == 25);
  equal_ox_auction_summary_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_auction_summary_message(&got, wire, 0) == 25);
  assert(encode_ox_auction_summary_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Auction Notification Message: 45 bytes ------------------------------- */

/* Auction Notification messages are used to disseminate order details of an auction. Auctions will be available for a defined period of time known as the exposure period. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t symbol[6];              /* bytes 4 to 9 */
  uint8_t auction_id[8];          /* bytes 10 to 17 */
  uint8_t auction_type;           /* byte 18 */
  uint8_t side;                   /* byte 19 */
  uint8_t price_long[8];          /* bytes 20 to 27 */
  uint8_t contracts[4];           /* bytes 28 to 31 */
  uint8_t customer_indicator;     /* byte 32 */
  uint8_t participant_id[4];      /* bytes 33 to 36 */
  uint8_t auction_end_offset[4];  /* bytes 37 to 40 */
  uint8_t client_id[4];           /* bytes 41 to 44 */
} OxAuctionNotificationMessage;

/* any Ox Auction Notification Message at all: every byte one the checker chooses */
static void any_ox_auction_notification_message(OxAuctionNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = arbitrary(); }
  record->auction_type = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
  record->customer_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_end_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
}

/* Ox Auction Notification Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_ox_auction_notification_message(const OxAuctionNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_id[i]; }
  wire[at++] = record->auction_type;
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }
  wire[at++] = record->customer_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_end_offset[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }

  return at;
}

/* Ox Auction Notification Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_ox_auction_notification_message(OxAuctionNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = wire[at++]; }
  record->auction_type = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }
  record->customer_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_end_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Auction Notification Message is what was written, byte for byte */
static void equal_ox_auction_notification_message(const OxAuctionNotificationMessage *read, const OxAuctionNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  assert(read->auction_type == written->auction_type);
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
  assert(read->customer_indicator == written->customer_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_id[i] == written->participant_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_end_offset[i] == written->auction_end_offset[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
}

/* Ox Auction Notification Message: written and read back, then read and written back */
static void check_ox_auction_notification_message(void) {
  OxAuctionNotificationMessage sent;
  OxAuctionNotificationMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_ox_auction_notification_message(&sent);
  assert(encode_ox_auction_notification_message(&sent, wire, 0) == 45);
  assert(decode_ox_auction_notification_message(&got, wire, 0) == 45);
  equal_ox_auction_notification_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_auction_notification_message(&got, wire, 0) == 45);
  assert(encode_ox_auction_notification_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Auction Cancel Message: 12 bytes ------------------------------------- */

/* Auction Cancel messages are used to disseminate the cancelation of an earlier Auction Notification message. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
  uint8_t auction_id[8];   /* bytes 4 to 11 */
} OxAuctionCancelMessage;

/* any Ox Auction Cancel Message at all: every byte one the checker chooses */
static void any_ox_auction_cancel_message(OxAuctionCancelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = arbitrary(); }
}

/* Ox Auction Cancel Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_ox_auction_cancel_message(const OxAuctionCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_id[i]; }

  return at;
}

/* Ox Auction Cancel Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_ox_auction_cancel_message(OxAuctionCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Auction Cancel Message is what was written, byte for byte */
static void equal_ox_auction_cancel_message(const OxAuctionCancelMessage *read, const OxAuctionCancelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
}

/* Ox Auction Cancel Message: written and read back, then read and written back */
static void check_ox_auction_cancel_message(void) {
  OxAuctionCancelMessage sent;
  OxAuctionCancelMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_ox_auction_cancel_message(&sent);
  assert(encode_ox_auction_cancel_message(&sent, wire, 0) == 12);
  assert(decode_ox_auction_cancel_message(&got, wire, 0) == 12);
  equal_ox_auction_cancel_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_auction_cancel_message(&got, wire, 0) == 12);
  assert(encode_ox_auction_cancel_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Auction Trade Message: 32 bytes -------------------------------------- */

/* Auction Trade messages are used to disseminate executions resulting from an options auction. */
typedef struct {
  uint8_t time_offset[4];   /* bytes 0 to 3 */
  uint8_t auction_id[8];    /* bytes 4 to 11 */
  uint8_t execution_id[8];  /* bytes 12 to 19 */
  uint8_t price_long[8];    /* bytes 20 to 27 */
  uint8_t contracts[4];     /* bytes 28 to 31 */
} OxAuctionTradeMessage;

/* any Ox Auction Trade Message at all: every byte one the checker chooses */
static void any_ox_auction_trade_message(OxAuctionTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = arbitrary(); }
}

/* Ox Auction Trade Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_ox_auction_trade_message(const OxAuctionTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contracts[i]; }

  return at;
}

/* Ox Auction Trade Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_ox_auction_trade_message(OxAuctionTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contracts[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Auction Trade Message is what was written, byte for byte */
static void equal_ox_auction_trade_message(const OxAuctionTradeMessage *read, const OxAuctionTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contracts[i] == written->contracts[i]); }
}

/* Ox Auction Trade Message: written and read back, then read and written back */
static void check_ox_auction_trade_message(void) {
  OxAuctionTradeMessage sent;
  OxAuctionTradeMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_ox_auction_trade_message(&sent);
  assert(encode_ox_auction_trade_message(&sent, wire, 0) == 32);
  assert(decode_ox_auction_trade_message(&got, wire, 0) == 32);
  equal_ox_auction_trade_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_auction_trade_message(&got, wire, 0) == 32);
  assert(encode_ox_auction_trade_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Soq Strike Range Update Message: 40 bytes ---------------------------- */

/* The SOQ Strike Range Update message is only available on the C1 Exchange. This message disseminates the minimum and maximum strike prices of the strike price range used to calculate the Special Opening Quote (SOQ) on a Volatility Settlement date. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t soq_identifier[20];     /* bytes 4 to 23 */
  uint8_t lower_strike_price[8];  /* bytes 24 to 31 */
  uint8_t upper_strike_price[8];  /* bytes 32 to 39 */
} OxSoqStrikeRangeUpdateMessage;

/* any Ox Soq Strike Range Update Message at all: every byte one the checker chooses */
static void any_ox_soq_strike_range_update_message(OxSoqStrikeRangeUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->soq_identifier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower_strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->upper_strike_price[i] = arbitrary(); }
}

/* Ox Soq Strike Range Update Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_ox_soq_strike_range_update_message(const OxSoqStrikeRangeUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->soq_identifier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_strike_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper_strike_price[i]; }

  return at;
}

/* Ox Soq Strike Range Update Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_ox_soq_strike_range_update_message(OxSoqStrikeRangeUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->soq_identifier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower_strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->upper_strike_price[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Soq Strike Range Update Message is what was written, byte for byte */
static void equal_ox_soq_strike_range_update_message(const OxSoqStrikeRangeUpdateMessage *read, const OxSoqStrikeRangeUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->soq_identifier[i] == written->soq_identifier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower_strike_price[i] == written->lower_strike_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->upper_strike_price[i] == written->upper_strike_price[i]); }
}

/* Ox Soq Strike Range Update Message: written and read back, then read and written back */
static void check_ox_soq_strike_range_update_message(void) {
  OxSoqStrikeRangeUpdateMessage sent;
  OxSoqStrikeRangeUpdateMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_ox_soq_strike_range_update_message(&sent);
  assert(encode_ox_soq_strike_range_update_message(&sent, wire, 0) == 40);
  assert(decode_ox_soq_strike_range_update_message(&got, wire, 0) == 40);
  equal_ox_soq_strike_range_update_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_soq_strike_range_update_message(&got, wire, 0) == 40);
  assert(encode_ox_soq_strike_range_update_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ox Constituent Symbol Mapping Message: 56 bytes ------------------------- */

/* The Constituent Symbol Mapping message is only available on the C1 Exchange. This message is used to communicate which options series are Constituent Series in a Volatility Settlement Special Opening Quote (SOQ). */
typedef struct {
  uint8_t feed_symbol[6];      /* bytes 0 to 5 */
  uint8_t osi_symbol[21];      /* bytes 6 to 26 */
  uint8_t symbol_condition;    /* byte 27 */
  uint8_t underlying[8];       /* bytes 28 to 35 */
  uint8_t soq_identifier[20];  /* bytes 36 to 55 */
} OxConstituentSymbolMappingMessage;

/* any Ox Constituent Symbol Mapping Message at all: every byte one the checker chooses */
static void any_ox_constituent_symbol_mapping_message(OxConstituentSymbolMappingMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 21; i++) { record->osi_symbol[i] = arbitrary(); }
  record->symbol_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->soq_identifier[i] = arbitrary(); }
}

/* Ox Constituent Symbol Mapping Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_ox_constituent_symbol_mapping_message(const OxConstituentSymbolMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->feed_symbol[i]; }
  for (size_t i = 0; i < 21; i++) { wire[at++] = record->osi_symbol[i]; }
  wire[at++] = record->symbol_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->soq_identifier[i]; }

  return at;
}

/* Ox Constituent Symbol Mapping Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_ox_constituent_symbol_mapping_message(OxConstituentSymbolMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 21; i++) { record->osi_symbol[i] = wire[at++]; }
  record->symbol_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->soq_identifier[i] = wire[at++]; }

  return at;
}

/* what was read of Ox Constituent Symbol Mapping Message is what was written, byte for byte */
static void equal_ox_constituent_symbol_mapping_message(const OxConstituentSymbolMappingMessage *read, const OxConstituentSymbolMappingMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->feed_symbol[i] == written->feed_symbol[i]); }
  for (size_t i = 0; i < 21; i++) { assert(read->osi_symbol[i] == written->osi_symbol[i]); }
  assert(read->symbol_condition == written->symbol_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->underlying[i] == written->underlying[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->soq_identifier[i] == written->soq_identifier[i]); }
}

/* Ox Constituent Symbol Mapping Message: written and read back, then read and written back */
static void check_ox_constituent_symbol_mapping_message(void) {
  OxConstituentSymbolMappingMessage sent;
  OxConstituentSymbolMappingMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_ox_constituent_symbol_mapping_message(&sent);
  assert(encode_ox_constituent_symbol_mapping_message(&sent, wire, 0) == 56);
  assert(decode_ox_constituent_symbol_mapping_message(&got, wire, 0) == 56);
  equal_ox_constituent_symbol_mapping_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_ox_constituent_symbol_mapping_message(&got, wire, 0) == 56);
  assert(encode_ox_constituent_symbol_mapping_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_ox_time_message();
  check_ox_unit_clear_message();
  check_ox_transaction_begin_message();
  check_ox_transaction_end_message();
  check_ox_order_executed_message();
  check_ox_order_executed_at_price_size_message();
  check_ox_reduce_size_long_message();
  check_ox_reduce_size_short_message();
  check_ox_delete_order_message();
  check_ox_trade_long_message();
  check_ox_trade_short_message();
  check_ox_trade_expanded_message();
  check_ox_trade_break_message();
  check_ox_end_of_session();
  check_ox_symbol_mapping_message();
  check_ox_trading_status_message();
  check_ox_width_update_message();
  check_ox_options_auction_update_message();
  check_ox_auction_summary_message();
  check_ox_auction_notification_message();
  check_ox_auction_cancel_message();
  check_ox_auction_trade_message();
  check_ox_soq_strike_range_update_message();
  check_ox_constituent_symbol_mapping_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
