// koscom/mdcsrealtime/koscom/Koscom_MdcsRealtime_Koscom_v1_20.c
/*
 * Koscom Co., Ltd. MDCS Realtime Koscom
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

/* ---- K Otc Issue Closing Message: 35 bytes ----------------------------------- */

/* K-OTC Issue Closing. Reports closing price and the quotation category per ISIN. */
typedef struct {
  uint8_t isin[12];            /* bytes 0 to 11 */
  uint8_t data_seq_number[8];  /* bytes 12 to 19 */
  uint8_t closing_price[9];    /* bytes 20 to 28 */
  uint8_t quotation_category;  /* byte 29 */
  uint8_t filler_4[4];         /* bytes 30 to 33 */
  uint8_t end_keyword;         /* byte 34 */
} KOtcIssueClosingMessage;

/* any K Otc Issue Closing Message at all: every byte one the checker chooses */
static void any_k_otc_issue_closing_message(KOtcIssueClosingMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->closing_price[i] = arbitrary(); }
  record->quotation_category = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* K Otc Issue Closing Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_k_otc_issue_closing_message(const KOtcIssueClosingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->data_seq_number[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->closing_price[i]; }
  wire[at++] = record->quotation_category;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* K Otc Issue Closing Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_k_otc_issue_closing_message(KOtcIssueClosingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->closing_price[i] = wire[at++]; }
  record->quotation_category = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of K Otc Issue Closing Message is what was written, byte for byte */
static void equal_k_otc_issue_closing_message(const KOtcIssueClosingMessage *read, const KOtcIssueClosingMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->data_seq_number[i] == written->data_seq_number[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  assert(read->quotation_category == written->quotation_category);
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* K Otc Issue Closing Message: written and read back, then read and written back */
static void check_k_otc_issue_closing_message(void) {
  KOtcIssueClosingMessage sent;
  KOtcIssueClosingMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_k_otc_issue_closing_message(&sent);
  assert(encode_k_otc_issue_closing_message(&sent, wire, 0) == 35);
  assert(decode_k_otc_issue_closing_message(&got, wire, 0) == 35);
  equal_k_otc_issue_closing_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_k_otc_issue_closing_message(&got, wire, 0) == 35);
  assert(encode_k_otc_issue_closing_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- K Otc Market Operation Message: 25 bytes -------------------------------- */

/* K-OTC Market Operation. Trading halt / lift-after-halt events with reason code. */
typedef struct {
  uint8_t isin[12];            /* bytes 0 to 11 */
  uint8_t data_seq_number[8];  /* bytes 12 to 19 */
  uint8_t type;                /* byte 20 */
  uint8_t reason[2];           /* bytes 21 to 22 */
  uint8_t filler_1;            /* byte 23 */
  uint8_t end_keyword;         /* byte 24 */
} KOtcMarketOperationMessage;

/* any K Otc Market Operation Message at all: every byte one the checker chooses */
static void any_k_otc_market_operation_message(KOtcMarketOperationMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = arbitrary(); }
  record->type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reason[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  record->end_keyword = arbitrary();
}

/* K Otc Market Operation Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_k_otc_market_operation_message(const KOtcMarketOperationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->data_seq_number[i]; }
  wire[at++] = record->type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reason[i]; }
  wire[at++] = record->filler_1;
  wire[at++] = record->end_keyword;

  return at;
}

/* K Otc Market Operation Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_k_otc_market_operation_message(KOtcMarketOperationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = wire[at++]; }
  record->type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reason[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of K Otc Market Operation Message is what was written, byte for byte */
static void equal_k_otc_market_operation_message(const KOtcMarketOperationMessage *read, const KOtcMarketOperationMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->data_seq_number[i] == written->data_seq_number[i]); }
  assert(read->type == written->type);
  for (size_t i = 0; i < 2; i++) { assert(read->reason[i] == written->reason[i]); }
  assert(read->filler_1 == written->filler_1);
  assert(read->end_keyword == written->end_keyword);
}

/* K Otc Market Operation Message: written and read back, then read and written back */
static void check_k_otc_market_operation_message(void) {
  KOtcMarketOperationMessage sent;
  KOtcMarketOperationMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_k_otc_market_operation_message(&sent);
  assert(encode_k_otc_market_operation_message(&sent, wire, 0) == 25);
  assert(decode_k_otc_market_operation_message(&got, wire, 0) == 25);
  equal_k_otc_market_operation_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_k_otc_market_operation_message(&got, wire, 0) == 25);
  assert(encode_k_otc_market_operation_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- K Otc Market Action Message: 95 bytes ----------------------------------- */

/* K-OTC Market Action. Basis price and upper/lower limit price changes. */
typedef struct {
  uint8_t isin_nullable[12];                   /* bytes 0 to 11 */
  uint8_t data_type[2];                        /* bytes 12 to 13 */
  uint8_t change_date[8];                      /* bytes 14 to 21 */
  uint8_t change_time[8];                      /* bytes 22 to 29 */
  uint8_t basis_price_before_action[9];        /* bytes 30 to 38 */
  uint8_t upper_limit_price_before_action[9];  /* bytes 39 to 47 */
  uint8_t lower_limit_price_before_action[9];  /* bytes 48 to 56 */
  uint8_t basis_price_after_action[9];         /* bytes 57 to 65 */
  uint8_t upper_limit_price_after_action[9];   /* bytes 66 to 74 */
  uint8_t lower_limit_price_after_action[9];   /* bytes 75 to 83 */
  uint8_t filler_10[10];                       /* bytes 84 to 93 */
  uint8_t end_keyword;                         /* byte 94 */
} KOtcMarketActionMessage;

/* any K Otc Market Action Message at all: every byte one the checker chooses */
static void any_k_otc_market_action_message(KOtcMarketActionMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_nullable[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->data_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->change_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->change_time[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->basis_price_before_action[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->upper_limit_price_before_action[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->lower_limit_price_before_action[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->basis_price_after_action[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->upper_limit_price_after_action[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->lower_limit_price_after_action[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->filler_10[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* K Otc Market Action Message to the wire: 95 bytes from at, returning where the next byte goes */
static size_t encode_k_otc_market_action_message(const KOtcMarketActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_nullable[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->data_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->change_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->change_time[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->basis_price_before_action[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->upper_limit_price_before_action[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->lower_limit_price_before_action[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->basis_price_after_action[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->upper_limit_price_after_action[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->lower_limit_price_after_action[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->filler_10[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* K Otc Market Action Message off the wire: 95 bytes from at, returning where the next byte lies */
static size_t decode_k_otc_market_action_message(KOtcMarketActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_nullable[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->data_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->change_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->change_time[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->basis_price_before_action[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->upper_limit_price_before_action[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->lower_limit_price_before_action[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->basis_price_after_action[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->upper_limit_price_after_action[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->lower_limit_price_after_action[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->filler_10[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of K Otc Market Action Message is what was written, byte for byte */
static void equal_k_otc_market_action_message(const KOtcMarketActionMessage *read, const KOtcMarketActionMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_nullable[i] == written->isin_nullable[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->data_type[i] == written->data_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->change_date[i] == written->change_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->change_time[i] == written->change_time[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->basis_price_before_action[i] == written->basis_price_before_action[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->upper_limit_price_before_action[i] == written->upper_limit_price_before_action[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->lower_limit_price_before_action[i] == written->lower_limit_price_before_action[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->basis_price_after_action[i] == written->basis_price_after_action[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->upper_limit_price_after_action[i] == written->upper_limit_price_after_action[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->lower_limit_price_after_action[i] == written->lower_limit_price_after_action[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->filler_10[i] == written->filler_10[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* K Otc Market Action Message: written and read back, then read and written back */
static void check_k_otc_market_action_message(void) {
  KOtcMarketActionMessage sent;
  KOtcMarketActionMessage got;
  uint8_t wire[95];
  uint8_t again[95];

  any_k_otc_market_action_message(&sent);
  assert(encode_k_otc_market_action_message(&sent, wire, 0) == 95);
  assert(decode_k_otc_market_action_message(&got, wire, 0) == 95);
  equal_k_otc_market_action_message(&got, &sent);

  for (size_t i = 0; i < 95; i++) { wire[i] = arbitrary(); }
  assert(decode_k_otc_market_action_message(&got, wire, 0) == 95);
  assert(encode_k_otc_market_action_message(&got, again, 0) == 95);
  for (size_t i = 0; i < 95; i++) { assert(again[i] == wire[i]); }
}

/* ---- K Otc Quote Message: 195 bytes ------------------------------------------ */

/* K-OTC Quote. Bid/ask quote with remaining quantity at the best price. */
typedef struct {
  uint8_t isin[12];                                                /* bytes 0 to 11 */
  uint8_t data_seq_number[8];                                      /* bytes 12 to 19 */
  uint8_t process_type;                                            /* byte 20 */
  uint8_t quote_number[6];                                         /* bytes 21 to 26 */
  uint8_t original_quote_number[6];                                /* bytes 27 to 32 */
  uint8_t original_quote_price[9];                                 /* bytes 33 to 41 */
  uint8_t bidask_type;                                             /* byte 42 */
  uint8_t price[9];                                                /* bytes 43 to 51 */
  uint8_t quantity[10];                                            /* bytes 52 to 61 */
  uint8_t subscription_time[6];                                    /* bytes 62 to 67 */
  uint8_t total_remaining_quantity_of_ask[10];                     /* bytes 68 to 77 */
  uint8_t total_remaining_quantity_of_bid[10];                     /* bytes 78 to 87 */
  uint8_t ask_best_order[9];                                       /* bytes 88 to 96 */
  uint8_t remaining_quantity_of_ask_best_order[10];                /* bytes 97 to 106 */
  uint8_t bid_best_order[9];                                       /* bytes 107 to 115 */
  uint8_t remaining_quantity_of_bid_best_order[10];                /* bytes 116 to 125 */
  uint8_t price_compare_remaining_quantity_of_order[10];           /* bytes 126 to 135 */
  uint8_t original_price_compare_remaining_quantity_of_order[10];  /* bytes 136 to 145 */
  uint8_t securities_company_number[3];                            /* bytes 146 to 148 */
  uint8_t branch_name[12];                                         /* bytes 149 to 160 */
  uint8_t filler_33[33];                                           /* bytes 161 to 193 */
  uint8_t end_keyword;                                             /* byte 194 */
} KOtcQuoteMessage;

/* any K Otc Quote Message at all: every byte one the checker chooses */
static void any_k_otc_quote_message(KOtcQuoteMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = arbitrary(); }
  record->process_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->quote_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->original_quote_number[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->original_quote_price[i] = arbitrary(); }
  record->bidask_type = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->subscription_time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->total_remaining_quantity_of_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->total_remaining_quantity_of_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->ask_best_order[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->remaining_quantity_of_ask_best_order[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->bid_best_order[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->remaining_quantity_of_bid_best_order[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price_compare_remaining_quantity_of_order[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->original_price_compare_remaining_quantity_of_order[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->securities_company_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->branch_name[i] = arbitrary(); }
  for (size_t i = 0; i < 33; i++) { record->filler_33[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* K Otc Quote Message to the wire: 195 bytes from at, returning where the next byte goes */
static size_t encode_k_otc_quote_message(const KOtcQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->data_seq_number[i]; }
  wire[at++] = record->process_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->quote_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->original_quote_number[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->original_quote_price[i]; }
  wire[at++] = record->bidask_type;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->subscription_time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->total_remaining_quantity_of_ask[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->total_remaining_quantity_of_bid[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->ask_best_order[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->remaining_quantity_of_ask_best_order[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->bid_best_order[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->remaining_quantity_of_bid_best_order[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price_compare_remaining_quantity_of_order[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->original_price_compare_remaining_quantity_of_order[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->securities_company_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->branch_name[i]; }
  for (size_t i = 0; i < 33; i++) { wire[at++] = record->filler_33[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* K Otc Quote Message off the wire: 195 bytes from at, returning where the next byte lies */
static size_t decode_k_otc_quote_message(KOtcQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = wire[at++]; }
  record->process_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->quote_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->original_quote_number[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->original_quote_price[i] = wire[at++]; }
  record->bidask_type = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->subscription_time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->total_remaining_quantity_of_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->total_remaining_quantity_of_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->ask_best_order[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->remaining_quantity_of_ask_best_order[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->bid_best_order[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->remaining_quantity_of_bid_best_order[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price_compare_remaining_quantity_of_order[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->original_price_compare_remaining_quantity_of_order[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->securities_company_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->branch_name[i] = wire[at++]; }
  for (size_t i = 0; i < 33; i++) { record->filler_33[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of K Otc Quote Message is what was written, byte for byte */
static void equal_k_otc_quote_message(const KOtcQuoteMessage *read, const KOtcQuoteMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->data_seq_number[i] == written->data_seq_number[i]); }
  assert(read->process_type == written->process_type);
  for (size_t i = 0; i < 6; i++) { assert(read->quote_number[i] == written->quote_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->original_quote_number[i] == written->original_quote_number[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->original_quote_price[i] == written->original_quote_price[i]); }
  assert(read->bidask_type == written->bidask_type);
  for (size_t i = 0; i < 9; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->subscription_time[i] == written->subscription_time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->total_remaining_quantity_of_ask[i] == written->total_remaining_quantity_of_ask[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->total_remaining_quantity_of_bid[i] == written->total_remaining_quantity_of_bid[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->ask_best_order[i] == written->ask_best_order[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->remaining_quantity_of_ask_best_order[i] == written->remaining_quantity_of_ask_best_order[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->bid_best_order[i] == written->bid_best_order[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->remaining_quantity_of_bid_best_order[i] == written->remaining_quantity_of_bid_best_order[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price_compare_remaining_quantity_of_order[i] == written->price_compare_remaining_quantity_of_order[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->original_price_compare_remaining_quantity_of_order[i] == written->original_price_compare_remaining_quantity_of_order[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->securities_company_number[i] == written->securities_company_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->branch_name[i] == written->branch_name[i]); }
  for (size_t i = 0; i < 33; i++) { assert(read->filler_33[i] == written->filler_33[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* K Otc Quote Message: written and read back, then read and written back */
static void check_k_otc_quote_message(void) {
  KOtcQuoteMessage sent;
  KOtcQuoteMessage got;
  uint8_t wire[195];
  uint8_t again[195];

  any_k_otc_quote_message(&sent);
  assert(encode_k_otc_quote_message(&sent, wire, 0) == 195);
  assert(decode_k_otc_quote_message(&got, wire, 0) == 195);
  equal_k_otc_quote_message(&got, &sent);

  for (size_t i = 0; i < 195; i++) { wire[i] = arbitrary(); }
  assert(decode_k_otc_quote_message(&got, wire, 0) == 195);
  assert(encode_k_otc_quote_message(&got, again, 0) == 195);
  for (size_t i = 0; i < 195; i++) { assert(again[i] == wire[i]); }
}

/* ---- K Otc Order Filled Message: 245 bytes ----------------------------------- */

/* K-OTC Order Filled. Trade prints with running totals, high/low, weighted average price, and previous-day comparison. */
typedef struct {
  uint8_t isin[12];                                             /* bytes 0 to 11 */
  uint8_t data_seq_number[8];                                   /* bytes 12 to 19 */
  uint8_t trading_number[6];                                    /* bytes 20 to 25 */
  uint8_t trading_price[9];                                     /* bytes 26 to 34 */
  uint8_t trading_volume_short[10];                             /* bytes 35 to 44 */
  uint8_t trading_time[6];                                      /* bytes 45 to 50 */
  uint8_t ask_quote_number[6];                                  /* bytes 51 to 56 */
  uint8_t bid_quote_number[6];                                  /* bytes 57 to 62 */
  uint8_t high_price[9];                                        /* bytes 63 to 71 */
  uint8_t low_price[9];                                         /* bytes 72 to 80 */
  uint8_t weighted_average_stock_price[9];                      /* bytes 81 to 89 */
  uint8_t total_trading_accumulated_volume[12];                 /* bytes 90 to 101 */
  uint8_t total_trading_accumulated_value[14];                  /* bytes 102 to 115 */
  uint8_t total_remaining_quantity_of_ask[10];                  /* bytes 116 to 125 */
  uint8_t total_remaining_quantity_of_bid[10];                  /* bytes 126 to 135 */
  uint8_t best_ask_order[9];                                    /* bytes 136 to 144 */
  uint8_t remaining_quantity_of_best_ask_order[10];             /* bytes 145 to 154 */
  uint8_t best_bid_order[9];                                    /* bytes 155 to 163 */
  uint8_t remaining_quantity_of_best_bid_order[10];             /* bytes 164 to 173 */
  uint8_t compared_to_previous_day_type;                        /* byte 174 */
  uint8_t compared_to_previous_day[9];                          /* bytes 175 to 183 */
  uint8_t trading_price_compare_remaining_quantity_of_ask[10];  /* bytes 184 to 193 */
  uint8_t trading_price_compare_remaining_quantity_of_bid[10];  /* bytes 194 to 203 */
  uint8_t filler_40[40];                                        /* bytes 204 to 243 */
  uint8_t end_keyword;                                          /* byte 244 */
} KOtcOrderFilledMessage;

/* any K Otc Order Filled Message at all: every byte one the checker chooses */
static void any_k_otc_order_filled_message(KOtcOrderFilledMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->trading_number[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_volume_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->trading_time[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->ask_quote_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->bid_quote_number[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->weighted_average_stock_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->total_trading_accumulated_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->total_trading_accumulated_value[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->total_remaining_quantity_of_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->total_remaining_quantity_of_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->best_ask_order[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->remaining_quantity_of_best_ask_order[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->best_bid_order[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->remaining_quantity_of_best_bid_order[i] = arbitrary(); }
  record->compared_to_previous_day_type = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->compared_to_previous_day[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_price_compare_remaining_quantity_of_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trading_price_compare_remaining_quantity_of_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->filler_40[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* K Otc Order Filled Message to the wire: 245 bytes from at, returning where the next byte goes */
static size_t encode_k_otc_order_filled_message(const KOtcOrderFilledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->data_seq_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trading_number[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_volume_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trading_time[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->ask_quote_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->bid_quote_number[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->weighted_average_stock_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->total_trading_accumulated_volume[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->total_trading_accumulated_value[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->total_remaining_quantity_of_ask[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->total_remaining_quantity_of_bid[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->best_ask_order[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->remaining_quantity_of_best_ask_order[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->best_bid_order[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->remaining_quantity_of_best_bid_order[i]; }
  wire[at++] = record->compared_to_previous_day_type;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->compared_to_previous_day[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_price_compare_remaining_quantity_of_ask[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trading_price_compare_remaining_quantity_of_bid[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->filler_40[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* K Otc Order Filled Message off the wire: 245 bytes from at, returning where the next byte lies */
static size_t decode_k_otc_order_filled_message(KOtcOrderFilledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->trading_number[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_volume_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->trading_time[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->ask_quote_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->bid_quote_number[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->weighted_average_stock_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->total_trading_accumulated_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->total_trading_accumulated_value[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->total_remaining_quantity_of_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->total_remaining_quantity_of_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->best_ask_order[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->remaining_quantity_of_best_ask_order[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->best_bid_order[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->remaining_quantity_of_best_bid_order[i] = wire[at++]; }
  record->compared_to_previous_day_type = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->compared_to_previous_day[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_price_compare_remaining_quantity_of_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trading_price_compare_remaining_quantity_of_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->filler_40[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of K Otc Order Filled Message is what was written, byte for byte */
static void equal_k_otc_order_filled_message(const KOtcOrderFilledMessage *read, const KOtcOrderFilledMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->data_seq_number[i] == written->data_seq_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->trading_number[i] == written->trading_number[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_volume_short[i] == written->trading_volume_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->trading_time[i] == written->trading_time[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->ask_quote_number[i] == written->ask_quote_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->bid_quote_number[i] == written->bid_quote_number[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->weighted_average_stock_price[i] == written->weighted_average_stock_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->total_trading_accumulated_volume[i] == written->total_trading_accumulated_volume[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->total_trading_accumulated_value[i] == written->total_trading_accumulated_value[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->total_remaining_quantity_of_ask[i] == written->total_remaining_quantity_of_ask[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->total_remaining_quantity_of_bid[i] == written->total_remaining_quantity_of_bid[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->best_ask_order[i] == written->best_ask_order[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->remaining_quantity_of_best_ask_order[i] == written->remaining_quantity_of_best_ask_order[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->best_bid_order[i] == written->best_bid_order[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->remaining_quantity_of_best_bid_order[i] == written->remaining_quantity_of_best_bid_order[i]); }
  assert(read->compared_to_previous_day_type == written->compared_to_previous_day_type);
  for (size_t i = 0; i < 9; i++) { assert(read->compared_to_previous_day[i] == written->compared_to_previous_day[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_price_compare_remaining_quantity_of_ask[i] == written->trading_price_compare_remaining_quantity_of_ask[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trading_price_compare_remaining_quantity_of_bid[i] == written->trading_price_compare_remaining_quantity_of_bid[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->filler_40[i] == written->filler_40[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* K Otc Order Filled Message: written and read back, then read and written back */
static void check_k_otc_order_filled_message(void) {
  KOtcOrderFilledMessage sent;
  KOtcOrderFilledMessage got;
  uint8_t wire[245];
  uint8_t again[245];

  any_k_otc_order_filled_message(&sent);
  assert(encode_k_otc_order_filled_message(&sent, wire, 0) == 245);
  assert(decode_k_otc_order_filled_message(&got, wire, 0) == 245);
  equal_k_otc_order_filled_message(&got, &sent);

  for (size_t i = 0; i < 245; i++) { wire[i] = arbitrary(); }
  assert(decode_k_otc_order_filled_message(&got, wire, 0) == 245);
  assert(encode_k_otc_order_filled_message(&got, again, 0) == 245);
  for (size_t i = 0; i < 245; i++) { assert(again[i] == wire[i]); }
}

/* ---- Otc Bond Traded Info Message: 105 bytes --------------------------------- */

/* OTC Bond Traded Information. Reports today's or prior-day trading history with volume, pretax unit price, yield, settlement date, and FX category. */
typedef struct {
  uint8_t isin[12];                         /* bytes 0 to 11 */
  uint8_t subcategory[2];                   /* bytes 12 to 13 */
  uint8_t trading_date[8];                  /* bytes 14 to 21 */
  uint8_t registered_time[6];               /* bytes 22 to 27 */
  uint8_t process_category;                 /* byte 28 */
  uint8_t registered_number[8];             /* bytes 29 to 36 */
  uint8_t originally_registered_number[8];  /* bytes 37 to 44 */
  uint8_t trading_type_category;            /* byte 45 */
  uint8_t volume[16];                       /* bytes 46 to 61 */
  uint8_t pretax_unit_price[8];             /* bytes 62 to 69 */
  uint8_t pretax_yield[8];                  /* bytes 70 to 77 */
  uint8_t settlement_date_otc[8];           /* bytes 78 to 85 */
  uint8_t market_base_rate[8];              /* bytes 86 to 93 */
  uint8_t fx_category;                      /* byte 94 */
  uint8_t based_fx[8];                      /* bytes 95 to 102 */
  uint8_t trading_category;                 /* byte 103 */
  uint8_t end_keyword;                      /* byte 104 */
} OtcBondTradedInfoMessage;

/* any Otc Bond Traded Info Message at all: every byte one the checker chooses */
static void any_otc_bond_traded_info_message(OtcBondTradedInfoMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->subcategory[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->registered_time[i] = arbitrary(); }
  record->process_category = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->registered_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->originally_registered_number[i] = arbitrary(); }
  record->trading_type_category = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pretax_unit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pretax_yield[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_date_otc[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_base_rate[i] = arbitrary(); }
  record->fx_category = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->based_fx[i] = arbitrary(); }
  record->trading_category = arbitrary();
  record->end_keyword = arbitrary();
}

/* Otc Bond Traded Info Message to the wire: 105 bytes from at, returning where the next byte goes */
static size_t encode_otc_bond_traded_info_message(const OtcBondTradedInfoMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->subcategory[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->registered_time[i]; }
  wire[at++] = record->process_category;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->registered_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->originally_registered_number[i]; }
  wire[at++] = record->trading_type_category;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pretax_unit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pretax_yield[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_date_otc[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_base_rate[i]; }
  wire[at++] = record->fx_category;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->based_fx[i]; }
  wire[at++] = record->trading_category;
  wire[at++] = record->end_keyword;

  return at;
}

/* Otc Bond Traded Info Message off the wire: 105 bytes from at, returning where the next byte lies */
static size_t decode_otc_bond_traded_info_message(OtcBondTradedInfoMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->subcategory[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->registered_time[i] = wire[at++]; }
  record->process_category = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->registered_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->originally_registered_number[i] = wire[at++]; }
  record->trading_type_category = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pretax_unit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pretax_yield[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_date_otc[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_base_rate[i] = wire[at++]; }
  record->fx_category = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->based_fx[i] = wire[at++]; }
  record->trading_category = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Otc Bond Traded Info Message is what was written, byte for byte */
static void equal_otc_bond_traded_info_message(const OtcBondTradedInfoMessage *read, const OtcBondTradedInfoMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->subcategory[i] == written->subcategory[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_date[i] == written->trading_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->registered_time[i] == written->registered_time[i]); }
  assert(read->process_category == written->process_category);
  for (size_t i = 0; i < 8; i++) { assert(read->registered_number[i] == written->registered_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->originally_registered_number[i] == written->originally_registered_number[i]); }
  assert(read->trading_type_category == written->trading_type_category);
  for (size_t i = 0; i < 16; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pretax_unit_price[i] == written->pretax_unit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pretax_yield[i] == written->pretax_yield[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_date_otc[i] == written->settlement_date_otc[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_base_rate[i] == written->market_base_rate[i]); }
  assert(read->fx_category == written->fx_category);
  for (size_t i = 0; i < 8; i++) { assert(read->based_fx[i] == written->based_fx[i]); }
  assert(read->trading_category == written->trading_category);
  assert(read->end_keyword == written->end_keyword);
}

/* Otc Bond Traded Info Message: written and read back, then read and written back */
static void check_otc_bond_traded_info_message(void) {
  OtcBondTradedInfoMessage sent;
  OtcBondTradedInfoMessage got;
  uint8_t wire[105];
  uint8_t again[105];

  any_otc_bond_traded_info_message(&sent);
  assert(encode_otc_bond_traded_info_message(&sent, wire, 0) == 105);
  assert(decode_otc_bond_traded_info_message(&got, wire, 0) == 105);
  equal_otc_bond_traded_info_message(&got, &sent);

  for (size_t i = 0; i < 105; i++) { wire[i] = arbitrary(); }
  assert(decode_otc_bond_traded_info_message(&got, wire, 0) == 105);
  assert(encode_otc_bond_traded_info_message(&got, again, 0) == 105);
  for (size_t i = 0; i < 105; i++) { assert(again[i] == wire[i]); }
}

/* ---- Otc Bond Trades Per Institution Message: 105 bytes ---------------------- */

/* OTC Bond trade aggregates per institution. Reports bid and ask yields and trading volumes/values per institution code and bond type. */
typedef struct {
  uint8_t data_process_category;               /* byte 0 */
  uint8_t date[8];                             /* bytes 1 to 8 */
  uint8_t institution_code[4];                 /* bytes 9 to 12 */
  uint8_t bond_type_code[4];                   /* bytes 13 to 16 */
  uint8_t ask_yield_institution[8];            /* bytes 17 to 24 */
  uint8_t ask_trading_volume_institution[15];  /* bytes 25 to 39 */
  uint8_t ask_trading_value_institution[15];   /* bytes 40 to 54 */
  uint8_t bid_yield_institution[8];            /* bytes 55 to 62 */
  uint8_t bid_trading_volume_institution[15];  /* bytes 63 to 77 */
  uint8_t bid_trading_value_institution[15];   /* bytes 78 to 92 */
  uint8_t filler_11[11];                       /* bytes 93 to 103 */
  uint8_t end_keyword;                         /* byte 104 */
} OtcBondTradesPerInstitutionMessage;

/* any Otc Bond Trades Per Institution Message at all: every byte one the checker chooses */
static void any_otc_bond_trades_per_institution_message(OtcBondTradesPerInstitutionMessage *record) {
  record->data_process_category = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->institution_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bond_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_yield_institution[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_trading_volume_institution[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->ask_trading_value_institution[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_yield_institution[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_trading_volume_institution[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->bid_trading_value_institution[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->filler_11[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Otc Bond Trades Per Institution Message to the wire: 105 bytes from at, returning where the next byte goes */
static size_t encode_otc_bond_trades_per_institution_message(const OtcBondTradesPerInstitutionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->data_process_category;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->institution_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bond_type_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_yield_institution[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_trading_volume_institution[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->ask_trading_value_institution[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_yield_institution[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_trading_volume_institution[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->bid_trading_value_institution[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->filler_11[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Otc Bond Trades Per Institution Message off the wire: 105 bytes from at, returning where the next byte lies */
static size_t decode_otc_bond_trades_per_institution_message(OtcBondTradesPerInstitutionMessage *record, const uint8_t *wire, size_t at) {
  record->data_process_category = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->institution_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bond_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_yield_institution[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_trading_volume_institution[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->ask_trading_value_institution[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_yield_institution[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_trading_volume_institution[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->bid_trading_value_institution[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->filler_11[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Otc Bond Trades Per Institution Message is what was written, byte for byte */
static void equal_otc_bond_trades_per_institution_message(const OtcBondTradesPerInstitutionMessage *read, const OtcBondTradesPerInstitutionMessage *written) {
  assert(read->data_process_category == written->data_process_category);
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->institution_code[i] == written->institution_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bond_type_code[i] == written->bond_type_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_yield_institution[i] == written->ask_yield_institution[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_trading_volume_institution[i] == written->ask_trading_volume_institution[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->ask_trading_value_institution[i] == written->ask_trading_value_institution[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_yield_institution[i] == written->bid_yield_institution[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_trading_volume_institution[i] == written->bid_trading_volume_institution[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->bid_trading_value_institution[i] == written->bid_trading_value_institution[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->filler_11[i] == written->filler_11[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Otc Bond Trades Per Institution Message: written and read back, then read and written back */
static void check_otc_bond_trades_per_institution_message(void) {
  OtcBondTradesPerInstitutionMessage sent;
  OtcBondTradesPerInstitutionMessage got;
  uint8_t wire[105];
  uint8_t again[105];

  any_otc_bond_trades_per_institution_message(&sent);
  assert(encode_otc_bond_trades_per_institution_message(&sent, wire, 0) == 105);
  assert(decode_otc_bond_trades_per_institution_message(&got, wire, 0) == 105);
  equal_otc_bond_trades_per_institution_message(&got, &sent);

  for (size_t i = 0; i < 105; i++) { wire[i] = arbitrary(); }
  assert(decode_otc_bond_trades_per_institution_message(&got, wire, 0) == 105);
  assert(encode_otc_bond_trades_per_institution_message(&got, again, 0) == 105);
  for (size_t i = 0; i < 105; i++) { assert(again[i] == wire[i]); }
}

/* ---- Otc Bond Types Per Investor Message: 135 bytes -------------------------- */

/* OTC Bond trade aggregates per investor category. Bid/ask yields and trading volumes/values per ISIN and investor category. */
typedef struct {
  uint8_t isin[12];                         /* bytes 0 to 11 */
  uint8_t sequence_number[8];               /* bytes 12 to 19 */
  uint8_t trading_date[8];                  /* bytes 20 to 27 */
  uint8_t investor_category[4];             /* bytes 28 to 31 */
  uint8_t ask_yield_investor[10];           /* bytes 32 to 41 */
  uint8_t bid_yield_investor[10];           /* bytes 42 to 51 */
  uint8_t ask_trading_volume_investor[20];  /* bytes 52 to 71 */
  uint8_t bid_trading_volume_investor[20];  /* bytes 72 to 91 */
  uint8_t ask_trading_value_investor[20];   /* bytes 92 to 111 */
  uint8_t bid_trading_value_investor[20];   /* bytes 112 to 131 */
  uint8_t filler_2[2];                      /* bytes 132 to 133 */
  uint8_t end_keyword;                      /* byte 134 */
} OtcBondTypesPerInvestorMessage;

/* any Otc Bond Types Per Investor Message at all: every byte one the checker chooses */
static void any_otc_bond_types_per_investor_message(OtcBondTypesPerInvestorMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->investor_category[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->ask_yield_investor[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->bid_yield_investor[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->ask_trading_volume_investor[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->bid_trading_volume_investor[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->ask_trading_value_investor[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->bid_trading_value_investor[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Otc Bond Types Per Investor Message to the wire: 135 bytes from at, returning where the next byte goes */
static size_t encode_otc_bond_types_per_investor_message(const OtcBondTypesPerInvestorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->investor_category[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->ask_yield_investor[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->bid_yield_investor[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->ask_trading_volume_investor[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->bid_trading_volume_investor[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->ask_trading_value_investor[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->bid_trading_value_investor[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Otc Bond Types Per Investor Message off the wire: 135 bytes from at, returning where the next byte lies */
static size_t decode_otc_bond_types_per_investor_message(OtcBondTypesPerInvestorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->investor_category[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->ask_yield_investor[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->bid_yield_investor[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->ask_trading_volume_investor[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->bid_trading_volume_investor[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->ask_trading_value_investor[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->bid_trading_value_investor[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Otc Bond Types Per Investor Message is what was written, byte for byte */
static void equal_otc_bond_types_per_investor_message(const OtcBondTypesPerInvestorMessage *read, const OtcBondTypesPerInvestorMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_date[i] == written->trading_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->investor_category[i] == written->investor_category[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->ask_yield_investor[i] == written->ask_yield_investor[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->bid_yield_investor[i] == written->bid_yield_investor[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->ask_trading_volume_investor[i] == written->ask_trading_volume_investor[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->bid_trading_volume_investor[i] == written->bid_trading_volume_investor[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->ask_trading_value_investor[i] == written->ask_trading_value_investor[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->bid_trading_value_investor[i] == written->bid_trading_value_investor[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Otc Bond Types Per Investor Message: written and read back, then read and written back */
static void check_otc_bond_types_per_investor_message(void) {
  OtcBondTypesPerInvestorMessage sent;
  OtcBondTypesPerInvestorMessage got;
  uint8_t wire[135];
  uint8_t again[135];

  any_otc_bond_types_per_investor_message(&sent);
  assert(encode_otc_bond_types_per_investor_message(&sent, wire, 0) == 135);
  assert(decode_otc_bond_types_per_investor_message(&got, wire, 0) == 135);
  equal_otc_bond_types_per_investor_message(&got, &sent);

  for (size_t i = 0; i < 135; i++) { wire[i] = arbitrary(); }
  assert(decode_otc_bond_types_per_investor_message(&got, wire, 0) == 135);
  assert(encode_otc_bond_types_per_investor_message(&got, again, 0) == 135);
  for (size_t i = 0; i < 135; i++) { assert(again[i] == wire[i]); }
}

/* ---- K Bond Message: 145 bytes ----------------------------------------------- */

/* K-BOND dissemination. Quotes and trades with profit rate or price, contract category, settlement date, and replacement order details. */
typedef struct {
  uint8_t isin[12];                         /* bytes 0 to 11 */
  uint8_t data_small_category[2];           /* bytes 12 to 13 */
  uint8_t data_source_type;                 /* byte 14 */
  uint8_t sequence_number[8];               /* bytes 15 to 22 */
  uint8_t original_sequence_number[8];      /* bytes 23 to 30 */
  uint8_t replacement_type;                 /* byte 31 */
  uint8_t previous_isin_of_replacement[8];  /* bytes 32 to 39 */
  uint8_t input_date[8];                    /* bytes 40 to 47 */
  uint8_t quotes_offer_time[6];             /* bytes 48 to 53 */
  uint8_t bond_type_name[40];               /* bytes 54 to 93 */
  uint8_t change_category;                  /* byte 94 */
  uint8_t market_data_type;                 /* byte 95 */
  uint8_t profit_rate_quotes_trading[8];    /* bytes 96 to 103 */
  uint8_t price_quotes_trading[8];          /* bytes 104 to 111 */
  uint8_t contract_category;                /* byte 112 */
  uint8_t quotes_amount[16];                /* bytes 113 to 128 */
  uint8_t contract_date[2];                 /* bytes 129 to 130 */
  uint8_t settlement_date_k_bond[2];        /* bytes 131 to 132 */
  uint8_t filler_11[11];                    /* bytes 133 to 143 */
  uint8_t end_keyword;                      /* byte 144 */
} KBondMessage;

/* any K Bond Message at all: every byte one the checker chooses */
static void any_k_bond_message(KBondMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->data_small_category[i] = arbitrary(); }
  record->data_source_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_sequence_number[i] = arbitrary(); }
  record->replacement_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->previous_isin_of_replacement[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->input_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->quotes_offer_time[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->bond_type_name[i] = arbitrary(); }
  record->change_category = arbitrary();
  record->market_data_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->profit_rate_quotes_trading[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_quotes_trading[i] = arbitrary(); }
  record->contract_category = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->quotes_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->contract_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->settlement_date_k_bond[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->filler_11[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* K Bond Message to the wire: 145 bytes from at, returning where the next byte goes */
static size_t encode_k_bond_message(const KBondMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->data_small_category[i]; }
  wire[at++] = record->data_source_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_sequence_number[i]; }
  wire[at++] = record->replacement_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_isin_of_replacement[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->input_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->quotes_offer_time[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->bond_type_name[i]; }
  wire[at++] = record->change_category;
  wire[at++] = record->market_data_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->profit_rate_quotes_trading[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_quotes_trading[i]; }
  wire[at++] = record->contract_category;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->quotes_amount[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->contract_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->settlement_date_k_bond[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->filler_11[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* K Bond Message off the wire: 145 bytes from at, returning where the next byte lies */
static size_t decode_k_bond_message(KBondMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->data_small_category[i] = wire[at++]; }
  record->data_source_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_sequence_number[i] = wire[at++]; }
  record->replacement_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->previous_isin_of_replacement[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->input_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->quotes_offer_time[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->bond_type_name[i] = wire[at++]; }
  record->change_category = wire[at++];
  record->market_data_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->profit_rate_quotes_trading[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_quotes_trading[i] = wire[at++]; }
  record->contract_category = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->quotes_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->contract_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->settlement_date_k_bond[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->filler_11[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of K Bond Message is what was written, byte for byte */
static void equal_k_bond_message(const KBondMessage *read, const KBondMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->data_small_category[i] == written->data_small_category[i]); }
  assert(read->data_source_type == written->data_source_type);
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_sequence_number[i] == written->original_sequence_number[i]); }
  assert(read->replacement_type == written->replacement_type);
  for (size_t i = 0; i < 8; i++) { assert(read->previous_isin_of_replacement[i] == written->previous_isin_of_replacement[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->input_date[i] == written->input_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->quotes_offer_time[i] == written->quotes_offer_time[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->bond_type_name[i] == written->bond_type_name[i]); }
  assert(read->change_category == written->change_category);
  assert(read->market_data_type == written->market_data_type);
  for (size_t i = 0; i < 8; i++) { assert(read->profit_rate_quotes_trading[i] == written->profit_rate_quotes_trading[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_quotes_trading[i] == written->price_quotes_trading[i]); }
  assert(read->contract_category == written->contract_category);
  for (size_t i = 0; i < 16; i++) { assert(read->quotes_amount[i] == written->quotes_amount[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->contract_date[i] == written->contract_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->settlement_date_k_bond[i] == written->settlement_date_k_bond[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->filler_11[i] == written->filler_11[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* K Bond Message: written and read back, then read and written back */
static void check_k_bond_message(void) {
  KBondMessage sent;
  KBondMessage got;
  uint8_t wire[145];
  uint8_t again[145];

  any_k_bond_message(&sent);
  assert(encode_k_bond_message(&sent, wire, 0) == 145);
  assert(decode_k_bond_message(&got, wire, 0) == 145);
  equal_k_bond_message(&got, &sent);

  for (size_t i = 0; i < 145; i++) { wire[i] = arbitrary(); }
  assert(decode_k_bond_message(&got, wire, 0) == 145);
  assert(encode_k_bond_message(&got, again, 0) == 145);
  for (size_t i = 0; i < 145; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mkf Index Message: 72 bytes --------------------------------------------- */

/* MKF Index real-time message. Reports current index value, sign and magnitude of change against the previous day, and accumulated trading volume and value for one MKF index identifier. */
typedef struct {
  uint8_t index_id[6];              /* bytes 0 to 5 */
  uint8_t isin[12];                 /* bytes 6 to 17 */
  uint8_t time[6];                  /* bytes 18 to 23 */
  uint8_t index[9];                 /* bytes 24 to 32 */
  uint8_t sign;                     /* byte 33 */
  uint8_t comparison[9];            /* bytes 34 to 42 */
  uint8_t trading_volume_long[12];  /* bytes 43 to 54 */
  uint8_t trading_value[12];        /* bytes 55 to 66 */
  uint8_t filler_4[4];              /* bytes 67 to 70 */
  uint8_t end_keyword;              /* byte 71 */
} MkfIndexMessage;

/* any Mkf Index Message at all: every byte one the checker chooses */
static void any_mkf_index_message(MkfIndexMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->index[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->comparison[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->trading_volume_long[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Mkf Index Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_mkf_index_message(const MkfIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->comparison[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trading_volume_long[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trading_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Mkf Index Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_mkf_index_message(MkfIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->index[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->comparison[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->trading_volume_long[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Mkf Index Message is what was written, byte for byte */
static void equal_mkf_index_message(const MkfIndexMessage *read, const MkfIndexMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->index[i] == written->index[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 9; i++) { assert(read->comparison[i] == written->comparison[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->trading_volume_long[i] == written->trading_volume_long[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->trading_value[i] == written->trading_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Mkf Index Message: written and read back, then read and written back */
static void check_mkf_index_message(void) {
  MkfIndexMessage sent;
  MkfIndexMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_mkf_index_message(&sent);
  assert(encode_mkf_index_message(&sent, wire, 0) == 72);
  assert(decode_mkf_index_message(&got, wire, 0) == 72);
  equal_mkf_index_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_mkf_index_message(&got, wire, 0) == 72);
  assert(encode_mkf_index_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mkf Index Jpy Message: 72 bytes ----------------------------------------- */

/* MKF Index real-time message with the Japanese Yen exchange rate reflected. Identical field layout to the Mkf Index Message. */
typedef struct {
  uint8_t index_id[6];              /* bytes 0 to 5 */
  uint8_t isin[12];                 /* bytes 6 to 17 */
  uint8_t time[6];                  /* bytes 18 to 23 */
  uint8_t index[9];                 /* bytes 24 to 32 */
  uint8_t sign;                     /* byte 33 */
  uint8_t comparison[9];            /* bytes 34 to 42 */
  uint8_t trading_volume_long[12];  /* bytes 43 to 54 */
  uint8_t trading_value[12];        /* bytes 55 to 66 */
  uint8_t filler_4[4];              /* bytes 67 to 70 */
  uint8_t end_keyword;              /* byte 71 */
} MkfIndexJpyMessage;

/* any Mkf Index Jpy Message at all: every byte one the checker chooses */
static void any_mkf_index_jpy_message(MkfIndexJpyMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->index[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->comparison[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->trading_volume_long[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Mkf Index Jpy Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_mkf_index_jpy_message(const MkfIndexJpyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->comparison[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trading_volume_long[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trading_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Mkf Index Jpy Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_mkf_index_jpy_message(MkfIndexJpyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->index[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->comparison[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->trading_volume_long[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Mkf Index Jpy Message is what was written, byte for byte */
static void equal_mkf_index_jpy_message(const MkfIndexJpyMessage *read, const MkfIndexJpyMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->index[i] == written->index[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 9; i++) { assert(read->comparison[i] == written->comparison[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->trading_volume_long[i] == written->trading_volume_long[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->trading_value[i] == written->trading_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Mkf Index Jpy Message: written and read back, then read and written back */
static void check_mkf_index_jpy_message(void) {
  MkfIndexJpyMessage sent;
  MkfIndexJpyMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_mkf_index_jpy_message(&sent);
  assert(encode_mkf_index_jpy_message(&sent, wire, 0) == 72);
  assert(decode_mkf_index_jpy_message(&got, wire, 0) == 72);
  equal_mkf_index_jpy_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_mkf_index_jpy_message(&got, wire, 0) == 72);
  assert(encode_mkf_index_jpy_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Wisefn Index Message: 72 bytes ------------------------------------------ */

/* WISEfn equity index real-time message. Identical field layout to the Mkf Index Message. */
typedef struct {
  uint8_t index_id[6];              /* bytes 0 to 5 */
  uint8_t isin[12];                 /* bytes 6 to 17 */
  uint8_t time[6];                  /* bytes 18 to 23 */
  uint8_t index[9];                 /* bytes 24 to 32 */
  uint8_t sign;                     /* byte 33 */
  uint8_t comparison[9];            /* bytes 34 to 42 */
  uint8_t trading_volume_long[12];  /* bytes 43 to 54 */
  uint8_t trading_value[12];        /* bytes 55 to 66 */
  uint8_t filler_4[4];              /* bytes 67 to 70 */
  uint8_t end_keyword;              /* byte 71 */
} WisefnIndexMessage;

/* any Wisefn Index Message at all: every byte one the checker chooses */
static void any_wisefn_index_message(WisefnIndexMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->index[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->comparison[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->trading_volume_long[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Wisefn Index Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_wisefn_index_message(const WisefnIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->comparison[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trading_volume_long[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trading_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Wisefn Index Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_wisefn_index_message(WisefnIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->index[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->comparison[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->trading_volume_long[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Wisefn Index Message is what was written, byte for byte */
static void equal_wisefn_index_message(const WisefnIndexMessage *read, const WisefnIndexMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->index[i] == written->index[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 9; i++) { assert(read->comparison[i] == written->comparison[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->trading_volume_long[i] == written->trading_volume_long[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->trading_value[i] == written->trading_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Wisefn Index Message: written and read back, then read and written back */
static void check_wisefn_index_message(void) {
  WisefnIndexMessage sent;
  WisefnIndexMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_wisefn_index_message(&sent);
  assert(encode_wisefn_index_message(&sent, wire, 0) == 72);
  assert(decode_wisefn_index_message(&got, wire, 0) == 72);
  equal_wisefn_index_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_wisefn_index_message(&got, wire, 0) == 72);
  assert(encode_wisefn_index_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Kis Index Message: 72 bytes --------------------------------------------- */

/* KIS equity index real-time message. Identical field layout to the Mkf Index Message. */
typedef struct {
  uint8_t index_id[6];              /* bytes 0 to 5 */
  uint8_t isin[12];                 /* bytes 6 to 17 */
  uint8_t time[6];                  /* bytes 18 to 23 */
  uint8_t index[9];                 /* bytes 24 to 32 */
  uint8_t sign;                     /* byte 33 */
  uint8_t comparison[9];            /* bytes 34 to 42 */
  uint8_t trading_volume_long[12];  /* bytes 43 to 54 */
  uint8_t trading_value[12];        /* bytes 55 to 66 */
  uint8_t filler_4[4];              /* bytes 67 to 70 */
  uint8_t end_keyword;              /* byte 71 */
} KisIndexMessage;

/* any Kis Index Message at all: every byte one the checker chooses */
static void any_kis_index_message(KisIndexMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->index[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->comparison[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->trading_volume_long[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Kis Index Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_kis_index_message(const KisIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->index[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->comparison[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trading_volume_long[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trading_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Kis Index Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_kis_index_message(KisIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->index[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->comparison[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->trading_volume_long[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Kis Index Message is what was written, byte for byte */
static void equal_kis_index_message(const KisIndexMessage *read, const KisIndexMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->index[i] == written->index[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 9; i++) { assert(read->comparison[i] == written->comparison[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->trading_volume_long[i] == written->trading_volume_long[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->trading_value[i] == written->trading_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Kis Index Message: written and read back, then read and written back */
static void check_kis_index_message(void) {
  KisIndexMessage sent;
  KisIndexMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_kis_index_message(&sent);
  assert(encode_kis_index_message(&sent, wire, 0) == 72);
  assert(decode_kis_index_message(&got, wire, 0) == 72);
  equal_kis_index_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_kis_index_message(&got, wire, 0) == 72);
  assert(encode_kis_index_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mkf Bond Index Message: 109 bytes --------------------------------------- */

/* MKF Bond Index real-time message. Carries total profit / clean price / market price / call and zero re-investment indices, futures basis price, duration, convexity, and YTM for one bond index identifier. */
typedef struct {
  uint8_t filler_4[4];                   /* bytes 0 to 3 */
  uint8_t index_id[6];                   /* bytes 4 to 9 */
  uint8_t standard_date[8];              /* bytes 10 to 17 */
  uint8_t standard_time[6];              /* bytes 18 to 23 */
  uint8_t total_profit_index[10];        /* bytes 24 to 33 */
  uint8_t clean_price_index[10];         /* bytes 34 to 43 */
  uint8_t market_price_index[10];        /* bytes 44 to 53 */
  uint8_t call_re_investment_index[10];  /* bytes 54 to 63 */
  uint8_t zero_re_investment_index[10];  /* bytes 64 to 73 */
  uint8_t futures_basis_price[9];        /* bytes 74 to 82 */
  uint8_t average_duration_nullable[6];  /* bytes 83 to 88 */
  uint8_t average_convexity[6];          /* bytes 89 to 94 */
  uint8_t average_ytm[6];                /* bytes 95 to 100 */
  uint8_t average_forward_ytm[6];        /* bytes 101 to 106 */
  uint8_t filler_1;                      /* byte 107 */
  uint8_t end_keyword;                   /* byte 108 */
} MkfBondIndexMessage;

/* any Mkf Bond Index Message at all: every byte one the checker chooses */
static void any_mkf_bond_index_message(MkfBondIndexMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->standard_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->standard_time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->total_profit_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->clean_price_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->market_price_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->call_re_investment_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->zero_re_investment_index[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->futures_basis_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_duration_nullable[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_convexity[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_ytm[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_forward_ytm[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  record->end_keyword = arbitrary();
}

/* Mkf Bond Index Message to the wire: 109 bytes from at, returning where the next byte goes */
static size_t encode_mkf_bond_index_message(const MkfBondIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->standard_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->standard_time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->total_profit_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->clean_price_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->market_price_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->call_re_investment_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->zero_re_investment_index[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->futures_basis_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_duration_nullable[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_convexity[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_ytm[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_forward_ytm[i]; }
  wire[at++] = record->filler_1;
  wire[at++] = record->end_keyword;

  return at;
}

/* Mkf Bond Index Message off the wire: 109 bytes from at, returning where the next byte lies */
static size_t decode_mkf_bond_index_message(MkfBondIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->standard_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->standard_time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->total_profit_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->clean_price_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->market_price_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->call_re_investment_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->zero_re_investment_index[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->futures_basis_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_duration_nullable[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_convexity[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_ytm[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_forward_ytm[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Mkf Bond Index Message is what was written, byte for byte */
static void equal_mkf_bond_index_message(const MkfBondIndexMessage *read, const MkfBondIndexMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->standard_date[i] == written->standard_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->standard_time[i] == written->standard_time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->total_profit_index[i] == written->total_profit_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->clean_price_index[i] == written->clean_price_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->market_price_index[i] == written->market_price_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->call_re_investment_index[i] == written->call_re_investment_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->zero_re_investment_index[i] == written->zero_re_investment_index[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->futures_basis_price[i] == written->futures_basis_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_duration_nullable[i] == written->average_duration_nullable[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_convexity[i] == written->average_convexity[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_ytm[i] == written->average_ytm[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_forward_ytm[i] == written->average_forward_ytm[i]); }
  assert(read->filler_1 == written->filler_1);
  assert(read->end_keyword == written->end_keyword);
}

/* Mkf Bond Index Message: written and read back, then read and written back */
static void check_mkf_bond_index_message(void) {
  MkfBondIndexMessage sent;
  MkfBondIndexMessage got;
  uint8_t wire[109];
  uint8_t again[109];

  any_mkf_bond_index_message(&sent);
  assert(encode_mkf_bond_index_message(&sent, wire, 0) == 109);
  assert(decode_mkf_bond_index_message(&got, wire, 0) == 109);
  equal_mkf_bond_index_message(&got, &sent);

  for (size_t i = 0; i < 109; i++) { wire[i] = arbitrary(); }
  assert(decode_mkf_bond_index_message(&got, wire, 0) == 109);
  assert(encode_mkf_bond_index_message(&got, again, 0) == 109);
  for (size_t i = 0; i < 109; i++) { assert(again[i] == wire[i]); }
}

/* ---- Kis Bond Index Message: 109 bytes --------------------------------------- */

/* KIS Bond Index real-time message. Identical field layout to the Mkf Bond Index Message. */
typedef struct {
  uint8_t filler_4[4];                   /* bytes 0 to 3 */
  uint8_t index_id[6];                   /* bytes 4 to 9 */
  uint8_t standard_date[8];              /* bytes 10 to 17 */
  uint8_t standard_time[6];              /* bytes 18 to 23 */
  uint8_t total_profit_index[10];        /* bytes 24 to 33 */
  uint8_t clean_price_index[10];         /* bytes 34 to 43 */
  uint8_t market_price_index[10];        /* bytes 44 to 53 */
  uint8_t call_re_investment_index[10];  /* bytes 54 to 63 */
  uint8_t zero_re_investment_index[10];  /* bytes 64 to 73 */
  uint8_t futures_basis_price[9];        /* bytes 74 to 82 */
  uint8_t average_duration[6];           /* bytes 83 to 88 */
  uint8_t average_convexity[6];          /* bytes 89 to 94 */
  uint8_t average_ytm[6];                /* bytes 95 to 100 */
  uint8_t average_forward_ytm[6];        /* bytes 101 to 106 */
  uint8_t filler_1;                      /* byte 107 */
  uint8_t end_keyword;                   /* byte 108 */
} KisBondIndexMessage;

/* any Kis Bond Index Message at all: every byte one the checker chooses */
static void any_kis_bond_index_message(KisBondIndexMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->standard_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->standard_time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->total_profit_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->clean_price_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->market_price_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->call_re_investment_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->zero_re_investment_index[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->futures_basis_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_duration[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_convexity[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_ytm[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_forward_ytm[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  record->end_keyword = arbitrary();
}

/* Kis Bond Index Message to the wire: 109 bytes from at, returning where the next byte goes */
static size_t encode_kis_bond_index_message(const KisBondIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->standard_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->standard_time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->total_profit_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->clean_price_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->market_price_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->call_re_investment_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->zero_re_investment_index[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->futures_basis_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_duration[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_convexity[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_ytm[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_forward_ytm[i]; }
  wire[at++] = record->filler_1;
  wire[at++] = record->end_keyword;

  return at;
}

/* Kis Bond Index Message off the wire: 109 bytes from at, returning where the next byte lies */
static size_t decode_kis_bond_index_message(KisBondIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->standard_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->standard_time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->total_profit_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->clean_price_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->market_price_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->call_re_investment_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->zero_re_investment_index[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->futures_basis_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_duration[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_convexity[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_ytm[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_forward_ytm[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Kis Bond Index Message is what was written, byte for byte */
static void equal_kis_bond_index_message(const KisBondIndexMessage *read, const KisBondIndexMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->standard_date[i] == written->standard_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->standard_time[i] == written->standard_time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->total_profit_index[i] == written->total_profit_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->clean_price_index[i] == written->clean_price_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->market_price_index[i] == written->market_price_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->call_re_investment_index[i] == written->call_re_investment_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->zero_re_investment_index[i] == written->zero_re_investment_index[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->futures_basis_price[i] == written->futures_basis_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_duration[i] == written->average_duration[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_convexity[i] == written->average_convexity[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_ytm[i] == written->average_ytm[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_forward_ytm[i] == written->average_forward_ytm[i]); }
  assert(read->filler_1 == written->filler_1);
  assert(read->end_keyword == written->end_keyword);
}

/* Kis Bond Index Message: written and read back, then read and written back */
static void check_kis_bond_index_message(void) {
  KisBondIndexMessage sent;
  KisBondIndexMessage got;
  uint8_t wire[109];
  uint8_t again[109];

  any_kis_bond_index_message(&sent);
  assert(encode_kis_bond_index_message(&sent, wire, 0) == 109);
  assert(decode_kis_bond_index_message(&got, wire, 0) == 109);
  equal_kis_bond_index_message(&got, &sent);

  for (size_t i = 0; i < 109; i++) { wire[i] = arbitrary(); }
  assert(decode_kis_bond_index_message(&got, wire, 0) == 109);
  assert(encode_kis_bond_index_message(&got, again, 0) == 109);
  for (size_t i = 0; i < 109; i++) { assert(again[i] == wire[i]); }
}

/* ---- Kebi Bond Index Message: 109 bytes -------------------------------------- */

/* KEBI Bond Index real-time message. Identical field layout to the Mkf Bond Index Message. */
typedef struct {
  uint8_t filler_4[4];                   /* bytes 0 to 3 */
  uint8_t index_id[6];                   /* bytes 4 to 9 */
  uint8_t standard_date[8];              /* bytes 10 to 17 */
  uint8_t standard_time[6];              /* bytes 18 to 23 */
  uint8_t total_profit_index[10];        /* bytes 24 to 33 */
  uint8_t clean_price_index[10];         /* bytes 34 to 43 */
  uint8_t market_price_index[10];        /* bytes 44 to 53 */
  uint8_t call_re_investment_index[10];  /* bytes 54 to 63 */
  uint8_t zero_re_investment_index[10];  /* bytes 64 to 73 */
  uint8_t futures_basis_price[9];        /* bytes 74 to 82 */
  uint8_t average_duration_nullable[6];  /* bytes 83 to 88 */
  uint8_t average_convexity[6];          /* bytes 89 to 94 */
  uint8_t average_ytm[6];                /* bytes 95 to 100 */
  uint8_t average_forward_ytm[6];        /* bytes 101 to 106 */
  uint8_t filler_1;                      /* byte 107 */
  uint8_t end_keyword;                   /* byte 108 */
} KebiBondIndexMessage;

/* any Kebi Bond Index Message at all: every byte one the checker chooses */
static void any_kebi_bond_index_message(KebiBondIndexMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->standard_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->standard_time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->total_profit_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->clean_price_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->market_price_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->call_re_investment_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->zero_re_investment_index[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->futures_basis_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_duration_nullable[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_convexity[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_ytm[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_forward_ytm[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  record->end_keyword = arbitrary();
}

/* Kebi Bond Index Message to the wire: 109 bytes from at, returning where the next byte goes */
static size_t encode_kebi_bond_index_message(const KebiBondIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->standard_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->standard_time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->total_profit_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->clean_price_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->market_price_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->call_re_investment_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->zero_re_investment_index[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->futures_basis_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_duration_nullable[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_convexity[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_ytm[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_forward_ytm[i]; }
  wire[at++] = record->filler_1;
  wire[at++] = record->end_keyword;

  return at;
}

/* Kebi Bond Index Message off the wire: 109 bytes from at, returning where the next byte lies */
static size_t decode_kebi_bond_index_message(KebiBondIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->standard_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->standard_time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->total_profit_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->clean_price_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->market_price_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->call_re_investment_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->zero_re_investment_index[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->futures_basis_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_duration_nullable[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_convexity[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_ytm[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_forward_ytm[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Kebi Bond Index Message is what was written, byte for byte */
static void equal_kebi_bond_index_message(const KebiBondIndexMessage *read, const KebiBondIndexMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->standard_date[i] == written->standard_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->standard_time[i] == written->standard_time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->total_profit_index[i] == written->total_profit_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->clean_price_index[i] == written->clean_price_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->market_price_index[i] == written->market_price_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->call_re_investment_index[i] == written->call_re_investment_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->zero_re_investment_index[i] == written->zero_re_investment_index[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->futures_basis_price[i] == written->futures_basis_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_duration_nullable[i] == written->average_duration_nullable[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_convexity[i] == written->average_convexity[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_ytm[i] == written->average_ytm[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_forward_ytm[i] == written->average_forward_ytm[i]); }
  assert(read->filler_1 == written->filler_1);
  assert(read->end_keyword == written->end_keyword);
}

/* Kebi Bond Index Message: written and read back, then read and written back */
static void check_kebi_bond_index_message(void) {
  KebiBondIndexMessage sent;
  KebiBondIndexMessage got;
  uint8_t wire[109];
  uint8_t again[109];

  any_kebi_bond_index_message(&sent);
  assert(encode_kebi_bond_index_message(&sent, wire, 0) == 109);
  assert(decode_kebi_bond_index_message(&got, wire, 0) == 109);
  equal_kebi_bond_index_message(&got, &sent);

  for (size_t i = 0; i < 109; i++) { wire[i] = arbitrary(); }
  assert(decode_kebi_bond_index_message(&got, wire, 0) == 109);
  assert(encode_kebi_bond_index_message(&got, again, 0) == 109);
  for (size_t i = 0; i < 109; i++) { assert(again[i] == wire[i]); }
}

/* ---- Kabi Bond Index Message: 109 bytes -------------------------------------- */

/* KABI Bond Index real-time message. Same field layout as the Mkf Bond Index Message; KABI uses standard 100 rather than 10,000 for the various indices. */
typedef struct {
  uint8_t filler_4[4];                      /* bytes 0 to 3 */
  uint8_t index_id[6];                      /* bytes 4 to 9 */
  uint8_t standard_date[8];                 /* bytes 10 to 17 */
  uint8_t standard_time[6];                 /* bytes 18 to 23 */
  uint8_t total_profit_index[10];           /* bytes 24 to 33 */
  uint8_t clean_price_index[10];            /* bytes 34 to 43 */
  uint8_t market_price_index[10];           /* bytes 44 to 53 */
  uint8_t call_re_investment_index[10];     /* bytes 54 to 63 */
  uint8_t zero_re_investment_index[10];     /* bytes 64 to 73 */
  uint8_t futures_basis_price_nullable[9];  /* bytes 74 to 82 */
  uint8_t average_duration[6];              /* bytes 83 to 88 */
  uint8_t average_convexity[6];             /* bytes 89 to 94 */
  uint8_t average_ytm[6];                   /* bytes 95 to 100 */
  uint8_t average_forward_ytm_nullable[6];  /* bytes 101 to 106 */
  uint8_t filler_1;                         /* byte 107 */
  uint8_t end_keyword;                      /* byte 108 */
} KabiBondIndexMessage;

/* any Kabi Bond Index Message at all: every byte one the checker chooses */
static void any_kabi_bond_index_message(KabiBondIndexMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->standard_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->standard_time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->total_profit_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->clean_price_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->market_price_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->call_re_investment_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->zero_re_investment_index[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->futures_basis_price_nullable[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_duration[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_convexity[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_ytm[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_forward_ytm_nullable[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  record->end_keyword = arbitrary();
}

/* Kabi Bond Index Message to the wire: 109 bytes from at, returning where the next byte goes */
static size_t encode_kabi_bond_index_message(const KabiBondIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->standard_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->standard_time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->total_profit_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->clean_price_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->market_price_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->call_re_investment_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->zero_re_investment_index[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->futures_basis_price_nullable[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_duration[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_convexity[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_ytm[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_forward_ytm_nullable[i]; }
  wire[at++] = record->filler_1;
  wire[at++] = record->end_keyword;

  return at;
}

/* Kabi Bond Index Message off the wire: 109 bytes from at, returning where the next byte lies */
static size_t decode_kabi_bond_index_message(KabiBondIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->standard_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->standard_time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->total_profit_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->clean_price_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->market_price_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->call_re_investment_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->zero_re_investment_index[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->futures_basis_price_nullable[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_duration[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_convexity[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_ytm[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_forward_ytm_nullable[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Kabi Bond Index Message is what was written, byte for byte */
static void equal_kabi_bond_index_message(const KabiBondIndexMessage *read, const KabiBondIndexMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->standard_date[i] == written->standard_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->standard_time[i] == written->standard_time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->total_profit_index[i] == written->total_profit_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->clean_price_index[i] == written->clean_price_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->market_price_index[i] == written->market_price_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->call_re_investment_index[i] == written->call_re_investment_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->zero_re_investment_index[i] == written->zero_re_investment_index[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->futures_basis_price_nullable[i] == written->futures_basis_price_nullable[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_duration[i] == written->average_duration[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_convexity[i] == written->average_convexity[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_ytm[i] == written->average_ytm[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_forward_ytm_nullable[i] == written->average_forward_ytm_nullable[i]); }
  assert(read->filler_1 == written->filler_1);
  assert(read->end_keyword == written->end_keyword);
}

/* Kabi Bond Index Message: written and read back, then read and written back */
static void check_kabi_bond_index_message(void) {
  KabiBondIndexMessage sent;
  KabiBondIndexMessage got;
  uint8_t wire[109];
  uint8_t again[109];

  any_kabi_bond_index_message(&sent);
  assert(encode_kabi_bond_index_message(&sent, wire, 0) == 109);
  assert(decode_kabi_bond_index_message(&got, wire, 0) == 109);
  equal_kabi_bond_index_message(&got, &sent);

  for (size_t i = 0; i < 109; i++) { wire[i] = arbitrary(); }
  assert(decode_kabi_bond_index_message(&got, wire, 0) == 109);
  assert(encode_kabi_bond_index_message(&got, again, 0) == 109);
  for (size_t i = 0; i < 109; i++) { assert(again[i] == wire[i]); }
}

/* ---- Nicepni Bond Index Message: 109 bytes ----------------------------------- */

/* NicePNI Bond Index real-time message. Identical field layout to the Mkf Bond Index Message. */
typedef struct {
  uint8_t filler_4[4];                   /* bytes 0 to 3 */
  uint8_t index_id[6];                   /* bytes 4 to 9 */
  uint8_t standard_date[8];              /* bytes 10 to 17 */
  uint8_t standard_time[6];              /* bytes 18 to 23 */
  uint8_t total_profit_index[10];        /* bytes 24 to 33 */
  uint8_t clean_price_index[10];         /* bytes 34 to 43 */
  uint8_t market_price_index[10];        /* bytes 44 to 53 */
  uint8_t call_re_investment_index[10];  /* bytes 54 to 63 */
  uint8_t zero_re_investment_index[10];  /* bytes 64 to 73 */
  uint8_t futures_basis_price[9];        /* bytes 74 to 82 */
  uint8_t average_duration_nullable[6];  /* bytes 83 to 88 */
  uint8_t average_convexity[6];          /* bytes 89 to 94 */
  uint8_t average_ytm[6];                /* bytes 95 to 100 */
  uint8_t average_forward_ytm[6];        /* bytes 101 to 106 */
  uint8_t filler_1;                      /* byte 107 */
  uint8_t end_keyword;                   /* byte 108 */
} NicepniBondIndexMessage;

/* any Nicepni Bond Index Message at all: every byte one the checker chooses */
static void any_nicepni_bond_index_message(NicepniBondIndexMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->standard_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->standard_time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->total_profit_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->clean_price_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->market_price_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->call_re_investment_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->zero_re_investment_index[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->futures_basis_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_duration_nullable[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_convexity[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_ytm[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->average_forward_ytm[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  record->end_keyword = arbitrary();
}

/* Nicepni Bond Index Message to the wire: 109 bytes from at, returning where the next byte goes */
static size_t encode_nicepni_bond_index_message(const NicepniBondIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->index_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->standard_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->standard_time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->total_profit_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->clean_price_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->market_price_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->call_re_investment_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->zero_re_investment_index[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->futures_basis_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_duration_nullable[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_convexity[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_ytm[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->average_forward_ytm[i]; }
  wire[at++] = record->filler_1;
  wire[at++] = record->end_keyword;

  return at;
}

/* Nicepni Bond Index Message off the wire: 109 bytes from at, returning where the next byte lies */
static size_t decode_nicepni_bond_index_message(NicepniBondIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->index_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->standard_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->standard_time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->total_profit_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->clean_price_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->market_price_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->call_re_investment_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->zero_re_investment_index[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->futures_basis_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_duration_nullable[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_convexity[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_ytm[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->average_forward_ytm[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Nicepni Bond Index Message is what was written, byte for byte */
static void equal_nicepni_bond_index_message(const NicepniBondIndexMessage *read, const NicepniBondIndexMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->index_id[i] == written->index_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->standard_date[i] == written->standard_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->standard_time[i] == written->standard_time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->total_profit_index[i] == written->total_profit_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->clean_price_index[i] == written->clean_price_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->market_price_index[i] == written->market_price_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->call_re_investment_index[i] == written->call_re_investment_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->zero_re_investment_index[i] == written->zero_re_investment_index[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->futures_basis_price[i] == written->futures_basis_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_duration_nullable[i] == written->average_duration_nullable[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_convexity[i] == written->average_convexity[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_ytm[i] == written->average_ytm[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->average_forward_ytm[i] == written->average_forward_ytm[i]); }
  assert(read->filler_1 == written->filler_1);
  assert(read->end_keyword == written->end_keyword);
}

/* Nicepni Bond Index Message: written and read back, then read and written back */
static void check_nicepni_bond_index_message(void) {
  NicepniBondIndexMessage sent;
  NicepniBondIndexMessage got;
  uint8_t wire[109];
  uint8_t again[109];

  any_nicepni_bond_index_message(&sent);
  assert(encode_nicepni_bond_index_message(&sent, wire, 0) == 109);
  assert(decode_nicepni_bond_index_message(&got, wire, 0) == 109);
  equal_nicepni_bond_index_message(&got, &sent);

  for (size_t i = 0; i < 109; i++) { wire[i] = arbitrary(); }
  assert(decode_nicepni_bond_index_message(&got, wire, 0) == 109);
  assert(encode_nicepni_bond_index_message(&got, again, 0) == 109);
  for (size_t i = 0; i < 109; i++) { assert(again[i] == wire[i]); }
}

/* ---- Domestic Etf Inav Message: 65 bytes ------------------------------------- */

/* Domestic ETF intraday NAV (1-second interval). Carries previous-day and during-market/final NAV per ETF ISIN. */
typedef struct {
  uint8_t isin[12];                   /* bytes 0 to 11 */
  uint8_t time[6];                    /* bytes 12 to 17 */
  uint8_t previous_nav[9];            /* bytes 18 to 26 */
  uint8_t during_marketfinal_nav[9];  /* bytes 27 to 35 */
  uint8_t filler_28[28];              /* bytes 36 to 63 */
  uint8_t end_keyword;                /* byte 64 */
} DomesticEtfInavMessage;

/* any Domestic Etf Inav Message at all: every byte one the checker chooses */
static void any_domestic_etf_inav_message(DomesticEtfInavMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->previous_nav[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->during_marketfinal_nav[i] = arbitrary(); }
  for (size_t i = 0; i < 28; i++) { record->filler_28[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Domestic Etf Inav Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_domestic_etf_inav_message(const DomesticEtfInavMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->previous_nav[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->during_marketfinal_nav[i]; }
  for (size_t i = 0; i < 28; i++) { wire[at++] = record->filler_28[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Domestic Etf Inav Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_domestic_etf_inav_message(DomesticEtfInavMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->previous_nav[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->during_marketfinal_nav[i] = wire[at++]; }
  for (size_t i = 0; i < 28; i++) { record->filler_28[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Domestic Etf Inav Message is what was written, byte for byte */
static void equal_domestic_etf_inav_message(const DomesticEtfInavMessage *read, const DomesticEtfInavMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->previous_nav[i] == written->previous_nav[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->during_marketfinal_nav[i] == written->during_marketfinal_nav[i]); }
  for (size_t i = 0; i < 28; i++) { assert(read->filler_28[i] == written->filler_28[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Domestic Etf Inav Message: written and read back, then read and written back */
static void check_domestic_etf_inav_message(void) {
  DomesticEtfInavMessage sent;
  DomesticEtfInavMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_domestic_etf_inav_message(&sent);
  assert(encode_domestic_etf_inav_message(&sent, wire, 0) == 65);
  assert(decode_domestic_etf_inav_message(&got, wire, 0) == 65);
  equal_domestic_etf_inav_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_domestic_etf_inav_message(&got, wire, 0) == 65);
  assert(encode_domestic_etf_inav_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Domestic Etf Estimated Inav Message: 45 bytes --------------------------- */

/* Domestic ETF Estimated iNAV. Carries previous-day and during-market/final estimated NAV. */
typedef struct {
  uint8_t isin[12];                          /* bytes 0 to 11 */
  uint8_t time[6];                           /* bytes 12 to 17 */
  uint8_t previous_nav[9];                   /* bytes 18 to 26 */
  uint8_t during_marketfinal_market_nav[9];  /* bytes 27 to 35 */
  uint8_t filler_8[8];                       /* bytes 36 to 43 */
  uint8_t end_keyword;                       /* byte 44 */
} DomesticEtfEstimatedInavMessage;

/* any Domestic Etf Estimated Inav Message at all: every byte one the checker chooses */
static void any_domestic_etf_estimated_inav_message(DomesticEtfEstimatedInavMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->previous_nav[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->during_marketfinal_market_nav[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->filler_8[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Domestic Etf Estimated Inav Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_domestic_etf_estimated_inav_message(const DomesticEtfEstimatedInavMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->previous_nav[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->during_marketfinal_market_nav[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->filler_8[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Domestic Etf Estimated Inav Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_domestic_etf_estimated_inav_message(DomesticEtfEstimatedInavMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->previous_nav[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->during_marketfinal_market_nav[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->filler_8[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Domestic Etf Estimated Inav Message is what was written, byte for byte */
static void equal_domestic_etf_estimated_inav_message(const DomesticEtfEstimatedInavMessage *read, const DomesticEtfEstimatedInavMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->previous_nav[i] == written->previous_nav[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->during_marketfinal_market_nav[i] == written->during_marketfinal_market_nav[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->filler_8[i] == written->filler_8[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Domestic Etf Estimated Inav Message: written and read back, then read and written back */
static void check_domestic_etf_estimated_inav_message(void) {
  DomesticEtfEstimatedInavMessage sent;
  DomesticEtfEstimatedInavMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_domestic_etf_estimated_inav_message(&sent);
  assert(encode_domestic_etf_estimated_inav_message(&sent, wire, 0) == 45);
  assert(decode_domestic_etf_estimated_inav_message(&got, wire, 0) == 45);
  equal_domestic_etf_estimated_inav_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_domestic_etf_estimated_inav_message(&got, wire, 0) == 45);
  assert(encode_domestic_etf_estimated_inav_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Global Etf Inav Message: 65 bytes --------------------------------------- */

/* Global ETF intraday NAV per ETF ISIN. */
typedef struct {
  uint8_t isin[12];                   /* bytes 0 to 11 */
  uint8_t time[6];                    /* bytes 12 to 17 */
  uint8_t previous_nav[9];            /* bytes 18 to 26 */
  uint8_t during_marketfinal_nav[9];  /* bytes 27 to 35 */
  uint8_t filler_28[28];              /* bytes 36 to 63 */
  uint8_t end_keyword;                /* byte 64 */
} GlobalEtfInavMessage;

/* any Global Etf Inav Message at all: every byte one the checker chooses */
static void any_global_etf_inav_message(GlobalEtfInavMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->previous_nav[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->during_marketfinal_nav[i] = arbitrary(); }
  for (size_t i = 0; i < 28; i++) { record->filler_28[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Global Etf Inav Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_global_etf_inav_message(const GlobalEtfInavMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->previous_nav[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->during_marketfinal_nav[i]; }
  for (size_t i = 0; i < 28; i++) { wire[at++] = record->filler_28[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Global Etf Inav Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_global_etf_inav_message(GlobalEtfInavMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->previous_nav[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->during_marketfinal_nav[i] = wire[at++]; }
  for (size_t i = 0; i < 28; i++) { record->filler_28[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Global Etf Inav Message is what was written, byte for byte */
static void equal_global_etf_inav_message(const GlobalEtfInavMessage *read, const GlobalEtfInavMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->previous_nav[i] == written->previous_nav[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->during_marketfinal_nav[i] == written->during_marketfinal_nav[i]); }
  for (size_t i = 0; i < 28; i++) { assert(read->filler_28[i] == written->filler_28[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Global Etf Inav Message: written and read back, then read and written back */
static void check_global_etf_inav_message(void) {
  GlobalEtfInavMessage sent;
  GlobalEtfInavMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_global_etf_inav_message(&sent);
  assert(encode_global_etf_inav_message(&sent, wire, 0) == 65);
  assert(decode_global_etf_inav_message(&got, wire, 0) == 65);
  equal_global_etf_inav_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_global_etf_inav_message(&got, wire, 0) == 65);
  assert(encode_global_etf_inav_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Etf Tracking Error Message: 55 bytes ------------------------------------ */

/* ETF tracking error and signed disparate ratio per ETF. */
typedef struct {
  uint8_t isin[12];              /* bytes 0 to 11 */
  uint8_t seq_number[8];         /* bytes 12 to 19 */
  uint8_t date[8];               /* bytes 20 to 27 */
  uint8_t tracking_error[9];     /* bytes 28 to 36 */
  uint8_t disparate_ratio_sign;  /* byte 37 */
  uint8_t disparate_ratio[9];    /* bytes 38 to 46 */
  uint8_t filler_7[7];           /* bytes 47 to 53 */
  uint8_t end_keyword;           /* byte 54 */
} EtfTrackingErrorMessage;

/* any Etf Tracking Error Message at all: every byte one the checker chooses */
static void any_etf_tracking_error_message(EtfTrackingErrorMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->seq_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->tracking_error[i] = arbitrary(); }
  record->disparate_ratio_sign = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->disparate_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->filler_7[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Etf Tracking Error Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_etf_tracking_error_message(const EtfTrackingErrorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->seq_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->tracking_error[i]; }
  wire[at++] = record->disparate_ratio_sign;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->disparate_ratio[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->filler_7[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Etf Tracking Error Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_etf_tracking_error_message(EtfTrackingErrorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->seq_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->tracking_error[i] = wire[at++]; }
  record->disparate_ratio_sign = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->disparate_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->filler_7[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Etf Tracking Error Message is what was written, byte for byte */
static void equal_etf_tracking_error_message(const EtfTrackingErrorMessage *read, const EtfTrackingErrorMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->seq_number[i] == written->seq_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->tracking_error[i] == written->tracking_error[i]); }
  assert(read->disparate_ratio_sign == written->disparate_ratio_sign);
  for (size_t i = 0; i < 9; i++) { assert(read->disparate_ratio[i] == written->disparate_ratio[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->filler_7[i] == written->filler_7[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Etf Tracking Error Message: written and read back, then read and written back */
static void check_etf_tracking_error_message(void) {
  EtfTrackingErrorMessage sent;
  EtfTrackingErrorMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_etf_tracking_error_message(&sent);
  assert(encode_etf_tracking_error_message(&sent, wire, 0) == 55);
  assert(decode_etf_tracking_error_message(&got, wire, 0) == 55);
  equal_etf_tracking_error_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_etf_tracking_error_message(&got, wire, 0) == 55);
  assert(encode_etf_tracking_error_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- Global Etf Tracking Error Message: 55 bytes ----------------------------- */

/* Global ETF tracking error and signed disparate ratio. */
typedef struct {
  uint8_t isin[12];              /* bytes 0 to 11 */
  uint8_t seq_number[8];         /* bytes 12 to 19 */
  uint8_t date[8];               /* bytes 20 to 27 */
  uint8_t tracking_error[9];     /* bytes 28 to 36 */
  uint8_t disparate_ratio_sign;  /* byte 37 */
  uint8_t disparate_ratio[9];    /* bytes 38 to 46 */
  uint8_t filler_7[7];           /* bytes 47 to 53 */
  uint8_t end_keyword;           /* byte 54 */
} GlobalEtfTrackingErrorMessage;

/* any Global Etf Tracking Error Message at all: every byte one the checker chooses */
static void any_global_etf_tracking_error_message(GlobalEtfTrackingErrorMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->seq_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->tracking_error[i] = arbitrary(); }
  record->disparate_ratio_sign = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->disparate_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->filler_7[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Global Etf Tracking Error Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_global_etf_tracking_error_message(const GlobalEtfTrackingErrorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->seq_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->tracking_error[i]; }
  wire[at++] = record->disparate_ratio_sign;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->disparate_ratio[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->filler_7[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Global Etf Tracking Error Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_global_etf_tracking_error_message(GlobalEtfTrackingErrorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->seq_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->tracking_error[i] = wire[at++]; }
  record->disparate_ratio_sign = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->disparate_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->filler_7[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Global Etf Tracking Error Message is what was written, byte for byte */
static void equal_global_etf_tracking_error_message(const GlobalEtfTrackingErrorMessage *read, const GlobalEtfTrackingErrorMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->seq_number[i] == written->seq_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->tracking_error[i] == written->tracking_error[i]); }
  assert(read->disparate_ratio_sign == written->disparate_ratio_sign);
  for (size_t i = 0; i < 9; i++) { assert(read->disparate_ratio[i] == written->disparate_ratio[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->filler_7[i] == written->filler_7[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Global Etf Tracking Error Message: written and read back, then read and written back */
static void check_global_etf_tracking_error_message(void) {
  GlobalEtfTrackingErrorMessage sent;
  GlobalEtfTrackingErrorMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_global_etf_tracking_error_message(&sent);
  assert(encode_global_etf_tracking_error_message(&sent, wire, 0) == 55);
  assert(decode_global_etf_tracking_error_message(&got, wire, 0) == 55);
  equal_global_etf_tracking_error_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_global_etf_tracking_error_message(&got, wire, 0) == 55);
  assert(encode_global_etf_tracking_error_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- Etp Pdf Message: 155 bytes ---------------------------------------------- */

/* ETP Portfolio Deposit File. One record per composition issue: unit share, market type, issue name, par value, appraised value, profit distribution basis date. */
typedef struct {
  uint8_t isin[12];                                                                            /* bytes 0 to 11 */
  uint8_t data_seq_number[8];                                                                  /* bytes 12 to 19 */
  uint8_t date[8];                                                                             /* bytes 20 to 27 */
  uint8_t office_consignment_companys_registration_number[3];                                  /* bytes 28 to 30 */
  uint8_t composition_issue_number[4];                                                         /* bytes 31 to 34 */
  uint8_t composition_issue_code[12];                                                          /* bytes 35 to 46 */
  uint8_t c_u_unit_share_number_of_contract_k_r_w_cash_u_s_d_cash_converted_amount_k_r_w[18];  /* bytes 47 to 64 */
  uint8_t composition_issue_market_type;                                                       /* byte 65 */
  uint8_t composition_issue_name[40];                                                          /* bytes 66 to 105 */
  uint8_t par_value_amount_cash_amount_converted_amount_krw[18];                               /* bytes 106 to 123 */
  uint8_t profit_distribution_basis_date[8];                                                   /* bytes 124 to 131 */
  uint8_t appraised_value[18];                                                                 /* bytes 132 to 149 */
  uint8_t filler_4[4];                                                                         /* bytes 150 to 153 */
  uint8_t end_keyword;                                                                         /* byte 154 */
} EtpPdfMessage;

/* any Etp Pdf Message at all: every byte one the checker chooses */
static void any_etp_pdf_message(EtpPdfMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->office_consignment_companys_registration_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->composition_issue_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->composition_issue_code[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->c_u_unit_share_number_of_contract_k_r_w_cash_u_s_d_cash_converted_amount_k_r_w[i] = arbitrary(); }
  record->composition_issue_market_type = arbitrary();
  for (size_t i = 0; i < 40; i++) { record->composition_issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->par_value_amount_cash_amount_converted_amount_krw[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->profit_distribution_basis_date[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->appraised_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Etp Pdf Message to the wire: 155 bytes from at, returning where the next byte goes */
static size_t encode_etp_pdf_message(const EtpPdfMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->data_seq_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->office_consignment_companys_registration_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->composition_issue_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->composition_issue_code[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->c_u_unit_share_number_of_contract_k_r_w_cash_u_s_d_cash_converted_amount_k_r_w[i]; }
  wire[at++] = record->composition_issue_market_type;
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->composition_issue_name[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->par_value_amount_cash_amount_converted_amount_krw[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->profit_distribution_basis_date[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->appraised_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Etp Pdf Message off the wire: 155 bytes from at, returning where the next byte lies */
static size_t decode_etp_pdf_message(EtpPdfMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->office_consignment_companys_registration_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->composition_issue_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->composition_issue_code[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->c_u_unit_share_number_of_contract_k_r_w_cash_u_s_d_cash_converted_amount_k_r_w[i] = wire[at++]; }
  record->composition_issue_market_type = wire[at++];
  for (size_t i = 0; i < 40; i++) { record->composition_issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->par_value_amount_cash_amount_converted_amount_krw[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->profit_distribution_basis_date[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->appraised_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Etp Pdf Message is what was written, byte for byte */
static void equal_etp_pdf_message(const EtpPdfMessage *read, const EtpPdfMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->data_seq_number[i] == written->data_seq_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->office_consignment_companys_registration_number[i] == written->office_consignment_companys_registration_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->composition_issue_number[i] == written->composition_issue_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->composition_issue_code[i] == written->composition_issue_code[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->c_u_unit_share_number_of_contract_k_r_w_cash_u_s_d_cash_converted_amount_k_r_w[i] == written->c_u_unit_share_number_of_contract_k_r_w_cash_u_s_d_cash_converted_amount_k_r_w[i]); }
  assert(read->composition_issue_market_type == written->composition_issue_market_type);
  for (size_t i = 0; i < 40; i++) { assert(read->composition_issue_name[i] == written->composition_issue_name[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->par_value_amount_cash_amount_converted_amount_krw[i] == written->par_value_amount_cash_amount_converted_amount_krw[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->profit_distribution_basis_date[i] == written->profit_distribution_basis_date[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->appraised_value[i] == written->appraised_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Etp Pdf Message: written and read back, then read and written back */
static void check_etp_pdf_message(void) {
  EtpPdfMessage sent;
  EtpPdfMessage got;
  uint8_t wire[155];
  uint8_t again[155];

  any_etp_pdf_message(&sent);
  assert(encode_etp_pdf_message(&sent, wire, 0) == 155);
  assert(decode_etp_pdf_message(&got, wire, 0) == 155);
  equal_etp_pdf_message(&got, &sent);

  for (size_t i = 0; i < 155; i++) { wire[i] = arbitrary(); }
  assert(decode_etp_pdf_message(&got, wire, 0) == 155);
  assert(encode_etp_pdf_message(&got, again, 0) == 155);
  for (size_t i = 0; i < 155; i++) { assert(again[i] == wire[i]); }
}

/* ---- Etp Operator Information Message: 125 bytes ----------------------------- */

/* ETP/BDC operator information. Office consignment company, operator code, and abbreviated names in Korean and English. */
typedef struct {
  uint8_t isin[12];                                            /* bytes 0 to 11 */
  uint8_t seq_number[8];                                       /* bytes 12 to 19 */
  uint8_t office_consignment_companys_registration_number[3];  /* bytes 20 to 22 */
  uint8_t operator_code[6];                                    /* bytes 23 to 28 */
  uint8_t operator_abbreviated_name_korean[50];                /* bytes 29 to 78 */
  uint8_t operator_abbreviated_name_english[40];               /* bytes 79 to 118 */
  uint8_t filler_5[5];                                         /* bytes 119 to 123 */
  uint8_t end_keyword;                                         /* byte 124 */
} EtpOperatorInformationMessage;

/* any Etp Operator Information Message at all: every byte one the checker chooses */
static void any_etp_operator_information_message(EtpOperatorInformationMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->seq_number[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->office_consignment_companys_registration_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->operator_code[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->operator_abbreviated_name_korean[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->operator_abbreviated_name_english[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->filler_5[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Etp Operator Information Message to the wire: 125 bytes from at, returning where the next byte goes */
static size_t encode_etp_operator_information_message(const EtpOperatorInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->seq_number[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->office_consignment_companys_registration_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->operator_code[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->operator_abbreviated_name_korean[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->operator_abbreviated_name_english[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->filler_5[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Etp Operator Information Message off the wire: 125 bytes from at, returning where the next byte lies */
static size_t decode_etp_operator_information_message(EtpOperatorInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->seq_number[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->office_consignment_companys_registration_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->operator_code[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->operator_abbreviated_name_korean[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->operator_abbreviated_name_english[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->filler_5[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Etp Operator Information Message is what was written, byte for byte */
static void equal_etp_operator_information_message(const EtpOperatorInformationMessage *read, const EtpOperatorInformationMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->seq_number[i] == written->seq_number[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->office_consignment_companys_registration_number[i] == written->office_consignment_companys_registration_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->operator_code[i] == written->operator_code[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->operator_abbreviated_name_korean[i] == written->operator_abbreviated_name_korean[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->operator_abbreviated_name_english[i] == written->operator_abbreviated_name_english[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->filler_5[i] == written->filler_5[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Etp Operator Information Message: written and read back, then read and written back */
static void check_etp_operator_information_message(void) {
  EtpOperatorInformationMessage sent;
  EtpOperatorInformationMessage got;
  uint8_t wire[125];
  uint8_t again[125];

  any_etp_operator_information_message(&sent);
  assert(encode_etp_operator_information_message(&sent, wire, 0) == 125);
  assert(decode_etp_operator_information_message(&got, wire, 0) == 125);
  equal_etp_operator_information_message(&got, &sent);

  for (size_t i = 0; i < 125; i++) { wire[i] = arbitrary(); }
  assert(decode_etp_operator_information_message(&got, wire, 0) == 125);
  assert(encode_etp_operator_information_message(&got, again, 0) == 125);
  for (size_t i = 0; i < 125; i++) { assert(again[i] == wire[i]); }
}

/* ---- Etp Transfer Agent Batch Message: 245 bytes ----------------------------- */

/* ETP/BDC transfer agent batch data. */
typedef struct {
  uint8_t isin[12];                                                                     /* bytes 0 to 11 */
  uint8_t data_seq_number[8];                                                           /* bytes 12 to 19 */
  uint8_t filler_10[10];                                                                /* bytes 20 to 29 */
  uint8_t etf_flow_net_asset_total_amount[15];                                          /* bytes 30 to 44 */
  uint8_t etf_foreign_net_asset_value_amount[15];                                       /* bytes 45 to 59 */
  uint8_t etf_net_asset_value_amount[9];                                                /* bytes 60 to 68 */
  uint8_t etf_foreign_flow_net_asset_total_amount[15];                                  /* bytes 69 to 83 */
  uint8_t etf_foreign_net_asset_total[15];                                              /* bytes 84 to 98 */
  uint8_t etf_foreign_final_net_asset_value[9];                                         /* bytes 99 to 107 */
  uint8_t etf_cu_quantity[8];                                                           /* bytes 108 to 115 */
  uint8_t previous_days_tax_base_nav[9];                                                /* bytes 116 to 124 */
  uint8_t previous_days_tax_base_nav_before_dividend[9];                                /* bytes 125 to 133 */
  uint8_t previous_days_cash_dividend_amount[12];                                       /* bytes 134 to 145 */
  uint8_t tax_base_nav_as_of_the_day_before_the_previous_day[9];                        /* bytes 146 to 154 */
  uint8_t previous_days_non_taxable_base_price_for_overseas_stocks[9];                  /* bytes 155 to 163 */
  uint8_t previous_days_non_taxable_base_price_before_dividend_for_overseas_stocks[9];  /* bytes 164 to 172 */
  uint8_t day_before_previous_days_non_taxable_base_price_for_overseas_stocks[9];       /* bytes 173 to 181 */
  uint8_t number_of_free_floating_etf_shares[16];                                       /* bytes 182 to 197 */
  uint8_t filler_46[46];                                                                /* bytes 198 to 243 */
  uint8_t end_keyword;                                                                  /* byte 244 */
} EtpTransferAgentBatchMessage;

/* any Etp Transfer Agent Batch Message at all: every byte one the checker chooses */
static void any_etp_transfer_agent_batch_message(EtpTransferAgentBatchMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->filler_10[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->etf_flow_net_asset_total_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->etf_foreign_net_asset_value_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->etf_net_asset_value_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->etf_foreign_flow_net_asset_total_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->etf_foreign_net_asset_total[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->etf_foreign_final_net_asset_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->etf_cu_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->previous_days_tax_base_nav[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->previous_days_tax_base_nav_before_dividend[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->previous_days_cash_dividend_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->tax_base_nav_as_of_the_day_before_the_previous_day[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->previous_days_non_taxable_base_price_for_overseas_stocks[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->previous_days_non_taxable_base_price_before_dividend_for_overseas_stocks[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->day_before_previous_days_non_taxable_base_price_for_overseas_stocks[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->number_of_free_floating_etf_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 46; i++) { record->filler_46[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Etp Transfer Agent Batch Message to the wire: 245 bytes from at, returning where the next byte goes */
static size_t encode_etp_transfer_agent_batch_message(const EtpTransferAgentBatchMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->data_seq_number[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->filler_10[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->etf_flow_net_asset_total_amount[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->etf_foreign_net_asset_value_amount[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->etf_net_asset_value_amount[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->etf_foreign_flow_net_asset_total_amount[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->etf_foreign_net_asset_total[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->etf_foreign_final_net_asset_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->etf_cu_quantity[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->previous_days_tax_base_nav[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->previous_days_tax_base_nav_before_dividend[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->previous_days_cash_dividend_amount[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->tax_base_nav_as_of_the_day_before_the_previous_day[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->previous_days_non_taxable_base_price_for_overseas_stocks[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->previous_days_non_taxable_base_price_before_dividend_for_overseas_stocks[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->day_before_previous_days_non_taxable_base_price_for_overseas_stocks[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->number_of_free_floating_etf_shares[i]; }
  for (size_t i = 0; i < 46; i++) { wire[at++] = record->filler_46[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Etp Transfer Agent Batch Message off the wire: 245 bytes from at, returning where the next byte lies */
static size_t decode_etp_transfer_agent_batch_message(EtpTransferAgentBatchMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->filler_10[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->etf_flow_net_asset_total_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->etf_foreign_net_asset_value_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->etf_net_asset_value_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->etf_foreign_flow_net_asset_total_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->etf_foreign_net_asset_total[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->etf_foreign_final_net_asset_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->etf_cu_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->previous_days_tax_base_nav[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->previous_days_tax_base_nav_before_dividend[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->previous_days_cash_dividend_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->tax_base_nav_as_of_the_day_before_the_previous_day[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->previous_days_non_taxable_base_price_for_overseas_stocks[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->previous_days_non_taxable_base_price_before_dividend_for_overseas_stocks[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->day_before_previous_days_non_taxable_base_price_for_overseas_stocks[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->number_of_free_floating_etf_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 46; i++) { record->filler_46[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Etp Transfer Agent Batch Message is what was written, byte for byte */
static void equal_etp_transfer_agent_batch_message(const EtpTransferAgentBatchMessage *read, const EtpTransferAgentBatchMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->data_seq_number[i] == written->data_seq_number[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->filler_10[i] == written->filler_10[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->etf_flow_net_asset_total_amount[i] == written->etf_flow_net_asset_total_amount[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->etf_foreign_net_asset_value_amount[i] == written->etf_foreign_net_asset_value_amount[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->etf_net_asset_value_amount[i] == written->etf_net_asset_value_amount[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->etf_foreign_flow_net_asset_total_amount[i] == written->etf_foreign_flow_net_asset_total_amount[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->etf_foreign_net_asset_total[i] == written->etf_foreign_net_asset_total[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->etf_foreign_final_net_asset_value[i] == written->etf_foreign_final_net_asset_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->etf_cu_quantity[i] == written->etf_cu_quantity[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->previous_days_tax_base_nav[i] == written->previous_days_tax_base_nav[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->previous_days_tax_base_nav_before_dividend[i] == written->previous_days_tax_base_nav_before_dividend[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->previous_days_cash_dividend_amount[i] == written->previous_days_cash_dividend_amount[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->tax_base_nav_as_of_the_day_before_the_previous_day[i] == written->tax_base_nav_as_of_the_day_before_the_previous_day[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->previous_days_non_taxable_base_price_for_overseas_stocks[i] == written->previous_days_non_taxable_base_price_for_overseas_stocks[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->previous_days_non_taxable_base_price_before_dividend_for_overseas_stocks[i] == written->previous_days_non_taxable_base_price_before_dividend_for_overseas_stocks[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->day_before_previous_days_non_taxable_base_price_for_overseas_stocks[i] == written->day_before_previous_days_non_taxable_base_price_for_overseas_stocks[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->number_of_free_floating_etf_shares[i] == written->number_of_free_floating_etf_shares[i]); }
  for (size_t i = 0; i < 46; i++) { assert(read->filler_46[i] == written->filler_46[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Etp Transfer Agent Batch Message: written and read back, then read and written back */
static void check_etp_transfer_agent_batch_message(void) {
  EtpTransferAgentBatchMessage sent;
  EtpTransferAgentBatchMessage got;
  uint8_t wire[245];
  uint8_t again[245];

  any_etp_transfer_agent_batch_message(&sent);
  assert(encode_etp_transfer_agent_batch_message(&sent, wire, 0) == 245);
  assert(decode_etp_transfer_agent_batch_message(&got, wire, 0) == 245);
  equal_etp_transfer_agent_batch_message(&got, &sent);

  for (size_t i = 0; i < 245; i++) { wire[i] = arbitrary(); }
  assert(decode_etp_transfer_agent_batch_message(&got, wire, 0) == 245);
  assert(encode_etp_transfer_agent_batch_message(&got, again, 0) == 245);
  for (size_t i = 0; i < 245; i++) { assert(again[i] == wire[i]); }
}

/* ---- Etf Risk Appraisement Message: 195 bytes -------------------------------- */

/* Synthetic ETF risk appraisement daily trading data. */
typedef struct {
  uint8_t isin[12];                                            /* bytes 0 to 11 */
  uint8_t data_seq_number[8];                                  /* bytes 12 to 19 */
  uint8_t date[8];                                             /* bytes 20 to 27 */
  uint8_t office_consignment_companys_registration_number[3];  /* bytes 28 to 30 */
  uint8_t name_of_counterparty[50];                            /* bytes 31 to 80 */
  uint8_t otc_derivatives_type;                                /* byte 81 */
  uint8_t net_assets_amount[15];                               /* bytes 82 to 96 */
  uint8_t total_danger_exposure_amount[15];                    /* bytes 97 to 111 */
  uint8_t security_appraisal_amount[15];                       /* bytes 112 to 126 */
  uint8_t security_rate[7];                                    /* bytes 127 to 133 */
  uint8_t risk_appraisal_amount[15];                           /* bytes 134 to 148 */
  uint8_t risk_appraisal_amount_rate[7];                       /* bytes 149 to 155 */
  uint8_t filler_38[38];                                       /* bytes 156 to 193 */
  uint8_t end_keyword;                                         /* byte 194 */
} EtfRiskAppraisementMessage;

/* any Etf Risk Appraisement Message at all: every byte one the checker chooses */
static void any_etf_risk_appraisement_message(EtfRiskAppraisementMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->office_consignment_companys_registration_number[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->name_of_counterparty[i] = arbitrary(); }
  record->otc_derivatives_type = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->net_assets_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->total_danger_exposure_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->security_appraisal_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->security_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->risk_appraisal_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->risk_appraisal_amount_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 38; i++) { record->filler_38[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Etf Risk Appraisement Message to the wire: 195 bytes from at, returning where the next byte goes */
static size_t encode_etf_risk_appraisement_message(const EtfRiskAppraisementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->data_seq_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->office_consignment_companys_registration_number[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->name_of_counterparty[i]; }
  wire[at++] = record->otc_derivatives_type;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->net_assets_amount[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->total_danger_exposure_amount[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->security_appraisal_amount[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->security_rate[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->risk_appraisal_amount[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->risk_appraisal_amount_rate[i]; }
  for (size_t i = 0; i < 38; i++) { wire[at++] = record->filler_38[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Etf Risk Appraisement Message off the wire: 195 bytes from at, returning where the next byte lies */
static size_t decode_etf_risk_appraisement_message(EtfRiskAppraisementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->office_consignment_companys_registration_number[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->name_of_counterparty[i] = wire[at++]; }
  record->otc_derivatives_type = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->net_assets_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->total_danger_exposure_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->security_appraisal_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->security_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->risk_appraisal_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->risk_appraisal_amount_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 38; i++) { record->filler_38[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Etf Risk Appraisement Message is what was written, byte for byte */
static void equal_etf_risk_appraisement_message(const EtfRiskAppraisementMessage *read, const EtfRiskAppraisementMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->data_seq_number[i] == written->data_seq_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->office_consignment_companys_registration_number[i] == written->office_consignment_companys_registration_number[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->name_of_counterparty[i] == written->name_of_counterparty[i]); }
  assert(read->otc_derivatives_type == written->otc_derivatives_type);
  for (size_t i = 0; i < 15; i++) { assert(read->net_assets_amount[i] == written->net_assets_amount[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->total_danger_exposure_amount[i] == written->total_danger_exposure_amount[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->security_appraisal_amount[i] == written->security_appraisal_amount[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->security_rate[i] == written->security_rate[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->risk_appraisal_amount[i] == written->risk_appraisal_amount[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->risk_appraisal_amount_rate[i] == written->risk_appraisal_amount_rate[i]); }
  for (size_t i = 0; i < 38; i++) { assert(read->filler_38[i] == written->filler_38[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Etf Risk Appraisement Message: written and read back, then read and written back */
static void check_etf_risk_appraisement_message(void) {
  EtfRiskAppraisementMessage sent;
  EtfRiskAppraisementMessage got;
  uint8_t wire[195];
  uint8_t again[195];

  any_etf_risk_appraisement_message(&sent);
  assert(encode_etf_risk_appraisement_message(&sent, wire, 0) == 195);
  assert(decode_etf_risk_appraisement_message(&got, wire, 0) == 195);
  equal_etf_risk_appraisement_message(&got, &sent);

  for (size_t i = 0; i < 195; i++) { wire[i] = arbitrary(); }
  assert(decode_etf_risk_appraisement_message(&got, wire, 0) == 195);
  assert(encode_etf_risk_appraisement_message(&got, again, 0) == 195);
  for (size_t i = 0; i < 195; i++) { assert(again[i] == wire[i]); }
}

/* ---- Synthetic Etf Constituents Message: 195 bytes --------------------------- */

/* Synthetic ETF basic index composition constituents. */
typedef struct {
  uint8_t isin[12];                                            /* bytes 0 to 11 */
  uint8_t data_seq_number[8];                                  /* bytes 12 to 19 */
  uint8_t date[8];                                             /* bytes 20 to 27 */
  uint8_t office_consignment_companys_registration_number[3];  /* bytes 28 to 30 */
  uint8_t composition_constituents_number[4];                  /* bytes 31 to 34 */
  uint8_t composition_constituents_code[12];                   /* bytes 35 to 46 */
  uint8_t composition_constituents_name[80];                   /* bytes 47 to 126 */
  uint8_t composition_ratio[7];                                /* bytes 127 to 133 */
  uint8_t filler_60[60];                                       /* bytes 134 to 193 */
  uint8_t end_keyword;                                         /* byte 194 */
} SyntheticEtfConstituentsMessage;

/* any Synthetic Etf Constituents Message at all: every byte one the checker chooses */
static void any_synthetic_etf_constituents_message(SyntheticEtfConstituentsMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->office_consignment_companys_registration_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->composition_constituents_number[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->composition_constituents_code[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->composition_constituents_name[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->composition_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 60; i++) { record->filler_60[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Synthetic Etf Constituents Message to the wire: 195 bytes from at, returning where the next byte goes */
static size_t encode_synthetic_etf_constituents_message(const SyntheticEtfConstituentsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->data_seq_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->office_consignment_companys_registration_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->composition_constituents_number[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->composition_constituents_code[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->composition_constituents_name[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->composition_ratio[i]; }
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->filler_60[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Synthetic Etf Constituents Message off the wire: 195 bytes from at, returning where the next byte lies */
static size_t decode_synthetic_etf_constituents_message(SyntheticEtfConstituentsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->data_seq_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->office_consignment_companys_registration_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->composition_constituents_number[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->composition_constituents_code[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->composition_constituents_name[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->composition_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 60; i++) { record->filler_60[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Synthetic Etf Constituents Message is what was written, byte for byte */
static void equal_synthetic_etf_constituents_message(const SyntheticEtfConstituentsMessage *read, const SyntheticEtfConstituentsMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->data_seq_number[i] == written->data_seq_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->office_consignment_companys_registration_number[i] == written->office_consignment_companys_registration_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->composition_constituents_number[i] == written->composition_constituents_number[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->composition_constituents_code[i] == written->composition_constituents_code[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->composition_constituents_name[i] == written->composition_constituents_name[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->composition_ratio[i] == written->composition_ratio[i]); }
  for (size_t i = 0; i < 60; i++) { assert(read->filler_60[i] == written->filler_60[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Synthetic Etf Constituents Message: written and read back, then read and written back */
static void check_synthetic_etf_constituents_message(void) {
  SyntheticEtfConstituentsMessage sent;
  SyntheticEtfConstituentsMessage got;
  uint8_t wire[195];
  uint8_t again[195];

  any_synthetic_etf_constituents_message(&sent);
  assert(encode_synthetic_etf_constituents_message(&sent, wire, 0) == 195);
  assert(decode_synthetic_etf_constituents_message(&got, wire, 0) == 195);
  equal_synthetic_etf_constituents_message(&got, &sent);

  for (size_t i = 0; i < 195; i++) { wire[i] = arbitrary(); }
  assert(decode_synthetic_etf_constituents_message(&got, wire, 0) == 195);
  assert(encode_synthetic_etf_constituents_message(&got, again, 0) == 195);
  for (size_t i = 0; i < 195; i++) { assert(again[i] == wire[i]); }
}

/* ---- Elw Investment Indicator Sensitivity Message: 105 bytes ----------------- */

/* ELW Investment Indicator Sensitivity. Theoretical warrant price plus signed Delta/Gamma/Theta/Vega/Rho sensitivities, intrinsic volatility, and prerequisite cost. */
typedef struct {
  uint8_t isin[12];                       /* bytes 0 to 11 */
  uint8_t time[6];                        /* bytes 12 to 17 */
  uint8_t theoretical_warrant_price[10];  /* bytes 18 to 27 */
  uint8_t sensitivity_delta_sign;         /* byte 28 */
  uint8_t sensitivity_delta[7];           /* bytes 29 to 35 */
  uint8_t sensitivity_gamma_sign;         /* byte 36 */
  uint8_t sensitivity_gamma[7];           /* bytes 37 to 43 */
  uint8_t sensitivity_theta_sign;         /* byte 44 */
  uint8_t sensitivity_theta[12];          /* bytes 45 to 56 */
  uint8_t sensitivity_vega_sign;          /* byte 57 */
  uint8_t sensitivity_vega[12];           /* bytes 58 to 69 */
  uint8_t sensitivity_rho_sign;           /* byte 70 */
  uint8_t sensitivity_rho[12];            /* bytes 71 to 82 */
  uint8_t intrinsic_volatility[5];        /* bytes 83 to 87 */
  uint8_t prerequisite_cost[10];          /* bytes 88 to 97 */
  uint8_t filler_6[6];                    /* bytes 98 to 103 */
  uint8_t end_keyword;                    /* byte 104 */
} ElwInvestmentIndicatorSensitivityMessage;

/* any Elw Investment Indicator Sensitivity Message at all: every byte one the checker chooses */
static void any_elw_investment_indicator_sensitivity_message(ElwInvestmentIndicatorSensitivityMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->theoretical_warrant_price[i] = arbitrary(); }
  record->sensitivity_delta_sign = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->sensitivity_delta[i] = arbitrary(); }
  record->sensitivity_gamma_sign = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->sensitivity_gamma[i] = arbitrary(); }
  record->sensitivity_theta_sign = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->sensitivity_theta[i] = arbitrary(); }
  record->sensitivity_vega_sign = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->sensitivity_vega[i] = arbitrary(); }
  record->sensitivity_rho_sign = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->sensitivity_rho[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->intrinsic_volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->prerequisite_cost[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Elw Investment Indicator Sensitivity Message to the wire: 105 bytes from at, returning where the next byte goes */
static size_t encode_elw_investment_indicator_sensitivity_message(const ElwInvestmentIndicatorSensitivityMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->theoretical_warrant_price[i]; }
  wire[at++] = record->sensitivity_delta_sign;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->sensitivity_delta[i]; }
  wire[at++] = record->sensitivity_gamma_sign;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->sensitivity_gamma[i]; }
  wire[at++] = record->sensitivity_theta_sign;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->sensitivity_theta[i]; }
  wire[at++] = record->sensitivity_vega_sign;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->sensitivity_vega[i]; }
  wire[at++] = record->sensitivity_rho_sign;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->sensitivity_rho[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->intrinsic_volatility[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->prerequisite_cost[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->filler_6[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Elw Investment Indicator Sensitivity Message off the wire: 105 bytes from at, returning where the next byte lies */
static size_t decode_elw_investment_indicator_sensitivity_message(ElwInvestmentIndicatorSensitivityMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->theoretical_warrant_price[i] = wire[at++]; }
  record->sensitivity_delta_sign = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->sensitivity_delta[i] = wire[at++]; }
  record->sensitivity_gamma_sign = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->sensitivity_gamma[i] = wire[at++]; }
  record->sensitivity_theta_sign = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->sensitivity_theta[i] = wire[at++]; }
  record->sensitivity_vega_sign = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->sensitivity_vega[i] = wire[at++]; }
  record->sensitivity_rho_sign = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->sensitivity_rho[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->intrinsic_volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->prerequisite_cost[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Elw Investment Indicator Sensitivity Message is what was written, byte for byte */
static void equal_elw_investment_indicator_sensitivity_message(const ElwInvestmentIndicatorSensitivityMessage *read, const ElwInvestmentIndicatorSensitivityMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->theoretical_warrant_price[i] == written->theoretical_warrant_price[i]); }
  assert(read->sensitivity_delta_sign == written->sensitivity_delta_sign);
  for (size_t i = 0; i < 7; i++) { assert(read->sensitivity_delta[i] == written->sensitivity_delta[i]); }
  assert(read->sensitivity_gamma_sign == written->sensitivity_gamma_sign);
  for (size_t i = 0; i < 7; i++) { assert(read->sensitivity_gamma[i] == written->sensitivity_gamma[i]); }
  assert(read->sensitivity_theta_sign == written->sensitivity_theta_sign);
  for (size_t i = 0; i < 12; i++) { assert(read->sensitivity_theta[i] == written->sensitivity_theta[i]); }
  assert(read->sensitivity_vega_sign == written->sensitivity_vega_sign);
  for (size_t i = 0; i < 12; i++) { assert(read->sensitivity_vega[i] == written->sensitivity_vega[i]); }
  assert(read->sensitivity_rho_sign == written->sensitivity_rho_sign);
  for (size_t i = 0; i < 12; i++) { assert(read->sensitivity_rho[i] == written->sensitivity_rho[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->intrinsic_volatility[i] == written->intrinsic_volatility[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->prerequisite_cost[i] == written->prerequisite_cost[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->filler_6[i] == written->filler_6[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Elw Investment Indicator Sensitivity Message: written and read back, then read and written back */
static void check_elw_investment_indicator_sensitivity_message(void) {
  ElwInvestmentIndicatorSensitivityMessage sent;
  ElwInvestmentIndicatorSensitivityMessage got;
  uint8_t wire[105];
  uint8_t again[105];

  any_elw_investment_indicator_sensitivity_message(&sent);
  assert(encode_elw_investment_indicator_sensitivity_message(&sent, wire, 0) == 105);
  assert(decode_elw_investment_indicator_sensitivity_message(&got, wire, 0) == 105);
  equal_elw_investment_indicator_sensitivity_message(&got, &sent);

  for (size_t i = 0; i < 105; i++) { wire[i] = arbitrary(); }
  assert(decode_elw_investment_indicator_sensitivity_message(&got, wire, 0) == 105);
  assert(encode_elw_investment_indicator_sensitivity_message(&got, again, 0) == 105);
  for (size_t i = 0; i < 105; i++) { assert(again[i] == wire[i]); }
}

/* ---- Etn Iiv Message: 65 bytes ----------------------------------------------- */

/* ETN intraday indicative value. Previous-day and during-market/final iIV per ETN. */
typedef struct {
  uint8_t isin[12];                         /* bytes 0 to 11 */
  uint8_t hours[6];                         /* bytes 12 to 17 */
  uint8_t previous_days_iv[9];              /* bytes 18 to 26 */
  uint8_t during_market_hours_final_iv[9];  /* bytes 27 to 35 */
  uint8_t filler_28[28];                    /* bytes 36 to 63 */
  uint8_t end_keyword;                      /* byte 64 */
} EtnIivMessage;

/* any Etn Iiv Message at all: every byte one the checker chooses */
static void any_etn_iiv_message(EtnIivMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->hours[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->previous_days_iv[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->during_market_hours_final_iv[i] = arbitrary(); }
  for (size_t i = 0; i < 28; i++) { record->filler_28[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Etn Iiv Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_etn_iiv_message(const EtnIivMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->hours[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->previous_days_iv[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->during_market_hours_final_iv[i]; }
  for (size_t i = 0; i < 28; i++) { wire[at++] = record->filler_28[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Etn Iiv Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_etn_iiv_message(EtnIivMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->hours[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->previous_days_iv[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->during_market_hours_final_iv[i] = wire[at++]; }
  for (size_t i = 0; i < 28; i++) { record->filler_28[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Etn Iiv Message is what was written, byte for byte */
static void equal_etn_iiv_message(const EtnIivMessage *read, const EtnIivMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->hours[i] == written->hours[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->previous_days_iv[i] == written->previous_days_iv[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->during_market_hours_final_iv[i] == written->during_market_hours_final_iv[i]); }
  for (size_t i = 0; i < 28; i++) { assert(read->filler_28[i] == written->filler_28[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Etn Iiv Message: written and read back, then read and written back */
static void check_etn_iiv_message(void) {
  EtnIivMessage sent;
  EtnIivMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_etn_iiv_message(&sent);
  assert(encode_etn_iiv_message(&sent, wire, 0) == 65);
  assert(decode_etn_iiv_message(&got, wire, 0) == 65);
  equal_etn_iiv_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_etn_iiv_message(&got, wire, 0) == 65);
  assert(encode_etn_iiv_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Etn Disparate Ratio Message: 95 bytes ----------------------------------- */

/* ETN signed disparate ratio per ETN. */
typedef struct {
  uint8_t isin[12];              /* bytes 0 to 11 */
  uint8_t seq_number[8];         /* bytes 12 to 19 */
  uint8_t date[8];               /* bytes 20 to 27 */
  uint8_t disparate_ratio_sign;  /* byte 28 */
  uint8_t disparate_ratio[9];    /* bytes 29 to 37 */
  uint8_t filler_56[56];         /* bytes 38 to 93 */
  uint8_t end_keyword;           /* byte 94 */
} EtnDisparateRatioMessage;

/* any Etn Disparate Ratio Message at all: every byte one the checker chooses */
static void any_etn_disparate_ratio_message(EtnDisparateRatioMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->seq_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  record->disparate_ratio_sign = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->disparate_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 56; i++) { record->filler_56[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Etn Disparate Ratio Message to the wire: 95 bytes from at, returning where the next byte goes */
static size_t encode_etn_disparate_ratio_message(const EtnDisparateRatioMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->seq_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  wire[at++] = record->disparate_ratio_sign;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->disparate_ratio[i]; }
  for (size_t i = 0; i < 56; i++) { wire[at++] = record->filler_56[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Etn Disparate Ratio Message off the wire: 95 bytes from at, returning where the next byte lies */
static size_t decode_etn_disparate_ratio_message(EtnDisparateRatioMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->seq_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  record->disparate_ratio_sign = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->disparate_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 56; i++) { record->filler_56[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Etn Disparate Ratio Message is what was written, byte for byte */
static void equal_etn_disparate_ratio_message(const EtnDisparateRatioMessage *read, const EtnDisparateRatioMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->seq_number[i] == written->seq_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  assert(read->disparate_ratio_sign == written->disparate_ratio_sign);
  for (size_t i = 0; i < 9; i++) { assert(read->disparate_ratio[i] == written->disparate_ratio[i]); }
  for (size_t i = 0; i < 56; i++) { assert(read->filler_56[i] == written->filler_56[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Etn Disparate Ratio Message: written and read back, then read and written back */
static void check_etn_disparate_ratio_message(void) {
  EtnDisparateRatioMessage sent;
  EtnDisparateRatioMessage got;
  uint8_t wire[95];
  uint8_t again[95];

  any_etn_disparate_ratio_message(&sent);
  assert(encode_etn_disparate_ratio_message(&sent, wire, 0) == 95);
  assert(decode_etn_disparate_ratio_message(&got, wire, 0) == 95);
  equal_etn_disparate_ratio_message(&got, &sent);

  for (size_t i = 0; i < 95; i++) { wire[i] = arbitrary(); }
  assert(decode_etn_disparate_ratio_message(&got, wire, 0) == 95);
  assert(encode_etn_disparate_ratio_message(&got, again, 0) == 95);
  for (size_t i = 0; i < 95; i++) { assert(again[i] == wire[i]); }
}

/* ---- Loan Transaction Available Quantity Message: 45 bytes ------------------- */

/* Loan transaction available quantity public disclosure. Reports the available stock lending quantity for one issue (ISIN) in shares. */
typedef struct {
  uint8_t issue_code[12];                  /* bytes 0 to 11 */
  uint8_t business_code[3];                /* bytes 12 to 14 */
  uint8_t available_lending_quantity[10];  /* bytes 15 to 24 */
  uint8_t filler_19[19];                   /* bytes 25 to 43 */
  uint8_t end_keyword;                     /* byte 44 */
} LoanTransactionAvailableQuantityMessage;

/* any Loan Transaction Available Quantity Message at all: every byte one the checker chooses */
static void any_loan_transaction_available_quantity_message(LoanTransactionAvailableQuantityMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->issue_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->business_code[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->available_lending_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 19; i++) { record->filler_19[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Loan Transaction Available Quantity Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_loan_transaction_available_quantity_message(const LoanTransactionAvailableQuantityMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->issue_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->business_code[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->available_lending_quantity[i]; }
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->filler_19[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Loan Transaction Available Quantity Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_loan_transaction_available_quantity_message(LoanTransactionAvailableQuantityMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->issue_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->business_code[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->available_lending_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 19; i++) { record->filler_19[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Loan Transaction Available Quantity Message is what was written, byte for byte */
static void equal_loan_transaction_available_quantity_message(const LoanTransactionAvailableQuantityMessage *read, const LoanTransactionAvailableQuantityMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->issue_code[i] == written->issue_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->business_code[i] == written->business_code[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->available_lending_quantity[i] == written->available_lending_quantity[i]); }
  for (size_t i = 0; i < 19; i++) { assert(read->filler_19[i] == written->filler_19[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Loan Transaction Available Quantity Message: written and read back, then read and written back */
static void check_loan_transaction_available_quantity_message(void) {
  LoanTransactionAvailableQuantityMessage sent;
  LoanTransactionAvailableQuantityMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_loan_transaction_available_quantity_message(&sent);
  assert(encode_loan_transaction_available_quantity_message(&sent, wire, 0) == 45);
  assert(decode_loan_transaction_available_quantity_message(&got, wire, 0) == 45);
  equal_loan_transaction_available_quantity_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_loan_transaction_available_quantity_message(&got, wire, 0) == 45);
  assert(encode_loan_transaction_available_quantity_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_k_otc_issue_closing_message();
  check_k_otc_market_operation_message();
  check_k_otc_market_action_message();
  check_k_otc_quote_message();
  check_k_otc_order_filled_message();
  check_otc_bond_traded_info_message();
  check_otc_bond_trades_per_institution_message();
  check_otc_bond_types_per_investor_message();
  check_k_bond_message();
  check_mkf_index_message();
  check_mkf_index_jpy_message();
  check_wisefn_index_message();
  check_kis_index_message();
  check_mkf_bond_index_message();
  check_kis_bond_index_message();
  check_kebi_bond_index_message();
  check_kabi_bond_index_message();
  check_nicepni_bond_index_message();
  check_domestic_etf_inav_message();
  check_domestic_etf_estimated_inav_message();
  check_global_etf_inav_message();
  check_etf_tracking_error_message();
  check_global_etf_tracking_error_message();
  check_etp_pdf_message();
  check_etp_operator_information_message();
  check_etp_transfer_agent_batch_message();
  check_etf_risk_appraisement_message();
  check_synthetic_etf_constituents_message();
  check_elw_investment_indicator_sensitivity_message();
  check_etn_iiv_message();
  check_etn_disparate_ratio_message();
  check_loan_transaction_available_quantity_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
