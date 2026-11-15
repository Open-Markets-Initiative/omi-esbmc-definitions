// athex/athexsecurities/realtime/AthexSecurities_RealTime_v5_2.c
/*
 * Athens Exchange Group Athens Exchange Securities Market Real Time Channel
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
 *   - a field filling what is left of what holds it
 *   - a run counted by a field
 *   - a length prefix framing what follows
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

/* ---- Message Header: 35 bytes ------------------------------------------------ */

/* Thirty five character header succeeding the Soh character of every message packet */
typedef struct {
  uint8_t vendor_identifier[2];        /* bytes 0 to 1 */
  uint8_t message_category;            /* byte 2 */
  uint8_t message_subcategory;         /* byte 3 */
  uint8_t venue_i_d[4];                /* bytes 4 to 7 */
  uint8_t message_sequence_number[7];  /* bytes 8 to 14 */
  uint8_t publication_timestamp[20];   /* bytes 15 to 34 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->vendor_identifier[i] = arbitrary(); }
  record->message_category = arbitrary();
  record->message_subcategory = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->venue_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->publication_timestamp[i] = arbitrary(); }
}

/* Message Header to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->vendor_identifier[i]; }
  wire[at++] = record->message_category;
  wire[at++] = record->message_subcategory;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_i_d[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->publication_timestamp[i]; }

  return at;
}

/* Message Header off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->vendor_identifier[i] = wire[at++]; }
  record->message_category = wire[at++];
  record->message_subcategory = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->venue_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->publication_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->vendor_identifier[i] == written->vendor_identifier[i]); }
  assert(read->message_category == written->message_category);
  assert(read->message_subcategory == written->message_subcategory);
  for (size_t i = 0; i < 4; i++) { assert(read->venue_i_d[i] == written->venue_i_d[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->publication_timestamp[i] == written->publication_timestamp[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[35];
  uint8_t again[35];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 35);
  assert(decode_message_header(&got, wire, 0) == 35);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 35);
  assert(encode_message_header(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 147 bytes ------------------------------------------------ */

/* Transmitted when an instrument trade occurs in the trading platform or the clearing system */
typedef struct {
  uint8_t symbol[15];                /* bytes 0 to 14 */
  uint8_t board_id;                  /* byte 15 */
  uint8_t trade_number[6];           /* bytes 16 to 21 */
  uint8_t buy_order_number[8];       /* bytes 22 to 29 */
  uint8_t buy_order_date[8];         /* bytes 30 to 37 */
  uint8_t sell_order_number[8];      /* bytes 38 to 45 */
  uint8_t sell_order_date[8];        /* bytes 46 to 53 */
  uint8_t price[9];                  /* bytes 54 to 62 */
  uint8_t volume[17];                /* bytes 63 to 79 */
  uint8_t total_volume[17];          /* bytes 80 to 96 */
  uint8_t trade_type;                /* byte 97 */
  uint8_t trade_source;              /* byte 98 */
  uint8_t buy_order_type;            /* byte 99 */
  uint8_t sell_order_type;           /* byte 100 */
  uint8_t buy_waiver_indicator[4];   /* bytes 101 to 104 */
  uint8_t sell_waiver_indicator[4];  /* bytes 105 to 108 */
  uint8_t notional_amount[14];       /* bytes 109 to 122 */
  uint8_t buy_algo_flag;             /* byte 123 */
  uint8_t sell_algo_flag;            /* byte 124 */
  uint8_t sdiv_flag;                 /* byte 125 */
  uint8_t dupl_flag;                 /* byte 126 */
  uint8_t time_stamp[20];            /* bytes 127 to 146 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = arbitrary(); }
  record->board_id = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_order_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_order_date[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 17; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 17; i++) { record->total_volume[i] = arbitrary(); }
  record->trade_type = arbitrary();
  record->trade_source = arbitrary();
  record->buy_order_type = arbitrary();
  record->sell_order_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->buy_waiver_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_waiver_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->notional_amount[i] = arbitrary(); }
  record->buy_algo_flag = arbitrary();
  record->sell_algo_flag = arbitrary();
  record->sdiv_flag = arbitrary();
  record->dupl_flag = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->time_stamp[i] = arbitrary(); }
}

/* Trade Message to the wire: 147 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->board_id;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_order_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_order_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_order_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_order_date[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->total_volume[i]; }
  wire[at++] = record->trade_type;
  wire[at++] = record->trade_source;
  wire[at++] = record->buy_order_type;
  wire[at++] = record->sell_order_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_waiver_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_waiver_indicator[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->notional_amount[i]; }
  wire[at++] = record->buy_algo_flag;
  wire[at++] = record->sell_algo_flag;
  wire[at++] = record->sdiv_flag;
  wire[at++] = record->dupl_flag;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->time_stamp[i]; }

  return at;
}

/* Trade Message off the wire: 147 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = wire[at++]; }
  record->board_id = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_order_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_order_date[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 17; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 17; i++) { record->total_volume[i] = wire[at++]; }
  record->trade_type = wire[at++];
  record->trade_source = wire[at++];
  record->buy_order_type = wire[at++];
  record->sell_order_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->buy_waiver_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_waiver_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->notional_amount[i] = wire[at++]; }
  record->buy_algo_flag = wire[at++];
  record->sell_algo_flag = wire[at++];
  record->sdiv_flag = wire[at++];
  record->dupl_flag = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->board_id == written->board_id);
  for (size_t i = 0; i < 6; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_order_number[i] == written->buy_order_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_order_date[i] == written->buy_order_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_order_number[i] == written->sell_order_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_order_date[i] == written->sell_order_date[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 17; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 17; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  assert(read->trade_type == written->trade_type);
  assert(read->trade_source == written->trade_source);
  assert(read->buy_order_type == written->buy_order_type);
  assert(read->sell_order_type == written->sell_order_type);
  for (size_t i = 0; i < 4; i++) { assert(read->buy_waiver_indicator[i] == written->buy_waiver_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_waiver_indicator[i] == written->sell_waiver_indicator[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->notional_amount[i] == written->notional_amount[i]); }
  assert(read->buy_algo_flag == written->buy_algo_flag);
  assert(read->sell_algo_flag == written->sell_algo_flag);
  assert(read->sdiv_flag == written->sdiv_flag);
  assert(read->dupl_flag == written->dupl_flag);
  for (size_t i = 0; i < 20; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[147];
  uint8_t again[147];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 147);
  assert(decode_trade_message(&got, wire, 0) == 147);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 147; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 147);
  assert(encode_trade_message(&got, again, 0) == 147);
  for (size_t i = 0; i < 147; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Message: 24 bytes ------------------------------------------------- */

/* Transmitted every time the trading platform calculates the price of a given index */
typedef struct {
  uint8_t symbol[15];      /* bytes 0 to 14 */
  uint8_t index_price[9];  /* bytes 15 to 23 */
} IndexMessage;

/* any Index Message at all: every byte one the checker chooses */
static void any_index_message(IndexMessage *record) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->index_price[i] = arbitrary(); }
}

