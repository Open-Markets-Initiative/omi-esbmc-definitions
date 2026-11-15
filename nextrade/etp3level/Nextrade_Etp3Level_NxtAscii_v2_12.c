// nextrade/etp3level/Nextrade_Etp3Level_NxtAscii_v2_12.c
/*
 * Nextrade Nextrade Etp Market Data 3 Level
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

/* ---- Polling Data Message: 5 bytes ------------------------------------------- */

/* The data is provided periodically in order to check multicast group status. */
typedef struct {
  uint8_t current_time_1_minute_interval[4];  /* bytes 0 to 3 */
  uint8_t end_keyword;                        /* byte 4 */
} PollingDataMessage;

/* any Polling Data Message at all: every byte one the checker chooses */
static void any_polling_data_message(PollingDataMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->current_time_1_minute_interval[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Polling Data Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_polling_data_message(const PollingDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->current_time_1_minute_interval[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Polling Data Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_polling_data_message(PollingDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->current_time_1_minute_interval[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Polling Data Message is what was written, byte for byte */
static void equal_polling_data_message(const PollingDataMessage *read, const PollingDataMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->current_time_1_minute_interval[i] == written->current_time_1_minute_interval[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Polling Data Message: written and read back, then read and written back */
static void check_polling_data_message(void) {
  PollingDataMessage sent;
  PollingDataMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_polling_data_message(&sent);
  assert(encode_polling_data_message(&sent, wire, 0) == 5);
  assert(decode_polling_data_message(&got, wire, 0) == 5);
  equal_polling_data_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_polling_data_message(&got, wire, 0) == 5);
  assert(encode_polling_data_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Quote Mm Lp Quotes Included 3 Level Message: 335 bytes ------- */

/* Securities_Quote (MM/LP Quotes Included, 3 Level) Best Order Data on NXT Trading Items provided - MM/LP Quotes Included * 3 Level Best Order on Ask/Bid. */
typedef struct {
  uint8_t message_sequence_number[8];                                    /* bytes 0 to 7 */
  uint8_t board_id[2];                                                   /* bytes 8 to 9 */
  uint8_t session_id[2];                                                 /* bytes 10 to 11 */
  uint8_t isin_code[12];                                                 /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue_from_krx[6];                  /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];                         /* bytes 30 to 41 */
  uint8_t ask_level_1_price[11];                                         /* bytes 42 to 52 */
  uint8_t bid_level_1_price[11];                                         /* bytes 53 to 63 */
  uint8_t ask_level_1_volume[12];                                        /* bytes 64 to 75 */
  uint8_t bid_level_1_volume[12];                                        /* bytes 76 to 87 */
  uint8_t lp_ask_level_1_volume[12];                                     /* bytes 88 to 99 */
  uint8_t lp_bid_level_1_volume[12];                                     /* bytes 100 to 111 */
  uint8_t ask_level_2_price[11];                                         /* bytes 112 to 122 */
  uint8_t bid_level_2_price[11];                                         /* bytes 123 to 133 */
  uint8_t ask_level_2_volume[12];                                        /* bytes 134 to 145 */
  uint8_t bid_level_2_volume[12];                                        /* bytes 146 to 157 */
  uint8_t lp_ask_level_2_volume[12];                                     /* bytes 158 to 169 */
  uint8_t lp_bid_level_2_volume[12];                                     /* bytes 170 to 181 */
  uint8_t ask_level_3_price[11];                                         /* bytes 182 to 192 */
  uint8_t bid_level_3_price[11];                                         /* bytes 193 to 203 */
  uint8_t ask_level_3_volume[12];                                        /* bytes 204 to 215 */
  uint8_t bid_level_3_volume[12];                                        /* bytes 216 to 227 */
  uint8_t lp_ask_level_3_volume[12];                                     /* bytes 228 to 239 */
  uint8_t lp_bid_level_3_volume[12];                                     /* bytes 240 to 251 */
  uint8_t total_ask_volume[12];                                          /* bytes 252 to 263 */
  uint8_t total_bid_volume[12];                                          /* bytes 264 to 275 */
  uint8_t estimated_trading_price[11];                                   /* bytes 276 to 286 */
  uint8_t estimated_trading_volume[12];                                  /* bytes 287 to 298 */
  uint8_t mid_price[11];                                                 /* bytes 299 to 309 */
  uint8_t total_mid_price_ask_volume_total_ask_volume_on_mid_price[12];  /* bytes 310 to 321 */
  uint8_t total_mid_price_bid_volume_total_bid_volume_on_mid_price[12];  /* bytes 322 to 333 */
  uint8_t end_keyword;                                                   /* byte 334 */
} SecuritiesQuoteMmLpQuotesIncluded3LevelMessage;

/* any Securities Quote Mm Lp Quotes Included 3 Level Message at all: every byte one the checker chooses */
static void any_securities_quote_mm_lp_quotes_included3_level_message(SecuritiesQuoteMmLpQuotesIncluded3LevelMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Quote Mm Lp Quotes Included 3 Level Message to the wire: 335 bytes from at, returning where the next byte goes */
static size_t encode_securities_quote_mm_lp_quotes_included3_level_message(const SecuritiesQuoteMmLpQuotesIncluded3LevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_1_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_1_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_1_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_1_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_2_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_2_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_2_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_2_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_ask_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_bid_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->estimated_trading_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->estimated_trading_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->mid_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Quote Mm Lp Quotes Included 3 Level Message off the wire: 335 bytes from at, returning where the next byte lies */
static size_t decode_securities_quote_mm_lp_quotes_included3_level_message(SecuritiesQuoteMmLpQuotesIncluded3LevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Quote Mm Lp Quotes Included 3 Level Message is what was written, byte for byte */
static void equal_securities_quote_mm_lp_quotes_included3_level_message(const SecuritiesQuoteMmLpQuotesIncluded3LevelMessage *read, const SecuritiesQuoteMmLpQuotesIncluded3LevelMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_1_volume[i] == written->ask_level_1_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_1_volume[i] == written->bid_level_1_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_1_volume[i] == written->lp_ask_level_1_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_1_volume[i] == written->lp_bid_level_1_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_2_volume[i] == written->ask_level_2_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_2_volume[i] == written->bid_level_2_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_2_volume[i] == written->lp_ask_level_2_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_2_volume[i] == written->lp_bid_level_2_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_3_volume[i] == written->ask_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_3_volume[i] == written->bid_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_3_volume[i] == written->lp_ask_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_3_volume[i] == written->lp_bid_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_ask_volume[i] == written->total_ask_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_bid_volume[i] == written->total_bid_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->estimated_trading_price[i] == written->estimated_trading_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->estimated_trading_volume[i] == written->estimated_trading_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->mid_price[i] == written->mid_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] == written->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] == written->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Quote Mm Lp Quotes Included 3 Level Message: written and read back, then read and written back */
static void check_securities_quote_mm_lp_quotes_included3_level_message(void) {
  SecuritiesQuoteMmLpQuotesIncluded3LevelMessage sent;
  SecuritiesQuoteMmLpQuotesIncluded3LevelMessage got;
  uint8_t wire[335];
  uint8_t again[335];

  any_securities_quote_mm_lp_quotes_included3_level_message(&sent);
  assert(encode_securities_quote_mm_lp_quotes_included3_level_message(&sent, wire, 0) == 335);
  assert(decode_securities_quote_mm_lp_quotes_included3_level_message(&got, wire, 0) == 335);
  equal_securities_quote_mm_lp_quotes_included3_level_message(&got, &sent);

  for (size_t i = 0; i < 335; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_quote_mm_lp_quotes_included3_level_message(&got, wire, 0) == 335);
  assert(encode_securities_quote_mm_lp_quotes_included3_level_message(&got, again, 0) == 335);
  for (size_t i = 0; i < 335; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Order Filled Plus Quote Mm Lp Quotes Included 3 Level Message: 428 bytes ---- */

/* Order Filled data with Best Order on NXT trading items - MM/LP Quotes Included * 3 Level Best Order on Ask/Bid. */
typedef struct {
  uint8_t message_sequence_number[8];                                    /* bytes 0 to 7 */
  uint8_t board_id[2];                                                   /* bytes 8 to 9 */
  uint8_t session_id[2];                                                 /* bytes 10 to 11 */
  uint8_t isin_code[12];                                                 /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue_from_krx[6];                  /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];                         /* bytes 30 to 41 */
  uint8_t price_change_against_previous_day;                             /* byte 42 */
  uint8_t a_price_change_against_the_previous_day[11];                   /* bytes 43 to 53 */
  uint8_t trading_price[11];                                             /* bytes 54 to 64 */
  uint8_t trading_volume[10];                                            /* bytes 65 to 74 */
  uint8_t opening_price[11];                                             /* bytes 75 to 85 */
  uint8_t todays_high[11];                                               /* bytes 86 to 96 */
  uint8_t todays_low[11];                                                /* bytes 97 to 107 */
  uint8_t accumulated_trading_volume[12];                                /* bytes 108 to 119 */
  uint8_t accumulated_trading_value[22];                                 /* bytes 120 to 141 */
  uint8_t final_ask_bid_type_code;                                       /* byte 142 */
  uint8_t lp_holding_quantity[15];                                       /* bytes 143 to 157 */
  uint8_t ask_level_1_price[11];                                         /* bytes 158 to 168 */
  uint8_t bid_level_1_price[11];                                         /* bytes 169 to 179 */
  uint8_t ask_level_1_volume[12];                                        /* bytes 180 to 191 */
  uint8_t bid_level_1_volume[12];                                        /* bytes 192 to 203 */
  uint8_t lp_ask_level_1_volume[12];                                     /* bytes 204 to 215 */
  uint8_t lp_bid_level_1_volume[12];                                     /* bytes 216 to 227 */
  uint8_t ask_level_2_price[11];                                         /* bytes 228 to 238 */
  uint8_t bid_level_2_price[11];                                         /* bytes 239 to 249 */
  uint8_t ask_level_2_volume[12];                                        /* bytes 250 to 261 */
  uint8_t bid_level_2_volume[12];                                        /* bytes 262 to 273 */
  uint8_t lp_ask_level_2_volume[12];                                     /* bytes 274 to 285 */
  uint8_t lp_bid_level_2_volume[12];                                     /* bytes 286 to 297 */
  uint8_t ask_level_3_price[11];                                         /* bytes 298 to 308 */
  uint8_t bid_level_3_price[11];                                         /* bytes 309 to 319 */
  uint8_t ask_level_3_volume[12];                                        /* bytes 320 to 331 */
  uint8_t bid_level_3_volume[12];                                        /* bytes 332 to 343 */
  uint8_t lp_ask_level_3_volume[12];                                     /* bytes 344 to 355 */
  uint8_t lp_bid_level_3_volume[12];                                     /* bytes 356 to 367 */
  uint8_t total_ask_volume_level_10[12];                                 /* bytes 368 to 379 */
  uint8_t total_bid_volume_level_10[12];                                 /* bytes 380 to 391 */
  uint8_t mid_price[11];                                                 /* bytes 392 to 402 */
  uint8_t total_mid_price_ask_volume_total_ask_volume_on_mid_price[12];  /* bytes 403 to 414 */
  uint8_t total_mid_price_bid_volume_total_bid_volume_on_mid_price[12];  /* bytes 415 to 426 */
  uint8_t end_keyword;                                                   /* byte 427 */
} SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded3LevelMessage;

/* any Securities Order Filled Plus Quote Mm Lp Quotes Included 3 Level Message at all: every byte one the checker chooses */
static void any_securities_order_filled_plus_quote_mm_lp_quotes_included3_level_message(SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded3LevelMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  record->price_change_against_previous_day = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->a_price_change_against_the_previous_day[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = arbitrary(); }
  record->final_ask_bid_type_code = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->lp_holding_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume_level_10[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume_level_10[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Order Filled Plus Quote Mm Lp Quotes Included 3 Level Message to the wire: 428 bytes from at, returning where the next byte goes */
static size_t encode_securities_order_filled_plus_quote_mm_lp_quotes_included3_level_message(const SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded3LevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  wire[at++] = record->price_change_against_previous_day;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->a_price_change_against_the_previous_day[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value[i]; }
  wire[at++] = record->final_ask_bid_type_code;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->lp_holding_quantity[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_1_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_1_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_1_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_1_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_2_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_2_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_2_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_2_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_ask_volume_level_10[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_bid_volume_level_10[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->mid_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Order Filled Plus Quote Mm Lp Quotes Included 3 Level Message off the wire: 428 bytes from at, returning where the next byte lies */
static size_t decode_securities_order_filled_plus_quote_mm_lp_quotes_included3_level_message(SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded3LevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  record->price_change_against_previous_day = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->a_price_change_against_the_previous_day[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = wire[at++]; }
  record->final_ask_bid_type_code = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->lp_holding_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume_level_10[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume_level_10[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Order Filled Plus Quote Mm Lp Quotes Included 3 Level Message is what was written, byte for byte */
static void equal_securities_order_filled_plus_quote_mm_lp_quotes_included3_level_message(const SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded3LevelMessage *read, const SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded3LevelMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  assert(read->price_change_against_previous_day == written->price_change_against_previous_day);
  for (size_t i = 0; i < 11; i++) { assert(read->a_price_change_against_the_previous_day[i] == written->a_price_change_against_the_previous_day[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value[i] == written->accumulated_trading_value[i]); }
  assert(read->final_ask_bid_type_code == written->final_ask_bid_type_code);
  for (size_t i = 0; i < 15; i++) { assert(read->lp_holding_quantity[i] == written->lp_holding_quantity[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_1_volume[i] == written->ask_level_1_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_1_volume[i] == written->bid_level_1_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_1_volume[i] == written->lp_ask_level_1_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_1_volume[i] == written->lp_bid_level_1_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_2_volume[i] == written->ask_level_2_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_2_volume[i] == written->bid_level_2_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_2_volume[i] == written->lp_ask_level_2_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_2_volume[i] == written->lp_bid_level_2_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_3_volume[i] == written->ask_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_3_volume[i] == written->bid_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_3_volume[i] == written->lp_ask_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_3_volume[i] == written->lp_bid_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_ask_volume_level_10[i] == written->total_ask_volume_level_10[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_bid_volume_level_10[i] == written->total_bid_volume_level_10[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->mid_price[i] == written->mid_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] == written->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] == written->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Order Filled Plus Quote Mm Lp Quotes Included 3 Level Message: written and read back, then read and written back */
static void check_securities_order_filled_plus_quote_mm_lp_quotes_included3_level_message(void) {
  SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded3LevelMessage sent;
  SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded3LevelMessage got;
  uint8_t wire[428];
  uint8_t again[428];

  any_securities_order_filled_plus_quote_mm_lp_quotes_included3_level_message(&sent);
  assert(encode_securities_order_filled_plus_quote_mm_lp_quotes_included3_level_message(&sent, wire, 0) == 428);
  assert(decode_securities_order_filled_plus_quote_mm_lp_quotes_included3_level_message(&got, wire, 0) == 428);
  equal_securities_order_filled_plus_quote_mm_lp_quotes_included3_level_message(&got, &sent);

  for (size_t i = 0; i < 428; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_order_filled_plus_quote_mm_lp_quotes_included3_level_message(&got, wire, 0) == 428);
  assert(encode_securities_order_filled_plus_quote_mm_lp_quotes_included3_level_message(&got, again, 0) == 428);
  for (size_t i = 0; i < 428; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Operation Ts Plus Quote Mm Lp Quotes Included 3 Level Message: 355 bytes ---- */

/* Market Operation TS with Best Order on NXT trading items - MM/LP Quotes Included The data is provided per an issue if a Market Operation Trading session event occurs and Best Order changes. * 3 Level. */
typedef struct {
  uint8_t message_sequence_number[8];                                    /* bytes 0 to 7 */
  uint8_t board_id[2];                                                   /* bytes 8 to 9 */
  uint8_t session_id[2];                                                 /* bytes 10 to 11 */
  uint8_t isin_code[12];                                                 /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue_from_krx[6];                  /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];                         /* bytes 30 to 41 */
  uint8_t board_event_id[3];                                             /* bytes 42 to 44 */
  uint8_t start_time_of_a_board_event[9];                                /* bytes 45 to 53 */
  uint8_t board_event_group_code[5];                                     /* bytes 54 to 58 */
  uint8_t trading_halt_reason_code[3];                                   /* bytes 59 to 61 */
  uint8_t ask_level_1_price[11];                                         /* bytes 62 to 72 */
  uint8_t bid_level_1_price[11];                                         /* bytes 73 to 83 */
  uint8_t ask_level_1_volume[12];                                        /* bytes 84 to 95 */
  uint8_t bid_level_1_volume[12];                                        /* bytes 96 to 107 */
  uint8_t lp_ask_level_1_volume[12];                                     /* bytes 108 to 119 */
  uint8_t lp_bid_level_1_volume[12];                                     /* bytes 120 to 131 */
  uint8_t ask_level_2_price[11];                                         /* bytes 132 to 142 */
  uint8_t bid_level_2_price[11];                                         /* bytes 143 to 153 */
  uint8_t ask_level_2_volume[12];                                        /* bytes 154 to 165 */
  uint8_t bid_level_2_volume[12];                                        /* bytes 166 to 177 */
  uint8_t lp_ask_level_2_volume[12];                                     /* bytes 178 to 189 */
  uint8_t lp_bid_level_2_volume[12];                                     /* bytes 190 to 201 */
  uint8_t ask_level_3_price[11];                                         /* bytes 202 to 212 */
  uint8_t bid_level_3_price[11];                                         /* bytes 213 to 223 */
  uint8_t ask_level_3_volume[12];                                        /* bytes 224 to 235 */
  uint8_t bid_level_3_volume[12];                                        /* bytes 236 to 247 */
  uint8_t lp_ask_level_3_volume[12];                                     /* bytes 248 to 259 */
  uint8_t lp_bid_level_3_volume[12];                                     /* bytes 260 to 271 */
  uint8_t total_ask_volume_level_10[12];                                 /* bytes 272 to 283 */
  uint8_t total_bid_volume_level_10[12];                                 /* bytes 284 to 295 */
  uint8_t estimated_trading_price[11];                                   /* bytes 296 to 306 */
  uint8_t estimated_trading_volume[12];                                  /* bytes 307 to 318 */
  uint8_t mid_price[11];                                                 /* bytes 319 to 329 */
  uint8_t total_mid_price_ask_volume_total_ask_volume_on_mid_price[12];  /* bytes 330 to 341 */
  uint8_t total_mid_price_bid_volume_total_bid_volume_on_mid_price[12];  /* bytes 342 to 353 */
  uint8_t end_keyword;                                                   /* byte 354 */
} MarketOperationTsPlusQuoteMmLpQuotesIncluded3LevelMessage;

/* any Market Operation Ts Plus Quote Mm Lp Quotes Included 3 Level Message at all: every byte one the checker chooses */
static void any_market_operation_ts_plus_quote_mm_lp_quotes_included3_level_message(MarketOperationTsPlusQuoteMmLpQuotesIncluded3LevelMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume_level_10[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume_level_10[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Market Operation Ts Plus Quote Mm Lp Quotes Included 3 Level Message to the wire: 355 bytes from at, returning where the next byte goes */
static size_t encode_market_operation_ts_plus_quote_mm_lp_quotes_included3_level_message(const MarketOperationTsPlusQuoteMmLpQuotesIncluded3LevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->board_event_id[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->start_time_of_a_board_event[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->board_event_group_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_halt_reason_code[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_1_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_1_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_1_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_1_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_2_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_2_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_2_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_2_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_ask_volume_level_10[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_bid_volume_level_10[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->estimated_trading_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->estimated_trading_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->mid_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Market Operation Ts Plus Quote Mm Lp Quotes Included 3 Level Message off the wire: 355 bytes from at, returning where the next byte lies */
static size_t decode_market_operation_ts_plus_quote_mm_lp_quotes_included3_level_message(MarketOperationTsPlusQuoteMmLpQuotesIncluded3LevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume_level_10[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume_level_10[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Market Operation Ts Plus Quote Mm Lp Quotes Included 3 Level Message is what was written, byte for byte */
static void equal_market_operation_ts_plus_quote_mm_lp_quotes_included3_level_message(const MarketOperationTsPlusQuoteMmLpQuotesIncluded3LevelMessage *read, const MarketOperationTsPlusQuoteMmLpQuotesIncluded3LevelMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->board_event_id[i] == written->board_event_id[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->start_time_of_a_board_event[i] == written->start_time_of_a_board_event[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->board_event_group_code[i] == written->board_event_group_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trading_halt_reason_code[i] == written->trading_halt_reason_code[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_1_volume[i] == written->ask_level_1_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_1_volume[i] == written->bid_level_1_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_1_volume[i] == written->lp_ask_level_1_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_1_volume[i] == written->lp_bid_level_1_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_2_volume[i] == written->ask_level_2_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_2_volume[i] == written->bid_level_2_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_2_volume[i] == written->lp_ask_level_2_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_2_volume[i] == written->lp_bid_level_2_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_3_volume[i] == written->ask_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_3_volume[i] == written->bid_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_3_volume[i] == written->lp_ask_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_3_volume[i] == written->lp_bid_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_ask_volume_level_10[i] == written->total_ask_volume_level_10[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_bid_volume_level_10[i] == written->total_bid_volume_level_10[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->estimated_trading_price[i] == written->estimated_trading_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->estimated_trading_volume[i] == written->estimated_trading_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->mid_price[i] == written->mid_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] == written->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] == written->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Market Operation Ts Plus Quote Mm Lp Quotes Included 3 Level Message: written and read back, then read and written back */
static void check_market_operation_ts_plus_quote_mm_lp_quotes_included3_level_message(void) {
  MarketOperationTsPlusQuoteMmLpQuotesIncluded3LevelMessage sent;
  MarketOperationTsPlusQuoteMmLpQuotesIncluded3LevelMessage got;
  uint8_t wire[355];
  uint8_t again[355];

  any_market_operation_ts_plus_quote_mm_lp_quotes_included3_level_message(&sent);
  assert(encode_market_operation_ts_plus_quote_mm_lp_quotes_included3_level_message(&sent, wire, 0) == 355);
  assert(decode_market_operation_ts_plus_quote_mm_lp_quotes_included3_level_message(&got, wire, 0) == 355);
  equal_market_operation_ts_plus_quote_mm_lp_quotes_included3_level_message(&got, &sent);

  for (size_t i = 0; i < 355; i++) { wire[i] = arbitrary(); }
  assert(decode_market_operation_ts_plus_quote_mm_lp_quotes_included3_level_message(&got, wire, 0) == 355);
  assert(encode_market_operation_ts_plus_quote_mm_lp_quotes_included3_level_message(&got, again, 0) == 355);
  for (size_t i = 0; i < 355; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Order Filled Message: 181 bytes ------------------------------ */

/* Securities_Order Filled Order Filled Data on NXT trading items provided. */
typedef struct {
  uint8_t message_sequence_number[8];                    /* bytes 0 to 7 */
  uint8_t board_id[2];                                   /* bytes 8 to 9 */
  uint8_t session_id[2];                                 /* bytes 10 to 11 */
  uint8_t isin_code[12];                                 /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue_from_krx[6];  /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];         /* bytes 30 to 41 */
  uint8_t price_change_against_previous_day;             /* byte 42 */
  uint8_t a_price_change_against_the_previous_day[11];   /* bytes 43 to 53 */
  uint8_t trading_price[11];                             /* bytes 54 to 64 */
  uint8_t trading_volume[10];                            /* bytes 65 to 74 */
  uint8_t opening_price[11];                             /* bytes 75 to 85 */
  uint8_t todays_high[11];                               /* bytes 86 to 96 */
  uint8_t todays_low[11];                                /* bytes 97 to 107 */
  uint8_t accumulated_trading_volume[12];                /* bytes 108 to 119 */
  uint8_t accumulated_trading_value[22];                 /* bytes 120 to 141 */
  uint8_t final_ask_bid_type_code;                       /* byte 142 */
  uint8_t lp_holding_quantity[15];                       /* bytes 143 to 157 */
  uint8_t the_best_ask[11];                              /* bytes 158 to 168 */
  uint8_t the_best_bid[11];                              /* bytes 169 to 179 */
  uint8_t end_keyword;                                   /* byte 180 */
} SecuritiesOrderFilledMessage;

/* any Securities Order Filled Message at all: every byte one the checker chooses */
static void any_securities_order_filled_message(SecuritiesOrderFilledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  record->price_change_against_previous_day = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->a_price_change_against_the_previous_day[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = arbitrary(); }
  record->final_ask_bid_type_code = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->lp_holding_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->the_best_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->the_best_bid[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Order Filled Message to the wire: 181 bytes from at, returning where the next byte goes */
static size_t encode_securities_order_filled_message(const SecuritiesOrderFilledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  wire[at++] = record->price_change_against_previous_day;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->a_price_change_against_the_previous_day[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value[i]; }
  wire[at++] = record->final_ask_bid_type_code;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->lp_holding_quantity[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->the_best_ask[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->the_best_bid[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Order Filled Message off the wire: 181 bytes from at, returning where the next byte lies */
static size_t decode_securities_order_filled_message(SecuritiesOrderFilledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  record->price_change_against_previous_day = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->a_price_change_against_the_previous_day[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = wire[at++]; }
  record->final_ask_bid_type_code = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->lp_holding_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->the_best_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->the_best_bid[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Order Filled Message is what was written, byte for byte */
static void equal_securities_order_filled_message(const SecuritiesOrderFilledMessage *read, const SecuritiesOrderFilledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  assert(read->price_change_against_previous_day == written->price_change_against_previous_day);
  for (size_t i = 0; i < 11; i++) { assert(read->a_price_change_against_the_previous_day[i] == written->a_price_change_against_the_previous_day[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value[i] == written->accumulated_trading_value[i]); }
  assert(read->final_ask_bid_type_code == written->final_ask_bid_type_code);
  for (size_t i = 0; i < 15; i++) { assert(read->lp_holding_quantity[i] == written->lp_holding_quantity[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->the_best_ask[i] == written->the_best_ask[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->the_best_bid[i] == written->the_best_bid[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Order Filled Message: written and read back, then read and written back */
static void check_securities_order_filled_message(void) {
  SecuritiesOrderFilledMessage sent;
  SecuritiesOrderFilledMessage got;
  uint8_t wire[181];
  uint8_t again[181];

  any_securities_order_filled_message(&sent);
  assert(encode_securities_order_filled_message(&sent, wire, 0) == 181);
  assert(decode_securities_order_filled_message(&got, wire, 0) == 181);
  equal_securities_order_filled_message(&got, &sent);

  for (size_t i = 0; i < 181; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_order_filled_message(&got, wire, 0) == 181);
  assert(encode_securities_order_filled_message(&got, again, 0) == 181);
  for (size_t i = 0; i < 181; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Operation Ts Message: 63 bytes ----------------------------------- */

/* The data is provided per an issue if a Market Operation Trading session event occurs. */
typedef struct {
  uint8_t message_sequence_number[8];                    /* bytes 0 to 7 */
  uint8_t board_id[2];                                   /* bytes 8 to 9 */
  uint8_t session_id[2];                                 /* bytes 10 to 11 */
  uint8_t isin_code[12];                                 /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue_from_krx[6];  /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];         /* bytes 30 to 41 */
  uint8_t board_event_id[3];                             /* bytes 42 to 44 */
  uint8_t start_time_of_a_board_event[9];                /* bytes 45 to 53 */
  uint8_t board_event_group_code[5];                     /* bytes 54 to 58 */
  uint8_t trading_halt_reason_code[3];                   /* bytes 59 to 61 */
  uint8_t end_keyword;                                   /* byte 62 */
} MarketOperationTsMessage;

/* any Market Operation Ts Message at all: every byte one the checker chooses */
static void any_market_operation_ts_message(MarketOperationTsMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Market Operation Ts Message to the wire: 63 bytes from at, returning where the next byte goes */
static size_t encode_market_operation_ts_message(const MarketOperationTsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->board_event_id[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->start_time_of_a_board_event[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->board_event_group_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_halt_reason_code[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Market Operation Ts Message off the wire: 63 bytes from at, returning where the next byte lies */
static size_t decode_market_operation_ts_message(MarketOperationTsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Market Operation Ts Message is what was written, byte for byte */
static void equal_market_operation_ts_message(const MarketOperationTsMessage *read, const MarketOperationTsMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->board_event_id[i] == written->board_event_id[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->start_time_of_a_board_event[i] == written->start_time_of_a_board_event[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->board_event_group_code[i] == written->board_event_group_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trading_halt_reason_code[i] == written->trading_halt_reason_code[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Market Operation Ts Message: written and read back, then read and written back */
static void check_market_operation_ts_message(void) {
  MarketOperationTsMessage sent;
  MarketOperationTsMessage got;
  uint8_t wire[63];
  uint8_t again[63];

  any_market_operation_ts_message(&sent);
  assert(encode_market_operation_ts_message(&sent, wire, 0) == 63);
  assert(decode_market_operation_ts_message(&got, wire, 0) == 63);
  equal_market_operation_ts_message(&got, &sent);

  for (size_t i = 0; i < 63; i++) { wire[i] = arbitrary(); }
  assert(decode_market_operation_ts_message(&got, wire, 0) == 63);
  assert(encode_market_operation_ts_message(&got, again, 0) == 63);
  for (size_t i = 0; i < 63; i++) { assert(again[i] == wire[i]); }
}

/* ---- Issue Closing Message: 107 bytes ---------------------------------------- */

/* The data is provided in case of an issue closing per board. */
typedef struct {
  uint8_t message_sequence_number[8];                                                /* bytes 0 to 7 */
  uint8_t board_id[2];                                                               /* bytes 8 to 9 */
  uint8_t isin_code[12];                                                             /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue_from_krx[6];                              /* bytes 22 to 27 */
  uint8_t closing_price[11];                                                         /* bytes 28 to 38 */
  uint8_t closing_price_type_code;                                                   /* byte 39 */
  uint8_t upper_limit_price_on_the_single_price_trade_in_the_off_hours_session[11];  /* bytes 40 to 50 */
  uint8_t lower_limit_price_on_the_single_price_trade_in_the_off_hours_session[11];  /* bytes 51 to 61 */
  uint8_t closing_price_weighted_stock_price_average[11];                            /* bytes 62 to 72 */
  uint8_t closing_price_base_price_of_buy_in[11];                                    /* bytes 73 to 83 */
  uint8_t closing_price_upper_limit_of_buy_in[11];                                   /* bytes 84 to 94 */
  uint8_t closing_price_lower_limit_of_buy_in[11];                                   /* bytes 95 to 105 */
  uint8_t end_keyword;                                                               /* byte 106 */
} IssueClosingMessage;

/* any Issue Closing Message at all: every byte one the checker chooses */
static void any_issue_closing_message(IssueClosingMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price[i] = arbitrary(); }
  record->closing_price_type_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->upper_limit_price_on_the_single_price_trade_in_the_off_hours_session[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_price_on_the_single_price_trade_in_the_off_hours_session[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_weighted_stock_price_average[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_base_price_of_buy_in[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_upper_limit_of_buy_in[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_lower_limit_of_buy_in[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Issue Closing Message to the wire: 107 bytes from at, returning where the next byte goes */
static size_t encode_issue_closing_message(const IssueClosingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price[i]; }
  wire[at++] = record->closing_price_type_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->upper_limit_price_on_the_single_price_trade_in_the_off_hours_session[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lower_limit_price_on_the_single_price_trade_in_the_off_hours_session[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_weighted_stock_price_average[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_base_price_of_buy_in[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_upper_limit_of_buy_in[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_lower_limit_of_buy_in[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Issue Closing Message off the wire: 107 bytes from at, returning where the next byte lies */
static size_t decode_issue_closing_message(IssueClosingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price[i] = wire[at++]; }
  record->closing_price_type_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->upper_limit_price_on_the_single_price_trade_in_the_off_hours_session[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_price_on_the_single_price_trade_in_the_off_hours_session[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_weighted_stock_price_average[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_base_price_of_buy_in[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_upper_limit_of_buy_in[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_lower_limit_of_buy_in[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Issue Closing Message is what was written, byte for byte */
static void equal_issue_closing_message(const IssueClosingMessage *read, const IssueClosingMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  assert(read->closing_price_type_code == written->closing_price_type_code);
  for (size_t i = 0; i < 11; i++) { assert(read->upper_limit_price_on_the_single_price_trade_in_the_off_hours_session[i] == written->upper_limit_price_on_the_single_price_trade_in_the_off_hours_session[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lower_limit_price_on_the_single_price_trade_in_the_off_hours_session[i] == written->lower_limit_price_on_the_single_price_trade_in_the_off_hours_session[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_weighted_stock_price_average[i] == written->closing_price_weighted_stock_price_average[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_base_price_of_buy_in[i] == written->closing_price_base_price_of_buy_in[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_upper_limit_of_buy_in[i] == written->closing_price_upper_limit_of_buy_in[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_lower_limit_of_buy_in[i] == written->closing_price_lower_limit_of_buy_in[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Issue Closing Message: written and read back, then read and written back */
static void check_issue_closing_message(void) {
  IssueClosingMessage sent;
  IssueClosingMessage got;
  uint8_t wire[107];
  uint8_t again[107];

  any_issue_closing_message(&sent);
  assert(encode_issue_closing_message(&sent, wire, 0) == 107);
  assert(decode_issue_closing_message(&got, wire, 0) == 107);
  equal_issue_closing_message(&got, &sent);

  for (size_t i = 0; i < 107; i++) { wire[i] = arbitrary(); }
  assert(decode_issue_closing_message(&got, wire, 0) == 107);
  assert(encode_issue_closing_message(&got, again, 0) == 107);
  for (size_t i = 0; i < 107; i++) { assert(again[i] == wire[i]); }
}

/* ---- Triggering Removing Vi Message: 111 bytes ------------------------------- */

/* Triggering/removing VI (Volatility Interruption). */
typedef struct {
  uint8_t message_sequence_number[8];                    /* bytes 0 to 7 */
  uint8_t board_id[2];                                   /* bytes 8 to 9 */
  uint8_t isin_code[12];                                 /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue_from_krx[6];  /* bytes 22 to 27 */
  uint8_t processing_time_of_trading_system[12];         /* bytes 28 to 39 */
  uint8_t the_time_ending_vi[9];                         /* bytes 40 to 48 */
  uint8_t vi_status_code;                                /* byte 49 */
  uint8_t vi_type_code;                                  /* byte 50 */
  uint8_t a_base_price_to_trigger_static_vi[11];         /* bytes 51 to 61 */
  uint8_t a_base_price_to_trigger_dynamic_vi[11];        /* bytes 62 to 72 */
  uint8_t vi_triggering_price[11];                       /* bytes 73 to 83 */
  uint8_t disparate_ratio_to_trigger_static_vi[13];      /* bytes 84 to 96 */
  uint8_t disparate_ratio_to_trigger_dynamic_vi[13];     /* bytes 97 to 109 */
  uint8_t end_keyword;                                   /* byte 110 */
} TriggeringRemovingViMessage;

/* any Triggering Removing Vi Message at all: every byte one the checker chooses */
static void any_triggering_removing_vi_message(TriggeringRemovingViMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->the_time_ending_vi[i] = arbitrary(); }
  record->vi_status_code = arbitrary();
  record->vi_type_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->a_base_price_to_trigger_static_vi[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->a_base_price_to_trigger_dynamic_vi[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->vi_triggering_price[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->disparate_ratio_to_trigger_static_vi[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->disparate_ratio_to_trigger_dynamic_vi[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Triggering Removing Vi Message to the wire: 111 bytes from at, returning where the next byte goes */
static size_t encode_triggering_removing_vi_message(const TriggeringRemovingViMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->the_time_ending_vi[i]; }
  wire[at++] = record->vi_status_code;
  wire[at++] = record->vi_type_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->a_base_price_to_trigger_static_vi[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->a_base_price_to_trigger_dynamic_vi[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->vi_triggering_price[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->disparate_ratio_to_trigger_static_vi[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->disparate_ratio_to_trigger_dynamic_vi[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Triggering Removing Vi Message off the wire: 111 bytes from at, returning where the next byte lies */
static size_t decode_triggering_removing_vi_message(TriggeringRemovingViMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->the_time_ending_vi[i] = wire[at++]; }
  record->vi_status_code = wire[at++];
  record->vi_type_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->a_base_price_to_trigger_static_vi[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->a_base_price_to_trigger_dynamic_vi[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->vi_triggering_price[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->disparate_ratio_to_trigger_static_vi[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->disparate_ratio_to_trigger_dynamic_vi[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Triggering Removing Vi Message is what was written, byte for byte */
static void equal_triggering_removing_vi_message(const TriggeringRemovingViMessage *read, const TriggeringRemovingViMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->the_time_ending_vi[i] == written->the_time_ending_vi[i]); }
  assert(read->vi_status_code == written->vi_status_code);
  assert(read->vi_type_code == written->vi_type_code);
  for (size_t i = 0; i < 11; i++) { assert(read->a_base_price_to_trigger_static_vi[i] == written->a_base_price_to_trigger_static_vi[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->a_base_price_to_trigger_dynamic_vi[i] == written->a_base_price_to_trigger_dynamic_vi[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->vi_triggering_price[i] == written->vi_triggering_price[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->disparate_ratio_to_trigger_static_vi[i] == written->disparate_ratio_to_trigger_static_vi[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->disparate_ratio_to_trigger_dynamic_vi[i] == written->disparate_ratio_to_trigger_dynamic_vi[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Triggering Removing Vi Message: written and read back, then read and written back */
static void check_triggering_removing_vi_message(void) {
  TriggeringRemovingViMessage sent;
  TriggeringRemovingViMessage got;
  uint8_t wire[111];
  uint8_t again[111];

  any_triggering_removing_vi_message(&sent);
  assert(encode_triggering_removing_vi_message(&sent, wire, 0) == 111);
  assert(decode_triggering_removing_vi_message(&got, wire, 0) == 111);
  equal_triggering_removing_vi_message(&got, &sent);

  for (size_t i = 0; i < 111; i++) { wire[i] = arbitrary(); }
  assert(decode_triggering_removing_vi_message(&got, wire, 0) == 111);
  assert(encode_triggering_removing_vi_message(&got, again, 0) == 111);
  for (size_t i = 0; i < 111; i++) { assert(again[i] == wire[i]); }
}

/* ---- Closing Price Trading Quote Message: 53 bytes --------------------------- */

/* Total Ask/Bid volume per Issue on Closing Price Trade. */
typedef struct {
  uint8_t message_sequence_number[8];                    /* bytes 0 to 7 */
  uint8_t board_id[2];                                   /* bytes 8 to 9 */
  uint8_t isin_code[12];                                 /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue_from_krx[6];  /* bytes 22 to 27 */
  uint8_t total_ask_volume[12];                          /* bytes 28 to 39 */
  uint8_t total_bid_volume[12];                          /* bytes 40 to 51 */
  uint8_t end_keyword;                                   /* byte 52 */
} ClosingPriceTradingQuoteMessage;

/* any Closing Price Trading Quote Message at all: every byte one the checker chooses */
static void any_closing_price_trading_quote_message(ClosingPriceTradingQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Closing Price Trading Quote Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_closing_price_trading_quote_message(const ClosingPriceTradingQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_ask_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_bid_volume[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Closing Price Trading Quote Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_closing_price_trading_quote_message(ClosingPriceTradingQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Closing Price Trading Quote Message is what was written, byte for byte */
static void equal_closing_price_trading_quote_message(const ClosingPriceTradingQuoteMessage *read, const ClosingPriceTradingQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_ask_volume[i] == written->total_ask_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_bid_volume[i] == written->total_bid_volume[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Closing Price Trading Quote Message: written and read back, then read and written back */
static void check_closing_price_trading_quote_message(void) {
  ClosingPriceTradingQuoteMessage sent;
  ClosingPriceTradingQuoteMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_closing_price_trading_quote_message(&sent);
  assert(encode_closing_price_trading_quote_message(&sent, wire, 0) == 53);
  assert(decode_closing_price_trading_quote_message(&got, wire, 0) == 53);
  equal_closing_price_trading_quote_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_closing_price_trading_quote_message(&got, wire, 0) == 53);
  assert(encode_closing_price_trading_quote_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_polling_data_message();
  check_securities_quote_mm_lp_quotes_included3_level_message();
  check_securities_order_filled_plus_quote_mm_lp_quotes_included3_level_message();
  check_market_operation_ts_plus_quote_mm_lp_quotes_included3_level_message();
  check_securities_order_filled_message();
  check_market_operation_ts_message();
  check_issue_closing_message();
  check_triggering_removing_vi_message();
  check_closing_price_trading_quote_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
