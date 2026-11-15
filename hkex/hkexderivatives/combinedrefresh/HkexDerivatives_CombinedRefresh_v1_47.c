// hkex/hkexderivatives/combinedrefresh/HkexDerivatives_CombinedRefresh_v1_47.c
/*
 * Hong Kong Exchanges and Clearing Orion Market Data Derivatives Combined Refresh
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

/* ---- Calculated Opening Price Message: 20 bytes ------------------------------ */

/* The Calculated Opening Price (COP) message indicates an instrument's theoretical opening price during the pre-opening phases of the market prior to an auction */
typedef struct {
  uint8_t orderbook_id[4];              /* bytes 0 to 3 */
  uint8_t calculated_opening_price[4];  /* bytes 4 to 7 */
  uint8_t filler_4[4];                  /* bytes 8 to 11 */
  uint8_t quantity[8];                  /* bytes 12 to 19 */
} CalculatedOpeningPriceMessage;

/* any Calculated Opening Price Message at all: every byte one the checker chooses */
static void any_calculated_opening_price_message(CalculatedOpeningPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->calculated_opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
}

/* Calculated Opening Price Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_calculated_opening_price_message(const CalculatedOpeningPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->calculated_opening_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Calculated Opening Price Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_calculated_opening_price_message(CalculatedOpeningPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->calculated_opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Calculated Opening Price Message is what was written, byte for byte */
static void equal_calculated_opening_price_message(const CalculatedOpeningPriceMessage *read, const CalculatedOpeningPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->calculated_opening_price[i] == written->calculated_opening_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Calculated Opening Price Message: written and read back, then read and written back */
static void check_calculated_opening_price_message(void) {
  CalculatedOpeningPriceMessage sent;
  CalculatedOpeningPriceMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_calculated_opening_price_message(&sent);
  assert(encode_calculated_opening_price_message(&sent, wire, 0) == 20);
  assert(decode_calculated_opening_price_message(&got, wire, 0) == 20);
  equal_calculated_opening_price_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_calculated_opening_price_message(&got, wire, 0) == 20);
  assert(encode_calculated_opening_price_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Implied Volatility Message: 8 bytes ------------------------------------- */

/* Contains implied volitility */
typedef struct {
  uint8_t orderbook_id[4];        /* bytes 0 to 3 */
  uint8_t implied_volatility[4];  /* bytes 4 to 7 */
} ImpliedVolatilityMessage;

/* any Implied Volatility Message at all: every byte one the checker chooses */
static void any_implied_volatility_message(ImpliedVolatilityMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->implied_volatility[i] = arbitrary(); }
}

/* Implied Volatility Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_implied_volatility_message(const ImpliedVolatilityMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->implied_volatility[i]; }

  return at;
}

/* Implied Volatility Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_implied_volatility_message(ImpliedVolatilityMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->implied_volatility[i] = wire[at++]; }

  return at;
}

/* what was read of Implied Volatility Message is what was written, byte for byte */
static void equal_implied_volatility_message(const ImpliedVolatilityMessage *read, const ImpliedVolatilityMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->implied_volatility[i] == written->implied_volatility[i]); }
}