/* Index Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_index_message(const IndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index_price[i]; }

  return at;
}

/* Index Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_index_message(IndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->index_price[i] = wire[at++]; }

  return at;
}

/* what was read of Index Message is what was written, byte for byte */
static void equal_index_message(const IndexMessage *read, const IndexMessage *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->index_price[i] == written->index_price[i]); }
}

/* Index Message: written and read back, then read and written back */
static void check_index_message(void) {
  IndexMessage sent;
  IndexMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_index_message(&sent);
  assert(encode_index_message(&sent, wire, 0) == 24);
  assert(decode_index_message(&got, wire, 0) == 24);
  equal_index_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_index_message(&got, wire, 0) == 24);
  assert(encode_index_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Summary Message: 103 bytes ----------------------------------- */

/* Transmitted for each instrument right after the corresponding market status changes to End of Day */
typedef struct {
  uint8_t symbol[15];             /* bytes 0 to 14 */
  uint8_t opening_price[9];       /* bytes 15 to 23 */
  uint8_t high[9];                /* bytes 24 to 32 */
  uint8_t low[9];                 /* bytes 33 to 41 */
  uint8_t last[9];                /* bytes 42 to 50 */
  uint8_t closing_price[9];       /* bytes 51 to 59 */
  uint8_t start_of_day_price[9];  /* bytes 60 to 68 */
  uint8_t total_volume[17];       /* bytes 69 to 85 */
  uint8_t total_value[17];        /* bytes 86 to 102 */
} InstrumentSummaryMessage;

/* any Instrument Summary Message at all: every byte one the checker chooses */
static void any_instrument_summary_message(InstrumentSummaryMessage *record) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->last[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->start_of_day_price[i] = arbitrary(); }
  for (size_t i = 0; i < 17; i++) { record->total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 17; i++) { record->total_value[i] = arbitrary(); }
}

