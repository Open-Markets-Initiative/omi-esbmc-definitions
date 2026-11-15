// koscom/mdcsrealtime/referenceinfoinvestoractivities/Koscom_MdcsRealtime_ReferenceInfoInvestorActivities_v2_020.c
/*
 * Koscom Co., Ltd. MDCS Realtime Reference Info and Investor Activities
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
  uint8_t accumulated_trading_value[12];               /* bytes 55 to 66 */
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
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_value[i] = arbitrary(); }
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
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_value[i]; }
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
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_value[i] = wire[at++]; }
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
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_value[i] == written->accumulated_trading_value[i]); }
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
  uint8_t accumulated_trading_value[12];               /* bytes 55 to 66 */
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
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_value[i] = arbitrary(); }
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
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_value[i]; }
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
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_value[i] = wire[at++]; }
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
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_value[i] == written->accumulated_trading_value[i]); }
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
  uint8_t currency_code[3];                            /* bytes 51 to 53 */
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
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = arbitrary(); }
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
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency_code[i]; }
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
  for (size_t i = 0; i < 3; i++) { record->currency_code[i] = wire[at++]; }
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
  for (size_t i = 0; i < 3; i++) { assert(read->currency_code[i] == written->currency_code[i]); }
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

/* ---- Securities Investor Activities Per Industry Message: 100 bytes ---------- */

/* Investor Activities per Industry. Aggregated bid/ask volumes and values per investor category and industry. */
typedef struct {
  uint8_t calculation_time[6];                 /* bytes 0 to 5 */
  uint8_t investor_code[4];                    /* bytes 6 to 9 */
  uint8_t index_id[6];                         /* bytes 10 to 15 */
  uint8_t isin_code[12];                       /* bytes 16 to 27 */
  uint8_t accumulated_ask_trading_volume[12];  /* bytes 28 to 39 */
  uint8_t accumulated_ask_trading_value[22];   /* bytes 40 to 61 */
  uint8_t accumulated_bid_trading_volume[12];  /* bytes 62 to 73 */
  uint8_t accumulated_bid_trading_value[22];   /* bytes 74 to 95 */
  uint8_t filler_3[3];                         /* bytes 96 to 98 */
  uint8_t end_keyword;                         /* byte 99 */
} SecuritiesInvestorActivitiesPerIndustryMessage;

