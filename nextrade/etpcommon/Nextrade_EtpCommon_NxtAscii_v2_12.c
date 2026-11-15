// nextrade/etpcommon/Nextrade_EtpCommon_NxtAscii_v2_12.c
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

/* ---- Securities Quote Mm Lp Quotes Included 10 Level Message: 825 bytes ------ */

/* Securities_Quote (MM/LP Quotes Included, 10 Level) Best Order Data on NXT Trading Items provided - MM/LP Quotes Included * 10 Level Best Order on Ask/Bid. */
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
  uint8_t ask_level_4_price[11];                                         /* bytes 252 to 262 */
  uint8_t bid_level_4_price[11];                                         /* bytes 263 to 273 */
  uint8_t ask_level_4_volume[12];                                        /* bytes 274 to 285 */
  uint8_t bid_level_4_volume[12];                                        /* bytes 286 to 297 */
  uint8_t lp_ask_level_4_volume[12];                                     /* bytes 298 to 309 */
  uint8_t lp_bid_level_4_volume[12];                                     /* bytes 310 to 321 */
  uint8_t ask_level_5_price[11];                                         /* bytes 322 to 332 */
  uint8_t bid_level_5_price[11];                                         /* bytes 333 to 343 */
  uint8_t ask_level_5_volume[12];                                        /* bytes 344 to 355 */
  uint8_t bid_level_5_volume[12];                                        /* bytes 356 to 367 */
  uint8_t lp_ask_level_5_volume[12];                                     /* bytes 368 to 379 */
  uint8_t lp_bid_level_5_volume[12];                                     /* bytes 380 to 391 */
  uint8_t ask_level_6_price[11];                                         /* bytes 392 to 402 */
  uint8_t bid_level_6_price[11];                                         /* bytes 403 to 413 */
  uint8_t ask_level_6_volume[12];                                        /* bytes 414 to 425 */
  uint8_t bid_level_6_volume[12];                                        /* bytes 426 to 437 */
  uint8_t lp_ask_level_6_volume[12];                                     /* bytes 438 to 449 */
  uint8_t lp_bid_level_6_volume[12];                                     /* bytes 450 to 461 */
  uint8_t ask_level_7_price[11];                                         /* bytes 462 to 472 */
  uint8_t bid_level_7_price[11];                                         /* bytes 473 to 483 */
  uint8_t ask_level_7_volume[12];                                        /* bytes 484 to 495 */
  uint8_t bid_level_7_volume[12];                                        /* bytes 496 to 507 */
  uint8_t lp_ask_level_7_volume[12];                                     /* bytes 508 to 519 */
  uint8_t lp_bid_level_7_volume[12];                                     /* bytes 520 to 531 */
  uint8_t ask_level_8_price[11];                                         /* bytes 532 to 542 */
  uint8_t bid_level_8_price[11];                                         /* bytes 543 to 553 */
  uint8_t ask_level_8_volume[12];                                        /* bytes 554 to 565 */
  uint8_t bid_level_8_volume[12];                                        /* bytes 566 to 577 */
  uint8_t lp_ask_level_8_volume[12];                                     /* bytes 578 to 589 */
  uint8_t lp_bid_level_8_volume[12];                                     /* bytes 590 to 601 */
  uint8_t ask_level_9_price[11];                                         /* bytes 602 to 612 */
  uint8_t bid_level_9_price[11];                                         /* bytes 613 to 623 */
  uint8_t ask_level_9_volume[12];                                        /* bytes 624 to 635 */
  uint8_t bid_level_9_volume[12];                                        /* bytes 636 to 647 */
  uint8_t lp_ask_level_9_volume[12];                                     /* bytes 648 to 659 */
  uint8_t lp_bid_level_9_volume[12];                                     /* bytes 660 to 671 */
  uint8_t ask_level_10_price[11];                                        /* bytes 672 to 682 */
  uint8_t bid_level_10_price[11];                                        /* bytes 683 to 693 */
  uint8_t ask_level_10_volume[12];                                       /* bytes 694 to 705 */
  uint8_t bid_level_10_volume[12];                                       /* bytes 706 to 717 */
  uint8_t lp_ask_level_10_volume[12];                                    /* bytes 718 to 729 */
  uint8_t lp_bid_level_10_volume[12];                                    /* bytes 730 to 741 */
  uint8_t total_ask_volume[12];                                          /* bytes 742 to 753 */
  uint8_t total_bid_volume[12];                                          /* bytes 754 to 765 */
  uint8_t estimated_trading_price[11];                                   /* bytes 766 to 776 */
  uint8_t estimated_trading_volume[12];                                  /* bytes 777 to 788 */
  uint8_t mid_price[11];                                                 /* bytes 789 to 799 */
  uint8_t total_mid_price_ask_volume_total_ask_volume_on_mid_price[12];  /* bytes 800 to 811 */
  uint8_t total_mid_price_bid_volume_total_bid_volume_on_mid_price[12];  /* bytes 812 to 823 */
  uint8_t end_keyword;                                                   /* byte 824 */
} SecuritiesQuoteMmLpQuotesIncluded10LevelMessage;