/* Instrument Summary Message to the wire: 103 bytes from at, returning where the next byte goes */
static size_t encode_instrument_summary_message(const InstrumentSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->last[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->closing_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->start_of_day_price[i]; }
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->total_volume[i]; }
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->total_value[i]; }

  return at;
}

/* Instrument Summary Message off the wire: 103 bytes from at, returning where the next byte lies */
static size_t decode_instrument_summary_message(InstrumentSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->last[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->start_of_day_price[i] = wire[at++]; }
  for (size_t i = 0; i < 17; i++) { record->total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 17; i++) { record->total_value[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Summary Message is what was written, byte for byte */
static void equal_instrument_summary_message(const InstrumentSummaryMessage *read, const InstrumentSummaryMessage *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->last[i] == written->last[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->start_of_day_price[i] == written->start_of_day_price[i]); }
  for (size_t i = 0; i < 17; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  for (size_t i = 0; i < 17; i++) { assert(read->total_value[i] == written->total_value[i]); }
}

/* Instrument Summary Message: written and read back, then read and written back */
static void check_instrument_summary_message(void) {
  InstrumentSummaryMessage sent;
  InstrumentSummaryMessage got;
  uint8_t wire[103];
  uint8_t again[103];

  any_instrument_summary_message(&sent);
  assert(encode_instrument_summary_message(&sent, wire, 0) == 103);
  assert(decode_instrument_summary_message(&got, wire, 0) == 103);
  equal_instrument_summary_message(&got, &sent);

  for (size_t i = 0; i < 103; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_summary_message(&got, wire, 0) == 103);
  assert(encode_instrument_summary_message(&got, again, 0) == 103);
  for (size_t i = 0; i < 103; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancelled Trade Message: 147 bytes -------------------------------------- */

/* Transmitted when an instrument trade cancellation occurs in the trading platform or clearing system */
typedef struct {
  uint8_t symbol[15];                /* bytes 0 to 14 */
  uint8_t board_id;                  /* byte 15 */
  uint8_t trade_number[6];           /* bytes 16 to 21 */
  uint8_t buy_order_number[8];       /* bytes 22 to 29 */
  uint8_t buy_order_date[8];         /* bytes 30 to 37 */
  uint8_t sell_order_number[8];      /* bytes 38 to 45 */
  uint8_t sell_order_date[8];        /* bytes 46 to 53 */
  uint8_t cancelled_trade_price[9];  /* bytes 54 to 62 */
  uint8_t cancelled_volume[17];      /* bytes 63 to 79 */
  uint8_t total_volume[17];          /* bytes 80 to 96 */
  uint8_t trade_type;                /* byte 97 */
  uint8_t trade_source;              /* byte 98 */
  uint8_t buy_order_type;            /* byte 99 */
  uint8_t sell_order_type;           /* byte 100 */
  uint8_t buy_waiver_indicator[4];   /* bytes 101 to 104 */
  uint8_t sell_waiver_indicator[4];  /* bytes 105 to 108 */
  uint8_t notional_amount[14];       /* bytes 109 to 122 */
  uint8_t buy_algo_flag;             /* byte 123 */
  uint8_t sell_algo_flag;            /* byte 124 */
  uint8_t sdiv_flag;                 /* byte 125 */
  uint8_t dupl_flag;                 /* byte 126 */
  uint8_t time_stamp[20];            /* bytes 127 to 146 */
} CancelledTradeMessage;

/* any Cancelled Trade Message at all: every byte one the checker chooses */
static void any_cancelled_trade_message(CancelledTradeMessage *record) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = arbitrary(); }
  record->board_id = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_order_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_order_date[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->cancelled_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 17; i++) { record->cancelled_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 17; i++) { record->total_volume[i] = arbitrary(); }
  record->trade_type = arbitrary();
  record->trade_source = arbitrary();
  record->buy_order_type = arbitrary();
  record->sell_order_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->buy_waiver_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_waiver_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->notional_amount[i] = arbitrary(); }
  record->buy_algo_flag = arbitrary();
  record->sell_algo_flag = arbitrary();
  record->sdiv_flag = arbitrary();
  record->dupl_flag = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->time_stamp[i] = arbitrary(); }
}

/* Cancelled Trade Message to the wire: 147 bytes from at, returning where the next byte goes */
static size_t encode_cancelled_trade_message(const CancelledTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->board_id;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_order_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_order_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_order_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_order_date[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->cancelled_trade_price[i]; }
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->cancelled_volume[i]; }
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->total_volume[i]; }
  wire[at++] = record->trade_type;
  wire[at++] = record->trade_source;
  wire[at++] = record->buy_order_type;
  wire[at++] = record->sell_order_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_waiver_indicator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_waiver_indicator[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->notional_amount[i]; }
  wire[at++] = record->buy_algo_flag;
  wire[at++] = record->sell_algo_flag;
  wire[at++] = record->sdiv_flag;
  wire[at++] = record->dupl_flag;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->time_stamp[i]; }

  return at;
}

