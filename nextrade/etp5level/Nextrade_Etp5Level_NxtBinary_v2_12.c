// nextrade/etp5level/Nextrade_Etp5Level_NxtBinary_v2_12.c
/*
 * Nextrade Nextrade Etp Market Data 5 Level
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

/* ---- Polling Data Message: 8 bytes ------------------------------------------- */

/* The data is provided periodically in order to check multicast group status. */
typedef struct {
  uint8_t current_time_1_minute_interval[4];  /* bytes 0 to 3 */
  uint8_t end_keyword[4];                     /* bytes 4 to 7 */
} PollingDataMessage;

/* any Polling Data Message at all: every byte one the checker chooses */
static void any_polling_data_message(PollingDataMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->current_time_1_minute_interval[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Polling Data Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_polling_data_message(const PollingDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->current_time_1_minute_interval[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Polling Data Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_polling_data_message(PollingDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->current_time_1_minute_interval[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Polling Data Message is what was written, byte for byte */
static void equal_polling_data_message(const PollingDataMessage *read, const PollingDataMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->current_time_1_minute_interval[i] == written->current_time_1_minute_interval[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Polling Data Message: written and read back, then read and written back */
static void check_polling_data_message(void) {
  PollingDataMessage sent;
  PollingDataMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_polling_data_message(&sent);
  assert(encode_polling_data_message(&sent, wire, 0) == 8);
  assert(decode_polling_data_message(&got, wire, 0) == 8);
  equal_polling_data_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_polling_data_message(&got, wire, 0) == 8);
  assert(encode_polling_data_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Quote Mm Lp Quotes Included 5 Level Message: 336 bytes ------- */

/* Securities_Quote (MM/LP Quotes Included, 5 Level) Best Order Data on NXT Trading Items provided - MM/LP Quotes Included * 5 Level Best Order on Ask/Bid. */
typedef struct {
  uint8_t message_sequence_number[4];                                   /* bytes 0 to 3 */
  uint8_t board_id[2];                                                  /* bytes 4 to 5 */
  uint8_t session_id[2];                                                /* bytes 6 to 7 */
  uint8_t isin_code[12];                                                /* bytes 8 to 19 */
  uint8_t a_designated_number_for_an_issue_from_krx[4];                 /* bytes 20 to 23 */
  uint8_t processing_time_of_trading_system[12];                        /* bytes 24 to 35 */
  uint8_t ask_level_1_price[8];                                         /* bytes 36 to 43 */
  uint8_t bid_level_1_price[8];                                         /* bytes 44 to 51 */
  uint8_t ask_level_1_volume[8];                                        /* bytes 52 to 59 */
  uint8_t bid_level_1_volume[8];                                        /* bytes 60 to 67 */
  uint8_t lp_ask_level_1_volume[8];                                     /* bytes 68 to 75 */
  uint8_t lp_bid_level_1_volume[8];                                     /* bytes 76 to 83 */
  uint8_t ask_level_2_price[8];                                         /* bytes 84 to 91 */
  uint8_t bid_level_2_price[8];                                         /* bytes 92 to 99 */
  uint8_t ask_level_2_volume[8];                                        /* bytes 100 to 107 */
  uint8_t bid_level_2_volume[8];                                        /* bytes 108 to 115 */
  uint8_t lp_ask_level_2_volume[8];                                     /* bytes 116 to 123 */
  uint8_t lp_bid_level_2_volume[8];                                     /* bytes 124 to 131 */
  uint8_t ask_level_3_price[8];                                         /* bytes 132 to 139 */
  uint8_t bid_level_3_price[8];                                         /* bytes 140 to 147 */
  uint8_t ask_level_3_volume[8];                                        /* bytes 148 to 155 */
  uint8_t bid_level_3_volume[8];                                        /* bytes 156 to 163 */
  uint8_t lp_ask_level_3_volume[8];                                     /* bytes 164 to 171 */
  uint8_t lp_bid_level_3_volume[8];                                     /* bytes 172 to 179 */
  uint8_t ask_level_4_price[8];                                         /* bytes 180 to 187 */
  uint8_t bid_level_4_price[8];                                         /* bytes 188 to 195 */
  uint8_t ask_level_4_volume[8];                                        /* bytes 196 to 203 */
  uint8_t bid_level_4_volume[8];                                        /* bytes 204 to 211 */
  uint8_t lp_ask_level_4_volume[8];                                     /* bytes 212 to 219 */
  uint8_t lp_bid_level_4_volume[8];                                     /* bytes 220 to 227 */
  uint8_t ask_level_5_price[8];                                         /* bytes 228 to 235 */
  uint8_t bid_level_5_price[8];                                         /* bytes 236 to 243 */
  uint8_t ask_level_5_volume[8];                                        /* bytes 244 to 251 */
  uint8_t bid_level_5_volume[8];                                        /* bytes 252 to 259 */
  uint8_t lp_ask_level_5_volume[8];                                     /* bytes 260 to 267 */
  uint8_t lp_bid_level_5_volume[8];                                     /* bytes 268 to 275 */
  uint8_t total_ask_volume[8];                                          /* bytes 276 to 283 */
  uint8_t total_bid_volume[8];                                          /* bytes 284 to 291 */
  uint8_t estimated_trading_price[8];                                   /* bytes 292 to 299 */
  uint8_t estimated_trading_volume[8];                                  /* bytes 300 to 307 */
  uint8_t mid_price[8];                                                 /* bytes 308 to 315 */
  uint8_t total_mid_price_ask_volume_total_ask_volume_on_mid_price[8];  /* bytes 316 to 323 */
  uint8_t total_mid_price_bid_volume_total_bid_volume_on_mid_price[8];  /* bytes 324 to 331 */
  uint8_t end_keyword[4];                                               /* bytes 332 to 335 */
} SecuritiesQuoteMmLpQuotesIncluded5LevelMessage;

/* any Securities Quote Mm Lp Quotes Included 5 Level Message at all: every byte one the checker chooses */
static void any_securities_quote_mm_lp_quotes_included5_level_message(SecuritiesQuoteMmLpQuotesIncluded5LevelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->estimated_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->estimated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Securities Quote Mm Lp Quotes Included 5 Level Message to the wire: 336 bytes from at, returning where the next byte goes */
static size_t encode_securities_quote_mm_lp_quotes_included5_level_message(const SecuritiesQuoteMmLpQuotesIncluded5LevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_1_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_1_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_1_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_1_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_2_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_2_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_2_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_2_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_3_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_3_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_3_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_3_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_4_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_4_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_4_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_4_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_5_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_5_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_5_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_5_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_ask_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_bid_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->estimated_trading_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->estimated_trading_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Securities Quote Mm Lp Quotes Included 5 Level Message off the wire: 336 bytes from at, returning where the next byte lies */
static size_t decode_securities_quote_mm_lp_quotes_included5_level_message(SecuritiesQuoteMmLpQuotesIncluded5LevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_bid_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->estimated_trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->estimated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Securities Quote Mm Lp Quotes Included 5 Level Message is what was written, byte for byte */
static void equal_securities_quote_mm_lp_quotes_included5_level_message(const SecuritiesQuoteMmLpQuotesIncluded5LevelMessage *read, const SecuritiesQuoteMmLpQuotesIncluded5LevelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_1_volume[i] == written->ask_level_1_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_1_volume[i] == written->bid_level_1_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_1_volume[i] == written->lp_ask_level_1_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_1_volume[i] == written->lp_bid_level_1_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_2_volume[i] == written->ask_level_2_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_2_volume[i] == written->bid_level_2_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_2_volume[i] == written->lp_ask_level_2_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_2_volume[i] == written->lp_bid_level_2_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_3_volume[i] == written->ask_level_3_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_3_volume[i] == written->bid_level_3_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_3_volume[i] == written->lp_ask_level_3_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_3_volume[i] == written->lp_bid_level_3_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_4_volume[i] == written->ask_level_4_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_4_volume[i] == written->bid_level_4_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_4_volume[i] == written->lp_ask_level_4_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_4_volume[i] == written->lp_bid_level_4_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_5_volume[i] == written->ask_level_5_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_5_volume[i] == written->bid_level_5_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_5_volume[i] == written->lp_ask_level_5_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_5_volume[i] == written->lp_bid_level_5_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_ask_volume[i] == written->total_ask_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_bid_volume[i] == written->total_bid_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->estimated_trading_price[i] == written->estimated_trading_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->estimated_trading_volume[i] == written->estimated_trading_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mid_price[i] == written->mid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] == written->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] == written->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Securities Quote Mm Lp Quotes Included 5 Level Message: written and read back, then read and written back */
static void check_securities_quote_mm_lp_quotes_included5_level_message(void) {
  SecuritiesQuoteMmLpQuotesIncluded5LevelMessage sent;
  SecuritiesQuoteMmLpQuotesIncluded5LevelMessage got;
  uint8_t wire[336];
  uint8_t again[336];

  any_securities_quote_mm_lp_quotes_included5_level_message(&sent);
  assert(encode_securities_quote_mm_lp_quotes_included5_level_message(&sent, wire, 0) == 336);
  assert(decode_securities_quote_mm_lp_quotes_included5_level_message(&got, wire, 0) == 336);
  equal_securities_quote_mm_lp_quotes_included5_level_message(&got, &sent);

  for (size_t i = 0; i < 336; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_quote_mm_lp_quotes_included5_level_message(&got, wire, 0) == 336);
  assert(encode_securities_quote_mm_lp_quotes_included5_level_message(&got, again, 0) == 336);
  for (size_t i = 0; i < 336; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Order Filled Plus Quote Mm Lp Quotes Included 5 Level Message: 402 bytes ---- */

/* Order Filled data with Best Order on NXT trading items - MM/LP Quotes Included * 5 Level Best Order on Ask/Bid. */
typedef struct {
  uint8_t message_sequence_number[4];                                   /* bytes 0 to 3 */
  uint8_t board_id[2];                                                  /* bytes 4 to 5 */
  uint8_t session_id[2];                                                /* bytes 6 to 7 */
  uint8_t isin_code[12];                                                /* bytes 8 to 19 */
  uint8_t a_designated_number_for_an_issue_from_krx[4];                 /* bytes 20 to 23 */
  uint8_t processing_time_of_trading_system[12];                        /* bytes 24 to 35 */
  uint8_t price_change_against_previous_day;                            /* byte 36 */
  uint8_t a_price_change_against_the_previous_day[8];                   /* bytes 37 to 44 */
  uint8_t trading_price[8];                                             /* bytes 45 to 52 */
  uint8_t trading_volume[8];                                            /* bytes 53 to 60 */
  uint8_t opening_price[8];                                             /* bytes 61 to 68 */
  uint8_t todays_high[8];                                               /* bytes 69 to 76 */
  uint8_t todays_low[8];                                                /* bytes 77 to 84 */
  uint8_t accumulated_trading_volume[8];                                /* bytes 85 to 92 */
  uint8_t accumulated_trading_value[16];                                /* bytes 93 to 108 */
  uint8_t final_ask_bid_type_code;                                      /* byte 109 */
  uint8_t lp_holding_quantity[8];                                       /* bytes 110 to 117 */
  uint8_t ask_level_1_price[8];                                         /* bytes 118 to 125 */
  uint8_t bid_level_1_price[8];                                         /* bytes 126 to 133 */
  uint8_t ask_level_1_volume[8];                                        /* bytes 134 to 141 */
  uint8_t bid_level_1_volume[8];                                        /* bytes 142 to 149 */
  uint8_t lp_ask_level_1_volume[8];                                     /* bytes 150 to 157 */
  uint8_t lp_bid_level_1_volume[8];                                     /* bytes 158 to 165 */
  uint8_t ask_level_2_price[8];                                         /* bytes 166 to 173 */
  uint8_t bid_level_2_price[8];                                         /* bytes 174 to 181 */
  uint8_t ask_level_2_volume[8];                                        /* bytes 182 to 189 */
  uint8_t bid_level_2_volume[8];                                        /* bytes 190 to 197 */
  uint8_t lp_ask_level_2_volume[8];                                     /* bytes 198 to 205 */
  uint8_t lp_bid_level_2_volume[8];                                     /* bytes 206 to 213 */
  uint8_t ask_level_3_price[8];                                         /* bytes 214 to 221 */
  uint8_t bid_level_3_price[8];                                         /* bytes 222 to 229 */
  uint8_t ask_level_3_volume[8];                                        /* bytes 230 to 237 */
  uint8_t bid_level_3_volume[8];                                        /* bytes 238 to 245 */
  uint8_t lp_ask_level_3_volume[8];                                     /* bytes 246 to 253 */
  uint8_t lp_bid_level_3_volume[8];                                     /* bytes 254 to 261 */
  uint8_t ask_level_4_price[8];                                         /* bytes 262 to 269 */
  uint8_t bid_level_4_price[8];                                         /* bytes 270 to 277 */
  uint8_t ask_level_4_volume[8];                                        /* bytes 278 to 285 */
  uint8_t bid_level_4_volume[8];                                        /* bytes 286 to 293 */
  uint8_t lp_ask_level_4_volume[8];                                     /* bytes 294 to 301 */
  uint8_t lp_bid_level_4_volume[8];                                     /* bytes 302 to 309 */
  uint8_t ask_level_5_price[8];                                         /* bytes 310 to 317 */
  uint8_t bid_level_5_price[8];                                         /* bytes 318 to 325 */
  uint8_t ask_level_5_volume[8];                                        /* bytes 326 to 333 */
  uint8_t bid_level_5_volume[8];                                        /* bytes 334 to 341 */
  uint8_t lp_ask_level_5_volume[8];                                     /* bytes 342 to 349 */
  uint8_t lp_bid_level_5_volume[8];                                     /* bytes 350 to 357 */
  uint8_t total_ask_volume_level_10[8];                                 /* bytes 358 to 365 */
  uint8_t total_bid_volume_level_10[8];                                 /* bytes 366 to 373 */
  uint8_t mid_price[8];                                                 /* bytes 374 to 381 */
  uint8_t total_mid_price_ask_volume_total_ask_volume_on_mid_price[8];  /* bytes 382 to 389 */
  uint8_t total_mid_price_bid_volume_total_bid_volume_on_mid_price[8];  /* bytes 390 to 397 */
  uint8_t end_keyword[4];                                               /* bytes 398 to 401 */
} SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded5LevelMessage;

/* any Securities Order Filled Plus Quote Mm Lp Quotes Included 5 Level Message at all: every byte one the checker chooses */
static void any_securities_order_filled_plus_quote_mm_lp_quotes_included5_level_message(SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded5LevelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  record->price_change_against_previous_day = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->a_price_change_against_the_previous_day[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->accumulated_trading_value[i] = arbitrary(); }
  record->final_ask_bid_type_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->lp_holding_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_ask_volume_level_10[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_bid_volume_level_10[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Securities Order Filled Plus Quote Mm Lp Quotes Included 5 Level Message to the wire: 402 bytes from at, returning where the next byte goes */
static size_t encode_securities_order_filled_plus_quote_mm_lp_quotes_included5_level_message(const SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded5LevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  wire[at++] = record->price_change_against_previous_day;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->a_price_change_against_the_previous_day[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->accumulated_trading_value[i]; }
  wire[at++] = record->final_ask_bid_type_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_holding_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_1_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_1_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_1_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_1_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_2_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_2_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_2_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_2_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_3_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_3_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_3_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_3_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_4_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_4_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_4_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_4_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_5_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_5_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_5_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_5_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_ask_volume_level_10[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_bid_volume_level_10[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Securities Order Filled Plus Quote Mm Lp Quotes Included 5 Level Message off the wire: 402 bytes from at, returning where the next byte lies */
static size_t decode_securities_order_filled_plus_quote_mm_lp_quotes_included5_level_message(SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded5LevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  record->price_change_against_previous_day = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->a_price_change_against_the_previous_day[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->accumulated_trading_value[i] = wire[at++]; }
  record->final_ask_bid_type_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->lp_holding_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_ask_volume_level_10[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_bid_volume_level_10[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Securities Order Filled Plus Quote Mm Lp Quotes Included 5 Level Message is what was written, byte for byte */
static void equal_securities_order_filled_plus_quote_mm_lp_quotes_included5_level_message(const SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded5LevelMessage *read, const SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded5LevelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  assert(read->price_change_against_previous_day == written->price_change_against_previous_day);
  for (size_t i = 0; i < 8; i++) { assert(read->a_price_change_against_the_previous_day[i] == written->a_price_change_against_the_previous_day[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->accumulated_trading_value[i] == written->accumulated_trading_value[i]); }
  assert(read->final_ask_bid_type_code == written->final_ask_bid_type_code);
  for (size_t i = 0; i < 8; i++) { assert(read->lp_holding_quantity[i] == written->lp_holding_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_1_volume[i] == written->ask_level_1_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_1_volume[i] == written->bid_level_1_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_1_volume[i] == written->lp_ask_level_1_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_1_volume[i] == written->lp_bid_level_1_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_2_volume[i] == written->ask_level_2_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_2_volume[i] == written->bid_level_2_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_2_volume[i] == written->lp_ask_level_2_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_2_volume[i] == written->lp_bid_level_2_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_3_volume[i] == written->ask_level_3_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_3_volume[i] == written->bid_level_3_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_3_volume[i] == written->lp_ask_level_3_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_3_volume[i] == written->lp_bid_level_3_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_4_volume[i] == written->ask_level_4_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_4_volume[i] == written->bid_level_4_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_4_volume[i] == written->lp_ask_level_4_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_4_volume[i] == written->lp_bid_level_4_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_5_volume[i] == written->ask_level_5_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_5_volume[i] == written->bid_level_5_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_5_volume[i] == written->lp_ask_level_5_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_5_volume[i] == written->lp_bid_level_5_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_ask_volume_level_10[i] == written->total_ask_volume_level_10[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_bid_volume_level_10[i] == written->total_bid_volume_level_10[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mid_price[i] == written->mid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] == written->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] == written->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Securities Order Filled Plus Quote Mm Lp Quotes Included 5 Level Message: written and read back, then read and written back */
static void check_securities_order_filled_plus_quote_mm_lp_quotes_included5_level_message(void) {
  SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded5LevelMessage sent;
  SecuritiesOrderFilledPlusQuoteMmLpQuotesIncluded5LevelMessage got;
  uint8_t wire[402];
  uint8_t again[402];

  any_securities_order_filled_plus_quote_mm_lp_quotes_included5_level_message(&sent);
  assert(encode_securities_order_filled_plus_quote_mm_lp_quotes_included5_level_message(&sent, wire, 0) == 402);
  assert(decode_securities_order_filled_plus_quote_mm_lp_quotes_included5_level_message(&got, wire, 0) == 402);
  equal_securities_order_filled_plus_quote_mm_lp_quotes_included5_level_message(&got, &sent);

  for (size_t i = 0; i < 402; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_order_filled_plus_quote_mm_lp_quotes_included5_level_message(&got, wire, 0) == 402);
  assert(encode_securities_order_filled_plus_quote_mm_lp_quotes_included5_level_message(&got, again, 0) == 402);
  for (size_t i = 0; i < 402; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Operation Ts Plus Quote Mm Lp Quotes Included 5 Level Message: 355 bytes ---- */

/* Market Operation TS with Best Order on NXT trading items - MM/LP Quotes Included The data is provided per an issue if a Market Operation Trading session event occurs and Best Order changes. * 5 Level. */
typedef struct {
  uint8_t message_sequence_number[4];                                   /* bytes 0 to 3 */
  uint8_t board_id[2];                                                  /* bytes 4 to 5 */
  uint8_t session_id[2];                                                /* bytes 6 to 7 */
  uint8_t isin_code[12];                                                /* bytes 8 to 19 */
  uint8_t a_designated_number_for_an_issue_from_krx[4];                 /* bytes 20 to 23 */
  uint8_t processing_time_of_trading_system[12];                        /* bytes 24 to 35 */
  uint8_t board_event_id[3];                                            /* bytes 36 to 38 */
  uint8_t start_time_of_a_board_event[9];                               /* bytes 39 to 47 */
  uint8_t board_event_group_code[4];                                    /* bytes 48 to 51 */
  uint8_t trading_halt_reason_code[3];                                  /* bytes 52 to 54 */
  uint8_t ask_level_1_price[8];                                         /* bytes 55 to 62 */
  uint8_t bid_level_1_price[8];                                         /* bytes 63 to 70 */
  uint8_t ask_level_1_volume[8];                                        /* bytes 71 to 78 */
  uint8_t bid_level_1_volume[8];                                        /* bytes 79 to 86 */
  uint8_t lp_ask_level_1_volume[8];                                     /* bytes 87 to 94 */
  uint8_t lp_bid_level_1_volume[8];                                     /* bytes 95 to 102 */
  uint8_t ask_level_2_price[8];                                         /* bytes 103 to 110 */
  uint8_t bid_level_2_price[8];                                         /* bytes 111 to 118 */
  uint8_t ask_level_2_volume[8];                                        /* bytes 119 to 126 */
  uint8_t bid_level_2_volume[8];                                        /* bytes 127 to 134 */
  uint8_t lp_ask_level_2_volume[8];                                     /* bytes 135 to 142 */
  uint8_t lp_bid_level_2_volume[8];                                     /* bytes 143 to 150 */
  uint8_t ask_level_3_price[8];                                         /* bytes 151 to 158 */
  uint8_t bid_level_3_price[8];                                         /* bytes 159 to 166 */
  uint8_t ask_level_3_volume[8];                                        /* bytes 167 to 174 */
  uint8_t bid_level_3_volume[8];                                        /* bytes 175 to 182 */
  uint8_t lp_ask_level_3_volume[8];                                     /* bytes 183 to 190 */
  uint8_t lp_bid_level_3_volume[8];                                     /* bytes 191 to 198 */
  uint8_t ask_level_4_price[8];                                         /* bytes 199 to 206 */
  uint8_t bid_level_4_price[8];                                         /* bytes 207 to 214 */
  uint8_t ask_level_4_volume[8];                                        /* bytes 215 to 222 */
  uint8_t bid_level_4_volume[8];                                        /* bytes 223 to 230 */
  uint8_t lp_ask_level_4_volume[8];                                     /* bytes 231 to 238 */
  uint8_t lp_bid_level_4_volume[8];                                     /* bytes 239 to 246 */
  uint8_t ask_level_5_price[8];                                         /* bytes 247 to 254 */
  uint8_t bid_level_5_price[8];                                         /* bytes 255 to 262 */
  uint8_t ask_level_5_volume[8];                                        /* bytes 263 to 270 */
  uint8_t bid_level_5_volume[8];                                        /* bytes 271 to 278 */
  uint8_t lp_ask_level_5_volume[8];                                     /* bytes 279 to 286 */
  uint8_t lp_bid_level_5_volume[8];                                     /* bytes 287 to 294 */
  uint8_t total_ask_volume_level_10[8];                                 /* bytes 295 to 302 */
  uint8_t total_bid_volume_level_10[8];                                 /* bytes 303 to 310 */
  uint8_t estimated_trading_price[8];                                   /* bytes 311 to 318 */
  uint8_t estimated_trading_volume[8];                                  /* bytes 319 to 326 */
  uint8_t mid_price[8];                                                 /* bytes 327 to 334 */
  uint8_t total_mid_price_ask_volume_total_ask_volume_on_mid_price[8];  /* bytes 335 to 342 */
  uint8_t total_mid_price_bid_volume_total_bid_volume_on_mid_price[8];  /* bytes 343 to 350 */
  uint8_t end_keyword[4];                                               /* bytes 351 to 354 */
} MarketOperationTsPlusQuoteMmLpQuotesIncluded5LevelMessage;

/* any Market Operation Ts Plus Quote Mm Lp Quotes Included 5 Level Message at all: every byte one the checker chooses */
static void any_market_operation_ts_plus_quote_mm_lp_quotes_included5_level_message(MarketOperationTsPlusQuoteMmLpQuotesIncluded5LevelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->board_event_group_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_ask_volume_level_10[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_bid_volume_level_10[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->estimated_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->estimated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Market Operation Ts Plus Quote Mm Lp Quotes Included 5 Level Message to the wire: 355 bytes from at, returning where the next byte goes */
static size_t encode_market_operation_ts_plus_quote_mm_lp_quotes_included5_level_message(const MarketOperationTsPlusQuoteMmLpQuotesIncluded5LevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->board_event_id[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->start_time_of_a_board_event[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->board_event_group_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_halt_reason_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_1_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_1_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_1_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_1_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_2_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_2_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_2_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_2_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_3_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_3_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_3_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_3_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_4_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_4_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_4_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_4_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_5_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_5_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_5_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_5_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_ask_volume_level_10[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_bid_volume_level_10[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->estimated_trading_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->estimated_trading_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Market Operation Ts Plus Quote Mm Lp Quotes Included 5 Level Message off the wire: 355 bytes from at, returning where the next byte lies */
static size_t decode_market_operation_ts_plus_quote_mm_lp_quotes_included5_level_message(MarketOperationTsPlusQuoteMmLpQuotesIncluded5LevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->board_event_group_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_ask_volume_level_10[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_bid_volume_level_10[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->estimated_trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->estimated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Market Operation Ts Plus Quote Mm Lp Quotes Included 5 Level Message is what was written, byte for byte */
static void equal_market_operation_ts_plus_quote_mm_lp_quotes_included5_level_message(const MarketOperationTsPlusQuoteMmLpQuotesIncluded5LevelMessage *read, const MarketOperationTsPlusQuoteMmLpQuotesIncluded5LevelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->board_event_id[i] == written->board_event_id[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->start_time_of_a_board_event[i] == written->start_time_of_a_board_event[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->board_event_group_code[i] == written->board_event_group_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trading_halt_reason_code[i] == written->trading_halt_reason_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_1_volume[i] == written->ask_level_1_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_1_volume[i] == written->bid_level_1_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_1_volume[i] == written->lp_ask_level_1_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_1_volume[i] == written->lp_bid_level_1_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_2_volume[i] == written->ask_level_2_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_2_volume[i] == written->bid_level_2_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_2_volume[i] == written->lp_ask_level_2_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_2_volume[i] == written->lp_bid_level_2_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_3_volume[i] == written->ask_level_3_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_3_volume[i] == written->bid_level_3_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_3_volume[i] == written->lp_ask_level_3_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_3_volume[i] == written->lp_bid_level_3_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_4_volume[i] == written->ask_level_4_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_4_volume[i] == written->bid_level_4_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_4_volume[i] == written->lp_ask_level_4_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_4_volume[i] == written->lp_bid_level_4_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_5_volume[i] == written->ask_level_5_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_5_volume[i] == written->bid_level_5_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_5_volume[i] == written->lp_ask_level_5_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_5_volume[i] == written->lp_bid_level_5_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_ask_volume_level_10[i] == written->total_ask_volume_level_10[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_bid_volume_level_10[i] == written->total_bid_volume_level_10[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->estimated_trading_price[i] == written->estimated_trading_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->estimated_trading_volume[i] == written->estimated_trading_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mid_price[i] == written->mid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] == written->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] == written->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Market Operation Ts Plus Quote Mm Lp Quotes Included 5 Level Message: written and read back, then read and written back */
static void check_market_operation_ts_plus_quote_mm_lp_quotes_included5_level_message(void) {
  MarketOperationTsPlusQuoteMmLpQuotesIncluded5LevelMessage sent;
  MarketOperationTsPlusQuoteMmLpQuotesIncluded5LevelMessage got;
  uint8_t wire[355];
  uint8_t again[355];

  any_market_operation_ts_plus_quote_mm_lp_quotes_included5_level_message(&sent);
  assert(encode_market_operation_ts_plus_quote_mm_lp_quotes_included5_level_message(&sent, wire, 0) == 355);
  assert(decode_market_operation_ts_plus_quote_mm_lp_quotes_included5_level_message(&got, wire, 0) == 355);
  equal_market_operation_ts_plus_quote_mm_lp_quotes_included5_level_message(&got, &sent);

  for (size_t i = 0; i < 355; i++) { wire[i] = arbitrary(); }
  assert(decode_market_operation_ts_plus_quote_mm_lp_quotes_included5_level_message(&got, wire, 0) == 355);
  assert(encode_market_operation_ts_plus_quote_mm_lp_quotes_included5_level_message(&got, again, 0) == 355);
  for (size_t i = 0; i < 355; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Order Filled Message: 138 bytes ------------------------------ */

/* Securities_Order Filled Order Filled Data on NXT trading items provided. */
typedef struct {
  uint8_t message_sequence_number[4];                    /* bytes 0 to 3 */
  uint8_t board_id[2];                                   /* bytes 4 to 5 */
  uint8_t session_id[2];                                 /* bytes 6 to 7 */
  uint8_t isin_code[12];                                 /* bytes 8 to 19 */
  uint8_t a_designated_number_for_an_issue_from_krx[4];  /* bytes 20 to 23 */
  uint8_t processing_time_of_trading_system[12];         /* bytes 24 to 35 */
  uint8_t price_change_against_previous_day;             /* byte 36 */
  uint8_t a_price_change_against_the_previous_day[8];    /* bytes 37 to 44 */
  uint8_t trading_price[8];                              /* bytes 45 to 52 */
  uint8_t trading_volume[8];                             /* bytes 53 to 60 */
  uint8_t opening_price[8];                              /* bytes 61 to 68 */
  uint8_t todays_high[8];                                /* bytes 69 to 76 */
  uint8_t todays_low[8];                                 /* bytes 77 to 84 */
  uint8_t accumulated_trading_volume[8];                 /* bytes 85 to 92 */
  uint8_t accumulated_trading_value[16];                 /* bytes 93 to 108 */
  uint8_t final_ask_bid_type_code;                       /* byte 109 */
  uint8_t lp_holding_quantity[8];                        /* bytes 110 to 117 */
  uint8_t the_best_ask[8];                               /* bytes 118 to 125 */
  uint8_t the_best_bid[8];                               /* bytes 126 to 133 */
  uint8_t end_keyword[4];                                /* bytes 134 to 137 */
} SecuritiesOrderFilledMessage;

/* any Securities Order Filled Message at all: every byte one the checker chooses */
static void any_securities_order_filled_message(SecuritiesOrderFilledMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  record->price_change_against_previous_day = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->a_price_change_against_the_previous_day[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->accumulated_trading_value[i] = arbitrary(); }
  record->final_ask_bid_type_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->lp_holding_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->the_best_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->the_best_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Securities Order Filled Message to the wire: 138 bytes from at, returning where the next byte goes */
static size_t encode_securities_order_filled_message(const SecuritiesOrderFilledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  wire[at++] = record->price_change_against_previous_day;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->a_price_change_against_the_previous_day[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->accumulated_trading_value[i]; }
  wire[at++] = record->final_ask_bid_type_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_holding_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->the_best_ask[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->the_best_bid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Securities Order Filled Message off the wire: 138 bytes from at, returning where the next byte lies */
static size_t decode_securities_order_filled_message(SecuritiesOrderFilledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  record->price_change_against_previous_day = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->a_price_change_against_the_previous_day[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->accumulated_trading_value[i] = wire[at++]; }
  record->final_ask_bid_type_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->lp_holding_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->the_best_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->the_best_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Securities Order Filled Message is what was written, byte for byte */
static void equal_securities_order_filled_message(const SecuritiesOrderFilledMessage *read, const SecuritiesOrderFilledMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  assert(read->price_change_against_previous_day == written->price_change_against_previous_day);
  for (size_t i = 0; i < 8; i++) { assert(read->a_price_change_against_the_previous_day[i] == written->a_price_change_against_the_previous_day[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->accumulated_trading_value[i] == written->accumulated_trading_value[i]); }
  assert(read->final_ask_bid_type_code == written->final_ask_bid_type_code);
  for (size_t i = 0; i < 8; i++) { assert(read->lp_holding_quantity[i] == written->lp_holding_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->the_best_ask[i] == written->the_best_ask[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->the_best_bid[i] == written->the_best_bid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Securities Order Filled Message: written and read back, then read and written back */
static void check_securities_order_filled_message(void) {
  SecuritiesOrderFilledMessage sent;
  SecuritiesOrderFilledMessage got;
  uint8_t wire[138];
  uint8_t again[138];

  any_securities_order_filled_message(&sent);
  assert(encode_securities_order_filled_message(&sent, wire, 0) == 138);
  assert(decode_securities_order_filled_message(&got, wire, 0) == 138);
  equal_securities_order_filled_message(&got, &sent);

  for (size_t i = 0; i < 138; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_order_filled_message(&got, wire, 0) == 138);
  assert(encode_securities_order_filled_message(&got, again, 0) == 138);
  for (size_t i = 0; i < 138; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Operation Ts Message: 59 bytes ----------------------------------- */

/* The data is provided per an issue if a Market Operation Trading session event occurs. */
typedef struct {
  uint8_t message_sequence_number[4];                    /* bytes 0 to 3 */
  uint8_t board_id[2];                                   /* bytes 4 to 5 */
  uint8_t session_id[2];                                 /* bytes 6 to 7 */
  uint8_t isin_code[12];                                 /* bytes 8 to 19 */
  uint8_t a_designated_number_for_an_issue_from_krx[4];  /* bytes 20 to 23 */
  uint8_t processing_time_of_trading_system[12];         /* bytes 24 to 35 */
  uint8_t board_event_id[3];                             /* bytes 36 to 38 */
  uint8_t start_time_of_a_board_event[9];                /* bytes 39 to 47 */
  uint8_t board_event_group_code[4];                     /* bytes 48 to 51 */
  uint8_t trading_halt_reason_code[3];                   /* bytes 52 to 54 */
  uint8_t end_keyword[4];                                /* bytes 55 to 58 */
} MarketOperationTsMessage;

/* any Market Operation Ts Message at all: every byte one the checker chooses */
static void any_market_operation_ts_message(MarketOperationTsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->board_event_group_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Market Operation Ts Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_market_operation_ts_message(const MarketOperationTsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->board_event_id[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->start_time_of_a_board_event[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->board_event_group_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_halt_reason_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Market Operation Ts Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_market_operation_ts_message(MarketOperationTsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->board_event_group_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Market Operation Ts Message is what was written, byte for byte */
static void equal_market_operation_ts_message(const MarketOperationTsMessage *read, const MarketOperationTsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->board_event_id[i] == written->board_event_id[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->start_time_of_a_board_event[i] == written->start_time_of_a_board_event[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->board_event_group_code[i] == written->board_event_group_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trading_halt_reason_code[i] == written->trading_halt_reason_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Market Operation Ts Message: written and read back, then read and written back */
static void check_market_operation_ts_message(void) {
  MarketOperationTsMessage sent;
  MarketOperationTsMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_market_operation_ts_message(&sent);
  assert(encode_market_operation_ts_message(&sent, wire, 0) == 59);
  assert(decode_market_operation_ts_message(&got, wire, 0) == 59);
  equal_market_operation_ts_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_market_operation_ts_message(&got, wire, 0) == 59);
  assert(encode_market_operation_ts_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- Issue Closing Message: 83 bytes ----------------------------------------- */

/* The data is provided in case of an issue closing per board. */
typedef struct {
  uint8_t message_sequence_number[4];                                               /* bytes 0 to 3 */
  uint8_t board_id[2];                                                              /* bytes 4 to 5 */
  uint8_t isin_code[12];                                                            /* bytes 6 to 17 */
  uint8_t a_designated_number_for_an_issue_from_krx[4];                             /* bytes 18 to 21 */
  uint8_t closing_price[8];                                                         /* bytes 22 to 29 */
  uint8_t closing_price_type_code;                                                  /* byte 30 */
  uint8_t upper_limit_price_on_the_single_price_trade_in_the_off_hours_session[8];  /* bytes 31 to 38 */
  uint8_t lower_limit_price_on_the_single_price_trade_in_the_off_hours_session[8];  /* bytes 39 to 46 */
  uint8_t closing_price_weighted_stock_price_average[8];                            /* bytes 47 to 54 */
  uint8_t closing_price_base_price_of_buy_in[8];                                    /* bytes 55 to 62 */
  uint8_t closing_price_upper_limit_of_buy_in[8];                                   /* bytes 63 to 70 */
  uint8_t closing_price_lower_limit_of_buy_in[8];                                   /* bytes 71 to 78 */
  uint8_t end_keyword[4];                                                           /* bytes 79 to 82 */
} IssueClosingMessage;

/* any Issue Closing Message at all: every byte one the checker chooses */
static void any_issue_closing_message(IssueClosingMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = arbitrary(); }
  record->closing_price_type_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->upper_limit_price_on_the_single_price_trade_in_the_off_hours_session[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower_limit_price_on_the_single_price_trade_in_the_off_hours_session[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price_weighted_stock_price_average[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price_base_price_of_buy_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price_upper_limit_of_buy_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price_lower_limit_of_buy_in[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Issue Closing Message to the wire: 83 bytes from at, returning where the next byte goes */
static size_t encode_issue_closing_message(const IssueClosingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price[i]; }
  wire[at++] = record->closing_price_type_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper_limit_price_on_the_single_price_trade_in_the_off_hours_session[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_limit_price_on_the_single_price_trade_in_the_off_hours_session[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price_weighted_stock_price_average[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price_base_price_of_buy_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price_upper_limit_of_buy_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price_lower_limit_of_buy_in[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Issue Closing Message off the wire: 83 bytes from at, returning where the next byte lies */
static size_t decode_issue_closing_message(IssueClosingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = wire[at++]; }
  record->closing_price_type_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->upper_limit_price_on_the_single_price_trade_in_the_off_hours_session[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower_limit_price_on_the_single_price_trade_in_the_off_hours_session[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price_weighted_stock_price_average[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price_base_price_of_buy_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price_upper_limit_of_buy_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price_lower_limit_of_buy_in[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Issue Closing Message is what was written, byte for byte */
static void equal_issue_closing_message(const IssueClosingMessage *read, const IssueClosingMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  assert(read->closing_price_type_code == written->closing_price_type_code);
  for (size_t i = 0; i < 8; i++) { assert(read->upper_limit_price_on_the_single_price_trade_in_the_off_hours_session[i] == written->upper_limit_price_on_the_single_price_trade_in_the_off_hours_session[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower_limit_price_on_the_single_price_trade_in_the_off_hours_session[i] == written->lower_limit_price_on_the_single_price_trade_in_the_off_hours_session[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price_weighted_stock_price_average[i] == written->closing_price_weighted_stock_price_average[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price_base_price_of_buy_in[i] == written->closing_price_base_price_of_buy_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price_upper_limit_of_buy_in[i] == written->closing_price_upper_limit_of_buy_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price_lower_limit_of_buy_in[i] == written->closing_price_lower_limit_of_buy_in[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Issue Closing Message: written and read back, then read and written back */
static void check_issue_closing_message(void) {
  IssueClosingMessage sent;
  IssueClosingMessage got;
  uint8_t wire[83];
  uint8_t again[83];

  any_issue_closing_message(&sent);
  assert(encode_issue_closing_message(&sent, wire, 0) == 83);
  assert(decode_issue_closing_message(&got, wire, 0) == 83);
  equal_issue_closing_message(&got, &sent);

  for (size_t i = 0; i < 83; i++) { wire[i] = arbitrary(); }
  assert(decode_issue_closing_message(&got, wire, 0) == 83);
  assert(encode_issue_closing_message(&got, again, 0) == 83);
  for (size_t i = 0; i < 83; i++) { assert(again[i] == wire[i]); }
}

/* ---- Triggering Removing Vi Message: 89 bytes -------------------------------- */

/* Triggering/removing VI (Volatility Interruption). */
typedef struct {
  uint8_t message_sequence_number[4];                    /* bytes 0 to 3 */
  uint8_t board_id[2];                                   /* bytes 4 to 5 */
  uint8_t isin_code[12];                                 /* bytes 6 to 17 */
  uint8_t a_designated_number_for_an_issue_from_krx[4];  /* bytes 18 to 21 */
  uint8_t processing_time_of_trading_system[12];         /* bytes 22 to 33 */
  uint8_t the_time_ending_vi[9];                         /* bytes 34 to 42 */
  uint8_t vi_status_code;                                /* byte 43 */
  uint8_t vi_type_code;                                  /* byte 44 */
  uint8_t a_base_price_to_trigger_static_vi[8];          /* bytes 45 to 52 */
  uint8_t a_base_price_to_trigger_dynamic_vi[8];         /* bytes 53 to 60 */
  uint8_t vi_triggering_price[8];                        /* bytes 61 to 68 */
  uint8_t disparate_ratio_to_trigger_static_vi[8];       /* bytes 69 to 76 */
  uint8_t disparate_ratio_to_trigger_dynamic_vi[8];      /* bytes 77 to 84 */
  uint8_t end_keyword[4];                                /* bytes 85 to 88 */
} TriggeringRemovingViMessage;

/* any Triggering Removing Vi Message at all: every byte one the checker chooses */
static void any_triggering_removing_vi_message(TriggeringRemovingViMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->the_time_ending_vi[i] = arbitrary(); }
  record->vi_status_code = arbitrary();
  record->vi_type_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->a_base_price_to_trigger_static_vi[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->a_base_price_to_trigger_dynamic_vi[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vi_triggering_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->disparate_ratio_to_trigger_static_vi[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->disparate_ratio_to_trigger_dynamic_vi[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Triggering Removing Vi Message to the wire: 89 bytes from at, returning where the next byte goes */
static size_t encode_triggering_removing_vi_message(const TriggeringRemovingViMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->the_time_ending_vi[i]; }
  wire[at++] = record->vi_status_code;
  wire[at++] = record->vi_type_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->a_base_price_to_trigger_static_vi[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->a_base_price_to_trigger_dynamic_vi[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vi_triggering_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->disparate_ratio_to_trigger_static_vi[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->disparate_ratio_to_trigger_dynamic_vi[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Triggering Removing Vi Message off the wire: 89 bytes from at, returning where the next byte lies */
static size_t decode_triggering_removing_vi_message(TriggeringRemovingViMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->the_time_ending_vi[i] = wire[at++]; }
  record->vi_status_code = wire[at++];
  record->vi_type_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->a_base_price_to_trigger_static_vi[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->a_base_price_to_trigger_dynamic_vi[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vi_triggering_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->disparate_ratio_to_trigger_static_vi[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->disparate_ratio_to_trigger_dynamic_vi[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Triggering Removing Vi Message is what was written, byte for byte */
static void equal_triggering_removing_vi_message(const TriggeringRemovingViMessage *read, const TriggeringRemovingViMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->the_time_ending_vi[i] == written->the_time_ending_vi[i]); }
  assert(read->vi_status_code == written->vi_status_code);
  assert(read->vi_type_code == written->vi_type_code);
  for (size_t i = 0; i < 8; i++) { assert(read->a_base_price_to_trigger_static_vi[i] == written->a_base_price_to_trigger_static_vi[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->a_base_price_to_trigger_dynamic_vi[i] == written->a_base_price_to_trigger_dynamic_vi[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vi_triggering_price[i] == written->vi_triggering_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->disparate_ratio_to_trigger_static_vi[i] == written->disparate_ratio_to_trigger_static_vi[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->disparate_ratio_to_trigger_dynamic_vi[i] == written->disparate_ratio_to_trigger_dynamic_vi[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Triggering Removing Vi Message: written and read back, then read and written back */
static void check_triggering_removing_vi_message(void) {
  TriggeringRemovingViMessage sent;
  TriggeringRemovingViMessage got;
  uint8_t wire[89];
  uint8_t again[89];

  any_triggering_removing_vi_message(&sent);
  assert(encode_triggering_removing_vi_message(&sent, wire, 0) == 89);
  assert(decode_triggering_removing_vi_message(&got, wire, 0) == 89);
  equal_triggering_removing_vi_message(&got, &sent);

  for (size_t i = 0; i < 89; i++) { wire[i] = arbitrary(); }
  assert(decode_triggering_removing_vi_message(&got, wire, 0) == 89);
  assert(encode_triggering_removing_vi_message(&got, again, 0) == 89);
  for (size_t i = 0; i < 89; i++) { assert(again[i] == wire[i]); }
}

/* ---- Closing Price Trading Quote Message: 42 bytes --------------------------- */

/* Total Ask/Bid volume per Issue on Closing Price Trade. */
typedef struct {
  uint8_t message_sequence_number[4];                    /* bytes 0 to 3 */
  uint8_t board_id[2];                                   /* bytes 4 to 5 */
  uint8_t isin_code[12];                                 /* bytes 6 to 17 */
  uint8_t a_designated_number_for_an_issue_from_krx[4];  /* bytes 18 to 21 */
  uint8_t total_ask_volume[8];                           /* bytes 22 to 29 */
  uint8_t total_bid_volume[8];                           /* bytes 30 to 37 */
  uint8_t end_keyword[4];                                /* bytes 38 to 41 */
} ClosingPriceTradingQuoteMessage;

/* any Closing Price Trading Quote Message at all: every byte one the checker chooses */
static void any_closing_price_trading_quote_message(ClosingPriceTradingQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Closing Price Trading Quote Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_closing_price_trading_quote_message(const ClosingPriceTradingQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_ask_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_bid_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Closing Price Trading Quote Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_closing_price_trading_quote_message(ClosingPriceTradingQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_bid_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Closing Price Trading Quote Message is what was written, byte for byte */
static void equal_closing_price_trading_quote_message(const ClosingPriceTradingQuoteMessage *read, const ClosingPriceTradingQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_ask_volume[i] == written->total_ask_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_bid_volume[i] == written->total_bid_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Closing Price Trading Quote Message: written and read back, then read and written back */
static void check_closing_price_trading_quote_message(void) {
  ClosingPriceTradingQuoteMessage sent;
  ClosingPriceTradingQuoteMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_closing_price_trading_quote_message(&sent);
  assert(encode_closing_price_trading_quote_message(&sent, wire, 0) == 42);
  assert(decode_closing_price_trading_quote_message(&got, wire, 0) == 42);
  equal_closing_price_trading_quote_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_closing_price_trading_quote_message(&got, wire, 0) == 42);
  assert(encode_closing_price_trading_quote_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_polling_data_message();
  check_securities_quote_mm_lp_quotes_included5_level_message();
  check_securities_order_filled_plus_quote_mm_lp_quotes_included5_level_message();
  check_market_operation_ts_plus_quote_mm_lp_quotes_included5_level_message();
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
