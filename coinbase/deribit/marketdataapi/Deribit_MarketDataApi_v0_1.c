// coinbase/deribit/marketdataapi/Deribit_MarketDataApi_v0_1.c
/*
 * Coinbase Market Data Api
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
 *   - a field read in bits
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

/* ---- Logical Expiry: 8 bytes ------------------------------------------------- */

/* InstrumentMessage */
typedef struct {
  uint8_t year[2];           /* bytes 0 to 1 */
  uint8_t month[2];          /* bytes 2 to 3 */
  uint8_t week_of_month[2];  /* bytes 4 to 5 */
  uint8_t day_of_month[2];   /* bytes 6 to 7 */
} LogicalExpiry;

/* any Logical Expiry at all: every byte one the checker chooses */
static void any_logical_expiry(LogicalExpiry *record) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->week_of_month[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->day_of_month[i] = arbitrary(); }
}

/* Logical Expiry to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_logical_expiry(const LogicalExpiry *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->week_of_month[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->day_of_month[i]; }

  return at;
}

/* Logical Expiry off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_logical_expiry(LogicalExpiry *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->week_of_month[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->day_of_month[i] = wire[at++]; }

  return at;
}

/* what was read of Logical Expiry is what was written, byte for byte */
static void equal_logical_expiry(const LogicalExpiry *read, const LogicalExpiry *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->week_of_month[i] == written->week_of_month[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->day_of_month[i] == written->day_of_month[i]); }
}

/* Logical Expiry: written and read back, then read and written back */
static void check_logical_expiry(void) {
  LogicalExpiry sent;
  LogicalExpiry got;
  uint8_t wire[8];
  uint8_t again[8];

  any_logical_expiry(&sent);
  assert(encode_logical_expiry(&sent, wire, 0) == 8);
  assert(decode_logical_expiry(&got, wire, 0) == 8);
  equal_logical_expiry(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_logical_expiry(&got, wire, 0) == 8);
  assert(encode_logical_expiry(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Update Message: 9 bytes ---------------------------------- */

/* TradingStatusUpdateMessage */
typedef struct {
  uint8_t instrument_id[8];  /* bytes 0 to 7 */
  uint8_t trading_status;    /* byte 8 */
} TradingStatusUpdateMessage;

/* any Trading Status Update Message at all: every byte one the checker chooses */
static void any_trading_status_update_message(TradingStatusUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = arbitrary(); }
  record->trading_status = arbitrary();
}

/* Trading Status Update Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_update_message(const TradingStatusUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->trading_status;

  return at;
}

/* Trading Status Update Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_update_message(TradingStatusUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = wire[at++]; }
  record->trading_status = wire[at++];

  return at;
}

/* what was read of Trading Status Update Message is what was written, byte for byte */
static void equal_trading_status_update_message(const TradingStatusUpdateMessage *read, const TradingStatusUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->trading_status == written->trading_status);
}

/* Trading Status Update Message: written and read back, then read and written back */
static void check_trading_status_update_message(void) {
  TradingStatusUpdateMessage sent;
  TradingStatusUpdateMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_trading_status_update_message(&sent);
  assert(encode_trading_status_update_message(&sent, wire, 0) == 9);
  assert(decode_trading_status_update_message(&got, wire, 0) == 9);
  equal_trading_status_update_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_update_message(&got, wire, 0) == 9);
  assert(encode_trading_status_update_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Info Message: 40 bytes --------------------------------------- */

/* InstrumentInfoMessage */
typedef struct {
  uint8_t instrument_id[8];   /* bytes 0 to 7 */
  uint8_t min_sell_price[8];  /* bytes 8 to 15 */
  uint8_t max_buy_price[8];   /* bytes 16 to 23 */
  uint8_t index_price[8];     /* bytes 24 to 31 */
  uint8_t mark_price[8];      /* bytes 32 to 39 */
} InstrumentInfoMessage;

/* any Instrument Info Message at all: every byte one the checker chooses */
static void any_instrument_info_message(InstrumentInfoMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_sell_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_buy_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mark_price[i] = arbitrary(); }
}

/* Instrument Info Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_instrument_info_message(const InstrumentInfoMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_sell_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_buy_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mark_price[i]; }

  return at;
}

/* Instrument Info Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_instrument_info_message(InstrumentInfoMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_sell_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_buy_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mark_price[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Info Message is what was written, byte for byte */
static void equal_instrument_info_message(const InstrumentInfoMessage *read, const InstrumentInfoMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_sell_price[i] == written->min_sell_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_buy_price[i] == written->max_buy_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_price[i] == written->index_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mark_price[i] == written->mark_price[i]); }
}

