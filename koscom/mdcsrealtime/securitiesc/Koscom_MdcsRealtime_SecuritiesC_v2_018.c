// koscom/mdcsrealtime/securitiesc/Koscom_MdcsRealtime_SecuritiesC_v2_018.c
/*
 * Koscom Co., Ltd. MDCS Realtime Securities C
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
  uint8_t index_accumulated_trading_value[12];         /* bytes 55 to 66 */
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
  for (size_t i = 0; i < 12; i++) { record->index_accumulated_trading_value[i] = arbitrary(); }
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
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->index_accumulated_trading_value[i]; }
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
  for (size_t i = 0; i < 12; i++) { record->index_accumulated_trading_value[i] = wire[at++]; }
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
  for (size_t i = 0; i < 12; i++) { assert(read->index_accumulated_trading_value[i] == written->index_accumulated_trading_value[i]); }
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
  uint8_t index_accumulated_trading_value[12];         /* bytes 55 to 66 */
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
  for (size_t i = 0; i < 12; i++) { record->index_accumulated_trading_value[i] = arbitrary(); }
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
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->index_accumulated_trading_value[i]; }
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
  for (size_t i = 0; i < 12; i++) { record->index_accumulated_trading_value[i] = wire[at++]; }
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
  for (size_t i = 0; i < 12; i++) { assert(read->index_accumulated_trading_value[i] == written->index_accumulated_trading_value[i]); }
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

/* ---- Securities Quote Mm Lp Excluded Message: 585 bytes ---------------------- */

/* Securities Quote (MM/LP Quotes Excluded). Multi-level bid/ask quotes and remaining quantities for KOSPI/KOSDAQ/KONEX equities. */
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
  uint8_t ask_level_6_price[11];                  /* bytes 272 to 282 */
  uint8_t bid_level_6_price[11];                  /* bytes 283 to 293 */
  uint8_t ask_level_6_volume[12];                 /* bytes 294 to 305 */
  uint8_t bid_level_6_volume[12];                 /* bytes 306 to 317 */
  uint8_t ask_level_7_price[11];                  /* bytes 318 to 328 */
  uint8_t bid_level_7_price[11];                  /* bytes 329 to 339 */
  uint8_t ask_level_7_volume[12];                 /* bytes 340 to 351 */
  uint8_t bid_level_7_volume[12];                 /* bytes 352 to 363 */
  uint8_t ask_level_8_price[11];                  /* bytes 364 to 374 */
  uint8_t bid_level_8_price[11];                  /* bytes 375 to 385 */
  uint8_t ask_level_8_volume[12];                 /* bytes 386 to 397 */
  uint8_t bid_level_8_volume[12];                 /* bytes 398 to 409 */
  uint8_t ask_level_9_price[11];                  /* bytes 410 to 420 */
  uint8_t bid_level_9_price[11];                  /* bytes 421 to 431 */
  uint8_t ask_level_9_volume[12];                 /* bytes 432 to 443 */
  uint8_t bid_level_9_volume[12];                 /* bytes 444 to 455 */
  uint8_t ask_level_10_price[11];                 /* bytes 456 to 466 */
  uint8_t bid_level_10_price[11];                 /* bytes 467 to 477 */
  uint8_t ask_level_10_volume[12];                /* bytes 478 to 489 */
  uint8_t bid_level_10_volume[12];                /* bytes 490 to 501 */
  uint8_t total_ask_volume[12];                   /* bytes 502 to 513 */
  uint8_t total_bid_volume[12];                   /* bytes 514 to 525 */
  uint8_t estimated_trading_price[11];            /* bytes 526 to 536 */
  uint8_t estimated_trading_volume[12];           /* bytes 537 to 548 */
  uint8_t midpoint[11];                           /* bytes 549 to 559 */
  uint8_t ask_mid_price_total_volume[12];         /* bytes 560 to 571 */
  uint8_t bid_mid_price_total_volume[12];         /* bytes 572 to 583 */
  uint8_t end_keyword;                            /* byte 584 */
} SecuritiesQuoteMmLpExcludedMessage;