/* Cancelled Trade Message off the wire: 147 bytes from at, returning where the next byte lies */
static size_t decode_cancelled_trade_message(CancelledTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = wire[at++]; }
  record->board_id = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_order_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_order_date[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->cancelled_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 17; i++) { record->cancelled_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 17; i++) { record->total_volume[i] = wire[at++]; }
  record->trade_type = wire[at++];
  record->trade_source = wire[at++];
  record->buy_order_type = wire[at++];
  record->sell_order_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->buy_waiver_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_waiver_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->notional_amount[i] = wire[at++]; }
  record->buy_algo_flag = wire[at++];
  record->sell_algo_flag = wire[at++];
  record->sdiv_flag = wire[at++];
  record->dupl_flag = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Cancelled Trade Message is what was written, byte for byte */
static void equal_cancelled_trade_message(const CancelledTradeMessage *read, const CancelledTradeMessage *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->board_id == written->board_id);
  for (size_t i = 0; i < 6; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_order_number[i] == written->buy_order_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_order_date[i] == written->buy_order_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_order_number[i] == written->sell_order_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_order_date[i] == written->sell_order_date[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->cancelled_trade_price[i] == written->cancelled_trade_price[i]); }
  for (size_t i = 0; i < 17; i++) { assert(read->cancelled_volume[i] == written->cancelled_volume[i]); }
  for (size_t i = 0; i < 17; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  assert(read->trade_type == written->trade_type);
  assert(read->trade_source == written->trade_source);
  assert(read->buy_order_type == written->buy_order_type);
  assert(read->sell_order_type == written->sell_order_type);
  for (size_t i = 0; i < 4; i++) { assert(read->buy_waiver_indicator[i] == written->buy_waiver_indicator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_waiver_indicator[i] == written->sell_waiver_indicator[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->notional_amount[i] == written->notional_amount[i]); }
  assert(read->buy_algo_flag == written->buy_algo_flag);
  assert(read->sell_algo_flag == written->sell_algo_flag);
  assert(read->sdiv_flag == written->sdiv_flag);
  assert(read->dupl_flag == written->dupl_flag);
  for (size_t i = 0; i < 20; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
}

/* Cancelled Trade Message: written and read back, then read and written back */
static void check_cancelled_trade_message(void) {
  CancelledTradeMessage sent;
  CancelledTradeMessage got;
  uint8_t wire[147];
  uint8_t again[147];

  any_cancelled_trade_message(&sent);
  assert(encode_cancelled_trade_message(&sent, wire, 0) == 147);
  assert(decode_cancelled_trade_message(&got, wire, 0) == 147);
  equal_cancelled_trade_message(&got, &sent);

  for (size_t i = 0; i < 147; i++) { wire[i] = arbitrary(); }
  assert(decode_cancelled_trade_message(&got, wire, 0) == 147);
  assert(encode_cancelled_trade_message(&got, again, 0) == 147);
  for (size_t i = 0; i < 147; i++) { assert(again[i] == wire[i]); }
}

/* ---- Closing Price Message: 32 bytes ----------------------------------------- */

/* Transmitted for every instrument whose closing price has been calculated by the trading platform, and again whenever the trading platform recalculates one */
typedef struct {
  uint8_t symbol[15];        /* bytes 0 to 14 */
  uint8_t closing[9];        /* bytes 15 to 23 */
  uint8_t open_interest[8];  /* bytes 24 to 31 */
} ClosingPriceMessage;

/* any Closing Price Message at all: every byte one the checker chooses */
static void any_closing_price_message(ClosingPriceMessage *record) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->closing[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = arbitrary(); }
}

/* Closing Price Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_closing_price_message(const ClosingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->closing[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_interest[i]; }

  return at;
}

/* Closing Price Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_closing_price_message(ClosingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->closing[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = wire[at++]; }

  return at;
}

/* what was read of Closing Price Message is what was written, byte for byte */
static void equal_closing_price_message(const ClosingPriceMessage *read, const ClosingPriceMessage *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->closing[i] == written->closing[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
}

/* Closing Price Message: written and read back, then read and written back */
static void check_closing_price_message(void) {
  ClosingPriceMessage sent;
  ClosingPriceMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_closing_price_message(&sent);
  assert(encode_closing_price_message(&sent, wire, 0) == 32);
  assert(decode_closing_price_message(&got, wire, 0) == 32);
  equal_closing_price_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_closing_price_message(&got, wire, 0) == 32);
  assert(encode_closing_price_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Projected Auction Auction Open Projected Close Price Message: 62 bytes ---- */

/* Transmitted whenever the trading platform calculates a Projected Auction, Auction Open or Projected Close price for the instrument */
typedef struct {
  uint8_t symbol[15];      /* bytes 0 to 14 */
  uint8_t price_flag;      /* byte 15 */
  uint8_t price[9];        /* bytes 16 to 24 */
  uint8_t volume[17];      /* bytes 25 to 41 */
  uint8_t time_stamp[20];  /* bytes 42 to 61 */
} ProjectedAuctionAuctionOpenProjectedClosePriceMessage;

/* any Projected Auction Auction Open Projected Close Price Message at all: every byte one the checker chooses */
static void any_projected_auction_auction_open_projected_close_price_message(ProjectedAuctionAuctionOpenProjectedClosePriceMessage *record) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = arbitrary(); }
  record->price_flag = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 17; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->time_stamp[i] = arbitrary(); }
}

