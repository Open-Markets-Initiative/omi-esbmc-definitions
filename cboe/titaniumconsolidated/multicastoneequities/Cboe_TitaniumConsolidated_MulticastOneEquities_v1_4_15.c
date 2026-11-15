// cboe/titaniumconsolidated/multicastoneequities/Cboe_TitaniumConsolidated_MulticastOneEquities_v1_4_15.c
/*
 * Chicago Board Options Exchange Multicast One Equities
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

/* ---- Clear Quote Message: 17 bytes ------------------------------------------- */

/* The Clear Quote message instructs feed recipients to clear all quotes and Summary and/or ADAP information for the specified symbol on the specified market(s). */
typedef struct {
  uint8_t last_update_timestamp[8];  /* bytes 0 to 7 */
  uint8_t symbol[8];                 /* bytes 8 to 15 */
  uint8_t market_center;             /* byte 16 */
} ClearQuoteMessage;

/* any Clear Quote Message at all: every byte one the checker chooses */
static void any_clear_quote_message(ClearQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->last_update_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->market_center = arbitrary();
}

/* Clear Quote Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_clear_quote_message(const ClearQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_update_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->market_center;

  return at;
}

/* Clear Quote Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_clear_quote_message(ClearQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->last_update_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->market_center = wire[at++];

  return at;
}

/* what was read of Clear Quote Message is what was written, byte for byte */
static void equal_clear_quote_message(const ClearQuoteMessage *read, const ClearQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->last_update_timestamp[i] == written->last_update_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->market_center == written->market_center);
}

/* Clear Quote Message: written and read back, then read and written back */
static void check_clear_quote_message(void) {
  ClearQuoteMessage sent;
  ClearQuoteMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_clear_quote_message(&sent);
  assert(encode_clear_quote_message(&sent, wire, 0) == 17);
  assert(decode_clear_quote_message(&got, wire, 0) == 17);
  equal_clear_quote_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_clear_quote_message(&got, wire, 0) == 17);
  assert(encode_clear_quote_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Best Quote Update Message: 33 bytes ------------------------------------- */

/* The Best Quote Update message is used to update one side of the Cboe consolidated quote information for a symbol. */
typedef struct {
  uint8_t last_update_timestamp[8];          /* bytes 0 to 7 */
  uint8_t symbol[8];                         /* bytes 8 to 15 */
  uint8_t side_indicator;                    /* byte 16 */
  uint8_t consolidated_best_quote_price[8];  /* bytes 17 to 24 */
  uint8_t consolidated_quote_quantity[8];    /* bytes 25 to 32 */
} BestQuoteUpdateMessage;

/* any Best Quote Update Message at all: every byte one the checker chooses */
static void any_best_quote_update_message(BestQuoteUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->last_update_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->consolidated_best_quote_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_quote_quantity[i] = arbitrary(); }
}

/* Best Quote Update Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_best_quote_update_message(const BestQuoteUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_update_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_best_quote_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_quote_quantity[i]; }

  return at;
}

/* Best Quote Update Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_best_quote_update_message(BestQuoteUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->last_update_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->consolidated_best_quote_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_quote_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Best Quote Update Message is what was written, byte for byte */
static void equal_best_quote_update_message(const BestQuoteUpdateMessage *read, const BestQuoteUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->last_update_timestamp[i] == written->last_update_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_best_quote_price[i] == written->consolidated_best_quote_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_quote_quantity[i] == written->consolidated_quote_quantity[i]); }
}

/* Best Quote Update Message: written and read back, then read and written back */
static void check_best_quote_update_message(void) {
  BestQuoteUpdateMessage sent;
  BestQuoteUpdateMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_best_quote_update_message(&sent);
  assert(encode_best_quote_update_message(&sent, wire, 0) == 33);
  assert(decode_best_quote_update_message(&got, wire, 0) == 33);
  equal_best_quote_update_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_best_quote_update_message(&got, wire, 0) == 33);
  assert(encode_best_quote_update_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cboe Market Status Message: 11 bytes ------------------------------------ */

/* The Cboe Market Status message is disseminated to reflect a change in the status of a market. */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t market_center;      /* byte 8 */
  uint8_t market_status;      /* byte 9 */
  uint8_t session_indicator;  /* byte 10 */
} CboeMarketStatusMessage;

