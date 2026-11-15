// koscom/mdcsrealtime/bonda/Koscom_MdcsRealtime_BondA_v2_018.c
/*
 * Koscom Co., Ltd. MDCS Realtime Bond A
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
  uint8_t calculation_time_short[6];                   /* bytes 18 to 23 */
  uint8_t index[9];                                    /* bytes 24 to 32 */
  uint8_t index_change_sign_against_the_previous_day;  /* byte 33 */
  uint8_t index_change_against_the_previous_day[9];    /* bytes 34 to 42 */
  uint8_t accumulated_trading_volume_short[12];        /* bytes 43 to 54 */
  uint8_t accumulated_trading_value_short[12];         /* bytes 55 to 66 */
  uint8_t filler_4[4];                                 /* bytes 67 to 70 */
  uint8_t end_keyword;                                 /* byte 71 */
} KrxIndexMessage;

/* any Krx Index Message at all: every byte one the checker chooses */
static void any_krx_index_message(KrxIndexMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->calculation_time_short[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->index[i] = arbitrary(); }
  record->index_change_sign_against_the_previous_day = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->index_change_against_the_previous_day[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume_short[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_value_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Krx Index Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_krx_index_message(const KrxIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->calculation_time_short[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index[i]; }
  wire[at++] = record->index_change_sign_against_the_previous_day;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index_change_against_the_previous_day[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume_short[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_value_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Krx Index Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_krx_index_message(KrxIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->calculation_time_short[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->index[i] = wire[at++]; }
  record->index_change_sign_against_the_previous_day = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->index_change_against_the_previous_day[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume_short[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_value_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Krx Index Message is what was written, byte for byte */
static void equal_krx_index_message(const KrxIndexMessage *read, const KrxIndexMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->calculation_time_short[i] == written->calculation_time_short[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->index[i] == written->index[i]); }
  assert(read->index_change_sign_against_the_previous_day == written->index_change_sign_against_the_previous_day);
  for (size_t i = 0; i < 9; i++) { assert(read->index_change_against_the_previous_day[i] == written->index_change_against_the_previous_day[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume_short[i] == written->accumulated_trading_volume_short[i]); }
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
  uint8_t calculation_time_short[6];                   /* bytes 18 to 23 */
  uint8_t index[9];                                    /* bytes 24 to 32 */
  uint8_t index_change_sign_against_the_previous_day;  /* byte 33 */
  uint8_t index_change_against_the_previous_day[9];    /* bytes 34 to 42 */
  uint8_t accumulated_trading_volume_short[12];        /* bytes 43 to 54 */
  uint8_t accumulated_trading_value_short[12];         /* bytes 55 to 66 */
  uint8_t filler_4[4];                                 /* bytes 67 to 70 */
  uint8_t end_keyword;                                 /* byte 71 */
} KrxEstimatedIndexMessage;

/* any Krx Estimated Index Message at all: every byte one the checker chooses */
static void any_krx_estimated_index_message(KrxEstimatedIndexMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->calculation_time_short[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->index[i] = arbitrary(); }
  record->index_change_sign_against_the_previous_day = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->index_change_against_the_previous_day[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume_short[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_value_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Krx Estimated Index Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_krx_estimated_index_message(const KrxEstimatedIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->calculation_time_short[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index[i]; }
  wire[at++] = record->index_change_sign_against_the_previous_day;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index_change_against_the_previous_day[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume_short[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_value_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Krx Estimated Index Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_krx_estimated_index_message(KrxEstimatedIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->calculation_time_short[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->index[i] = wire[at++]; }
  record->index_change_sign_against_the_previous_day = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->index_change_against_the_previous_day[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume_short[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_value_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Krx Estimated Index Message is what was written, byte for byte */
static void equal_krx_estimated_index_message(const KrxEstimatedIndexMessage *read, const KrxEstimatedIndexMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->calculation_time_short[i] == written->calculation_time_short[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->index[i] == written->index[i]); }
  assert(read->index_change_sign_against_the_previous_day == written->index_change_sign_against_the_previous_day);
  for (size_t i = 0; i < 9; i++) { assert(read->index_change_against_the_previous_day[i] == written->index_change_against_the_previous_day[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume_short[i] == written->accumulated_trading_volume_short[i]); }
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
  uint8_t calculation_time_short[6];                   /* bytes 26 to 31 */
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
  for (size_t i = 0; i < 6; i++) { record->calculation_time_short[i] = arbitrary(); }
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
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->calculation_time_short[i]; }
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
  for (size_t i = 0; i < 6; i++) { record->calculation_time_short[i] = wire[at++]; }
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
  for (size_t i = 0; i < 6; i++) { assert(read->calculation_time_short[i] == written->calculation_time_short[i]); }
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
  uint8_t transmission_time_short[8];                                  /* bytes 168 to 175 */
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
  for (size_t i = 0; i < 8; i++) { record->transmission_time_short[i] = arbitrary(); }
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
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transmission_time_short[i]; }
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
  for (size_t i = 0; i < 8; i++) { record->transmission_time_short[i] = wire[at++]; }
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
  for (size_t i = 0; i < 8; i++) { assert(read->transmission_time_short[i] == written->transmission_time_short[i]); }
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

/* ---- Market Operation Ts Message: 63 bytes ----------------------------------- */

/* Market Operation TS. Reports per-issue when a Market Operation event occurs (halts, resumes, expirations). Information Category byte 3 selects market (K=KTB, B=Bonds, M=Baby Bonds, R=REPO, S=KOSPI, Q=KOSDAQ, X=KONEX, G=Gold, E=Emissions, F=Derivatives). */
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
} MarketOperationTsMessage;

/* any Market Operation Ts Message at all: every byte one the checker chooses */
static void any_market_operation_ts_message(MarketOperationTsMessage *record) {
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

/* Market Operation Ts Message to the wire: 63 bytes from at, returning where the next byte goes */
static size_t encode_market_operation_ts_message(const MarketOperationTsMessage *record, uint8_t *wire, size_t at) {
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

/* Market Operation Ts Message off the wire: 63 bytes from at, returning where the next byte lies */
static size_t decode_market_operation_ts_message(MarketOperationTsMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Market Operation Ts Message is what was written, byte for byte */
static void equal_market_operation_ts_message(const MarketOperationTsMessage *read, const MarketOperationTsMessage *written) {
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

/* ---- Market Operation Schedule Message: 78 bytes ----------------------------- */

/* Market Operation Schedule. Reports session-level schedule and configuration changes. */
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

/* ---- Issue Closing Message: 52 bytes ----------------------------------------- */

/* Bonds Issue Closing. Reports per-issue closing event with closing price. */
typedef struct {
  uint8_t message_sequence_number[8];  /* bytes 0 to 7 */
  uint8_t board_id[2];                 /* bytes 8 to 9 */
  uint8_t isin_code[12];               /* bytes 10 to 21 */
  uint8_t duration_of_term_repo[4];    /* bytes 22 to 25 */
  uint8_t closing_price[11];           /* bytes 26 to 36 */
  uint8_t closing_price_yield[13];     /* bytes 37 to 49 */
  uint8_t closing_price_type_code;     /* byte 50 */
  uint8_t end_keyword;                 /* byte 51 */
} IssueClosingMessage;

/* any Issue Closing Message at all: every byte one the checker chooses */
static void any_issue_closing_message(IssueClosingMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->duration_of_term_repo[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->closing_price_yield[i] = arbitrary(); }
  record->closing_price_type_code = arbitrary();
  record->end_keyword = arbitrary();
}

/* Issue Closing Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_issue_closing_message(const IssueClosingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->duration_of_term_repo[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->closing_price_yield[i]; }
  wire[at++] = record->closing_price_type_code;
  wire[at++] = record->end_keyword;

  return at;
}

/* Issue Closing Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_issue_closing_message(IssueClosingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->duration_of_term_repo[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->closing_price_yield[i] = wire[at++]; }
  record->closing_price_type_code = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Issue Closing Message is what was written, byte for byte */
static void equal_issue_closing_message(const IssueClosingMessage *read, const IssueClosingMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->duration_of_term_repo[i] == written->duration_of_term_repo[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->closing_price_yield[i] == written->closing_price_yield[i]); }
  assert(read->closing_price_type_code == written->closing_price_type_code);
  assert(read->end_keyword == written->end_keyword);
}

/* Issue Closing Message: written and read back, then read and written back */
static void check_issue_closing_message(void) {
  IssueClosingMessage sent;
  IssueClosingMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_issue_closing_message(&sent);
  assert(encode_issue_closing_message(&sent, wire, 0) == 52);
  assert(decode_issue_closing_message(&got, wire, 0) == 52);
  equal_issue_closing_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_issue_closing_message(&got, wire, 0) == 52);
  assert(encode_issue_closing_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Member Firm Sanctions Message: 41 bytes --------------------------------- */

/* Member firm imposing/lifting of sanctions. Information Category byte 3 selects market. */
typedef struct {
  uint8_t isin_code[12];                             /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue[6];       /* bytes 12 to 17 */
  uint8_t disclosing_data_type_code[3];              /* bytes 18 to 20 */
  uint8_t disclosure_time[9];                        /* bytes 21 to 29 */
  uint8_t member_number[5];                          /* bytes 30 to 34 */
  uint8_t member_firm_trust_principal_type_code[5];  /* bytes 35 to 39 */
  uint8_t end_keyword;                               /* byte 40 */
} MemberFirmSanctionsMessage;

/* any Member Firm Sanctions Message at all: every byte one the checker chooses */
static void any_member_firm_sanctions_message(MemberFirmSanctionsMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->disclosing_data_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->disclosure_time[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_firm_trust_principal_type_code[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Member Firm Sanctions Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_member_firm_sanctions_message(const MemberFirmSanctionsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->disclosing_data_type_code[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->disclosure_time[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_firm_trust_principal_type_code[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Member Firm Sanctions Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_member_firm_sanctions_message(MemberFirmSanctionsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->disclosing_data_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->disclosure_time[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_firm_trust_principal_type_code[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Member Firm Sanctions Message is what was written, byte for byte */
static void equal_member_firm_sanctions_message(const MemberFirmSanctionsMessage *read, const MemberFirmSanctionsMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->disclosing_data_type_code[i] == written->disclosing_data_type_code[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->disclosure_time[i] == written->disclosure_time[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number[i] == written->member_number[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_firm_trust_principal_type_code[i] == written->member_firm_trust_principal_type_code[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Member Firm Sanctions Message: written and read back, then read and written back */
static void check_member_firm_sanctions_message(void) {
  MemberFirmSanctionsMessage sent;
  MemberFirmSanctionsMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_member_firm_sanctions_message(&sent);
  assert(encode_member_firm_sanctions_message(&sent, wire, 0) == 41);
  assert(decode_member_firm_sanctions_message(&got, wire, 0) == 41);
  equal_member_firm_sanctions_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_member_firm_sanctions_message(&got, wire, 0) == 41);
  assert(encode_member_firm_sanctions_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Regular Bonds Ktb Quote Message: 457 bytes ------------------------------ */

/* Regular Bonds and KTB Quote. Multi-level bid/ask quotes and remaining quantities. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t session_id[2];                          /* bytes 10 to 11 */
  uint8_t isin_code[12];                          /* bytes 12 to 23 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 24 to 35 */
  uint8_t ask_level_1_price[11];                  /* bytes 36 to 46 */
  uint8_t bid_level_1_price[11];                  /* bytes 47 to 57 */
  uint8_t ask_level_1_remaining_quantity[15];     /* bytes 58 to 72 */
  uint8_t bid_level_1_remaining_quantity[15];     /* bytes 73 to 87 */
  uint8_t ask_level_1_yield[13];                  /* bytes 88 to 100 */
  uint8_t bid_level_1_yield[13];                  /* bytes 101 to 113 */
  uint8_t ask_level_2_price[11];                  /* bytes 114 to 124 */
  uint8_t bid_level_2_price[11];                  /* bytes 125 to 135 */
  uint8_t ask_level_2_remaining_quantity[15];     /* bytes 136 to 150 */
  uint8_t bid_level_2_remaining_quantity[15];     /* bytes 151 to 165 */
  uint8_t ask_level_2_yield[13];                  /* bytes 166 to 178 */
  uint8_t bid_level_2_yield[13];                  /* bytes 179 to 191 */
  uint8_t ask_level_3_price[11];                  /* bytes 192 to 202 */
  uint8_t bid_level_3_price[11];                  /* bytes 203 to 213 */
  uint8_t ask_level_3_remaining_quantity[15];     /* bytes 214 to 228 */
  uint8_t bid_level_3_remaining_quantity[15];     /* bytes 229 to 243 */
  uint8_t ask_level_3_yield[13];                  /* bytes 244 to 256 */
  uint8_t bid_level_3_yield[13];                  /* bytes 257 to 269 */
  uint8_t ask_level_4_price[11];                  /* bytes 270 to 280 */
  uint8_t bid_level_4_price[11];                  /* bytes 281 to 291 */
  uint8_t ask_level_4_remaining_quantity[15];     /* bytes 292 to 306 */
  uint8_t bid_level_4_remaining_quantity[15];     /* bytes 307 to 321 */
  uint8_t ask_level_4_yield[13];                  /* bytes 322 to 334 */
  uint8_t bid_level_4_yield[13];                  /* bytes 335 to 347 */
  uint8_t ask_level_5_price[11];                  /* bytes 348 to 358 */
  uint8_t bid_level_5_price[11];                  /* bytes 359 to 369 */
  uint8_t ask_level_5_remaining_quantity[15];     /* bytes 370 to 384 */
  uint8_t bid_level_5_remaining_quantity[15];     /* bytes 385 to 399 */
  uint8_t ask_level_5_yield[13];                  /* bytes 400 to 412 */
  uint8_t bid_level_5_yield[13];                  /* bytes 413 to 425 */
  uint8_t ask_total_remaining_quantity[15];       /* bytes 426 to 440 */
  uint8_t bid_total_remaining_quantity[15];       /* bytes 441 to 455 */
  uint8_t end_keyword;                            /* byte 456 */
} RegularBondsKtbQuoteMessage;

/* any Regular Bonds Ktb Quote Message at all: every byte one the checker chooses */
static void any_regular_bonds_ktb_quote_message(RegularBondsKtbQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_1_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_1_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_2_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_2_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_3_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_3_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_4_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_4_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_5_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_5_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_total_remaining_quantity[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Regular Bonds Ktb Quote Message to the wire: 457 bytes from at, returning where the next byte goes */
static size_t encode_regular_bonds_ktb_quote_message(const RegularBondsKtbQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_1_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_1_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_2_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_2_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_3_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_3_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_4_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_4_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_5_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_5_yield[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_total_remaining_quantity[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Regular Bonds Ktb Quote Message off the wire: 457 bytes from at, returning where the next byte lies */
static size_t decode_regular_bonds_ktb_quote_message(RegularBondsKtbQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_1_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_1_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_2_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_2_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_3_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_3_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_4_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_4_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_5_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_5_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_total_remaining_quantity[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Regular Bonds Ktb Quote Message is what was written, byte for byte */
static void equal_regular_bonds_ktb_quote_message(const RegularBondsKtbQuoteMessage *read, const RegularBondsKtbQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_1_remaining_quantity[i] == written->ask_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_1_remaining_quantity[i] == written->bid_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_1_yield[i] == written->ask_level_1_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_1_yield[i] == written->bid_level_1_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_2_remaining_quantity[i] == written->ask_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_2_remaining_quantity[i] == written->bid_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_2_yield[i] == written->ask_level_2_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_2_yield[i] == written->bid_level_2_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_3_remaining_quantity[i] == written->ask_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_3_remaining_quantity[i] == written->bid_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_3_yield[i] == written->ask_level_3_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_3_yield[i] == written->bid_level_3_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_4_remaining_quantity[i] == written->ask_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_4_remaining_quantity[i] == written->bid_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_4_yield[i] == written->ask_level_4_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_4_yield[i] == written->bid_level_4_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_5_remaining_quantity[i] == written->ask_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_5_remaining_quantity[i] == written->bid_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_5_yield[i] == written->ask_level_5_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_5_yield[i] == written->bid_level_5_yield[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_total_remaining_quantity[i] == written->ask_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_total_remaining_quantity[i] == written->bid_total_remaining_quantity[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Regular Bonds Ktb Quote Message: written and read back, then read and written back */
static void check_regular_bonds_ktb_quote_message(void) {
  RegularBondsKtbQuoteMessage sent;
  RegularBondsKtbQuoteMessage got;
  uint8_t wire[457];
  uint8_t again[457];

  any_regular_bonds_ktb_quote_message(&sent);
  assert(encode_regular_bonds_ktb_quote_message(&sent, wire, 0) == 457);
  assert(decode_regular_bonds_ktb_quote_message(&got, wire, 0) == 457);
  equal_regular_bonds_ktb_quote_message(&got, &sent);

  for (size_t i = 0; i < 457; i++) { wire[i] = arbitrary(); }
  assert(decode_regular_bonds_ktb_quote_message(&got, wire, 0) == 457);
  assert(encode_regular_bonds_ktb_quote_message(&got, again, 0) == 457);
  for (size_t i = 0; i < 457; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bonds Order Filled Message: 218 bytes ----------------------------------- */

/* Bonds Order Filled. Trade prints for KTB, Baby Bonds, and General Bonds. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t session_id[2];                          /* bytes 10 to 11 */
  uint8_t isin_code[12];                          /* bytes 12 to 23 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 24 to 35 */
  uint8_t trading_price[11];                      /* bytes 36 to 46 */
  uint8_t trading_volume[10];                     /* bytes 47 to 56 */
  uint8_t trading_date[8];                        /* bytes 57 to 64 */
  uint8_t trading_value[22];                      /* bytes 65 to 86 */
  uint8_t bond_yield[13];                         /* bytes 87 to 99 */
  uint8_t opening_price[11];                      /* bytes 100 to 110 */
  uint8_t todays_high[11];                        /* bytes 111 to 121 */
  uint8_t todays_low[11];                         /* bytes 122 to 132 */
  uint8_t yield_opening_price[13];                /* bytes 133 to 145 */
  uint8_t yield_todays_high[13];                  /* bytes 146 to 158 */
  uint8_t yield_todays_low[13];                   /* bytes 159 to 171 */
  uint8_t accumulated_trading_volume_long[15];    /* bytes 172 to 186 */
  uint8_t accumulated_trading_value_long[22];     /* bytes 187 to 208 */
  uint8_t settlement_date[8];                     /* bytes 209 to 216 */
  uint8_t end_keyword;                            /* byte 217 */
} BondsOrderFilledMessage;

/* any Bonds Order Filled Message at all: every byte one the checker chooses */
static void any_bonds_order_filled_message(BondsOrderFilledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bond_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->yield_opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->yield_todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->yield_todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->accumulated_trading_volume_long[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Bonds Order Filled Message to the wire: 218 bytes from at, returning where the next byte goes */
static size_t encode_bonds_order_filled_message(const BondsOrderFilledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_date[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->trading_value[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bond_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->yield_opening_price[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->yield_todays_high[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->yield_todays_low[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->accumulated_trading_volume_long[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_date[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Bonds Order Filled Message off the wire: 218 bytes from at, returning where the next byte lies */
static size_t decode_bonds_order_filled_message(BondsOrderFilledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bond_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->yield_opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->yield_todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->yield_todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->accumulated_trading_volume_long[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Bonds Order Filled Message is what was written, byte for byte */
static void equal_bonds_order_filled_message(const BondsOrderFilledMessage *read, const BondsOrderFilledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_date[i] == written->trading_date[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->trading_value[i] == written->trading_value[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bond_yield[i] == written->bond_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->yield_opening_price[i] == written->yield_opening_price[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->yield_todays_high[i] == written->yield_todays_high[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->yield_todays_low[i] == written->yield_todays_low[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->accumulated_trading_volume_long[i] == written->accumulated_trading_volume_long[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value_long[i] == written->accumulated_trading_value_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Bonds Order Filled Message: written and read back, then read and written back */
static void check_bonds_order_filled_message(void) {
  BondsOrderFilledMessage sent;
  BondsOrderFilledMessage got;
  uint8_t wire[218];
  uint8_t again[218];

  any_bonds_order_filled_message(&sent);
  assert(encode_bonds_order_filled_message(&sent, wire, 0) == 218);
  assert(decode_bonds_order_filled_message(&got, wire, 0) == 218);
  equal_bonds_order_filled_message(&got, &sent);

  for (size_t i = 0; i < 218; i++) { wire[i] = arbitrary(); }
  assert(decode_bonds_order_filled_message(&got, wire, 0) == 218);
  assert(encode_bonds_order_filled_message(&got, again, 0) == 218);
  for (size_t i = 0; i < 218; i++) { assert(again[i] == wire[i]); }
}

/* ---- General Bonds Ktb Order Filled Plus Quote Message: 638 bytes ------------ */

/* General Bonds and KTB Order Filled plus Quote. Trade print followed by full multi-level quote state. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t session_id[2];                          /* bytes 10 to 11 */
  uint8_t isin_code[12];                          /* bytes 12 to 23 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 24 to 35 */
  uint8_t trading_price[11];                      /* bytes 36 to 46 */
  uint8_t trading_volume[10];                     /* bytes 47 to 56 */
  uint8_t trading_date[8];                        /* bytes 57 to 64 */
  uint8_t trading_value[22];                      /* bytes 65 to 86 */
  uint8_t bond_yield[13];                         /* bytes 87 to 99 */
  uint8_t opening_price[11];                      /* bytes 100 to 110 */
  uint8_t todays_high[11];                        /* bytes 111 to 121 */
  uint8_t todays_low[11];                         /* bytes 122 to 132 */
  uint8_t yield_opening_price[13];                /* bytes 133 to 145 */
  uint8_t yield_todays_high[13];                  /* bytes 146 to 158 */
  uint8_t yield_todays_low[13];                   /* bytes 159 to 171 */
  uint8_t accumulated_trading_volume_long[15];    /* bytes 172 to 186 */
  uint8_t accumulated_trading_value_long[22];     /* bytes 187 to 208 */
  uint8_t settlement_date[8];                     /* bytes 209 to 216 */
  uint8_t ask_level_1_price[11];                  /* bytes 217 to 227 */
  uint8_t bid_level_1_price[11];                  /* bytes 228 to 238 */
  uint8_t ask_level_1_remaining_quantity[15];     /* bytes 239 to 253 */
  uint8_t bid_level_1_remaining_quantity[15];     /* bytes 254 to 268 */
  uint8_t ask_level_1_yield[13];                  /* bytes 269 to 281 */
  uint8_t bid_level_1_yield[13];                  /* bytes 282 to 294 */
  uint8_t ask_level_2_price[11];                  /* bytes 295 to 305 */
  uint8_t bid_level_2_price[11];                  /* bytes 306 to 316 */
  uint8_t ask_level_2_remaining_quantity[15];     /* bytes 317 to 331 */
  uint8_t bid_level_2_remaining_quantity[15];     /* bytes 332 to 346 */
  uint8_t ask_level_2_yield[13];                  /* bytes 347 to 359 */
  uint8_t bid_level_2_yield[13];                  /* bytes 360 to 372 */
  uint8_t ask_level_3_price[11];                  /* bytes 373 to 383 */
  uint8_t bid_level_3_price[11];                  /* bytes 384 to 394 */
  uint8_t ask_level_3_remaining_quantity[15];     /* bytes 395 to 409 */
  uint8_t bid_level_3_remaining_quantity[15];     /* bytes 410 to 424 */
  uint8_t ask_level_3_yield[13];                  /* bytes 425 to 437 */
  uint8_t bid_level_3_yield[13];                  /* bytes 438 to 450 */
  uint8_t ask_level_4_price[11];                  /* bytes 451 to 461 */
  uint8_t bid_level_4_price[11];                  /* bytes 462 to 472 */
  uint8_t ask_level_4_remaining_quantity[15];     /* bytes 473 to 487 */
  uint8_t bid_level_4_remaining_quantity[15];     /* bytes 488 to 502 */
  uint8_t ask_level_4_yield[13];                  /* bytes 503 to 515 */
  uint8_t bid_level_4_yield[13];                  /* bytes 516 to 528 */
  uint8_t ask_level_5_price[11];                  /* bytes 529 to 539 */
  uint8_t bid_level_5_price[11];                  /* bytes 540 to 550 */
  uint8_t ask_level_5_remaining_quantity[15];     /* bytes 551 to 565 */
  uint8_t bid_level_5_remaining_quantity[15];     /* bytes 566 to 580 */
  uint8_t ask_level_5_yield[13];                  /* bytes 581 to 593 */
  uint8_t bid_level_5_yield[13];                  /* bytes 594 to 606 */
  uint8_t ask_total_remaining_quantity[15];       /* bytes 607 to 621 */
  uint8_t bid_total_remaining_quantity[15];       /* bytes 622 to 636 */
  uint8_t end_keyword;                            /* byte 637 */
} GeneralBondsKtbOrderFilledPlusQuoteMessage;

/* any General Bonds Ktb Order Filled Plus Quote Message at all: every byte one the checker chooses */
static void any_general_bonds_ktb_order_filled_plus_quote_message(GeneralBondsKtbOrderFilledPlusQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bond_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->yield_opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->yield_todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->yield_todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->accumulated_trading_volume_long[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_1_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_1_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_2_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_2_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_3_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_3_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_4_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_4_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_5_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_5_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_total_remaining_quantity[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* General Bonds Ktb Order Filled Plus Quote Message to the wire: 638 bytes from at, returning where the next byte goes */
static size_t encode_general_bonds_ktb_order_filled_plus_quote_message(const GeneralBondsKtbOrderFilledPlusQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_date[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->trading_value[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bond_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->yield_opening_price[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->yield_todays_high[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->yield_todays_low[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->accumulated_trading_volume_long[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_date[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_1_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_1_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_2_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_2_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_3_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_3_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_4_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_4_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_5_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_5_yield[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_total_remaining_quantity[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* General Bonds Ktb Order Filled Plus Quote Message off the wire: 638 bytes from at, returning where the next byte lies */
static size_t decode_general_bonds_ktb_order_filled_plus_quote_message(GeneralBondsKtbOrderFilledPlusQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bond_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->yield_opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->yield_todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->yield_todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->accumulated_trading_volume_long[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_1_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_1_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_2_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_2_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_3_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_3_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_4_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_4_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_5_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_5_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_total_remaining_quantity[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of General Bonds Ktb Order Filled Plus Quote Message is what was written, byte for byte */
static void equal_general_bonds_ktb_order_filled_plus_quote_message(const GeneralBondsKtbOrderFilledPlusQuoteMessage *read, const GeneralBondsKtbOrderFilledPlusQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_date[i] == written->trading_date[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->trading_value[i] == written->trading_value[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bond_yield[i] == written->bond_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->yield_opening_price[i] == written->yield_opening_price[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->yield_todays_high[i] == written->yield_todays_high[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->yield_todays_low[i] == written->yield_todays_low[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->accumulated_trading_volume_long[i] == written->accumulated_trading_volume_long[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value_long[i] == written->accumulated_trading_value_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_1_remaining_quantity[i] == written->ask_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_1_remaining_quantity[i] == written->bid_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_1_yield[i] == written->ask_level_1_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_1_yield[i] == written->bid_level_1_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_2_remaining_quantity[i] == written->ask_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_2_remaining_quantity[i] == written->bid_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_2_yield[i] == written->ask_level_2_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_2_yield[i] == written->bid_level_2_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_3_remaining_quantity[i] == written->ask_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_3_remaining_quantity[i] == written->bid_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_3_yield[i] == written->ask_level_3_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_3_yield[i] == written->bid_level_3_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_4_remaining_quantity[i] == written->ask_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_4_remaining_quantity[i] == written->bid_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_4_yield[i] == written->ask_level_4_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_4_yield[i] == written->bid_level_4_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_5_remaining_quantity[i] == written->ask_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_5_remaining_quantity[i] == written->bid_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_5_yield[i] == written->ask_level_5_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_5_yield[i] == written->bid_level_5_yield[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_total_remaining_quantity[i] == written->ask_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_total_remaining_quantity[i] == written->bid_total_remaining_quantity[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* General Bonds Ktb Order Filled Plus Quote Message: written and read back, then read and written back */
static void check_general_bonds_ktb_order_filled_plus_quote_message(void) {
  GeneralBondsKtbOrderFilledPlusQuoteMessage sent;
  GeneralBondsKtbOrderFilledPlusQuoteMessage got;
  uint8_t wire[638];
  uint8_t again[638];

  any_general_bonds_ktb_order_filled_plus_quote_message(&sent);
  assert(encode_general_bonds_ktb_order_filled_plus_quote_message(&sent, wire, 0) == 638);
  assert(decode_general_bonds_ktb_order_filled_plus_quote_message(&got, wire, 0) == 638);
  equal_general_bonds_ktb_order_filled_plus_quote_message(&got, &sent);

  for (size_t i = 0; i < 638; i++) { wire[i] = arbitrary(); }
  assert(decode_general_bonds_ktb_order_filled_plus_quote_message(&got, wire, 0) == 638);
  assert(encode_general_bonds_ktb_order_filled_plus_quote_message(&got, again, 0) == 638);
  for (size_t i = 0; i < 638; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bonds Negotiated Trade Data Message: 36 bytes --------------------------- */

/* Bonds Negotiated Trade Data. Negotiated trades for KTB and General Bonds. */
typedef struct {
  uint8_t board_id[2];                          /* bytes 0 to 1 */
  uint8_t isin_code[12];                        /* bytes 2 to 13 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 14 to 19 */
  uint8_t accumulated_trading_volume_long[15];  /* bytes 20 to 34 */
  uint8_t end_keyword;                          /* byte 35 */
} BondsNegotiatedTradeDataMessage;

/* any Bonds Negotiated Trade Data Message at all: every byte one the checker chooses */
static void any_bonds_negotiated_trade_data_message(BondsNegotiatedTradeDataMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->accumulated_trading_volume_long[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Bonds Negotiated Trade Data Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_bonds_negotiated_trade_data_message(const BondsNegotiatedTradeDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->accumulated_trading_volume_long[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Bonds Negotiated Trade Data Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_bonds_negotiated_trade_data_message(BondsNegotiatedTradeDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->accumulated_trading_volume_long[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Bonds Negotiated Trade Data Message is what was written, byte for byte */
static void equal_bonds_negotiated_trade_data_message(const BondsNegotiatedTradeDataMessage *read, const BondsNegotiatedTradeDataMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->accumulated_trading_volume_long[i] == written->accumulated_trading_volume_long[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Bonds Negotiated Trade Data Message: written and read back, then read and written back */
static void check_bonds_negotiated_trade_data_message(void) {
  BondsNegotiatedTradeDataMessage sent;
  BondsNegotiatedTradeDataMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_bonds_negotiated_trade_data_message(&sent);
  assert(encode_bonds_negotiated_trade_data_message(&sent, wire, 0) == 36);
  assert(decode_bonds_negotiated_trade_data_message(&got, wire, 0) == 36);
  equal_bonds_negotiated_trade_data_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_bonds_negotiated_trade_data_message(&got, wire, 0) == 36);
  assert(encode_bonds_negotiated_trade_data_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Repo Negotiated Trade Data Message: 50 bytes ---------------------------- */

/* REPO Negotiated Trade Data. */
typedef struct {
  uint8_t isin_code[12];                            /* bytes 0 to 11 */
  uint8_t rfq_accumulated_trading_value[22];        /* bytes 12 to 33 */
  uint8_t report_trading_total_trading_volume[15];  /* bytes 34 to 48 */
  uint8_t end_keyword;                              /* byte 49 */
} RepoNegotiatedTradeDataMessage;

/* any Repo Negotiated Trade Data Message at all: every byte one the checker chooses */
static void any_repo_negotiated_trade_data_message(RepoNegotiatedTradeDataMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->rfq_accumulated_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->report_trading_total_trading_volume[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Repo Negotiated Trade Data Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_repo_negotiated_trade_data_message(const RepoNegotiatedTradeDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->rfq_accumulated_trading_value[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->report_trading_total_trading_volume[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Repo Negotiated Trade Data Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_repo_negotiated_trade_data_message(RepoNegotiatedTradeDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->rfq_accumulated_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->report_trading_total_trading_volume[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Repo Negotiated Trade Data Message is what was written, byte for byte */
static void equal_repo_negotiated_trade_data_message(const RepoNegotiatedTradeDataMessage *read, const RepoNegotiatedTradeDataMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->rfq_accumulated_trading_value[i] == written->rfq_accumulated_trading_value[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->report_trading_total_trading_volume[i] == written->report_trading_total_trading_volume[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Repo Negotiated Trade Data Message: written and read back, then read and written back */
static void check_repo_negotiated_trade_data_message(void) {
  RepoNegotiatedTradeDataMessage sent;
  RepoNegotiatedTradeDataMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_repo_negotiated_trade_data_message(&sent);
  assert(encode_repo_negotiated_trade_data_message(&sent, wire, 0) == 50);
  assert(decode_repo_negotiated_trade_data_message(&got, wire, 0) == 50);
  equal_repo_negotiated_trade_data_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_repo_negotiated_trade_data_message(&got, wire, 0) == 50);
  assert(encode_repo_negotiated_trade_data_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bonds Batch Data Message: 303 bytes ------------------------------------- */

/* Bonds Batch Data. Per-issue reference data dumped at start-of-day for General Bonds, KTB, and Baby Bonds. */
typedef struct {
  uint8_t message_sequence_number[8];                      /* bytes 0 to 7 */
  uint8_t total_number_of_instruments_of_the_contract[6];  /* bytes 8 to 13 */
  uint8_t business_date[8];                                /* bytes 14 to 21 */
  uint8_t isin_code[12];                                   /* bytes 22 to 33 */
  uint8_t a_designated_number_for_an_issue[6];             /* bytes 34 to 39 */
  uint8_t retail_bond_type_code[2];                        /* bytes 40 to 41 */
  uint8_t abbreviated_issue_name[40];                      /* bytes 42 to 81 */
  uint8_t abbreviated_issue_name_in_en[40];                /* bytes 82 to 121 */
  uint8_t market_operation_product_id[3];                  /* bytes 122 to 124 */
  uint8_t bond_listing_type_code;                          /* byte 125 */
  uint8_t bond_category_code[6];                           /* bytes 126 to 131 */
  uint8_t bond_guaranteed_type_code;                       /* byte 132 */
  uint8_t coupon_payment_type_code[2];                     /* bytes 133 to 134 */
  uint8_t listing_date[8];                                 /* bytes 135 to 142 */
  uint8_t issue_date[8];                                   /* bytes 143 to 150 */
  uint8_t redemption_date[8];                              /* bytes 151 to 158 */
  uint8_t sale_date[8];                                    /* bytes 159 to 166 */
  uint8_t bond_issuance_rate[13];                          /* bytes 167 to 179 */
  uint8_t coupon_rate[14];                                 /* bytes 180 to 193 */
  uint8_t monthly_cycle_of_coupon_payment[4];              /* bytes 194 to 197 */
  uint8_t coupon_payment_timing_code;                      /* byte 198 */
  uint8_t interest_payment;                                /* byte 199 */
  uint8_t coupon_payment_date_type_code;                   /* byte 200 */
  uint8_t decimal_point_of_coupon_type_code;               /* byte 201 */
  uint8_t pre_issue_sale_coupon_payment_type_code;         /* byte 202 */
  uint8_t issuing_amount[22];                              /* bytes 203 to 224 */
  uint8_t listed_amount[22];                               /* bytes 225 to 246 */
  uint8_t redemption_ratio_at_maturity[13];                /* bytes 247 to 259 */
  uint8_t amortization_type_code;                          /* byte 260 */
  uint8_t number_of_months_for_grace[4];                   /* bytes 261 to 264 */
  uint8_t number_of_amortization[5];                       /* bytes 265 to 269 */
  uint8_t trading_halt;                                    /* byte 270 */
  uint8_t prior_coupon_payment_date[8];                    /* bytes 271 to 278 */
  uint8_t next_coupon_payment_date[8];                     /* bytes 279 to 286 */
  uint8_t perpetual_bond_maturity_structure_status;        /* byte 287 */
  uint8_t strip_bond_type_code;                            /* byte 288 */
  uint8_t base_price[11];                                  /* bytes 289 to 299 */
  uint8_t liquidation_trade;                               /* byte 300 */
  uint8_t investment_caution_bond_type_code;               /* byte 301 */
  uint8_t end_keyword;                                     /* byte 302 */
} BondsBatchDataMessage;

/* any Bonds Batch Data Message at all: every byte one the checker chooses */
static void any_bonds_batch_data_message(BondsBatchDataMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_instruments_of_the_contract[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->retail_bond_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name_in_en[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = arbitrary(); }
  record->bond_listing_type_code = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->bond_category_code[i] = arbitrary(); }
  record->bond_guaranteed_type_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->coupon_payment_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->issue_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->redemption_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sale_date[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bond_issuance_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->coupon_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->monthly_cycle_of_coupon_payment[i] = arbitrary(); }
  record->coupon_payment_timing_code = arbitrary();
  record->interest_payment = arbitrary();
  record->coupon_payment_date_type_code = arbitrary();
  record->decimal_point_of_coupon_type_code = arbitrary();
  record->pre_issue_sale_coupon_payment_type_code = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->issuing_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->listed_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->redemption_ratio_at_maturity[i] = arbitrary(); }
  record->amortization_type_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->number_of_months_for_grace[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->number_of_amortization[i] = arbitrary(); }
  record->trading_halt = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->prior_coupon_payment_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->next_coupon_payment_date[i] = arbitrary(); }
  record->perpetual_bond_maturity_structure_status = arbitrary();
  record->strip_bond_type_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = arbitrary(); }
  record->liquidation_trade = arbitrary();
  record->investment_caution_bond_type_code = arbitrary();
  record->end_keyword = arbitrary();
}

/* Bonds Batch Data Message to the wire: 303 bytes from at, returning where the next byte goes */
static size_t encode_bonds_batch_data_message(const BondsBatchDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_number_of_instruments_of_the_contract[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->retail_bond_type_code[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name_in_en[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_operation_product_id[i]; }
  wire[at++] = record->bond_listing_type_code;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->bond_category_code[i]; }
  wire[at++] = record->bond_guaranteed_type_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->coupon_payment_type_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->listing_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->redemption_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sale_date[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bond_issuance_rate[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->coupon_rate[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->monthly_cycle_of_coupon_payment[i]; }
  wire[at++] = record->coupon_payment_timing_code;
  wire[at++] = record->interest_payment;
  wire[at++] = record->coupon_payment_date_type_code;
  wire[at++] = record->decimal_point_of_coupon_type_code;
  wire[at++] = record->pre_issue_sale_coupon_payment_type_code;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->issuing_amount[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->listed_amount[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->redemption_ratio_at_maturity[i]; }
  wire[at++] = record->amortization_type_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_months_for_grace[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->number_of_amortization[i]; }
  wire[at++] = record->trading_halt;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->prior_coupon_payment_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_coupon_payment_date[i]; }
  wire[at++] = record->perpetual_bond_maturity_structure_status;
  wire[at++] = record->strip_bond_type_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->base_price[i]; }
  wire[at++] = record->liquidation_trade;
  wire[at++] = record->investment_caution_bond_type_code;
  wire[at++] = record->end_keyword;

  return at;
}

/* Bonds Batch Data Message off the wire: 303 bytes from at, returning where the next byte lies */
static size_t decode_bonds_batch_data_message(BondsBatchDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_instruments_of_the_contract[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->retail_bond_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name_in_en[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = wire[at++]; }
  record->bond_listing_type_code = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->bond_category_code[i] = wire[at++]; }
  record->bond_guaranteed_type_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->coupon_payment_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->issue_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->redemption_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sale_date[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bond_issuance_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->coupon_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->monthly_cycle_of_coupon_payment[i] = wire[at++]; }
  record->coupon_payment_timing_code = wire[at++];
  record->interest_payment = wire[at++];
  record->coupon_payment_date_type_code = wire[at++];
  record->decimal_point_of_coupon_type_code = wire[at++];
  record->pre_issue_sale_coupon_payment_type_code = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->issuing_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->listed_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->redemption_ratio_at_maturity[i] = wire[at++]; }
  record->amortization_type_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->number_of_months_for_grace[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->number_of_amortization[i] = wire[at++]; }
  record->trading_halt = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->prior_coupon_payment_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->next_coupon_payment_date[i] = wire[at++]; }
  record->perpetual_bond_maturity_structure_status = wire[at++];
  record->strip_bond_type_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = wire[at++]; }
  record->liquidation_trade = wire[at++];
  record->investment_caution_bond_type_code = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Bonds Batch Data Message is what was written, byte for byte */
static void equal_bonds_batch_data_message(const BondsBatchDataMessage *read, const BondsBatchDataMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_number_of_instruments_of_the_contract[i] == written->total_number_of_instruments_of_the_contract[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->retail_bond_type_code[i] == written->retail_bond_type_code[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name[i] == written->abbreviated_issue_name[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name_in_en[i] == written->abbreviated_issue_name_in_en[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->market_operation_product_id[i] == written->market_operation_product_id[i]); }
  assert(read->bond_listing_type_code == written->bond_listing_type_code);
  for (size_t i = 0; i < 6; i++) { assert(read->bond_category_code[i] == written->bond_category_code[i]); }
  assert(read->bond_guaranteed_type_code == written->bond_guaranteed_type_code);
  for (size_t i = 0; i < 2; i++) { assert(read->coupon_payment_type_code[i] == written->coupon_payment_type_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->listing_date[i] == written->listing_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->issue_date[i] == written->issue_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->redemption_date[i] == written->redemption_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sale_date[i] == written->sale_date[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bond_issuance_rate[i] == written->bond_issuance_rate[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->coupon_rate[i] == written->coupon_rate[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->monthly_cycle_of_coupon_payment[i] == written->monthly_cycle_of_coupon_payment[i]); }
  assert(read->coupon_payment_timing_code == written->coupon_payment_timing_code);
  assert(read->interest_payment == written->interest_payment);
  assert(read->coupon_payment_date_type_code == written->coupon_payment_date_type_code);
  assert(read->decimal_point_of_coupon_type_code == written->decimal_point_of_coupon_type_code);
  assert(read->pre_issue_sale_coupon_payment_type_code == written->pre_issue_sale_coupon_payment_type_code);
  for (size_t i = 0; i < 22; i++) { assert(read->issuing_amount[i] == written->issuing_amount[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->listed_amount[i] == written->listed_amount[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->redemption_ratio_at_maturity[i] == written->redemption_ratio_at_maturity[i]); }
  assert(read->amortization_type_code == written->amortization_type_code);
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_months_for_grace[i] == written->number_of_months_for_grace[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->number_of_amortization[i] == written->number_of_amortization[i]); }
  assert(read->trading_halt == written->trading_halt);
  for (size_t i = 0; i < 8; i++) { assert(read->prior_coupon_payment_date[i] == written->prior_coupon_payment_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->next_coupon_payment_date[i] == written->next_coupon_payment_date[i]); }
  assert(read->perpetual_bond_maturity_structure_status == written->perpetual_bond_maturity_structure_status);
  assert(read->strip_bond_type_code == written->strip_bond_type_code);
  for (size_t i = 0; i < 11; i++) { assert(read->base_price[i] == written->base_price[i]); }
  assert(read->liquidation_trade == written->liquidation_trade);
  assert(read->investment_caution_bond_type_code == written->investment_caution_bond_type_code);
  assert(read->end_keyword == written->end_keyword);
}

/* Bonds Batch Data Message: written and read back, then read and written back */
static void check_bonds_batch_data_message(void) {
  BondsBatchDataMessage sent;
  BondsBatchDataMessage got;
  uint8_t wire[303];
  uint8_t again[303];

  any_bonds_batch_data_message(&sent);
  assert(encode_bonds_batch_data_message(&sent, wire, 0) == 303);
  assert(decode_bonds_batch_data_message(&got, wire, 0) == 303);
  equal_bonds_batch_data_message(&got, &sent);

  for (size_t i = 0; i < 303; i++) { wire[i] = arbitrary(); }
  assert(decode_bonds_batch_data_message(&got, wire, 0) == 303);
  assert(encode_bonds_batch_data_message(&got, again, 0) == 303);
  for (size_t i = 0; i < 303; i++) { assert(again[i] == wire[i]); }
}

/* ---- Repo Batch Data Message: 95 bytes --------------------------------------- */

/* REPO Batch Data. Per-issue reference data dumped at start-of-day for REPO instruments. */
typedef struct {
  uint8_t message_sequence_number[8];                      /* bytes 0 to 7 */
  uint8_t total_number_of_instruments_of_the_contract[6];  /* bytes 8 to 13 */
  uint8_t business_date[8];                                /* bytes 14 to 21 */
  uint8_t isin_code[12];                                   /* bytes 22 to 33 */
  uint8_t a_designated_number_for_an_issue[6];             /* bytes 34 to 39 */
  uint8_t market_operation_product_id[3];                  /* bytes 40 to 42 */
  uint8_t abbreviated_issue_name[40];                      /* bytes 43 to 82 */
  uint8_t market_value[11];                                /* bytes 83 to 93 */
  uint8_t end_keyword;                                     /* byte 94 */
} RepoBatchDataMessage;

/* any Repo Batch Data Message at all: every byte one the checker chooses */
static void any_repo_batch_data_message(RepoBatchDataMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_instruments_of_the_contract[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->market_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Repo Batch Data Message to the wire: 95 bytes from at, returning where the next byte goes */
static size_t encode_repo_batch_data_message(const RepoBatchDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_number_of_instruments_of_the_contract[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_operation_product_id[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->market_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Repo Batch Data Message off the wire: 95 bytes from at, returning where the next byte lies */
static size_t decode_repo_batch_data_message(RepoBatchDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_instruments_of_the_contract[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->market_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Repo Batch Data Message is what was written, byte for byte */
static void equal_repo_batch_data_message(const RepoBatchDataMessage *read, const RepoBatchDataMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_number_of_instruments_of_the_contract[i] == written->total_number_of_instruments_of_the_contract[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->market_operation_product_id[i] == written->market_operation_product_id[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name[i] == written->abbreviated_issue_name[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->market_value[i] == written->market_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Repo Batch Data Message: written and read back, then read and written back */
static void check_repo_batch_data_message(void) {
  RepoBatchDataMessage sent;
  RepoBatchDataMessage got;
  uint8_t wire[95];
  uint8_t again[95];

  any_repo_batch_data_message(&sent);
  assert(encode_repo_batch_data_message(&sent, wire, 0) == 95);
  assert(decode_repo_batch_data_message(&got, wire, 0) == 95);
  equal_repo_batch_data_message(&got, &sent);

  for (size_t i = 0; i < 95; i++) { wire[i] = arbitrary(); }
  assert(decode_repo_batch_data_message(&got, wire, 0) == 95);
  assert(encode_repo_batch_data_message(&got, again, 0) == 95);
  for (size_t i = 0; i < 95; i++) { assert(again[i] == wire[i]); }
}

/* ---- Issue Event Message: 43 bytes ------------------------------------------- */

/* Issue Event. Per-issue lifecycle event log. */
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

/* ---- Corporate Bonds Reference Message: 240 bytes ---------------------------- */

/* Corporate Bonds related to Securities and Baby Bonds Issue reference data. */
typedef struct {
  uint8_t message_sequence_number[8];                                /* bytes 0 to 7 */
  uint8_t isin_code[12];                                             /* bytes 8 to 19 */
  uint8_t abbreviated_issue_name[40];                                /* bytes 20 to 59 */
  uint8_t issue_date[8];                                             /* bytes 60 to 67 */
  uint8_t redemption_date[8];                                        /* bytes 68 to 75 */
  uint8_t listing_date[8];                                           /* bytes 76 to 83 */
  uint8_t coupon_payment_type_code[2];                               /* bytes 84 to 85 */
  uint8_t issuing_amount[22];                                        /* bytes 86 to 107 */
  uint8_t listed_amount[22];                                         /* bytes 108 to 129 */
  uint8_t coupon_payment_timing_code;                                /* byte 130 */
  uint8_t number_of_months_for_grace[4];                             /* bytes 131 to 134 */
  uint8_t number_of_amortization[5];                                 /* bytes 135 to 139 */
  uint8_t interest_payment;                                          /* byte 140 */
  uint8_t coupon_payment_date_type_code;                             /* byte 141 */
  uint8_t coupon_rate[14];                                           /* bytes 142 to 155 */
  uint8_t substitute_price_of_securities[11];                        /* bytes 156 to 166 */
  uint8_t isin[12];                                                  /* bytes 167 to 178 */
  uint8_t date_to_start_exercising[8];                               /* bytes 179 to 186 */
  uint8_t date_to_end_exercising[8];                                 /* bytes 187 to 194 */
  uint8_t record_date_of_dividend_payout;                            /* byte 195 */
  uint8_t exercise_ratio[7];                                         /* bytes 196 to 202 */
  uint8_t yield_to_maturity[13];                                     /* bytes 203 to 215 */
  uint8_t corporate_bonds_related_to_securities_exercise_price[11];  /* bytes 216 to 226 */
  uint8_t abbreviated_issue_code[9];                                 /* bytes 227 to 235 */
  uint8_t baby_bonds_type_code[3];                                   /* bytes 236 to 238 */
  uint8_t end_keyword;                                               /* byte 239 */
} CorporateBondsReferenceMessage;

/* any Corporate Bonds Reference Message at all: every byte one the checker chooses */
static void any_corporate_bonds_reference_message(CorporateBondsReferenceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->issue_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->redemption_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->coupon_payment_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->issuing_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->listed_amount[i] = arbitrary(); }
  record->coupon_payment_timing_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->number_of_months_for_grace[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->number_of_amortization[i] = arbitrary(); }
  record->interest_payment = arbitrary();
  record->coupon_payment_date_type_code = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->coupon_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->substitute_price_of_securities[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_to_start_exercising[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_to_end_exercising[i] = arbitrary(); }
  record->record_date_of_dividend_payout = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->exercise_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->yield_to_maturity[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->corporate_bonds_related_to_securities_exercise_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->abbreviated_issue_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->baby_bonds_type_code[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Corporate Bonds Reference Message to the wire: 240 bytes from at, returning where the next byte goes */
static size_t encode_corporate_bonds_reference_message(const CorporateBondsReferenceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->redemption_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->listing_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->coupon_payment_type_code[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->issuing_amount[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->listed_amount[i]; }
  wire[at++] = record->coupon_payment_timing_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_months_for_grace[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->number_of_amortization[i]; }
  wire[at++] = record->interest_payment;
  wire[at++] = record->coupon_payment_date_type_code;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->coupon_rate[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->substitute_price_of_securities[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_to_start_exercising[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_to_end_exercising[i]; }
  wire[at++] = record->record_date_of_dividend_payout;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->exercise_ratio[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->yield_to_maturity[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->corporate_bonds_related_to_securities_exercise_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->abbreviated_issue_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->baby_bonds_type_code[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Corporate Bonds Reference Message off the wire: 240 bytes from at, returning where the next byte lies */
static size_t decode_corporate_bonds_reference_message(CorporateBondsReferenceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->issue_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->redemption_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->coupon_payment_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->issuing_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->listed_amount[i] = wire[at++]; }
  record->coupon_payment_timing_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->number_of_months_for_grace[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->number_of_amortization[i] = wire[at++]; }
  record->interest_payment = wire[at++];
  record->coupon_payment_date_type_code = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->coupon_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->substitute_price_of_securities[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_to_start_exercising[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_to_end_exercising[i] = wire[at++]; }
  record->record_date_of_dividend_payout = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->exercise_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->yield_to_maturity[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->corporate_bonds_related_to_securities_exercise_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->abbreviated_issue_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->baby_bonds_type_code[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Corporate Bonds Reference Message is what was written, byte for byte */
static void equal_corporate_bonds_reference_message(const CorporateBondsReferenceMessage *read, const CorporateBondsReferenceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name[i] == written->abbreviated_issue_name[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->issue_date[i] == written->issue_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->redemption_date[i] == written->redemption_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->listing_date[i] == written->listing_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->coupon_payment_type_code[i] == written->coupon_payment_type_code[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->issuing_amount[i] == written->issuing_amount[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->listed_amount[i] == written->listed_amount[i]); }
  assert(read->coupon_payment_timing_code == written->coupon_payment_timing_code);
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_months_for_grace[i] == written->number_of_months_for_grace[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->number_of_amortization[i] == written->number_of_amortization[i]); }
  assert(read->interest_payment == written->interest_payment);
  assert(read->coupon_payment_date_type_code == written->coupon_payment_date_type_code);
  for (size_t i = 0; i < 14; i++) { assert(read->coupon_rate[i] == written->coupon_rate[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->substitute_price_of_securities[i] == written->substitute_price_of_securities[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_to_start_exercising[i] == written->date_to_start_exercising[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_to_end_exercising[i] == written->date_to_end_exercising[i]); }
  assert(read->record_date_of_dividend_payout == written->record_date_of_dividend_payout);
  for (size_t i = 0; i < 7; i++) { assert(read->exercise_ratio[i] == written->exercise_ratio[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->yield_to_maturity[i] == written->yield_to_maturity[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->corporate_bonds_related_to_securities_exercise_price[i] == written->corporate_bonds_related_to_securities_exercise_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->abbreviated_issue_code[i] == written->abbreviated_issue_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->baby_bonds_type_code[i] == written->baby_bonds_type_code[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Corporate Bonds Reference Message: written and read back, then read and written back */
static void check_corporate_bonds_reference_message(void) {
  CorporateBondsReferenceMessage sent;
  CorporateBondsReferenceMessage got;
  uint8_t wire[240];
  uint8_t again[240];

  any_corporate_bonds_reference_message(&sent);
  assert(encode_corporate_bonds_reference_message(&sent, wire, 0) == 240);
  assert(decode_corporate_bonds_reference_message(&got, wire, 0) == 240);
  equal_corporate_bonds_reference_message(&got, &sent);

  for (size_t i = 0; i < 240; i++) { wire[i] = arbitrary(); }
  assert(decode_corporate_bonds_reference_message(&got, wire, 0) == 240);
  assert(encode_corporate_bonds_reference_message(&got, again, 0) == 240);
  for (size_t i = 0; i < 240; i++) { assert(again[i] == wire[i]); }
}

/* ---- Regular Bonds Installment Repayment Date Message: 29 bytes -------------- */

/* Regular Bonds installment repayment date. */
typedef struct {
  uint8_t message_sequence_number[8];     /* bytes 0 to 7 */
  uint8_t isin_code[12];                  /* bytes 8 to 19 */
  uint8_t installment_repayment_date[8];  /* bytes 20 to 27 */
  uint8_t end_keyword;                    /* byte 28 */
} RegularBondsInstallmentRepaymentDateMessage;

/* any Regular Bonds Installment Repayment Date Message at all: every byte one the checker chooses */
static void any_regular_bonds_installment_repayment_date_message(RegularBondsInstallmentRepaymentDateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->installment_repayment_date[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Regular Bonds Installment Repayment Date Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_regular_bonds_installment_repayment_date_message(const RegularBondsInstallmentRepaymentDateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->installment_repayment_date[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Regular Bonds Installment Repayment Date Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_regular_bonds_installment_repayment_date_message(RegularBondsInstallmentRepaymentDateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->installment_repayment_date[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Regular Bonds Installment Repayment Date Message is what was written, byte for byte */
static void equal_regular_bonds_installment_repayment_date_message(const RegularBondsInstallmentRepaymentDateMessage *read, const RegularBondsInstallmentRepaymentDateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->installment_repayment_date[i] == written->installment_repayment_date[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Regular Bonds Installment Repayment Date Message: written and read back, then read and written back */
static void check_regular_bonds_installment_repayment_date_message(void) {
  RegularBondsInstallmentRepaymentDateMessage sent;
  RegularBondsInstallmentRepaymentDateMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_regular_bonds_installment_repayment_date_message(&sent);
  assert(encode_regular_bonds_installment_repayment_date_message(&sent, wire, 0) == 29);
  assert(decode_regular_bonds_installment_repayment_date_message(&got, wire, 0) == 29);
  equal_regular_bonds_installment_repayment_date_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_regular_bonds_installment_repayment_date_message(&got, wire, 0) == 29);
  assert(encode_regular_bonds_installment_repayment_date_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Repo Classification Data Message: 39 bytes ------------------------------ */

/* REPO Classification Data. */
typedef struct {
  uint8_t message_sequence_number[8];    /* bytes 0 to 7 */
  uint8_t business_date[8];              /* bytes 8 to 15 */
  uint8_t repo_classification_code[2];   /* bytes 16 to 17 */
  uint8_t repo_classification_name[20];  /* bytes 18 to 37 */
  uint8_t end_keyword;                   /* byte 38 */
} RepoClassificationDataMessage;

/* any Repo Classification Data Message at all: every byte one the checker chooses */
static void any_repo_classification_data_message(RepoClassificationDataMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->repo_classification_code[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->repo_classification_name[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Repo Classification Data Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_repo_classification_data_message(const RepoClassificationDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->repo_classification_code[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->repo_classification_name[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Repo Classification Data Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_repo_classification_data_message(RepoClassificationDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->repo_classification_code[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->repo_classification_name[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Repo Classification Data Message is what was written, byte for byte */
static void equal_repo_classification_data_message(const RepoClassificationDataMessage *read, const RepoClassificationDataMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->repo_classification_code[i] == written->repo_classification_code[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->repo_classification_name[i] == written->repo_classification_name[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Repo Classification Data Message: written and read back, then read and written back */
static void check_repo_classification_data_message(void) {
  RepoClassificationDataMessage sent;
  RepoClassificationDataMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_repo_classification_data_message(&sent);
  assert(encode_repo_classification_data_message(&sent, wire, 0) == 39);
  assert(decode_repo_classification_data_message(&got, wire, 0) == 39);
  equal_repo_classification_data_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_repo_classification_data_message(&got, wire, 0) == 39);
  assert(encode_repo_classification_data_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Repo Trade Availability Per Term Message: 54 bytes ---------------------- */

/* REPO Trade Availability per Term. */
typedef struct {
  uint8_t message_sequence_number[8];       /* bytes 0 to 7 */
  uint8_t isin_code[12];                    /* bytes 8 to 19 */
  uint8_t number_of_repo_trade_periods[3];  /* bytes 20 to 22 */
  uint8_t repo_trade_period_1[3];           /* bytes 23 to 25 */
  uint8_t repo_trade_period_2[3];           /* bytes 26 to 28 */
  uint8_t repo_trade_period_3[3];           /* bytes 29 to 31 */
  uint8_t repo_trade_period_4[3];           /* bytes 32 to 34 */
  uint8_t repo_trade_period_5[3];           /* bytes 35 to 37 */
  uint8_t repo_trade_period_6[3];           /* bytes 38 to 40 */
  uint8_t repo_trade_period_7[3];           /* bytes 41 to 43 */
  uint8_t repo_trade_period_8[3];           /* bytes 44 to 46 */
  uint8_t repo_trade_period_9[3];           /* bytes 47 to 49 */
  uint8_t repo_trade_period_10[3];          /* bytes 50 to 52 */
  uint8_t end_keyword;                      /* byte 53 */
} RepoTradeAvailabilityPerTermMessage;

/* any Repo Trade Availability Per Term Message at all: every byte one the checker chooses */
static void any_repo_trade_availability_per_term_message(RepoTradeAvailabilityPerTermMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->number_of_repo_trade_periods[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_1[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_2[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_3[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_4[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_5[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_6[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_7[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_8[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_9[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_10[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Repo Trade Availability Per Term Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_repo_trade_availability_per_term_message(const RepoTradeAvailabilityPerTermMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->number_of_repo_trade_periods[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->repo_trade_period_1[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->repo_trade_period_2[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->repo_trade_period_3[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->repo_trade_period_4[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->repo_trade_period_5[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->repo_trade_period_6[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->repo_trade_period_7[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->repo_trade_period_8[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->repo_trade_period_9[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->repo_trade_period_10[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Repo Trade Availability Per Term Message off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_repo_trade_availability_per_term_message(RepoTradeAvailabilityPerTermMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->number_of_repo_trade_periods[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_1[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_2[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_3[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_4[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_5[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_6[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_7[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_8[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_9[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->repo_trade_period_10[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Repo Trade Availability Per Term Message is what was written, byte for byte */
static void equal_repo_trade_availability_per_term_message(const RepoTradeAvailabilityPerTermMessage *read, const RepoTradeAvailabilityPerTermMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->number_of_repo_trade_periods[i] == written->number_of_repo_trade_periods[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->repo_trade_period_1[i] == written->repo_trade_period_1[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->repo_trade_period_2[i] == written->repo_trade_period_2[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->repo_trade_period_3[i] == written->repo_trade_period_3[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->repo_trade_period_4[i] == written->repo_trade_period_4[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->repo_trade_period_5[i] == written->repo_trade_period_5[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->repo_trade_period_6[i] == written->repo_trade_period_6[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->repo_trade_period_7[i] == written->repo_trade_period_7[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->repo_trade_period_8[i] == written->repo_trade_period_8[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->repo_trade_period_9[i] == written->repo_trade_period_9[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->repo_trade_period_10[i] == written->repo_trade_period_10[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Repo Trade Availability Per Term Message: written and read back, then read and written back */
static void check_repo_trade_availability_per_term_message(void) {
  RepoTradeAvailabilityPerTermMessage sent;
  RepoTradeAvailabilityPerTermMessage got;
  uint8_t wire[54];
  uint8_t again[54];

  any_repo_trade_availability_per_term_message(&sent);
  assert(encode_repo_trade_availability_per_term_message(&sent, wire, 0) == 54);
  assert(decode_repo_trade_availability_per_term_message(&got, wire, 0) == 54);
  equal_repo_trade_availability_per_term_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_repo_trade_availability_per_term_message(&got, wire, 0) == 54);
  assert(encode_repo_trade_availability_per_term_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retail Bonds Type Code Message: 52 bytes -------------------------------- */

/* Retail Bonds Type Code reference (IFMSBTD0018) — Bonds A BND variant. */
typedef struct {
  uint8_t message_sequence_number[8];           /* bytes 0 to 7 */
  uint8_t retail_bond_type_code[2];             /* bytes 8 to 9 */
  uint8_t retail_bond_category_name[20];        /* bytes 10 to 29 */
  uint8_t retail_bond_category_name_in_en[20];  /* bytes 30 to 49 */
  uint8_t retail_bond_generated_quotes;         /* byte 50 */
  uint8_t end_keyword;                          /* byte 51 */
} RetailBondsTypeCodeMessage;

/* any Retail Bonds Type Code Message at all: every byte one the checker chooses */
static void any_retail_bonds_type_code_message(RetailBondsTypeCodeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->retail_bond_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->retail_bond_category_name[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->retail_bond_category_name_in_en[i] = arbitrary(); }
  record->retail_bond_generated_quotes = arbitrary();
  record->end_keyword = arbitrary();
}

/* Retail Bonds Type Code Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_retail_bonds_type_code_message(const RetailBondsTypeCodeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->retail_bond_type_code[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->retail_bond_category_name[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->retail_bond_category_name_in_en[i]; }
  wire[at++] = record->retail_bond_generated_quotes;
  wire[at++] = record->end_keyword;

  return at;
}

/* Retail Bonds Type Code Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_retail_bonds_type_code_message(RetailBondsTypeCodeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->retail_bond_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->retail_bond_category_name[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->retail_bond_category_name_in_en[i] = wire[at++]; }
  record->retail_bond_generated_quotes = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Retail Bonds Type Code Message is what was written, byte for byte */
static void equal_retail_bonds_type_code_message(const RetailBondsTypeCodeMessage *read, const RetailBondsTypeCodeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->retail_bond_type_code[i] == written->retail_bond_type_code[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->retail_bond_category_name[i] == written->retail_bond_category_name[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->retail_bond_category_name_in_en[i] == written->retail_bond_category_name_in_en[i]); }
  assert(read->retail_bond_generated_quotes == written->retail_bond_generated_quotes);
  assert(read->end_keyword == written->end_keyword);
}

/* Retail Bonds Type Code Message: written and read back, then read and written back */
static void check_retail_bonds_type_code_message(void) {
  RetailBondsTypeCodeMessage sent;
  RetailBondsTypeCodeMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_retail_bonds_type_code_message(&sent);
  assert(encode_retail_bonds_type_code_message(&sent, wire, 0) == 52);
  assert(decode_retail_bonds_type_code_message(&got, wire, 0) == 52);
  equal_retail_bonds_type_code_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_retail_bonds_type_code_message(&got, wire, 0) == 52);
  assert(encode_retail_bonds_type_code_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Baby Bonds Reporting Market Yield Message: 68 bytes --------------------- */

/* Baby Bonds reporting market yield. Reference yields per issue. */
typedef struct {
  uint8_t message_sequence_number[8];            /* bytes 0 to 7 */
  uint8_t business_date[8];                      /* bytes 8 to 15 */
  uint8_t baby_bonds_type_code[3];               /* bytes 16 to 18 */
  uint8_t report_market_yield_rate[13];          /* bytes 19 to 31 */
  uint8_t report_market_a_price_with_yield[11];  /* bytes 32 to 42 */
  uint8_t closing_price_yield_rate[13];          /* bytes 43 to 55 */
  uint8_t closing_price_with_yield[11];          /* bytes 56 to 66 */
  uint8_t end_keyword;                           /* byte 67 */
} BabyBondsReportingMarketYieldMessage;

/* any Baby Bonds Reporting Market Yield Message at all: every byte one the checker chooses */
static void any_baby_bonds_reporting_market_yield_message(BabyBondsReportingMarketYieldMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->baby_bonds_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->report_market_yield_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->report_market_a_price_with_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->closing_price_yield_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_with_yield[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Baby Bonds Reporting Market Yield Message to the wire: 68 bytes from at, returning where the next byte goes */
static size_t encode_baby_bonds_reporting_market_yield_message(const BabyBondsReportingMarketYieldMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->baby_bonds_type_code[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->report_market_yield_rate[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->report_market_a_price_with_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->closing_price_yield_rate[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_with_yield[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Baby Bonds Reporting Market Yield Message off the wire: 68 bytes from at, returning where the next byte lies */
static size_t decode_baby_bonds_reporting_market_yield_message(BabyBondsReportingMarketYieldMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->baby_bonds_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->report_market_yield_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->report_market_a_price_with_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->closing_price_yield_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_with_yield[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Baby Bonds Reporting Market Yield Message is what was written, byte for byte */
static void equal_baby_bonds_reporting_market_yield_message(const BabyBondsReportingMarketYieldMessage *read, const BabyBondsReportingMarketYieldMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->baby_bonds_type_code[i] == written->baby_bonds_type_code[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->report_market_yield_rate[i] == written->report_market_yield_rate[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->report_market_a_price_with_yield[i] == written->report_market_a_price_with_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->closing_price_yield_rate[i] == written->closing_price_yield_rate[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_with_yield[i] == written->closing_price_with_yield[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Baby Bonds Reporting Market Yield Message: written and read back, then read and written back */
static void check_baby_bonds_reporting_market_yield_message(void) {
  BabyBondsReportingMarketYieldMessage sent;
  BabyBondsReportingMarketYieldMessage got;
  uint8_t wire[68];
  uint8_t again[68];

  any_baby_bonds_reporting_market_yield_message(&sent);
  assert(encode_baby_bonds_reporting_market_yield_message(&sent, wire, 0) == 68);
  assert(decode_baby_bonds_reporting_market_yield_message(&got, wire, 0) == 68);
  equal_baby_bonds_reporting_market_yield_message(&got, &sent);

  for (size_t i = 0; i < 68; i++) { wire[i] = arbitrary(); }
  assert(decode_baby_bonds_reporting_market_yield_message(&got, wire, 0) == 68);
  assert(encode_baby_bonds_reporting_market_yield_message(&got, again, 0) == 68);
  for (size_t i = 0; i < 68; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ktb Confirmed Info For Wit Message: 67 bytes ---------------------------- */

/* KTB Confirmed info for WIT (When-Issued Trading). */
typedef struct {
  uint8_t isin_code[12];                        /* bytes 0 to 11 */
  uint8_t trading_date[8];                      /* bytes 12 to 19 */
  uint8_t bid_closing_date[8];                  /* bytes 20 to 27 */
  uint8_t accumulated_trading_volume_long[15];  /* bytes 28 to 42 */
  uint8_t accumulated_trading_value_long[22];   /* bytes 43 to 64 */
  uint8_t cancellation;                         /* byte 65 */
  uint8_t end_keyword;                          /* byte 66 */
} KtbConfirmedInfoForWitMessage;

/* any Ktb Confirmed Info For Wit Message at all: every byte one the checker chooses */
static void any_ktb_confirmed_info_for_wit_message(KtbConfirmedInfoForWitMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_closing_date[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->accumulated_trading_volume_long[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = arbitrary(); }
  record->cancellation = arbitrary();
  record->end_keyword = arbitrary();
}

/* Ktb Confirmed Info For Wit Message to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_ktb_confirmed_info_for_wit_message(const KtbConfirmedInfoForWitMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_closing_date[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->accumulated_trading_volume_long[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value_long[i]; }
  wire[at++] = record->cancellation;
  wire[at++] = record->end_keyword;

  return at;
}

/* Ktb Confirmed Info For Wit Message off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_ktb_confirmed_info_for_wit_message(KtbConfirmedInfoForWitMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_closing_date[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->accumulated_trading_volume_long[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = wire[at++]; }
  record->cancellation = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Ktb Confirmed Info For Wit Message is what was written, byte for byte */
static void equal_ktb_confirmed_info_for_wit_message(const KtbConfirmedInfoForWitMessage *read, const KtbConfirmedInfoForWitMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_date[i] == written->trading_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_closing_date[i] == written->bid_closing_date[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->accumulated_trading_volume_long[i] == written->accumulated_trading_volume_long[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value_long[i] == written->accumulated_trading_value_long[i]); }
  assert(read->cancellation == written->cancellation);
  assert(read->end_keyword == written->end_keyword);
}

/* Ktb Confirmed Info For Wit Message: written and read back, then read and written back */
static void check_ktb_confirmed_info_for_wit_message(void) {
  KtbConfirmedInfoForWitMessage sent;
  KtbConfirmedInfoForWitMessage got;
  uint8_t wire[67];
  uint8_t again[67];

  any_ktb_confirmed_info_for_wit_message(&sent);
  assert(encode_ktb_confirmed_info_for_wit_message(&sent, wire, 0) == 67);
  assert(decode_ktb_confirmed_info_for_wit_message(&got, wire, 0) == 67);
  equal_ktb_confirmed_info_for_wit_message(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_ktb_confirmed_info_for_wit_message(&got, wire, 0) == 67);
  assert(encode_ktb_confirmed_info_for_wit_message(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ktb Short Term Yield Message: 32 bytes ---------------------------------- */

/* KTB Short-term Yield reference. */
typedef struct {
  uint8_t transmission_date[8];                 /* bytes 0 to 7 */
  uint8_t calculation_time_long[9];             /* bytes 8 to 16 */
  uint8_t short_term_interest_rates_type_code;  /* byte 17 */
  uint8_t short_term_yield[13];                 /* bytes 18 to 30 */
  uint8_t end_keyword;                          /* byte 31 */
} KtbShortTermYieldMessage;

/* any Ktb Short Term Yield Message at all: every byte one the checker chooses */
static void any_ktb_short_term_yield_message(KtbShortTermYieldMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transmission_date[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->calculation_time_long[i] = arbitrary(); }
  record->short_term_interest_rates_type_code = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->short_term_yield[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Ktb Short Term Yield Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_ktb_short_term_yield_message(const KtbShortTermYieldMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transmission_date[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->calculation_time_long[i]; }
  wire[at++] = record->short_term_interest_rates_type_code;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->short_term_yield[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Ktb Short Term Yield Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_ktb_short_term_yield_message(KtbShortTermYieldMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transmission_date[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->calculation_time_long[i] = wire[at++]; }
  record->short_term_interest_rates_type_code = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->short_term_yield[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Ktb Short Term Yield Message is what was written, byte for byte */
static void equal_ktb_short_term_yield_message(const KtbShortTermYieldMessage *read, const KtbShortTermYieldMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transmission_date[i] == written->transmission_date[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->calculation_time_long[i] == written->calculation_time_long[i]); }
  assert(read->short_term_interest_rates_type_code == written->short_term_interest_rates_type_code);
  for (size_t i = 0; i < 13; i++) { assert(read->short_term_yield[i] == written->short_term_yield[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Ktb Short Term Yield Message: written and read back, then read and written back */
static void check_ktb_short_term_yield_message(void) {
  KtbShortTermYieldMessage sent;
  KtbShortTermYieldMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_ktb_short_term_yield_message(&sent);
  assert(encode_ktb_short_term_yield_message(&sent, wire, 0) == 32);
  assert(decode_ktb_short_term_yield_message(&got, wire, 0) == 32);
  equal_ktb_short_term_yield_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_ktb_short_term_yield_message(&got, wire, 0) == 32);
  assert(encode_ktb_short_term_yield_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ktb Average Yield Message: 32 bytes ------------------------------------- */

/* KTB Average Yield reference. */
typedef struct {
  uint8_t transmission_date[8];                 /* bytes 0 to 7 */
  uint8_t calculation_time_long[9];             /* bytes 8 to 16 */
  uint8_t short_term_interest_rates_type_code;  /* byte 17 */
  uint8_t average_yield[13];                    /* bytes 18 to 30 */
  uint8_t end_keyword;                          /* byte 31 */
} KtbAverageYieldMessage;

/* any Ktb Average Yield Message at all: every byte one the checker chooses */
static void any_ktb_average_yield_message(KtbAverageYieldMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transmission_date[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->calculation_time_long[i] = arbitrary(); }
  record->short_term_interest_rates_type_code = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->average_yield[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Ktb Average Yield Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_ktb_average_yield_message(const KtbAverageYieldMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transmission_date[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->calculation_time_long[i]; }
  wire[at++] = record->short_term_interest_rates_type_code;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->average_yield[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Ktb Average Yield Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_ktb_average_yield_message(KtbAverageYieldMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transmission_date[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->calculation_time_long[i] = wire[at++]; }
  record->short_term_interest_rates_type_code = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->average_yield[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Ktb Average Yield Message is what was written, byte for byte */
static void equal_ktb_average_yield_message(const KtbAverageYieldMessage *read, const KtbAverageYieldMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transmission_date[i] == written->transmission_date[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->calculation_time_long[i] == written->calculation_time_long[i]); }
  assert(read->short_term_interest_rates_type_code == written->short_term_interest_rates_type_code);
  for (size_t i = 0; i < 13; i++) { assert(read->average_yield[i] == written->average_yield[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Ktb Average Yield Message: written and read back, then read and written back */
static void check_ktb_average_yield_message(void) {
  KtbAverageYieldMessage sent;
  KtbAverageYieldMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_ktb_average_yield_message(&sent);
  assert(encode_ktb_average_yield_message(&sent, wire, 0) == 32);
  assert(decode_ktb_average_yield_message(&got, wire, 0) == 32);
  equal_ktb_average_yield_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_ktb_average_yield_message(&got, wire, 0) == 32);
  assert(encode_ktb_average_yield_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bonds Credit Rating Information Message: 65 bytes ----------------------- */

/* Bonds Credit Rating Information. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t isin_code[12];                          /* bytes 8 to 19 */
  uint8_t transmission_date[8];                   /* bytes 20 to 27 */
  uint8_t credit_rating_agency_code_no_1[4];      /* bytes 28 to 31 */
  uint8_t credit_rating_per_agency_code_no_1[4];  /* bytes 32 to 35 */
  uint8_t sf_ratings_1;                           /* byte 36 */
  uint8_t credit_rating_agency_code_no_2[4];      /* bytes 37 to 40 */
  uint8_t credit_rating_per_agency_code_no_2[4];  /* bytes 41 to 44 */
  uint8_t sf_ratings_2;                           /* byte 45 */
  uint8_t credit_rating_agency_code_no_3[4];      /* bytes 46 to 49 */
  uint8_t credit_rating_per_agency_code_no_3[4];  /* bytes 50 to 53 */
  uint8_t sf_ratings_3;                           /* byte 54 */
  uint8_t credit_rating_agency_code_no_4[4];      /* bytes 55 to 58 */
  uint8_t credit_rating_per_agency_code_no_4[4];  /* bytes 59 to 62 */
  uint8_t sf_ratings_4;                           /* byte 63 */
  uint8_t end_keyword;                            /* byte 64 */
} BondsCreditRatingInformationMessage;

/* any Bonds Credit Rating Information Message at all: every byte one the checker chooses */
static void any_bonds_credit_rating_information_message(BondsCreditRatingInformationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transmission_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->credit_rating_agency_code_no_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->credit_rating_per_agency_code_no_1[i] = arbitrary(); }
  record->sf_ratings_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->credit_rating_agency_code_no_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->credit_rating_per_agency_code_no_2[i] = arbitrary(); }
  record->sf_ratings_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->credit_rating_agency_code_no_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->credit_rating_per_agency_code_no_3[i] = arbitrary(); }
  record->sf_ratings_3 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->credit_rating_agency_code_no_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->credit_rating_per_agency_code_no_4[i] = arbitrary(); }
  record->sf_ratings_4 = arbitrary();
  record->end_keyword = arbitrary();
}

/* Bonds Credit Rating Information Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_bonds_credit_rating_information_message(const BondsCreditRatingInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transmission_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->credit_rating_agency_code_no_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->credit_rating_per_agency_code_no_1[i]; }
  wire[at++] = record->sf_ratings_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->credit_rating_agency_code_no_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->credit_rating_per_agency_code_no_2[i]; }
  wire[at++] = record->sf_ratings_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->credit_rating_agency_code_no_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->credit_rating_per_agency_code_no_3[i]; }
  wire[at++] = record->sf_ratings_3;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->credit_rating_agency_code_no_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->credit_rating_per_agency_code_no_4[i]; }
  wire[at++] = record->sf_ratings_4;
  wire[at++] = record->end_keyword;

  return at;
}

/* Bonds Credit Rating Information Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_bonds_credit_rating_information_message(BondsCreditRatingInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transmission_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->credit_rating_agency_code_no_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->credit_rating_per_agency_code_no_1[i] = wire[at++]; }
  record->sf_ratings_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->credit_rating_agency_code_no_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->credit_rating_per_agency_code_no_2[i] = wire[at++]; }
  record->sf_ratings_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->credit_rating_agency_code_no_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->credit_rating_per_agency_code_no_3[i] = wire[at++]; }
  record->sf_ratings_3 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->credit_rating_agency_code_no_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->credit_rating_per_agency_code_no_4[i] = wire[at++]; }
  record->sf_ratings_4 = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Bonds Credit Rating Information Message is what was written, byte for byte */
static void equal_bonds_credit_rating_information_message(const BondsCreditRatingInformationMessage *read, const BondsCreditRatingInformationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transmission_date[i] == written->transmission_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->credit_rating_agency_code_no_1[i] == written->credit_rating_agency_code_no_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->credit_rating_per_agency_code_no_1[i] == written->credit_rating_per_agency_code_no_1[i]); }
  assert(read->sf_ratings_1 == written->sf_ratings_1);
  for (size_t i = 0; i < 4; i++) { assert(read->credit_rating_agency_code_no_2[i] == written->credit_rating_agency_code_no_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->credit_rating_per_agency_code_no_2[i] == written->credit_rating_per_agency_code_no_2[i]); }
  assert(read->sf_ratings_2 == written->sf_ratings_2);
  for (size_t i = 0; i < 4; i++) { assert(read->credit_rating_agency_code_no_3[i] == written->credit_rating_agency_code_no_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->credit_rating_per_agency_code_no_3[i] == written->credit_rating_per_agency_code_no_3[i]); }
  assert(read->sf_ratings_3 == written->sf_ratings_3);
  for (size_t i = 0; i < 4; i++) { assert(read->credit_rating_agency_code_no_4[i] == written->credit_rating_agency_code_no_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->credit_rating_per_agency_code_no_4[i] == written->credit_rating_per_agency_code_no_4[i]); }
  assert(read->sf_ratings_4 == written->sf_ratings_4);
  assert(read->end_keyword == written->end_keyword);
}

/* Bonds Credit Rating Information Message: written and read back, then read and written back */
static void check_bonds_credit_rating_information_message(void) {
  BondsCreditRatingInformationMessage sent;
  BondsCreditRatingInformationMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_bonds_credit_rating_information_message(&sent);
  assert(encode_bonds_credit_rating_information_message(&sent, wire, 0) == 65);
  assert(decode_bonds_credit_rating_information_message(&got, wire, 0) == 65);
  equal_bonds_credit_rating_information_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_bonds_credit_rating_information_message(&got, wire, 0) == 65);
  assert(encode_bonds_credit_rating_information_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Regular Bonds Disclosure Basic Exchange Rate Message: 27 bytes ---------- */

/* Regular Bonds Disclosure of Basic Exchange Rate for Settlement. */
typedef struct {
  uint8_t disclosing_data_type_code[3];  /* bytes 0 to 2 */
  uint8_t disclosure_time[9];            /* bytes 3 to 11 */
  uint8_t applied_exchange_rate[13];     /* bytes 12 to 24 */
  uint8_t currency_type_code;            /* byte 25 */
  uint8_t end_keyword;                   /* byte 26 */
} RegularBondsDisclosureBasicExchangeRateMessage;

/* any Regular Bonds Disclosure Basic Exchange Rate Message at all: every byte one the checker chooses */
static void any_regular_bonds_disclosure_basic_exchange_rate_message(RegularBondsDisclosureBasicExchangeRateMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->disclosing_data_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->disclosure_time[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->applied_exchange_rate[i] = arbitrary(); }
  record->currency_type_code = arbitrary();
  record->end_keyword = arbitrary();
}

/* Regular Bonds Disclosure Basic Exchange Rate Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_regular_bonds_disclosure_basic_exchange_rate_message(const RegularBondsDisclosureBasicExchangeRateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->disclosing_data_type_code[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->disclosure_time[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->applied_exchange_rate[i]; }
  wire[at++] = record->currency_type_code;
  wire[at++] = record->end_keyword;

  return at;
}

/* Regular Bonds Disclosure Basic Exchange Rate Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_regular_bonds_disclosure_basic_exchange_rate_message(RegularBondsDisclosureBasicExchangeRateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->disclosing_data_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->disclosure_time[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->applied_exchange_rate[i] = wire[at++]; }
  record->currency_type_code = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Regular Bonds Disclosure Basic Exchange Rate Message is what was written, byte for byte */
static void equal_regular_bonds_disclosure_basic_exchange_rate_message(const RegularBondsDisclosureBasicExchangeRateMessage *read, const RegularBondsDisclosureBasicExchangeRateMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->disclosing_data_type_code[i] == written->disclosing_data_type_code[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->disclosure_time[i] == written->disclosure_time[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->applied_exchange_rate[i] == written->applied_exchange_rate[i]); }
  assert(read->currency_type_code == written->currency_type_code);
  assert(read->end_keyword == written->end_keyword);
}

/* Regular Bonds Disclosure Basic Exchange Rate Message: written and read back, then read and written back */
static void check_regular_bonds_disclosure_basic_exchange_rate_message(void) {
  RegularBondsDisclosureBasicExchangeRateMessage sent;
  RegularBondsDisclosureBasicExchangeRateMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_regular_bonds_disclosure_basic_exchange_rate_message(&sent);
  assert(encode_regular_bonds_disclosure_basic_exchange_rate_message(&sent, wire, 0) == 27);
  assert(decode_regular_bonds_disclosure_basic_exchange_rate_message(&got, wire, 0) == 27);
  equal_regular_bonds_disclosure_basic_exchange_rate_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_regular_bonds_disclosure_basic_exchange_rate_message(&got, wire, 0) == 27);
  assert(encode_regular_bonds_disclosure_basic_exchange_rate_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Investor Activities Per Bond Types Message: 85 bytes -------------------- */

/* Investor Activities per Bond Types. Aggregated bid/ask volumes and values per investor category and bond type. */
typedef struct {
  uint8_t investor_code[4];                    /* bytes 0 to 3 */
  uint8_t bond_category_code[6];               /* bytes 4 to 9 */
  uint8_t accumulated_ask_trading_volume[15];  /* bytes 10 to 24 */
  uint8_t accumulated_ask_trading_value[22];   /* bytes 25 to 46 */
  uint8_t accumulated_bid_trading_volume[15];  /* bytes 47 to 61 */
  uint8_t accumulated_bid_trading_value[22];   /* bytes 62 to 83 */
  uint8_t end_keyword;                         /* byte 84 */
} InvestorActivitiesPerBondTypesMessage;

/* any Investor Activities Per Bond Types Message at all: every byte one the checker chooses */
static void any_investor_activities_per_bond_types_message(InvestorActivitiesPerBondTypesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->bond_category_code[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->accumulated_ask_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_ask_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->accumulated_bid_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_bid_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Investor Activities Per Bond Types Message to the wire: 85 bytes from at, returning where the next byte goes */
static size_t encode_investor_activities_per_bond_types_message(const InvestorActivitiesPerBondTypesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->investor_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->bond_category_code[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->accumulated_ask_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_ask_trading_value[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->accumulated_bid_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_bid_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Investor Activities Per Bond Types Message off the wire: 85 bytes from at, returning where the next byte lies */
static size_t decode_investor_activities_per_bond_types_message(InvestorActivitiesPerBondTypesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->bond_category_code[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->accumulated_ask_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_ask_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->accumulated_bid_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_bid_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Investor Activities Per Bond Types Message is what was written, byte for byte */
static void equal_investor_activities_per_bond_types_message(const InvestorActivitiesPerBondTypesMessage *read, const InvestorActivitiesPerBondTypesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->investor_code[i] == written->investor_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->bond_category_code[i] == written->bond_category_code[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->accumulated_ask_trading_volume[i] == written->accumulated_ask_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_ask_trading_value[i] == written->accumulated_ask_trading_value[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->accumulated_bid_trading_volume[i] == written->accumulated_bid_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_bid_trading_value[i] == written->accumulated_bid_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Investor Activities Per Bond Types Message: written and read back, then read and written back */
static void check_investor_activities_per_bond_types_message(void) {
  InvestorActivitiesPerBondTypesMessage sent;
  InvestorActivitiesPerBondTypesMessage got;
  uint8_t wire[85];
  uint8_t again[85];

  any_investor_activities_per_bond_types_message(&sent);
  assert(encode_investor_activities_per_bond_types_message(&sent, wire, 0) == 85);
  assert(decode_investor_activities_per_bond_types_message(&got, wire, 0) == 85);
  equal_investor_activities_per_bond_types_message(&got, &sent);

  for (size_t i = 0; i < 85; i++) { wire[i] = arbitrary(); }
  assert(decode_investor_activities_per_bond_types_message(&got, wire, 0) == 85);
  assert(encode_investor_activities_per_bond_types_message(&got, again, 0) == 85);
  for (size_t i = 0; i < 85; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bonds Isin Issue Information Message: 898 bytes ------------------------- */

/* Bonds ISIN Issue Information (IFMSRID0038) — Bonds A. Comprehensive bond issue reference data. */
typedef struct {
  uint8_t message_sequence_number[8];                                      /* bytes 0 to 7 */
  uint8_t isin_code[12];                                                   /* bytes 8 to 19 */
  uint8_t transmission_date[8];                                            /* bytes 20 to 27 */
  uint8_t transmission_time_long[9];                                       /* bytes 28 to 36 */
  uint8_t record_process_category;                                         /* byte 37 */
  uint8_t abbreviated_issue_name[40];                                      /* bytes 38 to 77 */
  uint8_t abbreviated_issue_name_in_en[40];                                /* bytes 78 to 117 */
  uint8_t issuer_code[5];                                                  /* bytes 118 to 122 */
  uint8_t bond_listing_type_code;                                          /* byte 123 */
  uint8_t bond_category_code[6];                                           /* bytes 124 to 129 */
  uint8_t bond_type_code[2];                                               /* bytes 130 to 131 */
  uint8_t special_bond_issue_code[3];                                      /* bytes 132 to 134 */
  uint8_t mb_type_code;                                                    /* byte 135 */
  uint8_t bond_guaranteed_type_code;                                       /* byte 136 */
  uint8_t guaranteed_rate_for_payment[13];                                 /* bytes 137 to 149 */
  uint8_t other_types_of_bond;                                             /* byte 150 */
  uint8_t option_embedded_type_code;                                       /* byte 151 */
  uint8_t coupon_payment_type_code[2];                                     /* bytes 152 to 153 */
  uint8_t risk_bond_redemption_type_code;                                  /* byte 154 */
  uint8_t bond_issuance_type_code[3];                                      /* bytes 155 to 157 */
  uint8_t securitization_type_code[2];                                     /* bytes 158 to 159 */
  uint8_t redemption_priority_type_code;                                   /* byte 160 */
  uint8_t listing_date[8];                                                 /* bytes 161 to 168 */
  uint8_t issue_date[8];                                                   /* bytes 169 to 176 */
  uint8_t redemption_date[8];                                              /* bytes 177 to 184 */
  uint8_t sale_date[8];                                                    /* bytes 185 to 192 */
  uint8_t the_1_st_coupon_payment_date[8];                                 /* bytes 193 to 200 */
  uint8_t bond_issuance_rate[13];                                          /* bytes 201 to 213 */
  uint8_t coupon_rate[14];                                                 /* bytes 214 to 227 */
  uint8_t monthly_cycle_of_coupon_payment[4];                              /* bytes 228 to 231 */
  uint8_t coupon_payment_timing_code;                                      /* byte 232 */
  uint8_t interest_payment;                                                /* byte 233 */
  uint8_t coupon_payment_date_type_code;                                   /* byte 234 */
  uint8_t decimal_point_of_coupon_type_code;                               /* byte 235 */
  uint8_t number_of_months_to_pay_interest[4];                             /* bytes 236 to 239 */
  uint8_t bond_sale_type_code;                                             /* byte 240 */
  uint8_t pre_issue_sale_coupon_payment_type_code;                         /* byte 241 */
  uint8_t issuing_amount[22];                                              /* bytes 242 to 263 */
  uint8_t listed_amount[22];                                               /* bytes 264 to 285 */
  uint8_t confirmation_of_lump_sum_payment;                                /* byte 286 */
  uint8_t currency_type_code;                                              /* byte 287 */
  uint8_t redemption_ratio_at_maturity[13];                                /* bytes 288 to 300 */
  uint8_t yield_to_maturity[13];                                           /* bytes 301 to 313 */
  uint8_t guaranteed_yield_effective_date[8];                              /* bytes 314 to 321 */
  uint8_t additional_yield[13];                                            /* bytes 322 to 334 */
  uint8_t additional_yield_effective_date[8];                              /* bytes 335 to 342 */
  uint8_t facility_fund[22];                                               /* bytes 343 to 364 */
  uint8_t maintenance_fund[22];                                            /* bytes 365 to 386 */
  uint8_t loan_fund[22];                                                   /* bytes 387 to 408 */
  uint8_t other_funds[22];                                                 /* bytes 409 to 430 */
  uint8_t inscription_type_of_bond;                                        /* byte 431 */
  uint8_t taxation;                                                        /* byte 432 */
  uint8_t bond_lead_manager_company_code[4];                               /* bytes 433 to 436 */
  uint8_t payment_guarantor_code[4];                                       /* bytes 437 to 440 */
  uint8_t trustee_code[4];                                                 /* bytes 441 to 444 */
  uint8_t register_institute_code[4];                                      /* bytes 445 to 448 */
  uint8_t payment_agent_code[4];                                           /* bytes 449 to 452 */
  uint8_t abbreviated_issue_code[9];                                       /* bytes 453 to 461 */
  uint8_t bond_delisting_reason_code[2];                                   /* bytes 462 to 463 */
  uint8_t bond_delisted_date[8];                                           /* bytes 464 to 471 */
  uint8_t equity_linked_bond_rights_type_code[2];                          /* bytes 472 to 473 */
  uint8_t isin[12];                                                        /* bytes 474 to 485 */
  uint8_t issue_name_short[60];                                            /* bytes 486 to 545 */
  uint8_t equity_linked_bond_exercise_price[11];                           /* bytes 546 to 556 */
  uint8_t exercise_ratio[7];                                               /* bytes 557 to 563 */
  uint8_t date_to_start_exercising[8];                                     /* bytes 564 to 571 */
  uint8_t date_to_end_exercising[8];                                       /* bytes 572 to 579 */
  uint8_t institution_code[4];                                             /* bytes 580 to 583 */
  uint8_t record_date_of_dividend_payout;                                  /* byte 584 */
  uint8_t profit_participating_accum_status;                               /* byte 585 */
  uint8_t issue_code_of_post_exercise[12];                                 /* bytes 586 to 597 */
  uint8_t amortization_type_code;                                          /* byte 598 */
  uint8_t level_payment_amount[22];                                        /* bytes 599 to 620 */
  uint8_t number_of_months_for_grace[4];                                   /* bytes 621 to 624 */
  uint8_t interest_type_code_during_amortization;                          /* byte 625 */
  uint8_t number_of_amortization[5];                                       /* bytes 626 to 630 */
  uint8_t interest_rate_decision_other_base_rate_name[20];                 /* bytes 631 to 650 */
  uint8_t spread[10];                                                      /* bytes 651 to 660 */
  uint8_t timing_of_interest_rate_decision_type_code;                      /* byte 661 */
  uint8_t upper_limit_coupon_rate[14];                                     /* bytes 662 to 675 */
  uint8_t lower_limit_coupon_rate[14];                                     /* bytes 676 to 689 */
  uint8_t the_date_to_decide_interest_rate[8];                             /* bytes 690 to 697 */
  uint8_t first_call_exercise_start_date[8];                               /* bytes 698 to 705 */
  uint8_t first_call_exercise_end_date[8];                                 /* bytes 706 to 713 */
  uint8_t second_call_exercise_start_date[8];                              /* bytes 714 to 721 */
  uint8_t second_call_exercise_end_date[8];                                /* bytes 722 to 729 */
  uint8_t first_put_exercise_start_date[8];                                /* bytes 730 to 737 */
  uint8_t first_put_exercise_end_date[8];                                  /* bytes 738 to 745 */
  uint8_t second_put_exercise_start_date[8];                               /* bytes 746 to 753 */
  uint8_t second_put_exercise_end_date[8];                                 /* bytes 754 to 761 */
  uint8_t coupon_payment_decision_code_for_bank_holidays;                  /* byte 762 */
  uint8_t hybrid_bond;                                                     /* byte 763 */
  uint8_t co_cos_type_code;                                                /* byte 764 */
  uint8_t coupon_rate_confirmation;                                        /* byte 765 */
  uint8_t principal_guranteed_rate[13];                                    /* bytes 766 to 778 */
  uint8_t participating_rate[11];                                          /* bytes 779 to 789 */
  uint8_t maximum_yield[11];                                               /* bytes 790 to 800 */
  uint8_t strip_bond_type_code;                                            /* byte 801 */
  uint8_t original_bond_type_code_subjec_to_strip[12];                     /* bytes 802 to 813 */
  uint8_t unstripped_balance[22];                                          /* bytes 814 to 835 */
  uint8_t inflation_indexed_category;                                      /* byte 836 */
  uint8_t reference_index_for_issue_date[11];                              /* bytes 837 to 847 */
  uint8_t coupon_rate_decision_base_rate_type_code[2];                     /* bytes 848 to 849 */
  uint8_t bond_odd_lot_days_base_interest_type_code;                       /* byte 850 */
  uint8_t base_interest_rate_on_bank_holidays_type_code;                   /* byte 851 */
  uint8_t accrued_interest_rate_on_bank_holidays_type_code[14];            /* bytes 852 to 865 */
  uint8_t principal_payment_methods_on_bank_holidays_type_code;            /* byte 866 */
  uint8_t principal_base_rate_on_bank_holidays_type_code;                  /* byte 867 */
  uint8_t principal_accrued_interest_rate_on_bank_holidays_type_code[14];  /* bytes 868 to 881 */
  uint8_t stop_out_rate[14];                                               /* bytes 882 to 895 */
  uint8_t crowdfunding;                                                    /* byte 896 */
  uint8_t end_keyword;                                                     /* byte 897 */
} BondsIsinIssueInformationMessage;

/* any Bonds Isin Issue Information Message at all: every byte one the checker chooses */
static void any_bonds_isin_issue_information_message(BondsIsinIssueInformationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transmission_date[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->transmission_time_long[i] = arbitrary(); }
  record->record_process_category = arbitrary();
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name_in_en[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->issuer_code[i] = arbitrary(); }
  record->bond_listing_type_code = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->bond_category_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bond_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->special_bond_issue_code[i] = arbitrary(); }
  record->mb_type_code = arbitrary();
  record->bond_guaranteed_type_code = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->guaranteed_rate_for_payment[i] = arbitrary(); }
  record->other_types_of_bond = arbitrary();
  record->option_embedded_type_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->coupon_payment_type_code[i] = arbitrary(); }
  record->risk_bond_redemption_type_code = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->bond_issuance_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->securitization_type_code[i] = arbitrary(); }
  record->redemption_priority_type_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->issue_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->redemption_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sale_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->the_1_st_coupon_payment_date[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bond_issuance_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->coupon_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->monthly_cycle_of_coupon_payment[i] = arbitrary(); }
  record->coupon_payment_timing_code = arbitrary();
  record->interest_payment = arbitrary();
  record->coupon_payment_date_type_code = arbitrary();
  record->decimal_point_of_coupon_type_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->number_of_months_to_pay_interest[i] = arbitrary(); }
  record->bond_sale_type_code = arbitrary();
  record->pre_issue_sale_coupon_payment_type_code = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->issuing_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->listed_amount[i] = arbitrary(); }
  record->confirmation_of_lump_sum_payment = arbitrary();
  record->currency_type_code = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->redemption_ratio_at_maturity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->yield_to_maturity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->guaranteed_yield_effective_date[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->additional_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->additional_yield_effective_date[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->facility_fund[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->maintenance_fund[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->loan_fund[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->other_funds[i] = arbitrary(); }
  record->inscription_type_of_bond = arbitrary();
  record->taxation = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->bond_lead_manager_company_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->payment_guarantor_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trustee_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->register_institute_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->payment_agent_code[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->abbreviated_issue_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bond_delisting_reason_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bond_delisted_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->equity_linked_bond_rights_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 60; i++) { record->issue_name_short[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->equity_linked_bond_exercise_price[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->exercise_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_to_start_exercising[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_to_end_exercising[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->institution_code[i] = arbitrary(); }
  record->record_date_of_dividend_payout = arbitrary();
  record->profit_participating_accum_status = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->issue_code_of_post_exercise[i] = arbitrary(); }
  record->amortization_type_code = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->level_payment_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_months_for_grace[i] = arbitrary(); }
  record->interest_type_code_during_amortization = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->number_of_amortization[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->interest_rate_decision_other_base_rate_name[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->spread[i] = arbitrary(); }
  record->timing_of_interest_rate_decision_type_code = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->upper_limit_coupon_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->lower_limit_coupon_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->the_date_to_decide_interest_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->first_call_exercise_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->first_call_exercise_end_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->second_call_exercise_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->second_call_exercise_end_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->first_put_exercise_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->first_put_exercise_end_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->second_put_exercise_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->second_put_exercise_end_date[i] = arbitrary(); }
  record->coupon_payment_decision_code_for_bank_holidays = arbitrary();
  record->hybrid_bond = arbitrary();
  record->co_cos_type_code = arbitrary();
  record->coupon_rate_confirmation = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->principal_guranteed_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->participating_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->maximum_yield[i] = arbitrary(); }
  record->strip_bond_type_code = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->original_bond_type_code_subjec_to_strip[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->unstripped_balance[i] = arbitrary(); }
  record->inflation_indexed_category = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->reference_index_for_issue_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->coupon_rate_decision_base_rate_type_code[i] = arbitrary(); }
  record->bond_odd_lot_days_base_interest_type_code = arbitrary();
  record->base_interest_rate_on_bank_holidays_type_code = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->accrued_interest_rate_on_bank_holidays_type_code[i] = arbitrary(); }
  record->principal_payment_methods_on_bank_holidays_type_code = arbitrary();
  record->principal_base_rate_on_bank_holidays_type_code = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->principal_accrued_interest_rate_on_bank_holidays_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->stop_out_rate[i] = arbitrary(); }
  record->crowdfunding = arbitrary();
  record->end_keyword = arbitrary();
}

/* Bonds Isin Issue Information Message to the wire: 898 bytes from at, returning where the next byte goes */
static size_t encode_bonds_isin_issue_information_message(const BondsIsinIssueInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transmission_date[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->transmission_time_long[i]; }
  wire[at++] = record->record_process_category;
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name_in_en[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->issuer_code[i]; }
  wire[at++] = record->bond_listing_type_code;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->bond_category_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bond_type_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->special_bond_issue_code[i]; }
  wire[at++] = record->mb_type_code;
  wire[at++] = record->bond_guaranteed_type_code;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->guaranteed_rate_for_payment[i]; }
  wire[at++] = record->other_types_of_bond;
  wire[at++] = record->option_embedded_type_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->coupon_payment_type_code[i]; }
  wire[at++] = record->risk_bond_redemption_type_code;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->bond_issuance_type_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->securitization_type_code[i]; }
  wire[at++] = record->redemption_priority_type_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->listing_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->issue_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->redemption_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sale_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->the_1_st_coupon_payment_date[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bond_issuance_rate[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->coupon_rate[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->monthly_cycle_of_coupon_payment[i]; }
  wire[at++] = record->coupon_payment_timing_code;
  wire[at++] = record->interest_payment;
  wire[at++] = record->coupon_payment_date_type_code;
  wire[at++] = record->decimal_point_of_coupon_type_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_months_to_pay_interest[i]; }
  wire[at++] = record->bond_sale_type_code;
  wire[at++] = record->pre_issue_sale_coupon_payment_type_code;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->issuing_amount[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->listed_amount[i]; }
  wire[at++] = record->confirmation_of_lump_sum_payment;
  wire[at++] = record->currency_type_code;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->redemption_ratio_at_maturity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->yield_to_maturity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->guaranteed_yield_effective_date[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->additional_yield[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->additional_yield_effective_date[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->facility_fund[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->maintenance_fund[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->loan_fund[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->other_funds[i]; }
  wire[at++] = record->inscription_type_of_bond;
  wire[at++] = record->taxation;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bond_lead_manager_company_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->payment_guarantor_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trustee_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->register_institute_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->payment_agent_code[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->abbreviated_issue_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bond_delisting_reason_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bond_delisted_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->equity_linked_bond_rights_type_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->issue_name_short[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->equity_linked_bond_exercise_price[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->exercise_ratio[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_to_start_exercising[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_to_end_exercising[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->institution_code[i]; }
  wire[at++] = record->record_date_of_dividend_payout;
  wire[at++] = record->profit_participating_accum_status;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->issue_code_of_post_exercise[i]; }
  wire[at++] = record->amortization_type_code;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->level_payment_amount[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_months_for_grace[i]; }
  wire[at++] = record->interest_type_code_during_amortization;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->number_of_amortization[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->interest_rate_decision_other_base_rate_name[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->spread[i]; }
  wire[at++] = record->timing_of_interest_rate_decision_type_code;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->upper_limit_coupon_rate[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->lower_limit_coupon_rate[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->the_date_to_decide_interest_rate[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->first_call_exercise_start_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->first_call_exercise_end_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->second_call_exercise_start_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->second_call_exercise_end_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->first_put_exercise_start_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->first_put_exercise_end_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->second_put_exercise_start_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->second_put_exercise_end_date[i]; }
  wire[at++] = record->coupon_payment_decision_code_for_bank_holidays;
  wire[at++] = record->hybrid_bond;
  wire[at++] = record->co_cos_type_code;
  wire[at++] = record->coupon_rate_confirmation;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->principal_guranteed_rate[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->participating_rate[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->maximum_yield[i]; }
  wire[at++] = record->strip_bond_type_code;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->original_bond_type_code_subjec_to_strip[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->unstripped_balance[i]; }
  wire[at++] = record->inflation_indexed_category;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->reference_index_for_issue_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->coupon_rate_decision_base_rate_type_code[i]; }
  wire[at++] = record->bond_odd_lot_days_base_interest_type_code;
  wire[at++] = record->base_interest_rate_on_bank_holidays_type_code;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->accrued_interest_rate_on_bank_holidays_type_code[i]; }
  wire[at++] = record->principal_payment_methods_on_bank_holidays_type_code;
  wire[at++] = record->principal_base_rate_on_bank_holidays_type_code;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->principal_accrued_interest_rate_on_bank_holidays_type_code[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->stop_out_rate[i]; }
  wire[at++] = record->crowdfunding;
  wire[at++] = record->end_keyword;

  return at;
}

/* Bonds Isin Issue Information Message off the wire: 898 bytes from at, returning where the next byte lies */
static size_t decode_bonds_isin_issue_information_message(BondsIsinIssueInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transmission_date[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->transmission_time_long[i] = wire[at++]; }
  record->record_process_category = wire[at++];
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name_in_en[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->issuer_code[i] = wire[at++]; }
  record->bond_listing_type_code = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->bond_category_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bond_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->special_bond_issue_code[i] = wire[at++]; }
  record->mb_type_code = wire[at++];
  record->bond_guaranteed_type_code = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->guaranteed_rate_for_payment[i] = wire[at++]; }
  record->other_types_of_bond = wire[at++];
  record->option_embedded_type_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->coupon_payment_type_code[i] = wire[at++]; }
  record->risk_bond_redemption_type_code = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->bond_issuance_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->securitization_type_code[i] = wire[at++]; }
  record->redemption_priority_type_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->issue_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->redemption_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sale_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->the_1_st_coupon_payment_date[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bond_issuance_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->coupon_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->monthly_cycle_of_coupon_payment[i] = wire[at++]; }
  record->coupon_payment_timing_code = wire[at++];
  record->interest_payment = wire[at++];
  record->coupon_payment_date_type_code = wire[at++];
  record->decimal_point_of_coupon_type_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->number_of_months_to_pay_interest[i] = wire[at++]; }
  record->bond_sale_type_code = wire[at++];
  record->pre_issue_sale_coupon_payment_type_code = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->issuing_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->listed_amount[i] = wire[at++]; }
  record->confirmation_of_lump_sum_payment = wire[at++];
  record->currency_type_code = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->redemption_ratio_at_maturity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->yield_to_maturity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->guaranteed_yield_effective_date[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->additional_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->additional_yield_effective_date[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->facility_fund[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->maintenance_fund[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->loan_fund[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->other_funds[i] = wire[at++]; }
  record->inscription_type_of_bond = wire[at++];
  record->taxation = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->bond_lead_manager_company_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->payment_guarantor_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trustee_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->register_institute_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->payment_agent_code[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->abbreviated_issue_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bond_delisting_reason_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bond_delisted_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->equity_linked_bond_rights_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 60; i++) { record->issue_name_short[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->equity_linked_bond_exercise_price[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->exercise_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_to_start_exercising[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_to_end_exercising[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->institution_code[i] = wire[at++]; }
  record->record_date_of_dividend_payout = wire[at++];
  record->profit_participating_accum_status = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->issue_code_of_post_exercise[i] = wire[at++]; }
  record->amortization_type_code = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->level_payment_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_months_for_grace[i] = wire[at++]; }
  record->interest_type_code_during_amortization = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->number_of_amortization[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->interest_rate_decision_other_base_rate_name[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->spread[i] = wire[at++]; }
  record->timing_of_interest_rate_decision_type_code = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->upper_limit_coupon_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->lower_limit_coupon_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->the_date_to_decide_interest_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->first_call_exercise_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->first_call_exercise_end_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->second_call_exercise_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->second_call_exercise_end_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->first_put_exercise_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->first_put_exercise_end_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->second_put_exercise_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->second_put_exercise_end_date[i] = wire[at++]; }
  record->coupon_payment_decision_code_for_bank_holidays = wire[at++];
  record->hybrid_bond = wire[at++];
  record->co_cos_type_code = wire[at++];
  record->coupon_rate_confirmation = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->principal_guranteed_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->participating_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->maximum_yield[i] = wire[at++]; }
  record->strip_bond_type_code = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->original_bond_type_code_subjec_to_strip[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->unstripped_balance[i] = wire[at++]; }
  record->inflation_indexed_category = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->reference_index_for_issue_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->coupon_rate_decision_base_rate_type_code[i] = wire[at++]; }
  record->bond_odd_lot_days_base_interest_type_code = wire[at++];
  record->base_interest_rate_on_bank_holidays_type_code = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->accrued_interest_rate_on_bank_holidays_type_code[i] = wire[at++]; }
  record->principal_payment_methods_on_bank_holidays_type_code = wire[at++];
  record->principal_base_rate_on_bank_holidays_type_code = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->principal_accrued_interest_rate_on_bank_holidays_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->stop_out_rate[i] = wire[at++]; }
  record->crowdfunding = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Bonds Isin Issue Information Message is what was written, byte for byte */
static void equal_bonds_isin_issue_information_message(const BondsIsinIssueInformationMessage *read, const BondsIsinIssueInformationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transmission_date[i] == written->transmission_date[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->transmission_time_long[i] == written->transmission_time_long[i]); }
  assert(read->record_process_category == written->record_process_category);
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name[i] == written->abbreviated_issue_name[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name_in_en[i] == written->abbreviated_issue_name_in_en[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->issuer_code[i] == written->issuer_code[i]); }
  assert(read->bond_listing_type_code == written->bond_listing_type_code);
  for (size_t i = 0; i < 6; i++) { assert(read->bond_category_code[i] == written->bond_category_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bond_type_code[i] == written->bond_type_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->special_bond_issue_code[i] == written->special_bond_issue_code[i]); }
  assert(read->mb_type_code == written->mb_type_code);
  assert(read->bond_guaranteed_type_code == written->bond_guaranteed_type_code);
  for (size_t i = 0; i < 13; i++) { assert(read->guaranteed_rate_for_payment[i] == written->guaranteed_rate_for_payment[i]); }
  assert(read->other_types_of_bond == written->other_types_of_bond);
  assert(read->option_embedded_type_code == written->option_embedded_type_code);
  for (size_t i = 0; i < 2; i++) { assert(read->coupon_payment_type_code[i] == written->coupon_payment_type_code[i]); }
  assert(read->risk_bond_redemption_type_code == written->risk_bond_redemption_type_code);
  for (size_t i = 0; i < 3; i++) { assert(read->bond_issuance_type_code[i] == written->bond_issuance_type_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->securitization_type_code[i] == written->securitization_type_code[i]); }
  assert(read->redemption_priority_type_code == written->redemption_priority_type_code);
  for (size_t i = 0; i < 8; i++) { assert(read->listing_date[i] == written->listing_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->issue_date[i] == written->issue_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->redemption_date[i] == written->redemption_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sale_date[i] == written->sale_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->the_1_st_coupon_payment_date[i] == written->the_1_st_coupon_payment_date[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bond_issuance_rate[i] == written->bond_issuance_rate[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->coupon_rate[i] == written->coupon_rate[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->monthly_cycle_of_coupon_payment[i] == written->monthly_cycle_of_coupon_payment[i]); }
  assert(read->coupon_payment_timing_code == written->coupon_payment_timing_code);
  assert(read->interest_payment == written->interest_payment);
  assert(read->coupon_payment_date_type_code == written->coupon_payment_date_type_code);
  assert(read->decimal_point_of_coupon_type_code == written->decimal_point_of_coupon_type_code);
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_months_to_pay_interest[i] == written->number_of_months_to_pay_interest[i]); }
  assert(read->bond_sale_type_code == written->bond_sale_type_code);
  assert(read->pre_issue_sale_coupon_payment_type_code == written->pre_issue_sale_coupon_payment_type_code);
  for (size_t i = 0; i < 22; i++) { assert(read->issuing_amount[i] == written->issuing_amount[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->listed_amount[i] == written->listed_amount[i]); }
  assert(read->confirmation_of_lump_sum_payment == written->confirmation_of_lump_sum_payment);
  assert(read->currency_type_code == written->currency_type_code);
  for (size_t i = 0; i < 13; i++) { assert(read->redemption_ratio_at_maturity[i] == written->redemption_ratio_at_maturity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->yield_to_maturity[i] == written->yield_to_maturity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->guaranteed_yield_effective_date[i] == written->guaranteed_yield_effective_date[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->additional_yield[i] == written->additional_yield[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->additional_yield_effective_date[i] == written->additional_yield_effective_date[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->facility_fund[i] == written->facility_fund[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->maintenance_fund[i] == written->maintenance_fund[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->loan_fund[i] == written->loan_fund[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->other_funds[i] == written->other_funds[i]); }
  assert(read->inscription_type_of_bond == written->inscription_type_of_bond);
  assert(read->taxation == written->taxation);
  for (size_t i = 0; i < 4; i++) { assert(read->bond_lead_manager_company_code[i] == written->bond_lead_manager_company_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->payment_guarantor_code[i] == written->payment_guarantor_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trustee_code[i] == written->trustee_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->register_institute_code[i] == written->register_institute_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->payment_agent_code[i] == written->payment_agent_code[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->abbreviated_issue_code[i] == written->abbreviated_issue_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bond_delisting_reason_code[i] == written->bond_delisting_reason_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bond_delisted_date[i] == written->bond_delisted_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->equity_linked_bond_rights_type_code[i] == written->equity_linked_bond_rights_type_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 60; i++) { assert(read->issue_name_short[i] == written->issue_name_short[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->equity_linked_bond_exercise_price[i] == written->equity_linked_bond_exercise_price[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->exercise_ratio[i] == written->exercise_ratio[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_to_start_exercising[i] == written->date_to_start_exercising[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_to_end_exercising[i] == written->date_to_end_exercising[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->institution_code[i] == written->institution_code[i]); }
  assert(read->record_date_of_dividend_payout == written->record_date_of_dividend_payout);
  assert(read->profit_participating_accum_status == written->profit_participating_accum_status);
  for (size_t i = 0; i < 12; i++) { assert(read->issue_code_of_post_exercise[i] == written->issue_code_of_post_exercise[i]); }
  assert(read->amortization_type_code == written->amortization_type_code);
  for (size_t i = 0; i < 22; i++) { assert(read->level_payment_amount[i] == written->level_payment_amount[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_months_for_grace[i] == written->number_of_months_for_grace[i]); }
  assert(read->interest_type_code_during_amortization == written->interest_type_code_during_amortization);
  for (size_t i = 0; i < 5; i++) { assert(read->number_of_amortization[i] == written->number_of_amortization[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->interest_rate_decision_other_base_rate_name[i] == written->interest_rate_decision_other_base_rate_name[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->spread[i] == written->spread[i]); }
  assert(read->timing_of_interest_rate_decision_type_code == written->timing_of_interest_rate_decision_type_code);
  for (size_t i = 0; i < 14; i++) { assert(read->upper_limit_coupon_rate[i] == written->upper_limit_coupon_rate[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->lower_limit_coupon_rate[i] == written->lower_limit_coupon_rate[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->the_date_to_decide_interest_rate[i] == written->the_date_to_decide_interest_rate[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->first_call_exercise_start_date[i] == written->first_call_exercise_start_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->first_call_exercise_end_date[i] == written->first_call_exercise_end_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->second_call_exercise_start_date[i] == written->second_call_exercise_start_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->second_call_exercise_end_date[i] == written->second_call_exercise_end_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->first_put_exercise_start_date[i] == written->first_put_exercise_start_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->first_put_exercise_end_date[i] == written->first_put_exercise_end_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->second_put_exercise_start_date[i] == written->second_put_exercise_start_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->second_put_exercise_end_date[i] == written->second_put_exercise_end_date[i]); }
  assert(read->coupon_payment_decision_code_for_bank_holidays == written->coupon_payment_decision_code_for_bank_holidays);
  assert(read->hybrid_bond == written->hybrid_bond);
  assert(read->co_cos_type_code == written->co_cos_type_code);
  assert(read->coupon_rate_confirmation == written->coupon_rate_confirmation);
  for (size_t i = 0; i < 13; i++) { assert(read->principal_guranteed_rate[i] == written->principal_guranteed_rate[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->participating_rate[i] == written->participating_rate[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->maximum_yield[i] == written->maximum_yield[i]); }
  assert(read->strip_bond_type_code == written->strip_bond_type_code);
  for (size_t i = 0; i < 12; i++) { assert(read->original_bond_type_code_subjec_to_strip[i] == written->original_bond_type_code_subjec_to_strip[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->unstripped_balance[i] == written->unstripped_balance[i]); }
  assert(read->inflation_indexed_category == written->inflation_indexed_category);
  for (size_t i = 0; i < 11; i++) { assert(read->reference_index_for_issue_date[i] == written->reference_index_for_issue_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->coupon_rate_decision_base_rate_type_code[i] == written->coupon_rate_decision_base_rate_type_code[i]); }
  assert(read->bond_odd_lot_days_base_interest_type_code == written->bond_odd_lot_days_base_interest_type_code);
  assert(read->base_interest_rate_on_bank_holidays_type_code == written->base_interest_rate_on_bank_holidays_type_code);
  for (size_t i = 0; i < 14; i++) { assert(read->accrued_interest_rate_on_bank_holidays_type_code[i] == written->accrued_interest_rate_on_bank_holidays_type_code[i]); }
  assert(read->principal_payment_methods_on_bank_holidays_type_code == written->principal_payment_methods_on_bank_holidays_type_code);
  assert(read->principal_base_rate_on_bank_holidays_type_code == written->principal_base_rate_on_bank_holidays_type_code);
  for (size_t i = 0; i < 14; i++) { assert(read->principal_accrued_interest_rate_on_bank_holidays_type_code[i] == written->principal_accrued_interest_rate_on_bank_holidays_type_code[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->stop_out_rate[i] == written->stop_out_rate[i]); }
  assert(read->crowdfunding == written->crowdfunding);
  assert(read->end_keyword == written->end_keyword);
}

/* Bonds Isin Issue Information Message: written and read back, then read and written back */
static void check_bonds_isin_issue_information_message(void) {
  BondsIsinIssueInformationMessage sent;
  BondsIsinIssueInformationMessage got;
  uint8_t wire[898];
  uint8_t again[898];

  any_bonds_isin_issue_information_message(&sent);
  assert(encode_bonds_isin_issue_information_message(&sent, wire, 0) == 898);
  assert(decode_bonds_isin_issue_information_message(&got, wire, 0) == 898);
  equal_bonds_isin_issue_information_message(&got, &sent);

  for (size_t i = 0; i < 898; i++) { wire[i] = arbitrary(); }
  assert(decode_bonds_isin_issue_information_message(&got, wire, 0) == 898);
  assert(encode_bonds_isin_issue_information_message(&got, again, 0) == 898);
  for (size_t i = 0; i < 898; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bonds Isin Information Text Message: 649 bytes -------------------------- */

/* Bonds ISIN Information TEXT (IFMSRID0040) — Bonds A. Free-form text fields: issue name, conditions, ELS conditions. */
typedef struct {
  uint8_t message_sequence_number[8];         /* bytes 0 to 7 */
  uint8_t isin_code[12];                      /* bytes 8 to 19 */
  uint8_t transmission_date[8];               /* bytes 20 to 27 */
  uint8_t issue_name_long[80];                /* bytes 28 to 107 */
  uint8_t english_issue_name[80];             /* bytes 108 to 187 */
  uint8_t unusual_issuance_condition[60];     /* bytes 188 to 247 */
  uint8_t reason_for_exercising_a_call[50];   /* bytes 248 to 297 */
  uint8_t reason_for_exercising_a_put[50];    /* bytes 298 to 347 */
  uint8_t contents_of_underlying_asset[100];  /* bytes 348 to 447 */
  uint8_t els_condition_1[100];               /* bytes 448 to 547 */
  uint8_t els_condition_2[100];               /* bytes 548 to 647 */
  uint8_t end_keyword;                        /* byte 648 */
} BondsIsinInformationTextMessage;

/* any Bonds Isin Information Text Message at all: every byte one the checker chooses */
static void any_bonds_isin_information_text_message(BondsIsinInformationTextMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transmission_date[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->issue_name_long[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->english_issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 60; i++) { record->unusual_issuance_condition[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->reason_for_exercising_a_call[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->reason_for_exercising_a_put[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->contents_of_underlying_asset[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->els_condition_1[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->els_condition_2[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Bonds Isin Information Text Message to the wire: 649 bytes from at, returning where the next byte goes */
static size_t encode_bonds_isin_information_text_message(const BondsIsinInformationTextMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transmission_date[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->issue_name_long[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->english_issue_name[i]; }
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->unusual_issuance_condition[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->reason_for_exercising_a_call[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->reason_for_exercising_a_put[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->contents_of_underlying_asset[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->els_condition_1[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->els_condition_2[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Bonds Isin Information Text Message off the wire: 649 bytes from at, returning where the next byte lies */
static size_t decode_bonds_isin_information_text_message(BondsIsinInformationTextMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transmission_date[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->issue_name_long[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->english_issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 60; i++) { record->unusual_issuance_condition[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->reason_for_exercising_a_call[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->reason_for_exercising_a_put[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->contents_of_underlying_asset[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->els_condition_1[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->els_condition_2[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Bonds Isin Information Text Message is what was written, byte for byte */
static void equal_bonds_isin_information_text_message(const BondsIsinInformationTextMessage *read, const BondsIsinInformationTextMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transmission_date[i] == written->transmission_date[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->issue_name_long[i] == written->issue_name_long[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->english_issue_name[i] == written->english_issue_name[i]); }
  for (size_t i = 0; i < 60; i++) { assert(read->unusual_issuance_condition[i] == written->unusual_issuance_condition[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->reason_for_exercising_a_call[i] == written->reason_for_exercising_a_call[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->reason_for_exercising_a_put[i] == written->reason_for_exercising_a_put[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->contents_of_underlying_asset[i] == written->contents_of_underlying_asset[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->els_condition_1[i] == written->els_condition_1[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->els_condition_2[i] == written->els_condition_2[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Bonds Isin Information Text Message: written and read back, then read and written back */
static void check_bonds_isin_information_text_message(void) {
  BondsIsinInformationTextMessage sent;
  BondsIsinInformationTextMessage got;
  uint8_t wire[649];
  uint8_t again[649];

  any_bonds_isin_information_text_message(&sent);
  assert(encode_bonds_isin_information_text_message(&sent, wire, 0) == 649);
  assert(decode_bonds_isin_information_text_message(&got, wire, 0) == 649);
  equal_bonds_isin_information_text_message(&got, &sent);

  for (size_t i = 0; i < 649; i++) { wire[i] = arbitrary(); }
  assert(decode_bonds_isin_information_text_message(&got, wire, 0) == 649);
  assert(encode_bonds_isin_information_text_message(&got, again, 0) == 649);
  for (size_t i = 0; i < 649; i++) { assert(again[i] == wire[i]); }
}

/* ---- Baby Bonds Quote Message: 877 bytes ------------------------------------- */

/* Baby Bonds Quote (IFMSRPD0024) — Bonds A SMB. 5-level depth of book with yields, per-Type breakdown. */
typedef struct {
  uint8_t message_sequence_number[8];                   /* bytes 0 to 7 */
  uint8_t board_id[2];                                  /* bytes 8 to 9 */
  uint8_t session_id[2];                                /* bytes 10 to 11 */
  uint8_t isin_code[12];                                /* bytes 12 to 23 */
  uint8_t processing_time_of_trading_system[12];        /* bytes 24 to 35 */
  uint8_t ask_level_1_price[11];                        /* bytes 36 to 46 */
  uint8_t bid_level_1_price[11];                        /* bytes 47 to 57 */
  uint8_t ask_level_1_remaining_quantity[15];           /* bytes 58 to 72 */
  uint8_t bid_level_1_remaining_quantity[15];           /* bytes 73 to 87 */
  uint8_t ask_level_1_yield[13];                        /* bytes 88 to 100 */
  uint8_t bid_level_1_yield[13];                        /* bytes 101 to 113 */
  uint8_t ask_per_type_level_1_price[11];               /* bytes 114 to 124 */
  uint8_t bid_per_type_level_1_price[11];               /* bytes 125 to 135 */
  uint8_t ask_per_type_level_1_remaining_quantity[15];  /* bytes 136 to 150 */
  uint8_t bid_per_type_level_1_remaining_quantity[15];  /* bytes 151 to 165 */
  uint8_t ask_per_type_level_1_yield[13];               /* bytes 166 to 178 */
  uint8_t bid_per_type_level_1_yield[13];               /* bytes 179 to 191 */
  uint8_t ask_level_2_price[11];                        /* bytes 192 to 202 */
  uint8_t bid_level_2_price[11];                        /* bytes 203 to 213 */
  uint8_t ask_level_2_remaining_quantity[15];           /* bytes 214 to 228 */
  uint8_t bid_level_2_remaining_quantity[15];           /* bytes 229 to 243 */
  uint8_t ask_level_2_yield[13];                        /* bytes 244 to 256 */
  uint8_t bid_level_2_yield[13];                        /* bytes 257 to 269 */
  uint8_t ask_per_type_level_2_price[11];               /* bytes 270 to 280 */
  uint8_t bid_per_type_level_2_price[11];               /* bytes 281 to 291 */
  uint8_t ask_per_type_level_2_remaining_quantity[15];  /* bytes 292 to 306 */
  uint8_t bid_per_type_level_2_remaining_quantity[15];  /* bytes 307 to 321 */
  uint8_t ask_per_type_level_2_yield[13];               /* bytes 322 to 334 */
  uint8_t bid_per_type_level_2_yield[13];               /* bytes 335 to 347 */
  uint8_t ask_level_3_price[11];                        /* bytes 348 to 358 */
  uint8_t bid_level_3_price[11];                        /* bytes 359 to 369 */
  uint8_t ask_level_3_remaining_quantity[15];           /* bytes 370 to 384 */
  uint8_t bid_level_3_remaining_quantity[15];           /* bytes 385 to 399 */
  uint8_t ask_level_3_yield[13];                        /* bytes 400 to 412 */
  uint8_t bid_level_3_yield[13];                        /* bytes 413 to 425 */
  uint8_t ask_per_type_level_3_price[11];               /* bytes 426 to 436 */
  uint8_t bid_per_type_level_3_price[11];               /* bytes 437 to 447 */
  uint8_t ask_per_type_level_3_remaining_quantity[15];  /* bytes 448 to 462 */
  uint8_t bid_per_type_level_3_remaining_quantity[15];  /* bytes 463 to 477 */
  uint8_t ask_per_type_level_3_yield[13];               /* bytes 478 to 490 */
  uint8_t bid_per_type_level_3_yield[13];               /* bytes 491 to 503 */
  uint8_t ask_level_4_price[11];                        /* bytes 504 to 514 */
  uint8_t bid_level_4_price[11];                        /* bytes 515 to 525 */
  uint8_t ask_level_4_remaining_quantity[15];           /* bytes 526 to 540 */
  uint8_t bid_level_4_remaining_quantity[15];           /* bytes 541 to 555 */
  uint8_t ask_level_4_yield[13];                        /* bytes 556 to 568 */
  uint8_t bid_level_4_yield[13];                        /* bytes 569 to 581 */
  uint8_t ask_per_type_level_4_price[11];               /* bytes 582 to 592 */
  uint8_t bid_per_type_level_4_price[11];               /* bytes 593 to 603 */
  uint8_t ask_per_type_level_4_remaining_quantity[15];  /* bytes 604 to 618 */
  uint8_t bid_per_type_level_4_remaining_quantity[15];  /* bytes 619 to 633 */
  uint8_t ask_per_type_level_4_yield[13];               /* bytes 634 to 646 */
  uint8_t bid_per_type_level_4_yield[13];               /* bytes 647 to 659 */
  uint8_t ask_level_5_price[11];                        /* bytes 660 to 670 */
  uint8_t bid_level_5_price[11];                        /* bytes 671 to 681 */
  uint8_t ask_level_5_remaining_quantity[15];           /* bytes 682 to 696 */
  uint8_t bid_level_5_remaining_quantity[15];           /* bytes 697 to 711 */
  uint8_t ask_level_5_yield[13];                        /* bytes 712 to 724 */
  uint8_t bid_level_5_yield[13];                        /* bytes 725 to 737 */
  uint8_t ask_per_type_level_5_price[11];               /* bytes 738 to 748 */
  uint8_t bid_per_type_level_5_price[11];               /* bytes 749 to 759 */
  uint8_t ask_per_type_level_5_remaining_quantity[15];  /* bytes 760 to 774 */
  uint8_t bid_per_type_level_5_remaining_quantity[15];  /* bytes 775 to 789 */
  uint8_t ask_per_type_level_5_yield[13];               /* bytes 790 to 802 */
  uint8_t bid_per_type_level_5_yield[13];               /* bytes 803 to 815 */
  uint8_t ask_total_remaining_quantity[15];             /* bytes 816 to 830 */
  uint8_t bid_total_remaining_quantity[15];             /* bytes 831 to 845 */
  uint8_t ask_per_type_total_remaining_quantity[15];    /* bytes 846 to 860 */
  uint8_t bid_per_type_total_remaining_quantity[15];    /* bytes 861 to 875 */
  uint8_t end_keyword;                                  /* byte 876 */
} BabyBondsQuoteMessage;

/* any Baby Bonds Quote Message at all: every byte one the checker chooses */
static void any_baby_bonds_quote_message(BabyBondsQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_1_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_1_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_1_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_1_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_2_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_2_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_2_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_2_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_3_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_3_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_3_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_3_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_4_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_4_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_4_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_4_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_5_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_5_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_5_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_5_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_total_remaining_quantity[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Baby Bonds Quote Message to the wire: 877 bytes from at, returning where the next byte goes */
static size_t encode_baby_bonds_quote_message(const BabyBondsQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_1_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_1_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_1_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_per_type_level_1_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_per_type_level_1_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_2_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_2_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_2_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_per_type_level_2_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_per_type_level_2_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_3_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_3_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_3_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_per_type_level_3_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_per_type_level_3_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_4_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_4_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_4_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_per_type_level_4_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_per_type_level_4_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_5_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_5_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_5_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_per_type_level_5_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_per_type_level_5_yield[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_total_remaining_quantity[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Baby Bonds Quote Message off the wire: 877 bytes from at, returning where the next byte lies */
static size_t decode_baby_bonds_quote_message(BabyBondsQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_1_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_1_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_1_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_1_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_2_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_2_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_2_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_2_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_3_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_3_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_3_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_3_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_4_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_4_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_4_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_4_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_5_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_5_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_5_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_5_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_total_remaining_quantity[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Baby Bonds Quote Message is what was written, byte for byte */
static void equal_baby_bonds_quote_message(const BabyBondsQuoteMessage *read, const BabyBondsQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_1_remaining_quantity[i] == written->ask_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_1_remaining_quantity[i] == written->bid_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_1_yield[i] == written->ask_level_1_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_1_yield[i] == written->bid_level_1_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_1_price[i] == written->ask_per_type_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_1_price[i] == written->bid_per_type_level_1_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_1_remaining_quantity[i] == written->ask_per_type_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_1_remaining_quantity[i] == written->bid_per_type_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_per_type_level_1_yield[i] == written->ask_per_type_level_1_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_per_type_level_1_yield[i] == written->bid_per_type_level_1_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_2_remaining_quantity[i] == written->ask_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_2_remaining_quantity[i] == written->bid_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_2_yield[i] == written->ask_level_2_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_2_yield[i] == written->bid_level_2_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_2_price[i] == written->ask_per_type_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_2_price[i] == written->bid_per_type_level_2_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_2_remaining_quantity[i] == written->ask_per_type_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_2_remaining_quantity[i] == written->bid_per_type_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_per_type_level_2_yield[i] == written->ask_per_type_level_2_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_per_type_level_2_yield[i] == written->bid_per_type_level_2_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_3_remaining_quantity[i] == written->ask_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_3_remaining_quantity[i] == written->bid_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_3_yield[i] == written->ask_level_3_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_3_yield[i] == written->bid_level_3_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_3_price[i] == written->ask_per_type_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_3_price[i] == written->bid_per_type_level_3_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_3_remaining_quantity[i] == written->ask_per_type_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_3_remaining_quantity[i] == written->bid_per_type_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_per_type_level_3_yield[i] == written->ask_per_type_level_3_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_per_type_level_3_yield[i] == written->bid_per_type_level_3_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_4_remaining_quantity[i] == written->ask_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_4_remaining_quantity[i] == written->bid_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_4_yield[i] == written->ask_level_4_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_4_yield[i] == written->bid_level_4_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_4_price[i] == written->ask_per_type_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_4_price[i] == written->bid_per_type_level_4_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_4_remaining_quantity[i] == written->ask_per_type_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_4_remaining_quantity[i] == written->bid_per_type_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_per_type_level_4_yield[i] == written->ask_per_type_level_4_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_per_type_level_4_yield[i] == written->bid_per_type_level_4_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_5_remaining_quantity[i] == written->ask_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_5_remaining_quantity[i] == written->bid_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_5_yield[i] == written->ask_level_5_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_5_yield[i] == written->bid_level_5_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_5_price[i] == written->ask_per_type_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_5_price[i] == written->bid_per_type_level_5_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_5_remaining_quantity[i] == written->ask_per_type_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_5_remaining_quantity[i] == written->bid_per_type_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_per_type_level_5_yield[i] == written->ask_per_type_level_5_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_per_type_level_5_yield[i] == written->bid_per_type_level_5_yield[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_total_remaining_quantity[i] == written->ask_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_total_remaining_quantity[i] == written->bid_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_total_remaining_quantity[i] == written->ask_per_type_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_total_remaining_quantity[i] == written->bid_per_type_total_remaining_quantity[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Baby Bonds Quote Message: written and read back, then read and written back */
static void check_baby_bonds_quote_message(void) {
  BabyBondsQuoteMessage sent;
  BabyBondsQuoteMessage got;
  uint8_t wire[877];
  uint8_t again[877];

  any_baby_bonds_quote_message(&sent);
  assert(encode_baby_bonds_quote_message(&sent, wire, 0) == 877);
  assert(decode_baby_bonds_quote_message(&got, wire, 0) == 877);
  equal_baby_bonds_quote_message(&got, &sent);

  for (size_t i = 0; i < 877; i++) { wire[i] = arbitrary(); }
  assert(decode_baby_bonds_quote_message(&got, wire, 0) == 877);
  assert(encode_baby_bonds_quote_message(&got, again, 0) == 877);
  for (size_t i = 0; i < 877; i++) { assert(again[i] == wire[i]); }
}

/* ---- Repo Quote Message: 1382 bytes ------------------------------------------ */

/* REPO Quote (IFMSRPD0025) — Bonds A RPO. 5-level depth + designated bid levels 1-10 with REPO amounts. */
typedef struct {
  uint8_t message_sequence_number[8];                           /* bytes 0 to 7 */
  uint8_t board_id[2];                                          /* bytes 8 to 9 */
  uint8_t session_id[2];                                        /* bytes 10 to 11 */
  uint8_t isin_code[12];                                        /* bytes 12 to 23 */
  uint8_t processing_time_of_trading_system[12];                /* bytes 24 to 35 */
  uint8_t duration_of_term_repo[4];                             /* bytes 36 to 39 */
  uint8_t ask_level_1_price[11];                                /* bytes 40 to 50 */
  uint8_t bid_level_1_price[11];                                /* bytes 51 to 61 */
  uint8_t ask_level_1_remaining_quantity[15];                   /* bytes 62 to 76 */
  uint8_t bid_level_1_remaining_quantity[15];                   /* bytes 77 to 91 */
  uint8_t ask_level_1_trading_amount[22];                       /* bytes 92 to 113 */
  uint8_t total_bid_level_1_price[11];                          /* bytes 114 to 124 */
  uint8_t total_bid_level_1_remaining_quantity[15];             /* bytes 125 to 139 */
  uint8_t bid_level_1_including_gc;                             /* byte 140 */
  uint8_t ask_per_type_level_1_price[11];                       /* bytes 141 to 151 */
  uint8_t bid_per_type_level_1_price[11];                       /* bytes 152 to 162 */
  uint8_t ask_per_type_level_1_remaining_quantity[15];          /* bytes 163 to 177 */
  uint8_t bid_per_type_level_1_remaining_quantity[15];          /* bytes 178 to 192 */
  uint8_t ask_per_type_level_1_trading_amount[22];              /* bytes 193 to 214 */
  uint8_t ask_level_2_price[11];                                /* bytes 215 to 225 */
  uint8_t bid_level_2_price[11];                                /* bytes 226 to 236 */
  uint8_t ask_level_2_remaining_quantity[15];                   /* bytes 237 to 251 */
  uint8_t bid_level_2_remaining_quantity[15];                   /* bytes 252 to 266 */
  uint8_t ask_level_2_trading_amount[22];                       /* bytes 267 to 288 */
  uint8_t total_bid_level_2_price[11];                          /* bytes 289 to 299 */
  uint8_t total_bid_level_2_remaining_quantity[15];             /* bytes 300 to 314 */
  uint8_t bid_level_2_including_gc;                             /* byte 315 */
  uint8_t ask_per_type_level_2_price[11];                       /* bytes 316 to 326 */
  uint8_t bid_per_type_level_2_price[11];                       /* bytes 327 to 337 */
  uint8_t ask_per_type_level_2_remaining_quantity[15];          /* bytes 338 to 352 */
  uint8_t bid_per_type_level_2_remaining_quantity[15];          /* bytes 353 to 367 */
  uint8_t ask_per_type_level_2_trading_amount[22];              /* bytes 368 to 389 */
  uint8_t ask_level_3_price[11];                                /* bytes 390 to 400 */
  uint8_t bid_level_3_price[11];                                /* bytes 401 to 411 */
  uint8_t ask_level_3_remaining_quantity[15];                   /* bytes 412 to 426 */
  uint8_t bid_level_3_remaining_quantity[15];                   /* bytes 427 to 441 */
  uint8_t ask_level_3_trading_amount[22];                       /* bytes 442 to 463 */
  uint8_t total_bid_level_3_price[11];                          /* bytes 464 to 474 */
  uint8_t total_bid_level_3_remaining_quantity[15];             /* bytes 475 to 489 */
  uint8_t bid_level_3_including_gc;                             /* byte 490 */
  uint8_t ask_per_type_level_3_price[11];                       /* bytes 491 to 501 */
  uint8_t bid_per_type_level_3_price[11];                       /* bytes 502 to 512 */
  uint8_t ask_per_type_level_3_remaining_quantity[15];          /* bytes 513 to 527 */
  uint8_t bid_per_type_level_3_remaining_quantity[15];          /* bytes 528 to 542 */
  uint8_t ask_per_type_level_3_trading_amount[22];              /* bytes 543 to 564 */
  uint8_t ask_level_4_price[11];                                /* bytes 565 to 575 */
  uint8_t bid_level_4_price[11];                                /* bytes 576 to 586 */
  uint8_t ask_level_4_remaining_quantity[15];                   /* bytes 587 to 601 */
  uint8_t bid_level_4_remaining_quantity[15];                   /* bytes 602 to 616 */
  uint8_t ask_level_4_trading_amount[22];                       /* bytes 617 to 638 */
  uint8_t total_bid_level_4_price[11];                          /* bytes 639 to 649 */
  uint8_t total_bid_level_4_remaining_quantity[15];             /* bytes 650 to 664 */
  uint8_t bid_level_4_including_gc;                             /* byte 665 */
  uint8_t ask_per_type_level_4_price[11];                       /* bytes 666 to 676 */
  uint8_t bid_per_type_level_4_price[11];                       /* bytes 677 to 687 */
  uint8_t ask_per_type_level_4_remaining_quantity[15];          /* bytes 688 to 702 */
  uint8_t bid_per_type_level_4_remaining_quantity[15];          /* bytes 703 to 717 */
  uint8_t ask_per_type_level_4_trading_amount[22];              /* bytes 718 to 739 */
  uint8_t ask_level_5_price[11];                                /* bytes 740 to 750 */
  uint8_t bid_level_5_price[11];                                /* bytes 751 to 761 */
  uint8_t ask_level_5_remaining_quantity[15];                   /* bytes 762 to 776 */
  uint8_t bid_level_5_remaining_quantity[15];                   /* bytes 777 to 791 */
  uint8_t ask_level_5_trading_amount[22];                       /* bytes 792 to 813 */
  uint8_t total_bid_level_5_price[11];                          /* bytes 814 to 824 */
  uint8_t total_bid_level_5_remaining_quantity[15];             /* bytes 825 to 839 */
  uint8_t bid_level_5_including_gc;                             /* byte 840 */
  uint8_t ask_per_type_level_5_price[11];                       /* bytes 841 to 851 */
  uint8_t bid_per_type_level_5_price[11];                       /* bytes 852 to 862 */
  uint8_t ask_per_type_level_5_remaining_quantity[15];          /* bytes 863 to 877 */
  uint8_t bid_per_type_level_5_remaining_quantity[15];          /* bytes 878 to 892 */
  uint8_t ask_per_type_level_5_trading_amount[22];              /* bytes 893 to 914 */
  uint8_t ask_total_remaining_quantity[15];                     /* bytes 915 to 929 */
  uint8_t bid_total_remaining_quantity[15];                     /* bytes 930 to 944 */
  uint8_t ask_per_type_total_remaining_quantity[15];            /* bytes 945 to 959 */
  uint8_t bid_per_type_total_remaining_quantity[15];            /* bytes 960 to 974 */
  uint8_t designated_bid_level_1_price[11];                     /* bytes 975 to 985 */
  uint8_t designated_bid_level_1_repo_remaining_quantity[15];   /* bytes 986 to 1000 */
  uint8_t designated_bid_level_1_isin[12];                      /* bytes 1001 to 1012 */
  uint8_t designated_bid_level_2_price[11];                     /* bytes 1013 to 1023 */
  uint8_t designated_bid_level_2_repo_remaining_quantity[15];   /* bytes 1024 to 1038 */
  uint8_t designated_bid_level_2_isin[12];                      /* bytes 1039 to 1050 */
  uint8_t designated_bid_level_3_price[11];                     /* bytes 1051 to 1061 */
  uint8_t designated_bid_level_3_repo_remaining_quantity[15];   /* bytes 1062 to 1076 */
  uint8_t designated_bid_level_3_isin[12];                      /* bytes 1077 to 1088 */
  uint8_t designated_bid_level_4_price[11];                     /* bytes 1089 to 1099 */
  uint8_t designated_bid_level_4_repo_remaining_quantity[15];   /* bytes 1100 to 1114 */
  uint8_t designated_bid_level_4_isin[12];                      /* bytes 1115 to 1126 */
  uint8_t designated_bid_level_5_price[11];                     /* bytes 1127 to 1137 */
  uint8_t designated_bid_level_5_repo_remaining_quantity[15];   /* bytes 1138 to 1152 */
  uint8_t designated_bid_level_5_isin[12];                      /* bytes 1153 to 1164 */
  uint8_t designated_bid_level_6_price[11];                     /* bytes 1165 to 1175 */
  uint8_t designated_bid_level_6_repo_remaining_quantity[15];   /* bytes 1176 to 1190 */
  uint8_t designated_bid_level_6_isin[12];                      /* bytes 1191 to 1202 */
  uint8_t designated_bid_level_7_price[11];                     /* bytes 1203 to 1213 */
  uint8_t designated_bid_level_7_repo_remaining_quantity[15];   /* bytes 1214 to 1228 */
  uint8_t designated_bid_level_7_isin[12];                      /* bytes 1229 to 1240 */
  uint8_t designated_bid_level_8_price[11];                     /* bytes 1241 to 1251 */
  uint8_t designated_bid_level_8_repo_remaining_quantity[15];   /* bytes 1252 to 1266 */
  uint8_t designated_bid_level_8_isin[12];                      /* bytes 1267 to 1278 */
  uint8_t designated_bid_level_9_price[11];                     /* bytes 1279 to 1289 */
  uint8_t designated_bid_level_9_repo_remaining_quantity[15];   /* bytes 1290 to 1304 */
  uint8_t designated_bid_level_9_isin[12];                      /* bytes 1305 to 1316 */
  uint8_t designated_bid_level_10_price[11];                    /* bytes 1317 to 1327 */
  uint8_t designated_bid_level_10_repo_remaining_quantity[15];  /* bytes 1328 to 1342 */
  uint8_t designated_bid_level_10_isin[12];                     /* bytes 1343 to 1354 */
  uint8_t designated_best_bid_price[11];                        /* bytes 1355 to 1365 */
  uint8_t net_bid_per_type_total_remaining_quantity[15];        /* bytes 1366 to 1380 */
  uint8_t end_keyword;                                          /* byte 1381 */
} RepoQuoteMessage;

/* any Repo Quote Message at all: every byte one the checker chooses */
static void any_repo_quote_message(RepoQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->duration_of_term_repo[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_level_1_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_1_remaining_quantity[i] = arbitrary(); }
  record->bid_level_1_including_gc = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_1_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_level_2_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_2_remaining_quantity[i] = arbitrary(); }
  record->bid_level_2_including_gc = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_2_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_level_3_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_3_remaining_quantity[i] = arbitrary(); }
  record->bid_level_3_including_gc = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_3_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_level_4_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_4_remaining_quantity[i] = arbitrary(); }
  record->bid_level_4_including_gc = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_4_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_level_5_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_5_remaining_quantity[i] = arbitrary(); }
  record->bid_level_5_including_gc = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_5_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_1_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_1_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_2_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_2_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_3_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_3_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_4_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_4_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_5_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_5_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_6_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_6_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_6_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_7_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_7_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_7_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_8_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_8_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_8_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_9_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_9_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_9_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_10_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_10_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_10_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->net_bid_per_type_total_remaining_quantity[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Repo Quote Message to the wire: 1382 bytes from at, returning where the next byte goes */
static size_t encode_repo_quote_message(const RepoQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->duration_of_term_repo[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_level_1_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->total_bid_level_1_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->total_bid_level_1_remaining_quantity[i]; }
  wire[at++] = record->bid_level_1_including_gc;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_1_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_per_type_level_1_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_level_2_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->total_bid_level_2_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->total_bid_level_2_remaining_quantity[i]; }
  wire[at++] = record->bid_level_2_including_gc;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_2_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_per_type_level_2_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_level_3_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->total_bid_level_3_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->total_bid_level_3_remaining_quantity[i]; }
  wire[at++] = record->bid_level_3_including_gc;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_3_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_per_type_level_3_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_level_4_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->total_bid_level_4_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->total_bid_level_4_remaining_quantity[i]; }
  wire[at++] = record->bid_level_4_including_gc;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_4_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_per_type_level_4_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_level_5_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->total_bid_level_5_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->total_bid_level_5_remaining_quantity[i]; }
  wire[at++] = record->bid_level_5_including_gc;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_5_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_per_type_level_5_trading_amount[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_1_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_1_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_1_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_2_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_2_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_2_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_3_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_3_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_3_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_4_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_4_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_4_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_5_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_5_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_5_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_6_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_6_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_6_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_7_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_7_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_7_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_8_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_8_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_8_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_9_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_9_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_9_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_10_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_10_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_10_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_best_bid_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->net_bid_per_type_total_remaining_quantity[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Repo Quote Message off the wire: 1382 bytes from at, returning where the next byte lies */
static size_t decode_repo_quote_message(RepoQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->duration_of_term_repo[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_level_1_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_1_remaining_quantity[i] = wire[at++]; }
  record->bid_level_1_including_gc = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_1_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_level_2_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_2_remaining_quantity[i] = wire[at++]; }
  record->bid_level_2_including_gc = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_2_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_level_3_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_3_remaining_quantity[i] = wire[at++]; }
  record->bid_level_3_including_gc = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_3_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_level_4_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_4_remaining_quantity[i] = wire[at++]; }
  record->bid_level_4_including_gc = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_4_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_level_5_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_5_remaining_quantity[i] = wire[at++]; }
  record->bid_level_5_including_gc = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_5_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_1_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_1_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_2_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_2_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_3_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_3_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_4_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_4_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_5_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_5_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_6_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_6_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_6_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_7_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_7_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_7_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_8_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_8_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_8_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_9_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_9_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_9_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_10_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_10_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_10_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->net_bid_per_type_total_remaining_quantity[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Repo Quote Message is what was written, byte for byte */
static void equal_repo_quote_message(const RepoQuoteMessage *read, const RepoQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->duration_of_term_repo[i] == written->duration_of_term_repo[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_1_remaining_quantity[i] == written->ask_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_1_remaining_quantity[i] == written->bid_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_level_1_trading_amount[i] == written->ask_level_1_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->total_bid_level_1_price[i] == written->total_bid_level_1_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->total_bid_level_1_remaining_quantity[i] == written->total_bid_level_1_remaining_quantity[i]); }
  assert(read->bid_level_1_including_gc == written->bid_level_1_including_gc);
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_1_price[i] == written->ask_per_type_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_1_price[i] == written->bid_per_type_level_1_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_1_remaining_quantity[i] == written->ask_per_type_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_1_remaining_quantity[i] == written->bid_per_type_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_per_type_level_1_trading_amount[i] == written->ask_per_type_level_1_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_2_remaining_quantity[i] == written->ask_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_2_remaining_quantity[i] == written->bid_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_level_2_trading_amount[i] == written->ask_level_2_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->total_bid_level_2_price[i] == written->total_bid_level_2_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->total_bid_level_2_remaining_quantity[i] == written->total_bid_level_2_remaining_quantity[i]); }
  assert(read->bid_level_2_including_gc == written->bid_level_2_including_gc);
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_2_price[i] == written->ask_per_type_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_2_price[i] == written->bid_per_type_level_2_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_2_remaining_quantity[i] == written->ask_per_type_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_2_remaining_quantity[i] == written->bid_per_type_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_per_type_level_2_trading_amount[i] == written->ask_per_type_level_2_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_3_remaining_quantity[i] == written->ask_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_3_remaining_quantity[i] == written->bid_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_level_3_trading_amount[i] == written->ask_level_3_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->total_bid_level_3_price[i] == written->total_bid_level_3_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->total_bid_level_3_remaining_quantity[i] == written->total_bid_level_3_remaining_quantity[i]); }
  assert(read->bid_level_3_including_gc == written->bid_level_3_including_gc);
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_3_price[i] == written->ask_per_type_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_3_price[i] == written->bid_per_type_level_3_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_3_remaining_quantity[i] == written->ask_per_type_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_3_remaining_quantity[i] == written->bid_per_type_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_per_type_level_3_trading_amount[i] == written->ask_per_type_level_3_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_4_remaining_quantity[i] == written->ask_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_4_remaining_quantity[i] == written->bid_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_level_4_trading_amount[i] == written->ask_level_4_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->total_bid_level_4_price[i] == written->total_bid_level_4_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->total_bid_level_4_remaining_quantity[i] == written->total_bid_level_4_remaining_quantity[i]); }
  assert(read->bid_level_4_including_gc == written->bid_level_4_including_gc);
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_4_price[i] == written->ask_per_type_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_4_price[i] == written->bid_per_type_level_4_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_4_remaining_quantity[i] == written->ask_per_type_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_4_remaining_quantity[i] == written->bid_per_type_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_per_type_level_4_trading_amount[i] == written->ask_per_type_level_4_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_5_remaining_quantity[i] == written->ask_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_5_remaining_quantity[i] == written->bid_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_level_5_trading_amount[i] == written->ask_level_5_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->total_bid_level_5_price[i] == written->total_bid_level_5_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->total_bid_level_5_remaining_quantity[i] == written->total_bid_level_5_remaining_quantity[i]); }
  assert(read->bid_level_5_including_gc == written->bid_level_5_including_gc);
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_5_price[i] == written->ask_per_type_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_5_price[i] == written->bid_per_type_level_5_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_5_remaining_quantity[i] == written->ask_per_type_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_5_remaining_quantity[i] == written->bid_per_type_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_per_type_level_5_trading_amount[i] == written->ask_per_type_level_5_trading_amount[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_total_remaining_quantity[i] == written->ask_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_total_remaining_quantity[i] == written->bid_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_total_remaining_quantity[i] == written->ask_per_type_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_total_remaining_quantity[i] == written->bid_per_type_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_1_price[i] == written->designated_bid_level_1_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_1_repo_remaining_quantity[i] == written->designated_bid_level_1_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_1_isin[i] == written->designated_bid_level_1_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_2_price[i] == written->designated_bid_level_2_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_2_repo_remaining_quantity[i] == written->designated_bid_level_2_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_2_isin[i] == written->designated_bid_level_2_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_3_price[i] == written->designated_bid_level_3_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_3_repo_remaining_quantity[i] == written->designated_bid_level_3_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_3_isin[i] == written->designated_bid_level_3_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_4_price[i] == written->designated_bid_level_4_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_4_repo_remaining_quantity[i] == written->designated_bid_level_4_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_4_isin[i] == written->designated_bid_level_4_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_5_price[i] == written->designated_bid_level_5_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_5_repo_remaining_quantity[i] == written->designated_bid_level_5_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_5_isin[i] == written->designated_bid_level_5_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_6_price[i] == written->designated_bid_level_6_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_6_repo_remaining_quantity[i] == written->designated_bid_level_6_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_6_isin[i] == written->designated_bid_level_6_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_7_price[i] == written->designated_bid_level_7_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_7_repo_remaining_quantity[i] == written->designated_bid_level_7_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_7_isin[i] == written->designated_bid_level_7_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_8_price[i] == written->designated_bid_level_8_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_8_repo_remaining_quantity[i] == written->designated_bid_level_8_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_8_isin[i] == written->designated_bid_level_8_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_9_price[i] == written->designated_bid_level_9_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_9_repo_remaining_quantity[i] == written->designated_bid_level_9_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_9_isin[i] == written->designated_bid_level_9_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_10_price[i] == written->designated_bid_level_10_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_10_repo_remaining_quantity[i] == written->designated_bid_level_10_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_10_isin[i] == written->designated_bid_level_10_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_best_bid_price[i] == written->designated_best_bid_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->net_bid_per_type_total_remaining_quantity[i] == written->net_bid_per_type_total_remaining_quantity[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Repo Quote Message: written and read back, then read and written back */
static void check_repo_quote_message(void) {
  RepoQuoteMessage sent;
  RepoQuoteMessage got;
  uint8_t wire[1382];
  uint8_t again[1382];

  any_repo_quote_message(&sent);
  assert(encode_repo_quote_message(&sent, wire, 0) == 1382);
  assert(decode_repo_quote_message(&got, wire, 0) == 1382);
  equal_repo_quote_message(&got, &sent);

  for (size_t i = 0; i < 1382; i++) { wire[i] = arbitrary(); }
  assert(decode_repo_quote_message(&got, wire, 0) == 1382);
  assert(encode_repo_quote_message(&got, again, 0) == 1382);
  for (size_t i = 0; i < 1382; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bonds Total Remaining Volume On Quotes Message: 101 bytes --------------- */

/* General Bonds / Baby Bonds Total Remaining Volume on Quotes (IFMSRPD0026) — Bonds A BND (Regular Bonds). */
typedef struct {
  uint8_t message_sequence_number[8];                 /* bytes 0 to 7 */
  uint8_t board_id[2];                                /* bytes 8 to 9 */
  uint8_t isin_code[12];                              /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];        /* bytes 22 to 27 */
  uint8_t processing_time_of_trading_system[12];      /* bytes 28 to 39 */
  uint8_t ask_total_remaining_quantity[15];           /* bytes 40 to 54 */
  uint8_t bid_total_remaining_quantity[15];           /* bytes 55 to 69 */
  uint8_t ask_per_type_total_remaining_quantity[15];  /* bytes 70 to 84 */
  uint8_t bid_per_type_total_remaining_quantity[15];  /* bytes 85 to 99 */
  uint8_t end_keyword;                                /* byte 100 */
} BondsTotalRemainingVolumeOnQuotesMessage;

/* any Bonds Total Remaining Volume On Quotes Message at all: every byte one the checker chooses */
static void any_bonds_total_remaining_volume_on_quotes_message(BondsTotalRemainingVolumeOnQuotesMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_total_remaining_quantity[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Bonds Total Remaining Volume On Quotes Message to the wire: 101 bytes from at, returning where the next byte goes */
static size_t encode_bonds_total_remaining_volume_on_quotes_message(const BondsTotalRemainingVolumeOnQuotesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_total_remaining_quantity[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Bonds Total Remaining Volume On Quotes Message off the wire: 101 bytes from at, returning where the next byte lies */
static size_t decode_bonds_total_remaining_volume_on_quotes_message(BondsTotalRemainingVolumeOnQuotesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_total_remaining_quantity[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Bonds Total Remaining Volume On Quotes Message is what was written, byte for byte */
static void equal_bonds_total_remaining_volume_on_quotes_message(const BondsTotalRemainingVolumeOnQuotesMessage *read, const BondsTotalRemainingVolumeOnQuotesMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_total_remaining_quantity[i] == written->ask_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_total_remaining_quantity[i] == written->bid_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_total_remaining_quantity[i] == written->ask_per_type_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_total_remaining_quantity[i] == written->bid_per_type_total_remaining_quantity[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Bonds Total Remaining Volume On Quotes Message: written and read back, then read and written back */
static void check_bonds_total_remaining_volume_on_quotes_message(void) {
  BondsTotalRemainingVolumeOnQuotesMessage sent;
  BondsTotalRemainingVolumeOnQuotesMessage got;
  uint8_t wire[101];
  uint8_t again[101];

  any_bonds_total_remaining_volume_on_quotes_message(&sent);
  assert(encode_bonds_total_remaining_volume_on_quotes_message(&sent, wire, 0) == 101);
  assert(decode_bonds_total_remaining_volume_on_quotes_message(&got, wire, 0) == 101);
  equal_bonds_total_remaining_volume_on_quotes_message(&got, &sent);

  for (size_t i = 0; i < 101; i++) { wire[i] = arbitrary(); }
  assert(decode_bonds_total_remaining_volume_on_quotes_message(&got, wire, 0) == 101);
  assert(encode_bonds_total_remaining_volume_on_quotes_message(&got, again, 0) == 101);
  for (size_t i = 0; i < 101; i++) { assert(again[i] == wire[i]); }
}

/* ---- Baby Bonds Order Filled Plus Quote Message: 1058 bytes ------------------ */

/* Baby Bonds Order Filled + Quote (IFMSRPD0030) — Bonds A SMB. Trade + 5-level quote with yields. */
typedef struct {
  uint8_t message_sequence_number[8];                   /* bytes 0 to 7 */
  uint8_t board_id[2];                                  /* bytes 8 to 9 */
  uint8_t session_id[2];                                /* bytes 10 to 11 */
  uint8_t isin_code[12];                                /* bytes 12 to 23 */
  uint8_t processing_time_of_trading_system[12];        /* bytes 24 to 35 */
  uint8_t trading_price[11];                            /* bytes 36 to 46 */
  uint8_t trading_volume[10];                           /* bytes 47 to 56 */
  uint8_t trading_date[8];                              /* bytes 57 to 64 */
  uint8_t trading_value[22];                            /* bytes 65 to 86 */
  uint8_t bond_yield[13];                               /* bytes 87 to 99 */
  uint8_t opening_price[11];                            /* bytes 100 to 110 */
  uint8_t todays_high[11];                              /* bytes 111 to 121 */
  uint8_t todays_low[11];                               /* bytes 122 to 132 */
  uint8_t yield_opening_price[13];                      /* bytes 133 to 145 */
  uint8_t yield_todays_high[13];                        /* bytes 146 to 158 */
  uint8_t yield_todays_low[13];                         /* bytes 159 to 171 */
  uint8_t accumulated_trading_volume_long[15];          /* bytes 172 to 186 */
  uint8_t accumulated_trading_value_long[22];           /* bytes 187 to 208 */
  uint8_t settlement_date[8];                           /* bytes 209 to 216 */
  uint8_t ask_level_1_price[11];                        /* bytes 217 to 227 */
  uint8_t bid_level_1_price[11];                        /* bytes 228 to 238 */
  uint8_t ask_level_1_remaining_quantity[15];           /* bytes 239 to 253 */
  uint8_t bid_level_1_remaining_quantity[15];           /* bytes 254 to 268 */
  uint8_t ask_level_1_yield[13];                        /* bytes 269 to 281 */
  uint8_t bid_level_1_yield[13];                        /* bytes 282 to 294 */
  uint8_t ask_per_type_level_1_price[11];               /* bytes 295 to 305 */
  uint8_t bid_per_type_level_1_price[11];               /* bytes 306 to 316 */
  uint8_t ask_per_type_level_1_remaining_quantity[15];  /* bytes 317 to 331 */
  uint8_t bid_per_type_level_1_remaining_quantity[15];  /* bytes 332 to 346 */
  uint8_t ask_per_type_level_1_yield[13];               /* bytes 347 to 359 */
  uint8_t bid_per_type_level_1_yield[13];               /* bytes 360 to 372 */
  uint8_t ask_level_2_price[11];                        /* bytes 373 to 383 */
  uint8_t bid_level_2_price[11];                        /* bytes 384 to 394 */
  uint8_t ask_level_2_remaining_quantity[15];           /* bytes 395 to 409 */
  uint8_t bid_level_2_remaining_quantity[15];           /* bytes 410 to 424 */
  uint8_t ask_level_2_yield[13];                        /* bytes 425 to 437 */
  uint8_t bid_level_2_yield[13];                        /* bytes 438 to 450 */
  uint8_t ask_per_type_level_2_price[11];               /* bytes 451 to 461 */
  uint8_t bid_per_type_level_2_price[11];               /* bytes 462 to 472 */
  uint8_t ask_per_type_level_2_remaining_quantity[15];  /* bytes 473 to 487 */
  uint8_t bid_per_type_level_2_remaining_quantity[15];  /* bytes 488 to 502 */
  uint8_t ask_per_type_level_2_yield[13];               /* bytes 503 to 515 */
  uint8_t bid_per_type_level_2_yield[13];               /* bytes 516 to 528 */
  uint8_t ask_level_3_price[11];                        /* bytes 529 to 539 */
  uint8_t bid_level_3_price[11];                        /* bytes 540 to 550 */
  uint8_t ask_level_3_remaining_quantity[15];           /* bytes 551 to 565 */
  uint8_t bid_level_3_remaining_quantity[15];           /* bytes 566 to 580 */
  uint8_t ask_level_3_yield[13];                        /* bytes 581 to 593 */
  uint8_t bid_level_3_yield[13];                        /* bytes 594 to 606 */
  uint8_t ask_per_type_level_3_price[11];               /* bytes 607 to 617 */
  uint8_t bid_per_type_level_3_price[11];               /* bytes 618 to 628 */
  uint8_t ask_per_type_level_3_remaining_quantity[15];  /* bytes 629 to 643 */
  uint8_t bid_per_type_level_3_remaining_quantity[15];  /* bytes 644 to 658 */
  uint8_t ask_per_type_level_3_yield[13];               /* bytes 659 to 671 */
  uint8_t bid_per_type_level_3_yield[13];               /* bytes 672 to 684 */
  uint8_t ask_level_4_price[11];                        /* bytes 685 to 695 */
  uint8_t bid_level_4_price[11];                        /* bytes 696 to 706 */
  uint8_t ask_level_4_remaining_quantity[15];           /* bytes 707 to 721 */
  uint8_t bid_level_4_remaining_quantity[15];           /* bytes 722 to 736 */
  uint8_t ask_level_4_yield[13];                        /* bytes 737 to 749 */
  uint8_t bid_level_4_yield[13];                        /* bytes 750 to 762 */
  uint8_t ask_per_type_level_4_price[11];               /* bytes 763 to 773 */
  uint8_t bid_per_type_level_4_price[11];               /* bytes 774 to 784 */
  uint8_t ask_per_type_level_4_remaining_quantity[15];  /* bytes 785 to 799 */
  uint8_t bid_per_type_level_4_remaining_quantity[15];  /* bytes 800 to 814 */
  uint8_t ask_per_type_level_4_yield[13];               /* bytes 815 to 827 */
  uint8_t bid_per_type_level_4_yield[13];               /* bytes 828 to 840 */
  uint8_t ask_level_5_price[11];                        /* bytes 841 to 851 */
  uint8_t bid_level_5_price[11];                        /* bytes 852 to 862 */
  uint8_t ask_level_5_remaining_quantity[15];           /* bytes 863 to 877 */
  uint8_t bid_level_5_remaining_quantity[15];           /* bytes 878 to 892 */
  uint8_t ask_level_5_yield[13];                        /* bytes 893 to 905 */
  uint8_t bid_level_5_yield[13];                        /* bytes 906 to 918 */
  uint8_t ask_per_type_level_5_price[11];               /* bytes 919 to 929 */
  uint8_t bid_per_type_level_5_price[11];               /* bytes 930 to 940 */
  uint8_t ask_per_type_level_5_remaining_quantity[15];  /* bytes 941 to 955 */
  uint8_t bid_per_type_level_5_remaining_quantity[15];  /* bytes 956 to 970 */
  uint8_t ask_per_type_level_5_yield[13];               /* bytes 971 to 983 */
  uint8_t bid_per_type_level_5_yield[13];               /* bytes 984 to 996 */
  uint8_t ask_total_remaining_quantity[15];             /* bytes 997 to 1011 */
  uint8_t bid_total_remaining_quantity[15];             /* bytes 1012 to 1026 */
  uint8_t ask_per_type_total_remaining_quantity[15];    /* bytes 1027 to 1041 */
  uint8_t bid_per_type_total_remaining_quantity[15];    /* bytes 1042 to 1056 */
  uint8_t end_keyword;                                  /* byte 1057 */
} BabyBondsOrderFilledPlusQuoteMessage;

/* any Baby Bonds Order Filled Plus Quote Message at all: every byte one the checker chooses */
static void any_baby_bonds_order_filled_plus_quote_message(BabyBondsOrderFilledPlusQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bond_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->yield_opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->yield_todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->yield_todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->accumulated_trading_volume_long[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_1_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_1_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_1_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_1_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_2_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_2_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_2_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_2_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_3_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_3_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_3_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_3_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_4_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_4_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_4_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_4_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_level_5_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_level_5_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_5_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_5_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_total_remaining_quantity[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Baby Bonds Order Filled Plus Quote Message to the wire: 1058 bytes from at, returning where the next byte goes */
static size_t encode_baby_bonds_order_filled_plus_quote_message(const BabyBondsOrderFilledPlusQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_date[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->trading_value[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bond_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->yield_opening_price[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->yield_todays_high[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->yield_todays_low[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->accumulated_trading_volume_long[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_date[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_1_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_1_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_1_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_per_type_level_1_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_per_type_level_1_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_2_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_2_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_2_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_per_type_level_2_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_per_type_level_2_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_3_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_3_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_3_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_per_type_level_3_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_per_type_level_3_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_4_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_4_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_4_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_per_type_level_4_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_per_type_level_4_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_level_5_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_level_5_yield[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_5_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->ask_per_type_level_5_yield[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->bid_per_type_level_5_yield[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_total_remaining_quantity[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Baby Bonds Order Filled Plus Quote Message off the wire: 1058 bytes from at, returning where the next byte lies */
static size_t decode_baby_bonds_order_filled_plus_quote_message(BabyBondsOrderFilledPlusQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bond_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->yield_opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->yield_todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->yield_todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->accumulated_trading_volume_long[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_1_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_1_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_1_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_1_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_2_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_2_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_2_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_2_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_3_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_3_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_3_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_3_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_4_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_4_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_4_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_4_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_level_5_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_level_5_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->ask_per_type_level_5_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->bid_per_type_level_5_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_total_remaining_quantity[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Baby Bonds Order Filled Plus Quote Message is what was written, byte for byte */
static void equal_baby_bonds_order_filled_plus_quote_message(const BabyBondsOrderFilledPlusQuoteMessage *read, const BabyBondsOrderFilledPlusQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_date[i] == written->trading_date[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->trading_value[i] == written->trading_value[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bond_yield[i] == written->bond_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->yield_opening_price[i] == written->yield_opening_price[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->yield_todays_high[i] == written->yield_todays_high[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->yield_todays_low[i] == written->yield_todays_low[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->accumulated_trading_volume_long[i] == written->accumulated_trading_volume_long[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value_long[i] == written->accumulated_trading_value_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_1_remaining_quantity[i] == written->ask_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_1_remaining_quantity[i] == written->bid_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_1_yield[i] == written->ask_level_1_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_1_yield[i] == written->bid_level_1_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_1_price[i] == written->ask_per_type_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_1_price[i] == written->bid_per_type_level_1_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_1_remaining_quantity[i] == written->ask_per_type_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_1_remaining_quantity[i] == written->bid_per_type_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_per_type_level_1_yield[i] == written->ask_per_type_level_1_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_per_type_level_1_yield[i] == written->bid_per_type_level_1_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_2_remaining_quantity[i] == written->ask_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_2_remaining_quantity[i] == written->bid_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_2_yield[i] == written->ask_level_2_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_2_yield[i] == written->bid_level_2_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_2_price[i] == written->ask_per_type_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_2_price[i] == written->bid_per_type_level_2_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_2_remaining_quantity[i] == written->ask_per_type_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_2_remaining_quantity[i] == written->bid_per_type_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_per_type_level_2_yield[i] == written->ask_per_type_level_2_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_per_type_level_2_yield[i] == written->bid_per_type_level_2_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_3_remaining_quantity[i] == written->ask_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_3_remaining_quantity[i] == written->bid_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_3_yield[i] == written->ask_level_3_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_3_yield[i] == written->bid_level_3_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_3_price[i] == written->ask_per_type_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_3_price[i] == written->bid_per_type_level_3_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_3_remaining_quantity[i] == written->ask_per_type_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_3_remaining_quantity[i] == written->bid_per_type_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_per_type_level_3_yield[i] == written->ask_per_type_level_3_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_per_type_level_3_yield[i] == written->bid_per_type_level_3_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_4_remaining_quantity[i] == written->ask_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_4_remaining_quantity[i] == written->bid_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_4_yield[i] == written->ask_level_4_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_4_yield[i] == written->bid_level_4_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_4_price[i] == written->ask_per_type_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_4_price[i] == written->bid_per_type_level_4_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_4_remaining_quantity[i] == written->ask_per_type_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_4_remaining_quantity[i] == written->bid_per_type_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_per_type_level_4_yield[i] == written->ask_per_type_level_4_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_per_type_level_4_yield[i] == written->bid_per_type_level_4_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_5_remaining_quantity[i] == written->ask_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_5_remaining_quantity[i] == written->bid_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_level_5_yield[i] == written->ask_level_5_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_level_5_yield[i] == written->bid_level_5_yield[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_5_price[i] == written->ask_per_type_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_5_price[i] == written->bid_per_type_level_5_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_5_remaining_quantity[i] == written->ask_per_type_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_5_remaining_quantity[i] == written->bid_per_type_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->ask_per_type_level_5_yield[i] == written->ask_per_type_level_5_yield[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->bid_per_type_level_5_yield[i] == written->bid_per_type_level_5_yield[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_total_remaining_quantity[i] == written->ask_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_total_remaining_quantity[i] == written->bid_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_total_remaining_quantity[i] == written->ask_per_type_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_total_remaining_quantity[i] == written->bid_per_type_total_remaining_quantity[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Baby Bonds Order Filled Plus Quote Message: written and read back, then read and written back */
static void check_baby_bonds_order_filled_plus_quote_message(void) {
  BabyBondsOrderFilledPlusQuoteMessage sent;
  BabyBondsOrderFilledPlusQuoteMessage got;
  uint8_t wire[1058];
  uint8_t again[1058];

  any_baby_bonds_order_filled_plus_quote_message(&sent);
  assert(encode_baby_bonds_order_filled_plus_quote_message(&sent, wire, 0) == 1058);
  assert(decode_baby_bonds_order_filled_plus_quote_message(&got, wire, 0) == 1058);
  equal_baby_bonds_order_filled_plus_quote_message(&got, &sent);

  for (size_t i = 0; i < 1058; i++) { wire[i] = arbitrary(); }
  assert(decode_baby_bonds_order_filled_plus_quote_message(&got, wire, 0) == 1058);
  assert(encode_baby_bonds_order_filled_plus_quote_message(&got, again, 0) == 1058);
  for (size_t i = 0; i < 1058; i++) { assert(again[i] == wire[i]); }
}

/* ---- Repo Order Filled Plus Quote Message: 1581 bytes ------------------------ */

/* REPO Order Filled + Quote (IFMSRPD0031) — Bonds A RPO. Trade + 5-level quote + designated bid levels 1-10. */
typedef struct {
  uint8_t message_sequence_number[8];                           /* bytes 0 to 7 */
  uint8_t board_id[2];                                          /* bytes 8 to 9 */
  uint8_t session_id[2];                                        /* bytes 10 to 11 */
  uint8_t isin_code[12];                                        /* bytes 12 to 23 */
  uint8_t processing_time_of_trading_system[12];                /* bytes 24 to 35 */
  uint8_t trading_price[11];                                    /* bytes 36 to 46 */
  uint8_t trading_volume[10];                                   /* bytes 47 to 56 */
  uint8_t trading_date[8];                                      /* bytes 57 to 64 */
  uint8_t trading_value[22];                                    /* bytes 65 to 86 */
  uint8_t ask_repo_type_code[2];                                /* bytes 87 to 88 */
  uint8_t ask_duration_of_term_repo[4];                         /* bytes 89 to 92 */
  uint8_t bid_repo_type_code[2];                                /* bytes 93 to 94 */
  uint8_t bid_duration_of_term_repo[4];                         /* bytes 95 to 98 */
  uint8_t opening_price[11];                                    /* bytes 99 to 109 */
  uint8_t todays_high[11];                                      /* bytes 110 to 120 */
  uint8_t todays_low[11];                                       /* bytes 121 to 131 */
  uint8_t category_opening_price[11];                           /* bytes 132 to 142 */
  uint8_t category_todays_high[11];                             /* bytes 143 to 153 */
  uint8_t category_todays_low[11];                              /* bytes 154 to 164 */
  uint8_t accumulated_trading_volume_long[15];                  /* bytes 165 to 179 */
  uint8_t accumulated_trading_value_long[22];                   /* bytes 180 to 201 */
  uint8_t category_accumulated_trading_volume[15];              /* bytes 202 to 216 */
  uint8_t category_accumulated_trading_value[22];               /* bytes 217 to 238 */
  uint8_t ask_level_1_price[11];                                /* bytes 239 to 249 */
  uint8_t bid_level_1_price[11];                                /* bytes 250 to 260 */
  uint8_t ask_level_1_remaining_quantity[15];                   /* bytes 261 to 275 */
  uint8_t bid_level_1_remaining_quantity[15];                   /* bytes 276 to 290 */
  uint8_t ask_level_1_trading_amount[22];                       /* bytes 291 to 312 */
  uint8_t total_bid_level_1_price[11];                          /* bytes 313 to 323 */
  uint8_t total_bid_level_1_remaining_quantity[15];             /* bytes 324 to 338 */
  uint8_t bid_level_1_including_gc;                             /* byte 339 */
  uint8_t ask_per_type_level_1_price[11];                       /* bytes 340 to 350 */
  uint8_t bid_per_type_level_1_price[11];                       /* bytes 351 to 361 */
  uint8_t ask_per_type_level_1_remaining_quantity[15];          /* bytes 362 to 376 */
  uint8_t bid_per_type_level_1_remaining_quantity[15];          /* bytes 377 to 391 */
  uint8_t ask_per_type_level_1_trading_amount[22];              /* bytes 392 to 413 */
  uint8_t ask_level_2_price[11];                                /* bytes 414 to 424 */
  uint8_t bid_level_2_price[11];                                /* bytes 425 to 435 */
  uint8_t ask_level_2_remaining_quantity[15];                   /* bytes 436 to 450 */
  uint8_t bid_level_2_remaining_quantity[15];                   /* bytes 451 to 465 */
  uint8_t ask_level_2_trading_amount[22];                       /* bytes 466 to 487 */
  uint8_t total_bid_level_2_price[11];                          /* bytes 488 to 498 */
  uint8_t total_bid_level_2_remaining_quantity[15];             /* bytes 499 to 513 */
  uint8_t bid_level_2_including_gc;                             /* byte 514 */
  uint8_t ask_per_type_level_2_price[11];                       /* bytes 515 to 525 */
  uint8_t bid_per_type_level_2_price[11];                       /* bytes 526 to 536 */
  uint8_t ask_per_type_level_2_remaining_quantity[15];          /* bytes 537 to 551 */
  uint8_t bid_per_type_level_2_remaining_quantity[15];          /* bytes 552 to 566 */
  uint8_t ask_per_type_level_2_trading_amount[22];              /* bytes 567 to 588 */
  uint8_t ask_level_3_price[11];                                /* bytes 589 to 599 */
  uint8_t bid_level_3_price[11];                                /* bytes 600 to 610 */
  uint8_t ask_level_3_remaining_quantity[15];                   /* bytes 611 to 625 */
  uint8_t bid_level_3_remaining_quantity[15];                   /* bytes 626 to 640 */
  uint8_t ask_level_3_trading_amount[22];                       /* bytes 641 to 662 */
  uint8_t total_bid_level_3_price[11];                          /* bytes 663 to 673 */
  uint8_t total_bid_level_3_remaining_quantity[15];             /* bytes 674 to 688 */
  uint8_t bid_level_3_including_gc;                             /* byte 689 */
  uint8_t ask_per_type_level_3_price[11];                       /* bytes 690 to 700 */
  uint8_t bid_per_type_level_3_price[11];                       /* bytes 701 to 711 */
  uint8_t ask_per_type_level_3_remaining_quantity[15];          /* bytes 712 to 726 */
  uint8_t bid_per_type_level_3_remaining_quantity[15];          /* bytes 727 to 741 */
  uint8_t ask_per_type_level_3_trading_amount[22];              /* bytes 742 to 763 */
  uint8_t ask_level_4_price[11];                                /* bytes 764 to 774 */
  uint8_t bid_level_4_price[11];                                /* bytes 775 to 785 */
  uint8_t ask_level_4_remaining_quantity[15];                   /* bytes 786 to 800 */
  uint8_t bid_level_4_remaining_quantity[15];                   /* bytes 801 to 815 */
  uint8_t ask_level_4_trading_amount[22];                       /* bytes 816 to 837 */
  uint8_t total_bid_level_4_price[11];                          /* bytes 838 to 848 */
  uint8_t total_bid_level_4_remaining_quantity[15];             /* bytes 849 to 863 */
  uint8_t bid_level_4_including_gc;                             /* byte 864 */
  uint8_t ask_per_type_level_4_price[11];                       /* bytes 865 to 875 */
  uint8_t bid_per_type_level_4_price[11];                       /* bytes 876 to 886 */
  uint8_t ask_per_type_level_4_remaining_quantity[15];          /* bytes 887 to 901 */
  uint8_t bid_per_type_level_4_remaining_quantity[15];          /* bytes 902 to 916 */
  uint8_t ask_per_type_level_4_trading_amount[22];              /* bytes 917 to 938 */
  uint8_t ask_level_5_price[11];                                /* bytes 939 to 949 */
  uint8_t bid_level_5_price[11];                                /* bytes 950 to 960 */
  uint8_t ask_level_5_remaining_quantity[15];                   /* bytes 961 to 975 */
  uint8_t bid_level_5_remaining_quantity[15];                   /* bytes 976 to 990 */
  uint8_t ask_level_5_trading_amount[22];                       /* bytes 991 to 1012 */
  uint8_t total_bid_level_5_price[11];                          /* bytes 1013 to 1023 */
  uint8_t total_bid_level_5_remaining_quantity[15];             /* bytes 1024 to 1038 */
  uint8_t bid_level_5_including_gc;                             /* byte 1039 */
  uint8_t ask_per_type_level_5_price[11];                       /* bytes 1040 to 1050 */
  uint8_t bid_per_type_level_5_price[11];                       /* bytes 1051 to 1061 */
  uint8_t ask_per_type_level_5_remaining_quantity[15];          /* bytes 1062 to 1076 */
  uint8_t bid_per_type_level_5_remaining_quantity[15];          /* bytes 1077 to 1091 */
  uint8_t ask_per_type_level_5_trading_amount[22];              /* bytes 1092 to 1113 */
  uint8_t ask_total_remaining_quantity[15];                     /* bytes 1114 to 1128 */
  uint8_t bid_total_remaining_quantity[15];                     /* bytes 1129 to 1143 */
  uint8_t ask_per_type_total_remaining_quantity[15];            /* bytes 1144 to 1158 */
  uint8_t bid_per_type_total_remaining_quantity[15];            /* bytes 1159 to 1173 */
  uint8_t designated_bid_level_1_price[11];                     /* bytes 1174 to 1184 */
  uint8_t designated_bid_level_1_repo_remaining_quantity[15];   /* bytes 1185 to 1199 */
  uint8_t designated_bid_level_1_isin[12];                      /* bytes 1200 to 1211 */
  uint8_t designated_bid_level_2_price[11];                     /* bytes 1212 to 1222 */
  uint8_t designated_bid_level_2_repo_remaining_quantity[15];   /* bytes 1223 to 1237 */
  uint8_t designated_bid_level_2_isin[12];                      /* bytes 1238 to 1249 */
  uint8_t designated_bid_level_3_price[11];                     /* bytes 1250 to 1260 */
  uint8_t designated_bid_level_3_repo_remaining_quantity[15];   /* bytes 1261 to 1275 */
  uint8_t designated_bid_level_3_isin[12];                      /* bytes 1276 to 1287 */
  uint8_t designated_bid_level_4_price[11];                     /* bytes 1288 to 1298 */
  uint8_t designated_bid_level_4_repo_remaining_quantity[15];   /* bytes 1299 to 1313 */
  uint8_t designated_bid_level_4_isin[12];                      /* bytes 1314 to 1325 */
  uint8_t designated_bid_level_5_price[11];                     /* bytes 1326 to 1336 */
  uint8_t designated_bid_level_5_repo_remaining_quantity[15];   /* bytes 1337 to 1351 */
  uint8_t designated_bid_level_5_isin[12];                      /* bytes 1352 to 1363 */
  uint8_t designated_bid_level_6_price[11];                     /* bytes 1364 to 1374 */
  uint8_t designated_bid_level_6_repo_remaining_quantity[15];   /* bytes 1375 to 1389 */
  uint8_t designated_bid_level_6_isin[12];                      /* bytes 1390 to 1401 */
  uint8_t designated_bid_level_7_price[11];                     /* bytes 1402 to 1412 */
  uint8_t designated_bid_level_7_repo_remaining_quantity[15];   /* bytes 1413 to 1427 */
  uint8_t designated_bid_level_7_isin[12];                      /* bytes 1428 to 1439 */
  uint8_t designated_bid_level_8_price[11];                     /* bytes 1440 to 1450 */
  uint8_t designated_bid_level_8_repo_remaining_quantity[15];   /* bytes 1451 to 1465 */
  uint8_t designated_bid_level_8_isin[12];                      /* bytes 1466 to 1477 */
  uint8_t designated_bid_level_9_price[11];                     /* bytes 1478 to 1488 */
  uint8_t designated_bid_level_9_repo_remaining_quantity[15];   /* bytes 1489 to 1503 */
  uint8_t designated_bid_level_9_isin[12];                      /* bytes 1504 to 1515 */
  uint8_t designated_bid_level_10_price[11];                    /* bytes 1516 to 1526 */
  uint8_t designated_bid_level_10_repo_remaining_quantity[15];  /* bytes 1527 to 1541 */
  uint8_t designated_bid_level_10_isin[12];                     /* bytes 1542 to 1553 */
  uint8_t designated_best_bid_price[11];                        /* bytes 1554 to 1564 */
  uint8_t net_bid_per_type_total_remaining_quantity[15];        /* bytes 1565 to 1579 */
  uint8_t end_keyword;                                          /* byte 1580 */
} RepoOrderFilledPlusQuoteMessage;

/* any Repo Order Filled Plus Quote Message at all: every byte one the checker chooses */
static void any_repo_order_filled_plus_quote_message(RepoOrderFilledPlusQuoteMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_repo_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_duration_of_term_repo[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_repo_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_duration_of_term_repo[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->category_opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->category_todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->category_todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->accumulated_trading_volume_long[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->category_accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->category_accumulated_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_level_1_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_1_remaining_quantity[i] = arbitrary(); }
  record->bid_level_1_including_gc = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_1_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_1_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_level_2_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_2_remaining_quantity[i] = arbitrary(); }
  record->bid_level_2_including_gc = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_2_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_2_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_level_3_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_3_remaining_quantity[i] = arbitrary(); }
  record->bid_level_3_including_gc = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_3_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_3_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_level_4_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_4_remaining_quantity[i] = arbitrary(); }
  record->bid_level_4_including_gc = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_4_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_4_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_level_5_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_5_remaining_quantity[i] = arbitrary(); }
  record->bid_level_5_including_gc = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_5_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_5_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_total_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_1_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_1_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_1_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_2_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_2_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_2_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_3_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_3_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_3_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_4_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_4_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_4_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_5_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_5_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_5_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_6_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_6_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_6_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_7_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_7_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_7_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_8_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_8_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_8_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_9_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_9_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_9_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_10_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_10_repo_remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_10_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->designated_best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->net_bid_per_type_total_remaining_quantity[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Repo Order Filled Plus Quote Message to the wire: 1581 bytes from at, returning where the next byte goes */
static size_t encode_repo_order_filled_plus_quote_message(const RepoOrderFilledPlusQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_date[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->trading_value[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_repo_type_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_duration_of_term_repo[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_repo_type_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_duration_of_term_repo[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->category_opening_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->category_todays_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->category_todays_low[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->accumulated_trading_volume_long[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value_long[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->category_accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->category_accumulated_trading_value[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_1_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_level_1_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->total_bid_level_1_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->total_bid_level_1_remaining_quantity[i]; }
  wire[at++] = record->bid_level_1_including_gc;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_1_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_1_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_1_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_per_type_level_1_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_2_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_level_2_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->total_bid_level_2_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->total_bid_level_2_remaining_quantity[i]; }
  wire[at++] = record->bid_level_2_including_gc;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_2_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_2_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_2_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_per_type_level_2_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_3_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_level_3_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->total_bid_level_3_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->total_bid_level_3_remaining_quantity[i]; }
  wire[at++] = record->bid_level_3_including_gc;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_3_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_3_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_3_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_per_type_level_3_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_4_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_level_4_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->total_bid_level_4_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->total_bid_level_4_remaining_quantity[i]; }
  wire[at++] = record->bid_level_4_including_gc;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_4_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_4_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_4_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_per_type_level_4_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_5_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_level_5_trading_amount[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->total_bid_level_5_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->total_bid_level_5_remaining_quantity[i]; }
  wire[at++] = record->bid_level_5_including_gc;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_per_type_level_5_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_per_type_level_5_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_level_5_remaining_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_per_type_level_5_trading_amount[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_per_type_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_per_type_total_remaining_quantity[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_1_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_1_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_1_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_2_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_2_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_2_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_3_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_3_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_3_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_4_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_4_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_4_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_5_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_5_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_5_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_6_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_6_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_6_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_7_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_7_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_7_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_8_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_8_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_8_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_9_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_9_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_9_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_bid_level_10_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->designated_bid_level_10_repo_remaining_quantity[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->designated_bid_level_10_isin[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->designated_best_bid_price[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->net_bid_per_type_total_remaining_quantity[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Repo Order Filled Plus Quote Message off the wire: 1581 bytes from at, returning where the next byte lies */
static size_t decode_repo_order_filled_plus_quote_message(RepoOrderFilledPlusQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_repo_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_duration_of_term_repo[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_repo_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_duration_of_term_repo[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->category_opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->category_todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->category_todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->accumulated_trading_volume_long[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value_long[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->category_accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->category_accumulated_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_level_1_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_1_remaining_quantity[i] = wire[at++]; }
  record->bid_level_1_including_gc = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_1_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_1_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_level_2_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_2_remaining_quantity[i] = wire[at++]; }
  record->bid_level_2_including_gc = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_2_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_2_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_level_3_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_3_remaining_quantity[i] = wire[at++]; }
  record->bid_level_3_including_gc = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_3_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_3_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_level_4_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_4_remaining_quantity[i] = wire[at++]; }
  record->bid_level_4_including_gc = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_4_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_4_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_level_5_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->total_bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->total_bid_level_5_remaining_quantity[i] = wire[at++]; }
  record->bid_level_5_including_gc = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->ask_per_type_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_per_type_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_level_5_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_per_type_level_5_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_per_type_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_per_type_total_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_1_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_1_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_1_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_2_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_2_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_2_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_3_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_3_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_3_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_4_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_4_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_4_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_5_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_5_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_5_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_6_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_6_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_6_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_7_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_7_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_7_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_8_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_8_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_8_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_9_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_9_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_9_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_bid_level_10_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->designated_bid_level_10_repo_remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->designated_bid_level_10_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->designated_best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->net_bid_per_type_total_remaining_quantity[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Repo Order Filled Plus Quote Message is what was written, byte for byte */
static void equal_repo_order_filled_plus_quote_message(const RepoOrderFilledPlusQuoteMessage *read, const RepoOrderFilledPlusQuoteMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_date[i] == written->trading_date[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->trading_value[i] == written->trading_value[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_repo_type_code[i] == written->ask_repo_type_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_duration_of_term_repo[i] == written->ask_duration_of_term_repo[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_repo_type_code[i] == written->bid_repo_type_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_duration_of_term_repo[i] == written->bid_duration_of_term_repo[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->category_opening_price[i] == written->category_opening_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->category_todays_high[i] == written->category_todays_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->category_todays_low[i] == written->category_todays_low[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->accumulated_trading_volume_long[i] == written->accumulated_trading_volume_long[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value_long[i] == written->accumulated_trading_value_long[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->category_accumulated_trading_volume[i] == written->category_accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->category_accumulated_trading_value[i] == written->category_accumulated_trading_value[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_1_price[i] == written->ask_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_1_price[i] == written->bid_level_1_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_1_remaining_quantity[i] == written->ask_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_1_remaining_quantity[i] == written->bid_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_level_1_trading_amount[i] == written->ask_level_1_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->total_bid_level_1_price[i] == written->total_bid_level_1_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->total_bid_level_1_remaining_quantity[i] == written->total_bid_level_1_remaining_quantity[i]); }
  assert(read->bid_level_1_including_gc == written->bid_level_1_including_gc);
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_1_price[i] == written->ask_per_type_level_1_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_1_price[i] == written->bid_per_type_level_1_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_1_remaining_quantity[i] == written->ask_per_type_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_1_remaining_quantity[i] == written->bid_per_type_level_1_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_per_type_level_1_trading_amount[i] == written->ask_per_type_level_1_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_2_price[i] == written->ask_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_2_price[i] == written->bid_level_2_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_2_remaining_quantity[i] == written->ask_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_2_remaining_quantity[i] == written->bid_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_level_2_trading_amount[i] == written->ask_level_2_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->total_bid_level_2_price[i] == written->total_bid_level_2_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->total_bid_level_2_remaining_quantity[i] == written->total_bid_level_2_remaining_quantity[i]); }
  assert(read->bid_level_2_including_gc == written->bid_level_2_including_gc);
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_2_price[i] == written->ask_per_type_level_2_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_2_price[i] == written->bid_per_type_level_2_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_2_remaining_quantity[i] == written->ask_per_type_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_2_remaining_quantity[i] == written->bid_per_type_level_2_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_per_type_level_2_trading_amount[i] == written->ask_per_type_level_2_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_3_price[i] == written->ask_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_3_price[i] == written->bid_level_3_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_3_remaining_quantity[i] == written->ask_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_3_remaining_quantity[i] == written->bid_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_level_3_trading_amount[i] == written->ask_level_3_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->total_bid_level_3_price[i] == written->total_bid_level_3_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->total_bid_level_3_remaining_quantity[i] == written->total_bid_level_3_remaining_quantity[i]); }
  assert(read->bid_level_3_including_gc == written->bid_level_3_including_gc);
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_3_price[i] == written->ask_per_type_level_3_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_3_price[i] == written->bid_per_type_level_3_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_3_remaining_quantity[i] == written->ask_per_type_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_3_remaining_quantity[i] == written->bid_per_type_level_3_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_per_type_level_3_trading_amount[i] == written->ask_per_type_level_3_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_4_price[i] == written->ask_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_4_price[i] == written->bid_level_4_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_4_remaining_quantity[i] == written->ask_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_4_remaining_quantity[i] == written->bid_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_level_4_trading_amount[i] == written->ask_level_4_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->total_bid_level_4_price[i] == written->total_bid_level_4_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->total_bid_level_4_remaining_quantity[i] == written->total_bid_level_4_remaining_quantity[i]); }
  assert(read->bid_level_4_including_gc == written->bid_level_4_including_gc);
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_4_price[i] == written->ask_per_type_level_4_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_4_price[i] == written->bid_per_type_level_4_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_4_remaining_quantity[i] == written->ask_per_type_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_4_remaining_quantity[i] == written->bid_per_type_level_4_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_per_type_level_4_trading_amount[i] == written->ask_per_type_level_4_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_5_price[i] == written->ask_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_5_price[i] == written->bid_level_5_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_level_5_remaining_quantity[i] == written->ask_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_level_5_remaining_quantity[i] == written->bid_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_level_5_trading_amount[i] == written->ask_level_5_trading_amount[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->total_bid_level_5_price[i] == written->total_bid_level_5_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->total_bid_level_5_remaining_quantity[i] == written->total_bid_level_5_remaining_quantity[i]); }
  assert(read->bid_level_5_including_gc == written->bid_level_5_including_gc);
  for (size_t i = 0; i < 11; i++) { assert(read->ask_per_type_level_5_price[i] == written->ask_per_type_level_5_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_per_type_level_5_price[i] == written->bid_per_type_level_5_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_level_5_remaining_quantity[i] == written->ask_per_type_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_level_5_remaining_quantity[i] == written->bid_per_type_level_5_remaining_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_per_type_level_5_trading_amount[i] == written->ask_per_type_level_5_trading_amount[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_total_remaining_quantity[i] == written->ask_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_total_remaining_quantity[i] == written->bid_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_per_type_total_remaining_quantity[i] == written->ask_per_type_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_per_type_total_remaining_quantity[i] == written->bid_per_type_total_remaining_quantity[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_1_price[i] == written->designated_bid_level_1_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_1_repo_remaining_quantity[i] == written->designated_bid_level_1_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_1_isin[i] == written->designated_bid_level_1_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_2_price[i] == written->designated_bid_level_2_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_2_repo_remaining_quantity[i] == written->designated_bid_level_2_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_2_isin[i] == written->designated_bid_level_2_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_3_price[i] == written->designated_bid_level_3_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_3_repo_remaining_quantity[i] == written->designated_bid_level_3_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_3_isin[i] == written->designated_bid_level_3_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_4_price[i] == written->designated_bid_level_4_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_4_repo_remaining_quantity[i] == written->designated_bid_level_4_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_4_isin[i] == written->designated_bid_level_4_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_5_price[i] == written->designated_bid_level_5_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_5_repo_remaining_quantity[i] == written->designated_bid_level_5_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_5_isin[i] == written->designated_bid_level_5_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_6_price[i] == written->designated_bid_level_6_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_6_repo_remaining_quantity[i] == written->designated_bid_level_6_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_6_isin[i] == written->designated_bid_level_6_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_7_price[i] == written->designated_bid_level_7_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_7_repo_remaining_quantity[i] == written->designated_bid_level_7_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_7_isin[i] == written->designated_bid_level_7_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_8_price[i] == written->designated_bid_level_8_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_8_repo_remaining_quantity[i] == written->designated_bid_level_8_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_8_isin[i] == written->designated_bid_level_8_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_9_price[i] == written->designated_bid_level_9_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_9_repo_remaining_quantity[i] == written->designated_bid_level_9_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_9_isin[i] == written->designated_bid_level_9_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_bid_level_10_price[i] == written->designated_bid_level_10_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->designated_bid_level_10_repo_remaining_quantity[i] == written->designated_bid_level_10_repo_remaining_quantity[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->designated_bid_level_10_isin[i] == written->designated_bid_level_10_isin[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->designated_best_bid_price[i] == written->designated_best_bid_price[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->net_bid_per_type_total_remaining_quantity[i] == written->net_bid_per_type_total_remaining_quantity[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Repo Order Filled Plus Quote Message: written and read back, then read and written back */
static void check_repo_order_filled_plus_quote_message(void) {
  RepoOrderFilledPlusQuoteMessage sent;
  RepoOrderFilledPlusQuoteMessage got;
  uint8_t wire[1581];
  uint8_t again[1581];

  any_repo_order_filled_plus_quote_message(&sent);
  assert(encode_repo_order_filled_plus_quote_message(&sent, wire, 0) == 1581);
  assert(decode_repo_order_filled_plus_quote_message(&got, wire, 0) == 1581);
  equal_repo_order_filled_plus_quote_message(&got, &sent);

  for (size_t i = 0; i < 1581; i++) { wire[i] = arbitrary(); }
  assert(decode_repo_order_filled_plus_quote_message(&got, wire, 0) == 1581);
  assert(encode_repo_order_filled_plus_quote_message(&got, again, 0) == 1581);
  for (size_t i = 0; i < 1581; i++) { assert(again[i] == wire[i]); }
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
  check_market_operation_ts_message();
  check_market_operation_schedule_message();
  check_issue_closing_message();
  check_member_firm_sanctions_message();
  check_regular_bonds_ktb_quote_message();
  check_bonds_order_filled_message();
  check_general_bonds_ktb_order_filled_plus_quote_message();
  check_bonds_negotiated_trade_data_message();
  check_repo_negotiated_trade_data_message();
  check_bonds_batch_data_message();
  check_repo_batch_data_message();
  check_issue_event_message();
  check_corporate_bonds_reference_message();
  check_regular_bonds_installment_repayment_date_message();
  check_repo_classification_data_message();
  check_repo_trade_availability_per_term_message();
  check_retail_bonds_type_code_message();
  check_baby_bonds_reporting_market_yield_message();
  check_ktb_confirmed_info_for_wit_message();
  check_ktb_short_term_yield_message();
  check_ktb_average_yield_message();
  check_bonds_credit_rating_information_message();
  check_regular_bonds_disclosure_basic_exchange_rate_message();
  check_investor_activities_per_bond_types_message();
  check_bonds_isin_issue_information_message();
  check_bonds_isin_information_text_message();
  check_baby_bonds_quote_message();
  check_repo_quote_message();
  check_bonds_total_remaining_volume_on_quotes_message();
  check_baby_bonds_order_filled_plus_quote_message();
  check_repo_order_filled_plus_quote_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