/* Projected Auction Auction Open Projected Close Price Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_projected_auction_auction_open_projected_close_price_message(const ProjectedAuctionAuctionOpenProjectedClosePriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->price_flag;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->time_stamp[i]; }

  return at;
}

/* Projected Auction Auction Open Projected Close Price Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_projected_auction_auction_open_projected_close_price_message(ProjectedAuctionAuctionOpenProjectedClosePriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = wire[at++]; }
  record->price_flag = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 17; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Projected Auction Auction Open Projected Close Price Message is what was written, byte for byte */
static void equal_projected_auction_auction_open_projected_close_price_message(const ProjectedAuctionAuctionOpenProjectedClosePriceMessage *read, const ProjectedAuctionAuctionOpenProjectedClosePriceMessage *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->price_flag == written->price_flag);
  for (size_t i = 0; i < 9; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 17; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
}

/* Projected Auction Auction Open Projected Close Price Message: written and read back, then read and written back */
static void check_projected_auction_auction_open_projected_close_price_message(void) {
  ProjectedAuctionAuctionOpenProjectedClosePriceMessage sent;
  ProjectedAuctionAuctionOpenProjectedClosePriceMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_projected_auction_auction_open_projected_close_price_message(&sent);
  assert(encode_projected_auction_auction_open_projected_close_price_message(&sent, wire, 0) == 62);
  assert(decode_projected_auction_auction_open_projected_close_price_message(&got, wire, 0) == 62);
  equal_projected_auction_auction_open_projected_close_price_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_projected_auction_auction_open_projected_close_price_message(&got, wire, 0) == 62);
  assert(encode_projected_auction_auction_open_projected_close_price_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- High Low Limit Modification Message: 56 bytes --------------------------- */

/* Transmitted at the beginning of the trading day, and whenever the static High and Low limits for the given instrument change */
typedef struct {
  uint8_t symbol[15];             /* bytes 0 to 14 */
  uint8_t ceiling_price[9];       /* bytes 15 to 23 */
  uint8_t floor_price[9];         /* bytes 24 to 32 */
  uint8_t start_of_day_price[9];  /* bytes 33 to 41 */
  uint8_t accrued_interest[14];   /* bytes 42 to 55 */
} HighLowLimitModificationMessage;

/* any High Low Limit Modification Message at all: every byte one the checker chooses */
static void any_high_low_limit_modification_message(HighLowLimitModificationMessage *record) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->ceiling_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->floor_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->start_of_day_price[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->accrued_interest[i] = arbitrary(); }
}

