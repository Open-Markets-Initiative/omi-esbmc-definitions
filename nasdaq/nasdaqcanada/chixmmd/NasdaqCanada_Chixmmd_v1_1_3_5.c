// nasdaq/nasdaqcanada/chixmmd/NasdaqCanada_Chixmmd_v1_1_3_5.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) CHIXMMD Multicast Market Data
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

/* ---- Packet Header: 6 bytes -------------------------------------------------- */

/* CHIXMMD multicast packet header */
typedef struct {
  uint8_t sequence[4];       /* bytes 0 to 3 */
  uint8_t message_count[2];  /* bytes 4 to 5 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = arbitrary(); }
}

/* Packet Header to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_count[i]; }

  return at;
}

/* Packet Header off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_count[i] == written->message_count[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[6];
  uint8_t again[6];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 6);
  assert(decode_packet_header(&got, wire, 0) == 6);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 6);
  assert(encode_packet_header(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat: 10 bytes ----------------------------------------------------- */

/* The heartbeat carries the current session of the market data stream, to be used in the Login Request of the recovery service */
typedef struct {
  uint8_t session[10];  /* bytes 0 to 9 */
} Heartbeat;

/* any Heartbeat at all: every byte one the checker chooses */
static void any_heartbeat(Heartbeat *record) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = arbitrary(); }
}

/* Heartbeat to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat(const Heartbeat *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->session[i]; }

  return at;
}

/* Heartbeat off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat(Heartbeat *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat is what was written, byte for byte */
static void equal_heartbeat(const Heartbeat *read, const Heartbeat *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->session[i] == written->session[i]); }
}

