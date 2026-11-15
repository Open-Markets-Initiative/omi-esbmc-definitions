// jpx/tseequities/tostnet/TseEquities_ToSTNeT_v19_5.c
/*
 * Japan Exchange Group ToSTNeT
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

/* ---- Trading Halt: 8 bytes --------------------------------------------------- */

/* Trading Halt */
typedef struct {
  uint8_t state_flag[2];  /* bytes 0 to 1 */
  uint8_t time_c_6[6];    /* bytes 2 to 7 */
} TradingHalt;

/* any Trading Halt at all: every byte one the checker chooses */
static void any_trading_halt(TradingHalt *record) {
  for (size_t i = 0; i < 2; i++) { record->state_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = arbitrary(); }
}

/* Trading Halt to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_trading_halt(const TradingHalt *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->state_flag[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6[i]; }

  return at;
}

/* Trading Halt off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_trading_halt(TradingHalt *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->state_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Halt is what was written, byte for byte */
static void equal_trading_halt(const TradingHalt *read, const TradingHalt *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->state_flag[i] == written->state_flag[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6[i] == written->time_c_6[i]); }
}

/* Trading Halt: written and read back, then read and written back */
static void check_trading_halt(void) {
  TradingHalt sent;
  TradingHalt got;
  uint8_t wire[8];
  uint8_t again[8];

  any_trading_halt(&sent);
  assert(encode_trading_halt(&sent, wire, 0) == 8);
  assert(decode_trading_halt(&got, wire, 0) == 8);
  equal_trading_halt(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_halt(&got, wire, 0) == 8);
  assert(encode_trading_halt(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price: 30 bytes --------------------------------------------------------- */

/* Price */
typedef struct {
  uint8_t price_code[2];       /* bytes 0 to 1 */
  uint8_t lot_size_unit_flag;  /* byte 2 */
  uint8_t price_c_14[14];      /* bytes 3 to 16 */
  uint8_t sign;                /* byte 17 */
  uint8_t time_c_12[12];       /* bytes 18 to 29 */
} Price;

/* any Price at all: every byte one the checker chooses */
static void any_price(Price *record) {
  for (size_t i = 0; i < 2; i++) { record->price_code[i] = arbitrary(); }
  record->lot_size_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->price_c_14[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = arbitrary(); }
}

/* Price to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_price(const Price *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_code[i]; }
  wire[at++] = record->lot_size_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->price_c_14[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_c_12[i]; }

  return at;
}

/* Price off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_price(Price *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->price_code[i] = wire[at++]; }
  record->lot_size_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->price_c_14[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = wire[at++]; }

  return at;
}

/* what was read of Price is what was written, byte for byte */
static void equal_price(const Price *read, const Price *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->price_code[i] == written->price_code[i]); }
  assert(read->lot_size_unit_flag == written->lot_size_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->price_c_14[i] == written->price_c_14[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 12; i++) { assert(read->time_c_12[i] == written->time_c_12[i]); }
}

/* Price: written and read back, then read and written back */
static void check_price(void) {
  Price sent;
  Price got;
  uint8_t wire[30];
  uint8_t again[30];

  any_price(&sent);
  assert(encode_price(&sent, wire, 0) == 30);
  assert(decode_price(&got, wire, 0) == 30);
  equal_price(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_price(&got, wire, 0) == 30);
  assert(encode_price(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Volume: 15 bytes ------------------------------------------------ */

/* Trading Volume */
typedef struct {
  uint8_t trading_volume_turnover_unit_flag;  /* byte 0 */
  uint8_t trading_volume_c_14[14];            /* bytes 1 to 14 */
} TradingVolume;

/* any Trading Volume at all: every byte one the checker chooses */
static void any_trading_volume(TradingVolume *record) {
  record->trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->trading_volume_c_14[i] = arbitrary(); }
}

/* Trading Volume to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_trading_volume(const TradingVolume *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->trading_volume_c_14[i]; }

  return at;
}

/* Trading Volume off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_trading_volume(TradingVolume *record, const uint8_t *wire, size_t at) {
  record->trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->trading_volume_c_14[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Volume is what was written, byte for byte */
static void equal_trading_volume(const TradingVolume *read, const TradingVolume *written) {
  assert(read->trading_volume_turnover_unit_flag == written->trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->trading_volume_c_14[i] == written->trading_volume_c_14[i]); }
}

/* Trading Volume: written and read back, then read and written back */
static void check_trading_volume(void) {
  TradingVolume sent;
  TradingVolume got;
  uint8_t wire[15];
  uint8_t again[15];

  any_trading_volume(&sent);
  assert(encode_trading_volume(&sent, wire, 0) == 15);
  assert(decode_trading_volume(&got, wire, 0) == 15);
  equal_trading_volume(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_volume(&got, wire, 0) == 15);
  assert(encode_trading_volume(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Turnover: 15 bytes ------------------------------------------------------ */

/* Turnover */
typedef struct {
  uint8_t trading_volume_turnover_unit_flag;  /* byte 0 */
  uint8_t turnover_c_14[14];                  /* bytes 1 to 14 */
} Turnover;

/* any Turnover at all: every byte one the checker chooses */
static void any_turnover(Turnover *record) {
  record->trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->turnover_c_14[i] = arbitrary(); }
}

/* Turnover to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_turnover(const Turnover *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->turnover_c_14[i]; }

  return at;
}

/* Turnover off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_turnover(Turnover *record, const uint8_t *wire, size_t at) {
  record->trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->turnover_c_14[i] = wire[at++]; }

  return at;
}

/* what was read of Turnover is what was written, byte for byte */
static void equal_turnover(const Turnover *read, const Turnover *written) {
  assert(read->trading_volume_turnover_unit_flag == written->trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->turnover_c_14[i] == written->turnover_c_14[i]); }
}

/* Turnover: written and read back, then read and written back */
static void check_turnover(void) {
  Turnover sent;
  Turnover got;
  uint8_t wire[15];
  uint8_t again[15];

  any_turnover(&sent);
  assert(encode_turnover(&sent, wire, 0) == 15);
  assert(decode_turnover(&got, wire, 0) == 15);
  equal_turnover(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_turnover(&got, wire, 0) == 15);
  assert(encode_turnover(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- ToSTNeT By-Issue Information Message: 72 bytes -------------------------- */

/* In this tag, information concerning trade and trading halt for an issue (single-issue transaction, basket transaction, or closing price transaction) on the ToSTNeT is set. This data appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];                    /* bytes 0 to 1 */
  uint8_t market_identification_flag;       /* byte 2 */
  TradingHalt trading_halt;                 /* bytes 3 to 10 */
  uint8_t transaction_identification_flag;  /* byte 11 */
  Price price;                              /* bytes 12 to 41 */
  TradingVolume trading_volume;             /* bytes 42 to 56 */
  Turnover turnover;                        /* bytes 57 to 71 */
} ToSTNeTBy_IssueInformationMessage;

/* any ToSTNeT By-Issue Information Message at all: every byte one the checker chooses */
static void any_to_s_t_ne_t_by_issue_information_message(ToSTNeTBy_IssueInformationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->market_identification_flag = arbitrary();
  any_trading_halt(&record->trading_halt);
  record->transaction_identification_flag = arbitrary();
  any_price(&record->price);
  any_trading_volume(&record->trading_volume);
  any_turnover(&record->turnover);
}

/* ToSTNeT By-Issue Information Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_to_s_t_ne_t_by_issue_information_message(const ToSTNeTBy_IssueInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->market_identification_flag;
  at = encode_trading_halt(&record->trading_halt, wire, at);
  wire[at++] = record->transaction_identification_flag;
  at = encode_price(&record->price, wire, at);
  at = encode_trading_volume(&record->trading_volume, wire, at);
  at = encode_turnover(&record->turnover, wire, at);

  return at;
}

/* ToSTNeT By-Issue Information Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_to_s_t_ne_t_by_issue_information_message(ToSTNeTBy_IssueInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->market_identification_flag = wire[at++];
  at = decode_trading_halt(&record->trading_halt, wire, at);
  record->transaction_identification_flag = wire[at++];
  at = decode_price(&record->price, wire, at);
  at = decode_trading_volume(&record->trading_volume, wire, at);
  at = decode_turnover(&record->turnover, wire, at);

  return at;
}

/* what was read of ToSTNeT By-Issue Information Message is what was written, byte for byte */
static void equal_to_s_t_ne_t_by_issue_information_message(const ToSTNeTBy_IssueInformationMessage *read, const ToSTNeTBy_IssueInformationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->market_identification_flag == written->market_identification_flag);
  equal_trading_halt(&read->trading_halt, &written->trading_halt);
  assert(read->transaction_identification_flag == written->transaction_identification_flag);
  equal_price(&read->price, &written->price);
  equal_trading_volume(&read->trading_volume, &written->trading_volume);
  equal_turnover(&read->turnover, &written->turnover);
}

/* ToSTNeT By-Issue Information Message: written and read back, then read and written back */
static void check_to_s_t_ne_t_by_issue_information_message(void) {
  ToSTNeTBy_IssueInformationMessage sent;
  ToSTNeTBy_IssueInformationMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_to_s_t_ne_t_by_issue_information_message(&sent);
  assert(encode_to_s_t_ne_t_by_issue_information_message(&sent, wire, 0) == 72);
  assert(decode_to_s_t_ne_t_by_issue_information_message(&got, wire, 0) == 72);
  equal_to_s_t_ne_t_by_issue_information_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_to_s_t_ne_t_by_issue_information_message(&got, wire, 0) == 72);
  assert(encode_to_s_t_ne_t_by_issue_information_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- State: 8 bytes ---------------------------------------------------------- */

/* State */
typedef struct {
  uint8_t market_state_flag[2];  /* bytes 0 to 1 */
  uint8_t time_c_6[6];           /* bytes 2 to 7 */
} State;

/* any State at all: every byte one the checker chooses */
static void any_state(State *record) {
  for (size_t i = 0; i < 2; i++) { record->market_state_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = arbitrary(); }
}

/* State to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_state(const State *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_state_flag[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6[i]; }

  return at;
}

/* State off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_state(State *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->market_state_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = wire[at++]; }

  return at;
}

/* what was read of State is what was written, byte for byte */
static void equal_state(const State *read, const State *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->market_state_flag[i] == written->market_state_flag[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6[i] == written->time_c_6[i]); }
}

/* State: written and read back, then read and written back */
static void check_state(void) {
  State sent;
  State got;
  uint8_t wire[8];
  uint8_t again[8];

  any_state(&sent);
  assert(encode_state(&sent, wire, 0) == 8);
  assert(decode_state(&got, wire, 0) == 8);
  equal_state(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_state(&got, wire, 0) == 8);
  assert(encode_state(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- ToSTNeT Market Information Message: 11 bytes ---------------------------- */

/* In this tag, state information on the ToSTNeT will be set. This data appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];               /* bytes 0 to 1 */
  uint8_t market_identification_flag;  /* byte 2 */
  State state;                         /* bytes 3 to 10 */
} ToSTNeTMarketInformationMessage;

/* any ToSTNeT Market Information Message at all: every byte one the checker chooses */
static void any_to_s_t_ne_t_market_information_message(ToSTNeTMarketInformationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->market_identification_flag = arbitrary();
  any_state(&record->state);
}

/* ToSTNeT Market Information Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_to_s_t_ne_t_market_information_message(const ToSTNeTMarketInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->market_identification_flag;
  at = encode_state(&record->state, wire, at);

  return at;
}

/* ToSTNeT Market Information Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_to_s_t_ne_t_market_information_message(ToSTNeTMarketInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->market_identification_flag = wire[at++];
  at = decode_state(&record->state, wire, at);

  return at;
}

/* what was read of ToSTNeT Market Information Message is what was written, byte for byte */
static void equal_to_s_t_ne_t_market_information_message(const ToSTNeTMarketInformationMessage *read, const ToSTNeTMarketInformationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->market_identification_flag == written->market_identification_flag);
  equal_state(&read->state, &written->state);
}

/* ToSTNeT Market Information Message: written and read back, then read and written back */
static void check_to_s_t_ne_t_market_information_message(void) {
  ToSTNeTMarketInformationMessage sent;
  ToSTNeTMarketInformationMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_to_s_t_ne_t_market_information_message(&sent);
  assert(encode_to_s_t_ne_t_market_information_message(&sent, wire, 0) == 11);
  assert(decode_to_s_t_ne_t_market_information_message(&got, wire, 0) == 11);
  equal_to_s_t_ne_t_market_information_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_to_s_t_ne_t_market_information_message(&got, wire, 0) == 11);
  assert(encode_to_s_t_ne_t_market_information_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Control Message: 10 bytes ----------------------------------------------- */

/* In this tag, the test mode flag and the start/end flag that are used in a control message will be set. This tag will be edited into a control message (communication control and health check control) for output. */
typedef struct {
  uint8_t reserved_2[2];   /* bytes 0 to 1 */
  uint8_t test_mode_flag;  /* byte 2 */
  uint8_t start_end_flag;  /* byte 3 */
  uint8_t time_c_6[6];     /* bytes 4 to 9 */
} ControlMessage;

/* any Control Message at all: every byte one the checker chooses */
static void any_control_message(ControlMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->test_mode_flag = arbitrary();
  record->start_end_flag = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = arbitrary(); }
}

/* Control Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_control_message(const ControlMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->test_mode_flag;
  wire[at++] = record->start_end_flag;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6[i]; }

  return at;
}

/* Control Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_control_message(ControlMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->test_mode_flag = wire[at++];
  record->start_end_flag = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = wire[at++]; }

  return at;
}

/* what was read of Control Message is what was written, byte for byte */
static void equal_control_message(const ControlMessage *read, const ControlMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->test_mode_flag == written->test_mode_flag);
  assert(read->start_end_flag == written->start_end_flag);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6[i] == written->time_c_6[i]); }
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
  check_trading_halt();
  check_price();
  check_trading_volume();
  check_turnover();
  check_to_s_t_ne_t_by_issue_information_message();
  check_state();
  check_to_s_t_ne_t_market_information_message();
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
