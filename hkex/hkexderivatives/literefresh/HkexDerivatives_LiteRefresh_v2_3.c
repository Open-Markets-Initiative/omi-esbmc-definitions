// hkex/hkexderivatives/literefresh/HkexDerivatives_LiteRefresh_v2_3.c
/*
 * Hong Kong Exchanges and Clearing Orion Market Data Derivatives Lite Refresh
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
 *   - a field filling what is left of what holds it
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

/* Omd packet header (byte 3 is Compression Mode indicator) */
typedef struct {
  uint8_t pkt_size[2];       /* bytes 0 to 1 */
  uint8_t msg_count;         /* byte 2 */
  uint8_t compression_mode;  /* byte 3 */
  uint8_t seq_num[4];        /* bytes 4 to 7 */
  uint8_t send_time[8];      /* bytes 8 to 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->pkt_size[i] = arbitrary(); }
  record->msg_count = arbitrary();
  record->compression_mode = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = arbitrary(); }
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->pkt_size[i]; }
  wire[at++] = record->msg_count;
  wire[at++] = record->compression_mode;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->send_time[i]; }

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->pkt_size[i] = wire[at++]; }
  record->msg_count = wire[at++];
  record->compression_mode = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->pkt_size[i] == written->pkt_size[i]); }
  assert(read->msg_count == written->msg_count);
  assert(read->compression_mode == written->compression_mode);
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->send_time[i] == written->send_time[i]); }
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

/* ---- Msg Header: 4 bytes ----------------------------------------------------- */

/* Omd message header */
typedef struct {
  uint8_t msg_size[2];  /* bytes 0 to 1 */
  uint8_t msg_type[2];  /* bytes 2 to 3 */
} MsgHeader;

/* any Msg Header at all: every byte one the checker chooses */
static void any_msg_header(MsgHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->msg_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->msg_type[i] = arbitrary(); }
}

/* Msg Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_msg_header(const MsgHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_type[i]; }

  return at;
}

/* Msg Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_msg_header(MsgHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->msg_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->msg_type[i] = wire[at++]; }

  return at;
}

/* what was read of Msg Header is what was written, byte for byte */
static void equal_msg_header(const MsgHeader *read, const MsgHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->msg_size[i] == written->msg_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->msg_type[i] == written->msg_type[i]); }
}

/* Msg Header: written and read back, then read and written back */
static void check_msg_header(void) {
  MsgHeader sent;
  MsgHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_msg_header(&sent);
  assert(encode_msg_header(&sent, wire, 0) == 4);
  assert(decode_msg_header(&got, wire, 0) == 4);
  equal_msg_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_msg_header(&got, wire, 0) == 4);
  assert(encode_msg_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order: 40 bytes ----------------------------------------------------- */

/* Generated when a new normal order is inserted into the order book. */
typedef struct {
  uint8_t orderbook_id[4];         /* bytes 0 to 3 */
  uint8_t order_id[8];             /* bytes 4 to 11 */
  uint8_t price[8];                /* bytes 12 to 19 */
  uint8_t quantity[4];             /* bytes 20 to 23 */
  uint8_t side;                    /* byte 24 */
  uint8_t lot_type;                /* byte 25 */
  uint8_t order_type;              /* byte 26 */
  uint8_t order_book_position[4];  /* bytes 27 to 30 */
  uint8_t business_time[8];        /* bytes 31 to 38 */
  uint8_t filler_1;                /* byte 39 */
} AddOrder;

/* any Add Order at all: every byte one the checker chooses */
static void any_add_order(AddOrder *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->side = arbitrary();
  record->lot_type = arbitrary();
  record->order_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_book_position[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_time[i] = arbitrary(); }
  record->filler_1 = arbitrary();
}

/* Add Order to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_add_order(const AddOrder *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->side;
  wire[at++] = record->lot_type;
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_position[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_time[i]; }
  wire[at++] = record->filler_1;

  return at;
}

/* Add Order off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_add_order(AddOrder *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->side = wire[at++];
  record->lot_type = wire[at++];
  record->order_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_book_position[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_time[i] = wire[at++]; }
  record->filler_1 = wire[at++];

  return at;
}

/* what was read of Add Order is what was written, byte for byte */
static void equal_add_order(const AddOrder *read, const AddOrder *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->side == written->side);
  assert(read->lot_type == written->lot_type);
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_position[i] == written->order_book_position[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_time[i] == written->business_time[i]); }
  assert(read->filler_1 == written->filler_1);
}

/* Add Order: written and read back, then read and written back */
static void check_add_order(void) {
  AddOrder sent;
  AddOrder got;
  uint8_t wire[40];
  uint8_t again[40];

  any_add_order(&sent);
  assert(encode_add_order(&sent, wire, 0) == 40);
  assert(decode_add_order(&got, wire, 0) == 40);
  equal_add_order(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order(&got, wire, 0) == 40);
  assert(encode_add_order(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Aggregate Implied Order: 22 bytes --------------------------------------- */

/* Generated whenever there is an update on implied order at the given implied price. */
typedef struct {
  uint8_t orderbook_id[4];      /* bytes 0 to 3 */
  uint8_t implied_price[8];     /* bytes 4 to 11 */
  uint8_t implied_quantity[8];  /* bytes 12 to 19 */
  uint8_t side;                 /* byte 20 */
  uint8_t filler_1;             /* byte 21 */
} AggregateImpliedOrder;

/* any Aggregate Implied Order at all: every byte one the checker chooses */
static void any_aggregate_implied_order(AggregateImpliedOrder *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->implied_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->implied_quantity[i] = arbitrary(); }
  record->side = arbitrary();
  record->filler_1 = arbitrary();
}

/* Aggregate Implied Order to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_aggregate_implied_order(const AggregateImpliedOrder *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->implied_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->implied_quantity[i]; }
  wire[at++] = record->side;
  wire[at++] = record->filler_1;

  return at;
}

/* Aggregate Implied Order off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_aggregate_implied_order(AggregateImpliedOrder *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->implied_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->implied_quantity[i] = wire[at++]; }
  record->side = wire[at++];
  record->filler_1 = wire[at++];

  return at;
}

/* what was read of Aggregate Implied Order is what was written, byte for byte */
static void equal_aggregate_implied_order(const AggregateImpliedOrder *read, const AggregateImpliedOrder *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->implied_price[i] == written->implied_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->implied_quantity[i] == written->implied_quantity[i]); }
  assert(read->side == written->side);
  assert(read->filler_1 == written->filler_1);
}

