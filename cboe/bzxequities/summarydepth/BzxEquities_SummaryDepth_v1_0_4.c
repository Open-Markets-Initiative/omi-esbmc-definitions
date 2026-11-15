// cboe/bzxequities/summarydepth/BzxEquities_SummaryDepth_v1_0_4.c
/*
 * Chicago Board Options Exchange Summary Depth
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

/* The Clear Quote message instructs feed recipients to clear all quotes and ADAP information for the specified symbol */
typedef struct {
  uint8_t last_update_timestamp[8];  /* bytes 0 to 7 */
  uint8_t symbol[8];                 /* bytes 8 to 15 */
  uint8_t reserved_1;                /* byte 16 */
} ClearQuoteMessage;

/* any Clear Quote Message at all: every byte one the checker chooses */
static void any_clear_quote_message(ClearQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->last_update_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Clear Quote Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_clear_quote_message(const ClearQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_update_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Clear Quote Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_clear_quote_message(ClearQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->last_update_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Clear Quote Message is what was written, byte for byte */
static void equal_clear_quote_message(const ClearQuoteMessage *read, const ClearQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->last_update_timestamp[i] == written->last_update_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->reserved_1 == written->reserved_1);
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

/* ---- Cboe Market Status Message: 11 bytes ------------------------------------ */

/* The Cboe Market Status message is disseminated to reflect a change in the status of the market */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t reserved_1;         /* byte 8 */
  uint8_t market_status;      /* byte 9 */
  uint8_t session_indicator;  /* byte 10 */
} CboeMarketStatusMessage;

/* any Cboe Market Status Message at all: every byte one the checker chooses */
static void any_cboe_market_status_message(CboeMarketStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->market_status = arbitrary();
  record->session_indicator = arbitrary();
}

/* Cboe Market Status Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_cboe_market_status_message(const CboeMarketStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->market_status;
  wire[at++] = record->session_indicator;

  return at;
}

/* Cboe Market Status Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_cboe_market_status_message(CboeMarketStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->market_status = wire[at++];
  record->session_indicator = wire[at++];

  return at;
}

/* what was read of Cboe Market Status Message is what was written, byte for byte */
static void equal_cboe_market_status_message(const CboeMarketStatusMessage *read, const CboeMarketStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->reserved_1 == written->reserved_1);
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

/* ---- Short Update Adap Block: 9 bytes ---------------------------------------- */

/* Short Update ADAP Block */
typedef struct {
  uint8_t side;               /* byte 0 */
  uint8_t price_short[4];     /* bytes 1 to 4 */
  uint8_t quantity_short[4];  /* bytes 5 to 8 */
} ShortUpdateAdapBlock;

/* any Short Update Adap Block at all: every byte one the checker chooses */
static void any_short_update_adap_block(ShortUpdateAdapBlock *record) {
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_short[i] = arbitrary(); }
}

/* Short Update Adap Block to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_short_update_adap_block(const ShortUpdateAdapBlock *record, uint8_t *wire, size_t at) {
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_short[i]; }

  return at;
}

/* Short Update Adap Block off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_short_update_adap_block(ShortUpdateAdapBlock *record, const uint8_t *wire, size_t at) {
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_short[i] = wire[at++]; }

  return at;
}

/* what was read of Short Update Adap Block is what was written, byte for byte */
static void equal_short_update_adap_block(const ShortUpdateAdapBlock *read, const ShortUpdateAdapBlock *written) {
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
}

/* Short Update Adap Block: written and read back, then read and written back */
static void check_short_update_adap_block(void) {
  ShortUpdateAdapBlock sent;
  ShortUpdateAdapBlock got;
  uint8_t wire[9];
  uint8_t again[9];

  any_short_update_adap_block(&sent);
  assert(encode_short_update_adap_block(&sent, wire, 0) == 9);
  assert(decode_short_update_adap_block(&got, wire, 0) == 9);
  equal_short_update_adap_block(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_short_update_adap_block(&got, wire, 0) == 9);
  assert(encode_short_update_adap_block(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Update Adap Block: 17 bytes ---------------------------------------- */

/* Long Update ADAP Block */
typedef struct {
  uint8_t side;              /* byte 0 */
  uint8_t price_long[8];     /* bytes 1 to 8 */
  uint8_t quantity_long[8];  /* bytes 9 to 16 */
} LongUpdateAdapBlock;

/* any Long Update Adap Block at all: every byte one the checker chooses */
static void any_long_update_adap_block(LongUpdateAdapBlock *record) {
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_long[i] = arbitrary(); }
}

/* Long Update Adap Block to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_long_update_adap_block(const LongUpdateAdapBlock *record, uint8_t *wire, size_t at) {
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_long[i]; }

  return at;
}

/* Long Update Adap Block off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_long_update_adap_block(LongUpdateAdapBlock *record, const uint8_t *wire, size_t at) {
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Long Update Adap Block is what was written, byte for byte */
static void equal_long_update_adap_block(const LongUpdateAdapBlock *read, const LongUpdateAdapBlock *written) {
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
}

/* Long Update Adap Block: written and read back, then read and written back */
static void check_long_update_adap_block(void) {
  LongUpdateAdapBlock sent;
  LongUpdateAdapBlock got;
  uint8_t wire[17];
  uint8_t again[17];

  any_long_update_adap_block(&sent);
  assert(encode_long_update_adap_block(&sent, wire, 0) == 17);
  assert(decode_long_update_adap_block(&got, wire, 0) == 17);
  equal_long_update_adap_block(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_long_update_adap_block(&got, wire, 0) == 17);
  assert(encode_long_update_adap_block(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rpi Message: 18 bytes --------------------------------------------------- */

/* RPI Message */
typedef struct {
  uint8_t timestamp[8];              /* bytes 0 to 7 */
  uint8_t symbol[8];                 /* bytes 8 to 15 */
  uint8_t reserved_1;                /* byte 16 */
  uint8_t retail_price_improvement;  /* byte 17 */
} RpiMessage;

/* any Rpi Message at all: every byte one the checker chooses */
static void any_rpi_message(RpiMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->retail_price_improvement = arbitrary();
}

/* Rpi Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_rpi_message(const RpiMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->retail_price_improvement;

  return at;
}

/* Rpi Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_rpi_message(RpiMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->retail_price_improvement = wire[at++];

  return at;
}

/* what was read of Rpi Message is what was written, byte for byte */
static void equal_rpi_message(const RpiMessage *read, const RpiMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->reserved_1 == written->reserved_1);
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

/* ---- Trade Break Message: 42 bytes ------------------------------------------- */

/* Trade Break Message */
typedef struct {
  uint8_t transaction_time[8];                 /* bytes 0 to 7 */
  uint8_t symbol[8];                           /* bytes 8 to 15 */
  uint8_t reserved_1;                          /* byte 16 */
  uint8_t execution_id[8];                     /* bytes 17 to 24 */
  uint8_t cboe_cumulative_executed_volume[8];  /* bytes 25 to 32 */
  uint8_t reserved_8[8];                       /* bytes 33 to 40 */
  uint8_t trade_break_flags;                   /* byte 41 */
} TradeBreakMessage;

/* any Trade Break Message at all: every byte one the checker chooses */
static void any_trade_break_message(TradeBreakMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cboe_cumulative_executed_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  record->trade_break_flags = arbitrary();
}

/* Trade Break Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_trade_break_message(const TradeBreakMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cboe_cumulative_executed_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  wire[at++] = record->trade_break_flags;

  return at;
}

/* Trade Break Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_trade_break_message(TradeBreakMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cboe_cumulative_executed_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  record->trade_break_flags = wire[at++];

  return at;
}

/* what was read of Trade Break Message is what was written, byte for byte */
static void equal_trade_break_message(const TradeBreakMessage *read, const TradeBreakMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cboe_cumulative_executed_volume[i] == written->cboe_cumulative_executed_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  assert(read->trade_break_flags == written->trade_break_flags);
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

/* Trading Status Message */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t symbol[8];       /* bytes 8 to 15 */
  uint8_t reserved_1;      /* byte 16 */
  uint8_t halt_status;     /* byte 17 */
  uint8_t reg_sho_action;  /* byte 18 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->halt_status = arbitrary();
  record->reg_sho_action = arbitrary();
}

/* Trading Status Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->halt_status;
  wire[at++] = record->reg_sho_action;

  return at;
}

/* Trading Status Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->halt_status = wire[at++];
  record->reg_sho_action = wire[at++];

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->reserved_1 == written->reserved_1);
  assert(read->halt_status == written->halt_status);
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_clear_quote_message();
  check_cboe_market_status_message();
  check_short_update_adap_block();
  check_long_update_adap_block();
  check_rpi_message();
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