/* Instrument Info Message: written and read back, then read and written back */
static void check_instrument_info_message(void) {
  InstrumentInfoMessage sent;
  InstrumentInfoMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_instrument_info_message(&sent);
  assert(encode_instrument_info_message(&sent, wire, 0) == 40);
  assert(decode_instrument_info_message(&got, wire, 0) == 40);
  equal_instrument_info_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_info_message(&got, wire, 0) == 40);
  assert(encode_instrument_info_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Ref Message: 48 bytes ---------------------------------------- */

/* InstrumentRefMessage */
typedef struct {
  uint8_t instrument_id[8];             /* bytes 0 to 7 */
  uint8_t current_funding[8];           /* bytes 8 to 15 */
  uint8_t funding_8h[8];                /* bytes 16 to 23 */
  uint8_t estimated_delivery_price[8];  /* bytes 24 to 31 */
  uint8_t delivery_price[8];            /* bytes 32 to 39 */
  uint8_t settlement_price[8];          /* bytes 40 to 47 */
} InstrumentRefMessage;

/* any Instrument Ref Message at all: every byte one the checker chooses */
static void any_instrument_ref_message(InstrumentRefMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->current_funding[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->funding_8h[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->estimated_delivery_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->delivery_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = arbitrary(); }
}

/* Instrument Ref Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_instrument_ref_message(const InstrumentRefMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->current_funding[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->funding_8h[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->estimated_delivery_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->delivery_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price[i]; }

  return at;
}

/* Instrument Ref Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_instrument_ref_message(InstrumentRefMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->current_funding[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->funding_8h[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->estimated_delivery_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->delivery_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Ref Message is what was written, byte for byte */
static void equal_instrument_ref_message(const InstrumentRefMessage *read, const InstrumentRefMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->current_funding[i] == written->current_funding[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->funding_8h[i] == written->funding_8h[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->estimated_delivery_price[i] == written->estimated_delivery_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->delivery_price[i] == written->delivery_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
}

/* Instrument Ref Message: written and read back, then read and written back */
static void check_instrument_ref_message(void) {
  InstrumentRefMessage sent;
  InstrumentRefMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_instrument_ref_message(&sent);
  assert(encode_instrument_ref_message(&sent, wire, 0) == 48);
  assert(decode_instrument_ref_message(&got, wire, 0) == 48);
  equal_instrument_ref_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_ref_message(&got, wire, 0) == 48);
  assert(encode_instrument_ref_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Put Message: 32 bytes ----------------------------------------------- */

/* BidPutMessage */
typedef struct {
  uint8_t order_id[8];           /* bytes 0 to 7 */
  uint8_t instrument_id[8];      /* bytes 8 to 15 */
  uint8_t quantity_mantissa[8];  /* bytes 16 to 23 */
  uint8_t price[8];              /* bytes 24 to 31 */
} BidPutMessage;

/* any Bid Put Message at all: every byte one the checker chooses */
static void any_bid_put_message(BidPutMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_mantissa[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Bid Put Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_bid_put_message(const BidPutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_mantissa[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Bid Put Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_bid_put_message(BidPutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_mantissa[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Bid Put Message is what was written, byte for byte */
static void equal_bid_put_message(const BidPutMessage *read, const BidPutMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_mantissa[i] == written->quantity_mantissa[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Bid Put Message: written and read back, then read and written back */
static void check_bid_put_message(void) {
  BidPutMessage sent;
  BidPutMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_bid_put_message(&sent);
  assert(encode_bid_put_message(&sent, wire, 0) == 32);
  assert(decode_bid_put_message(&got, wire, 0) == 32);
  equal_bid_put_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_put_message(&got, wire, 0) == 32);
  assert(encode_bid_put_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Put Message: 32 bytes ----------------------------------------------- */

/* AskPutMessage */
typedef struct {
  uint8_t order_id[8];           /* bytes 0 to 7 */
  uint8_t instrument_id[8];      /* bytes 8 to 15 */
  uint8_t quantity_mantissa[8];  /* bytes 16 to 23 */
  uint8_t price[8];              /* bytes 24 to 31 */
} AskPutMessage;

/* any Ask Put Message at all: every byte one the checker chooses */
static void any_ask_put_message(AskPutMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_mantissa[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Ask Put Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_ask_put_message(const AskPutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_mantissa[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Ask Put Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_ask_put_message(AskPutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_mantissa[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Ask Put Message is what was written, byte for byte */
static void equal_ask_put_message(const AskPutMessage *read, const AskPutMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_mantissa[i] == written->quantity_mantissa[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Ask Put Message: written and read back, then read and written back */
static void check_ask_put_message(void) {
  AskPutMessage sent;
  AskPutMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_ask_put_message(&sent);
  assert(encode_ask_put_message(&sent, wire, 0) == 32);
  assert(decode_ask_put_message(&got, wire, 0) == 32);
  equal_ask_put_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_put_message(&got, wire, 0) == 32);
  assert(encode_ask_put_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Qty Reduced Message: 24 bytes --------------------------------------- */

/* BidQtyReducedMessage */
typedef struct {
  uint8_t order_id[8];           /* bytes 0 to 7 */
  uint8_t instrument_id[8];      /* bytes 8 to 15 */
  uint8_t quantity_mantissa[8];  /* bytes 16 to 23 */
} BidQtyReducedMessage;

/* any Bid Qty Reduced Message at all: every byte one the checker chooses */
static void any_bid_qty_reduced_message(BidQtyReducedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_mantissa[i] = arbitrary(); }
}

/* Bid Qty Reduced Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_bid_qty_reduced_message(const BidQtyReducedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_mantissa[i]; }

  return at;
}

/* Bid Qty Reduced Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_bid_qty_reduced_message(BidQtyReducedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_mantissa[i] = wire[at++]; }

  return at;
}

/* what was read of Bid Qty Reduced Message is what was written, byte for byte */
static void equal_bid_qty_reduced_message(const BidQtyReducedMessage *read, const BidQtyReducedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_mantissa[i] == written->quantity_mantissa[i]); }
}

/* Bid Qty Reduced Message: written and read back, then read and written back */
static void check_bid_qty_reduced_message(void) {
  BidQtyReducedMessage sent;
  BidQtyReducedMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_bid_qty_reduced_message(&sent);
  assert(encode_bid_qty_reduced_message(&sent, wire, 0) == 24);
  assert(decode_bid_qty_reduced_message(&got, wire, 0) == 24);
  equal_bid_qty_reduced_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_qty_reduced_message(&got, wire, 0) == 24);
  assert(encode_bid_qty_reduced_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Qty Reduced Message: 24 bytes --------------------------------------- */

/* AskQtyReducedMessage */
typedef struct {
  uint8_t order_id[8];           /* bytes 0 to 7 */
  uint8_t instrument_id[8];      /* bytes 8 to 15 */
  uint8_t quantity_mantissa[8];  /* bytes 16 to 23 */
} AskQtyReducedMessage;

/* any Ask Qty Reduced Message at all: every byte one the checker chooses */
static void any_ask_qty_reduced_message(AskQtyReducedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_mantissa[i] = arbitrary(); }
}

/* Ask Qty Reduced Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_ask_qty_reduced_message(const AskQtyReducedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_mantissa[i]; }

  return at;
}

/* Ask Qty Reduced Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_ask_qty_reduced_message(AskQtyReducedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_mantissa[i] = wire[at++]; }

  return at;
}

/* what was read of Ask Qty Reduced Message is what was written, byte for byte */
static void equal_ask_qty_reduced_message(const AskQtyReducedMessage *read, const AskQtyReducedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_mantissa[i] == written->quantity_mantissa[i]); }
}

/* Ask Qty Reduced Message: written and read back, then read and written back */
static void check_ask_qty_reduced_message(void) {
  AskQtyReducedMessage sent;
  AskQtyReducedMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_ask_qty_reduced_message(&sent);
  assert(encode_ask_qty_reduced_message(&sent, wire, 0) == 24);
  assert(decode_ask_qty_reduced_message(&got, wire, 0) == 24);
  equal_ask_qty_reduced_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_qty_reduced_message(&got, wire, 0) == 24);
  assert(encode_ask_qty_reduced_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Delete Message: 16 bytes -------------------------------------------- */

/* BidDeleteMessage */
typedef struct {
  uint8_t order_id[8];       /* bytes 0 to 7 */
  uint8_t instrument_id[8];  /* bytes 8 to 15 */
} BidDeleteMessage;

/* any Bid Delete Message at all: every byte one the checker chooses */
static void any_bid_delete_message(BidDeleteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = arbitrary(); }
}

/* Bid Delete Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_bid_delete_message(const BidDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument_id[i]; }

  return at;
}

/* Bid Delete Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_bid_delete_message(BidDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = wire[at++]; }

  return at;
}

/* what was read of Bid Delete Message is what was written, byte for byte */
static void equal_bid_delete_message(const BidDeleteMessage *read, const BidDeleteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
}

/* Bid Delete Message: written and read back, then read and written back */
static void check_bid_delete_message(void) {
  BidDeleteMessage sent;
  BidDeleteMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_bid_delete_message(&sent);
  assert(encode_bid_delete_message(&sent, wire, 0) == 16);
  assert(decode_bid_delete_message(&got, wire, 0) == 16);
  equal_bid_delete_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_delete_message(&got, wire, 0) == 16);
  assert(encode_bid_delete_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Delete Message: 16 bytes -------------------------------------------- */

/* AskDeleteMessage */
typedef struct {
  uint8_t order_id[8];       /* bytes 0 to 7 */
  uint8_t instrument_id[8];  /* bytes 8 to 15 */
} AskDeleteMessage;

/* any Ask Delete Message at all: every byte one the checker chooses */
static void any_ask_delete_message(AskDeleteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = arbitrary(); }
}

/* Ask Delete Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_ask_delete_message(const AskDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument_id[i]; }

  return at;
}

/* Ask Delete Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_ask_delete_message(AskDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = wire[at++]; }

  return at;
}

/* what was read of Ask Delete Message is what was written, byte for byte */
static void equal_ask_delete_message(const AskDeleteMessage *read, const AskDeleteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
}

/* Ask Delete Message: written and read back, then read and written back */
static void check_ask_delete_message(void) {
  AskDeleteMessage sent;
  AskDeleteMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_ask_delete_message(&sent);
  assert(encode_ask_delete_message(&sent, wire, 0) == 16);
  assert(decode_ask_delete_message(&got, wire, 0) == 16);
  equal_ask_delete_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_delete_message(&got, wire, 0) == 16);
  assert(encode_ask_delete_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Header Message: 24 bytes --------------------------------------- */

/* SnapshotHeaderMessage */
typedef struct {
  uint8_t instrument_id[8];          /* bytes 0 to 7 */
  uint8_t incremental_timestamp[8];  /* bytes 8 to 15 */
  uint8_t incremental_seq_num[8];    /* bytes 16 to 23 */
} SnapshotHeaderMessage;

/* any Snapshot Header Message at all: every byte one the checker chooses */
static void any_snapshot_header_message(SnapshotHeaderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->incremental_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->incremental_seq_num[i] = arbitrary(); }
}

/* Snapshot Header Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_header_message(const SnapshotHeaderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->incremental_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->incremental_seq_num[i]; }

  return at;
}

/* Snapshot Header Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_header_message(SnapshotHeaderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->incremental_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->incremental_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot Header Message is what was written, byte for byte */
static void equal_snapshot_header_message(const SnapshotHeaderMessage *read, const SnapshotHeaderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->incremental_timestamp[i] == written->incremental_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->incremental_seq_num[i] == written->incremental_seq_num[i]); }
}

/* Snapshot Header Message: written and read back, then read and written back */
static void check_snapshot_header_message(void) {
  SnapshotHeaderMessage sent;
  SnapshotHeaderMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_snapshot_header_message(&sent);
  assert(encode_snapshot_header_message(&sent, wire, 0) == 24);
  assert(decode_snapshot_header_message(&got, wire, 0) == 24);
  equal_snapshot_header_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_header_message(&got, wire, 0) == 24);
  assert(encode_snapshot_header_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Trailer Message: 24 bytes -------------------------------------- */

/* SnapshotTrailerMessage */
typedef struct {
  uint8_t instrument_id[8];      /* bytes 0 to 7 */
  uint8_t timestamp[8];          /* bytes 8 to 15 */
  uint8_t increment_seq_num[8];  /* bytes 16 to 23 */
} SnapshotTrailerMessage;

/* any Snapshot Trailer Message at all: every byte one the checker chooses */
static void any_snapshot_trailer_message(SnapshotTrailerMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->increment_seq_num[i] = arbitrary(); }
}

/* Snapshot Trailer Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_trailer_message(const SnapshotTrailerMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->increment_seq_num[i]; }

  return at;
}

/* Snapshot Trailer Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_trailer_message(SnapshotTrailerMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->increment_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot Trailer Message is what was written, byte for byte */
static void equal_snapshot_trailer_message(const SnapshotTrailerMessage *read, const SnapshotTrailerMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->increment_seq_num[i] == written->increment_seq_num[i]); }
}

/* Snapshot Trailer Message: written and read back, then read and written back */
static void check_snapshot_trailer_message(void) {
  SnapshotTrailerMessage sent;
  SnapshotTrailerMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_snapshot_trailer_message(&sent);
  assert(encode_snapshot_trailer_message(&sent, wire, 0) == 24);
  assert(decode_snapshot_trailer_message(&got, wire, 0) == 24);
  equal_snapshot_trailer_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_trailer_message(&got, wire, 0) == 24);
  assert(encode_snapshot_trailer_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Cycle Message: 4 bytes ------------------------------------------- */

/* EndOfCycleMessage */
typedef struct {
  uint8_t active_instrument_count[4];  /* bytes 0 to 3 */
} EndOfCycleMessage;

/* any End Of Cycle Message at all: every byte one the checker chooses */
static void any_end_of_cycle_message(EndOfCycleMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->active_instrument_count[i] = arbitrary(); }
}

/* End Of Cycle Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_end_of_cycle_message(const EndOfCycleMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->active_instrument_count[i]; }

  return at;
}

/* End Of Cycle Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_end_of_cycle_message(EndOfCycleMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->active_instrument_count[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Cycle Message is what was written, byte for byte */
static void equal_end_of_cycle_message(const EndOfCycleMessage *read, const EndOfCycleMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->active_instrument_count[i] == written->active_instrument_count[i]); }
}

/* End Of Cycle Message: written and read back, then read and written back */
static void check_end_of_cycle_message(void) {
  EndOfCycleMessage sent;
  EndOfCycleMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_end_of_cycle_message(&sent);
  assert(encode_end_of_cycle_message(&sent, wire, 0) == 4);
  assert(decode_end_of_cycle_message(&got, wire, 0) == 4);
  equal_end_of_cycle_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_cycle_message(&got, wire, 0) == 4);
  assert(encode_end_of_cycle_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmit Request Message: 9 bytes ------------------------------------- */

/* RetransmitRequestMessage */
typedef struct {
  uint8_t begin_seq_num[8];     /* bytes 0 to 7 */
  uint8_t message_count_short;  /* byte 8 */
} RetransmitRequestMessage;

/* any Retransmit Request Message at all: every byte one the checker chooses */
static void any_retransmit_request_message(RetransmitRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->begin_seq_num[i] = arbitrary(); }
  record->message_count_short = arbitrary();
}

/* Retransmit Request Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_retransmit_request_message(const RetransmitRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->begin_seq_num[i]; }
  wire[at++] = record->message_count_short;

  return at;
}

/* Retransmit Request Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_retransmit_request_message(RetransmitRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->begin_seq_num[i] = wire[at++]; }
  record->message_count_short = wire[at++];

  return at;
}

/* what was read of Retransmit Request Message is what was written, byte for byte */
static void equal_retransmit_request_message(const RetransmitRequestMessage *read, const RetransmitRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->begin_seq_num[i] == written->begin_seq_num[i]); }
  assert(read->message_count_short == written->message_count_short);
}

/* Retransmit Request Message: written and read back, then read and written back */
static void check_retransmit_request_message(void) {
  RetransmitRequestMessage sent;
  RetransmitRequestMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_retransmit_request_message(&sent);
  assert(encode_retransmit_request_message(&sent, wire, 0) == 9);
  assert(decode_retransmit_request_message(&got, wire, 0) == 9);
  equal_retransmit_request_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmit_request_message(&got, wire, 0) == 9);
  assert(encode_retransmit_request_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmit Reject Message: 49 bytes ------------------------------------- */

/* RetransmitRejectMessage */
typedef struct {
  uint8_t retry_delay_nanos[8];  /* bytes 0 to 7 */
  uint8_t details[40];           /* bytes 8 to 47 */
  uint8_t reason;                /* byte 48 */
} RetransmitRejectMessage;

/* any Retransmit Reject Message at all: every byte one the checker chooses */
static void any_retransmit_reject_message(RetransmitRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->retry_delay_nanos[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->details[i] = arbitrary(); }
  record->reason = arbitrary();
}

/* Retransmit Reject Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_retransmit_reject_message(const RetransmitRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->retry_delay_nanos[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->details[i]; }
  wire[at++] = record->reason;

  return at;
}

/* Retransmit Reject Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_retransmit_reject_message(RetransmitRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->retry_delay_nanos[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->details[i] = wire[at++]; }
  record->reason = wire[at++];

  return at;
}

/* what was read of Retransmit Reject Message is what was written, byte for byte */
static void equal_retransmit_reject_message(const RetransmitRejectMessage *read, const RetransmitRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->retry_delay_nanos[i] == written->retry_delay_nanos[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->details[i] == written->details[i]); }
  assert(read->reason == written->reason);
}

/* Retransmit Reject Message: written and read back, then read and written back */
static void check_retransmit_reject_message(void) {
  RetransmitRejectMessage sent;
  RetransmitRejectMessage got;
  uint8_t wire[49];
  uint8_t again[49];

  any_retransmit_reject_message(&sent);
  assert(encode_retransmit_reject_message(&sent, wire, 0) == 49);
  assert(decode_retransmit_reject_message(&got, wire, 0) == 49);
  equal_retransmit_reject_message(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmit_reject_message(&got, wire, 0) == 49);
  assert(encode_retransmit_reject_message(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_logical_expiry();
  check_trading_status_update_message();
  check_instrument_info_message();
  check_instrument_ref_message();
  check_bid_put_message();
  check_ask_put_message();
  check_bid_qty_reduced_message();
  check_ask_qty_reduced_message();
  check_bid_delete_message();
  check_ask_delete_message();
  check_snapshot_header_message();
  check_snapshot_trailer_message();
  check_end_of_cycle_message();
  check_retransmit_request_message();
  check_retransmit_reject_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
