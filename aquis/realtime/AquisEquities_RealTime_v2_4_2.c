// aquis/realtime/AquisEquities_RealTime_v2_4_2.c
/*
 * Aquis Exchange Real Time Market Data Feed
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

/* ---- Packet Header: 1 byte --------------------------------------------------- */

/* Aquis udp packet header */
typedef struct {
  uint8_t message_count;  /* byte 0 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  record->message_count = arbitrary();
}

/* Packet Header to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_count;

  return at;
}

/* Packet Header off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  record->message_count = wire[at++];

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  assert(read->message_count == written->message_count);
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[1];
  uint8_t again[1];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 1);
  assert(decode_packet_header(&got, wire, 0) == 1);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 1);
  assert(encode_packet_header(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 6 bytes ------------------------------------------------- */

/* Aquis market data message header */
typedef struct {
  uint8_t msg_type;    /* byte 0 */
  uint8_t msg_length;  /* byte 1 */
  uint8_t seq_no[4];   /* bytes 2 to 5 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->msg_type = arbitrary();
  record->msg_length = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->seq_no[i] = arbitrary(); }
}

/* Message Header to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->msg_type;
  wire[at++] = record->msg_length;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_no[i]; }

  return at;
}

/* Message Header off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->msg_type = wire[at++];
  record->msg_length = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->msg_type == written->msg_type);
  assert(read->msg_length == written->msg_length);
  for (size_t i = 0; i < 4; i++) { assert(read->seq_no[i] == written->seq_no[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[6];
  uint8_t again[6];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 6);
  assert(decode_message_header(&got, wire, 0) == 6);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 6);
  assert(encode_message_header(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Add Message: 27 bytes --------------------------------------------- */

/* The Order Add message is published when order quantity is posted to the order book for a particular security. */
typedef struct {
  uint8_t security_id[2];  /* bytes 0 to 1 */
  uint8_t side;            /* byte 2 */
  uint8_t quantity[4];     /* bytes 3 to 6 */
  uint8_t price[8];        /* bytes 7 to 14 */
  uint8_t order_ref[4];    /* bytes 15 to 18 */
  uint8_t timestamp[8];    /* bytes 19 to 26 */
} OrderAddMessage;

/* any Order Add Message at all: every byte one the checker chooses */
static void any_order_add_message(OrderAddMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* Order Add Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_order_add_message(const OrderAddMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_ref[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* Order Add Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_order_add_message(OrderAddMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Add Message is what was written, byte for byte */
static void equal_order_add_message(const OrderAddMessage *read, const OrderAddMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_ref[i] == written->order_ref[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
}

/* Order Add Message: written and read back, then read and written back */
static void check_order_add_message(void) {
  OrderAddMessage sent;
  OrderAddMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_order_add_message(&sent);
  assert(encode_order_add_message(&sent, wire, 0) == 27);
  assert(decode_order_add_message(&got, wire, 0) == 27);
  equal_order_add_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_order_add_message(&got, wire, 0) == 27);
  assert(encode_order_add_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Message: 14 bytes ------------------------------------------ */

/* The Order Cancel message is published when a visible order is removed from the book. */
typedef struct {
  uint8_t security_id[2];  /* bytes 0 to 1 */
  uint8_t order_ref[4];    /* bytes 2 to 5 */
  uint8_t timestamp[8];    /* bytes 6 to 13 */
} OrderCancelMessage;

/* any Order Cancel Message at all: every byte one the checker chooses */
static void any_order_cancel_message(OrderCancelMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* Order Cancel Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_message(const OrderCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_ref[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* Order Cancel Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_message(OrderCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Message is what was written, byte for byte */
static void equal_order_cancel_message(const OrderCancelMessage *read, const OrderCancelMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_ref[i] == written->order_ref[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
}

/* Order Cancel Message: written and read back, then read and written back */
static void check_order_cancel_message(void) {
  OrderCancelMessage sent;
  OrderCancelMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_order_cancel_message(&sent);
  assert(encode_order_cancel_message(&sent, wire, 0) == 14);
  assert(decode_order_cancel_message(&got, wire, 0) == 14);
  equal_order_cancel_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_message(&got, wire, 0) == 14);
  assert(encode_order_cancel_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modify Message: 26 bytes ------------------------------------------ */

/* The Order Modify message is published when a visible order is modified by the client (change of price and/or quantity). */
typedef struct {
  uint8_t security_id[2];         /* bytes 0 to 1 */
  uint8_t remaining_quantity[4];  /* bytes 2 to 5 */
  uint8_t price[8];               /* bytes 6 to 13 */
  uint8_t order_ref[4];           /* bytes 14 to 17 */
  uint8_t timestamp[8];           /* bytes 18 to 25 */
} OrderModifyMessage;

/* any Order Modify Message at all: every byte one the checker chooses */
static void any_order_modify_message(OrderModifyMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* Order Modify Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_order_modify_message(const OrderModifyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->remaining_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_ref[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* Order Modify Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_order_modify_message(OrderModifyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Modify Message is what was written, byte for byte */
static void equal_order_modify_message(const OrderModifyMessage *read, const OrderModifyMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->remaining_quantity[i] == written->remaining_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_ref[i] == written->order_ref[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
}

/* Order Modify Message: written and read back, then read and written back */
static void check_order_modify_message(void) {
  OrderModifyMessage sent;
  OrderModifyMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_order_modify_message(&sent);
  assert(encode_order_modify_message(&sent, wire, 0) == 26);
  assert(decode_order_modify_message(&got, wire, 0) == 26);
  equal_order_modify_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modify_message(&got, wire, 0) == 26);
  assert(encode_order_modify_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Table Data Message: 27 bytes --------------------------------------- */

/* A series of Tick Table Data messages are published pre-market to specify the dynamic tick tables and static ticks that apply to the securities traded on Aquis. */
typedef struct {
  uint8_t tick_table_id;  /* byte 0 */
  uint8_t name[10];       /* bytes 1 to 10 */
  uint8_t threshold[8];   /* bytes 11 to 18 */
  uint8_t tick_size[8];   /* bytes 19 to 26 */
} TickTableDataMessage;

/* any Tick Table Data Message at all: every byte one the checker chooses */
static void any_tick_table_data_message(TickTableDataMessage *record) {
  record->tick_table_id = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->name[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->threshold[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = arbitrary(); }
}

/* Tick Table Data Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_tick_table_data_message(const TickTableDataMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->tick_table_id;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->name[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->threshold[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_size[i]; }

  return at;
}

/* Tick Table Data Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_tick_table_data_message(TickTableDataMessage *record, const uint8_t *wire, size_t at) {
  record->tick_table_id = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->name[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->threshold[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = wire[at++]; }

  return at;
}

/* what was read of Tick Table Data Message is what was written, byte for byte */
static void equal_tick_table_data_message(const TickTableDataMessage *read, const TickTableDataMessage *written) {
  assert(read->tick_table_id == written->tick_table_id);
  for (size_t i = 0; i < 10; i++) { assert(read->name[i] == written->name[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->threshold[i] == written->threshold[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tick_size[i] == written->tick_size[i]); }
}

/* Tick Table Data Message: written and read back, then read and written back */
static void check_tick_table_data_message(void) {
  TickTableDataMessage sent;
  TickTableDataMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_tick_table_data_message(&sent);
  assert(encode_tick_table_data_message(&sent, wire, 0) == 27);
  assert(decode_tick_table_data_message(&got, wire, 0) == 27);
  equal_tick_table_data_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_table_data_message(&got, wire, 0) == 27);
  assert(encode_tick_table_data_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Aod Update Message: 22 bytes -------------------------------------------- */

/* During the AoD this message is used to publish the indicative price and indicative matched volume. */
typedef struct {
  uint8_t security_id[2];       /* bytes 0 to 1 */
  uint8_t indicative_price[8];  /* bytes 2 to 9 */
  uint8_t match_vol[4];         /* bytes 10 to 13 */
  uint8_t timestamp[8];         /* bytes 14 to 21 */
} AodUpdateMessage;

/* any Aod Update Message at all: every byte one the checker chooses */
static void any_aod_update_message(AodUpdateMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_vol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* Aod Update Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_aod_update_message(const AodUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_vol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* Aod Update Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_aod_update_message(AodUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_vol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Aod Update Message is what was written, byte for byte */
static void equal_aod_update_message(const AodUpdateMessage *read, const AodUpdateMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_price[i] == written->indicative_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_vol[i] == written->match_vol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
}

/* Aod Update Message: written and read back, then read and written back */
static void check_aod_update_message(void) {
  AodUpdateMessage sent;
  AodUpdateMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_aod_update_message(&sent);
  assert(encode_aod_update_message(&sent, wire, 0) == 22);
  assert(decode_aod_update_message(&got, wire, 0) == 22);
  equal_aod_update_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_aod_update_message(&got, wire, 0) == 22);
  assert(encode_aod_update_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mac Update Message: 26 bytes -------------------------------------------- */

/* During the MaC this message is used to publish the indicative price from the buy and sell order totals. */
typedef struct {
  uint8_t security_id[2];       /* bytes 0 to 1 */
  uint8_t indicative_price[8];  /* bytes 2 to 9 */
  uint8_t closing_buy_qty[4];   /* bytes 10 to 13 */
  uint8_t closing_sell_qty[4];  /* bytes 14 to 17 */
  uint8_t timestamp[8];         /* bytes 18 to 25 */
} MacUpdateMessage;

/* any Mac Update Message at all: every byte one the checker chooses */
static void any_mac_update_message(MacUpdateMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->closing_buy_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->closing_sell_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* Mac Update Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_mac_update_message(const MacUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_buy_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_sell_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* Mac Update Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_mac_update_message(MacUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->closing_buy_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->closing_sell_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Mac Update Message is what was written, byte for byte */
static void equal_mac_update_message(const MacUpdateMessage *read, const MacUpdateMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_price[i] == written->indicative_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->closing_buy_qty[i] == written->closing_buy_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->closing_sell_qty[i] == written->closing_sell_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
}

/* Mac Update Message: written and read back, then read and written back */
static void check_mac_update_message(void) {
  MacUpdateMessage sent;
  MacUpdateMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_mac_update_message(&sent);
  assert(encode_mac_update_message(&sent, wire, 0) == 26);
  assert(decode_mac_update_message(&got, wire, 0) == 26);
  equal_mac_update_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_mac_update_message(&got, wire, 0) == 26);
  assert(encode_mac_update_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_order_add_message();
  check_order_cancel_message();
  check_order_modify_message();
  check_tick_table_data_message();
  check_aod_update_message();
  check_mac_update_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
