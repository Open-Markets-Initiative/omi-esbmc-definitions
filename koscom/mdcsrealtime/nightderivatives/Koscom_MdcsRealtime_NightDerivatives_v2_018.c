// koscom/mdcsrealtime/nightderivatives/Koscom_MdcsRealtime_NightDerivatives_v2_018.c
/*
 * Koscom Co., Ltd. MDCS Realtime Night Derivatives
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
 *   - a run of a stated number of entries
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

/* Polling Data. Transmitted at one-minute intervals on every market data line, all markets, 24 hours a day. */
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

/* ---- Derivatives Order Filled Message: 168 bytes ----------------------------- */

/* Derivatives Order Filled. Real-time trade prints with running totals for futures and options. */
typedef struct {
  uint8_t message_sequence_number[8];               /* bytes 0 to 7 */
  uint8_t board_id[2];                              /* bytes 8 to 9 */
  uint8_t session_id[2];                            /* bytes 10 to 11 */
  uint8_t isin_code[12];                            /* bytes 12 to 23 */
  uint8_t a_designated_number_for_an_issue[6];      /* bytes 24 to 29 */
  uint8_t processing_time_of_trading_system[12];    /* bytes 30 to 41 */
  uint8_t trading_price[9];                         /* bytes 42 to 50 */
  uint8_t trading_volume[9];                        /* bytes 51 to 59 */
  uint8_t nearby_month_contract_trading_price[9];   /* bytes 60 to 68 */
  uint8_t distant_month_contract_trading_price[9];  /* bytes 69 to 77 */
  uint8_t opening_price[9];                         /* bytes 78 to 86 */
  uint8_t todays_high[9];                           /* bytes 87 to 95 */
  uint8_t todays_low[9];                            /* bytes 96 to 104 */
  uint8_t previous_price[9];                        /* bytes 105 to 113 */
  uint8_t accumulated_trading_volume[12];           /* bytes 114 to 125 */
  uint8_t accumulated_trading_value[22];            /* bytes 126 to 147 */
  uint8_t final_ask_bid_type_code;                  /* byte 148 */
  uint8_t upper_limit_of_dynamic_price_range[9];    /* bytes 149 to 157 */
  uint8_t lower_limit_of_dynamic_price_range[9];    /* bytes 158 to 166 */
  uint8_t end_keyword;                              /* byte 167 */
} DerivativesOrderFilledMessage;

