// cboe/titaniumconsolidated/oneoptions/Cboe_TitaniumConsolidated_OneOptions_Pitch_v1_0_10.c
/*
 * Chicago Board Options Exchange One Options
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

/* ---- Short Symbol Summary Message: 41 bytes ---------------------------------- */

/* The Short Symbol Summary message delivers the Cboe consolidated best bid/offer and total executed volume across all applicable Cboe One Options books. */
typedef struct {
  uint8_t last_update_timestamp[8];                  /* bytes 0 to 7 */
  uint8_t symbol[8];                                 /* bytes 8 to 15 */
  uint8_t cboe_cumulative_executed_volume_short[4];  /* bytes 16 to 19 */
  uint8_t consolidated_best_bid_price_short[4];      /* bytes 20 to 23 */
  uint8_t consolidated_best_bid_quantity_short[4];   /* bytes 24 to 27 */
  uint8_t consolidated_best_ask_price_short[4];      /* bytes 28 to 31 */
  uint8_t consolidated_best_ask_quantity_short[4];   /* bytes 32 to 35 */
  uint8_t reserved_5[5];                             /* bytes 36 to 40 */
} ShortSymbolSummaryMessage;

/* any Short Symbol Summary Message at all: every byte one the checker chooses */
static void any_short_symbol_summary_message(ShortSymbolSummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->last_update_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cboe_cumulative_executed_volume_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->consolidated_best_bid_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->consolidated_best_bid_quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->consolidated_best_ask_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->consolidated_best_ask_quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = arbitrary(); }
}