/* High Low Limit Modification Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_high_low_limit_modification_message(const HighLowLimitModificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->ceiling_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->floor_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->start_of_day_price[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->accrued_interest[i]; }

  return at;
}

/* High Low Limit Modification Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_high_low_limit_modification_message(HighLowLimitModificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->ceiling_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->floor_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->start_of_day_price[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->accrued_interest[i] = wire[at++]; }

  return at;
}

/* what was read of High Low Limit Modification Message is what was written, byte for byte */
static void equal_high_low_limit_modification_message(const HighLowLimitModificationMessage *read, const HighLowLimitModificationMessage *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->ceiling_price[i] == written->ceiling_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->floor_price[i] == written->floor_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->start_of_day_price[i] == written->start_of_day_price[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->accrued_interest[i] == written->accrued_interest[i]); }
}

/* High Low Limit Modification Message: written and read back, then read and written back */
static void check_high_low_limit_modification_message(void) {
  HighLowLimitModificationMessage sent;
  HighLowLimitModificationMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_high_low_limit_modification_message(&sent);
  assert(encode_high_low_limit_modification_message(&sent, wire, 0) == 56);
  assert(decode_high_low_limit_modification_message(&got, wire, 0) == 56);
  equal_high_low_limit_modification_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_high_low_limit_modification_message(&got, wire, 0) == 56);
  assert(encode_high_low_limit_modification_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument State Message: 38 bytes -------------------------------------- */

/* Transmitted at the beginning of the trading day, and whenever the instrument changes its trading phase or its status */
typedef struct {
  uint8_t symbol[15];           /* bytes 0 to 14 */
  uint8_t phase_id;             /* byte 15 */
  uint8_t instrument_status;    /* byte 16 */
  uint8_t halt_suspend_reason;  /* byte 17 */
  uint8_t time_stamp[20];       /* bytes 18 to 37 */
} InstrumentStateMessage;

/* any Instrument State Message at all: every byte one the checker chooses */
static void any_instrument_state_message(InstrumentStateMessage *record) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = arbitrary(); }
  record->phase_id = arbitrary();
  record->instrument_status = arbitrary();
  record->halt_suspend_reason = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->time_stamp[i] = arbitrary(); }
}

/* Instrument State Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_instrument_state_message(const InstrumentStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->phase_id;
  wire[at++] = record->instrument_status;
  wire[at++] = record->halt_suspend_reason;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->time_stamp[i]; }

  return at;
}

/* Instrument State Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_instrument_state_message(InstrumentStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = wire[at++]; }
  record->phase_id = wire[at++];
  record->instrument_status = wire[at++];
  record->halt_suspend_reason = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument State Message is what was written, byte for byte */
static void equal_instrument_state_message(const InstrumentStateMessage *read, const InstrumentStateMessage *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->phase_id == written->phase_id);
  assert(read->instrument_status == written->instrument_status);
  assert(read->halt_suspend_reason == written->halt_suspend_reason);
  for (size_t i = 0; i < 20; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
}