/* any Securities Quote Mm Lp Quotes Included 10 Level Message at all: every byte one the checker chooses */
static void any_securities_quote_mm_lp_quotes_included10_level_message(SecuritiesQuoteMmLpQuotesIncluded10LevelMessage *record) {
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
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_6_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_6_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_7_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_7_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_8_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_8_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_9_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_9_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_10_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_10_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Quote Mm Lp Quotes Included 10 Level Message to the wire: 825 bytes from at, returning where the next byte goes */
static size_t encode_securities_quote_mm_lp_quotes_included10_level_message(const SecuritiesQuoteMmLpQuotesIncluded10LevelMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_4_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_4_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_4_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_4_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_5_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_5_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_5_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_5_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_6_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_6_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_6_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_6_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_6_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_6_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_7_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_7_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_7_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_7_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_7_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_7_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_8_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_8_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_8_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_8_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_8_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_8_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_9_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_9_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_9_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_9_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_9_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_9_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_10_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_10_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_10_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_10_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_10_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_10_volume[i]; }
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

/* Securities Quote Mm Lp Quotes Included 10 Level Message off the wire: 825 bytes from at, returning where the next byte lies */
static size_t decode_securities_quote_mm_lp_quotes_included10_level_message(SecuritiesQuoteMmLpQuotesIncluded10LevelMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_6_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_6_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_7_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_7_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_8_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_8_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_9_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_9_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_10_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_10_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_10_volume[i] = wire[at++]; }
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

/* what was read of Securities Quote Mm Lp Quotes Included 10 Level Message is what was written, byte for byte */
static void equal_securities_quote_mm_lp_quotes_included10_level_message(const SecuritiesQuoteMmLpQuotesIncluded10LevelMessage *read, const SecuritiesQuoteMmLpQuotesIncluded10LevelMessage *written) {
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
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_4_volume[i] == written->ask_level_4_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_4_volume[i] == written->bid_level_4_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_4_volume[i] == written->lp_ask_level_4_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_4_volume[i] == written->lp_bid_level_4_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_5_volume[i] == written->ask_level_5_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_5_volume[i] == written->bid_level_5_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_5_volume[i] == written->lp_ask_level_5_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_5_volume[i] == written->lp_bid_level_5_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_6_price[i] == written->ask_level_6_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_6_price[i] == written->bid_level_6_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_6_volume[i] == written->ask_level_6_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_6_volume[i] == written->bid_level_6_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_6_volume[i] == written->lp_ask_level_6_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_6_volume[i] == written->lp_bid_level_6_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_7_price[i] == written->ask_level_7_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_7_price[i] == written->bid_level_7_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_7_volume[i] == written->ask_level_7_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_7_volume[i] == written->bid_level_7_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_7_volume[i] == written->lp_ask_level_7_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_7_volume[i] == written->lp_bid_level_7_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_8_price[i] == written->ask_level_8_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_8_price[i] == written->bid_level_8_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_8_volume[i] == written->ask_level_8_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_8_volume[i] == written->bid_level_8_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_8_volume[i] == written->lp_ask_level_8_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_8_volume[i] == written->lp_bid_level_8_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_9_price[i] == written->ask_level_9_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_9_price[i] == written->bid_level_9_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_9_volume[i] == written->ask_level_9_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_9_volume[i] == written->bid_level_9_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_9_volume[i] == written->lp_ask_level_9_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_9_volume[i] == written->lp_bid_level_9_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_10_price[i] == written->ask_level_10_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_10_price[i] == written->bid_level_10_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_10_volume[i] == written->ask_level_10_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_10_volume[i] == written->bid_level_10_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_10_volume[i] == written->lp_ask_level_10_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_10_volume[i] == written->lp_bid_level_10_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_ask_volume[i] == written->total_ask_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_bid_volume[i] == written->total_bid_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->estimated_trading_price[i] == written->estimated_trading_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->estimated_trading_volume[i] == written->estimated_trading_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->mid_price[i] == written->mid_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] == written->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] == written->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Quote Mm Lp Quotes Included 10 Level Message: written and read back, then read and written back */
static void check_securities_quote_mm_lp_quotes_included10_level_message(void) {
  SecuritiesQuoteMmLpQuotesIncluded10LevelMessage sent;
  SecuritiesQuoteMmLpQuotesIncluded10LevelMessage got;
  uint8_t wire[825];
  uint8_t again[825];

  any_securities_quote_mm_lp_quotes_included10_level_message(&sent);
  assert(encode_securities_quote_mm_lp_quotes_included10_level_message(&sent, wire, 0) == 825);
  assert(decode_securities_quote_mm_lp_quotes_included10_level_message(&got, wire, 0) == 825);
  equal_securities_quote_mm_lp_quotes_included10_level_message(&got, &sent);

  for (size_t i = 0; i < 825; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_quote_mm_lp_quotes_included10_level_message(&got, wire, 0) == 825);
  assert(encode_securities_quote_mm_lp_quotes_included10_level_message(&got, again, 0) == 825);
  for (size_t i = 0; i < 825; i++) { assert(again[i] == wire[i]); }
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

/* ---- Equities Snapshot Mm Lp Quotes Included 10 Level Message: 930 bytes ----- */

/* Snapshot and final status are provided with certain intervals per issue and board - MM/LP Quotes Included * 10 Level Best Order on Ask/Bid. */
typedef struct {
  uint8_t board_id[2];                                                   /* bytes 0 to 1 */
  uint8_t session_id[2];                                                 /* bytes 2 to 3 */
  uint8_t isin_code[12];                                                 /* bytes 4 to 15 */
  uint8_t a_designated_number_for_an_issue_from_krx[6];                  /* bytes 16 to 21 */
  uint8_t price_change_against_previous_day;                             /* byte 22 */
  uint8_t a_price_change_against_the_previous_day[11];                   /* bytes 23 to 33 */
  uint8_t upper_limit_price[11];                                         /* bytes 34 to 44 */
  uint8_t lower_limit_price[11];                                         /* bytes 45 to 55 */
  uint8_t current_price[11];                                             /* bytes 56 to 66 */
  uint8_t opening_price[11];                                             /* bytes 67 to 77 */
  uint8_t todays_high[11];                                               /* bytes 78 to 88 */
  uint8_t todays_low[11];                                                /* bytes 89 to 99 */
  uint8_t accumulated_trading_volume[12];                                /* bytes 100 to 111 */
  uint8_t accumulated_trading_value[22];                                 /* bytes 112 to 133 */
  uint8_t final_ask_bid_type_code;                                       /* byte 134 */
  uint8_t ask_level_1_price[11];                                         /* bytes 135 to 145 */
  uint8_t bid_level_1_price[11];                                         /* bytes 146 to 156 */
  uint8_t ask_level_1_volume[12];                                        /* bytes 157 to 168 */
  uint8_t bid_level_1_volume[12];                                        /* bytes 169 to 180 */
  uint8_t lp_ask_level_1_volume[12];                                     /* bytes 181 to 192 */
  uint8_t lp_bid_level_1_volume[12];                                     /* bytes 193 to 204 */
  uint8_t ask_level_2_price[11];                                         /* bytes 205 to 215 */
  uint8_t bid_level_2_price[11];                                         /* bytes 216 to 226 */
  uint8_t ask_level_2_volume[12];                                        /* bytes 227 to 238 */
  uint8_t bid_level_2_volume[12];                                        /* bytes 239 to 250 */
  uint8_t lp_ask_level_2_volume[12];                                     /* bytes 251 to 262 */
  uint8_t lp_bid_level_2_volume[12];                                     /* bytes 263 to 274 */
  uint8_t ask_level_3_price[11];                                         /* bytes 275 to 285 */
  uint8_t bid_level_3_price[11];                                         /* bytes 286 to 296 */
  uint8_t ask_level_3_volume[12];                                        /* bytes 297 to 308 */
  uint8_t bid_level_3_volume[12];                                        /* bytes 309 to 320 */
  uint8_t lp_ask_level_3_volume[12];                                     /* bytes 321 to 332 */
  uint8_t lp_bid_level_3_volume[12];                                     /* bytes 333 to 344 */
  uint8_t ask_level_4_price[11];                                         /* bytes 345 to 355 */
  uint8_t bid_level_4_price[11];                                         /* bytes 356 to 366 */
  uint8_t ask_level_4_volume[12];                                        /* bytes 367 to 378 */
  uint8_t bid_level_4_volume[12];                                        /* bytes 379 to 390 */
  uint8_t lp_ask_level_4_volume[12];                                     /* bytes 391 to 402 */
  uint8_t lp_bid_level_4_volume[12];                                     /* bytes 403 to 414 */
  uint8_t ask_level_5_price[11];                                         /* bytes 415 to 425 */
  uint8_t bid_level_5_price[11];                                         /* bytes 426 to 436 */
  uint8_t ask_level_5_volume[12];                                        /* bytes 437 to 448 */
  uint8_t bid_level_5_volume[12];                                        /* bytes 449 to 460 */
  uint8_t lp_ask_level_5_volume[12];                                     /* bytes 461 to 472 */
  uint8_t lp_bid_level_5_volume[12];                                     /* bytes 473 to 484 */
  uint8_t ask_level_6_price[11];                                         /* bytes 485 to 495 */
  uint8_t bid_level_6_price[11];                                         /* bytes 496 to 506 */
  uint8_t ask_level_6_volume[12];                                        /* bytes 507 to 518 */
  uint8_t bid_level_6_volume[12];                                        /* bytes 519 to 530 */
  uint8_t lp_ask_level_6_volume[12];                                     /* bytes 531 to 542 */
  uint8_t lp_bid_level_6_volume[12];                                     /* bytes 543 to 554 */
  uint8_t ask_level_7_price[11];                                         /* bytes 555 to 565 */
  uint8_t bid_level_7_price[11];                                         /* bytes 566 to 576 */
  uint8_t ask_level_7_volume[12];                                        /* bytes 577 to 588 */
  uint8_t bid_level_7_volume[12];                                        /* bytes 589 to 600 */
  uint8_t lp_ask_level_7_volume[12];                                     /* bytes 601 to 612 */
  uint8_t lp_bid_level_7_volume[12];                                     /* bytes 613 to 624 */
  uint8_t ask_level_8_price[11];                                         /* bytes 625 to 635 */
  uint8_t bid_level_8_price[11];                                         /* bytes 636 to 646 */
  uint8_t ask_level_8_volume[12];                                        /* bytes 647 to 658 */
  uint8_t bid_level_8_volume[12];                                        /* bytes 659 to 670 */
  uint8_t lp_ask_level_8_volume[12];                                     /* bytes 671 to 682 */
  uint8_t lp_bid_level_8_volume[12];                                     /* bytes 683 to 694 */
  uint8_t ask_level_9_price[11];                                         /* bytes 695 to 705 */
  uint8_t bid_level_9_price[11];                                         /* bytes 706 to 716 */
  uint8_t ask_level_9_volume[12];                                        /* bytes 717 to 728 */
  uint8_t bid_level_9_volume[12];                                        /* bytes 729 to 740 */
  uint8_t lp_ask_level_9_volume[12];                                     /* bytes 741 to 752 */
  uint8_t lp_bid_level_9_volume[12];                                     /* bytes 753 to 764 */
  uint8_t ask_level_10_price[11];                                        /* bytes 765 to 775 */
  uint8_t bid_level_10_price[11];                                        /* bytes 776 to 786 */
  uint8_t ask_level_10_volume[12];                                       /* bytes 787 to 798 */
  uint8_t bid_level_10_volume[12];                                       /* bytes 799 to 810 */
  uint8_t lp_ask_level_10_volume[12];                                    /* bytes 811 to 822 */
  uint8_t lp_bid_level_10_volume[12];                                    /* bytes 823 to 834 */
  uint8_t total_ask_volume[12];                                          /* bytes 835 to 846 */
  uint8_t total_bid_volume[12];                                          /* bytes 847 to 858 */
  uint8_t estimated_trading_price[11];                                   /* bytes 859 to 869 */
  uint8_t estimated_trading_volume[12];                                  /* bytes 870 to 881 */
  uint8_t closing_price_type_code;                                       /* byte 882 */
  uint8_t trading_halt;                                                  /* byte 883 */
  uint8_t knock_out_elw_type_code;                                       /* byte 884 */
  uint8_t knock_out_elw_triggering_time[9];                              /* bytes 885 to 893 */
  uint8_t mid_price[11];                                                 /* bytes 894 to 904 */
  uint8_t total_mid_price_ask_volume_total_ask_volume_on_mid_price[12];  /* bytes 905 to 916 */
  uint8_t total_mid_price_bid_volume_total_bid_volume_on_mid_price[12];  /* bytes 917 to 928 */
  uint8_t end_keyword;                                                   /* byte 929 */
} EquitiesSnapshotMmLpQuotesIncluded10LevelMessage;

/* any Equities Snapshot Mm Lp Quotes Included 10 Level Message at all: every byte one the checker chooses */
static void any_equities_snapshot_mm_lp_quotes_included10_level_message(EquitiesSnapshotMmLpQuotesIncluded10LevelMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  record->price_change_against_previous_day = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->a_price_change_against_the_previous_day[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->upper_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->current_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = arbitrary(); }
  record->final_ask_bid_type_code = arbitrary();
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
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_6_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_6_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_7_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_7_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_8_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_8_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_9_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_9_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_10_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_10_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = arbitrary(); }
  record->closing_price_type_code = arbitrary();
  record->trading_halt = arbitrary();
  record->knock_out_elw_type_code = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->knock_out_elw_triggering_time[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Equities Snapshot Mm Lp Quotes Included 10 Level Message to the wire: 930 bytes from at, returning where the next byte goes */
static size_t encode_equities_snapshot_mm_lp_quotes_included10_level_message(const EquitiesSnapshotMmLpQuotesIncluded10LevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  wire[at++] = record->price_change_against_previous_day;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->a_price_change_against_the_previous_day[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->upper_limit_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lower_limit_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->current_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value[i]; }
  wire[at++] = record->final_ask_bid_type_code;
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
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_4_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_4_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_4_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_4_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_5_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_5_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_5_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_5_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_6_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_6_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_6_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_6_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_6_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_6_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_7_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_7_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_7_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_7_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_7_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_7_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_8_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_8_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_8_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_8_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_8_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_8_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_9_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_9_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_9_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_9_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_9_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_9_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_10_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_10_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_10_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_10_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_ask_level_10_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->lp_bid_level_10_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_ask_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_bid_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->estimated_trading_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->estimated_trading_volume[i]; }
  wire[at++] = record->closing_price_type_code;
  wire[at++] = record->trading_halt;
  wire[at++] = record->knock_out_elw_type_code;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->knock_out_elw_triggering_time[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->mid_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Equities Snapshot Mm Lp Quotes Included 10 Level Message off the wire: 930 bytes from at, returning where the next byte lies */
static size_t decode_equities_snapshot_mm_lp_quotes_included10_level_message(EquitiesSnapshotMmLpQuotesIncluded10LevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  record->price_change_against_previous_day = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->a_price_change_against_the_previous_day[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->upper_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->current_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = wire[at++]; }
  record->final_ask_bid_type_code = wire[at++];
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
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_6_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_6_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_7_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_7_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_8_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_8_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_9_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_9_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_10_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_10_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_ask_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->lp_bid_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = wire[at++]; }
  record->closing_price_type_code = wire[at++];
  record->trading_halt = wire[at++];
  record->knock_out_elw_type_code = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->knock_out_elw_triggering_time[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Equities Snapshot Mm Lp Quotes Included 10 Level Message is what was written, byte for byte */
static void equal_equities_snapshot_mm_lp_quotes_included10_level_message(const EquitiesSnapshotMmLpQuotesIncluded10LevelMessage *read, const EquitiesSnapshotMmLpQuotesIncluded10LevelMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  assert(read->price_change_against_previous_day == written->price_change_against_previous_day);
  for (size_t i = 0; i < 11; i++) { assert(read->a_price_change_against_the_previous_day[i] == written->a_price_change_against_the_previous_day[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->upper_limit_price[i] == written->upper_limit_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lower_limit_price[i] == written->lower_limit_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->current_price[i] == written->current_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value[i] == written->accumulated_trading_value[i]); }
  assert(read->final_ask_bid_type_code == written->final_ask_bid_type_code);
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
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_4_volume[i] == written->ask_level_4_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_4_volume[i] == written->bid_level_4_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_4_volume[i] == written->lp_ask_level_4_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_4_volume[i] == written->lp_bid_level_4_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_5_volume[i] == written->ask_level_5_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_5_volume[i] == written->bid_level_5_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_5_volume[i] == written->lp_ask_level_5_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_5_volume[i] == written->lp_bid_level_5_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_6_price[i] == written->ask_level_6_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_6_price[i] == written->bid_level_6_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_6_volume[i] == written->ask_level_6_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_6_volume[i] == written->bid_level_6_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_6_volume[i] == written->lp_ask_level_6_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_6_volume[i] == written->lp_bid_level_6_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_7_price[i] == written->ask_level_7_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_7_price[i] == written->bid_level_7_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_7_volume[i] == written->ask_level_7_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_7_volume[i] == written->bid_level_7_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_7_volume[i] == written->lp_ask_level_7_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_7_volume[i] == written->lp_bid_level_7_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_8_price[i] == written->ask_level_8_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_8_price[i] == written->bid_level_8_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_8_volume[i] == written->ask_level_8_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_8_volume[i] == written->bid_level_8_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_8_volume[i] == written->lp_ask_level_8_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_8_volume[i] == written->lp_bid_level_8_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_9_price[i] == written->ask_level_9_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_9_price[i] == written->bid_level_9_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_9_volume[i] == written->ask_level_9_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_9_volume[i] == written->bid_level_9_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_9_volume[i] == written->lp_ask_level_9_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_9_volume[i] == written->lp_bid_level_9_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_10_price[i] == written->ask_level_10_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_10_price[i] == written->bid_level_10_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_10_volume[i] == written->ask_level_10_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_10_volume[i] == written->bid_level_10_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_ask_level_10_volume[i] == written->lp_ask_level_10_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->lp_bid_level_10_volume[i] == written->lp_bid_level_10_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_ask_volume[i] == written->total_ask_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_bid_volume[i] == written->total_bid_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->estimated_trading_price[i] == written->estimated_trading_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->estimated_trading_volume[i] == written->estimated_trading_volume[i]); }
  assert(read->closing_price_type_code == written->closing_price_type_code);
  assert(read->trading_halt == written->trading_halt);
  assert(read->knock_out_elw_type_code == written->knock_out_elw_type_code);
  for (size_t i = 0; i < 9; i++) { assert(read->knock_out_elw_triggering_time[i] == written->knock_out_elw_triggering_time[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->mid_price[i] == written->mid_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i] == written->total_mid_price_ask_volume_total_ask_volume_on_mid_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i] == written->total_mid_price_bid_volume_total_bid_volume_on_mid_price[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Equities Snapshot Mm Lp Quotes Included 10 Level Message: written and read back, then read and written back */
static void check_equities_snapshot_mm_lp_quotes_included10_level_message(void) {
  EquitiesSnapshotMmLpQuotesIncluded10LevelMessage sent;
  EquitiesSnapshotMmLpQuotesIncluded10LevelMessage got;
  uint8_t wire[930];
  uint8_t again[930];

  any_equities_snapshot_mm_lp_quotes_included10_level_message(&sent);
  assert(encode_equities_snapshot_mm_lp_quotes_included10_level_message(&sent, wire, 0) == 930);
  assert(decode_equities_snapshot_mm_lp_quotes_included10_level_message(&got, wire, 0) == 930);
  equal_equities_snapshot_mm_lp_quotes_included10_level_message(&got, &sent);

  for (size_t i = 0; i < 930; i++) { wire[i] = arbitrary(); }
  assert(decode_equities_snapshot_mm_lp_quotes_included10_level_message(&got, wire, 0) == 930);
  assert(encode_equities_snapshot_mm_lp_quotes_included10_level_message(&got, again, 0) == 930);
  for (size_t i = 0; i < 930; i++) { assert(again[i] == wire[i]); }
}

/* ---- Investor Activities Per Commodities Message: 79 bytes ------------------- */

/* Investor Activities per Commodities. */
typedef struct {
  uint8_t calculation_time[6];                 /* bytes 0 to 5 */
  uint8_t investor_code[4];                    /* bytes 6 to 9 */
  uint8_t accumulated_ask_trading_volume[12];  /* bytes 10 to 21 */
  uint8_t accumulated_ask_trading_value[22];   /* bytes 22 to 43 */
  uint8_t accumulated_bid_trading_volume[12];  /* bytes 44 to 55 */
  uint8_t accumulated_bid_trading_value[22];   /* bytes 56 to 77 */
  uint8_t end_keyword;                         /* byte 78 */
} InvestorActivitiesPerCommoditiesMessage;

/* any Investor Activities Per Commodities Message at all: every byte one the checker chooses */
static void any_investor_activities_per_commodities_message(InvestorActivitiesPerCommoditiesMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->calculation_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_ask_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_ask_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_bid_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_bid_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Investor Activities Per Commodities Message to the wire: 79 bytes from at, returning where the next byte goes */
static size_t encode_investor_activities_per_commodities_message(const InvestorActivitiesPerCommoditiesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->calculation_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->investor_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_ask_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_ask_trading_value[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_bid_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_bid_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Investor Activities Per Commodities Message off the wire: 79 bytes from at, returning where the next byte lies */
static size_t decode_investor_activities_per_commodities_message(InvestorActivitiesPerCommoditiesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->calculation_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_ask_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_ask_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_bid_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_bid_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Investor Activities Per Commodities Message is what was written, byte for byte */
static void equal_investor_activities_per_commodities_message(const InvestorActivitiesPerCommoditiesMessage *read, const InvestorActivitiesPerCommoditiesMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->calculation_time[i] == written->calculation_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->investor_code[i] == written->investor_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_ask_trading_volume[i] == written->accumulated_ask_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_ask_trading_value[i] == written->accumulated_ask_trading_value[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_bid_trading_volume[i] == written->accumulated_bid_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_bid_trading_value[i] == written->accumulated_bid_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Investor Activities Per Commodities Message: written and read back, then read and written back */
static void check_investor_activities_per_commodities_message(void) {
  InvestorActivitiesPerCommoditiesMessage sent;
  InvestorActivitiesPerCommoditiesMessage got;
  uint8_t wire[79];
  uint8_t again[79];

  any_investor_activities_per_commodities_message(&sent);
  assert(encode_investor_activities_per_commodities_message(&sent, wire, 0) == 79);
  assert(decode_investor_activities_per_commodities_message(&got, wire, 0) == 79);
  equal_investor_activities_per_commodities_message(&got, &sent);

  for (size_t i = 0; i < 79; i++) { wire[i] = arbitrary(); }
  assert(decode_investor_activities_per_commodities_message(&got, wire, 0) == 79);
  assert(encode_investor_activities_per_commodities_message(&got, again, 0) == 79);
  for (size_t i = 0; i < 79; i++) { assert(again[i] == wire[i]); }
}

/* ---- Etp Constituents Message: 204 bytes ------------------------------------- */

/* Constituents of Structured Products. */
typedef struct {
  uint8_t message_sequence_number[8];                  /* bytes 0 to 7 */
  uint8_t index_calculation_institution_type_code[2];  /* bytes 8 to 9 */
  uint8_t index_market_classification_id[6];           /* bytes 10 to 15 */
  uint8_t index_sequence_number[3];                    /* bytes 16 to 18 */
  uint8_t index_leverage_inverse_type_code[2];         /* bytes 19 to 20 */
  uint8_t index_name[80];                              /* bytes 21 to 100 */
  uint8_t index_name_in_en[80];                        /* bytes 101 to 180 */
  uint8_t index_asset_classification_id_1[6];          /* bytes 181 to 186 */
  uint8_t index_asset_classification_id_2[6];          /* bytes 187 to 192 */
  uint8_t index_id[6];                                 /* bytes 193 to 198 */
  uint8_t filler_4[4];                                 /* bytes 199 to 202 */
  uint8_t end_keyword;                                 /* byte 203 */
} EtpConstituentsMessage;

/* any Etp Constituents Message at all: every byte one the checker chooses */
static void any_etp_constituents_message(EtpConstituentsMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
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
  record->end_keyword = arbitrary();
}

/* Etp Constituents Message to the wire: 204 bytes from at, returning where the next byte goes */
static size_t encode_etp_constituents_message(const EtpConstituentsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
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
  wire[at++] = record->end_keyword;

  return at;
}

/* Etp Constituents Message off the wire: 204 bytes from at, returning where the next byte lies */
static size_t decode_etp_constituents_message(EtpConstituentsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
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
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Etp Constituents Message is what was written, byte for byte */
static void equal_etp_constituents_message(const EtpConstituentsMessage *read, const EtpConstituentsMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
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
  assert(read->end_keyword == written->end_keyword);
}

/* Etp Constituents Message: written and read back, then read and written back */
static void check_etp_constituents_message(void) {
  EtpConstituentsMessage sent;
  EtpConstituentsMessage got;
  uint8_t wire[204];
  uint8_t again[204];

  any_etp_constituents_message(&sent);
  assert(encode_etp_constituents_message(&sent, wire, 0) == 204);
  assert(decode_etp_constituents_message(&got, wire, 0) == 204);
  equal_etp_constituents_message(&got, &sent);

  for (size_t i = 0; i < 204; i++) { wire[i] = arbitrary(); }
  assert(decode_etp_constituents_message(&got, wire, 0) == 204);
  assert(encode_etp_constituents_message(&got, again, 0) == 204);
  for (size_t i = 0; i < 204; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mm Lp Information Message: 217 bytes ------------------------------------ */

/* Details. */
typedef struct {
  uint8_t message_sequence_number[8];                        /* bytes 0 to 7 */
  uint8_t isin_code[12];                                     /* bytes 8 to 19 */
  uint8_t market_participant_number[5];                      /* bytes 20 to 24 */
  uint8_t board_id[2];                                       /* bytes 25 to 26 */
  uint8_t market_making_lp_type_code;                        /* byte 27 */
  uint8_t lp_start_date[8];                                  /* bytes 28 to 35 */
  uint8_t lp_end_date[8];                                    /* bytes 36 to 43 */
  uint8_t minimum_order_volume[11];                          /* bytes 44 to 54 */
  uint8_t maximum_volume_of_multiple_order[11];              /* bytes 55 to 65 */
  uint8_t bid_ask_spread_unit_code;                          /* byte 66 */
  uint8_t main_market_bid_ask_spread_value[22];              /* bytes 67 to 88 */
  uint8_t spread_multiple_for_market_holidays[11];           /* bytes 89 to 99 */
  uint8_t an_obligatory_time_interval_to_place_an_order[6];  /* bytes 100 to 105 */
  uint8_t minimum_ask_price[22];                             /* bytes 106 to 127 */
  uint8_t maximum_bid_price[22];                             /* bytes 128 to 149 */
  uint8_t minimum_order_price[22];                           /* bytes 150 to 171 */
  uint8_t maximum_order_price[22];                           /* bytes 172 to 193 */
  uint8_t extended_market_bid_ask_spread_value[22];          /* bytes 194 to 215 */
  uint8_t end_keyword;                                       /* byte 216 */
} MmLpInformationMessage;

/* any Mm Lp Information Message at all: every byte one the checker chooses */
static void any_mm_lp_information_message(MmLpInformationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->market_participant_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  record->market_making_lp_type_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->lp_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_end_date[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->minimum_order_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->maximum_volume_of_multiple_order[i] = arbitrary(); }
  record->bid_ask_spread_unit_code = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->main_market_bid_ask_spread_value[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->spread_multiple_for_market_holidays[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->an_obligatory_time_interval_to_place_an_order[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->minimum_ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->maximum_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->minimum_order_price[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->maximum_order_price[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->extended_market_bid_ask_spread_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Mm Lp Information Message to the wire: 217 bytes from at, returning where the next byte goes */
static size_t encode_mm_lp_information_message(const MmLpInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->market_participant_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  wire[at++] = record->market_making_lp_type_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_start_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_end_date[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->minimum_order_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->maximum_volume_of_multiple_order[i]; }
  wire[at++] = record->bid_ask_spread_unit_code;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->main_market_bid_ask_spread_value[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->spread_multiple_for_market_holidays[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->an_obligatory_time_interval_to_place_an_order[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->minimum_ask_price[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->maximum_bid_price[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->minimum_order_price[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->maximum_order_price[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->extended_market_bid_ask_spread_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Mm Lp Information Message off the wire: 217 bytes from at, returning where the next byte lies */
static size_t decode_mm_lp_information_message(MmLpInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->market_participant_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  record->market_making_lp_type_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->lp_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_end_date[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->minimum_order_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->maximum_volume_of_multiple_order[i] = wire[at++]; }
  record->bid_ask_spread_unit_code = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->main_market_bid_ask_spread_value[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->spread_multiple_for_market_holidays[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->an_obligatory_time_interval_to_place_an_order[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->minimum_ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->maximum_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->minimum_order_price[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->maximum_order_price[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->extended_market_bid_ask_spread_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Mm Lp Information Message is what was written, byte for byte */
static void equal_mm_lp_information_message(const MmLpInformationMessage *read, const MmLpInformationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->market_participant_number[i] == written->market_participant_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  assert(read->market_making_lp_type_code == written->market_making_lp_type_code);
  for (size_t i = 0; i < 8; i++) { assert(read->lp_start_date[i] == written->lp_start_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_end_date[i] == written->lp_end_date[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->minimum_order_volume[i] == written->minimum_order_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->maximum_volume_of_multiple_order[i] == written->maximum_volume_of_multiple_order[i]); }
  assert(read->bid_ask_spread_unit_code == written->bid_ask_spread_unit_code);
  for (size_t i = 0; i < 22; i++) { assert(read->main_market_bid_ask_spread_value[i] == written->main_market_bid_ask_spread_value[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->spread_multiple_for_market_holidays[i] == written->spread_multiple_for_market_holidays[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->an_obligatory_time_interval_to_place_an_order[i] == written->an_obligatory_time_interval_to_place_an_order[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->minimum_ask_price[i] == written->minimum_ask_price[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->maximum_bid_price[i] == written->maximum_bid_price[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->minimum_order_price[i] == written->minimum_order_price[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->maximum_order_price[i] == written->maximum_order_price[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->extended_market_bid_ask_spread_value[i] == written->extended_market_bid_ask_spread_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Mm Lp Information Message: written and read back, then read and written back */
static void check_mm_lp_information_message(void) {
  MmLpInformationMessage sent;
  MmLpInformationMessage got;
  uint8_t wire[217];
  uint8_t again[217];

  any_mm_lp_information_message(&sent);
  assert(encode_mm_lp_information_message(&sent, wire, 0) == 217);
  assert(decode_mm_lp_information_message(&got, wire, 0) == 217);
  equal_mm_lp_information_message(&got, &sent);

  for (size_t i = 0; i < 217; i++) { wire[i] = arbitrary(); }
  assert(decode_mm_lp_information_message(&got, wire, 0) == 217);
  assert(encode_mm_lp_information_message(&got, again, 0) == 217);
  for (size_t i = 0; i < 217; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Operation Schedule Message: 78 bytes ----------------------------- */

/* The data is provided when a Market Operation Schedule event is disclosed. */
typedef struct {
  uint8_t market_operation_product_id[3];                        /* bytes 0 to 2 */
  uint8_t board_id[2];                                           /* bytes 3 to 4 */
  uint8_t board_event_id[3];                                     /* bytes 5 to 7 */
  uint8_t start_time_of_a_board_event[9];                        /* bytes 8 to 16 */
  uint8_t board_event_group_code[5];                             /* bytes 17 to 21 */
  uint8_t session_start_end_code[2];                             /* bytes 22 to 23 */
  uint8_t session_id[2];                                         /* bytes 24 to 25 */
  uint8_t isin_code[12];                                         /* bytes 26 to 37 */
  uint8_t isin_code_of_a_common_stock[12];                       /* bytes 38 to 49 */
  uint8_t product_id[11];                                        /* bytes 50 to 60 */
  uint8_t trading_halt_reason_code[3];                           /* bytes 61 to 63 */
  uint8_t trading_halt_type_code;                                /* byte 64 */
  uint8_t step_applied[2];                                       /* bytes 65 to 66 */
  uint8_t price_limit_range_expansion_for_base_issue_type_code;  /* byte 67 */
  uint8_t expected_time_of_expanding_price_limit_range[9];       /* bytes 68 to 76 */
  uint8_t end_keyword;                                           /* byte 77 */
} MarketOperationScheduleMessage;

/* any Market Operation Schedule Message at all: every byte one the checker chooses */
static void any_market_operation_schedule_message(MarketOperationScheduleMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_start_end_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code_of_a_common_stock[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = arbitrary(); }
  record->trading_halt_type_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->step_applied[i] = arbitrary(); }
  record->price_limit_range_expansion_for_base_issue_type_code = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->expected_time_of_expanding_price_limit_range[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Market Operation Schedule Message to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_market_operation_schedule_message(const MarketOperationScheduleMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_operation_product_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->board_event_id[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->start_time_of_a_board_event[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->board_event_group_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_start_end_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code_of_a_common_stock[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_halt_reason_code[i]; }
  wire[at++] = record->trading_halt_type_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->step_applied[i]; }
  wire[at++] = record->price_limit_range_expansion_for_base_issue_type_code;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->expected_time_of_expanding_price_limit_range[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Market Operation Schedule Message off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_market_operation_schedule_message(MarketOperationScheduleMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_start_end_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code_of_a_common_stock[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = wire[at++]; }
  record->trading_halt_type_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->step_applied[i] = wire[at++]; }
  record->price_limit_range_expansion_for_base_issue_type_code = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->expected_time_of_expanding_price_limit_range[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Market Operation Schedule Message is what was written, byte for byte */
static void equal_market_operation_schedule_message(const MarketOperationScheduleMessage *read, const MarketOperationScheduleMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->market_operation_product_id[i] == written->market_operation_product_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->board_event_id[i] == written->board_event_id[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->start_time_of_a_board_event[i] == written->start_time_of_a_board_event[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->board_event_group_code[i] == written->board_event_group_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_start_end_code[i] == written->session_start_end_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code_of_a_common_stock[i] == written->isin_code_of_a_common_stock[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trading_halt_reason_code[i] == written->trading_halt_reason_code[i]); }
  assert(read->trading_halt_type_code == written->trading_halt_type_code);
  for (size_t i = 0; i < 2; i++) { assert(read->step_applied[i] == written->step_applied[i]); }
  assert(read->price_limit_range_expansion_for_base_issue_type_code == written->price_limit_range_expansion_for_base_issue_type_code);
  for (size_t i = 0; i < 9; i++) { assert(read->expected_time_of_expanding_price_limit_range[i] == written->expected_time_of_expanding_price_limit_range[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Market Operation Schedule Message: written and read back, then read and written back */
static void check_market_operation_schedule_message(void) {
  MarketOperationScheduleMessage sent;
  MarketOperationScheduleMessage got;
  uint8_t wire[78];
  uint8_t again[78];

  any_market_operation_schedule_message(&sent);
  assert(encode_market_operation_schedule_message(&sent, wire, 0) == 78);
  assert(decode_market_operation_schedule_message(&got, wire, 0) == 78);
  equal_market_operation_schedule_message(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_market_operation_schedule_message(&got, wire, 0) == 78);
  assert(encode_market_operation_schedule_message(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Member Firm Imposing Lifting Sanctions Message: 41 bytes ---------------- */

/* The data is provided when a sanction is imposed on a member firm or lifted. */
typedef struct {
  uint8_t isin_code[12];                                 /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue_from_krx[6];  /* bytes 12 to 17 */
  uint8_t disclosing_data_type_code[3];                  /* bytes 18 to 20 */
  uint8_t disclosure_time[9];                            /* bytes 21 to 29 */
  uint8_t member_number[5];                              /* bytes 30 to 34 */
  uint8_t member_firm_trust_principal_type_code[5];      /* bytes 35 to 39 */
  uint8_t end_keyword;                                   /* byte 40 */
} MemberFirmImposingLiftingSanctionsMessage;

/* any Member Firm Imposing Lifting Sanctions Message at all: every byte one the checker chooses */
static void any_member_firm_imposing_lifting_sanctions_message(MemberFirmImposingLiftingSanctionsMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->disclosing_data_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->disclosure_time[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_firm_trust_principal_type_code[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Member Firm Imposing Lifting Sanctions Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_member_firm_imposing_lifting_sanctions_message(const MemberFirmImposingLiftingSanctionsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->disclosing_data_type_code[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->disclosure_time[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_firm_trust_principal_type_code[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Member Firm Imposing Lifting Sanctions Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_member_firm_imposing_lifting_sanctions_message(MemberFirmImposingLiftingSanctionsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->disclosing_data_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->disclosure_time[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_firm_trust_principal_type_code[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Member Firm Imposing Lifting Sanctions Message is what was written, byte for byte */
static void equal_member_firm_imposing_lifting_sanctions_message(const MemberFirmImposingLiftingSanctionsMessage *read, const MemberFirmImposingLiftingSanctionsMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->disclosing_data_type_code[i] == written->disclosing_data_type_code[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->disclosure_time[i] == written->disclosure_time[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number[i] == written->member_number[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_firm_trust_principal_type_code[i] == written->member_firm_trust_principal_type_code[i]); }
  assert(read->end_keyword == written->end_keyword);
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

/* ---- Top Five Traders Activities Message: 409 bytes -------------------------- */

/* Top Five Traders' Activities (including only Regular Board). */
typedef struct {
  uint8_t isin_code[12];                                 /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue_from_krx[6];  /* bytes 12 to 17 */
  uint8_t member_number_1_for_ask[5];                    /* bytes 18 to 22 */
  uint8_t ask_trading_volume_1[12];                      /* bytes 23 to 34 */
  uint8_t ask_trading_value_1[22];                       /* bytes 35 to 56 */
  uint8_t member_number_1_for_bid[5];                    /* bytes 57 to 61 */
  uint8_t bid_trading_volume_1[12];                      /* bytes 62 to 73 */
  uint8_t bid_trading_value_1[22];                       /* bytes 74 to 95 */
  uint8_t member_number_2_for_ask[5];                    /* bytes 96 to 100 */
  uint8_t ask_trading_volume_2[12];                      /* bytes 101 to 112 */
  uint8_t ask_trading_value_2[22];                       /* bytes 113 to 134 */
  uint8_t member_number_2_for_bid[5];                    /* bytes 135 to 139 */
  uint8_t bid_trading_volume_2[12];                      /* bytes 140 to 151 */
  uint8_t bid_trading_value_2[22];                       /* bytes 152 to 173 */
  uint8_t member_number_3_for_ask[5];                    /* bytes 174 to 178 */
  uint8_t ask_trading_volume_3[12];                      /* bytes 179 to 190 */
  uint8_t ask_trading_value_3[22];                       /* bytes 191 to 212 */
  uint8_t member_number_3_for_bid[5];                    /* bytes 213 to 217 */
  uint8_t bid_trading_volume_3[12];                      /* bytes 218 to 229 */
  uint8_t bid_trading_value_3[22];                       /* bytes 230 to 251 */
  uint8_t member_number_4_for_ask[5];                    /* bytes 252 to 256 */
  uint8_t ask_trading_volume_4[12];                      /* bytes 257 to 268 */
  uint8_t ask_trading_value_4[22];                       /* bytes 269 to 290 */
  uint8_t member_number_4_for_bid[5];                    /* bytes 291 to 295 */
  uint8_t bid_trading_volume_4[12];                      /* bytes 296 to 307 */
  uint8_t bid_trading_value_4[22];                       /* bytes 308 to 329 */
  uint8_t member_number_5_for_ask[5];                    /* bytes 330 to 334 */
  uint8_t ask_trading_volume_5[12];                      /* bytes 335 to 346 */
  uint8_t ask_trading_value_5[22];                       /* bytes 347 to 368 */
  uint8_t member_number_5_for_bid[5];                    /* bytes 369 to 373 */
  uint8_t bid_trading_volume_5[12];                      /* bytes 374 to 385 */
  uint8_t bid_trading_value_5[22];                       /* bytes 386 to 407 */
  uint8_t end_keyword;                                   /* byte 408 */
} TopFiveTradersActivitiesMessage;

/* any Top Five Traders Activities Message at all: every byte one the checker chooses */
static void any_top_five_traders_activities_message(TopFiveTradersActivitiesMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_1_for_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_trading_volume_1[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_trading_value_1[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_1_for_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_trading_volume_1[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->bid_trading_value_1[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_2_for_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_trading_volume_2[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_trading_value_2[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_2_for_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_trading_volume_2[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->bid_trading_value_2[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_3_for_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_trading_volume_3[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_trading_value_3[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_3_for_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_trading_volume_3[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->bid_trading_value_3[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_4_for_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_trading_volume_4[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_trading_value_4[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_4_for_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_trading_volume_4[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->bid_trading_value_4[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_5_for_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_trading_volume_5[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_trading_value_5[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number_5_for_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_trading_volume_5[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->bid_trading_value_5[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Top Five Traders Activities Message to the wire: 409 bytes from at, returning where the next byte goes */
static size_t encode_top_five_traders_activities_message(const TopFiveTradersActivitiesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_1_for_ask[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_trading_volume_1[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_trading_value_1[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_1_for_bid[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_trading_volume_1[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->bid_trading_value_1[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_2_for_ask[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_trading_volume_2[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_trading_value_2[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_2_for_bid[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_trading_volume_2[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->bid_trading_value_2[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_3_for_ask[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_trading_volume_3[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_trading_value_3[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_3_for_bid[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_trading_volume_3[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->bid_trading_value_3[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_4_for_ask[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_trading_volume_4[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_trading_value_4[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_4_for_bid[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_trading_volume_4[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->bid_trading_value_4[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_5_for_ask[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_trading_volume_5[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_trading_value_5[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number_5_for_bid[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_trading_volume_5[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->bid_trading_value_5[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Top Five Traders Activities Message off the wire: 409 bytes from at, returning where the next byte lies */
static size_t decode_top_five_traders_activities_message(TopFiveTradersActivitiesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_1_for_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_trading_volume_1[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_trading_value_1[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_1_for_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_trading_volume_1[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->bid_trading_value_1[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_2_for_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_trading_volume_2[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_trading_value_2[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_2_for_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_trading_volume_2[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->bid_trading_value_2[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_3_for_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_trading_volume_3[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_trading_value_3[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_3_for_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_trading_volume_3[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->bid_trading_value_3[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_4_for_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_trading_volume_4[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_trading_value_4[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_4_for_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_trading_volume_4[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->bid_trading_value_4[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_5_for_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_trading_volume_5[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_trading_value_5[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number_5_for_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_trading_volume_5[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->bid_trading_value_5[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Top Five Traders Activities Message is what was written, byte for byte */
static void equal_top_five_traders_activities_message(const TopFiveTradersActivitiesMessage *read, const TopFiveTradersActivitiesMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_1_for_ask[i] == written->member_number_1_for_ask[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_trading_volume_1[i] == written->ask_trading_volume_1[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_trading_value_1[i] == written->ask_trading_value_1[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_1_for_bid[i] == written->member_number_1_for_bid[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_trading_volume_1[i] == written->bid_trading_volume_1[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->bid_trading_value_1[i] == written->bid_trading_value_1[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_2_for_ask[i] == written->member_number_2_for_ask[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_trading_volume_2[i] == written->ask_trading_volume_2[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_trading_value_2[i] == written->ask_trading_value_2[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_2_for_bid[i] == written->member_number_2_for_bid[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_trading_volume_2[i] == written->bid_trading_volume_2[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->bid_trading_value_2[i] == written->bid_trading_value_2[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_3_for_ask[i] == written->member_number_3_for_ask[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_trading_volume_3[i] == written->ask_trading_volume_3[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_trading_value_3[i] == written->ask_trading_value_3[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_3_for_bid[i] == written->member_number_3_for_bid[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_trading_volume_3[i] == written->bid_trading_volume_3[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->bid_trading_value_3[i] == written->bid_trading_value_3[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_4_for_ask[i] == written->member_number_4_for_ask[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_trading_volume_4[i] == written->ask_trading_volume_4[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_trading_value_4[i] == written->ask_trading_value_4[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_4_for_bid[i] == written->member_number_4_for_bid[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_trading_volume_4[i] == written->bid_trading_volume_4[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->bid_trading_value_4[i] == written->bid_trading_value_4[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_5_for_ask[i] == written->member_number_5_for_ask[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_trading_volume_5[i] == written->ask_trading_volume_5[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_trading_value_5[i] == written->ask_trading_value_5[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number_5_for_bid[i] == written->member_number_5_for_bid[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_trading_volume_5[i] == written->bid_trading_volume_5[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->bid_trading_value_5[i] == written->bid_trading_value_5[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Top Five Traders Activities Message: written and read back, then read and written back */
static void check_top_five_traders_activities_message(void) {
  TopFiveTradersActivitiesMessage sent;
  TopFiveTradersActivitiesMessage got;
  uint8_t wire[409];
  uint8_t again[409];

  any_top_five_traders_activities_message(&sent);
  assert(encode_top_five_traders_activities_message(&sent, wire, 0) == 409);
  assert(decode_top_five_traders_activities_message(&got, wire, 0) == 409);
  equal_top_five_traders_activities_message(&got, &sent);

  for (size_t i = 0; i < 409; i++) { wire[i] = arbitrary(); }
  assert(decode_top_five_traders_activities_message(&got, wire, 0) == 409);
  assert(encode_top_five_traders_activities_message(&got, again, 0) == 409);
  for (size_t i = 0; i < 409; i++) { assert(again[i] == wire[i]); }
}

/* ---- Equities Batch Data Message: 649 bytes ---------------------------------- */

/* Details. */
typedef struct {
  uint8_t message_sequence_number[8];                                          /* bytes 0 to 7 */
  uint8_t total_number_of_instruments_of_the_contract[6];                      /* bytes 8 to 13 */
  uint8_t business_date[8];                                                    /* bytes 14 to 21 */
  uint8_t isin_code[12];                                                       /* bytes 22 to 33 */
  uint8_t a_designated_number_for_an_issue_from_krx[6];                        /* bytes 34 to 39 */
  uint8_t abbreviated_issue_code[9];                                           /* bytes 40 to 48 */
  uint8_t abbreviated_issue_name[40];                                          /* bytes 49 to 88 */
  uint8_t abbreviated_issue_name_in_en[40];                                    /* bytes 89 to 128 */
  uint8_t group_number[5];                                                     /* bytes 129 to 133 */
  uint8_t market_operation_product_id[3];                                      /* bytes 134 to 136 */
  uint8_t security_group_id[2];                                                /* bytes 137 to 138 */
  uint8_t unit_trading;                                                        /* byte 139 */
  uint8_t rights_type_code[2];                                                 /* bytes 140 to 141 */
  uint8_t par_value_type_code[2];                                              /* bytes 142 to 143 */
  uint8_t an_issue_of_which_base_price_is_settled_with_a_todays_single_price;  /* byte 144 */
  uint8_t reevaluation_reason_code[2];                                         /* bytes 145 to 146 */
  uint8_t base_price_change;                                                   /* byte 147 */
  uint8_t random_end_trigger_code;                                             /* byte 148 */
  uint8_t market_alert;                                                        /* byte 149 */
  uint8_t market_alert_type_code[2];                                           /* bytes 150 to 151 */
  uint8_t korea_corporate_governance_stock_price_index_kogi;                   /* byte 152 */
  uint8_t issue_for_administration;                                            /* byte 153 */
  uint8_t unfaithful_disclosure;                                               /* byte 154 */
  uint8_t back_door_listing;                                                   /* byte 155 */
  uint8_t trading_halt;                                                        /* byte 156 */
  uint8_t industry_id[10];                                                     /* bytes 157 to 166 */
  uint8_t small_medium_sized_business;                                         /* byte 167 */
  uint8_t section_type_code;                                                   /* byte 168 */
  uint8_t investment_institution_type_code;                                    /* byte 169 */
  uint8_t base_price[11];                                                      /* bytes 170 to 180 */
  uint8_t yesterdays_closing_price_type_code_krx;                              /* byte 181 */
  uint8_t yesterdays_closing_price_krx[11];                                    /* bytes 182 to 192 */
  uint8_t yesterdays_accumulated_trading_amount[12];                           /* bytes 193 to 204 */
  uint8_t yesterdays_accumulated_trading_value[22];                            /* bytes 205 to 226 */
  uint8_t upper_limit_price[11];                                               /* bytes 227 to 237 */
  uint8_t lower_limit_price[11];                                               /* bytes 238 to 248 */
  uint8_t substitute_price_of_securities[11];                                  /* bytes 249 to 259 */
  uint8_t par_value[11];                                                       /* bytes 260 to 270 */
  uint8_t issuing_price[11];                                                   /* bytes 271 to 281 */
  uint8_t listing_date[8];                                                     /* bytes 282 to 289 */
  uint8_t number_of_listed_shares[16];                                         /* bytes 290 to 305 */
  uint8_t liquidation_trade;                                                   /* byte 306 */
  uint8_t the_establishment_date[8];                                           /* bytes 307 to 314 */
  uint8_t maturity_date[8];                                                    /* bytes 315 to 322 */
  uint8_t exercising_period[8];                                                /* bytes 323 to 330 */
  uint8_t expiration_date_for_right[8];                                        /* bytes 331 to 338 */
  uint8_t exercise_price_of_elw_or_bw[13];                                     /* bytes 339 to 351 */
  uint8_t capital[22];                                                         /* bytes 352 to 373 */
  uint8_t credit_order_possibility;                                            /* byte 374 */
  uint8_t limit_order_permission_type_code[5];                                 /* bytes 375 to 379 */
  uint8_t market_price_order_permission_type_code[5];                          /* bytes 380 to 384 */
  uint8_t conditioned_order_permission_type_code[5];                           /* bytes 385 to 389 */
  uint8_t best_favorable_order_permission_type_code[5];                        /* bytes 390 to 394 */
  uint8_t first_best_order_permission_type[5];                                 /* bytes 395 to 399 */
  uint8_t mid_price_order_permission_type_code[5];                             /* bytes 400 to 404 */
  uint8_t stop_limit_price_order_permission_type_code[5];                      /* bytes 405 to 409 */
  uint8_t capital_increase_type_code[2];                                       /* bytes 410 to 411 */
  uint8_t other_stock_type_code;                                               /* byte 412 */
  uint8_t national_stock;                                                      /* byte 413 */
  uint8_t appraised_price[11];                                                 /* bytes 414 to 424 */
  uint8_t lowest_order_price[11];                                              /* bytes 425 to 435 */
  uint8_t highest_order_price[11];                                             /* bytes 436 to 446 */
  uint8_t unit_of_volume_in_main_board[11];                                    /* bytes 447 to 457 */
  uint8_t lot_size_after_hours_trading[11];                                    /* bytes 458 to 468 */
  uint8_t rei_ts_type_code;                                                    /* byte 469 */
  uint8_t target_stock_isin_code[12];                                          /* bytes 470 to 481 */
  uint8_t currency_iso_code[3];                                                /* bytes 482 to 484 */
  uint8_t country_code[3];                                                     /* bytes 485 to 487 */
  uint8_t market_making_possibility;                                           /* byte 488 */
  uint8_t closing_price_trading_possibility_in_the_after_hours;                /* byte 489 */
  uint8_t closing_price_trading_in_the_pre_opening_market;                     /* byte 490 */
  uint8_t block_trading_in_the_pre_opening_market;                             /* byte 491 */
  uint8_t basket_trading_in_the_pre_opening_market;                            /* byte 492 */
  uint8_t announcement_of_estimated_trading_price;                             /* byte 493 */
  uint8_t short_selling;                                                       /* byte 494 */
  uint8_t etf_tracking_difference[13];                                         /* bytes 495 to 507 */
  uint8_t regs;                                                                /* byte 508 */
  uint8_t spac;                                                                /* byte 509 */
  uint8_t tax_type_code;                                                       /* byte 510 */
  uint8_t appraisal_ratio_of_substitute_price[13];                             /* bytes 511 to 523 */
  uint8_t investment_caution_issue;                                            /* byte 524 */
  uint8_t delisting_date[8];                                                   /* bytes 525 to 532 */
  uint8_t short_term_overheat_issue_type_code;                                 /* byte 533 */
  uint8_t etf_replication_methods_type_code;                                   /* byte 534 */
  uint8_t expiration_date[8];                                                  /* bytes 535 to 542 */
  uint8_t distribution_type_code[2];                                           /* bytes 543 to 544 */
  uint8_t calculation_of_redemption_price_start_date[8];                       /* bytes 545 to 552 */
  uint8_t calculation_of_redemption_price_end_date[8];                         /* bytes 553 to 560 */
  uint8_t etp_product_type_code;                                               /* byte 561 */
  uint8_t index_calculation_institution_type_code[2];                          /* bytes 562 to 563 */
  uint8_t index_market_classification_id[6];                                   /* bytes 564 to 569 */
  uint8_t index_sequence_number[3];                                            /* bytes 570 to 572 */
  uint8_t tracking_index_leverage_inverse_type_code[2];                        /* bytes 573 to 574 */
  uint8_t reference_index_leverage_inverse_type_code[2];                       /* bytes 575 to 576 */
  uint8_t index_asset_classification_id_1[6];                                  /* bytes 577 to 582 */
  uint8_t index_asset_classification_id_2[6];                                  /* bytes 583 to 588 */
  uint8_t ipo_underwriter_member_number[5];                                    /* bytes 589 to 593 */
  uint8_t lp_order;                                                            /* byte 594 */
  uint8_t low_liquidity;                                                       /* byte 595 */
  uint8_t abnormal_rise;                                                       /* byte 596 */
  uint8_t upper_limit_quantity[23];                                            /* bytes 597 to 619 */
  uint8_t investment_precaution_issue;                                         /* byte 620 */
  uint8_t preferred_stocks_with_lesser_shares;                                 /* byte 621 */
  uint8_t spac_merger;                                                         /* byte 622 */
  uint8_t segment_type_code;                                                   /* byte 623 */
  uint8_t after_market_possibility;                                            /* byte 624 */
  uint8_t choice_on_competitive_trading;                                       /* byte 625 */
  uint8_t limit_on_competitive_trading_volume;                                 /* byte 626 */
  uint8_t occurrence_of_reasons_prohibiting_competitive_trading;               /* byte 627 */
  uint8_t approval_on_competitive_trading;                                     /* byte 628 */
  uint8_t approval_on_negotiation_trading;                                     /* byte 629 */
  uint8_t yesterdays_closing_price_type_code_nxt;                              /* byte 630 */
  uint8_t yesterdays_closing_price_nxt[11];                                    /* bytes 631 to 641 */
  uint8_t competition_board_trade_permission_code[5];                          /* bytes 642 to 646 */
  uint8_t negotiation_possible_or_not_before_main_market;                      /* byte 647 */
  uint8_t end_keyword;                                                         /* byte 648 */
} EquitiesBatchDataMessage;

/* any Equities Batch Data Message at all: every byte one the checker chooses */
static void any_equities_batch_data_message(EquitiesBatchDataMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_instruments_of_the_contract[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
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
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = arbitrary(); }
  record->yesterdays_closing_price_type_code_krx = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->yesterdays_closing_price_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->yesterdays_accumulated_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->yesterdays_accumulated_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->upper_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->substitute_price_of_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->par_value[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->issuing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->number_of_listed_shares[i] = arbitrary(); }
  record->liquidation_trade = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->the_establishment_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exercising_period[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expiration_date_for_right[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->exercise_price_of_elw_or_bw[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->capital[i] = arbitrary(); }
  record->credit_order_possibility = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->limit_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->market_price_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->conditioned_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->best_favorable_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->first_best_order_permission_type[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->mid_price_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->stop_limit_price_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->capital_increase_type_code[i] = arbitrary(); }
  record->other_stock_type_code = arbitrary();
  record->national_stock = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->appraised_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lowest_order_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->highest_order_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->unit_of_volume_in_main_board[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lot_size_after_hours_trading[i] = arbitrary(); }
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
  for (size_t i = 0; i < 13; i++) { record->etf_tracking_difference[i] = arbitrary(); }
  record->regs = arbitrary();
  record->spac = arbitrary();
  record->tax_type_code = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->appraisal_ratio_of_substitute_price[i] = arbitrary(); }
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
  for (size_t i = 0; i < 23; i++) { record->upper_limit_quantity[i] = arbitrary(); }
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
  for (size_t i = 0; i < 11; i++) { record->yesterdays_closing_price_nxt[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->competition_board_trade_permission_code[i] = arbitrary(); }
  record->negotiation_possible_or_not_before_main_market = arbitrary();
  record->end_keyword = arbitrary();
}

/* Equities Batch Data Message to the wire: 649 bytes from at, returning where the next byte goes */
static size_t encode_equities_batch_data_message(const EquitiesBatchDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_number_of_instruments_of_the_contract[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
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
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->base_price[i]; }
  wire[at++] = record->yesterdays_closing_price_type_code_krx;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->yesterdays_closing_price_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->yesterdays_accumulated_trading_amount[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->yesterdays_accumulated_trading_value[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->upper_limit_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lower_limit_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->substitute_price_of_securities[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->par_value[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->issuing_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->listing_date[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->number_of_listed_shares[i]; }
  wire[at++] = record->liquidation_trade;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->the_establishment_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exercising_period[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiration_date_for_right[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->exercise_price_of_elw_or_bw[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->capital[i]; }
  wire[at++] = record->credit_order_possibility;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->limit_order_permission_type_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->market_price_order_permission_type_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->conditioned_order_permission_type_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->best_favorable_order_permission_type_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->first_best_order_permission_type[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->mid_price_order_permission_type_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->stop_limit_price_order_permission_type_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->capital_increase_type_code[i]; }
  wire[at++] = record->other_stock_type_code;
  wire[at++] = record->national_stock;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->appraised_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lowest_order_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->highest_order_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->unit_of_volume_in_main_board[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lot_size_after_hours_trading[i]; }
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
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->etf_tracking_difference[i]; }
  wire[at++] = record->regs;
  wire[at++] = record->spac;
  wire[at++] = record->tax_type_code;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->appraisal_ratio_of_substitute_price[i]; }
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
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->upper_limit_quantity[i]; }
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
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->yesterdays_closing_price_nxt[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->competition_board_trade_permission_code[i]; }
  wire[at++] = record->negotiation_possible_or_not_before_main_market;
  wire[at++] = record->end_keyword;

  return at;
}

/* Equities Batch Data Message off the wire: 649 bytes from at, returning where the next byte lies */
static size_t decode_equities_batch_data_message(EquitiesBatchDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_instruments_of_the_contract[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
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
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = wire[at++]; }
  record->yesterdays_closing_price_type_code_krx = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->yesterdays_closing_price_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->yesterdays_accumulated_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->yesterdays_accumulated_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->upper_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->substitute_price_of_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->par_value[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->issuing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->number_of_listed_shares[i] = wire[at++]; }
  record->liquidation_trade = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->the_establishment_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exercising_period[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expiration_date_for_right[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->exercise_price_of_elw_or_bw[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->capital[i] = wire[at++]; }
  record->credit_order_possibility = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->limit_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->market_price_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->conditioned_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->best_favorable_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->first_best_order_permission_type[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->mid_price_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->stop_limit_price_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->capital_increase_type_code[i] = wire[at++]; }
  record->other_stock_type_code = wire[at++];
  record->national_stock = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->appraised_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lowest_order_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->highest_order_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->unit_of_volume_in_main_board[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lot_size_after_hours_trading[i] = wire[at++]; }
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
  for (size_t i = 0; i < 13; i++) { record->etf_tracking_difference[i] = wire[at++]; }
  record->regs = wire[at++];
  record->spac = wire[at++];
  record->tax_type_code = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->appraisal_ratio_of_substitute_price[i] = wire[at++]; }
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
  for (size_t i = 0; i < 23; i++) { record->upper_limit_quantity[i] = wire[at++]; }
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
  for (size_t i = 0; i < 11; i++) { record->yesterdays_closing_price_nxt[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->competition_board_trade_permission_code[i] = wire[at++]; }
  record->negotiation_possible_or_not_before_main_market = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Equities Batch Data Message is what was written, byte for byte */
static void equal_equities_batch_data_message(const EquitiesBatchDataMessage *read, const EquitiesBatchDataMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_number_of_instruments_of_the_contract[i] == written->total_number_of_instruments_of_the_contract[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
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
  for (size_t i = 0; i < 11; i++) { assert(read->base_price[i] == written->base_price[i]); }
  assert(read->yesterdays_closing_price_type_code_krx == written->yesterdays_closing_price_type_code_krx);
  for (size_t i = 0; i < 11; i++) { assert(read->yesterdays_closing_price_krx[i] == written->yesterdays_closing_price_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->yesterdays_accumulated_trading_amount[i] == written->yesterdays_accumulated_trading_amount[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->yesterdays_accumulated_trading_value[i] == written->yesterdays_accumulated_trading_value[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->upper_limit_price[i] == written->upper_limit_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lower_limit_price[i] == written->lower_limit_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->substitute_price_of_securities[i] == written->substitute_price_of_securities[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->par_value[i] == written->par_value[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->issuing_price[i] == written->issuing_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->listing_date[i] == written->listing_date[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->number_of_listed_shares[i] == written->number_of_listed_shares[i]); }
  assert(read->liquidation_trade == written->liquidation_trade);
  for (size_t i = 0; i < 8; i++) { assert(read->the_establishment_date[i] == written->the_establishment_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exercising_period[i] == written->exercising_period[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expiration_date_for_right[i] == written->expiration_date_for_right[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->exercise_price_of_elw_or_bw[i] == written->exercise_price_of_elw_or_bw[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->capital[i] == written->capital[i]); }
  assert(read->credit_order_possibility == written->credit_order_possibility);
  for (size_t i = 0; i < 5; i++) { assert(read->limit_order_permission_type_code[i] == written->limit_order_permission_type_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->market_price_order_permission_type_code[i] == written->market_price_order_permission_type_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->conditioned_order_permission_type_code[i] == written->conditioned_order_permission_type_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->best_favorable_order_permission_type_code[i] == written->best_favorable_order_permission_type_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->first_best_order_permission_type[i] == written->first_best_order_permission_type[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->mid_price_order_permission_type_code[i] == written->mid_price_order_permission_type_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->stop_limit_price_order_permission_type_code[i] == written->stop_limit_price_order_permission_type_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->capital_increase_type_code[i] == written->capital_increase_type_code[i]); }
  assert(read->other_stock_type_code == written->other_stock_type_code);
  assert(read->national_stock == written->national_stock);
  for (size_t i = 0; i < 11; i++) { assert(read->appraised_price[i] == written->appraised_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lowest_order_price[i] == written->lowest_order_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->highest_order_price[i] == written->highest_order_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->unit_of_volume_in_main_board[i] == written->unit_of_volume_in_main_board[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lot_size_after_hours_trading[i] == written->lot_size_after_hours_trading[i]); }
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
  for (size_t i = 0; i < 13; i++) { assert(read->etf_tracking_difference[i] == written->etf_tracking_difference[i]); }
  assert(read->regs == written->regs);
  assert(read->spac == written->spac);
  assert(read->tax_type_code == written->tax_type_code);
  for (size_t i = 0; i < 13; i++) { assert(read->appraisal_ratio_of_substitute_price[i] == written->appraisal_ratio_of_substitute_price[i]); }
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
  for (size_t i = 0; i < 23; i++) { assert(read->upper_limit_quantity[i] == written->upper_limit_quantity[i]); }
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
  for (size_t i = 0; i < 11; i++) { assert(read->yesterdays_closing_price_nxt[i] == written->yesterdays_closing_price_nxt[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->competition_board_trade_permission_code[i] == written->competition_board_trade_permission_code[i]); }
  assert(read->negotiation_possible_or_not_before_main_market == written->negotiation_possible_or_not_before_main_market);
  assert(read->end_keyword == written->end_keyword);
}

/* Equities Batch Data Message: written and read back, then read and written back */
static void check_equities_batch_data_message(void) {
  EquitiesBatchDataMessage sent;
  EquitiesBatchDataMessage got;
  uint8_t wire[649];
  uint8_t again[649];

  any_equities_batch_data_message(&sent);
  assert(encode_equities_batch_data_message(&sent, wire, 0) == 649);
  assert(decode_equities_batch_data_message(&got, wire, 0) == 649);
  equal_equities_batch_data_message(&got, &sent);

  for (size_t i = 0; i < 649; i++) { wire[i] = arbitrary(); }
  assert(decode_equities_batch_data_message(&got, wire, 0) == 649);
  assert(encode_equities_batch_data_message(&got, again, 0) == 649);
  for (size_t i = 0; i < 649; i++) { assert(again[i] == wire[i]); }
}

/* ---- Member Information Message: 202 bytes ----------------------------------- */

/* Details. */
typedef struct {
  uint8_t message_sequence_number[8];                             /* bytes 0 to 7 */
  uint8_t business_date[8];                                       /* bytes 8 to 15 */
  uint8_t market_participant_number[5];                           /* bytes 16 to 20 */
  uint8_t name_of_a_market_participant_in_kr[80];                 /* bytes 21 to 100 */
  uint8_t name_of_a_market_participant_in_en[80];                 /* bytes 101 to 180 */
  uint8_t an_abbreviated_name_of_a_market_participant_in_kr[20];  /* bytes 181 to 200 */
  uint8_t end_keyword;                                            /* byte 201 */
} MemberInformationMessage;

/* any Member Information Message at all: every byte one the checker chooses */
static void any_member_information_message(MemberInformationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->market_participant_number[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->name_of_a_market_participant_in_kr[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->name_of_a_market_participant_in_en[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->an_abbreviated_name_of_a_market_participant_in_kr[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Member Information Message to the wire: 202 bytes from at, returning where the next byte goes */
static size_t encode_member_information_message(const MemberInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->market_participant_number[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->name_of_a_market_participant_in_kr[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->name_of_a_market_participant_in_en[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->an_abbreviated_name_of_a_market_participant_in_kr[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Member Information Message off the wire: 202 bytes from at, returning where the next byte lies */
static size_t decode_member_information_message(MemberInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->market_participant_number[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->name_of_a_market_participant_in_kr[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->name_of_a_market_participant_in_en[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->an_abbreviated_name_of_a_market_participant_in_kr[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Member Information Message is what was written, byte for byte */
static void equal_member_information_message(const MemberInformationMessage *read, const MemberInformationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->market_participant_number[i] == written->market_participant_number[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->name_of_a_market_participant_in_kr[i] == written->name_of_a_market_participant_in_kr[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->name_of_a_market_participant_in_en[i] == written->name_of_a_market_participant_in_en[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->an_abbreviated_name_of_a_market_participant_in_kr[i] == written->an_abbreviated_name_of_a_market_participant_in_kr[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Member Information Message: written and read back, then read and written back */
static void check_member_information_message(void) {
  MemberInformationMessage sent;
  MemberInformationMessage got;
  uint8_t wire[202];
  uint8_t again[202];

  any_member_information_message(&sent);
  assert(encode_member_information_message(&sent, wire, 0) == 202);
  assert(decode_member_information_message(&got, wire, 0) == 202);
  equal_member_information_message(&got, &sent);

  for (size_t i = 0; i < 202; i++) { wire[i] = arbitrary(); }
  assert(decode_member_information_message(&got, wire, 0) == 202);
  assert(encode_member_information_message(&got, again, 0) == 202);
  for (size_t i = 0; i < 202; i++) { assert(again[i] == wire[i]); }
}

/* ---- Issue Event Message: 43 bytes ------------------------------------------- */

/* Details. */
typedef struct {
  uint8_t message_sequence_number[8];  /* bytes 0 to 7 */
  uint8_t isin_code[12];               /* bytes 8 to 19 */
  uint8_t event_type_code[2];          /* bytes 20 to 21 */
  uint8_t event_reason_code[4];        /* bytes 22 to 25 */
  uint8_t event_start_date[8];         /* bytes 26 to 33 */
  uint8_t event_end_date[8];           /* bytes 34 to 41 */
  uint8_t end_keyword;                 /* byte 42 */
} IssueEventMessage;

/* any Issue Event Message at all: every byte one the checker chooses */
static void any_issue_event_message(IssueEventMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->event_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->event_reason_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_end_date[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Issue Event Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_issue_event_message(const IssueEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->event_type_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_reason_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_start_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_end_date[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Issue Event Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_issue_event_message(IssueEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->event_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->event_reason_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_end_date[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Issue Event Message is what was written, byte for byte */
static void equal_issue_event_message(const IssueEventMessage *read, const IssueEventMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->event_type_code[i] == written->event_type_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->event_reason_code[i] == written->event_reason_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_start_date[i] == written->event_start_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_end_date[i] == written->event_end_date[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Issue Event Message: written and read back, then read and written back */
static void check_issue_event_message(void) {
  IssueEventMessage sent;
  IssueEventMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_issue_event_message(&sent);
  assert(encode_issue_event_message(&sent, wire, 0) == 43);
  assert(decode_issue_event_message(&got, wire, 0) == 43);
  equal_issue_event_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_issue_event_message(&got, wire, 0) == 43);
  assert(encode_issue_event_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Block Basket Trade Data Message: 55 bytes ------------------------------- */

/* Block/Basket Trade Data in NXT. */
typedef struct {
  uint8_t board_id[2];                                   /* bytes 0 to 1 */
  uint8_t isin_code[12];                                 /* bytes 2 to 13 */
  uint8_t a_designated_number_for_an_issue_from_krx[6];  /* bytes 14 to 19 */
  uint8_t accumulated_trading_volume[12];                /* bytes 20 to 31 */
  uint8_t accumulated_trading_value[22];                 /* bytes 32 to 53 */
  uint8_t end_keyword;                                   /* byte 54 */
} BlockBasketTradeDataMessage;

/* any Block Basket Trade Data Message at all: every byte one the checker chooses */
static void any_block_basket_trade_data_message(BlockBasketTradeDataMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Block Basket Trade Data Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_block_basket_trade_data_message(const BlockBasketTradeDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Block Basket Trade Data Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_block_basket_trade_data_message(BlockBasketTradeDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Block Basket Trade Data Message is what was written, byte for byte */
static void equal_block_basket_trade_data_message(const BlockBasketTradeDataMessage *read, const BlockBasketTradeDataMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value[i] == written->accumulated_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Block Basket Trade Data Message: written and read back, then read and written back */
static void check_block_basket_trade_data_message(void) {
  BlockBasketTradeDataMessage sent;
  BlockBasketTradeDataMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_block_basket_trade_data_message(&sent);
  assert(encode_block_basket_trade_data_message(&sent, wire, 0) == 55);
  assert(decode_block_basket_trade_data_message(&got, wire, 0) == 55);
  equal_block_basket_trade_data_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_block_basket_trade_data_message(&got, wire, 0) == 55);
  assert(encode_block_basket_trade_data_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- Investor Activities Per An Issue Eod Message: 91 bytes ------------------ */

/* Investor Activities per an issue_EOD. */
typedef struct {
  uint8_t isin_code[12];                                 /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue_from_krx[6];  /* bytes 12 to 17 */
  uint8_t investor_code[4];                              /* bytes 18 to 21 */
  uint8_t accumulated_ask_trading_volume[12];            /* bytes 22 to 33 */
  uint8_t accumulated_ask_trading_value[22];             /* bytes 34 to 55 */
  uint8_t accumulated_bid_trading_volume[12];            /* bytes 56 to 67 */
  uint8_t accumulated_bid_trading_value[22];             /* bytes 68 to 89 */
  uint8_t end_keyword;                                   /* byte 90 */
} InvestorActivitiesPerAnIssueEodMessage;

/* any Investor Activities Per An Issue Eod Message at all: every byte one the checker chooses */
static void any_investor_activities_per_an_issue_eod_message(InvestorActivitiesPerAnIssueEodMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_ask_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_ask_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_bid_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_bid_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Investor Activities Per An Issue Eod Message to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_investor_activities_per_an_issue_eod_message(const InvestorActivitiesPerAnIssueEodMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue_from_krx[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->investor_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_ask_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_ask_trading_value[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_bid_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_bid_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Investor Activities Per An Issue Eod Message off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_investor_activities_per_an_issue_eod_message(InvestorActivitiesPerAnIssueEodMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue_from_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_ask_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_ask_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_bid_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_bid_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Investor Activities Per An Issue Eod Message is what was written, byte for byte */
static void equal_investor_activities_per_an_issue_eod_message(const InvestorActivitiesPerAnIssueEodMessage *read, const InvestorActivitiesPerAnIssueEodMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue_from_krx[i] == written->a_designated_number_for_an_issue_from_krx[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->investor_code[i] == written->investor_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_ask_trading_volume[i] == written->accumulated_ask_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_ask_trading_value[i] == written->accumulated_ask_trading_value[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_bid_trading_volume[i] == written->accumulated_bid_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_bid_trading_value[i] == written->accumulated_bid_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Investor Activities Per An Issue Eod Message: written and read back, then read and written back */
static void check_investor_activities_per_an_issue_eod_message(void) {
  InvestorActivitiesPerAnIssueEodMessage sent;
  InvestorActivitiesPerAnIssueEodMessage got;
  uint8_t wire[91];
  uint8_t again[91];

  any_investor_activities_per_an_issue_eod_message(&sent);
  assert(encode_investor_activities_per_an_issue_eod_message(&sent, wire, 0) == 91);
  assert(decode_investor_activities_per_an_issue_eod_message(&got, wire, 0) == 91);
  equal_investor_activities_per_an_issue_eod_message(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_investor_activities_per_an_issue_eod_message(&got, wire, 0) == 91);
  assert(encode_investor_activities_per_an_issue_eod_message(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Selling Message: 115 bytes ---------------------------------------- */

/* Short Selling. */
typedef struct {
  uint8_t isin_code[12];                                                   /* bytes 0 to 11 */
  uint8_t covered_short_selling_trading_volume[12];                        /* bytes 12 to 23 */
  uint8_t covered_short_selling_trading_value[22];                         /* bytes 24 to 45 */
  uint8_t uptick_rule_applied_covered_short_selling_trading_volume[12];    /* bytes 46 to 57 */
  uint8_t uptick_rule_applied_covered_short_selling_trading_value[22];     /* bytes 58 to 79 */
  uint8_t uptick_rule_unapplied_covered_short_selling_trading_volume[12];  /* bytes 80 to 91 */
  uint8_t uptick_rule_unapplied_covered_short_selling_trading_value[22];   /* bytes 92 to 113 */
  uint8_t end_keyword;                                                     /* byte 114 */
} ShortSellingMessage;

/* any Short Selling Message at all: every byte one the checker chooses */
static void any_short_selling_message(ShortSellingMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->covered_short_selling_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->covered_short_selling_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->uptick_rule_applied_covered_short_selling_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->uptick_rule_applied_covered_short_selling_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->uptick_rule_unapplied_covered_short_selling_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->uptick_rule_unapplied_covered_short_selling_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Short Selling Message to the wire: 115 bytes from at, returning where the next byte goes */
static size_t encode_short_selling_message(const ShortSellingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->covered_short_selling_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->covered_short_selling_trading_value[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->uptick_rule_applied_covered_short_selling_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->uptick_rule_applied_covered_short_selling_trading_value[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->uptick_rule_unapplied_covered_short_selling_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->uptick_rule_unapplied_covered_short_selling_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Short Selling Message off the wire: 115 bytes from at, returning where the next byte lies */
static size_t decode_short_selling_message(ShortSellingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->covered_short_selling_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->covered_short_selling_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->uptick_rule_applied_covered_short_selling_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->uptick_rule_applied_covered_short_selling_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->uptick_rule_unapplied_covered_short_selling_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->uptick_rule_unapplied_covered_short_selling_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Short Selling Message is what was written, byte for byte */
static void equal_short_selling_message(const ShortSellingMessage *read, const ShortSellingMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->covered_short_selling_trading_volume[i] == written->covered_short_selling_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->covered_short_selling_trading_value[i] == written->covered_short_selling_trading_value[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->uptick_rule_applied_covered_short_selling_trading_volume[i] == written->uptick_rule_applied_covered_short_selling_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->uptick_rule_applied_covered_short_selling_trading_value[i] == written->uptick_rule_applied_covered_short_selling_trading_value[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->uptick_rule_unapplied_covered_short_selling_trading_volume[i] == written->uptick_rule_unapplied_covered_short_selling_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->uptick_rule_unapplied_covered_short_selling_trading_value[i] == written->uptick_rule_unapplied_covered_short_selling_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Short Selling Message: written and read back, then read and written back */
static void check_short_selling_message(void) {
  ShortSellingMessage sent;
  ShortSellingMessage got;
  uint8_t wire[115];
  uint8_t again[115];

  any_short_selling_message(&sent);
  assert(encode_short_selling_message(&sent, wire, 0) == 115);
  assert(decode_short_selling_message(&got, wire, 0) == 115);
  equal_short_selling_message(&got, &sent);

  for (size_t i = 0; i < 115; i++) { wire[i] = arbitrary(); }
  assert(decode_short_selling_message(&got, wire, 0) == 115);
  assert(encode_short_selling_message(&got, again, 0) == 115);
  for (size_t i = 0; i < 115; i++) { assert(again[i] == wire[i]); }
}

/* ---- Brokers Acitity Information Message: 86 bytes --------------------------- */

/* Information on Brokers Activity in NXT market. */
typedef struct {
  uint8_t isin_code[12];                       /* bytes 0 to 11 */
  uint8_t member_number[5];                    /* bytes 12 to 16 */
  uint8_t accumulated_ask_trading_volume[12];  /* bytes 17 to 28 */
  uint8_t accumulated_ask_trading_value[22];   /* bytes 29 to 50 */
  uint8_t accumulated_bid_trading_volume[12];  /* bytes 51 to 62 */
  uint8_t accumulated_bid_trading_value[22];   /* bytes 63 to 84 */
  uint8_t end_keyword;                         /* byte 85 */
} BrokersAcitityInformationMessage;

/* any Brokers Acitity Information Message at all: every byte one the checker chooses */
static void any_brokers_acitity_information_message(BrokersAcitityInformationMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_ask_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_ask_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_bid_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_bid_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Brokers Acitity Information Message to the wire: 86 bytes from at, returning where the next byte goes */
static size_t encode_brokers_acitity_information_message(const BrokersAcitityInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_ask_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_ask_trading_value[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_bid_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_bid_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Brokers Acitity Information Message off the wire: 86 bytes from at, returning where the next byte lies */
static size_t decode_brokers_acitity_information_message(BrokersAcitityInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_ask_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_ask_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_bid_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_bid_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Brokers Acitity Information Message is what was written, byte for byte */
static void equal_brokers_acitity_information_message(const BrokersAcitityInformationMessage *read, const BrokersAcitityInformationMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number[i] == written->member_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_ask_trading_volume[i] == written->accumulated_ask_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_ask_trading_value[i] == written->accumulated_ask_trading_value[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_bid_trading_volume[i] == written->accumulated_bid_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_bid_trading_value[i] == written->accumulated_bid_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Brokers Acitity Information Message: written and read back, then read and written back */
static void check_brokers_acitity_information_message(void) {
  BrokersAcitityInformationMessage sent;
  BrokersAcitityInformationMessage got;
  uint8_t wire[86];
  uint8_t again[86];

  any_brokers_acitity_information_message(&sent);
  assert(encode_brokers_acitity_information_message(&sent, wire, 0) == 86);
  assert(decode_brokers_acitity_information_message(&got, wire, 0) == 86);
  equal_brokers_acitity_information_message(&got, &sent);

  for (size_t i = 0; i < 86; i++) { wire[i] = arbitrary(); }
  assert(decode_brokers_acitity_information_message(&got, wire, 0) == 86);
  assert(encode_brokers_acitity_information_message(&got, again, 0) == 86);
  for (size_t i = 0; i < 86; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Activity By Session Per An Issue Message: 120 bytes ------------- */

/* Trading Activity by session for each issue and market. */
typedef struct {
  uint8_t isin_code[12];                                              /* bytes 0 to 11 */
  uint8_t total_number_of_tradable_issues_on_competitive_trading[5];  /* bytes 12 to 16 */
  uint8_t pre_market_accumulated_trading_volume[12];                  /* bytes 17 to 28 */
  uint8_t pre_market_accumulated_trading_value[22];                   /* bytes 29 to 50 */
  uint8_t main_market_accumulated_trading_volume[12];                 /* bytes 51 to 62 */
  uint8_t main_market_accumulated_trading_value[22];                  /* bytes 63 to 84 */
  uint8_t after_market_accumulated_trading_volume[12];                /* bytes 85 to 96 */
  uint8_t after_market_accumulated_trading_value[22];                 /* bytes 97 to 118 */
  uint8_t end_keyword;                                                /* byte 119 */
} TradingActivityBySessionPerAnIssueMessage;

/* any Trading Activity By Session Per An Issue Message at all: every byte one the checker chooses */
static void any_trading_activity_by_session_per_an_issue_message(TradingActivityBySessionPerAnIssueMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->total_number_of_tradable_issues_on_competitive_trading[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->pre_market_accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->pre_market_accumulated_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->main_market_accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->main_market_accumulated_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->after_market_accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->after_market_accumulated_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Trading Activity By Session Per An Issue Message to the wire: 120 bytes from at, returning where the next byte goes */
static size_t encode_trading_activity_by_session_per_an_issue_message(const TradingActivityBySessionPerAnIssueMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->total_number_of_tradable_issues_on_competitive_trading[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->pre_market_accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->pre_market_accumulated_trading_value[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->main_market_accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->main_market_accumulated_trading_value[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->after_market_accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->after_market_accumulated_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Trading Activity By Session Per An Issue Message off the wire: 120 bytes from at, returning where the next byte lies */
static size_t decode_trading_activity_by_session_per_an_issue_message(TradingActivityBySessionPerAnIssueMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->total_number_of_tradable_issues_on_competitive_trading[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->pre_market_accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->pre_market_accumulated_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->main_market_accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->main_market_accumulated_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->after_market_accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->after_market_accumulated_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Trading Activity By Session Per An Issue Message is what was written, byte for byte */
static void equal_trading_activity_by_session_per_an_issue_message(const TradingActivityBySessionPerAnIssueMessage *read, const TradingActivityBySessionPerAnIssueMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->total_number_of_tradable_issues_on_competitive_trading[i] == written->total_number_of_tradable_issues_on_competitive_trading[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->pre_market_accumulated_trading_volume[i] == written->pre_market_accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->pre_market_accumulated_trading_value[i] == written->pre_market_accumulated_trading_value[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->main_market_accumulated_trading_volume[i] == written->main_market_accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->main_market_accumulated_trading_value[i] == written->main_market_accumulated_trading_value[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->after_market_accumulated_trading_volume[i] == written->after_market_accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->after_market_accumulated_trading_value[i] == written->after_market_accumulated_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Trading Activity By Session Per An Issue Message: written and read back, then read and written back */
static void check_trading_activity_by_session_per_an_issue_message(void) {
  TradingActivityBySessionPerAnIssueMessage sent;
  TradingActivityBySessionPerAnIssueMessage got;
  uint8_t wire[120];
  uint8_t again[120];

  any_trading_activity_by_session_per_an_issue_message(&sent);
  assert(encode_trading_activity_by_session_per_an_issue_message(&sent, wire, 0) == 120);
  assert(decode_trading_activity_by_session_per_an_issue_message(&got, wire, 0) == 120);
  equal_trading_activity_by_session_per_an_issue_message(&got, &sent);

  for (size_t i = 0; i < 120; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_activity_by_session_per_an_issue_message(&got, wire, 0) == 120);
  assert(encode_trading_activity_by_session_per_an_issue_message(&got, again, 0) == 120);
  for (size_t i = 0; i < 120; i++) { assert(again[i] == wire[i]); }
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