/* Aggregate Implied Order: written and read back, then read and written back */
static void check_aggregate_implied_order(void) {
  AggregateImpliedOrder sent;
  AggregateImpliedOrder got;
  uint8_t wire[22];
  uint8_t again[22];

  any_aggregate_implied_order(&sent);
  assert(encode_aggregate_implied_order(&sent, wire, 0) == 22);
  assert(decode_aggregate_implied_order(&got, wire, 0) == 22);
  equal_aggregate_implied_order(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_aggregate_implied_order(&got, wire, 0) == 22);
  assert(encode_aggregate_implied_order(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Calculated Opening Price Message: 24 bytes ------------------------------ */

/* The Calculated Opening Price (COP) message indicates an instrument's theoretical opening price during the pre-opening phases of the market prior to an auction */
typedef struct {
  uint8_t orderbook_id[4];                 /* bytes 0 to 3 */
  uint8_t calculated_opening_price[8];     /* bytes 4 to 11 */
  uint8_t filler_4[4];                     /* bytes 12 to 15 */
  uint8_t calculated_opening_quantity[8];  /* bytes 16 to 23 */
} CalculatedOpeningPriceMessage;

/* any Calculated Opening Price Message at all: every byte one the checker chooses */
static void any_calculated_opening_price_message(CalculatedOpeningPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->calculated_opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->calculated_opening_quantity[i] = arbitrary(); }
}

/* Calculated Opening Price Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_calculated_opening_price_message(const CalculatedOpeningPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->calculated_opening_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->calculated_opening_quantity[i]; }

  return at;
}

/* Calculated Opening Price Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_calculated_opening_price_message(CalculatedOpeningPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->calculated_opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->calculated_opening_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Calculated Opening Price Message is what was written, byte for byte */
static void equal_calculated_opening_price_message(const CalculatedOpeningPriceMessage *read, const CalculatedOpeningPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->calculated_opening_price[i] == written->calculated_opening_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->calculated_opening_quantity[i] == written->calculated_opening_quantity[i]); }
}