/* any Derivatives Order Filled Message at all: every byte one the checker chooses */
static void any_derivatives_order_filled_message(DerivativesOrderFilledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->nearby_month_contract_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->distant_month_contract_trading_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->todays_high[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->todays_low[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->previous_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = arbitrary(); }
  record->final_ask_bid_type_code = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->upper_limit_of_dynamic_price_range[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->lower_limit_of_dynamic_price_range[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Derivatives Order Filled Message to the wire: 168 bytes from at, returning where the next byte goes */
static size_t encode_derivatives_order_filled_message(const DerivativesOrderFilledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->trading_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->nearby_month_contract_trading_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->distant_month_contract_trading_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->todays_high[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->todays_low[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->previous_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value[i]; }
  wire[at++] = record->final_ask_bid_type_code;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->upper_limit_of_dynamic_price_range[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->lower_limit_of_dynamic_price_range[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Derivatives Order Filled Message off the wire: 168 bytes from at, returning where the next byte lies */
static size_t decode_derivatives_order_filled_message(DerivativesOrderFilledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->nearby_month_contract_trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->distant_month_contract_trading_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->todays_high[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->todays_low[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->previous_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = wire[at++]; }
  record->final_ask_bid_type_code = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->upper_limit_of_dynamic_price_range[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->lower_limit_of_dynamic_price_range[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Derivatives Order Filled Message is what was written, byte for byte */
static void equal_derivatives_order_filled_message(const DerivativesOrderFilledMessage *read, const DerivativesOrderFilledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->trading_price[i] == written->trading_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->nearby_month_contract_trading_price[i] == written->nearby_month_contract_trading_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->distant_month_contract_trading_price[i] == written->distant_month_contract_trading_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->todays_high[i] == written->todays_high[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->todays_low[i] == written->todays_low[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->previous_price[i] == written->previous_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value[i] == written->accumulated_trading_value[i]); }
  assert(read->final_ask_bid_type_code == written->final_ask_bid_type_code);
  for (size_t i = 0; i < 9; i++) { assert(read->upper_limit_of_dynamic_price_range[i] == written->upper_limit_of_dynamic_price_range[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->lower_limit_of_dynamic_price_range[i] == written->lower_limit_of_dynamic_price_range[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Derivatives Order Filled Message: written and read back, then read and written back */
static void check_derivatives_order_filled_message(void) {
  DerivativesOrderFilledMessage sent;
  DerivativesOrderFilledMessage got;
  uint8_t wire[168];
  uint8_t again[168];

  any_derivatives_order_filled_message(&sent);
  assert(encode_derivatives_order_filled_message(&sent, wire, 0) == 168);
  assert(decode_derivatives_order_filled_message(&got, wire, 0) == 168);
  equal_derivatives_order_filled_message(&got, &sent);

  for (size_t i = 0; i < 168; i++) { wire[i] = arbitrary(); }
  assert(decode_derivatives_order_filled_message(&got, wire, 0) == 168);
  assert(encode_derivatives_order_filled_message(&got, again, 0) == 168);
  for (size_t i = 0; i < 168; i++) { assert(again[i] == wire[i]); }
}

/* ---- Derivatives Negotiated Trade Message: 56 bytes -------------------------- */

/* Derivatives Negotiated Trade Data. Off-book negotiated trades for futures and options. */
typedef struct {
  uint8_t isin_code[12];                         /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue[6];   /* bytes 12 to 17 */
  uint8_t total_accumulated_trading_volume[15];  /* bytes 18 to 32 */
  uint8_t total_accumulated_trading_value[22];   /* bytes 33 to 54 */
  uint8_t end_keyword;                           /* byte 55 */
} DerivativesNegotiatedTradeMessage;

/* any Derivatives Negotiated Trade Message at all: every byte one the checker chooses */
static void any_derivatives_negotiated_trade_message(DerivativesNegotiatedTradeMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->total_accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->total_accumulated_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Derivatives Negotiated Trade Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_derivatives_negotiated_trade_message(const DerivativesNegotiatedTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->total_accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->total_accumulated_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Derivatives Negotiated Trade Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_derivatives_negotiated_trade_message(DerivativesNegotiatedTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->total_accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->total_accumulated_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Derivatives Negotiated Trade Message is what was written, byte for byte */
static void equal_derivatives_negotiated_trade_message(const DerivativesNegotiatedTradeMessage *read, const DerivativesNegotiatedTradeMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->total_accumulated_trading_volume[i] == written->total_accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->total_accumulated_trading_value[i] == written->total_accumulated_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Derivatives Negotiated Trade Message: written and read back, then read and written back */
static void check_derivatives_negotiated_trade_message(void) {
  DerivativesNegotiatedTradeMessage sent;
  DerivativesNegotiatedTradeMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_derivatives_negotiated_trade_message(&sent);
  assert(encode_derivatives_negotiated_trade_message(&sent, wire, 0) == 56);
  assert(decode_derivatives_negotiated_trade_message(&got, wire, 0) == 56);
  equal_derivatives_negotiated_trade_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_derivatives_negotiated_trade_message(&got, wire, 0) == 56);
  assert(encode_derivatives_negotiated_trade_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Derivatives Market Operation Ts Message: 63 bytes ----------------------- */

/* Derivatives Market Operation TS. Per-issue session-state events for futures, options, and other derivatives. */
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
} DerivativesMarketOperationTsMessage;

/* any Derivatives Market Operation Ts Message at all: every byte one the checker chooses */
static void any_derivatives_market_operation_ts_message(DerivativesMarketOperationTsMessage *record) {
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

/* Derivatives Market Operation Ts Message to the wire: 63 bytes from at, returning where the next byte goes */
static size_t encode_derivatives_market_operation_ts_message(const DerivativesMarketOperationTsMessage *record, uint8_t *wire, size_t at) {
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

/* Derivatives Market Operation Ts Message off the wire: 63 bytes from at, returning where the next byte lies */
static size_t decode_derivatives_market_operation_ts_message(DerivativesMarketOperationTsMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Derivatives Market Operation Ts Message is what was written, byte for byte */
static void equal_derivatives_market_operation_ts_message(const DerivativesMarketOperationTsMessage *read, const DerivativesMarketOperationTsMessage *written) {
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

/* Derivatives Market Operation Ts Message: written and read back, then read and written back */
static void check_derivatives_market_operation_ts_message(void) {
  DerivativesMarketOperationTsMessage sent;
  DerivativesMarketOperationTsMessage got;
  uint8_t wire[63];
  uint8_t again[63];

  any_derivatives_market_operation_ts_message(&sent);
  assert(encode_derivatives_market_operation_ts_message(&sent, wire, 0) == 63);
  assert(decode_derivatives_market_operation_ts_message(&got, wire, 0) == 63);
  equal_derivatives_market_operation_ts_message(&got, &sent);

  for (size_t i = 0; i < 63; i++) { wire[i] = arbitrary(); }
  assert(decode_derivatives_market_operation_ts_message(&got, wire, 0) == 63);
  assert(encode_derivatives_market_operation_ts_message(&got, again, 0) == 63);
  for (size_t i = 0; i < 63; i++) { assert(again[i] == wire[i]); }
}

/* ---- Derivatives Issue Closing Message: 73 bytes ----------------------------- */

/* Derivatives Issue Closing. Per-issue closing event for futures and options. */
typedef struct {
  uint8_t message_sequence_number[8];           /* bytes 0 to 7 */
  uint8_t board_id[2];                          /* bytes 8 to 9 */
  uint8_t isin_code[12];                        /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 22 to 27 */
  uint8_t closing_price[9];                     /* bytes 28 to 36 */
  uint8_t closing_price_type_code;              /* byte 37 */
  uint8_t accumulated_trading_volume[12];       /* bytes 38 to 49 */
  uint8_t accumulated_trading_value[22];        /* bytes 50 to 71 */
  uint8_t end_keyword;                          /* byte 72 */
} DerivativesIssueClosingMessage;

/* any Derivatives Issue Closing Message at all: every byte one the checker chooses */
static void any_derivatives_issue_closing_message(DerivativesIssueClosingMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->closing_price[i] = arbitrary(); }
  record->closing_price_type_code = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Derivatives Issue Closing Message to the wire: 73 bytes from at, returning where the next byte goes */
static size_t encode_derivatives_issue_closing_message(const DerivativesIssueClosingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->closing_price[i]; }
  wire[at++] = record->closing_price_type_code;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->accumulated_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Derivatives Issue Closing Message off the wire: 73 bytes from at, returning where the next byte lies */
static size_t decode_derivatives_issue_closing_message(DerivativesIssueClosingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->closing_price[i] = wire[at++]; }
  record->closing_price_type_code = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->accumulated_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Derivatives Issue Closing Message is what was written, byte for byte */
static void equal_derivatives_issue_closing_message(const DerivativesIssueClosingMessage *read, const DerivativesIssueClosingMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  assert(read->closing_price_type_code == written->closing_price_type_code);
  for (size_t i = 0; i < 12; i++) { assert(read->accumulated_trading_volume[i] == written->accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->accumulated_trading_value[i] == written->accumulated_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Derivatives Issue Closing Message: written and read back, then read and written back */
static void check_derivatives_issue_closing_message(void) {
  DerivativesIssueClosingMessage sent;
  DerivativesIssueClosingMessage got;
  uint8_t wire[73];
  uint8_t again[73];

  any_derivatives_issue_closing_message(&sent);
  assert(encode_derivatives_issue_closing_message(&sent, wire, 0) == 73);
  assert(decode_derivatives_issue_closing_message(&got, wire, 0) == 73);
  equal_derivatives_issue_closing_message(&got, &sent);

  for (size_t i = 0; i < 73; i++) { wire[i] = arbitrary(); }
  assert(decode_derivatives_issue_closing_message(&got, wire, 0) == 73);
  assert(encode_derivatives_issue_closing_message(&got, again, 0) == 73);
  for (size_t i = 0; i < 73; i++) { assert(again[i] == wire[i]); }
}

/* ---- Derivatives Market Operation Schedule Message: 78 bytes ----------------- */

/* Derivatives Market Operation Schedule. Session-level schedule and configuration changes. */
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
} DerivativesMarketOperationScheduleMessage;

/* any Derivatives Market Operation Schedule Message at all: every byte one the checker chooses */
static void any_derivatives_market_operation_schedule_message(DerivativesMarketOperationScheduleMessage *record) {
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

/* Derivatives Market Operation Schedule Message to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_derivatives_market_operation_schedule_message(const DerivativesMarketOperationScheduleMessage *record, uint8_t *wire, size_t at) {
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

/* Derivatives Market Operation Schedule Message off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_derivatives_market_operation_schedule_message(DerivativesMarketOperationScheduleMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Derivatives Market Operation Schedule Message is what was written, byte for byte */
static void equal_derivatives_market_operation_schedule_message(const DerivativesMarketOperationScheduleMessage *read, const DerivativesMarketOperationScheduleMessage *written) {
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

/* Derivatives Market Operation Schedule Message: written and read back, then read and written back */
static void check_derivatives_market_operation_schedule_message(void) {
  DerivativesMarketOperationScheduleMessage sent;
  DerivativesMarketOperationScheduleMessage got;
  uint8_t wire[78];
  uint8_t again[78];

  any_derivatives_market_operation_schedule_message(&sent);
  assert(encode_derivatives_market_operation_schedule_message(&sent, wire, 0) == 78);
  assert(decode_derivatives_market_operation_schedule_message(&got, wire, 0) == 78);
  equal_derivatives_market_operation_schedule_message(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_derivatives_market_operation_schedule_message(&got, wire, 0) == 78);
  assert(encode_derivatives_market_operation_schedule_message(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Derivatives Dynamic Upper Lower Limit Message: 60 bytes ----------------- */

/* Derivatives Applying/Removing Dynamic Upper/Lower Limit. Per-issue dynamic price-limit application or removal. */
typedef struct {
  uint8_t message_sequence_number[8];             /* bytes 0 to 7 */
  uint8_t board_id[2];                            /* bytes 8 to 9 */
  uint8_t isin_code[12];                          /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];    /* bytes 22 to 27 */
  uint8_t processing_time_of_trading_system[12];  /* bytes 28 to 39 */
  uint8_t dynamic_price_limit_type_code;          /* byte 40 */
  uint8_t upper_limit_of_dynamic_price_range[9];  /* bytes 41 to 49 */
  uint8_t lower_limit_of_dynamic_price_range[9];  /* bytes 50 to 58 */
  uint8_t end_keyword;                            /* byte 59 */
} DerivativesDynamicUpperLowerLimitMessage;

/* any Derivatives Dynamic Upper Lower Limit Message at all: every byte one the checker chooses */
static void any_derivatives_dynamic_upper_lower_limit_message(DerivativesDynamicUpperLowerLimitMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = arbitrary(); }
  record->dynamic_price_limit_type_code = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->upper_limit_of_dynamic_price_range[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->lower_limit_of_dynamic_price_range[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Derivatives Dynamic Upper Lower Limit Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_derivatives_dynamic_upper_lower_limit_message(const DerivativesDynamicUpperLowerLimitMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->processing_time_of_trading_system[i]; }
  wire[at++] = record->dynamic_price_limit_type_code;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->upper_limit_of_dynamic_price_range[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->lower_limit_of_dynamic_price_range[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Derivatives Dynamic Upper Lower Limit Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_derivatives_dynamic_upper_lower_limit_message(DerivativesDynamicUpperLowerLimitMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->processing_time_of_trading_system[i] = wire[at++]; }
  record->dynamic_price_limit_type_code = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->upper_limit_of_dynamic_price_range[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->lower_limit_of_dynamic_price_range[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Derivatives Dynamic Upper Lower Limit Message is what was written, byte for byte */
static void equal_derivatives_dynamic_upper_lower_limit_message(const DerivativesDynamicUpperLowerLimitMessage *read, const DerivativesDynamicUpperLowerLimitMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->processing_time_of_trading_system[i] == written->processing_time_of_trading_system[i]); }
  assert(read->dynamic_price_limit_type_code == written->dynamic_price_limit_type_code);
  for (size_t i = 0; i < 9; i++) { assert(read->upper_limit_of_dynamic_price_range[i] == written->upper_limit_of_dynamic_price_range[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->lower_limit_of_dynamic_price_range[i] == written->lower_limit_of_dynamic_price_range[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Derivatives Dynamic Upper Lower Limit Message: written and read back, then read and written back */
static void check_derivatives_dynamic_upper_lower_limit_message(void) {
  DerivativesDynamicUpperLowerLimitMessage sent;
  DerivativesDynamicUpperLowerLimitMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_derivatives_dynamic_upper_lower_limit_message(&sent);
  assert(encode_derivatives_dynamic_upper_lower_limit_message(&sent, wire, 0) == 60);
  assert(decode_derivatives_dynamic_upper_lower_limit_message(&got, wire, 0) == 60);
  equal_derivatives_dynamic_upper_lower_limit_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_derivatives_dynamic_upper_lower_limit_message(&got, wire, 0) == 60);
  assert(encode_derivatives_dynamic_upper_lower_limit_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Derivatives Price Limit Range Increase Message: 60 bytes ---------------- */

/* Derivatives Increasing Price Limit Range. Per-issue price-limit range expansion event. */
typedef struct {
  uint8_t message_sequence_number[8];            /* bytes 0 to 7 */
  uint8_t board_id[2];                           /* bytes 8 to 9 */
  uint8_t isin_code[12];                         /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];   /* bytes 22 to 27 */
  uint8_t the_time_imposing_a_price_limit[9];    /* bytes 28 to 36 */
  uint8_t price_limit_expansion_upper_limit[2];  /* bytes 37 to 38 */
  uint8_t price_limit_expansion_lower_limit[2];  /* bytes 39 to 40 */
  uint8_t upper_limit_price[9];                  /* bytes 41 to 49 */
  uint8_t lower_limit_price[9];                  /* bytes 50 to 58 */
  uint8_t end_keyword;                           /* byte 59 */
} DerivativesPriceLimitRangeIncreaseMessage;

/* any Derivatives Price Limit Range Increase Message at all: every byte one the checker chooses */
static void any_derivatives_price_limit_range_increase_message(DerivativesPriceLimitRangeIncreaseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->the_time_imposing_a_price_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_limit_expansion_upper_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_limit_expansion_lower_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->upper_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->lower_limit_price[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Derivatives Price Limit Range Increase Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_derivatives_price_limit_range_increase_message(const DerivativesPriceLimitRangeIncreaseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->the_time_imposing_a_price_limit[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_limit_expansion_upper_limit[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_limit_expansion_lower_limit[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->upper_limit_price[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->lower_limit_price[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Derivatives Price Limit Range Increase Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_derivatives_price_limit_range_increase_message(DerivativesPriceLimitRangeIncreaseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->the_time_imposing_a_price_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_limit_expansion_upper_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_limit_expansion_lower_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->upper_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->lower_limit_price[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Derivatives Price Limit Range Increase Message is what was written, byte for byte */
static void equal_derivatives_price_limit_range_increase_message(const DerivativesPriceLimitRangeIncreaseMessage *read, const DerivativesPriceLimitRangeIncreaseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->the_time_imposing_a_price_limit[i] == written->the_time_imposing_a_price_limit[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_limit_expansion_upper_limit[i] == written->price_limit_expansion_upper_limit[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_limit_expansion_lower_limit[i] == written->price_limit_expansion_lower_limit[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->upper_limit_price[i] == written->upper_limit_price[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->lower_limit_price[i] == written->lower_limit_price[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Derivatives Price Limit Range Increase Message: written and read back, then read and written back */
static void check_derivatives_price_limit_range_increase_message(void) {
  DerivativesPriceLimitRangeIncreaseMessage sent;
  DerivativesPriceLimitRangeIncreaseMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_derivatives_price_limit_range_increase_message(&sent);
  assert(encode_derivatives_price_limit_range_increase_message(&sent, wire, 0) == 60);
  assert(decode_derivatives_price_limit_range_increase_message(&got, wire, 0) == 60);
  equal_derivatives_price_limit_range_increase_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_derivatives_price_limit_range_increase_message(&got, wire, 0) == 60);
  assert(encode_derivatives_price_limit_range_increase_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Derivatives Quantity Allocation Message: 40 bytes ----------------------- */

/* Derivatives Quantity Allocation. Reports the quantity allocated to each price level at a single price trade match. */
typedef struct {
  uint8_t message_sequence_number[8];           /* bytes 0 to 7 */
  uint8_t board_id[2];                          /* bytes 8 to 9 */
  uint8_t isin_code[12];                        /* bytes 10 to 21 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 22 to 27 */
  uint8_t start_end_of_allocation;              /* byte 28 */
  uint8_t allocation_type_code;                 /* byte 29 */
  uint8_t time_when_allocation_ended[9];        /* bytes 30 to 38 */
  uint8_t end_keyword;                          /* byte 39 */
} DerivativesQuantityAllocationMessage;

/* any Derivatives Quantity Allocation Message at all: every byte one the checker chooses */
static void any_derivatives_quantity_allocation_message(DerivativesQuantityAllocationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  record->start_end_of_allocation = arbitrary();
  record->allocation_type_code = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->time_when_allocation_ended[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Derivatives Quantity Allocation Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_derivatives_quantity_allocation_message(const DerivativesQuantityAllocationMessage *record, uint8_t *wire, size_t at) {
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

/* Derivatives Quantity Allocation Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_derivatives_quantity_allocation_message(DerivativesQuantityAllocationMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Derivatives Quantity Allocation Message is what was written, byte for byte */
static void equal_derivatives_quantity_allocation_message(const DerivativesQuantityAllocationMessage *read, const DerivativesQuantityAllocationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  assert(read->start_end_of_allocation == written->start_end_of_allocation);
  assert(read->allocation_type_code == written->allocation_type_code);
  for (size_t i = 0; i < 9; i++) { assert(read->time_when_allocation_ended[i] == written->time_when_allocation_ended[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Derivatives Quantity Allocation Message: written and read back, then read and written back */
static void check_derivatives_quantity_allocation_message(void) {
  DerivativesQuantityAllocationMessage sent;
  DerivativesQuantityAllocationMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_derivatives_quantity_allocation_message(&sent);
  assert(encode_derivatives_quantity_allocation_message(&sent, wire, 0) == 40);
  assert(decode_derivatives_quantity_allocation_message(&got, wire, 0) == 40);
  equal_derivatives_quantity_allocation_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_derivatives_quantity_allocation_message(&got, wire, 0) == 40);
  assert(encode_derivatives_quantity_allocation_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Derivatives Group Order Acceptance Halt Message: 28 bytes --------------- */

/* Derivatives Group Order Acceptance Halt/Release. Matching engine group-order halt and release events for futures and options. */
typedef struct {
  uint8_t market_id[3];                    /* bytes 0 to 2 */
  uint8_t me_group_number[5];              /* bytes 3 to 7 */
  uint8_t board_id[2];                     /* bytes 8 to 9 */
  uint8_t board_event_id[3];               /* bytes 10 to 12 */
  uint8_t board_event_group_code[5];       /* bytes 13 to 17 */
  uint8_t board_event_processing_time[9];  /* bytes 18 to 26 */
  uint8_t end_keyword;                     /* byte 27 */
} DerivativesGroupOrderAcceptanceHaltMessage;

/* any Derivatives Group Order Acceptance Halt Message at all: every byte one the checker chooses */
static void any_derivatives_group_order_acceptance_halt_message(DerivativesGroupOrderAcceptanceHaltMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->me_group_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->board_event_processing_time[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Derivatives Group Order Acceptance Halt Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_derivatives_group_order_acceptance_halt_message(const DerivativesGroupOrderAcceptanceHaltMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->me_group_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->board_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->board_event_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->board_event_group_code[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->board_event_processing_time[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Derivatives Group Order Acceptance Halt Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_derivatives_group_order_acceptance_halt_message(DerivativesGroupOrderAcceptanceHaltMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->me_group_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->board_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->board_event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->board_event_group_code[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->board_event_processing_time[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Derivatives Group Order Acceptance Halt Message is what was written, byte for byte */
static void equal_derivatives_group_order_acceptance_halt_message(const DerivativesGroupOrderAcceptanceHaltMessage *read, const DerivativesGroupOrderAcceptanceHaltMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->me_group_number[i] == written->me_group_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->board_id[i] == written->board_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->board_event_id[i] == written->board_event_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->board_event_group_code[i] == written->board_event_group_code[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->board_event_processing_time[i] == written->board_event_processing_time[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Derivatives Group Order Acceptance Halt Message: written and read back, then read and written back */
static void check_derivatives_group_order_acceptance_halt_message(void) {
  DerivativesGroupOrderAcceptanceHaltMessage sent;
  DerivativesGroupOrderAcceptanceHaltMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_derivatives_group_order_acceptance_halt_message(&sent);
  assert(encode_derivatives_group_order_acceptance_halt_message(&sent, wire, 0) == 28);
  assert(decode_derivatives_group_order_acceptance_halt_message(&got, wire, 0) == 28);
  equal_derivatives_group_order_acceptance_halt_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_derivatives_group_order_acceptance_halt_message(&got, wire, 0) == 28);
  assert(encode_derivatives_group_order_acceptance_halt_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Derivatives Batch Data Message: 1313 bytes ------------------------------ */

/* Derivatives Batch Data. Comprehensive per-issue reference data dumped at start-of-day for futures, options, and other derivatives. */
typedef struct {
  uint8_t message_sequence_number[8];                                            /* bytes 0 to 7 */
  uint8_t total_number_of_instruments_of_the_contract[6];                        /* bytes 8 to 13 */
  uint8_t business_date[8];                                                      /* bytes 14 to 21 */
  uint8_t isin_code[12];                                                         /* bytes 22 to 33 */
  uint8_t a_designated_number_for_an_issue[6];                                   /* bytes 34 to 39 */
  uint8_t futures_options_type_code;                                             /* byte 40 */
  uint8_t product_id[11];                                                        /* bytes 41 to 51 */
  uint8_t abbreviated_issue_code[9];                                             /* bytes 52 to 60 */
  uint8_t issue_name[80];                                                        /* bytes 61 to 140 */
  uint8_t abbreviated_issue_name[40];                                            /* bytes 141 to 180 */
  uint8_t english_issue_name[80];                                                /* bytes 181 to 260 */
  uint8_t abbreviated_issue_name_in_en[40];                                      /* bytes 261 to 300 */
  uint8_t market_operation_product_id[3];                                        /* bytes 301 to 303 */
  uint8_t listing_date[8];                                                       /* bytes 304 to 311 */
  uint8_t delisting_date[8];                                                     /* bytes 312 to 319 */
  uint8_t spread_type_code;                                                      /* byte 320 */
  uint8_t payment_methods;                                                       /* byte 321 */
  uint8_t direction_of_price_limit_expansion_type_code;                          /* byte 322 */
  uint8_t final_stage_of_price_limit_expansion[3];                               /* bytes 323 to 325 */
  uint8_t upper_price_limit_1_st_stage[11];                                      /* bytes 326 to 336 */
  uint8_t upper_price_limit_2_nd_stage[11];                                      /* bytes 337 to 347 */
  uint8_t upper_price_limit_3_rd_stage[11];                                      /* bytes 348 to 358 */
  uint8_t lower_price_limit_1_st_stage[11];                                      /* bytes 359 to 369 */
  uint8_t lower_price_limit_2_nd_stage[11];                                      /* bytes 370 to 380 */
  uint8_t lower_price_limit_3_rd_stage[11];                                      /* bytes 381 to 391 */
  uint8_t base_price[11];                                                        /* bytes 392 to 402 */
  uint8_t underlying_asset_id[3];                                                /* bytes 403 to 405 */
  uint8_t rights_execution_type_code;                                            /* byte 406 */
  uint8_t spread_composition_code[2];                                            /* bytes 407 to 408 */
  uint8_t spread_issue_isin_1[12];                                               /* bytes 409 to 420 */
  uint8_t spread_issue_isin_2[12];                                               /* bytes 421 to 432 */
  uint8_t last_trading_date[8];                                                  /* bytes 433 to 440 */
  uint8_t last_payment_date[8];                                                  /* bytes 441 to 448 */
  uint8_t sequence_number_for_delivery_month[3];                                 /* bytes 449 to 451 */
  uint8_t expiration_date[8];                                                    /* bytes 452 to 459 */
  uint8_t exercise_price[18];                                                    /* bytes 460 to 477 */
  uint8_t base_price_adjustment_type_code;                                       /* byte 478 */
  uint8_t trading_unit[22];                                                      /* bytes 479 to 500 */
  uint8_t trading_multiplier[22];                                                /* bytes 501 to 522 */
  uint8_t type_of_liquidity_providing_lp;                                        /* byte 523 */
  uint8_t listing_type_code;                                                     /* byte 524 */
  uint8_t atm[11];                                                               /* bytes 525 to 535 */
  uint8_t adjustment_reason_code[2];                                             /* bytes 536 to 537 */
  uint8_t isin_of_underlying_asset[12];                                          /* bytes 538 to 549 */
  uint8_t closing_price_of_underlying_asset[11];                                 /* bytes 550 to 560 */
  uint8_t remaining_days[8];                                                     /* bytes 561 to 568 */
  uint8_t adjusted_base_price[18];                                               /* bytes 569 to 586 */
  uint8_t base_price_type_code[2];                                               /* bytes 587 to 588 */
  uint8_t base_price_for_trading_type_code;                                      /* byte 589 */
  uint8_t previous_days_adjusted_closing_price[18];                              /* bytes 590 to 607 */
  uint8_t block_trading_type_code;                                               /* byte 608 */
  uint8_t previous_days_bpmm[23];                                                /* bytes 609 to 631 */
  uint8_t base_price_of_clearing_margins_type_code[2];                           /* bytes 632 to 633 */
  uint8_t theoretical_settlement_price[16];                                      /* bytes 634 to 649 */
  uint8_t base_theoretical_price[16];                                            /* bytes 650 to 665 */
  uint8_t previous_days_settlement_price[18];                                    /* bytes 666 to 683 */
  uint8_t trading_halt;                                                          /* byte 684 */
  uint8_t futures_circuit_breakers_upper_limit_price[11];                        /* bytes 685 to 695 */
  uint8_t futures_circuit_breakers_lower_limit_price[11];                        /* bytes 696 to 706 */
  uint8_t exercise_price_for_displaying_not_for_trading[18];                     /* bytes 707 to 724 */
  uint8_t atm_type_code;                                                         /* byte 725 */
  uint8_t last_trading_day;                                                      /* byte 726 */
  uint8_t dividend_value_for_settlement_price[16];                               /* bytes 727 to 742 */
  uint8_t yesterdays_closing_price[11];                                          /* bytes 743 to 753 */
  uint8_t yesterdays_closing_price_type_code;                                    /* byte 754 */
  uint8_t previous_days_opening_price[11];                                       /* bytes 755 to 765 */
  uint8_t previous_days_high_price[11];                                          /* bytes 766 to 776 */
  uint8_t previous_days_low_price[11];                                           /* bytes 777 to 787 */
  uint8_t the_first_trading_date[8];                                             /* bytes 788 to 795 */
  uint8_t the_last_trading_time[9];                                              /* bytes 796 to 804 */
  uint8_t settlement_price_type_code[2];                                         /* bytes 805 to 806 */
  uint8_t disparate_ratio[13];                                                   /* bytes 807 to 819 */
  uint8_t previous_days_open_interest[12];                                       /* bytes 820 to 831 */
  uint8_t previous_days_best_ask[11];                                            /* bytes 832 to 842 */
  uint8_t previous_days_best_bid[11];                                            /* bytes 843 to 853 */
  uint8_t implied_volatility[11];                                                /* bytes 854 to 864 */
  uint8_t the_highest_premium_of_the_lifetime[11];                               /* bytes 865 to 875 */
  uint8_t the_lowest_premium_of_the_lifetime[11];                                /* bytes 876 to 886 */
  uint8_t the_highest_premium_in_a_year[11];                                     /* bytes 887 to 897 */
  uint8_t the_lowest_premium_in_a_year[11];                                      /* bytes 898 to 908 */
  uint8_t the_date_of_the_highest_premium_of_the_lifetime[8];                    /* bytes 909 to 916 */
  uint8_t the_date_of_the_lowest_premium_of_the_lifetime[8];                     /* bytes 917 to 924 */
  uint8_t the_date_of_the_highest_premium_in_a_year[8];                          /* bytes 925 to 932 */
  uint8_t the_date_of_the_lowest_premium_in_a_year[8];                           /* bytes 933 to 940 */
  uint8_t number_of_listing_days_per_year[8];                                    /* bytes 941 to 948 */
  uint8_t number_of_trading_days_per_month[8];                                   /* bytes 949 to 956 */
  uint8_t number_of_trading_days_per_year[8];                                    /* bytes 957 to 964 */
  uint8_t number_of_previous_days_trading[15];                                   /* bytes 965 to 979 */
  uint8_t yesterdays_accumulated_trading_amount[12];                             /* bytes 980 to 991 */
  uint8_t yesterdays_accumulated_trading_value[22];                              /* bytes 992 to 1013 */
  uint8_t previous_days_total_accumulated_trading_volume[15];                    /* bytes 1014 to 1028 */
  uint8_t previous_days_total_accumulated_trading_value[22];                     /* bytes 1029 to 1050 */
  uint8_t interest_rate[11];                                                     /* bytes 1051 to 1061 */
  uint8_t open_interest_limit_quantity[15];                                      /* bytes 1062 to 1076 */
  uint8_t underlying_asset_product_id[4];                                        /* bytes 1077 to 1080 */
  uint8_t offset_rate_of_asset_group[11];                                        /* bytes 1081 to 1091 */
  uint8_t limit_order_permission_type_code[5];                                   /* bytes 1092 to 1096 */
  uint8_t market_price_order_permission_type_code[5];                            /* bytes 1097 to 1101 */
  uint8_t conditioned_order_permission_type_code[5];                             /* bytes 1102 to 1106 */
  uint8_t best_favorable_order_permission_type_code[5];                          /* bytes 1107 to 1111 */
  uint8_t efp_trading_item;                                                      /* byte 1112 */
  uint8_t flex_trading_item;                                                     /* byte 1113 */
  uint8_t efp_trading_volume[12];                                                /* bytes 1114 to 1125 */
  uint8_t efp_trading_value[22];                                                 /* bytes 1126 to 1147 */
  uint8_t market_holidays;                                                       /* byte 1148 */
  uint8_t limitation_of_dynamic_price;                                           /* byte 1149 */
  uint8_t gap_between_upper_limit_price_of_dynamic_price_and_trading_value[11];  /* bytes 1150 to 1160 */
  uint8_t gap_between_lower_limit_price_of_dynamic_price_and_trading_value[11];  /* bytes 1161 to 1171 */
  uint8_t underlying_asset_market_id[3];                                         /* bytes 1172 to 1174 */
  uint8_t upper_limit_quantity[23];                                              /* bytes 1175 to 1197 */
  uint8_t lower_limit_quantity[23];                                              /* bytes 1198 to 1220 */
  uint8_t upper_limit_quantity_for_block_trade[23];                              /* bytes 1221 to 1243 */
  uint8_t lower_limit_quantity_for_block_trade[23];                              /* bytes 1244 to 1266 */
  uint8_t base_product_id[11];                                                   /* bytes 1267 to 1277 */
  uint8_t subsidiary_product_id[11];                                             /* bytes 1278 to 1288 */
  uint8_t number_of_issues_for_base_product[6];                                  /* bytes 1289 to 1294 */
  uint8_t number_of_issues_for_subsidiary_product[6];                            /* bytes 1295 to 1300 */
  uint8_t settlement_week[2];                                                    /* bytes 1301 to 1302 */
  uint8_t suspended_stocks;                                                      /* byte 1303 */
  uint8_t designation_date_for_suspended_stocks[8];                              /* bytes 1304 to 1311 */
  uint8_t end_keyword;                                                           /* byte 1312 */
} DerivativesBatchDataMessage;

/* any Derivatives Batch Data Message at all: every byte one the checker chooses */
static void any_derivatives_batch_data_message(DerivativesBatchDataMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_instruments_of_the_contract[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  record->futures_options_type_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->abbreviated_issue_code[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->english_issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name_in_en[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->delisting_date[i] = arbitrary(); }
  record->spread_type_code = arbitrary();
  record->payment_methods = arbitrary();
  record->direction_of_price_limit_expansion_type_code = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->final_stage_of_price_limit_expansion[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->upper_price_limit_1_st_stage[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->upper_price_limit_2_nd_stage[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->upper_price_limit_3_rd_stage[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lower_price_limit_1_st_stage[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lower_price_limit_2_nd_stage[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->lower_price_limit_3_rd_stage[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->underlying_asset_id[i] = arbitrary(); }
  record->rights_execution_type_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->spread_composition_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->spread_issue_isin_1[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->spread_issue_isin_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_payment_date[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->sequence_number_for_delivery_month[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->exercise_price[i] = arbitrary(); }
  record->base_price_adjustment_type_code = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->trading_unit[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->trading_multiplier[i] = arbitrary(); }
  record->type_of_liquidity_providing_lp = arbitrary();
  record->listing_type_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->atm[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->adjustment_reason_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_of_underlying_asset[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->closing_price_of_underlying_asset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->remaining_days[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->adjusted_base_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->base_price_type_code[i] = arbitrary(); }
  record->base_price_for_trading_type_code = arbitrary();
  for (size_t i = 0; i < 18; i++) { record->previous_days_adjusted_closing_price[i] = arbitrary(); }
  record->block_trading_type_code = arbitrary();
  for (size_t i = 0; i < 23; i++) { record->previous_days_bpmm[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->base_price_of_clearing_margins_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->theoretical_settlement_price[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->base_theoretical_price[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->previous_days_settlement_price[i] = arbitrary(); }
  record->trading_halt = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->futures_circuit_breakers_upper_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->futures_circuit_breakers_lower_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->exercise_price_for_displaying_not_for_trading[i] = arbitrary(); }
  record->atm_type_code = arbitrary();
  record->last_trading_day = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->dividend_value_for_settlement_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->yesterdays_closing_price[i] = arbitrary(); }
  record->yesterdays_closing_price_type_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->previous_days_opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->previous_days_high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->previous_days_low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->the_first_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->the_last_trading_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->settlement_price_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->disparate_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->previous_days_open_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->previous_days_best_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->previous_days_best_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->implied_volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->the_highest_premium_of_the_lifetime[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->the_lowest_premium_of_the_lifetime[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->the_highest_premium_in_a_year[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->the_lowest_premium_in_a_year[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->the_date_of_the_highest_premium_of_the_lifetime[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->the_date_of_the_lowest_premium_of_the_lifetime[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->the_date_of_the_highest_premium_in_a_year[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->the_date_of_the_lowest_premium_in_a_year[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->number_of_listing_days_per_year[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->number_of_trading_days_per_month[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->number_of_trading_days_per_year[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->number_of_previous_days_trading[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->yesterdays_accumulated_trading_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->yesterdays_accumulated_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->previous_days_total_accumulated_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->previous_days_total_accumulated_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->interest_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->open_interest_limit_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_asset_product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->offset_rate_of_asset_group[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->limit_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->market_price_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->conditioned_order_permission_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->best_favorable_order_permission_type_code[i] = arbitrary(); }
  record->efp_trading_item = arbitrary();
  record->flex_trading_item = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->efp_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->efp_trading_value[i] = arbitrary(); }
  record->market_holidays = arbitrary();
  record->limitation_of_dynamic_price = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->gap_between_upper_limit_price_of_dynamic_price_and_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->gap_between_lower_limit_price_of_dynamic_price_and_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->underlying_asset_market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 23; i++) { record->upper_limit_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 23; i++) { record->lower_limit_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 23; i++) { record->upper_limit_quantity_for_block_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 23; i++) { record->lower_limit_quantity_for_block_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->base_product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->subsidiary_product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->number_of_issues_for_base_product[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->number_of_issues_for_subsidiary_product[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->settlement_week[i] = arbitrary(); }
  record->suspended_stocks = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->designation_date_for_suspended_stocks[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Derivatives Batch Data Message to the wire: 1313 bytes from at, returning where the next byte goes */
static size_t encode_derivatives_batch_data_message(const DerivativesBatchDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->total_number_of_instruments_of_the_contract[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  wire[at++] = record->futures_options_type_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->abbreviated_issue_code[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->issue_name[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->english_issue_name[i]; }
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->abbreviated_issue_name_in_en[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->market_operation_product_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->listing_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->delisting_date[i]; }
  wire[at++] = record->spread_type_code;
  wire[at++] = record->payment_methods;
  wire[at++] = record->direction_of_price_limit_expansion_type_code;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->final_stage_of_price_limit_expansion[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->upper_price_limit_1_st_stage[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->upper_price_limit_2_nd_stage[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->upper_price_limit_3_rd_stage[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lower_price_limit_1_st_stage[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lower_price_limit_2_nd_stage[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->lower_price_limit_3_rd_stage[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->base_price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->underlying_asset_id[i]; }
  wire[at++] = record->rights_execution_type_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->spread_composition_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->spread_issue_isin_1[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->spread_issue_isin_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_trading_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_payment_date[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->sequence_number_for_delivery_month[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->exercise_price[i]; }
  wire[at++] = record->base_price_adjustment_type_code;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->trading_unit[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->trading_multiplier[i]; }
  wire[at++] = record->type_of_liquidity_providing_lp;
  wire[at++] = record->listing_type_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->atm[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->adjustment_reason_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_of_underlying_asset[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->closing_price_of_underlying_asset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->remaining_days[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->adjusted_base_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->base_price_type_code[i]; }
  wire[at++] = record->base_price_for_trading_type_code;
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->previous_days_adjusted_closing_price[i]; }
  wire[at++] = record->block_trading_type_code;
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->previous_days_bpmm[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->base_price_of_clearing_margins_type_code[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->theoretical_settlement_price[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->base_theoretical_price[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->previous_days_settlement_price[i]; }
  wire[at++] = record->trading_halt;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->futures_circuit_breakers_upper_limit_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->futures_circuit_breakers_lower_limit_price[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->exercise_price_for_displaying_not_for_trading[i]; }
  wire[at++] = record->atm_type_code;
  wire[at++] = record->last_trading_day;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->dividend_value_for_settlement_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->yesterdays_closing_price[i]; }
  wire[at++] = record->yesterdays_closing_price_type_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->previous_days_opening_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->previous_days_high_price[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->previous_days_low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->the_first_trading_date[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->the_last_trading_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->settlement_price_type_code[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->disparate_ratio[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->previous_days_open_interest[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->previous_days_best_ask[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->previous_days_best_bid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->implied_volatility[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->the_highest_premium_of_the_lifetime[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->the_lowest_premium_of_the_lifetime[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->the_highest_premium_in_a_year[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->the_lowest_premium_in_a_year[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->the_date_of_the_highest_premium_of_the_lifetime[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->the_date_of_the_lowest_premium_of_the_lifetime[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->the_date_of_the_highest_premium_in_a_year[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->the_date_of_the_lowest_premium_in_a_year[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->number_of_listing_days_per_year[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->number_of_trading_days_per_month[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->number_of_trading_days_per_year[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->number_of_previous_days_trading[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->yesterdays_accumulated_trading_amount[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->yesterdays_accumulated_trading_value[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->previous_days_total_accumulated_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->previous_days_total_accumulated_trading_value[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->interest_rate[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->open_interest_limit_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_asset_product_id[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->offset_rate_of_asset_group[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->limit_order_permission_type_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->market_price_order_permission_type_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->conditioned_order_permission_type_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->best_favorable_order_permission_type_code[i]; }
  wire[at++] = record->efp_trading_item;
  wire[at++] = record->flex_trading_item;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->efp_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->efp_trading_value[i]; }
  wire[at++] = record->market_holidays;
  wire[at++] = record->limitation_of_dynamic_price;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->gap_between_upper_limit_price_of_dynamic_price_and_trading_value[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->gap_between_lower_limit_price_of_dynamic_price_and_trading_value[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->underlying_asset_market_id[i]; }
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->upper_limit_quantity[i]; }
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->lower_limit_quantity[i]; }
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->upper_limit_quantity_for_block_trade[i]; }
  for (size_t i = 0; i < 23; i++) { wire[at++] = record->lower_limit_quantity_for_block_trade[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->base_product_id[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->subsidiary_product_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->number_of_issues_for_base_product[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->number_of_issues_for_subsidiary_product[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->settlement_week[i]; }
  wire[at++] = record->suspended_stocks;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->designation_date_for_suspended_stocks[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Derivatives Batch Data Message off the wire: 1313 bytes from at, returning where the next byte lies */
static size_t decode_derivatives_batch_data_message(DerivativesBatchDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->total_number_of_instruments_of_the_contract[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  record->futures_options_type_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->abbreviated_issue_code[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->english_issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 40; i++) { record->abbreviated_issue_name_in_en[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->market_operation_product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->listing_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->delisting_date[i] = wire[at++]; }
  record->spread_type_code = wire[at++];
  record->payment_methods = wire[at++];
  record->direction_of_price_limit_expansion_type_code = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->final_stage_of_price_limit_expansion[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->upper_price_limit_1_st_stage[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->upper_price_limit_2_nd_stage[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->upper_price_limit_3_rd_stage[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lower_price_limit_1_st_stage[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lower_price_limit_2_nd_stage[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->lower_price_limit_3_rd_stage[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->base_price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->underlying_asset_id[i] = wire[at++]; }
  record->rights_execution_type_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->spread_composition_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->spread_issue_isin_1[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->spread_issue_isin_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_payment_date[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->sequence_number_for_delivery_month[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->exercise_price[i] = wire[at++]; }
  record->base_price_adjustment_type_code = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->trading_unit[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->trading_multiplier[i] = wire[at++]; }
  record->type_of_liquidity_providing_lp = wire[at++];
  record->listing_type_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->atm[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->adjustment_reason_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_of_underlying_asset[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->closing_price_of_underlying_asset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->remaining_days[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->adjusted_base_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->base_price_type_code[i] = wire[at++]; }
  record->base_price_for_trading_type_code = wire[at++];
  for (size_t i = 0; i < 18; i++) { record->previous_days_adjusted_closing_price[i] = wire[at++]; }
  record->block_trading_type_code = wire[at++];
  for (size_t i = 0; i < 23; i++) { record->previous_days_bpmm[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->base_price_of_clearing_margins_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->theoretical_settlement_price[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->base_theoretical_price[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->previous_days_settlement_price[i] = wire[at++]; }
  record->trading_halt = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->futures_circuit_breakers_upper_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->futures_circuit_breakers_lower_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->exercise_price_for_displaying_not_for_trading[i] = wire[at++]; }
  record->atm_type_code = wire[at++];
  record->last_trading_day = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->dividend_value_for_settlement_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->yesterdays_closing_price[i] = wire[at++]; }
  record->yesterdays_closing_price_type_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->previous_days_opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->previous_days_high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->previous_days_low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->the_first_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->the_last_trading_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->settlement_price_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->disparate_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->previous_days_open_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->previous_days_best_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->previous_days_best_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->implied_volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->the_highest_premium_of_the_lifetime[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->the_lowest_premium_of_the_lifetime[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->the_highest_premium_in_a_year[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->the_lowest_premium_in_a_year[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->the_date_of_the_highest_premium_of_the_lifetime[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->the_date_of_the_lowest_premium_of_the_lifetime[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->the_date_of_the_highest_premium_in_a_year[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->the_date_of_the_lowest_premium_in_a_year[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->number_of_listing_days_per_year[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->number_of_trading_days_per_month[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->number_of_trading_days_per_year[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->number_of_previous_days_trading[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->yesterdays_accumulated_trading_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->yesterdays_accumulated_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->previous_days_total_accumulated_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->previous_days_total_accumulated_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->interest_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->open_interest_limit_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_asset_product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->offset_rate_of_asset_group[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->limit_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->market_price_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->conditioned_order_permission_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->best_favorable_order_permission_type_code[i] = wire[at++]; }
  record->efp_trading_item = wire[at++];
  record->flex_trading_item = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->efp_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->efp_trading_value[i] = wire[at++]; }
  record->market_holidays = wire[at++];
  record->limitation_of_dynamic_price = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->gap_between_upper_limit_price_of_dynamic_price_and_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->gap_between_lower_limit_price_of_dynamic_price_and_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->underlying_asset_market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 23; i++) { record->upper_limit_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 23; i++) { record->lower_limit_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 23; i++) { record->upper_limit_quantity_for_block_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 23; i++) { record->lower_limit_quantity_for_block_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->base_product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->subsidiary_product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->number_of_issues_for_base_product[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->number_of_issues_for_subsidiary_product[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->settlement_week[i] = wire[at++]; }
  record->suspended_stocks = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->designation_date_for_suspended_stocks[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Derivatives Batch Data Message is what was written, byte for byte */
static void equal_derivatives_batch_data_message(const DerivativesBatchDataMessage *read, const DerivativesBatchDataMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->total_number_of_instruments_of_the_contract[i] == written->total_number_of_instruments_of_the_contract[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  assert(read->futures_options_type_code == written->futures_options_type_code);
  for (size_t i = 0; i < 11; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->abbreviated_issue_code[i] == written->abbreviated_issue_code[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->issue_name[i] == written->issue_name[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name[i] == written->abbreviated_issue_name[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->english_issue_name[i] == written->english_issue_name[i]); }
  for (size_t i = 0; i < 40; i++) { assert(read->abbreviated_issue_name_in_en[i] == written->abbreviated_issue_name_in_en[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->market_operation_product_id[i] == written->market_operation_product_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->listing_date[i] == written->listing_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->delisting_date[i] == written->delisting_date[i]); }
  assert(read->spread_type_code == written->spread_type_code);
  assert(read->payment_methods == written->payment_methods);
  assert(read->direction_of_price_limit_expansion_type_code == written->direction_of_price_limit_expansion_type_code);
  for (size_t i = 0; i < 3; i++) { assert(read->final_stage_of_price_limit_expansion[i] == written->final_stage_of_price_limit_expansion[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->upper_price_limit_1_st_stage[i] == written->upper_price_limit_1_st_stage[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->upper_price_limit_2_nd_stage[i] == written->upper_price_limit_2_nd_stage[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->upper_price_limit_3_rd_stage[i] == written->upper_price_limit_3_rd_stage[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lower_price_limit_1_st_stage[i] == written->lower_price_limit_1_st_stage[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lower_price_limit_2_nd_stage[i] == written->lower_price_limit_2_nd_stage[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->lower_price_limit_3_rd_stage[i] == written->lower_price_limit_3_rd_stage[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->base_price[i] == written->base_price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->underlying_asset_id[i] == written->underlying_asset_id[i]); }
  assert(read->rights_execution_type_code == written->rights_execution_type_code);
  for (size_t i = 0; i < 2; i++) { assert(read->spread_composition_code[i] == written->spread_composition_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->spread_issue_isin_1[i] == written->spread_issue_isin_1[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->spread_issue_isin_2[i] == written->spread_issue_isin_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_trading_date[i] == written->last_trading_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_payment_date[i] == written->last_payment_date[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->sequence_number_for_delivery_month[i] == written->sequence_number_for_delivery_month[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->exercise_price[i] == written->exercise_price[i]); }
  assert(read->base_price_adjustment_type_code == written->base_price_adjustment_type_code);
  for (size_t i = 0; i < 22; i++) { assert(read->trading_unit[i] == written->trading_unit[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->trading_multiplier[i] == written->trading_multiplier[i]); }
  assert(read->type_of_liquidity_providing_lp == written->type_of_liquidity_providing_lp);
  assert(read->listing_type_code == written->listing_type_code);
  for (size_t i = 0; i < 11; i++) { assert(read->atm[i] == written->atm[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->adjustment_reason_code[i] == written->adjustment_reason_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_of_underlying_asset[i] == written->isin_of_underlying_asset[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->closing_price_of_underlying_asset[i] == written->closing_price_of_underlying_asset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->remaining_days[i] == written->remaining_days[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->adjusted_base_price[i] == written->adjusted_base_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->base_price_type_code[i] == written->base_price_type_code[i]); }
  assert(read->base_price_for_trading_type_code == written->base_price_for_trading_type_code);
  for (size_t i = 0; i < 18; i++) { assert(read->previous_days_adjusted_closing_price[i] == written->previous_days_adjusted_closing_price[i]); }
  assert(read->block_trading_type_code == written->block_trading_type_code);
  for (size_t i = 0; i < 23; i++) { assert(read->previous_days_bpmm[i] == written->previous_days_bpmm[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->base_price_of_clearing_margins_type_code[i] == written->base_price_of_clearing_margins_type_code[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->theoretical_settlement_price[i] == written->theoretical_settlement_price[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->base_theoretical_price[i] == written->base_theoretical_price[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->previous_days_settlement_price[i] == written->previous_days_settlement_price[i]); }
  assert(read->trading_halt == written->trading_halt);
  for (size_t i = 0; i < 11; i++) { assert(read->futures_circuit_breakers_upper_limit_price[i] == written->futures_circuit_breakers_upper_limit_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->futures_circuit_breakers_lower_limit_price[i] == written->futures_circuit_breakers_lower_limit_price[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->exercise_price_for_displaying_not_for_trading[i] == written->exercise_price_for_displaying_not_for_trading[i]); }
  assert(read->atm_type_code == written->atm_type_code);
  assert(read->last_trading_day == written->last_trading_day);
  for (size_t i = 0; i < 16; i++) { assert(read->dividend_value_for_settlement_price[i] == written->dividend_value_for_settlement_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->yesterdays_closing_price[i] == written->yesterdays_closing_price[i]); }
  assert(read->yesterdays_closing_price_type_code == written->yesterdays_closing_price_type_code);
  for (size_t i = 0; i < 11; i++) { assert(read->previous_days_opening_price[i] == written->previous_days_opening_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->previous_days_high_price[i] == written->previous_days_high_price[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->previous_days_low_price[i] == written->previous_days_low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->the_first_trading_date[i] == written->the_first_trading_date[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->the_last_trading_time[i] == written->the_last_trading_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->settlement_price_type_code[i] == written->settlement_price_type_code[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->disparate_ratio[i] == written->disparate_ratio[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->previous_days_open_interest[i] == written->previous_days_open_interest[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->previous_days_best_ask[i] == written->previous_days_best_ask[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->previous_days_best_bid[i] == written->previous_days_best_bid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->implied_volatility[i] == written->implied_volatility[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->the_highest_premium_of_the_lifetime[i] == written->the_highest_premium_of_the_lifetime[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->the_lowest_premium_of_the_lifetime[i] == written->the_lowest_premium_of_the_lifetime[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->the_highest_premium_in_a_year[i] == written->the_highest_premium_in_a_year[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->the_lowest_premium_in_a_year[i] == written->the_lowest_premium_in_a_year[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->the_date_of_the_highest_premium_of_the_lifetime[i] == written->the_date_of_the_highest_premium_of_the_lifetime[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->the_date_of_the_lowest_premium_of_the_lifetime[i] == written->the_date_of_the_lowest_premium_of_the_lifetime[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->the_date_of_the_highest_premium_in_a_year[i] == written->the_date_of_the_highest_premium_in_a_year[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->the_date_of_the_lowest_premium_in_a_year[i] == written->the_date_of_the_lowest_premium_in_a_year[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->number_of_listing_days_per_year[i] == written->number_of_listing_days_per_year[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->number_of_trading_days_per_month[i] == written->number_of_trading_days_per_month[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->number_of_trading_days_per_year[i] == written->number_of_trading_days_per_year[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->number_of_previous_days_trading[i] == written->number_of_previous_days_trading[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->yesterdays_accumulated_trading_amount[i] == written->yesterdays_accumulated_trading_amount[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->yesterdays_accumulated_trading_value[i] == written->yesterdays_accumulated_trading_value[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->previous_days_total_accumulated_trading_volume[i] == written->previous_days_total_accumulated_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->previous_days_total_accumulated_trading_value[i] == written->previous_days_total_accumulated_trading_value[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->interest_rate[i] == written->interest_rate[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->open_interest_limit_quantity[i] == written->open_interest_limit_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_asset_product_id[i] == written->underlying_asset_product_id[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->offset_rate_of_asset_group[i] == written->offset_rate_of_asset_group[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->limit_order_permission_type_code[i] == written->limit_order_permission_type_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->market_price_order_permission_type_code[i] == written->market_price_order_permission_type_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->conditioned_order_permission_type_code[i] == written->conditioned_order_permission_type_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->best_favorable_order_permission_type_code[i] == written->best_favorable_order_permission_type_code[i]); }
  assert(read->efp_trading_item == written->efp_trading_item);
  assert(read->flex_trading_item == written->flex_trading_item);
  for (size_t i = 0; i < 12; i++) { assert(read->efp_trading_volume[i] == written->efp_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->efp_trading_value[i] == written->efp_trading_value[i]); }
  assert(read->market_holidays == written->market_holidays);
  assert(read->limitation_of_dynamic_price == written->limitation_of_dynamic_price);
  for (size_t i = 0; i < 11; i++) { assert(read->gap_between_upper_limit_price_of_dynamic_price_and_trading_value[i] == written->gap_between_upper_limit_price_of_dynamic_price_and_trading_value[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->gap_between_lower_limit_price_of_dynamic_price_and_trading_value[i] == written->gap_between_lower_limit_price_of_dynamic_price_and_trading_value[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->underlying_asset_market_id[i] == written->underlying_asset_market_id[i]); }
  for (size_t i = 0; i < 23; i++) { assert(read->upper_limit_quantity[i] == written->upper_limit_quantity[i]); }
  for (size_t i = 0; i < 23; i++) { assert(read->lower_limit_quantity[i] == written->lower_limit_quantity[i]); }
  for (size_t i = 0; i < 23; i++) { assert(read->upper_limit_quantity_for_block_trade[i] == written->upper_limit_quantity_for_block_trade[i]); }
  for (size_t i = 0; i < 23; i++) { assert(read->lower_limit_quantity_for_block_trade[i] == written->lower_limit_quantity_for_block_trade[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->base_product_id[i] == written->base_product_id[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->subsidiary_product_id[i] == written->subsidiary_product_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->number_of_issues_for_base_product[i] == written->number_of_issues_for_base_product[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->number_of_issues_for_subsidiary_product[i] == written->number_of_issues_for_subsidiary_product[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->settlement_week[i] == written->settlement_week[i]); }
  assert(read->suspended_stocks == written->suspended_stocks);
  for (size_t i = 0; i < 8; i++) { assert(read->designation_date_for_suspended_stocks[i] == written->designation_date_for_suspended_stocks[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Derivatives Batch Data Message: written and read back, then read and written back */
static void check_derivatives_batch_data_message(void) {
  DerivativesBatchDataMessage sent;
  DerivativesBatchDataMessage got;
  uint8_t wire[1313];
  uint8_t again[1313];

  any_derivatives_batch_data_message(&sent);
  assert(encode_derivatives_batch_data_message(&sent, wire, 0) == 1313);
  assert(decode_derivatives_batch_data_message(&got, wire, 0) == 1313);
  equal_derivatives_batch_data_message(&got, &sent);

  for (size_t i = 0; i < 1313; i++) { wire[i] = arbitrary(); }
  assert(decode_derivatives_batch_data_message(&got, wire, 0) == 1313);
  assert(encode_derivatives_batch_data_message(&got, again, 0) == 1313);
  for (size_t i = 0; i < 1313; i++) { assert(again[i] == wire[i]); }
}

/* ---- Equity Derivatives Adjustment Details Message: 151 bytes ---------------- */

/* Equity Derivatives Adjustment Details. Corporate-action and contract-spec adjustments to equity-derivatives positions. */
typedef struct {
  uint8_t message_sequence_number[8];                                                  /* bytes 0 to 7 */
  uint8_t business_date[8];                                                            /* bytes 8 to 15 */
  uint8_t isin_code[12];                                                               /* bytes 16 to 27 */
  uint8_t denominator_coefficient_of_adjustment[18];                                   /* bytes 28 to 45 */
  uint8_t numerator_adjustment_of_coefficient[18];                                     /* bytes 46 to 63 */
  uint8_t trading_multiplier_before_adjustment[22];                                    /* bytes 64 to 85 */
  uint8_t trading_multiplier_after_adjustment_equity_options_10[22];                   /* bytes 86 to 107 */
  uint8_t exercise_price_before_adjustment[18];                                        /* bytes 108 to 125 */
  uint8_t exercise_price_after_adjustment[18];                                         /* bytes 126 to 143 */
  uint8_t adjustment_coefficient_of_open_intetest_volumes_that_have_been_adjusted[6];  /* bytes 144 to 149 */
  uint8_t end_keyword;                                                                 /* byte 150 */
} EquityDerivativesAdjustmentDetailsMessage;

/* any Equity Derivatives Adjustment Details Message at all: every byte one the checker chooses */
static void any_equity_derivatives_adjustment_details_message(EquityDerivativesAdjustmentDetailsMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->denominator_coefficient_of_adjustment[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->numerator_adjustment_of_coefficient[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->trading_multiplier_before_adjustment[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->trading_multiplier_after_adjustment_equity_options_10[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->exercise_price_before_adjustment[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->exercise_price_after_adjustment[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->adjustment_coefficient_of_open_intetest_volumes_that_have_been_adjusted[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Equity Derivatives Adjustment Details Message to the wire: 151 bytes from at, returning where the next byte goes */
static size_t encode_equity_derivatives_adjustment_details_message(const EquityDerivativesAdjustmentDetailsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->business_date[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->denominator_coefficient_of_adjustment[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->numerator_adjustment_of_coefficient[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->trading_multiplier_before_adjustment[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->trading_multiplier_after_adjustment_equity_options_10[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->exercise_price_before_adjustment[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->exercise_price_after_adjustment[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->adjustment_coefficient_of_open_intetest_volumes_that_have_been_adjusted[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Equity Derivatives Adjustment Details Message off the wire: 151 bytes from at, returning where the next byte lies */
static size_t decode_equity_derivatives_adjustment_details_message(EquityDerivativesAdjustmentDetailsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->business_date[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->denominator_coefficient_of_adjustment[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->numerator_adjustment_of_coefficient[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->trading_multiplier_before_adjustment[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->trading_multiplier_after_adjustment_equity_options_10[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->exercise_price_before_adjustment[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->exercise_price_after_adjustment[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->adjustment_coefficient_of_open_intetest_volumes_that_have_been_adjusted[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Equity Derivatives Adjustment Details Message is what was written, byte for byte */
static void equal_equity_derivatives_adjustment_details_message(const EquityDerivativesAdjustmentDetailsMessage *read, const EquityDerivativesAdjustmentDetailsMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->business_date[i] == written->business_date[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->denominator_coefficient_of_adjustment[i] == written->denominator_coefficient_of_adjustment[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->numerator_adjustment_of_coefficient[i] == written->numerator_adjustment_of_coefficient[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->trading_multiplier_before_adjustment[i] == written->trading_multiplier_before_adjustment[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->trading_multiplier_after_adjustment_equity_options_10[i] == written->trading_multiplier_after_adjustment_equity_options_10[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->exercise_price_before_adjustment[i] == written->exercise_price_before_adjustment[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->exercise_price_after_adjustment[i] == written->exercise_price_after_adjustment[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->adjustment_coefficient_of_open_intetest_volumes_that_have_been_adjusted[i] == written->adjustment_coefficient_of_open_intetest_volumes_that_have_been_adjusted[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Equity Derivatives Adjustment Details Message: written and read back, then read and written back */
static void check_equity_derivatives_adjustment_details_message(void) {
  EquityDerivativesAdjustmentDetailsMessage sent;
  EquityDerivativesAdjustmentDetailsMessage got;
  uint8_t wire[151];
  uint8_t again[151];

  any_equity_derivatives_adjustment_details_message(&sent);
  assert(encode_equity_derivatives_adjustment_details_message(&sent, wire, 0) == 151);
  assert(decode_equity_derivatives_adjustment_details_message(&got, wire, 0) == 151);
  equal_equity_derivatives_adjustment_details_message(&got, &sent);

  for (size_t i = 0; i < 151; i++) { wire[i] = arbitrary(); }
  assert(decode_equity_derivatives_adjustment_details_message(&got, wire, 0) == 151);
  assert(encode_equity_derivatives_adjustment_details_message(&got, again, 0) == 151);
  for (size_t i = 0; i < 151; i++) { assert(again[i] == wire[i]); }
}

/* ---- Commodity Futures Settlement Reference Ktb Message: 66 bytes ------------ */

/* Commodity Futures Settlement Reference for KTB. */
typedef struct {
  uint8_t message_sequence_number[8];          /* bytes 0 to 7 */
  uint8_t application_date[8];                 /* bytes 8 to 15 */
  uint8_t underlying_asset_id[3];              /* bytes 16 to 18 */
  uint8_t ktb_isin[12];                        /* bytes 19 to 30 */
  uint8_t isin_of_base_issue_for_payment[12];  /* bytes 31 to 42 */
  uint8_t conversion_factor[22];               /* bytes 43 to 64 */
  uint8_t end_keyword;                         /* byte 65 */
} CommodityFuturesSettlementReferenceKtbMessage;

/* any Commodity Futures Settlement Reference Ktb Message at all: every byte one the checker chooses */
static void any_commodity_futures_settlement_reference_ktb_message(CommodityFuturesSettlementReferenceKtbMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->application_date[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->underlying_asset_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ktb_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_of_base_issue_for_payment[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->conversion_factor[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Commodity Futures Settlement Reference Ktb Message to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_commodity_futures_settlement_reference_ktb_message(const CommodityFuturesSettlementReferenceKtbMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->application_date[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->underlying_asset_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ktb_isin[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_of_base_issue_for_payment[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->conversion_factor[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Commodity Futures Settlement Reference Ktb Message off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_commodity_futures_settlement_reference_ktb_message(CommodityFuturesSettlementReferenceKtbMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->application_date[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->underlying_asset_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ktb_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_of_base_issue_for_payment[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->conversion_factor[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Commodity Futures Settlement Reference Ktb Message is what was written, byte for byte */
static void equal_commodity_futures_settlement_reference_ktb_message(const CommodityFuturesSettlementReferenceKtbMessage *read, const CommodityFuturesSettlementReferenceKtbMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->application_date[i] == written->application_date[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->underlying_asset_id[i] == written->underlying_asset_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ktb_isin[i] == written->ktb_isin[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_of_base_issue_for_payment[i] == written->isin_of_base_issue_for_payment[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->conversion_factor[i] == written->conversion_factor[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Commodity Futures Settlement Reference Ktb Message: written and read back, then read and written back */
static void check_commodity_futures_settlement_reference_ktb_message(void) {
  CommodityFuturesSettlementReferenceKtbMessage sent;
  CommodityFuturesSettlementReferenceKtbMessage got;
  uint8_t wire[66];
  uint8_t again[66];

  any_commodity_futures_settlement_reference_ktb_message(&sent);
  assert(encode_commodity_futures_settlement_reference_ktb_message(&sent, wire, 0) == 66);
  assert(decode_commodity_futures_settlement_reference_ktb_message(&got, wire, 0) == 66);
  equal_commodity_futures_settlement_reference_ktb_message(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_commodity_futures_settlement_reference_ktb_message(&got, wire, 0) == 66);
  assert(encode_commodity_futures_settlement_reference_ktb_message(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Derivatives Investor Activities Message: 161 bytes ---------------------- */

/* Investor Activities per Derivatives. Aggregated bid/ask volumes and values by investor category per derivatives product. */
typedef struct {
  uint8_t date[8];                          /* bytes 0 to 7 */
  uint8_t calculation_time_activities[6];   /* bytes 8 to 13 */
  uint8_t transaction_status_type_code[2];  /* bytes 14 to 15 */
  uint8_t product_id[11];                   /* bytes 16 to 26 */
  uint8_t futures_options_type_code;        /* byte 27 */
  uint8_t investor_code[4];                 /* bytes 28 to 31 */
  uint8_t bid_trading_volume[10];           /* bytes 32 to 41 */
  uint8_t ask_trading_volume[10];           /* bytes 42 to 51 */
  uint8_t bid_trading_value[22];            /* bytes 52 to 73 */
  uint8_t ask_trading_value[22];            /* bytes 74 to 95 */
  uint8_t spread_bid_trading_volume[10];    /* bytes 96 to 105 */
  uint8_t spread_ask_trading_volume[10];    /* bytes 106 to 115 */
  uint8_t spread_bid_trading_value[22];     /* bytes 116 to 137 */
  uint8_t spread_ask_trading_value[22];     /* bytes 138 to 159 */
  uint8_t end_keyword;                      /* byte 160 */
} DerivativesInvestorActivitiesMessage;

/* any Derivatives Investor Activities Message at all: every byte one the checker chooses */
static void any_derivatives_investor_activities_message(DerivativesInvestorActivitiesMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->calculation_time_activities[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->transaction_status_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->product_id[i] = arbitrary(); }
  record->futures_options_type_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->bid_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->ask_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->bid_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->ask_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->spread_bid_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->spread_ask_trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->spread_bid_trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->spread_ask_trading_value[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Derivatives Investor Activities Message to the wire: 161 bytes from at, returning where the next byte goes */
static size_t encode_derivatives_investor_activities_message(const DerivativesInvestorActivitiesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->calculation_time_activities[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->transaction_status_type_code[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->product_id[i]; }
  wire[at++] = record->futures_options_type_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->investor_code[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->bid_trading_volume[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->ask_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->bid_trading_value[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->ask_trading_value[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->spread_bid_trading_volume[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->spread_ask_trading_volume[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->spread_bid_trading_value[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->spread_ask_trading_value[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Derivatives Investor Activities Message off the wire: 161 bytes from at, returning where the next byte lies */
static size_t decode_derivatives_investor_activities_message(DerivativesInvestorActivitiesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->calculation_time_activities[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->transaction_status_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->product_id[i] = wire[at++]; }
  record->futures_options_type_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->investor_code[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->bid_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->ask_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->bid_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->ask_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->spread_bid_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->spread_ask_trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->spread_bid_trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->spread_ask_trading_value[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Derivatives Investor Activities Message is what was written, byte for byte */
static void equal_derivatives_investor_activities_message(const DerivativesInvestorActivitiesMessage *read, const DerivativesInvestorActivitiesMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->date[i] == written->date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->calculation_time_activities[i] == written->calculation_time_activities[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->transaction_status_type_code[i] == written->transaction_status_type_code[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->product_id[i] == written->product_id[i]); }
  assert(read->futures_options_type_code == written->futures_options_type_code);
  for (size_t i = 0; i < 4; i++) { assert(read->investor_code[i] == written->investor_code[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->bid_trading_volume[i] == written->bid_trading_volume[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->ask_trading_volume[i] == written->ask_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->bid_trading_value[i] == written->bid_trading_value[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->ask_trading_value[i] == written->ask_trading_value[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->spread_bid_trading_volume[i] == written->spread_bid_trading_volume[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->spread_ask_trading_volume[i] == written->spread_ask_trading_volume[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->spread_bid_trading_value[i] == written->spread_bid_trading_value[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->spread_ask_trading_value[i] == written->spread_ask_trading_value[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Derivatives Investor Activities Message: written and read back, then read and written back */
static void check_derivatives_investor_activities_message(void) {
  DerivativesInvestorActivitiesMessage sent;
  DerivativesInvestorActivitiesMessage got;
  uint8_t wire[161];
  uint8_t again[161];

  any_derivatives_investor_activities_message(&sent);
  assert(encode_derivatives_investor_activities_message(&sent, wire, 0) == 161);
  assert(decode_derivatives_investor_activities_message(&got, wire, 0) == 161);
  equal_derivatives_investor_activities_message(&got, &sent);

  for (size_t i = 0; i < 161; i++) { wire[i] = arbitrary(); }
  assert(decode_derivatives_investor_activities_message(&got, wire, 0) == 161);
  assert(encode_derivatives_investor_activities_message(&got, again, 0) == 161);
  for (size_t i = 0; i < 161; i++) { assert(again[i] == wire[i]); }
}

/* ---- Derivatives Open Interest Message: 39 bytes ----------------------------- */

/* Derivatives Open Interest. Total open interest per derivatives contract. */
typedef struct {
  uint8_t isin_code[12];                        /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 12 to 17 */
  uint8_t open_interest_type_code[2];           /* bytes 18 to 19 */
  uint8_t trading_date[8];                      /* bytes 20 to 27 */
  uint8_t open_interest[10];                    /* bytes 28 to 37 */
  uint8_t end_keyword;                          /* byte 38 */
} DerivativesOpenInterestMessage;

/* any Derivatives Open Interest Message at all: every byte one the checker chooses */
static void any_derivatives_open_interest_message(DerivativesOpenInterestMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->open_interest_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->open_interest[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Derivatives Open Interest Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_derivatives_open_interest_message(const DerivativesOpenInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->open_interest_type_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_date[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->open_interest[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Derivatives Open Interest Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_derivatives_open_interest_message(DerivativesOpenInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->open_interest_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->open_interest[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Derivatives Open Interest Message is what was written, byte for byte */
static void equal_derivatives_open_interest_message(const DerivativesOpenInterestMessage *read, const DerivativesOpenInterestMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->open_interest_type_code[i] == written->open_interest_type_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_date[i] == written->trading_date[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Derivatives Open Interest Message: written and read back, then read and written back */
static void check_derivatives_open_interest_message(void) {
  DerivativesOpenInterestMessage sent;
  DerivativesOpenInterestMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_derivatives_open_interest_message(&sent);
  assert(encode_derivatives_open_interest_message(&sent, wire, 0) == 39);
  assert(decode_derivatives_open_interest_message(&got, wire, 0) == 39);
  equal_derivatives_open_interest_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_derivatives_open_interest_message(&got, wire, 0) == 39);
  assert(encode_derivatives_open_interest_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Futures Settled Price Message: 58 bytes --------------------------------- */

/* Futures Settled Price. Daily settled price for futures contracts. */
typedef struct {
  uint8_t isin_code[12];                        /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 12 to 17 */
  uint8_t settlement_price[18];                 /* bytes 18 to 35 */
  uint8_t settlement_price_type_code[2];        /* bytes 36 to 37 */
  uint8_t the_last_settlement_price[18];        /* bytes 38 to 55 */
  uint8_t last_settlement_price_type_code;      /* byte 56 */
  uint8_t end_keyword;                          /* byte 57 */
} FuturesSettledPriceMessage;

/* any Futures Settled Price Message at all: every byte one the checker chooses */
static void any_futures_settled_price_message(FuturesSettledPriceMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->settlement_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->settlement_price_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->the_last_settlement_price[i] = arbitrary(); }
  record->last_settlement_price_type_code = arbitrary();
  record->end_keyword = arbitrary();
}

/* Futures Settled Price Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_futures_settled_price_message(const FuturesSettledPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->settlement_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->settlement_price_type_code[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->the_last_settlement_price[i]; }
  wire[at++] = record->last_settlement_price_type_code;
  wire[at++] = record->end_keyword;

  return at;
}

/* Futures Settled Price Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_futures_settled_price_message(FuturesSettledPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->settlement_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->settlement_price_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->the_last_settlement_price[i] = wire[at++]; }
  record->last_settlement_price_type_code = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Futures Settled Price Message is what was written, byte for byte */
static void equal_futures_settled_price_message(const FuturesSettledPriceMessage *read, const FuturesSettledPriceMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->settlement_price_type_code[i] == written->settlement_price_type_code[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->the_last_settlement_price[i] == written->the_last_settlement_price[i]); }
  assert(read->last_settlement_price_type_code == written->last_settlement_price_type_code);
  assert(read->end_keyword == written->end_keyword);
}

/* Futures Settled Price Message: written and read back, then read and written back */
static void check_futures_settled_price_message(void) {
  FuturesSettledPriceMessage sent;
  FuturesSettledPriceMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_futures_settled_price_message(&sent);
  assert(encode_futures_settled_price_message(&sent, wire, 0) == 58);
  assert(decode_futures_settled_price_message(&got, wire, 0) == 58);
  equal_futures_settled_price_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_futures_settled_price_message(&got, wire, 0) == 58);
  assert(encode_futures_settled_price_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Base Price Of Clearing Margins Message: 58 bytes ---------------- */

/* Options Base Price of Clearing Margins. Base price used for margin calculation. */
typedef struct {
  uint8_t isin_code[12];                                             /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue[6];                       /* bytes 12 to 17 */
  uint8_t base_price_of_clearing_margins[18];                        /* bytes 18 to 35 */
  uint8_t base_price_of_clearing_margins_type_code[2];               /* bytes 36 to 37 */
  uint8_t settlement_price_after_exercising_an_option[18];           /* bytes 38 to 55 */
  uint8_t type_code_of_settlement_price_after_exercising_an_option;  /* byte 56 */
  uint8_t end_keyword;                                               /* byte 57 */
} OptionsBasePriceOfClearingMarginsMessage;

/* any Options Base Price Of Clearing Margins Message at all: every byte one the checker chooses */
static void any_options_base_price_of_clearing_margins_message(OptionsBasePriceOfClearingMarginsMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->base_price_of_clearing_margins[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->base_price_of_clearing_margins_type_code[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->settlement_price_after_exercising_an_option[i] = arbitrary(); }
  record->type_code_of_settlement_price_after_exercising_an_option = arbitrary();
  record->end_keyword = arbitrary();
}

/* Options Base Price Of Clearing Margins Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_options_base_price_of_clearing_margins_message(const OptionsBasePriceOfClearingMarginsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->base_price_of_clearing_margins[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->base_price_of_clearing_margins_type_code[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->settlement_price_after_exercising_an_option[i]; }
  wire[at++] = record->type_code_of_settlement_price_after_exercising_an_option;
  wire[at++] = record->end_keyword;

  return at;
}

/* Options Base Price Of Clearing Margins Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_options_base_price_of_clearing_margins_message(OptionsBasePriceOfClearingMarginsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->base_price_of_clearing_margins[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->base_price_of_clearing_margins_type_code[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->settlement_price_after_exercising_an_option[i] = wire[at++]; }
  record->type_code_of_settlement_price_after_exercising_an_option = wire[at++];
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Options Base Price Of Clearing Margins Message is what was written, byte for byte */
static void equal_options_base_price_of_clearing_margins_message(const OptionsBasePriceOfClearingMarginsMessage *read, const OptionsBasePriceOfClearingMarginsMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->base_price_of_clearing_margins[i] == written->base_price_of_clearing_margins[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->base_price_of_clearing_margins_type_code[i] == written->base_price_of_clearing_margins_type_code[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->settlement_price_after_exercising_an_option[i] == written->settlement_price_after_exercising_an_option[i]); }
  assert(read->type_code_of_settlement_price_after_exercising_an_option == written->type_code_of_settlement_price_after_exercising_an_option);
  assert(read->end_keyword == written->end_keyword);
}

/* Options Base Price Of Clearing Margins Message: written and read back, then read and written back */
static void check_options_base_price_of_clearing_margins_message(void) {
  OptionsBasePriceOfClearingMarginsMessage sent;
  OptionsBasePriceOfClearingMarginsMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_options_base_price_of_clearing_margins_message(&sent);
  assert(encode_options_base_price_of_clearing_margins_message(&sent, wire, 0) == 58);
  assert(decode_options_base_price_of_clearing_margins_message(&got, wire, 0) == 58);
  equal_options_base_price_of_clearing_margins_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_options_base_price_of_clearing_margins_message(&got, wire, 0) == 58);
  assert(encode_options_base_price_of_clearing_margins_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Implied Volatility Message: 45 bytes ---------------------------- */

/* Options Implied Volatility per option contract. */
typedef struct {
  uint8_t call_averaged_implied_volatility[11];   /* bytes 0 to 10 */
  uint8_t put_averaged_implied_volatility[11];    /* bytes 11 to 21 */
  uint8_t representative_implied_volatility[11];  /* bytes 22 to 32 */
  uint8_t historical_volatility_90_days[11];      /* bytes 33 to 43 */
  uint8_t end_keyword;                            /* byte 44 */
} OptionsImpliedVolatilityMessage;

/* any Options Implied Volatility Message at all: every byte one the checker chooses */
static void any_options_implied_volatility_message(OptionsImpliedVolatilityMessage *record) {
  for (size_t i = 0; i < 11; i++) { record->call_averaged_implied_volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->put_averaged_implied_volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->representative_implied_volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->historical_volatility_90_days[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Options Implied Volatility Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_options_implied_volatility_message(const OptionsImpliedVolatilityMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->call_averaged_implied_volatility[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->put_averaged_implied_volatility[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->representative_implied_volatility[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->historical_volatility_90_days[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Options Implied Volatility Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_options_implied_volatility_message(OptionsImpliedVolatilityMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 11; i++) { record->call_averaged_implied_volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->put_averaged_implied_volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->representative_implied_volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->historical_volatility_90_days[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Options Implied Volatility Message is what was written, byte for byte */
static void equal_options_implied_volatility_message(const OptionsImpliedVolatilityMessage *read, const OptionsImpliedVolatilityMessage *written) {
  for (size_t i = 0; i < 11; i++) { assert(read->call_averaged_implied_volatility[i] == written->call_averaged_implied_volatility[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->put_averaged_implied_volatility[i] == written->put_averaged_implied_volatility[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->representative_implied_volatility[i] == written->representative_implied_volatility[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->historical_volatility_90_days[i] == written->historical_volatility_90_days[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Options Implied Volatility Message: written and read back, then read and written back */
static void check_options_implied_volatility_message(void) {
  OptionsImpliedVolatilityMessage sent;
  OptionsImpliedVolatilityMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_options_implied_volatility_message(&sent);
  assert(encode_options_implied_volatility_message(&sent, wire, 0) == 45);
  assert(decode_options_implied_volatility_message(&got, wire, 0) == 45);
  equal_options_implied_volatility_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_options_implied_volatility_message(&got, wire, 0) == 45);
  assert(encode_options_implied_volatility_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Sensitivity Message: 140 bytes ---------------------------------- */

/* Options Sensitivity. Greeks (Delta, Gamma, Theta, Vega, Rho) per option contract. */
typedef struct {
  uint8_t isin_code[12];                        /* bytes 0 to 11 */
  uint8_t a_designated_number_for_an_issue[6];  /* bytes 12 to 17 */
  uint8_t calculating_date[8];                  /* bytes 18 to 25 */
  uint8_t calculation_time_sensitivity[9];      /* bytes 26 to 34 */
  uint8_t implied_volatility_type_code;         /* byte 35 */
  uint8_t underlying_asset_id[3];               /* bytes 36 to 38 */
  uint8_t sensitivity_delta[20];                /* bytes 39 to 58 */
  uint8_t sensitivity_theta[20];                /* bytes 59 to 78 */
  uint8_t sensitivity_vega[20];                 /* bytes 79 to 98 */
  uint8_t sensitivity_gamma[20];                /* bytes 99 to 118 */
  uint8_t sensitivity_rho[20];                  /* bytes 119 to 138 */
  uint8_t end_keyword;                          /* byte 139 */
} OptionsSensitivityMessage;

/* any Options Sensitivity Message at all: every byte one the checker chooses */
static void any_options_sensitivity_message(OptionsSensitivityMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->calculating_date[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->calculation_time_sensitivity[i] = arbitrary(); }
  record->implied_volatility_type_code = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->underlying_asset_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sensitivity_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sensitivity_theta[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sensitivity_vega[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sensitivity_gamma[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sensitivity_rho[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Options Sensitivity Message to the wire: 140 bytes from at, returning where the next byte goes */
static size_t encode_options_sensitivity_message(const OptionsSensitivityMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->a_designated_number_for_an_issue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->calculating_date[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->calculation_time_sensitivity[i]; }
  wire[at++] = record->implied_volatility_type_code;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->underlying_asset_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sensitivity_delta[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sensitivity_theta[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sensitivity_vega[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sensitivity_gamma[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sensitivity_rho[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Options Sensitivity Message off the wire: 140 bytes from at, returning where the next byte lies */
static size_t decode_options_sensitivity_message(OptionsSensitivityMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->a_designated_number_for_an_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->calculating_date[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->calculation_time_sensitivity[i] = wire[at++]; }
  record->implied_volatility_type_code = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->underlying_asset_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sensitivity_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sensitivity_theta[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sensitivity_vega[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sensitivity_gamma[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sensitivity_rho[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Options Sensitivity Message is what was written, byte for byte */
static void equal_options_sensitivity_message(const OptionsSensitivityMessage *read, const OptionsSensitivityMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->a_designated_number_for_an_issue[i] == written->a_designated_number_for_an_issue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->calculating_date[i] == written->calculating_date[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->calculation_time_sensitivity[i] == written->calculation_time_sensitivity[i]); }
  assert(read->implied_volatility_type_code == written->implied_volatility_type_code);
  for (size_t i = 0; i < 3; i++) { assert(read->underlying_asset_id[i] == written->underlying_asset_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sensitivity_delta[i] == written->sensitivity_delta[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sensitivity_theta[i] == written->sensitivity_theta[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sensitivity_vega[i] == written->sensitivity_vega[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sensitivity_gamma[i] == written->sensitivity_gamma[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sensitivity_rho[i] == written->sensitivity_rho[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Options Sensitivity Message: written and read back, then read and written back */
static void check_options_sensitivity_message(void) {
  OptionsSensitivityMessage sent;
  OptionsSensitivityMessage got;
  uint8_t wire[140];
  uint8_t again[140];

  any_options_sensitivity_message(&sent);
  assert(encode_options_sensitivity_message(&sent, wire, 0) == 140);
  assert(decode_options_sensitivity_message(&got, wire, 0) == 140);
  equal_options_sensitivity_message(&got, &sent);

  for (size_t i = 0; i < 140; i++) { wire[i] = arbitrary(); }
  assert(decode_options_sensitivity_message(&got, wire, 0) == 140);
  assert(encode_options_sensitivity_message(&got, again, 0) == 140);
  for (size_t i = 0; i < 140; i++) { assert(again[i] == wire[i]); }
}

/* ---- Commodity Futures Spot Settlement Reference Message: 55 bytes ----------- */

/* Commodity Futures Spot Market Info Settlement Reference. */
typedef struct {
  uint8_t bis_announcement_date[8];             /* bytes 0 to 7 */
  uint8_t bis_announcement_time[6];             /* bytes 8 to 13 */
  uint8_t underlying_asset_id[3];               /* bytes 14 to 16 */
  uint8_t bis_yield_ratio[9];                   /* bytes 17 to 25 */
  uint8_t isin_of_base_issue_for_payment[12];   /* bytes 26 to 37 */
  uint8_t ktb_isin[12];                         /* bytes 38 to 49 */
  uint8_t bis_time_of_inputting_yield_rate[4];  /* bytes 50 to 53 */
  uint8_t end_keyword;                          /* byte 54 */
} CommodityFuturesSpotSettlementReferenceMessage;

/* any Commodity Futures Spot Settlement Reference Message at all: every byte one the checker chooses */
static void any_commodity_futures_spot_settlement_reference_message(CommodityFuturesSpotSettlementReferenceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->bis_announcement_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->bis_announcement_time[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->underlying_asset_id[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->bis_yield_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin_of_base_issue_for_payment[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->ktb_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bis_time_of_inputting_yield_rate[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Commodity Futures Spot Settlement Reference Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_commodity_futures_spot_settlement_reference_message(const CommodityFuturesSpotSettlementReferenceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bis_announcement_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->bis_announcement_time[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->underlying_asset_id[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->bis_yield_ratio[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_of_base_issue_for_payment[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->ktb_isin[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bis_time_of_inputting_yield_rate[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Commodity Futures Spot Settlement Reference Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_commodity_futures_spot_settlement_reference_message(CommodityFuturesSpotSettlementReferenceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->bis_announcement_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->bis_announcement_time[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->underlying_asset_id[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->bis_yield_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin_of_base_issue_for_payment[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->ktb_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bis_time_of_inputting_yield_rate[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Commodity Futures Spot Settlement Reference Message is what was written, byte for byte */
static void equal_commodity_futures_spot_settlement_reference_message(const CommodityFuturesSpotSettlementReferenceMessage *read, const CommodityFuturesSpotSettlementReferenceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->bis_announcement_date[i] == written->bis_announcement_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->bis_announcement_time[i] == written->bis_announcement_time[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->underlying_asset_id[i] == written->underlying_asset_id[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->bis_yield_ratio[i] == written->bis_yield_ratio[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin_of_base_issue_for_payment[i] == written->isin_of_base_issue_for_payment[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->ktb_isin[i] == written->ktb_isin[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bis_time_of_inputting_yield_rate[i] == written->bis_time_of_inputting_yield_rate[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Commodity Futures Spot Settlement Reference Message: written and read back, then read and written back */
static void check_commodity_futures_spot_settlement_reference_message(void) {
  CommodityFuturesSpotSettlementReferenceMessage sent;
  CommodityFuturesSpotSettlementReferenceMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_commodity_futures_spot_settlement_reference_message(&sent);
  assert(encode_commodity_futures_spot_settlement_reference_message(&sent, wire, 0) == 55);
  assert(decode_commodity_futures_spot_settlement_reference_message(&got, wire, 0) == 55);
  equal_commodity_futures_spot_settlement_reference_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_commodity_futures_spot_settlement_reference_message(&got, wire, 0) == 55);
  assert(encode_commodity_futures_spot_settlement_reference_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- Daily Disclosed Rfr Message: 82 bytes ----------------------------------- */

/* Daily disclosed Risk-Free Rate (RFR) reference. */
typedef struct {
  uint8_t base_date[8];               /* bytes 0 to 7 */
  uint8_t disclosure_type[2];         /* bytes 8 to 9 */
  uint8_t disclosure_date[14];        /* bytes 10 to 23 */
  uint8_t rfr[9];                     /* bytes 24 to 32 */
  uint8_t indexed_interest_rate[12];  /* bytes 33 to 44 */
  uint8_t interest_rate_30_day[12];   /* bytes 45 to 56 */
  uint8_t interest_rate_90_day[12];   /* bytes 57 to 68 */
  uint8_t interest_rate_180_day[12];  /* bytes 69 to 80 */
  uint8_t end_keyword;                /* byte 81 */
} DailyDisclosedRfrMessage;

/* any Daily Disclosed Rfr Message at all: every byte one the checker chooses */
static void any_daily_disclosed_rfr_message(DailyDisclosedRfrMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->base_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->disclosure_type[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->disclosure_date[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->rfr[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->indexed_interest_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->interest_rate_30_day[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->interest_rate_90_day[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->interest_rate_180_day[i] = arbitrary(); }
  record->end_keyword = arbitrary();
}

/* Daily Disclosed Rfr Message to the wire: 82 bytes from at, returning where the next byte goes */
static size_t encode_daily_disclosed_rfr_message(const DailyDisclosedRfrMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->base_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->disclosure_type[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->disclosure_date[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->rfr[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->indexed_interest_rate[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->interest_rate_30_day[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->interest_rate_90_day[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->interest_rate_180_day[i]; }
  wire[at++] = record->end_keyword;

  return at;
}

/* Daily Disclosed Rfr Message off the wire: 82 bytes from at, returning where the next byte lies */
static size_t decode_daily_disclosed_rfr_message(DailyDisclosedRfrMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->base_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->disclosure_type[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->disclosure_date[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->rfr[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->indexed_interest_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->interest_rate_30_day[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->interest_rate_90_day[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->interest_rate_180_day[i] = wire[at++]; }
  record->end_keyword = wire[at++];

  return at;
}

/* what was read of Daily Disclosed Rfr Message is what was written, byte for byte */
static void equal_daily_disclosed_rfr_message(const DailyDisclosedRfrMessage *read, const DailyDisclosedRfrMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->base_date[i] == written->base_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->disclosure_type[i] == written->disclosure_type[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->disclosure_date[i] == written->disclosure_date[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->rfr[i] == written->rfr[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->indexed_interest_rate[i] == written->indexed_interest_rate[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->interest_rate_30_day[i] == written->interest_rate_30_day[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->interest_rate_90_day[i] == written->interest_rate_90_day[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->interest_rate_180_day[i] == written->interest_rate_180_day[i]); }
  assert(read->end_keyword == written->end_keyword);
}

/* Daily Disclosed Rfr Message: written and read back, then read and written back */
static void check_daily_disclosed_rfr_message(void) {
  DailyDisclosedRfrMessage sent;
  DailyDisclosedRfrMessage got;
  uint8_t wire[82];
  uint8_t again[82];

  any_daily_disclosed_rfr_message(&sent);
  assert(encode_daily_disclosed_rfr_message(&sent, wire, 0) == 82);
  assert(decode_daily_disclosed_rfr_message(&got, wire, 0) == 82);
  equal_daily_disclosed_rfr_message(&got, &sent);

  for (size_t i = 0; i < 82; i++) { wire[i] = arbitrary(); }
  assert(decode_daily_disclosed_rfr_message(&got, wire, 0) == 82);
  assert(encode_daily_disclosed_rfr_message(&got, again, 0) == 82);
  for (size_t i = 0; i < 82; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_polling_data_message();
  check_derivatives_order_filled_message();
  check_derivatives_negotiated_trade_message();
  check_derivatives_market_operation_ts_message();
  check_derivatives_issue_closing_message();
  check_derivatives_market_operation_schedule_message();
  check_derivatives_dynamic_upper_lower_limit_message();
  check_derivatives_price_limit_range_increase_message();
  check_derivatives_quantity_allocation_message();
  check_derivatives_group_order_acceptance_halt_message();
  check_derivatives_batch_data_message();
  check_equity_derivatives_adjustment_details_message();
  check_commodity_futures_settlement_reference_ktb_message();
  check_derivatives_investor_activities_message();
  check_derivatives_open_interest_message();
  check_futures_settled_price_message();
  check_options_base_price_of_clearing_margins_message();
  check_options_implied_volatility_message();
  check_options_sensitivity_message();
  check_commodity_futures_spot_settlement_reference_message();
  check_daily_disclosed_rfr_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
