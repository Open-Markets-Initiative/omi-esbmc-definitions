// jpx/tseequities/issuebasicinformation/TseEquities_IssueBasicInformation_v19_5.c
/*
 * Japan Exchange Group IssueBasicInformation
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

/* ---- Index Constituent Issue: 20 bytes --------------------------------------- */

/* Index constituent issue */
typedef struct {
  uint8_t arbitrary_1;            /* byte 0 */
  uint8_t arbitrary_2;            /* byte 1 */
  uint8_t arbitrary_3;            /* byte 2 */
  uint8_t arbitrary_4;            /* byte 3 */
  uint8_t arbitrary_5;            /* byte 4 */
  uint8_t arbitrary_6;            /* byte 5 */
  uint8_t arbitrary_7;            /* byte 6 */
  uint8_t arbitrary_8_to_10[3];   /* bytes 7 to 9 */
  uint8_t arbitrary_11;           /* byte 10 */
  uint8_t arbitrary_12_to_15[4];  /* bytes 11 to 14 */
  uint8_t arbitrary_16;           /* byte 15 */
  uint8_t arbitrary_17_to_19[3];  /* bytes 16 to 18 */
  uint8_t arbitrary_20;           /* byte 19 */
} IndexConstituentIssue;

/* any Index Constituent Issue at all: every byte one the checker chooses */
static void any_index_constituent_issue(IndexConstituentIssue *record) {
  record->arbitrary_1 = arbitrary();
  record->arbitrary_2 = arbitrary();
  record->arbitrary_3 = arbitrary();
  record->arbitrary_4 = arbitrary();
  record->arbitrary_5 = arbitrary();
  record->arbitrary_6 = arbitrary();
  record->arbitrary_7 = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->arbitrary_8_to_10[i] = arbitrary(); }
  record->arbitrary_11 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->arbitrary_12_to_15[i] = arbitrary(); }
  record->arbitrary_16 = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->arbitrary_17_to_19[i] = arbitrary(); }
  record->arbitrary_20 = arbitrary();
}

/* Index Constituent Issue to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_index_constituent_issue(const IndexConstituentIssue *record, uint8_t *wire, size_t at) {
  wire[at++] = record->arbitrary_1;
  wire[at++] = record->arbitrary_2;
  wire[at++] = record->arbitrary_3;
  wire[at++] = record->arbitrary_4;
  wire[at++] = record->arbitrary_5;
  wire[at++] = record->arbitrary_6;
  wire[at++] = record->arbitrary_7;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->arbitrary_8_to_10[i]; }
  wire[at++] = record->arbitrary_11;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->arbitrary_12_to_15[i]; }
  wire[at++] = record->arbitrary_16;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->arbitrary_17_to_19[i]; }
  wire[at++] = record->arbitrary_20;

  return at;
}

/* Index Constituent Issue off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_index_constituent_issue(IndexConstituentIssue *record, const uint8_t *wire, size_t at) {
  record->arbitrary_1 = wire[at++];
  record->arbitrary_2 = wire[at++];
  record->arbitrary_3 = wire[at++];
  record->arbitrary_4 = wire[at++];
  record->arbitrary_5 = wire[at++];
  record->arbitrary_6 = wire[at++];
  record->arbitrary_7 = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->arbitrary_8_to_10[i] = wire[at++]; }
  record->arbitrary_11 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->arbitrary_12_to_15[i] = wire[at++]; }
  record->arbitrary_16 = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->arbitrary_17_to_19[i] = wire[at++]; }
  record->arbitrary_20 = wire[at++];

  return at;
}

/* what was read of Index Constituent Issue is what was written, byte for byte */
static void equal_index_constituent_issue(const IndexConstituentIssue *read, const IndexConstituentIssue *written) {
  assert(read->arbitrary_1 == written->arbitrary_1);
  assert(read->arbitrary_2 == written->arbitrary_2);
  assert(read->arbitrary_3 == written->arbitrary_3);
  assert(read->arbitrary_4 == written->arbitrary_4);
  assert(read->arbitrary_5 == written->arbitrary_5);
  assert(read->arbitrary_6 == written->arbitrary_6);
  assert(read->arbitrary_7 == written->arbitrary_7);
  for (size_t i = 0; i < 3; i++) { assert(read->arbitrary_8_to_10[i] == written->arbitrary_8_to_10[i]); }
  assert(read->arbitrary_11 == written->arbitrary_11);
  for (size_t i = 0; i < 4; i++) { assert(read->arbitrary_12_to_15[i] == written->arbitrary_12_to_15[i]); }
  assert(read->arbitrary_16 == written->arbitrary_16);
  for (size_t i = 0; i < 3; i++) { assert(read->arbitrary_17_to_19[i] == written->arbitrary_17_to_19[i]); }
  assert(read->arbitrary_20 == written->arbitrary_20);
}

