// cboe/edgaequities/multicastdepthofbook/EdgaEquities_MulticastDepthOfBook_v2_41_64.c
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

/* ---- Eq Time Message: 4 bytes ------------------------------------------------ */

/* A Time message is immediately generated and sent when there is a PITCH event for a given clock second */
typedef struct {
  uint8_t time[4];  /* bytes 0 to 3 */
} EqTimeMessage;

/* any Eq Time Message at all: every byte one the checker chooses */
static void any_eq_time_message(EqTimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
}

/* Eq Time Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_eq_time_message(const EqTimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }

  return at;
}

/* Eq Time Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_eq_time_message(EqTimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }

  return at;
}

/* what was read of Eq Time Message is what was written, byte for byte */
static void equal_eq_time_message(const EqTimeMessage *read, const EqTimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
}

/* Eq Time Message: written and read back, then read and written back */
static void check_eq_time_message(void) {
  EqTimeMessage sent;
  EqTimeMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_eq_time_message(&sent);
  assert(encode_eq_time_message(&sent, wire, 0) == 4);
  assert(decode_eq_time_message(&got, wire, 0) == 4);
  equal_eq_time_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_time_message(&got, wire, 0) == 4);
  assert(encode_eq_time_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq Unit Clear Message: 4 bytes ------------------------------------------ */

/* The Unit Clear message instructs feed recipients to clear all orders for the Cboe book in the unit specified in the Sequenced Unit Header */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} EqUnitClearMessage;