/* Calculated Opening Price Message: written and read back, then read and written back */
static void check_calculated_opening_price_message(void) {
  CalculatedOpeningPriceMessage sent;
  CalculatedOpeningPriceMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_calculated_opening_price_message(&sent);
  assert(encode_calculated_opening_price_message(&sent, wire, 0) == 24);
  assert(decode_calculated_opening_price_message(&got, wire, 0) == 24);
  equal_calculated_opening_price_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_calculated_opening_price_message(&got, wire, 0) == 24);
  assert(encode_calculated_opening_price_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Interest Message: 28 bytes ----------------------------------------- */

/* Issued to show the Previous Day settlement price and open interest */
typedef struct {
  uint8_t day_indicator[2];     /* bytes 0 to 1 */
  uint8_t filler_6[6];          /* bytes 2 to 7 */
  uint8_t orderbook_id[4];      /* bytes 8 to 11 */
  uint8_t settlement_price[8];  /* bytes 12 to 19 */
  uint8_t gross_oi[4];          /* bytes 20 to 23 */
  uint8_t net_oi[4];            /* bytes 24 to 27 */
} OpenInterestMessage;

/* any Open Interest Message at all: every byte one the checker chooses */
static void any_open_interest_message(OpenInterestMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->day_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->gross_oi[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->net_oi[i] = arbitrary(); }
}

/* Open Interest Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_open_interest_message(const OpenInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day_indicator[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->filler_6[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->gross_oi[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->net_oi[i]; }

  return at;
}

/* Open Interest Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_open_interest_message(OpenInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->day_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->gross_oi[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->net_oi[i] = wire[at++]; }

  return at;
}

/* what was read of Open Interest Message is what was written, byte for byte */
static void equal_open_interest_message(const OpenInterestMessage *read, const OpenInterestMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->day_indicator[i] == written->day_indicator[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->filler_6[i] == written->filler_6[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->gross_oi[i] == written->gross_oi[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->net_oi[i] == written->net_oi[i]); }
}

/* Open Interest Message: written and read back, then read and written back */
static void check_open_interest_message(void) {
  OpenInterestMessage sent;
  OpenInterestMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_open_interest_message(&sent);
  assert(encode_open_interest_message(&sent, wire, 0) == 28);
  assert(decode_open_interest_message(&got, wire, 0) == 28);
  equal_open_interest_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_open_interest_message(&got, wire, 0) == 28);
  assert(encode_open_interest_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Commodity Definition: 89 bytes ------------------------------------------ */

/* Describes individual commodities available from the OMD-D system */
typedef struct {
  uint8_t commodity_code[4];            /* bytes 0 to 3 */
  uint8_t commodity_name[40];           /* bytes 4 to 43 */
  uint8_t commodity_id[6];              /* bytes 44 to 49 */
  uint8_t underlying_code[20];          /* bytes 50 to 69 */
  uint8_t underlying_type;              /* byte 70 */
  uint8_t decimal_in_underlying_price;  /* byte 71 */
  uint8_t base_currency[3];             /* bytes 72 to 74 */
  uint8_t underlying_source[6];         /* bytes 75 to 80 */
  uint8_t ca_created;                   /* byte 81 */
  uint8_t effective_tomorrow;           /* byte 82 */
  uint8_t filler_6[6];                  /* bytes 83 to 88 */
} CommodityDefinition;

/* any Commodity Definition at all: every byte one the checker chooses */
static void any_commodity_definition(CommodityDefinition *record) {
  for (size_t i = 0; i < 4; i++) { record->commodity_code[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->commodity_name[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->commodity_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->underlying_code[i] = arbitrary(); }
  record->underlying_type = arbitrary();
  record->decimal_in_underlying_price = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->base_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->underlying_source[i] = arbitrary(); }
  record->ca_created = arbitrary();
  record->effective_tomorrow = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = arbitrary(); }
}

/* Commodity Definition to the wire: 89 bytes from at, returning where the next byte goes */
static size_t encode_commodity_definition(const CommodityDefinition *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->commodity_code[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->commodity_name[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->commodity_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->underlying_code[i]; }
  wire[at++] = record->underlying_type;
  wire[at++] = record->decimal_in_underlying_price;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->base_currency[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->underlying_source[i]; }
  wire[at++] = record->ca_created;
  wire[at++] = record->effective_tomorrow;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->filler_6[i]; }

  return at;
}

/* Commodity Definition off the wire: 89 bytes from at, returning where the next byte lies */
static size_t decode_commodity_definition(CommodityDefinition *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->commodity_code[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->commodity_name[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->commodity_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->underlying_code[i] = wire[at++]; }
  record->underlying_type = wire[at++];
  record->decimal_in_underlying_price = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->base_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->underlying_source[i] = wire[at++]; }
  record->ca_created = wire[at++];
  record->effective_tomorrow = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = wire[at++]; }

  return at;
}

/* what was read of Commodity Definition is what was written, byte for byte */
static void equal_commodity_definition(const CommodityDefinition *read, const CommodityDefinition *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->commodity_code[i] == written->commodity_code[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->commodity_name[i] == written->commodity_name[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->commodity_id[i] == written->commodity_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->underlying_code[i] == written->underlying_code[i]); }
  assert(read->underlying_type == written->underlying_type);
  assert(read->decimal_in_underlying_price == written->decimal_in_underlying_price);
  for (size_t i = 0; i < 3; i++) { assert(read->base_currency[i] == written->base_currency[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->underlying_source[i] == written->underlying_source[i]); }
  assert(read->ca_created == written->ca_created);
  assert(read->effective_tomorrow == written->effective_tomorrow);
  for (size_t i = 0; i < 6; i++) { assert(read->filler_6[i] == written->filler_6[i]); }
}

/* Commodity Definition: written and read back, then read and written back */
static void check_commodity_definition(void) {
  CommodityDefinition sent;
  CommodityDefinition got;
  uint8_t wire[89];
  uint8_t again[89];

  any_commodity_definition(&sent);
  assert(encode_commodity_definition(&sent, wire, 0) == 89);
  assert(decode_commodity_definition(&got, wire, 0) == 89);
  equal_commodity_definition(&got, &sent);

  for (size_t i = 0; i < 89; i++) { wire[i] = arbitrary(); }
  assert(decode_commodity_definition(&got, wire, 0) == 89);
  assert(encode_commodity_definition(&got, again, 0) == 89);
  for (size_t i = 0; i < 89; i++) { assert(again[i] == wire[i]); }
}

/* ---- Class Definition: 106 bytes --------------------------------------------- */

/* Describes individual instrument classes available from the OMD-D system. */
typedef struct {
  uint8_t instrument_class_id[14];    /* bytes 0 to 13 */
  uint8_t instrument_class_key[4];    /* bytes 14 to 17 */
  uint8_t instrument_class_name[40];  /* bytes 18 to 57 */
  uint8_t exchange[2];                /* bytes 58 to 59 */
  uint8_t market[2];                  /* bytes 60 to 61 */
  uint8_t instrument_group[2];        /* bytes 62 to 63 */
  uint8_t modifier;                   /* byte 64 */
  uint8_t commodity_code[4];          /* bytes 65 to 68 */
  uint8_t filler_3[3];                /* bytes 69 to 71 */
  uint8_t price_quotation_factor[4];  /* bytes 72 to 75 */
  uint8_t contract_size[4];           /* bytes 76 to 79 */
  uint8_t decimal_in_contract_size;   /* byte 80 */
  uint8_t decimal_in_strike_price;    /* byte 81 */
  uint8_t decimal_in_price;           /* byte 82 */
  uint8_t tick_size[8];               /* bytes 83 to 90 */
  uint8_t tradable;                   /* byte 91 */
  uint8_t base_currency[3];           /* bytes 92 to 94 */
  uint8_t settlement_currency_id[3];  /* bytes 95 to 97 */
  uint8_t effective_tomorrow;         /* byte 98 */
  uint8_t filler_7[7];                /* bytes 99 to 105 */
} ClassDefinition;

/* any Class Definition at all: every byte one the checker chooses */
static void any_class_definition(ClassDefinition *record) {
  for (size_t i = 0; i < 14; i++) { record->instrument_class_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_class_key[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->instrument_class_name[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->exchange[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_group[i] = arbitrary(); }
  record->modifier = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->commodity_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_quotation_factor[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_size[i] = arbitrary(); }
  record->decimal_in_contract_size = arbitrary();
  record->decimal_in_strike_price = arbitrary();
  record->decimal_in_price = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = arbitrary(); }
  record->tradable = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->base_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->settlement_currency_id[i] = arbitrary(); }
  record->effective_tomorrow = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->filler_7[i] = arbitrary(); }
}

/* Class Definition to the wire: 106 bytes from at, returning where the next byte goes */
static size_t encode_class_definition(const ClassDefinition *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->instrument_class_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_class_key[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->instrument_class_name[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->exchange[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_group[i]; }
  wire[at++] = record->modifier;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->commodity_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_quotation_factor[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_size[i]; }
  wire[at++] = record->decimal_in_contract_size;
  wire[at++] = record->decimal_in_strike_price;
  wire[at++] = record->decimal_in_price;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_size[i]; }
  wire[at++] = record->tradable;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->base_currency[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->settlement_currency_id[i]; }
  wire[at++] = record->effective_tomorrow;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->filler_7[i]; }

  return at;
}

/* Class Definition off the wire: 106 bytes from at, returning where the next byte lies */
static size_t decode_class_definition(ClassDefinition *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->instrument_class_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_class_key[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->instrument_class_name[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->exchange[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_group[i] = wire[at++]; }
  record->modifier = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->commodity_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_quotation_factor[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_size[i] = wire[at++]; }
  record->decimal_in_contract_size = wire[at++];
  record->decimal_in_strike_price = wire[at++];
  record->decimal_in_price = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = wire[at++]; }
  record->tradable = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->base_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->settlement_currency_id[i] = wire[at++]; }
  record->effective_tomorrow = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->filler_7[i] = wire[at++]; }

  return at;
}

/* what was read of Class Definition is what was written, byte for byte */
static void equal_class_definition(const ClassDefinition *read, const ClassDefinition *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->instrument_class_id[i] == written->instrument_class_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_class_key[i] == written->instrument_class_key[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->instrument_class_name[i] == written->instrument_class_name[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->exchange[i] == written->exchange[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market[i] == written->market[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_group[i] == written->instrument_group[i]); }
  assert(read->modifier == written->modifier);
  for (size_t i = 0; i < 4; i++) { assert(read->commodity_code[i] == written->commodity_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_quotation_factor[i] == written->price_quotation_factor[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_size[i] == written->contract_size[i]); }
  assert(read->decimal_in_contract_size == written->decimal_in_contract_size);
  assert(read->decimal_in_strike_price == written->decimal_in_strike_price);
  assert(read->decimal_in_price == written->decimal_in_price);
  for (size_t i = 0; i < 8; i++) { assert(read->tick_size[i] == written->tick_size[i]); }
  assert(read->tradable == written->tradable);
  for (size_t i = 0; i < 3; i++) { assert(read->base_currency[i] == written->base_currency[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->settlement_currency_id[i] == written->settlement_currency_id[i]); }
  assert(read->effective_tomorrow == written->effective_tomorrow);
  for (size_t i = 0; i < 7; i++) { assert(read->filler_7[i] == written->filler_7[i]); }
}

/* Class Definition: written and read back, then read and written back */
static void check_class_definition(void) {
  ClassDefinition sent;
  ClassDefinition got;
  uint8_t wire[106];
  uint8_t again[106];

  any_class_definition(&sent);
  assert(encode_class_definition(&sent, wire, 0) == 106);
  assert(decode_class_definition(&got, wire, 0) == 106);
  equal_class_definition(&got, &sent);

  for (size_t i = 0; i < 106; i++) { wire[i] = arbitrary(); }
  assert(decode_class_definition(&got, wire, 0) == 106);
  assert(encode_class_definition(&got, again, 0) == 106);
  for (size_t i = 0; i < 106; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Definition: 118 bytes ---------------------------------------- */

/* Describes instrument static data. */
typedef struct {
  uint8_t orderbook_id[4];                 /* bytes 0 to 3 */
  uint8_t symbol[32];                      /* bytes 4 to 35 */
  uint8_t instrument_class_key[4];         /* bytes 36 to 39 */
  uint8_t exchange[2];                     /* bytes 40 to 41 */
  uint8_t market[2];                       /* bytes 42 to 43 */
  uint8_t instrument_group[2];             /* bytes 44 to 45 */
  uint8_t modifier;                        /* byte 46 */
  uint8_t commodity_code[4];               /* bytes 47 to 50 */
  uint8_t last_trading_date[4];            /* bytes 51 to 54 */
  uint8_t strike_price[8];                 /* bytes 55 to 62 */
  uint8_t filler_3[3];                     /* bytes 63 to 65 */
  uint8_t date_time_last_trading[8];       /* bytes 66 to 73 */
  uint8_t effective_last_trading_date[4];  /* bytes 74 to 77 */
  uint8_t date_time_first_trading[8];      /* bytes 78 to 85 */
  uint8_t instrument_status_code;          /* byte 86 */
  uint8_t decimal_in_strike_price;         /* byte 87 */
  uint8_t decimal_in_price;                /* byte 88 */
  uint8_t financial_product;               /* byte 89 */
  uint8_t put_or_call;                     /* byte 90 */
  uint8_t contract_size[4];                /* bytes 91 to 94 */
  uint8_t price_quotation_factor[4];       /* bytes 95 to 98 */
  uint8_t number_of_legs;                  /* byte 99 */
  uint8_t vcm_flag;                        /* byte 100 */
  uint8_t isin_code[12];                   /* bytes 101 to 112 */
  uint8_t effective_tomorrow;              /* byte 113 */
  uint8_t filler_4[4];                     /* bytes 114 to 117 */
} InstrumentDefinition;

/* any Instrument Definition at all: every byte one the checker chooses */
static void any_instrument_definition(InstrumentDefinition *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_class_key[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->exchange[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_group[i] = arbitrary(); }
  record->modifier = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->commodity_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_time_last_trading[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->effective_last_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_time_first_trading[i] = arbitrary(); }
  record->instrument_status_code = arbitrary();
  record->decimal_in_strike_price = arbitrary();
  record->decimal_in_price = arbitrary();
  record->financial_product = arbitrary();
  record->put_or_call = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contract_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_quotation_factor[i] = arbitrary(); }
  record->number_of_legs = arbitrary();
  record->vcm_flag = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  record->effective_tomorrow = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
}

/* Instrument Definition to the wire: 118 bytes from at, returning where the next byte goes */
static size_t encode_instrument_definition(const InstrumentDefinition *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_class_key[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->exchange[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_group[i]; }
  wire[at++] = record->modifier;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->commodity_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trading_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_time_last_trading[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->effective_last_trading_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_time_first_trading[i]; }
  wire[at++] = record->instrument_status_code;
  wire[at++] = record->decimal_in_strike_price;
  wire[at++] = record->decimal_in_price;
  wire[at++] = record->financial_product;
  wire[at++] = record->put_or_call;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_quotation_factor[i]; }
  wire[at++] = record->number_of_legs;
  wire[at++] = record->vcm_flag;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  wire[at++] = record->effective_tomorrow;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }

  return at;
}

/* Instrument Definition off the wire: 118 bytes from at, returning where the next byte lies */
static size_t decode_instrument_definition(InstrumentDefinition *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_class_key[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->exchange[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_group[i] = wire[at++]; }
  record->modifier = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->commodity_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_time_last_trading[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->effective_last_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_time_first_trading[i] = wire[at++]; }
  record->instrument_status_code = wire[at++];
  record->decimal_in_strike_price = wire[at++];
  record->decimal_in_price = wire[at++];
  record->financial_product = wire[at++];
  record->put_or_call = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contract_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_quotation_factor[i] = wire[at++]; }
  record->number_of_legs = wire[at++];
  record->vcm_flag = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  record->effective_tomorrow = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Definition is what was written, byte for byte */
static void equal_instrument_definition(const InstrumentDefinition *read, const InstrumentDefinition *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_class_key[i] == written->instrument_class_key[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->exchange[i] == written->exchange[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market[i] == written->market[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_group[i] == written->instrument_group[i]); }
  assert(read->modifier == written->modifier);
  for (size_t i = 0; i < 4; i++) { assert(read->commodity_code[i] == written->commodity_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trading_date[i] == written->last_trading_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_time_last_trading[i] == written->date_time_last_trading[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->effective_last_trading_date[i] == written->effective_last_trading_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_time_first_trading[i] == written->date_time_first_trading[i]); }
  assert(read->instrument_status_code == written->instrument_status_code);
  assert(read->decimal_in_strike_price == written->decimal_in_strike_price);
  assert(read->decimal_in_price == written->decimal_in_price);
  assert(read->financial_product == written->financial_product);
  assert(read->put_or_call == written->put_or_call);
  for (size_t i = 0; i < 4; i++) { assert(read->contract_size[i] == written->contract_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_quotation_factor[i] == written->price_quotation_factor[i]); }
  assert(read->number_of_legs == written->number_of_legs);
  assert(read->vcm_flag == written->vcm_flag);
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  assert(read->effective_tomorrow == written->effective_tomorrow);
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
}

/* Instrument Definition: written and read back, then read and written back */
static void check_instrument_definition(void) {
  InstrumentDefinition sent;
  InstrumentDefinition got;
  uint8_t wire[118];
  uint8_t again[118];

  any_instrument_definition(&sent);
  assert(encode_instrument_definition(&sent, wire, 0) == 118);
  assert(decode_instrument_definition(&got, wire, 0) == 118);
  equal_instrument_definition(&got, &sent);

  for (size_t i = 0; i < 118; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_definition(&got, wire, 0) == 118);
  assert(encode_instrument_definition(&got, again, 0) == 118);
  for (size_t i = 0; i < 118; i++) { assert(again[i] == wire[i]); }
}

/* ---- Combination Definition: 16 bytes ---------------------------------------- */

/* Describes the composition of a combination instrument. */
typedef struct {
  uint8_t combo_orderbook_id[4];  /* bytes 0 to 3 */
  uint8_t leg_orderbook_id[4];    /* bytes 4 to 7 */
  uint8_t filler_3[3];            /* bytes 8 to 10 */
  uint8_t leg_side;               /* byte 11 */
  uint8_t leg_ratio[4];           /* bytes 12 to 15 */
} CombinationDefinition;

/* any Combination Definition at all: every byte one the checker chooses */
static void any_combination_definition(CombinationDefinition *record) {
  for (size_t i = 0; i < 4; i++) { record->combo_orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
  record->leg_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_ratio[i] = arbitrary(); }
}

/* Combination Definition to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_combination_definition(const CombinationDefinition *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->combo_orderbook_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_orderbook_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }
  wire[at++] = record->leg_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio[i]; }

  return at;
}

/* Combination Definition off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_combination_definition(CombinationDefinition *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->combo_orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }
  record->leg_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_ratio[i] = wire[at++]; }

  return at;
}

/* what was read of Combination Definition is what was written, byte for byte */
static void equal_combination_definition(const CombinationDefinition *read, const CombinationDefinition *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->combo_orderbook_id[i] == written->combo_orderbook_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_orderbook_id[i] == written->leg_orderbook_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
  assert(read->leg_side == written->leg_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio[i] == written->leg_ratio[i]); }
}

/* Combination Definition: written and read back, then read and written back */
static void check_combination_definition(void) {
  CombinationDefinition sent;
  CombinationDefinition got;
  uint8_t wire[16];
  uint8_t again[16];

  any_combination_definition(&sent);
  assert(encode_combination_definition(&sent, wire, 0) == 16);
  assert(decode_combination_definition(&got, wire, 0) == 16);
  equal_combination_definition(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_combination_definition(&got, wire, 0) == 16);
  assert(encode_combination_definition(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Complete: 4 bytes ----------------------------------------------- */

/* RefreshComplete */
typedef struct {
  uint8_t last_seq_num[4];  /* bytes 0 to 3 */
} RefreshComplete;

/* any Refresh Complete at all: every byte one the checker chooses */
static void any_refresh_complete(RefreshComplete *record) {
  for (size_t i = 0; i < 4; i++) { record->last_seq_num[i] = arbitrary(); }
}

/* Refresh Complete to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_refresh_complete(const RefreshComplete *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_seq_num[i]; }

  return at;
}

/* Refresh Complete off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_refresh_complete(RefreshComplete *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Refresh Complete is what was written, byte for byte */
static void equal_refresh_complete(const RefreshComplete *read, const RefreshComplete *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_seq_num[i] == written->last_seq_num[i]); }
}

/* Refresh Complete: written and read back, then read and written back */
static void check_refresh_complete(void) {
  RefreshComplete sent;
  RefreshComplete got;
  uint8_t wire[4];
  uint8_t again[4];

  any_refresh_complete(&sent);
  assert(encode_refresh_complete(&sent, wire, 0) == 4);
  assert(decode_refresh_complete(&got, wire, 0) == 4);
  equal_refresh_complete(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_complete(&got, wire, 0) == 4);
  assert(encode_refresh_complete(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Status: 54 bytes ------------------------------------------------- */

/* Indicates the state of the Market, Instrument Type, or Class. */
typedef struct {
  uint8_t state_level;              /* byte 0 */
  uint8_t instrument_class_key[4];  /* bytes 1 to 4 */
  uint8_t market[2];                /* bytes 5 to 6 */
  uint8_t instrument_group[2];      /* bytes 7 to 8 */
  uint8_t commodity_code[4];        /* bytes 9 to 12 */
  uint8_t filler_8[8];              /* bytes 13 to 20 */
  uint8_t actual_start_date[8];     /* bytes 21 to 28 */
  uint8_t actual_start_time[6];     /* bytes 29 to 34 */
  uint8_t planned_start_date[8];    /* bytes 35 to 42 */
  uint8_t planned_start_time[6];    /* bytes 43 to 48 */
  uint8_t trading_session;          /* byte 49 */
  uint8_t state[2];                 /* bytes 50 to 51 */
  uint8_t filler_2[2];              /* bytes 52 to 53 */
} MarketStatus;

/* any Market Status at all: every byte one the checker chooses */
static void any_market_status(MarketStatus *record) {
  record->state_level = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_class_key[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->commodity_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->filler_8[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->actual_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->actual_start_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->planned_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->planned_start_time[i] = arbitrary(); }
  record->trading_session = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->state[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
}

/* Market Status to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_market_status(const MarketStatus *record, uint8_t *wire, size_t at) {
  wire[at++] = record->state_level;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_class_key[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->commodity_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->filler_8[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->actual_start_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->actual_start_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->planned_start_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->planned_start_time[i]; }
  wire[at++] = record->trading_session;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->state[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }

  return at;
}

/* Market Status off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_market_status(MarketStatus *record, const uint8_t *wire, size_t at) {
  record->state_level = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_class_key[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->commodity_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->filler_8[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->actual_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->actual_start_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->planned_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->planned_start_time[i] = wire[at++]; }
  record->trading_session = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->state[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }

  return at;
}

/* what was read of Market Status is what was written, byte for byte */
static void equal_market_status(const MarketStatus *read, const MarketStatus *written) {
  assert(read->state_level == written->state_level);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_class_key[i] == written->instrument_class_key[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market[i] == written->market[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_group[i] == written->instrument_group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->commodity_code[i] == written->commodity_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->filler_8[i] == written->filler_8[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->actual_start_date[i] == written->actual_start_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->actual_start_time[i] == written->actual_start_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->planned_start_date[i] == written->planned_start_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->planned_start_time[i] == written->planned_start_time[i]); }
  assert(read->trading_session == written->trading_session);
  for (size_t i = 0; i < 2; i++) { assert(read->state[i] == written->state[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
}

/* Market Status: written and read back, then read and written back */
static void check_market_status(void) {
  MarketStatus sent;
  MarketStatus got;
  uint8_t wire[54];
  uint8_t again[54];

  any_market_status(&sent);
  assert(encode_market_status(&sent, wire, 0) == 54);
  assert(decode_market_status(&got, wire, 0) == 54);
  equal_market_status(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_market_status(&got, wire, 0) == 54);
  assert(encode_market_status(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Status: 8 bytes ---------------------------------------------- */

/* Generated whenever there is a change to suspension indicator or instrument status. */
typedef struct {
  uint8_t orderbook_id[4];         /* bytes 0 to 3 */
  uint8_t suspension_indicator;    /* byte 4 */
  uint8_t instrument_status_code;  /* byte 5 */
  uint8_t filler_2[2];             /* bytes 6 to 7 */
} InstrumentStatus;

/* any Instrument Status at all: every byte one the checker chooses */
static void any_instrument_status(InstrumentStatus *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  record->suspension_indicator = arbitrary();
  record->instrument_status_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
}

/* Instrument Status to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_instrument_status(const InstrumentStatus *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  wire[at++] = record->suspension_indicator;
  wire[at++] = record->instrument_status_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }

  return at;
}

/* Instrument Status off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_instrument_status(InstrumentStatus *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  record->suspension_indicator = wire[at++];
  record->instrument_status_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Status is what was written, byte for byte */
static void equal_instrument_status(const InstrumentStatus *read, const InstrumentStatus *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  assert(read->suspension_indicator == written->suspension_indicator);
  assert(read->instrument_status_code == written->instrument_status_code);
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
}

/* Instrument Status: written and read back, then read and written back */
static void check_instrument_status(void) {
  InstrumentStatus sent;
  InstrumentStatus got;
  uint8_t wire[8];
  uint8_t again[8];

  any_instrument_status(&sent);
  assert(encode_instrument_status(&sent, wire, 0) == 8);
  assert(decode_instrument_status(&got, wire, 0) == 8);
  equal_instrument_status(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_status(&got, wire, 0) == 8);
  assert(encode_instrument_status(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Commodity And Class Status: 10 bytes ------------------------------------ */

/* Generated whenever a commodity and / or instrument class status changes. */
typedef struct {
  uint8_t commodity_code[4];        /* bytes 0 to 3 */
  uint8_t instrument_class_key[4];  /* bytes 4 to 7 */
  uint8_t suspended;                /* byte 8 */
  uint8_t filler_1;                 /* byte 9 */
} CommodityAndClassStatus;

/* any Commodity And Class Status at all: every byte one the checker chooses */
static void any_commodity_and_class_status(CommodityAndClassStatus *record) {
  for (size_t i = 0; i < 4; i++) { record->commodity_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_class_key[i] = arbitrary(); }
  record->suspended = arbitrary();
  record->filler_1 = arbitrary();
}

/* Commodity And Class Status to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_commodity_and_class_status(const CommodityAndClassStatus *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->commodity_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_class_key[i]; }
  wire[at++] = record->suspended;
  wire[at++] = record->filler_1;

  return at;
}

/* Commodity And Class Status off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_commodity_and_class_status(CommodityAndClassStatus *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->commodity_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_class_key[i] = wire[at++]; }
  record->suspended = wire[at++];
  record->filler_1 = wire[at++];

  return at;
}

/* what was read of Commodity And Class Status is what was written, byte for byte */
static void equal_commodity_and_class_status(const CommodityAndClassStatus *read, const CommodityAndClassStatus *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->commodity_code[i] == written->commodity_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_class_key[i] == written->instrument_class_key[i]); }
  assert(read->suspended == written->suspended);
  assert(read->filler_1 == written->filler_1);
}

/* Commodity And Class Status: written and read back, then read and written back */
static void check_commodity_and_class_status(void) {
  CommodityAndClassStatus sent;
  CommodityAndClassStatus got;
  uint8_t wire[10];
  uint8_t again[10];

  any_commodity_and_class_status(&sent);
  assert(encode_commodity_and_class_status(&sent, wire, 0) == 10);
  assert(decode_commodity_and_class_status(&got, wire, 0) == 10);
  equal_commodity_and_class_status(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_commodity_and_class_status(&got, wire, 0) == 10);
  assert(encode_commodity_and_class_status(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Vcm Trigger: 46 bytes --------------------------------------------------- */

/* Generated when VCM is triggered on a particular instrument. */
typedef struct {
  uint8_t orderbook_id[4];            /* bytes 0 to 3 */
  uint8_t cooling_off_start_time[8];  /* bytes 4 to 11 */
  uint8_t cooling_off_end_time[8];    /* bytes 12 to 19 */
  uint8_t vcm_reference_price[8];     /* bytes 20 to 27 */
  uint8_t vcm_lower_price[8];         /* bytes 28 to 35 */
  uint8_t vcm_upper_price[8];         /* bytes 36 to 43 */
  uint8_t filler_2[2];                /* bytes 44 to 45 */
} VcmTrigger;

/* any Vcm Trigger at all: every byte one the checker chooses */
static void any_vcm_trigger(VcmTrigger *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cooling_off_start_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cooling_off_end_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vcm_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vcm_lower_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vcm_upper_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
}

/* Vcm Trigger to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_vcm_trigger(const VcmTrigger *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cooling_off_start_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cooling_off_end_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vcm_reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vcm_lower_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vcm_upper_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }

  return at;
}

/* Vcm Trigger off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_vcm_trigger(VcmTrigger *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cooling_off_start_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cooling_off_end_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vcm_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vcm_lower_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vcm_upper_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }

  return at;
}

/* what was read of Vcm Trigger is what was written, byte for byte */
static void equal_vcm_trigger(const VcmTrigger *read, const VcmTrigger *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cooling_off_start_time[i] == written->cooling_off_start_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cooling_off_end_time[i] == written->cooling_off_end_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vcm_reference_price[i] == written->vcm_reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vcm_lower_price[i] == written->vcm_lower_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vcm_upper_price[i] == written->vcm_upper_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
}

/* Vcm Trigger: written and read back, then read and written back */
static void check_vcm_trigger(void) {
  VcmTrigger sent;
  VcmTrigger got;
  uint8_t wire[46];
  uint8_t again[46];

  any_vcm_trigger(&sent);
  assert(encode_vcm_trigger(&sent, wire, 0) == 46);
  assert(decode_vcm_trigger(&got, wire, 0) == 46);
  equal_vcm_trigger(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_vcm_trigger(&got, wire, 0) == 46);
  assert(encode_vcm_trigger(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Thm Trigger: 16 bytes --------------------------------------------------- */

/* Generated when trading halt is triggered on a particular instrument class. */
typedef struct {
  uint8_t instrument_class_key[4];  /* bytes 0 to 3 */
  uint8_t market[2];                /* bytes 4 to 5 */
  uint8_t instrument_group[2];      /* bytes 6 to 7 */
  uint8_t modifier;                 /* byte 8 */
  uint8_t commodity_code[4];        /* bytes 9 to 12 */
  uint8_t thm_status;               /* byte 13 */
  uint8_t filler_2[2];              /* bytes 14 to 15 */
} ThmTrigger;

/* any Thm Trigger at all: every byte one the checker chooses */
static void any_thm_trigger(ThmTrigger *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_class_key[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_group[i] = arbitrary(); }
  record->modifier = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->commodity_code[i] = arbitrary(); }
  record->thm_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
}

/* Thm Trigger to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_thm_trigger(const ThmTrigger *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_class_key[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_group[i]; }
  wire[at++] = record->modifier;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->commodity_code[i]; }
  wire[at++] = record->thm_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }

  return at;
}

/* Thm Trigger off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_thm_trigger(ThmTrigger *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_class_key[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_group[i] = wire[at++]; }
  record->modifier = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->commodity_code[i] = wire[at++]; }
  record->thm_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }

  return at;
}

/* what was read of Thm Trigger is what was written, byte for byte */
static void equal_thm_trigger(const ThmTrigger *read, const ThmTrigger *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_class_key[i] == written->instrument_class_key[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market[i] == written->market[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_group[i] == written->instrument_group[i]); }
  assert(read->modifier == written->modifier);
  for (size_t i = 0; i < 4; i++) { assert(read->commodity_code[i] == written->commodity_code[i]); }
  assert(read->thm_status == written->thm_status);
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
}

/* Thm Trigger: written and read back, then read and written back */
static void check_thm_trigger(void) {
  ThmTrigger sent;
  ThmTrigger got;
  uint8_t wire[16];
  uint8_t again[16];

  any_thm_trigger(&sent);
  assert(encode_thm_trigger(&sent, wire, 0) == 16);
  assert(decode_thm_trigger(&got, wire, 0) == 16);
  equal_thm_trigger(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_thm_trigger(&got, wire, 0) == 16);
  assert(encode_thm_trigger(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Statistics Message: 56 bytes -------------------------------------- */

/* Trade information for completed deals */
typedef struct {
  uint8_t orderbook_id[4];         /* bytes 0 to 3 */
  uint8_t last_price[8];           /* bytes 4 to 11 */
  uint8_t session;                 /* byte 12 */
  uint8_t open_price[8];           /* bytes 13 to 20 */
  uint8_t high_price[8];           /* bytes 21 to 28 */
  uint8_t low_price[8];            /* bytes 29 to 36 */
  uint8_t trade_report_volume[8];  /* bytes 37 to 44 */
  uint8_t turnover[8];             /* bytes 45 to 52 */
  uint8_t filler_3[3];             /* bytes 53 to 55 */
} TradeStatisticsMessage;

/* any Trade Statistics Message at all: every byte one the checker chooses */
static void any_trade_statistics_message(TradeStatisticsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  record->session = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_report_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
}

/* Trade Statistics Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_trade_statistics_message(const TradeStatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  wire[at++] = record->session;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_report_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }

  return at;
}

/* Trade Statistics Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_trade_statistics_message(TradeStatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  record->session = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_report_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Statistics Message is what was written, byte for byte */
static void equal_trade_statistics_message(const TradeStatisticsMessage *read, const TradeStatisticsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  assert(read->session == written->session);
  for (size_t i = 0; i < 8; i++) { assert(read->open_price[i] == written->open_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_report_volume[i] == written->trade_report_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
}

/* Trade Statistics Message: written and read back, then read and written back */
static void check_trade_statistics_message(void) {
  TradeStatisticsMessage sent;
  TradeStatisticsMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_trade_statistics_message(&sent);
  assert(encode_trade_statistics_message(&sent, wire, 0) == 56);
  assert(decode_trade_statistics_message(&got, wire, 0) == 56);
  equal_trade_statistics_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_statistics_message(&got, wire, 0) == 56);
  assert(encode_trade_statistics_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_msg_header();
  check_add_order();
  check_aggregate_implied_order();
  check_calculated_opening_price_message();
  check_open_interest_message();
  check_commodity_definition();
  check_class_definition();
  check_instrument_definition();
  check_combination_definition();
  check_refresh_complete();
  check_market_status();
  check_instrument_status();
  check_commodity_and_class_status();
  check_vcm_trigger();
  check_thm_trigger();
  check_trade_statistics_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