/* Implied Volatility Message: written and read back, then read and written back */
static void check_implied_volatility_message(void) {
  ImpliedVolatilityMessage sent;
  ImpliedVolatilityMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_implied_volatility_message(&sent);
  assert(encode_implied_volatility_message(&sent, wire, 0) == 8);
  assert(decode_implied_volatility_message(&got, wire, 0) == 8);
  equal_implied_volatility_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_implied_volatility_message(&got, wire, 0) == 8);
  assert(encode_implied_volatility_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Interest Message: 36 bytes ----------------------------------------- */

/* Issued to show the Previous Day settlement price and open interest */
typedef struct {
  uint8_t day_indicator[2];  /* bytes 0 to 1 */
  uint8_t filler_6[6];       /* bytes 2 to 7 */
  uint8_t orderbook_id[4];   /* bytes 8 to 11 */
  uint8_t settlement[4];     /* bytes 12 to 15 */
  uint8_t deal_count[4];     /* bytes 16 to 19 */
  uint8_t gross_oi[4];       /* bytes 20 to 23 */
  uint8_t net_oi[4];         /* bytes 24 to 27 */
  uint8_t turnover[8];       /* bytes 28 to 35 */
} OpenInterestMessage;

/* any Open Interest Message at all: every byte one the checker chooses */
static void any_open_interest_message(OpenInterestMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->day_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->settlement[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->deal_count[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->gross_oi[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->net_oi[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
}

/* Open Interest Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_open_interest_message(const OpenInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day_indicator[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->filler_6[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settlement[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->deal_count[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->gross_oi[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->net_oi[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }

  return at;
}

/* Open Interest Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_open_interest_message(OpenInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->day_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->settlement[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->deal_count[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->gross_oi[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->net_oi[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }

  return at;
}

/* what was read of Open Interest Message is what was written, byte for byte */
static void equal_open_interest_message(const OpenInterestMessage *read, const OpenInterestMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->day_indicator[i] == written->day_indicator[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->filler_6[i] == written->filler_6[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->settlement[i] == written->settlement[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->deal_count[i] == written->deal_count[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->gross_oi[i] == written->gross_oi[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->net_oi[i] == written->net_oi[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
}

/* Open Interest Message: written and read back, then read and written back */
static void check_open_interest_message(void) {
  OpenInterestMessage sent;
  OpenInterestMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_open_interest_message(&sent);
  assert(encode_open_interest_message(&sent, wire, 0) == 36);
  assert(decode_open_interest_message(&got, wire, 0) == 36);
  equal_open_interest_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_open_interest_message(&got, wire, 0) == 36);
  assert(encode_open_interest_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Order Message: 14 bytes ------------------------------------------ */

/* The Delete Order message is generated when an existing order identified by the OrderBookID, OrderID and Side is deleted */
typedef struct {
  uint8_t orderbook_id[4];  /* bytes 0 to 3 */
  uint8_t order_id[8];      /* bytes 4 to 11 */
  uint8_t side;             /* byte 12 */
  uint8_t filler_1;         /* byte 13 */
} DeleteOrderMessage;

/* any Delete Order Message at all: every byte one the checker chooses */
static void any_delete_order_message(DeleteOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  record->filler_1 = arbitrary();
}

/* Delete Order Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_delete_order_message(const DeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  wire[at++] = record->filler_1;

  return at;
}

/* Delete Order Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_delete_order_message(DeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  record->filler_1 = wire[at++];

  return at;
}

/* what was read of Delete Order Message is what was written, byte for byte */
static void equal_delete_order_message(const DeleteOrderMessage *read, const DeleteOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  assert(read->filler_1 == written->filler_1);
}

/* Delete Order Message: written and read back, then read and written back */
static void check_delete_order_message(void) {
  DeleteOrderMessage sent;
  DeleteOrderMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_delete_order_message(&sent);
  assert(encode_delete_order_message(&sent, wire, 0) == 14);
  assert(decode_delete_order_message(&got, wire, 0) == 14);
  equal_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_order_message(&got, wire, 0) == 14);
  assert(encode_delete_order_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Orderbook Clear Message: 4 bytes ---------------------------------------- */

/* The Orderbook Clear message is used to inform clients that all existing orders should be removed from both the bid and ask sides of the specified orderbook */
typedef struct {
  uint8_t orderbook_id[4];  /* bytes 0 to 3 */
} OrderbookClearMessage;

/* any Orderbook Clear Message at all: every byte one the checker chooses */
static void any_orderbook_clear_message(OrderbookClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
}

/* Orderbook Clear Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_orderbook_clear_message(const OrderbookClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }

  return at;
}

/* Orderbook Clear Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_orderbook_clear_message(OrderbookClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }

  return at;
}

/* what was read of Orderbook Clear Message is what was written, byte for byte */
static void equal_orderbook_clear_message(const OrderbookClearMessage *read, const OrderbookClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
}

/* Orderbook Clear Message: written and read back, then read and written back */
static void check_orderbook_clear_message(void) {
  OrderbookClearMessage sent;
  OrderbookClearMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_orderbook_clear_message(&sent);
  assert(encode_orderbook_clear_message(&sent, wire, 0) == 4);
  assert(decode_orderbook_clear_message(&got, wire, 0) == 4);
  equal_orderbook_clear_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_orderbook_clear_message(&got, wire, 0) == 4);
  assert(encode_orderbook_clear_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Commodity Definition Message: 90 bytes ---------------------------------- */

/* Describes individual commodities available from the OMD-D system */
typedef struct {
  uint8_t commodity_code[2];               /* bytes 0 to 1 */
  uint8_t decimal_in_underlying_price[2];  /* bytes 2 to 3 */
  uint8_t isin_code[12];                   /* bytes 4 to 15 */
  uint8_t base_currency[3];                /* bytes 16 to 18 */
  uint8_t underlying_price_unit;           /* byte 19 */
  uint8_t commodity_name[32];              /* bytes 20 to 51 */
  uint8_t nominal_value[8];                /* bytes 52 to 59 */
  uint8_t underlying_code[20];             /* bytes 60 to 79 */
  uint8_t underlying_type;                 /* byte 80 */
  uint8_t effective_tomorrow;              /* byte 81 */
  uint8_t commodity_id[6];                 /* bytes 82 to 87 */
  uint8_t filler_2[2];                     /* bytes 88 to 89 */
} CommodityDefinitionMessage;

/* any Commodity Definition Message at all: every byte one the checker chooses */
static void any_commodity_definition_message(CommodityDefinitionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->commodity_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->decimal_in_underlying_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->base_currency[i] = arbitrary(); }
  record->underlying_price_unit = arbitrary();
  for (size_t i = 0; i < 32; i++) { record->commodity_name[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->underlying_code[i] = arbitrary(); }
  record->underlying_type = arbitrary();
  record->effective_tomorrow = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->commodity_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
}

/* Commodity Definition Message to the wire: 90 bytes from at, returning where the next byte goes */
static size_t encode_commodity_definition_message(const CommodityDefinitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->commodity_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->decimal_in_underlying_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->base_currency[i]; }
  wire[at++] = record->underlying_price_unit;
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->commodity_name[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nominal_value[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->underlying_code[i]; }
  wire[at++] = record->underlying_type;
  wire[at++] = record->effective_tomorrow;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->commodity_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }

  return at;
}

/* Commodity Definition Message off the wire: 90 bytes from at, returning where the next byte lies */
static size_t decode_commodity_definition_message(CommodityDefinitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->commodity_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->decimal_in_underlying_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->base_currency[i] = wire[at++]; }
  record->underlying_price_unit = wire[at++];
  for (size_t i = 0; i < 32; i++) { record->commodity_name[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->underlying_code[i] = wire[at++]; }
  record->underlying_type = wire[at++];
  record->effective_tomorrow = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->commodity_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }

  return at;
}

/* what was read of Commodity Definition Message is what was written, byte for byte */
static void equal_commodity_definition_message(const CommodityDefinitionMessage *read, const CommodityDefinitionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->commodity_code[i] == written->commodity_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->decimal_in_underlying_price[i] == written->decimal_in_underlying_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->base_currency[i] == written->base_currency[i]); }
  assert(read->underlying_price_unit == written->underlying_price_unit);
  for (size_t i = 0; i < 32; i++) { assert(read->commodity_name[i] == written->commodity_name[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nominal_value[i] == written->nominal_value[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->underlying_code[i] == written->underlying_code[i]); }
  assert(read->underlying_type == written->underlying_type);
  assert(read->effective_tomorrow == written->effective_tomorrow);
  for (size_t i = 0; i < 6; i++) { assert(read->commodity_id[i] == written->commodity_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
}

/* Commodity Definition Message: written and read back, then read and written back */
static void check_commodity_definition_message(void) {
  CommodityDefinitionMessage sent;
  CommodityDefinitionMessage got;
  uint8_t wire[90];
  uint8_t again[90];

  any_commodity_definition_message(&sent);
  assert(encode_commodity_definition_message(&sent, wire, 0) == 90);
  assert(decode_commodity_definition_message(&got, wire, 0) == 90);
  equal_commodity_definition_message(&got, &sent);

  for (size_t i = 0; i < 90; i++) { wire[i] = arbitrary(); }
  assert(decode_commodity_definition_message(&got, wire, 0) == 90);
  assert(encode_commodity_definition_message(&got, again, 0) == 90);
  for (size_t i = 0; i < 90; i++) { assert(again[i] == wire[i]); }
}

/* ---- Class Definition Message: 114 bytes ------------------------------------- */

/* Describes individual instrument classes available from the OMD-D system */
typedef struct {
  uint8_t country;                      /* byte 0 */
  uint8_t market;                       /* byte 1 */
  uint8_t instrument_group;             /* byte 2 */
  uint8_t modifier;                     /* byte 3 */
  uint8_t commodity_code[2];            /* bytes 4 to 5 */
  uint8_t filler_2[2];                  /* bytes 6 to 7 */
  uint8_t price_quotation_factor[4];    /* bytes 8 to 11 */
  uint8_t contract_size[4];             /* bytes 12 to 15 */
  uint8_t decimal_in_strike_price[2];   /* bytes 16 to 17 */
  uint8_t decimal_in_contract_size[2];  /* bytes 18 to 19 */
  uint8_t decimal_in_premium[2];        /* bytes 20 to 21 */
  uint8_t ranking_type[2];              /* bytes 22 to 23 */
  uint8_t tradable;                     /* byte 24 */
  uint8_t premium_unit_4_price;         /* byte 25 */
  uint8_t base_currency[3];             /* bytes 26 to 28 */
  uint8_t instrument_class_id[14];      /* bytes 29 to 42 */
  uint8_t instrument_class_name[32];    /* bytes 43 to 74 */
  uint8_t is_fractions;                 /* byte 75 */
  uint8_t settlement_currency_id[32];   /* bytes 76 to 107 */
  uint8_t effective_tomorrow;           /* byte 108 */
  uint8_t tick_step_size[4];            /* bytes 109 to 112 */
  uint8_t filler_1;                     /* byte 113 */
} ClassDefinitionMessage;

/* any Class Definition Message at all: every byte one the checker chooses */
static void any_class_definition_message(ClassDefinitionMessage *record) {
  record->country = arbitrary();
  record->market = arbitrary();
  record->instrument_group = arbitrary();
  record->modifier = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->commodity_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_quotation_factor[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->decimal_in_strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->decimal_in_contract_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->decimal_in_premium[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ranking_type[i] = arbitrary(); }
  record->tradable = arbitrary();
  record->premium_unit_4_price = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->base_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->instrument_class_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->instrument_class_name[i] = arbitrary(); }
  record->is_fractions = arbitrary();
  for (size_t i = 0; i < 32; i++) { record->settlement_currency_id[i] = arbitrary(); }
  record->effective_tomorrow = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->tick_step_size[i] = arbitrary(); }
  record->filler_1 = arbitrary();
}

/* Class Definition Message to the wire: 114 bytes from at, returning where the next byte goes */
static size_t encode_class_definition_message(const ClassDefinitionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->country;
  wire[at++] = record->market;
  wire[at++] = record->instrument_group;
  wire[at++] = record->modifier;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->commodity_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_quotation_factor[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->decimal_in_strike_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->decimal_in_contract_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->decimal_in_premium[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ranking_type[i]; }
  wire[at++] = record->tradable;
  wire[at++] = record->premium_unit_4_price;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->base_currency[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->instrument_class_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->instrument_class_name[i]; }
  wire[at++] = record->is_fractions;
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->settlement_currency_id[i]; }
  wire[at++] = record->effective_tomorrow;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tick_step_size[i]; }
  wire[at++] = record->filler_1;

  return at;
}

/* Class Definition Message off the wire: 114 bytes from at, returning where the next byte lies */
static size_t decode_class_definition_message(ClassDefinitionMessage *record, const uint8_t *wire, size_t at) {
  record->country = wire[at++];
  record->market = wire[at++];
  record->instrument_group = wire[at++];
  record->modifier = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->commodity_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_quotation_factor[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->decimal_in_strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->decimal_in_contract_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->decimal_in_premium[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ranking_type[i] = wire[at++]; }
  record->tradable = wire[at++];
  record->premium_unit_4_price = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->base_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->instrument_class_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->instrument_class_name[i] = wire[at++]; }
  record->is_fractions = wire[at++];
  for (size_t i = 0; i < 32; i++) { record->settlement_currency_id[i] = wire[at++]; }
  record->effective_tomorrow = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->tick_step_size[i] = wire[at++]; }
  record->filler_1 = wire[at++];

  return at;
}

/* what was read of Class Definition Message is what was written, byte for byte */
static void equal_class_definition_message(const ClassDefinitionMessage *read, const ClassDefinitionMessage *written) {
  assert(read->country == written->country);
  assert(read->market == written->market);
  assert(read->instrument_group == written->instrument_group);
  assert(read->modifier == written->modifier);
  for (size_t i = 0; i < 2; i++) { assert(read->commodity_code[i] == written->commodity_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_quotation_factor[i] == written->price_quotation_factor[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_size[i] == written->contract_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->decimal_in_strike_price[i] == written->decimal_in_strike_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->decimal_in_contract_size[i] == written->decimal_in_contract_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->decimal_in_premium[i] == written->decimal_in_premium[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ranking_type[i] == written->ranking_type[i]); }
  assert(read->tradable == written->tradable);
  assert(read->premium_unit_4_price == written->premium_unit_4_price);
  for (size_t i = 0; i < 3; i++) { assert(read->base_currency[i] == written->base_currency[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->instrument_class_id[i] == written->instrument_class_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->instrument_class_name[i] == written->instrument_class_name[i]); }
  assert(read->is_fractions == written->is_fractions);
  for (size_t i = 0; i < 32; i++) { assert(read->settlement_currency_id[i] == written->settlement_currency_id[i]); }
  assert(read->effective_tomorrow == written->effective_tomorrow);
  for (size_t i = 0; i < 4; i++) { assert(read->tick_step_size[i] == written->tick_step_size[i]); }
  assert(read->filler_1 == written->filler_1);
}

/* Class Definition Message: written and read back, then read and written back */
static void check_class_definition_message(void) {
  ClassDefinitionMessage sent;
  ClassDefinitionMessage got;
  uint8_t wire[114];
  uint8_t again[114];

  any_class_definition_message(&sent);
  assert(encode_class_definition_message(&sent, wire, 0) == 114);
  assert(decode_class_definition_message(&got, wire, 0) == 114);
  equal_class_definition_message(&got, &sent);

  for (size_t i = 0; i < 114; i++) { wire[i] = arbitrary(); }
  assert(decode_class_definition_message(&got, wire, 0) == 114);
  assert(encode_class_definition_message(&got, again, 0) == 114);
  for (size_t i = 0; i < 114; i++) { assert(again[i] == wire[i]); }
}

/* ---- Series Definition Base Message: 56 bytes -------------------------------- */

/* Describes basic series information */
typedef struct {
  uint8_t orderbook_id[4];              /* bytes 0 to 3 */
  uint8_t symbol[32];                   /* bytes 4 to 35 */
  uint8_t financial_product;            /* byte 36 */
  uint8_t number_of_decimals_price[2];  /* bytes 37 to 38 */
  uint8_t number_of_legs;               /* byte 39 */
  uint8_t strike_price[4];              /* bytes 40 to 43 */
  uint8_t expiration_date[8];           /* bytes 44 to 51 */
  uint8_t decimal_in_strike_price[2];   /* bytes 52 to 53 */
  uint8_t put_or_call;                  /* byte 54 */
  uint8_t filler_1;                     /* byte 55 */
} SeriesDefinitionBaseMessage;

/* any Series Definition Base Message at all: every byte one the checker chooses */
static void any_series_definition_base_message(SeriesDefinitionBaseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = arbitrary(); }
  record->financial_product = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_price[i] = arbitrary(); }
  record->number_of_legs = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->decimal_in_strike_price[i] = arbitrary(); }
  record->put_or_call = arbitrary();
  record->filler_1 = arbitrary();
}

/* Series Definition Base Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_series_definition_base_message(const SeriesDefinitionBaseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->financial_product;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_price[i]; }
  wire[at++] = record->number_of_legs;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->decimal_in_strike_price[i]; }
  wire[at++] = record->put_or_call;
  wire[at++] = record->filler_1;

  return at;
}

/* Series Definition Base Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_series_definition_base_message(SeriesDefinitionBaseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = wire[at++]; }
  record->financial_product = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_price[i] = wire[at++]; }
  record->number_of_legs = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->decimal_in_strike_price[i] = wire[at++]; }
  record->put_or_call = wire[at++];
  record->filler_1 = wire[at++];

  return at;
}

/* what was read of Series Definition Base Message is what was written, byte for byte */
static void equal_series_definition_base_message(const SeriesDefinitionBaseMessage *read, const SeriesDefinitionBaseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->financial_product == written->financial_product);
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_price[i] == written->number_of_decimals_price[i]); }
  assert(read->number_of_legs == written->number_of_legs);
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->decimal_in_strike_price[i] == written->decimal_in_strike_price[i]); }
  assert(read->put_or_call == written->put_or_call);
  assert(read->filler_1 == written->filler_1);
}

/* Series Definition Base Message: written and read back, then read and written back */
static void check_series_definition_base_message(void) {
  SeriesDefinitionBaseMessage sent;
  SeriesDefinitionBaseMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_series_definition_base_message(&sent);
  assert(encode_series_definition_base_message(&sent, wire, 0) == 56);
  assert(decode_series_definition_base_message(&got, wire, 0) == 56);
  equal_series_definition_base_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_series_definition_base_message(&got, wire, 0) == 56);
  assert(encode_series_definition_base_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Series Definition Extended Message: 100 bytes --------------------------- */

/* Describes series static data */
typedef struct {
  uint8_t orderbook_id[4];             /* bytes 0 to 3 */
  uint8_t symbol[32];                  /* bytes 4 to 35 */
  uint8_t country;                     /* byte 36 */
  uint8_t market;                      /* byte 37 */
  uint8_t instrument_group;            /* byte 38 */
  uint8_t modifier;                    /* byte 39 */
  uint8_t commodity_code[2];           /* bytes 40 to 41 */
  uint8_t expiry_date[2];              /* bytes 42 to 43 */
  uint8_t strike_price[4];             /* bytes 44 to 47 */
  uint8_t contract_size_extended[8];   /* bytes 48 to 55 */
  uint8_t isin_code[12];               /* bytes 56 to 67 */
  uint8_t series_status;               /* byte 68 */
  uint8_t effective_tomorrow;          /* byte 69 */
  uint8_t price_quotation_factor[4];   /* bytes 70 to 73 */
  uint8_t price_method;                /* byte 74 */
  uint8_t filler_1;                    /* byte 75 */
  uint8_t effective_exp_date[8];       /* bytes 76 to 83 */
  uint8_t date_time_last_trading[8];   /* bytes 84 to 91 */
  uint8_t date_time_first_trading[8];  /* bytes 92 to 99 */
} SeriesDefinitionExtendedMessage;

/* any Series Definition Extended Message at all: every byte one the checker chooses */
static void any_series_definition_extended_message(SeriesDefinitionExtendedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = arbitrary(); }
  record->country = arbitrary();
  record->market = arbitrary();
  record->instrument_group = arbitrary();
  record->modifier = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->commodity_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->contract_size_extended[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  record->series_status = arbitrary();
  record->effective_tomorrow = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_quotation_factor[i] = arbitrary(); }
  record->price_method = arbitrary();
  record->filler_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->effective_exp_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_time_last_trading[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_time_first_trading[i] = arbitrary(); }
}

/* Series Definition Extended Message to the wire: 100 bytes from at, returning where the next byte goes */
static size_t encode_series_definition_extended_message(const SeriesDefinitionExtendedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->country;
  wire[at++] = record->market;
  wire[at++] = record->instrument_group;
  wire[at++] = record->modifier;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->commodity_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->contract_size_extended[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  wire[at++] = record->series_status;
  wire[at++] = record->effective_tomorrow;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_quotation_factor[i]; }
  wire[at++] = record->price_method;
  wire[at++] = record->filler_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->effective_exp_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_time_last_trading[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_time_first_trading[i]; }

  return at;
}

/* Series Definition Extended Message off the wire: 100 bytes from at, returning where the next byte lies */
static size_t decode_series_definition_extended_message(SeriesDefinitionExtendedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = wire[at++]; }
  record->country = wire[at++];
  record->market = wire[at++];
  record->instrument_group = wire[at++];
  record->modifier = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->commodity_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->contract_size_extended[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  record->series_status = wire[at++];
  record->effective_tomorrow = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_quotation_factor[i] = wire[at++]; }
  record->price_method = wire[at++];
  record->filler_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->effective_exp_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_time_last_trading[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_time_first_trading[i] = wire[at++]; }

  return at;
}

/* what was read of Series Definition Extended Message is what was written, byte for byte */
static void equal_series_definition_extended_message(const SeriesDefinitionExtendedMessage *read, const SeriesDefinitionExtendedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->country == written->country);
  assert(read->market == written->market);
  assert(read->instrument_group == written->instrument_group);
  assert(read->modifier == written->modifier);
  for (size_t i = 0; i < 2; i++) { assert(read->commodity_code[i] == written->commodity_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->contract_size_extended[i] == written->contract_size_extended[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  assert(read->series_status == written->series_status);
  assert(read->effective_tomorrow == written->effective_tomorrow);
  for (size_t i = 0; i < 4; i++) { assert(read->price_quotation_factor[i] == written->price_quotation_factor[i]); }
  assert(read->price_method == written->price_method);
  assert(read->filler_1 == written->filler_1);
  for (size_t i = 0; i < 8; i++) { assert(read->effective_exp_date[i] == written->effective_exp_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_time_last_trading[i] == written->date_time_last_trading[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_time_first_trading[i] == written->date_time_first_trading[i]); }
}

/* Series Definition Extended Message: written and read back, then read and written back */
static void check_series_definition_extended_message(void) {
  SeriesDefinitionExtendedMessage sent;
  SeriesDefinitionExtendedMessage got;
  uint8_t wire[100];
  uint8_t again[100];

  any_series_definition_extended_message(&sent);
  assert(encode_series_definition_extended_message(&sent, wire, 0) == 100);
  assert(decode_series_definition_extended_message(&got, wire, 0) == 100);
  equal_series_definition_extended_message(&got, &sent);

  for (size_t i = 0; i < 100; i++) { wire[i] = arbitrary(); }
  assert(decode_series_definition_extended_message(&got, wire, 0) == 100);
  assert(encode_series_definition_extended_message(&got, again, 0) == 100);
  for (size_t i = 0; i < 100; i++) { assert(again[i] == wire[i]); }
}

/* ---- Combination Definition Message: 16 bytes -------------------------------- */

/* Describes a combination orderbook */
typedef struct {
  uint8_t combo_orderbook_id[4];  /* bytes 0 to 3 */
  uint8_t leg_orderbook_id[4];    /* bytes 4 to 7 */
  uint8_t filler_3[3];            /* bytes 8 to 10 */
  uint8_t leg_side;               /* byte 11 */
  uint8_t leg_ratio[4];           /* bytes 12 to 15 */
} CombinationDefinitionMessage;

/* any Combination Definition Message at all: every byte one the checker chooses */
static void any_combination_definition_message(CombinationDefinitionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->combo_orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
  record->leg_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_ratio[i] = arbitrary(); }
}

/* Combination Definition Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_combination_definition_message(const CombinationDefinitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->combo_orderbook_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_orderbook_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }
  wire[at++] = record->leg_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio[i]; }

  return at;
}

/* Combination Definition Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_combination_definition_message(CombinationDefinitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->combo_orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }
  record->leg_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_ratio[i] = wire[at++]; }

  return at;
}

/* what was read of Combination Definition Message is what was written, byte for byte */
static void equal_combination_definition_message(const CombinationDefinitionMessage *read, const CombinationDefinitionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->combo_orderbook_id[i] == written->combo_orderbook_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_orderbook_id[i] == written->leg_orderbook_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
  assert(read->leg_side == written->leg_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio[i] == written->leg_ratio[i]); }
}

/* Combination Definition Message: written and read back, then read and written back */
static void check_combination_definition_message(void) {
  CombinationDefinitionMessage sent;
  CombinationDefinitionMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_combination_definition_message(&sent);
  assert(encode_combination_definition_message(&sent, wire, 0) == 16);
  assert(decode_combination_definition_message(&got, wire, 0) == 16);
  equal_combination_definition_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_combination_definition_message(&got, wire, 0) == 16);
  assert(encode_combination_definition_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Complete: 4 bytes ----------------------------------------------- */

/* This message is published to mark the end of a refresh cycle */
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

/* ---- Series Statistics Message: 44 bytes ------------------------------------- */

/* Provides series information including high, low and open prices */
typedef struct {
  uint8_t orderbook_id[4];         /* bytes 0 to 3 */
  uint8_t session;                 /* byte 4 */
  uint8_t filler_3[3];             /* bytes 5 to 7 */
  uint8_t open[4];                 /* bytes 8 to 11 */
  uint8_t high[4];                 /* bytes 12 to 15 */
  uint8_t low[4];                  /* bytes 16 to 19 */
  uint8_t trade_report_volume[8];  /* bytes 20 to 27 */
  uint8_t deal_count[4];           /* bytes 28 to 31 */
  uint8_t price[4];                /* bytes 32 to 35 */
  uint8_t turnover[8];             /* bytes 36 to 43 */
} SeriesStatisticsMessage;

/* any Series Statistics Message at all: every byte one the checker chooses */
static void any_series_statistics_message(SeriesStatisticsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  record->session = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_report_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->deal_count[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
}

/* Series Statistics Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_series_statistics_message(const SeriesStatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  wire[at++] = record->session;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_report_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->deal_count[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }

  return at;
}

/* Series Statistics Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_series_statistics_message(SeriesStatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  record->session = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_report_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->deal_count[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }

  return at;
}

/* what was read of Series Statistics Message is what was written, byte for byte */
static void equal_series_statistics_message(const SeriesStatisticsMessage *read, const SeriesStatisticsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  assert(read->session == written->session);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open[i] == written->open[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_report_volume[i] == written->trade_report_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->deal_count[i] == written->deal_count[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
}

/* Series Statistics Message: written and read back, then read and written back */
static void check_series_statistics_message(void) {
  SeriesStatisticsMessage sent;
  SeriesStatisticsMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_series_statistics_message(&sent);
  assert(encode_series_statistics_message(&sent, wire, 0) == 44);
  assert(decode_series_statistics_message(&got, wire, 0) == 44);
  equal_series_statistics_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_series_statistics_message(&got, wire, 0) == 44);
  assert(encode_series_statistics_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Status Message: 48 bytes ----------------------------------------- */

/* The Market Status message can be used to derive the active state of a series */
typedef struct {
  uint8_t state_level[2];              /* bytes 0 to 1 */
  uint8_t market;                      /* byte 2 */
  uint8_t instrument;                  /* byte 3 */
  uint8_t orderbook_id[4];             /* bytes 4 to 7 */
  uint8_t commodity_code[2];           /* bytes 8 to 9 */
  uint8_t filler_2[2];                 /* bytes 10 to 11 */
  uint8_t actual_start_date[8];        /* bytes 12 to 19 */
  uint8_t actual_start_time[6];        /* bytes 20 to 25 */
  uint8_t planned_start_date[8];       /* bytes 26 to 33 */
  uint8_t planned_start_time[6];       /* bytes 34 to 39 */
  uint8_t seconds_to_state_change[2];  /* bytes 40 to 41 */
  uint8_t state[2];                    /* bytes 42 to 43 */
  uint8_t priority;                    /* byte 44 */
  uint8_t filler_3[3];                 /* bytes 45 to 47 */
} MarketStatusMessage;

/* any Market Status Message at all: every byte one the checker chooses */
static void any_market_status_message(MarketStatusMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->state_level[i] = arbitrary(); }
  record->market = arbitrary();
  record->instrument = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->commodity_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->actual_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->actual_start_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->planned_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->planned_start_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->seconds_to_state_change[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->state[i] = arbitrary(); }
  record->priority = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
}

/* Market Status Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_market_status_message(const MarketStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->state_level[i]; }
  wire[at++] = record->market;
  wire[at++] = record->instrument;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->commodity_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->actual_start_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->actual_start_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->planned_start_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->planned_start_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->seconds_to_state_change[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->state[i]; }
  wire[at++] = record->priority;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }

  return at;
}

/* Market Status Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_market_status_message(MarketStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->state_level[i] = wire[at++]; }
  record->market = wire[at++];
  record->instrument = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->commodity_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->actual_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->actual_start_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->planned_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->planned_start_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->seconds_to_state_change[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->state[i] = wire[at++]; }
  record->priority = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }

  return at;
}

/* what was read of Market Status Message is what was written, byte for byte */
static void equal_market_status_message(const MarketStatusMessage *read, const MarketStatusMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->state_level[i] == written->state_level[i]); }
  assert(read->market == written->market);
  assert(read->instrument == written->instrument);
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->commodity_code[i] == written->commodity_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->actual_start_date[i] == written->actual_start_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->actual_start_time[i] == written->actual_start_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->planned_start_date[i] == written->planned_start_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->planned_start_time[i] == written->planned_start_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->seconds_to_state_change[i] == written->seconds_to_state_change[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->state[i] == written->state[i]); }
  assert(read->priority == written->priority);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
}

/* Market Status Message: written and read back, then read and written back */
static void check_market_status_message(void) {
  MarketStatusMessage sent;
  MarketStatusMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_market_status_message(&sent);
  assert(encode_market_status_message(&sent, wire, 0) == 48);
  assert(decode_market_status_message(&got, wire, 0) == 48);
  equal_market_status_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_market_status_message(&got, wire, 0) == 48);
  assert(encode_market_status_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Series Status Message: 8 bytes ------------------------------------------ */

/* The Series Status message is generated whenever there is a change to suspension indicator or series status, or when the date/time of last trading is changed */
typedef struct {
  uint8_t orderbook_id[4];       /* bytes 0 to 3 */
  uint8_t suspension_indicator;  /* byte 4 */
  uint8_t series_status;         /* byte 5 */
  uint8_t filler_2[2];           /* bytes 6 to 7 */
} SeriesStatusMessage;

/* any Series Status Message at all: every byte one the checker chooses */
static void any_series_status_message(SeriesStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  record->suspension_indicator = arbitrary();
  record->series_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
}

/* Series Status Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_series_status_message(const SeriesStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  wire[at++] = record->suspension_indicator;
  wire[at++] = record->series_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }

  return at;
}

/* Series Status Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_series_status_message(SeriesStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  record->suspension_indicator = wire[at++];
  record->series_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }

  return at;
}

/* what was read of Series Status Message is what was written, byte for byte */
static void equal_series_status_message(const SeriesStatusMessage *read, const SeriesStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  assert(read->suspension_indicator == written->suspension_indicator);
  assert(read->series_status == written->series_status);
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
}

/* Series Status Message: written and read back, then read and written back */
static void check_series_status_message(void) {
  SeriesStatusMessage sent;
  SeriesStatusMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_series_status_message(&sent);
  assert(encode_series_status_message(&sent, wire, 0) == 8);
  assert(decode_series_status_message(&got, wire, 0) == 8);
  equal_series_status_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_series_status_message(&got, wire, 0) == 8);
  assert(encode_series_status_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Commodity Status Message: 4 bytes --------------------------------------- */

/* The Commodity Status message is generated whenever a commodity status changes */
typedef struct {
  uint8_t commodity_code[2];  /* bytes 0 to 1 */
  uint8_t suspended;          /* byte 2 */
  uint8_t locked;             /* byte 3 */
} CommodityStatusMessage;

/* any Commodity Status Message at all: every byte one the checker chooses */
static void any_commodity_status_message(CommodityStatusMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->commodity_code[i] = arbitrary(); }
  record->suspended = arbitrary();
  record->locked = arbitrary();
}

/* Commodity Status Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_commodity_status_message(const CommodityStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->commodity_code[i]; }
  wire[at++] = record->suspended;
  wire[at++] = record->locked;

  return at;
}

/* Commodity Status Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_commodity_status_message(CommodityStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->commodity_code[i] = wire[at++]; }
  record->suspended = wire[at++];
  record->locked = wire[at++];

  return at;
}

/* what was read of Commodity Status Message is what was written, byte for byte */
static void equal_commodity_status_message(const CommodityStatusMessage *read, const CommodityStatusMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->commodity_code[i] == written->commodity_code[i]); }
  assert(read->suspended == written->suspended);
  assert(read->locked == written->locked);
}

/* Commodity Status Message: written and read back, then read and written back */
static void check_commodity_status_message(void) {
  CommodityStatusMessage sent;
  CommodityStatusMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_commodity_status_message(&sent);
  assert(encode_commodity_status_message(&sent, wire, 0) == 4);
  assert(decode_commodity_status_message(&got, wire, 0) == 4);
  equal_commodity_status_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_commodity_status_message(&got, wire, 0) == 4);
  assert(encode_commodity_status_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Statistics Message: 56 bytes -------------------------------------- */

/* Trade information for completed deals */
typedef struct {
  uint8_t orderbook_id[4];                   /* bytes 0 to 3 */
  uint8_t price[4];                          /* bytes 4 to 7 */
  uint8_t deal_source;                       /* byte 8 */
  uint8_t session;                           /* byte 9 */
  uint8_t filler_2[2];                       /* bytes 10 to 11 */
  uint8_t statistics_aggregate_quantity[8];  /* bytes 12 to 19 */
  uint8_t open[4];                           /* bytes 20 to 23 */
  uint8_t high[4];                           /* bytes 24 to 27 */
  uint8_t low[4];                            /* bytes 28 to 31 */
  uint8_t filler_4[4];                       /* bytes 32 to 35 */
  uint8_t trade_report_volume[8];            /* bytes 36 to 43 */
  uint8_t deal_count[4];                     /* bytes 44 to 47 */
  uint8_t turnover[8];                       /* bytes 48 to 55 */
} TradeStatisticsMessage;

/* any Trade Statistics Message at all: every byte one the checker chooses */
static void any_trade_statistics_message(TradeStatisticsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->deal_source = arbitrary();
  record->session = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->statistics_aggregate_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_report_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->deal_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
}

/* Trade Statistics Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_trade_statistics_message(const TradeStatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->deal_source;
  wire[at++] = record->session;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->statistics_aggregate_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_report_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->deal_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }

  return at;
}

/* Trade Statistics Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_trade_statistics_message(TradeStatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->deal_source = wire[at++];
  record->session = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->statistics_aggregate_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_report_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->deal_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Statistics Message is what was written, byte for byte */
static void equal_trade_statistics_message(const TradeStatisticsMessage *read, const TradeStatisticsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->deal_source == written->deal_source);
  assert(read->session == written->session);
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->statistics_aggregate_quantity[i] == written->statistics_aggregate_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open[i] == written->open[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_report_volume[i] == written->trade_report_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->deal_count[i] == written->deal_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
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
  check_calculated_opening_price_message();
  check_implied_volatility_message();
  check_open_interest_message();
  check_delete_order_message();
  check_orderbook_clear_message();
  check_commodity_definition_message();
  check_class_definition_message();
  check_series_definition_base_message();
  check_series_definition_extended_message();
  check_combination_definition_message();
  check_refresh_complete();
  check_series_statistics_message();
  check_market_status_message();
  check_series_status_message();
  check_commodity_status_message();
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
