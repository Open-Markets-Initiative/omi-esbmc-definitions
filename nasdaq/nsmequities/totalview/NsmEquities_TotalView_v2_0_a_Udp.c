// nasdaq/nsmequities/totalview/NsmEquities_TotalView_v2_0_a_Udp.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) TotalView Itch
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

/* ---- Message Header: 9 bytes ------------------------------------------------- */

typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t message_type;  /* byte 8 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[9];
  uint8_t again[9];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 9);
  assert(decode_message_header(&got, wire, 0) == 9);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 9);
  assert(encode_message_header(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 1 byte -------------------------------------------- */

/* System Event Messages signal events that affect the entire NASDAQ system. */
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

/* ---- Add Order Message: 37 bytes --------------------------------------------- */

/* An Add Order Message indicates that a new order has been accepted by the NASDAQ system and added onto the displayable book. It includes a day-unique Order Reference Number assigned by NASDAQ to the order. The Add Order message is a variable length message, 42 or 46 bytes: the MMID field is present only if the Display field equals "A" (attributed). */
typedef struct {
  uint8_t order_reference_number[9];  /* bytes 0 to 8 */
  uint8_t side;                       /* byte 9 */
  uint8_t shares[6];                  /* bytes 10 to 15 */
  uint8_t stock[6];                   /* bytes 16 to 21 */
  uint8_t price[10];                  /* bytes 22 to 31 */
  uint8_t display;                    /* byte 32 */
  uint8_t mmid[4];                    /* bytes 33 to 36 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->order_reference_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  record->display = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->mmid[i] = arbitrary(); }
}

/* Add Order Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->display;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mmid[i]; }

  return at;
}

/* Add Order Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->order_reference_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  record->display = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->mmid[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->display == written->display);
  for (size_t i = 0; i < 4; i++) { assert(read->mmid[i] == written->mmid[i]); }
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 37);
  assert(decode_add_order_message(&got, wire, 0) == 37);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 37);
  assert(encode_add_order_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 24 bytes ---------------------------------------- */

/* This message is sent whenever an order on the book is executed in whole or in part. The execution price is always equal to the limit price of the order as indicated in the Add Order Message. */
typedef struct {
  uint8_t order_reference_number[9];  /* bytes 0 to 8 */
  uint8_t executed_shares[6];         /* bytes 9 to 14 */
  uint8_t match_number[9];            /* bytes 15 to 23 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->match_number[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->executed_shares[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Order Executed Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->executed_shares[i] == written->executed_shares[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->match_number[i] == written->match_number[i]); }
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

/* ---- Order Cancel Message: 15 bytes ------------------------------------------ */

/* This message is sent whenever an order on the book is modified as a result of being canceled in whole or in part. */
typedef struct {
  uint8_t order_reference_number[9];  /* bytes 0 to 8 */
  uint8_t canceled_shares[6];         /* bytes 9 to 14 */
} OrderCancelMessage;

/* any Order Cancel Message at all: every byte one the checker chooses */
static void any_order_cancel_message(OrderCancelMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->canceled_shares[i] = arbitrary(); }
}

/* Order Cancel Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_message(const OrderCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->canceled_shares[i]; }

  return at;
}

/* Order Cancel Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_message(OrderCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->canceled_shares[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Message is what was written, byte for byte */
static void equal_order_cancel_message(const OrderCancelMessage *read, const OrderCancelMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
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

/* ---- Trade Message: 41 bytes ------------------------------------------------- */

/* The Trade Message provides information about execution events that involve orders not visible on the NASDAQ book. A Trade Message is transmitted each time a hidden order is executed in whole or in part. */
typedef struct {
  uint8_t order_reference_number[9];  /* bytes 0 to 8 */
  uint8_t side;                       /* byte 9 */
  uint8_t shares[6];                  /* bytes 10 to 15 */
  uint8_t stock[6];                   /* bytes 16 to 21 */
  uint8_t price[10];                  /* bytes 22 to 31 */
  uint8_t match_number[9];            /* bytes 32 to 40 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->order_reference_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->match_number[i] = arbitrary(); }
}

/* Trade Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Trade Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->order_reference_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 41);
  assert(decode_trade_message(&got, wire, 0) == 41);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 41);
  assert(encode_trade_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Message: 9 bytes ------------------------------------------- */

/* The Broken Trade message is sent whenever an execution on NASDAQ is broken. */
typedef struct {
  uint8_t match_number[9];  /* bytes 0 to 8 */
} BrokenTradeMessage;

/* any Broken Trade Message at all: every byte one the checker chooses */
static void any_broken_trade_message(BrokenTradeMessage *record) {
  for (size_t i = 0; i < 9; i++) { record->match_number[i] = arbitrary(); }
}

/* Broken Trade Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_message(const BrokenTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Broken Trade Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_message(BrokenTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Broken Trade Message is what was written, byte for byte */
static void equal_broken_trade_message(const BrokenTradeMessage *read, const BrokenTradeMessage *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->match_number[i] == written->match_number[i]); }
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

/* ---- Stock Halt Status Message: 7 bytes -------------------------------------- */

/* Prior to the start of system hours, NASDAQ will send out a Stock Halt Status spin. After the start of system hours, NASDAQ will use this message to relay trading status changes for an individual security. */
typedef struct {
  uint8_t stock[6];      /* bytes 0 to 5 */
  uint8_t stock_halted;  /* byte 6 */
} StockHaltStatusMessage;

/* any Stock Halt Status Message at all: every byte one the checker chooses */
static void any_stock_halt_status_message(StockHaltStatusMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->stock[i] = arbitrary(); }
  record->stock_halted = arbitrary();
}

/* Stock Halt Status Message to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_stock_halt_status_message(const StockHaltStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->stock_halted;

  return at;
}

/* Stock Halt Status Message off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_stock_halt_status_message(StockHaltStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->stock[i] = wire[at++]; }
  record->stock_halted = wire[at++];

  return at;
}

/* what was read of Stock Halt Status Message is what was written, byte for byte */
static void equal_stock_halt_status_message(const StockHaltStatusMessage *read, const StockHaltStatusMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->stock_halted == written->stock_halted);
}

/* Stock Halt Status Message: written and read back, then read and written back */
static void check_stock_halt_status_message(void) {
  StockHaltStatusMessage sent;
  StockHaltStatusMessage got;
  uint8_t wire[7];
  uint8_t again[7];

  any_stock_halt_status_message(&sent);
  assert(encode_stock_halt_status_message(&sent, wire, 0) == 7);
  assert(decode_stock_halt_status_message(&got, wire, 0) == 7);
  equal_stock_halt_status_message(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_halt_status_message(&got, wire, 0) == 7);
  assert(encode_stock_halt_status_message(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_system_event_message();
  check_add_order_message();
  check_order_executed_message();
  check_order_cancel_message();
  check_trade_message();
  check_broken_trade_message();
  check_stock_halt_status_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