/* any Eq Unit Clear Message at all: every byte one the checker chooses */
static void any_eq_unit_clear_message(EqUnitClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* Eq Unit Clear Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_eq_unit_clear_message(const EqUnitClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* Eq Unit Clear Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_eq_unit_clear_message(EqUnitClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Eq Unit Clear Message is what was written, byte for byte */
static void equal_eq_unit_clear_message(const EqUnitClearMessage *read, const EqUnitClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* Eq Unit Clear Message: written and read back, then read and written back */
static void check_eq_unit_clear_message(void) {
  EqUnitClearMessage sent;
  EqUnitClearMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_eq_unit_clear_message(&sent);
  assert(encode_eq_unit_clear_message(&sent, wire, 0) == 4);
  assert(decode_eq_unit_clear_message(&got, wire, 0) == 4);
  equal_eq_unit_clear_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_unit_clear_message(&got, wire, 0) == 4);
  assert(encode_eq_unit_clear_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq Order Executed Message: 24 bytes ------------------------------------- */

/* Order Executed messages are sent when a visible order on the Cboe book is executed in whole or in part */
typedef struct {
  uint8_t time_offset[4];        /* bytes 0 to 3 */
  uint8_t order_id[8];           /* bytes 4 to 11 */
  uint8_t executed_quantity[4];  /* bytes 12 to 15 */
  uint8_t execution_id[8];       /* bytes 16 to 23 */
} EqOrderExecutedMessage;

/* any Eq Order Executed Message at all: every byte one the checker chooses */
static void any_eq_order_executed_message(EqOrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Eq Order Executed Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_eq_order_executed_message(const EqOrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Eq Order Executed Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_eq_order_executed_message(EqOrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Eq Order Executed Message is what was written, byte for byte */
static void equal_eq_order_executed_message(const EqOrderExecutedMessage *read, const EqOrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Eq Order Executed Message: written and read back, then read and written back */
static void check_eq_order_executed_message(void) {
  EqOrderExecutedMessage sent;
  EqOrderExecutedMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_eq_order_executed_message(&sent);
  assert(encode_eq_order_executed_message(&sent, wire, 0) == 24);
  assert(decode_eq_order_executed_message(&got, wire, 0) == 24);
  equal_eq_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_order_executed_message(&got, wire, 0) == 24);
  assert(encode_eq_order_executed_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq Order Executed At Price Size Message: 36 bytes ----------------------- */

/* Order Executed at Price/Size messages are sent when a visible order on the Cboe book is executed in whole or in part at a different price than the limit price on the original Add Order message or the limit order price in the latest Modify Order message referencing the Order Id */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t order_id[8];            /* bytes 4 to 11 */
  uint8_t executed_quantity[4];   /* bytes 12 to 15 */
  uint8_t remaining_quantity[4];  /* bytes 16 to 19 */
  uint8_t execution_id[8];        /* bytes 20 to 27 */
  uint8_t price_long[8];          /* bytes 28 to 35 */
} EqOrderExecutedAtPriceSizeMessage;

/* any Eq Order Executed At Price Size Message at all: every byte one the checker chooses */
static void any_eq_order_executed_at_price_size_message(EqOrderExecutedAtPriceSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
}

/* Eq Order Executed At Price Size Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_eq_order_executed_at_price_size_message(const EqOrderExecutedAtPriceSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->remaining_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }

  return at;
}

/* Eq Order Executed At Price Size Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_eq_order_executed_at_price_size_message(EqOrderExecutedAtPriceSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }

  return at;
}

/* what was read of Eq Order Executed At Price Size Message is what was written, byte for byte */
static void equal_eq_order_executed_at_price_size_message(const EqOrderExecutedAtPriceSizeMessage *read, const EqOrderExecutedAtPriceSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->remaining_quantity[i] == written->remaining_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
}

/* Eq Order Executed At Price Size Message: written and read back, then read and written back */
static void check_eq_order_executed_at_price_size_message(void) {
  EqOrderExecutedAtPriceSizeMessage sent;
  EqOrderExecutedAtPriceSizeMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_eq_order_executed_at_price_size_message(&sent);
  assert(encode_eq_order_executed_at_price_size_message(&sent, wire, 0) == 36);
  assert(decode_eq_order_executed_at_price_size_message(&got, wire, 0) == 36);
  equal_eq_order_executed_at_price_size_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_order_executed_at_price_size_message(&got, wire, 0) == 36);
  assert(encode_eq_order_executed_at_price_size_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq Reduce Size Long Message: 16 bytes ----------------------------------- */

/* Reduce Size messages are sent when a visible order on the Cboe book is partially reduced */
typedef struct {
  uint8_t time_offset[4];             /* bytes 0 to 3 */
  uint8_t order_id[8];                /* bytes 4 to 11 */
  uint8_t canceled_quantity_long[4];  /* bytes 12 to 15 */
} EqReduceSizeLongMessage;

/* any Eq Reduce Size Long Message at all: every byte one the checker chooses */
static void any_eq_reduce_size_long_message(EqReduceSizeLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->canceled_quantity_long[i] = arbitrary(); }
}

/* Eq Reduce Size Long Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_eq_reduce_size_long_message(const EqReduceSizeLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->canceled_quantity_long[i]; }

  return at;
}

/* Eq Reduce Size Long Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_eq_reduce_size_long_message(EqReduceSizeLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->canceled_quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Eq Reduce Size Long Message is what was written, byte for byte */
static void equal_eq_reduce_size_long_message(const EqReduceSizeLongMessage *read, const EqReduceSizeLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->canceled_quantity_long[i] == written->canceled_quantity_long[i]); }
}

/* Eq Reduce Size Long Message: written and read back, then read and written back */
static void check_eq_reduce_size_long_message(void) {
  EqReduceSizeLongMessage sent;
  EqReduceSizeLongMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_eq_reduce_size_long_message(&sent);
  assert(encode_eq_reduce_size_long_message(&sent, wire, 0) == 16);
  assert(decode_eq_reduce_size_long_message(&got, wire, 0) == 16);
  equal_eq_reduce_size_long_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_reduce_size_long_message(&got, wire, 0) == 16);
  assert(encode_eq_reduce_size_long_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq Reduce Size Short Message: 14 bytes ---------------------------------- */

/* Reduce Size messages are sent when a visible order on the Cboe book is partially reduced */
typedef struct {
  uint8_t time_offset[4];              /* bytes 0 to 3 */
  uint8_t order_id[8];                 /* bytes 4 to 11 */
  uint8_t canceled_quantity_short[2];  /* bytes 12 to 13 */
} EqReduceSizeShortMessage;

/* any Eq Reduce Size Short Message at all: every byte one the checker chooses */
static void any_eq_reduce_size_short_message(EqReduceSizeShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->canceled_quantity_short[i] = arbitrary(); }
}

/* Eq Reduce Size Short Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_eq_reduce_size_short_message(const EqReduceSizeShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->canceled_quantity_short[i]; }

  return at;
}

/* Eq Reduce Size Short Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_eq_reduce_size_short_message(EqReduceSizeShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->canceled_quantity_short[i] = wire[at++]; }

  return at;
}

/* what was read of Eq Reduce Size Short Message is what was written, byte for byte */
static void equal_eq_reduce_size_short_message(const EqReduceSizeShortMessage *read, const EqReduceSizeShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->canceled_quantity_short[i] == written->canceled_quantity_short[i]); }
}

/* Eq Reduce Size Short Message: written and read back, then read and written back */
static void check_eq_reduce_size_short_message(void) {
  EqReduceSizeShortMessage sent;
  EqReduceSizeShortMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_eq_reduce_size_short_message(&sent);
  assert(encode_eq_reduce_size_short_message(&sent, wire, 0) == 14);
  assert(decode_eq_reduce_size_short_message(&got, wire, 0) == 14);
  equal_eq_reduce_size_short_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_reduce_size_short_message(&got, wire, 0) == 14);
  assert(encode_eq_reduce_size_short_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq Delete Order Message: 12 bytes --------------------------------------- */

/* The Delete Order message is sent whenever a booked order is cancelled or leaves the order book */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
  uint8_t order_id[8];     /* bytes 4 to 11 */
} EqDeleteOrderMessage;

/* any Eq Delete Order Message at all: every byte one the checker chooses */
static void any_eq_delete_order_message(EqDeleteOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Eq Delete Order Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_eq_delete_order_message(const EqDeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Eq Delete Order Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_eq_delete_order_message(EqDeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Eq Delete Order Message is what was written, byte for byte */
static void equal_eq_delete_order_message(const EqDeleteOrderMessage *read, const EqDeleteOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Eq Delete Order Message: written and read back, then read and written back */
static void check_eq_delete_order_message(void) {
  EqDeleteOrderMessage sent;
  EqDeleteOrderMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_eq_delete_order_message(&sent);
  assert(encode_eq_delete_order_message(&sent, wire, 0) == 12);
  assert(decode_eq_delete_order_message(&got, wire, 0) == 12);
  equal_eq_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_delete_order_message(&got, wire, 0) == 12);
  assert(encode_eq_delete_order_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq Trade Long Message: 39 bytes ----------------------------------------- */

/* The Trade message provides information about executions of non-displayed orders on the Cboe book and routed executions to other trading centers */
typedef struct {
  uint8_t time_offset[4];    /* bytes 0 to 3 */
  uint8_t order_id[8];       /* bytes 4 to 11 */
  uint8_t side_indicator;    /* byte 12 */
  uint8_t quantity_long[4];  /* bytes 13 to 16 */
  uint8_t symbol_short[6];   /* bytes 17 to 22 */
  uint8_t price_long[8];     /* bytes 23 to 30 */
  uint8_t execution_id[8];   /* bytes 31 to 38 */
} EqTradeLongMessage;

/* any Eq Trade Long Message at all: every byte one the checker chooses */
static void any_eq_trade_long_message(EqTradeLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Eq Trade Long Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_eq_trade_long_message(const EqTradeLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Eq Trade Long Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_eq_trade_long_message(EqTradeLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Eq Trade Long Message is what was written, byte for byte */
static void equal_eq_trade_long_message(const EqTradeLongMessage *read, const EqTradeLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Eq Trade Long Message: written and read back, then read and written back */
static void check_eq_trade_long_message(void) {
  EqTradeLongMessage sent;
  EqTradeLongMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_eq_trade_long_message(&sent);
  assert(encode_eq_trade_long_message(&sent, wire, 0) == 39);
  assert(decode_eq_trade_long_message(&got, wire, 0) == 39);
  equal_eq_trade_long_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_trade_long_message(&got, wire, 0) == 39);
  assert(encode_eq_trade_long_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq Trade Short Message: 31 bytes ---------------------------------------- */

/* The Trade message provides information about executions of non-displayed orders on the Cboe book and routed executions to other trading centers */
typedef struct {
  uint8_t time_offset[4];     /* bytes 0 to 3 */
  uint8_t order_id[8];        /* bytes 4 to 11 */
  uint8_t side_indicator;     /* byte 12 */
  uint8_t quantity_short[2];  /* bytes 13 to 14 */
  uint8_t symbol_short[6];    /* bytes 15 to 20 */
  uint8_t price_short[2];     /* bytes 21 to 22 */
  uint8_t execution_id[8];    /* bytes 23 to 30 */
} EqTradeShortMessage;

/* any Eq Trade Short Message at all: every byte one the checker chooses */
static void any_eq_trade_short_message(EqTradeShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Eq Trade Short Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_eq_trade_short_message(const EqTradeShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Eq Trade Short Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_eq_trade_short_message(EqTradeShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Eq Trade Short Message is what was written, byte for byte */
static void equal_eq_trade_short_message(const EqTradeShortMessage *read, const EqTradeShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Eq Trade Short Message: written and read back, then read and written back */
static void check_eq_trade_short_message(void) {
  EqTradeShortMessage sent;
  EqTradeShortMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_eq_trade_short_message(&sent);
  assert(encode_eq_trade_short_message(&sent, wire, 0) == 31);
  assert(decode_eq_trade_short_message(&got, wire, 0) == 31);
  equal_eq_trade_short_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_trade_short_message(&got, wire, 0) == 31);
  assert(encode_eq_trade_short_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq Trade Expanded Message: 41 bytes ------------------------------------- */

/* The Trade message provides information about executions of non-displayed orders on the Cboe book and routed executions to other trading centers. Expanded version accommodates larger symbol sizes possible through the ISRA plan. */
typedef struct {
  uint8_t time_offset[4];    /* bytes 0 to 3 */
  uint8_t order_id[8];       /* bytes 4 to 11 */
  uint8_t side_indicator;    /* byte 12 */
  uint8_t quantity_long[4];  /* bytes 13 to 16 */
  uint8_t symbol_long[8];    /* bytes 17 to 24 */
  uint8_t price_long[8];     /* bytes 25 to 32 */
  uint8_t execution_id[8];   /* bytes 33 to 40 */
} EqTradeExpandedMessage;

/* any Eq Trade Expanded Message at all: every byte one the checker chooses */
static void any_eq_trade_expanded_message(EqTradeExpandedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Eq Trade Expanded Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_eq_trade_expanded_message(const EqTradeExpandedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Eq Trade Expanded Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_eq_trade_expanded_message(EqTradeExpandedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Eq Trade Expanded Message is what was written, byte for byte */
static void equal_eq_trade_expanded_message(const EqTradeExpandedMessage *read, const EqTradeExpandedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Eq Trade Expanded Message: written and read back, then read and written back */
static void check_eq_trade_expanded_message(void) {
  EqTradeExpandedMessage sent;
  EqTradeExpandedMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_eq_trade_expanded_message(&sent);
  assert(encode_eq_trade_expanded_message(&sent, wire, 0) == 41);
  assert(decode_eq_trade_expanded_message(&got, wire, 0) == 41);
  equal_eq_trade_expanded_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_trade_expanded_message(&got, wire, 0) == 41);
  assert(encode_eq_trade_expanded_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq Trade Break Message: 12 bytes ---------------------------------------- */

/* The Trade Break message is sent whenever an execution on Cboe is broken */
typedef struct {
  uint8_t time_offset[4];   /* bytes 0 to 3 */
  uint8_t execution_id[8];  /* bytes 4 to 11 */
} EqTradeBreakMessage;

/* any Eq Trade Break Message at all: every byte one the checker chooses */
static void any_eq_trade_break_message(EqTradeBreakMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Eq Trade Break Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_eq_trade_break_message(const EqTradeBreakMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Eq Trade Break Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_eq_trade_break_message(EqTradeBreakMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Eq Trade Break Message is what was written, byte for byte */
static void equal_eq_trade_break_message(const EqTradeBreakMessage *read, const EqTradeBreakMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Eq Trade Break Message: written and read back, then read and written back */
static void check_eq_trade_break_message(void) {
  EqTradeBreakMessage sent;
  EqTradeBreakMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_eq_trade_break_message(&sent);
  assert(encode_eq_trade_break_message(&sent, wire, 0) == 12);
  assert(decode_eq_trade_break_message(&got, wire, 0) == 12);
  equal_eq_trade_break_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_trade_break_message(&got, wire, 0) == 12);
  assert(encode_eq_trade_break_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq End Of Session: 4 bytes ---------------------------------------------- */

/* The End of Session message is sent for each unit when the unit shuts down */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} EqEndOfSession;

/* any Eq End Of Session at all: every byte one the checker chooses */
static void any_eq_end_of_session(EqEndOfSession *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* Eq End Of Session to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_eq_end_of_session(const EqEndOfSession *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* Eq End Of Session off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_eq_end_of_session(EqEndOfSession *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Eq End Of Session is what was written, byte for byte */
static void equal_eq_end_of_session(const EqEndOfSession *read, const EqEndOfSession *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* Eq End Of Session: written and read back, then read and written back */
static void check_eq_end_of_session(void) {
  EqEndOfSession sent;
  EqEndOfSession got;
  uint8_t wire[4];
  uint8_t again[4];

  any_eq_end_of_session(&sent);
  assert(encode_eq_end_of_session(&sent, wire, 0) == 4);
  assert(decode_eq_end_of_session(&got, wire, 0) == 4);
  equal_eq_end_of_session(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_end_of_session(&got, wire, 0) == 4);
  assert(encode_eq_end_of_session(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq Trading Status Message: 16 bytes ------------------------------------- */

/* The Trading Status message is used to indicate the current trading status of a security */
typedef struct {
  uint8_t time_offset[4];     /* bytes 0 to 3 */
  uint8_t symbol_long[8];     /* bytes 4 to 11 */
  uint8_t trading_status;     /* byte 12 */
  uint8_t reg_sho_action;     /* byte 13 */
  uint8_t reserved_1;         /* byte 14 */
  uint8_t second_reserved_1;  /* byte 15 */
} EqTradingStatusMessage;

/* any Eq Trading Status Message at all: every byte one the checker chooses */
static void any_eq_trading_status_message(EqTradingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->reg_sho_action = arbitrary();
  record->reserved_1 = arbitrary();
  record->second_reserved_1 = arbitrary();
}

/* Eq Trading Status Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_eq_trading_status_message(const EqTradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->reg_sho_action;
  wire[at++] = record->reserved_1;
  wire[at++] = record->second_reserved_1;

  return at;
}

/* Eq Trading Status Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_eq_trading_status_message(EqTradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->reg_sho_action = wire[at++];
  record->reserved_1 = wire[at++];
  record->second_reserved_1 = wire[at++];

  return at;
}

/* what was read of Eq Trading Status Message is what was written, byte for byte */
static void equal_eq_trading_status_message(const EqTradingStatusMessage *read, const EqTradingStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->reg_sho_action == written->reg_sho_action);
  assert(read->reserved_1 == written->reserved_1);
  assert(read->second_reserved_1 == written->second_reserved_1);
}

/* Eq Trading Status Message: written and read back, then read and written back */
static void check_eq_trading_status_message(void) {
  EqTradingStatusMessage sent;
  EqTradingStatusMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_eq_trading_status_message(&sent);
  assert(encode_eq_trading_status_message(&sent, wire, 0) == 16);
  assert(decode_eq_trading_status_message(&got, wire, 0) == 16);
  equal_eq_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_trading_status_message(&got, wire, 0) == 16);
  assert(encode_eq_trading_status_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq Auction Update Message: 45 bytes ------------------------------------- */

/* Auction Update messages are used to disseminate Cboe price and size information during auctions for Cboe listed securities and for Cboe Market Close crosses on BZX, and for Periodic Auctions on BYX */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t stock_symbol[8];        /* bytes 4 to 11 */
  uint8_t auction_type;           /* byte 12 */
  uint8_t reference_price[8];     /* bytes 13 to 20 */
  uint8_t buy_shares[4];          /* bytes 21 to 24 */
  uint8_t sell_shares[4];         /* bytes 25 to 28 */
  uint8_t indicative_price[8];    /* bytes 29 to 36 */
  uint8_t auction_only_price[8];  /* bytes 37 to 44 */
} EqAuctionUpdateMessage;

/* any Eq Auction Update Message at all: every byte one the checker chooses */
static void any_eq_auction_update_message(EqAuctionUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_only_price[i] = arbitrary(); }
}

/* Eq Auction Update Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_eq_auction_update_message(const EqAuctionUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_only_price[i]; }

  return at;
}

/* Eq Auction Update Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_eq_auction_update_message(EqAuctionUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_only_price[i] = wire[at++]; }

  return at;
}

/* what was read of Eq Auction Update Message is what was written, byte for byte */
static void equal_eq_auction_update_message(const EqAuctionUpdateMessage *read, const EqAuctionUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_shares[i] == written->buy_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_shares[i] == written->sell_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_price[i] == written->indicative_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_only_price[i] == written->auction_only_price[i]); }
}

/* Eq Auction Update Message: written and read back, then read and written back */
static void check_eq_auction_update_message(void) {
  EqAuctionUpdateMessage sent;
  EqAuctionUpdateMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_eq_auction_update_message(&sent);
  assert(encode_eq_auction_update_message(&sent, wire, 0) == 45);
  assert(decode_eq_auction_update_message(&got, wire, 0) == 45);
  equal_eq_auction_update_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_auction_update_message(&got, wire, 0) == 45);
  assert(encode_eq_auction_update_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq Auction Summary Message: 25 bytes ------------------------------------ */

/* Auction Summary messages are used to disseminate the results of an auction of a Cboe listed security on BZX, and for Periodic Auctions on BYX */
typedef struct {
  uint8_t time_offset[4];       /* bytes 0 to 3 */
  uint8_t stock_symbol[8];      /* bytes 4 to 11 */
  uint8_t auction_type;         /* byte 12 */
  uint8_t price_long[8];        /* bytes 13 to 20 */
  uint8_t shares_contracts[4];  /* bytes 21 to 24 */
} EqAuctionSummaryMessage;

/* any Eq Auction Summary Message at all: every byte one the checker chooses */
static void any_eq_auction_summary_message(EqAuctionSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares_contracts[i] = arbitrary(); }
}

/* Eq Auction Summary Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_eq_auction_summary_message(const EqAuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares_contracts[i]; }

  return at;
}

/* Eq Auction Summary Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_eq_auction_summary_message(EqAuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares_contracts[i] = wire[at++]; }

  return at;
}

/* what was read of Eq Auction Summary Message is what was written, byte for byte */
static void equal_eq_auction_summary_message(const EqAuctionSummaryMessage *read, const EqAuctionSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares_contracts[i] == written->shares_contracts[i]); }
}

/* Eq Auction Summary Message: written and read back, then read and written back */
static void check_eq_auction_summary_message(void) {
  EqAuctionSummaryMessage sent;
  EqAuctionSummaryMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_eq_auction_summary_message(&sent);
  assert(encode_eq_auction_summary_message(&sent, wire, 0) == 25);
  assert(decode_eq_auction_summary_message(&got, wire, 0) == 25);
  equal_eq_auction_summary_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_auction_summary_message(&got, wire, 0) == 25);
  assert(encode_eq_auction_summary_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Eq Retail Price Improvement Message: 13 bytes --------------------------- */

/* This message is a Retail Liquidity Indicator (RLI) that includes symbol and side, but not price and size. BYX Only. */
typedef struct {
  uint8_t time_offset[4];            /* bytes 0 to 3 */
  uint8_t symbol_long[8];            /* bytes 4 to 11 */
  uint8_t retail_price_improvement;  /* byte 12 */
} EqRetailPriceImprovementMessage;

/* any Eq Retail Price Improvement Message at all: every byte one the checker chooses */
static void any_eq_retail_price_improvement_message(EqRetailPriceImprovementMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = arbitrary(); }
  record->retail_price_improvement = arbitrary();
}

/* Eq Retail Price Improvement Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_eq_retail_price_improvement_message(const EqRetailPriceImprovementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->retail_price_improvement;

  return at;
}

/* Eq Retail Price Improvement Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_eq_retail_price_improvement_message(EqRetailPriceImprovementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = wire[at++]; }
  record->retail_price_improvement = wire[at++];

  return at;
}

/* what was read of Eq Retail Price Improvement Message is what was written, byte for byte */
static void equal_eq_retail_price_improvement_message(const EqRetailPriceImprovementMessage *read, const EqRetailPriceImprovementMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->retail_price_improvement == written->retail_price_improvement);
}

/* Eq Retail Price Improvement Message: written and read back, then read and written back */
static void check_eq_retail_price_improvement_message(void) {
  EqRetailPriceImprovementMessage sent;
  EqRetailPriceImprovementMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_eq_retail_price_improvement_message(&sent);
  assert(encode_eq_retail_price_improvement_message(&sent, wire, 0) == 13);
  assert(decode_eq_retail_price_improvement_message(&got, wire, 0) == 13);
  equal_eq_retail_price_improvement_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_eq_retail_price_improvement_message(&got, wire, 0) == 13);
  assert(encode_eq_retail_price_improvement_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_eq_time_message();
  check_eq_unit_clear_message();
  check_eq_order_executed_message();
  check_eq_order_executed_at_price_size_message();
  check_eq_reduce_size_long_message();
  check_eq_reduce_size_short_message();
  check_eq_delete_order_message();
  check_eq_trade_long_message();
  check_eq_trade_short_message();
  check_eq_trade_expanded_message();
  check_eq_trade_break_message();
  check_eq_end_of_session();
  check_eq_trading_status_message();
  check_eq_auction_update_message();
  check_eq_auction_summary_message();
  check_eq_retail_price_improvement_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