/* any Cboe Market Status Message at all: every byte one the checker chooses */
static void any_cboe_market_status_message(CboeMarketStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->market_center = arbitrary();
  record->market_status = arbitrary();
  record->session_indicator = arbitrary();
}

/* Cboe Market Status Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_cboe_market_status_message(const CboeMarketStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->market_center;
  wire[at++] = record->market_status;
  wire[at++] = record->session_indicator;

  return at;
}

/* Cboe Market Status Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_cboe_market_status_message(CboeMarketStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->market_center = wire[at++];
  record->market_status = wire[at++];
  record->session_indicator = wire[at++];

  return at;
}

/* what was read of Cboe Market Status Message is what was written, byte for byte */
static void equal_cboe_market_status_message(const CboeMarketStatusMessage *read, const CboeMarketStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->market_center == written->market_center);
  assert(read->market_status == written->market_status);
  assert(read->session_indicator == written->session_indicator);
}

/* Cboe Market Status Message: written and read back, then read and written back */
static void check_cboe_market_status_message(void) {
  CboeMarketStatusMessage sent;
  CboeMarketStatusMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_cboe_market_status_message(&sent);
  assert(encode_cboe_market_status_message(&sent, wire, 0) == 11);
  assert(decode_cboe_market_status_message(&got, wire, 0) == 11);
  equal_cboe_market_status_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_cboe_market_status_message(&got, wire, 0) == 11);
  assert(encode_cboe_market_status_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Update Adap Block: 10 bytes --------------------------------------- */

/* Short Update ADAP Block */
typedef struct {
  uint8_t market_center;      /* byte 0 */
  uint8_t side;               /* byte 1 */
  uint8_t price_short[4];     /* bytes 2 to 5 */
  uint8_t quantity_short[4];  /* bytes 6 to 9 */
} ShortUpdateAdapBlock;

/* any Short Update Adap Block at all: every byte one the checker chooses */
static void any_short_update_adap_block(ShortUpdateAdapBlock *record) {
  record->market_center = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_short[i] = arbitrary(); }
}

/* Short Update Adap Block to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_short_update_adap_block(const ShortUpdateAdapBlock *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center;
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_short[i]; }

  return at;
}

/* Short Update Adap Block off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_short_update_adap_block(ShortUpdateAdapBlock *record, const uint8_t *wire, size_t at) {
  record->market_center = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_short[i] = wire[at++]; }

  return at;
}

/* what was read of Short Update Adap Block is what was written, byte for byte */
static void equal_short_update_adap_block(const ShortUpdateAdapBlock *read, const ShortUpdateAdapBlock *written) {
  assert(read->market_center == written->market_center);
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
}

