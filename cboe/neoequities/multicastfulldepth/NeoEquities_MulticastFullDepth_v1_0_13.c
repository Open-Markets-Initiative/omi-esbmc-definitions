// cboe/neoequities/multicastfulldepth/NeoEquities_MulticastFullDepth_v1_0_13.c
/*
 * Chicago Board Options Exchange Multicast Full Depth
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

/* ---- Unit Clear Message: 4 bytes --------------------------------------------- */

/* Instructs feed recipients to clear all orders for the Cboe Canada order book in the unit specified in the Sequenced Unit Header. Distributed in rare recovery events such as a data center fail-over. */
typedef struct {
  uint8_t reserved_4[4];  /* bytes 0 to 3 */
} UnitClearMessage;

/* any Unit Clear Message at all: every byte one the checker chooses */
static void any_unit_clear_message(UnitClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Unit Clear Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_unit_clear_message(const UnitClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Unit Clear Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_unit_clear_message(UnitClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Unit Clear Message is what was written, byte for byte */
static void equal_unit_clear_message(const UnitClearMessage *read, const UnitClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
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

/* ---- Trading Status Message: 26 bytes ---------------------------------------- */

/* Indicates the current trading status of a security on the Cboe Canada NEO system. Sequenced Trading Status messages are sent upon system startup for all active securities with Trading Status = S (suspended). */
typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t order_book_type;     /* byte 8 */
  uint8_t symbol[14];          /* bytes 9 to 22 */
  uint8_t trading_status;      /* byte 23 */
  uint8_t trading_sub_status;  /* byte 24 */
  uint8_t halt_reason;         /* byte 25 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->order_book_type = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->trading_sub_status = arbitrary();
  record->halt_reason = arbitrary();
}

/* Trading Status Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->order_book_type;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->trading_sub_status;
  wire[at++] = record->halt_reason;

  return at;
}

/* Trading Status Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->order_book_type = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->trading_sub_status = wire[at++];
  record->halt_reason = wire[at++];

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->order_book_type == written->order_book_type);
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->trading_sub_status == written->trading_sub_status);
  assert(read->halt_reason == written->halt_reason);
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 26);
  assert(decode_trading_status_message(&got, wire, 0) == 26);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 26);
  assert(encode_trading_status_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 52 bytes --------------------------------------------- */

/* Represents a newly accepted order on Cboe Canada NEO. It includes a unique Order Id assigned by Cboe Canada NEO to the order. */
typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t order_book_type;     /* byte 8 */
  uint8_t order_id[8];         /* bytes 9 to 16 */
  uint8_t side_indicator;      /* byte 17 */
  uint8_t quantity[4];         /* bytes 18 to 21 */
  uint8_t symbol[14];          /* bytes 22 to 35 */
  uint8_t price[8];            /* bytes 36 to 43 */
  uint8_t broker_id[2];        /* bytes 44 to 45 */
  uint8_t settlement_type;     /* byte 46 */
  uint8_t settlement_date[4];  /* bytes 47 to 50 */
  uint8_t reserved_1;          /* byte 51 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->order_book_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  record->settlement_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settlement_date[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Add Order Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->order_book_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  wire[at++] = record->settlement_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settlement_date[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Add Order Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->order_book_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  record->settlement_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settlement_date[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->order_book_type == written->order_book_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  assert(read->settlement_type == written->settlement_type);
  for (size_t i = 0; i < 4; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 52);
  assert(decode_add_order_message(&got, wire, 0) == 52);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 52);
  assert(encode_add_order_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reduce Size Message: 21 bytes ------------------------------------------- */

/* Sent when a visible order on Cboe Canada NEO is partially reduced. Orders that are reduced in size do not lose priority. */
typedef struct {
  uint8_t timestamp[8];           /* bytes 0 to 7 */
  uint8_t order_book_type;        /* byte 8 */
  uint8_t order_id[8];            /* bytes 9 to 16 */
  uint8_t cancelled_quantity[4];  /* bytes 17 to 20 */
} ReduceSizeMessage;

/* any Reduce Size Message at all: every byte one the checker chooses */
static void any_reduce_size_message(ReduceSizeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->order_book_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_quantity[i] = arbitrary(); }
}

/* Reduce Size Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_reduce_size_message(const ReduceSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->order_book_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_quantity[i]; }

  return at;
}

/* Reduce Size Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_reduce_size_message(ReduceSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->order_book_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Reduce Size Message is what was written, byte for byte */
static void equal_reduce_size_message(const ReduceSizeMessage *read, const ReduceSizeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->order_book_type == written->order_book_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_quantity[i] == written->cancelled_quantity[i]); }
}

/* Reduce Size Message: written and read back, then read and written back */
static void check_reduce_size_message(void) {
  ReduceSizeMessage sent;
  ReduceSizeMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_reduce_size_message(&sent);
  assert(encode_reduce_size_message(&sent, wire, 0) == 21);
  assert(decode_reduce_size_message(&got, wire, 0) == 21);
  equal_reduce_size_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_reduce_size_message(&got, wire, 0) == 21);
  assert(encode_reduce_size_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Order Message: 17 bytes ------------------------------------------ */

/* Sent whenever a booked order is cancelled or leaves the order book. The Order Id refers to the Order Id of the original Add Order message. */
typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t order_book_type;  /* byte 8 */
  uint8_t order_id[8];      /* bytes 9 to 16 */
} DeleteOrderMessage;

/* any Delete Order Message at all: every byte one the checker chooses */
static void any_delete_order_message(DeleteOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->order_book_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Delete Order Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_delete_order_message(const DeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->order_book_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Delete Order Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_delete_order_message(DeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->order_book_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Order Message is what was written, byte for byte */
static void equal_delete_order_message(const DeleteOrderMessage *read, const DeleteOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->order_book_type == written->order_book_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Delete Order Message: written and read back, then read and written back */
static void check_delete_order_message(void) {
  DeleteOrderMessage sent;
  DeleteOrderMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_delete_order_message(&sent);
  assert(encode_delete_order_message(&sent, wire, 0) == 17);
  assert(decode_delete_order_message(&got, wire, 0) == 17);
  equal_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_order_message(&got, wire, 0) == 17);
  assert(encode_delete_order_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Message: 30 bytes ------------------------------------------ */

/* Sent whenever an open order is visibly modified. The Order Id refers to the Order Id of the original Add Order message. Modify Order messages appearing to be no ops will still lose priority. */
typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t order_book_type;  /* byte 8 */
  uint8_t order_id[8];      /* bytes 9 to 16 */
  uint8_t quantity[4];      /* bytes 17 to 20 */
  uint8_t price[8];         /* bytes 21 to 28 */
  uint8_t reserved_1;       /* byte 29 */
} ModifyOrderMessage;

/* any Modify Order Message at all: every byte one the checker chooses */
static void any_modify_order_message(ModifyOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->order_book_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Modify Order Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_message(const ModifyOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->order_book_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Modify Order Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_message(ModifyOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->order_book_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Modify Order Message is what was written, byte for byte */
static void equal_modify_order_message(const ModifyOrderMessage *read, const ModifyOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->order_book_type == written->order_book_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Modify Order Message: written and read back, then read and written back */
static void check_modify_order_message(void) {
  ModifyOrderMessage sent;
  ModifyOrderMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_modify_order_message(&sent);
  assert(encode_modify_order_message(&sent, wire, 0) == 30);
  assert(decode_modify_order_message(&got, wire, 0) == 30);
  equal_modify_order_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_message(&got, wire, 0) == 30);
  assert(encode_modify_order_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Break Message: 43 bytes ------------------------------------------- */

/* Sent whenever an execution on Cboe Canada NEO is cancelled. Applications that simply build a Cboe Canada NEO book can ignore Trade Break messages. */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t order_book_type;       /* byte 8 */
  uint8_t symbol[14];            /* bytes 9 to 22 */
  uint8_t original_quantity[4];  /* bytes 23 to 26 */
  uint8_t original_price[8];     /* bytes 27 to 34 */
  uint8_t execution_id[8];       /* bytes 35 to 42 */
} TradeBreakMessage;

/* any Trade Break Message at all: every byte one the checker chooses */
static void any_trade_break_message(TradeBreakMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->order_book_type = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Trade Break Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_trade_break_message(const TradeBreakMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->order_book_type;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Trade Break Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_trade_break_message(TradeBreakMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->order_book_type = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Break Message is what was written, byte for byte */
static void equal_trade_break_message(const TradeBreakMessage *read, const TradeBreakMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->order_book_type == written->order_book_type);
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_quantity[i] == written->original_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_price[i] == written->original_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Trade Break Message: written and read back, then read and written back */
static void check_trade_break_message(void) {
  TradeBreakMessage sent;
  TradeBreakMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_trade_break_message(&sent);
  assert(encode_trade_break_message(&sent, wire, 0) == 43);
  assert(decode_trade_break_message(&got, wire, 0) == 43);
  equal_trade_break_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_break_message(&got, wire, 0) == 43);
  assert(encode_trade_break_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Correction Message: 65 bytes -------------------------------------- */

/* Sent whenever an execution on Cboe Canada NEO is corrected. Applications that simply build a Cboe Canada NEO book can ignore Trade Correction messages. */
typedef struct {
  uint8_t timestamp[8];                  /* bytes 0 to 7 */
  uint8_t order_book_type;               /* byte 8 */
  uint8_t symbol[14];                    /* bytes 9 to 22 */
  uint8_t original_quantity[4];          /* bytes 23 to 26 */
  uint8_t original_price[8];             /* bytes 27 to 34 */
  uint8_t original_settlement_type;      /* byte 35 */
  uint8_t original_settlement_date[4];   /* bytes 36 to 39 */
  uint8_t corrected_quantity[4];         /* bytes 40 to 43 */
  uint8_t corrected_price[8];            /* bytes 44 to 51 */
  uint8_t corrected_settlement_type;     /* byte 52 */
  uint8_t corrected_settlement_date[4];  /* bytes 53 to 56 */
  uint8_t execution_id[8];               /* bytes 57 to 64 */
} TradeCorrectionMessage;

/* any Trade Correction Message at all: every byte one the checker chooses */
static void any_trade_correction_message(TradeCorrectionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->order_book_type = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_price[i] = arbitrary(); }
  record->original_settlement_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->original_settlement_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_price[i] = arbitrary(); }
  record->corrected_settlement_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->corrected_settlement_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Trade Correction Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_trade_correction_message(const TradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->order_book_type;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_price[i]; }
  wire[at++] = record->original_settlement_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_settlement_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_price[i]; }
  wire[at++] = record->corrected_settlement_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_settlement_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Trade Correction Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_trade_correction_message(TradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->order_book_type = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_price[i] = wire[at++]; }
  record->original_settlement_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->original_settlement_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_price[i] = wire[at++]; }
  record->corrected_settlement_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->corrected_settlement_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Correction Message is what was written, byte for byte */
static void equal_trade_correction_message(const TradeCorrectionMessage *read, const TradeCorrectionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->order_book_type == written->order_book_type);
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_quantity[i] == written->original_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_price[i] == written->original_price[i]); }
  assert(read->original_settlement_type == written->original_settlement_type);
  for (size_t i = 0; i < 4; i++) { assert(read->original_settlement_date[i] == written->original_settlement_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_quantity[i] == written->corrected_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_price[i] == written->corrected_price[i]); }
  assert(read->corrected_settlement_type == written->corrected_settlement_type);
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_settlement_date[i] == written->corrected_settlement_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Trade Correction Message: written and read back, then read and written back */
static void check_trade_correction_message(void) {
  TradeCorrectionMessage sent;
  TradeCorrectionMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_trade_correction_message(&sent);
  assert(encode_trade_correction_message(&sent, wire, 0) == 65);
  assert(decode_trade_correction_message(&got, wire, 0) == 65);
  equal_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_correction_message(&got, wire, 0) == 65);
  assert(encode_trade_correction_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Update Message: 58 bytes ---------------------------------------- */

/* Disseminates price and size information and Composite Market bid and offer prices during Opening Call, Closing Call, and reopening call (halt). Auction Update messages are sent during an auction period, unless in a delayed closing. */
typedef struct {
  uint8_t timestamp[8];              /* bytes 0 to 7 */
  uint8_t order_book_type;           /* byte 8 */
  uint8_t symbol[14];                /* bytes 9 to 22 */
  uint8_t auction_type;              /* byte 23 */
  uint8_t reference_price[8];        /* bytes 24 to 31 */
  uint8_t imbalance_quantity[4];     /* bytes 32 to 35 */
  uint8_t imbalance_side_indicator;  /* byte 36 */
  uint8_t matched_shares[4];         /* bytes 37 to 40 */
  uint8_t indicative_price[8];       /* bytes 41 to 48 */
  uint8_t auction_only_price[8];     /* bytes 49 to 56 */
  uint8_t reserved_1;                /* byte 57 */
} AuctionUpdateMessage;

/* any Auction Update Message at all: every byte one the checker chooses */
static void any_auction_update_message(AuctionUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->order_book_type = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->imbalance_quantity[i] = arbitrary(); }
  record->imbalance_side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->matched_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_only_price[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Auction Update Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_auction_update_message(const AuctionUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->order_book_type;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->imbalance_quantity[i]; }
  wire[at++] = record->imbalance_side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->matched_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_only_price[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Auction Update Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_auction_update_message(AuctionUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->order_book_type = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->imbalance_quantity[i] = wire[at++]; }
  record->imbalance_side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->matched_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_only_price[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Auction Update Message is what was written, byte for byte */
static void equal_auction_update_message(const AuctionUpdateMessage *read, const AuctionUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->order_book_type == written->order_book_type);
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->imbalance_quantity[i] == written->imbalance_quantity[i]); }
  assert(read->imbalance_side_indicator == written->imbalance_side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->matched_shares[i] == written->matched_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_price[i] == written->indicative_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_only_price[i] == written->auction_only_price[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Auction Update Message: written and read back, then read and written back */
static void check_auction_update_message(void) {
  AuctionUpdateMessage sent;
  AuctionUpdateMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_auction_update_message(&sent);
  assert(encode_auction_update_message(&sent, wire, 0) == 58);
  assert(decode_auction_update_message(&got, wire, 0) == 58);
  equal_auction_update_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_update_message(&got, wire, 0) == 58);
  assert(encode_auction_update_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Summary Message: 37 bytes --------------------------------------- */

/* Disseminates the results of an Opening Call, Closing Call, or reopening call (Halt) on Cboe Canada NEO. An Auction Summary message for each Cboe Canada Listed Security is sent at the conclusion of its Opening Call and represents the Cboe official Opening Price (or Closing Price). */
typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t order_book_type;  /* byte 8 */
  uint8_t symbol[14];       /* bytes 9 to 22 */
  uint8_t auction_type;     /* byte 23 */
  uint8_t price[8];         /* bytes 24 to 31 */
  uint8_t shares[4];        /* bytes 32 to 35 */
  uint8_t reserved_1;       /* byte 36 */
} AuctionSummaryMessage;

/* any Auction Summary Message at all: every byte one the checker chooses */
static void any_auction_summary_message(AuctionSummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->order_book_type = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Auction Summary Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_auction_summary_message(const AuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->order_book_type;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Auction Summary Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_auction_summary_message(AuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->order_book_type = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Auction Summary Message is what was written, byte for byte */
static void equal_auction_summary_message(const AuctionSummaryMessage *read, const AuctionSummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->order_book_type == written->order_book_type);
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Auction Summary Message: written and read back, then read and written back */
static void check_auction_summary_message(void) {
  AuctionSummaryMessage sent;
  AuctionSummaryMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_auction_summary_message(&sent);
  assert(encode_auction_summary_message(&sent, wire, 0) == 37);
  assert(decode_auction_summary_message(&got, wire, 0) == 37);
  equal_auction_summary_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_summary_message(&got, wire, 0) == 37);
  assert(encode_auction_summary_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Session Message: 4 bytes ----------------------------------------- */

/* Sent for each unit when the unit shuts down. No additional sequenced messages will be delivered for this unit, but heartbeats from the unit may be received. */
typedef struct {
  uint8_t reserved_4[4];  /* bytes 0 to 3 */
} EndOfSessionMessage;

/* any End Of Session Message at all: every byte one the checker chooses */
static void any_end_of_session_message(EndOfSessionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* End Of Session Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_end_of_session_message(const EndOfSessionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* End Of Session Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_end_of_session_message(EndOfSessionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Session Message is what was written, byte for byte */
static void equal_end_of_session_message(const EndOfSessionMessage *read, const EndOfSessionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* End Of Session Message: written and read back, then read and written back */
static void check_end_of_session_message(void) {
  EndOfSessionMessage sent;
  EndOfSessionMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_end_of_session_message(&sent);
  assert(encode_end_of_session_message(&sent, wire, 0) == 4);
  assert(decode_end_of_session_message(&got, wire, 0) == 4);
  equal_end_of_session_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_session_message(&got, wire, 0) == 4);
  assert(encode_end_of_session_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_unit_clear_message();
  check_trading_status_message();
  check_add_order_message();
  check_reduce_size_message();
  check_delete_order_message();
  check_modify_order_message();
  check_trade_break_message();
  check_trade_correction_message();
  check_auction_update_message();
  check_auction_summary_message();
  check_end_of_session_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
