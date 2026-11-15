// nextrade/etpcommon/Nextrade_EtpCommon_NxtBinary_v2_12.c
/*
 * Nextrade Nextrade Etp Market Data Common
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

/* ---- Securities Quote Mm Lp Quotes Included 10 Level Message: 576 bytes ------ */

/* Securities_Quote (MM/LP Quotes Included, 10 Level) Best Order Data on NXT Trading Items provided - MM/LP Quotes Included * 10 Level Best Order on Ask/Bid. */
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
  uint8_t ask_level_6_price[8];                                         /* bytes 276 to 283 */
  uint8_t bid_level_6_price[8];                                         /* bytes 284 to 291 */
  uint8_t ask_level_6_volume[8];                                        /* bytes 292 to 299 */
  uint8_t bid_level_6_volume[8];                                        /* bytes 300 to 307 */
  uint8_t lp_ask_level_6_volume[8];                                     /* bytes 308 to 315 */
  uint8_t lp_bid_level_6_volume[8];                                     /* bytes 316 to 323 */
  uint8_t ask_level_7_price[8];                                         /* bytes 324 to 331 */
  uint8_t bid_level_7_price[8];                                         /* bytes 332 to 339 */
  uint8_t ask_level_7_volume[8];                                        /* bytes 340 to 347 */
  uint8_t bid_level_7_volume[8];                                        /* bytes 348 to 355 */
  uint8_t lp_ask_level_7_volume[8];                                     /* bytes 356 to 363 */
  uint8_t lp_bid_level_7_volume[8];                                     /* bytes 364 to 371 */
  uint8_t ask_level_8_price[8];                                         /* bytes 372 to 379 */
  uint8_t bid_level_8_price[8];                                         /* bytes 380 to 387 */
  uint8_t ask_level_8_volume[8];                                        /* bytes 388 to 395 */
  uint8_t bid_level_8_volume[8];                                        /* bytes 396 to 403 */
  uint8_t lp_ask_level_8_volume[8];                                     /* bytes 404 to 411 */
  uint8_t lp_bid_level_8_volume[8];                                     /* bytes 412 to 419 */
  uint8_t ask_level_9_price[8];                                         /* bytes 420 to 427 */
  uint8_t bid_level_9_price[8];                                         /* bytes 428 to 435 */
  uint8_t ask_level_9_volume[8];                                        /* bytes 436 to 443 */
  uint8_t bid_level_9_volume[8];                                        /* bytes 444 to 451 */
  uint8_t lp_ask_level_9_volume[8];                                     /* bytes 452 to 459 */
  uint8_t lp_bid_level_9_volume[8];                                     /* bytes 460 to 467 */
  uint8_t ask_level_10_price[8];                                        /* bytes 468 to 475 */
  uint8_t bid_level_10_price[8];                                        /* bytes 476 to 483 */
  uint8_t ask_level_10_volume[8];                                       /* bytes 484 to 491 */
  uint8_t bid_level_10_volume[8];                                       /* bytes 492 to 499 */
  uint8_t lp_ask_level_10_volume[8];                                    /* bytes 500 to 507 */
  uint8_t lp_bid_level_10_volume[8];                                    /* bytes 508 to 515 */
  uint8_t total_ask_volume[8];                                          /* bytes 516 to 523 */
  uint8_t total_bid_volume[8];                                          /* bytes 524 to 531 */
  uint8_t estimated_trading_price[8];                                   /* bytes 532 to 539 */
  uint8_t estimated_trading_volume[8];                                  /* bytes 540 to 547 */
  uint8_t mid_price[8];                                                 /* bytes 548 to 555 */
  uint8_t total_mid_price_ask_volume_total_ask_volume_on_mid_price[8];  /* bytes 556 to 563 */
  uint8_t total_mid_price_bid_volume_total_bid_volume_on_mid_price[8];  /* bytes 564 to 571 */
  uint8_t end_keyword[4];                                               /* bytes 572 to 575 */
} SecuritiesQuoteMmLpQuotesIncluded10LevelMessage;