/* Heartbeat: written and read back, then read and written back */
static void check_heartbeat(void) {
  Heartbeat sent;
  Heartbeat got;
  uint8_t wire[10];
  uint8_t again[10];

  any_heartbeat(&sent);
  assert(encode_heartbeat(&sent, wire, 0) == 10);
  assert(decode_heartbeat(&got, wire, 0) == 10);
  equal_heartbeat(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat(&got, wire, 0) == 10);
  assert(encode_heartbeat(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 11 bytes ------------------------------------------------ */

/* Length of the market data message, then its timestamp and type */
typedef struct {
  uint8_t length[2];     /* bytes 0 to 1 */
  uint8_t timestamp[8];  /* bytes 2 to 9 */
  uint8_t message_type;  /* byte 10 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[11];
  uint8_t again[11];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 11);
  assert(decode_message_header(&got, wire, 0) == 11);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 11);
  assert(encode_message_header(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 39 bytes --------------------------------------------- */

/* An Add Order Message indicates that CXC or CX2 has accepted a visible order into the book. It includes a day-unique Order Reference key assigned to the order. The issuing of an Add Order Message is not necessarily always for a new order (see Modification of Existing Orders). Not applicable to CXD. */
typedef struct {
  uint8_t order_reference[9];  /* bytes 0 to 8 */
  uint8_t buy_sell_indicator;  /* byte 9 */
  uint8_t shares[6];           /* bytes 10 to 15 */
  uint8_t stock[10];           /* bytes 16 to 25 */
  uint8_t price[10];           /* bytes 26 to 35 */
  uint8_t broker[3];           /* bytes 36 to 38 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = arbitrary(); }
}

/* Add Order Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->order_reference[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker[i]; }

  return at;
}

/* Add Order Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->order_reference[i] == written->order_reference[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->broker[i] == written->broker[i]); }
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 39);
  assert(decode_add_order_message(&got, wire, 0) == 39);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 39);
  assert(encode_add_order_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Form Add Order Message: 52 bytes ----------------------------------- */

/* An Add Order Message indicates that CXC or CX2 has accepted a visible order into the book. It includes a day-unique Order Reference key assigned to the order. The issuing of an Add Order Message is not necessarily always for a new order (see Modification of Existing Orders). Not applicable to CXD. Long form messages are used when either the price or size is larger than the standard messages can permit. */
typedef struct {
  uint8_t order_reference[9];  /* bytes 0 to 8 */
  uint8_t buy_sell_indicator;  /* byte 9 */
  uint8_t long_shares[10];     /* bytes 10 to 19 */
  uint8_t stock[10];           /* bytes 20 to 29 */
  uint8_t long_price[19];      /* bytes 30 to 48 */
  uint8_t broker[3];           /* bytes 49 to 51 */
} LongFormAddOrderMessage;

/* any Long Form Add Order Message at all: every byte one the checker chooses */
static void any_long_form_add_order_message(LongFormAddOrderMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->long_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 19; i++) { record->long_price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = arbitrary(); }
}

/* Long Form Add Order Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_long_form_add_order_message(const LongFormAddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->order_reference[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->long_shares[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->long_price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker[i]; }

  return at;
}

/* Long Form Add Order Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_long_form_add_order_message(LongFormAddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->long_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 19; i++) { record->long_price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = wire[at++]; }

  return at;
}

/* what was read of Long Form Add Order Message is what was written, byte for byte */
static void equal_long_form_add_order_message(const LongFormAddOrderMessage *read, const LongFormAddOrderMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->order_reference[i] == written->order_reference[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 10; i++) { assert(read->long_shares[i] == written->long_shares[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 19; i++) { assert(read->long_price[i] == written->long_price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->broker[i] == written->broker[i]); }
}

/* Long Form Add Order Message: written and read back, then read and written back */
static void check_long_form_add_order_message(void) {
  LongFormAddOrderMessage sent;
  LongFormAddOrderMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_long_form_add_order_message(&sent);
  assert(encode_long_form_add_order_message(&sent, wire, 0) == 52);
  assert(decode_long_form_add_order_message(&got, wire, 0) == 52);
  equal_long_form_add_order_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_long_form_add_order_message(&got, wire, 0) == 52);
  assert(encode_long_form_add_order_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Execution Message: 40 bytes --------------------------------------- */

/* An Order Execution Message is sent whenever an order on the book is executed in whole or in part. Not applicable to CXD. */
typedef struct {
  uint8_t order_reference[9];         /* bytes 0 to 8 */
  uint8_t executed_shares[6];         /* bytes 9 to 14 */
  uint8_t trade_reference[9];         /* bytes 15 to 23 */
  uint8_t contra_order_reference[9];  /* bytes 24 to 32 */
  uint8_t trade_attribute;            /* byte 33 */
  uint8_t broker[3];                  /* bytes 34 to 36 */
  uint8_t contra_broker[3];           /* bytes 37 to 39 */
} OrderExecutionMessage;

/* any Order Execution Message at all: every byte one the checker chooses */
static void any_order_execution_message(OrderExecutionMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->trade_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->contra_order_reference[i] = arbitrary(); }
  record->trade_attribute = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->broker[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = arbitrary(); }
}

/* Order Execution Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_order_execution_message(const OrderExecutionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->order_reference[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->executed_shares[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->trade_reference[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->contra_order_reference[i]; }
  wire[at++] = record->trade_attribute;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->contra_broker[i]; }

  return at;
}

/* Order Execution Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_order_execution_message(OrderExecutionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->trade_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->contra_order_reference[i] = wire[at++]; }
  record->trade_attribute = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->broker[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = wire[at++]; }

  return at;
}

/* what was read of Order Execution Message is what was written, byte for byte */
static void equal_order_execution_message(const OrderExecutionMessage *read, const OrderExecutionMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->order_reference[i] == written->order_reference[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->executed_shares[i] == written->executed_shares[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->trade_reference[i] == written->trade_reference[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->contra_order_reference[i] == written->contra_order_reference[i]); }
  assert(read->trade_attribute == written->trade_attribute);
  for (size_t i = 0; i < 3; i++) { assert(read->broker[i] == written->broker[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->contra_broker[i] == written->contra_broker[i]); }
}

/* Order Execution Message: written and read back, then read and written back */
static void check_order_execution_message(void) {
  OrderExecutionMessage sent;
  OrderExecutionMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_order_execution_message(&sent);
  assert(encode_order_execution_message(&sent, wire, 0) == 40);
  assert(decode_order_execution_message(&got, wire, 0) == 40);
  equal_order_execution_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_order_execution_message(&got, wire, 0) == 40);
  assert(encode_order_execution_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Form Order Execution Message: 44 bytes ----------------------------- */

/* An Order Execution Message is sent whenever an order on the book is executed in whole or in part. Not applicable to CXD. Long form messages are used when either the price or size is larger than the standard messages can permit. */
typedef struct {
  uint8_t order_reference[9];         /* bytes 0 to 8 */
  uint8_t long_executed_shares[10];   /* bytes 9 to 18 */
  uint8_t trade_reference[9];         /* bytes 19 to 27 */
  uint8_t contra_order_reference[9];  /* bytes 28 to 36 */
  uint8_t trade_attribute;            /* byte 37 */
  uint8_t broker[3];                  /* bytes 38 to 40 */
  uint8_t contra_broker[3];           /* bytes 41 to 43 */
} LongFormOrderExecutionMessage;

/* any Long Form Order Execution Message at all: every byte one the checker chooses */
static void any_long_form_order_execution_message(LongFormOrderExecutionMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->long_executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->trade_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->contra_order_reference[i] = arbitrary(); }
  record->trade_attribute = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->broker[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = arbitrary(); }
}

/* Long Form Order Execution Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_long_form_order_execution_message(const LongFormOrderExecutionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->order_reference[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->long_executed_shares[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->trade_reference[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->contra_order_reference[i]; }
  wire[at++] = record->trade_attribute;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->contra_broker[i]; }

  return at;
}

/* Long Form Order Execution Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_long_form_order_execution_message(LongFormOrderExecutionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->long_executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->trade_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->contra_order_reference[i] = wire[at++]; }
  record->trade_attribute = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->broker[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = wire[at++]; }

  return at;
}

/* what was read of Long Form Order Execution Message is what was written, byte for byte */
static void equal_long_form_order_execution_message(const LongFormOrderExecutionMessage *read, const LongFormOrderExecutionMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->order_reference[i] == written->order_reference[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->long_executed_shares[i] == written->long_executed_shares[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->trade_reference[i] == written->trade_reference[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->contra_order_reference[i] == written->contra_order_reference[i]); }
  assert(read->trade_attribute == written->trade_attribute);
  for (size_t i = 0; i < 3; i++) { assert(read->broker[i] == written->broker[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->contra_broker[i] == written->contra_broker[i]); }
}

/* Long Form Order Execution Message: written and read back, then read and written back */
static void check_long_form_order_execution_message(void) {
  LongFormOrderExecutionMessage sent;
  LongFormOrderExecutionMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_long_form_order_execution_message(&sent);
  assert(encode_long_form_order_execution_message(&sent, wire, 0) == 44);
  assert(decode_long_form_order_execution_message(&got, wire, 0) == 44);
  equal_long_form_order_execution_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_long_form_order_execution_message(&got, wire, 0) == 44);
  assert(encode_long_form_order_execution_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Message: 15 bytes ------------------------------------------ */

/* An Order Cancel Message is sent whenever an order on the book is fully canceled, its quantity revised down or when a pegged order is re-priced. Not applicable to CXD. */
typedef struct {
  uint8_t order_reference[9];  /* bytes 0 to 8 */
  uint8_t canceled_shares[6];  /* bytes 9 to 14 */
} OrderCancelMessage;

/* any Order Cancel Message at all: every byte one the checker chooses */
static void any_order_cancel_message(OrderCancelMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->canceled_shares[i] = arbitrary(); }
}

/* Order Cancel Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_message(const OrderCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->order_reference[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->canceled_shares[i]; }

  return at;
}

/* Order Cancel Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_message(OrderCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->canceled_shares[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Message is what was written, byte for byte */
static void equal_order_cancel_message(const OrderCancelMessage *read, const OrderCancelMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->order_reference[i] == written->order_reference[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->canceled_shares[i] == written->canceled_shares[i]); }
}

/* Order Cancel Message: written and read back, then read and written back */
static void check_order_cancel_message(void) {
  OrderCancelMessage sent;
  OrderCancelMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_order_cancel_message(&sent);
  assert(encode_order_cancel_message(&sent, wire, 0) == 15);
  assert(decode_order_cancel_message(&got, wire, 0) == 15);
  equal_order_cancel_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_message(&got, wire, 0) == 15);
  assert(encode_order_cancel_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Form Order Cancel Message: 19 bytes -------------------------------- */

/* An Order Cancel Message is sent whenever an order on the book is fully canceled, its quantity revised down or when a pegged order is re-priced. Not applicable to CXD. Long form messages are used when either the price or size is larger than the standard messages can permit. */
typedef struct {
  uint8_t order_reference[9];        /* bytes 0 to 8 */
  uint8_t long_canceled_shares[10];  /* bytes 9 to 18 */
} LongFormOrderCancelMessage;

/* any Long Form Order Cancel Message at all: every byte one the checker chooses */
static void any_long_form_order_cancel_message(LongFormOrderCancelMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->long_canceled_shares[i] = arbitrary(); }
}

/* Long Form Order Cancel Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_long_form_order_cancel_message(const LongFormOrderCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->order_reference[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->long_canceled_shares[i]; }

  return at;
}

/* Long Form Order Cancel Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_long_form_order_cancel_message(LongFormOrderCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->long_canceled_shares[i] = wire[at++]; }

  return at;
}

/* what was read of Long Form Order Cancel Message is what was written, byte for byte */
static void equal_long_form_order_cancel_message(const LongFormOrderCancelMessage *read, const LongFormOrderCancelMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->order_reference[i] == written->order_reference[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->long_canceled_shares[i] == written->long_canceled_shares[i]); }
}

/* Long Form Order Cancel Message: written and read back, then read and written back */
static void check_long_form_order_cancel_message(void) {
  LongFormOrderCancelMessage sent;
  LongFormOrderCancelMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_long_form_order_cancel_message(&sent);
  assert(encode_long_form_order_cancel_message(&sent, wire, 0) == 19);
  assert(decode_long_form_order_cancel_message(&got, wire, 0) == 19);
  equal_long_form_order_cancel_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_long_form_order_cancel_message(&got, wire, 0) == 19);
  assert(encode_long_form_order_cancel_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 63 bytes ------------------------------------------------- */

/* A Trade Message is sent when a trade occurs against order quantity not visible on the book (i.e. a fully or partially hidden order). They do not affect the book. The Order Reference is always 0 and the Buy/Sell indicator B. */
typedef struct {
  uint8_t order_reference[9];         /* bytes 0 to 8 */
  uint8_t buy_sell_indicator;         /* byte 9 */
  uint8_t shares[6];                  /* bytes 10 to 15 */
  uint8_t stock[10];                  /* bytes 16 to 25 */
  uint8_t price[10];                  /* bytes 26 to 35 */
  uint8_t trade_reference[9];         /* bytes 36 to 44 */
  uint8_t contra_order_reference[9];  /* bytes 45 to 53 */
  uint8_t broker[3];                  /* bytes 54 to 56 */
  uint8_t contra_broker[3];           /* bytes 57 to 59 */
  uint8_t trade_attribute;            /* byte 60 */
  uint8_t cross_type;                 /* byte 61 */
  uint8_t settlement_terms;           /* byte 62 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->trade_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->contra_order_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = arbitrary(); }
  record->trade_attribute = arbitrary();
  record->cross_type = arbitrary();
  record->settlement_terms = arbitrary();
}

/* Trade Message to the wire: 63 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->order_reference[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->trade_reference[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->contra_order_reference[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->contra_broker[i]; }
  wire[at++] = record->trade_attribute;
  wire[at++] = record->cross_type;
  wire[at++] = record->settlement_terms;

  return at;
}

/* Trade Message off the wire: 63 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->trade_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->contra_order_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = wire[at++]; }
  record->trade_attribute = wire[at++];
  record->cross_type = wire[at++];
  record->settlement_terms = wire[at++];

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->order_reference[i] == written->order_reference[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->trade_reference[i] == written->trade_reference[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->contra_order_reference[i] == written->contra_order_reference[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->broker[i] == written->broker[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->contra_broker[i] == written->contra_broker[i]); }
  assert(read->trade_attribute == written->trade_attribute);
  assert(read->cross_type == written->cross_type);
  assert(read->settlement_terms == written->settlement_terms);
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[63];
  uint8_t again[63];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 63);
  assert(decode_trade_message(&got, wire, 0) == 63);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 63; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 63);
  assert(encode_trade_message(&got, again, 0) == 63);
  for (size_t i = 0; i < 63; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Form Trade Message: 76 bytes --------------------------------------- */

/* A Trade Message is sent when a trade occurs against order quantity not visible on the book (i.e. a fully or partially hidden order). They do not affect the book. The Order Reference is always 0 and the Buy/Sell indicator B. Long form messages are used when either the price or size is larger than the standard messages can permit. */
typedef struct {
  uint8_t order_reference[9];         /* bytes 0 to 8 */
  uint8_t buy_sell_indicator;         /* byte 9 */
  uint8_t long_shares[10];            /* bytes 10 to 19 */
  uint8_t stock[10];                  /* bytes 20 to 29 */
  uint8_t long_price[19];             /* bytes 30 to 48 */
  uint8_t trade_reference[9];         /* bytes 49 to 57 */
  uint8_t contra_order_reference[9];  /* bytes 58 to 66 */
  uint8_t broker[3];                  /* bytes 67 to 69 */
  uint8_t contra_broker[3];           /* bytes 70 to 72 */
  uint8_t trade_attribute;            /* byte 73 */
  uint8_t cross_type;                 /* byte 74 */
  uint8_t settlement_terms;           /* byte 75 */
} LongFormTradeMessage;

/* any Long Form Trade Message at all: every byte one the checker chooses */
static void any_long_form_trade_message(LongFormTradeMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->long_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 19; i++) { record->long_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->trade_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->contra_order_reference[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = arbitrary(); }
  record->trade_attribute = arbitrary();
  record->cross_type = arbitrary();
  record->settlement_terms = arbitrary();
}

/* Long Form Trade Message to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_long_form_trade_message(const LongFormTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->order_reference[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->long_shares[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->long_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->trade_reference[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->contra_order_reference[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->contra_broker[i]; }
  wire[at++] = record->trade_attribute;
  wire[at++] = record->cross_type;
  wire[at++] = record->settlement_terms;

  return at;
}

/* Long Form Trade Message off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_long_form_trade_message(LongFormTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->order_reference[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->long_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 19; i++) { record->long_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->trade_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->contra_order_reference[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->broker[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->contra_broker[i] = wire[at++]; }
  record->trade_attribute = wire[at++];
  record->cross_type = wire[at++];
  record->settlement_terms = wire[at++];

  return at;
}

/* what was read of Long Form Trade Message is what was written, byte for byte */
static void equal_long_form_trade_message(const LongFormTradeMessage *read, const LongFormTradeMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->order_reference[i] == written->order_reference[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 10; i++) { assert(read->long_shares[i] == written->long_shares[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 19; i++) { assert(read->long_price[i] == written->long_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->trade_reference[i] == written->trade_reference[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->contra_order_reference[i] == written->contra_order_reference[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->broker[i] == written->broker[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->contra_broker[i] == written->contra_broker[i]); }
  assert(read->trade_attribute == written->trade_attribute);
  assert(read->cross_type == written->cross_type);
  assert(read->settlement_terms == written->settlement_terms);
}

/* Long Form Trade Message: written and read back, then read and written back */
static void check_long_form_trade_message(void) {
  LongFormTradeMessage sent;
  LongFormTradeMessage got;
  uint8_t wire[76];
  uint8_t again[76];

  any_long_form_trade_message(&sent);
  assert(encode_long_form_trade_message(&sent, wire, 0) == 76);
  assert(decode_long_form_trade_message(&got, wire, 0) == 76);
  equal_long_form_trade_message(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_long_form_trade_message(&got, wire, 0) == 76);
  assert(encode_long_form_trade_message(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Message: 9 bytes ------------------------------------------- */

/* A Broken Trade message is sent whenever an execution is broken. A Broken Trade is final; once a trade is broken it cannot be reinstated. */
typedef struct {
  uint8_t trade_reference[9];  /* bytes 0 to 8 */
} BrokenTradeMessage;

/* any Broken Trade Message at all: every byte one the checker chooses */
static void any_broken_trade_message(BrokenTradeMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->trade_reference[i] = arbitrary(); }
}

/* Broken Trade Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_message(const BrokenTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->trade_reference[i]; }

  return at;
}

/* Broken Trade Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_message(BrokenTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->trade_reference[i] = wire[at++]; }

  return at;
}

/* what was read of Broken Trade Message is what was written, byte for byte */
static void equal_broken_trade_message(const BrokenTradeMessage *read, const BrokenTradeMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->trade_reference[i] == written->trade_reference[i]); }
}

/* Broken Trade Message: written and read back, then read and written back */
static void check_broken_trade_message(void) {
  BrokenTradeMessage sent;
  BrokenTradeMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_broken_trade_message(&sent);
  assert(encode_broken_trade_message(&sent, wire, 0) == 9);
  assert(decode_broken_trade_message(&got, wire, 0) == 9);
  equal_broken_trade_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_message(&got, wire, 0) == 9);
  assert(encode_broken_trade_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 1 byte -------------------------------------------- */

/* The system event message type is used to indicate a market state event. */
typedef struct {
  uint8_t event_code;  /* byte 0 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  assert(read->event_code == written->event_code);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 1);
  assert(decode_system_event_message(&got, wire, 0) == 1);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 1);
  assert(encode_system_event_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Status Message: 21 bytes ------------------------------------------ */

/* This message indicates the current trading status of a stock. At the start of day, the feed will send out a stock status message for each of the symbols trading on CXC, CX2 and CXD. Subsequently, stock status messages will be sent when a stock is halted or is released for trading. */
typedef struct {
  uint8_t stock[10];          /* bytes 0 to 9 */
  uint8_t trading_state;      /* byte 10 */
  uint8_t reserved_1;         /* byte 11 */
  uint8_t listing_market;     /* byte 12 */
  uint8_t board_lot_size[4];  /* bytes 13 to 16 */
  uint8_t currency[3];        /* bytes 17 to 19 */
  uint8_t gef_eligible;       /* byte 20 */
} StockStatusMessage;

/* any Stock Status Message at all: every byte one the checker chooses */
static void any_stock_status_message(StockStatusMessage *record) {
  for (size_t i = 0; i < 10; i++) { record->stock[i] = arbitrary(); }
  record->trading_state = arbitrary();
  record->reserved_1 = arbitrary();
  record->listing_market = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  record->gef_eligible = arbitrary();
}

/* Stock Status Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_stock_status_message(const StockStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->trading_state;
  wire[at++] = record->reserved_1;
  wire[at++] = record->listing_market;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->board_lot_size[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->gef_eligible;

  return at;
}

/* Stock Status Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_stock_status_message(StockStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->stock[i] = wire[at++]; }
  record->trading_state = wire[at++];
  record->reserved_1 = wire[at++];
  record->listing_market = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->board_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  record->gef_eligible = wire[at++];

  return at;
}

/* what was read of Stock Status Message is what was written, byte for byte */
static void equal_stock_status_message(const StockStatusMessage *read, const StockStatusMessage *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->trading_state == written->trading_state);
  assert(read->reserved_1 == written->reserved_1);
  assert(read->listing_market == written->listing_market);
  for (size_t i = 0; i < 4; i++) { assert(read->board_lot_size[i] == written->board_lot_size[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->gef_eligible == written->gef_eligible);
}

/* Stock Status Message: written and read back, then read and written back */
static void check_stock_status_message(void) {
  StockStatusMessage sent;
  StockStatusMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_stock_status_message(&sent);
  assert(encode_stock_status_message(&sent, wire, 0) == 21);
  assert(decode_stock_status_message(&got, wire, 0) == 21);
  equal_stock_status_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_status_message(&got, wire, 0) == 21);
  assert(encode_stock_status_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_heartbeat();
  check_message_header();
  check_add_order_message();
  check_long_form_add_order_message();
  check_order_execution_message();
  check_long_form_order_execution_message();
  check_order_cancel_message();
  check_long_form_order_cancel_message();
  check_trade_message();
  check_long_form_trade_message();
  check_broken_trade_message();
  check_system_event_message();
  check_stock_status_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
