// koscom/mdcsrealtime/commodities/Koscom_MdcsRealtime_Commodities_v2_018.c
/*
 * Koscom Co., Ltd. MDCS Realtime Commodities
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

/* Polling data transmitted at one-minute intervals on every market data feed. Carries Current Time as a heartbeat. */
typedef struct {
  uint8_t current_time[4];  /* bytes 0 to 3 */
  uint8_t end_keyword;      /* byte 4 */
} PollingDataMessage;

/* any Polling Data Message at all: every byte one the checker chooses */
static void any_polling_data_message(PollingDataMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->current_time[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Polling Data Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_polling_data_message(const PollingDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->current_time[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Polling Data Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_polling_data_message(PollingDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->current_time[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Polling Data Message is what was written, byte for byte */
static void equal_polling_data_message(const PollingDataMessage *read, const PollingDataMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->current_time[i] == written->current_time[i]); }
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

/* ---- Krx Index Message: 72 bytes --------------------------------------------- */

/* Krx Index real-time message. Reports current index value, change against previous day, accumulated trading volume, and accumulated trading value for one index. The Index ID field identifies which index group (KRX Index Group 1/2/3, Sector A/B, Gold Spot, or Equity Derivatives) this record belongs to. */
typedef struct {
  uint8_t index_id[6];                                 /* bytes 0 to 5 */
  uint8_t isin_code[12];                               /* bytes 6 to 17 */
  uint8_t calculation_time[6];                         /* bytes 18 to 23 */
  uint8_t index[9];                                    /* bytes 24 to 32 */
  uint8_t index_change_sign_against_the_previous_day;  /* byte 33 */
  uint8_t index_change_against_the_previous_day[9];    /* bytes 34 to 42 */
  uint8_t accumulated_trading_volume[12];              /* bytes 43 to 54 */
  uint8_t accumulated_trading_value_short[12];         /* bytes 55 to 66 */
  uint8_t filler_4[4];                                 /* bytes 67 to 70 */
  uint8_t end_keyword;                                 /* byte 71 */
} KrxIndexMessage;

/* any Krx Index Message at all: every byte one the checker chooses */
static void any_krx_index_message(KrxIndexMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->calculation_time[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->index[i] = arbitrary(); }
  record->index_change_sign_against_the_previous_day = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->index_change_against_the_previous_day[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_value_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Krx Index Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_krx_index_message(const KrxIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->calculation_time[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index[i]; }
  wire[at++] = record->index_change_sign_against_the_previous_day;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index_change_against_the_previous_day[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_value_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Krx Index Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_krx_index_message(KrxIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->calculation_time[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->index[i] = wire[at++]; }
  record->index_change_sign_against_the_previous_day = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->index_change_against_the_previous_day[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_value_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Krx Index Message is what was written, byte for byte */
static void equal_krx_index_message(const KrxIndexMessage *read, const KrxIndexMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->calculation_time[i] == written->calculation_time[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->index[i] == written->index[i]); }
  assert(read->index_change_sign_against_the_previous_day == written->index_change_sign_against_the_previous_day);
  for (size_t i = 0; i < 9; i++) { assert(read->index_change_against_the_previous_day[i] == written->index_change_against_the_previous_day[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_value_short[i] == written->accumulated_trading_value_short[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Krx Index Message: written and read back, then read and written back */
static void check_krx_index_message(void) {
  KrxIndexMessage sent;
  KrxIndexMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_krx_index_message(&sent);
  assert(encode_krx_index_message(&sent, wire, 0) == 72);
  assert(decode_krx_index_message(&got, wire, 0) == 72);
  equal_krx_index_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_krx_index_message(&got, wire, 0) == 72);
  assert(encode_krx_index_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Krx Estimated Index Message: 72 bytes ----------------------------------- */

/* Krx Estimated Index real-time message. Reports the estimated index value during the pre-opening simultaneous-trading window or during regular session estimation. Identical field layout to the Krx Index Message. */
typedef struct {
  uint8_t index_id[6];                                 /* bytes 0 to 5 */
  uint8_t isin_code[12];                               /* bytes 6 to 17 */
  uint8_t calculation_time[6];                         /* bytes 18 to 23 */
  uint8_t index[9];                                    /* bytes 24 to 32 */
  uint8_t index_change_sign_against_the_previous_day;  /* byte 33 */
  uint8_t index_change_against_the_previous_day[9];    /* bytes 34 to 42 */
  uint8_t accumulated_trading_volume[12];              /* bytes 43 to 54 */
  uint8_t accumulated_trading_value_short[12];         /* bytes 55 to 66 */
  uint8_t filler_4[4];                                 /* bytes 67 to 70 */
  uint8_t end_keyword;                                 /* byte 71 */
} KrxEstimatedIndexMessage;

/* any Krx Estimated Index Message at all: every byte one the checker chooses */
static void any_krx_estimated_index_message(KrxEstimatedIndexMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->calculation_time[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->index[i] = arbitrary(); }
  record->index_change_sign_against_the_previous_day = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->index_change_against_the_previous_day[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_value_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Krx Estimated Index Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_krx_estimated_index_message(const KrxEstimatedIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->calculation_time[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index[i]; }
  wire[at++] = record->index_change_sign_against_the_previous_day;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index_change_against_the_previous_day[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_value_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Krx Estimated Index Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_krx_estimated_index_message(KrxEstimatedIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->calculation_time[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->index[i] = wire[at++]; }
  record->index_change_sign_against_the_previous_day = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->index_change_against_the_previous_day[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_value_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Krx Estimated Index Message is what was written, byte for byte */
static void equal_krx_estimated_index_message(const KrxEstimatedIndexMessage *read, const KrxEstimatedIndexMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->calculation_time[i] == written->calculation_time[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->index[i] == written->index[i]); }
  assert(read->index_change_sign_against_the_previous_day == written->index_change_sign_against_the_previous_day);
  for (size_t i = 0; i < 9; i++) { assert(read->index_change_against_the_previous_day[i] == written->index_change_against_the_previous_day[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_value_short[i] == written->accumulated_trading_value_short[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Krx Estimated Index Message: written and read back, then read and written back */
static void check_krx_estimated_index_message(void) {
  KrxEstimatedIndexMessage sent;
  KrxEstimatedIndexMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_krx_estimated_index_message(&sent);
  assert(encode_krx_estimated_index_message(&sent, wire, 0) == 72);
  assert(decode_krx_estimated_index_message(&got, wire, 0) == 72);
  equal_krx_estimated_index_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_krx_estimated_index_message(&got, wire, 0) == 72);
  assert(encode_krx_estimated_index_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Global Index Message: 59 bytes ------------------------------------------ */

/* Global Index real-time message. Reports the current value of a foreign index referenced by KRX (e.g. Korea-Taiwan IT Premier, Korea-China Index) in the index's native currency. */
typedef struct {
  uint8_t index_id[6];                                 /* bytes 0 to 5 */
  uint8_t isin_code[12];                               /* bytes 6 to 17 */
  uint8_t business_date[8];                            /* bytes 18 to 25 */
  uint8_t calculation_time[6];                         /* bytes 26 to 31 */
  uint8_t index[9];                                    /* bytes 32 to 40 */
  uint8_t index_change_sign_against_the_previous_day;  /* byte 41 */
  uint8_t index_change_against_the_previous_day[9];    /* bytes 42 to 50 */
  uint8_t currency_code_short[3];                      /* bytes 51 to 53 */
  uint8_t filler_4[4];                                 /* bytes 54 to 57 */
  uint8_t end_keyword;                                 /* byte 58 */
} GlobalIndexMessage;

/* any Global Index Message at all: every byte one the checker chooses */
static void any_global_index_message(GlobalIndexMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->calculation_time[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->index[i] = arbitrary(); }
  record->index_change_sign_against_the_previous_day = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->index_change_against_the_previous_day[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency_code_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Global Index Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_global_index_message(const GlobalIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->calculation_time[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index[i]; }
  wire[at++] = record->index_change_sign_against_the_previous_day;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index_change_against_the_previous_day[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency_code_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Global Index Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_global_index_message(GlobalIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->calculation_time[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->index[i] = wire[at++]; }
  record->index_change_sign_against_the_previous_day = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->index_change_against_the_previous_day[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency_code_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Global Index Message is what was written, byte for byte */
static void equal_global_index_message(const GlobalIndexMessage *read, const GlobalIndexMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->calculation_time[i] == written->calculation_time[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->index[i] == written->index[i]); }
  assert(read->index_change_sign_against_the_previous_day == written->index_change_sign_against_the_previous_day);
  for (size_t i = 0; i < 9; i++) { assert(read->index_change_against_the_previous_day[i] == written->index_change_against_the_previous_day[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency_code_short[i] == written->currency_code_short[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Global Index Message: written and read back, then read and written back */
static void check_global_index_message(void) {
  GlobalIndexMessage sent;
  GlobalIndexMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_global_index_message(&sent);
  assert(encode_global_index_message(&sent, wire, 0) == 59);
  assert(decode_global_index_message(&got, wire, 0) == 59);
  equal_global_index_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_global_index_message(&got, wire, 0) == 59);
  assert(encode_global_index_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bond Prime Index Message: 177 bytes ------------------------------------- */

/* Bond Prime Index intraday calculation. Reports clean and total-earnings index values plus their weighted variants and average duration / convexity / yield for one Group Code and Maturity Code pair. */
typedef struct {
  uint8_t calculating_date[8];                                         /* bytes 0 to 7 */
  uint8_t calculating_time[8];                                         /* bytes 8 to 15 */
  uint8_t group_code[5];                                               /* bytes 16 to 20 */
  uint8_t maturity_code[3];                                            /* bytes 21 to 23 */
  uint8_t clean_price_index_krx[16];                                   /* bytes 24 to 39 */
  uint8_t total_earnings_index[16];                                    /* bytes 40 to 55 */
  uint8_t clean_price_index_weight[16];                                /* bytes 56 to 71 */
  uint8_t total_earnings_index_weight[16];                             /* bytes 72 to 87 */
  uint8_t weight_of_clean_index_value_for_integrity_index_weight[16];  /* bytes 88 to 103 */
  uint8_t weight_of_sum_index_value_for_integrity_index_weight[16];    /* bytes 104 to 119 */
  uint8_t average_duration[16];                                        /* bytes 120 to 135 */
  uint8_t average_convexity[16];                                       /* bytes 136 to 151 */
  uint8_t average_yld[16];                                             /* bytes 152 to 167 */
  uint8_t transmission_time[8];                                        /* bytes 168 to 175 */
  uint8_t end_keyword;                                                 /* byte 176 */
} BondPrimeIndexMessage;

/* any Bond Prime Index Message at all: every byte one the checker chooses */
static void any_bond_prime_index_message(BondPrimeIndexMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->calculating_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->calculating_time[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->group_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->maturity_code[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->clean_price_index_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->total_earnings_index[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->clean_price_index_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->total_earnings_index_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->weight_of_clean_index_value_for_integrity_index_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->weight_of_sum_index_value_for_integrity_index_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->average_duration[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->average_convexity[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->average_yld[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transmission_time[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Bond Prime Index Message to the wire: 177 bytes from at, returning where the next byte goes */
static size_t encode_bond_prime_index_message(const BondPrimeIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->calculating_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->calculating_time[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->group_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->maturity_code[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->clean_price_index_krx[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->total_earnings_index[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->clean_price_index_weight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->total_earnings_index_weight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->weight_of_clean_index_value_for_integrity_index_weight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->weight_of_sum_index_value_for_integrity_index_weight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->average_duration[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->average_convexity[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->average_yld[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transmission_time[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Bond Prime Index Message off the wire: 177 bytes from at, returning where the next byte lies */
static size_t decode_bond_prime_index_message(BondPrimeIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->calculating_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->calculating_time[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->group_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->maturity_code[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->clean_price_index_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->total_earnings_index[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->clean_price_index_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->total_earnings_index_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->weight_of_clean_index_value_for_integrity_index_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->weight_of_sum_index_value_for_integrity_index_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->average_duration[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->average_convexity[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->average_yld[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transmission_time[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Bond Prime Index Message is what was written, byte for byte */
static void equal_bond_prime_index_message(const BondPrimeIndexMessage *read, const BondPrimeIndexMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->calculating_date[i] == written->calculating_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->calculating_time[i] == written->calculating_time[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->group_code[i] == written->group_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->maturity_code[i] == written->maturity_code[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->clean_price_index_krx[i] == written->clean_price_index_krx[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->total_earnings_index[i] == written->total_earnings_index[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->clean_price_index_weight[i] == written->clean_price_index_weight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->total_earnings_index_weight[i] == written->total_earnings_index_weight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->weight_of_clean_index_value_for_integrity_index_weight[i] == written->weight_of_clean_index_value_for_integrity_index_weight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->weight_of_sum_index_value_for_integrity_index_weight[i] == written->weight_of_sum_index_value_for_integrity_index_weight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->average_duration[i] == written->average_duration[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->average_convexity[i] == written->average_convexity[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->average_yld[i] == written->average_yld[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transmission_time[i] == written->transmission_time[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Bond Prime Index Message: written and read back, then read and written back */
static void check_bond_prime_index_message(void) {
  BondPrimeIndexMessage sent;
  BondPrimeIndexMessage got;
  uint8_t wire[177];
  uint8_t again[177];

  any_bond_prime_index_message(&sent);
  assert(encode_bond_prime_index_message(&sent, wire, 0) == 177);
  assert(decode_bond_prime_index_message(&got, wire, 0) == 177);
  equal_bond_prime_index_message(&got, &sent);

  for (size_t i = 0; i < 177; i++) { wire[i] = arbitrary(); }
  assert(decode_bond_prime_index_message(&got, wire, 0) == 177);
  assert(encode_bond_prime_index_message(&got, again, 0) == 177);
  for (size_t i = 0; i < 177; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bond Ktb Index Message: 114 bytes --------------------------------------- */

/* Bond KTB Index intraday calculation. Reports total profit, clean price, market price, call and zero re-investment indices, futures basis price, duration, convexity, and YTM for one KTB-based Bond Index ID. */
typedef struct {
  uint8_t bond_index_id[6];                  /* bytes 0 to 5 */
  uint8_t base_date[8];                      /* bytes 6 to 13 */
  uint8_t base_time[6];                      /* bytes 14 to 19 */
  uint8_t total_profit_index[11];            /* bytes 20 to 30 */
  uint8_t clean_price_index_ktb[11];         /* bytes 31 to 41 */
  uint8_t market_price_index_ktb[11];        /* bytes 42 to 52 */
  uint8_t call_re_investment_index_ktb[11];  /* bytes 53 to 63 */
  uint8_t zero_re_investment_index_ktb[11];  /* bytes 64 to 74 */
  uint8_t futures_basis_price[10];           /* bytes 75 to 84 */
  uint8_t duration[7];                       /* bytes 85 to 91 */
  uint8_t convexity[7];                      /* bytes 92 to 98 */
  uint8_t average_ytm[7];                    /* bytes 99 to 105 */
  uint8_t average_forward_ytm[7];            /* bytes 106 to 112 */
  uint8_t end_keyword;                       /* byte 113 */
} BondKtbIndexMessage;

/* any Bond Ktb Index Message at all: every byte one the checker chooses */
static void any_bond_ktb_index_message(BondKtbIndexMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->bond_index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->base_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->base_time[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->total_profit_index[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->clean_price_index_ktb[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->market_price_index_ktb[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->call_re_investment_index_ktb[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->zero_re_investment_index_ktb[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->futures_basis_price[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->duration[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->convexity[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->average_ytm[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->average_forward_ytm[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Bond Ktb Index Message to the wire: 114 bytes from at, returning where the next byte goes */
static size_t encode_bond_ktb_index_message(const BondKtbIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->bond_index_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->base_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->base_time[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->total_profit_index[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->clean_price_index_ktb[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->market_price_index_ktb[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->call_re_investment_index_ktb[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->zero_re_investment_index_ktb[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->futures_basis_price[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->duration[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->convexity[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->average_ytm[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->average_forward_ytm[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Bond Ktb Index Message off the wire: 114 bytes from at, returning where the next byte lies */
static size_t decode_bond_ktb_index_message(BondKtbIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->bond_index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->base_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->base_time[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->total_profit_index[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->clean_price_index_ktb[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->market_price_index_ktb[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->call_re_investment_index_ktb[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->zero_re_investment_index_ktb[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->futures_basis_price[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->duration[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->convexity[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->average_ytm[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->average_forward_ytm[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Bond Ktb Index Message is what was written, byte for byte */
static void equal_bond_ktb_index_message(const BondKtbIndexMessage *read, const BondKtbIndexMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->bond_index_id[i] == written->bond_index_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->base_date[i] == written->base_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->base_time[i] == written->base_time[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->total_profit_index[i] == written->total_profit_index[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->clean_price_index_ktb[i] == written->clean_price_index_ktb[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->market_price_index_ktb[i] == written->market_price_index_ktb[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->call_re_investment_index_ktb[i] == written->call_re_investment_index_ktb[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->zero_re_investment_index_ktb[i] == written->zero_re_investment_index_ktb[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->futures_basis_price[i] == written->futures_basis_price[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->duration[i] == written->duration[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->convexity[i] == written->convexity[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->average_ytm[i] == written->average_ytm[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->average_forward_ytm[i] == written->average_forward_ytm[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Bond Ktb Index Message: written and read back, then read and written back */
static void check_bond_ktb_index_message(void) {
  BondKtbIndexMessage sent;
  BondKtbIndexMessage got;
  uint8_t wire[114];
  uint8_t again[114];

  any_bond_ktb_index_message(&sent);
  assert(encode_bond_ktb_index_message(&sent, wire, 0) == 114);
  assert(decode_bond_ktb_index_message(&got, wire, 0) == 114);
  equal_bond_ktb_index_message(&got, &sent);

  for (size_t i = 0; i < 114; i++) { wire[i] = arbitrary(); }
  assert(decode_bond_ktb_index_message(&got, wire, 0) == 114);
  assert(encode_bond_ktb_index_message(&got, again, 0) == 114);
  for (size_t i = 0; i < 114; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bond Ktb Index Term Structure Message: 61 bytes ------------------------- */

/* Bond KTB Index TermStructure. One record per ISIN constituent of a KTB Index showing its basis price, clean price, YTM, and the Index Constituent flag. */
typedef struct {
  uint8_t bond_index_id[6];   /* bytes 0 to 5 */
  uint8_t base_date[8];       /* bytes 6 to 13 */
  uint8_t base_time[6];       /* bytes 14 to 19 */
  uint8_t isin_code[12];      /* bytes 20 to 31 */
  uint8_t basis_price[10];    /* bytes 32 to 41 */
  uint8_t clean_price[10];    /* bytes 42 to 51 */
  uint8_t average_ytm[7];     /* bytes 52 to 58 */
  uint8_t index_constituent;  /* byte 59 */
  uint8_t end_keyword;        /* byte 60 */
} BondKtbIndexTermStructureMessage;

/* any Bond Ktb Index Term Structure Message at all: every byte one the checker chooses */
static void any_bond_ktb_index_term_structure_message(BondKtbIndexTermStructureMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->bond_index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->base_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->base_time[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->basis_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->clean_price[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->average_ytm[i] = arbitrary(); }
  record->index_constituent = arbitrary();
  record->end_keyword = arbitrary();
}

/* Bond Ktb Index Term Structure Message to the wire: 61 bytes from at, returning where the next byte goes */
static size_t encode_bond_ktb_index_term_structure_message(const BondKtbIndexTermStructureMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->bond_index_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->base_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->base_time[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->basis_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->clean_price[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->average_ytm[i]; }
  wire[at++] = record->index_constituent;
  wire[at++] = record->end_keyword;

  return at;
}

/* Bond Ktb Index Term Structure Message off the wire: 61 bytes from at, returning where the next byte lies */
static size_t decode_bond_ktb_index_term_structure_message(BondKtbIndexTermStructureMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->bond_index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->base_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->base_time[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->basis_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->clean_price[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->average_ytm[i] = wire[at++]; }
  record->index_constituent = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Bond Ktb Index Term Structure Message is what was written, byte for byte */
static void equal_bond_ktb_index_term_structure_message(const BondKtbIndexTermStructureMessage *read, const BondKtbIndexTermStructureMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->bond_index_id[i] == written->bond_index_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->base_date[i] == written->base_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->base_time[i] == written->base_time[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->basis_price[i] == written->basis_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->clean_price[i] == written->clean_price[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->average_ytm[i] == written->average_ytm[i]); }
  assert(read->index_constituent == written->index_constituent);
  assert(read->end_keyword == written->end_keyword);
}

/* Bond Ktb Index Term Structure Message: written and read back, then read and written back */
static void check_bond_ktb_index_term_structure_message(void) {
  BondKtbIndexTermStructureMessage sent;
  BondKtbIndexTermStructureMessage got;
  uint8_t wire[61];
  uint8_t again[61];

  any_bond_ktb_index_term_structure_message(&sent);
  assert(encode_bond_ktb_index_term_structure_message(&sent, wire, 0) == 61);
  assert(decode_bond_ktb_index_term_structure_message(&got, wire, 0) == 61);
  equal_bond_ktb_index_term_structure_message(&got, &sent);

  for (size_t i = 0; i < 61; i++) { wire[i] = arbitrary(); }
  assert(decode_bond_ktb_index_term_structure_message(&got, wire, 0) == 61);
  assert(encode_bond_ktb_index_term_structure_message(&got, again, 0) == 61);
  for (size_t i = 0; i < 61; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bond Index Krx Message: 518 bytes --------------------------------------- */

/* KRX Aggregate Bond Index (AA- or higher) end-of-day index data. Reports clean-price, total-earnings, market-price, and re-investment indices, their weighted variants, integrity-index weights, average duration, convexity, yield, coupon, remaining maturity, spread, market capitalization, and accumulated cash flows for one Bond Index ID. */
typedef struct {
  uint8_t message_sequence_number[8];                                               /* bytes 0 to 7 */
  uint8_t calculating_date[8];                                                      /* bytes 8 to 15 */
  uint8_t index_id[6];                                                              /* bytes 16 to 21 */
  uint8_t clean_price_index_krx[16];                                                /* bytes 22 to 37 */
  uint8_t total_earnings_index[16];                                                 /* bytes 38 to 53 */
  uint8_t market_price_index_krx[16];                                               /* bytes 54 to 69 */
  uint8_t zero_re_investment_index_krx[16];                                         /* bytes 70 to 85 */
  uint8_t call_re_investment_index_krx[16];                                         /* bytes 86 to 101 */
  uint8_t clean_price_index_weight[16];                                             /* bytes 102 to 117 */
  uint8_t total_earnings_index_weight[16];                                          /* bytes 118 to 133 */
  uint8_t market_price_index_weight[16];                                            /* bytes 134 to 149 */
  uint8_t zero_re_investment_index_weight[16];                                      /* bytes 150 to 165 */
  uint8_t call_re_investment_index_weight[16];                                      /* bytes 166 to 181 */
  uint8_t weight_of_clean_index_value_for_integrity_index_weight[16];               /* bytes 182 to 197 */
  uint8_t weight_of_sum_index_value_for_integrity_index_weight[16];                 /* bytes 198 to 213 */
  uint8_t weight_of_zero_re_investment_index_value_for_integrity_index_weight[16];  /* bytes 214 to 229 */
  uint8_t weight_of_call_re_investment_index_value_for_integrity_index_weight[16];  /* bytes 230 to 245 */
  uint8_t average_duration[16];                                                     /* bytes 246 to 261 */
  uint8_t average_convexity[16];                                                    /* bytes 262 to 277 */
  uint8_t average_yld[16];                                                          /* bytes 278 to 293 */
  uint8_t average_coupon_price[16];                                                 /* bytes 294 to 309 */
  uint8_t average_remaining_maturity_price[16];                                     /* bytes 310 to 325 */
  uint8_t average_current_yield[16];                                                /* bytes 326 to 341 */
  uint8_t average_spread_sign;                                                      /* byte 342 */
  uint8_t average_spread[16];                                                       /* bytes 343 to 358 */
  uint8_t index_number_of_securities[8];                                            /* bytes 359 to 366 */
  uint8_t issued_amount[20];                                                        /* bytes 367 to 386 */
  uint8_t issued_amount_weight[16];                                                 /* bytes 387 to 402 */
  uint8_t index_market_capitalization[20];                                          /* bytes 403 to 422 */
  uint8_t market_capitalization_weight[16];                                         /* bytes 423 to 438 */
  uint8_t accumulated_cash[26];                                                     /* bytes 439 to 464 */
  uint8_t cash_inflow[26];                                                          /* bytes 465 to 490 */
  uint8_t reinvest_call_cash[26];                                                   /* bytes 491 to 516 */
  uint8_t end_keyword;                                                              /* byte 517 */
} BondIndexKrxMessage;

/* any Bond Index Krx Message at all: every byte one the checker chooses */
static void any_bond_index_krx_message(BondIndexKrxMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->calculating_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->clean_price_index_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->total_earnings_index[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->market_price_index_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->zero_re_investment_index_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->call_re_investment_index_krx[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->clean_price_index_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->total_earnings_index_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->market_price_index_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->zero_re_investment_index_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->call_re_investment_index_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->weight_of_clean_index_value_for_integrity_index_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->weight_of_sum_index_value_for_integrity_index_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->weight_of_zero_re_investment_index_value_for_integrity_index_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->weight_of_call_re_investment_index_value_for_integrity_index_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->average_duration[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->average_convexity[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->average_yld[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->average_coupon_price[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->average_remaining_maturity_price[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->average_current_yield[i] = arbitrary(); }
  record->average_spread_sign = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->average_spread[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_number_of_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->issued_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->issued_amount_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->index_market_capitalization[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->market_capitalization_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 26; i++) { record->accumulated_cash[i] = arbitrary(); }
  for (size_t i = 0; i < 26; i++) { record->cash_inflow[i] = arbitrary(); }
  for (size_t i = 0; i < 26; i++) { record->reinvest_call_cash[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Bond Index Krx Message to the wire: 518 bytes from at, returning where the next byte goes */
static size_t encode_bond_index_krx_message(const BondIndexKrxMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->calculating_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->clean_price_index_krx[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->total_earnings_index[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->market_price_index_krx[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->zero_re_investment_index_krx[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->call_re_investment_index_krx[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->clean_price_index_weight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->total_earnings_index_weight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->market_price_index_weight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->zero_re_investment_index_weight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->call_re_investment_index_weight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->weight_of_clean_index_value_for_integrity_index_weight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->weight_of_sum_index_value_for_integrity_index_weight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->weight_of_zero_re_investment_index_value_for_integrity_index_weight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->weight_of_call_re_investment_index_value_for_integrity_index_weight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->average_duration[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->average_convexity[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->average_yld[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->average_coupon_price[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->average_remaining_maturity_price[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->average_current_yield[i]; }
  wire[at++] = record->average_spread_sign;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->average_spread[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_number_of_securities[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->issued_amount[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->issued_amount_weight[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->index_market_capitalization[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->market_capitalization_weight[i]; }
  for (size_t i = 0; i < 26; i++) { wire[at++] = record->accumulated_cash[i]; }
  for (size_t i = 0; i < 26; i++) { wire[at++] = record->cash_inflow[i]; }
  for (size_t i = 0; i < 26; i++) { wire[at++] = record->reinvest_call_cash[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Bond Index Krx Message off the wire: 518 bytes from at, returning where the next byte lies */
static size_t decode_bond_index_krx_message(BondIndexKrxMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->calculating_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->clean_price_index_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->total_earnings_index[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->market_price_index_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->zero_re_investment_index_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->call_re_investment_index_krx[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->clean_price_index_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->total_earnings_index_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->market_price_index_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->zero_re_investment_index_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->call_re_investment_index_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->weight_of_clean_index_value_for_integrity_index_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->weight_of_sum_index_value_for_integrity_index_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->weight_of_zero_re_investment_index_value_for_integrity_index_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->weight_of_call_re_investment_index_value_for_integrity_index_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->average_duration[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->average_convexity[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->average_yld[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->average_coupon_price[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->average_remaining_maturity_price[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->average_current_yield[i] = wire[at++]; }
  record->average_spread_sign = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->average_spread[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_number_of_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->issued_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->issued_amount_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->index_market_capitalization[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->market_capitalization_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 26; i++) { record->accumulated_cash[i] = wire[at++]; }
  for (size_t i = 0; i < 26; i++) { record->cash_inflow[i] = wire[at++]; }
  for (size_t i = 0; i < 26; i++) { record->reinvest_call_cash[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Bond Index Krx Message is what was written, byte for byte */
static void equal_bond_index_krx_message(const BondIndexKrxMessage *read, const BondIndexKrxMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->calculating_date[i] == written->calculating_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->clean_price_index_krx[i] == written->clean_price_index_krx[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->total_earnings_index[i] == written->total_earnings_index[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->market_price_index_krx[i] == written->market_price_index_krx[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->zero_re_investment_index_krx[i] == written->zero_re_investment_index_krx[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->call_re_investment_index_krx[i] == written->call_re_investment_index_krx[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->clean_price_index_weight[i] == written->clean_price_index_weight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->total_earnings_index_weight[i] == written->total_earnings_index_weight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->market_price_index_weight[i] == written->market_price_index_weight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->zero_re_investment_index_weight[i] == written->zero_re_investment_index_weight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->call_re_investment_index_weight[i] == written->call_re_investment_index_weight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->weight_of_clean_index_value_for_integrity_index_weight[i] == written->weight_of_clean_index_value_for_integrity_index_weight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->weight_of_sum_index_value_for_integrity_index_weight[i] == written->weight_of_sum_index_value_for_integrity_index_weight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->weight_of_zero_re_investment_index_value_for_integrity_index_weight[i] == written->weight_of_zero_re_investment_index_value_for_integrity_index_weight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->weight_of_call_re_investment_index_value_for_integrity_index_weight[i] == written->weight_of_call_re_investment_index_value_for_integrity_index_weight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->average_duration[i] == written->average_duration[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->average_convexity[i] == written->average_convexity[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->average_yld[i] == written->average_yld[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->average_coupon_price[i] == written->average_coupon_price[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->average_remaining_maturity_price[i] == written->average_remaining_maturity_price[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->average_current_yield[i] == written->average_current_yield[i]); }
  assert(read->average_spread_sign == written->average_spread_sign);
  for (size_t i = 0; i < 16; i++) { assert(read->average_spread[i] == written->average_spread[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_number_of_securities[i] == written->index_number_of_securities[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->issued_amount[i] == written->issued_amount[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->issued_amount_weight[i] == written->issued_amount_weight[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->index_market_capitalization[i] == written->index_market_capitalization[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->market_capitalization_weight[i] == written->market_capitalization_weight[i]); }
  for (size_t i = 0; i < 26; i++) { assert(read->accumulated_cash[i] == written->accumulated_cash[i]); }
  for (size_t i = 0; i < 26; i++) { assert(read->cash_inflow[i] == written->cash_inflow[i]); }
  for (size_t i = 0; i < 26; i++) { assert(read->reinvest_call_cash[i] == written->reinvest_call_cash[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Bond Index Krx Message: written and read back, then read and written back */
static void check_bond_index_krx_message(void) {
  BondIndexKrxMessage sent;
  BondIndexKrxMessage got;
  uint8_t wire[518];
  uint8_t again[518];

  any_bond_index_krx_message(&sent);
  assert(encode_bond_index_krx_message(&sent, wire, 0) == 518);
  assert(decode_bond_index_krx_message(&got, wire, 0) == 518);
  equal_bond_index_krx_message(&got, &sent);

  for (size_t i = 0; i < 518; i++) { wire[i] = arbitrary(); }
  assert(decode_bond_index_krx_message(&got, wire, 0) == 518);
  assert(encode_bond_index_krx_message(&got, again, 0) == 518);
  for (size_t i = 0; i < 518; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spot Gold Quote Message: 790 bytes -------------------------------------- */

/* Spot Gold Quote. Multi-level bid/ask quotes for Spot Gold. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t session_id[2];                          /* bytes 10 to 11 */
  uint8_t isin_code[12];                          /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue[6];    /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 30 to 41 */
  uint8_t ask_level_1_price[11];                  /* bytes 42 to 52 */
  uint8_t bid_level_1_price[11];                  /* bytes 53 to 63 */
  uint8_t ask_level_1_volume[12];                 /* bytes 64 to 75 */
  uint8_t bid_level_1_volume[12];                 /* bytes 76 to 87 */
  uint8_t lp_ask_level_1_volume[12];              /* bytes 88 to 99 */
  uint8_t lp_bid_level_1_volume[12];              /* bytes 100 to 111 */
  uint8_t ask_level_2_price[11];                  /* bytes 112 to 122 */
  uint8_t bid_level_2_price[11];                  /* bytes 123 to 133 */
  uint8_t ask_level_2_volume[12];                 /* bytes 134 to 145 */
  uint8_t bid_level_2_volume[12];                 /* bytes 146 to 157 */
  uint8_t lp_ask_level_2_volume[12];              /* bytes 158 to 169 */
  uint8_t lp_bid_level_2_volume[12];              /* bytes 170 to 181 */
  uint8_t ask_level_3_price[11];                  /* bytes 182 to 192 */
  uint8_t bid_level_3_price[11];                  /* bytes 193 to 203 */
  uint8_t ask_level_3_volume[12];                 /* bytes 204 to 215 */
  uint8_t bid_level_3_volume[12];                 /* bytes 216 to 227 */
  uint8_t lp_ask_level_3_volume[12];              /* bytes 228 to 239 */
  uint8_t lp_bid_level_3_volume[12];              /* bytes 240 to 251 */
  uint8_t ask_level_4_price[11];                  /* bytes 252 to 262 */
  uint8_t bid_level_4_price[11];                  /* bytes 263 to 273 */
  uint8_t ask_level_4_volume[12];                 /* bytes 274 to 285 */
  uint8_t bid_level_4_volume[12];                 /* bytes 286 to 297 */
  uint8_t lp_ask_level_4_volume[12];              /* bytes 298 to 309 */
  uint8_t lp_bid_level_4_volume[12];              /* bytes 310 to 321 */
  uint8_t ask_level_5_price[11];                  /* bytes 322 to 332 */
  uint8_t bid_level_5_price[11];                  /* bytes 333 to 343 */
  uint8_t ask_level_5_volume[12];                 /* bytes 344 to 355 */
  uint8_t bid_level_5_volume[12];                 /* bytes 356 to 367 */
  uint8_t lp_ask_level_5_volume[12];              /* bytes 368 to 379 */
  uint8_t lp_bid_level_5_volume[12];              /* bytes 380 to 391 */
  uint8_t ask_level_6_price[11];                  /* bytes 392 to 402 */
  uint8_t bid_level_6_price[11];                  /* bytes 403 to 413 */
  uint8_t ask_level_6_volume[12];                 /* bytes 414 to 425 */
  uint8_t bid_level_6_volume[12];                 /* bytes 426 to 437 */
  uint8_t lp_ask_level_6_volume[12];              /* bytes 438 to 449 */
  uint8_t lp_bid_level_6_volume[12];              /* bytes 450 to 461 */
  uint8_t ask_level_7_price[11];                  /* bytes 462 to 472 */
  uint8_t bid_level_7_price[11];                  /* bytes 473 to 483 */
  uint8_t ask_level_7_volume[12];                 /* bytes 484 to 495 */
  uint8_t bid_level_7_volume[12];                 /* bytes 496 to 507 */
  uint8_t lp_ask_level_7_volume[12];              /* bytes 508 to 519 */
  uint8_t lp_bid_level_7_volume[12];              /* bytes 520 to 531 */
  uint8_t ask_level_8_price[11];                  /* bytes 532 to 542 */
  uint8_t bid_level_8_price[11];                  /* bytes 543 to 553 */
  uint8_t ask_level_8_volume[12];                 /* bytes 554 to 565 */
  uint8_t bid_level_8_volume[12];                 /* bytes 566 to 577 */
  uint8_t lp_ask_level_8_volume[12];              /* bytes 578 to 589 */
  uint8_t lp_bid_level_8_volume[12];              /* bytes 590 to 601 */
  uint8_t ask_level_9_price[11];                  /* bytes 602 to 612 */
  uint8_t bid_level_9_price[11];                  /* bytes 613 to 623 */
  uint8_t ask_level_9_volume[12];                 /* bytes 624 to 635 */
  uint8_t bid_level_9_volume[12];                 /* bytes 636 to 647 */
  uint8_t lp_ask_level_9_volume[12];              /* bytes 648 to 659 */
  uint8_t lp_bid_level_9_volume[12];              /* bytes 660 to 671 */
  uint8_t ask_level_10_price[11];                 /* bytes 672 to 682 */
  uint8_t bid_level_10_price[11];                 /* bytes 683 to 693 */
  uint8_t ask_level_10_volume[12];                /* bytes 694 to 705 */
  uint8_t bid_level_10_volume[12];                /* bytes 706 to 717 */
  uint8_t lp_ask_level_10_volume[12];             /* bytes 718 to 729 */
  uint8_t lp_bid_level_10_volume[12];             /* bytes 730 to 741 */
  uint8_t total_ask_volume[12];                   /* bytes 742 to 753 */
  uint8_t total_bid_volume[12];                   /* bytes 754 to 765 */
  uint8_t estimated_trading_price[11];            /* bytes 766 to 776 */
  uint8_t estimated_trading_volume[12];           /* bytes 777 to 788 */
  uint8_t end_keyword;                            /* byte 789 */
} SpotGoldQuoteMessage;

/* any Spot Gold Quote Message at all: every byte one the checker chooses */
static void any_spot_gold_quote_message(SpotGoldQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
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
  record->end_keyword = arbitrary();
}

/* Spot Gold Quote Message to the wire: 790 bytes from at, returning where the next byte goes */
static size_t encode_spot_gold_quote_message(const SpotGoldQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
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
  wire[at++] = record->end_keyword;

  return at;
}

/* Spot Gold Quote Message off the wire: 790 bytes from at, returning where the next byte lies */
static size_t decode_spot_gold_quote_message(SpotGoldQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
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
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Spot Gold Quote Message is what was written, byte for byte */
static void equal_spot_gold_quote_message(const SpotGoldQuoteMessage *read, const SpotGoldQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
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
  assert(read->end_keyword == written->end_keyword);
}

/* Spot Gold Quote Message: written and read back, then read and written back */
static void check_spot_gold_quote_message(void) {
  SpotGoldQuoteMessage sent;
  SpotGoldQuoteMessage got;
  uint8_t wire[790];
  uint8_t again[790];

  any_spot_gold_quote_message(&sent);
  assert(encode_spot_gold_quote_message(&sent, wire, 0) == 790);
  assert(decode_spot_gold_quote_message(&got, wire, 0) == 790);
  equal_spot_gold_quote_message(&got, &sent);

  for (size_t i = 0; i < 790; i++) { wire[i] = arbitrary(); }
  assert(decode_spot_gold_quote_message(&got, wire, 0) == 790);
  assert(encode_spot_gold_quote_message(&got, again, 0) == 790);
  for (size_t i = 0; i < 790; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spot Gold Order Filled Message: 158 bytes ------------------------------- */

/* Spot Gold Order Filled. Real-time trade prints with running totals. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t session_id[2];                          /* bytes 10 to 11 */
  uint8_t isin_code[12];                          /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue[6];    /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 30 to 41 */
  uint8_t trading_price[11];                      /* bytes 42 to 52 */
  uint8_t trading_volume[10];                     /* bytes 53 to 62 */
  uint8_t opening_price_long[11];                 /* bytes 63 to 73 */
  uint8_t todays_high[11];                        /* bytes 74 to 84 */
  uint8_t todays_low[11];                         /* bytes 85 to 95 */
  uint8_t previous_price[11];                     /* bytes 96 to 106 */
  uint8_t accumulated_trading_volume[12];         /* bytes 107 to 118 */
  uint8_t accumulated_trading_value_long[22];     /* bytes 119 to 140 */
  uint8_t final_ask_bid_type_code;                /* byte 141 */
  uint8_t lp_holding_quantity[15];                /* bytes 142 to 156 */
  uint8_t end_keyword;                            /* byte 157 */
} SpotGoldOrderFilledMessage;

/* any Spot Gold Order Filled Message at all: every byte one the checker chooses */
static void any_spot_gold_order_filled_message(SpotGoldOrderFilledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->opening_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->previous_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = arbitrary(); }
  record->final_ask_bid_type_code = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->lp_holding_quantity[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Spot Gold Order Filled Message to the wire: 158 bytes from at, returning where the next byte goes */
static size_t encode_spot_gold_order_filled_message(const SpotGoldOrderFilledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->opening_price_long[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->previous_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value_long[i]; }
  wire[at++] = record->final_ask_bid_type_code;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->lp_holding_quantity[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Spot Gold Order Filled Message off the wire: 158 bytes from at, returning where the next byte lies */
static size_t decode_spot_gold_order_filled_message(SpotGoldOrderFilledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->opening_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->previous_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = wire[at++]; }
  record->final_ask_bid_type_code = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->lp_holding_quantity[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Spot Gold Order Filled Message is what was written, byte for byte */
static void equal_spot_gold_order_filled_message(const SpotGoldOrderFilledMessage *read, const SpotGoldOrderFilledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->opening_price_long[i] == written->opening_price_long[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->previous_price[i] == written->previous_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value_long[i] == written->accumulated_trading_value_long[i]); }
  assert(read->final_ask_bid_type_code == written->final_ask_bid_type_code);
  for (size_t i = 0; i < 15; i++) { assert(read->lp_holding_quantity[i] == written->lp_holding_quantity[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Spot Gold Order Filled Message: written and read back, then read and written back */
static void check_spot_gold_order_filled_message(void) {
  SpotGoldOrderFilledMessage sent;
  SpotGoldOrderFilledMessage got;
  uint8_t wire[158];
  uint8_t again[158];

  any_spot_gold_order_filled_message(&sent);
  assert(encode_spot_gold_order_filled_message(&sent, wire, 0) == 158);
  assert(decode_spot_gold_order_filled_message(&got, wire, 0) == 158);
  equal_spot_gold_order_filled_message(&got, &sent);

  for (size_t i = 0; i < 158; i++) { wire[i] = arbitrary(); }
  assert(decode_spot_gold_order_filled_message(&got, wire, 0) == 158);
  assert(encode_spot_gold_order_filled_message(&got, again, 0) == 158);
  for (size_t i = 0; i < 158; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spot Gold Order Filled Plus Quote Message: 882 bytes -------------------- */

/* Spot Gold Order Filled plus Quote. Trade print followed by full quote state. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t session_id[2];                          /* bytes 10 to 11 */
  uint8_t isin_code[12];                          /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue[6];    /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 30 to 41 */
  uint8_t trading_price[11];                      /* bytes 42 to 52 */
  uint8_t trading_volume[10];                     /* bytes 53 to 62 */
  uint8_t opening_price_long[11];                 /* bytes 63 to 73 */
  uint8_t todays_high[11];                        /* bytes 74 to 84 */
  uint8_t todays_low[11];                         /* bytes 85 to 95 */
  uint8_t previous_price[11];                     /* bytes 96 to 106 */
  uint8_t accumulated_trading_volume[12];         /* bytes 107 to 118 */
  uint8_t accumulated_trading_value_long[22];     /* bytes 119 to 140 */
  uint8_t final_ask_bid_type_code;                /* byte 141 */
  uint8_t lp_holding_quantity[15];                /* bytes 142 to 156 */
  uint8_t ask_level_1_price[11];                  /* bytes 157 to 167 */
  uint8_t bid_level_1_price[11];                  /* bytes 168 to 178 */
  uint8_t ask_level_1_volume[12];                 /* bytes 179 to 190 */
  uint8_t bid_level_1_volume[12];                 /* bytes 191 to 202 */
  uint8_t lp_ask_level_1_volume[12];              /* bytes 203 to 214 */
  uint8_t lp_bid_level_1_volume[12];              /* bytes 215 to 226 */
  uint8_t ask_level_2_price[11];                  /* bytes 227 to 237 */
  uint8_t bid_level_2_price[11];                  /* bytes 238 to 248 */
  uint8_t ask_level_2_volume[12];                 /* bytes 249 to 260 */
  uint8_t bid_level_2_volume[12];                 /* bytes 261 to 272 */
  uint8_t lp_ask_level_2_volume[12];              /* bytes 273 to 284 */
  uint8_t lp_bid_level_2_volume[12];              /* bytes 285 to 296 */
  uint8_t ask_level_3_price[11];                  /* bytes 297 to 307 */
  uint8_t bid_level_3_price[11];                  /* bytes 308 to 318 */
  uint8_t ask_level_3_volume[12];                 /* bytes 319 to 330 */
  uint8_t bid_level_3_volume[12];                 /* bytes 331 to 342 */
  uint8_t lp_ask_level_3_volume[12];              /* bytes 343 to 354 */
  uint8_t lp_bid_level_3_volume[12];              /* bytes 355 to 366 */
  uint8_t ask_level_4_price[11];                  /* bytes 367 to 377 */
  uint8_t bid_level_4_price[11];                  /* bytes 378 to 388 */
  uint8_t ask_level_4_volume[12];                 /* bytes 389 to 400 */
  uint8_t bid_level_4_volume[12];                 /* bytes 401 to 412 */
  uint8_t lp_ask_level_4_volume[12];              /* bytes 413 to 424 */
  uint8_t lp_bid_level_4_volume[12];              /* bytes 425 to 436 */
  uint8_t ask_level_5_price[11];                  /* bytes 437 to 447 */
  uint8_t bid_level_5_price[11];                  /* bytes 448 to 458 */
  uint8_t ask_level_5_volume[12];                 /* bytes 459 to 470 */
  uint8_t bid_level_5_volume[12];                 /* bytes 471 to 482 */
  uint8_t lp_ask_level_5_volume[12];              /* bytes 483 to 494 */
  uint8_t lp_bid_level_5_volume[12];              /* bytes 495 to 506 */
  uint8_t ask_level_6_price[11];                  /* bytes 507 to 517 */
  uint8_t bid_level_6_price[11];                  /* bytes 518 to 528 */
  uint8_t ask_level_6_volume[12];                 /* bytes 529 to 540 */
  uint8_t bid_level_6_volume[12];                 /* bytes 541 to 552 */
  uint8_t lp_ask_level_6_volume[12];              /* bytes 553 to 564 */
  uint8_t lp_bid_level_6_volume[12];              /* bytes 565 to 576 */
  uint8_t ask_level_7_price[11];                  /* bytes 577 to 587 */
  uint8_t bid_level_7_price[11];                  /* bytes 588 to 598 */
  uint8_t ask_level_7_volume[12];                 /* bytes 599 to 610 */
  uint8_t bid_level_7_volume[12];                 /* bytes 611 to 622 */
  uint8_t lp_ask_level_7_volume[12];              /* bytes 623 to 634 */
  uint8_t lp_bid_level_7_volume[12];              /* bytes 635 to 646 */
  uint8_t ask_level_8_price[11];                  /* bytes 647 to 657 */
  uint8_t bid_level_8_price[11];                  /* bytes 658 to 668 */
  uint8_t ask_level_8_volume[12];                 /* bytes 669 to 680 */
  uint8_t bid_level_8_volume[12];                 /* bytes 681 to 692 */
  uint8_t lp_ask_level_8_volume[12];              /* bytes 693 to 704 */
  uint8_t lp_bid_level_8_volume[12];              /* bytes 705 to 716 */
  uint8_t ask_level_9_price[11];                  /* bytes 717 to 727 */
  uint8_t bid_level_9_price[11];                  /* bytes 728 to 738 */
  uint8_t ask_level_9_volume[12];                 /* bytes 739 to 750 */
  uint8_t bid_level_9_volume[12];                 /* bytes 751 to 762 */
  uint8_t lp_ask_level_9_volume[12];              /* bytes 763 to 774 */
  uint8_t lp_bid_level_9_volume[12];              /* bytes 775 to 786 */
  uint8_t ask_level_10_price[11];                 /* bytes 787 to 797 */
  uint8_t bid_level_10_price[11];                 /* bytes 798 to 808 */
  uint8_t ask_level_10_volume[12];                /* bytes 809 to 820 */
  uint8_t bid_level_10_volume[12];                /* bytes 821 to 832 */
  uint8_t lp_ask_level_10_volume[12];             /* bytes 833 to 844 */
  uint8_t lp_bid_level_10_volume[12];             /* bytes 845 to 856 */
  uint8_t total_ask_volume[12];                   /* bytes 857 to 868 */
  uint8_t total_bid_volume[12];                   /* bytes 869 to 880 */
  uint8_t end_keyword;                            /* byte 881 */
} SpotGoldOrderFilledPlusQuoteMessage;

/* any Spot Gold Order Filled Plus Quote Message at all: every byte one the checker chooses */
static void any_spot_gold_order_filled_plus_quote_message(SpotGoldOrderFilledPlusQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->opening_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->previous_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = arbitrary(); }
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
  record->end_keyword = arbitrary();
}

/* Spot Gold Order Filled Plus Quote Message to the wire: 882 bytes from at, returning where the next byte goes */
static size_t encode_spot_gold_order_filled_plus_quote_message(const SpotGoldOrderFilledPlusQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->opening_price_long[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->previous_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value_long[i]; }
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
  wire[at++] = record->end_keyword;

  return at;
}

/* Spot Gold Order Filled Plus Quote Message off the wire: 882 bytes from at, returning where the next byte lies */
static size_t decode_spot_gold_order_filled_plus_quote_message(SpotGoldOrderFilledPlusQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->opening_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->previous_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = wire[at++]; }
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
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Spot Gold Order Filled Plus Quote Message is what was written, byte for byte */
static void equal_spot_gold_order_filled_plus_quote_message(const SpotGoldOrderFilledPlusQuoteMessage *read, const SpotGoldOrderFilledPlusQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->opening_price_long[i] == written->opening_price_long[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->previous_price[i] == written->previous_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value_long[i] == written->accumulated_trading_value_long[i]); }
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
  assert(read->end_keyword == written->end_keyword);
}

/* Spot Gold Order Filled Plus Quote Message: written and read back, then read and written back */
static void check_spot_gold_order_filled_plus_quote_message(void) {
  SpotGoldOrderFilledPlusQuoteMessage sent;
  SpotGoldOrderFilledPlusQuoteMessage got;
  uint8_t wire[882];
  uint8_t again[882];

  any_spot_gold_order_filled_plus_quote_message(&sent);
  assert(encode_spot_gold_order_filled_plus_quote_message(&sent, wire, 0) == 882);
  assert(decode_spot_gold_order_filled_plus_quote_message(&got, wire, 0) == 882);
  equal_spot_gold_order_filled_plus_quote_message(&got, &sent);

  for (size_t i = 0; i < 882; i++) { wire[i] = arbitrary(); }
  assert(decode_spot_gold_order_filled_plus_quote_message(&got, wire, 0) == 882);
  assert(encode_spot_gold_order_filled_plus_quote_message(&got, again, 0) == 882);
  for (size_t i = 0; i < 882; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spot Gold Market Operation Ts Plus Quote Message: 810 bytes ------------- */

/* Spot Gold Market Operation TS plus Quote. Session-state event followed by full quote state. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t session_id[2];                          /* bytes 10 to 11 */
  uint8_t isin_code[12];                          /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue[6];    /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 30 to 41 */
  uint8_t board_event_id[3];                      /* bytes 42 to 44 */
  uint8_t start_time_of_a_board_event[9];         /* bytes 45 to 53 */
  uint8_t board_event_group_code[5];              /* bytes 54 to 58 */
  uint8_t trading_halt_reason_code[3];            /* bytes 59 to 61 */
  uint8_t ask_level_1_price[11];                  /* bytes 62 to 72 */
  uint8_t bid_level_1_price[11];                  /* bytes 73 to 83 */
  uint8_t ask_level_1_volume[12];                 /* bytes 84 to 95 */
  uint8_t bid_level_1_volume[12];                 /* bytes 96 to 107 */
  uint8_t lp_ask_level_1_volume[12];              /* bytes 108 to 119 */
  uint8_t lp_bid_level_1_volume[12];              /* bytes 120 to 131 */
  uint8_t ask_level_2_price[11];                  /* bytes 132 to 142 */
  uint8_t bid_level_2_price[11];                  /* bytes 143 to 153 */
  uint8_t ask_level_2_volume[12];                 /* bytes 154 to 165 */
  uint8_t bid_level_2_volume[12];                 /* bytes 166 to 177 */
  uint8_t lp_ask_level_2_volume[12];              /* bytes 178 to 189 */
  uint8_t lp_bid_level_2_volume[12];              /* bytes 190 to 201 */
  uint8_t ask_level_3_price[11];                  /* bytes 202 to 212 */
  uint8_t bid_level_3_price[11];                  /* bytes 213 to 223 */
  uint8_t ask_level_3_volume[12];                 /* bytes 224 to 235 */
  uint8_t bid_level_3_volume[12];                 /* bytes 236 to 247 */
  uint8_t lp_ask_level_3_volume[12];              /* bytes 248 to 259 */
  uint8_t lp_bid_level_3_volume[12];              /* bytes 260 to 271 */
  uint8_t ask_level_4_price[11];                  /* bytes 272 to 282 */
  uint8_t bid_level_4_price[11];                  /* bytes 283 to 293 */
  uint8_t ask_level_4_volume[12];                 /* bytes 294 to 305 */
  uint8_t bid_level_4_volume[12];                 /* bytes 306 to 317 */
  uint8_t lp_ask_level_4_volume[12];              /* bytes 318 to 329 */
  uint8_t lp_bid_level_4_volume[12];              /* bytes 330 to 341 */
  uint8_t ask_level_5_price[11];                  /* bytes 342 to 352 */
  uint8_t bid_level_5_price[11];                  /* bytes 353 to 363 */
  uint8_t ask_level_5_volume[12];                 /* bytes 364 to 375 */
  uint8_t bid_level_5_volume[12];                 /* bytes 376 to 387 */
  uint8_t lp_ask_level_5_volume[12];              /* bytes 388 to 399 */
  uint8_t lp_bid_level_5_volume[12];              /* bytes 400 to 411 */
  uint8_t ask_level_6_price[11];                  /* bytes 412 to 422 */
  uint8_t bid_level_6_price[11];                  /* bytes 423 to 433 */
  uint8_t ask_level_6_volume[12];                 /* bytes 434 to 445 */
  uint8_t bid_level_6_volume[12];                 /* bytes 446 to 457 */
  uint8_t lp_ask_level_6_volume[12];              /* bytes 458 to 469 */
  uint8_t lp_bid_level_6_volume[12];              /* bytes 470 to 481 */
  uint8_t ask_level_7_price[11];                  /* bytes 482 to 492 */
  uint8_t bid_level_7_price[11];                  /* bytes 493 to 503 */
  uint8_t ask_level_7_volume[12];                 /* bytes 504 to 515 */
  uint8_t bid_level_7_volume[12];                 /* bytes 516 to 527 */
  uint8_t lp_ask_level_7_volume[12];              /* bytes 528 to 539 */
  uint8_t lp_bid_level_7_volume[12];              /* bytes 540 to 551 */
  uint8_t ask_level_8_price[11];                  /* bytes 552 to 562 */
  uint8_t bid_level_8_price[11];                  /* bytes 563 to 573 */
  uint8_t ask_level_8_volume[12];                 /* bytes 574 to 585 */
  uint8_t bid_level_8_volume[12];                 /* bytes 586 to 597 */
  uint8_t lp_ask_level_8_volume[12];              /* bytes 598 to 609 */
  uint8_t lp_bid_level_8_volume[12];              /* bytes 610 to 621 */
  uint8_t ask_level_9_price[11];                  /* bytes 622 to 632 */
  uint8_t bid_level_9_price[11];                  /* bytes 633 to 643 */
  uint8_t ask_level_9_volume[12];                 /* bytes 644 to 655 */
  uint8_t bid_level_9_volume[12];                 /* bytes 656 to 667 */
  uint8_t lp_ask_level_9_volume[12];              /* bytes 668 to 679 */
  uint8_t lp_bid_level_9_volume[12];              /* bytes 680 to 691 */
  uint8_t ask_level_10_price[11];                 /* bytes 692 to 702 */
  uint8_t bid_level_10_price[11];                 /* bytes 703 to 713 */
  uint8_t ask_level_10_volume[12];                /* bytes 714 to 725 */
  uint8_t bid_level_10_volume[12];                /* bytes 726 to 737 */
  uint8_t lp_ask_level_10_volume[12];             /* bytes 738 to 749 */
  uint8_t lp_bid_level_10_volume[12];             /* bytes 750 to 761 */
  uint8_t total_ask_volume[12];                   /* bytes 762 to 773 */
  uint8_t total_bid_volume[12];                   /* bytes 774 to 785 */
  uint8_t estimated_trading_price[11];            /* bytes 786 to 796 */
  uint8_t estimated_trading_volume[12];           /* bytes 797 to 808 */
  uint8_t end_keyword;                            /* byte 809 */
} SpotGoldMarketOperationTsPlusQuoteMessage;

/* any Spot Gold Market Operation Ts Plus Quote Message at all: every byte one the checker chooses */
static void any_spot_gold_market_operation_ts_plus_quote_message(SpotGoldMarketOperationTsPlusQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
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
  record->end_keyword = arbitrary();
}

/* Spot Gold Market Operation Ts Plus Quote Message to the wire: 810 bytes from at, returning where the next byte goes */
static size_t encode_spot_gold_market_operation_ts_plus_quote_message(const SpotGoldMarketOperationTsPlusQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
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
  wire[at++] = record->end_keyword;

  return at;
}

/* Spot Gold Market Operation Ts Plus Quote Message off the wire: 810 bytes from at, returning where the next byte lies */
static size_t decode_spot_gold_market_operation_ts_plus_quote_message(SpotGoldMarketOperationTsPlusQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
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
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Spot Gold Market Operation Ts Plus Quote Message is what was written, byte for byte */
static void equal_spot_gold_market_operation_ts_plus_quote_message(const SpotGoldMarketOperationTsPlusQuoteMessage *read, const SpotGoldMarketOperationTsPlusQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
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
  assert(read->end_keyword == written->end_keyword);
}

/* Spot Gold Market Operation Ts Plus Quote Message: written and read back, then read and written back */
static void check_spot_gold_market_operation_ts_plus_quote_message(void) {
  SpotGoldMarketOperationTsPlusQuoteMessage sent;
  SpotGoldMarketOperationTsPlusQuoteMessage got;
  uint8_t wire[810];
  uint8_t again[810];

  any_spot_gold_market_operation_ts_plus_quote_message(&sent);
  assert(encode_spot_gold_market_operation_ts_plus_quote_message(&sent, wire, 0) == 810);
  assert(decode_spot_gold_market_operation_ts_plus_quote_message(&got, wire, 0) == 810);
  equal_spot_gold_market_operation_ts_plus_quote_message(&got, &sent);

  for (size_t i = 0; i < 810; i++) { wire[i] = arbitrary(); }
  assert(decode_spot_gold_market_operation_ts_plus_quote_message(&got, wire, 0) == 810);
  assert(encode_spot_gold_market_operation_ts_plus_quote_message(&got, again, 0) == 810);
  for (size_t i = 0; i < 810; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spot Gold Snapshot Message: 849 bytes ----------------------------------- */

/* Spot Gold Market Data Snapshot. Periodic full state snapshot. */
typedef struct {
  uint8_t board_id[2];                          /* bytes 0 to 1 */
  uint8_t session_id[2];                        /* bytes 2 to 3 */
  uint8_t isin_code[12];                        /* bytes 4 to 15 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 16 to 21 */
  uint8_t current_price[11];                    /* bytes 22 to 32 */
  uint8_t opening_price_long[11];               /* bytes 33 to 43 */
  uint8_t todays_high[11];                      /* bytes 44 to 54 */
  uint8_t todays_low[11];                       /* bytes 55 to 65 */
  uint8_t accumulated_trading_volume[12];       /* bytes 66 to 77 */
  uint8_t accumulated_trading_value_long[22];   /* bytes 78 to 99 */
  uint8_t trading_halt;                         /* byte 100 */
  uint8_t ask_level_1_price[11];                /* bytes 101 to 111 */
  uint8_t bid_level_1_price[11];                /* bytes 112 to 122 */
  uint8_t ask_level_1_volume[12];               /* bytes 123 to 134 */
  uint8_t bid_level_1_volume[12];               /* bytes 135 to 146 */
  uint8_t lp_ask_level_1_volume[12];            /* bytes 147 to 158 */
  uint8_t lp_bid_level_1_volume[12];            /* bytes 159 to 170 */
  uint8_t ask_level_2_price[11];                /* bytes 171 to 181 */
  uint8_t bid_level_2_price[11];                /* bytes 182 to 192 */
  uint8_t ask_level_2_volume[12];               /* bytes 193 to 204 */
  uint8_t bid_level_2_volume[12];               /* bytes 205 to 216 */
  uint8_t lp_ask_level_2_volume[12];            /* bytes 217 to 228 */
  uint8_t lp_bid_level_2_volume[12];            /* bytes 229 to 240 */
  uint8_t ask_level_3_price[11];                /* bytes 241 to 251 */
  uint8_t bid_level_3_price[11];                /* bytes 252 to 262 */
  uint8_t ask_level_3_volume[12];               /* bytes 263 to 274 */
  uint8_t bid_level_3_volume[12];               /* bytes 275 to 286 */
  uint8_t lp_ask_level_3_volume[12];            /* bytes 287 to 298 */
  uint8_t lp_bid_level_3_volume[12];            /* bytes 299 to 310 */
  uint8_t ask_level_4_price[11];                /* bytes 311 to 321 */
  uint8_t bid_level_4_price[11];                /* bytes 322 to 332 */
  uint8_t ask_level_4_volume[12];               /* bytes 333 to 344 */
  uint8_t bid_level_4_volume[12];               /* bytes 345 to 356 */
  uint8_t lp_ask_level_4_volume[12];            /* bytes 357 to 368 */
  uint8_t lp_bid_level_4_volume[12];            /* bytes 369 to 380 */
  uint8_t ask_level_5_price[11];                /* bytes 381 to 391 */
  uint8_t bid_level_5_price[11];                /* bytes 392 to 402 */
  uint8_t ask_level_5_volume[12];               /* bytes 403 to 414 */
  uint8_t bid_level_5_volume[12];               /* bytes 415 to 426 */
  uint8_t lp_ask_level_5_volume[12];            /* bytes 427 to 438 */
  uint8_t lp_bid_level_5_volume[12];            /* bytes 439 to 450 */
  uint8_t ask_level_6_price[11];                /* bytes 451 to 461 */
  uint8_t bid_level_6_price[11];                /* bytes 462 to 472 */
  uint8_t ask_level_6_volume[12];               /* bytes 473 to 484 */
  uint8_t bid_level_6_volume[12];               /* bytes 485 to 496 */
  uint8_t lp_ask_level_6_volume[12];            /* bytes 497 to 508 */
  uint8_t lp_bid_level_6_volume[12];            /* bytes 509 to 520 */
  uint8_t ask_level_7_price[11];                /* bytes 521 to 531 */
  uint8_t bid_level_7_price[11];                /* bytes 532 to 542 */
  uint8_t ask_level_7_volume[12];               /* bytes 543 to 554 */
  uint8_t bid_level_7_volume[12];               /* bytes 555 to 566 */
  uint8_t lp_ask_level_7_volume[12];            /* bytes 567 to 578 */
  uint8_t lp_bid_level_7_volume[12];            /* bytes 579 to 590 */
  uint8_t ask_level_8_price[11];                /* bytes 591 to 601 */
  uint8_t bid_level_8_price[11];                /* bytes 602 to 612 */
  uint8_t ask_level_8_volume[12];               /* bytes 613 to 624 */
  uint8_t bid_level_8_volume[12];               /* bytes 625 to 636 */
  uint8_t lp_ask_level_8_volume[12];            /* bytes 637 to 648 */
  uint8_t lp_bid_level_8_volume[12];            /* bytes 649 to 660 */
  uint8_t ask_level_9_price[11];                /* bytes 661 to 671 */
  uint8_t bid_level_9_price[11];                /* bytes 672 to 682 */
  uint8_t ask_level_9_volume[12];               /* bytes 683 to 694 */
  uint8_t bid_level_9_volume[12];               /* bytes 695 to 706 */
  uint8_t lp_ask_level_9_volume[12];            /* bytes 707 to 718 */
  uint8_t lp_bid_level_9_volume[12];            /* bytes 719 to 730 */
  uint8_t ask_level_10_price[11];               /* bytes 731 to 741 */
  uint8_t bid_level_10_price[11];               /* bytes 742 to 752 */
  uint8_t ask_level_10_volume[12];              /* bytes 753 to 764 */
  uint8_t bid_level_10_volume[12];              /* bytes 765 to 776 */
  uint8_t lp_ask_level_10_volume[12];           /* bytes 777 to 788 */
  uint8_t lp_bid_level_10_volume[12];           /* bytes 789 to 800 */
  uint8_t total_ask_volume[12];                 /* bytes 801 to 812 */
  uint8_t total_bid_volume[12];                 /* bytes 813 to 824 */
  uint8_t estimated_trading_price[11];          /* bytes 825 to 835 */
  uint8_t estimated_trading_volume[12];         /* bytes 836 to 847 */
  uint8_t end_keyword;                          /* byte 848 */
} SpotGoldSnapshotMessage;

/* any Spot Gold Snapshot Message at all: every byte one the checker chooses */
static void any_spot_gold_snapshot_message(SpotGoldSnapshotMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->current_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->opening_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = arbitrary(); }
  record->trading_halt = arbitrary();
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
  record->end_keyword = arbitrary();
}

/* Spot Gold Snapshot Message to the wire: 849 bytes from at, returning where the next byte goes */
static size_t encode_spot_gold_snapshot_message(const SpotGoldSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->current_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->opening_price_long[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value_long[i]; }
  wire[at++] = record->trading_halt;
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
  wire[at++] = record->end_keyword;

  return at;
}

/* Spot Gold Snapshot Message off the wire: 849 bytes from at, returning where the next byte lies */
static size_t decode_spot_gold_snapshot_message(SpotGoldSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->current_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->opening_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = wire[at++]; }
  record->trading_halt = wire[at++];
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
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Spot Gold Snapshot Message is what was written, byte for byte */
static void equal_spot_gold_snapshot_message(const SpotGoldSnapshotMessage *read, const SpotGoldSnapshotMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->current_price[i] == written->current_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->opening_price_long[i] == written->opening_price_long[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value_long[i] == written->accumulated_trading_value_long[i]); }
  assert(read->trading_halt == written->trading_halt);
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
  assert(read->end_keyword == written->end_keyword);
}

/* Spot Gold Snapshot Message: written and read back, then read and written back */
static void check_spot_gold_snapshot_message(void) {
  SpotGoldSnapshotMessage sent;
  SpotGoldSnapshotMessage got;
  uint8_t wire[849];
  uint8_t again[849];

  any_spot_gold_snapshot_message(&sent);
  assert(encode_spot_gold_snapshot_message(&sent, wire, 0) == 849);
  assert(decode_spot_gold_snapshot_message(&got, wire, 0) == 849);
  equal_spot_gold_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 849; i++) { wire[i] = arbitrary(); }
  assert(decode_spot_gold_snapshot_message(&got, wire, 0) == 849);
  assert(encode_spot_gold_snapshot_message(&got, again, 0) == 849);
  for (size_t i = 0; i < 849; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spot Gold Negotiated Trade Message: 93 bytes ---------------------------- */

/* Spot Gold Negotiated Trade Data. */
typedef struct {
  uint8_t isin_code[12];                                    /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue[6];              /* bytes 12 to 17 */
  uint8_t negotiated_trade_accumulated_trading_volume[15];  /* bytes 18 to 32 */
  uint8_t negotiated_trade_accumulated_trading_value[22];   /* bytes 33 to 54 */
  uint8_t total_accumulated_trading_volume[15];             /* bytes 55 to 69 */
  uint8_t total_accumulated_trading_value[22];              /* bytes 70 to 91 */
  uint8_t end_keyword;                                      /* byte 92 */
} SpotGoldNegotiatedTradeMessage;

/* any Spot Gold Negotiated Trade Message at all: every byte one the checker chooses */
static void any_spot_gold_negotiated_trade_message(SpotGoldNegotiatedTradeMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->negotiated_trade_accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->negotiated_trade_accumulated_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->total_accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->total_accumulated_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Spot Gold Negotiated Trade Message to the wire: 93 bytes from at, returning where the next byte goes */
static size_t encode_spot_gold_negotiated_trade_message(const SpotGoldNegotiatedTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->negotiated_trade_accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->negotiated_trade_accumulated_trading_value[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->total_accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->total_accumulated_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Spot Gold Negotiated Trade Message off the wire: 93 bytes from at, returning where the next byte lies */
static size_t decode_spot_gold_negotiated_trade_message(SpotGoldNegotiatedTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->negotiated_trade_accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->negotiated_trade_accumulated_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->total_accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->total_accumulated_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Spot Gold Negotiated Trade Message is what was written, byte for byte */
static void equal_spot_gold_negotiated_trade_message(const SpotGoldNegotiatedTradeMessage *read, const SpotGoldNegotiatedTradeMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->negotiated_trade_accumulated_trading_volume[i] == written->negotiated_trade_accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->negotiated_trade_accumulated_trading_value[i] == written->negotiated_trade_accumulated_trading_value[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->total_accumulated_trading_volume[i] == written->total_accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->total_accumulated_trading_value[i] == written->total_accumulated_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Spot Gold Negotiated Trade Message: written and read back, then read and written back */
static void check_spot_gold_negotiated_trade_message(void) {
  SpotGoldNegotiatedTradeMessage sent;
  SpotGoldNegotiatedTradeMessage got;
  uint8_t wire[93];
  uint8_t again[93];

  any_spot_gold_negotiated_trade_message(&sent);
  assert(encode_spot_gold_negotiated_trade_message(&sent, wire, 0) == 93);
  assert(decode_spot_gold_negotiated_trade_message(&got, wire, 0) == 93);
  equal_spot_gold_negotiated_trade_message(&got, &sent);

  for (size_t i = 0; i < 93; i++) { wire[i] = arbitrary(); }
  assert(decode_spot_gold_negotiated_trade_message(&got, wire, 0) == 93);
  assert(encode_spot_gold_negotiated_trade_message(&got, again, 0) == 93);
  for (size_t i = 0; i < 93; i++) { assert(again[i] == wire[i]); }
}

/* ---- Emissions Quote Message: 320 bytes -------------------------------------- */

/* Emissions Quote. Multi-level bid/ask quotes for Emissions. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t session_id[2];                          /* bytes 10 to 11 */
  uint8_t isin_code[12];                          /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue[6];    /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 30 to 41 */
  uint8_t ask_level_1_price[11];                  /* bytes 42 to 52 */
  uint8_t bid_level_1_price[11];                  /* bytes 53 to 63 */
  uint8_t ask_level_1_volume[12];                 /* bytes 64 to 75 */
  uint8_t bid_level_1_volume[12];                 /* bytes 76 to 87 */
  uint8_t ask_level_2_price[11];                  /* bytes 88 to 98 */
  uint8_t bid_level_2_price[11];                  /* bytes 99 to 109 */
  uint8_t ask_level_2_volume[12];                 /* bytes 110 to 121 */
  uint8_t bid_level_2_volume[12];                 /* bytes 122 to 133 */
  uint8_t ask_level_3_price[11];                  /* bytes 134 to 144 */
  uint8_t bid_level_3_price[11];                  /* bytes 145 to 155 */
  uint8_t ask_level_3_volume[12];                 /* bytes 156 to 167 */
  uint8_t bid_level_3_volume[12];                 /* bytes 168 to 179 */
  uint8_t ask_level_4_price[11];                  /* bytes 180 to 190 */
  uint8_t bid_level_4_price[11];                  /* bytes 191 to 201 */
  uint8_t ask_level_4_volume[12];                 /* bytes 202 to 213 */
  uint8_t bid_level_4_volume[12];                 /* bytes 214 to 225 */
  uint8_t ask_level_5_price[11];                  /* bytes 226 to 236 */
  uint8_t bid_level_5_price[11];                  /* bytes 237 to 247 */
  uint8_t ask_level_5_volume[12];                 /* bytes 248 to 259 */
  uint8_t bid_level_5_volume[12];                 /* bytes 260 to 271 */
  uint8_t total_ask_volume[12];                   /* bytes 272 to 283 */
  uint8_t total_bid_volume[12];                   /* bytes 284 to 295 */
  uint8_t estimated_trading_price[11];            /* bytes 296 to 306 */
  uint8_t estimated_trading_volume[12];           /* bytes 307 to 318 */
  uint8_t end_keyword;                            /* byte 319 */
} EmissionsQuoteMessage;

/* any Emissions Quote Message at all: every byte one the checker chooses */
static void any_emissions_quote_message(EmissionsQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Emissions Quote Message to the wire: 320 bytes from at, returning where the next byte goes */
static size_t encode_emissions_quote_message(const EmissionsQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_1_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_1_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_2_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_2_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_3_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_4_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_4_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_5_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_5_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_ask_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_bid_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->estimated_trading_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->estimated_trading_volume[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Emissions Quote Message off the wire: 320 bytes from at, returning where the next byte lies */
static size_t decode_emissions_quote_message(EmissionsQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Emissions Quote Message is what was written, byte for byte */
static void equal_emissions_quote_message(const EmissionsQuoteMessage *read, const EmissionsQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_1_volume[i] == written->ask_level_1_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_1_volume[i] == written->bid_level_1_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_2_volume[i] == written->ask_level_2_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_2_volume[i] == written->bid_level_2_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_3_volume[i] == written->ask_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_3_volume[i] == written->bid_level_3_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_4_volume[i] == written->ask_level_4_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_4_volume[i] == written->bid_level_4_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_5_volume[i] == written->ask_level_5_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_5_volume[i] == written->bid_level_5_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_ask_volume[i] == written->total_ask_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_bid_volume[i] == written->total_bid_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->estimated_trading_price[i] == written->estimated_trading_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->estimated_trading_volume[i] == written->estimated_trading_volume[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Emissions Quote Message: written and read back, then read and written back */
static void check_emissions_quote_message(void) {
  EmissionsQuoteMessage sent;
  EmissionsQuoteMessage got;
  uint8_t wire[320];
  uint8_t again[320];

  any_emissions_quote_message(&sent);
  assert(encode_emissions_quote_message(&sent, wire, 0) == 320);
  assert(decode_emissions_quote_message(&got, wire, 0) == 320);
  equal_emissions_quote_message(&got, &sent);

  for (size_t i = 0; i < 320; i++) { wire[i] = arbitrary(); }
  assert(decode_emissions_quote_message(&got, wire, 0) == 320);
  assert(encode_emissions_quote_message(&got, again, 0) == 320);
  for (size_t i = 0; i < 320; i++) { assert(again[i] == wire[i]); }
}

/* ---- Emissions Order Filled Message: 143 bytes ------------------------------- */

/* Emissions Order Filled. Real-time trade prints with running totals. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t session_id[2];                          /* bytes 10 to 11 */
  uint8_t isin_code[12];                          /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue[6];    /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 30 to 41 */
  uint8_t trading_price[11];                      /* bytes 42 to 52 */
  uint8_t trading_volume[10];                     /* bytes 53 to 62 */
  uint8_t opening_price_long[11];                 /* bytes 63 to 73 */
  uint8_t todays_high[11];                        /* bytes 74 to 84 */
  uint8_t todays_low[11];                         /* bytes 85 to 95 */
  uint8_t previous_price[11];                     /* bytes 96 to 106 */
  uint8_t accumulated_trading_volume[12];         /* bytes 107 to 118 */
  uint8_t accumulated_trading_value_long[22];     /* bytes 119 to 140 */
  uint8_t final_ask_bid_type_code;                /* byte 141 */
  uint8_t end_keyword;                            /* byte 142 */
} EmissionsOrderFilledMessage;

/* any Emissions Order Filled Message at all: every byte one the checker chooses */
static void any_emissions_order_filled_message(EmissionsOrderFilledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->opening_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->previous_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = arbitrary(); }
  record->final_ask_bid_type_code = arbitrary();
  record->end_keyword = arbitrary();
}

/* Emissions Order Filled Message to the wire: 143 bytes from at, returning where the next byte goes */
static size_t encode_emissions_order_filled_message(const EmissionsOrderFilledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->opening_price_long[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->previous_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value_long[i]; }
  wire[at++] = record->final_ask_bid_type_code;
  wire[at++] = record->end_keyword;

  return at;
}

/* Emissions Order Filled Message off the wire: 143 bytes from at, returning where the next byte lies */
static size_t decode_emissions_order_filled_message(EmissionsOrderFilledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->opening_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->previous_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = wire[at++]; }
  record->final_ask_bid_type_code = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Emissions Order Filled Message is what was written, byte for byte */
static void equal_emissions_order_filled_message(const EmissionsOrderFilledMessage *read, const EmissionsOrderFilledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->opening_price_long[i] == written->opening_price_long[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->previous_price[i] == written->previous_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value_long[i] == written->accumulated_trading_value_long[i]); }
  assert(read->final_ask_bid_type_code == written->final_ask_bid_type_code);
  assert(read->end_keyword == written->end_keyword);
}

/* Emissions Order Filled Message: written and read back, then read and written back */
static void check_emissions_order_filled_message(void) {
  EmissionsOrderFilledMessage sent;
  EmissionsOrderFilledMessage got;
  uint8_t wire[143];
  uint8_t again[143];

  any_emissions_order_filled_message(&sent);
  assert(encode_emissions_order_filled_message(&sent, wire, 0) == 143);
  assert(decode_emissions_order_filled_message(&got, wire, 0) == 143);
  equal_emissions_order_filled_message(&got, &sent);

  for (size_t i = 0; i < 143; i++) { wire[i] = arbitrary(); }
  assert(decode_emissions_order_filled_message(&got, wire, 0) == 143);
  assert(encode_emissions_order_filled_message(&got, again, 0) == 143);
  for (size_t i = 0; i < 143; i++) { assert(again[i] == wire[i]); }
}

/* ---- Emissions Order Filled Plus Quote Message: 397 bytes -------------------- */

/* Emissions Order Filled plus Quote. Trade print followed by full quote state. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t session_id[2];                          /* bytes 10 to 11 */
  uint8_t isin_code[12];                          /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue[6];    /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 30 to 41 */
  uint8_t trading_price[11];                      /* bytes 42 to 52 */
  uint8_t trading_volume[10];                     /* bytes 53 to 62 */
  uint8_t opening_price_long[11];                 /* bytes 63 to 73 */
  uint8_t todays_high[11];                        /* bytes 74 to 84 */
  uint8_t todays_low[11];                         /* bytes 85 to 95 */
  uint8_t previous_price[11];                     /* bytes 96 to 106 */
  uint8_t accumulated_trading_volume[12];         /* bytes 107 to 118 */
  uint8_t accumulated_trading_value_long[22];     /* bytes 119 to 140 */
  uint8_t final_ask_bid_type_code;                /* byte 141 */
  uint8_t ask_level_1_price[11];                  /* bytes 142 to 152 */
  uint8_t bid_level_1_price[11];                  /* bytes 153 to 163 */
  uint8_t ask_level_1_volume[12];                 /* bytes 164 to 175 */
  uint8_t bid_level_1_volume[12];                 /* bytes 176 to 187 */
  uint8_t ask_level_2_price[11];                  /* bytes 188 to 198 */
  uint8_t bid_level_2_price[11];                  /* bytes 199 to 209 */
  uint8_t ask_level_2_volume[12];                 /* bytes 210 to 221 */
  uint8_t bid_level_2_volume[12];                 /* bytes 222 to 233 */
  uint8_t ask_level_3_price[11];                  /* bytes 234 to 244 */
  uint8_t bid_level_3_price[11];                  /* bytes 245 to 255 */
  uint8_t ask_level_3_volume[12];                 /* bytes 256 to 267 */
  uint8_t bid_level_3_volume[12];                 /* bytes 268 to 279 */
  uint8_t ask_level_4_price[11];                  /* bytes 280 to 290 */
  uint8_t bid_level_4_price[11];                  /* bytes 291 to 301 */
  uint8_t ask_level_4_volume[12];                 /* bytes 302 to 313 */
  uint8_t bid_level_4_volume[12];                 /* bytes 314 to 325 */
  uint8_t ask_level_5_price[11];                  /* bytes 326 to 336 */
  uint8_t bid_level_5_price[11];                  /* bytes 337 to 347 */
  uint8_t ask_level_5_volume[12];                 /* bytes 348 to 359 */
  uint8_t bid_level_5_volume[12];                 /* bytes 360 to 371 */
  uint8_t total_ask_volume[12];                   /* bytes 372 to 383 */
  uint8_t total_bid_volume[12];                   /* bytes 384 to 395 */
  uint8_t end_keyword;                            /* byte 396 */
} EmissionsOrderFilledPlusQuoteMessage;

/* any Emissions Order Filled Plus Quote Message at all: every byte one the checker chooses */
static void any_emissions_order_filled_plus_quote_message(EmissionsOrderFilledPlusQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->opening_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->previous_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = arbitrary(); }
  record->final_ask_bid_type_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Emissions Order Filled Plus Quote Message to the wire: 397 bytes from at, returning where the next byte goes */
static size_t encode_emissions_order_filled_plus_quote_message(const EmissionsOrderFilledPlusQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->opening_price_long[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->previous_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value_long[i]; }
  wire[at++] = record->final_ask_bid_type_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_1_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_1_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_2_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_2_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_3_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_4_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_4_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_5_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_5_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_ask_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_bid_volume[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Emissions Order Filled Plus Quote Message off the wire: 397 bytes from at, returning where the next byte lies */
static size_t decode_emissions_order_filled_plus_quote_message(EmissionsOrderFilledPlusQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->opening_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->previous_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = wire[at++]; }
  record->final_ask_bid_type_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Emissions Order Filled Plus Quote Message is what was written, byte for byte */
static void equal_emissions_order_filled_plus_quote_message(const EmissionsOrderFilledPlusQuoteMessage *read, const EmissionsOrderFilledPlusQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->opening_price_long[i] == written->opening_price_long[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->previous_price[i] == written->previous_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value_long[i] == written->accumulated_trading_value_long[i]); }
  assert(read->final_ask_bid_type_code == written->final_ask_bid_type_code);
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_1_volume[i] == written->ask_level_1_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_1_volume[i] == written->bid_level_1_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_2_volume[i] == written->ask_level_2_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_2_volume[i] == written->bid_level_2_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_3_volume[i] == written->ask_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_3_volume[i] == written->bid_level_3_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_4_volume[i] == written->ask_level_4_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_4_volume[i] == written->bid_level_4_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_5_volume[i] == written->ask_level_5_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_5_volume[i] == written->bid_level_5_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_ask_volume[i] == written->total_ask_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_bid_volume[i] == written->total_bid_volume[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Emissions Order Filled Plus Quote Message: written and read back, then read and written back */
static void check_emissions_order_filled_plus_quote_message(void) {
  EmissionsOrderFilledPlusQuoteMessage sent;
  EmissionsOrderFilledPlusQuoteMessage got;
  uint8_t wire[397];
  uint8_t again[397];

  any_emissions_order_filled_plus_quote_message(&sent);
  assert(encode_emissions_order_filled_plus_quote_message(&sent, wire, 0) == 397);
  assert(decode_emissions_order_filled_plus_quote_message(&got, wire, 0) == 397);
  equal_emissions_order_filled_plus_quote_message(&got, &sent);

  for (size_t i = 0; i < 397; i++) { wire[i] = arbitrary(); }
  assert(decode_emissions_order_filled_plus_quote_message(&got, wire, 0) == 397);
  assert(encode_emissions_order_filled_plus_quote_message(&got, again, 0) == 397);
  for (size_t i = 0; i < 397; i++) { assert(again[i] == wire[i]); }
}

/* ---- Emissions Market Operation Ts Plus Quote Message: 340 bytes ------------- */

/* Emissions Market Operation TS plus Quote. Session-state event followed by full quote state. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t session_id[2];                          /* bytes 10 to 11 */
  uint8_t isin_code[12];                          /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue[6];    /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 30 to 41 */
  uint8_t board_event_id[3];                      /* bytes 42 to 44 */
  uint8_t start_time_of_a_board_event[9];         /* bytes 45 to 53 */
  uint8_t board_event_group_code[5];              /* bytes 54 to 58 */
  uint8_t trading_halt_reason_code[3];            /* bytes 59 to 61 */
  uint8_t ask_level_1_price[11];                  /* bytes 62 to 72 */
  uint8_t bid_level_1_price[11];                  /* bytes 73 to 83 */
  uint8_t ask_level_1_volume[12];                 /* bytes 84 to 95 */
  uint8_t bid_level_1_volume[12];                 /* bytes 96 to 107 */
  uint8_t ask_level_2_price[11];                  /* bytes 108 to 118 */
  uint8_t bid_level_2_price[11];                  /* bytes 119 to 129 */
  uint8_t ask_level_2_volume[12];                 /* bytes 130 to 141 */
  uint8_t bid_level_2_volume[12];                 /* bytes 142 to 153 */
  uint8_t ask_level_3_price[11];                  /* bytes 154 to 164 */
  uint8_t bid_level_3_price[11];                  /* bytes 165 to 175 */
  uint8_t ask_level_3_volume[12];                 /* bytes 176 to 187 */
  uint8_t bid_level_3_volume[12];                 /* bytes 188 to 199 */
  uint8_t ask_level_4_price[11];                  /* bytes 200 to 210 */
  uint8_t bid_level_4_price[11];                  /* bytes 211 to 221 */
  uint8_t ask_level_4_volume[12];                 /* bytes 222 to 233 */
  uint8_t bid_level_4_volume[12];                 /* bytes 234 to 245 */
  uint8_t ask_level_5_price[11];                  /* bytes 246 to 256 */
  uint8_t bid_level_5_price[11];                  /* bytes 257 to 267 */
  uint8_t ask_level_5_volume[12];                 /* bytes 268 to 279 */
  uint8_t bid_level_5_volume[12];                 /* bytes 280 to 291 */
  uint8_t total_ask_volume[12];                   /* bytes 292 to 303 */
  uint8_t total_bid_volume[12];                   /* bytes 304 to 315 */
  uint8_t estimated_trading_price[11];            /* bytes 316 to 326 */
  uint8_t estimated_trading_volume[12];           /* bytes 327 to 338 */
  uint8_t end_keyword;                            /* byte 339 */
} EmissionsMarketOperationTsPlusQuoteMessage;

/* any Emissions Market Operation Ts Plus Quote Message at all: every byte one the checker chooses */
static void any_emissions_market_operation_ts_plus_quote_message(EmissionsMarketOperationTsPlusQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Emissions Market Operation Ts Plus Quote Message to the wire: 340 bytes from at, returning where the next byte goes */
static size_t encode_emissions_market_operation_ts_plus_quote_message(const EmissionsMarketOperationTsPlusQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->board_event_id[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->start_time_of_a_board_event[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->board_event_group_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_halt_reason_code[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_1_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_1_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_2_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_2_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_3_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_4_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_4_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_5_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_5_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_ask_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_bid_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->estimated_trading_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->estimated_trading_volume[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Emissions Market Operation Ts Plus Quote Message off the wire: 340 bytes from at, returning where the next byte lies */
static size_t decode_emissions_market_operation_ts_plus_quote_message(EmissionsMarketOperationTsPlusQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Emissions Market Operation Ts Plus Quote Message is what was written, byte for byte */
static void equal_emissions_market_operation_ts_plus_quote_message(const EmissionsMarketOperationTsPlusQuoteMessage *read, const EmissionsMarketOperationTsPlusQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->board_event_id[i] == written->board_event_id[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->start_time_of_a_board_event[i] == written->start_time_of_a_board_event[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->board_event_group_code[i] == written->board_event_group_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trading_halt_reason_code[i] == written->trading_halt_reason_code[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_1_volume[i] == written->ask_level_1_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_1_volume[i] == written->bid_level_1_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_2_volume[i] == written->ask_level_2_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_2_volume[i] == written->bid_level_2_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_3_volume[i] == written->ask_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_3_volume[i] == written->bid_level_3_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_4_volume[i] == written->ask_level_4_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_4_volume[i] == written->bid_level_4_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_5_volume[i] == written->ask_level_5_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_5_volume[i] == written->bid_level_5_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_ask_volume[i] == written->total_ask_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_bid_volume[i] == written->total_bid_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->estimated_trading_price[i] == written->estimated_trading_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->estimated_trading_volume[i] == written->estimated_trading_volume[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Emissions Market Operation Ts Plus Quote Message: written and read back, then read and written back */
static void check_emissions_market_operation_ts_plus_quote_message(void) {
  EmissionsMarketOperationTsPlusQuoteMessage sent;
  EmissionsMarketOperationTsPlusQuoteMessage got;
  uint8_t wire[340];
  uint8_t again[340];

  any_emissions_market_operation_ts_plus_quote_message(&sent);
  assert(encode_emissions_market_operation_ts_plus_quote_message(&sent, wire, 0) == 340);
  assert(decode_emissions_market_operation_ts_plus_quote_message(&got, wire, 0) == 340);
  equal_emissions_market_operation_ts_plus_quote_message(&got, &sent);

  for (size_t i = 0; i < 340; i++) { wire[i] = arbitrary(); }
  assert(decode_emissions_market_operation_ts_plus_quote_message(&got, wire, 0) == 340);
  assert(encode_emissions_market_operation_ts_plus_quote_message(&got, again, 0) == 340);
  for (size_t i = 0; i < 340; i++) { assert(again[i] == wire[i]); }
}

/* ---- Emissions Snapshot Message: 413 bytes ----------------------------------- */

/* Emissions Market Data Snapshot. Periodic full state snapshot. */
typedef struct {
  uint8_t board_id[2];                                /* bytes 0 to 1 */
  uint8_t session_id[2];                              /* bytes 2 to 3 */
  uint8_t isin_code[12];                              /* bytes 4 to 15 */
  uint8_t a_designated_number_for_an_issue[6];        /* bytes 16 to 21 */
  uint8_t current_price[11];                          /* bytes 22 to 32 */
  uint8_t opening_price_long[11];                     /* bytes 33 to 43 */
  uint8_t todays_high[11];                            /* bytes 44 to 54 */
  uint8_t todays_low[11];                             /* bytes 55 to 65 */
  uint8_t accumulated_trading_volume[12];             /* bytes 66 to 77 */
  uint8_t accumulated_trading_value_long[22];         /* bytes 78 to 99 */
  uint8_t negotiated_block_trade_trading_volume[12];  /* bytes 100 to 111 */
  uint8_t negotiated_block_trade_trading_value[22];   /* bytes 112 to 133 */
  uint8_t trading_halt;                               /* byte 134 */
  uint8_t ask_level_1_price[11];                      /* bytes 135 to 145 */
  uint8_t bid_level_1_price[11];                      /* bytes 146 to 156 */
  uint8_t ask_level_1_volume[12];                     /* bytes 157 to 168 */
  uint8_t bid_level_1_volume[12];                     /* bytes 169 to 180 */
  uint8_t ask_level_2_price[11];                      /* bytes 181 to 191 */
  uint8_t bid_level_2_price[11];                      /* bytes 192 to 202 */
  uint8_t ask_level_2_volume[12];                     /* bytes 203 to 214 */
  uint8_t bid_level_2_volume[12];                     /* bytes 215 to 226 */
  uint8_t ask_level_3_price[11];                      /* bytes 227 to 237 */
  uint8_t bid_level_3_price[11];                      /* bytes 238 to 248 */
  uint8_t ask_level_3_volume[12];                     /* bytes 249 to 260 */
  uint8_t bid_level_3_volume[12];                     /* bytes 261 to 272 */
  uint8_t ask_level_4_price[11];                      /* bytes 273 to 283 */
  uint8_t bid_level_4_price[11];                      /* bytes 284 to 294 */
  uint8_t ask_level_4_volume[12];                     /* bytes 295 to 306 */
  uint8_t bid_level_4_volume[12];                     /* bytes 307 to 318 */
  uint8_t ask_level_5_price[11];                      /* bytes 319 to 329 */
  uint8_t bid_level_5_price[11];                      /* bytes 330 to 340 */
  uint8_t ask_level_5_volume[12];                     /* bytes 341 to 352 */
  uint8_t bid_level_5_volume[12];                     /* bytes 353 to 364 */
  uint8_t total_ask_volume[12];                       /* bytes 365 to 376 */
  uint8_t total_bid_volume[12];                       /* bytes 377 to 388 */
  uint8_t estimated_trading_price[11];                /* bytes 389 to 399 */
  uint8_t estimated_trading_volume[12];               /* bytes 400 to 411 */
  uint8_t end_keyword;                                /* byte 412 */
} EmissionsSnapshotMessage;

/* any Emissions Snapshot Message at all: every byte one the checker chooses */
static void any_emissions_snapshot_message(EmissionsSnapshotMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->current_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->opening_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->negotiated_block_trade_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->negotiated_block_trade_trading_value[i] = arbitrary(); }
  record->trading_halt = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_1_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_2_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_3_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_4_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_5_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Emissions Snapshot Message to the wire: 413 bytes from at, returning where the next byte goes */
static size_t encode_emissions_snapshot_message(const EmissionsSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->current_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->opening_price_long[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value_long[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->negotiated_block_trade_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->negotiated_block_trade_trading_value[i]; }
  wire[at++] = record->trading_halt;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_1_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_1_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_2_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_2_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_3_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_3_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_4_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_4_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_5_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_5_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_ask_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_bid_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->estimated_trading_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->estimated_trading_volume[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Emissions Snapshot Message off the wire: 413 bytes from at, returning where the next byte lies */
static size_t decode_emissions_snapshot_message(EmissionsSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->current_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->opening_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->negotiated_block_trade_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->negotiated_block_trade_trading_value[i] = wire[at++]; }
  record->trading_halt = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_1_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_2_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_3_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_4_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_5_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Emissions Snapshot Message is what was written, byte for byte */
static void equal_emissions_snapshot_message(const EmissionsSnapshotMessage *read, const EmissionsSnapshotMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->current_price[i] == written->current_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->opening_price_long[i] == written->opening_price_long[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value_long[i] == written->accumulated_trading_value_long[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->negotiated_block_trade_trading_volume[i] == written->negotiated_block_trade_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->negotiated_block_trade_trading_value[i] == written->negotiated_block_trade_trading_value[i]); }
  assert(read->trading_halt == written->trading_halt);
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_1_volume[i] == written->ask_level_1_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_1_volume[i] == written->bid_level_1_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_2_volume[i] == written->ask_level_2_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_2_volume[i] == written->bid_level_2_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_3_volume[i] == written->ask_level_3_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_3_volume[i] == written->bid_level_3_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_4_volume[i] == written->ask_level_4_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_4_volume[i] == written->bid_level_4_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_5_volume[i] == written->ask_level_5_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_5_volume[i] == written->bid_level_5_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_ask_volume[i] == written->total_ask_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_bid_volume[i] == written->total_bid_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->estimated_trading_price[i] == written->estimated_trading_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->estimated_trading_volume[i] == written->estimated_trading_volume[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Emissions Snapshot Message: written and read back, then read and written back */
static void check_emissions_snapshot_message(void) {
  EmissionsSnapshotMessage sent;
  EmissionsSnapshotMessage got;
  uint8_t wire[413];
  uint8_t again[413];

  any_emissions_snapshot_message(&sent);
  assert(encode_emissions_snapshot_message(&sent, wire, 0) == 413);
  assert(decode_emissions_snapshot_message(&got, wire, 0) == 413);
  equal_emissions_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 413; i++) { wire[i] = arbitrary(); }
  assert(decode_emissions_snapshot_message(&got, wire, 0) == 413);
  assert(encode_emissions_snapshot_message(&got, again, 0) == 413);
  for (size_t i = 0; i < 413; i++) { assert(again[i] == wire[i]); }
}

/* ---- Emissions Negotiated Trade Message: 76 bytes ---------------------------- */

/* Emissions Negotiated Trade Data. */
typedef struct {
  uint8_t board_id[2];                          /* bytes 0 to 1 */
  uint8_t isin_code[12];                        /* bytes 2 to 13 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 14 to 19 */
  uint8_t trading_price[11];                    /* bytes 20 to 30 */
  uint8_t trading_volume[10];                   /* bytes 31 to 40 */
  uint8_t accumulated_trading_volume[12];       /* bytes 41 to 52 */
  uint8_t accumulated_trading_value_long[22];   /* bytes 53 to 74 */
  uint8_t end_keyword;                          /* byte 75 */
} EmissionsNegotiatedTradeMessage;

/* any Emissions Negotiated Trade Message at all: every byte one the checker chooses */
static void any_emissions_negotiated_trade_message(EmissionsNegotiatedTradeMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Emissions Negotiated Trade Message to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_emissions_negotiated_trade_message(const EmissionsNegotiatedTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value_long[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Emissions Negotiated Trade Message off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_emissions_negotiated_trade_message(EmissionsNegotiatedTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Emissions Negotiated Trade Message is what was written, byte for byte */
static void equal_emissions_negotiated_trade_message(const EmissionsNegotiatedTradeMessage *read, const EmissionsNegotiatedTradeMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value_long[i] == written->accumulated_trading_value_long[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Emissions Negotiated Trade Message: written and read back, then read and written back */
static void check_emissions_negotiated_trade_message(void) {
  EmissionsNegotiatedTradeMessage sent;
  EmissionsNegotiatedTradeMessage got;
  uint8_t wire[76];
  uint8_t again[76];

  any_emissions_negotiated_trade_message(&sent);
  assert(encode_emissions_negotiated_trade_message(&sent, wire, 0) == 76);
  assert(decode_emissions_negotiated_trade_message(&got, wire, 0) == 76);
  equal_emissions_negotiated_trade_message(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_emissions_negotiated_trade_message(&got, wire, 0) == 76);
  assert(encode_emissions_negotiated_trade_message(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Emissions Determination Of Base Price Message: 84 bytes ----------------- */

/* Emissions Determination of Base Price. Per-issue base price assignment. */
typedef struct {
  uint8_t message_sequence_number[8];           /* bytes 0 to 7 */
  uint8_t board_id[2];                          /* bytes 8 to 9 */
  uint8_t isin_code[12];                        /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 22 to 27 */
  uint8_t base_price[11];                       /* bytes 28 to 38 */
  uint8_t upper_limit_of_base_price[11];        /* bytes 39 to 49 */
  uint8_t lower_limit_of_base_price[11];        /* bytes 50 to 60 */
  uint8_t block_trading_upper_limit_price[11];  /* bytes 61 to 71 */
  uint8_t block_trading_lower_limit_price[11];  /* bytes 72 to 82 */
  uint8_t end_keyword;                          /* byte 83 */
} EmissionsDeterminationOfBasePriceMessage;

/* any Emissions Determination Of Base Price Message at all: every byte one the checker chooses */
static void any_emissions_determination_of_base_price_message(EmissionsDeterminationOfBasePriceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->upper_limit_of_base_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_of_base_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->block_trading_upper_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->block_trading_lower_limit_price[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Emissions Determination Of Base Price Message to the wire: 84 bytes from at, returning where the next byte goes */
static size_t encode_emissions_determination_of_base_price_message(const EmissionsDeterminationOfBasePriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->base_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->upper_limit_of_base_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lower_limit_of_base_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->block_trading_upper_limit_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->block_trading_lower_limit_price[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Emissions Determination Of Base Price Message off the wire: 84 bytes from at, returning where the next byte lies */
static size_t decode_emissions_determination_of_base_price_message(EmissionsDeterminationOfBasePriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->upper_limit_of_base_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_of_base_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->block_trading_upper_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->block_trading_lower_limit_price[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Emissions Determination Of Base Price Message is what was written, byte for byte */
static void equal_emissions_determination_of_base_price_message(const EmissionsDeterminationOfBasePriceMessage *read, const EmissionsDeterminationOfBasePriceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->base_price[i] == written->base_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->upper_limit_of_base_price[i] == written->upper_limit_of_base_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lower_limit_of_base_price[i] == written->lower_limit_of_base_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->block_trading_upper_limit_price[i] == written->block_trading_upper_limit_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->block_trading_lower_limit_price[i] == written->block_trading_lower_limit_price[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Emissions Determination Of Base Price Message: written and read back, then read and written back */
static void check_emissions_determination_of_base_price_message(void) {
  EmissionsDeterminationOfBasePriceMessage sent;
  EmissionsDeterminationOfBasePriceMessage got;
  uint8_t wire[84];
  uint8_t again[84];

  any_emissions_determination_of_base_price_message(&sent);
  assert(encode_emissions_determination_of_base_price_message(&sent, wire, 0) == 84);
  assert(decode_emissions_determination_of_base_price_message(&got, wire, 0) == 84);
  equal_emissions_determination_of_base_price_message(&got, &sent);

  for (size_t i = 0; i < 84; i++) { wire[i] = arbitrary(); }
  assert(decode_emissions_determination_of_base_price_message(&got, wire, 0) == 84);
  assert(encode_emissions_determination_of_base_price_message(&got, again, 0) == 84);
  for (size_t i = 0; i < 84; i++) { assert(again[i] == wire[i]); }
}

/* ---- Emissions Auction Results Message: 90 bytes ----------------------------- */

/* Emissions Auction Results per Issue. */
typedef struct {
  uint8_t isin_code[12];                        /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 12 to 17 */
  uint8_t auction_bid_volume[12];               /* bytes 18 to 29 */
  uint8_t auction_price[11];                    /* bytes 30 to 40 */
  uint8_t auction_volume[12];                   /* bytes 41 to 52 */
  uint8_t volume_in_the_bid_invitation[12];     /* bytes 53 to 64 */
  uint8_t number_of_bidders[13];                /* bytes 65 to 77 */
  uint8_t bid_to_cover_ratio[11];               /* bytes 78 to 88 */
  uint8_t end_keyword;                          /* byte 89 */
} EmissionsAuctionResultsMessage;

/* any Emissions Auction Results Message at all: every byte one the checker chooses */
static void any_emissions_auction_results_message(EmissionsAuctionResultsMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->auction_bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->auction_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->auction_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->volume_in_the_bid_invitation[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->number_of_bidders[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_to_cover_ratio[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Emissions Auction Results Message to the wire: 90 bytes from at, returning where the next byte goes */
static size_t encode_emissions_auction_results_message(const EmissionsAuctionResultsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->auction_bid_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->auction_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->auction_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->volume_in_the_bid_invitation[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->number_of_bidders[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_to_cover_ratio[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Emissions Auction Results Message off the wire: 90 bytes from at, returning where the next byte lies */
static size_t decode_emissions_auction_results_message(EmissionsAuctionResultsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->auction_bid_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->auction_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->auction_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->volume_in_the_bid_invitation[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->number_of_bidders[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_to_cover_ratio[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Emissions Auction Results Message is what was written, byte for byte */
static void equal_emissions_auction_results_message(const EmissionsAuctionResultsMessage *read, const EmissionsAuctionResultsMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->auction_bid_volume[i] == written->auction_bid_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->auction_price[i] == written->auction_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->auction_volume[i] == written->auction_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->volume_in_the_bid_invitation[i] == written->volume_in_the_bid_invitation[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->number_of_bidders[i] == written->number_of_bidders[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_to_cover_ratio[i] == written->bid_to_cover_ratio[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Emissions Auction Results Message: written and read back, then read and written back */
static void check_emissions_auction_results_message(void) {
  EmissionsAuctionResultsMessage sent;
  EmissionsAuctionResultsMessage got;
  uint8_t wire[90];
  uint8_t again[90];

  any_emissions_auction_results_message(&sent);
  assert(encode_emissions_auction_results_message(&sent, wire, 0) == 90);
  assert(decode_emissions_auction_results_message(&got, wire, 0) == 90);
  equal_emissions_auction_results_message(&got, &sent);

  for (size_t i = 0; i < 90; i++) { wire[i] = arbitrary(); }
  assert(decode_emissions_auction_results_message(&got, wire, 0) == 90);
  assert(encode_emissions_auction_results_message(&got, again, 0) == 90);
  for (size_t i = 0; i < 90; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spot Gold Batch Data Message: 408 bytes --------------------------------- */

/* Spot Gold Batch Data. Per-issue reference data dumped at start-of-day. */
typedef struct {
  uint8_t message_sequence_number[8];                          /* bytes 0 to 7 */
  uint8_t total_number_of_instruments_of_the_contract[6];      /* bytes 8 to 13 */
  uint8_t business_date[8];                                    /* bytes 14 to 21 */
  uint8_t isin_code[12];                                       /* bytes 22 to 33 */
  uint8_t a_designated_number_for_an_issue[6];                 /* bytes 34 to 39 */
  uint8_t abbreviated_issue_code[9];                           /* bytes 40 to 48 */
  uint8_t issue_name[80];                                      /* bytes 49 to 128 */
  uint8_t abbreviated_issue_name[40];                          /* bytes 129 to 168 */
  uint8_t english_issue_name[80];                              /* bytes 169 to 248 */
  uint8_t abbreviated_issue_name_in_en[40];                    /* bytes 249 to 288 */
  uint8_t market_operation_product_id[3];                      /* bytes 289 to 291 */
  uint8_t security_group_id[2];                                /* bytes 292 to 293 */
  uint8_t listing_date[8];                                     /* bytes 294 to 301 */
  uint8_t delisting_date[8];                                   /* bytes 302 to 309 */
  uint8_t market_id[3];                                        /* bytes 310 to 312 */
  uint8_t upper_limit_price[11];                               /* bytes 313 to 323 */
  uint8_t lower_limit_price[11];                               /* bytes 324 to 334 */
  uint8_t base_price[11];                                      /* bytes 335 to 345 */
  uint8_t random_end_trigger_code;                             /* byte 346 */
  uint8_t trading_halt;                                        /* byte 347 */
  uint8_t unit_of_volume_in_main_board[11];                    /* bytes 348 to 358 */
  uint8_t yesterdays_closing_price[11];                        /* bytes 359 to 369 */
  uint8_t yesterdays_closing_price_type_code;                  /* byte 370 */
  uint8_t substitute_price_of_securities[11];                  /* bytes 371 to 381 */
  uint8_t appraisal_ratio_of_substitute_price[13];             /* bytes 382 to 394 */
  uint8_t a_representative_issue_to_calculate_base_price[12];  /* bytes 395 to 406 */
  uint8_t end_keyword;                                         /* byte 407 */
} SpotGoldBatchDataMessage;

/* any Spot Gold Batch Data Message at all: every byte one the checker chooses */
static void any_spot_gold_batch_data_message(SpotGoldBatchDataMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_instruments_of_the_contract[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->abbreviated_issue_code[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->english_issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name_in_en[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->delisting_date[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->upper_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = arbitrary(); }
  record->random_end_trigger_code = arbitrary();
  record->trading_halt = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->unit_of_volume_in_main_board[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->yesterdays_closing_price[i] = arbitrary(); }
  record->yesterdays_closing_price_type_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->substitute_price_of_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->appraisal_ratio_of_substitute_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->a_representative_issue_to_calculate_base_price[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Spot Gold Batch Data Message to the wire: 408 bytes from at, returning where the next byte goes */
static size_t encode_spot_gold_batch_data_message(const SpotGoldBatchDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_number_of_instruments_of_the_contract[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->abbreviated_issue_code[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->issue_name[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->english_issue_name[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name_in_en[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_operation_product_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->listing_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->delisting_date[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->upper_limit_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lower_limit_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->base_price[i]; }
  wire[at++] = record->random_end_trigger_code;
  wire[at++] = record->trading_halt;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->unit_of_volume_in_main_board[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->yesterdays_closing_price[i]; }
  wire[at++] = record->yesterdays_closing_price_type_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->substitute_price_of_securities[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->appraisal_ratio_of_substitute_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->a_representative_issue_to_calculate_base_price[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Spot Gold Batch Data Message off the wire: 408 bytes from at, returning where the next byte lies */
static size_t decode_spot_gold_batch_data_message(SpotGoldBatchDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_instruments_of_the_contract[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->abbreviated_issue_code[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->english_issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name_in_en[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->delisting_date[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->upper_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = wire[at++]; }
  record->random_end_trigger_code = wire[at++];
  record->trading_halt = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->unit_of_volume_in_main_board[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->yesterdays_closing_price[i] = wire[at++]; }
  record->yesterdays_closing_price_type_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->substitute_price_of_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->appraisal_ratio_of_substitute_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->a_representative_issue_to_calculate_base_price[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Spot Gold Batch Data Message is what was written, byte for byte */
static void equal_spot_gold_batch_data_message(const SpotGoldBatchDataMessage *read, const SpotGoldBatchDataMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_number_of_instruments_of_the_contract[i] == written->total_number_of_instruments_of_the_contract[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->abbreviated_issue_code[i] == written->abbreviated_issue_code[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->issue_name[i] == written->issue_name[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name[i] == written->abbreviated_issue_name[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->english_issue_name[i] == written->english_issue_name[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name_in_en[i] == written->abbreviated_issue_name_in_en[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->market_operation_product_id[i] == written->market_operation_product_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_group_id[i] == written->security_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->listing_date[i] == written->listing_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->delisting_date[i] == written->delisting_date[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->upper_limit_price[i] == written->upper_limit_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lower_limit_price[i] == written->lower_limit_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->base_price[i] == written->base_price[i]); }
  assert(read->random_end_trigger_code == written->random_end_trigger_code);
  assert(read->trading_halt == written->trading_halt);
  for (size_t i = 0; i < 11; i++) { assert(read->unit_of_volume_in_main_board[i] == written->unit_of_volume_in_main_board[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->yesterdays_closing_price[i] == written->yesterdays_closing_price[i]); }
  assert(read->yesterdays_closing_price_type_code == written->yesterdays_closing_price_type_code);
  for (size_t i = 0; i < 11; i++) { assert(read->substitute_price_of_securities[i] == written->substitute_price_of_securities[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->appraisal_ratio_of_substitute_price[i] == written->appraisal_ratio_of_substitute_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->a_representative_issue_to_calculate_base_price[i] == written->a_representative_issue_to_calculate_base_price[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Spot Gold Batch Data Message: written and read back, then read and written back */
static void check_spot_gold_batch_data_message(void) {
  SpotGoldBatchDataMessage sent;
  SpotGoldBatchDataMessage got;
  uint8_t wire[408];
  uint8_t again[408];

  any_spot_gold_batch_data_message(&sent);
  assert(encode_spot_gold_batch_data_message(&sent, wire, 0) == 408);
  assert(decode_spot_gold_batch_data_message(&got, wire, 0) == 408);
  equal_spot_gold_batch_data_message(&got, &sent);

  for (size_t i = 0; i < 408; i++) { wire[i] = arbitrary(); }
  assert(decode_spot_gold_batch_data_message(&got, wire, 0) == 408);
  assert(encode_spot_gold_batch_data_message(&got, again, 0) == 408);
  for (size_t i = 0; i < 408; i++) { assert(again[i] == wire[i]); }
}

/* ---- Emissions Batch Data Message: 409 bytes --------------------------------- */

/* Emissions Batch Data. Per-issue reference data dumped at start-of-day. */
typedef struct {
  uint8_t message_sequence_number[8];                                          /* bytes 0 to 7 */
  uint8_t total_number_of_instruments_of_the_contract[6];                      /* bytes 8 to 13 */
  uint8_t business_date[8];                                                    /* bytes 14 to 21 */
  uint8_t isin_code[12];                                                       /* bytes 22 to 33 */
  uint8_t a_designated_number_for_an_issue[6];                                 /* bytes 34 to 39 */
  uint8_t abbreviated_issue_code[9];                                           /* bytes 40 to 48 */
  uint8_t issue_name[80];                                                      /* bytes 49 to 128 */
  uint8_t abbreviated_issue_name[40];                                          /* bytes 129 to 168 */
  uint8_t english_issue_name[80];                                              /* bytes 169 to 248 */
  uint8_t abbreviated_issue_name_in_en[40];                                    /* bytes 249 to 288 */
  uint8_t market_operation_product_id[3];                                      /* bytes 289 to 291 */
  uint8_t security_group_id[2];                                                /* bytes 292 to 293 */
  uint8_t listing_date[8];                                                     /* bytes 294 to 301 */
  uint8_t delisting_date[8];                                                   /* bytes 302 to 309 */
  uint8_t market_id[3];                                                        /* bytes 310 to 312 */
  uint8_t upper_limit_price[11];                                               /* bytes 313 to 323 */
  uint8_t lower_limit_price[11];                                               /* bytes 324 to 334 */
  uint8_t base_price[11];                                                      /* bytes 335 to 345 */
  uint8_t random_end_trigger_code;                                             /* byte 346 */
  uint8_t trading_halt;                                                        /* byte 347 */
  uint8_t unit_of_volume_in_main_board[11];                                    /* bytes 348 to 358 */
  uint8_t yesterdays_closing_price[11];                                        /* bytes 359 to 369 */
  uint8_t yesterdays_closing_price_type_code;                                  /* byte 370 */
  uint8_t substitute_price_of_securities[11];                                  /* bytes 371 to 381 */
  uint8_t appraisal_ratio_of_substitute_price[13];                             /* bytes 382 to 394 */
  uint8_t a_representative_issue_to_calculate_base_price[12];                  /* bytes 395 to 406 */
  uint8_t an_issue_of_which_base_price_is_settled_with_a_todays_single_price;  /* byte 407 */
  uint8_t end_keyword;                                                         /* byte 408 */
} EmissionsBatchDataMessage;

/* any Emissions Batch Data Message at all: every byte one the checker chooses */
static void any_emissions_batch_data_message(EmissionsBatchDataMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_instruments_of_the_contract[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->abbreviated_issue_code[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->english_issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name_in_en[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->delisting_date[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->upper_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = arbitrary(); }
  record->random_end_trigger_code = arbitrary();
  record->trading_halt = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->unit_of_volume_in_main_board[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->yesterdays_closing_price[i] = arbitrary(); }
  record->yesterdays_closing_price_type_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->substitute_price_of_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->appraisal_ratio_of_substitute_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->a_representative_issue_to_calculate_base_price[i] = arbitrary(); }
  record->an_issue_of_which_base_price_is_settled_with_a_todays_single_price = arbitrary();
  record->end_keyword = arbitrary();
}

/* Emissions Batch Data Message to the wire: 409 bytes from at, returning where the next byte goes */
static size_t encode_emissions_batch_data_message(const EmissionsBatchDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_number_of_instruments_of_the_contract[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->abbreviated_issue_code[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->issue_name[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->english_issue_name[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name_in_en[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_operation_product_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->listing_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->delisting_date[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->upper_limit_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lower_limit_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->base_price[i]; }
  wire[at++] = record->random_end_trigger_code;
  wire[at++] = record->trading_halt;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->unit_of_volume_in_main_board[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->yesterdays_closing_price[i]; }
  wire[at++] = record->yesterdays_closing_price_type_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->substitute_price_of_securities[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->appraisal_ratio_of_substitute_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->a_representative_issue_to_calculate_base_price[i]; }
  wire[at++] = record->an_issue_of_which_base_price_is_settled_with_a_todays_single_price;
  wire[at++] = record->end_keyword;

  return at;
}

/* Emissions Batch Data Message off the wire: 409 bytes from at, returning where the next byte lies */
static size_t decode_emissions_batch_data_message(EmissionsBatchDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_instruments_of_the_contract[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->abbreviated_issue_code[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->english_issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name_in_en[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->delisting_date[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->upper_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = wire[at++]; }
  record->random_end_trigger_code = wire[at++];
  record->trading_halt = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->unit_of_volume_in_main_board[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->yesterdays_closing_price[i] = wire[at++]; }
  record->yesterdays_closing_price_type_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->substitute_price_of_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->appraisal_ratio_of_substitute_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->a_representative_issue_to_calculate_base_price[i] = wire[at++]; }
  record->an_issue_of_which_base_price_is_settled_with_a_todays_single_price = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Emissions Batch Data Message is what was written, byte for byte */
static void equal_emissions_batch_data_message(const EmissionsBatchDataMessage *read, const EmissionsBatchDataMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_number_of_instruments_of_the_contract[i] == written->total_number_of_instruments_of_the_contract[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->abbreviated_issue_code[i] == written->abbreviated_issue_code[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->issue_name[i] == written->issue_name[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name[i] == written->abbreviated_issue_name[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->english_issue_name[i] == written->english_issue_name[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name_in_en[i] == written->abbreviated_issue_name_in_en[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->market_operation_product_id[i] == written->market_operation_product_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_group_id[i] == written->security_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->listing_date[i] == written->listing_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->delisting_date[i] == written->delisting_date[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->upper_limit_price[i] == written->upper_limit_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lower_limit_price[i] == written->lower_limit_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->base_price[i] == written->base_price[i]); }
  assert(read->random_end_trigger_code == written->random_end_trigger_code);
  assert(read->trading_halt == written->trading_halt);
  for (size_t i = 0; i < 11; i++) { assert(read->unit_of_volume_in_main_board[i] == written->unit_of_volume_in_main_board[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->yesterdays_closing_price[i] == written->yesterdays_closing_price[i]); }
  assert(read->yesterdays_closing_price_type_code == written->yesterdays_closing_price_type_code);
  for (size_t i = 0; i < 11; i++) { assert(read->substitute_price_of_securities[i] == written->substitute_price_of_securities[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->appraisal_ratio_of_substitute_price[i] == written->appraisal_ratio_of_substitute_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->a_representative_issue_to_calculate_base_price[i] == written->a_representative_issue_to_calculate_base_price[i]); }
  assert(read->an_issue_of_which_base_price_is_settled_with_a_todays_single_price == written->an_issue_of_which_base_price_is_settled_with_a_todays_single_price);
  assert(read->end_keyword == written->end_keyword);
}

/* Emissions Batch Data Message: written and read back, then read and written back */
static void check_emissions_batch_data_message(void) {
  EmissionsBatchDataMessage sent;
  EmissionsBatchDataMessage got;
  uint8_t wire[409];
  uint8_t again[409];

  any_emissions_batch_data_message(&sent);
  assert(encode_emissions_batch_data_message(&sent, wire, 0) == 409);
  assert(decode_emissions_batch_data_message(&got, wire, 0) == 409);
  equal_emissions_batch_data_message(&got, &sent);

  for (size_t i = 0; i < 409; i++) { wire[i] = arbitrary(); }
  assert(decode_emissions_batch_data_message(&got, wire, 0) == 409);
  assert(encode_emissions_batch_data_message(&got, again, 0) == 409);
  for (size_t i = 0; i < 409; i++) { assert(again[i] == wire[i]); }
}

/* ---- External Gold Spot Closing Price Message: 120 bytes --------------------- */

/* External Gold Spot (Closing Price) (IFMSRID0036) — Commodities A CMD variant. NESTED-BRANCH NOTE: TR-CODE M200G is shared with the Real-time variant (IFMSRID0035); the Data Type field (field 3) discriminates between Closing Price and Real-time. The loader will need an inner Branch on Data Type once the nested-Branch shape is settled. Real-time variant deferred. */
typedef struct {
  uint8_t data_type;                          /* byte 0 */
  uint8_t job_code_symbol[16];                /* bytes 1 to 16 */
  uint8_t trading_date[8];                    /* bytes 17 to 24 */
  uint8_t trading_time[6];                    /* bytes 25 to 30 */
  uint8_t opening_price_short[9];             /* bytes 31 to 39 */
  uint8_t high_price[9];                      /* bytes 40 to 48 */
  uint8_t low_price[9];                       /* bytes 49 to 57 */
  uint8_t closing_price_short[9];             /* bytes 58 to 66 */
  uint8_t change_from_previous_day_sign;      /* byte 67 */
  uint8_t change_from_previous_day[9];        /* bytes 68 to 76 */
  uint8_t fluctuating_rate[9];                /* bytes 77 to 85 */
  uint8_t bid_quote[9];                       /* bytes 86 to 94 */
  uint8_t ask_quote[9];                       /* bytes 95 to 103 */
  uint8_t currency_code_long[6];              /* bytes 104 to 109 */
  uint8_t conversion_basic_exchange_rate[9];  /* bytes 110 to 118 */
  uint8_t end_keyword;                        /* byte 119 */
} ExternalGoldSpotClosingPriceMessage;

/* any External Gold Spot Closing Price Message at all: every byte one the checker chooses */
static void any_external_gold_spot_closing_price_message(ExternalGoldSpotClosingPriceMessage *record) {
  record->data_type = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->job_code_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->trading_time[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->opening_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->closing_price_short[i] = arbitrary(); }
  record->change_from_previous_day_sign = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->change_from_previous_day[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->fluctuating_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->bid_quote[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->ask_quote[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->currency_code_long[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->conversion_basic_exchange_rate[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* External Gold Spot Closing Price Message to the wire: 120 bytes from at, returning where the next byte goes */
static size_t encode_external_gold_spot_closing_price_message(const ExternalGoldSpotClosingPriceMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->data_type;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->job_code_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trading_time[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->opening_price_short[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->closing_price_short[i]; }
  wire[at++] = record->change_from_previous_day_sign;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->change_from_previous_day[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->fluctuating_rate[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->bid_quote[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->ask_quote[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->currency_code_long[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->conversion_basic_exchange_rate[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* External Gold Spot Closing Price Message off the wire: 120 bytes from at, returning where the next byte lies */
static size_t decode_external_gold_spot_closing_price_message(ExternalGoldSpotClosingPriceMessage *record, const uint8_t *wire, size_t at) {
  record->data_type = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->job_code_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->trading_time[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->opening_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->closing_price_short[i] = wire[at++]; }
  record->change_from_previous_day_sign = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->change_from_previous_day[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->fluctuating_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->bid_quote[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->ask_quote[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->currency_code_long[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->conversion_basic_exchange_rate[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of External Gold Spot Closing Price Message is what was written, byte for byte */
static void equal_external_gold_spot_closing_price_message(const ExternalGoldSpotClosingPriceMessage *read, const ExternalGoldSpotClosingPriceMessage *written) {
  assert(read->data_type == written->data_type);
  for (size_t i = 0; i < 16; i++) { assert(read->job_code_symbol[i] == written->job_code_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_date[i] == written->trading_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->trading_time[i] == written->trading_time[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->opening_price_short[i] == written->opening_price_short[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->closing_price_short[i] == written->closing_price_short[i]); }
  assert(read->change_from_previous_day_sign == written->change_from_previous_day_sign);
  for (size_t i = 0; i < 9; i++) { assert(read->change_from_previous_day[i] == written->change_from_previous_day[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->fluctuating_rate[i] == written->fluctuating_rate[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->bid_quote[i] == written->bid_quote[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->ask_quote[i] == written->ask_quote[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->currency_code_long[i] == written->currency_code_long[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->conversion_basic_exchange_rate[i] == written->conversion_basic_exchange_rate[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* External Gold Spot Closing Price Message: written and read back, then read and written back */
static void check_external_gold_spot_closing_price_message(void) {
  ExternalGoldSpotClosingPriceMessage sent;
  ExternalGoldSpotClosingPriceMessage got;
  uint8_t wire[120];
  uint8_t again[120];

  any_external_gold_spot_closing_price_message(&sent);
  assert(encode_external_gold_spot_closing_price_message(&sent, wire, 0) == 120);
  assert(decode_external_gold_spot_closing_price_message(&got, wire, 0) == 120);
  equal_external_gold_spot_closing_price_message(&got, &sent);

  for (size_t i = 0; i < 120; i++) { wire[i] = arbitrary(); }
  assert(decode_external_gold_spot_closing_price_message(&got, wire, 0) == 120);
  assert(encode_external_gold_spot_closing_price_message(&got, again, 0) == 120);
  for (size_t i = 0; i < 120; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spot Gold Market Operation Ts Message: 63 bytes ------------------------- */

/* Spot Gold Market Operation TS. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t session_id[2];                          /* bytes 10 to 11 */
  uint8_t isin_code[12];                          /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue[6];    /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 30 to 41 */
  uint8_t board_event_id[3];                      /* bytes 42 to 44 */
  uint8_t start_time_of_a_board_event[9];         /* bytes 45 to 53 */
  uint8_t board_event_group_code[5];              /* bytes 54 to 58 */
  uint8_t trading_halt_reason_code[3];            /* bytes 59 to 61 */
  uint8_t end_keyword;                            /* byte 62 */
} SpotGoldMarketOperationTsMessage;

/* any Spot Gold Market Operation Ts Message at all: every byte one the checker chooses */
static void any_spot_gold_market_operation_ts_message(SpotGoldMarketOperationTsMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Spot Gold Market Operation Ts Message to the wire: 63 bytes from at, returning where the next byte goes */
static size_t encode_spot_gold_market_operation_ts_message(const SpotGoldMarketOperationTsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->board_event_id[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->start_time_of_a_board_event[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->board_event_group_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_halt_reason_code[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Spot Gold Market Operation Ts Message off the wire: 63 bytes from at, returning where the next byte lies */
static size_t decode_spot_gold_market_operation_ts_message(SpotGoldMarketOperationTsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Spot Gold Market Operation Ts Message is what was written, byte for byte */
static void equal_spot_gold_market_operation_ts_message(const SpotGoldMarketOperationTsMessage *read, const SpotGoldMarketOperationTsMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->board_event_id[i] == written->board_event_id[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->start_time_of_a_board_event[i] == written->start_time_of_a_board_event[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->board_event_group_code[i] == written->board_event_group_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trading_halt_reason_code[i] == written->trading_halt_reason_code[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Spot Gold Market Operation Ts Message: written and read back, then read and written back */
static void check_spot_gold_market_operation_ts_message(void) {
  SpotGoldMarketOperationTsMessage sent;
  SpotGoldMarketOperationTsMessage got;
  uint8_t wire[63];
  uint8_t again[63];

  any_spot_gold_market_operation_ts_message(&sent);
  assert(encode_spot_gold_market_operation_ts_message(&sent, wire, 0) == 63);
  assert(decode_spot_gold_market_operation_ts_message(&got, wire, 0) == 63);
  equal_spot_gold_market_operation_ts_message(&got, &sent);

  for (size_t i = 0; i < 63; i++) { wire[i] = arbitrary(); }
  assert(decode_spot_gold_market_operation_ts_message(&got, wire, 0) == 63);
  assert(encode_spot_gold_market_operation_ts_message(&got, again, 0) == 63);
  for (size_t i = 0; i < 63; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spot Gold Issue Closing Message: 107 bytes ------------------------------ */

/* Spot Gold Issue Closing. */
typedef struct {
  uint8_t message_sequence_number[8];                      /* bytes 0 to 7 */
  uint8_t board_id[2];                                     /* bytes 8 to 9 */
  uint8_t isin_code[12];                                   /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];             /* bytes 22 to 27 */
  uint8_t closing_price_long[11];                          /* bytes 28 to 38 */
  uint8_t closing_price_type_code;                         /* byte 39 */
  uint8_t filler_11[11];                                   /* bytes 40 to 50 */
  uint8_t second_filler_11[11];                            /* bytes 51 to 61 */
  uint8_t closing_price_weighted_stock_price_average[11];  /* bytes 62 to 72 */
  uint8_t closing_price_base_price_of_buy_in[11];          /* bytes 73 to 83 */
  uint8_t closing_price_upper_limit_of_buy_in[11];         /* bytes 84 to 94 */
  uint8_t closing_price_lower_limit_of_buy_in[11];         /* bytes 95 to 105 */
  uint8_t end_keyword;                                     /* byte 106 */
} SpotGoldIssueClosingMessage;

/* any Spot Gold Issue Closing Message at all: every byte one the checker chooses */
static void any_spot_gold_issue_closing_message(SpotGoldIssueClosingMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_long[i] = arbitrary(); }
  record->closing_price_type_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->filler_11[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->second_filler_11[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_weighted_stock_price_average[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_base_price_of_buy_in[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_upper_limit_of_buy_in[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_lower_limit_of_buy_in[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Spot Gold Issue Closing Message to the wire: 107 bytes from at, returning where the next byte goes */
static size_t encode_spot_gold_issue_closing_message(const SpotGoldIssueClosingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_long[i]; }
  wire[at++] = record->closing_price_type_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->filler_11[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->second_filler_11[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_weighted_stock_price_average[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_base_price_of_buy_in[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_upper_limit_of_buy_in[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_lower_limit_of_buy_in[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Spot Gold Issue Closing Message off the wire: 107 bytes from at, returning where the next byte lies */
static size_t decode_spot_gold_issue_closing_message(SpotGoldIssueClosingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_long[i] = wire[at++]; }
  record->closing_price_type_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->filler_11[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->second_filler_11[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_weighted_stock_price_average[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_base_price_of_buy_in[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_upper_limit_of_buy_in[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_lower_limit_of_buy_in[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Spot Gold Issue Closing Message is what was written, byte for byte */
static void equal_spot_gold_issue_closing_message(const SpotGoldIssueClosingMessage *read, const SpotGoldIssueClosingMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_long[i] == written->closing_price_long[i]); }
  assert(read->closing_price_type_code == written->closing_price_type_code);
  for (size_t i = 0; i < 11; i++) { assert(read->filler_11[i] == written->filler_11[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->second_filler_11[i] == written->second_filler_11[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_weighted_stock_price_average[i] == written->closing_price_weighted_stock_price_average[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_base_price_of_buy_in[i] == written->closing_price_base_price_of_buy_in[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_upper_limit_of_buy_in[i] == written->closing_price_upper_limit_of_buy_in[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_lower_limit_of_buy_in[i] == written->closing_price_lower_limit_of_buy_in[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Spot Gold Issue Closing Message: written and read back, then read and written back */
static void check_spot_gold_issue_closing_message(void) {
  SpotGoldIssueClosingMessage sent;
  SpotGoldIssueClosingMessage got;
  uint8_t wire[107];
  uint8_t again[107];

  any_spot_gold_issue_closing_message(&sent);
  assert(encode_spot_gold_issue_closing_message(&sent, wire, 0) == 107);
  assert(decode_spot_gold_issue_closing_message(&got, wire, 0) == 107);
  equal_spot_gold_issue_closing_message(&got, &sent);

  for (size_t i = 0; i < 107; i++) { wire[i] = arbitrary(); }
  assert(decode_spot_gold_issue_closing_message(&got, wire, 0) == 107);
  assert(encode_spot_gold_issue_closing_message(&got, again, 0) == 107);
  for (size_t i = 0; i < 107; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spot Gold Market Operation Schedule Message: 78 bytes ------------------- */

/* Spot Gold Market Operation Schedule. */
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
} SpotGoldMarketOperationScheduleMessage;

/* any Spot Gold Market Operation Schedule Message at all: every byte one the checker chooses */
static void any_spot_gold_market_operation_schedule_message(SpotGoldMarketOperationScheduleMessage *record) {
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

/* Spot Gold Market Operation Schedule Message to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_spot_gold_market_operation_schedule_message(const SpotGoldMarketOperationScheduleMessage *record, uint8_t *wire, size_t at) {
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

/* Spot Gold Market Operation Schedule Message off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_spot_gold_market_operation_schedule_message(SpotGoldMarketOperationScheduleMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Spot Gold Market Operation Schedule Message is what was written, byte for byte */
static void equal_spot_gold_market_operation_schedule_message(const SpotGoldMarketOperationScheduleMessage *read, const SpotGoldMarketOperationScheduleMessage *written) {
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

/* Spot Gold Market Operation Schedule Message: written and read back, then read and written back */
static void check_spot_gold_market_operation_schedule_message(void) {
  SpotGoldMarketOperationScheduleMessage sent;
  SpotGoldMarketOperationScheduleMessage got;
  uint8_t wire[78];
  uint8_t again[78];

  any_spot_gold_market_operation_schedule_message(&sent);
  assert(encode_spot_gold_market_operation_schedule_message(&sent, wire, 0) == 78);
  assert(decode_spot_gold_market_operation_schedule_message(&got, wire, 0) == 78);
  equal_spot_gold_market_operation_schedule_message(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_spot_gold_market_operation_schedule_message(&got, wire, 0) == 78);
  assert(encode_spot_gold_market_operation_schedule_message(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Emissions Market Operation Ts Message: 63 bytes ------------------------- */

/* Emissions Market Operation TS. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t session_id[2];                          /* bytes 10 to 11 */
  uint8_t isin_code[12];                          /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue[6];    /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 30 to 41 */
  uint8_t board_event_id[3];                      /* bytes 42 to 44 */
  uint8_t start_time_of_a_board_event[9];         /* bytes 45 to 53 */
  uint8_t board_event_group_code[5];              /* bytes 54 to 58 */
  uint8_t trading_halt_reason_code[3];            /* bytes 59 to 61 */
  uint8_t end_keyword;                            /* byte 62 */
} EmissionsMarketOperationTsMessage;

/* any Emissions Market Operation Ts Message at all: every byte one the checker chooses */
static void any_emissions_market_operation_ts_message(EmissionsMarketOperationTsMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Emissions Market Operation Ts Message to the wire: 63 bytes from at, returning where the next byte goes */
static size_t encode_emissions_market_operation_ts_message(const EmissionsMarketOperationTsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->board_event_id[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->start_time_of_a_board_event[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->board_event_group_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_halt_reason_code[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Emissions Market Operation Ts Message off the wire: 63 bytes from at, returning where the next byte lies */
static size_t decode_emissions_market_operation_ts_message(EmissionsMarketOperationTsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->start_time_of_a_board_event[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trading_halt_reason_code[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Emissions Market Operation Ts Message is what was written, byte for byte */
static void equal_emissions_market_operation_ts_message(const EmissionsMarketOperationTsMessage *read, const EmissionsMarketOperationTsMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->board_event_id[i] == written->board_event_id[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->start_time_of_a_board_event[i] == written->start_time_of_a_board_event[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->board_event_group_code[i] == written->board_event_group_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trading_halt_reason_code[i] == written->trading_halt_reason_code[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Emissions Market Operation Ts Message: written and read back, then read and written back */
static void check_emissions_market_operation_ts_message(void) {
  EmissionsMarketOperationTsMessage sent;
  EmissionsMarketOperationTsMessage got;
  uint8_t wire[63];
  uint8_t again[63];

  any_emissions_market_operation_ts_message(&sent);
  assert(encode_emissions_market_operation_ts_message(&sent, wire, 0) == 63);
  assert(decode_emissions_market_operation_ts_message(&got, wire, 0) == 63);
  equal_emissions_market_operation_ts_message(&got, &sent);

  for (size_t i = 0; i < 63; i++) { wire[i] = arbitrary(); }
  assert(decode_emissions_market_operation_ts_message(&got, wire, 0) == 63);
  assert(encode_emissions_market_operation_ts_message(&got, again, 0) == 63);
  for (size_t i = 0; i < 63; i++) { assert(again[i] == wire[i]); }
}

/* ---- Emissions Issue Closing Message: 107 bytes ------------------------------ */

/* Emissions Issue Closing. */
typedef struct {
  uint8_t message_sequence_number[8];                      /* bytes 0 to 7 */
  uint8_t board_id[2];                                     /* bytes 8 to 9 */
  uint8_t isin_code[12];                                   /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];             /* bytes 22 to 27 */
  uint8_t closing_price_long[11];                          /* bytes 28 to 38 */
  uint8_t closing_price_type_code;                         /* byte 39 */
  uint8_t filler_11[11];                                   /* bytes 40 to 50 */
  uint8_t second_filler_11[11];                            /* bytes 51 to 61 */
  uint8_t closing_price_weighted_stock_price_average[11];  /* bytes 62 to 72 */
  uint8_t closing_price_base_price_of_buy_in[11];          /* bytes 73 to 83 */
  uint8_t closing_price_upper_limit_of_buy_in[11];         /* bytes 84 to 94 */
  uint8_t closing_price_lower_limit_of_buy_in[11];         /* bytes 95 to 105 */
  uint8_t end_keyword;                                     /* byte 106 */
} EmissionsIssueClosingMessage;

/* any Emissions Issue Closing Message at all: every byte one the checker chooses */
static void any_emissions_issue_closing_message(EmissionsIssueClosingMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_long[i] = arbitrary(); }
  record->closing_price_type_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->filler_11[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->second_filler_11[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_weighted_stock_price_average[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_base_price_of_buy_in[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_upper_limit_of_buy_in[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_lower_limit_of_buy_in[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Emissions Issue Closing Message to the wire: 107 bytes from at, returning where the next byte goes */
static size_t encode_emissions_issue_closing_message(const EmissionsIssueClosingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_long[i]; }
  wire[at++] = record->closing_price_type_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->filler_11[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->second_filler_11[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_weighted_stock_price_average[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_base_price_of_buy_in[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_upper_limit_of_buy_in[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_lower_limit_of_buy_in[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Emissions Issue Closing Message off the wire: 107 bytes from at, returning where the next byte lies */
static size_t decode_emissions_issue_closing_message(EmissionsIssueClosingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_long[i] = wire[at++]; }
  record->closing_price_type_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->filler_11[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->second_filler_11[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_weighted_stock_price_average[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_base_price_of_buy_in[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_upper_limit_of_buy_in[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_lower_limit_of_buy_in[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Emissions Issue Closing Message is what was written, byte for byte */
static void equal_emissions_issue_closing_message(const EmissionsIssueClosingMessage *read, const EmissionsIssueClosingMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_long[i] == written->closing_price_long[i]); }
  assert(read->closing_price_type_code == written->closing_price_type_code);
  for (size_t i = 0; i < 11; i++) { assert(read->filler_11[i] == written->filler_11[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->second_filler_11[i] == written->second_filler_11[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_weighted_stock_price_average[i] == written->closing_price_weighted_stock_price_average[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_base_price_of_buy_in[i] == written->closing_price_base_price_of_buy_in[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_upper_limit_of_buy_in[i] == written->closing_price_upper_limit_of_buy_in[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_lower_limit_of_buy_in[i] == written->closing_price_lower_limit_of_buy_in[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Emissions Issue Closing Message: written and read back, then read and written back */
static void check_emissions_issue_closing_message(void) {
  EmissionsIssueClosingMessage sent;
  EmissionsIssueClosingMessage got;
  uint8_t wire[107];
  uint8_t again[107];

  any_emissions_issue_closing_message(&sent);
  assert(encode_emissions_issue_closing_message(&sent, wire, 0) == 107);
  assert(decode_emissions_issue_closing_message(&got, wire, 0) == 107);
  equal_emissions_issue_closing_message(&got, &sent);

  for (size_t i = 0; i < 107; i++) { wire[i] = arbitrary(); }
  assert(decode_emissions_issue_closing_message(&got, wire, 0) == 107);
  assert(encode_emissions_issue_closing_message(&got, again, 0) == 107);
  for (size_t i = 0; i < 107; i++) { assert(again[i] == wire[i]); }
}

/* ---- Emissions Market Operation Schedule Message: 78 bytes ------------------- */

/* Emissions Market Operation Schedule. */
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
} EmissionsMarketOperationScheduleMessage;

/* any Emissions Market Operation Schedule Message at all: every byte one the checker chooses */
static void any_emissions_market_operation_schedule_message(EmissionsMarketOperationScheduleMessage *record) {
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

/* Emissions Market Operation Schedule Message to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_emissions_market_operation_schedule_message(const EmissionsMarketOperationScheduleMessage *record, uint8_t *wire, size_t at) {
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

/* Emissions Market Operation Schedule Message off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_emissions_market_operation_schedule_message(EmissionsMarketOperationScheduleMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Emissions Market Operation Schedule Message is what was written, byte for byte */
static void equal_emissions_market_operation_schedule_message(const EmissionsMarketOperationScheduleMessage *read, const EmissionsMarketOperationScheduleMessage *written) {
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

/* Emissions Market Operation Schedule Message: written and read back, then read and written back */
static void check_emissions_market_operation_schedule_message(void) {
  EmissionsMarketOperationScheduleMessage sent;
  EmissionsMarketOperationScheduleMessage got;
  uint8_t wire[78];
  uint8_t again[78];

  any_emissions_market_operation_schedule_message(&sent);
  assert(encode_emissions_market_operation_schedule_message(&sent, wire, 0) == 78);
  assert(decode_emissions_market_operation_schedule_message(&got, wire, 0) == 78);
  equal_emissions_market_operation_schedule_message(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_emissions_market_operation_schedule_message(&got, wire, 0) == 78);
  assert(encode_emissions_market_operation_schedule_message(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spot Gold Random End Message: 30 bytes ---------------------------------- */

/* Spot Gold Random End. Reports random extension of the call auction window when conditional random-end is triggered. */
typedef struct {
  uint8_t message_sequence_number[8];           /* bytes 0 to 7 */
  uint8_t board_id[2];                          /* bytes 8 to 9 */
  uint8_t isin_code[12];                        /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 22 to 27 */
  uint8_t random_end_trigger_code;              /* byte 28 */
  uint8_t end_keyword;                          /* byte 29 */
} SpotGoldRandomEndMessage;

/* any Spot Gold Random End Message at all: every byte one the checker chooses */
static void any_spot_gold_random_end_message(SpotGoldRandomEndMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  record->random_end_trigger_code = arbitrary();
  record->end_keyword = arbitrary();
}

/* Spot Gold Random End Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_spot_gold_random_end_message(const SpotGoldRandomEndMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  wire[at++] = record->random_end_trigger_code;
  wire[at++] = record->end_keyword;

  return at;
}

/* Spot Gold Random End Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_spot_gold_random_end_message(SpotGoldRandomEndMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  record->random_end_trigger_code = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Spot Gold Random End Message is what was written, byte for byte */
static void equal_spot_gold_random_end_message(const SpotGoldRandomEndMessage *read, const SpotGoldRandomEndMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  assert(read->random_end_trigger_code == written->random_end_trigger_code);
  assert(read->end_keyword == written->end_keyword);
}

/* Spot Gold Random End Message: written and read back, then read and written back */
static void check_spot_gold_random_end_message(void) {
  SpotGoldRandomEndMessage sent;
  SpotGoldRandomEndMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_spot_gold_random_end_message(&sent);
  assert(encode_spot_gold_random_end_message(&sent, wire, 0) == 30);
  assert(decode_spot_gold_random_end_message(&got, wire, 0) == 30);
  equal_spot_gold_random_end_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_spot_gold_random_end_message(&got, wire, 0) == 30);
  assert(encode_spot_gold_random_end_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_polling_data_message();
  check_krx_index_message();
  check_krx_estimated_index_message();
  check_global_index_message();
  check_bond_prime_index_message();
  check_bond_ktb_index_message();
  check_bond_ktb_index_term_structure_message();
  check_bond_index_krx_message();
  check_spot_gold_quote_message();
  check_spot_gold_order_filled_message();
  check_spot_gold_order_filled_plus_quote_message();
  check_spot_gold_market_operation_ts_plus_quote_message();
  check_spot_gold_snapshot_message();
  check_spot_gold_negotiated_trade_message();
  check_emissions_quote_message();
  check_emissions_order_filled_message();
  check_emissions_order_filled_plus_quote_message();
  check_emissions_market_operation_ts_plus_quote_message();
  check_emissions_snapshot_message();
  check_emissions_negotiated_trade_message();
  check_emissions_determination_of_base_price_message();
  check_emissions_auction_results_message();
  check_spot_gold_batch_data_message();
  check_emissions_batch_data_message();
  check_external_gold_spot_closing_price_message();
  check_spot_gold_market_operation_ts_message();
  check_spot_gold_issue_closing_message();
  check_spot_gold_market_operation_schedule_message();
  check_emissions_market_operation_ts_message();
  check_emissions_issue_closing_message();
  check_emissions_market_operation_schedule_message();
  check_spot_gold_random_end_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
