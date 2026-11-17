// jpx/tseequities/indexstatistics/TseEquities_IndexStatistics_v19_5.c
/*
 * Japan Exchange Group IndexStatistics
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
 *   - the dispatch that chooses a message by its type
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

/* ---- Message Serial No: 11 bytes --------------------------------------------- */

/* Numbered from 1 on each Multicast Group, with the multicast group number in the first to third byte */
typedef struct {
  uint8_t multicast_group_number[3];  /* bytes 0 to 2 */
  uint8_t sequence_number[8];         /* bytes 3 to 10 */
} MessageSerialNo;

/* any Message Serial No at all: every byte one the checker chooses */
static void any_message_serial_no(MessageSerialNo *record) {
  for (size_t i = 0; i < 3; i++) { record->multicast_group_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Message Serial No to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_message_serial_no(const MessageSerialNo *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->multicast_group_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Message Serial No off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_message_serial_no(MessageSerialNo *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->multicast_group_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Message Serial No is what was written, byte for byte */
static void equal_message_serial_no(const MessageSerialNo *read, const MessageSerialNo *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->multicast_group_number[i] == written->multicast_group_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Message Serial No: written and read back, then read and written back */
static void check_message_serial_no(void) {
  MessageSerialNo sent;
  MessageSerialNo got;
  uint8_t wire[11];
  uint8_t again[11];

  any_message_serial_no(&sent);
  assert(encode_message_serial_no(&sent, wire, 0) == 11);
  assert(decode_message_serial_no(&got, wire, 0) == 11);
  equal_message_serial_no(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_message_serial_no(&got, wire, 0) == 11);
  assert(encode_message_serial_no(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Issue Classification: 4 bytes ------------------------------------------- */

/* Set in issue realtime message and issue basic message. In the case of Control, Index and Statistics Message, space is set. */
typedef struct {
  uint8_t issue_classification_large_classification[2];   /* bytes 0 to 1 */
  uint8_t issue_classification_medium_classification[2];  /* bytes 2 to 3 */
} IssueClassification;

/* any Issue Classification at all: every byte one the checker chooses */
static void any_issue_classification(IssueClassification *record) {
  for (size_t i = 0; i < 2; i++) { record->issue_classification_large_classification[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->issue_classification_medium_classification[i] = arbitrary(); }
}

/* Issue Classification to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_issue_classification(const IssueClassification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->issue_classification_large_classification[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->issue_classification_medium_classification[i]; }

  return at;
}

/* Issue Classification off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_issue_classification(IssueClassification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->issue_classification_large_classification[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->issue_classification_medium_classification[i] = wire[at++]; }

  return at;
}

/* what was read of Issue Classification is what was written, byte for byte */
static void equal_issue_classification(const IssueClassification *read, const IssueClassification *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->issue_classification_large_classification[i] == written->issue_classification_large_classification[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->issue_classification_medium_classification[i] == written->issue_classification_medium_classification[i]); }
}

/* Issue Classification: written and read back, then read and written back */
static void check_issue_classification(void) {
  IssueClassification sent;
  IssueClassification got;
  uint8_t wire[4];
  uint8_t again[4];

  any_issue_classification(&sent);
  assert(encode_issue_classification(&sent, wire, 0) == 4);
  assert(decode_issue_classification(&got, wire, 0) == 4);
  equal_issue_classification(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_issue_classification(&got, wire, 0) == 4);
  assert(encode_issue_classification(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Issue Code: 12 bytes ---------------------------------------------- */

/* Issue Code layout a. Stocks, used when Issue Classification Large Classification is 01 Stock-Related. FLEX Issue Code is set with right-align. */
typedef struct {
  uint8_t stock_space[7];             /* bytes 0 to 6 */
  uint8_t stock_proper_name_code[4];  /* bytes 7 to 10 */
  uint8_t stock_reserved_code;        /* byte 11 */
} StockIssueCode;

/* any Stock Issue Code at all: every byte one the checker chooses */
static void any_stock_issue_code(StockIssueCode *record) {
  for (size_t i = 0; i < 7; i++) { record->stock_space[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->stock_proper_name_code[i] = arbitrary(); }
  record->stock_reserved_code = arbitrary();
}

/* Stock Issue Code to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_stock_issue_code(const StockIssueCode *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->stock_space[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->stock_proper_name_code[i]; }
  wire[at++] = record->stock_reserved_code;

  return at;
}

/* Stock Issue Code off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_stock_issue_code(StockIssueCode *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->stock_space[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->stock_proper_name_code[i] = wire[at++]; }
  record->stock_reserved_code = wire[at++];

  return at;
}

/* what was read of Stock Issue Code is what was written, byte for byte */
static void equal_stock_issue_code(const StockIssueCode *read, const StockIssueCode *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->stock_space[i] == written->stock_space[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->stock_proper_name_code[i] == written->stock_proper_name_code[i]); }
  assert(read->stock_reserved_code == written->stock_reserved_code);
}

/* Stock Issue Code: written and read back, then read and written back */
static void check_stock_issue_code(void) {
  StockIssueCode sent;
  StockIssueCode got;
  uint8_t wire[12];
  uint8_t again[12];

  any_stock_issue_code(&sent);
  assert(encode_stock_issue_code(&sent, wire, 0) == 12);
  assert(decode_stock_issue_code(&got, wire, 0) == 12);
  equal_stock_issue_code(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_issue_code(&got, wire, 0) == 12);
  assert(encode_stock_issue_code(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- CB Issue Code: 12 bytes ------------------------------------------------- */

/* Issue Code layout used when Issue Classification Large Classification is 02 CB-Related. The figure carries no label of its own in 5.3.3 (7). FLEX Issue Code is set with right-align. */
typedef struct {
  uint8_t c_b_space[3];             /* bytes 0 to 2 */
  uint8_t c_b_reserved_code;        /* byte 3 */
  uint8_t time_symbol[4];           /* bytes 4 to 7 */
  uint8_t c_b_proper_name_code[4];  /* bytes 8 to 11 */
} CBIssueCode;

/* any CB Issue Code at all: every byte one the checker chooses */
static void any_c_b_issue_code(CBIssueCode *record) {
  for (size_t i = 0; i < 3; i++) { record->c_b_space[i] = arbitrary(); }
  record->c_b_reserved_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->time_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->c_b_proper_name_code[i] = arbitrary(); }
}

/* CB Issue Code to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_c_b_issue_code(const CBIssueCode *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->c_b_space[i]; }
  wire[at++] = record->c_b_reserved_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->c_b_proper_name_code[i]; }

  return at;
}

/* CB Issue Code off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_c_b_issue_code(CBIssueCode *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->c_b_space[i] = wire[at++]; }
  record->c_b_reserved_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->time_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->c_b_proper_name_code[i] = wire[at++]; }

  return at;
}

/* what was read of CB Issue Code is what was written, byte for byte */
static void equal_c_b_issue_code(const CBIssueCode *read, const CBIssueCode *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->c_b_space[i] == written->c_b_space[i]); }
  assert(read->c_b_reserved_code == written->c_b_reserved_code);
  for (size_t i = 0; i < 4; i++) { assert(read->time_symbol[i] == written->time_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->c_b_proper_name_code[i] == written->c_b_proper_name_code[i]); }
}

/* CB Issue Code: written and read back, then read and written back */
static void check_c_b_issue_code(void) {
  CBIssueCode sent;
  CBIssueCode got;
  uint8_t wire[12];
  uint8_t again[12];

  any_c_b_issue_code(&sent);
  assert(encode_c_b_issue_code(&sent, wire, 0) == 12);
  assert(decode_c_b_issue_code(&got, wire, 0) == 12);
  equal_c_b_issue_code(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_c_b_issue_code(&got, wire, 0) == 12);
  assert(encode_c_b_issue_code(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Total Market Value: 15 bytes -------------------------------------------- */

/* Total market value */
typedef struct {
  uint8_t trading_volume_turnover_unit_flag;  /* byte 0 */
  uint8_t total_market_value_amount[14];      /* bytes 1 to 14 */
} TotalMarketValue;

/* any Total Market Value at all: every byte one the checker chooses */
static void any_total_market_value(TotalMarketValue *record) {
  record->trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->total_market_value_amount[i] = arbitrary(); }
}

/* Total Market Value to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_total_market_value(const TotalMarketValue *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->total_market_value_amount[i]; }

  return at;
}

/* Total Market Value off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_total_market_value(TotalMarketValue *record, const uint8_t *wire, size_t at) {
  record->trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->total_market_value_amount[i] = wire[at++]; }

  return at;
}

/* what was read of Total Market Value is what was written, byte for byte */
static void equal_total_market_value(const TotalMarketValue *read, const TotalMarketValue *written) {
  assert(read->trading_volume_turnover_unit_flag == written->trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->total_market_value_amount[i] == written->total_market_value_amount[i]); }
}

/* Total Market Value: written and read back, then read and written back */
static void check_total_market_value(void) {
  TotalMarketValue sent;
  TotalMarketValue got;
  uint8_t wire[15];
  uint8_t again[15];

  any_total_market_value(&sent);
  assert(encode_total_market_value(&sent, wire, 0) == 15);
  assert(decode_total_market_value(&got, wire, 0) == 15);
  equal_total_market_value(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_total_market_value(&got, wire, 0) == 15);
  assert(encode_total_market_value(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Value Day On Day Comparison: 16 bytes ---------------------------- */

/* Market value Day-on-day comparison */
typedef struct {
  uint8_t trading_volume_turnover_unit_flag;  /* byte 0 */
  uint8_t day_on_day_comparison[14];          /* bytes 1 to 14 */
  uint8_t sign;                               /* byte 15 */
} MarketValueDayOnDayComparison;

/* any Market Value Day On Day Comparison at all: every byte one the checker chooses */
static void any_market_value_day_on_day_comparison(MarketValueDayOnDayComparison *record) {
  record->trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->day_on_day_comparison[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Market Value Day On Day Comparison to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_market_value_day_on_day_comparison(const MarketValueDayOnDayComparison *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->day_on_day_comparison[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Market Value Day On Day Comparison off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_market_value_day_on_day_comparison(MarketValueDayOnDayComparison *record, const uint8_t *wire, size_t at) {
  record->trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->day_on_day_comparison[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Market Value Day On Day Comparison is what was written, byte for byte */
static void equal_market_value_day_on_day_comparison(const MarketValueDayOnDayComparison *read, const MarketValueDayOnDayComparison *written) {
  assert(read->trading_volume_turnover_unit_flag == written->trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->day_on_day_comparison[i] == written->day_on_day_comparison[i]); }
  assert(read->sign == written->sign);
}

/* Market Value Day On Day Comparison: written and read back, then read and written back */
static void check_market_value_day_on_day_comparison(void) {
  MarketValueDayOnDayComparison sent;
  MarketValueDayOnDayComparison got;
  uint8_t wire[16];
  uint8_t again[16];

  any_market_value_day_on_day_comparison(&sent);
  assert(encode_market_value_day_on_day_comparison(&sent, wire, 0) == 16);
  assert(decode_market_value_day_on_day_comparison(&got, wire, 0) == 16);
  equal_market_value_day_on_day_comparison(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_market_value_day_on_day_comparison(&got, wire, 0) == 16);
  assert(encode_market_value_day_on_day_comparison(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Value Message: 43 bytes ------------------------------------------ */

/* In this tag, total market value information for each market (issue classification) will be set. This data appears as part of a statistics message. */
typedef struct {
  uint8_t reserved_2[2];                                             /* bytes 0 to 1 */
  uint8_t time_c_6_hhmm[6];                                          /* bytes 2 to 7 */
  uint8_t issue_classification_code[4];                              /* bytes 8 to 11 */
  TotalMarketValue total_market_value;                               /* bytes 12 to 26 */
  MarketValueDayOnDayComparison market_value_day_on_day_comparison;  /* bytes 27 to 42 */
} MarketValueMessage;

/* any Market Value Message at all: every byte one the checker chooses */
static void any_market_value_message(MarketValueMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = arbitrary(); }
  any_total_market_value(&record->total_market_value);
  any_market_value_day_on_day_comparison(&record->market_value_day_on_day_comparison);
}

/* Market Value Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_market_value_message(const MarketValueMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6_hhmm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->issue_classification_code[i]; }
  at = encode_total_market_value(&record->total_market_value, wire, at);
  at = encode_market_value_day_on_day_comparison(&record->market_value_day_on_day_comparison, wire, at);

  return at;
}

/* Market Value Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_market_value_message(MarketValueMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = wire[at++]; }
  at = decode_total_market_value(&record->total_market_value, wire, at);
  at = decode_market_value_day_on_day_comparison(&record->market_value_day_on_day_comparison, wire, at);

  return at;
}

/* what was read of Market Value Message is what was written, byte for byte */
static void equal_market_value_message(const MarketValueMessage *read, const MarketValueMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6_hhmm[i] == written->time_c_6_hhmm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->issue_classification_code[i] == written->issue_classification_code[i]); }
  equal_total_market_value(&read->total_market_value, &written->total_market_value);
  equal_market_value_day_on_day_comparison(&read->market_value_day_on_day_comparison, &written->market_value_day_on_day_comparison);
}

/* Market Value Message: written and read back, then read and written back */
static void check_market_value_message(void) {
  MarketValueMessage sent;
  MarketValueMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_market_value_message(&sent);
  assert(encode_market_value_message(&sent, wire, 0) == 43);
  assert(decode_market_value_message(&got, wire, 0) == 43);
  equal_market_value_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_market_value_message(&got, wire, 0) == 43);
  assert(encode_market_value_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Yield: 9 bytes --------------------------------------------------- */

/* Simple yield */
typedef struct {
  uint8_t simple_yield_value[8];  /* bytes 0 to 7 */
  uint8_t sign;                   /* byte 8 */
} SimpleYield;

/* any Simple Yield at all: every byte one the checker chooses */
static void any_simple_yield(SimpleYield *record) {
  for (size_t i = 0; i < 8; i++) { record->simple_yield_value[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Simple Yield to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_simple_yield(const SimpleYield *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->simple_yield_value[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Simple Yield off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_simple_yield(SimpleYield *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->simple_yield_value[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Simple Yield is what was written, byte for byte */
static void equal_simple_yield(const SimpleYield *read, const SimpleYield *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->simple_yield_value[i] == written->simple_yield_value[i]); }
  assert(read->sign == written->sign);
}

/* Simple Yield: written and read back, then read and written back */
static void check_simple_yield(void) {
  SimpleYield sent;
  SimpleYield got;
  uint8_t wire[9];
  uint8_t again[9];

  any_simple_yield(&sent);
  assert(encode_simple_yield(&sent, wire, 0) == 9);
  assert(decode_simple_yield(&got, wire, 0) == 9);
  equal_simple_yield(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_yield(&got, wire, 0) == 9);
  assert(encode_simple_yield(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Yield Day On Day Comparison: 9 bytes ------------------------------------ */

/* Yield Day-on-day comparison */
typedef struct {
  uint8_t day_on_day_comparison_rate[8];  /* bytes 0 to 7 */
  uint8_t sign;                           /* byte 8 */
} YieldDayOnDayComparison;

/* any Yield Day On Day Comparison at all: every byte one the checker chooses */
static void any_yield_day_on_day_comparison(YieldDayOnDayComparison *record) {
  for (size_t i = 0; i < 8; i++) { record->day_on_day_comparison_rate[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Yield Day On Day Comparison to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_yield_day_on_day_comparison(const YieldDayOnDayComparison *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->day_on_day_comparison_rate[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Yield Day On Day Comparison off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_yield_day_on_day_comparison(YieldDayOnDayComparison *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->day_on_day_comparison_rate[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Yield Day On Day Comparison is what was written, byte for byte */
static void equal_yield_day_on_day_comparison(const YieldDayOnDayComparison *read, const YieldDayOnDayComparison *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->day_on_day_comparison_rate[i] == written->day_on_day_comparison_rate[i]); }
  assert(read->sign == written->sign);
}

/* Yield Day On Day Comparison: written and read back, then read and written back */
static void check_yield_day_on_day_comparison(void) {
  YieldDayOnDayComparison sent;
  YieldDayOnDayComparison got;
  uint8_t wire[9];
  uint8_t again[9];

  any_yield_day_on_day_comparison(&sent);
  assert(encode_yield_day_on_day_comparison(&sent, wire, 0) == 9);
  assert(decode_yield_day_on_day_comparison(&got, wire, 0) == 9);
  equal_yield_day_on_day_comparison(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_yield_day_on_day_comparison(&got, wire, 0) == 9);
  assert(encode_yield_day_on_day_comparison(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Yield Message: 30 bytes ------------------------------------------ */

/* In this tag, simple yield information for each market (issue classification) will be set. This data appears as part of a statistics message. */
typedef struct {
  uint8_t reserved_2[2];                                /* bytes 0 to 1 */
  uint8_t time_c_6_hhmm[6];                             /* bytes 2 to 7 */
  uint8_t issue_classification_code[4];                 /* bytes 8 to 11 */
  SimpleYield simple_yield;                             /* bytes 12 to 20 */
  YieldDayOnDayComparison yield_day_on_day_comparison;  /* bytes 21 to 29 */
} SimpleYieldMessage;

/* any Simple Yield Message at all: every byte one the checker chooses */
static void any_simple_yield_message(SimpleYieldMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = arbitrary(); }
  any_simple_yield(&record->simple_yield);
  any_yield_day_on_day_comparison(&record->yield_day_on_day_comparison);
}

/* Simple Yield Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_simple_yield_message(const SimpleYieldMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6_hhmm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->issue_classification_code[i]; }
  at = encode_simple_yield(&record->simple_yield, wire, at);
  at = encode_yield_day_on_day_comparison(&record->yield_day_on_day_comparison, wire, at);

  return at;
}

/* Simple Yield Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_simple_yield_message(SimpleYieldMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = wire[at++]; }
  at = decode_simple_yield(&record->simple_yield, wire, at);
  at = decode_yield_day_on_day_comparison(&record->yield_day_on_day_comparison, wire, at);

  return at;
}

/* what was read of Simple Yield Message is what was written, byte for byte */
static void equal_simple_yield_message(const SimpleYieldMessage *read, const SimpleYieldMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6_hhmm[i] == written->time_c_6_hhmm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->issue_classification_code[i] == written->issue_classification_code[i]); }
  equal_simple_yield(&read->simple_yield, &written->simple_yield);
  equal_yield_day_on_day_comparison(&read->yield_day_on_day_comparison, &written->yield_day_on_day_comparison);
}

/* Simple Yield Message: written and read back, then read and written back */
static void check_simple_yield_message(void) {
  SimpleYieldMessage sent;
  SimpleYieldMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_simple_yield_message(&sent);
  assert(encode_simple_yield_message(&sent, wire, 0) == 30);
  assert(decode_simple_yield_message(&got, wire, 0) == 30);
  equal_simple_yield_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_yield_message(&got, wire, 0) == 30);
  assert(encode_simple_yield_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Weighted Yield: 9 bytes ------------------------------------------------- */

/* Weighted yield */
typedef struct {
  uint8_t weighted_yield_value[8];  /* bytes 0 to 7 */
  uint8_t sign;                     /* byte 8 */
} WeightedYield;

/* any Weighted Yield at all: every byte one the checker chooses */
static void any_weighted_yield(WeightedYield *record) {
  for (size_t i = 0; i < 8; i++) { record->weighted_yield_value[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Weighted Yield to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_weighted_yield(const WeightedYield *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->weighted_yield_value[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Weighted Yield off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_weighted_yield(WeightedYield *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->weighted_yield_value[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Weighted Yield is what was written, byte for byte */
static void equal_weighted_yield(const WeightedYield *read, const WeightedYield *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->weighted_yield_value[i] == written->weighted_yield_value[i]); }
  assert(read->sign == written->sign);
}

/* Weighted Yield: written and read back, then read and written back */
static void check_weighted_yield(void) {
  WeightedYield sent;
  WeightedYield got;
  uint8_t wire[9];
  uint8_t again[9];

  any_weighted_yield(&sent);
  assert(encode_weighted_yield(&sent, wire, 0) == 9);
  assert(decode_weighted_yield(&got, wire, 0) == 9);
  equal_weighted_yield(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_weighted_yield(&got, wire, 0) == 9);
  assert(encode_weighted_yield(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Weighted Yield Message: 30 bytes ---------------------------------------- */

/* In this tag, weighted yield information for each market (issue classification) will be set. This data appears as part of a statistics message. */
typedef struct {
  uint8_t reserved_2[2];                                /* bytes 0 to 1 */
  uint8_t time_c_6_hhmm[6];                             /* bytes 2 to 7 */
  uint8_t issue_classification_code[4];                 /* bytes 8 to 11 */
  WeightedYield weighted_yield;                         /* bytes 12 to 20 */
  YieldDayOnDayComparison yield_day_on_day_comparison;  /* bytes 21 to 29 */
} WeightedYieldMessage;

/* any Weighted Yield Message at all: every byte one the checker chooses */
static void any_weighted_yield_message(WeightedYieldMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = arbitrary(); }
  any_weighted_yield(&record->weighted_yield);
  any_yield_day_on_day_comparison(&record->yield_day_on_day_comparison);
}

/* Weighted Yield Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_weighted_yield_message(const WeightedYieldMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6_hhmm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->issue_classification_code[i]; }
  at = encode_weighted_yield(&record->weighted_yield, wire, at);
  at = encode_yield_day_on_day_comparison(&record->yield_day_on_day_comparison, wire, at);

  return at;
}

/* Weighted Yield Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_weighted_yield_message(WeightedYieldMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = wire[at++]; }
  at = decode_weighted_yield(&record->weighted_yield, wire, at);
  at = decode_yield_day_on_day_comparison(&record->yield_day_on_day_comparison, wire, at);

  return at;
}

/* what was read of Weighted Yield Message is what was written, byte for byte */
static void equal_weighted_yield_message(const WeightedYieldMessage *read, const WeightedYieldMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6_hhmm[i] == written->time_c_6_hhmm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->issue_classification_code[i] == written->issue_classification_code[i]); }
  equal_weighted_yield(&read->weighted_yield, &written->weighted_yield);
  equal_yield_day_on_day_comparison(&read->yield_day_on_day_comparison, &written->yield_day_on_day_comparison);
}

/* Weighted Yield Message: written and read back, then read and written back */
static void check_weighted_yield_message(void) {
  WeightedYieldMessage sent;
  WeightedYieldMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_weighted_yield_message(&sent);
  assert(encode_weighted_yield_message(&sent, wire, 0) == 30);
  assert(decode_weighted_yield_message(&got, wire, 0) == 30);
  equal_weighted_yield_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_weighted_yield_message(&got, wire, 0) == 30);
  assert(encode_weighted_yield_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Stock Price Average: 16 bytes ------------------------------------ */

/* Simple stock price average */
typedef struct {
  uint8_t unit_flag;                             /* byte 0 */
  uint8_t simple_stock_price_average_value[14];  /* bytes 1 to 14 */
  uint8_t sign;                                  /* byte 15 */
} SimpleStockPriceAverage;

/* any Simple Stock Price Average at all: every byte one the checker chooses */
static void any_simple_stock_price_average(SimpleStockPriceAverage *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->simple_stock_price_average_value[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Simple Stock Price Average to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_simple_stock_price_average(const SimpleStockPriceAverage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->simple_stock_price_average_value[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Simple Stock Price Average off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_simple_stock_price_average(SimpleStockPriceAverage *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->simple_stock_price_average_value[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Simple Stock Price Average is what was written, byte for byte */
static void equal_simple_stock_price_average(const SimpleStockPriceAverage *read, const SimpleStockPriceAverage *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->simple_stock_price_average_value[i] == written->simple_stock_price_average_value[i]); }
  assert(read->sign == written->sign);
}

/* Simple Stock Price Average: written and read back, then read and written back */
static void check_simple_stock_price_average(void) {
  SimpleStockPriceAverage sent;
  SimpleStockPriceAverage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_simple_stock_price_average(&sent);
  assert(encode_simple_stock_price_average(&sent, wire, 0) == 16);
  assert(decode_simple_stock_price_average(&got, wire, 0) == 16);
  equal_simple_stock_price_average(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_stock_price_average(&got, wire, 0) == 16);
  assert(encode_simple_stock_price_average(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Price Average Day On Day Comparison: 16 bytes --------------------- */

/* Stock price average Day-on-day comparison */
typedef struct {
  uint8_t unit_flag;                  /* byte 0 */
  uint8_t day_on_day_comparison[14];  /* bytes 1 to 14 */
  uint8_t sign;                       /* byte 15 */
} StockPriceAverageDayOnDayComparison;

/* any Stock Price Average Day On Day Comparison at all: every byte one the checker chooses */
static void any_stock_price_average_day_on_day_comparison(StockPriceAverageDayOnDayComparison *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->day_on_day_comparison[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Stock Price Average Day On Day Comparison to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_stock_price_average_day_on_day_comparison(const StockPriceAverageDayOnDayComparison *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->day_on_day_comparison[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Stock Price Average Day On Day Comparison off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_stock_price_average_day_on_day_comparison(StockPriceAverageDayOnDayComparison *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->day_on_day_comparison[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Stock Price Average Day On Day Comparison is what was written, byte for byte */
static void equal_stock_price_average_day_on_day_comparison(const StockPriceAverageDayOnDayComparison *read, const StockPriceAverageDayOnDayComparison *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->day_on_day_comparison[i] == written->day_on_day_comparison[i]); }
  assert(read->sign == written->sign);
}

/* Stock Price Average Day On Day Comparison: written and read back, then read and written back */
static void check_stock_price_average_day_on_day_comparison(void) {
  StockPriceAverageDayOnDayComparison sent;
  StockPriceAverageDayOnDayComparison got;
  uint8_t wire[16];
  uint8_t again[16];

  any_stock_price_average_day_on_day_comparison(&sent);
  assert(encode_stock_price_average_day_on_day_comparison(&sent, wire, 0) == 16);
  assert(decode_stock_price_average_day_on_day_comparison(&got, wire, 0) == 16);
  equal_stock_price_average_day_on_day_comparison(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_price_average_day_on_day_comparison(&got, wire, 0) == 16);
  assert(encode_stock_price_average_day_on_day_comparison(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Stock Price Average Message: 44 bytes ---------------------------- */

/* In this tag, simple stock price average information for each market (issue classification) will be set. This data appears as part of a statistics message. */
typedef struct {
  uint8_t reserved_2[2];                                                          /* bytes 0 to 1 */
  uint8_t output_time[6];                                                         /* bytes 2 to 7 */
  uint8_t issue_classification_code[4];                                           /* bytes 8 to 11 */
  SimpleStockPriceAverage simple_stock_price_average;                             /* bytes 12 to 27 */
  StockPriceAverageDayOnDayComparison stock_price_average_day_on_day_comparison;  /* bytes 28 to 43 */
} SimpleStockPriceAverageMessage;

/* any Simple Stock Price Average Message at all: every byte one the checker chooses */
static void any_simple_stock_price_average_message(SimpleStockPriceAverageMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = arbitrary(); }
  any_simple_stock_price_average(&record->simple_stock_price_average);
  any_stock_price_average_day_on_day_comparison(&record->stock_price_average_day_on_day_comparison);
}

/* Simple Stock Price Average Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_simple_stock_price_average_message(const SimpleStockPriceAverageMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->output_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->issue_classification_code[i]; }
  at = encode_simple_stock_price_average(&record->simple_stock_price_average, wire, at);
  at = encode_stock_price_average_day_on_day_comparison(&record->stock_price_average_day_on_day_comparison, wire, at);

  return at;
}

/* Simple Stock Price Average Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_simple_stock_price_average_message(SimpleStockPriceAverageMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = wire[at++]; }
  at = decode_simple_stock_price_average(&record->simple_stock_price_average, wire, at);
  at = decode_stock_price_average_day_on_day_comparison(&record->stock_price_average_day_on_day_comparison, wire, at);

  return at;
}

/* what was read of Simple Stock Price Average Message is what was written, byte for byte */
static void equal_simple_stock_price_average_message(const SimpleStockPriceAverageMessage *read, const SimpleStockPriceAverageMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->output_time[i] == written->output_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->issue_classification_code[i] == written->issue_classification_code[i]); }
  equal_simple_stock_price_average(&read->simple_stock_price_average, &written->simple_stock_price_average);
  equal_stock_price_average_day_on_day_comparison(&read->stock_price_average_day_on_day_comparison, &written->stock_price_average_day_on_day_comparison);
}

/* Simple Stock Price Average Message: written and read back, then read and written back */
static void check_simple_stock_price_average_message(void) {
  SimpleStockPriceAverageMessage sent;
  SimpleStockPriceAverageMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_simple_stock_price_average_message(&sent);
  assert(encode_simple_stock_price_average_message(&sent, wire, 0) == 44);
  assert(decode_simple_stock_price_average_message(&got, wire, 0) == 44);
  equal_simple_stock_price_average_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_stock_price_average_message(&got, wire, 0) == 44);
  assert(encode_simple_stock_price_average_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Weighted Stock Price Average: 16 bytes ---------------------------------- */

/* Weighted stock price average */
typedef struct {
  uint8_t unit_flag;                               /* byte 0 */
  uint8_t weighted_stock_price_average_value[14];  /* bytes 1 to 14 */
  uint8_t sign;                                    /* byte 15 */
} WeightedStockPriceAverage;

/* any Weighted Stock Price Average at all: every byte one the checker chooses */
static void any_weighted_stock_price_average(WeightedStockPriceAverage *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->weighted_stock_price_average_value[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Weighted Stock Price Average to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_weighted_stock_price_average(const WeightedStockPriceAverage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->weighted_stock_price_average_value[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Weighted Stock Price Average off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_weighted_stock_price_average(WeightedStockPriceAverage *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->weighted_stock_price_average_value[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Weighted Stock Price Average is what was written, byte for byte */
static void equal_weighted_stock_price_average(const WeightedStockPriceAverage *read, const WeightedStockPriceAverage *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->weighted_stock_price_average_value[i] == written->weighted_stock_price_average_value[i]); }
  assert(read->sign == written->sign);
}

/* Weighted Stock Price Average: written and read back, then read and written back */
static void check_weighted_stock_price_average(void) {
  WeightedStockPriceAverage sent;
  WeightedStockPriceAverage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_weighted_stock_price_average(&sent);
  assert(encode_weighted_stock_price_average(&sent, wire, 0) == 16);
  assert(decode_weighted_stock_price_average(&got, wire, 0) == 16);
  equal_weighted_stock_price_average(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_weighted_stock_price_average(&got, wire, 0) == 16);
  assert(encode_weighted_stock_price_average(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Weighted Stock Price Average Message: 44 bytes -------------------------- */

/* In this tag, weighted stock price average information for each market (issue classification) will be set. This data appears as part of a statistics message. */
typedef struct {
  uint8_t reserved_2[2];                                                          /* bytes 0 to 1 */
  uint8_t output_time[6];                                                         /* bytes 2 to 7 */
  uint8_t issue_classification_code[4];                                           /* bytes 8 to 11 */
  WeightedStockPriceAverage weighted_stock_price_average;                         /* bytes 12 to 27 */
  StockPriceAverageDayOnDayComparison stock_price_average_day_on_day_comparison;  /* bytes 28 to 43 */
} WeightedStockPriceAverageMessage;

/* any Weighted Stock Price Average Message at all: every byte one the checker chooses */
static void any_weighted_stock_price_average_message(WeightedStockPriceAverageMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = arbitrary(); }
  any_weighted_stock_price_average(&record->weighted_stock_price_average);
  any_stock_price_average_day_on_day_comparison(&record->stock_price_average_day_on_day_comparison);
}

/* Weighted Stock Price Average Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_weighted_stock_price_average_message(const WeightedStockPriceAverageMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->output_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->issue_classification_code[i]; }
  at = encode_weighted_stock_price_average(&record->weighted_stock_price_average, wire, at);
  at = encode_stock_price_average_day_on_day_comparison(&record->stock_price_average_day_on_day_comparison, wire, at);

  return at;
}

/* Weighted Stock Price Average Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_weighted_stock_price_average_message(WeightedStockPriceAverageMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = wire[at++]; }
  at = decode_weighted_stock_price_average(&record->weighted_stock_price_average, wire, at);
  at = decode_stock_price_average_day_on_day_comparison(&record->stock_price_average_day_on_day_comparison, wire, at);

  return at;
}

/* what was read of Weighted Stock Price Average Message is what was written, byte for byte */
static void equal_weighted_stock_price_average_message(const WeightedStockPriceAverageMessage *read, const WeightedStockPriceAverageMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->output_time[i] == written->output_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->issue_classification_code[i] == written->issue_classification_code[i]); }
  equal_weighted_stock_price_average(&read->weighted_stock_price_average, &written->weighted_stock_price_average);
  equal_stock_price_average_day_on_day_comparison(&read->stock_price_average_day_on_day_comparison, &written->stock_price_average_day_on_day_comparison);
}

/* Weighted Stock Price Average Message: written and read back, then read and written back */
static void check_weighted_stock_price_average_message(void) {
  WeightedStockPriceAverageMessage sent;
  WeightedStockPriceAverageMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_weighted_stock_price_average_message(&sent);
  assert(encode_weighted_stock_price_average_message(&sent, wire, 0) == 44);
  assert(decode_weighted_stock_price_average_message(&got, wire, 0) == 44);
  equal_weighted_stock_price_average_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_weighted_stock_price_average_message(&got, wire, 0) == 44);
  assert(encode_weighted_stock_price_average_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Stock Price Average By Industry Message: 44 bytes ---------------- */

/* In this tag, simple stock price average information by industry classification will be set. This data appears as part of a statistics message. */
typedef struct {
  uint8_t reserved_2[2];                                                          /* bytes 0 to 1 */
  uint8_t output_time[6];                                                         /* bytes 2 to 7 */
  uint8_t industry_code[4];                                                       /* bytes 8 to 11 */
  SimpleStockPriceAverage simple_stock_price_average;                             /* bytes 12 to 27 */
  StockPriceAverageDayOnDayComparison stock_price_average_day_on_day_comparison;  /* bytes 28 to 43 */
} SimpleStockPriceAverageByIndustryMessage;

/* any Simple Stock Price Average By Industry Message at all: every byte one the checker chooses */
static void any_simple_stock_price_average_by_industry_message(SimpleStockPriceAverageByIndustryMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->industry_code[i] = arbitrary(); }
  any_simple_stock_price_average(&record->simple_stock_price_average);
  any_stock_price_average_day_on_day_comparison(&record->stock_price_average_day_on_day_comparison);
}

/* Simple Stock Price Average By Industry Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_simple_stock_price_average_by_industry_message(const SimpleStockPriceAverageByIndustryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->output_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->industry_code[i]; }
  at = encode_simple_stock_price_average(&record->simple_stock_price_average, wire, at);
  at = encode_stock_price_average_day_on_day_comparison(&record->stock_price_average_day_on_day_comparison, wire, at);

  return at;
}

/* Simple Stock Price Average By Industry Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_simple_stock_price_average_by_industry_message(SimpleStockPriceAverageByIndustryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->industry_code[i] = wire[at++]; }
  at = decode_simple_stock_price_average(&record->simple_stock_price_average, wire, at);
  at = decode_stock_price_average_day_on_day_comparison(&record->stock_price_average_day_on_day_comparison, wire, at);

  return at;
}

/* what was read of Simple Stock Price Average By Industry Message is what was written, byte for byte */
static void equal_simple_stock_price_average_by_industry_message(const SimpleStockPriceAverageByIndustryMessage *read, const SimpleStockPriceAverageByIndustryMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->output_time[i] == written->output_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->industry_code[i] == written->industry_code[i]); }
  equal_simple_stock_price_average(&read->simple_stock_price_average, &written->simple_stock_price_average);
  equal_stock_price_average_day_on_day_comparison(&read->stock_price_average_day_on_day_comparison, &written->stock_price_average_day_on_day_comparison);
}

/* Simple Stock Price Average By Industry Message: written and read back, then read and written back */
static void check_simple_stock_price_average_by_industry_message(void) {
  SimpleStockPriceAverageByIndustryMessage sent;
  SimpleStockPriceAverageByIndustryMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_simple_stock_price_average_by_industry_message(&sent);
  assert(encode_simple_stock_price_average_by_industry_message(&sent, wire, 0) == 44);
  assert(decode_simple_stock_price_average_by_industry_message(&got, wire, 0) == 44);
  equal_simple_stock_price_average_by_industry_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_stock_price_average_by_industry_message(&got, wire, 0) == 44);
  assert(encode_simple_stock_price_average_by_industry_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Overall Simple Average: 32 bytes ---------------------------------------- */

/* Overall Simple average */
typedef struct {
  uint8_t unit_flag;                  /* byte 0 */
  uint8_t simple_average_value[14];   /* bytes 1 to 14 */
  uint8_t sign;                       /* byte 15 */
  uint8_t second_unit_flag;           /* byte 16 */
  uint8_t day_on_day_comparison[14];  /* bytes 17 to 30 */
  uint8_t second_sign;                /* byte 31 */
} OverallSimpleAverage;

/* any Overall Simple Average at all: every byte one the checker chooses */
static void any_overall_simple_average(OverallSimpleAverage *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->simple_average_value[i] = arbitrary(); }
  record->sign = arbitrary();
  record->second_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->day_on_day_comparison[i] = arbitrary(); }
  record->second_sign = arbitrary();
}

/* Overall Simple Average to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_overall_simple_average(const OverallSimpleAverage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->simple_average_value[i]; }
  wire[at++] = record->sign;
  wire[at++] = record->second_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->day_on_day_comparison[i]; }
  wire[at++] = record->second_sign;

  return at;
}

/* Overall Simple Average off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_overall_simple_average(OverallSimpleAverage *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->simple_average_value[i] = wire[at++]; }
  record->sign = wire[at++];
  record->second_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->day_on_day_comparison[i] = wire[at++]; }
  record->second_sign = wire[at++];

  return at;
}

/* what was read of Overall Simple Average is what was written, byte for byte */
static void equal_overall_simple_average(const OverallSimpleAverage *read, const OverallSimpleAverage *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->simple_average_value[i] == written->simple_average_value[i]); }
  assert(read->sign == written->sign);
  assert(read->second_unit_flag == written->second_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->day_on_day_comparison[i] == written->day_on_day_comparison[i]); }
  assert(read->second_sign == written->second_sign);
}

/* Overall Simple Average: written and read back, then read and written back */
static void check_overall_simple_average(void) {
  OverallSimpleAverage sent;
  OverallSimpleAverage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_overall_simple_average(&sent);
  assert(encode_overall_simple_average(&sent, wire, 0) == 32);
  assert(decode_overall_simple_average(&got, wire, 0) == 32);
  equal_overall_simple_average(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_overall_simple_average(&got, wire, 0) == 32);
  assert(encode_overall_simple_average(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Overall Divergence Average: 18 bytes ------------------------------------ */

/* Overall Divergence average */
typedef struct {
  uint8_t divergence_average_value[8];    /* bytes 0 to 7 */
  uint8_t sign;                           /* byte 8 */
  uint8_t day_on_day_comparison_rate[8];  /* bytes 9 to 16 */
  uint8_t second_sign;                    /* byte 17 */
} OverallDivergenceAverage;

/* any Overall Divergence Average at all: every byte one the checker chooses */
static void any_overall_divergence_average(OverallDivergenceAverage *record) {
  for (size_t i = 0; i < 8; i++) { record->divergence_average_value[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->day_on_day_comparison_rate[i] = arbitrary(); }
  record->second_sign = arbitrary();
}

/* Overall Divergence Average to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_overall_divergence_average(const OverallDivergenceAverage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->divergence_average_value[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->day_on_day_comparison_rate[i]; }
  wire[at++] = record->second_sign;

  return at;
}

/* Overall Divergence Average off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_overall_divergence_average(OverallDivergenceAverage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->divergence_average_value[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->day_on_day_comparison_rate[i] = wire[at++]; }
  record->second_sign = wire[at++];

  return at;
}

/* what was read of Overall Divergence Average is what was written, byte for byte */
static void equal_overall_divergence_average(const OverallDivergenceAverage *read, const OverallDivergenceAverage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->divergence_average_value[i] == written->divergence_average_value[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 8; i++) { assert(read->day_on_day_comparison_rate[i] == written->day_on_day_comparison_rate[i]); }
  assert(read->second_sign == written->second_sign);
}

/* Overall Divergence Average: written and read back, then read and written back */
static void check_overall_divergence_average(void) {
  OverallDivergenceAverage sent;
  OverallDivergenceAverage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_overall_divergence_average(&sent);
  assert(encode_overall_divergence_average(&sent, wire, 0) == 18);
  assert(decode_overall_divergence_average(&got, wire, 0) == 18);
  equal_overall_divergence_average(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_overall_divergence_average(&got, wire, 0) == 18);
  assert(encode_overall_divergence_average(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Overall Parity Average: 32 bytes ---------------------------------------- */

/* Overall Parity average */
typedef struct {
  uint8_t unit_flag;                  /* byte 0 */
  uint8_t parity_average_value[14];   /* bytes 1 to 14 */
  uint8_t sign;                       /* byte 15 */
  uint8_t second_unit_flag;           /* byte 16 */
  uint8_t day_on_day_comparison[14];  /* bytes 17 to 30 */
  uint8_t second_sign;                /* byte 31 */
} OverallParityAverage;

/* any Overall Parity Average at all: every byte one the checker chooses */
static void any_overall_parity_average(OverallParityAverage *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->parity_average_value[i] = arbitrary(); }
  record->sign = arbitrary();
  record->second_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->day_on_day_comparison[i] = arbitrary(); }
  record->second_sign = arbitrary();
}

/* Overall Parity Average to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_overall_parity_average(const OverallParityAverage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->parity_average_value[i]; }
  wire[at++] = record->sign;
  wire[at++] = record->second_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->day_on_day_comparison[i]; }
  wire[at++] = record->second_sign;

  return at;
}

/* Overall Parity Average off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_overall_parity_average(OverallParityAverage *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->parity_average_value[i] = wire[at++]; }
  record->sign = wire[at++];
  record->second_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->day_on_day_comparison[i] = wire[at++]; }
  record->second_sign = wire[at++];

  return at;
}

/* what was read of Overall Parity Average is what was written, byte for byte */
static void equal_overall_parity_average(const OverallParityAverage *read, const OverallParityAverage *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->parity_average_value[i] == written->parity_average_value[i]); }
  assert(read->sign == written->sign);
  assert(read->second_unit_flag == written->second_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->day_on_day_comparison[i] == written->day_on_day_comparison[i]); }
  assert(read->second_sign == written->second_sign);
}

/* Overall Parity Average: written and read back, then read and written back */
static void check_overall_parity_average(void) {
  OverallParityAverage sent;
  OverallParityAverage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_overall_parity_average(&sent);
  assert(encode_overall_parity_average(&sent, wire, 0) == 32);
  assert(decode_overall_parity_average(&got, wire, 0) == 32);
  equal_overall_parity_average(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_overall_parity_average(&got, wire, 0) == 32);
  assert(encode_overall_parity_average(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Overall Direct Yield Average: 18 bytes ---------------------------------- */

/* Overall Direct yield average */
typedef struct {
  uint8_t direct_yield_average_value[8];  /* bytes 0 to 7 */
  uint8_t sign;                           /* byte 8 */
  uint8_t day_on_day_comparison_rate[8];  /* bytes 9 to 16 */
  uint8_t second_sign;                    /* byte 17 */
} OverallDirectYieldAverage;

/* any Overall Direct Yield Average at all: every byte one the checker chooses */
static void any_overall_direct_yield_average(OverallDirectYieldAverage *record) {
  for (size_t i = 0; i < 8; i++) { record->direct_yield_average_value[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->day_on_day_comparison_rate[i] = arbitrary(); }
  record->second_sign = arbitrary();
}

/* Overall Direct Yield Average to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_overall_direct_yield_average(const OverallDirectYieldAverage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->direct_yield_average_value[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->day_on_day_comparison_rate[i]; }
  wire[at++] = record->second_sign;

  return at;
}

/* Overall Direct Yield Average off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_overall_direct_yield_average(OverallDirectYieldAverage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->direct_yield_average_value[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->day_on_day_comparison_rate[i] = wire[at++]; }
  record->second_sign = wire[at++];

  return at;
}

/* what was read of Overall Direct Yield Average is what was written, byte for byte */
static void equal_overall_direct_yield_average(const OverallDirectYieldAverage *read, const OverallDirectYieldAverage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->direct_yield_average_value[i] == written->direct_yield_average_value[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 8; i++) { assert(read->day_on_day_comparison_rate[i] == written->day_on_day_comparison_rate[i]); }
  assert(read->second_sign == written->second_sign);
}

/* Overall Direct Yield Average: written and read back, then read and written back */
static void check_overall_direct_yield_average(void) {
  OverallDirectYieldAverage sent;
  OverallDirectYieldAverage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_overall_direct_yield_average(&sent);
  assert(encode_overall_direct_yield_average(&sent, wire, 0) == 18);
  assert(decode_overall_direct_yield_average(&got, wire, 0) == 18);
  equal_overall_direct_yield_average(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_overall_direct_yield_average(&got, wire, 0) == 18);
  assert(encode_overall_direct_yield_average(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Overall: 100 bytes ------------------------------------------------------ */

/* Overall */
typedef struct {
  OverallSimpleAverage overall_simple_average;             /* bytes 0 to 31 */
  OverallDivergenceAverage overall_divergence_average;     /* bytes 32 to 49 */
  OverallParityAverage overall_parity_average;             /* bytes 50 to 81 */
  OverallDirectYieldAverage overall_direct_yield_average;  /* bytes 82 to 99 */
} Overall;

/* any Overall at all: every byte one the checker chooses */
static void any_overall(Overall *record) {
  any_overall_simple_average(&record->overall_simple_average);
  any_overall_divergence_average(&record->overall_divergence_average);
  any_overall_parity_average(&record->overall_parity_average);
  any_overall_direct_yield_average(&record->overall_direct_yield_average);
}

/* Overall to the wire: 100 bytes from at, returning where the next byte goes */
static size_t encode_overall(const Overall *record, uint8_t *wire, size_t at) {
  at = encode_overall_simple_average(&record->overall_simple_average, wire, at);
  at = encode_overall_divergence_average(&record->overall_divergence_average, wire, at);
  at = encode_overall_parity_average(&record->overall_parity_average, wire, at);
  at = encode_overall_direct_yield_average(&record->overall_direct_yield_average, wire, at);

  return at;
}

/* Overall off the wire: 100 bytes from at, returning where the next byte lies */
static size_t decode_overall(Overall *record, const uint8_t *wire, size_t at) {
  at = decode_overall_simple_average(&record->overall_simple_average, wire, at);
  at = decode_overall_divergence_average(&record->overall_divergence_average, wire, at);
  at = decode_overall_parity_average(&record->overall_parity_average, wire, at);
  at = decode_overall_direct_yield_average(&record->overall_direct_yield_average, wire, at);

  return at;
}

/* what was read of Overall is what was written, byte for byte */
static void equal_overall(const Overall *read, const Overall *written) {
  equal_overall_simple_average(&read->overall_simple_average, &written->overall_simple_average);
  equal_overall_divergence_average(&read->overall_divergence_average, &written->overall_divergence_average);
  equal_overall_parity_average(&read->overall_parity_average, &written->overall_parity_average);
  equal_overall_direct_yield_average(&read->overall_direct_yield_average, &written->overall_direct_yield_average);
}

/* Overall: written and read back, then read and written back */
static void check_overall(void) {
  Overall sent;
  Overall got;
  uint8_t wire[100];
  uint8_t again[100];

  any_overall(&sent);
  assert(encode_overall(&sent, wire, 0) == 100);
  assert(decode_overall(&got, wire, 0) == 100);
  equal_overall(&got, &sent);

  for (size_t i = 0; i < 100; i++) { wire[i] = arbitrary(); }
  assert(decode_overall(&got, wire, 0) == 100);
  assert(encode_overall(&got, again, 0) == 100);
  for (size_t i = 0; i < 100; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Average: 16 bytes ------------------------------------------------ */

/* Simple average */
typedef struct {
  uint8_t unit_flag;                 /* byte 0 */
  uint8_t simple_average_value[14];  /* bytes 1 to 14 */
  uint8_t sign;                      /* byte 15 */
} SimpleAverage;

/* any Simple Average at all: every byte one the checker chooses */
static void any_simple_average(SimpleAverage *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->simple_average_value[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Simple Average to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_simple_average(const SimpleAverage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->simple_average_value[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Simple Average off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_simple_average(SimpleAverage *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->simple_average_value[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Simple Average is what was written, byte for byte */
static void equal_simple_average(const SimpleAverage *read, const SimpleAverage *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->simple_average_value[i] == written->simple_average_value[i]); }
  assert(read->sign == written->sign);
}

/* Simple Average: written and read back, then read and written back */
static void check_simple_average(void) {
  SimpleAverage sent;
  SimpleAverage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_simple_average(&sent);
  assert(encode_simple_average(&sent, wire, 0) == 16);
  assert(decode_simple_average(&got, wire, 0) == 16);
  equal_simple_average(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_average(&got, wire, 0) == 16);
  assert(encode_simple_average(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Divergence Average: 9 bytes --------------------------------------------- */

/* Divergence average */
typedef struct {
  uint8_t divergence_average_value[8];  /* bytes 0 to 7 */
  uint8_t sign;                         /* byte 8 */
} DivergenceAverage;

/* any Divergence Average at all: every byte one the checker chooses */
static void any_divergence_average(DivergenceAverage *record) {
  for (size_t i = 0; i < 8; i++) { record->divergence_average_value[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Divergence Average to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_divergence_average(const DivergenceAverage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->divergence_average_value[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Divergence Average off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_divergence_average(DivergenceAverage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->divergence_average_value[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Divergence Average is what was written, byte for byte */
static void equal_divergence_average(const DivergenceAverage *read, const DivergenceAverage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->divergence_average_value[i] == written->divergence_average_value[i]); }
  assert(read->sign == written->sign);
}

/* Divergence Average: written and read back, then read and written back */
static void check_divergence_average(void) {
  DivergenceAverage sent;
  DivergenceAverage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_divergence_average(&sent);
  assert(encode_divergence_average(&sent, wire, 0) == 9);
  assert(decode_divergence_average(&got, wire, 0) == 9);
  equal_divergence_average(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_divergence_average(&got, wire, 0) == 9);
  assert(encode_divergence_average(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Parity Average: 16 bytes ------------------------------------------------ */

/* Parity average */
typedef struct {
  uint8_t unit_flag;                 /* byte 0 */
  uint8_t parity_average_value[14];  /* bytes 1 to 14 */
  uint8_t sign;                      /* byte 15 */
} ParityAverage;

/* any Parity Average at all: every byte one the checker chooses */
static void any_parity_average(ParityAverage *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->parity_average_value[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Parity Average to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_parity_average(const ParityAverage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->parity_average_value[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Parity Average off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_parity_average(ParityAverage *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->parity_average_value[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Parity Average is what was written, byte for byte */
static void equal_parity_average(const ParityAverage *read, const ParityAverage *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->parity_average_value[i] == written->parity_average_value[i]); }
  assert(read->sign == written->sign);
}

/* Parity Average: written and read back, then read and written back */
static void check_parity_average(void) {
  ParityAverage sent;
  ParityAverage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_parity_average(&sent);
  assert(encode_parity_average(&sent, wire, 0) == 16);
  assert(decode_parity_average(&got, wire, 0) == 16);
  equal_parity_average(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_parity_average(&got, wire, 0) == 16);
  assert(encode_parity_average(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Direct Yield Average: 9 bytes ------------------------------------------- */

/* Direct yield average */
typedef struct {
  uint8_t direct_yield_average_value[8];  /* bytes 0 to 7 */
  uint8_t sign;                           /* byte 8 */
} DirectYieldAverage;

/* any Direct Yield Average at all: every byte one the checker chooses */
static void any_direct_yield_average(DirectYieldAverage *record) {
  for (size_t i = 0; i < 8; i++) { record->direct_yield_average_value[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Direct Yield Average to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_direct_yield_average(const DirectYieldAverage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->direct_yield_average_value[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Direct Yield Average off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_direct_yield_average(DirectYieldAverage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->direct_yield_average_value[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Direct Yield Average is what was written, byte for byte */
static void equal_direct_yield_average(const DirectYieldAverage *read, const DirectYieldAverage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->direct_yield_average_value[i] == written->direct_yield_average_value[i]); }
  assert(read->sign == written->sign);
}

/* Direct Yield Average: written and read back, then read and written back */
static void check_direct_yield_average(void) {
  DirectYieldAverage sent;
  DirectYieldAverage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_direct_yield_average(&sent);
  assert(encode_direct_yield_average(&sent, wire, 0) == 9);
  assert(decode_direct_yield_average(&got, wire, 0) == 9);
  equal_direct_yield_average(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_direct_yield_average(&got, wire, 0) == 9);
  assert(encode_direct_yield_average(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Parity 100 Or Higher: 50 bytes ------------------------------------------ */

/* Parity 100 or higher */
typedef struct {
  SimpleAverage simple_average;             /* bytes 0 to 15 */
  DivergenceAverage divergence_average;     /* bytes 16 to 24 */
  ParityAverage parity_average;             /* bytes 25 to 40 */
  DirectYieldAverage direct_yield_average;  /* bytes 41 to 49 */
} Parity100OrHigher;

/* any Parity 100 Or Higher at all: every byte one the checker chooses */
static void any_parity100_or_higher(Parity100OrHigher *record) {
  any_simple_average(&record->simple_average);
  any_divergence_average(&record->divergence_average);
  any_parity_average(&record->parity_average);
  any_direct_yield_average(&record->direct_yield_average);
}

/* Parity 100 Or Higher to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_parity100_or_higher(const Parity100OrHigher *record, uint8_t *wire, size_t at) {
  at = encode_simple_average(&record->simple_average, wire, at);
  at = encode_divergence_average(&record->divergence_average, wire, at);
  at = encode_parity_average(&record->parity_average, wire, at);
  at = encode_direct_yield_average(&record->direct_yield_average, wire, at);

  return at;
}

/* Parity 100 Or Higher off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_parity100_or_higher(Parity100OrHigher *record, const uint8_t *wire, size_t at) {
  at = decode_simple_average(&record->simple_average, wire, at);
  at = decode_divergence_average(&record->divergence_average, wire, at);
  at = decode_parity_average(&record->parity_average, wire, at);
  at = decode_direct_yield_average(&record->direct_yield_average, wire, at);

  return at;
}

/* what was read of Parity 100 Or Higher is what was written, byte for byte */
static void equal_parity100_or_higher(const Parity100OrHigher *read, const Parity100OrHigher *written) {
  equal_simple_average(&read->simple_average, &written->simple_average);
  equal_divergence_average(&read->divergence_average, &written->divergence_average);
  equal_parity_average(&read->parity_average, &written->parity_average);
  equal_direct_yield_average(&read->direct_yield_average, &written->direct_yield_average);
}

/* Parity 100 Or Higher: written and read back, then read and written back */
static void check_parity100_or_higher(void) {
  Parity100OrHigher sent;
  Parity100OrHigher got;
  uint8_t wire[50];
  uint8_t again[50];

  any_parity100_or_higher(&sent);
  assert(encode_parity100_or_higher(&sent, wire, 0) == 50);
  assert(decode_parity100_or_higher(&got, wire, 0) == 50);
  equal_parity100_or_higher(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_parity100_or_higher(&got, wire, 0) == 50);
  assert(encode_parity100_or_higher(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Parity Less Than 100: 50 bytes ------------------------------------------ */

/* Parity less than 100 */
typedef struct {
  SimpleAverage simple_average;             /* bytes 0 to 15 */
  DivergenceAverage divergence_average;     /* bytes 16 to 24 */
  ParityAverage parity_average;             /* bytes 25 to 40 */
  DirectYieldAverage direct_yield_average;  /* bytes 41 to 49 */
} ParityLessThan100;

/* any Parity Less Than 100 at all: every byte one the checker chooses */
static void any_parity_less_than100(ParityLessThan100 *record) {
  any_simple_average(&record->simple_average);
  any_divergence_average(&record->divergence_average);
  any_parity_average(&record->parity_average);
  any_direct_yield_average(&record->direct_yield_average);
}

/* Parity Less Than 100 to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_parity_less_than100(const ParityLessThan100 *record, uint8_t *wire, size_t at) {
  at = encode_simple_average(&record->simple_average, wire, at);
  at = encode_divergence_average(&record->divergence_average, wire, at);
  at = encode_parity_average(&record->parity_average, wire, at);
  at = encode_direct_yield_average(&record->direct_yield_average, wire, at);

  return at;
}

/* Parity Less Than 100 off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_parity_less_than100(ParityLessThan100 *record, const uint8_t *wire, size_t at) {
  at = decode_simple_average(&record->simple_average, wire, at);
  at = decode_divergence_average(&record->divergence_average, wire, at);
  at = decode_parity_average(&record->parity_average, wire, at);
  at = decode_direct_yield_average(&record->direct_yield_average, wire, at);

  return at;
}

/* what was read of Parity Less Than 100 is what was written, byte for byte */
static void equal_parity_less_than100(const ParityLessThan100 *read, const ParityLessThan100 *written) {
  equal_simple_average(&read->simple_average, &written->simple_average);
  equal_divergence_average(&read->divergence_average, &written->divergence_average);
  equal_parity_average(&read->parity_average, &written->parity_average);
  equal_direct_yield_average(&read->direct_yield_average, &written->direct_yield_average);
}

/* Parity Less Than 100: written and read back, then read and written back */
static void check_parity_less_than100(void) {
  ParityLessThan100 sent;
  ParityLessThan100 got;
  uint8_t wire[50];
  uint8_t again[50];

  any_parity_less_than100(&sent);
  assert(encode_parity_less_than100(&sent, wire, 0) == 50);
  assert(decode_parity_less_than100(&got, wire, 0) == 50);
  equal_parity_less_than100(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_parity_less_than100(&got, wire, 0) == 50);
  assert(encode_parity_less_than100(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Japanese Yen Cb Indicator Message: 208 bytes ---------------------------- */

/* In this tag, CB indicator (overall, parity 100 or higher, and parity less than 100) information will be set. This data appears as part of a statistics message. */
typedef struct {
  uint8_t reserved_2[2];                   /* bytes 0 to 1 */
  uint8_t output_time[6];                  /* bytes 2 to 7 */
  Overall overall;                         /* bytes 8 to 107 */
  Parity100OrHigher parity_100_or_higher;  /* bytes 108 to 157 */
  ParityLessThan100 parity_less_than_100;  /* bytes 158 to 207 */
} JapaneseYenCbIndicatorMessage;

/* any Japanese Yen Cb Indicator Message at all: every byte one the checker chooses */
static void any_japanese_yen_cb_indicator_message(JapaneseYenCbIndicatorMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = arbitrary(); }
  any_overall(&record->overall);
  any_parity100_or_higher(&record->parity_100_or_higher);
  any_parity_less_than100(&record->parity_less_than_100);
}

/* Japanese Yen Cb Indicator Message to the wire: 208 bytes from at, returning where the next byte goes */
static size_t encode_japanese_yen_cb_indicator_message(const JapaneseYenCbIndicatorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->output_time[i]; }
  at = encode_overall(&record->overall, wire, at);
  at = encode_parity100_or_higher(&record->parity_100_or_higher, wire, at);
  at = encode_parity_less_than100(&record->parity_less_than_100, wire, at);

  return at;
}

/* Japanese Yen Cb Indicator Message off the wire: 208 bytes from at, returning where the next byte lies */
static size_t decode_japanese_yen_cb_indicator_message(JapaneseYenCbIndicatorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = wire[at++]; }
  at = decode_overall(&record->overall, wire, at);
  at = decode_parity100_or_higher(&record->parity_100_or_higher, wire, at);
  at = decode_parity_less_than100(&record->parity_less_than_100, wire, at);

  return at;
}

/* what was read of Japanese Yen Cb Indicator Message is what was written, byte for byte */
static void equal_japanese_yen_cb_indicator_message(const JapaneseYenCbIndicatorMessage *read, const JapaneseYenCbIndicatorMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->output_time[i] == written->output_time[i]); }
  equal_overall(&read->overall, &written->overall);
  equal_parity100_or_higher(&read->parity_100_or_higher, &written->parity_100_or_higher);
  equal_parity_less_than100(&read->parity_less_than_100, &written->parity_less_than_100);
}

/* Japanese Yen Cb Indicator Message: written and read back, then read and written back */
static void check_japanese_yen_cb_indicator_message(void) {
  JapaneseYenCbIndicatorMessage sent;
  JapaneseYenCbIndicatorMessage got;
  uint8_t wire[208];
  uint8_t again[208];

  any_japanese_yen_cb_indicator_message(&sent);
  assert(encode_japanese_yen_cb_indicator_message(&sent, wire, 0) == 208);
  assert(decode_japanese_yen_cb_indicator_message(&got, wire, 0) == 208);
  equal_japanese_yen_cb_indicator_message(&got, &sent);

  for (size_t i = 0; i < 208; i++) { wire[i] = arbitrary(); }
  assert(decode_japanese_yen_cb_indicator_message(&got, wire, 0) == 208);
  assert(encode_japanese_yen_cb_indicator_message(&got, again, 0) == 208);
  for (size_t i = 0; i < 208; i++) { assert(again[i] == wire[i]); }
}

/* ---- Number Of Active Issues: 10 bytes --------------------------------------- */

/* Number of active issues */
typedef struct {
  uint8_t number_of_issues[5];  /* bytes 0 to 4 */
  uint8_t ratio[5];             /* bytes 5 to 9 */
} NumberOfActiveIssues;

/* any Number Of Active Issues at all: every byte one the checker chooses */
static void any_number_of_active_issues(NumberOfActiveIssues *record) {
  for (size_t i = 0; i < 5; i++) { record->number_of_issues[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->ratio[i] = arbitrary(); }
}

/* Number Of Active Issues to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_number_of_active_issues(const NumberOfActiveIssues *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->number_of_issues[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->ratio[i]; }

  return at;
}

/* Number Of Active Issues off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_number_of_active_issues(NumberOfActiveIssues *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->number_of_issues[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->ratio[i] = wire[at++]; }

  return at;
}

/* what was read of Number Of Active Issues is what was written, byte for byte */
static void equal_number_of_active_issues(const NumberOfActiveIssues *read, const NumberOfActiveIssues *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->number_of_issues[i] == written->number_of_issues[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->ratio[i] == written->ratio[i]); }
}

/* Number Of Active Issues: written and read back, then read and written back */
static void check_number_of_active_issues(void) {
  NumberOfActiveIssues sent;
  NumberOfActiveIssues got;
  uint8_t wire[10];
  uint8_t again[10];

  any_number_of_active_issues(&sent);
  assert(encode_number_of_active_issues(&sent, wire, 0) == 10);
  assert(decode_number_of_active_issues(&got, wire, 0) == 10);
  equal_number_of_active_issues(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_number_of_active_issues(&got, wire, 0) == 10);
  assert(encode_number_of_active_issues(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Number Of Gainers: 10 bytes --------------------------------------------- */

/* Number of gainers */
typedef struct {
  uint8_t number_of_issues[5];  /* bytes 0 to 4 */
  uint8_t ratio[5];             /* bytes 5 to 9 */
} NumberOfGainers;

/* any Number Of Gainers at all: every byte one the checker chooses */
static void any_number_of_gainers(NumberOfGainers *record) {
  for (size_t i = 0; i < 5; i++) { record->number_of_issues[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->ratio[i] = arbitrary(); }
}

/* Number Of Gainers to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_number_of_gainers(const NumberOfGainers *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->number_of_issues[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->ratio[i]; }

  return at;
}

/* Number Of Gainers off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_number_of_gainers(NumberOfGainers *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->number_of_issues[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->ratio[i] = wire[at++]; }

  return at;
}

/* what was read of Number Of Gainers is what was written, byte for byte */
static void equal_number_of_gainers(const NumberOfGainers *read, const NumberOfGainers *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->number_of_issues[i] == written->number_of_issues[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->ratio[i] == written->ratio[i]); }
}

/* Number Of Gainers: written and read back, then read and written back */
static void check_number_of_gainers(void) {
  NumberOfGainers sent;
  NumberOfGainers got;
  uint8_t wire[10];
  uint8_t again[10];

  any_number_of_gainers(&sent);
  assert(encode_number_of_gainers(&sent, wire, 0) == 10);
  assert(decode_number_of_gainers(&got, wire, 0) == 10);
  equal_number_of_gainers(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_number_of_gainers(&got, wire, 0) == 10);
  assert(encode_number_of_gainers(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Number Of Decliners: 10 bytes ------------------------------------------- */

/* Number of decliners */
typedef struct {
  uint8_t number_of_issues[5];  /* bytes 0 to 4 */
  uint8_t ratio[5];             /* bytes 5 to 9 */
} NumberOfDecliners;

/* any Number Of Decliners at all: every byte one the checker chooses */
static void any_number_of_decliners(NumberOfDecliners *record) {
  for (size_t i = 0; i < 5; i++) { record->number_of_issues[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->ratio[i] = arbitrary(); }
}

/* Number Of Decliners to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_number_of_decliners(const NumberOfDecliners *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->number_of_issues[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->ratio[i]; }

  return at;
}

/* Number Of Decliners off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_number_of_decliners(NumberOfDecliners *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->number_of_issues[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->ratio[i] = wire[at++]; }

  return at;
}

/* what was read of Number Of Decliners is what was written, byte for byte */
static void equal_number_of_decliners(const NumberOfDecliners *read, const NumberOfDecliners *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->number_of_issues[i] == written->number_of_issues[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->ratio[i] == written->ratio[i]); }
}

/* Number Of Decliners: written and read back, then read and written back */
static void check_number_of_decliners(void) {
  NumberOfDecliners sent;
  NumberOfDecliners got;
  uint8_t wire[10];
  uint8_t again[10];

  any_number_of_decliners(&sent);
  assert(encode_number_of_decliners(&sent, wire, 0) == 10);
  assert(decode_number_of_decliners(&got, wire, 0) == 10);
  equal_number_of_decliners(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_number_of_decliners(&got, wire, 0) == 10);
  assert(encode_number_of_decliners(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Number Of Issues With No Change: 10 bytes ------------------------------- */

/* Number of issues with no change */
typedef struct {
  uint8_t number_of_issues[5];  /* bytes 0 to 4 */
  uint8_t ratio[5];             /* bytes 5 to 9 */
} NumberOfIssuesWithNoChange;

/* any Number Of Issues With No Change at all: every byte one the checker chooses */
static void any_number_of_issues_with_no_change(NumberOfIssuesWithNoChange *record) {
  for (size_t i = 0; i < 5; i++) { record->number_of_issues[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->ratio[i] = arbitrary(); }
}

/* Number Of Issues With No Change to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_number_of_issues_with_no_change(const NumberOfIssuesWithNoChange *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->number_of_issues[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->ratio[i]; }

  return at;
}

/* Number Of Issues With No Change off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_number_of_issues_with_no_change(NumberOfIssuesWithNoChange *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->number_of_issues[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->ratio[i] = wire[at++]; }

  return at;
}

/* what was read of Number Of Issues With No Change is what was written, byte for byte */
static void equal_number_of_issues_with_no_change(const NumberOfIssuesWithNoChange *read, const NumberOfIssuesWithNoChange *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->number_of_issues[i] == written->number_of_issues[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->ratio[i] == written->ratio[i]); }
}

/* Number Of Issues With No Change: written and read back, then read and written back */
static void check_number_of_issues_with_no_change(void) {
  NumberOfIssuesWithNoChange sent;
  NumberOfIssuesWithNoChange got;
  uint8_t wire[10];
  uint8_t again[10];

  any_number_of_issues_with_no_change(&sent);
  assert(encode_number_of_issues_with_no_change(&sent, wire, 0) == 10);
  assert(decode_number_of_issues_with_no_change(&got, wire, 0) == 10);
  equal_number_of_issues_with_no_change(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_number_of_issues_with_no_change(&got, wire, 0) == 10);
  assert(encode_number_of_issues_with_no_change(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Number Of Issues With No Comparison: 10 bytes --------------------------- */

/* Number of issues with no comparison */
typedef struct {
  uint8_t number_of_issues[5];  /* bytes 0 to 4 */
  uint8_t ratio[5];             /* bytes 5 to 9 */
} NumberOfIssuesWithNoComparison;

/* any Number Of Issues With No Comparison at all: every byte one the checker chooses */
static void any_number_of_issues_with_no_comparison(NumberOfIssuesWithNoComparison *record) {
  for (size_t i = 0; i < 5; i++) { record->number_of_issues[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->ratio[i] = arbitrary(); }
}

/* Number Of Issues With No Comparison to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_number_of_issues_with_no_comparison(const NumberOfIssuesWithNoComparison *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->number_of_issues[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->ratio[i]; }

  return at;
}

/* Number Of Issues With No Comparison off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_number_of_issues_with_no_comparison(NumberOfIssuesWithNoComparison *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->number_of_issues[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->ratio[i] = wire[at++]; }

  return at;
}

/* what was read of Number Of Issues With No Comparison is what was written, byte for byte */
static void equal_number_of_issues_with_no_comparison(const NumberOfIssuesWithNoComparison *read, const NumberOfIssuesWithNoComparison *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->number_of_issues[i] == written->number_of_issues[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->ratio[i] == written->ratio[i]); }
}

/* Number Of Issues With No Comparison: written and read back, then read and written back */
static void check_number_of_issues_with_no_comparison(void) {
  NumberOfIssuesWithNoComparison sent;
  NumberOfIssuesWithNoComparison got;
  uint8_t wire[10];
  uint8_t again[10];

  any_number_of_issues_with_no_comparison(&sent);
  assert(encode_number_of_issues_with_no_comparison(&sent, wire, 0) == 10);
  assert(decode_number_of_issues_with_no_comparison(&got, wire, 0) == 10);
  equal_number_of_issues_with_no_comparison(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_number_of_issues_with_no_comparison(&got, wire, 0) == 10);
  assert(encode_number_of_issues_with_no_comparison(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Number Of Inactive Issues: 10 bytes ------------------------------------- */

/* Number of inactive issues */
typedef struct {
  uint8_t number_of_issues[5];  /* bytes 0 to 4 */
  uint8_t ratio[5];             /* bytes 5 to 9 */
} NumberOfInactiveIssues;

/* any Number Of Inactive Issues at all: every byte one the checker chooses */
static void any_number_of_inactive_issues(NumberOfInactiveIssues *record) {
  for (size_t i = 0; i < 5; i++) { record->number_of_issues[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->ratio[i] = arbitrary(); }
}

/* Number Of Inactive Issues to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_number_of_inactive_issues(const NumberOfInactiveIssues *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->number_of_issues[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->ratio[i]; }

  return at;
}

/* Number Of Inactive Issues off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_number_of_inactive_issues(NumberOfInactiveIssues *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->number_of_issues[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->ratio[i] = wire[at++]; }

  return at;
}

/* what was read of Number Of Inactive Issues is what was written, byte for byte */
static void equal_number_of_inactive_issues(const NumberOfInactiveIssues *read, const NumberOfInactiveIssues *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->number_of_issues[i] == written->number_of_issues[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->ratio[i] == written->ratio[i]); }
}

/* Number Of Inactive Issues: written and read back, then read and written back */
static void check_number_of_inactive_issues(void) {
  NumberOfInactiveIssues sent;
  NumberOfInactiveIssues got;
  uint8_t wire[10];
  uint8_t again[10];

  any_number_of_inactive_issues(&sent);
  assert(encode_number_of_inactive_issues(&sent, wire, 0) == 10);
  assert(decode_number_of_inactive_issues(&got, wire, 0) == 10);
  equal_number_of_inactive_issues(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_number_of_inactive_issues(&got, wire, 0) == 10);
  assert(encode_number_of_inactive_issues(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Number Of Gainers Decliners Message: 82 bytes --------------------------- */

/* In this tag, number of listed issues and number of gainers/decliners information by market (issue classification) will be set. This data appears as part of a statistics message. */
typedef struct {
  uint8_t reserved_2[2];                                               /* bytes 0 to 1 */
  uint8_t output_time[6];                                              /* bytes 2 to 7 */
  uint8_t issue_classification_code[4];                                /* bytes 8 to 11 */
  uint8_t number_of_listed_companies[5];                               /* bytes 12 to 16 */
  uint8_t number_of_listed_issues[5];                                  /* bytes 17 to 21 */
  NumberOfActiveIssues number_of_active_issues;                        /* bytes 22 to 31 */
  NumberOfGainers number_of_gainers;                                   /* bytes 32 to 41 */
  NumberOfDecliners number_of_decliners;                               /* bytes 42 to 51 */
  NumberOfIssuesWithNoChange number_of_issues_with_no_change;          /* bytes 52 to 61 */
  NumberOfIssuesWithNoComparison number_of_issues_with_no_comparison;  /* bytes 62 to 71 */
  NumberOfInactiveIssues number_of_inactive_issues;                    /* bytes 72 to 81 */
} NumberOfGainersDeclinersMessage;

/* any Number Of Gainers Decliners Message at all: every byte one the checker chooses */
static void any_number_of_gainers_decliners_message(NumberOfGainersDeclinersMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->number_of_listed_companies[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->number_of_listed_issues[i] = arbitrary(); }
  any_number_of_active_issues(&record->number_of_active_issues);
  any_number_of_gainers(&record->number_of_gainers);
  any_number_of_decliners(&record->number_of_decliners);
  any_number_of_issues_with_no_change(&record->number_of_issues_with_no_change);
  any_number_of_issues_with_no_comparison(&record->number_of_issues_with_no_comparison);
  any_number_of_inactive_issues(&record->number_of_inactive_issues);
}

/* Number Of Gainers Decliners Message to the wire: 82 bytes from at, returning where the next byte goes */
static size_t encode_number_of_gainers_decliners_message(const NumberOfGainersDeclinersMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->output_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->issue_classification_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->number_of_listed_companies[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->number_of_listed_issues[i]; }
  at = encode_number_of_active_issues(&record->number_of_active_issues, wire, at);
  at = encode_number_of_gainers(&record->number_of_gainers, wire, at);
  at = encode_number_of_decliners(&record->number_of_decliners, wire, at);
  at = encode_number_of_issues_with_no_change(&record->number_of_issues_with_no_change, wire, at);
  at = encode_number_of_issues_with_no_comparison(&record->number_of_issues_with_no_comparison, wire, at);
  at = encode_number_of_inactive_issues(&record->number_of_inactive_issues, wire, at);

  return at;
}

/* Number Of Gainers Decliners Message off the wire: 82 bytes from at, returning where the next byte lies */
static size_t decode_number_of_gainers_decliners_message(NumberOfGainersDeclinersMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->number_of_listed_companies[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->number_of_listed_issues[i] = wire[at++]; }
  at = decode_number_of_active_issues(&record->number_of_active_issues, wire, at);
  at = decode_number_of_gainers(&record->number_of_gainers, wire, at);
  at = decode_number_of_decliners(&record->number_of_decliners, wire, at);
  at = decode_number_of_issues_with_no_change(&record->number_of_issues_with_no_change, wire, at);
  at = decode_number_of_issues_with_no_comparison(&record->number_of_issues_with_no_comparison, wire, at);
  at = decode_number_of_inactive_issues(&record->number_of_inactive_issues, wire, at);

  return at;
}

/* what was read of Number Of Gainers Decliners Message is what was written, byte for byte */
static void equal_number_of_gainers_decliners_message(const NumberOfGainersDeclinersMessage *read, const NumberOfGainersDeclinersMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->output_time[i] == written->output_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->issue_classification_code[i] == written->issue_classification_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->number_of_listed_companies[i] == written->number_of_listed_companies[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->number_of_listed_issues[i] == written->number_of_listed_issues[i]); }
  equal_number_of_active_issues(&read->number_of_active_issues, &written->number_of_active_issues);
  equal_number_of_gainers(&read->number_of_gainers, &written->number_of_gainers);
  equal_number_of_decliners(&read->number_of_decliners, &written->number_of_decliners);
  equal_number_of_issues_with_no_change(&read->number_of_issues_with_no_change, &written->number_of_issues_with_no_change);
  equal_number_of_issues_with_no_comparison(&read->number_of_issues_with_no_comparison, &written->number_of_issues_with_no_comparison);
  equal_number_of_inactive_issues(&read->number_of_inactive_issues, &written->number_of_inactive_issues);
}

/* Number Of Gainers Decliners Message: written and read back, then read and written back */
static void check_number_of_gainers_decliners_message(void) {
  NumberOfGainersDeclinersMessage sent;
  NumberOfGainersDeclinersMessage got;
  uint8_t wire[82];
  uint8_t again[82];

  any_number_of_gainers_decliners_message(&sent);
  assert(encode_number_of_gainers_decliners_message(&sent, wire, 0) == 82);
  assert(decode_number_of_gainers_decliners_message(&got, wire, 0) == 82);
  equal_number_of_gainers_decliners_message(&got, &sent);

  for (size_t i = 0; i < 82; i++) { wire[i] = arbitrary(); }
  assert(decode_number_of_gainers_decliners_message(&got, wire, 0) == 82);
  assert(encode_number_of_gainers_decliners_message(&got, again, 0) == 82);
  for (size_t i = 0; i < 82; i++) { assert(again[i] == wire[i]); }
}

/* ---- Estimated Total Trading Volume: 15 bytes -------------------------------- */

/* Estimated total trading volume */
typedef struct {
  uint8_t trading_volume_turnover_unit_flag;         /* byte 0 */
  uint8_t estimated_total_trading_volume_value[14];  /* bytes 1 to 14 */
} EstimatedTotalTradingVolume;

/* any Estimated Total Trading Volume at all: every byte one the checker chooses */
static void any_estimated_total_trading_volume(EstimatedTotalTradingVolume *record) {
  record->trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->estimated_total_trading_volume_value[i] = arbitrary(); }
}

/* Estimated Total Trading Volume to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_estimated_total_trading_volume(const EstimatedTotalTradingVolume *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->estimated_total_trading_volume_value[i]; }

  return at;
}

/* Estimated Total Trading Volume off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_estimated_total_trading_volume(EstimatedTotalTradingVolume *record, const uint8_t *wire, size_t at) {
  record->trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->estimated_total_trading_volume_value[i] = wire[at++]; }

  return at;
}

/* what was read of Estimated Total Trading Volume is what was written, byte for byte */
static void equal_estimated_total_trading_volume(const EstimatedTotalTradingVolume *read, const EstimatedTotalTradingVolume *written) {
  assert(read->trading_volume_turnover_unit_flag == written->trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->estimated_total_trading_volume_value[i] == written->estimated_total_trading_volume_value[i]); }
}

/* Estimated Total Trading Volume: written and read back, then read and written back */
static void check_estimated_total_trading_volume(void) {
  EstimatedTotalTradingVolume sent;
  EstimatedTotalTradingVolume got;
  uint8_t wire[15];
  uint8_t again[15];

  any_estimated_total_trading_volume(&sent);
  assert(encode_estimated_total_trading_volume(&sent, wire, 0) == 15);
  assert(decode_estimated_total_trading_volume(&got, wire, 0) == 15);
  equal_estimated_total_trading_volume(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_estimated_total_trading_volume(&got, wire, 0) == 15);
  assert(encode_estimated_total_trading_volume(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Estimated Total Trading Volume Message: 29 bytes ------------------------ */

/* In this tag, estimated total trading volume information for each market (issue classification) will be set. This data appears as part of a statistics message. */
typedef struct {
  uint8_t reserved_2[2];                                       /* bytes 0 to 1 */
  uint8_t output_time[6];                                      /* bytes 2 to 7 */
  uint8_t issue_classification_code[4];                        /* bytes 8 to 11 */
  uint8_t other_classification_code[2];                        /* bytes 12 to 13 */
  EstimatedTotalTradingVolume estimated_total_trading_volume;  /* bytes 14 to 28 */
} EstimatedTotalTradingVolumeMessage;

/* any Estimated Total Trading Volume Message at all: every byte one the checker chooses */
static void any_estimated_total_trading_volume_message(EstimatedTotalTradingVolumeMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->other_classification_code[i] = arbitrary(); }
  any_estimated_total_trading_volume(&record->estimated_total_trading_volume);
}

/* Estimated Total Trading Volume Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_estimated_total_trading_volume_message(const EstimatedTotalTradingVolumeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->output_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->issue_classification_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->other_classification_code[i]; }
  at = encode_estimated_total_trading_volume(&record->estimated_total_trading_volume, wire, at);

  return at;
}

/* Estimated Total Trading Volume Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_estimated_total_trading_volume_message(EstimatedTotalTradingVolumeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->other_classification_code[i] = wire[at++]; }
  at = decode_estimated_total_trading_volume(&record->estimated_total_trading_volume, wire, at);

  return at;
}

/* what was read of Estimated Total Trading Volume Message is what was written, byte for byte */
static void equal_estimated_total_trading_volume_message(const EstimatedTotalTradingVolumeMessage *read, const EstimatedTotalTradingVolumeMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->output_time[i] == written->output_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->issue_classification_code[i] == written->issue_classification_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->other_classification_code[i] == written->other_classification_code[i]); }
  equal_estimated_total_trading_volume(&read->estimated_total_trading_volume, &written->estimated_total_trading_volume);
}

/* Estimated Total Trading Volume Message: written and read back, then read and written back */
static void check_estimated_total_trading_volume_message(void) {
  EstimatedTotalTradingVolumeMessage sent;
  EstimatedTotalTradingVolumeMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_estimated_total_trading_volume_message(&sent);
  assert(encode_estimated_total_trading_volume_message(&sent, wire, 0) == 29);
  assert(decode_estimated_total_trading_volume_message(&got, wire, 0) == 29);
  equal_estimated_total_trading_volume_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_estimated_total_trading_volume_message(&got, wire, 0) == 29);
  assert(encode_estimated_total_trading_volume_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Estimated Total Turnover: 16 bytes -------------------------------------- */

/* Estimated total turnover */
typedef struct {
  uint8_t trading_volume_turnover_unit_flag;   /* byte 0 */
  uint8_t estimated_total_turnover_value[14];  /* bytes 1 to 14 */
  uint8_t reserved_1;                          /* byte 15 */
} EstimatedTotalTurnover;

/* any Estimated Total Turnover at all: every byte one the checker chooses */
static void any_estimated_total_turnover(EstimatedTotalTurnover *record) {
  record->trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->estimated_total_turnover_value[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Estimated Total Turnover to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_estimated_total_turnover(const EstimatedTotalTurnover *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->estimated_total_turnover_value[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Estimated Total Turnover off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_estimated_total_turnover(EstimatedTotalTurnover *record, const uint8_t *wire, size_t at) {
  record->trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->estimated_total_turnover_value[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Estimated Total Turnover is what was written, byte for byte */
static void equal_estimated_total_turnover(const EstimatedTotalTurnover *read, const EstimatedTotalTurnover *written) {
  assert(read->trading_volume_turnover_unit_flag == written->trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->estimated_total_turnover_value[i] == written->estimated_total_turnover_value[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Estimated Total Turnover: written and read back, then read and written back */
static void check_estimated_total_turnover(void) {
  EstimatedTotalTurnover sent;
  EstimatedTotalTurnover got;
  uint8_t wire[16];
  uint8_t again[16];

  any_estimated_total_turnover(&sent);
  assert(encode_estimated_total_turnover(&sent, wire, 0) == 16);
  assert(decode_estimated_total_turnover(&got, wire, 0) == 16);
  equal_estimated_total_turnover(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_estimated_total_turnover(&got, wire, 0) == 16);
  assert(encode_estimated_total_turnover(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Estimated Total Turnover Message: 30 bytes ------------------------------ */

/* In this tag, estimated total turnover information for each market (issue classification) will be set. This data appears as part of a statistics message. */
typedef struct {
  uint8_t reserved_2[2];                            /* bytes 0 to 1 */
  uint8_t output_time[6];                           /* bytes 2 to 7 */
  uint8_t issue_classification_code[4];             /* bytes 8 to 11 */
  uint8_t other_classification_flag[2];             /* bytes 12 to 13 */
  EstimatedTotalTurnover estimated_total_turnover;  /* bytes 14 to 29 */
} EstimatedTotalTurnoverMessage;

/* any Estimated Total Turnover Message at all: every byte one the checker chooses */
static void any_estimated_total_turnover_message(EstimatedTotalTurnoverMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->other_classification_flag[i] = arbitrary(); }
  any_estimated_total_turnover(&record->estimated_total_turnover);
}

/* Estimated Total Turnover Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_estimated_total_turnover_message(const EstimatedTotalTurnoverMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->output_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->issue_classification_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->other_classification_flag[i]; }
  at = encode_estimated_total_turnover(&record->estimated_total_turnover, wire, at);

  return at;
}

/* Estimated Total Turnover Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_estimated_total_turnover_message(EstimatedTotalTurnoverMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->other_classification_flag[i] = wire[at++]; }
  at = decode_estimated_total_turnover(&record->estimated_total_turnover, wire, at);

  return at;
}

/* what was read of Estimated Total Turnover Message is what was written, byte for byte */
static void equal_estimated_total_turnover_message(const EstimatedTotalTurnoverMessage *read, const EstimatedTotalTurnoverMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->output_time[i] == written->output_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->issue_classification_code[i] == written->issue_classification_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->other_classification_flag[i] == written->other_classification_flag[i]); }
  equal_estimated_total_turnover(&read->estimated_total_turnover, &written->estimated_total_turnover);
}

/* Estimated Total Turnover Message: written and read back, then read and written back */
static void check_estimated_total_turnover_message(void) {
  EstimatedTotalTurnoverMessage sent;
  EstimatedTotalTurnoverMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_estimated_total_turnover_message(&sent);
  assert(encode_estimated_total_turnover_message(&sent, wire, 0) == 30);
  assert(decode_estimated_total_turnover_message(&got, wire, 0) == 30);
  equal_estimated_total_turnover_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_estimated_total_turnover_message(&got, wire, 0) == 30);
  assert(encode_estimated_total_turnover_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Vwap By Market: 33 bytes ------------------------------------------------ */

/* VWAP by market */
typedef struct {
  uint8_t unit_flag;                  /* byte 0 */
  uint8_t vwap_by_market_value[14];   /* bytes 1 to 14 */
  uint8_t sign;                       /* byte 15 */
  uint8_t reserved_1;                 /* byte 16 */
  uint8_t second_unit_flag;           /* byte 17 */
  uint8_t day_on_day_comparison[14];  /* bytes 18 to 31 */
  uint8_t second_sign;                /* byte 32 */
} VwapByMarket;

/* any Vwap By Market at all: every byte one the checker chooses */
static void any_vwap_by_market(VwapByMarket *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->vwap_by_market_value[i] = arbitrary(); }
  record->sign = arbitrary();
  record->reserved_1 = arbitrary();
  record->second_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->day_on_day_comparison[i] = arbitrary(); }
  record->second_sign = arbitrary();
}

/* Vwap By Market to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_vwap_by_market(const VwapByMarket *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->vwap_by_market_value[i]; }
  wire[at++] = record->sign;
  wire[at++] = record->reserved_1;
  wire[at++] = record->second_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->day_on_day_comparison[i]; }
  wire[at++] = record->second_sign;

  return at;
}

/* Vwap By Market off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_vwap_by_market(VwapByMarket *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->vwap_by_market_value[i] = wire[at++]; }
  record->sign = wire[at++];
  record->reserved_1 = wire[at++];
  record->second_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->day_on_day_comparison[i] = wire[at++]; }
  record->second_sign = wire[at++];

  return at;
}

/* what was read of Vwap By Market is what was written, byte for byte */
static void equal_vwap_by_market(const VwapByMarket *read, const VwapByMarket *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->vwap_by_market_value[i] == written->vwap_by_market_value[i]); }
  assert(read->sign == written->sign);
  assert(read->reserved_1 == written->reserved_1);
  assert(read->second_unit_flag == written->second_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->day_on_day_comparison[i] == written->day_on_day_comparison[i]); }
  assert(read->second_sign == written->second_sign);
}

/* Vwap By Market: written and read back, then read and written back */
static void check_vwap_by_market(void) {
  VwapByMarket sent;
  VwapByMarket got;
  uint8_t wire[33];
  uint8_t again[33];

  any_vwap_by_market(&sent);
  assert(encode_vwap_by_market(&sent, wire, 0) == 33);
  assert(decode_vwap_by_market(&got, wire, 0) == 33);
  equal_vwap_by_market(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_vwap_by_market(&got, wire, 0) == 33);
  assert(encode_vwap_by_market(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Vwap By Market Message: 45 bytes ---------------------------------------- */

/* In this tag, volume weighted average price (VWAP) information for each market (issue classification) will be set. This data appears as part of a statistics message. */
typedef struct {
  uint8_t reserved_2[2];                 /* bytes 0 to 1 */
  uint8_t output_time[6];                /* bytes 2 to 7 */
  uint8_t issue_classification_code[4];  /* bytes 8 to 11 */
  VwapByMarket vwap_by_market;           /* bytes 12 to 44 */
} VwapByMarketMessage;

/* any Vwap By Market Message at all: every byte one the checker chooses */
static void any_vwap_by_market_message(VwapByMarketMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = arbitrary(); }
  any_vwap_by_market(&record->vwap_by_market);
}

/* Vwap By Market Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_vwap_by_market_message(const VwapByMarketMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->output_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->issue_classification_code[i]; }
  at = encode_vwap_by_market(&record->vwap_by_market, wire, at);

  return at;
}

/* Vwap By Market Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_vwap_by_market_message(VwapByMarketMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->issue_classification_code[i] = wire[at++]; }
  at = decode_vwap_by_market(&record->vwap_by_market, wire, at);

  return at;
}

/* what was read of Vwap By Market Message is what was written, byte for byte */
static void equal_vwap_by_market_message(const VwapByMarketMessage *read, const VwapByMarketMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->output_time[i] == written->output_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->issue_classification_code[i] == written->issue_classification_code[i]); }
  equal_vwap_by_market(&read->vwap_by_market, &written->vwap_by_market);
}

/* Vwap By Market Message: written and read back, then read and written back */
static void check_vwap_by_market_message(void) {
  VwapByMarketMessage sent;
  VwapByMarketMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_vwap_by_market_message(&sent);
  assert(encode_vwap_by_market_message(&sent, wire, 0) == 45);
  assert(decode_vwap_by_market_message(&got, wire, 0) == 45);
  equal_vwap_by_market_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_vwap_by_market_message(&got, wire, 0) == 45);
  assert(encode_vwap_by_market_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Volume: 60 bytes ------------------------------------------------ */

/* Trading volume */
typedef struct {
  uint8_t trading_volume_turnover_unit_flag;         /* byte 0 */
  uint8_t single_issue_transaction[14];              /* bytes 1 to 14 */
  uint8_t second_trading_volume_turnover_unit_flag;  /* byte 15 */
  uint8_t closing_price_transaction[14];             /* bytes 16 to 29 */
  uint8_t third_trading_volume_turnover_unit_flag;   /* byte 30 */
  uint8_t basket_transaction[14];                    /* bytes 31 to 44 */
  uint8_t fourth_trading_volume_turnover_unit_flag;  /* byte 45 */
  uint8_t aggregate_trading_volume[14];              /* bytes 46 to 59 */
} TradingVolume;

/* any Trading Volume at all: every byte one the checker chooses */
static void any_trading_volume(TradingVolume *record) {
  record->trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->single_issue_transaction[i] = arbitrary(); }
  record->second_trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->closing_price_transaction[i] = arbitrary(); }
  record->third_trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->basket_transaction[i] = arbitrary(); }
  record->fourth_trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->aggregate_trading_volume[i] = arbitrary(); }
}

/* Trading Volume to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_trading_volume(const TradingVolume *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->single_issue_transaction[i]; }
  wire[at++] = record->second_trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->closing_price_transaction[i]; }
  wire[at++] = record->third_trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->basket_transaction[i]; }
  wire[at++] = record->fourth_trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->aggregate_trading_volume[i]; }

  return at;
}

/* Trading Volume off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_trading_volume(TradingVolume *record, const uint8_t *wire, size_t at) {
  record->trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->single_issue_transaction[i] = wire[at++]; }
  record->second_trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->closing_price_transaction[i] = wire[at++]; }
  record->third_trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->basket_transaction[i] = wire[at++]; }
  record->fourth_trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->aggregate_trading_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Volume is what was written, byte for byte */
static void equal_trading_volume(const TradingVolume *read, const TradingVolume *written) {
  assert(read->trading_volume_turnover_unit_flag == written->trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->single_issue_transaction[i] == written->single_issue_transaction[i]); }
  assert(read->second_trading_volume_turnover_unit_flag == written->second_trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->closing_price_transaction[i] == written->closing_price_transaction[i]); }
  assert(read->third_trading_volume_turnover_unit_flag == written->third_trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->basket_transaction[i] == written->basket_transaction[i]); }
  assert(read->fourth_trading_volume_turnover_unit_flag == written->fourth_trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->aggregate_trading_volume[i] == written->aggregate_trading_volume[i]); }
}

/* Trading Volume: written and read back, then read and written back */
static void check_trading_volume(void) {
  TradingVolume sent;
  TradingVolume got;
  uint8_t wire[60];
  uint8_t again[60];

  any_trading_volume(&sent);
  assert(encode_trading_volume(&sent, wire, 0) == 60);
  assert(decode_trading_volume(&got, wire, 0) == 60);
  equal_trading_volume(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_volume(&got, wire, 0) == 60);
  assert(encode_trading_volume(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Turnover: 60 bytes ------------------------------------------------------ */

/* Turnover */
typedef struct {
  uint8_t trading_volume_turnover_unit_flag;         /* byte 0 */
  uint8_t single_issue_transaction[14];              /* bytes 1 to 14 */
  uint8_t second_trading_volume_turnover_unit_flag;  /* byte 15 */
  uint8_t closing_price_transaction[14];             /* bytes 16 to 29 */
  uint8_t third_trading_volume_turnover_unit_flag;   /* byte 30 */
  uint8_t basket_transaction[14];                    /* bytes 31 to 44 */
  uint8_t fourth_trading_volume_turnover_unit_flag;  /* byte 45 */
  uint8_t aggregate_turnover[14];                    /* bytes 46 to 59 */
} Turnover;

/* any Turnover at all: every byte one the checker chooses */
static void any_turnover(Turnover *record) {
  record->trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->single_issue_transaction[i] = arbitrary(); }
  record->second_trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->closing_price_transaction[i] = arbitrary(); }
  record->third_trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->basket_transaction[i] = arbitrary(); }
  record->fourth_trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->aggregate_turnover[i] = arbitrary(); }
}

/* Turnover to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_turnover(const Turnover *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->single_issue_transaction[i]; }
  wire[at++] = record->second_trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->closing_price_transaction[i]; }
  wire[at++] = record->third_trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->basket_transaction[i]; }
  wire[at++] = record->fourth_trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->aggregate_turnover[i]; }

  return at;
}

/* Turnover off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_turnover(Turnover *record, const uint8_t *wire, size_t at) {
  record->trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->single_issue_transaction[i] = wire[at++]; }
  record->second_trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->closing_price_transaction[i] = wire[at++]; }
  record->third_trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->basket_transaction[i] = wire[at++]; }
  record->fourth_trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->aggregate_turnover[i] = wire[at++]; }

  return at;
}

/* what was read of Turnover is what was written, byte for byte */
static void equal_turnover(const Turnover *read, const Turnover *written) {
  assert(read->trading_volume_turnover_unit_flag == written->trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->single_issue_transaction[i] == written->single_issue_transaction[i]); }
  assert(read->second_trading_volume_turnover_unit_flag == written->second_trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->closing_price_transaction[i] == written->closing_price_transaction[i]); }
  assert(read->third_trading_volume_turnover_unit_flag == written->third_trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->basket_transaction[i] == written->basket_transaction[i]); }
  assert(read->fourth_trading_volume_turnover_unit_flag == written->fourth_trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->aggregate_turnover[i] == written->aggregate_turnover[i]); }
}

/* Turnover: written and read back, then read and written back */
static void check_turnover(void) {
  Turnover sent;
  Turnover got;
  uint8_t wire[60];
  uint8_t again[60];

  any_turnover(&sent);
  assert(encode_turnover(&sent, wire, 0) == 60);
  assert(decode_turnover(&got, wire, 0) == 60);
  equal_turnover(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_turnover(&got, wire, 0) == 60);
  assert(encode_turnover(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Number Of Transactions: 16 bytes ---------------------------------------- */

/* Number of transactions */
typedef struct {
  uint8_t single_issue_transaction_count[8];  /* bytes 0 to 7 */
  uint8_t basket_transaction_count[8];        /* bytes 8 to 15 */
} NumberOfTransactions;

/* any Number Of Transactions at all: every byte one the checker chooses */
static void any_number_of_transactions(NumberOfTransactions *record) {
  for (size_t i = 0; i < 8; i++) { record->single_issue_transaction_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->basket_transaction_count[i] = arbitrary(); }
}

/* Number Of Transactions to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_number_of_transactions(const NumberOfTransactions *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->single_issue_transaction_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->basket_transaction_count[i]; }

  return at;
}

/* Number Of Transactions off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_number_of_transactions(NumberOfTransactions *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->single_issue_transaction_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->basket_transaction_count[i] = wire[at++]; }

  return at;
}

/* what was read of Number Of Transactions is what was written, byte for byte */
static void equal_number_of_transactions(const NumberOfTransactions *read, const NumberOfTransactions *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->single_issue_transaction_count[i] == written->single_issue_transaction_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->basket_transaction_count[i] == written->basket_transaction_count[i]); }
}

/* Number Of Transactions: written and read back, then read and written back */
static void check_number_of_transactions(void) {
  NumberOfTransactions sent;
  NumberOfTransactions got;
  uint8_t wire[16];
  uint8_t again[16];

  any_number_of_transactions(&sent);
  assert(encode_number_of_transactions(&sent, wire, 0) == 16);
  assert(decode_number_of_transactions(&got, wire, 0) == 16);
  equal_number_of_transactions(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_number_of_transactions(&got, wire, 0) == 16);
  assert(encode_number_of_transactions(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- ToSTNeT Statistics Message: 146 bytes ----------------------------------- */

/* In this tag, the quantities traded on the ToSTNeT and other information will be set. This data appears as part of a statistics message. */
typedef struct {
  uint8_t reserved_2[2];                        /* bytes 0 to 1 */
  uint8_t output_time[6];                       /* bytes 2 to 7 */
  uint8_t other_classification_flag[2];         /* bytes 8 to 9 */
  TradingVolume trading_volume;                 /* bytes 10 to 69 */
  Turnover turnover;                            /* bytes 70 to 129 */
  NumberOfTransactions number_of_transactions;  /* bytes 130 to 145 */
} ToSTNeTStatisticsMessage;

/* any ToSTNeT Statistics Message at all: every byte one the checker chooses */
static void any_to_s_t_ne_t_statistics_message(ToSTNeTStatisticsMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->other_classification_flag[i] = arbitrary(); }
  any_trading_volume(&record->trading_volume);
  any_turnover(&record->turnover);
  any_number_of_transactions(&record->number_of_transactions);
}

/* ToSTNeT Statistics Message to the wire: 146 bytes from at, returning where the next byte goes */
static size_t encode_to_s_t_ne_t_statistics_message(const ToSTNeTStatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->output_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->other_classification_flag[i]; }
  at = encode_trading_volume(&record->trading_volume, wire, at);
  at = encode_turnover(&record->turnover, wire, at);
  at = encode_number_of_transactions(&record->number_of_transactions, wire, at);

  return at;
}

/* ToSTNeT Statistics Message off the wire: 146 bytes from at, returning where the next byte lies */
static size_t decode_to_s_t_ne_t_statistics_message(ToSTNeTStatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->output_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->other_classification_flag[i] = wire[at++]; }
  at = decode_trading_volume(&record->trading_volume, wire, at);
  at = decode_turnover(&record->turnover, wire, at);
  at = decode_number_of_transactions(&record->number_of_transactions, wire, at);

  return at;
}

/* what was read of ToSTNeT Statistics Message is what was written, byte for byte */
static void equal_to_s_t_ne_t_statistics_message(const ToSTNeTStatisticsMessage *read, const ToSTNeTStatisticsMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->output_time[i] == written->output_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->other_classification_flag[i] == written->other_classification_flag[i]); }
  equal_trading_volume(&read->trading_volume, &written->trading_volume);
  equal_turnover(&read->turnover, &written->turnover);
  equal_number_of_transactions(&read->number_of_transactions, &written->number_of_transactions);
}

/* ToSTNeT Statistics Message: written and read back, then read and written back */
static void check_to_s_t_ne_t_statistics_message(void) {
  ToSTNeTStatisticsMessage sent;
  ToSTNeTStatisticsMessage got;
  uint8_t wire[146];
  uint8_t again[146];

  any_to_s_t_ne_t_statistics_message(&sent);
  assert(encode_to_s_t_ne_t_statistics_message(&sent, wire, 0) == 146);
  assert(decode_to_s_t_ne_t_statistics_message(&got, wire, 0) == 146);
  equal_to_s_t_ne_t_statistics_message(&got, &sent);

  for (size_t i = 0; i < 146; i++) { wire[i] = arbitrary(); }
  assert(decode_to_s_t_ne_t_statistics_message(&got, wire, 0) == 146);
  assert(encode_to_s_t_ne_t_statistics_message(&got, again, 0) == 146);
  for (size_t i = 0; i < 146; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open: 23 bytes ---------------------------------------------------------- */

/* Open */
typedef struct {
  uint8_t unit_flag;           /* byte 0 */
  uint8_t index_value[14];     /* bytes 1 to 14 */
  uint8_t sign;                /* byte 15 */
  uint8_t time_c_6_hhmmss[6];  /* bytes 16 to 21 */
  uint8_t flag;                /* byte 22 */
} Open;

/* any Open at all: every byte one the checker chooses */
static void any_open(Open *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->index_value[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmmss[i] = arbitrary(); }
  record->flag = arbitrary();
}

/* Open to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_open(const Open *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->index_value[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6_hhmmss[i]; }
  wire[at++] = record->flag;

  return at;
}

/* Open off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_open(Open *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->index_value[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmmss[i] = wire[at++]; }
  record->flag = wire[at++];

  return at;
}

/* what was read of Open is what was written, byte for byte */
static void equal_open(const Open *read, const Open *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->index_value[i] == written->index_value[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6_hhmmss[i] == written->time_c_6_hhmmss[i]); }
  assert(read->flag == written->flag);
}

/* Open: written and read back, then read and written back */
static void check_open(void) {
  Open sent;
  Open got;
  uint8_t wire[23];
  uint8_t again[23];

  any_open(&sent);
  assert(encode_open(&sent, wire, 0) == 23);
  assert(decode_open(&got, wire, 0) == 23);
  equal_open(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_open(&got, wire, 0) == 23);
  assert(encode_open(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Highest: 23 bytes ------------------------------------------------------- */

/* Highest */
typedef struct {
  uint8_t unit_flag;           /* byte 0 */
  uint8_t index_value[14];     /* bytes 1 to 14 */
  uint8_t sign;                /* byte 15 */
  uint8_t time_c_6_hhmmss[6];  /* bytes 16 to 21 */
  uint8_t flag;                /* byte 22 */
} Highest;

/* any Highest at all: every byte one the checker chooses */
static void any_highest(Highest *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->index_value[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmmss[i] = arbitrary(); }
  record->flag = arbitrary();
}

/* Highest to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_highest(const Highest *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->index_value[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6_hhmmss[i]; }
  wire[at++] = record->flag;

  return at;
}

/* Highest off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_highest(Highest *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->index_value[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmmss[i] = wire[at++]; }
  record->flag = wire[at++];

  return at;
}

/* what was read of Highest is what was written, byte for byte */
static void equal_highest(const Highest *read, const Highest *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->index_value[i] == written->index_value[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6_hhmmss[i] == written->time_c_6_hhmmss[i]); }
  assert(read->flag == written->flag);
}

/* Highest: written and read back, then read and written back */
static void check_highest(void) {
  Highest sent;
  Highest got;
  uint8_t wire[23];
  uint8_t again[23];

  any_highest(&sent);
  assert(encode_highest(&sent, wire, 0) == 23);
  assert(decode_highest(&got, wire, 0) == 23);
  equal_highest(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_highest(&got, wire, 0) == 23);
  assert(encode_highest(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Lowest: 23 bytes -------------------------------------------------------- */

/* Lowest */
typedef struct {
  uint8_t unit_flag;           /* byte 0 */
  uint8_t index_value[14];     /* bytes 1 to 14 */
  uint8_t sign;                /* byte 15 */
  uint8_t time_c_6_hhmmss[6];  /* bytes 16 to 21 */
  uint8_t flag;                /* byte 22 */
} Lowest;

/* any Lowest at all: every byte one the checker chooses */
static void any_lowest(Lowest *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->index_value[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmmss[i] = arbitrary(); }
  record->flag = arbitrary();
}

/* Lowest to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_lowest(const Lowest *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->index_value[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6_hhmmss[i]; }
  wire[at++] = record->flag;

  return at;
}

/* Lowest off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_lowest(Lowest *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->index_value[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmmss[i] = wire[at++]; }
  record->flag = wire[at++];

  return at;
}

/* what was read of Lowest is what was written, byte for byte */
static void equal_lowest(const Lowest *read, const Lowest *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->index_value[i] == written->index_value[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6_hhmmss[i] == written->time_c_6_hhmmss[i]); }
  assert(read->flag == written->flag);
}

/* Lowest: written and read back, then read and written back */
static void check_lowest(void) {
  Lowest sent;
  Lowest got;
  uint8_t wire[23];
  uint8_t again[23];

  any_lowest(&sent);
  assert(encode_lowest(&sent, wire, 0) == 23);
  assert(decode_lowest(&got, wire, 0) == 23);
  equal_lowest(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_lowest(&got, wire, 0) == 23);
  assert(encode_lowest(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Current Price: 23 bytes ------------------------------------------------- */

/* Current price */
typedef struct {
  uint8_t unit_flag;           /* byte 0 */
  uint8_t index_value[14];     /* bytes 1 to 14 */
  uint8_t sign;                /* byte 15 */
  uint8_t time_c_6_hhmmss[6];  /* bytes 16 to 21 */
  uint8_t flag;                /* byte 22 */
} CurrentPrice;

/* any Current Price at all: every byte one the checker chooses */
static void any_current_price(CurrentPrice *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->index_value[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmmss[i] = arbitrary(); }
  record->flag = arbitrary();
}

/* Current Price to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_current_price(const CurrentPrice *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->index_value[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6_hhmmss[i]; }
  wire[at++] = record->flag;

  return at;
}

/* Current Price off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_current_price(CurrentPrice *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->index_value[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmmss[i] = wire[at++]; }
  record->flag = wire[at++];

  return at;
}

/* what was read of Current Price is what was written, byte for byte */
static void equal_current_price(const CurrentPrice *read, const CurrentPrice *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->index_value[i] == written->index_value[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6_hhmmss[i] == written->time_c_6_hhmmss[i]); }
  assert(read->flag == written->flag);
}

/* Current Price: written and read back, then read and written back */
static void check_current_price(void) {
  CurrentPrice sent;
  CurrentPrice got;
  uint8_t wire[23];
  uint8_t again[23];

  any_current_price(&sent);
  assert(encode_current_price(&sent, wire, 0) == 23);
  assert(decode_current_price(&got, wire, 0) == 23);
  equal_current_price(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_current_price(&got, wire, 0) == 23);
  assert(encode_current_price(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Day On Day Comparison: 25 bytes ----------------------------------- */

/* Index Day-on-day comparison */
typedef struct {
  uint8_t net_change_rate[8];  /* bytes 0 to 7 */
  uint8_t sign;                /* byte 8 */
  uint8_t unit_flag;           /* byte 9 */
  uint8_t net_change[14];      /* bytes 10 to 23 */
  uint8_t second_sign;         /* byte 24 */
} IndexDayOnDayComparison;

/* any Index Day On Day Comparison at all: every byte one the checker chooses */
static void any_index_day_on_day_comparison(IndexDayOnDayComparison *record) {
  for (size_t i = 0; i < 8; i++) { record->net_change_rate[i] = arbitrary(); }
  record->sign = arbitrary();
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->net_change[i] = arbitrary(); }
  record->second_sign = arbitrary();
}

/* Index Day On Day Comparison to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_index_day_on_day_comparison(const IndexDayOnDayComparison *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->net_change_rate[i]; }
  wire[at++] = record->sign;
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->net_change[i]; }
  wire[at++] = record->second_sign;

  return at;
}

/* Index Day On Day Comparison off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_index_day_on_day_comparison(IndexDayOnDayComparison *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->net_change_rate[i] = wire[at++]; }
  record->sign = wire[at++];
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->net_change[i] = wire[at++]; }
  record->second_sign = wire[at++];

  return at;
}

/* what was read of Index Day On Day Comparison is what was written, byte for byte */
static void equal_index_day_on_day_comparison(const IndexDayOnDayComparison *read, const IndexDayOnDayComparison *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->net_change_rate[i] == written->net_change_rate[i]); }
  assert(read->sign == written->sign);
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->net_change[i] == written->net_change[i]); }
  assert(read->second_sign == written->second_sign);
}

/* Index Day On Day Comparison: written and read back, then read and written back */
static void check_index_day_on_day_comparison(void) {
  IndexDayOnDayComparison sent;
  IndexDayOnDayComparison got;
  uint8_t wire[25];
  uint8_t again[25];

  any_index_day_on_day_comparison(&sent);
  assert(encode_index_day_on_day_comparison(&sent, wire, 0) == 25);
  assert(decode_index_day_on_day_comparison(&got, wire, 0) == 25);
  equal_index_day_on_day_comparison(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_index_day_on_day_comparison(&got, wire, 0) == 25);
  assert(encode_index_day_on_day_comparison(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Open High Low And Closing Prices Message: 123 bytes --------------- */

/* In this tag, index information will be set. This data is appeared as one of index data. */
typedef struct {
  uint8_t reserved_2[2];                                /* bytes 0 to 1 */
  uint8_t index_type[4];                                /* bytes 2 to 5 */
  Open open;                                            /* bytes 6 to 28 */
  Highest highest;                                      /* bytes 29 to 51 */
  Lowest lowest;                                        /* bytes 52 to 74 */
  CurrentPrice current_price;                           /* bytes 75 to 97 */
  IndexDayOnDayComparison index_day_on_day_comparison;  /* bytes 98 to 122 */
} IndexOpenHighLowAndClosingPricesMessage;

/* any Index Open High Low And Closing Prices Message at all: every byte one the checker chooses */
static void any_index_open_high_low_and_closing_prices_message(IndexOpenHighLowAndClosingPricesMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->index_type[i] = arbitrary(); }
  any_open(&record->open);
  any_highest(&record->highest);
  any_lowest(&record->lowest);
  any_current_price(&record->current_price);
  any_index_day_on_day_comparison(&record->index_day_on_day_comparison);
}

/* Index Open High Low And Closing Prices Message to the wire: 123 bytes from at, returning where the next byte goes */
static size_t encode_index_open_high_low_and_closing_prices_message(const IndexOpenHighLowAndClosingPricesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_type[i]; }
  at = encode_open(&record->open, wire, at);
  at = encode_highest(&record->highest, wire, at);
  at = encode_lowest(&record->lowest, wire, at);
  at = encode_current_price(&record->current_price, wire, at);
  at = encode_index_day_on_day_comparison(&record->index_day_on_day_comparison, wire, at);

  return at;
}

/* Index Open High Low And Closing Prices Message off the wire: 123 bytes from at, returning where the next byte lies */
static size_t decode_index_open_high_low_and_closing_prices_message(IndexOpenHighLowAndClosingPricesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->index_type[i] = wire[at++]; }
  at = decode_open(&record->open, wire, at);
  at = decode_highest(&record->highest, wire, at);
  at = decode_lowest(&record->lowest, wire, at);
  at = decode_current_price(&record->current_price, wire, at);
  at = decode_index_day_on_day_comparison(&record->index_day_on_day_comparison, wire, at);

  return at;
}

/* what was read of Index Open High Low And Closing Prices Message is what was written, byte for byte */
static void equal_index_open_high_low_and_closing_prices_message(const IndexOpenHighLowAndClosingPricesMessage *read, const IndexOpenHighLowAndClosingPricesMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->index_type[i] == written->index_type[i]); }
  equal_open(&read->open, &written->open);
  equal_highest(&read->highest, &written->highest);
  equal_lowest(&read->lowest, &written->lowest);
  equal_current_price(&read->current_price, &written->current_price);
  equal_index_day_on_day_comparison(&read->index_day_on_day_comparison, &written->index_day_on_day_comparison);
}

/* Index Open High Low And Closing Prices Message: written and read back, then read and written back */
static void check_index_open_high_low_and_closing_prices_message(void) {
  IndexOpenHighLowAndClosingPricesMessage sent;
  IndexOpenHighLowAndClosingPricesMessage got;
  uint8_t wire[123];
  uint8_t again[123];

  any_index_open_high_low_and_closing_prices_message(&sent);
  assert(encode_index_open_high_low_and_closing_prices_message(&sent, wire, 0) == 123);
  assert(decode_index_open_high_low_and_closing_prices_message(&got, wire, 0) == 123);
  equal_index_open_high_low_and_closing_prices_message(&got, &sent);

  for (size_t i = 0; i < 123; i++) { wire[i] = arbitrary(); }
  assert(decode_index_open_high_low_and_closing_prices_message(&got, wire, 0) == 123);
  assert(encode_index_open_high_low_and_closing_prices_message(&got, again, 0) == 123);
  for (size_t i = 0; i < 123; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index: 22 bytes --------------------------------------------------------- */

/* Index */
typedef struct {
  uint8_t unit_flag;           /* byte 0 */
  uint8_t index_value[14];     /* bytes 1 to 14 */
  uint8_t sign;                /* byte 15 */
  uint8_t time_c_6_hhmmss[6];  /* bytes 16 to 21 */
} Index;

/* any Index at all: every byte one the checker chooses */
static void any_index(Index *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->index_value[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmmss[i] = arbitrary(); }
}

/* Index to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_index(const Index *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->index_value[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6_hhmmss[i]; }

  return at;
}

/* Index off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_index(Index *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->index_value[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmmss[i] = wire[at++]; }

  return at;
}

/* what was read of Index is what was written, byte for byte */
static void equal_index(const Index *read, const Index *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->index_value[i] == written->index_value[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6_hhmmss[i] == written->time_c_6_hhmmss[i]); }
}

/* Index: written and read back, then read and written back */
static void check_index(void) {
  Index sent;
  Index got;
  uint8_t wire[22];
  uint8_t again[22];

  any_index(&sent);
  assert(encode_index(&sent, wire, 0) == 22);
  assert(decode_index(&got, wire, 0) == 22);
  equal_index(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_index(&got, wire, 0) == 22);
  assert(encode_index(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Special Quotation Message: 29 bytes ------------------------------------- */

/* In this tag, special quotation (S.Q.) information will be set. This data appears as part of index data. */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
  uint8_t sq_type[4];     /* bytes 2 to 5 */
  Index index;            /* bytes 6 to 27 */
  uint8_t reserved_1;     /* byte 28 */
} SpecialQuotationMessage;

/* any Special Quotation Message at all: every byte one the checker chooses */
static void any_special_quotation_message(SpecialQuotationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sq_type[i] = arbitrary(); }
  any_index(&record->index);
  record->reserved_1 = arbitrary();
}

/* Special Quotation Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_special_quotation_message(const SpecialQuotationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sq_type[i]; }
  at = encode_index(&record->index, wire, at);
  wire[at++] = record->reserved_1;

  return at;
}

/* Special Quotation Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_special_quotation_message(SpecialQuotationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sq_type[i] = wire[at++]; }
  at = decode_index(&record->index, wire, at);
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Special Quotation Message is what was written, byte for byte */
static void equal_special_quotation_message(const SpecialQuotationMessage *read, const SpecialQuotationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sq_type[i] == written->sq_type[i]); }
  equal_index(&read->index, &written->index);
  assert(read->reserved_1 == written->reserved_1);
}

/* Special Quotation Message: written and read back, then read and written back */
static void check_special_quotation_message(void) {
  SpecialQuotationMessage sent;
  SpecialQuotationMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_special_quotation_message(&sent);
  assert(encode_special_quotation_message(&sent, wire, 0) == 29);
  assert(decode_special_quotation_message(&got, wire, 0) == 29);
  equal_special_quotation_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_special_quotation_message(&got, wire, 0) == 29);
  assert(encode_special_quotation_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Control Message: 10 bytes ----------------------------------------------- */

/* In this tag, the test mode flag and the start/end flag that are used in a control message will be set. This tag will be edited into a control message (communication control and health check control) for output. */
typedef struct {
  uint8_t reserved_2[2];     /* bytes 0 to 1 */
  uint8_t test_mode_flag;    /* byte 2 */
  uint8_t startend_flag;     /* byte 3 */
  uint8_t time_c_6_hhmm[6];  /* bytes 4 to 9 */
} ControlMessage;

/* any Control Message at all: every byte one the checker chooses */
static void any_control_message(ControlMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->test_mode_flag = arbitrary();
  record->startend_flag = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmm[i] = arbitrary(); }
}

/* Control Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_control_message(const ControlMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->test_mode_flag;
  wire[at++] = record->startend_flag;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6_hhmm[i]; }

  return at;
}

/* Control Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_control_message(ControlMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->test_mode_flag = wire[at++];
  record->startend_flag = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time_c_6_hhmm[i] = wire[at++]; }

  return at;
}

/* what was read of Control Message is what was written, byte for byte */
static void equal_control_message(const ControlMessage *read, const ControlMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->test_mode_flag == written->test_mode_flag);
  assert(read->startend_flag == written->startend_flag);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6_hhmm[i] == written->time_c_6_hhmm[i]); }
}

/* Control Message: written and read back, then read and written back */
static void check_control_message(void) {
  ControlMessage sent;
  ControlMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_control_message(&sent);
  assert(encode_control_message(&sent, wire, 0) == 10);
  assert(decode_control_message(&got, wire, 0) == 10);
  equal_control_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_control_message(&got, wire, 0) == 10);
  assert(encode_control_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_serial_no();
  check_issue_classification();
  check_stock_issue_code();
  check_c_b_issue_code();
  check_total_market_value();
  check_market_value_day_on_day_comparison();
  check_market_value_message();
  check_simple_yield();
  check_yield_day_on_day_comparison();
  check_simple_yield_message();
  check_weighted_yield();
  check_weighted_yield_message();
  check_simple_stock_price_average();
  check_stock_price_average_day_on_day_comparison();
  check_simple_stock_price_average_message();
  check_weighted_stock_price_average();
  check_weighted_stock_price_average_message();
  check_simple_stock_price_average_by_industry_message();
  check_overall_simple_average();
  check_overall_divergence_average();
  check_overall_parity_average();
  check_overall_direct_yield_average();
  check_overall();
  check_simple_average();
  check_divergence_average();
  check_parity_average();
  check_direct_yield_average();
  check_parity100_or_higher();
  check_parity_less_than100();
  check_japanese_yen_cb_indicator_message();
  check_number_of_active_issues();
  check_number_of_gainers();
  check_number_of_decliners();
  check_number_of_issues_with_no_change();
  check_number_of_issues_with_no_comparison();
  check_number_of_inactive_issues();
  check_number_of_gainers_decliners_message();
  check_estimated_total_trading_volume();
  check_estimated_total_trading_volume_message();
  check_estimated_total_turnover();
  check_estimated_total_turnover_message();
  check_vwap_by_market();
  check_vwap_by_market_message();
  check_trading_volume();
  check_turnover();
  check_number_of_transactions();
  check_to_s_t_ne_t_statistics_message();
  check_open();
  check_highest();
  check_lowest();
  check_current_price();
  check_index_day_on_day_comparison();
  check_index_open_high_low_and_closing_prices_message();
  check_index();
  check_special_quotation_message();
  check_control_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