/* Instrument State Message: written and read back, then read and written back */
static void check_instrument_state_message(void) {
  InstrumentStateMessage sent;
  InstrumentStateMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_instrument_state_message(&sent);
  assert(encode_instrument_state_message(&sent, wire, 0) == 38);
  assert(decode_instrument_state_message(&got, wire, 0) == 38);
  equal_instrument_state_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_state_message(&got, wire, 0) == 38);
  assert(encode_instrument_state_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Status Message: 2 bytes ------------------------------------------ */

/* Transmitted whenever the market changes its status */
typedef struct {
  uint8_t market_id;      /* byte 0 */
  uint8_t market_status;  /* byte 1 */
} MarketStatusMessage;

/* any Market Status Message at all: every byte one the checker chooses */
static void any_market_status_message(MarketStatusMessage *record) {
  record->market_id = arbitrary();
  record->market_status = arbitrary();
}

/* Market Status Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_market_status_message(const MarketStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_id;
  wire[at++] = record->market_status;

  return at;
}

/* Market Status Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_market_status_message(MarketStatusMessage *record, const uint8_t *wire, size_t at) {
  record->market_id = wire[at++];
  record->market_status = wire[at++];

  return at;
}

/* what was read of Market Status Message is what was written, byte for byte */
static void equal_market_status_message(const MarketStatusMessage *read, const MarketStatusMessage *written) {
  assert(read->market_id == written->market_id);
  assert(read->market_status == written->market_status);
}

/* Market Status Message: written and read back, then read and written back */
static void check_market_status_message(void) {
  MarketStatusMessage sent;
  MarketStatusMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_market_status_message(&sent);
  assert(encode_market_status_message(&sent, wire, 0) == 2);
  assert(decode_market_status_message(&got, wire, 0) == 2);
  equal_market_status_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_market_status_message(&got, wire, 0) == 2);
  assert(encode_market_status_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Message: 147 bytes ------------------------------------------------ */

/* Transmitted at the beginning of the trading session for an order whose lifetime spans multiple days, when a new order is entered in the trading platform, and when an already placed order is changed. It is not transmitted for Combinations */
typedef struct {
  uint8_t symbol[15];                 /* bytes 0 to 14 */
  uint8_t board_id;                   /* byte 15 */
  uint8_t order_number[8];            /* bytes 16 to 23 */
  uint8_t order_entry_date[8];        /* bytes 24 to 31 */
  uint8_t order_status[2];            /* bytes 32 to 33 */
  uint8_t side;                       /* byte 34 */
  uint8_t volume[17];                 /* bytes 35 to 51 */
  uint8_t matched_volume[17];         /* bytes 52 to 68 */
  uint8_t price[9];                   /* bytes 69 to 77 */
  uint8_t original_price_type;        /* byte 78 */
  uint8_t order_lifetime;             /* byte 79 */
  uint8_t special_conditions;         /* byte 80 */
  uint8_t condition_volume[17];       /* bytes 81 to 97 */
  uint8_t order_release_date[8];      /* bytes 98 to 105 */
  uint8_t order_release_time[12];     /* bytes 106 to 117 */
  uint8_t last_order_update_date[8];  /* bytes 118 to 125 */
  uint8_t order_type;                 /* byte 126 */
  uint8_t time_stamp[20];             /* bytes 127 to 146 */
} OrderMessage;

/* any Order Message at all: every byte one the checker chooses */
static void any_order_message(OrderMessage *record) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = arbitrary(); }
  record->board_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_entry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->order_status[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 17; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 17; i++) { record->matched_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->price[i] = arbitrary(); }
  record->original_price_type = arbitrary();
  record->order_lifetime = arbitrary();
  record->special_conditions = arbitrary();
  for (size_t i = 0; i < 17; i++) { record->condition_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_release_date[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->order_release_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_order_update_date[i] = arbitrary(); }
  record->order_type = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->time_stamp[i] = arbitrary(); }
}