/* Short Symbol Summary Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_short_symbol_summary_message(const ShortSymbolSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_update_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cboe_cumulative_executed_volume_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->consolidated_best_bid_price_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->consolidated_best_bid_quantity_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->consolidated_best_ask_price_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->consolidated_best_ask_quantity_short[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->reserved_5[i]; }

  return at;
}

/* Short Symbol Summary Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_short_symbol_summary_message(ShortSymbolSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->last_update_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cboe_cumulative_executed_volume_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->consolidated_best_bid_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->consolidated_best_bid_quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->consolidated_best_ask_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->consolidated_best_ask_quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = wire[at++]; }

  return at;
}

/* what was read of Short Symbol Summary Message is what was written, byte for byte */
static void equal_short_symbol_summary_message(const ShortSymbolSummaryMessage *read, const ShortSymbolSummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->last_update_timestamp[i] == written->last_update_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cboe_cumulative_executed_volume_short[i] == written->cboe_cumulative_executed_volume_short[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->consolidated_best_bid_price_short[i] == written->consolidated_best_bid_price_short[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->consolidated_best_bid_quantity_short[i] == written->consolidated_best_bid_quantity_short[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->consolidated_best_ask_price_short[i] == written->consolidated_best_ask_price_short[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->consolidated_best_ask_quantity_short[i] == written->consolidated_best_ask_quantity_short[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->reserved_5[i] == written->reserved_5[i]); }
}

/* Short Symbol Summary Message: written and read back, then read and written back */
static void check_short_symbol_summary_message(void) {
  ShortSymbolSummaryMessage sent;
  ShortSymbolSummaryMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_short_symbol_summary_message(&sent);
  assert(encode_short_symbol_summary_message(&sent, wire, 0) == 41);
  assert(decode_short_symbol_summary_message(&got, wire, 0) == 41);
  equal_short_symbol_summary_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_short_symbol_summary_message(&got, wire, 0) == 41);
  assert(encode_short_symbol_summary_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Symbol Summary Message: 65 bytes ----------------------------------- */

/* The Long Symbol Summary message delivers the Cboe consolidated best bid/offer and total executed volume across all applicable Cboe One Options books. */
typedef struct {
  uint8_t last_update_timestamp[8];                 /* bytes 0 to 7 */
  uint8_t symbol[8];                                /* bytes 8 to 15 */
  uint8_t cboe_cumulative_executed_volume_long[8];  /* bytes 16 to 23 */
  uint8_t consolidated_best_bid_price_long[8];      /* bytes 24 to 31 */
  uint8_t consolidated_best_bid_quantity_long[8];   /* bytes 32 to 39 */
  uint8_t consolidated_best_ask_price_long[8];      /* bytes 40 to 47 */
  uint8_t consolidated_best_ask_quantity_long[8];   /* bytes 48 to 55 */
  uint8_t reserved_9[9];                            /* bytes 56 to 64 */
} LongSymbolSummaryMessage;

/* any Long Symbol Summary Message at all: every byte one the checker chooses */
static void any_long_symbol_summary_message(LongSymbolSummaryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->last_update_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cboe_cumulative_executed_volume_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_best_bid_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_best_bid_quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_best_ask_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_best_ask_quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = arbitrary(); }
}

/* Long Symbol Summary Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_long_symbol_summary_message(const LongSymbolSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_update_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cboe_cumulative_executed_volume_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_best_bid_price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_best_bid_quantity_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_best_ask_price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_best_ask_quantity_long[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->reserved_9[i]; }

  return at;
}

/* Long Symbol Summary Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_long_symbol_summary_message(LongSymbolSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->last_update_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cboe_cumulative_executed_volume_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_best_bid_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_best_bid_quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_best_ask_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_best_ask_quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = wire[at++]; }

  return at;
}

/* what was read of Long Symbol Summary Message is what was written, byte for byte */
static void equal_long_symbol_summary_message(const LongSymbolSummaryMessage *read, const LongSymbolSummaryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->last_update_timestamp[i] == written->last_update_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cboe_cumulative_executed_volume_long[i] == written->cboe_cumulative_executed_volume_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_best_bid_price_long[i] == written->consolidated_best_bid_price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_best_bid_quantity_long[i] == written->consolidated_best_bid_quantity_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_best_ask_price_long[i] == written->consolidated_best_ask_price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_best_ask_quantity_long[i] == written->consolidated_best_ask_quantity_long[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->reserved_9[i] == written->reserved_9[i]); }
}

/* Long Symbol Summary Message: written and read back, then read and written back */
static void check_long_symbol_summary_message(void) {
  LongSymbolSummaryMessage sent;
  LongSymbolSummaryMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_long_symbol_summary_message(&sent);
  assert(encode_long_symbol_summary_message(&sent, wire, 0) == 65);
  assert(decode_long_symbol_summary_message(&got, wire, 0) == 65);
  equal_long_symbol_summary_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_long_symbol_summary_message(&got, wire, 0) == 65);
  assert(encode_long_symbol_summary_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Best Quote Update Message: 33 bytes ------------------------------------- */

/* The Best Quote Update message is used to update one side of the Cboe consolidated quote information for a symbol. Since the message only updates one side of the quote, the previous value for the other side of the quote remains in effect. This message does not affect the executed volume of the symbol. */
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

/* The Cboe Market Status message is disseminated to reflect a change in the status of a market. All markets should be assumed to be Normal unless otherwise indicated by a Cboe Market Status message. */
typedef struct {
  uint8_t timestamp[8];   /* bytes 0 to 7 */
  uint8_t market_center;  /* byte 8 */
  uint8_t market_status;  /* byte 9 */
  uint8_t reserved_1;     /* byte 10 */
} CboeMarketStatusMessage;

/* any Cboe Market Status Message at all: every byte one the checker chooses */
static void any_cboe_market_status_message(CboeMarketStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->market_center = arbitrary();
  record->market_status = arbitrary();
  record->reserved_1 = arbitrary();
}

/* Cboe Market Status Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_cboe_market_status_message(const CboeMarketStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->market_center;
  wire[at++] = record->market_status;
  wire[at++] = record->reserved_1;

  return at;
}

/* Cboe Market Status Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_cboe_market_status_message(CboeMarketStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->market_center = wire[at++];
  record->market_status = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Cboe Market Status Message is what was written, byte for byte */
static void equal_cboe_market_status_message(const CboeMarketStatusMessage *read, const CboeMarketStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->market_center == written->market_center);
  assert(read->market_status == written->market_status);
  assert(read->reserved_1 == written->reserved_1);
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

/* ---- Trade Message: 58 bytes ------------------------------------------------- */

/* Trade messages are sent when an order is executed in whole or in part on a Cboe exchange. */
typedef struct {
  uint8_t transaction_time[8];                      /* bytes 0 to 7 */
  uint8_t symbol[8];                                /* bytes 8 to 15 */
  uint8_t market_center;                            /* byte 16 */
  uint8_t market_center_execution_id[8];            /* bytes 17 to 24 */
  uint8_t last_price[8];                            /* bytes 25 to 32 */
  uint8_t last_quantity[8];                         /* bytes 33 to 40 */
  uint8_t cboe_cumulative_executed_volume_long[8];  /* bytes 41 to 48 */
  uint8_t trade_condition;                          /* byte 49 */
  uint8_t reserved_8[8];                            /* bytes 50 to 57 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->market_center = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->market_center_execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cboe_cumulative_executed_volume_long[i] = arbitrary(); }
  record->trade_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Trade Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->market_center;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_center_execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cboe_cumulative_executed_volume_long[i]; }
  wire[at++] = record->trade_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Trade Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->market_center = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->market_center_execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cboe_cumulative_executed_volume_long[i] = wire[at++]; }
  record->trade_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->market_center == written->market_center);
  for (size_t i = 0; i < 8; i++) { assert(read->market_center_execution_id[i] == written->market_center_execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_quantity[i] == written->last_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cboe_cumulative_executed_volume_long[i] == written->cboe_cumulative_executed_volume_long[i]); }
  assert(read->trade_condition == written->trade_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 58);
  assert(decode_trade_message(&got, wire, 0) == 58);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 58);
  assert(encode_trade_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Break Message: 42 bytes ------------------------------------------- */

/* The Trade Break message is sent whenever an execution on a Cboe exchange is broken. Trade breaks are rare and only affect applications that rely upon Cboe execution based data. */
typedef struct {
  uint8_t transaction_time[8];                      /* bytes 0 to 7 */
  uint8_t symbol[8];                                /* bytes 8 to 15 */
  uint8_t market_center;                            /* byte 16 */
  uint8_t market_center_execution_id[8];            /* bytes 17 to 24 */
  uint8_t cboe_cumulative_executed_volume_long[8];  /* bytes 25 to 32 */
  uint8_t reserved_9[9];                            /* bytes 33 to 41 */
} TradeBreakMessage;

/* any Trade Break Message at all: every byte one the checker chooses */
static void any_trade_break_message(TradeBreakMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->market_center = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->market_center_execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cboe_cumulative_executed_volume_long[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = arbitrary(); }
}

/* Trade Break Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_trade_break_message(const TradeBreakMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->market_center;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_center_execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cboe_cumulative_executed_volume_long[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->reserved_9[i]; }

  return at;
}

/* Trade Break Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_trade_break_message(TradeBreakMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->market_center = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->market_center_execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cboe_cumulative_executed_volume_long[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Break Message is what was written, byte for byte */
static void equal_trade_break_message(const TradeBreakMessage *read, const TradeBreakMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->market_center == written->market_center);
  for (size_t i = 0; i < 8; i++) { assert(read->market_center_execution_id[i] == written->market_center_execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cboe_cumulative_executed_volume_long[i] == written->cboe_cumulative_executed_volume_long[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->reserved_9[i] == written->reserved_9[i]); }
}

/* Trade Break Message: written and read back, then read and written back */
static void check_trade_break_message(void) {
  TradeBreakMessage sent;
  TradeBreakMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_trade_break_message(&sent);
  assert(encode_trade_break_message(&sent, wire, 0) == 42);
  assert(decode_trade_break_message(&got, wire, 0) == 42);
  equal_trade_break_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_break_message(&got, wire, 0) == 42);
  assert(encode_trade_break_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 19 bytes ---------------------------------------- */

/* The Trading Status message is used to indicate the current trading status of an options contract on a Cboe exchange. */
typedef struct {
  uint8_t timestamp[8];   /* bytes 0 to 7 */
  uint8_t symbol[8];      /* bytes 8 to 15 */
  uint8_t market_center;  /* byte 16 */
  uint8_t halt_status;    /* byte 17 */
  uint8_t reserved_1;     /* byte 18 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->market_center = arbitrary();
  record->halt_status = arbitrary();
  record->reserved_1 = arbitrary();
}

/* Trading Status Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->market_center;
  wire[at++] = record->halt_status;
  wire[at++] = record->reserved_1;

  return at;
}

/* Trading Status Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->market_center = wire[at++];
  record->halt_status = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->market_center == written->market_center);
  assert(read->halt_status == written->halt_status);
  assert(read->reserved_1 == written->reserved_1);
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_short_symbol_summary_message();
  check_long_symbol_summary_message();
  check_best_quote_update_message();
  check_cboe_market_status_message();
  check_trade_message();
  check_trade_break_message();
  check_trading_status_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
