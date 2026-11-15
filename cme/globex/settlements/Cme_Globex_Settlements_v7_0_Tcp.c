// cme/globex/settlements/Cme_Globex_Settlements_v7_0_Tcp.c
/*
 * CME Group Settlements
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
 *   - the dispatch that chooses a message by its type
 *   - a block whose stated length holds more than its fields
 *   - a run counted by a field
 *   - a field read in bits
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

/* ---- Technical Header: 14 bytes ---------------------------------------------- */

/* Cme Technical Header */
typedef struct {
  uint8_t encoding_type[2];            /* bytes 0 to 1 */
  uint8_t message_sequence_number[4];  /* bytes 2 to 5 */
  uint8_t tcp_sending_time[8];         /* bytes 6 to 13 */
} TechnicalHeader;

/* any Technical Header at all: every byte one the checker chooses */
static void any_technical_header(TechnicalHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->encoding_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tcp_sending_time[i] = arbitrary(); }
}

/* Technical Header to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_technical_header(const TechnicalHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->encoding_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->message_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tcp_sending_time[i]; }

  return at;
}

/* Technical Header off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_technical_header(TechnicalHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->encoding_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->message_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tcp_sending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Technical Header is what was written, byte for byte */
static void equal_technical_header(const TechnicalHeader *read, const TechnicalHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->encoding_type[i] == written->encoding_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->message_sequence_number[i] == written->message_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tcp_sending_time[i] == written->tcp_sending_time[i]); }
}