/* Order Message to the wire: 147 bytes from at, returning where the next byte goes */
static size_t encode_order_message(const OrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->board_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_entry_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->order_status[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->matched_volume[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->original_price_type;
  wire[at++] = record->order_lifetime;
  wire[at++] = record->special_conditions;
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->condition_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_release_date[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_release_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_order_update_date[i]; }
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->time_stamp[i]; }

  return at;
}

/* Order Message off the wire: 147 bytes from at, returning where the next byte lies */
static size_t decode_order_message(OrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = wire[at++]; }
  record->board_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_entry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->order_status[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 17; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 17; i++) { record->matched_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->price[i] = wire[at++]; }
  record->original_price_type = wire[at++];
  record->order_lifetime = wire[at++];
  record->special_conditions = wire[at++];
  for (size_t i = 0; i < 17; i++) { record->condition_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_release_date[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->order_release_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_order_update_date[i] = wire[at++]; }
  record->order_type = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Order Message is what was written, byte for byte */
static void equal_order_message(const OrderMessage *read, const OrderMessage *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->board_id == written->board_id);
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_entry_date[i] == written->order_entry_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->order_status[i] == written->order_status[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 17; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 17; i++) { assert(read->matched_volume[i] == written->matched_volume[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->original_price_type == written->original_price_type);
  assert(read->order_lifetime == written->order_lifetime);
  assert(read->special_conditions == written->special_conditions);
  for (size_t i = 0; i < 17; i++) { assert(read->condition_volume[i] == written->condition_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_release_date[i] == written->order_release_date[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->order_release_time[i] == written->order_release_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_order_update_date[i] == written->last_order_update_date[i]); }
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 20; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
}

/* Order Message: written and read back, then read and written back */
static void check_order_message(void) {
  OrderMessage sent;
  OrderMessage got;
  uint8_t wire[147];
  uint8_t again[147];

  any_order_message(&sent);
  assert(encode_order_message(&sent, wire, 0) == 147);
  assert(decode_order_message(&got, wire, 0) == 147);
  equal_order_message(&got, &sent);

  for (size_t i = 0; i < 147; i++) { wire[i] = arbitrary(); }
  assert(decode_order_message(&got, wire, 0) == 147);
  assert(encode_order_message(&got, again, 0) == 147);
  for (size_t i = 0; i < 147; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancelled Order Message: 117 bytes -------------------------------------- */

/* Transmitted whenever an order is cancelled. It is not transmitted for Combinations */
typedef struct {
  uint8_t symbol[15];            /* bytes 0 to 14 */
  uint8_t board_id;              /* byte 15 */
  uint8_t order_number[8];       /* bytes 16 to 23 */
  uint8_t order_entry_date[8];   /* bytes 24 to 31 */
  uint8_t side;                  /* byte 32 */
  uint8_t volume[17];            /* bytes 33 to 49 */
  uint8_t matched_volume[17];    /* bytes 50 to 66 */
  uint8_t price[9];              /* bytes 67 to 75 */
  uint8_t original_price_type;   /* byte 76 */
  uint8_t order_lifetime;        /* byte 77 */
  uint8_t special_conditions;    /* byte 78 */
  uint8_t condition_volume[17];  /* bytes 79 to 95 */
  uint8_t order_type;            /* byte 96 */
  uint8_t time_stamp[20];        /* bytes 97 to 116 */
} CancelledOrderMessage;

/* any Cancelled Order Message at all: every byte one the checker chooses */
static void any_cancelled_order_message(CancelledOrderMessage *record) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = arbitrary(); }
  record->board_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_entry_date[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 17; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 17; i++) { record->matched_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->price[i] = arbitrary(); }
  record->original_price_type = arbitrary();
  record->order_lifetime = arbitrary();
  record->special_conditions = arbitrary();
  for (size_t i = 0; i < 17; i++) { record->condition_volume[i] = arbitrary(); }
  record->order_type = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->time_stamp[i] = arbitrary(); }
}

/* Cancelled Order Message to the wire: 117 bytes from at, returning where the next byte goes */
static size_t encode_cancelled_order_message(const CancelledOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->board_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_entry_date[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->matched_volume[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->original_price_type;
  wire[at++] = record->order_lifetime;
  wire[at++] = record->special_conditions;
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->condition_volume[i]; }
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->time_stamp[i]; }

  return at;
}

/* Cancelled Order Message off the wire: 117 bytes from at, returning where the next byte lies */
static size_t decode_cancelled_order_message(CancelledOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->symbol[i] = wire[at++]; }
  record->board_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_entry_date[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 17; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 17; i++) { record->matched_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->price[i] = wire[at++]; }
  record->original_price_type = wire[at++];
  record->order_lifetime = wire[at++];
  record->special_conditions = wire[at++];
  for (size_t i = 0; i < 17; i++) { record->condition_volume[i] = wire[at++]; }
  record->order_type = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->time_stamp[i] = wire[at++]; }

  return at;
}

/* what was read of Cancelled Order Message is what was written, byte for byte */
static void equal_cancelled_order_message(const CancelledOrderMessage *read, const CancelledOrderMessage *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->board_id == written->board_id);
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_entry_date[i] == written->order_entry_date[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 17; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 17; i++) { assert(read->matched_volume[i] == written->matched_volume[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->original_price_type == written->original_price_type);
  assert(read->order_lifetime == written->order_lifetime);
  assert(read->special_conditions == written->special_conditions);
  for (size_t i = 0; i < 17; i++) { assert(read->condition_volume[i] == written->condition_volume[i]); }
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 20; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
}

/* Cancelled Order Message: written and read back, then read and written back */
static void check_cancelled_order_message(void) {
  CancelledOrderMessage sent;
  CancelledOrderMessage got;
  uint8_t wire[117];
  uint8_t again[117];

  any_cancelled_order_message(&sent);
  assert(encode_cancelled_order_message(&sent, wire, 0) == 117);
  assert(decode_cancelled_order_message(&got, wire, 0) == 117);
  equal_cancelled_order_message(&got, &sent);

  for (size_t i = 0; i < 117; i++) { wire[i] = arbitrary(); }
  assert(decode_cancelled_order_message(&got, wire, 0) == 117);
  assert(encode_cancelled_order_message(&got, again, 0) == 117);
  for (size_t i = 0; i < 117; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_trade_message();
  check_index_message();
  check_instrument_summary_message();
  check_cancelled_trade_message();
  check_closing_price_message();
  check_projected_auction_auction_open_projected_close_price_message();
  check_high_low_limit_modification_message();
  check_instrument_state_message();
  check_market_status_message();
  check_order_message();
  check_cancelled_order_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