/* Index Constituent Issue: written and read back, then read and written back */
static void check_index_constituent_issue(void) {
  IndexConstituentIssue sent;
  IndexConstituentIssue got;
  uint8_t wire[20];
  uint8_t again[20];

  any_index_constituent_issue(&sent);
  assert(encode_index_constituent_issue(&sent, wire, 0) == 20);
  assert(decode_index_constituent_issue(&got, wire, 0) == 20);
  equal_index_constituent_issue(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_index_constituent_issue(&got, wire, 0) == 20);
  assert(encode_index_constituent_issue(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Orders Prohibition: 4 bytes ----------------------------------------- */

/* New Orders Prohibition */
typedef struct {
  uint8_t market_limit_orders;    /* byte 0 */
  uint8_t side;                   /* byte 1 */
  uint8_t proprietary_brokerage;  /* byte 2 */
  uint8_t reserved_1;             /* byte 3 */
} NewOrdersProhibition;

/* any New Orders Prohibition at all: every byte one the checker chooses */
static void any_new_orders_prohibition(NewOrdersProhibition *record) {
  record->market_limit_orders = arbitrary();
  record->side = arbitrary();
  record->proprietary_brokerage = arbitrary();
  record->reserved_1 = arbitrary();
}

/* New Orders Prohibition to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_new_orders_prohibition(const NewOrdersProhibition *record, uint8_t *wire, size_t at) {
  wire[at++] = record->market_limit_orders;
  wire[at++] = record->side;
  wire[at++] = record->proprietary_brokerage;
  wire[at++] = record->reserved_1;

  return at;
}

/* New Orders Prohibition off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_new_orders_prohibition(NewOrdersProhibition *record, const uint8_t *wire, size_t at) {
  record->market_limit_orders = wire[at++];
  record->side = wire[at++];
  record->proprietary_brokerage = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of New Orders Prohibition is what was written, byte for byte */
static void equal_new_orders_prohibition(const NewOrdersProhibition *read, const NewOrdersProhibition *written) {
  assert(read->market_limit_orders == written->market_limit_orders);
  assert(read->side == written->side);
  assert(read->proprietary_brokerage == written->proprietary_brokerage);
  assert(read->reserved_1 == written->reserved_1);
}

/* New Orders Prohibition: written and read back, then read and written back */
static void check_new_orders_prohibition(void) {
  NewOrdersProhibition sent;
  NewOrdersProhibition got;
  uint8_t wire[4];
  uint8_t again[4];

  any_new_orders_prohibition(&sent);
  assert(encode_new_orders_prohibition(&sent, wire, 0) == 4);
  assert(decode_new_orders_prohibition(&got, wire, 0) == 4);
  equal_new_orders_prohibition(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_new_orders_prohibition(&got, wire, 0) == 4);
  assert(encode_new_orders_prohibition(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Margin Transactions Prohibition: 3 bytes -------------------------------- */

/* Margin Transactions Prohibition */
typedef struct {
  uint8_t side;                   /* byte 0 */
  uint8_t proprietary_brokerage;  /* byte 1 */
  uint8_t reserved_1;             /* byte 2 */
} MarginTransactionsProhibition;

/* any Margin Transactions Prohibition at all: every byte one the checker chooses */
static void any_margin_transactions_prohibition(MarginTransactionsProhibition *record) {
  record->side = arbitrary();
  record->proprietary_brokerage = arbitrary();
  record->reserved_1 = arbitrary();
}

/* Margin Transactions Prohibition to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_margin_transactions_prohibition(const MarginTransactionsProhibition *record, uint8_t *wire, size_t at) {
  wire[at++] = record->side;
  wire[at++] = record->proprietary_brokerage;
  wire[at++] = record->reserved_1;

  return at;
}

/* Margin Transactions Prohibition off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_margin_transactions_prohibition(MarginTransactionsProhibition *record, const uint8_t *wire, size_t at) {
  record->side = wire[at++];
  record->proprietary_brokerage = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Margin Transactions Prohibition is what was written, byte for byte */
static void equal_margin_transactions_prohibition(const MarginTransactionsProhibition *read, const MarginTransactionsProhibition *written) {
  assert(read->side == written->side);
  assert(read->proprietary_brokerage == written->proprietary_brokerage);
  assert(read->reserved_1 == written->reserved_1);
}

/* Margin Transactions Prohibition: written and read back, then read and written back */
static void check_margin_transactions_prohibition(void) {
  MarginTransactionsProhibition sent;
  MarginTransactionsProhibition got;
  uint8_t wire[3];
  uint8_t again[3];

  any_margin_transactions_prohibition(&sent);
  assert(encode_margin_transactions_prohibition(&sent, wire, 0) == 3);
  assert(decode_margin_transactions_prohibition(&got, wire, 0) == 3);
  equal_margin_transactions_prohibition(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_margin_transactions_prohibition(&got, wire, 0) == 3);
  assert(encode_margin_transactions_prohibition(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Selling Prohibition: 2 bytes -------------------------------------- */

/* Short Selling Prohibition */
typedef struct {
  uint8_t proprietary_brokerage;  /* byte 0 */
  uint8_t reserved_1;             /* byte 1 */
} ShortSellingProhibition;

/* any Short Selling Prohibition at all: every byte one the checker chooses */
static void any_short_selling_prohibition(ShortSellingProhibition *record) {
  record->proprietary_brokerage = arbitrary();
  record->reserved_1 = arbitrary();
}

/* Short Selling Prohibition to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_short_selling_prohibition(const ShortSellingProhibition *record, uint8_t *wire, size_t at) {
  wire[at++] = record->proprietary_brokerage;
  wire[at++] = record->reserved_1;

  return at;
}

/* Short Selling Prohibition off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_short_selling_prohibition(ShortSellingProhibition *record, const uint8_t *wire, size_t at) {
  record->proprietary_brokerage = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Short Selling Prohibition is what was written, byte for byte */
static void equal_short_selling_prohibition(const ShortSellingProhibition *read, const ShortSellingProhibition *written) {
  assert(read->proprietary_brokerage == written->proprietary_brokerage);
  assert(read->reserved_1 == written->reserved_1);
}

/* Short Selling Prohibition: written and read back, then read and written back */
static void check_short_selling_prohibition(void) {
  ShortSellingProhibition sent;
  ShortSellingProhibition got;
  uint8_t wire[2];
  uint8_t again[2];

  any_short_selling_prohibition(&sent);
  assert(encode_short_selling_prohibition(&sent, wire, 0) == 2);
  assert(decode_short_selling_prohibition(&got, wire, 0) == 2);
  equal_short_selling_prohibition(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_short_selling_prohibition(&got, wire, 0) == 2);
  assert(encode_short_selling_prohibition(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Prohibition Status At The Regular Distribution: 10 bytes ---------- */

/* Order Prohibition Status (at the regular distribution) */
typedef struct {
  NewOrdersProhibition new_orders_prohibition;                    /* bytes 0 to 3 */
  MarginTransactionsProhibition margin_transactions_prohibition;  /* bytes 4 to 6 */
  ShortSellingProhibition short_selling_prohibition;              /* bytes 7 to 8 */
  uint8_t all_orders_prohibition;                                 /* byte 9 */
} OrderProhibitionStatusAtTheRegularDistribution;

/* any Order Prohibition Status At The Regular Distribution at all: every byte one the checker chooses */
static void any_order_prohibition_status_at_the_regular_distribution(OrderProhibitionStatusAtTheRegularDistribution *record) {
  any_new_orders_prohibition(&record->new_orders_prohibition);
  any_margin_transactions_prohibition(&record->margin_transactions_prohibition);
  any_short_selling_prohibition(&record->short_selling_prohibition);
  record->all_orders_prohibition = arbitrary();
}

/* Order Prohibition Status At The Regular Distribution to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_order_prohibition_status_at_the_regular_distribution(const OrderProhibitionStatusAtTheRegularDistribution *record, uint8_t *wire, size_t at) {
  at = encode_new_orders_prohibition(&record->new_orders_prohibition, wire, at);
  at = encode_margin_transactions_prohibition(&record->margin_transactions_prohibition, wire, at);
  at = encode_short_selling_prohibition(&record->short_selling_prohibition, wire, at);
  wire[at++] = record->all_orders_prohibition;

  return at;
}

/* Order Prohibition Status At The Regular Distribution off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_order_prohibition_status_at_the_regular_distribution(OrderProhibitionStatusAtTheRegularDistribution *record, const uint8_t *wire, size_t at) {
  at = decode_new_orders_prohibition(&record->new_orders_prohibition, wire, at);
  at = decode_margin_transactions_prohibition(&record->margin_transactions_prohibition, wire, at);
  at = decode_short_selling_prohibition(&record->short_selling_prohibition, wire, at);
  record->all_orders_prohibition = wire[at++];

  return at;
}

/* what was read of Order Prohibition Status At The Regular Distribution is what was written, byte for byte */
static void equal_order_prohibition_status_at_the_regular_distribution(const OrderProhibitionStatusAtTheRegularDistribution *read, const OrderProhibitionStatusAtTheRegularDistribution *written) {
  equal_new_orders_prohibition(&read->new_orders_prohibition, &written->new_orders_prohibition);
  equal_margin_transactions_prohibition(&read->margin_transactions_prohibition, &written->margin_transactions_prohibition);
  equal_short_selling_prohibition(&read->short_selling_prohibition, &written->short_selling_prohibition);
  assert(read->all_orders_prohibition == written->all_orders_prohibition);
}

/* Order Prohibition Status At The Regular Distribution: written and read back, then read and written back */
static void check_order_prohibition_status_at_the_regular_distribution(void) {
  OrderProhibitionStatusAtTheRegularDistribution sent;
  OrderProhibitionStatusAtTheRegularDistribution got;
  uint8_t wire[10];
  uint8_t again[10];

  any_order_prohibition_status_at_the_regular_distribution(&sent);
  assert(encode_order_prohibition_status_at_the_regular_distribution(&sent, wire, 0) == 10);
  assert(decode_order_prohibition_status_at_the_regular_distribution(&got, wire, 0) == 10);
  equal_order_prohibition_status_at_the_regular_distribution(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_order_prohibition_status_at_the_regular_distribution(&got, wire, 0) == 10);
  assert(encode_order_prohibition_status_at_the_regular_distribution(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Issue Information Message: 123 bytes ------------------------------------ */

/* In this tag, the new security code, etc., of each issue will be set. This tag appears as part of an issue basic message. */
typedef struct {
  uint8_t reserved_2[2];                                                                                /* bytes 0 to 1 */
  uint8_t serial_no[6];                                                                                 /* bytes 2 to 7 */
  uint8_t applicable_business_day[8];                                                                   /* bytes 8 to 15 */
  uint8_t reserved_1;                                                                                   /* byte 16 */
  uint8_t issue_name[20];                                                                               /* bytes 17 to 36 */
  uint8_t security_type_etc_identification_code[2];                                                     /* bytes 37 to 38 */
  uint8_t isin_flag;                                                                                    /* byte 39 */
  uint8_t new_security_code[12];                                                                        /* bytes 40 to 51 */
  uint8_t industry_code[4];                                                                             /* bytes 52 to 55 */
  uint8_t new_listing_flag;                                                                             /* byte 56 */
  uint8_t when_issued_transaction_flag;                                                                 /* byte 57 */
  uint8_t short_selling_price_restriction_applied_flag_at_the_regular_distribution;                     /* byte 58 */
  uint8_t loan_margin_flag;                                                                             /* byte 59 */
  uint8_t ex_dividend_ex_right_flag[2];                                                                 /* bytes 60 to 61 */
  uint8_t securities_to_be_delisted_under_supervision_classification;                                   /* byte 62 */
  uint8_t reserved_5[5];                                                                                /* bytes 63 to 67 */
  uint8_t unit_of_trading[14];                                                                          /* bytes 68 to 81 */
  IndexConstituentIssue index_constituent_issue;                                                        /* bytes 82 to 101 */
  OrderProhibitionStatusAtTheRegularDistribution order_prohibition_status_at_the_regular_distribution;  /* bytes 102 to 111 */
  uint8_t reserved_11[11];                                                                              /* bytes 112 to 122 */
} IssueInformationMessage;

/* any Issue Information Message at all: every byte one the checker chooses */
static void any_issue_information_message(IssueInformationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->serial_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->applicable_business_day[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->issue_name[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_type_etc_identification_code[i] = arbitrary(); }
  record->isin_flag = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->new_security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->industry_code[i] = arbitrary(); }
  record->new_listing_flag = arbitrary();
  record->when_issued_transaction_flag = arbitrary();
  record->short_selling_price_restriction_applied_flag_at_the_regular_distribution = arbitrary();
  record->loan_margin_flag = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ex_dividend_ex_right_flag[i] = arbitrary(); }
  record->securities_to_be_delisted_under_supervision_classification = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->unit_of_trading[i] = arbitrary(); }
  any_index_constituent_issue(&record->index_constituent_issue);
  any_order_prohibition_status_at_the_regular_distribution(&record->order_prohibition_status_at_the_regular_distribution);
  for (size_t i = 0; i < 11; i++) { record->reserved_11[i] = arbitrary(); }
}

/* Issue Information Message to the wire: 123 bytes from at, returning where the next byte goes */
static size_t encode_issue_information_message(const IssueInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->serial_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->applicable_business_day[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->issue_name[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_type_etc_identification_code[i]; }
  wire[at++] = record->isin_flag;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->new_security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->industry_code[i]; }
  wire[at++] = record->new_listing_flag;
  wire[at++] = record->when_issued_transaction_flag;
  wire[at++] = record->short_selling_price_restriction_applied_flag_at_the_regular_distribution;
  wire[at++] = record->loan_margin_flag;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ex_dividend_ex_right_flag[i]; }
  wire[at++] = record->securities_to_be_delisted_under_supervision_classification;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->reserved_5[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->unit_of_trading[i]; }
  at = encode_index_constituent_issue(&record->index_constituent_issue, wire, at);
  at = encode_order_prohibition_status_at_the_regular_distribution(&record->order_prohibition_status_at_the_regular_distribution, wire, at);
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->reserved_11[i]; }

  return at;
}

/* Issue Information Message off the wire: 123 bytes from at, returning where the next byte lies */
static size_t decode_issue_information_message(IssueInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->serial_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->applicable_business_day[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->issue_name[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_type_etc_identification_code[i] = wire[at++]; }
  record->isin_flag = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->new_security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->industry_code[i] = wire[at++]; }
  record->new_listing_flag = wire[at++];
  record->when_issued_transaction_flag = wire[at++];
  record->short_selling_price_restriction_applied_flag_at_the_regular_distribution = wire[at++];
  record->loan_margin_flag = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ex_dividend_ex_right_flag[i] = wire[at++]; }
  record->securities_to_be_delisted_under_supervision_classification = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->unit_of_trading[i] = wire[at++]; }
  at = decode_index_constituent_issue(&record->index_constituent_issue, wire, at);
  at = decode_order_prohibition_status_at_the_regular_distribution(&record->order_prohibition_status_at_the_regular_distribution, wire, at);
  for (size_t i = 0; i < 11; i++) { record->reserved_11[i] = wire[at++]; }

  return at;
}

/* what was read of Issue Information Message is what was written, byte for byte */
static void equal_issue_information_message(const IssueInformationMessage *read, const IssueInformationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->serial_no[i] == written->serial_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->applicable_business_day[i] == written->applicable_business_day[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 20; i++) { assert(read->issue_name[i] == written->issue_name[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_type_etc_identification_code[i] == written->security_type_etc_identification_code[i]); }
  assert(read->isin_flag == written->isin_flag);
  for (size_t i = 0; i < 12; i++) { assert(read->new_security_code[i] == written->new_security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->industry_code[i] == written->industry_code[i]); }
  assert(read->new_listing_flag == written->new_listing_flag);
  assert(read->when_issued_transaction_flag == written->when_issued_transaction_flag);
  assert(read->short_selling_price_restriction_applied_flag_at_the_regular_distribution == written->short_selling_price_restriction_applied_flag_at_the_regular_distribution);
  assert(read->loan_margin_flag == written->loan_margin_flag);
  for (size_t i = 0; i < 2; i++) { assert(read->ex_dividend_ex_right_flag[i] == written->ex_dividend_ex_right_flag[i]); }
  assert(read->securities_to_be_delisted_under_supervision_classification == written->securities_to_be_delisted_under_supervision_classification);
  for (size_t i = 0; i < 5; i++) { assert(read->reserved_5[i] == written->reserved_5[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->unit_of_trading[i] == written->unit_of_trading[i]); }
  equal_index_constituent_issue(&read->index_constituent_issue, &written->index_constituent_issue);
  equal_order_prohibition_status_at_the_regular_distribution(&read->order_prohibition_status_at_the_regular_distribution, &written->order_prohibition_status_at_the_regular_distribution);
  for (size_t i = 0; i < 11; i++) { assert(read->reserved_11[i] == written->reserved_11[i]); }
}

/* Issue Information Message: written and read back, then read and written back */
static void check_issue_information_message(void) {
  IssueInformationMessage sent;
  IssueInformationMessage got;
  uint8_t wire[123];
  uint8_t again[123];

  any_issue_information_message(&sent);
  assert(encode_issue_information_message(&sent, wire, 0) == 123);
  assert(decode_issue_information_message(&got, wire, 0) == 123);
  equal_issue_information_message(&got, &sent);

  for (size_t i = 0; i < 123; i++) { wire[i] = arbitrary(); }
  assert(decode_issue_information_message(&got, wire, 0) == 123);
  assert(encode_issue_information_message(&got, again, 0) == 123);
  for (size_t i = 0; i < 123; i++) { assert(again[i] == wire[i]); }
}

/* ---- Base Price: 16 bytes ---------------------------------------------------- */

/* Base Price */
typedef struct {
  uint8_t unit_flag;  /* byte 0 */
  uint8_t price[14];  /* bytes 1 to 14 */
  uint8_t sign;       /* byte 15 */
} BasePrice;

/* any Base Price at all: every byte one the checker chooses */
static void any_base_price(BasePrice *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->price[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Base Price to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_base_price(const BasePrice *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Base Price off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_base_price(BasePrice *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->price[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Base Price is what was written, byte for byte */
static void equal_base_price(const BasePrice *read, const BasePrice *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->sign == written->sign);
}

/* Base Price: written and read back, then read and written back */
static void check_base_price(void) {
  BasePrice sent;
  BasePrice got;
  uint8_t wire[16];
  uint8_t again[16];

  any_base_price(&sent);
  assert(encode_base_price(&sent, wire, 0) == 16);
  assert(decode_base_price(&got, wire, 0) == 16);
  equal_base_price(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_base_price(&got, wire, 0) == 16);
  assert(encode_base_price(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Limit Price Maximum: 16 bytes ------------------------------------------- */

/* Limit Price (Maximum) */
typedef struct {
  uint8_t unit_flag;  /* byte 0 */
  uint8_t price[14];  /* bytes 1 to 14 */
  uint8_t sign;       /* byte 15 */
} LimitPriceMaximum;

/* any Limit Price Maximum at all: every byte one the checker chooses */
static void any_limit_price_maximum(LimitPriceMaximum *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->price[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Limit Price Maximum to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_limit_price_maximum(const LimitPriceMaximum *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Limit Price Maximum off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_limit_price_maximum(LimitPriceMaximum *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->price[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Limit Price Maximum is what was written, byte for byte */
static void equal_limit_price_maximum(const LimitPriceMaximum *read, const LimitPriceMaximum *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->sign == written->sign);
}

/* Limit Price Maximum: written and read back, then read and written back */
static void check_limit_price_maximum(void) {
  LimitPriceMaximum sent;
  LimitPriceMaximum got;
  uint8_t wire[16];
  uint8_t again[16];

  any_limit_price_maximum(&sent);
  assert(encode_limit_price_maximum(&sent, wire, 0) == 16);
  assert(decode_limit_price_maximum(&got, wire, 0) == 16);
  equal_limit_price_maximum(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_limit_price_maximum(&got, wire, 0) == 16);
  assert(encode_limit_price_maximum(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Limit Price Minimum: 16 bytes ------------------------------------------- */

/* Limit Price (Minimum) */
typedef struct {
  uint8_t unit_flag;  /* byte 0 */
  uint8_t price[14];  /* bytes 1 to 14 */
  uint8_t sign;       /* byte 15 */
} LimitPriceMinimum;

/* any Limit Price Minimum at all: every byte one the checker chooses */
static void any_limit_price_minimum(LimitPriceMinimum *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->price[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Limit Price Minimum to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_limit_price_minimum(const LimitPriceMinimum *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Limit Price Minimum off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_limit_price_minimum(LimitPriceMinimum *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->price[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Limit Price Minimum is what was written, byte for byte */
static void equal_limit_price_minimum(const LimitPriceMinimum *read, const LimitPriceMinimum *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->sign == written->sign);
}

/* Limit Price Minimum: written and read back, then read and written back */
static void check_limit_price_minimum(void) {
  LimitPriceMinimum sent;
  LimitPriceMinimum got;
  uint8_t wire[16];
  uint8_t again[16];

  any_limit_price_minimum(&sent);
  assert(encode_limit_price_minimum(&sent, wire, 0) == 16);
  assert(decode_limit_price_minimum(&got, wire, 0) == 16);
  equal_limit_price_minimum(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_limit_price_minimum(&got, wire, 0) == 16);
  assert(encode_limit_price_minimum(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Base Price Information Message: 66 bytes -------------------------------- */

/* In this Tag, the below items for the next business day or the day are set. This tag appears as part of an issue basic message. */
typedef struct {
  uint8_t reserved_2[2];                               /* bytes 0 to 1 */
  uint8_t based_business_day[8];                       /* bytes 2 to 9 */
  BasePrice base_price;                                /* bytes 10 to 25 */
  LimitPriceMaximum limit_price_maximum;               /* bytes 26 to 41 */
  LimitPriceMinimum limit_price_minimum;               /* bytes 42 to 57 */
  uint8_t base_price_price_of_the_middle_of_the_book;  /* byte 58 */
  uint8_t number_of_tick_size_table[2];                /* bytes 59 to 60 */
  uint8_t reserved_1;                                  /* byte 61 */
  uint8_t reserved_4[4];                               /* bytes 62 to 65 */
} BasePriceInformationMessage;

/* any Base Price Information Message at all: every byte one the checker chooses */
static void any_base_price_information_message(BasePriceInformationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->based_business_day[i] = arbitrary(); }
  any_base_price(&record->base_price);
  any_limit_price_maximum(&record->limit_price_maximum);
  any_limit_price_minimum(&record->limit_price_minimum);
  record->base_price_price_of_the_middle_of_the_book = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->number_of_tick_size_table[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Base Price Information Message to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_base_price_information_message(const BasePriceInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->based_business_day[i]; }
  at = encode_base_price(&record->base_price, wire, at);
  at = encode_limit_price_maximum(&record->limit_price_maximum, wire, at);
  at = encode_limit_price_minimum(&record->limit_price_minimum, wire, at);
  wire[at++] = record->base_price_price_of_the_middle_of_the_book;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_tick_size_table[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Base Price Information Message off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_base_price_information_message(BasePriceInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->based_business_day[i] = wire[at++]; }
  at = decode_base_price(&record->base_price, wire, at);
  at = decode_limit_price_maximum(&record->limit_price_maximum, wire, at);
  at = decode_limit_price_minimum(&record->limit_price_minimum, wire, at);
  record->base_price_price_of_the_middle_of_the_book = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->number_of_tick_size_table[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Base Price Information Message is what was written, byte for byte */
static void equal_base_price_information_message(const BasePriceInformationMessage *read, const BasePriceInformationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->based_business_day[i] == written->based_business_day[i]); }
  equal_base_price(&read->base_price, &written->base_price);
  equal_limit_price_maximum(&read->limit_price_maximum, &written->limit_price_maximum);
  equal_limit_price_minimum(&read->limit_price_minimum, &written->limit_price_minimum);
  assert(read->base_price_price_of_the_middle_of_the_book == written->base_price_price_of_the_middle_of_the_book);
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_tick_size_table[i] == written->number_of_tick_size_table[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Base Price Information Message: written and read back, then read and written back */
static void check_base_price_information_message(void) {
  BasePriceInformationMessage sent;
  BasePriceInformationMessage got;
  uint8_t wire[66];
  uint8_t again[66];

  any_base_price_information_message(&sent);
  assert(encode_base_price_information_message(&sent, wire, 0) == 66);
  assert(decode_base_price_information_message(&got, wire, 0) == 66);
  equal_base_price_information_message(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_base_price_information_message(&got, wire, 0) == 66);
  assert(encode_base_price_information_message(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Multicast Group Number Information Message: 14 bytes -------------------- */

/* In this tag, Multicast Group Number with which the issue is output is set. This tag appears as part of an Issue Realtime Message. */
typedef struct {
  uint8_t reserved_2[2];                    /* bytes 0 to 1 */
  uint8_t applicable_business_day[8];       /* bytes 2 to 9 */
  uint8_t issue_multicast_group_number[3];  /* bytes 10 to 12 */
  uint8_t reserved_1;                       /* byte 13 */
} MulticastGroupNumberInformationMessage;

/* any Multicast Group Number Information Message at all: every byte one the checker chooses */
static void any_multicast_group_number_information_message(MulticastGroupNumberInformationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->applicable_business_day[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->issue_multicast_group_number[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Multicast Group Number Information Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_multicast_group_number_information_message(const MulticastGroupNumberInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->applicable_business_day[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->issue_multicast_group_number[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Multicast Group Number Information Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_multicast_group_number_information_message(MulticastGroupNumberInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->applicable_business_day[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->issue_multicast_group_number[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Multicast Group Number Information Message is what was written, byte for byte */
static void equal_multicast_group_number_information_message(const MulticastGroupNumberInformationMessage *read, const MulticastGroupNumberInformationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->applicable_business_day[i] == written->applicable_business_day[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->issue_multicast_group_number[i] == written->issue_multicast_group_number[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Multicast Group Number Information Message: written and read back, then read and written back */
static void check_multicast_group_number_information_message(void) {
  MulticastGroupNumberInformationMessage sent;
  MulticastGroupNumberInformationMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_multicast_group_number_information_message(&sent);
  assert(encode_multicast_group_number_information_message(&sent, wire, 0) == 14);
  assert(decode_multicast_group_number_information_message(&got, wire, 0) == 14);
  equal_multicast_group_number_information_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_multicast_group_number_information_message(&got, wire, 0) == 14);
  assert(encode_multicast_group_number_information_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Control Message: 10 bytes ----------------------------------------------- */

/* In this tag, the Test Mode Flag and the Start/End Flag that are used in a Control Message will be set. This tag appears as part of a Control Message (Communication Control, Health Check Control, Stock Base Price Information Control, CB Base Price Information Control, Issue Information Control and Multicast Group Number Information Control). */
typedef struct {
  uint8_t reserved_2[2];   /* bytes 0 to 1 */
  uint8_t test_mode_flag;  /* byte 2 */
  uint8_t start_end_flag;  /* byte 3 */
  uint8_t time[6];         /* bytes 4 to 9 */
} ControlMessage;

/* any Control Message at all: every byte one the checker chooses */
static void any_control_message(ControlMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->test_mode_flag = arbitrary();
  record->start_end_flag = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
}

/* Control Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_control_message(const ControlMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->test_mode_flag;
  wire[at++] = record->start_end_flag;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }

  return at;
}

/* Control Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_control_message(ControlMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->test_mode_flag = wire[at++];
  record->start_end_flag = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }

  return at;
}

/* what was read of Control Message is what was written, byte for byte */
static void equal_control_message(const ControlMessage *read, const ControlMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->test_mode_flag == written->test_mode_flag);
  assert(read->start_end_flag == written->start_end_flag);
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
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
  check_index_constituent_issue();
  check_new_orders_prohibition();
  check_margin_transactions_prohibition();
  check_short_selling_prohibition();
  check_order_prohibition_status_at_the_regular_distribution();
  check_issue_information_message();
  check_base_price();
  check_limit_price_maximum();
  check_limit_price_minimum();
  check_base_price_information_message();
  check_multicast_group_number_information_message();
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