/* any Securities Quote Mm Lp Excluded Message at all: every byte one the checker chooses */
static void any_securities_quote_mm_lp_excluded_message(SecuritiesQuoteMmLpExcludedMessage *record) {
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
  for (size_t i = 0; i < 11; i++) { record->ask_level_6_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_6_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_7_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_7_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_8_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_8_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_9_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_9_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_10_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_10_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->midpoint[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_mid_price_total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_mid_price_total_volume[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Quote Mm Lp Excluded Message to the wire: 585 bytes from at, returning where the next byte goes */
static size_t encode_securities_quote_mm_lp_excluded_message(const SecuritiesQuoteMmLpExcludedMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_6_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_6_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_6_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_6_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_7_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_7_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_7_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_7_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_8_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_8_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_8_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_8_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_9_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_9_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_9_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_9_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_10_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_10_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_10_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_10_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_ask_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_bid_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->estimated_trading_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->estimated_trading_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->midpoint[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_mid_price_total_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_mid_price_total_volume[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Quote Mm Lp Excluded Message off the wire: 585 bytes from at, returning where the next byte lies */
static size_t decode_securities_quote_mm_lp_excluded_message(SecuritiesQuoteMmLpExcludedMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 11; i++) { record->ask_level_6_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_6_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_7_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_7_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_8_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_8_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_9_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_9_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_10_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_10_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->midpoint[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_mid_price_total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_mid_price_total_volume[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Quote Mm Lp Excluded Message is what was written, byte for byte */
static void equal_securities_quote_mm_lp_excluded_message(const SecuritiesQuoteMmLpExcludedMessage *read, const SecuritiesQuoteMmLpExcludedMessage *written) {
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
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_6_price[i] == written->ask_level_6_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_6_price[i] == written->bid_level_6_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_6_volume[i] == written->ask_level_6_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_6_volume[i] == written->bid_level_6_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_7_price[i] == written->ask_level_7_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_7_price[i] == written->bid_level_7_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_7_volume[i] == written->ask_level_7_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_7_volume[i] == written->bid_level_7_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_8_price[i] == written->ask_level_8_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_8_price[i] == written->bid_level_8_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_8_volume[i] == written->ask_level_8_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_8_volume[i] == written->bid_level_8_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_9_price[i] == written->ask_level_9_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_9_price[i] == written->bid_level_9_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_9_volume[i] == written->ask_level_9_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_9_volume[i] == written->bid_level_9_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_10_price[i] == written->ask_level_10_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_10_price[i] == written->bid_level_10_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_10_volume[i] == written->ask_level_10_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_10_volume[i] == written->bid_level_10_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_ask_volume[i] == written->total_ask_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_bid_volume[i] == written->total_bid_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->estimated_trading_price[i] == written->estimated_trading_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->estimated_trading_volume[i] == written->estimated_trading_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->midpoint[i] == written->midpoint[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_mid_price_total_volume[i] == written->ask_mid_price_total_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_mid_price_total_volume[i] == written->bid_mid_price_total_volume[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Quote Mm Lp Excluded Message: written and read back, then read and written back */
static void check_securities_quote_mm_lp_excluded_message(void) {
  SecuritiesQuoteMmLpExcludedMessage sent;
  SecuritiesQuoteMmLpExcludedMessage got;
  uint8_t wire[585];
  uint8_t again[585];

  any_securities_quote_mm_lp_excluded_message(&sent);
  assert(encode_securities_quote_mm_lp_excluded_message(&sent, wire, 0) == 585);
  assert(decode_securities_quote_mm_lp_excluded_message(&got, wire, 0) == 585);
  equal_securities_quote_mm_lp_excluded_message(&got, &sent);

  for (size_t i = 0; i < 585; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_quote_mm_lp_excluded_message(&got, wire, 0) == 585);
  assert(encode_securities_quote_mm_lp_excluded_message(&got, again, 0) == 585);
  for (size_t i = 0; i < 585; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Quote Mm Lp Included Message: 825 bytes ---------------------- */

/* Securities Quote (MM/LP Quotes Included). Multi-level bid/ask quotes including market maker and liquidity provider quotes. */
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
  uint8_t midpoint[11];                           /* bytes 789 to 799 */
  uint8_t ask_mid_price_total_volume[12];         /* bytes 800 to 811 */
  uint8_t bid_mid_price_total_volume[12];         /* bytes 812 to 823 */
  uint8_t end_keyword;                            /* byte 824 */
} SecuritiesQuoteMmLpIncludedMessage;

/* any Securities Quote Mm Lp Included Message at all: every byte one the checker chooses */
static void any_securities_quote_mm_lp_included_message(SecuritiesQuoteMmLpIncludedMessage *record) {
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
  for (size_t i = 0; i < 11; i++) { record->midpoint[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_mid_price_total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_mid_price_total_volume[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Quote Mm Lp Included Message to the wire: 825 bytes from at, returning where the next byte goes */
static size_t encode_securities_quote_mm_lp_included_message(const SecuritiesQuoteMmLpIncludedMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->midpoint[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_mid_price_total_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_mid_price_total_volume[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Quote Mm Lp Included Message off the wire: 825 bytes from at, returning where the next byte lies */
static size_t decode_securities_quote_mm_lp_included_message(SecuritiesQuoteMmLpIncludedMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 11; i++) { record->midpoint[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_mid_price_total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_mid_price_total_volume[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Quote Mm Lp Included Message is what was written, byte for byte */
static void equal_securities_quote_mm_lp_included_message(const SecuritiesQuoteMmLpIncludedMessage *read, const SecuritiesQuoteMmLpIncludedMessage *written) {
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
  for (size_t i = 0; i < 11; i++) { assert(read->midpoint[i] == written->midpoint[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_mid_price_total_volume[i] == written->ask_mid_price_total_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_mid_price_total_volume[i] == written->bid_mid_price_total_volume[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Quote Mm Lp Included Message: written and read back, then read and written back */
static void check_securities_quote_mm_lp_included_message(void) {
  SecuritiesQuoteMmLpIncludedMessage sent;
  SecuritiesQuoteMmLpIncludedMessage got;
  uint8_t wire[825];
  uint8_t again[825];

  any_securities_quote_mm_lp_included_message(&sent);
  assert(encode_securities_quote_mm_lp_included_message(&sent, wire, 0) == 825);
  assert(decode_securities_quote_mm_lp_included_message(&got, wire, 0) == 825);
  equal_securities_quote_mm_lp_included_message(&got, &sent);

  for (size_t i = 0; i < 825; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_quote_mm_lp_included_message(&got, wire, 0) == 825);
  assert(encode_securities_quote_mm_lp_included_message(&got, again, 0) == 825);
  for (size_t i = 0; i < 825; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Snapshot Mm Lp Excluded Message: 680 bytes ------------------- */

/* Equities Snapshot (MM/LP Quotes Excluded). Periodic full state snapshot for KOSPI/KOSDAQ/KONEX equities. */
typedef struct {
  uint8_t board_id[2];                                  /* bytes 0 to 1 */
  uint8_t session_id[2];                                /* bytes 2 to 3 */
  uint8_t isin_code[12];                                /* bytes 4 to 15 */
  uint8_t a_designated_number_for_an_issue[6];          /* bytes 16 to 21 */
  uint8_t price_change_against_previous_day;            /* byte 22 */
  uint8_t a_price_change_against_the_previous_day[11];  /* bytes 23 to 33 */
  uint8_t upper_limit_price[11];                        /* bytes 34 to 44 */
  uint8_t lower_limit_price[11];                        /* bytes 45 to 55 */
  uint8_t current_price[11];                            /* bytes 56 to 66 */
  uint8_t opening_price[11];                            /* bytes 67 to 77 */
  uint8_t todays_high[11];                              /* bytes 78 to 88 */
  uint8_t todays_low[11];                               /* bytes 89 to 99 */
  uint8_t accumulated_trading_volume[12];               /* bytes 100 to 111 */
  uint8_t accumulated_trading_value[22];                /* bytes 112 to 133 */
  uint8_t final_ask_bid_type_code;                      /* byte 134 */
  uint8_t ask_level_1_price[11];                        /* bytes 135 to 145 */
  uint8_t bid_level_1_price[11];                        /* bytes 146 to 156 */
  uint8_t ask_level_1_volume[12];                       /* bytes 157 to 168 */
  uint8_t bid_level_1_volume[12];                       /* bytes 169 to 180 */
  uint8_t ask_level_2_price[11];                        /* bytes 181 to 191 */
  uint8_t bid_level_2_price[11];                        /* bytes 192 to 202 */
  uint8_t ask_level_2_volume[12];                       /* bytes 203 to 214 */
  uint8_t bid_level_2_volume[12];                       /* bytes 215 to 226 */
  uint8_t ask_level_3_price[11];                        /* bytes 227 to 237 */
  uint8_t bid_level_3_price[11];                        /* bytes 238 to 248 */
  uint8_t ask_level_3_volume[12];                       /* bytes 249 to 260 */
  uint8_t bid_level_3_volume[12];                       /* bytes 261 to 272 */
  uint8_t ask_level_4_price[11];                        /* bytes 273 to 283 */
  uint8_t bid_level_4_price[11];                        /* bytes 284 to 294 */
  uint8_t ask_level_4_volume[12];                       /* bytes 295 to 306 */
  uint8_t bid_level_4_volume[12];                       /* bytes 307 to 318 */
  uint8_t ask_level_5_price[11];                        /* bytes 319 to 329 */
  uint8_t bid_level_5_price[11];                        /* bytes 330 to 340 */
  uint8_t ask_level_5_volume[12];                       /* bytes 341 to 352 */
  uint8_t bid_level_5_volume[12];                       /* bytes 353 to 364 */
  uint8_t ask_level_6_price[11];                        /* bytes 365 to 375 */
  uint8_t bid_level_6_price[11];                        /* bytes 376 to 386 */
  uint8_t ask_level_6_volume[12];                       /* bytes 387 to 398 */
  uint8_t bid_level_6_volume[12];                       /* bytes 399 to 410 */
  uint8_t ask_level_7_price[11];                        /* bytes 411 to 421 */
  uint8_t bid_level_7_price[11];                        /* bytes 422 to 432 */
  uint8_t ask_level_7_volume[12];                       /* bytes 433 to 444 */
  uint8_t bid_level_7_volume[12];                       /* bytes 445 to 456 */
  uint8_t ask_level_8_price[11];                        /* bytes 457 to 467 */
  uint8_t bid_level_8_price[11];                        /* bytes 468 to 478 */
  uint8_t ask_level_8_volume[12];                       /* bytes 479 to 490 */
  uint8_t bid_level_8_volume[12];                       /* bytes 491 to 502 */
  uint8_t ask_level_9_price[11];                        /* bytes 503 to 513 */
  uint8_t bid_level_9_price[11];                        /* bytes 514 to 524 */
  uint8_t ask_level_9_volume[12];                       /* bytes 525 to 536 */
  uint8_t bid_level_9_volume[12];                       /* bytes 537 to 548 */
  uint8_t ask_level_10_price[11];                       /* bytes 549 to 559 */
  uint8_t bid_level_10_price[11];                       /* bytes 560 to 570 */
  uint8_t ask_level_10_volume[12];                      /* bytes 571 to 582 */
  uint8_t bid_level_10_volume[12];                      /* bytes 583 to 594 */
  uint8_t total_ask_volume[12];                         /* bytes 595 to 606 */
  uint8_t total_bid_volume[12];                         /* bytes 607 to 618 */
  uint8_t estimated_trading_price[11];                  /* bytes 619 to 629 */
  uint8_t estimated_trading_volume[12];                 /* bytes 630 to 641 */
  uint8_t closing_price_type_code;                      /* byte 642 */
  uint8_t trading_halt;                                 /* byte 643 */
  uint8_t midpoint[11];                                 /* bytes 644 to 654 */
  uint8_t ask_mid_price_total_volume[12];               /* bytes 655 to 666 */
  uint8_t bid_mid_price_total_volume[12];               /* bytes 667 to 678 */
  uint8_t end_keyword;                                  /* byte 679 */
} SecuritiesSnapshotMmLpExcludedMessage;

/* any Securities Snapshot Mm Lp Excluded Message at all: every byte one the checker chooses */
static void any_securities_snapshot_mm_lp_excluded_message(SecuritiesSnapshotMmLpExcludedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
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
  for (size_t i = 0; i < 11; i++) { record->ask_level_6_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_6_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_6_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_7_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_7_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_7_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_8_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_8_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_8_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_9_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_9_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_9_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ask_level_10_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->bid_level_10_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_level_10_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = arbitrary(); }
  record->closing_price_type_code = arbitrary();
  record->trading_halt = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->midpoint[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_mid_price_total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_mid_price_total_volume[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Snapshot Mm Lp Excluded Message to the wire: 680 bytes from at, returning where the next byte goes */
static size_t encode_securities_snapshot_mm_lp_excluded_message(const SecuritiesSnapshotMmLpExcludedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
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
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_6_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_6_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_6_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_6_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_7_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_7_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_7_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_7_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_8_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_8_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_8_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_8_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_9_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_9_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_9_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_9_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ask_level_10_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bid_level_10_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_level_10_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_level_10_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_ask_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_bid_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->estimated_trading_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->estimated_trading_volume[i]; }
  wire[at++] = record->closing_price_type_code;
  wire[at++] = record->trading_halt;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->midpoint[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_mid_price_total_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_mid_price_total_volume[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Snapshot Mm Lp Excluded Message off the wire: 680 bytes from at, returning where the next byte lies */
static size_t decode_securities_snapshot_mm_lp_excluded_message(SecuritiesSnapshotMmLpExcludedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
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
  for (size_t i = 0; i < 11; i++) { record->ask_level_6_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_6_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_6_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_7_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_7_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_7_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_8_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_8_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_8_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_9_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_9_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_9_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ask_level_10_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->bid_level_10_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_level_10_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_bid_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->estimated_trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->estimated_trading_volume[i] = wire[at++]; }
  record->closing_price_type_code = wire[at++];
  record->trading_halt = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->midpoint[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_mid_price_total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_mid_price_total_volume[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Snapshot Mm Lp Excluded Message is what was written, byte for byte */
static void equal_securities_snapshot_mm_lp_excluded_message(const SecuritiesSnapshotMmLpExcludedMessage *read, const SecuritiesSnapshotMmLpExcludedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
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
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_6_price[i] == written->ask_level_6_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_6_price[i] == written->bid_level_6_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_6_volume[i] == written->ask_level_6_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_6_volume[i] == written->bid_level_6_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_7_price[i] == written->ask_level_7_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_7_price[i] == written->bid_level_7_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_7_volume[i] == written->ask_level_7_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_7_volume[i] == written->bid_level_7_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_8_price[i] == written->ask_level_8_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_8_price[i] == written->bid_level_8_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_8_volume[i] == written->ask_level_8_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_8_volume[i] == written->bid_level_8_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_9_price[i] == written->ask_level_9_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_9_price[i] == written->bid_level_9_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_9_volume[i] == written->ask_level_9_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_9_volume[i] == written->bid_level_9_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ask_level_10_price[i] == written->ask_level_10_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->bid_level_10_price[i] == written->bid_level_10_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_level_10_volume[i] == written->ask_level_10_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_level_10_volume[i] == written->bid_level_10_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_ask_volume[i] == written->total_ask_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_bid_volume[i] == written->total_bid_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->estimated_trading_price[i] == written->estimated_trading_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->estimated_trading_volume[i] == written->estimated_trading_volume[i]); }
  assert(read->closing_price_type_code == written->closing_price_type_code);
  assert(read->trading_halt == written->trading_halt);
  for (size_t i = 0; i < 11; i++) { assert(read->midpoint[i] == written->midpoint[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_mid_price_total_volume[i] == written->ask_mid_price_total_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_mid_price_total_volume[i] == written->bid_mid_price_total_volume[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Snapshot Mm Lp Excluded Message: written and read back, then read and written back */
static void check_securities_snapshot_mm_lp_excluded_message(void) {
  SecuritiesSnapshotMmLpExcludedMessage sent;
  SecuritiesSnapshotMmLpExcludedMessage got;
  uint8_t wire[680];
  uint8_t again[680];

  any_securities_snapshot_mm_lp_excluded_message(&sent);
  assert(encode_securities_snapshot_mm_lp_excluded_message(&sent, wire, 0) == 680);
  assert(decode_securities_snapshot_mm_lp_excluded_message(&got, wire, 0) == 680);
  equal_securities_snapshot_mm_lp_excluded_message(&got, &sent);

  for (size_t i = 0; i < 680; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_snapshot_mm_lp_excluded_message(&got, wire, 0) == 680);
  assert(encode_securities_snapshot_mm_lp_excluded_message(&got, again, 0) == 680);
  for (size_t i = 0; i < 680; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Snapshot Mm Lp Included Message: 930 bytes ------------------- */

/* Equities Snapshot (MM/LP Quotes Included). Periodic full state snapshot including MM/LP quotes for Securities C. */
typedef struct {
  uint8_t board_id[2];                                  /* bytes 0 to 1 */
  uint8_t session_id[2];                                /* bytes 2 to 3 */
  uint8_t isin_code[12];                                /* bytes 4 to 15 */
  uint8_t a_designated_number_for_an_issue[6];          /* bytes 16 to 21 */
  uint8_t price_change_against_previous_day;            /* byte 22 */
  uint8_t a_price_change_against_the_previous_day[11];  /* bytes 23 to 33 */
  uint8_t upper_limit_price[11];                        /* bytes 34 to 44 */
  uint8_t lower_limit_price[11];                        /* bytes 45 to 55 */
  uint8_t current_price[11];                            /* bytes 56 to 66 */
  uint8_t opening_price[11];                            /* bytes 67 to 77 */
  uint8_t todays_high[11];                              /* bytes 78 to 88 */
  uint8_t todays_low[11];                               /* bytes 89 to 99 */
  uint8_t accumulated_trading_volume[12];               /* bytes 100 to 111 */
  uint8_t accumulated_trading_value[22];                /* bytes 112 to 133 */
  uint8_t final_ask_bid_type_code;                      /* byte 134 */
  uint8_t ask_level_1_price[11];                        /* bytes 135 to 145 */
  uint8_t bid_level_1_price[11];                        /* bytes 146 to 156 */
  uint8_t ask_level_1_volume[12];                       /* bytes 157 to 168 */
  uint8_t bid_level_1_volume[12];                       /* bytes 169 to 180 */
  uint8_t lp_ask_level_1_volume[12];                    /* bytes 181 to 192 */
  uint8_t lp_bid_level_1_volume[12];                    /* bytes 193 to 204 */
  uint8_t ask_level_2_price[11];                        /* bytes 205 to 215 */
  uint8_t bid_level_2_price[11];                        /* bytes 216 to 226 */
  uint8_t ask_level_2_volume[12];                       /* bytes 227 to 238 */
  uint8_t bid_level_2_volume[12];                       /* bytes 239 to 250 */
  uint8_t lp_ask_level_2_volume[12];                    /* bytes 251 to 262 */
  uint8_t lp_bid_level_2_volume[12];                    /* bytes 263 to 274 */
  uint8_t ask_level_3_price[11];                        /* bytes 275 to 285 */
  uint8_t bid_level_3_price[11];                        /* bytes 286 to 296 */
  uint8_t ask_level_3_volume[12];                       /* bytes 297 to 308 */
  uint8_t bid_level_3_volume[12];                       /* bytes 309 to 320 */
  uint8_t lp_ask_level_3_volume[12];                    /* bytes 321 to 332 */
  uint8_t lp_bid_level_3_volume[12];                    /* bytes 333 to 344 */
  uint8_t ask_level_4_price[11];                        /* bytes 345 to 355 */
  uint8_t bid_level_4_price[11];                        /* bytes 356 to 366 */
  uint8_t ask_level_4_volume[12];                       /* bytes 367 to 378 */
  uint8_t bid_level_4_volume[12];                       /* bytes 379 to 390 */
  uint8_t lp_ask_level_4_volume[12];                    /* bytes 391 to 402 */
  uint8_t lp_bid_level_4_volume[12];                    /* bytes 403 to 414 */
  uint8_t ask_level_5_price[11];                        /* bytes 415 to 425 */
  uint8_t bid_level_5_price[11];                        /* bytes 426 to 436 */
  uint8_t ask_level_5_volume[12];                       /* bytes 437 to 448 */
  uint8_t bid_level_5_volume[12];                       /* bytes 449 to 460 */
  uint8_t lp_ask_level_5_volume[12];                    /* bytes 461 to 472 */
  uint8_t lp_bid_level_5_volume[12];                    /* bytes 473 to 484 */
  uint8_t ask_level_6_price[11];                        /* bytes 485 to 495 */
  uint8_t bid_level_6_price[11];                        /* bytes 496 to 506 */
  uint8_t ask_level_6_volume[12];                       /* bytes 507 to 518 */
  uint8_t bid_level_6_volume[12];                       /* bytes 519 to 530 */
  uint8_t lp_ask_level_6_volume[12];                    /* bytes 531 to 542 */
  uint8_t lp_bid_level_6_volume[12];                    /* bytes 543 to 554 */
  uint8_t ask_level_7_price[11];                        /* bytes 555 to 565 */
  uint8_t bid_level_7_price[11];                        /* bytes 566 to 576 */
  uint8_t ask_level_7_volume[12];                       /* bytes 577 to 588 */
  uint8_t bid_level_7_volume[12];                       /* bytes 589 to 600 */
  uint8_t lp_ask_level_7_volume[12];                    /* bytes 601 to 612 */
  uint8_t lp_bid_level_7_volume[12];                    /* bytes 613 to 624 */
  uint8_t ask_level_8_price[11];                        /* bytes 625 to 635 */
  uint8_t bid_level_8_price[11];                        /* bytes 636 to 646 */
  uint8_t ask_level_8_volume[12];                       /* bytes 647 to 658 */
  uint8_t bid_level_8_volume[12];                       /* bytes 659 to 670 */
  uint8_t lp_ask_level_8_volume[12];                    /* bytes 671 to 682 */
  uint8_t lp_bid_level_8_volume[12];                    /* bytes 683 to 694 */
  uint8_t ask_level_9_price[11];                        /* bytes 695 to 705 */
  uint8_t bid_level_9_price[11];                        /* bytes 706 to 716 */
  uint8_t ask_level_9_volume[12];                       /* bytes 717 to 728 */
  uint8_t bid_level_9_volume[12];                       /* bytes 729 to 740 */
  uint8_t lp_ask_level_9_volume[12];                    /* bytes 741 to 752 */
  uint8_t lp_bid_level_9_volume[12];                    /* bytes 753 to 764 */
  uint8_t ask_level_10_price[11];                       /* bytes 765 to 775 */
  uint8_t bid_level_10_price[11];                       /* bytes 776 to 786 */
  uint8_t ask_level_10_volume[12];                      /* bytes 787 to 798 */
  uint8_t bid_level_10_volume[12];                      /* bytes 799 to 810 */
  uint8_t lp_ask_level_10_volume[12];                   /* bytes 811 to 822 */
  uint8_t lp_bid_level_10_volume[12];                   /* bytes 823 to 834 */
  uint8_t total_ask_volume[12];                         /* bytes 835 to 846 */
  uint8_t total_bid_volume[12];                         /* bytes 847 to 858 */
  uint8_t estimated_trading_price[11];                  /* bytes 859 to 869 */
  uint8_t estimated_trading_volume[12];                 /* bytes 870 to 881 */
  uint8_t closing_price_type_code;                      /* byte 882 */
  uint8_t trading_halt;                                 /* byte 883 */
  uint8_t knock_out_elw_type_code;                      /* byte 884 */
  uint8_t knock_out_elw_triggering_time[9];             /* bytes 885 to 893 */
  uint8_t midpoint[11];                                 /* bytes 894 to 904 */
  uint8_t ask_mid_price_total_volume[12];               /* bytes 905 to 916 */
  uint8_t bid_mid_price_total_volume[12];               /* bytes 917 to 928 */
  uint8_t end_keyword;                                  /* byte 929 */
} SecuritiesSnapshotMmLpIncludedMessage;

/* any Securities Snapshot Mm Lp Included Message at all: every byte one the checker chooses */
static void any_securities_snapshot_mm_lp_included_message(SecuritiesSnapshotMmLpIncludedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
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
  for (size_t i = 0; i < 11; i++) { record->midpoint[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_mid_price_total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_mid_price_total_volume[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Snapshot Mm Lp Included Message to the wire: 930 bytes from at, returning where the next byte goes */
static size_t encode_securities_snapshot_mm_lp_included_message(const SecuritiesSnapshotMmLpIncludedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
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
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->midpoint[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_mid_price_total_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_mid_price_total_volume[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Snapshot Mm Lp Included Message off the wire: 930 bytes from at, returning where the next byte lies */
static size_t decode_securities_snapshot_mm_lp_included_message(SecuritiesSnapshotMmLpIncludedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
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
  for (size_t i = 0; i < 11; i++) { record->midpoint[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_mid_price_total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_mid_price_total_volume[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Snapshot Mm Lp Included Message is what was written, byte for byte */
static void equal_securities_snapshot_mm_lp_included_message(const SecuritiesSnapshotMmLpIncludedMessage *read, const SecuritiesSnapshotMmLpIncludedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
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
  for (size_t i = 0; i < 11; i++) { assert(read->midpoint[i] == written->midpoint[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_mid_price_total_volume[i] == written->ask_mid_price_total_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_mid_price_total_volume[i] == written->bid_mid_price_total_volume[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Snapshot Mm Lp Included Message: written and read back, then read and written back */
static void check_securities_snapshot_mm_lp_included_message(void) {
  SecuritiesSnapshotMmLpIncludedMessage sent;
  SecuritiesSnapshotMmLpIncludedMessage got;
  uint8_t wire[930];
  uint8_t again[930];

  any_securities_snapshot_mm_lp_included_message(&sent);
  assert(encode_securities_snapshot_mm_lp_included_message(&sent, wire, 0) == 930);
  assert(decode_securities_snapshot_mm_lp_included_message(&got, wire, 0) == 930);
  equal_securities_snapshot_mm_lp_included_message(&got, &sent);

  for (size_t i = 0; i < 930; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_snapshot_mm_lp_included_message(&got, wire, 0) == 930);
  assert(encode_securities_snapshot_mm_lp_included_message(&got, again, 0) == 930);
  for (size_t i = 0; i < 930; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Order Filled Message: 181 bytes ------------------------------ */

/* Securities Order Filled. Real-time trade prints with running totals for KOSPI/KOSDAQ/KONEX equities. */
typedef struct {
  uint8_t message_sequence_number[8];                   /* bytes 0 to 7 */
  uint8_t board_id[2];                                  /* bytes 8 to 9 */
  uint8_t session_id[2];                                /* bytes 10 to 11 */
  uint8_t isin_code[12];                                /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue[6];          /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];        /* bytes 30 to 41 */
  uint8_t price_change_against_previous_day;            /* byte 42 */
  uint8_t a_price_change_against_the_previous_day[11];  /* bytes 43 to 53 */
  uint8_t trading_price[11];                            /* bytes 54 to 64 */
  uint8_t trading_volume[10];                           /* bytes 65 to 74 */
  uint8_t opening_price[11];                            /* bytes 75 to 85 */
  uint8_t todays_high[11];                              /* bytes 86 to 96 */
  uint8_t todays_low[11];                               /* bytes 97 to 107 */
  uint8_t accumulated_trading_volume[12];               /* bytes 108 to 119 */
  uint8_t accumulated_trading_value[22];                /* bytes 120 to 141 */
  uint8_t final_ask_bid_type_code;                      /* byte 142 */
  uint8_t lp_holding_quantity[15];                      /* bytes 143 to 157 */
  uint8_t the_best_ask[11];                             /* bytes 158 to 168 */
  uint8_t the_best_bid[11];                             /* bytes 169 to 179 */
  uint8_t end_keyword;                                  /* byte 180 */
} SecuritiesOrderFilledMessage;

/* any Securities Order Filled Message at all: every byte one the checker chooses */
static void any_securities_order_filled_message(SecuritiesOrderFilledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
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
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
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
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
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
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
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

/* ---- Securities Negotiated Trade Message: 55 bytes --------------------------- */

/* Securities Negotiated Trade Data. Off-book negotiated trades for KOSPI/KOSDAQ/KONEX equities. */
typedef struct {
  uint8_t board_id[2];                          /* bytes 0 to 1 */
  uint8_t isin_code[12];                        /* bytes 2 to 13 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 14 to 19 */
  uint8_t accumulated_trading_volume[12];       /* bytes 20 to 31 */
  uint8_t accumulated_trading_value[22];        /* bytes 32 to 53 */
  uint8_t end_keyword;                          /* byte 54 */
} SecuritiesNegotiatedTradeMessage;

/* any Securities Negotiated Trade Message at all: every byte one the checker chooses */
static void any_securities_negotiated_trade_message(SecuritiesNegotiatedTradeMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Negotiated Trade Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_securities_negotiated_trade_message(const SecuritiesNegotiatedTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Negotiated Trade Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_securities_negotiated_trade_message(SecuritiesNegotiatedTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Negotiated Trade Message is what was written, byte for byte */
static void equal_securities_negotiated_trade_message(const SecuritiesNegotiatedTradeMessage *read, const SecuritiesNegotiatedTradeMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value[i] == written->accumulated_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Negotiated Trade Message: written and read back, then read and written back */
static void check_securities_negotiated_trade_message(void) {
  SecuritiesNegotiatedTradeMessage sent;
  SecuritiesNegotiatedTradeMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_securities_negotiated_trade_message(&sent);
  assert(encode_securities_negotiated_trade_message(&sent, wire, 0) == 55);
  assert(decode_securities_negotiated_trade_message(&got, wire, 0) == 55);
  equal_securities_negotiated_trade_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_negotiated_trade_message(&got, wire, 0) == 55);
  assert(encode_securities_negotiated_trade_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Market Operation Ts Message: 63 bytes ------------------------ */

/* Securities Market Operation TS. Per-issue session-state events (halts, resumes, expirations) for KOSPI/KOSDAQ/KONEX. */
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
} SecuritiesMarketOperationTsMessage;

/* any Securities Market Operation Ts Message at all: every byte one the checker chooses */
static void any_securities_market_operation_ts_message(SecuritiesMarketOperationTsMessage *record) {
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

/* Securities Market Operation Ts Message to the wire: 63 bytes from at, returning where the next byte goes */
static size_t encode_securities_market_operation_ts_message(const SecuritiesMarketOperationTsMessage *record, uint8_t *wire, size_t at) {
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

/* Securities Market Operation Ts Message off the wire: 63 bytes from at, returning where the next byte lies */
static size_t decode_securities_market_operation_ts_message(SecuritiesMarketOperationTsMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Securities Market Operation Ts Message is what was written, byte for byte */
static void equal_securities_market_operation_ts_message(const SecuritiesMarketOperationTsMessage *read, const SecuritiesMarketOperationTsMessage *written) {
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

/* Securities Market Operation Ts Message: written and read back, then read and written back */
static void check_securities_market_operation_ts_message(void) {
  SecuritiesMarketOperationTsMessage sent;
  SecuritiesMarketOperationTsMessage got;
  uint8_t wire[63];
  uint8_t again[63];

  any_securities_market_operation_ts_message(&sent);
  assert(encode_securities_market_operation_ts_message(&sent, wire, 0) == 63);
  assert(decode_securities_market_operation_ts_message(&got, wire, 0) == 63);
  equal_securities_market_operation_ts_message(&got, &sent);

  for (size_t i = 0; i < 63; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_market_operation_ts_message(&got, wire, 0) == 63);
  assert(encode_securities_market_operation_ts_message(&got, again, 0) == 63);
  for (size_t i = 0; i < 63; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Determination Of Base Price Message: 62 bytes ---------------- */

/* Determination of Base Price. Per-issue base price assignment events. */
typedef struct {
  uint8_t message_sequence_number[8];           /* bytes 0 to 7 */
  uint8_t board_id[2];                          /* bytes 8 to 9 */
  uint8_t isin_code[12];                        /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 22 to 27 */
  uint8_t base_price[11];                       /* bytes 28 to 38 */
  uint8_t upper_limit_of_base_price[11];        /* bytes 39 to 49 */
  uint8_t lower_limit_of_base_price[11];        /* bytes 50 to 60 */
  uint8_t end_keyword;                          /* byte 61 */
} SecuritiesDeterminationOfBasePriceMessage;

/* any Securities Determination Of Base Price Message at all: every byte one the checker chooses */
static void any_securities_determination_of_base_price_message(SecuritiesDeterminationOfBasePriceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->upper_limit_of_base_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_of_base_price[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Determination Of Base Price Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_securities_determination_of_base_price_message(const SecuritiesDeterminationOfBasePriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->base_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->upper_limit_of_base_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lower_limit_of_base_price[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Determination Of Base Price Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_securities_determination_of_base_price_message(SecuritiesDeterminationOfBasePriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->upper_limit_of_base_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_of_base_price[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Determination Of Base Price Message is what was written, byte for byte */
static void equal_securities_determination_of_base_price_message(const SecuritiesDeterminationOfBasePriceMessage *read, const SecuritiesDeterminationOfBasePriceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->base_price[i] == written->base_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->upper_limit_of_base_price[i] == written->upper_limit_of_base_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lower_limit_of_base_price[i] == written->lower_limit_of_base_price[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Determination Of Base Price Message: written and read back, then read and written back */
static void check_securities_determination_of_base_price_message(void) {
  SecuritiesDeterminationOfBasePriceMessage sent;
  SecuritiesDeterminationOfBasePriceMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_securities_determination_of_base_price_message(&sent);
  assert(encode_securities_determination_of_base_price_message(&sent, wire, 0) == 62);
  assert(decode_securities_determination_of_base_price_message(&got, wire, 0) == 62);
  equal_securities_determination_of_base_price_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_determination_of_base_price_message(&got, wire, 0) == 62);
  assert(encode_securities_determination_of_base_price_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Issue Closing Message: 107 bytes ----------------------------- */

/* Securities Issue Closing. Per-issue closing event for KOSPI/KOSDAQ/KONEX. */
typedef struct {
  uint8_t message_sequence_number[8];                      /* bytes 0 to 7 */
  uint8_t board_id[2];                                     /* bytes 8 to 9 */
  uint8_t isin_code[12];                                   /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];             /* bytes 22 to 27 */
  uint8_t closing_price[11];                               /* bytes 28 to 38 */
  uint8_t closing_price_type_code;                         /* byte 39 */
  uint8_t filler_11[11];                                   /* bytes 40 to 50 */
  uint8_t second_filler_11[11];                            /* bytes 51 to 61 */
  uint8_t closing_price_weighted_stock_price_average[11];  /* bytes 62 to 72 */
  uint8_t closing_price_base_price_of_buy_in[11];          /* bytes 73 to 83 */
  uint8_t closing_price_upper_limit_of_buy_in[11];         /* bytes 84 to 94 */
  uint8_t closing_price_lower_limit_of_buy_in[11];         /* bytes 95 to 105 */
  uint8_t end_keyword;                                     /* byte 106 */
} SecuritiesIssueClosingMessage;

/* any Securities Issue Closing Message at all: every byte one the checker chooses */
static void any_securities_issue_closing_message(SecuritiesIssueClosingMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price[i] = arbitrary(); }
  record->closing_price_type_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->filler_11[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->second_filler_11[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_weighted_stock_price_average[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_base_price_of_buy_in[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_upper_limit_of_buy_in[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_lower_limit_of_buy_in[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Issue Closing Message to the wire: 107 bytes from at, returning where the next byte goes */
static size_t encode_securities_issue_closing_message(const SecuritiesIssueClosingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price[i]; }
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

/* Securities Issue Closing Message off the wire: 107 bytes from at, returning where the next byte lies */
static size_t decode_securities_issue_closing_message(SecuritiesIssueClosingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price[i] = wire[at++]; }
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

/* what was read of Securities Issue Closing Message is what was written, byte for byte */
static void equal_securities_issue_closing_message(const SecuritiesIssueClosingMessage *read, const SecuritiesIssueClosingMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  assert(read->closing_price_type_code == written->closing_price_type_code);
  for (size_t i = 0; i < 11; i++) { assert(read->filler_11[i] == written->filler_11[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->second_filler_11[i] == written->second_filler_11[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_weighted_stock_price_average[i] == written->closing_price_weighted_stock_price_average[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_base_price_of_buy_in[i] == written->closing_price_base_price_of_buy_in[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_upper_limit_of_buy_in[i] == written->closing_price_upper_limit_of_buy_in[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_lower_limit_of_buy_in[i] == written->closing_price_lower_limit_of_buy_in[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Issue Closing Message: written and read back, then read and written back */
static void check_securities_issue_closing_message(void) {
  SecuritiesIssueClosingMessage sent;
  SecuritiesIssueClosingMessage got;
  uint8_t wire[107];
  uint8_t again[107];

  any_securities_issue_closing_message(&sent);
  assert(encode_securities_issue_closing_message(&sent, wire, 0) == 107);
  assert(decode_securities_issue_closing_message(&got, wire, 0) == 107);
  equal_securities_issue_closing_message(&got, &sent);

  for (size_t i = 0; i < 107; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_issue_closing_message(&got, wire, 0) == 107);
  assert(encode_securities_issue_closing_message(&got, again, 0) == 107);
  for (size_t i = 0; i < 107; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Market Operation Schedule Message: 78 bytes ------------------ */

/* Securities Market Operation Schedule. Session-level schedule and configuration changes. */
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
} SecuritiesMarketOperationScheduleMessage;

/* any Securities Market Operation Schedule Message at all: every byte one the checker chooses */
static void any_securities_market_operation_schedule_message(SecuritiesMarketOperationScheduleMessage *record) {
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

/* Securities Market Operation Schedule Message to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_securities_market_operation_schedule_message(const SecuritiesMarketOperationScheduleMessage *record, uint8_t *wire, size_t at) {
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

/* Securities Market Operation Schedule Message off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_securities_market_operation_schedule_message(SecuritiesMarketOperationScheduleMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Securities Market Operation Schedule Message is what was written, byte for byte */
static void equal_securities_market_operation_schedule_message(const SecuritiesMarketOperationScheduleMessage *read, const SecuritiesMarketOperationScheduleMessage *written) {
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

/* Securities Market Operation Schedule Message: written and read back, then read and written back */
static void check_securities_market_operation_schedule_message(void) {
  SecuritiesMarketOperationScheduleMessage sent;
  SecuritiesMarketOperationScheduleMessage got;
  uint8_t wire[78];
  uint8_t again[78];

  any_securities_market_operation_schedule_message(&sent);
  assert(encode_securities_market_operation_schedule_message(&sent, wire, 0) == 78);
  assert(decode_securities_market_operation_schedule_message(&got, wire, 0) == 78);
  equal_securities_market_operation_schedule_message(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_market_operation_schedule_message(&got, wire, 0) == 78);
  assert(encode_securities_market_operation_schedule_message(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Random End Message: 30 bytes --------------------------------- */

/* Random End. Reports random extension of the call auction window when conditional random-end is triggered. */
typedef struct {
  uint8_t message_sequence_number[8];           /* bytes 0 to 7 */
  uint8_t board_id[2];                          /* bytes 8 to 9 */
  uint8_t isin_code[12];                        /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 22 to 27 */
  uint8_t random_end_trigger_code;              /* byte 28 */
  uint8_t end_keyword;                          /* byte 29 */
} SecuritiesRandomEndMessage;

/* any Securities Random End Message at all: every byte one the checker chooses */
static void any_securities_random_end_message(SecuritiesRandomEndMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  record->random_end_trigger_code = arbitrary();
  record->end_keyword = arbitrary();
}

/* Securities Random End Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_securities_random_end_message(const SecuritiesRandomEndMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  wire[at++] = record->random_end_trigger_code;
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Random End Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_securities_random_end_message(SecuritiesRandomEndMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  record->random_end_trigger_code = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Random End Message is what was written, byte for byte */
static void equal_securities_random_end_message(const SecuritiesRandomEndMessage *read, const SecuritiesRandomEndMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  assert(read->random_end_trigger_code == written->random_end_trigger_code);
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Random End Message: written and read back, then read and written back */
static void check_securities_random_end_message(void) {
  SecuritiesRandomEndMessage sent;
  SecuritiesRandomEndMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_securities_random_end_message(&sent);
  assert(encode_securities_random_end_message(&sent, wire, 0) == 30);
  assert(decode_securities_random_end_message(&got, wire, 0) == 30);
  equal_securities_random_end_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_random_end_message(&got, wire, 0) == 30);
  assert(encode_securities_random_end_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Triggering Vi Message: 111 bytes ----------------------------- */

/* Triggering/Removing VI (Volatility Interruption). Per-issue VI trigger or release event. */
typedef struct {
  uint8_t message_sequence_number[8];                 /* bytes 0 to 7 */
  uint8_t board_id[2];                                /* bytes 8 to 9 */
  uint8_t isin_code[12];                              /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];        /* bytes 22 to 27 */
  uint8_t processing_time_of_trading_system[12];      /* bytes 28 to 39 */
  uint8_t the_time_ending_vi[9];                      /* bytes 40 to 48 */
  uint8_t vi_status_code;                             /* byte 49 */
  uint8_t vi_type_code;                               /* byte 50 */
  uint8_t a_base_price_to_trigger_static_vi[11];      /* bytes 51 to 61 */
  uint8_t a_base_price_to_trigger_dynamic_vi[11];     /* bytes 62 to 72 */
  uint8_t vi_triggering_price[11];                    /* bytes 73 to 83 */
  uint8_t disparate_ratio_to_trigger_static_vi[13];   /* bytes 84 to 96 */
  uint8_t disparate_ratio_to_trigger_dynamic_vi[13];  /* bytes 97 to 109 */
  uint8_t end_keyword;                                /* byte 110 */
} SecuritiesTriggeringViMessage;

/* any Securities Triggering Vi Message at all: every byte one the checker chooses */
static void any_securities_triggering_vi_message(SecuritiesTriggeringViMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
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

/* Securities Triggering Vi Message to the wire: 111 bytes from at, returning where the next byte goes */
static size_t encode_securities_triggering_vi_message(const SecuritiesTriggeringViMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
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

/* Securities Triggering Vi Message off the wire: 111 bytes from at, returning where the next byte lies */
static size_t decode_securities_triggering_vi_message(SecuritiesTriggeringViMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
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

/* what was read of Securities Triggering Vi Message is what was written, byte for byte */
static void equal_securities_triggering_vi_message(const SecuritiesTriggeringViMessage *read, const SecuritiesTriggeringViMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
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

/* Securities Triggering Vi Message: written and read back, then read and written back */
static void check_securities_triggering_vi_message(void) {
  SecuritiesTriggeringViMessage sent;
  SecuritiesTriggeringViMessage got;
  uint8_t wire[111];
  uint8_t again[111];

  any_securities_triggering_vi_message(&sent);
  assert(encode_securities_triggering_vi_message(&sent, wire, 0) == 111);
  assert(decode_securities_triggering_vi_message(&got, wire, 0) == 111);
  equal_securities_triggering_vi_message(&got, &sent);

  for (size_t i = 0; i < 111; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_triggering_vi_message(&got, wire, 0) == 111);
  assert(encode_securities_triggering_vi_message(&got, again, 0) == 111);
  for (size_t i = 0; i < 111; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Quantity Allocation Message: 40 bytes ------------------------ */

/* Quantity Allocation. Reports the quantity allocated to each price level at a single price trade match. */
typedef struct {
  uint8_t message_sequence_number[8];           /* bytes 0 to 7 */
  uint8_t board_id[2];                          /* bytes 8 to 9 */
  uint8_t isin_code[12];                        /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 22 to 27 */
  uint8_t start_end_of_allocation;              /* byte 28 */
  uint8_t allocation_type_code;                 /* byte 29 */
  uint8_t time_when_allocation_ended[9];        /* bytes 30 to 38 */
  uint8_t end_keyword;                          /* byte 39 */
} SecuritiesQuantityAllocationMessage;

/* any Securities Quantity Allocation Message at all: every byte one the checker chooses */
static void any_securities_quantity_allocation_message(SecuritiesQuantityAllocationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  record->start_end_of_allocation = arbitrary();
  record->allocation_type_code = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->time_when_allocation_ended[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Quantity Allocation Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_securities_quantity_allocation_message(const SecuritiesQuantityAllocationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  wire[at++] = record->start_end_of_allocation;
  wire[at++] = record->allocation_type_code;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->time_when_allocation_ended[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Quantity Allocation Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_securities_quantity_allocation_message(SecuritiesQuantityAllocationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  record->start_end_of_allocation = wire[at++];
  record->allocation_type_code = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->time_when_allocation_ended[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Quantity Allocation Message is what was written, byte for byte */
static void equal_securities_quantity_allocation_message(const SecuritiesQuantityAllocationMessage *read, const SecuritiesQuantityAllocationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  assert(read->start_end_of_allocation == written->start_end_of_allocation);
  assert(read->allocation_type_code == written->allocation_type_code);
  for (size_t i = 0; i < 9; i++) { assert(read->time_when_allocation_ended[i] == written->time_when_allocation_ended[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Quantity Allocation Message: written and read back, then read and written back */
static void check_securities_quantity_allocation_message(void) {
  SecuritiesQuantityAllocationMessage sent;
  SecuritiesQuantityAllocationMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_securities_quantity_allocation_message(&sent);
  assert(encode_securities_quantity_allocation_message(&sent, wire, 0) == 40);
  assert(decode_securities_quantity_allocation_message(&got, wire, 0) == 40);
  equal_securities_quantity_allocation_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_quantity_allocation_message(&got, wire, 0) == 40);
  assert(encode_securities_quantity_allocation_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Member Firm Sanctions Message: 41 bytes ---------------------- */

/* Securities Member Firm Imposing/Lifting of Sanctions. */
typedef struct {
  uint8_t isin_code[12];                             /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue[6];       /* bytes 12 to 17 */
  uint8_t disclosing_data_type_code[3];              /* bytes 18 to 20 */
  uint8_t disclosure_time[9];                        /* bytes 21 to 29 */
  uint8_t member_number[5];                          /* bytes 30 to 34 */
  uint8_t member_firm_trust_principal_type_code[5];  /* bytes 35 to 39 */
  uint8_t end_keyword;                               /* byte 40 */
} SecuritiesMemberFirmSanctionsMessage;

/* any Securities Member Firm Sanctions Message at all: every byte one the checker chooses */
static void any_securities_member_firm_sanctions_message(SecuritiesMemberFirmSanctionsMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->disclosing_data_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->disclosure_time[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_number[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->member_firm_trust_principal_type_code[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Member Firm Sanctions Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_securities_member_firm_sanctions_message(const SecuritiesMemberFirmSanctionsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->disclosing_data_type_code[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->disclosure_time[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_number[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_firm_trust_principal_type_code[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Member Firm Sanctions Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_securities_member_firm_sanctions_message(SecuritiesMemberFirmSanctionsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->disclosing_data_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->disclosure_time[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_number[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->member_firm_trust_principal_type_code[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Member Firm Sanctions Message is what was written, byte for byte */
static void equal_securities_member_firm_sanctions_message(const SecuritiesMemberFirmSanctionsMessage *read, const SecuritiesMemberFirmSanctionsMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->disclosing_data_type_code[i] == written->disclosing_data_type_code[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->disclosure_time[i] == written->disclosure_time[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_number[i] == written->member_number[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->member_firm_trust_principal_type_code[i] == written->member_firm_trust_principal_type_code[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Member Firm Sanctions Message: written and read back, then read and written back */
static void check_securities_member_firm_sanctions_message(void) {
  SecuritiesMemberFirmSanctionsMessage sent;
  SecuritiesMemberFirmSanctionsMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_securities_member_firm_sanctions_message(&sent);
  assert(encode_securities_member_firm_sanctions_message(&sent, wire, 0) == 41);
  assert(decode_securities_member_firm_sanctions_message(&got, wire, 0) == 41);
  equal_securities_member_firm_sanctions_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_member_firm_sanctions_message(&got, wire, 0) == 41);
  assert(encode_securities_member_firm_sanctions_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Equities Changes Of Batch Data Message: 124 bytes ------------ */

/* Equities Changes of Batch data. Mid-day updates to issue-level batch reference fields. */
typedef struct {
  uint8_t board_id[2];                                                                       /* bytes 0 to 1 */
  uint8_t isin_code[12];                                                                     /* bytes 2 to 13 */
  uint8_t a_designated_number_for_an_issue[6];                                               /* bytes 14 to 19 */
  uint8_t disclosing_data_type_code[3];                                                      /* bytes 20 to 22 */
  uint8_t base_price[11];                                                                    /* bytes 23 to 33 */
  uint8_t upper_limit_price[11];                                                             /* bytes 34 to 44 */
  uint8_t lower_limit_price[11];                                                             /* bytes 45 to 55 */
  uint8_t appraised_price[11];                                                               /* bytes 56 to 66 */
  uint8_t highest_order_price[11];                                                           /* bytes 67 to 77 */
  uint8_t lowest_order_price[11];                                                            /* bytes 78 to 88 */
  uint8_t type_code_for_an_issue_of_which_base_price_is_settled_with_a_todays_single_price;  /* byte 89 */
  uint8_t rights_type_code[2];                                                               /* bytes 90 to 91 */
  uint8_t par_value_type_code[2];                                                            /* bytes 92 to 93 */
  uint8_t lot_sizes[11];                                                                     /* bytes 94 to 104 */
  uint8_t number_of_listed_shares[16];                                                       /* bytes 105 to 120 */
  uint8_t designation;                                                                       /* byte 121 */
  uint8_t closing_price_trading_in_the_pre_opening_market;                                   /* byte 122 */
  uint8_t end_keyword;                                                                       /* byte 123 */
} SecuritiesEquitiesChangesOfBatchDataMessage;

/* any Securities Equities Changes Of Batch Data Message at all: every byte one the checker chooses */
static void any_securities_equities_changes_of_batch_data_message(SecuritiesEquitiesChangesOfBatchDataMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->disclosing_data_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->upper_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->appraised_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->highest_order_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lowest_order_price[i] = arbitrary(); }
  record->type_code_for_an_issue_of_which_base_price_is_settled_with_a_todays_single_price = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->rights_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->par_value_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lot_sizes[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->number_of_listed_shares[i] = arbitrary(); }
  record->designation = arbitrary();
  record->closing_price_trading_in_the_pre_opening_market = arbitrary();
  record->end_keyword = arbitrary();
}

/* Securities Equities Changes Of Batch Data Message to the wire: 124 bytes from at, returning where the next byte goes */
static size_t encode_securities_equities_changes_of_batch_data_message(const SecuritiesEquitiesChangesOfBatchDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->disclosing_data_type_code[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->base_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->upper_limit_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lower_limit_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->appraised_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->highest_order_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lowest_order_price[i]; }
  wire[at++] = record->type_code_for_an_issue_of_which_base_price_is_settled_with_a_todays_single_price;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->rights_type_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->par_value_type_code[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lot_sizes[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->number_of_listed_shares[i]; }
  wire[at++] = record->designation;
  wire[at++] = record->closing_price_trading_in_the_pre_opening_market;
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Equities Changes Of Batch Data Message off the wire: 124 bytes from at, returning where the next byte lies */
static size_t decode_securities_equities_changes_of_batch_data_message(SecuritiesEquitiesChangesOfBatchDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->disclosing_data_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->upper_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lower_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->appraised_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->highest_order_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lowest_order_price[i] = wire[at++]; }
  record->type_code_for_an_issue_of_which_base_price_is_settled_with_a_todays_single_price = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->rights_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->par_value_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lot_sizes[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->number_of_listed_shares[i] = wire[at++]; }
  record->designation = wire[at++];
  record->closing_price_trading_in_the_pre_opening_market = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Equities Changes Of Batch Data Message is what was written, byte for byte */
static void equal_securities_equities_changes_of_batch_data_message(const SecuritiesEquitiesChangesOfBatchDataMessage *read, const SecuritiesEquitiesChangesOfBatchDataMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->disclosing_data_type_code[i] == written->disclosing_data_type_code[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->base_price[i] == written->base_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->upper_limit_price[i] == written->upper_limit_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lower_limit_price[i] == written->lower_limit_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->appraised_price[i] == written->appraised_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->highest_order_price[i] == written->highest_order_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lowest_order_price[i] == written->lowest_order_price[i]); }
  assert(read->type_code_for_an_issue_of_which_base_price_is_settled_with_a_todays_single_price == written->type_code_for_an_issue_of_which_base_price_is_settled_with_a_todays_single_price);
  for (size_t i = 0; i < 2; i++) { assert(read->rights_type_code[i] == written->rights_type_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->par_value_type_code[i] == written->par_value_type_code[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lot_sizes[i] == written->lot_sizes[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->number_of_listed_shares[i] == written->number_of_listed_shares[i]); }
  assert(read->designation == written->designation);
  assert(read->closing_price_trading_in_the_pre_opening_market == written->closing_price_trading_in_the_pre_opening_market);
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Equities Changes Of Batch Data Message: written and read back, then read and written back */
static void check_securities_equities_changes_of_batch_data_message(void) {
  SecuritiesEquitiesChangesOfBatchDataMessage sent;
  SecuritiesEquitiesChangesOfBatchDataMessage got;
  uint8_t wire[124];
  uint8_t again[124];

  any_securities_equities_changes_of_batch_data_message(&sent);
  assert(encode_securities_equities_changes_of_batch_data_message(&sent, wire, 0) == 124);
  assert(decode_securities_equities_changes_of_batch_data_message(&got, wire, 0) == 124);
  equal_securities_equities_changes_of_batch_data_message(&got, &sent);

  for (size_t i = 0; i < 124; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_equities_changes_of_batch_data_message(&got, wire, 0) == 124);
  assert(encode_securities_equities_changes_of_batch_data_message(&got, again, 0) == 124);
  for (size_t i = 0; i < 124; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Group Order Acceptance Halt Message: 28 bytes ---------------- */

/* Group Order Acceptance Halt/Release. Matching engine group-order halt and release events. */
typedef struct {
  uint8_t market_id[3];                    /* bytes 0 to 2 */
  uint8_t me_group_number[5];              /* bytes 3 to 7 */
  uint8_t board_id[2];                     /* bytes 8 to 9 */
  uint8_t board_event_id[3];               /* bytes 10 to 12 */
  uint8_t board_event_group_code[5];       /* bytes 13 to 17 */
  uint8_t board_event_processing_time[9];  /* bytes 18 to 26 */
  uint8_t end_keyword;                     /* byte 27 */
} SecuritiesGroupOrderAcceptanceHaltMessage;

/* any Securities Group Order Acceptance Halt Message at all: every byte one the checker chooses */
static void any_securities_group_order_acceptance_halt_message(SecuritiesGroupOrderAcceptanceHaltMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->me_group_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->board_event_processing_time[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Group Order Acceptance Halt Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_securities_group_order_acceptance_halt_message(const SecuritiesGroupOrderAcceptanceHaltMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->me_group_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->board_event_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->board_event_group_code[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->board_event_processing_time[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Group Order Acceptance Halt Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_securities_group_order_acceptance_halt_message(SecuritiesGroupOrderAcceptanceHaltMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->me_group_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->board_event_processing_time[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Group Order Acceptance Halt Message is what was written, byte for byte */
static void equal_securities_group_order_acceptance_halt_message(const SecuritiesGroupOrderAcceptanceHaltMessage *read, const SecuritiesGroupOrderAcceptanceHaltMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->me_group_number[i] == written->me_group_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->board_event_id[i] == written->board_event_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->board_event_group_code[i] == written->board_event_group_code[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->board_event_processing_time[i] == written->board_event_processing_time[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Group Order Acceptance Halt Message: written and read back, then read and written back */
static void check_securities_group_order_acceptance_halt_message(void) {
  SecuritiesGroupOrderAcceptanceHaltMessage sent;
  SecuritiesGroupOrderAcceptanceHaltMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_securities_group_order_acceptance_halt_message(&sent);
  assert(encode_securities_group_order_acceptance_halt_message(&sent, wire, 0) == 28);
  assert(decode_securities_group_order_acceptance_halt_message(&got, wire, 0) == 28);
  equal_securities_group_order_acceptance_halt_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_group_order_acceptance_halt_message(&got, wire, 0) == 28);
  assert(encode_securities_group_order_acceptance_halt_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Equities Batch Data Message: 627 bytes ----------------------- */

/* Equities Batch Data. Comprehensive per-issue reference data dumped at start-of-day for KOSPI/KOSDAQ/KONEX equities. */
typedef struct {
  uint8_t message_sequence_number[8];                                          /* bytes 0 to 7 */
  uint8_t total_number_of_instruments_of_the_contract[6];                      /* bytes 8 to 13 */
  uint8_t business_date[8];                                                    /* bytes 14 to 21 */
  uint8_t isin_code[12];                                                       /* bytes 22 to 33 */
  uint8_t a_designated_number_for_an_issue[6];                                 /* bytes 34 to 39 */
  uint8_t abbreviated_issue_code[9];                                           /* bytes 40 to 48 */
  uint8_t abbreviated_issue_name[40];                                          /* bytes 49 to 88 */
  uint8_t abbreviated_issue_name_in_en[40];                                    /* bytes 89 to 128 */
  uint8_t group_number[5];                                                     /* bytes 129 to 133 */
  uint8_t market_operation_product_id[3];                                      /* bytes 134 to 136 */
  uint8_t security_group_id[2];                                                /* bytes 137 to 138 */
  uint8_t discrete_time_trading;                                               /* byte 139 */
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
  uint8_t yesterdays_closing_price_type_code;                                  /* byte 181 */
  uint8_t yesterdays_closing_price[11];                                        /* bytes 182 to 192 */
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
  uint8_t credit_order_possibillity;                                           /* byte 374 */
  uint8_t limit_order_permission_type_code[5];                                 /* bytes 375 to 379 */
  uint8_t market_price_order_permission_type_code[5];                          /* bytes 380 to 384 */
  uint8_t conditioned_order_permission_type_code[5];                           /* bytes 385 to 389 */
  uint8_t best_favorable_order_permission_type_code[5];                        /* bytes 390 to 394 */
  uint8_t first_best_order_permission_type_code[5];                            /* bytes 395 to 399 */
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
  uint8_t pre_market_possibility;                                              /* byte 625 */
  uint8_t end_keyword;                                                         /* byte 626 */
} SecuritiesEquitiesBatchDataMessage;

/* any Securities Equities Batch Data Message at all: every byte one the checker chooses */
static void any_securities_equities_batch_data_message(SecuritiesEquitiesBatchDataMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_instruments_of_the_contract[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->abbreviated_issue_code[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name_in_en[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->group_number[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_group_id[i] = arbitrary(); }
  record->discrete_time_trading = arbitrary();
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
  record->yesterdays_closing_price_type_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->yesterdays_closing_price[i] = arbitrary(); }
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
  record->credit_order_possibillity = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->limit_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->market_price_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->conditioned_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->best_favorable_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->first_best_order_permission_type_code[i] = arbitrary(); }
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
  record->pre_market_possibility = arbitrary();
  record->end_keyword = arbitrary();
}

/* Securities Equities Batch Data Message to the wire: 627 bytes from at, returning where the next byte goes */
static size_t encode_securities_equities_batch_data_message(const SecuritiesEquitiesBatchDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_number_of_instruments_of_the_contract[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->abbreviated_issue_code[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name_in_en[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->group_number[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_operation_product_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_group_id[i]; }
  wire[at++] = record->discrete_time_trading;
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
  wire[at++] = record->yesterdays_closing_price_type_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->yesterdays_closing_price[i]; }
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
  wire[at++] = record->credit_order_possibillity;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->limit_order_permission_type_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->market_price_order_permission_type_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->conditioned_order_permission_type_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->best_favorable_order_permission_type_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->first_best_order_permission_type_code[i]; }
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
  wire[at++] = record->pre_market_possibility;
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Equities Batch Data Message off the wire: 627 bytes from at, returning where the next byte lies */
static size_t decode_securities_equities_batch_data_message(SecuritiesEquitiesBatchDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_instruments_of_the_contract[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->abbreviated_issue_code[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name_in_en[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->group_number[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_group_id[i] = wire[at++]; }
  record->discrete_time_trading = wire[at++];
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
  record->yesterdays_closing_price_type_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->yesterdays_closing_price[i] = wire[at++]; }
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
  record->credit_order_possibillity = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->limit_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->market_price_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->conditioned_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->best_favorable_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->first_best_order_permission_type_code[i] = wire[at++]; }
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
  record->pre_market_possibility = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Equities Batch Data Message is what was written, byte for byte */
static void equal_securities_equities_batch_data_message(const SecuritiesEquitiesBatchDataMessage *read, const SecuritiesEquitiesBatchDataMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_number_of_instruments_of_the_contract[i] == written->total_number_of_instruments_of_the_contract[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->abbreviated_issue_code[i] == written->abbreviated_issue_code[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name[i] == written->abbreviated_issue_name[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name_in_en[i] == written->abbreviated_issue_name_in_en[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->group_number[i] == written->group_number[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->market_operation_product_id[i] == written->market_operation_product_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_group_id[i] == written->security_group_id[i]); }
  assert(read->discrete_time_trading == written->discrete_time_trading);
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
  assert(read->yesterdays_closing_price_type_code == written->yesterdays_closing_price_type_code);
  for (size_t i = 0; i < 11; i++) { assert(read->yesterdays_closing_price[i] == written->yesterdays_closing_price[i]); }
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
  assert(read->credit_order_possibillity == written->credit_order_possibillity);
  for (size_t i = 0; i < 5; i++) { assert(read->limit_order_permission_type_code[i] == written->limit_order_permission_type_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->market_price_order_permission_type_code[i] == written->market_price_order_permission_type_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->conditioned_order_permission_type_code[i] == written->conditioned_order_permission_type_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->best_favorable_order_permission_type_code[i] == written->best_favorable_order_permission_type_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->first_best_order_permission_type_code[i] == written->first_best_order_permission_type_code[i]); }
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
  assert(read->pre_market_possibility == written->pre_market_possibility);
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Equities Batch Data Message: written and read back, then read and written back */
static void check_securities_equities_batch_data_message(void) {
  SecuritiesEquitiesBatchDataMessage sent;
  SecuritiesEquitiesBatchDataMessage got;
  uint8_t wire[627];
  uint8_t again[627];

  any_securities_equities_batch_data_message(&sent);
  assert(encode_securities_equities_batch_data_message(&sent, wire, 0) == 627);
  assert(decode_securities_equities_batch_data_message(&got, wire, 0) == 627);
  equal_securities_equities_batch_data_message(&got, &sent);

  for (size_t i = 0; i < 627; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_equities_batch_data_message(&got, wire, 0) == 627);
  assert(encode_securities_equities_batch_data_message(&got, again, 0) == 627);
  for (size_t i = 0; i < 627; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Closing Date Message: 25 bytes ------------------------------- */

/* Closing Date reference. Per-issue closing date assignments. */
typedef struct {
  uint8_t message_sequence_number[8];  /* bytes 0 to 7 */
  uint8_t isin_code[12];               /* bytes 8 to 19 */
  uint8_t closing_date[4];             /* bytes 20 to 23 */
  uint8_t end_keyword;                 /* byte 24 */
} SecuritiesClosingDateMessage;

/* any Securities Closing Date Message at all: every byte one the checker chooses */
static void any_securities_closing_date_message(SecuritiesClosingDateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->closing_date[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Closing Date Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_securities_closing_date_message(const SecuritiesClosingDateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_date[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Closing Date Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_securities_closing_date_message(SecuritiesClosingDateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->closing_date[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Closing Date Message is what was written, byte for byte */
static void equal_securities_closing_date_message(const SecuritiesClosingDateMessage *read, const SecuritiesClosingDateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->closing_date[i] == written->closing_date[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Closing Date Message: written and read back, then read and written back */
static void check_securities_closing_date_message(void) {
  SecuritiesClosingDateMessage sent;
  SecuritiesClosingDateMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_securities_closing_date_message(&sent);
  assert(encode_securities_closing_date_message(&sent, wire, 0) == 25);
  assert(decode_securities_closing_date_message(&got, wire, 0) == 25);
  equal_securities_closing_date_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_closing_date_message(&got, wire, 0) == 25);
  assert(encode_securities_closing_date_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Mm Lp Information Message: 195 bytes ------------------------- */

/* MM/LP Information. Market maker and liquidity provider assignments per issue. */
typedef struct {
  uint8_t message_sequence_number[8];                        /* bytes 0 to 7 */
  uint8_t isin_code[12];                                     /* bytes 8 to 19 */
  uint8_t market_participant_number[5];                      /* bytes 20 to 24 */
  uint8_t board_id[2];                                       /* bytes 25 to 26 */
  uint8_t market_making_liquidity_provider_type_code;        /* byte 27 */
  uint8_t lp_start_date[8];                                  /* bytes 28 to 35 */
  uint8_t lp_end_date[8];                                    /* bytes 36 to 43 */
  uint8_t minimum_order_volume[11];                          /* bytes 44 to 54 */
  uint8_t maximum_volume_of_multiple_order[11];              /* bytes 55 to 65 */
  uint8_t bid_ask_spread_unit_code;                          /* byte 66 */
  uint8_t upper_limit_of_bid_ask_spread[22];                 /* bytes 67 to 88 */
  uint8_t spread_multiple_for_market_holidays[11];           /* bytes 89 to 99 */
  uint8_t an_obligatory_time_interval_to_place_an_order[6];  /* bytes 100 to 105 */
  uint8_t minimum_ask_price[22];                             /* bytes 106 to 127 */
  uint8_t maximum_bid_price[22];                             /* bytes 128 to 149 */
  uint8_t minimum_order_price[22];                           /* bytes 150 to 171 */
  uint8_t maximum_order_price[22];                           /* bytes 172 to 193 */
  uint8_t end_keyword;                                       /* byte 194 */
} SecuritiesMmLpInformationMessage;

/* any Securities Mm Lp Information Message at all: every byte one the checker chooses */
static void any_securities_mm_lp_information_message(SecuritiesMmLpInformationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->market_participant_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  record->market_making_liquidity_provider_type_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->lp_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lp_end_date[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->minimum_order_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->maximum_volume_of_multiple_order[i] = arbitrary(); }
  record->bid_ask_spread_unit_code = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->upper_limit_of_bid_ask_spread[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->spread_multiple_for_market_holidays[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->an_obligatory_time_interval_to_place_an_order[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->minimum_ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->maximum_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->minimum_order_price[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->maximum_order_price[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Mm Lp Information Message to the wire: 195 bytes from at, returning where the next byte goes */
static size_t encode_securities_mm_lp_information_message(const SecuritiesMmLpInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->market_participant_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  wire[at++] = record->market_making_liquidity_provider_type_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_start_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lp_end_date[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->minimum_order_volume[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->maximum_volume_of_multiple_order[i]; }
  wire[at++] = record->bid_ask_spread_unit_code;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->upper_limit_of_bid_ask_spread[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->spread_multiple_for_market_holidays[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->an_obligatory_time_interval_to_place_an_order[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->minimum_ask_price[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->maximum_bid_price[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->minimum_order_price[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->maximum_order_price[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Mm Lp Information Message off the wire: 195 bytes from at, returning where the next byte lies */
static size_t decode_securities_mm_lp_information_message(SecuritiesMmLpInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->market_participant_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  record->market_making_liquidity_provider_type_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->lp_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lp_end_date[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->minimum_order_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->maximum_volume_of_multiple_order[i] = wire[at++]; }
  record->bid_ask_spread_unit_code = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->upper_limit_of_bid_ask_spread[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->spread_multiple_for_market_holidays[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->an_obligatory_time_interval_to_place_an_order[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->minimum_ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->maximum_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->minimum_order_price[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->maximum_order_price[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Mm Lp Information Message is what was written, byte for byte */
static void equal_securities_mm_lp_information_message(const SecuritiesMmLpInformationMessage *read, const SecuritiesMmLpInformationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->market_participant_number[i] == written->market_participant_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  assert(read->market_making_liquidity_provider_type_code == written->market_making_liquidity_provider_type_code);
  for (size_t i = 0; i < 8; i++) { assert(read->lp_start_date[i] == written->lp_start_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lp_end_date[i] == written->lp_end_date[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->minimum_order_volume[i] == written->minimum_order_volume[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->maximum_volume_of_multiple_order[i] == written->maximum_volume_of_multiple_order[i]); }
  assert(read->bid_ask_spread_unit_code == written->bid_ask_spread_unit_code);
  for (size_t i = 0; i < 22; i++) { assert(read->upper_limit_of_bid_ask_spread[i] == written->upper_limit_of_bid_ask_spread[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->spread_multiple_for_market_holidays[i] == written->spread_multiple_for_market_holidays[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->an_obligatory_time_interval_to_place_an_order[i] == written->an_obligatory_time_interval_to_place_an_order[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->minimum_ask_price[i] == written->minimum_ask_price[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->maximum_bid_price[i] == written->maximum_bid_price[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->minimum_order_price[i] == written->minimum_order_price[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->maximum_order_price[i] == written->maximum_order_price[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Mm Lp Information Message: written and read back, then read and written back */
static void check_securities_mm_lp_information_message(void) {
  SecuritiesMmLpInformationMessage sent;
  SecuritiesMmLpInformationMessage got;
  uint8_t wire[195];
  uint8_t again[195];

  any_securities_mm_lp_information_message(&sent);
  assert(encode_securities_mm_lp_information_message(&sent, wire, 0) == 195);
  assert(decode_securities_mm_lp_information_message(&got, wire, 0) == 195);
  equal_securities_mm_lp_information_message(&got, &sent);

  for (size_t i = 0; i < 195; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_mm_lp_information_message(&got, wire, 0) == 195);
  assert(encode_securities_mm_lp_information_message(&got, again, 0) == 195);
  for (size_t i = 0; i < 195; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Member Information Message: 202 bytes ------------------------ */

/* Member firm information reference data (IFMSBTD0012) — Securities C STK variant. */
typedef struct {
  uint8_t message_sequence_number[8];                             /* bytes 0 to 7 */
  uint8_t business_date[8];                                       /* bytes 8 to 15 */
  uint8_t market_participant_number[5];                           /* bytes 16 to 20 */
  uint8_t name_of_a_market_participant_in_kr[80];                 /* bytes 21 to 100 */
  uint8_t name_of_a_market_participant_in_en[80];                 /* bytes 101 to 180 */
  uint8_t an_abbreviated_name_of_a_market_participant_in_kr[20];  /* bytes 181 to 200 */
  uint8_t end_keyword;                                            /* byte 201 */
} SecuritiesMemberInformationMessage;

/* any Securities Member Information Message at all: every byte one the checker chooses */
static void any_securities_member_information_message(SecuritiesMemberInformationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->market_participant_number[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->name_of_a_market_participant_in_kr[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->name_of_a_market_participant_in_en[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->an_abbreviated_name_of_a_market_participant_in_kr[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Member Information Message to the wire: 202 bytes from at, returning where the next byte goes */
static size_t encode_securities_member_information_message(const SecuritiesMemberInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->market_participant_number[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->name_of_a_market_participant_in_kr[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->name_of_a_market_participant_in_en[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->an_abbreviated_name_of_a_market_participant_in_kr[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Member Information Message off the wire: 202 bytes from at, returning where the next byte lies */
static size_t decode_securities_member_information_message(SecuritiesMemberInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->market_participant_number[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->name_of_a_market_participant_in_kr[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->name_of_a_market_participant_in_en[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->an_abbreviated_name_of_a_market_participant_in_kr[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Member Information Message is what was written, byte for byte */
static void equal_securities_member_information_message(const SecuritiesMemberInformationMessage *read, const SecuritiesMemberInformationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->market_participant_number[i] == written->market_participant_number[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->name_of_a_market_participant_in_kr[i] == written->name_of_a_market_participant_in_kr[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->name_of_a_market_participant_in_en[i] == written->name_of_a_market_participant_in_en[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->an_abbreviated_name_of_a_market_participant_in_kr[i] == written->an_abbreviated_name_of_a_market_participant_in_kr[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Member Information Message: written and read back, then read and written back */
static void check_securities_member_information_message(void) {
  SecuritiesMemberInformationMessage sent;
  SecuritiesMemberInformationMessage got;
  uint8_t wire[202];
  uint8_t again[202];

  any_securities_member_information_message(&sent);
  assert(encode_securities_member_information_message(&sent, wire, 0) == 202);
  assert(decode_securities_member_information_message(&got, wire, 0) == 202);
  equal_securities_member_information_message(&got, &sent);

  for (size_t i = 0; i < 202; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_member_information_message(&got, wire, 0) == 202);
  assert(encode_securities_member_information_message(&got, again, 0) == 202);
  for (size_t i = 0; i < 202; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Treasury Stocks Batch Message: 130 bytes --------------------- */

/* Treasury Stocks Batch reference data. */
typedef struct {
  uint8_t message_sequence_number[8];                            /* bytes 0 to 7 */
  uint8_t isin_code[12];                                         /* bytes 8 to 19 */
  uint8_t treasury_stock_report_id[5];                           /* bytes 20 to 24 */
  uint8_t treasury_stock_ask_bid_type_code;                      /* byte 25 */
  uint8_t treasury_stock_application_date[8];                    /* bytes 26 to 33 */
  uint8_t treasury_stock_trading_start_date[8];                  /* bytes 34 to 41 */
  uint8_t treasury_stock_trading_end_date[8];                    /* bytes 42 to 49 */
  uint8_t trearsury_stock_trading_method_type_code;              /* byte 50 */
  uint8_t market_participant_number[5];                          /* bytes 51 to 55 */
  uint8_t buying_volume_open_single_price_session[12];           /* bytes 56 to 67 */
  uint8_t buying_volume_regular_session[12];                     /* bytes 68 to 79 */
  uint8_t buying_volume_block_trading_in_off_hours_session[12];  /* bytes 80 to 91 */
  uint8_t accumulated_trading_quantity[15];                      /* bytes 92 to 106 */
  uint8_t accumulated_trading_value[22];                         /* bytes 107 to 128 */
  uint8_t end_keyword;                                           /* byte 129 */
} SecuritiesTreasuryStocksBatchMessage;

/* any Securities Treasury Stocks Batch Message at all: every byte one the checker chooses */
static void any_securities_treasury_stocks_batch_message(SecuritiesTreasuryStocksBatchMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->treasury_stock_report_id[i] = arbitrary(); }
  record->treasury_stock_ask_bid_type_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->treasury_stock_application_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->treasury_stock_trading_start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->treasury_stock_trading_end_date[i] = arbitrary(); }
  record->trearsury_stock_trading_method_type_code = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->market_participant_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->buying_volume_open_single_price_session[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->buying_volume_regular_session[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->buying_volume_block_trading_in_off_hours_session[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->accumulated_trading_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Treasury Stocks Batch Message to the wire: 130 bytes from at, returning where the next byte goes */
static size_t encode_securities_treasury_stocks_batch_message(const SecuritiesTreasuryStocksBatchMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->treasury_stock_report_id[i]; }
  wire[at++] = record->treasury_stock_ask_bid_type_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->treasury_stock_application_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->treasury_stock_trading_start_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->treasury_stock_trading_end_date[i]; }
  wire[at++] = record->trearsury_stock_trading_method_type_code;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->market_participant_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->buying_volume_open_single_price_session[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->buying_volume_regular_session[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->buying_volume_block_trading_in_off_hours_session[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->accumulated_trading_quantity[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Treasury Stocks Batch Message off the wire: 130 bytes from at, returning where the next byte lies */
static size_t decode_securities_treasury_stocks_batch_message(SecuritiesTreasuryStocksBatchMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->treasury_stock_report_id[i] = wire[at++]; }
  record->treasury_stock_ask_bid_type_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->treasury_stock_application_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->treasury_stock_trading_start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->treasury_stock_trading_end_date[i] = wire[at++]; }
  record->trearsury_stock_trading_method_type_code = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->market_participant_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->buying_volume_open_single_price_session[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->buying_volume_regular_session[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->buying_volume_block_trading_in_off_hours_session[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->accumulated_trading_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Treasury Stocks Batch Message is what was written, byte for byte */
static void equal_securities_treasury_stocks_batch_message(const SecuritiesTreasuryStocksBatchMessage *read, const SecuritiesTreasuryStocksBatchMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->treasury_stock_report_id[i] == written->treasury_stock_report_id[i]); }
  assert(read->treasury_stock_ask_bid_type_code == written->treasury_stock_ask_bid_type_code);
  for (size_t i = 0; i < 8; i++) { assert(read->treasury_stock_application_date[i] == written->treasury_stock_application_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->treasury_stock_trading_start_date[i] == written->treasury_stock_trading_start_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->treasury_stock_trading_end_date[i] == written->treasury_stock_trading_end_date[i]); }
  assert(read->trearsury_stock_trading_method_type_code == written->trearsury_stock_trading_method_type_code);
  for (size_t i = 0; i < 5; i++) { assert(read->market_participant_number[i] == written->market_participant_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->buying_volume_open_single_price_session[i] == written->buying_volume_open_single_price_session[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->buying_volume_regular_session[i] == written->buying_volume_regular_session[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->buying_volume_block_trading_in_off_hours_session[i] == written->buying_volume_block_trading_in_off_hours_session[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->accumulated_trading_quantity[i] == written->accumulated_trading_quantity[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value[i] == written->accumulated_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Treasury Stocks Batch Message: written and read back, then read and written back */
static void check_securities_treasury_stocks_batch_message(void) {
  SecuritiesTreasuryStocksBatchMessage sent;
  SecuritiesTreasuryStocksBatchMessage got;
  uint8_t wire[130];
  uint8_t again[130];

  any_securities_treasury_stocks_batch_message(&sent);
  assert(encode_securities_treasury_stocks_batch_message(&sent, wire, 0) == 130);
  assert(decode_securities_treasury_stocks_batch_message(&got, wire, 0) == 130);
  equal_securities_treasury_stocks_batch_message(&got, &sent);

  for (size_t i = 0; i < 130; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_treasury_stocks_batch_message(&got, wire, 0) == 130);
  assert(encode_securities_treasury_stocks_batch_message(&got, again, 0) == 130);
  for (size_t i = 0; i < 130; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Equity Index Indicator Message: 180 bytes -------------------- */

/* Equity Index Indicator. Real-time index value indicators for equity-derivatives underlying. */
typedef struct {
  uint8_t message_sequence_number[8];           /* bytes 0 to 7 */
  uint8_t isin_code[12];                        /* bytes 8 to 19 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 20 to 25 */
  uint8_t security_group_id[2];                 /* bytes 26 to 27 */
  uint8_t eps_calculation;                      /* byte 28 */
  uint8_t eps[22];                              /* bytes 29 to 50 */
  uint8_t loss_category;                        /* byte 51 */
  uint8_t per[13];                              /* bytes 52 to 64 */
  uint8_t bps_calculation;                      /* byte 65 */
  uint8_t bps[22];                              /* bytes 66 to 87 */
  uint8_t pbr[13];                              /* bytes 88 to 100 */
  uint8_t dps_calculation;                      /* byte 101 */
  uint8_t dps[22];                              /* bytes 102 to 123 */
  uint8_t dividend_yield[13];                   /* bytes 124 to 136 */
  uint8_t market_capitalization_type_code;      /* byte 137 */
  uint8_t filler_1;                             /* byte 138 */
  uint8_t index_classification_level_1[6];      /* bytes 139 to 144 */
  uint8_t index_classification_level_2[6];      /* bytes 145 to 150 */
  uint8_t index_classification_level_3[6];      /* bytes 151 to 156 */
  uint8_t kospi_200_sector_code_1;              /* byte 157 */
  uint8_t kospi_200_sector_code_2;              /* byte 158 */
  uint8_t kospi;                                /* byte 159 */
  uint8_t kosdaq;                               /* byte 160 */
  uint8_t kospi_100;                            /* byte 161 */
  uint8_t kospi_50;                             /* byte 162 */
  uint8_t kosdaq_150;                           /* byte 163 */
  uint8_t krx_100;                              /* byte 164 */
  uint8_t krx_300;                              /* byte 165 */
  uint8_t kospi_200_high_dividend_yield_index;  /* byte 166 */
  uint8_t krx_bbig_index;                       /* byte 167 */
  uint8_t krx_secondary_battery_top_10_index;   /* byte 168 */
  uint8_t krx_bio_top_10_index;                 /* byte 169 */
  uint8_t korea_value_up_index;                 /* byte 170 */
  uint8_t filler_8[8];                          /* bytes 171 to 178 */
  uint8_t end_keyword;                          /* byte 179 */
} SecuritiesEquityIndexIndicatorMessage;

/* any Securities Equity Index Indicator Message at all: every byte one the checker chooses */
static void any_securities_equity_index_indicator_message(SecuritiesEquityIndexIndicatorMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_group_id[i] = arbitrary(); }
  record->eps_calculation = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->eps[i] = arbitrary(); }
  record->loss_category = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->per[i] = arbitrary(); }
  record->bps_calculation = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->bps[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->pbr[i] = arbitrary(); }
  record->dps_calculation = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->dps[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->dividend_yield[i] = arbitrary(); }
  record->market_capitalization_type_code = arbitrary();
  record->filler_1 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->index_classification_level_1[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_classification_level_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_classification_level_3[i] = arbitrary(); }
  record->kospi_200_sector_code_1 = arbitrary();
  record->kospi_200_sector_code_2 = arbitrary();
  record->kospi = arbitrary();
  record->kosdaq = arbitrary();
  record->kospi_100 = arbitrary();
  record->kospi_50 = arbitrary();
  record->kosdaq_150 = arbitrary();
  record->krx_100 = arbitrary();
  record->krx_300 = arbitrary();
  record->kospi_200_high_dividend_yield_index = arbitrary();
  record->krx_bbig_index = arbitrary();
  record->krx_secondary_battery_top_10_index = arbitrary();
  record->krx_bio_top_10_index = arbitrary();
  record->korea_value_up_index = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->filler_8[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Equity Index Indicator Message to the wire: 180 bytes from at, returning where the next byte goes */
static size_t encode_securities_equity_index_indicator_message(const SecuritiesEquityIndexIndicatorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_group_id[i]; }
  wire[at++] = record->eps_calculation;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->eps[i]; }
  wire[at++] = record->loss_category;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->per[i]; }
  wire[at++] = record->bps_calculation;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->bps[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->pbr[i]; }
  wire[at++] = record->dps_calculation;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->dps[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->dividend_yield[i]; }
  wire[at++] = record->market_capitalization_type_code;
  wire[at++] = record->filler_1;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_classification_level_1[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_classification_level_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_classification_level_3[i]; }
  wire[at++] = record->kospi_200_sector_code_1;
  wire[at++] = record->kospi_200_sector_code_2;
  wire[at++] = record->kospi;
  wire[at++] = record->kosdaq;
  wire[at++] = record->kospi_100;
  wire[at++] = record->kospi_50;
  wire[at++] = record->kosdaq_150;
  wire[at++] = record->krx_100;
  wire[at++] = record->krx_300;
  wire[at++] = record->kospi_200_high_dividend_yield_index;
  wire[at++] = record->krx_bbig_index;
  wire[at++] = record->krx_secondary_battery_top_10_index;
  wire[at++] = record->krx_bio_top_10_index;
  wire[at++] = record->korea_value_up_index;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->filler_8[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Equity Index Indicator Message off the wire: 180 bytes from at, returning where the next byte lies */
static size_t decode_securities_equity_index_indicator_message(SecuritiesEquityIndexIndicatorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_group_id[i] = wire[at++]; }
  record->eps_calculation = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->eps[i] = wire[at++]; }
  record->loss_category = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->per[i] = wire[at++]; }
  record->bps_calculation = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->bps[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->pbr[i] = wire[at++]; }
  record->dps_calculation = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->dps[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->dividend_yield[i] = wire[at++]; }
  record->market_capitalization_type_code = wire[at++];
  record->filler_1 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->index_classification_level_1[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_classification_level_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_classification_level_3[i] = wire[at++]; }
  record->kospi_200_sector_code_1 = wire[at++];
  record->kospi_200_sector_code_2 = wire[at++];
  record->kospi = wire[at++];
  record->kosdaq = wire[at++];
  record->kospi_100 = wire[at++];
  record->kospi_50 = wire[at++];
  record->kosdaq_150 = wire[at++];
  record->krx_100 = wire[at++];
  record->krx_300 = wire[at++];
  record->kospi_200_high_dividend_yield_index = wire[at++];
  record->krx_bbig_index = wire[at++];
  record->krx_secondary_battery_top_10_index = wire[at++];
  record->krx_bio_top_10_index = wire[at++];
  record->korea_value_up_index = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->filler_8[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Equity Index Indicator Message is what was written, byte for byte */
static void equal_securities_equity_index_indicator_message(const SecuritiesEquityIndexIndicatorMessage *read, const SecuritiesEquityIndexIndicatorMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_group_id[i] == written->security_group_id[i]); }
  assert(read->eps_calculation == written->eps_calculation);
  for (size_t i = 0; i < 22; i++) { assert(read->eps[i] == written->eps[i]); }
  assert(read->loss_category == written->loss_category);
  for (size_t i = 0; i < 13; i++) { assert(read->per[i] == written->per[i]); }
  assert(read->bps_calculation == written->bps_calculation);
  for (size_t i = 0; i < 22; i++) { assert(read->bps[i] == written->bps[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->pbr[i] == written->pbr[i]); }
  assert(read->dps_calculation == written->dps_calculation);
  for (size_t i = 0; i < 22; i++) { assert(read->dps[i] == written->dps[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->dividend_yield[i] == written->dividend_yield[i]); }
  assert(read->market_capitalization_type_code == written->market_capitalization_type_code);
  assert(read->filler_1 == written->filler_1);
  for (size_t i = 0; i < 6; i++) { assert(read->index_classification_level_1[i] == written->index_classification_level_1[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_classification_level_2[i] == written->index_classification_level_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_classification_level_3[i] == written->index_classification_level_3[i]); }
  assert(read->kospi_200_sector_code_1 == written->kospi_200_sector_code_1);
  assert(read->kospi_200_sector_code_2 == written->kospi_200_sector_code_2);
  assert(read->kospi == written->kospi);
  assert(read->kosdaq == written->kosdaq);
  assert(read->kospi_100 == written->kospi_100);
  assert(read->kospi_50 == written->kospi_50);
  assert(read->kosdaq_150 == written->kosdaq_150);
  assert(read->krx_100 == written->krx_100);
  assert(read->krx_300 == written->krx_300);
  assert(read->kospi_200_high_dividend_yield_index == written->kospi_200_high_dividend_yield_index);
  assert(read->krx_bbig_index == written->krx_bbig_index);
  assert(read->krx_secondary_battery_top_10_index == written->krx_secondary_battery_top_10_index);
  assert(read->krx_bio_top_10_index == written->krx_bio_top_10_index);
  assert(read->korea_value_up_index == written->korea_value_up_index);
  for (size_t i = 0; i < 8; i++) { assert(read->filler_8[i] == written->filler_8[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Equity Index Indicator Message: written and read back, then read and written back */
static void check_securities_equity_index_indicator_message(void) {
  SecuritiesEquityIndexIndicatorMessage sent;
  SecuritiesEquityIndexIndicatorMessage got;
  uint8_t wire[180];
  uint8_t again[180];

  any_securities_equity_index_indicator_message(&sent);
  assert(encode_securities_equity_index_indicator_message(&sent, wire, 0) == 180);
  assert(decode_securities_equity_index_indicator_message(&got, wire, 0) == 180);
  equal_securities_equity_index_indicator_message(&got, &sent);

  for (size_t i = 0; i < 180; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_equity_index_indicator_message(&got, wire, 0) == 180);
  assert(encode_securities_equity_index_indicator_message(&got, again, 0) == 180);
  for (size_t i = 0; i < 180; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Dividend Yield Per Industry Message: 31 bytes ---------------- */

/* Dividend Yield per Industry reference (IFMSBTD0003) — KOSPI variant. */
typedef struct {
  uint8_t message_sequence_number[8];  /* bytes 0 to 7 */
  uint8_t index_id[6];                 /* bytes 8 to 13 */
  uint8_t dividend_yield[13];          /* bytes 14 to 26 */
  uint8_t filler_3[3];                 /* bytes 27 to 29 */
  uint8_t end_keyword;                 /* byte 30 */
} SecuritiesDividendYieldPerIndustryMessage;

/* any Securities Dividend Yield Per Industry Message at all: every byte one the checker chooses */
static void any_securities_dividend_yield_per_industry_message(SecuritiesDividendYieldPerIndustryMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->dividend_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Dividend Yield Per Industry Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_securities_dividend_yield_per_industry_message(const SecuritiesDividendYieldPerIndustryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->dividend_yield[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_3[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Dividend Yield Per Industry Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_securities_dividend_yield_per_industry_message(SecuritiesDividendYieldPerIndustryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->dividend_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->filler_3[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Dividend Yield Per Industry Message is what was written, byte for byte */
static void equal_securities_dividend_yield_per_industry_message(const SecuritiesDividendYieldPerIndustryMessage *read, const SecuritiesDividendYieldPerIndustryMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->dividend_yield[i] == written->dividend_yield[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->filler_3[i] == written->filler_3[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Dividend Yield Per Industry Message: written and read back, then read and written back */
static void check_securities_dividend_yield_per_industry_message(void) {
  SecuritiesDividendYieldPerIndustryMessage sent;
  SecuritiesDividendYieldPerIndustryMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_securities_dividend_yield_per_industry_message(&sent);
  assert(encode_securities_dividend_yield_per_industry_message(&sent, wire, 0) == 31);
  assert(decode_securities_dividend_yield_per_industry_message(&got, wire, 0) == 31);
  equal_securities_dividend_yield_per_industry_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_dividend_yield_per_industry_message(&got, wire, 0) == 31);
  assert(encode_securities_dividend_yield_per_industry_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
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

/* ---- Securities Elw Batch Data Message: 925 bytes ---------------------------- */

/* ELW Batch Data. Per-issue reference data for Equity Linked Warrants. */
typedef struct {
  uint8_t message_sequence_number[8];                               /* bytes 0 to 7 */
  uint8_t isin_code[12];                                            /* bytes 8 to 19 */
  uint8_t a_designated_number_for_an_issue[6];                      /* bytes 20 to 25 */
  uint8_t name_of_issuer[80];                                       /* bytes 26 to 105 */
  uint8_t english_name_of_issuer[80];                               /* bytes 106 to 185 */
  uint8_t numbers_of_issuer[5];                                     /* bytes 186 to 190 */
  uint8_t market_id_1_for_underlying_assets_indices[3];             /* bytes 191 to 193 */
  uint8_t market_id_2_for_underlying_assets_indices[3];             /* bytes 194 to 196 */
  uint8_t market_id_3_for_underlying_assets_indices[3];             /* bytes 197 to 199 */
  uint8_t market_id_4_for_underlying_assets_indices[3];             /* bytes 200 to 202 */
  uint8_t market_id_5_for_underlying_assets_indices[3];             /* bytes 203 to 205 */
  uint8_t underlying_asset_type_code_1[12];                         /* bytes 206 to 217 */
  uint8_t underlying_asset_type_code_2[12];                         /* bytes 218 to 229 */
  uint8_t underlying_asset_type_code_3[12];                         /* bytes 230 to 241 */
  uint8_t underlying_asset_type_code_4[12];                         /* bytes 242 to 253 */
  uint8_t underlying_asset_type_code_5[12];                         /* bytes 254 to 265 */
  uint8_t underlying_asset_composition_ratio_1[13];                 /* bytes 266 to 278 */
  uint8_t underlying_asset_composition_ratio_2[13];                 /* bytes 279 to 291 */
  uint8_t underlying_asset_composition_ratio_3[13];                 /* bytes 292 to 304 */
  uint8_t underlying_asset_composition_ratio_4[13];                 /* bytes 305 to 317 */
  uint8_t underlying_asset_composition_ratio_5[13];                 /* bytes 318 to 330 */
  uint8_t index_id[6];                                              /* bytes 331 to 336 */
  uint8_t option_rights_type_code;                                  /* byte 337 */
  uint8_t rights_execution_type_code;                               /* byte 338 */
  uint8_t payment_methods;                                          /* byte 339 */
  uint8_t last_trading_date[8];                                     /* bytes 340 to 347 */
  uint8_t elw_payment_date[8];                                      /* bytes 348 to 355 */
  uint8_t base_price_of_underlying_asset[13];                       /* bytes 356 to 368 */
  uint8_t details_of_rights[200];                                   /* bytes 369 to 568 */
  uint8_t elw_conversion_rate[13];                                  /* bytes 569 to 581 */
  uint8_t elw_guaranteed_rate_for_price_increases[10];              /* bytes 582 to 591 */
  uint8_t elw_guaranteed_rate_for_price_decreases[10];              /* bytes 592 to 601 */
  uint8_t elw_fixed_payment[22];                                    /* bytes 602 to 623 */
  uint8_t elw_payment_agent[80];                                    /* bytes 624 to 703 */
  uint8_t calculation_methods_of_appraised_price_at_maturity[200];  /* bytes 704 to 903 */
  uint8_t elw_rights_type_code;                                     /* byte 904 */
  uint8_t elw_lp_holding_quantity[15];                              /* bytes 905 to 919 */
  uint8_t filler_4[4];                                              /* bytes 920 to 923 */
  uint8_t end_keyword;                                              /* byte 924 */
} SecuritiesElwBatchDataMessage;

/* any Securities Elw Batch Data Message at all: every byte one the checker chooses */
static void any_securities_elw_batch_data_message(SecuritiesElwBatchDataMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->name_of_issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->english_name_of_issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->numbers_of_issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->market_id_1_for_underlying_assets_indices[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->market_id_2_for_underlying_assets_indices[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->market_id_3_for_underlying_assets_indices[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->market_id_4_for_underlying_assets_indices[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->market_id_5_for_underlying_assets_indices[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_asset_type_code_1[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_asset_type_code_2[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_asset_type_code_3[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_asset_type_code_4[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_asset_type_code_5[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_asset_composition_ratio_1[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_asset_composition_ratio_2[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_asset_composition_ratio_3[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_asset_composition_ratio_4[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_asset_composition_ratio_5[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  record->option_rights_type_code = arbitrary();
  record->rights_execution_type_code = arbitrary();
  record->payment_methods = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->elw_payment_date[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->base_price_of_underlying_asset[i] = arbitrary(); }
  for (size_t i = 0; i < 200; i++) { record->details_of_rights[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->elw_conversion_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->elw_guaranteed_rate_for_price_increases[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->elw_guaranteed_rate_for_price_decreases[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->elw_fixed_payment[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->elw_payment_agent[i] = arbitrary(); }
  for (size_t i = 0; i < 200; i++) { record->calculation_methods_of_appraised_price_at_maturity[i] = arbitrary(); }
  record->elw_rights_type_code = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->elw_lp_holding_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Elw Batch Data Message to the wire: 925 bytes from at, returning where the next byte goes */
static size_t encode_securities_elw_batch_data_message(const SecuritiesElwBatchDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->name_of_issuer[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->english_name_of_issuer[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->numbers_of_issuer[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_id_1_for_underlying_assets_indices[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_id_2_for_underlying_assets_indices[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_id_3_for_underlying_assets_indices[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_id_4_for_underlying_assets_indices[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_id_5_for_underlying_assets_indices[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_asset_type_code_1[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_asset_type_code_2[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_asset_type_code_3[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_asset_type_code_4[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_asset_type_code_5[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_asset_composition_ratio_1[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_asset_composition_ratio_2[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_asset_composition_ratio_3[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_asset_composition_ratio_4[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_asset_composition_ratio_5[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  wire[at++] = record->option_rights_type_code;
  wire[at++] = record->rights_execution_type_code;
  wire[at++] = record->payment_methods;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_trading_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->elw_payment_date[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->base_price_of_underlying_asset[i]; }
  for (size_t i = 0; i < 200; i++) { wire[at++] = record->details_of_rights[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->elw_conversion_rate[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->elw_guaranteed_rate_for_price_increases[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->elw_guaranteed_rate_for_price_decreases[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->elw_fixed_payment[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->elw_payment_agent[i]; }
  for (size_t i = 0; i < 200; i++) { wire[at++] = record->calculation_methods_of_appraised_price_at_maturity[i]; }
  wire[at++] = record->elw_rights_type_code;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->elw_lp_holding_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Elw Batch Data Message off the wire: 925 bytes from at, returning where the next byte lies */
static size_t decode_securities_elw_batch_data_message(SecuritiesElwBatchDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->name_of_issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->english_name_of_issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->numbers_of_issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->market_id_1_for_underlying_assets_indices[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->market_id_2_for_underlying_assets_indices[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->market_id_3_for_underlying_assets_indices[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->market_id_4_for_underlying_assets_indices[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->market_id_5_for_underlying_assets_indices[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_asset_type_code_1[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_asset_type_code_2[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_asset_type_code_3[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_asset_type_code_4[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_asset_type_code_5[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_asset_composition_ratio_1[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_asset_composition_ratio_2[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_asset_composition_ratio_3[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_asset_composition_ratio_4[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_asset_composition_ratio_5[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  record->option_rights_type_code = wire[at++];
  record->rights_execution_type_code = wire[at++];
  record->payment_methods = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->elw_payment_date[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->base_price_of_underlying_asset[i] = wire[at++]; }
  for (size_t i = 0; i < 200; i++) { record->details_of_rights[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->elw_conversion_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->elw_guaranteed_rate_for_price_increases[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->elw_guaranteed_rate_for_price_decreases[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->elw_fixed_payment[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->elw_payment_agent[i] = wire[at++]; }
  for (size_t i = 0; i < 200; i++) { record->calculation_methods_of_appraised_price_at_maturity[i] = wire[at++]; }
  record->elw_rights_type_code = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->elw_lp_holding_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Elw Batch Data Message is what was written, byte for byte */
static void equal_securities_elw_batch_data_message(const SecuritiesElwBatchDataMessage *read, const SecuritiesElwBatchDataMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->name_of_issuer[i] == written->name_of_issuer[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->english_name_of_issuer[i] == written->english_name_of_issuer[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->numbers_of_issuer[i] == written->numbers_of_issuer[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->market_id_1_for_underlying_assets_indices[i] == written->market_id_1_for_underlying_assets_indices[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->market_id_2_for_underlying_assets_indices[i] == written->market_id_2_for_underlying_assets_indices[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->market_id_3_for_underlying_assets_indices[i] == written->market_id_3_for_underlying_assets_indices[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->market_id_4_for_underlying_assets_indices[i] == written->market_id_4_for_underlying_assets_indices[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->market_id_5_for_underlying_assets_indices[i] == written->market_id_5_for_underlying_assets_indices[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_asset_type_code_1[i] == written->underlying_asset_type_code_1[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_asset_type_code_2[i] == written->underlying_asset_type_code_2[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_asset_type_code_3[i] == written->underlying_asset_type_code_3[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_asset_type_code_4[i] == written->underlying_asset_type_code_4[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_asset_type_code_5[i] == written->underlying_asset_type_code_5[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_asset_composition_ratio_1[i] == written->underlying_asset_composition_ratio_1[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_asset_composition_ratio_2[i] == written->underlying_asset_composition_ratio_2[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_asset_composition_ratio_3[i] == written->underlying_asset_composition_ratio_3[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_asset_composition_ratio_4[i] == written->underlying_asset_composition_ratio_4[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_asset_composition_ratio_5[i] == written->underlying_asset_composition_ratio_5[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  assert(read->option_rights_type_code == written->option_rights_type_code);
  assert(read->rights_execution_type_code == written->rights_execution_type_code);
  assert(read->payment_methods == written->payment_methods);
  for (size_t i = 0; i < 8; i++) { assert(read->last_trading_date[i] == written->last_trading_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->elw_payment_date[i] == written->elw_payment_date[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->base_price_of_underlying_asset[i] == written->base_price_of_underlying_asset[i]); }
  for (size_t i = 0; i < 200; i++) { assert(read->details_of_rights[i] == written->details_of_rights[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->elw_conversion_rate[i] == written->elw_conversion_rate[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->elw_guaranteed_rate_for_price_increases[i] == written->elw_guaranteed_rate_for_price_increases[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->elw_guaranteed_rate_for_price_decreases[i] == written->elw_guaranteed_rate_for_price_decreases[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->elw_fixed_payment[i] == written->elw_fixed_payment[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->elw_payment_agent[i] == written->elw_payment_agent[i]); }
  for (size_t i = 0; i < 200; i++) { assert(read->calculation_methods_of_appraised_price_at_maturity[i] == written->calculation_methods_of_appraised_price_at_maturity[i]); }
  assert(read->elw_rights_type_code == written->elw_rights_type_code);
  for (size_t i = 0; i < 15; i++) { assert(read->elw_lp_holding_quantity[i] == written->elw_lp_holding_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Elw Batch Data Message: written and read back, then read and written back */
static void check_securities_elw_batch_data_message(void) {
  SecuritiesElwBatchDataMessage sent;
  SecuritiesElwBatchDataMessage got;
  uint8_t wire[925];
  uint8_t again[925];

  any_securities_elw_batch_data_message(&sent);
  assert(encode_securities_elw_batch_data_message(&sent, wire, 0) == 925);
  assert(decode_securities_elw_batch_data_message(&got, wire, 0) == 925);
  equal_securities_elw_batch_data_message(&got, &sent);

  for (size_t i = 0; i < 925; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_elw_batch_data_message(&got, wire, 0) == 925);
  assert(encode_securities_elw_batch_data_message(&got, again, 0) == 925);
  for (size_t i = 0; i < 925; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Etn Batch Data Message: 255 bytes ---------------------------- */

/* ETN Batch Data. Per-issue reference data for Exchange Traded Notes. */
typedef struct {
  uint8_t message_sequence_number[8];                         /* bytes 0 to 7 */
  uint8_t isin_code[12];                                      /* bytes 8 to 19 */
  uint8_t a_designated_number_for_an_issue[6];                /* bytes 20 to 25 */
  uint8_t name_of_issuer[80];                                 /* bytes 26 to 105 */
  uint8_t english_name_of_issuer[80];                         /* bytes 106 to 185 */
  uint8_t numbers_of_issuer[5];                               /* bytes 186 to 190 */
  uint8_t payment_methods;                                    /* byte 191 */
  uint8_t last_trading_date[8];                               /* bytes 192 to 199 */
  uint8_t etn_payment_date[8];                                /* bytes 200 to 207 */
  uint8_t etn_lp_holding_quantity[15];                        /* bytes 208 to 222 */
  uint8_t loss_protection_etn_profit_structure_code[2];       /* bytes 223 to 224 */
  uint8_t etn_maximum_redemption_price[11];                   /* bytes 225 to 235 */
  uint8_t etn_minimum_redemption_price[11];                   /* bytes 236 to 246 */
  uint8_t etn_early_redemption_possibility;                   /* byte 247 */
  uint8_t etn_early_redemption_period[2];                     /* bytes 248 to 249 */
  uint8_t institution_code_1_appraised_price_calculation[2];  /* bytes 250 to 251 */
  uint8_t institution_code_2_appraised_price_calculation[2];  /* bytes 252 to 253 */
  uint8_t end_keyword;                                        /* byte 254 */
} SecuritiesEtnBatchDataMessage;

/* any Securities Etn Batch Data Message at all: every byte one the checker chooses */
static void any_securities_etn_batch_data_message(SecuritiesEtnBatchDataMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->name_of_issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->english_name_of_issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->numbers_of_issuer[i] = arbitrary(); }
  record->payment_methods = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->etn_payment_date[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->etn_lp_holding_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->loss_protection_etn_profit_structure_code[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->etn_maximum_redemption_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->etn_minimum_redemption_price[i] = arbitrary(); }
  record->etn_early_redemption_possibility = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->etn_early_redemption_period[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->institution_code_1_appraised_price_calculation[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->institution_code_2_appraised_price_calculation[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Etn Batch Data Message to the wire: 255 bytes from at, returning where the next byte goes */
static size_t encode_securities_etn_batch_data_message(const SecuritiesEtnBatchDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->name_of_issuer[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->english_name_of_issuer[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->numbers_of_issuer[i]; }
  wire[at++] = record->payment_methods;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_trading_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->etn_payment_date[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->etn_lp_holding_quantity[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->loss_protection_etn_profit_structure_code[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->etn_maximum_redemption_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->etn_minimum_redemption_price[i]; }
  wire[at++] = record->etn_early_redemption_possibility;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->etn_early_redemption_period[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->institution_code_1_appraised_price_calculation[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->institution_code_2_appraised_price_calculation[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Etn Batch Data Message off the wire: 255 bytes from at, returning where the next byte lies */
static size_t decode_securities_etn_batch_data_message(SecuritiesEtnBatchDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->name_of_issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->english_name_of_issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->numbers_of_issuer[i] = wire[at++]; }
  record->payment_methods = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->etn_payment_date[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->etn_lp_holding_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->loss_protection_etn_profit_structure_code[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->etn_maximum_redemption_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->etn_minimum_redemption_price[i] = wire[at++]; }
  record->etn_early_redemption_possibility = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->etn_early_redemption_period[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->institution_code_1_appraised_price_calculation[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->institution_code_2_appraised_price_calculation[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Etn Batch Data Message is what was written, byte for byte */
static void equal_securities_etn_batch_data_message(const SecuritiesEtnBatchDataMessage *read, const SecuritiesEtnBatchDataMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->name_of_issuer[i] == written->name_of_issuer[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->english_name_of_issuer[i] == written->english_name_of_issuer[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->numbers_of_issuer[i] == written->numbers_of_issuer[i]); }
  assert(read->payment_methods == written->payment_methods);
  for (size_t i = 0; i < 8; i++) { assert(read->last_trading_date[i] == written->last_trading_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->etn_payment_date[i] == written->etn_payment_date[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->etn_lp_holding_quantity[i] == written->etn_lp_holding_quantity[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->loss_protection_etn_profit_structure_code[i] == written->loss_protection_etn_profit_structure_code[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->etn_maximum_redemption_price[i] == written->etn_maximum_redemption_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->etn_minimum_redemption_price[i] == written->etn_minimum_redemption_price[i]); }
  assert(read->etn_early_redemption_possibility == written->etn_early_redemption_possibility);
  for (size_t i = 0; i < 2; i++) { assert(read->etn_early_redemption_period[i] == written->etn_early_redemption_period[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->institution_code_1_appraised_price_calculation[i] == written->institution_code_1_appraised_price_calculation[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->institution_code_2_appraised_price_calculation[i] == written->institution_code_2_appraised_price_calculation[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Etn Batch Data Message: written and read back, then read and written back */
static void check_securities_etn_batch_data_message(void) {
  SecuritiesEtnBatchDataMessage sent;
  SecuritiesEtnBatchDataMessage got;
  uint8_t wire[255];
  uint8_t again[255];

  any_securities_etn_batch_data_message(&sent);
  assert(encode_securities_etn_batch_data_message(&sent, wire, 0) == 255);
  assert(decode_securities_etn_batch_data_message(&got, wire, 0) == 255);
  equal_securities_etn_batch_data_message(&got, &sent);

  for (size_t i = 0; i < 255; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_etn_batch_data_message(&got, wire, 0) == 255);
  assert(encode_securities_etn_batch_data_message(&got, again, 0) == 255);
  for (size_t i = 0; i < 255; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Etn Early Redemption Message: 83 bytes ----------------------- */

/* ETN Early Redemption Criteria reference. */
typedef struct {
  uint8_t message_sequence_number[8];          /* bytes 0 to 7 */
  uint8_t isin_code[12];                       /* bytes 8 to 19 */
  uint8_t etn_early_redemption_period[2];      /* bytes 20 to 21 */
  uint8_t early_redemption_appraisal_date[8];  /* bytes 22 to 29 */
  uint8_t early_redemption_criteria_code;      /* byte 30 */
  uint8_t early_redemption_base_index_1[10];   /* bytes 31 to 40 */
  uint8_t early_redemption_base_index_2[10];   /* bytes 41 to 50 */
  uint8_t early_redemption_price[23];          /* bytes 51 to 73 */
  uint8_t early_repemption_payment_date[8];    /* bytes 74 to 81 */
  uint8_t end_keyword;                         /* byte 82 */
} SecuritiesEtnEarlyRedemptionMessage;

/* any Securities Etn Early Redemption Message at all: every byte one the checker chooses */
static void any_securities_etn_early_redemption_message(SecuritiesEtnEarlyRedemptionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->etn_early_redemption_period[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->early_redemption_appraisal_date[i] = arbitrary(); }
  record->early_redemption_criteria_code = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->early_redemption_base_index_1[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->early_redemption_base_index_2[i] = arbitrary(); }
  for (size_t i = 0; i < 23; i++) { record->early_redemption_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->early_repemption_payment_date[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Etn Early Redemption Message to the wire: 83 bytes from at, returning where the next byte goes */
static size_t encode_securities_etn_early_redemption_message(const SecuritiesEtnEarlyRedemptionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->etn_early_redemption_period[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->early_redemption_appraisal_date[i]; }
  wire[at++] = record->early_redemption_criteria_code;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->early_redemption_base_index_1[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->early_redemption_base_index_2[i]; }
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->early_redemption_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->early_repemption_payment_date[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Etn Early Redemption Message off the wire: 83 bytes from at, returning where the next byte lies */
static size_t decode_securities_etn_early_redemption_message(SecuritiesEtnEarlyRedemptionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->etn_early_redemption_period[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->early_redemption_appraisal_date[i] = wire[at++]; }
  record->early_redemption_criteria_code = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->early_redemption_base_index_1[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->early_redemption_base_index_2[i] = wire[at++]; }
  for (size_t i = 0; i < 23; i++) { record->early_redemption_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->early_repemption_payment_date[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Etn Early Redemption Message is what was written, byte for byte */
static void equal_securities_etn_early_redemption_message(const SecuritiesEtnEarlyRedemptionMessage *read, const SecuritiesEtnEarlyRedemptionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->etn_early_redemption_period[i] == written->etn_early_redemption_period[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->early_redemption_appraisal_date[i] == written->early_redemption_appraisal_date[i]); }
  assert(read->early_redemption_criteria_code == written->early_redemption_criteria_code);
  for (size_t i = 0; i < 10; i++) { assert(read->early_redemption_base_index_1[i] == written->early_redemption_base_index_1[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->early_redemption_base_index_2[i] == written->early_redemption_base_index_2[i]); }
  for (size_t i = 0; i < 23; i++) { assert(read->early_redemption_price[i] == written->early_redemption_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->early_repemption_payment_date[i] == written->early_repemption_payment_date[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Etn Early Redemption Message: written and read back, then read and written back */
static void check_securities_etn_early_redemption_message(void) {
  SecuritiesEtnEarlyRedemptionMessage sent;
  SecuritiesEtnEarlyRedemptionMessage got;
  uint8_t wire[83];
  uint8_t again[83];

  any_securities_etn_early_redemption_message(&sent);
  assert(encode_securities_etn_early_redemption_message(&sent, wire, 0) == 83);
  assert(decode_securities_etn_early_redemption_message(&got, wire, 0) == 83);
  equal_securities_etn_early_redemption_message(&got, &sent);

  for (size_t i = 0; i < 83; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_etn_early_redemption_message(&got, wire, 0) == 83);
  assert(encode_securities_etn_early_redemption_message(&got, again, 0) == 83);
  for (size_t i = 0; i < 83; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Etp Constituents Message: 204 bytes -------------------------- */

/* ETP Constituents reference (IFMSBTD0013) — Securities C STK variant. */
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
} SecuritiesEtpConstituentsMessage;

/* any Securities Etp Constituents Message at all: every byte one the checker chooses */
static void any_securities_etp_constituents_message(SecuritiesEtpConstituentsMessage *record) {
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

/* Securities Etp Constituents Message to the wire: 204 bytes from at, returning where the next byte goes */
static size_t encode_securities_etp_constituents_message(const SecuritiesEtpConstituentsMessage *record, uint8_t *wire, size_t at) {
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

/* Securities Etp Constituents Message off the wire: 204 bytes from at, returning where the next byte lies */
static size_t decode_securities_etp_constituents_message(SecuritiesEtpConstituentsMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Securities Etp Constituents Message is what was written, byte for byte */
static void equal_securities_etp_constituents_message(const SecuritiesEtpConstituentsMessage *read, const SecuritiesEtpConstituentsMessage *written) {
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

/* Securities Etp Constituents Message: written and read back, then read and written back */
static void check_securities_etp_constituents_message(void) {
  SecuritiesEtpConstituentsMessage sent;
  SecuritiesEtpConstituentsMessage got;
  uint8_t wire[204];
  uint8_t again[204];

  any_securities_etp_constituents_message(&sent);
  assert(encode_securities_etp_constituents_message(&sent, wire, 0) == 204);
  assert(decode_securities_etp_constituents_message(&got, wire, 0) == 204);
  equal_securities_etp_constituents_message(&got, &sent);

  for (size_t i = 0; i < 204; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_etp_constituents_message(&got, wire, 0) == 204);
  assert(encode_securities_etp_constituents_message(&got, again, 0) == 204);
  for (size_t i = 0; i < 204; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Knock Out Elw Message: 534 bytes ----------------------------- */

/* Knock-out ELW reference. */
typedef struct {
  uint8_t message_sequence_number[8];                         /* bytes 0 to 7 */
  uint8_t isin_code[12];                                      /* bytes 8 to 19 */
  uint8_t base_price_to_knock_out_elw[13];                    /* bytes 20 to 32 */
  uint8_t knock_out_elw_rights[200];                          /* bytes 33 to 232 */
  uint8_t knock_out_elw_calculation_of_appraised_price[300];  /* bytes 233 to 532 */
  uint8_t end_keyword;                                        /* byte 533 */
} SecuritiesKnockOutElwMessage;

/* any Securities Knock Out Elw Message at all: every byte one the checker chooses */
static void any_securities_knock_out_elw_message(SecuritiesKnockOutElwMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->base_price_to_knock_out_elw[i] = arbitrary(); }
  for (size_t i = 0; i < 200; i++) { record->knock_out_elw_rights[i] = arbitrary(); }
  for (size_t i = 0; i < 300; i++) { record->knock_out_elw_calculation_of_appraised_price[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Knock Out Elw Message to the wire: 534 bytes from at, returning where the next byte goes */
static size_t encode_securities_knock_out_elw_message(const SecuritiesKnockOutElwMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->base_price_to_knock_out_elw[i]; }
  for (size_t i = 0; i < 200; i++) { wire[at++] = record->knock_out_elw_rights[i]; }
  for (size_t i = 0; i < 300; i++) { wire[at++] = record->knock_out_elw_calculation_of_appraised_price[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Knock Out Elw Message off the wire: 534 bytes from at, returning where the next byte lies */
static size_t decode_securities_knock_out_elw_message(SecuritiesKnockOutElwMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->base_price_to_knock_out_elw[i] = wire[at++]; }
  for (size_t i = 0; i < 200; i++) { record->knock_out_elw_rights[i] = wire[at++]; }
  for (size_t i = 0; i < 300; i++) { record->knock_out_elw_calculation_of_appraised_price[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Knock Out Elw Message is what was written, byte for byte */
static void equal_securities_knock_out_elw_message(const SecuritiesKnockOutElwMessage *read, const SecuritiesKnockOutElwMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->base_price_to_knock_out_elw[i] == written->base_price_to_knock_out_elw[i]); }
  for (size_t i = 0; i < 200; i++) { assert(read->knock_out_elw_rights[i] == written->knock_out_elw_rights[i]); }
  for (size_t i = 0; i < 300; i++) { assert(read->knock_out_elw_calculation_of_appraised_price[i] == written->knock_out_elw_calculation_of_appraised_price[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Knock Out Elw Message: written and read back, then read and written back */
static void check_securities_knock_out_elw_message(void) {
  SecuritiesKnockOutElwMessage sent;
  SecuritiesKnockOutElwMessage got;
  uint8_t wire[534];
  uint8_t again[534];

  any_securities_knock_out_elw_message(&sent);
  assert(encode_securities_knock_out_elw_message(&sent, wire, 0) == 534);
  assert(decode_securities_knock_out_elw_message(&got, wire, 0) == 534);
  equal_securities_knock_out_elw_message(&got, &sent);

  for (size_t i = 0; i < 534; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_knock_out_elw_message(&got, wire, 0) == 534);
  assert(encode_securities_knock_out_elw_message(&got, again, 0) == 534);
  for (size_t i = 0; i < 534; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Knock Out Underlying Message: 90 bytes ----------------------- */

/* High/Low Price of Underlying Asset for Knock-out ELW. */
typedef struct {
  uint8_t isin_code[12];                        /* bytes 0 to 11 */
  uint8_t message_sequence_number[8];           /* bytes 12 to 19 */
  uint8_t transmission_date[8];                 /* bytes 20 to 27 */
  uint8_t trading_date_of_underlying_asset[8];  /* bytes 28 to 35 */
  uint8_t the_date_knock_out_occurred[8];       /* bytes 36 to 43 */
  uint8_t ampm_type_code;                       /* byte 44 */
  uint8_t underlying_i_s_i_n_code[12];          /* bytes 45 to 56 */
  uint8_t index_id[6];                          /* bytes 57 to 62 */
  uint8_t underlying_today_s_high[11];          /* bytes 63 to 73 */
  uint8_t underlying_today_s_low[11];           /* bytes 74 to 84 */
  uint8_t filler_4[4];                          /* bytes 85 to 88 */
  uint8_t end_keyword;                          /* byte 89 */
} SecuritiesKnockOutUnderlyingMessage;

/* any Securities Knock Out Underlying Message at all: every byte one the checker chooses */
static void any_securities_knock_out_underlying_message(SecuritiesKnockOutUnderlyingMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transmission_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_date_of_underlying_asset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->the_date_knock_out_occurred[i] = arbitrary(); }
  record->ampm_type_code = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->underlying_i_s_i_n_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_today_s_high[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_today_s_low[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Knock Out Underlying Message to the wire: 90 bytes from at, returning where the next byte goes */
static size_t encode_securities_knock_out_underlying_message(const SecuritiesKnockOutUnderlyingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transmission_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_date_of_underlying_asset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->the_date_knock_out_occurred[i]; }
  wire[at++] = record->ampm_type_code;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_i_s_i_n_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_today_s_high[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_today_s_low[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Knock Out Underlying Message off the wire: 90 bytes from at, returning where the next byte lies */
static size_t decode_securities_knock_out_underlying_message(SecuritiesKnockOutUnderlyingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transmission_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_date_of_underlying_asset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->the_date_knock_out_occurred[i] = wire[at++]; }
  record->ampm_type_code = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->underlying_i_s_i_n_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_today_s_high[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_today_s_low[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Knock Out Underlying Message is what was written, byte for byte */
static void equal_securities_knock_out_underlying_message(const SecuritiesKnockOutUnderlyingMessage *read, const SecuritiesKnockOutUnderlyingMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transmission_date[i] == written->transmission_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_date_of_underlying_asset[i] == written->trading_date_of_underlying_asset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->the_date_knock_out_occurred[i] == written->the_date_knock_out_occurred[i]); }
  assert(read->ampm_type_code == written->ampm_type_code);
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_i_s_i_n_code[i] == written->underlying_i_s_i_n_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_today_s_high[i] == written->underlying_today_s_high[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_today_s_low[i] == written->underlying_today_s_low[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Knock Out Underlying Message: written and read back, then read and written back */
static void check_securities_knock_out_underlying_message(void) {
  SecuritiesKnockOutUnderlyingMessage sent;
  SecuritiesKnockOutUnderlyingMessage got;
  uint8_t wire[90];
  uint8_t again[90];

  any_securities_knock_out_underlying_message(&sent);
  assert(encode_securities_knock_out_underlying_message(&sent, wire, 0) == 90);
  assert(decode_securities_knock_out_underlying_message(&got, wire, 0) == 90);
  equal_securities_knock_out_underlying_message(&got, &sent);

  for (size_t i = 0; i < 90; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_knock_out_underlying_message(&got, wire, 0) == 90);
  assert(encode_securities_knock_out_underlying_message(&got, again, 0) == 90);
  for (size_t i = 0; i < 90; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Closing Price Trade Remaining Quantity On Quotes Message: 77 bytes ---- */

/* Equities Closing Price Trade — Remaining Quantity on Quotes (IFMSRPD0063) — Securities A KOSPI variant. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t isin_code[12];                          /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];    /* bytes 22 to 27 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 28 to 39 */
  uint8_t accumulated_trading_volume[12];         /* bytes 40 to 51 */
  uint8_t ask_total_volume[12];                   /* bytes 52 to 63 */
  uint8_t bid_total_volume[12];                   /* bytes 64 to 75 */
  uint8_t end_keyword;                            /* byte 76 */
} SecuritiesClosingPriceTradeRemainingQuantityOnQuotesMessage;

/* any Securities Closing Price Trade Remaining Quantity On Quotes Message at all: every byte one the checker chooses */
static void any_securities_closing_price_trade_remaining_quantity_on_quotes_message(SecuritiesClosingPriceTradeRemainingQuantityOnQuotesMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ask_total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_total_volume[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Closing Price Trade Remaining Quantity On Quotes Message to the wire: 77 bytes from at, returning where the next byte goes */
static size_t encode_securities_closing_price_trade_remaining_quantity_on_quotes_message(const SecuritiesClosingPriceTradeRemainingQuantityOnQuotesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ask_total_volume[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_total_volume[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Closing Price Trade Remaining Quantity On Quotes Message off the wire: 77 bytes from at, returning where the next byte lies */
static size_t decode_securities_closing_price_trade_remaining_quantity_on_quotes_message(SecuritiesClosingPriceTradeRemainingQuantityOnQuotesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ask_total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_total_volume[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Closing Price Trade Remaining Quantity On Quotes Message is what was written, byte for byte */
static void equal_securities_closing_price_trade_remaining_quantity_on_quotes_message(const SecuritiesClosingPriceTradeRemainingQuantityOnQuotesMessage *read, const SecuritiesClosingPriceTradeRemainingQuantityOnQuotesMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ask_total_volume[i] == written->ask_total_volume[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_total_volume[i] == written->bid_total_volume[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Closing Price Trade Remaining Quantity On Quotes Message: written and read back, then read and written back */
static void check_securities_closing_price_trade_remaining_quantity_on_quotes_message(void) {
  SecuritiesClosingPriceTradeRemainingQuantityOnQuotesMessage sent;
  SecuritiesClosingPriceTradeRemainingQuantityOnQuotesMessage got;
  uint8_t wire[77];
  uint8_t again[77];

  any_securities_closing_price_trade_remaining_quantity_on_quotes_message(&sent);
  assert(encode_securities_closing_price_trade_remaining_quantity_on_quotes_message(&sent, wire, 0) == 77);
  assert(decode_securities_closing_price_trade_remaining_quantity_on_quotes_message(&got, wire, 0) == 77);
  equal_securities_closing_price_trade_remaining_quantity_on_quotes_message(&got, &sent);

  for (size_t i = 0; i < 77; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_closing_price_trade_remaining_quantity_on_quotes_message(&got, wire, 0) == 77);
  assert(encode_securities_closing_price_trade_remaining_quantity_on_quotes_message(&got, again, 0) == 77);
  for (size_t i = 0; i < 77; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities A Blox Trade Quotes Message: 42 bytes ------------------------ */

/* A-Blox trade Quotes (IFMSRPD0066) — Securities A KOSPI variant. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t isin_code[12];                          /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];    /* bytes 22 to 27 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 28 to 39 */
  uint8_t ask_bid_type_code;                      /* byte 40 */
  uint8_t end_keyword;                            /* byte 41 */
} SecuritiesABloxTradeQuotesMessage;

/* any Securities A Blox Trade Quotes Message at all: every byte one the checker chooses */
static void any_securities_a_blox_trade_quotes_message(SecuritiesABloxTradeQuotesMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  record->ask_bid_type_code = arbitrary();
  record->end_keyword = arbitrary();
}

/* Securities A Blox Trade Quotes Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_securities_a_blox_trade_quotes_message(const SecuritiesABloxTradeQuotesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  wire[at++] = record->ask_bid_type_code;
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities A Blox Trade Quotes Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_securities_a_blox_trade_quotes_message(SecuritiesABloxTradeQuotesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  record->ask_bid_type_code = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities A Blox Trade Quotes Message is what was written, byte for byte */
static void equal_securities_a_blox_trade_quotes_message(const SecuritiesABloxTradeQuotesMessage *read, const SecuritiesABloxTradeQuotesMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  assert(read->ask_bid_type_code == written->ask_bid_type_code);
  assert(read->end_keyword == written->end_keyword);
}

/* Securities A Blox Trade Quotes Message: written and read back, then read and written back */
static void check_securities_a_blox_trade_quotes_message(void) {
  SecuritiesABloxTradeQuotesMessage sent;
  SecuritiesABloxTradeQuotesMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_securities_a_blox_trade_quotes_message(&sent);
  assert(encode_securities_a_blox_trade_quotes_message(&sent, wire, 0) == 42);
  assert(decode_securities_a_blox_trade_quotes_message(&got, wire, 0) == 42);
  equal_securities_a_blox_trade_quotes_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_a_blox_trade_quotes_message(&got, wire, 0) == 42);
  assert(encode_securities_a_blox_trade_quotes_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Etn Profit Structure Message: 2021 bytes --------------------- */

/* ETN Profit Structure (IFMSBTD0008) — Securities C. Contains 2000-byte details of ETN profit structure. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t isin_code[12];                          /* bytes 8 to 19 */
  uint8_t details_of_etn_profit_structure[2000];  /* bytes 20 to 2019 */
  uint8_t end_keyword;                            /* byte 2020 */
} SecuritiesEtnProfitStructureMessage;

/* any Securities Etn Profit Structure Message at all: every byte one the checker chooses */
static void any_securities_etn_profit_structure_message(SecuritiesEtnProfitStructureMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2000; i++) { record->details_of_etn_profit_structure[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Securities Etn Profit Structure Message to the wire: 2021 bytes from at, returning where the next byte goes */
static size_t encode_securities_etn_profit_structure_message(const SecuritiesEtnProfitStructureMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 2000; i++) { wire[at++] = record->details_of_etn_profit_structure[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Securities Etn Profit Structure Message off the wire: 2021 bytes from at, returning where the next byte lies */
static size_t decode_securities_etn_profit_structure_message(SecuritiesEtnProfitStructureMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2000; i++) { record->details_of_etn_profit_structure[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Securities Etn Profit Structure Message is what was written, byte for byte */
static void equal_securities_etn_profit_structure_message(const SecuritiesEtnProfitStructureMessage *read, const SecuritiesEtnProfitStructureMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 2000; i++) { assert(read->details_of_etn_profit_structure[i] == written->details_of_etn_profit_structure[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Securities Etn Profit Structure Message: written and read back, then read and written back */
static void check_securities_etn_profit_structure_message(void) {
  SecuritiesEtnProfitStructureMessage sent;
  SecuritiesEtnProfitStructureMessage got;
  uint8_t wire[2021];
  uint8_t again[2021];

  any_securities_etn_profit_structure_message(&sent);
  assert(encode_securities_etn_profit_structure_message(&sent, wire, 0) == 2021);
  assert(decode_securities_etn_profit_structure_message(&got, wire, 0) == 2021);
  equal_securities_etn_profit_structure_message(&got, &sent);

  for (size_t i = 0; i < 2021; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_etn_profit_structure_message(&got, wire, 0) == 2021);
  assert(encode_securities_etn_profit_structure_message(&got, again, 0) == 2021);
  for (size_t i = 0; i < 2021; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Top Five Traders Activities Message: 409 bytes --------------- */

/* Top Five Traders' Activities for KOSPI (Securities A). Top Five Traders' Activities (IFMSSTD0006). Ask/bid member number, traded volume and value for the top five member firms per issue. */
typedef struct {
  uint8_t isin_code[12];                        /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 12 to 17 */
  uint8_t member_number_1_for_ask[5];           /* bytes 18 to 22 */
  uint8_t ask_trading_volume_1[12];             /* bytes 23 to 34 */
  uint8_t ask_trading_value_1[22];              /* bytes 35 to 56 */
  uint8_t member_number_1_for_bid[5];           /* bytes 57 to 61 */
  uint8_t bid_trading_volume_1[12];             /* bytes 62 to 73 */
  uint8_t bid_trading_value_1[22];              /* bytes 74 to 95 */
  uint8_t member_number_2_for_ask[5];           /* bytes 96 to 100 */
  uint8_t ask_trading_volume_2[12];             /* bytes 101 to 112 */
  uint8_t ask_trading_value_2[22];              /* bytes 113 to 134 */
  uint8_t member_number_2_for_bid[5];           /* bytes 135 to 139 */
  uint8_t bid_trading_volume_2[12];             /* bytes 140 to 151 */
  uint8_t bid_trading_value_2[22];              /* bytes 152 to 173 */
  uint8_t member_number_3_for_ask[5];           /* bytes 174 to 178 */
  uint8_t ask_trading_volume_3[12];             /* bytes 179 to 190 */
  uint8_t ask_trading_value_3[22];              /* bytes 191 to 212 */
  uint8_t member_number_3_for_bid[5];           /* bytes 213 to 217 */
  uint8_t bid_trading_volume_3[12];             /* bytes 218 to 229 */
  uint8_t bid_trading_value_3[22];              /* bytes 230 to 251 */
  uint8_t member_number_4_for_ask[5];           /* bytes 252 to 256 */
  uint8_t ask_trading_volume_4[12];             /* bytes 257 to 268 */
  uint8_t ask_trading_value_4[22];              /* bytes 269 to 290 */
  uint8_t member_number_4_for_bid[5];           /* bytes 291 to 295 */
  uint8_t bid_trading_volume_4[12];             /* bytes 296 to 307 */
  uint8_t bid_trading_value_4[22];              /* bytes 308 to 329 */
  uint8_t member_number_5_for_ask[5];           /* bytes 330 to 334 */
  uint8_t ask_trading_volume_5[12];             /* bytes 335 to 346 */
  uint8_t ask_trading_value_5[22];              /* bytes 347 to 368 */
  uint8_t member_number_5_for_bid[5];           /* bytes 369 to 373 */
  uint8_t bid_trading_volume_5[12];             /* bytes 374 to 385 */
  uint8_t bid_trading_value_5[22];              /* bytes 386 to 407 */
  uint8_t end_keyword;                          /* byte 408 */
} SecuritiesTopFiveTradersActivitiesMessage;

/* any Securities Top Five Traders Activities Message at all: every byte one the checker chooses */
static void any_securities_top_five_traders_activities_message(SecuritiesTopFiveTradersActivitiesMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
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

/* Securities Top Five Traders Activities Message to the wire: 409 bytes from at, returning where the next byte goes */
static size_t encode_securities_top_five_traders_activities_message(const SecuritiesTopFiveTradersActivitiesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
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

/* Securities Top Five Traders Activities Message off the wire: 409 bytes from at, returning where the next byte lies */
static size_t decode_securities_top_five_traders_activities_message(SecuritiesTopFiveTradersActivitiesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
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

/* what was read of Securities Top Five Traders Activities Message is what was written, byte for byte */
static void equal_securities_top_five_traders_activities_message(const SecuritiesTopFiveTradersActivitiesMessage *read, const SecuritiesTopFiveTradersActivitiesMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
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

/* Securities Top Five Traders Activities Message: written and read back, then read and written back */
static void check_securities_top_five_traders_activities_message(void) {
  SecuritiesTopFiveTradersActivitiesMessage sent;
  SecuritiesTopFiveTradersActivitiesMessage got;
  uint8_t wire[409];
  uint8_t again[409];

  any_securities_top_five_traders_activities_message(&sent);
  assert(encode_securities_top_five_traders_activities_message(&sent, wire, 0) == 409);
  assert(decode_securities_top_five_traders_activities_message(&got, wire, 0) == 409);
  equal_securities_top_five_traders_activities_message(&got, &sent);

  for (size_t i = 0; i < 409; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_top_five_traders_activities_message(&got, wire, 0) == 409);
  assert(encode_securities_top_five_traders_activities_message(&got, again, 0) == 409);
  for (size_t i = 0; i < 409; i++) { assert(again[i] == wire[i]); }
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
  check_securities_quote_mm_lp_excluded_message();
  check_securities_quote_mm_lp_included_message();
  check_securities_snapshot_mm_lp_excluded_message();
  check_securities_snapshot_mm_lp_included_message();
  check_securities_order_filled_message();
  check_securities_negotiated_trade_message();
  check_securities_market_operation_ts_message();
  check_securities_determination_of_base_price_message();
  check_securities_issue_closing_message();
  check_securities_market_operation_schedule_message();
  check_securities_random_end_message();
  check_securities_triggering_vi_message();
  check_securities_quantity_allocation_message();
  check_securities_member_firm_sanctions_message();
  check_securities_equities_changes_of_batch_data_message();
  check_securities_group_order_acceptance_halt_message();
  check_securities_equities_batch_data_message();
  check_securities_closing_date_message();
  check_securities_mm_lp_information_message();
  check_securities_member_information_message();
  check_securities_treasury_stocks_batch_message();
  check_securities_equity_index_indicator_message();
  check_securities_dividend_yield_per_industry_message();
  check_securities_investor_activities_per_industry_message();
  check_securities_investor_activities_per_issue_eod_message();
  check_securities_investor_activities_per_commodities_message();
  check_securities_short_selling_message();
  check_securities_treasury_stocks_traded_message();
  check_securities_buy_in_volume_message();
  check_securities_elw_batch_data_message();
  check_securities_etn_batch_data_message();
  check_securities_etn_early_redemption_message();
  check_securities_etp_constituents_message();
  check_securities_knock_out_elw_message();
  check_securities_knock_out_underlying_message();
  check_securities_closing_price_trade_remaining_quantity_on_quotes_message();
  check_securities_a_blox_trade_quotes_message();
  check_securities_etn_profit_structure_message();
  check_securities_top_five_traders_activities_message();
  check_bonds_batch_data_message();
  check_repo_batch_data_message();
  check_issue_event_message();
  check_corporate_bonds_reference_message();
  check_regular_bonds_installment_repayment_date_message();
  check_repo_classification_data_message();
  check_repo_trade_availability_per_term_message();
  check_retail_bonds_type_code_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