/* any Securities Investor Activities Per Industry Message at all: every byte one the checker chooses */
static void any_securities_investor_activities_per_industry_message(SecuritiesInvestorActivitiesPerIndustryMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->calculation_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_ask_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_ask_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_bid_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_bid_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Investor Activities Per Industry Message to the wire: 100 bytes from at, returning where the next byte goes */
static size_t encode_securities_investor_activities_per_industry_message(const SecuritiesInvestorActivitiesPerIndustryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->calculation_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->investor_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_ask_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_ask_trading_value[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_bid_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_bid_trading_value[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Investor Activities Per Industry Message off the wire: 100 bytes from at, returning where the next byte lies */
static size_t decode_securities_investor_activities_per_industry_message(SecuritiesInvestorActivitiesPerIndustryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->calculation_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_ask_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_ask_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_bid_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_bid_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Investor Activities Per Industry Message is what was written, byte for byte */
static void equal_securities_investor_activities_per_industry_message(const SecuritiesInvestorActivitiesPerIndustryMessage *read, const SecuritiesInvestorActivitiesPerIndustryMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->calculation_time[i] == written->calculation_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->investor_code[i] == written->investor_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_ask_trading_volume[i] == written->accumulated_ask_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_ask_trading_value[i] == written->accumulated_ask_trading_value[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_bid_trading_volume[i] == written->accumulated_bid_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_bid_trading_value[i] == written->accumulated_bid_trading_value[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Investor Activities Per Industry Message: written and read back, then read and written back */
static void check_securities_investor_activities_per_industry_message(void) {
  SecuritiesInvestorActivitiesPerIndustryMessage sent;
  SecuritiesInvestorActivitiesPerIndustryMessage got;
  uint8_t wire[100];
  uint8_t again[100];

  any_securities_investor_activities_per_industry_message(&sent);
  assert(encode_securities_investor_activities_per_industry_message(&sent, wire, 0) == 100);
  assert(decode_securities_investor_activities_per_industry_message(&got, wire, 0) == 100);
  equal_securities_investor_activities_per_industry_message(&got, &sent);

  for (size_t i = 0; i < 100; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_investor_activities_per_industry_message(&got, wire, 0) == 100);
  assert(encode_securities_investor_activities_per_industry_message(&got, again, 0) == 100);
  for (size_t i = 0; i < 100; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Investor Activities Per Issue Eod Message: 91 bytes ---------- */

/* Investor Activities per Issue EOD. Aggregated bid/ask volumes and values per investor category and ISIN at end-of-day. */
typedef struct {
  uint8_t isin_code[12];                        /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 12 to 17 */
  uint8_t investor_code[4];                     /* bytes 18 to 21 */
  uint8_t accumulated_ask_trading_volume[12];   /* bytes 22 to 33 */
  uint8_t accumulated_ask_trading_value[22];    /* bytes 34 to 55 */
  uint8_t accumulated_bid_trading_volume[12];   /* bytes 56 to 67 */
  uint8_t accumulated_bid_trading_value[22];    /* bytes 68 to 89 */
  uint8_t end_keyword;                          /* byte 90 */
} SecuritiesInvestorActivitiesPerIssueEodMessage;

/* any Securities Investor Activities Per Issue Eod Message at all: every byte one the checker chooses */
static void any_securities_investor_activities_per_issue_eod_message(SecuritiesInvestorActivitiesPerIssueEodMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_ask_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_ask_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_bid_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_bid_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Investor Activities Per Issue Eod Message to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_securities_investor_activities_per_issue_eod_message(const SecuritiesInvestorActivitiesPerIssueEodMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->investor_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_ask_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_ask_trading_value[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_bid_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_bid_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Investor Activities Per Issue Eod Message off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_securities_investor_activities_per_issue_eod_message(SecuritiesInvestorActivitiesPerIssueEodMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_ask_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_ask_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_bid_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_bid_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Investor Activities Per Issue Eod Message is what was written, byte for byte */
static void equal_securities_investor_activities_per_issue_eod_message(const SecuritiesInvestorActivitiesPerIssueEodMessage *read, const SecuritiesInvestorActivitiesPerIssueEodMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->investor_code[i] == written->investor_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_ask_trading_volume[i] == written->accumulated_ask_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_ask_trading_value[i] == written->accumulated_ask_trading_value[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_bid_trading_volume[i] == written->accumulated_bid_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_bid_trading_value[i] == written->accumulated_bid_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Investor Activities Per Issue Eod Message: written and read back, then read and written back */
static void check_securities_investor_activities_per_issue_eod_message(void) {
  SecuritiesInvestorActivitiesPerIssueEodMessage sent;
  SecuritiesInvestorActivitiesPerIssueEodMessage got;
  uint8_t wire[91];
  uint8_t again[91];

  any_securities_investor_activities_per_issue_eod_message(&sent);
  assert(encode_securities_investor_activities_per_issue_eod_message(&sent, wire, 0) == 91);
  assert(decode_securities_investor_activities_per_issue_eod_message(&got, wire, 0) == 91);
  equal_securities_investor_activities_per_issue_eod_message(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_investor_activities_per_issue_eod_message(&got, wire, 0) == 91);
  assert(encode_securities_investor_activities_per_issue_eod_message(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Investor Activities Per Commodities Message: 79 bytes -------- */

/* Investor Activities per Commodities. */
typedef struct {
  uint8_t calculation_time[6];                 /* bytes 0 to 5 */
  uint8_t investor_code[4];                    /* bytes 6 to 9 */
  uint8_t accumulated_ask_trading_volume[12];  /* bytes 10 to 21 */
  uint8_t accumulated_ask_trading_value[22];   /* bytes 22 to 43 */
  uint8_t accumulated_bid_trading_volume[12];  /* bytes 44 to 55 */
  uint8_t accumulated_bid_trading_value[22];   /* bytes 56 to 77 */
  uint8_t end_keyword;                         /* byte 78 */
} SecuritiesInvestorActivitiesPerCommoditiesMessage;

/* any Securities Investor Activities Per Commodities Message at all: every byte one the checker chooses */
static void any_securities_investor_activities_per_commodities_message(SecuritiesInvestorActivitiesPerCommoditiesMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->calculation_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_ask_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_ask_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_bid_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_bid_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Investor Activities Per Commodities Message to the wire: 79 bytes from at, returning where the next byte goes */
static size_t encode_securities_investor_activities_per_commodities_message(const SecuritiesInvestorActivitiesPerCommoditiesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->calculation_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->investor_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_ask_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_ask_trading_value[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_bid_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_bid_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Investor Activities Per Commodities Message off the wire: 79 bytes from at, returning where the next byte lies */
static size_t decode_securities_investor_activities_per_commodities_message(SecuritiesInvestorActivitiesPerCommoditiesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->calculation_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_ask_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_ask_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_bid_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_bid_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Investor Activities Per Commodities Message is what was written, byte for byte */
static void equal_securities_investor_activities_per_commodities_message(const SecuritiesInvestorActivitiesPerCommoditiesMessage *read, const SecuritiesInvestorActivitiesPerCommoditiesMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->calculation_time[i] == written->calculation_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->investor_code[i] == written->investor_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_ask_trading_volume[i] == written->accumulated_ask_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_ask_trading_value[i] == written->accumulated_ask_trading_value[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_bid_trading_volume[i] == written->accumulated_bid_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_bid_trading_value[i] == written->accumulated_bid_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Investor Activities Per Commodities Message: written and read back, then read and written back */
static void check_securities_investor_activities_per_commodities_message(void) {
  SecuritiesInvestorActivitiesPerCommoditiesMessage sent;
  SecuritiesInvestorActivitiesPerCommoditiesMessage got;
  uint8_t wire[79];
  uint8_t again[79];

  any_securities_investor_activities_per_commodities_message(&sent);
  assert(encode_securities_investor_activities_per_commodities_message(&sent, wire, 0) == 79);
  assert(decode_securities_investor_activities_per_commodities_message(&got, wire, 0) == 79);
  equal_securities_investor_activities_per_commodities_message(&got, &sent);

  for (size_t i = 0; i < 79; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_investor_activities_per_commodities_message(&got, wire, 0) == 79);
  assert(encode_securities_investor_activities_per_commodities_message(&got, again, 0) == 79);
  for (size_t i = 0; i < 79; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Short Selling Message: 115 bytes ----------------------------- */

/* Short Selling activity per issue. */
typedef struct {
  uint8_t isin_code[12];                                                   /* bytes 0 to 11 */
  uint8_t covered_short_selling_trading_volume[12];                        /* bytes 12 to 23 */
  uint8_t covered_short_selling_trading_value[22];                         /* bytes 24 to 45 */
  uint8_t uptick_rule_applied_covered_short_selling_trading_volume[12];    /* bytes 46 to 57 */
  uint8_t uptick_rule_applied_covered_short_selling_trading_value[22];     /* bytes 58 to 79 */
  uint8_t uptick_rule_unapplied_covered_short_selling_trading_volume[12];  /* bytes 80 to 91 */
  uint8_t uptick_rule_unapplied_covered_short_selling_trading_value[22];   /* bytes 92 to 113 */
  uint8_t end_keyword;                                                     /* byte 114 */
} SecuritiesShortSellingMessage;

/* any Securities Short Selling Message at all: every byte one the checker chooses */
static void any_securities_short_selling_message(SecuritiesShortSellingMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->covered_short_selling_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->covered_short_selling_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->uptick_rule_applied_covered_short_selling_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->uptick_rule_applied_covered_short_selling_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->uptick_rule_unapplied_covered_short_selling_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->uptick_rule_unapplied_covered_short_selling_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Short Selling Message to the wire: 115 bytes from at, returning where the next byte goes */
static size_t encode_securities_short_selling_message(const SecuritiesShortSellingMessage *record, uint8_t *wire, size_t at) {
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

/* Securities Short Selling Message off the wire: 115 bytes from at, returning where the next byte lies */
static size_t decode_securities_short_selling_message(SecuritiesShortSellingMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Securities Short Selling Message is what was written, byte for byte */
static void equal_securities_short_selling_message(const SecuritiesShortSellingMessage *read, const SecuritiesShortSellingMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->covered_short_selling_trading_volume[i] == written->covered_short_selling_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->covered_short_selling_trading_value[i] == written->covered_short_selling_trading_value[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->uptick_rule_applied_covered_short_selling_trading_volume[i] == written->uptick_rule_applied_covered_short_selling_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->uptick_rule_applied_covered_short_selling_trading_value[i] == written->uptick_rule_applied_covered_short_selling_trading_value[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->uptick_rule_unapplied_covered_short_selling_trading_volume[i] == written->uptick_rule_unapplied_covered_short_selling_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->uptick_rule_unapplied_covered_short_selling_trading_value[i] == written->uptick_rule_unapplied_covered_short_selling_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Short Selling Message: written and read back, then read and written back */
static void check_securities_short_selling_message(void) {
  SecuritiesShortSellingMessage sent;
  SecuritiesShortSellingMessage got;
  uint8_t wire[115];
  uint8_t again[115];

  any_securities_short_selling_message(&sent);
  assert(encode_securities_short_selling_message(&sent, wire, 0) == 115);
  assert(decode_securities_short_selling_message(&got, wire, 0) == 115);
  equal_securities_short_selling_message(&got, &sent);

  for (size_t i = 0; i < 115; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_short_selling_message(&got, wire, 0) == 115);
  assert(encode_securities_short_selling_message(&got, again, 0) == 115);
  for (size_t i = 0; i < 115; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Treasury Stocks Traded Message: 52 bytes --------------------- */

/* Treasury Stocks Traded Information. Real-time treasury-stock trade dissemination per issue. */
typedef struct {
  uint8_t session_id[2];                         /* bytes 0 to 1 */
  uint8_t isin_code[12];                         /* bytes 2 to 13 */
  uint8_t a_designated_number_for_an_issue[6];   /* bytes 14 to 19 */
  uint8_t trading_price[11];                     /* bytes 20 to 30 */
  uint8_t trading_volume[10];                    /* bytes 31 to 40 */
  uint8_t bid_treasury_stock_declaration_id[5];  /* bytes 41 to 45 */
  uint8_t ask_treasury_stock_declaration_id[5];  /* bytes 46 to 50 */
  uint8_t end_keyword;                           /* byte 51 */
} SecuritiesTreasuryStocksTradedMessage;

/* any Securities Treasury Stocks Traded Message at all: every byte one the checker chooses */
static void any_securities_treasury_stocks_traded_message(SecuritiesTreasuryStocksTradedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->bid_treasury_stock_declaration_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->ask_treasury_stock_declaration_id[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Treasury Stocks Traded Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_securities_treasury_stocks_traded_message(const SecuritiesTreasuryStocksTradedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->bid_treasury_stock_declaration_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->ask_treasury_stock_declaration_id[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Treasury Stocks Traded Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_securities_treasury_stocks_traded_message(SecuritiesTreasuryStocksTradedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->bid_treasury_stock_declaration_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->ask_treasury_stock_declaration_id[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Treasury Stocks Traded Message is what was written, byte for byte */
static void equal_securities_treasury_stocks_traded_message(const SecuritiesTreasuryStocksTradedMessage *read, const SecuritiesTreasuryStocksTradedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->bid_treasury_stock_declaration_id[i] == written->bid_treasury_stock_declaration_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->ask_treasury_stock_declaration_id[i] == written->ask_treasury_stock_declaration_id[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Treasury Stocks Traded Message: written and read back, then read and written back */
static void check_securities_treasury_stocks_traded_message(void) {
  SecuritiesTreasuryStocksTradedMessage sent;
  SecuritiesTreasuryStocksTradedMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_securities_treasury_stocks_traded_message(&sent);
  assert(encode_securities_treasury_stocks_traded_message(&sent, wire, 0) == 52);
  assert(decode_securities_treasury_stocks_traded_message(&got, wire, 0) == 52);
  equal_securities_treasury_stocks_traded_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_treasury_stocks_traded_message(&got, wire, 0) == 52);
  assert(encode_securities_treasury_stocks_traded_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Buy In Volume Message: 47 bytes ------------------------------ */

/* Buy-in Volume reference. */
typedef struct {
  uint8_t message_sequence_number[8];  /* bytes 0 to 7 */
  uint8_t isin_code[12];               /* bytes 8 to 19 */
  uint8_t transmission_date[8];        /* bytes 20 to 27 */
  uint8_t buy_in_type_code;            /* byte 28 */
  uint8_t security_group_id[2];        /* bytes 29 to 30 */
  uint8_t buy_in_volume[15];           /* bytes 31 to 45 */
  uint8_t end_keyword;                 /* byte 46 */
} SecuritiesBuyInVolumeMessage;

/* any Securities Buy In Volume Message at all: every byte one the checker chooses */
static void any_securities_buy_in_volume_message(SecuritiesBuyInVolumeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transmission_date[i] = arbitrary(); }
  record->buy_in_type_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->security_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->buy_in_volume[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Buy In Volume Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_securities_buy_in_volume_message(const SecuritiesBuyInVolumeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transmission_date[i]; }
  wire[at++] = record->buy_in_type_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_group_id[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->buy_in_volume[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Buy In Volume Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_securities_buy_in_volume_message(SecuritiesBuyInVolumeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transmission_date[i] = wire[at++]; }
  record->buy_in_type_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->security_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->buy_in_volume[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Buy In Volume Message is what was written, byte for byte */
static void equal_securities_buy_in_volume_message(const SecuritiesBuyInVolumeMessage *read, const SecuritiesBuyInVolumeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transmission_date[i] == written->transmission_date[i]); }
  assert(read->buy_in_type_code == written->buy_in_type_code);
  for (size_t i = 0; i < 2; i++) { assert(read->security_group_id[i] == written->security_group_id[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->buy_in_volume[i] == written->buy_in_volume[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Buy In Volume Message: written and read back, then read and written back */
static void check_securities_buy_in_volume_message(void) {
  SecuritiesBuyInVolumeMessage sent;
  SecuritiesBuyInVolumeMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_securities_buy_in_volume_message(&sent);
  assert(encode_securities_buy_in_volume_message(&sent, wire, 0) == 47);
  assert(decode_securities_buy_in_volume_message(&got, wire, 0) == 47);
  equal_securities_buy_in_volume_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_buy_in_volume_message(&got, wire, 0) == 47);
  assert(encode_securities_buy_in_volume_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
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
  check_securities_investor_activities_per_industry_message();
  check_securities_investor_activities_per_issue_eod_message();
  check_securities_investor_activities_per_commodities_message();
  check_securities_short_selling_message();
  check_securities_treasury_stocks_traded_message();
  check_securities_buy_in_volume_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