/* Short Update Adap Block: written and read back, then read and written back */
static void check_short_update_adap_block(void) {
  ShortUpdateAdapBlock sent;
  ShortUpdateAdapBlock got;
  uint8_t wire[10];
  uint8_t again[10];

  any_short_update_adap_block(&sent);
  assert(encode_short_update_adap_block(&sent, wire, 0) == 10);
  assert(decode_short_update_adap_block(&got, wire, 0) == 10);
  equal_short_update_adap_block(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_short_update_adap_block(&got, wire, 0) == 10);
  assert(encode_short_update_adap_block(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Update Adap Block: 18 bytes ---------------------------------------- */

/* Long Update ADAP Block */
typedef struct {
  uint8_t market_center;     /* byte 0 */
  uint8_t side;              /* byte 1 */
  uint8_t price_long[8];     /* bytes 2 to 9 */
  uint8_t quantity_long[8];  /* bytes 10 to 17 */
} LongUpdateAdapBlock;

/* any Long Update Adap Block at all: every byte one the checker chooses */
static void any_long_update_adap_block(LongUpdateAdapBlock *record) {
  record->market_center = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_long[i] = arbitrary(); }
}

/* Long Update Adap Block to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_long_update_adap_block(const LongUpdateAdapBlock *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_center;
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_long[i]; }

  return at;
}

/* Long Update Adap Block off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_long_update_adap_block(LongUpdateAdapBlock *record, const uint8_t *wire, size_t at) {
  record->market_center = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Long Update Adap Block is what was written, byte for byte */
static void equal_long_update_adap_block(const LongUpdateAdapBlock *read, const LongUpdateAdapBlock *written) {
  assert(read->market_center == written->market_center);
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
}

/* Long Update Adap Block: written and read back, then read and written back */
static void check_long_update_adap_block(void) {
  LongUpdateAdapBlock sent;
  LongUpdateAdapBlock got;
  uint8_t wire[18];
  uint8_t again[18];

  any_long_update_adap_block(&sent);
  assert(encode_long_update_adap_block(&sent, wire, 0) == 18);
  assert(decode_long_update_adap_block(&got, wire, 0) == 18);
  equal_long_update_adap_block(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_long_update_adap_block(&got, wire, 0) == 18);
  assert(encode_long_update_adap_block(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rpi Message: 18 bytes --------------------------------------------------- */

/* The Retail Price Improvement (RPI) message is a retail liquidity indicator that includes symbol and side, but not price and size. */
typedef struct {
  uint8_t timestamp[8];              /* bytes 0 to 7 */
  uint8_t symbol[8];                 /* bytes 8 to 15 */
  uint8_t market_center;             /* byte 16 */
  uint8_t retail_price_improvement;  /* byte 17 */
} RpiMessage;

/* any Rpi Message at all: every byte one the checker chooses */
static void any_rpi_message(RpiMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->market_center = arbitrary();
  record->retail_price_improvement = arbitrary();
}

/* Rpi Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_rpi_message(const RpiMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->market_center;
  wire[at++] = record->retail_price_improvement;

  return at;
}

/* Rpi Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_rpi_message(RpiMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->market_center = wire[at++];
  record->retail_price_improvement = wire[at++];

  return at;
}

/* what was read of Rpi Message is what was written, byte for byte */
static void equal_rpi_message(const RpiMessage *read, const RpiMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->market_center == written->market_center);
  assert(read->retail_price_improvement == written->retail_price_improvement);
}

/* Rpi Message: written and read back, then read and written back */
static void check_rpi_message(void) {
  RpiMessage sent;
  RpiMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_rpi_message(&sent);
  assert(encode_rpi_message(&sent, wire, 0) == 18);
  assert(decode_rpi_message(&got, wire, 0) == 18);
  equal_rpi_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_rpi_message(&got, wire, 0) == 18);
  assert(encode_rpi_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 19 bytes ---------------------------------------- */

/* The Trading Status message is used to indicate the current trading status of a security on a Cboe exchange. */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t symbol[8];       /* bytes 8 to 15 */
  uint8_t market_center;   /* byte 16 */
  uint8_t trading_status;  /* byte 17 */
  uint8_t reg_sho_action;  /* byte 18 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->market_center = arbitrary();
  record->trading_status = arbitrary();
  record->reg_sho_action = arbitrary();
}

/* Trading Status Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->market_center;
  wire[at++] = record->trading_status;
  wire[at++] = record->reg_sho_action;

  return at;
}

/* Trading Status Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->market_center = wire[at++];
  record->trading_status = wire[at++];
  record->reg_sho_action = wire[at++];

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->market_center == written->market_center);
  assert(read->trading_status == written->trading_status);
  assert(read->reg_sho_action == written->reg_sho_action);
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 19);
  assert(decode_trading_status_message(&got, wire, 0) == 19);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 19);
  assert(encode_trading_status_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Closing Price Message: 26 bytes --------------------------------- */

/* The Opening/Closing Price message is used to indicate the Opening or Closing price of a security on any of the Cboe markets and the primary listing market. */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t symbol[8];             /* bytes 8 to 15 */
  uint8_t market_center;         /* byte 16 */
  uint8_t open_close_indicator;  /* byte 17 */
  uint8_t price_long[8];         /* bytes 18 to 25 */
} OpeningClosingPriceMessage;

/* any Opening Closing Price Message at all: every byte one the checker chooses */
static void any_opening_closing_price_message(OpeningClosingPriceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->market_center = arbitrary();
  record->open_close_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
}

/* Opening Closing Price Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_opening_closing_price_message(const OpeningClosingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->market_center;
  wire[at++] = record->open_close_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }

  return at;
}

/* Opening Closing Price Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_opening_closing_price_message(OpeningClosingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->market_center = wire[at++];
  record->open_close_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }

  return at;
}

/* what was read of Opening Closing Price Message is what was written, byte for byte */
static void equal_opening_closing_price_message(const OpeningClosingPriceMessage *read, const OpeningClosingPriceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->market_center == written->market_center);
  assert(read->open_close_indicator == written->open_close_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
}

/* Opening Closing Price Message: written and read back, then read and written back */
static void check_opening_closing_price_message(void) {
  OpeningClosingPriceMessage sent;
  OpeningClosingPriceMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_opening_closing_price_message(&sent);
  assert(encode_opening_closing_price_message(&sent, wire, 0) == 26);
  assert(decode_opening_closing_price_message(&got, wire, 0) == 26);
  equal_opening_closing_price_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_closing_price_message(&got, wire, 0) == 26);
  assert(encode_opening_closing_price_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fractional End Of Day Summary Message: 57 bytes ------------------------- */

/* The Fractional End of Day Summary message is used to give a consolidated, high-level overview of a security for the day. */
typedef struct {
  uint8_t timestamp[8];                   /* bytes 0 to 7 */
  uint8_t symbol[8];                      /* bytes 8 to 15 */
  uint8_t data_source;                    /* byte 16 */
  uint8_t opening_price[8];               /* bytes 17 to 24 */
  uint8_t closing_price[8];               /* bytes 25 to 32 */
  uint8_t high_price[8];                  /* bytes 33 to 40 */
  uint8_t low_price[8];                   /* bytes 41 to 48 */
  uint8_t national_cumulative_volume[8];  /* bytes 49 to 56 */
} FractionalEndOfDaySummaryMessage;

/* any Fractional End Of Day Summary Message at all: every byte one the checker chooses */
static void any_fractional_end_of_day_summary_message(FractionalEndOfDaySummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->data_source = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->national_cumulative_volume[i] = arbitrary(); }
}

/* Fractional End Of Day Summary Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_fractional_end_of_day_summary_message(const FractionalEndOfDaySummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->data_source;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->national_cumulative_volume[i]; }

  return at;
}

/* Fractional End Of Day Summary Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_fractional_end_of_day_summary_message(FractionalEndOfDaySummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->data_source = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->national_cumulative_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Fractional End Of Day Summary Message is what was written, byte for byte */
static void equal_fractional_end_of_day_summary_message(const FractionalEndOfDaySummaryMessage *read, const FractionalEndOfDaySummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->data_source == written->data_source);
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->national_cumulative_volume[i] == written->national_cumulative_volume[i]); }
}

/* Fractional End Of Day Summary Message: written and read back, then read and written back */
static void check_fractional_end_of_day_summary_message(void) {
  FractionalEndOfDaySummaryMessage sent;
  FractionalEndOfDaySummaryMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_fractional_end_of_day_summary_message(&sent);
  assert(encode_fractional_end_of_day_summary_message(&sent, wire, 0) == 57);
  assert(decode_fractional_end_of_day_summary_message(&got, wire, 0) == 57);
  equal_fractional_end_of_day_summary_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_fractional_end_of_day_summary_message(&got, wire, 0) == 57);
  assert(encode_fractional_end_of_day_summary_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_clear_quote_message();
  check_best_quote_update_message();
  check_cboe_market_status_message();
  check_short_update_adap_block();
  check_long_update_adap_block();
  check_rpi_message();
  check_trading_status_message();
  check_opening_closing_price_message();
  check_fractional_end_of_day_summary_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