/* any Securities Quote Mm Lp Quotes Included 10 Level Message at all: every byte one the checker chooses */
static void any_securities_quote_mm_lp_quotes_included10_level_message(SecuritiesQuoteMmLpQuotesIncluded10LevelMessage *record) {
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
  for (size_t i = 0; i < 8; i++) { record->ask_level_6_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_6_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_7_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_7_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_8_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_8_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_9_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_9_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_10_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_10_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->estimated_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->estimated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Securities Quote Mm Lp Quotes Included 10 Level Message to the wire: 576 bytes from at, returning where the next byte goes */
static size_t encode_securities_quote_mm_lp_quotes_included10_level_message(const SecuritiesQuoteMmLpQuotesIncluded10LevelMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_6_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_6_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_6_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_6_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_6_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_6_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_7_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_7_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_7_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_7_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_7_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_7_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_8_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_8_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_8_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_8_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_8_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_8_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_9_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_9_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_9_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_9_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_9_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_9_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_10_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_10_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_10_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_10_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_10_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_10_volume[i]; }
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

/* Securities Quote Mm Lp Quotes Included 10 Level Message off the wire: 576 bytes from at, returning where the next byte lies */
static size_t decode_securities_quote_mm_lp_quotes_included10_level_message(SecuritiesQuoteMmLpQuotesIncluded10LevelMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 8; i++) { record->ask_level_6_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_6_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_7_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_7_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_8_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_8_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_9_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_9_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_10_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_10_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_10_volume[i] = wire[at++]; }
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

/* what was read of Securities Quote Mm Lp Quotes Included 10 Level Message is what was written, byte for byte */
static void equal_securities_quote_mm_lp_quotes_included10_level_message(const SecuritiesQuoteMmLpQuotesIncluded10LevelMessage *read, const SecuritiesQuoteMmLpQuotesIncluded10LevelMessage *written) {
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
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_6_price[i] == written->ask_level_6_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_6_price[i] == written->bid_level_6_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_6_volume[i] == written->ask_level_6_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_6_volume[i] == written->bid_level_6_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_6_volume[i] == written->lp_ask_level_6_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_6_volume[i] == written->lp_bid_level_6_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_7_price[i] == written->ask_level_7_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_7_price[i] == written->bid_level_7_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_7_volume[i] == written->ask_level_7_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_7_volume[i] == written->bid_level_7_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_7_volume[i] == written->lp_ask_level_7_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_7_volume[i] == written->lp_bid_level_7_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_8_price[i] == written->ask_level_8_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_8_price[i] == written->bid_level_8_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_8_volume[i] == written->ask_level_8_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_8_volume[i] == written->bid_level_8_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_8_volume[i] == written->lp_ask_level_8_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_8_volume[i] == written->lp_bid_level_8_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_9_price[i] == written->ask_level_9_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_9_price[i] == written->bid_level_9_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_9_volume[i] == written->ask_level_9_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_9_volume[i] == written->bid_level_9_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_9_volume[i] == written->lp_ask_level_9_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_9_volume[i] == written->lp_bid_level_9_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_10_price[i] == written->ask_level_10_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_10_price[i] == written->bid_level_10_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_10_volume[i] == written->ask_level_10_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_10_volume[i] == written->bid_level_10_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_10_volume[i] == written->lp_ask_level_10_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_10_volume[i] == written->lp_bid_level_10_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_ask_volume[i] == written->total_ask_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_bid_volume[i] == written->total_bid_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->estimated_trading_price[i] == written->estimated_trading_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->estimated_trading_volume[i] == written->estimated_trading_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mid_price[i] == written->mid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] == written->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] == written->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Securities Quote Mm Lp Quotes Included 10 Level Message: written and read back, then read and written back */
static void check_securities_quote_mm_lp_quotes_included10_level_message(void) {
  SecuritiesQuoteMmLpQuotesIncluded10LevelMessage sent;
  SecuritiesQuoteMmLpQuotesIncluded10LevelMessage got;
  uint8_t wire[576];
  uint8_t again[576];

  any_securities_quote_mm_lp_quotes_included10_level_message(&sent);
  assert(encode_securities_quote_mm_lp_quotes_included10_level_message(&sent, wire, 0) == 576);
  assert(decode_securities_quote_mm_lp_quotes_included10_level_message(&got, wire, 0) == 576);
  equal_securities_quote_mm_lp_quotes_included10_level_message(&got, &sent);

  for (size_t i = 0; i < 576; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_quote_mm_lp_quotes_included10_level_message(&got, wire, 0) == 576);
  assert(encode_securities_quote_mm_lp_quotes_included10_level_message(&got, again, 0) == 576);
  for (size_t i = 0; i < 576; i++) { assert(again[i] == wire[i]); }
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

/* ---- Equities Snapshot Mm Lp Quotes Included 10 Level Message: 654 bytes ----- */

/* Snapshot and final status are provided with certain intervals per issue and board - MM/LP Quotes Included * 10 Level Best Order on Ask/Bid. */
typedef struct {
  uint8_t board_id[2];                                                  /* bytes 0 to 1 */
  uint8_t session_id[2];                                                /* bytes 2 to 3 */
  uint8_t isin_code[12];                                                /* bytes 4 to 15 */
  uint8_t a_designated_number_for_an_issue_from_krx[4];                 /* bytes 16 to 19 */
  uint8_t price_change_against_previous_day;                            /* byte 20 */
  uint8_t a_price_change_against_the_previous_day[8];                   /* bytes 21 to 28 */
  uint8_t upper_limit_price[8];                                         /* bytes 29 to 36 */
  uint8_t lower_limit_price[8];                                         /* bytes 37 to 44 */
  uint8_t current_price[8];                                             /* bytes 45 to 52 */
  uint8_t opening_price[8];                                             /* bytes 53 to 60 */
  uint8_t todays_high[8];                                               /* bytes 61 to 68 */
  uint8_t todays_low[8];                                                /* bytes 69 to 76 */
  uint8_t accumulated_trading_volume[8];                                /* bytes 77 to 84 */
  uint8_t accumulated_trading_value[16];                                /* bytes 85 to 100 */
  uint8_t final_ask_bid_type_code;                                      /* byte 101 */
  uint8_t ask_level_1_price[8];                                         /* bytes 102 to 109 */
  uint8_t bid_level_1_price[8];                                         /* bytes 110 to 117 */
  uint8_t ask_level_1_volume[8];                                        /* bytes 118 to 125 */
  uint8_t bid_level_1_volume[8];                                        /* bytes 126 to 133 */
  uint8_t lp_ask_level_1_volume[8];                                     /* bytes 134 to 141 */
  uint8_t lp_bid_level_1_volume[8];                                     /* bytes 142 to 149 */
  uint8_t ask_level_2_price[8];                                         /* bytes 150 to 157 */
  uint8_t bid_level_2_price[8];                                         /* bytes 158 to 165 */
  uint8_t ask_level_2_volume[8];                                        /* bytes 166 to 173 */
  uint8_t bid_level_2_volume[8];                                        /* bytes 174 to 181 */
  uint8_t lp_ask_level_2_volume[8];                                     /* bytes 182 to 189 */
  uint8_t lp_bid_level_2_volume[8];                                     /* bytes 190 to 197 */
  uint8_t ask_level_3_price[8];                                         /* bytes 198 to 205 */
  uint8_t bid_level_3_price[8];                                         /* bytes 206 to 213 */
  uint8_t ask_level_3_volume[8];                                        /* bytes 214 to 221 */
  uint8_t bid_level_3_volume[8];                                        /* bytes 222 to 229 */
  uint8_t lp_ask_level_3_volume[8];                                     /* bytes 230 to 237 */
  uint8_t lp_bid_level_3_volume[8];                                     /* bytes 238 to 245 */
  uint8_t ask_level_4_price[8];                                         /* bytes 246 to 253 */
  uint8_t bid_level_4_price[8];                                         /* bytes 254 to 261 */
  uint8_t ask_level_4_volume[8];                                        /* bytes 262 to 269 */
  uint8_t bid_level_4_volume[8];                                        /* bytes 270 to 277 */
  uint8_t lp_ask_level_4_volume[8];                                     /* bytes 278 to 285 */
  uint8_t lp_bid_level_4_volume[8];                                     /* bytes 286 to 293 */
  uint8_t ask_level_5_price[8];                                         /* bytes 294 to 301 */
  uint8_t bid_level_5_price[8];                                         /* bytes 302 to 309 */
  uint8_t ask_level_5_volume[8];                                        /* bytes 310 to 317 */
  uint8_t bid_level_5_volume[8];                                        /* bytes 318 to 325 */
  uint8_t lp_ask_level_5_volume[8];                                     /* bytes 326 to 333 */
  uint8_t lp_bid_level_5_volume[8];                                     /* bytes 334 to 341 */
  uint8_t ask_level_6_price[8];                                         /* bytes 342 to 349 */
  uint8_t bid_level_6_price[8];                                         /* bytes 350 to 357 */
  uint8_t ask_level_6_volume[8];                                        /* bytes 358 to 365 */
  uint8_t bid_level_6_volume[8];                                        /* bytes 366 to 373 */
  uint8_t lp_ask_level_6_volume[8];                                     /* bytes 374 to 381 */
  uint8_t lp_bid_level_6_volume[8];                                     /* bytes 382 to 389 */
  uint8_t ask_level_7_price[8];                                         /* bytes 390 to 397 */
  uint8_t bid_level_7_price[8];                                         /* bytes 398 to 405 */
  uint8_t ask_level_7_volume[8];                                        /* bytes 406 to 413 */
  uint8_t bid_level_7_volume[8];                                        /* bytes 414 to 421 */
  uint8_t lp_ask_level_7_volume[8];                                     /* bytes 422 to 429 */
  uint8_t lp_bid_level_7_volume[8];                                     /* bytes 430 to 437 */
  uint8_t ask_level_8_price[8];                                         /* bytes 438 to 445 */
  uint8_t bid_level_8_price[8];                                         /* bytes 446 to 453 */
  uint8_t ask_level_8_volume[8];                                        /* bytes 454 to 461 */
  uint8_t bid_level_8_volume[8];                                        /* bytes 462 to 469 */
  uint8_t lp_ask_level_8_volume[8];                                     /* bytes 470 to 477 */
  uint8_t lp_bid_level_8_volume[8];                                     /* bytes 478 to 485 */
  uint8_t ask_level_9_price[8];                                         /* bytes 486 to 493 */
  uint8_t bid_level_9_price[8];                                         /* bytes 494 to 501 */
  uint8_t ask_level_9_volume[8];                                        /* bytes 502 to 509 */
  uint8_t bid_level_9_volume[8];                                        /* bytes 510 to 517 */
  uint8_t lp_ask_level_9_volume[8];                                     /* bytes 518 to 525 */
  uint8_t lp_bid_level_9_volume[8];                                     /* bytes 526 to 533 */
  uint8_t ask_level_10_price[8];                                        /* bytes 534 to 541 */
  uint8_t bid_level_10_price[8];                                        /* bytes 542 to 549 */
  uint8_t ask_level_10_volume[8];                                       /* bytes 550 to 557 */
  uint8_t bid_level_10_volume[8];                                       /* bytes 558 to 565 */
  uint8_t lp_ask_level_10_volume[8];                                    /* bytes 566 to 573 */
  uint8_t lp_bid_level_10_volume[8];                                    /* bytes 574 to 581 */
  uint8_t total_ask_volume[8];                                          /* bytes 582 to 589 */
  uint8_t total_bid_volume[8];                                          /* bytes 590 to 597 */
  uint8_t estimated_trading_price[8];                                   /* bytes 598 to 605 */
  uint8_t estimated_trading_volume[8];                                  /* bytes 606 to 613 */
  uint8_t closing_price_type_code;                                      /* byte 614 */
  uint8_t trading_halt;                                                 /* byte 615 */
  uint8_t knock_out_elw_type_code;                                      /* byte 616 */
  uint8_t knock_out_elw_triggering_time[9];                             /* bytes 617 to 625 */
  uint8_t mid_price[8];                                                 /* bytes 626 to 633 */
  uint8_t total_mid_price_ask_volume_total_ask_volume_on_mid_price[8];  /* bytes 634 to 641 */
  uint8_t total_mid_price_bid_volume_total_bid_volume_on_mid_price[8];  /* bytes 642 to 649 */
  uint8_t end_keyword[4];                                               /* bytes 650 to 653 */
} EquitiesSnapshotMmLpQuotesIncluded10LevelMessage;

/* any Equities Snapshot Mm Lp Quotes Included 10 Level Message at all: every byte one the checker chooses */
static void any_equities_snapshot_mm_lp_quotes_included10_level_message(EquitiesSnapshotMmLpQuotesIncluded10LevelMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  record->price_change_against_previous_day = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->a_price_change_against_the_previous_day[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->upper_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->current_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->accumulated_trading_value[i] = arbitrary(); }
  record->final_ask_bid_type_code = arbitrary();
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
  for (size_t i = 0; i < 8; i++) { record->ask_level_6_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_6_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_7_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_7_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_8_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_8_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_9_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_9_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_10_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_10_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->estimated_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->estimated_trading_volume[i] = arbitrary(); }
  record->closing_price_type_code = arbitrary();
  record->trading_halt = arbitrary();
  record->knock_out_elw_type_code = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->knock_out_elw_triggering_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Equities Snapshot Mm Lp Quotes Included 10 Level Message to the wire: 654 bytes from at, returning where the next byte goes */
static size_t encode_equities_snapshot_mm_lp_quotes_included10_level_message(const EquitiesSnapshotMmLpQuotesIncluded10LevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  wire[at++] = record->price_change_against_previous_day;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->a_price_change_against_the_previous_day[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->current_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->accumulated_trading_value[i]; }
  wire[at++] = record->final_ask_bid_type_code;
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
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_6_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_6_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_6_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_6_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_6_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_6_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_7_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_7_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_7_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_7_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_7_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_7_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_8_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_8_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_8_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_8_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_8_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_8_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_9_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_9_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_9_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_9_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_9_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_9_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_10_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_10_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_level_10_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_level_10_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_ask_level_10_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_bid_level_10_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_ask_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_bid_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->estimated_trading_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->estimated_trading_volume[i]; }
  wire[at++] = record->closing_price_type_code;
  wire[at++] = record->trading_halt;
  wire[at++] = record->knock_out_elw_type_code;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->knock_out_elw_triggering_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Equities Snapshot Mm Lp Quotes Included 10 Level Message off the wire: 654 bytes from at, returning where the next byte lies */
static size_t decode_equities_snapshot_mm_lp_quotes_included10_level_message(EquitiesSnapshotMmLpQuotesIncluded10LevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  record->price_change_against_previous_day = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->a_price_change_against_the_previous_day[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->upper_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->current_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->accumulated_trading_value[i] = wire[at++]; }
  record->final_ask_bid_type_code = wire[at++];
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
  for (size_t i = 0; i < 8; i++) { record->ask_level_6_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_6_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_7_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_7_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_8_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_8_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_9_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_9_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_10_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_10_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_ask_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_bid_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_bid_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->estimated_trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->estimated_trading_volume[i] = wire[at++]; }
  record->closing_price_type_code = wire[at++];
  record->trading_halt = wire[at++];
  record->knock_out_elw_type_code = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->knock_out_elw_triggering_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Equities Snapshot Mm Lp Quotes Included 10 Level Message is what was written, byte for byte */
static void equal_equities_snapshot_mm_lp_quotes_included10_level_message(const EquitiesSnapshotMmLpQuotesIncluded10LevelMessage *read, const EquitiesSnapshotMmLpQuotesIncluded10LevelMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  assert(read->price_change_against_previous_day == written->price_change_against_previous_day);
  for (size_t i = 0; i < 8; i++) { assert(read->a_price_change_against_the_previous_day[i] == written->a_price_change_against_the_previous_day[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->upper_limit_price[i] == written->upper_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower_limit_price[i] == written->lower_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->current_price[i] == written->current_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->accumulated_trading_value[i] == written->accumulated_trading_value[i]); }
  assert(read->final_ask_bid_type_code == written->final_ask_bid_type_code);
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
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_6_price[i] == written->ask_level_6_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_6_price[i] == written->bid_level_6_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_6_volume[i] == written->ask_level_6_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_6_volume[i] == written->bid_level_6_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_6_volume[i] == written->lp_ask_level_6_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_6_volume[i] == written->lp_bid_level_6_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_7_price[i] == written->ask_level_7_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_7_price[i] == written->bid_level_7_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_7_volume[i] == written->ask_level_7_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_7_volume[i] == written->bid_level_7_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_7_volume[i] == written->lp_ask_level_7_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_7_volume[i] == written->lp_bid_level_7_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_8_price[i] == written->ask_level_8_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_8_price[i] == written->bid_level_8_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_8_volume[i] == written->ask_level_8_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_8_volume[i] == written->bid_level_8_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_8_volume[i] == written->lp_ask_level_8_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_8_volume[i] == written->lp_bid_level_8_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_9_price[i] == written->ask_level_9_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_9_price[i] == written->bid_level_9_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_9_volume[i] == written->ask_level_9_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_9_volume[i] == written->bid_level_9_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_9_volume[i] == written->lp_ask_level_9_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_9_volume[i] == written->lp_bid_level_9_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_10_price[i] == written->ask_level_10_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_10_price[i] == written->bid_level_10_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_level_10_volume[i] == written->ask_level_10_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_level_10_volume[i] == written->bid_level_10_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_ask_level_10_volume[i] == written->lp_ask_level_10_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_bid_level_10_volume[i] == written->lp_bid_level_10_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_ask_volume[i] == written->total_ask_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_bid_volume[i] == written->total_bid_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->estimated_trading_price[i] == written->estimated_trading_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->estimated_trading_volume[i] == written->estimated_trading_volume[i]); }
  assert(read->closing_price_type_code == written->closing_price_type_code);
  assert(read->trading_halt == written->trading_halt);
  assert(read->knock_out_elw_type_code == written->knock_out_elw_type_code);
  for (size_t i = 0; i < 9; i++) { assert(read->knock_out_elw_triggering_time[i] == written->knock_out_elw_triggering_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mid_price[i] == written->mid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] == written->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] == written->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Equities Snapshot Mm Lp Quotes Included 10 Level Message: written and read back, then read and written back */
static void check_equities_snapshot_mm_lp_quotes_included10_level_message(void) {
  EquitiesSnapshotMmLpQuotesIncluded10LevelMessage sent;
  EquitiesSnapshotMmLpQuotesIncluded10LevelMessage got;
  uint8_t wire[654];
  uint8_t again[654];

  any_equities_snapshot_mm_lp_quotes_included10_level_message(&sent);
  assert(encode_equities_snapshot_mm_lp_quotes_included10_level_message(&sent, wire, 0) == 654);
  assert(decode_equities_snapshot_mm_lp_quotes_included10_level_message(&got, wire, 0) == 654);
  equal_equities_snapshot_mm_lp_quotes_included10_level_message(&got, &sent);

  for (size_t i = 0; i < 654; i++) { wire[i] = arbitrary(); }
  assert(decode_equities_snapshot_mm_lp_quotes_included10_level_message(&got, wire, 0) == 654);
  assert(encode_equities_snapshot_mm_lp_quotes_included10_level_message(&got, again, 0) == 654);
  for (size_t i = 0; i < 654; i++) { assert(again[i] == wire[i]); }
}

/* ---- Investor Activities Per Commodities Message: 62 bytes ------------------- */

/* Investor Activities per Commodities. */
typedef struct {
  uint8_t calculation_time[6];                /* bytes 0 to 5 */
  uint8_t investor_code[4];                   /* bytes 6 to 9 */
  uint8_t accumulated_ask_trading_volume[8];  /* bytes 10 to 17 */
  uint8_t accumulated_ask_trading_value[16];  /* bytes 18 to 33 */
  uint8_t accumulated_bid_trading_volume[8];  /* bytes 34 to 41 */
  uint8_t accumulated_bid_trading_value[16];  /* bytes 42 to 57 */
  uint8_t end_keyword[4];                     /* bytes 58 to 61 */
} InvestorActivitiesPerCommoditiesMessage;

/* any Investor Activities Per Commodities Message at all: every byte one the checker chooses */
static void any_investor_activities_per_commodities_message(InvestorActivitiesPerCommoditiesMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->calculation_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accumulated_ask_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->accumulated_ask_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accumulated_bid_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->accumulated_bid_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Investor Activities Per Commodities Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_investor_activities_per_commodities_message(const InvestorActivitiesPerCommoditiesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->calculation_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->investor_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accumulated_ask_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->accumulated_ask_trading_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accumulated_bid_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->accumulated_bid_trading_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Investor Activities Per Commodities Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_investor_activities_per_commodities_message(InvestorActivitiesPerCommoditiesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->calculation_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accumulated_ask_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->accumulated_ask_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accumulated_bid_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->accumulated_bid_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Investor Activities Per Commodities Message is what was written, byte for byte */
static void equal_investor_activities_per_commodities_message(const InvestorActivitiesPerCommoditiesMessage *read, const InvestorActivitiesPerCommoditiesMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->calculation_time[i] == written->calculation_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->investor_code[i] == written->investor_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accumulated_ask_trading_volume[i] == written->accumulated_ask_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->accumulated_ask_trading_value[i] == written->accumulated_ask_trading_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accumulated_bid_trading_volume[i] == written->accumulated_bid_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->accumulated_bid_trading_value[i] == written->accumulated_bid_trading_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Investor Activities Per Commodities Message: written and read back, then read and written back */
static void check_investor_activities_per_commodities_message(void) {
  InvestorActivitiesPerCommoditiesMessage sent;
  InvestorActivitiesPerCommoditiesMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_investor_activities_per_commodities_message(&sent);
  assert(encode_investor_activities_per_commodities_message(&sent, wire, 0) == 62);
  assert(decode_investor_activities_per_commodities_message(&got, wire, 0) == 62);
  equal_investor_activities_per_commodities_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_investor_activities_per_commodities_message(&got, wire, 0) == 62);
  assert(encode_investor_activities_per_commodities_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Etp Constituents Message: 203 bytes ------------------------------------- */

/* Constituents of Structured Products. */
typedef struct {
  uint8_t message_sequence_number[4];                  /* bytes 0 to 3 */
  uint8_t index_calculation_institution_type_code[2];  /* bytes 4 to 5 */
  uint8_t index_market_classification_id[6];           /* bytes 6 to 11 */
  uint8_t index_sequence_number[3];                    /* bytes 12 to 14 */
  uint8_t index_leverage_inverse_type_code[2];         /* bytes 15 to 16 */
  uint8_t index_name[80];                              /* bytes 17 to 96 */
  uint8_t index_name_in_en[80];                        /* bytes 97 to 176 */
  uint8_t index_asset_classification_id_1[6];          /* bytes 177 to 182 */
  uint8_t index_asset_classification_id_2[6];          /* bytes 183 to 188 */
  uint8_t index_id[6];                                 /* bytes 189 to 194 */
  uint8_t filler_4[4];                                 /* bytes 195 to 198 */
  uint8_t end_keyword[4];                              /* bytes 199 to 202 */
} EtpConstituentsMessage;

/* any Etp Constituents Message at all: every byte one the checker chooses */
static void any_etp_constituents_message(EtpConstituentsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->index_calculation_institution_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_market_classification_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->index_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->index_leverage_inverse_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->index_name[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->index_name_in_en[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_asset_classification_id_1[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_asset_classification_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Etp Constituents Message to the wire: 203 bytes from at, returning where the next byte goes */
static size_t encode_etp_constituents_message(const EtpConstituentsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->index_calculation_institution_type_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_market_classification_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->index_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->index_leverage_inverse_type_code[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->index_name[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->index_name_in_en[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_asset_classification_id_1[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_asset_classification_id_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Etp Constituents Message off the wire: 203 bytes from at, returning where the next byte lies */
static size_t decode_etp_constituents_message(EtpConstituentsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->index_calculation_institution_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_market_classification_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->index_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->index_leverage_inverse_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->index_name[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->index_name_in_en[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_asset_classification_id_1[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_asset_classification_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Etp Constituents Message is what was written, byte for byte */
static void equal_etp_constituents_message(const EtpConstituentsMessage *read, const EtpConstituentsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->index_calculation_institution_type_code[i] == written->index_calculation_institution_type_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_market_classification_id[i] == written->index_market_classification_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->index_sequence_number[i] == written->index_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->index_leverage_inverse_type_code[i] == written->index_leverage_inverse_type_code[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->index_name[i] == written->index_name[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->index_name_in_en[i] == written->index_name_in_en[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_asset_classification_id_1[i] == written->index_asset_classification_id_1[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_asset_classification_id_2[i] == written->index_asset_classification_id_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Etp Constituents Message: written and read back, then read and written back */
static void check_etp_constituents_message(void) {
  EtpConstituentsMessage sent;
  EtpConstituentsMessage got;
  uint8_t wire[203];
  uint8_t again[203];

  any_etp_constituents_message(&sent);
  assert(encode_etp_constituents_message(&sent, wire, 0) == 203);
  assert(decode_etp_constituents_message(&got, wire, 0) == 203);
  equal_etp_constituents_message(&got, &sent);

  for (size_t i = 0; i < 203; i++) { wire[i] = arbitrary(); }
  assert(decode_etp_constituents_message(&got, wire, 0) == 203);
  assert(encode_etp_constituents_message(&got, again, 0) == 203);
  for (size_t i = 0; i < 203; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mm Lp Information Message: 169 bytes ------------------------------------ */

/* Details. */
typedef struct {
  uint8_t message_sequence_number[4];                        /* bytes 0 to 3 */
  uint8_t isin_code[12];                                     /* bytes 4 to 15 */
  uint8_t market_participant_number[5];                      /* bytes 16 to 20 */
  uint8_t board_id[2];                                       /* bytes 21 to 22 */
  uint8_t market_making_lp_type_code;                        /* byte 23 */
  uint8_t lp_start_date[8];                                  /* bytes 24 to 31 */
  uint8_t lp_end_date[8];                                    /* bytes 32 to 39 */
  uint8_t minimum_order_volume[8];                           /* bytes 40 to 47 */
  uint8_t maximum_volume_of_multiple_order[8];               /* bytes 48 to 55 */
  uint8_t bid_ask_spread_unit_code;                          /* byte 56 */
  uint8_t main_market_bid_ask_spread_value[16];              /* bytes 57 to 72 */
  uint8_t spread_multiple_for_market_holidays[8];            /* bytes 73 to 80 */
  uint8_t an_obligatory_time_interval_to_place_an_order[4];  /* bytes 81 to 84 */
  uint8_t minimum_ask_price[16];                             /* bytes 85 to 100 */
  uint8_t maximum_bid_price[16];                             /* bytes 101 to 116 */
  uint8_t minimum_order_price[16];                           /* bytes 117 to 132 */
  uint8_t maximum_order_price[16];                           /* bytes 133 to 148 */
  uint8_t extended_market_bid_ask_spread_value[16];          /* bytes 149 to 164 */
  uint8_t end_keyword[4];                                    /* bytes 165 to 168 */
} MmLpInformationMessage;

/* any Mm Lp Information Message at all: every byte one the checker chooses */
static void any_mm_lp_information_message(MmLpInformationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->market_participant_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  record->market_making_lp_type_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->lp_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_end_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_order_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maximum_volume_of_multiple_order[i] = arbitrary(); }
  record->bid_ask_spread_unit_code = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->main_market_bid_ask_spread_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->spread_multiple_for_market_holidays[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->an_obligatory_time_interval_to_place_an_order[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->minimum_ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->maximum_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->minimum_order_price[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->maximum_order_price[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->extended_market_bid_ask_spread_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Mm Lp Information Message to the wire: 169 bytes from at, returning where the next byte goes */
static size_t encode_mm_lp_information_message(const MmLpInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->market_participant_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  wire[at++] = record->market_making_lp_type_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_start_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_end_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_order_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maximum_volume_of_multiple_order[i]; }
  wire[at++] = record->bid_ask_spread_unit_code;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->main_market_bid_ask_spread_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->spread_multiple_for_market_holidays[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->an_obligatory_time_interval_to_place_an_order[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->minimum_ask_price[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->maximum_bid_price[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->minimum_order_price[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->maximum_order_price[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->extended_market_bid_ask_spread_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Mm Lp Information Message off the wire: 169 bytes from at, returning where the next byte lies */
static size_t decode_mm_lp_information_message(MmLpInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->market_participant_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  record->market_making_lp_type_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->lp_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_end_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_order_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maximum_volume_of_multiple_order[i] = wire[at++]; }
  record->bid_ask_spread_unit_code = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->main_market_bid_ask_spread_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->spread_multiple_for_market_holidays[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->an_obligatory_time_interval_to_place_an_order[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->minimum_ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->maximum_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->minimum_order_price[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->maximum_order_price[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->extended_market_bid_ask_spread_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Mm Lp Information Message is what was written, byte for byte */
static void equal_mm_lp_information_message(const MmLpInformationMessage *read, const MmLpInformationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->market_participant_number[i] == written->market_participant_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  assert(read->market_making_lp_type_code == written->market_making_lp_type_code);
  for (size_t i = 0; i < 8; i++) { assert(read->lp_start_date[i] == written->lp_start_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_end_date[i] == written->lp_end_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_order_volume[i] == written->minimum_order_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maximum_volume_of_multiple_order[i] == written->maximum_volume_of_multiple_order[i]); }
  assert(read->bid_ask_spread_unit_code == written->bid_ask_spread_unit_code);
  for (size_t i = 0; i < 16; i++) { assert(read->main_market_bid_ask_spread_value[i] == written->main_market_bid_ask_spread_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->spread_multiple_for_market_holidays[i] == written->spread_multiple_for_market_holidays[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->an_obligatory_time_interval_to_place_an_order[i] == written->an_obligatory_time_interval_to_place_an_order[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->minimum_ask_price[i] == written->minimum_ask_price[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->maximum_bid_price[i] == written->maximum_bid_price[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->minimum_order_price[i] == written->minimum_order_price[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->maximum_order_price[i] == written->maximum_order_price[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->extended_market_bid_ask_spread_value[i] == written->extended_market_bid_ask_spread_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Mm Lp Information Message: written and read back, then read and written back */
static void check_mm_lp_information_message(void) {
  MmLpInformationMessage sent;
  MmLpInformationMessage got;
  uint8_t wire[169];
  uint8_t again[169];

  any_mm_lp_information_message(&sent);
  assert(encode_mm_lp_information_message(&sent, wire, 0) == 169);
  assert(decode_mm_lp_information_message(&got, wire, 0) == 169);
  equal_mm_lp_information_message(&got, &sent);

  for (size_t i = 0; i < 169; i++) { wire[i] = arbitrary(); }
  assert(decode_mm_lp_information_message(&got, wire, 0) == 169);
  assert(encode_mm_lp_information_message(&got, again, 0) == 169);
  for (size_t i = 0; i < 169; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Operation Schedule Message: 82 bytes ----------------------------- */

/* The data is provided when a Market Operation Schedule event is disclosed. */
typedef struct {
  uint8_t market_operation_product_id[3];                        /* bytes 0 to 2 */
  uint8_t board_id[2];                                           /* bytes 3 to 4 */
  uint8_t board_event_id[3];                                     /* bytes 5 to 7 */
  uint8_t start_time_of_a_board_event[9];                        /* bytes 8 to 16 */
  uint8_t board_event_group_code[4];                             /* bytes 17 to 20 */
  uint8_t session_start_end_code[2];                             /* bytes 21 to 22 */
  uint8_t session_id[2];                                         /* bytes 23 to 24 */
  uint8_t isin_code[12];                                         /* bytes 25 to 36 */
  uint8_t isin_code_of_a_common_stock[12];                       /* bytes 37 to 48 */
  uint8_t product_id[11];                                        /* bytes 49 to 59 */
  uint8_t trading_halt_reason_code[3];                           /* bytes 60 to 62 */
  uint8_t trading_halt_type_code;                                /* byte 63 */
  uint8_t step_applied[4];                                       /* bytes 64 to 67 */
  uint8_t price_limit_range_expansion_for_base_issue_type_code;  /* byte 68 */
  uint8_t expected_time_of_expanding_price_limit_range[9];       /* bytes 69 to 77 */
  uint8_t end_keyword[4];                                        /* bytes 78 to 81 */
} MarketOperationScheduleMessage;

/* any Market Operation Schedule Message at all: every byte one the checker chooses */
static void any_market_operation_schedule_message(MarketOperationScheduleMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->board_event_group_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_start_end_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code_of_a_common_stock[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = arbitrary(); }
  record->trading_halt_type_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->step_applied[i] = arbitrary(); }
  record->price_limit_range_expansion_for_base_issue_type_code = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->expected_time_of_expanding_price_limit_range[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Market Operation Schedule Message to the wire: 82 bytes from at, returning where the next byte goes */
static size_t encode_market_operation_schedule_message(const MarketOperationScheduleMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_operation_product_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->board_event_id[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->start_time_of_a_board_event[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->board_event_group_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_start_end_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code_of_a_common_stock[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_halt_reason_code[i]; }
  wire[at++] = record->trading_halt_type_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->step_applied[i]; }
  wire[at++] = record->price_limit_range_expansion_for_base_issue_type_code;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->expected_time_of_expanding_price_limit_range[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Market Operation Schedule Message off the wire: 82 bytes from at, returning where the next byte lies */
static size_t decode_market_operation_schedule_message(MarketOperationScheduleMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->board_event_group_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_start_end_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code_of_a_common_stock[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = wire[at++]; }
  record->trading_halt_type_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->step_applied[i] = wire[at++]; }
  record->price_limit_range_expansion_for_base_issue_type_code = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->expected_time_of_expanding_price_limit_range[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Market Operation Schedule Message is what was written, byte for byte */
static void equal_market_operation_schedule_message(const MarketOperationScheduleMessage *read, const MarketOperationScheduleMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->market_operation_product_id[i] == written->market_operation_product_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->board_event_id[i] == written->board_event_id[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->start_time_of_a_board_event[i] == written->start_time_of_a_board_event[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->board_event_group_code[i] == written->board_event_group_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_start_end_code[i] == written->session_start_end_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code_of_a_common_stock[i] == written->isin_code_of_a_common_stock[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trading_halt_reason_code[i] == written->trading_halt_reason_code[i]); }
  assert(read->trading_halt_type_code == written->trading_halt_type_code);
  for (size_t i = 0; i < 4; i++) { assert(read->step_applied[i] == written->step_applied[i]); }
  assert(read->price_limit_range_expansion_for_base_issue_type_code == written->price_limit_range_expansion_for_base_issue_type_code);
  for (size_t i = 0; i < 9; i++) { assert(read->expected_time_of_expanding_price_limit_range[i] == written->expected_time_of_expanding_price_limit_range[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Market Operation Schedule Message: written and read back, then read and written back */
static void check_market_operation_schedule_message(void) {
  MarketOperationScheduleMessage sent;
  MarketOperationScheduleMessage got;
  uint8_t wire[82];
  uint8_t again[82];

  any_market_operation_schedule_message(&sent);
  assert(encode_market_operation_schedule_message(&sent, wire, 0) == 82);
  assert(decode_market_operation_schedule_message(&got, wire, 0) == 82);
  equal_market_operation_schedule_message(&got, &sent);

  for (size_t i = 0; i < 82; i++) { wire[i] = arbitrary(); }
  assert(decode_market_operation_schedule_message(&got, wire, 0) == 82);
  assert(encode_market_operation_schedule_message(&got, again, 0) == 82);
  for (size_t i = 0; i < 82; i++) { assert(again[i] == wire[i]); }
}

/* ---- Member Firm Imposing Lifting Sanctions Message: 41 bytes ---------------- */

/* The data is provided when a sanction is imposed on a member firm or lifted. */
typedef struct {
  uint8_t isin_code[12];                                 /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue_from_krx[4];  /* bytes 12 to 15 */
  uint8_t disclosing_data_type_code[3];                  /* bytes 16 to 18 */
  uint8_t disclosure_time[9];                            /* bytes 19 to 27 */
  uint8_t member_number[5];                              /* bytes 28 to 32 */
  uint8_t member_firm_trust_principal_type_code[4];      /* bytes 33 to 36 */
  uint8_t end_keyword[4];                                /* bytes 37 to 40 */
} MemberFirmImposingLiftingSanctionsMessage;

/* any Member Firm Imposing Lifting Sanctions Message at all: every byte one the checker chooses */
static void any_member_firm_imposing_lifting_sanctions_message(MemberFirmImposingLiftingSanctionsMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->disclosing_data_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->disclosure_time[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->member_firm_trust_principal_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Member Firm Imposing Lifting Sanctions Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_member_firm_imposing_lifting_sanctions_message(const MemberFirmImposingLiftingSanctionsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->disclosing_data_type_code[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->disclosure_time[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member_firm_trust_principal_type_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Member Firm Imposing Lifting Sanctions Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_member_firm_imposing_lifting_sanctions_message(MemberFirmImposingLiftingSanctionsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->disclosing_data_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->disclosure_time[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->member_firm_trust_principal_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Member Firm Imposing Lifting Sanctions Message is what was written, byte for byte */
static void equal_member_firm_imposing_lifting_sanctions_message(const MemberFirmImposingLiftingSanctionsMessage *read, const MemberFirmImposingLiftingSanctionsMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->disclosing_data_type_code[i] == written->disclosing_data_type_code[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->disclosure_time[i] == written->disclosure_time[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number[i] == written->member_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->member_firm_trust_principal_type_code[i] == written->member_firm_trust_principal_type_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Member Firm Imposing Lifting Sanctions Message: written and read back, then read and written back */
static void check_member_firm_imposing_lifting_sanctions_message(void) {
  MemberFirmImposingLiftingSanctionsMessage sent;
  MemberFirmImposingLiftingSanctionsMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_member_firm_imposing_lifting_sanctions_message(&sent);
  assert(encode_member_firm_imposing_lifting_sanctions_message(&sent, wire, 0) == 41);
  assert(decode_member_firm_imposing_lifting_sanctions_message(&got, wire, 0) == 41);
  equal_member_firm_imposing_lifting_sanctions_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_member_firm_imposing_lifting_sanctions_message(&got, wire, 0) == 41);
  assert(encode_member_firm_imposing_lifting_sanctions_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Five Traders Activities Message: 310 bytes -------------------------- */

/* Top Five Traders' Activities (including only Regular Board). */
typedef struct {
  uint8_t isin_code[12];                                 /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue_from_krx[4];  /* bytes 12 to 15 */
  uint8_t member_number_1_for_ask[5];                    /* bytes 16 to 20 */
  uint8_t ask_trading_volume_1[8];                       /* bytes 21 to 28 */
  uint8_t ask_trading_value_1[16];                       /* bytes 29 to 44 */
  uint8_t member_number_1_for_bid[5];                    /* bytes 45 to 49 */
  uint8_t bid_trading_volume_1[8];                       /* bytes 50 to 57 */
  uint8_t bid_trading_value_1[16];                       /* bytes 58 to 73 */
  uint8_t member_number_2_for_ask[5];                    /* bytes 74 to 78 */
  uint8_t ask_trading_volume_2[8];                       /* bytes 79 to 86 */
  uint8_t ask_trading_value_2[16];                       /* bytes 87 to 102 */
  uint8_t member_number_2_for_bid[5];                    /* bytes 103 to 107 */
  uint8_t bid_trading_volume_2[8];                       /* bytes 108 to 115 */
  uint8_t bid_trading_value_2[16];                       /* bytes 116 to 131 */
  uint8_t member_number_3_for_ask[5];                    /* bytes 132 to 136 */
  uint8_t ask_trading_volume_3[8];                       /* bytes 137 to 144 */
  uint8_t ask_trading_value_3[16];                       /* bytes 145 to 160 */
  uint8_t member_number_3_for_bid[5];                    /* bytes 161 to 165 */
  uint8_t bid_trading_volume_3[8];                       /* bytes 166 to 173 */
  uint8_t bid_trading_value_3[16];                       /* bytes 174 to 189 */
  uint8_t member_number_4_for_ask[5];                    /* bytes 190 to 194 */
  uint8_t ask_trading_volume_4[8];                       /* bytes 195 to 202 */
  uint8_t ask_trading_value_4[16];                       /* bytes 203 to 218 */
  uint8_t member_number_4_for_bid[5];                    /* bytes 219 to 223 */
  uint8_t bid_trading_volume_4[8];                       /* bytes 224 to 231 */
  uint8_t bid_trading_value_4[16];                       /* bytes 232 to 247 */
  uint8_t member_number_5_for_ask[5];                    /* bytes 248 to 252 */
  uint8_t ask_trading_volume_5[8];                       /* bytes 253 to 260 */
  uint8_t ask_trading_value_5[16];                       /* bytes 261 to 276 */
  uint8_t member_number_5_for_bid[5];                    /* bytes 277 to 281 */
  uint8_t bid_trading_volume_5[8];                       /* bytes 282 to 289 */
  uint8_t bid_trading_value_5[16];                       /* bytes 290 to 305 */
  uint8_t end_keyword[4];                                /* bytes 306 to 309 */
} TopFiveTradersActivitiesMessage;

/* any Top Five Traders Activities Message at all: every byte one the checker chooses */
static void any_top_five_traders_activities_message(TopFiveTradersActivitiesMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_1_for_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_trading_volume_1[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->ask_trading_value_1[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_1_for_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_trading_volume_1[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->bid_trading_value_1[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_2_for_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_trading_volume_2[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->ask_trading_value_2[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_2_for_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_trading_volume_2[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->bid_trading_value_2[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_3_for_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_trading_volume_3[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->ask_trading_value_3[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_3_for_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_trading_volume_3[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->bid_trading_value_3[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_4_for_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_trading_volume_4[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->ask_trading_value_4[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_4_for_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_trading_volume_4[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->bid_trading_value_4[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_5_for_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_trading_volume_5[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->ask_trading_value_5[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_5_for_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_trading_volume_5[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->bid_trading_value_5[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Top Five Traders Activities Message to the wire: 310 bytes from at, returning where the next byte goes */
static size_t encode_top_five_traders_activities_message(const TopFiveTradersActivitiesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_1_for_ask[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_trading_volume_1[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->ask_trading_value_1[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_1_for_bid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_trading_volume_1[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->bid_trading_value_1[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_2_for_ask[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_trading_volume_2[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->ask_trading_value_2[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_2_for_bid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_trading_volume_2[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->bid_trading_value_2[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_3_for_ask[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_trading_volume_3[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->ask_trading_value_3[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_3_for_bid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_trading_volume_3[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->bid_trading_value_3[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_4_for_ask[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_trading_volume_4[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->ask_trading_value_4[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_4_for_bid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_trading_volume_4[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->bid_trading_value_4[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_5_for_ask[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_trading_volume_5[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->ask_trading_value_5[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_5_for_bid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_trading_volume_5[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->bid_trading_value_5[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Top Five Traders Activities Message off the wire: 310 bytes from at, returning where the next byte lies */
static size_t decode_top_five_traders_activities_message(TopFiveTradersActivitiesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_1_for_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_trading_volume_1[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->ask_trading_value_1[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_1_for_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_trading_volume_1[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->bid_trading_value_1[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_2_for_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_trading_volume_2[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->ask_trading_value_2[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_2_for_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_trading_volume_2[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->bid_trading_value_2[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_3_for_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_trading_volume_3[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->ask_trading_value_3[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_3_for_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_trading_volume_3[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->bid_trading_value_3[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_4_for_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_trading_volume_4[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->ask_trading_value_4[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_4_for_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_trading_volume_4[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->bid_trading_value_4[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_5_for_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_trading_volume_5[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->ask_trading_value_5[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_5_for_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_trading_volume_5[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->bid_trading_value_5[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Top Five Traders Activities Message is what was written, byte for byte */
static void equal_top_five_traders_activities_message(const TopFiveTradersActivitiesMessage *read, const TopFiveTradersActivitiesMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_1_for_ask[i] == written->member_number_1_for_ask[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_trading_volume_1[i] == written->ask_trading_volume_1[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->ask_trading_value_1[i] == written->ask_trading_value_1[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_1_for_bid[i] == written->member_number_1_for_bid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_trading_volume_1[i] == written->bid_trading_volume_1[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->bid_trading_value_1[i] == written->bid_trading_value_1[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_2_for_ask[i] == written->member_number_2_for_ask[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_trading_volume_2[i] == written->ask_trading_volume_2[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->ask_trading_value_2[i] == written->ask_trading_value_2[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_2_for_bid[i] == written->member_number_2_for_bid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_trading_volume_2[i] == written->bid_trading_volume_2[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->bid_trading_value_2[i] == written->bid_trading_value_2[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_3_for_ask[i] == written->member_number_3_for_ask[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_trading_volume_3[i] == written->ask_trading_volume_3[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->ask_trading_value_3[i] == written->ask_trading_value_3[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_3_for_bid[i] == written->member_number_3_for_bid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_trading_volume_3[i] == written->bid_trading_volume_3[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->bid_trading_value_3[i] == written->bid_trading_value_3[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_4_for_ask[i] == written->member_number_4_for_ask[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_trading_volume_4[i] == written->ask_trading_volume_4[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->ask_trading_value_4[i] == written->ask_trading_value_4[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_4_for_bid[i] == written->member_number_4_for_bid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_trading_volume_4[i] == written->bid_trading_volume_4[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->bid_trading_value_4[i] == written->bid_trading_value_4[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_5_for_ask[i] == written->member_number_5_for_ask[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_trading_volume_5[i] == written->ask_trading_volume_5[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->ask_trading_value_5[i] == written->ask_trading_value_5[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_5_for_bid[i] == written->member_number_5_for_bid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_trading_volume_5[i] == written->bid_trading_volume_5[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->bid_trading_value_5[i] == written->bid_trading_value_5[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Top Five Traders Activities Message: written and read back, then read and written back */
static void check_top_five_traders_activities_message(void) {
  TopFiveTradersActivitiesMessage sent;
  TopFiveTradersActivitiesMessage got;
  uint8_t wire[310];
  uint8_t again[310];

  any_top_five_traders_activities_message(&sent);
  assert(encode_top_five_traders_activities_message(&sent, wire, 0) == 310);
  assert(decode_top_five_traders_activities_message(&got, wire, 0) == 310);
  equal_top_five_traders_activities_message(&got, &sent);

  for (size_t i = 0; i < 310; i++) { wire[i] = arbitrary(); }
  assert(decode_top_five_traders_activities_message(&got, wire, 0) == 310);
  assert(encode_top_five_traders_activities_message(&got, again, 0) == 310);
  for (size_t i = 0; i < 310; i++) { assert(again[i] == wire[i]); }
}

/* ---- Equities Batch Data Message: 551 bytes ---------------------------------- */

/* Details. */
typedef struct {
  uint8_t message_sequence_number[4];                                          /* bytes 0 to 3 */
  uint8_t total_number_of_instruments_of_the_contract[4];                      /* bytes 4 to 7 */
  uint8_t business_date[8];                                                    /* bytes 8 to 15 */
  uint8_t isin_code[12];                                                       /* bytes 16 to 27 */
  uint8_t a_designated_number_for_an_issue_from_krx[4];                        /* bytes 28 to 31 */
  uint8_t abbreviated_issue_code[9];                                           /* bytes 32 to 40 */
  uint8_t abbreviated_issue_name[40];                                          /* bytes 41 to 80 */
  uint8_t abbreviated_issue_name_in_en[40];                                    /* bytes 81 to 120 */
  uint8_t group_number[5];                                                     /* bytes 121 to 125 */
  uint8_t market_operation_product_id[3];                                      /* bytes 126 to 128 */
  uint8_t security_group_id[2];                                                /* bytes 129 to 130 */
  uint8_t unit_trading;                                                        /* byte 131 */
  uint8_t rights_type_code[2];                                                 /* bytes 132 to 133 */
  uint8_t par_value_type_code[2];                                              /* bytes 134 to 135 */
  uint8_t an_issue_of_which_base_price_is_settled_with_a_todays_single_price;  /* byte 136 */
  uint8_t reevaluation_reason_code[2];                                         /* bytes 137 to 138 */
  uint8_t base_price_change;                                                   /* byte 139 */
  uint8_t random_end_trigger_code;                                             /* byte 140 */
  uint8_t market_alert;                                                        /* byte 141 */
  uint8_t market_alert_type_code[2];                                           /* bytes 142 to 143 */
  uint8_t korea_corporate_governance_stock_price_index_kogi;                   /* byte 144 */
  uint8_t issue_for_administration;                                            /* byte 145 */
  uint8_t unfaithful_disclosure;                                               /* byte 146 */
  uint8_t back_door_listing;                                                   /* byte 147 */
  uint8_t trading_halt;                                                        /* byte 148 */
  uint8_t industry_id[10];                                                     /* bytes 149 to 158 */
  uint8_t small_medium_sized_business;                                         /* byte 159 */
  uint8_t section_type_code;                                                   /* byte 160 */
  uint8_t investment_institution_type_code;                                    /* byte 161 */
  uint8_t base_price[8];                                                       /* bytes 162 to 169 */
  uint8_t yesterdays_closing_price_type_code_krx;                              /* byte 170 */
  uint8_t yesterdays_closing_price_krx[8];                                     /* bytes 171 to 178 */
  uint8_t yesterdays_accumulated_trading_amount[8];                            /* bytes 179 to 186 */
  uint8_t yesterdays_accumulated_trading_value[16];                            /* bytes 187 to 202 */
  uint8_t upper_limit_price[8];                                                /* bytes 203 to 210 */
  uint8_t lower_limit_price[8];                                                /* bytes 211 to 218 */
  uint8_t substitute_price_of_securities[8];                                   /* bytes 219 to 226 */
  uint8_t par_value[8];                                                        /* bytes 227 to 234 */
  uint8_t issuing_price[8];                                                    /* bytes 235 to 242 */
  uint8_t listing_date[8];                                                     /* bytes 243 to 250 */
  uint8_t number_of_listed_shares[8];                                          /* bytes 251 to 258 */
  uint8_t liquidation_trade;                                                   /* byte 259 */
  uint8_t the_establishment_date[8];                                           /* bytes 260 to 267 */
  uint8_t maturity_date[8];                                                    /* bytes 268 to 275 */
  uint8_t exercising_period[8];                                                /* bytes 276 to 283 */
  uint8_t expiration_date_for_right[8];                                        /* bytes 284 to 291 */
  uint8_t exercise_price_of_elw_or_bw[8];                                      /* bytes 292 to 299 */
  uint8_t capital[16];                                                         /* bytes 300 to 315 */
  uint8_t credit_order_possibility;                                            /* byte 316 */
  uint8_t limit_order_permission_type_code[4];                                 /* bytes 317 to 320 */
  uint8_t market_price_order_permission_type_code[4];                          /* bytes 321 to 324 */
  uint8_t conditioned_order_permission_type_code[4];                           /* bytes 325 to 328 */
  uint8_t best_favorable_order_permission_type_code[4];                        /* bytes 329 to 332 */
  uint8_t first_best_order_permission_type[4];                                 /* bytes 333 to 336 */
  uint8_t mid_price_order_permission_type_code[4];                             /* bytes 337 to 340 */
  uint8_t stop_limit_price_order_permission_type_code[4];                      /* bytes 341 to 344 */
  uint8_t capital_increase_type_code[2];                                       /* bytes 345 to 346 */
  uint8_t other_stock_type_code;                                               /* byte 347 */
  uint8_t national_stock;                                                      /* byte 348 */
  uint8_t appraised_price[8];                                                  /* bytes 349 to 356 */
  uint8_t lowest_order_price[8];                                               /* bytes 357 to 364 */
  uint8_t highest_order_price[8];                                              /* bytes 365 to 372 */
  uint8_t unit_of_volume_in_main_board[8];                                     /* bytes 373 to 380 */
  uint8_t lot_size_after_hours_trading[8];                                     /* bytes 381 to 388 */
  uint8_t rei_ts_type_code;                                                    /* byte 389 */
  uint8_t target_stock_isin_code[12];                                          /* bytes 390 to 401 */
  uint8_t currency_iso_code[3];                                                /* bytes 402 to 404 */
  uint8_t country_code[3];                                                     /* bytes 405 to 407 */
  uint8_t market_making_possibility;                                           /* byte 408 */
  uint8_t closing_price_trading_possibility_in_the_after_hours;                /* byte 409 */
  uint8_t closing_price_trading_in_the_pre_opening_market;                     /* byte 410 */
  uint8_t block_trading_in_the_pre_opening_market;                             /* byte 411 */
  uint8_t basket_trading_in_the_pre_opening_market;                            /* byte 412 */
  uint8_t announcement_of_estimated_trading_price;                             /* byte 413 */
  uint8_t short_selling;                                                       /* byte 414 */
  uint8_t etf_tracking_difference[8];                                          /* bytes 415 to 422 */
  uint8_t regs;                                                                /* byte 423 */
  uint8_t spac;                                                                /* byte 424 */
  uint8_t tax_type_code;                                                       /* byte 425 */
  uint8_t appraisal_ratio_of_substitute_price[8];                              /* bytes 426 to 433 */
  uint8_t investment_caution_issue;                                            /* byte 434 */
  uint8_t delisting_date[8];                                                   /* bytes 435 to 442 */
  uint8_t short_term_overheat_issue_type_code;                                 /* byte 443 */
  uint8_t etf_replication_methods_type_code;                                   /* byte 444 */
  uint8_t expiration_date[8];                                                  /* bytes 445 to 452 */
  uint8_t distribution_type_code[2];                                           /* bytes 453 to 454 */
  uint8_t calculation_of_redemption_price_start_date[8];                       /* bytes 455 to 462 */
  uint8_t calculation_of_redemption_price_end_date[8];                         /* bytes 463 to 470 */
  uint8_t etp_product_type_code;                                               /* byte 471 */
  uint8_t index_calculation_institution_type_code[2];                          /* bytes 472 to 473 */
  uint8_t index_market_classification_id[6];                                   /* bytes 474 to 479 */
  uint8_t index_sequence_number[3];                                            /* bytes 480 to 482 */
  uint8_t tracking_index_leverage_inverse_type_code[2];                        /* bytes 483 to 484 */
  uint8_t reference_index_leverage_inverse_type_code[2];                       /* bytes 485 to 486 */
  uint8_t index_asset_classification_id_1[6];                                  /* bytes 487 to 492 */
  uint8_t index_asset_classification_id_2[6];                                  /* bytes 493 to 498 */
  uint8_t ipo_underwriter_member_number[5];                                    /* bytes 499 to 503 */
  uint8_t lp_order;                                                            /* byte 504 */
  uint8_t low_liquidity;                                                       /* byte 505 */
  uint8_t abnormal_rise;                                                       /* byte 506 */
  uint8_t upper_limit_quantity[16];                                            /* bytes 507 to 522 */
  uint8_t investment_precaution_issue;                                         /* byte 523 */
  uint8_t preferred_stocks_with_lesser_shares;                                 /* byte 524 */
  uint8_t spac_merger;                                                         /* byte 525 */
  uint8_t segment_type_code;                                                   /* byte 526 */
  uint8_t after_market_possibility;                                            /* byte 527 */
  uint8_t choice_on_competitive_trading;                                       /* byte 528 */
  uint8_t limit_on_competitive_trading_volume;                                 /* byte 529 */
  uint8_t occurrence_of_reasons_prohibiting_competitive_trading;               /* byte 530 */
  uint8_t approval_on_competitive_trading;                                     /* byte 531 */
  uint8_t approval_on_negotiation_trading;                                     /* byte 532 */
  uint8_t yesterdays_closing_price_type_code_nxt;                              /* byte 533 */
  uint8_t yesterdays_closing_price_nxt[8];                                     /* bytes 534 to 541 */
  uint8_t competition_board_trade_permission_code[4];                          /* bytes 542 to 545 */
  uint8_t negotiation_possible_or_not_before_main_market;                      /* byte 546 */
  uint8_t end_keyword[4];                                                      /* bytes 547 to 550 */
} EquitiesBatchDataMessage;

/* any Equities Batch Data Message at all: every byte one the checker chooses */
static void any_equities_batch_data_message(EquitiesBatchDataMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_number_of_instruments_of_the_contract[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->abbreviated_issue_code[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name_in_en[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->group_number[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_group_id[i] = arbitrary(); }
  record->unit_trading = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->rights_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->par_value_type_code[i] = arbitrary(); }
  record->an_issue_of_which_base_price_is_settled_with_a_todays_single_price = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reevaluation_reason_code[i] = arbitrary(); }
  record->base_price_change = arbitrary();
  record->random_end_trigger_code = arbitrary();
  record->market_alert = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->market_alert_type_code[i] = arbitrary(); }
  record->korea_corporate_governance_stock_price_index_kogi = arbitrary();
  record->issue_for_administration = arbitrary();
  record->unfaithful_disclosure = arbitrary();
  record->back_door_listing = arbitrary();
  record->trading_halt = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->industry_id[i] = arbitrary(); }
  record->small_medium_sized_business = arbitrary();
  record->section_type_code = arbitrary();
  record->investment_institution_type_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->base_price[i] = arbitrary(); }
  record->yesterdays_closing_price_type_code_krx = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->yesterdays_closing_price_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->yesterdays_accumulated_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->yesterdays_accumulated_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->upper_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->substitute_price_of_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->par_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->issuing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->number_of_listed_shares[i] = arbitrary(); }
  record->liquidation_trade = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->the_establishment_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exercising_period[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expiration_date_for_right[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exercise_price_of_elw_or_bw[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->capital[i] = arbitrary(); }
  record->credit_order_possibility = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->limit_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_price_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->conditioned_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_favorable_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->first_best_order_permission_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mid_price_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->stop_limit_price_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->capital_increase_type_code[i] = arbitrary(); }
  record->other_stock_type_code = arbitrary();
  record->national_stock = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->appraised_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lowest_order_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->highest_order_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->unit_of_volume_in_main_board[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lot_size_after_hours_trading[i] = arbitrary(); }
  record->rei_ts_type_code = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->target_stock_isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency_iso_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->country_code[i] = arbitrary(); }
  record->market_making_possibility = arbitrary();
  record->closing_price_trading_possibility_in_the_after_hours = arbitrary();
  record->closing_price_trading_in_the_pre_opening_market = arbitrary();
  record->block_trading_in_the_pre_opening_market = arbitrary();
  record->basket_trading_in_the_pre_opening_market = arbitrary();
  record->announcement_of_estimated_trading_price = arbitrary();
  record->short_selling = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->etf_tracking_difference[i] = arbitrary(); }
  record->regs = arbitrary();
  record->spac = arbitrary();
  record->tax_type_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->appraisal_ratio_of_substitute_price[i] = arbitrary(); }
  record->investment_caution_issue = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->delisting_date[i] = arbitrary(); }
  record->short_term_overheat_issue_type_code = arbitrary();
  record->etf_replication_methods_type_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->distribution_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->calculation_of_redemption_price_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->calculation_of_redemption_price_end_date[i] = arbitrary(); }
  record->etp_product_type_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->index_calculation_institution_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_market_classification_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->index_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->tracking_index_leverage_inverse_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reference_index_leverage_inverse_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_asset_classification_id_1[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_asset_classification_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->ipo_underwriter_member_number[i] = arbitrary(); }
  record->lp_order = arbitrary();
  record->low_liquidity = arbitrary();
  record->abnormal_rise = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->upper_limit_quantity[i] = arbitrary(); }
  record->investment_precaution_issue = arbitrary();
  record->preferred_stocks_with_lesser_shares = arbitrary();
  record->spac_merger = arbitrary();
  record->segment_type_code = arbitrary();
  record->after_market_possibility = arbitrary();
  record->choice_on_competitive_trading = arbitrary();
  record->limit_on_competitive_trading_volume = arbitrary();
  record->occurrence_of_reasons_prohibiting_competitive_trading = arbitrary();
  record->approval_on_competitive_trading = arbitrary();
  record->approval_on_negotiation_trading = arbitrary();
  record->yesterdays_closing_price_type_code_nxt = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->yesterdays_closing_price_nxt[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->competition_board_trade_permission_code[i] = arbitrary(); }
  record->negotiation_possible_or_not_before_main_market = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Equities Batch Data Message to the wire: 551 bytes from at, returning where the next byte goes */
static size_t encode_equities_batch_data_message(const EquitiesBatchDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_number_of_instruments_of_the_contract[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->abbreviated_issue_code[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name_in_en[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->group_number[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_operation_product_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_group_id[i]; }
  wire[at++] = record->unit_trading;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->rights_type_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->par_value_type_code[i]; }
  wire[at++] = record->an_issue_of_which_base_price_is_settled_with_a_todays_single_price;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reevaluation_reason_code[i]; }
  wire[at++] = record->base_price_change;
  wire[at++] = record->random_end_trigger_code;
  wire[at++] = record->market_alert;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_alert_type_code[i]; }
  wire[at++] = record->korea_corporate_governance_stock_price_index_kogi;
  wire[at++] = record->issue_for_administration;
  wire[at++] = record->unfaithful_disclosure;
  wire[at++] = record->back_door_listing;
  wire[at++] = record->trading_halt;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->industry_id[i]; }
  wire[at++] = record->small_medium_sized_business;
  wire[at++] = record->section_type_code;
  wire[at++] = record->investment_institution_type_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->base_price[i]; }
  wire[at++] = record->yesterdays_closing_price_type_code_krx;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->yesterdays_closing_price_krx[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->yesterdays_accumulated_trading_amount[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->yesterdays_accumulated_trading_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->substitute_price_of_securities[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->par_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issuing_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->listing_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->number_of_listed_shares[i]; }
  wire[at++] = record->liquidation_trade;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->the_establishment_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exercising_period[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiration_date_for_right[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exercise_price_of_elw_or_bw[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->capital[i]; }
  wire[at++] = record->credit_order_possibility;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->limit_order_permission_type_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_price_order_permission_type_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->conditioned_order_permission_type_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_favorable_order_permission_type_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_best_order_permission_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mid_price_order_permission_type_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->stop_limit_price_order_permission_type_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->capital_increase_type_code[i]; }
  wire[at++] = record->other_stock_type_code;
  wire[at++] = record->national_stock;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appraised_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lowest_order_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->highest_order_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->unit_of_volume_in_main_board[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lot_size_after_hours_trading[i]; }
  wire[at++] = record->rei_ts_type_code;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->target_stock_isin_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency_iso_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->country_code[i]; }
  wire[at++] = record->market_making_possibility;
  wire[at++] = record->closing_price_trading_possibility_in_the_after_hours;
  wire[at++] = record->closing_price_trading_in_the_pre_opening_market;
  wire[at++] = record->block_trading_in_the_pre_opening_market;
  wire[at++] = record->basket_trading_in_the_pre_opening_market;
  wire[at++] = record->announcement_of_estimated_trading_price;
  wire[at++] = record->short_selling;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->etf_tracking_difference[i]; }
  wire[at++] = record->regs;
  wire[at++] = record->spac;
  wire[at++] = record->tax_type_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appraisal_ratio_of_substitute_price[i]; }
  wire[at++] = record->investment_caution_issue;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->delisting_date[i]; }
  wire[at++] = record->short_term_overheat_issue_type_code;
  wire[at++] = record->etf_replication_methods_type_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->distribution_type_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->calculation_of_redemption_price_start_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->calculation_of_redemption_price_end_date[i]; }
  wire[at++] = record->etp_product_type_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->index_calculation_institution_type_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_market_classification_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->index_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->tracking_index_leverage_inverse_type_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reference_index_leverage_inverse_type_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_asset_classification_id_1[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_asset_classification_id_2[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->ipo_underwriter_member_number[i]; }
  wire[at++] = record->lp_order;
  wire[at++] = record->low_liquidity;
  wire[at++] = record->abnormal_rise;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->upper_limit_quantity[i]; }
  wire[at++] = record->investment_precaution_issue;
  wire[at++] = record->preferred_stocks_with_lesser_shares;
  wire[at++] = record->spac_merger;
  wire[at++] = record->segment_type_code;
  wire[at++] = record->after_market_possibility;
  wire[at++] = record->choice_on_competitive_trading;
  wire[at++] = record->limit_on_competitive_trading_volume;
  wire[at++] = record->occurrence_of_reasons_prohibiting_competitive_trading;
  wire[at++] = record->approval_on_competitive_trading;
  wire[at++] = record->approval_on_negotiation_trading;
  wire[at++] = record->yesterdays_closing_price_type_code_nxt;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->yesterdays_closing_price_nxt[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->competition_board_trade_permission_code[i]; }
  wire[at++] = record->negotiation_possible_or_not_before_main_market;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Equities Batch Data Message off the wire: 551 bytes from at, returning where the next byte lies */
static size_t decode_equities_batch_data_message(EquitiesBatchDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_number_of_instruments_of_the_contract[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->abbreviated_issue_code[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name_in_en[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->group_number[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_group_id[i] = wire[at++]; }
  record->unit_trading = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->rights_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->par_value_type_code[i] = wire[at++]; }
  record->an_issue_of_which_base_price_is_settled_with_a_todays_single_price = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reevaluation_reason_code[i] = wire[at++]; }
  record->base_price_change = wire[at++];
  record->random_end_trigger_code = wire[at++];
  record->market_alert = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->market_alert_type_code[i] = wire[at++]; }
  record->korea_corporate_governance_stock_price_index_kogi = wire[at++];
  record->issue_for_administration = wire[at++];
  record->unfaithful_disclosure = wire[at++];
  record->back_door_listing = wire[at++];
  record->trading_halt = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->industry_id[i] = wire[at++]; }
  record->small_medium_sized_business = wire[at++];
  record->section_type_code = wire[at++];
  record->investment_institution_type_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->base_price[i] = wire[at++]; }
  record->yesterdays_closing_price_type_code_krx = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->yesterdays_closing_price_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->yesterdays_accumulated_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->yesterdays_accumulated_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->upper_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->substitute_price_of_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->par_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->issuing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->number_of_listed_shares[i] = wire[at++]; }
  record->liquidation_trade = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->the_establishment_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exercising_period[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expiration_date_for_right[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exercise_price_of_elw_or_bw[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->capital[i] = wire[at++]; }
  record->credit_order_possibility = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->limit_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_price_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->conditioned_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_favorable_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->first_best_order_permission_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mid_price_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->stop_limit_price_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->capital_increase_type_code[i] = wire[at++]; }
  record->other_stock_type_code = wire[at++];
  record->national_stock = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->appraised_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lowest_order_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->highest_order_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->unit_of_volume_in_main_board[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lot_size_after_hours_trading[i] = wire[at++]; }
  record->rei_ts_type_code = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->target_stock_isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency_iso_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->country_code[i] = wire[at++]; }
  record->market_making_possibility = wire[at++];
  record->closing_price_trading_possibility_in_the_after_hours = wire[at++];
  record->closing_price_trading_in_the_pre_opening_market = wire[at++];
  record->block_trading_in_the_pre_opening_market = wire[at++];
  record->basket_trading_in_the_pre_opening_market = wire[at++];
  record->announcement_of_estimated_trading_price = wire[at++];
  record->short_selling = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->etf_tracking_difference[i] = wire[at++]; }
  record->regs = wire[at++];
  record->spac = wire[at++];
  record->tax_type_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->appraisal_ratio_of_substitute_price[i] = wire[at++]; }
  record->investment_caution_issue = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->delisting_date[i] = wire[at++]; }
  record->short_term_overheat_issue_type_code = wire[at++];
  record->etf_replication_methods_type_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->distribution_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->calculation_of_redemption_price_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->calculation_of_redemption_price_end_date[i] = wire[at++]; }
  record->etp_product_type_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->index_calculation_institution_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_market_classification_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->index_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->tracking_index_leverage_inverse_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reference_index_leverage_inverse_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_asset_classification_id_1[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_asset_classification_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->ipo_underwriter_member_number[i] = wire[at++]; }
  record->lp_order = wire[at++];
  record->low_liquidity = wire[at++];
  record->abnormal_rise = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->upper_limit_quantity[i] = wire[at++]; }
  record->investment_precaution_issue = wire[at++];
  record->preferred_stocks_with_lesser_shares = wire[at++];
  record->spac_merger = wire[at++];
  record->segment_type_code = wire[at++];
  record->after_market_possibility = wire[at++];
  record->choice_on_competitive_trading = wire[at++];
  record->limit_on_competitive_trading_volume = wire[at++];
  record->occurrence_of_reasons_prohibiting_competitive_trading = wire[at++];
  record->approval_on_competitive_trading = wire[at++];
  record->approval_on_negotiation_trading = wire[at++];
  record->yesterdays_closing_price_type_code_nxt = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->yesterdays_closing_price_nxt[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->competition_board_trade_permission_code[i] = wire[at++]; }
  record->negotiation_possible_or_not_before_main_market = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Equities Batch Data Message is what was written, byte for byte */
static void equal_equities_batch_data_message(const EquitiesBatchDataMessage *read, const EquitiesBatchDataMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_number_of_instruments_of_the_contract[i] == written->total_number_of_instruments_of_the_contract[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->abbreviated_issue_code[i] == written->abbreviated_issue_code[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name[i] == written->abbreviated_issue_name[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name_in_en[i] == written->abbreviated_issue_name_in_en[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->group_number[i] == written->group_number[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->market_operation_product_id[i] == written->market_operation_product_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_group_id[i] == written->security_group_id[i]); }
  assert(read->unit_trading == written->unit_trading);
  for (size_t i = 0; i < 2; i++) { assert(read->rights_type_code[i] == written->rights_type_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->par_value_type_code[i] == written->par_value_type_code[i]); }
  assert(read->an_issue_of_which_base_price_is_settled_with_a_todays_single_price == written->an_issue_of_which_base_price_is_settled_with_a_todays_single_price);
  for (size_t i = 0; i < 2; i++) { assert(read->reevaluation_reason_code[i] == written->reevaluation_reason_code[i]); }
  assert(read->base_price_change == written->base_price_change);
  assert(read->random_end_trigger_code == written->random_end_trigger_code);
  assert(read->market_alert == written->market_alert);
  for (size_t i = 0; i < 2; i++) { assert(read->market_alert_type_code[i] == written->market_alert_type_code[i]); }
  assert(read->korea_corporate_governance_stock_price_index_kogi == written->korea_corporate_governance_stock_price_index_kogi);
  assert(read->issue_for_administration == written->issue_for_administration);
  assert(read->unfaithful_disclosure == written->unfaithful_disclosure);
  assert(read->back_door_listing == written->back_door_listing);
  assert(read->trading_halt == written->trading_halt);
  for (size_t i = 0; i < 10; i++) { assert(read->industry_id[i] == written->industry_id[i]); }
  assert(read->small_medium_sized_business == written->small_medium_sized_business);
  assert(read->section_type_code == written->section_type_code);
  assert(read->investment_institution_type_code == written->investment_institution_type_code);
  for (size_t i = 0; i < 8; i++) { assert(read->base_price[i] == written->base_price[i]); }
  assert(read->yesterdays_closing_price_type_code_krx == written->yesterdays_closing_price_type_code_krx);
  for (size_t i = 0; i < 8; i++) { assert(read->yesterdays_closing_price_krx[i] == written->yesterdays_closing_price_krx[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->yesterdays_accumulated_trading_amount[i] == written->yesterdays_accumulated_trading_amount[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->yesterdays_accumulated_trading_value[i] == written->yesterdays_accumulated_trading_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->upper_limit_price[i] == written->upper_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower_limit_price[i] == written->lower_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->substitute_price_of_securities[i] == written->substitute_price_of_securities[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->par_value[i] == written->par_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->issuing_price[i] == written->issuing_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->listing_date[i] == written->listing_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->number_of_listed_shares[i] == written->number_of_listed_shares[i]); }
  assert(read->liquidation_trade == written->liquidation_trade);
  for (size_t i = 0; i < 8; i++) { assert(read->the_establishment_date[i] == written->the_establishment_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exercising_period[i] == written->exercising_period[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expiration_date_for_right[i] == written->expiration_date_for_right[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exercise_price_of_elw_or_bw[i] == written->exercise_price_of_elw_or_bw[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->capital[i] == written->capital[i]); }
  assert(read->credit_order_possibility == written->credit_order_possibility);
  for (size_t i = 0; i < 4; i++) { assert(read->limit_order_permission_type_code[i] == written->limit_order_permission_type_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_price_order_permission_type_code[i] == written->market_price_order_permission_type_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->conditioned_order_permission_type_code[i] == written->conditioned_order_permission_type_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_favorable_order_permission_type_code[i] == written->best_favorable_order_permission_type_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->first_best_order_permission_type[i] == written->first_best_order_permission_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mid_price_order_permission_type_code[i] == written->mid_price_order_permission_type_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->stop_limit_price_order_permission_type_code[i] == written->stop_limit_price_order_permission_type_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->capital_increase_type_code[i] == written->capital_increase_type_code[i]); }
  assert(read->other_stock_type_code == written->other_stock_type_code);
  assert(read->national_stock == written->national_stock);
  for (size_t i = 0; i < 8; i++) { assert(read->appraised_price[i] == written->appraised_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lowest_order_price[i] == written->lowest_order_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->highest_order_price[i] == written->highest_order_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->unit_of_volume_in_main_board[i] == written->unit_of_volume_in_main_board[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lot_size_after_hours_trading[i] == written->lot_size_after_hours_trading[i]); }
  assert(read->rei_ts_type_code == written->rei_ts_type_code);
  for (size_t i = 0; i < 12; i++) { assert(read->target_stock_isin_code[i] == written->target_stock_isin_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency_iso_code[i] == written->currency_iso_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->country_code[i] == written->country_code[i]); }
  assert(read->market_making_possibility == written->market_making_possibility);
  assert(read->closing_price_trading_possibility_in_the_after_hours == written->closing_price_trading_possibility_in_the_after_hours);
  assert(read->closing_price_trading_in_the_pre_opening_market == written->closing_price_trading_in_the_pre_opening_market);
  assert(read->block_trading_in_the_pre_opening_market == written->block_trading_in_the_pre_opening_market);
  assert(read->basket_trading_in_the_pre_opening_market == written->basket_trading_in_the_pre_opening_market);
  assert(read->announcement_of_estimated_trading_price == written->announcement_of_estimated_trading_price);
  assert(read->short_selling == written->short_selling);
  for (size_t i = 0; i < 8; i++) { assert(read->etf_tracking_difference[i] == written->etf_tracking_difference[i]); }
  assert(read->regs == written->regs);
  assert(read->spac == written->spac);
  assert(read->tax_type_code == written->tax_type_code);
  for (size_t i = 0; i < 8; i++) { assert(read->appraisal_ratio_of_substitute_price[i] == written->appraisal_ratio_of_substitute_price[i]); }
  assert(read->investment_caution_issue == written->investment_caution_issue);
  for (size_t i = 0; i < 8; i++) { assert(read->delisting_date[i] == written->delisting_date[i]); }
  assert(read->short_term_overheat_issue_type_code == written->short_term_overheat_issue_type_code);
  assert(read->etf_replication_methods_type_code == written->etf_replication_methods_type_code);
  for (size_t i = 0; i < 8; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->distribution_type_code[i] == written->distribution_type_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->calculation_of_redemption_price_start_date[i] == written->calculation_of_redemption_price_start_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->calculation_of_redemption_price_end_date[i] == written->calculation_of_redemption_price_end_date[i]); }
  assert(read->etp_product_type_code == written->etp_product_type_code);
  for (size_t i = 0; i < 2; i++) { assert(read->index_calculation_institution_type_code[i] == written->index_calculation_institution_type_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_market_classification_id[i] == written->index_market_classification_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->index_sequence_number[i] == written->index_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->tracking_index_leverage_inverse_type_code[i] == written->tracking_index_leverage_inverse_type_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reference_index_leverage_inverse_type_code[i] == written->reference_index_leverage_inverse_type_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_asset_classification_id_1[i] == written->index_asset_classification_id_1[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_asset_classification_id_2[i] == written->index_asset_classification_id_2[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->ipo_underwriter_member_number[i] == written->ipo_underwriter_member_number[i]); }
  assert(read->lp_order == written->lp_order);
  assert(read->low_liquidity == written->low_liquidity);
  assert(read->abnormal_rise == written->abnormal_rise);
  for (size_t i = 0; i < 16; i++) { assert(read->upper_limit_quantity[i] == written->upper_limit_quantity[i]); }
  assert(read->investment_precaution_issue == written->investment_precaution_issue);
  assert(read->preferred_stocks_with_lesser_shares == written->preferred_stocks_with_lesser_shares);
  assert(read->spac_merger == written->spac_merger);
  assert(read->segment_type_code == written->segment_type_code);
  assert(read->after_market_possibility == written->after_market_possibility);
  assert(read->choice_on_competitive_trading == written->choice_on_competitive_trading);
  assert(read->limit_on_competitive_trading_volume == written->limit_on_competitive_trading_volume);
  assert(read->occurrence_of_reasons_prohibiting_competitive_trading == written->occurrence_of_reasons_prohibiting_competitive_trading);
  assert(read->approval_on_competitive_trading == written->approval_on_competitive_trading);
  assert(read->approval_on_negotiation_trading == written->approval_on_negotiation_trading);
  assert(read->yesterdays_closing_price_type_code_nxt == written->yesterdays_closing_price_type_code_nxt);
  for (size_t i = 0; i < 8; i++) { assert(read->yesterdays_closing_price_nxt[i] == written->yesterdays_closing_price_nxt[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->competition_board_trade_permission_code[i] == written->competition_board_trade_permission_code[i]); }
  assert(read->negotiation_possible_or_not_before_main_market == written->negotiation_possible_or_not_before_main_market);
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Equities Batch Data Message: written and read back, then read and written back */
static void check_equities_batch_data_message(void) {
  EquitiesBatchDataMessage sent;
  EquitiesBatchDataMessage got;
  uint8_t wire[551];
  uint8_t again[551];

  any_equities_batch_data_message(&sent);
  assert(encode_equities_batch_data_message(&sent, wire, 0) == 551);
  assert(decode_equities_batch_data_message(&got, wire, 0) == 551);
  equal_equities_batch_data_message(&got, &sent);

  for (size_t i = 0; i < 551; i++) { wire[i] = arbitrary(); }
  assert(decode_equities_batch_data_message(&got, wire, 0) == 551);
  assert(encode_equities_batch_data_message(&got, again, 0) == 551);
  for (size_t i = 0; i < 551; i++) { assert(again[i] == wire[i]); }
}

/* ---- Member Information Message: 201 bytes ----------------------------------- */

/* Details. */
typedef struct {
  uint8_t message_sequence_number[4];                             /* bytes 0 to 3 */
  uint8_t business_date[8];                                       /* bytes 4 to 11 */
  uint8_t market_participant_number[5];                           /* bytes 12 to 16 */
  uint8_t name_of_a_market_participant_in_kr[80];                 /* bytes 17 to 96 */
  uint8_t name_of_a_market_participant_in_en[80];                 /* bytes 97 to 176 */
  uint8_t an_abbreviated_name_of_a_market_participant_in_kr[20];  /* bytes 177 to 196 */
  uint8_t end_keyword[4];                                         /* bytes 197 to 200 */
} MemberInformationMessage;

/* any Member Information Message at all: every byte one the checker chooses */
static void any_member_information_message(MemberInformationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->market_participant_number[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->name_of_a_market_participant_in_kr[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->name_of_a_market_participant_in_en[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->an_abbreviated_name_of_a_market_participant_in_kr[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Member Information Message to the wire: 201 bytes from at, returning where the next byte goes */
static size_t encode_member_information_message(const MemberInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->market_participant_number[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->name_of_a_market_participant_in_kr[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->name_of_a_market_participant_in_en[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->an_abbreviated_name_of_a_market_participant_in_kr[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Member Information Message off the wire: 201 bytes from at, returning where the next byte lies */
static size_t decode_member_information_message(MemberInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->market_participant_number[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->name_of_a_market_participant_in_kr[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->name_of_a_market_participant_in_en[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->an_abbreviated_name_of_a_market_participant_in_kr[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Member Information Message is what was written, byte for byte */
static void equal_member_information_message(const MemberInformationMessage *read, const MemberInformationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->market_participant_number[i] == written->market_participant_number[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->name_of_a_market_participant_in_kr[i] == written->name_of_a_market_participant_in_kr[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->name_of_a_market_participant_in_en[i] == written->name_of_a_market_participant_in_en[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->an_abbreviated_name_of_a_market_participant_in_kr[i] == written->an_abbreviated_name_of_a_market_participant_in_kr[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Member Information Message: written and read back, then read and written back */
static void check_member_information_message(void) {
  MemberInformationMessage sent;
  MemberInformationMessage got;
  uint8_t wire[201];
  uint8_t again[201];

  any_member_information_message(&sent);
  assert(encode_member_information_message(&sent, wire, 0) == 201);
  assert(decode_member_information_message(&got, wire, 0) == 201);
  equal_member_information_message(&got, &sent);

  for (size_t i = 0; i < 201; i++) { wire[i] = arbitrary(); }
  assert(decode_member_information_message(&got, wire, 0) == 201);
  assert(encode_member_information_message(&got, again, 0) == 201);
  for (size_t i = 0; i < 201; i++) { assert(again[i] == wire[i]); }
}

/* ---- Issue Event Message: 42 bytes ------------------------------------------- */

/* Details. */
typedef struct {
  uint8_t message_sequence_number[4];  /* bytes 0 to 3 */
  uint8_t isin_code[12];               /* bytes 4 to 15 */
  uint8_t event_type_code[2];          /* bytes 16 to 17 */
  uint8_t event_reason_code[4];        /* bytes 18 to 21 */
  uint8_t event_start_date[8];         /* bytes 22 to 29 */
  uint8_t event_end_date[8];           /* bytes 30 to 37 */
  uint8_t end_keyword[4];              /* bytes 38 to 41 */
} IssueEventMessage;

/* any Issue Event Message at all: every byte one the checker chooses */
static void any_issue_event_message(IssueEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->event_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->event_reason_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_end_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Issue Event Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_issue_event_message(const IssueEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->event_type_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_reason_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_start_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_end_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Issue Event Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_issue_event_message(IssueEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->event_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->event_reason_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_end_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Issue Event Message is what was written, byte for byte */
static void equal_issue_event_message(const IssueEventMessage *read, const IssueEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->event_type_code[i] == written->event_type_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->event_reason_code[i] == written->event_reason_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_start_date[i] == written->event_start_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_end_date[i] == written->event_end_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Issue Event Message: written and read back, then read and written back */
static void check_issue_event_message(void) {
  IssueEventMessage sent;
  IssueEventMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_issue_event_message(&sent);
  assert(encode_issue_event_message(&sent, wire, 0) == 42);
  assert(decode_issue_event_message(&got, wire, 0) == 42);
  equal_issue_event_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_issue_event_message(&got, wire, 0) == 42);
  assert(encode_issue_event_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Block Basket Trade Data Message: 46 bytes ------------------------------- */

/* Block/Basket Trade Data in NXT. */
typedef struct {
  uint8_t board_id[2];                                   /* bytes 0 to 1 */
  uint8_t isin_code[12];                                 /* bytes 2 to 13 */
  uint8_t a_designated_number_for_an_issue_from_krx[4];  /* bytes 14 to 17 */
  uint8_t accumulated_trading_volume[8];                 /* bytes 18 to 25 */
  uint8_t accumulated_trading_value[16];                 /* bytes 26 to 41 */
  uint8_t end_keyword[4];                                /* bytes 42 to 45 */
} BlockBasketTradeDataMessage;

/* any Block Basket Trade Data Message at all: every byte one the checker chooses */
static void any_block_basket_trade_data_message(BlockBasketTradeDataMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->accumulated_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Block Basket Trade Data Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_block_basket_trade_data_message(const BlockBasketTradeDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->accumulated_trading_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Block Basket Trade Data Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_block_basket_trade_data_message(BlockBasketTradeDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->accumulated_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Block Basket Trade Data Message is what was written, byte for byte */
static void equal_block_basket_trade_data_message(const BlockBasketTradeDataMessage *read, const BlockBasketTradeDataMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->accumulated_trading_value[i] == written->accumulated_trading_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Block Basket Trade Data Message: written and read back, then read and written back */
static void check_block_basket_trade_data_message(void) {
  BlockBasketTradeDataMessage sent;
  BlockBasketTradeDataMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_block_basket_trade_data_message(&sent);
  assert(encode_block_basket_trade_data_message(&sent, wire, 0) == 46);
  assert(decode_block_basket_trade_data_message(&got, wire, 0) == 46);
  equal_block_basket_trade_data_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_block_basket_trade_data_message(&got, wire, 0) == 46);
  assert(encode_block_basket_trade_data_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Investor Activities Per An Issue Eod Message: 72 bytes ------------------ */

/* Investor Activities per an issue_EOD. */
typedef struct {
  uint8_t isin_code[12];                                 /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue_from_krx[4];  /* bytes 12 to 15 */
  uint8_t investor_code[4];                              /* bytes 16 to 19 */
  uint8_t accumulated_ask_trading_volume[8];             /* bytes 20 to 27 */
  uint8_t accumulated_ask_trading_value[16];             /* bytes 28 to 43 */
  uint8_t accumulated_bid_trading_volume[8];             /* bytes 44 to 51 */
  uint8_t accumulated_bid_trading_value[16];             /* bytes 52 to 67 */
  uint8_t end_keyword[4];                                /* bytes 68 to 71 */
} InvestorActivitiesPerAnIssueEodMessage;

/* any Investor Activities Per An Issue Eod Message at all: every byte one the checker chooses */
static void any_investor_activities_per_an_issue_eod_message(InvestorActivitiesPerAnIssueEodMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accumulated_ask_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->accumulated_ask_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accumulated_bid_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->accumulated_bid_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Investor Activities Per An Issue Eod Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_investor_activities_per_an_issue_eod_message(const InvestorActivitiesPerAnIssueEodMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->investor_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accumulated_ask_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->accumulated_ask_trading_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accumulated_bid_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->accumulated_bid_trading_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Investor Activities Per An Issue Eod Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_investor_activities_per_an_issue_eod_message(InvestorActivitiesPerAnIssueEodMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accumulated_ask_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->accumulated_ask_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accumulated_bid_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->accumulated_bid_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Investor Activities Per An Issue Eod Message is what was written, byte for byte */
static void equal_investor_activities_per_an_issue_eod_message(const InvestorActivitiesPerAnIssueEodMessage *read, const InvestorActivitiesPerAnIssueEodMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->investor_code[i] == written->investor_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accumulated_ask_trading_volume[i] == written->accumulated_ask_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->accumulated_ask_trading_value[i] == written->accumulated_ask_trading_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accumulated_bid_trading_volume[i] == written->accumulated_bid_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->accumulated_bid_trading_value[i] == written->accumulated_bid_trading_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Investor Activities Per An Issue Eod Message: written and read back, then read and written back */
static void check_investor_activities_per_an_issue_eod_message(void) {
  InvestorActivitiesPerAnIssueEodMessage sent;
  InvestorActivitiesPerAnIssueEodMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_investor_activities_per_an_issue_eod_message(&sent);
  assert(encode_investor_activities_per_an_issue_eod_message(&sent, wire, 0) == 72);
  assert(decode_investor_activities_per_an_issue_eod_message(&got, wire, 0) == 72);
  equal_investor_activities_per_an_issue_eod_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_investor_activities_per_an_issue_eod_message(&got, wire, 0) == 72);
  assert(encode_investor_activities_per_an_issue_eod_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Selling Message: 88 bytes ----------------------------------------- */

/* Short Selling. */
typedef struct {
  uint8_t isin_code[12];                                                  /* bytes 0 to 11 */
  uint8_t covered_short_selling_trading_volume[8];                        /* bytes 12 to 19 */
  uint8_t covered_short_selling_trading_value[16];                        /* bytes 20 to 35 */
  uint8_t uptick_rule_applied_covered_short_selling_trading_volume[8];    /* bytes 36 to 43 */
  uint8_t uptick_rule_applied_covered_short_selling_trading_value[16];    /* bytes 44 to 59 */
  uint8_t uptick_rule_unapplied_covered_short_selling_trading_volume[8];  /* bytes 60 to 67 */
  uint8_t uptick_rule_unapplied_covered_short_selling_trading_value[16];  /* bytes 68 to 83 */
  uint8_t end_keyword[4];                                                 /* bytes 84 to 87 */
} ShortSellingMessage;

/* any Short Selling Message at all: every byte one the checker chooses */
static void any_short_selling_message(ShortSellingMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->covered_short_selling_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->covered_short_selling_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->uptick_rule_applied_covered_short_selling_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->uptick_rule_applied_covered_short_selling_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->uptick_rule_unapplied_covered_short_selling_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->uptick_rule_unapplied_covered_short_selling_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Short Selling Message to the wire: 88 bytes from at, returning where the next byte goes */
static size_t encode_short_selling_message(const ShortSellingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->covered_short_selling_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->covered_short_selling_trading_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uptick_rule_applied_covered_short_selling_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->uptick_rule_applied_covered_short_selling_trading_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uptick_rule_unapplied_covered_short_selling_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->uptick_rule_unapplied_covered_short_selling_trading_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Short Selling Message off the wire: 88 bytes from at, returning where the next byte lies */
static size_t decode_short_selling_message(ShortSellingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->covered_short_selling_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->covered_short_selling_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->uptick_rule_applied_covered_short_selling_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->uptick_rule_applied_covered_short_selling_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->uptick_rule_unapplied_covered_short_selling_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->uptick_rule_unapplied_covered_short_selling_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Short Selling Message is what was written, byte for byte */
static void equal_short_selling_message(const ShortSellingMessage *read, const ShortSellingMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->covered_short_selling_trading_volume[i] == written->covered_short_selling_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->covered_short_selling_trading_value[i] == written->covered_short_selling_trading_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->uptick_rule_applied_covered_short_selling_trading_volume[i] == written->uptick_rule_applied_covered_short_selling_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->uptick_rule_applied_covered_short_selling_trading_value[i] == written->uptick_rule_applied_covered_short_selling_trading_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->uptick_rule_unapplied_covered_short_selling_trading_volume[i] == written->uptick_rule_unapplied_covered_short_selling_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->uptick_rule_unapplied_covered_short_selling_trading_value[i] == written->uptick_rule_unapplied_covered_short_selling_trading_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Short Selling Message: written and read back, then read and written back */
static void check_short_selling_message(void) {
  ShortSellingMessage sent;
  ShortSellingMessage got;
  uint8_t wire[88];
  uint8_t again[88];

  any_short_selling_message(&sent);
  assert(encode_short_selling_message(&sent, wire, 0) == 88);
  assert(decode_short_selling_message(&got, wire, 0) == 88);
  equal_short_selling_message(&got, &sent);

  for (size_t i = 0; i < 88; i++) { wire[i] = arbitrary(); }
  assert(decode_short_selling_message(&got, wire, 0) == 88);
  assert(encode_short_selling_message(&got, again, 0) == 88);
  for (size_t i = 0; i < 88; i++) { assert(again[i] == wire[i]); }
}

/* ---- Brokers Acitity Information Message: 69 bytes --------------------------- */

/* Information on Brokers Activity in NXT market. */
typedef struct {
  uint8_t isin_code[12];                      /* bytes 0 to 11 */
  uint8_t member_number[5];                   /* bytes 12 to 16 */
  uint8_t accumulated_ask_trading_volume[8];  /* bytes 17 to 24 */
  uint8_t accumulated_ask_trading_value[16];  /* bytes 25 to 40 */
  uint8_t accumulated_bid_trading_volume[8];  /* bytes 41 to 48 */
  uint8_t accumulated_bid_trading_value[16];  /* bytes 49 to 64 */
  uint8_t end_keyword[4];                     /* bytes 65 to 68 */
} BrokersAcitityInformationMessage;

/* any Brokers Acitity Information Message at all: every byte one the checker chooses */
static void any_brokers_acitity_information_message(BrokersAcitityInformationMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accumulated_ask_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->accumulated_ask_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accumulated_bid_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->accumulated_bid_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Brokers Acitity Information Message to the wire: 69 bytes from at, returning where the next byte goes */
static size_t encode_brokers_acitity_information_message(const BrokersAcitityInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accumulated_ask_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->accumulated_ask_trading_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accumulated_bid_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->accumulated_bid_trading_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Brokers Acitity Information Message off the wire: 69 bytes from at, returning where the next byte lies */
static size_t decode_brokers_acitity_information_message(BrokersAcitityInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accumulated_ask_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->accumulated_ask_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accumulated_bid_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->accumulated_bid_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Brokers Acitity Information Message is what was written, byte for byte */
static void equal_brokers_acitity_information_message(const BrokersAcitityInformationMessage *read, const BrokersAcitityInformationMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number[i] == written->member_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accumulated_ask_trading_volume[i] == written->accumulated_ask_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->accumulated_ask_trading_value[i] == written->accumulated_ask_trading_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accumulated_bid_trading_volume[i] == written->accumulated_bid_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->accumulated_bid_trading_value[i] == written->accumulated_bid_trading_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Brokers Acitity Information Message: written and read back, then read and written back */
static void check_brokers_acitity_information_message(void) {
  BrokersAcitityInformationMessage sent;
  BrokersAcitityInformationMessage got;
  uint8_t wire[69];
  uint8_t again[69];

  any_brokers_acitity_information_message(&sent);
  assert(encode_brokers_acitity_information_message(&sent, wire, 0) == 69);
  assert(decode_brokers_acitity_information_message(&got, wire, 0) == 69);
  equal_brokers_acitity_information_message(&got, &sent);

  for (size_t i = 0; i < 69; i++) { wire[i] = arbitrary(); }
  assert(decode_brokers_acitity_information_message(&got, wire, 0) == 69);
  assert(encode_brokers_acitity_information_message(&got, again, 0) == 69);
  for (size_t i = 0; i < 69; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Activity By Session Per An Issue Message: 92 bytes -------------- */

/* Trading Activity by session for each issue and market. */
typedef struct {
  uint8_t isin_code[12];                                              /* bytes 0 to 11 */
  uint8_t total_number_of_tradable_issues_on_competitive_trading[4];  /* bytes 12 to 15 */
  uint8_t pre_market_accumulated_trading_volume[8];                   /* bytes 16 to 23 */
  uint8_t pre_market_accumulated_trading_value[16];                   /* bytes 24 to 39 */
  uint8_t main_market_accumulated_trading_volume[8];                  /* bytes 40 to 47 */
  uint8_t main_market_accumulated_trading_value[16];                  /* bytes 48 to 63 */
  uint8_t after_market_accumulated_trading_volume[8];                 /* bytes 64 to 71 */
  uint8_t after_market_accumulated_trading_value[16];                 /* bytes 72 to 87 */
  uint8_t end_keyword[4];                                             /* bytes 88 to 91 */
} TradingActivityBySessionPerAnIssueMessage;

/* any Trading Activity By Session Per An Issue Message at all: every byte one the checker chooses */
static void any_trading_activity_by_session_per_an_issue_message(TradingActivityBySessionPerAnIssueMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_number_of_tradable_issues_on_competitive_trading[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pre_market_accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->pre_market_accumulated_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->main_market_accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->main_market_accumulated_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->after_market_accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->after_market_accumulated_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = arbitrary(); }
}

/* Trading Activity By Session Per An Issue Message to the wire: 92 bytes from at, returning where the next byte goes */
static size_t encode_trading_activity_by_session_per_an_issue_message(const TradingActivityBySessionPerAnIssueMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_number_of_tradable_issues_on_competitive_trading[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pre_market_accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->pre_market_accumulated_trading_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->main_market_accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->main_market_accumulated_trading_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->after_market_accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->after_market_accumulated_trading_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_keyword[i]; }

  return at;
}

/* Trading Activity By Session Per An Issue Message off the wire: 92 bytes from at, returning where the next byte lies */
static size_t decode_trading_activity_by_session_per_an_issue_message(TradingActivityBySessionPerAnIssueMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_number_of_tradable_issues_on_competitive_trading[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pre_market_accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->pre_market_accumulated_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->main_market_accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->main_market_accumulated_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->after_market_accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->after_market_accumulated_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_keyword[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Activity By Session Per An Issue Message is what was written, byte for byte */
static void equal_trading_activity_by_session_per_an_issue_message(const TradingActivityBySessionPerAnIssueMessage *read, const TradingActivityBySessionPerAnIssueMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_number_of_tradable_issues_on_competitive_trading[i] == written->total_number_of_tradable_issues_on_competitive_trading[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pre_market_accumulated_trading_volume[i] == written->pre_market_accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->pre_market_accumulated_trading_value[i] == written->pre_market_accumulated_trading_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->main_market_accumulated_trading_volume[i] == written->main_market_accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->main_market_accumulated_trading_value[i] == written->main_market_accumulated_trading_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->after_market_accumulated_trading_volume[i] == written->after_market_accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->after_market_accumulated_trading_value[i] == written->after_market_accumulated_trading_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_keyword[i] == written->end_keyword[i]); }
}

/* Trading Activity By Session Per An Issue Message: written and read back, then read and written back */
static void check_trading_activity_by_session_per_an_issue_message(void) {
  TradingActivityBySessionPerAnIssueMessage sent;
  TradingActivityBySessionPerAnIssueMessage got;
  uint8_t wire[92];
  uint8_t again[92];

  any_trading_activity_by_session_per_an_issue_message(&sent);
  assert(encode_trading_activity_by_session_per_an_issue_message(&sent, wire, 0) == 92);
  assert(decode_trading_activity_by_session_per_an_issue_message(&got, wire, 0) == 92);
  equal_trading_activity_by_session_per_an_issue_message(&got, &sent);

  for (size_t i = 0; i < 92; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_activity_by_session_per_an_issue_message(&got, wire, 0) == 92);
  assert(encode_trading_activity_by_session_per_an_issue_message(&got, again, 0) == 92);
  for (size_t i = 0; i < 92; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_polling_data_message();
  check_securities_quote_mm_lp_quotes_included10_level_message();
  check_securities_order_filled_message();
  check_market_operation_ts_message();
  check_issue_closing_message();
  check_triggering_removing_vi_message();
  check_closing_price_trading_quote_message();
  check_equities_snapshot_mm_lp_quotes_included10_level_message();
  check_investor_activities_per_commodities_message();
  check_etp_constituents_message();
  check_mm_lp_information_message();
  check_market_operation_schedule_message();
  check_member_firm_imposing_lifting_sanctions_message();
  check_top_five_traders_activities_message();
  check_equities_batch_data_message();
  check_member_information_message();
  check_issue_event_message();
  check_block_basket_trade_data_message();
  check_investor_activities_per_an_issue_eod_message();
  check_short_selling_message();
  check_brokers_acitity_information_message();
  check_trading_activity_by_session_per_an_issue_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