/* Technical Header: written and read back, then read and written back */
static void check_technical_header(void) {
  TechnicalHeader sent;
  TechnicalHeader got;
  uint8_t wire[14];
  uint8_t again[14];

  any_technical_header(&sent);
  assert(encode_technical_header(&sent, wire, 0) == 14);
  assert(decode_technical_header(&got, wire, 0) == 14);
  equal_technical_header(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_technical_header(&got, wire, 0) == 14);
  assert(encode_technical_header(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Binary Header: 8 bytes ------------------------------------------- */

/* Template ID and length of message root */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id[2];   /* bytes 2 to 3 */
  uint8_t schema_id[2];     /* bytes 4 to 5 */
  uint8_t version[2];       /* bytes 6 to 7 */
} SimpleBinaryHeader;

/* any Simple Binary Header at all: every byte one the checker chooses */
static void any_simple_binary_header(SimpleBinaryHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Simple Binary Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_simple_binary_header(const SimpleBinaryHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->schema_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Simple Binary Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_simple_binary_header(SimpleBinaryHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Binary Header is what was written, byte for byte */
static void equal_simple_binary_header(const SimpleBinaryHeader *read, const SimpleBinaryHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->schema_id[i] == written->schema_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Simple Binary Header: written and read back, then read and written back */
static void check_simple_binary_header(void) {
  SimpleBinaryHeader sent;
  SimpleBinaryHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_simple_binary_header(&sent);
  assert(encode_simple_binary_header(&sent, wire, 0) == 8);
  assert(decode_simple_binary_header(&got, wire, 0) == 8);
  equal_simple_binary_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_binary_header(&got, wire, 0) == 8);
  assert(encode_simple_binary_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 10 bytes ------------------------------------------------ */

/* Message Size followed by the Simple Binary Header */
typedef struct {
  uint8_t message_size[2];                  /* bytes 0 to 1 */
  SimpleBinaryHeader simple_binary_header;  /* bytes 2 to 9 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = arbitrary(); }
  any_simple_binary_header(&record->simple_binary_header);
}

/* Message Header to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_size[i]; }
  at = encode_simple_binary_header(&record->simple_binary_header, wire, at);

  return at;
}

/* Message Header off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = wire[at++]; }
  at = decode_simple_binary_header(&record->simple_binary_header, wire, at);

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_size[i] == written->message_size[i]); }
  equal_simple_binary_header(&read->simple_binary_header, &written->simple_binary_header);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[10];
  uint8_t again[10];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 10);
  assert(decode_message_header(&got, wire, 0) == 10);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 10);
  assert(encode_message_header(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size: 3 bytes ----------------------------------------------------- */

/* Repeating group dimensions */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t num_in_group;     /* byte 2 */
} GroupSize;

/* any Group Size at all: every byte one the checker chooses */
static void any_group_size(GroupSize *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->num_in_group = arbitrary();
}

/* Group Size to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_group_size(const GroupSize *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->num_in_group;

  return at;
}

/* Group Size off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_group_size(GroupSize *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Group Size is what was written, byte for byte */
static void equal_group_size(const GroupSize *read, const GroupSize *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->num_in_group == written->num_in_group);
}

/* Group Size: written and read back, then read and written back */
static void check_group_size(void) {
  GroupSize sent;
  GroupSize got;
  uint8_t wire[3];
  uint8_t again[3];

  any_group_size(&sent);
  assert(encode_group_size(&sent, wire, 0) == 3);
  assert(decode_group_size(&got, wire, 0) == 3);
  equal_group_size(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_group_size(&got, wire, 0) == 3);
  assert(encode_group_size(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maturity Month Year: 5 bytes -------------------------------------------- */

/* Number of data blocks */
typedef struct {
  uint8_t year[2];  /* bytes 0 to 1 */
  uint8_t month;    /* byte 2 */
  uint8_t day;      /* byte 3 */
  uint8_t week;     /* byte 4 */
} MaturityMonthYear;

/* any Maturity Month Year at all: every byte one the checker chooses */
static void any_maturity_month_year(MaturityMonthYear *record) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = arbitrary(); }
  record->month = arbitrary();
  record->day = arbitrary();
  record->week = arbitrary();
}

/* Maturity Month Year to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_maturity_month_year(const MaturityMonthYear *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->year[i]; }
  wire[at++] = record->month;
  wire[at++] = record->day;
  wire[at++] = record->week;

  return at;
}

/* Maturity Month Year off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_maturity_month_year(MaturityMonthYear *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = wire[at++]; }
  record->month = wire[at++];
  record->day = wire[at++];
  record->week = wire[at++];

  return at;
}

/* what was read of Maturity Month Year is what was written, byte for byte */
static void equal_maturity_month_year(const MaturityMonthYear *read, const MaturityMonthYear *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->year[i] == written->year[i]); }
  assert(read->month == written->month);
  assert(read->day == written->day);
  assert(read->week == written->week);
}

/* Maturity Month Year: written and read back, then read and written back */
static void check_maturity_month_year(void) {
  MaturityMonthYear sent;
  MaturityMonthYear got;
  uint8_t wire[5];
  uint8_t again[5];

  any_maturity_month_year(&sent);
  assert(encode_maturity_month_year(&sent, wire, 0) == 5);
  assert(decode_maturity_month_year(&got, wire, 0) == 5);
  equal_maturity_month_year(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_maturity_month_year(&got, wire, 0) == 5);
  assert(encode_maturity_month_year(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Price: 9 bytes --------------------------------------------------- */

/* Number of data blocks */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} StrikePrice;

/* any Strike Price at all: every byte one the checker chooses */
static void any_strike_price(StrikePrice *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Strike Price to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_strike_price(const StrikePrice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Strike Price off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_strike_price(StrikePrice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Strike Price is what was written, byte for byte */
static void equal_strike_price(const StrikePrice *read, const StrikePrice *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Strike Price: written and read back, then read and written back */
static void check_strike_price(void) {
  StrikePrice sent;
  StrikePrice got;
  uint8_t wire[9];
  uint8_t again[9];

  any_strike_price(&sent);
  assert(encode_strike_price(&sent, wire, 0) == 9);
  assert(decode_strike_price(&got, wire, 0) == 9);
  equal_strike_price(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_price(&got, wire, 0) == 9);
  assert(encode_strike_price(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Maturity Month Year: 5 bytes --------------------------------- */

/* Number of data blocks */
typedef struct {
  uint8_t year[2];  /* bytes 0 to 1 */
  uint8_t month;    /* byte 2 */
  uint8_t day;      /* byte 3 */
  uint8_t week;     /* byte 4 */
} UnderlyingMaturityMonthYear;

/* any Underlying Maturity Month Year at all: every byte one the checker chooses */
static void any_underlying_maturity_month_year(UnderlyingMaturityMonthYear *record) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = arbitrary(); }
  record->month = arbitrary();
  record->day = arbitrary();
  record->week = arbitrary();
}

/* Underlying Maturity Month Year to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_underlying_maturity_month_year(const UnderlyingMaturityMonthYear *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->year[i]; }
  wire[at++] = record->month;
  wire[at++] = record->day;
  wire[at++] = record->week;

  return at;
}

/* Underlying Maturity Month Year off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_underlying_maturity_month_year(UnderlyingMaturityMonthYear *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->year[i] = wire[at++]; }
  record->month = wire[at++];
  record->day = wire[at++];
  record->week = wire[at++];

  return at;
}

/* what was read of Underlying Maturity Month Year is what was written, byte for byte */
static void equal_underlying_maturity_month_year(const UnderlyingMaturityMonthYear *read, const UnderlyingMaturityMonthYear *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->year[i] == written->year[i]); }
  assert(read->month == written->month);
  assert(read->day == written->day);
  assert(read->week == written->week);
}

/* Underlying Maturity Month Year: written and read back, then read and written back */
static void check_underlying_maturity_month_year(void) {
  UnderlyingMaturityMonthYear sent;
  UnderlyingMaturityMonthYear got;
  uint8_t wire[5];
  uint8_t again[5];

  any_underlying_maturity_month_year(&sent);
  assert(encode_underlying_maturity_month_year(&sent, wire, 0) == 5);
  assert(decode_underlying_maturity_month_year(&got, wire, 0) == 5);
  equal_underlying_maturity_month_year(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_maturity_month_year(&got, wire, 0) == 5);
  assert(encode_underlying_maturity_month_year(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Formatted Last Px: 9 bytes ---------------------------------------------- */

/* Number of data blocks */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} FormattedLastPx;

/* any Formatted Last Px at all: every byte one the checker chooses */
static void any_formatted_last_px(FormattedLastPx *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Formatted Last Px to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_formatted_last_px(const FormattedLastPx *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Formatted Last Px off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_formatted_last_px(FormattedLastPx *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Formatted Last Px is what was written, byte for byte */
static void equal_formatted_last_px(const FormattedLastPx *read, const FormattedLastPx *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Formatted Last Px: written and read back, then read and written back */
static void check_formatted_last_px(void) {
  FormattedLastPx sent;
  FormattedLastPx got;
  uint8_t wire[9];
  uint8_t again[9];

  any_formatted_last_px(&sent);
  assert(encode_formatted_last_px(&sent, wire, 0) == 9);
  assert(decode_formatted_last_px(&got, wire, 0) == 9);
  equal_formatted_last_px(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_formatted_last_px(&got, wire, 0) == 9);
  assert(encode_formatted_last_px(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Low Px: 9 bytes --------------------------------------------------------- */

/* Number of data blocks */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} LowPx;

/* any Low Px at all: every byte one the checker chooses */
static void any_low_px(LowPx *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Low Px to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_low_px(const LowPx *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Low Px off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_low_px(LowPx *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Low Px is what was written, byte for byte */
static void equal_low_px(const LowPx *read, const LowPx *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* Low Px: written and read back, then read and written back */
static void check_low_px(void) {
  LowPx sent;
  LowPx got;
  uint8_t wire[9];
  uint8_t again[9];

  any_low_px(&sent);
  assert(encode_low_px(&sent, wire, 0) == 9);
  assert(decode_low_px(&got, wire, 0) == 9);
  equal_low_px(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_low_px(&got, wire, 0) == 9);
  assert(encode_low_px(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- High Px: 9 bytes -------------------------------------------------------- */

/* Number of data blocks */
typedef struct {
  uint8_t mantissa[8];  /* bytes 0 to 7 */
  uint8_t exponent;     /* byte 8 */
} HighPx;

/* any High Px at all: every byte one the checker chooses */
static void any_high_px(HighPx *record) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* High Px to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_high_px(const HighPx *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mantissa[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* High Px off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_high_px(HighPx *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->mantissa[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of High Px is what was written, byte for byte */
static void equal_high_px(const HighPx *read, const HighPx *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->mantissa[i] == written->mantissa[i]); }
  assert(read->exponent == written->exponent);
}

/* High Px: written and read back, then read and written back */
static void check_high_px(void) {
  HighPx sent;
  HighPx got;
  uint8_t wire[9];
  uint8_t again[9];

  any_high_px(&sent);
  assert(encode_high_px(&sent, wire, 0) == 9);
  assert(decode_high_px(&got, wire, 0) == 9);
  equal_high_px(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_high_px(&got, wire, 0) == 9);
  assert(encode_high_px(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_technical_header();
  check_simple_binary_header();
  check_message_header();
  check_group_size();
  check_maturity_month_year();
  check_strike_price();
  check_underlying_maturity_month_year();
  check_formatted_last_px();
  check_low_px();
  check_high_px();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
