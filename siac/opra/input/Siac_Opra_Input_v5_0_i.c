// siac/opra/input/Siac_Opra_Input_v5_0_i.c
/*
 * The Securities Industry Automation Corporation Input
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
 *   - a Reassemble rule
 *   - a run counted by a field
 *   - the dispatch that chooses a message by its type
 *   - a length prefix framing what follows
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

/* ---- Block Timestamp: 8 bytes ------------------------------------------------ */

/* Opra block timestamp */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} BlockTimestamp;

/* any Block Timestamp at all: every byte one the checker chooses */
static void any_block_timestamp(BlockTimestamp *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Block Timestamp to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_block_timestamp(const BlockTimestamp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Block Timestamp off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_block_timestamp(BlockTimestamp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Block Timestamp is what was written, byte for byte */
static void equal_block_timestamp(const BlockTimestamp *read, const BlockTimestamp *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Block Timestamp: written and read back, then read and written back */
static void check_block_timestamp(void) {
  BlockTimestamp sent;
  BlockTimestamp got;
  uint8_t wire[8];
  uint8_t again[8];

  any_block_timestamp(&sent);
  assert(encode_block_timestamp(&sent, wire, 0) == 8);
  assert(decode_block_timestamp(&got, wire, 0) == 8);
  equal_block_timestamp(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_block_timestamp(&got, wire, 0) == 8);
  assert(encode_block_timestamp(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Block Header: 21 bytes -------------------------------------------------- */

/* Opra Tcp block header */
typedef struct {
  uint8_t version;                   /* byte 0 */
  uint8_t block_size[2];             /* bytes 1 to 2 */
  uint8_t reserved;                  /* byte 3 */
  uint8_t second_reserved;           /* byte 4 */
  uint8_t third_reserved;            /* byte 5 */
  uint8_t block_sequence_number[4];  /* bytes 6 to 9 */
  uint8_t messages_in_block;         /* byte 10 */
  BlockTimestamp block_timestamp;    /* bytes 11 to 18 */
  uint8_t block_checksum[2];         /* bytes 19 to 20 */
} BlockHeader;

/* any Block Header at all: every byte one the checker chooses */
static void any_block_header(BlockHeader *record) {
  record->version = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->block_size[i] = arbitrary(); }
  record->reserved = arbitrary();
  record->second_reserved = arbitrary();
  record->third_reserved = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->block_sequence_number[i] = arbitrary(); }
  record->messages_in_block = arbitrary();
  any_block_timestamp(&record->block_timestamp);
  for (size_t i = 0; i < 2; i++) { record->block_checksum[i] = arbitrary(); }
}

/* Block Header to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_block_header(const BlockHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->version;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_size[i]; }
  wire[at++] = record->reserved;
  wire[at++] = record->second_reserved;
  wire[at++] = record->third_reserved;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_sequence_number[i]; }
  wire[at++] = record->messages_in_block;
  at = encode_block_timestamp(&record->block_timestamp, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_checksum[i]; }

  return at;
}

/* Block Header off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_block_header(BlockHeader *record, const uint8_t *wire, size_t at) {
  record->version = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->block_size[i] = wire[at++]; }
  record->reserved = wire[at++];
  record->second_reserved = wire[at++];
  record->third_reserved = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->block_sequence_number[i] = wire[at++]; }
  record->messages_in_block = wire[at++];
  at = decode_block_timestamp(&record->block_timestamp, wire, at);
  for (size_t i = 0; i < 2; i++) { record->block_checksum[i] = wire[at++]; }

  return at;
}

/* what was read of Block Header is what was written, byte for byte */
static void equal_block_header(const BlockHeader *read, const BlockHeader *written) {
  assert(read->version == written->version);
  for (size_t i = 0; i < 2; i++) { assert(read->block_size[i] == written->block_size[i]); }
  assert(read->reserved == written->reserved);
  assert(read->second_reserved == written->second_reserved);
  assert(read->third_reserved == written->third_reserved);
  for (size_t i = 0; i < 4; i++) { assert(read->block_sequence_number[i] == written->block_sequence_number[i]); }
  assert(read->messages_in_block == written->messages_in_block);
  equal_block_timestamp(&read->block_timestamp, &written->block_timestamp);
  for (size_t i = 0; i < 2; i++) { assert(read->block_checksum[i] == written->block_checksum[i]); }
}

/* Block Header: written and read back, then read and written back */
static void check_block_header(void) {
  BlockHeader sent;
  BlockHeader got;
  uint8_t wire[21];
  uint8_t again[21];

  any_block_header(&sent);
  assert(encode_block_header(&sent, wire, 0) == 21);
  assert(decode_block_header(&got, wire, 0) == 21);
  equal_block_header(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_block_header(&got, wire, 0) == 21);
  assert(encode_block_header(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 2 bytes ------------------------------------------------- */

/* Opra Message Header first level dispatch */
typedef struct {
  uint8_t participant_id;    /* byte 0 */
  uint8_t message_category;  /* byte 1 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->participant_id = arbitrary();
  record->message_category = arbitrary();
}

/* Message Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  wire[at++] = record->message_category;

  return at;
}

/* Message Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  record->message_category = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->participant_id == written->participant_id);
  assert(read->message_category == written->message_category);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[2];
  uint8_t again[2];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 2);
  assert(decode_message_header(&got, wire, 0) == 2);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 2);
  assert(encode_message_header(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Expiration Block: 3 bytes ----------------------------------------------- */

/* Expiration Block */
typedef struct {
  uint8_t expiration_month;  /* byte 0 */
  uint8_t expiration_day;    /* byte 1 */
  uint8_t expiration_year;   /* byte 2 */
} ExpirationBlock;

/* any Expiration Block at all: every byte one the checker chooses */
static void any_expiration_block(ExpirationBlock *record) {
  record->expiration_month = arbitrary();
  record->expiration_day = arbitrary();
  record->expiration_year = arbitrary();
}

/* Expiration Block to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_expiration_block(const ExpirationBlock *record, uint8_t *wire, size_t at) {
  wire[at++] = record->expiration_month;
  wire[at++] = record->expiration_day;
  wire[at++] = record->expiration_year;

  return at;
}

/* Expiration Block off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_expiration_block(ExpirationBlock *record, const uint8_t *wire, size_t at) {
  record->expiration_month = wire[at++];
  record->expiration_day = wire[at++];
  record->expiration_year = wire[at++];

  return at;
}

/* what was read of Expiration Block is what was written, byte for byte */
static void equal_expiration_block(const ExpirationBlock *read, const ExpirationBlock *written) {
  assert(read->expiration_month == written->expiration_month);
  assert(read->expiration_day == written->expiration_day);
  assert(read->expiration_year == written->expiration_year);
}

/* Expiration Block: written and read back, then read and written back */
static void check_expiration_block(void) {
  ExpirationBlock sent;
  ExpirationBlock got;
  uint8_t wire[3];
  uint8_t again[3];

  any_expiration_block(&sent);
  assert(encode_expiration_block(&sent, wire, 0) == 3);
  assert(decode_expiration_block(&got, wire, 0) == 3);
  equal_expiration_block(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_expiration_block(&got, wire, 0) == 3);
  assert(encode_expiration_block(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Equity And Index Last Sale Message: 36 bytes ---------------------------- */

/* Equity and Index Last Sale message used to report equity and index options last sale information */
typedef struct {
  uint8_t session_indicator;                /* byte 0 */
  uint8_t participant_reference_number[4];  /* bytes 1 to 4 */
  uint8_t security_symbol[5];               /* bytes 5 to 9 */
  uint8_t reserved_1;                       /* byte 10 */
  ExpirationBlock expiration_block;         /* bytes 11 to 13 */
  uint8_t strike_price_denominator_code;    /* byte 14 */
  uint8_t strike_price[4];                  /* bytes 15 to 18 */
  uint8_t volume[4];                        /* bytes 19 to 22 */
  uint8_t premium_price_denominator_code;   /* byte 23 */
  uint8_t premium_price[4];                 /* bytes 24 to 27 */
  uint8_t trade_identifier[4];              /* bytes 28 to 31 */
  uint8_t reserved_4[4];                    /* bytes 32 to 35 */
} EquityAndIndexLastSaleMessage;

/* any Equity And Index Last Sale Message at all: every byte one the checker chooses */
static void any_equity_and_index_last_sale_message(EquityAndIndexLastSaleMessage *record) {
  record->session_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  any_expiration_block(&record->expiration_block);
  record->strike_price_denominator_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->premium_price_denominator_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->premium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_identifier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Equity And Index Last Sale Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_equity_and_index_last_sale_message(const EquityAndIndexLastSaleMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->reserved_1;
  at = encode_expiration_block(&record->expiration_block, wire, at);
  wire[at++] = record->strike_price_denominator_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->premium_price_denominator_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->premium_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_identifier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Equity And Index Last Sale Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_equity_and_index_last_sale_message(EquityAndIndexLastSaleMessage *record, const uint8_t *wire, size_t at) {
  record->session_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  at = decode_expiration_block(&record->expiration_block, wire, at);
  record->strike_price_denominator_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->premium_price_denominator_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->premium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_identifier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Equity And Index Last Sale Message is what was written, byte for byte */
static void equal_equity_and_index_last_sale_message(const EquityAndIndexLastSaleMessage *read, const EquityAndIndexLastSaleMessage *written) {
  assert(read->session_indicator == written->session_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->reserved_1 == written->reserved_1);
  equal_expiration_block(&read->expiration_block, &written->expiration_block);
  assert(read->strike_price_denominator_code == written->strike_price_denominator_code);
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->premium_price_denominator_code == written->premium_price_denominator_code);
  for (size_t i = 0; i < 4; i++) { assert(read->premium_price[i] == written->premium_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_identifier[i] == written->trade_identifier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Equity And Index Last Sale Message: written and read back, then read and written back */
static void check_equity_and_index_last_sale_message(void) {
  EquityAndIndexLastSaleMessage sent;
  EquityAndIndexLastSaleMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_equity_and_index_last_sale_message(&sent);
  assert(encode_equity_and_index_last_sale_message(&sent, wire, 0) == 36);
  assert(decode_equity_and_index_last_sale_message(&got, wire, 0) == 36);
  equal_equity_and_index_last_sale_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_equity_and_index_last_sale_message(&got, wire, 0) == 36);
  assert(encode_equity_and_index_last_sale_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Equity And Index End Of Day Summary Message: 65 bytes ------------------- */

/* Equity and Index End of Day Summary message providing per symbol open high low last net change and underlying information */
typedef struct {
  uint8_t session_indicator;                  /* byte 0 */
  uint8_t participant_reference_number[4];    /* bytes 1 to 4 */
  uint8_t security_symbol[5];                 /* bytes 5 to 9 */
  uint8_t reserved_1;                         /* byte 10 */
  ExpirationBlock expiration_block;           /* bytes 11 to 13 */
  uint8_t strike_price_denominator_code;      /* byte 14 */
  uint8_t strike_price[4];                    /* bytes 15 to 18 */
  uint8_t volume[4];                          /* bytes 19 to 22 */
  uint8_t open_interest_volume[4];            /* bytes 23 to 26 */
  uint8_t premium_price_denominator_code;     /* byte 27 */
  uint8_t open_price[4];                      /* bytes 28 to 31 */
  uint8_t high_price[4];                      /* bytes 32 to 35 */
  uint8_t low_price[4];                       /* bytes 36 to 39 */
  uint8_t last_price[4];                      /* bytes 40 to 43 */
  uint8_t net_change[4];                      /* bytes 44 to 47 */
  uint8_t underlying_price_denominator_code;  /* byte 48 */
  uint8_t underlying_price[8];                /* bytes 49 to 56 */
  uint8_t bid_price[4];                       /* bytes 57 to 60 */
  uint8_t offer_price[4];                     /* bytes 61 to 64 */
} EquityAndIndexEndOfDaySummaryMessage;

/* any Equity And Index End Of Day Summary Message at all: every byte one the checker chooses */
static void any_equity_and_index_end_of_day_summary_message(EquityAndIndexEndOfDaySummaryMessage *record) {
  record->session_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  any_expiration_block(&record->expiration_block);
  record->strike_price_denominator_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_interest_volume[i] = arbitrary(); }
  record->premium_price_denominator_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->net_change[i] = arbitrary(); }
  record->underlying_price_denominator_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->underlying_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->offer_price[i] = arbitrary(); }
}

/* Equity And Index End Of Day Summary Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_equity_and_index_end_of_day_summary_message(const EquityAndIndexEndOfDaySummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->reserved_1;
  at = encode_expiration_block(&record->expiration_block, wire, at);
  wire[at++] = record->strike_price_denominator_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_interest_volume[i]; }
  wire[at++] = record->premium_price_denominator_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->net_change[i]; }
  wire[at++] = record->underlying_price_denominator_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->offer_price[i]; }

  return at;
}

/* Equity And Index End Of Day Summary Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_equity_and_index_end_of_day_summary_message(EquityAndIndexEndOfDaySummaryMessage *record, const uint8_t *wire, size_t at) {
  record->session_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  at = decode_expiration_block(&record->expiration_block, wire, at);
  record->strike_price_denominator_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_interest_volume[i] = wire[at++]; }
  record->premium_price_denominator_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->net_change[i] = wire[at++]; }
  record->underlying_price_denominator_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->underlying_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->offer_price[i] = wire[at++]; }

  return at;
}

/* what was read of Equity And Index End Of Day Summary Message is what was written, byte for byte */
static void equal_equity_and_index_end_of_day_summary_message(const EquityAndIndexEndOfDaySummaryMessage *read, const EquityAndIndexEndOfDaySummaryMessage *written) {
  assert(read->session_indicator == written->session_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->reserved_1 == written->reserved_1);
  equal_expiration_block(&read->expiration_block, &written->expiration_block);
  assert(read->strike_price_denominator_code == written->strike_price_denominator_code);
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_interest_volume[i] == written->open_interest_volume[i]); }
  assert(read->premium_price_denominator_code == written->premium_price_denominator_code);
  for (size_t i = 0; i < 4; i++) { assert(read->open_price[i] == written->open_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->net_change[i] == written->net_change[i]); }
  assert(read->underlying_price_denominator_code == written->underlying_price_denominator_code);
  for (size_t i = 0; i < 8; i++) { assert(read->underlying_price[i] == written->underlying_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->offer_price[i] == written->offer_price[i]); }
}

/* Equity And Index End Of Day Summary Message: written and read back, then read and written back */
static void check_equity_and_index_end_of_day_summary_message(void) {
  EquityAndIndexEndOfDaySummaryMessage sent;
  EquityAndIndexEndOfDaySummaryMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_equity_and_index_end_of_day_summary_message(&sent);
  assert(encode_equity_and_index_end_of_day_summary_message(&sent, wire, 0) == 65);
  assert(decode_equity_and_index_end_of_day_summary_message(&got, wire, 0) == 65);
  equal_equity_and_index_end_of_day_summary_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_equity_and_index_end_of_day_summary_message(&got, wire, 0) == 65);
  assert(encode_equity_and_index_end_of_day_summary_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Equity And Index Quote Message: 36 bytes --------------------------- */

/* Long Equity and Index Quote message containing a full quote using four byte integers for prices and sizes */
typedef struct {
  uint8_t session_indicator;                /* byte 0 */
  uint8_t participant_reference_number[4];  /* bytes 1 to 4 */
  uint8_t security_symbol[5];               /* bytes 5 to 9 */
  uint8_t reserved_1;                       /* byte 10 */
  ExpirationBlock expiration_block;         /* bytes 11 to 13 */
  uint8_t strike_price_denominator_code;    /* byte 14 */
  uint8_t strike_price[4];                  /* bytes 15 to 18 */
  uint8_t premium_price_denominator_code;   /* byte 19 */
  uint8_t bid_price[4];                     /* bytes 20 to 23 */
  uint8_t bid_size[4];                      /* bytes 24 to 27 */
  uint8_t offer_price[4];                   /* bytes 28 to 31 */
  uint8_t offer_size[4];                    /* bytes 32 to 35 */
} LongEquityAndIndexQuoteMessage;

/* any Long Equity And Index Quote Message at all: every byte one the checker chooses */
static void any_long_equity_and_index_quote_message(LongEquityAndIndexQuoteMessage *record) {
  record->session_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  any_expiration_block(&record->expiration_block);
  record->strike_price_denominator_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  record->premium_price_denominator_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->offer_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->offer_size[i] = arbitrary(); }
}

/* Long Equity And Index Quote Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_long_equity_and_index_quote_message(const LongEquityAndIndexQuoteMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->reserved_1;
  at = encode_expiration_block(&record->expiration_block, wire, at);
  wire[at++] = record->strike_price_denominator_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->premium_price_denominator_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->offer_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->offer_size[i]; }

  return at;
}

/* Long Equity And Index Quote Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_long_equity_and_index_quote_message(LongEquityAndIndexQuoteMessage *record, const uint8_t *wire, size_t at) {
  record->session_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  at = decode_expiration_block(&record->expiration_block, wire, at);
  record->strike_price_denominator_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  record->premium_price_denominator_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->offer_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->offer_size[i] = wire[at++]; }

  return at;
}

/* what was read of Long Equity And Index Quote Message is what was written, byte for byte */
static void equal_long_equity_and_index_quote_message(const LongEquityAndIndexQuoteMessage *read, const LongEquityAndIndexQuoteMessage *written) {
  assert(read->session_indicator == written->session_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->reserved_1 == written->reserved_1);
  equal_expiration_block(&read->expiration_block, &written->expiration_block);
  assert(read->strike_price_denominator_code == written->strike_price_denominator_code);
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->premium_price_denominator_code == written->premium_price_denominator_code);
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size[i] == written->bid_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->offer_price[i] == written->offer_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->offer_size[i] == written->offer_size[i]); }
}

/* Long Equity And Index Quote Message: written and read back, then read and written back */
static void check_long_equity_and_index_quote_message(void) {
  LongEquityAndIndexQuoteMessage sent;
  LongEquityAndIndexQuoteMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_long_equity_and_index_quote_message(&sent);
  assert(encode_long_equity_and_index_quote_message(&sent, wire, 0) == 36);
  assert(decode_long_equity_and_index_quote_message(&got, wire, 0) == 36);
  equal_long_equity_and_index_quote_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_long_equity_and_index_quote_message(&got, wire, 0) == 36);
  assert(encode_long_equity_and_index_quote_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Short Equity And Index Quote Message: 22 bytes -------------------------- */

/* Short Equity and Index Quote message containing a short quote using two byte unsigned integers for prices and sizes */
typedef struct {
  uint8_t session_indicator;                /* byte 0 */
  uint8_t participant_reference_number[4];  /* bytes 1 to 4 */
  uint8_t security_symbol_short[4];         /* bytes 5 to 8 */
  ExpirationBlock expiration_block;         /* bytes 9 to 11 */
  uint8_t strike_price_short[2];            /* bytes 12 to 13 */
  uint8_t bid_price_short[2];               /* bytes 14 to 15 */
  uint8_t bid_size_short[2];                /* bytes 16 to 17 */
  uint8_t offer_price_short[2];             /* bytes 18 to 19 */
  uint8_t offer_size_short[2];              /* bytes 20 to 21 */
} ShortEquityAndIndexQuoteMessage;

/* any Short Equity And Index Quote Message at all: every byte one the checker chooses */
static void any_short_equity_and_index_quote_message(ShortEquityAndIndexQuoteMessage *record) {
  record->session_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_symbol_short[i] = arbitrary(); }
  any_expiration_block(&record->expiration_block);
  for (size_t i = 0; i < 2; i++) { record->strike_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->offer_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->offer_size_short[i] = arbitrary(); }
}

/* Short Equity And Index Quote Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_short_equity_and_index_quote_message(const ShortEquityAndIndexQuoteMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_symbol_short[i]; }
  at = encode_expiration_block(&record->expiration_block, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->strike_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_size_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->offer_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->offer_size_short[i]; }

  return at;
}

/* Short Equity And Index Quote Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_short_equity_and_index_quote_message(ShortEquityAndIndexQuoteMessage *record, const uint8_t *wire, size_t at) {
  record->session_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_symbol_short[i] = wire[at++]; }
  at = decode_expiration_block(&record->expiration_block, wire, at);
  for (size_t i = 0; i < 2; i++) { record->strike_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->offer_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->offer_size_short[i] = wire[at++]; }

  return at;
}

/* what was read of Short Equity And Index Quote Message is what was written, byte for byte */
static void equal_short_equity_and_index_quote_message(const ShortEquityAndIndexQuoteMessage *read, const ShortEquityAndIndexQuoteMessage *written) {
  assert(read->session_indicator == written->session_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_symbol_short[i] == written->security_symbol_short[i]); }
  equal_expiration_block(&read->expiration_block, &written->expiration_block);
  for (size_t i = 0; i < 2; i++) { assert(read->strike_price_short[i] == written->strike_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_price_short[i] == written->bid_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_size_short[i] == written->bid_size_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->offer_price_short[i] == written->offer_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->offer_size_short[i] == written->offer_size_short[i]); }
}

/* Short Equity And Index Quote Message: written and read back, then read and written back */
static void check_short_equity_and_index_quote_message(void) {
  ShortEquityAndIndexQuoteMessage sent;
  ShortEquityAndIndexQuoteMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_short_equity_and_index_quote_message(&sent);
  assert(encode_short_equity_and_index_quote_message(&sent, wire, 0) == 22);
  assert(decode_short_equity_and_index_quote_message(&got, wire, 0) == 22);
  equal_short_equity_and_index_quote_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_short_equity_and_index_quote_message(&got, wire, 0) == 22);
  assert(encode_short_equity_and_index_quote_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Control Message: 5 bytes ------------------------------------------------ */

/* Control message performs specified control functions consists of standard Message Header only */
typedef struct {
  uint8_t session_indicator;                /* byte 0 */
  uint8_t participant_reference_number[4];  /* bytes 1 to 4 */
} ControlMessage;

/* any Control Message at all: every byte one the checker chooses */
static void any_control_message(ControlMessage *record) {
  record->session_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Control Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_control_message(const ControlMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Control Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_control_message(ControlMessage *record, const uint8_t *wire, size_t at) {
  record->session_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Control Message is what was written, byte for byte */
static void equal_control_message(const ControlMessage *read, const ControlMessage *written) {
  assert(read->session_indicator == written->session_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Control Message: written and read back, then read and written back */
static void check_control_message(void) {
  ControlMessage sent;
  ControlMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_control_message(&sent);
  assert(encode_control_message(&sent, wire, 0) == 5);
  assert(decode_control_message(&got, wire, 0) == 5);
  equal_control_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_control_message(&got, wire, 0) == 5);
  assert(encode_control_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Block Sequence Number Status Inquiry Request Message: 13 bytes ---------- */

/* Block Sequence Number Status Inquiry Request sent by the Participant to request the last Block Sequence Number received on that line */
typedef struct {
  uint8_t session_indicator;                /* byte 0 */
  uint8_t participant_reference_number[4];  /* bytes 1 to 4 */
  uint8_t reserved_4[4];                    /* bytes 5 to 8 */
  uint8_t second_reserved_4[4];             /* bytes 9 to 12 */
} BlockSequenceNumberStatusInquiryRequestMessage;

/* any Block Sequence Number Status Inquiry Request Message at all: every byte one the checker chooses */
static void any_block_sequence_number_status_inquiry_request_message(BlockSequenceNumberStatusInquiryRequestMessage *record) {
  record->session_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->second_reserved_4[i] = arbitrary(); }
}

/* Block Sequence Number Status Inquiry Request Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_block_sequence_number_status_inquiry_request_message(const BlockSequenceNumberStatusInquiryRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second_reserved_4[i]; }

  return at;
}

/* Block Sequence Number Status Inquiry Request Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_block_sequence_number_status_inquiry_request_message(BlockSequenceNumberStatusInquiryRequestMessage *record, const uint8_t *wire, size_t at) {
  record->session_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->second_reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Block Sequence Number Status Inquiry Request Message is what was written, byte for byte */
static void equal_block_sequence_number_status_inquiry_request_message(const BlockSequenceNumberStatusInquiryRequestMessage *read, const BlockSequenceNumberStatusInquiryRequestMessage *written) {
  assert(read->session_indicator == written->session_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->second_reserved_4[i] == written->second_reserved_4[i]); }
}

/* Block Sequence Number Status Inquiry Request Message: written and read back, then read and written back */
static void check_block_sequence_number_status_inquiry_request_message(void) {
  BlockSequenceNumberStatusInquiryRequestMessage sent;
  BlockSequenceNumberStatusInquiryRequestMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_block_sequence_number_status_inquiry_request_message(&sent);
  assert(encode_block_sequence_number_status_inquiry_request_message(&sent, wire, 0) == 13);
  assert(decode_block_sequence_number_status_inquiry_request_message(&got, wire, 0) == 13);
  equal_block_sequence_number_status_inquiry_request_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_block_sequence_number_status_inquiry_request_message(&got, wire, 0) == 13);
  assert(encode_block_sequence_number_status_inquiry_request_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Block Sequence Number Status Response Message: 13 bytes ----------------- */

/* Block Sequence Number Status Response sent to the Participant by Opra in response to a Type L message contains the last Block Sequence Number received on that input line */
typedef struct {
  uint8_t session_indicator;                /* byte 0 */
  uint8_t participant_reference_number[4];  /* bytes 1 to 4 */
  uint8_t block_sequence_number[4];         /* bytes 5 to 8 */
  uint8_t reserved_4[4];                    /* bytes 9 to 12 */
} BlockSequenceNumberStatusResponseMessage;

/* any Block Sequence Number Status Response Message at all: every byte one the checker chooses */
static void any_block_sequence_number_status_response_message(BlockSequenceNumberStatusResponseMessage *record) {
  record->session_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->block_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Block Sequence Number Status Response Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_block_sequence_number_status_response_message(const BlockSequenceNumberStatusResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Block Sequence Number Status Response Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_block_sequence_number_status_response_message(BlockSequenceNumberStatusResponseMessage *record, const uint8_t *wire, size_t at) {
  record->session_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->block_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Block Sequence Number Status Response Message is what was written, byte for byte */
static void equal_block_sequence_number_status_response_message(const BlockSequenceNumberStatusResponseMessage *read, const BlockSequenceNumberStatusResponseMessage *written) {
  assert(read->session_indicator == written->session_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->block_sequence_number[i] == written->block_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Block Sequence Number Status Response Message: written and read back, then read and written back */
static void check_block_sequence_number_status_response_message(void) {
  BlockSequenceNumberStatusResponseMessage sent;
  BlockSequenceNumberStatusResponseMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_block_sequence_number_status_response_message(&sent);
  assert(encode_block_sequence_number_status_response_message(&sent, wire, 0) == 13);
  assert(decode_block_sequence_number_status_response_message(&got, wire, 0) == 13);
  equal_block_sequence_number_status_response_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_block_sequence_number_status_response_message(&got, wire, 0) == 13);
  assert(encode_block_sequence_number_status_response_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Count Status Inquiry Request Message: 13 bytes ------------------ */

/* Message Count Status Inquiry Request sent by the Participant to request the message count on that line */
typedef struct {
  uint8_t session_indicator;                /* byte 0 */
  uint8_t participant_reference_number[4];  /* bytes 1 to 4 */
  uint8_t reserved_8[8];                    /* bytes 5 to 12 */
} MessageCountStatusInquiryRequestMessage;

/* any Message Count Status Inquiry Request Message at all: every byte one the checker chooses */
static void any_message_count_status_inquiry_request_message(MessageCountStatusInquiryRequestMessage *record) {
  record->session_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Message Count Status Inquiry Request Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_message_count_status_inquiry_request_message(const MessageCountStatusInquiryRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Message Count Status Inquiry Request Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_message_count_status_inquiry_request_message(MessageCountStatusInquiryRequestMessage *record, const uint8_t *wire, size_t at) {
  record->session_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Message Count Status Inquiry Request Message is what was written, byte for byte */
static void equal_message_count_status_inquiry_request_message(const MessageCountStatusInquiryRequestMessage *read, const MessageCountStatusInquiryRequestMessage *written) {
  assert(read->session_indicator == written->session_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Message Count Status Inquiry Request Message: written and read back, then read and written back */
static void check_message_count_status_inquiry_request_message(void) {
  MessageCountStatusInquiryRequestMessage sent;
  MessageCountStatusInquiryRequestMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_message_count_status_inquiry_request_message(&sent);
  assert(encode_message_count_status_inquiry_request_message(&sent, wire, 0) == 13);
  assert(decode_message_count_status_inquiry_request_message(&got, wire, 0) == 13);
  equal_message_count_status_inquiry_request_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_message_count_status_inquiry_request_message(&got, wire, 0) == 13);
  assert(encode_message_count_status_inquiry_request_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Count Status Response Message: 13 bytes ------------------------- */

/* Message Count Status Response sent from Opra to the Participant containing the count of messages received on an individual line since startup */
typedef struct {
  uint8_t session_indicator;                /* byte 0 */
  uint8_t participant_reference_number[4];  /* bytes 1 to 4 */
  uint8_t message_count[8];                 /* bytes 5 to 12 */
} MessageCountStatusResponseMessage;

/* any Message Count Status Response Message at all: every byte one the checker chooses */
static void any_message_count_status_response_message(MessageCountStatusResponseMessage *record) {
  record->session_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->message_count[i] = arbitrary(); }
}

/* Message Count Status Response Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_message_count_status_response_message(const MessageCountStatusResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->message_count[i]; }

  return at;
}

/* Message Count Status Response Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_message_count_status_response_message(MessageCountStatusResponseMessage *record, const uint8_t *wire, size_t at) {
  record->session_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Message Count Status Response Message is what was written, byte for byte */
static void equal_message_count_status_response_message(const MessageCountStatusResponseMessage *read, const MessageCountStatusResponseMessage *written) {
  assert(read->session_indicator == written->session_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->message_count[i] == written->message_count[i]); }
}

/* Message Count Status Response Message: written and read back, then read and written back */
static void check_message_count_status_response_message(void) {
  MessageCountStatusResponseMessage sent;
  MessageCountStatusResponseMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_message_count_status_response_message(&sent);
  assert(encode_message_count_status_response_message(&sent, wire, 0) == 13);
  assert(decode_message_count_status_response_message(&got, wire, 0) == 13);
  equal_message_count_status_response_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_message_count_status_response_message(&got, wire, 0) == 13);
  assert(encode_message_count_status_response_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Value Last Sale Message: 20 bytes ---------------------------- */

/* Underlying Value Last Sale message containing the Last Sale Index Value */
typedef struct {
  uint8_t session_indicator;                /* byte 0 */
  uint8_t participant_reference_number[4];  /* bytes 1 to 4 */
  uint8_t security_symbol[5];               /* bytes 5 to 9 */
  uint8_t reserved_1;                       /* byte 10 */
  uint8_t index_value_denominator_code;     /* byte 11 */
  uint8_t index_value[4];                   /* bytes 12 to 15 */
  uint8_t reserved_4[4];                    /* bytes 16 to 19 */
} UnderlyingValueLastSaleMessage;

/* any Underlying Value Last Sale Message at all: every byte one the checker chooses */
static void any_underlying_value_last_sale_message(UnderlyingValueLastSaleMessage *record) {
  record->session_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->index_value_denominator_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->index_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Underlying Value Last Sale Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_underlying_value_last_sale_message(const UnderlyingValueLastSaleMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->index_value_denominator_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Underlying Value Last Sale Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_underlying_value_last_sale_message(UnderlyingValueLastSaleMessage *record, const uint8_t *wire, size_t at) {
  record->session_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->index_value_denominator_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->index_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Underlying Value Last Sale Message is what was written, byte for byte */
static void equal_underlying_value_last_sale_message(const UnderlyingValueLastSaleMessage *read, const UnderlyingValueLastSaleMessage *written) {
  assert(read->session_indicator == written->session_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->reserved_1 == written->reserved_1);
  assert(read->index_value_denominator_code == written->index_value_denominator_code);
  for (size_t i = 0; i < 4; i++) { assert(read->index_value[i] == written->index_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Underlying Value Last Sale Message: written and read back, then read and written back */
static void check_underlying_value_last_sale_message(void) {
  UnderlyingValueLastSaleMessage sent;
  UnderlyingValueLastSaleMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_underlying_value_last_sale_message(&sent);
  assert(encode_underlying_value_last_sale_message(&sent, wire, 0) == 20);
  assert(decode_underlying_value_last_sale_message(&got, wire, 0) == 20);
  equal_underlying_value_last_sale_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_value_last_sale_message(&got, wire, 0) == 20);
  assert(encode_underlying_value_last_sale_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Value Bid And Offer Message: 20 bytes ------------------------ */

/* Underlying Value Bid and Offer message containing the Last Sale Bid Offer Index Value */
typedef struct {
  uint8_t session_indicator;                /* byte 0 */
  uint8_t participant_reference_number[4];  /* bytes 1 to 4 */
  uint8_t security_symbol[5];               /* bytes 5 to 9 */
  uint8_t reserved_1;                       /* byte 10 */
  uint8_t index_value_denominator_code;     /* byte 11 */
  uint8_t bid_index_value[4];               /* bytes 12 to 15 */
  uint8_t offer_index_value[4];             /* bytes 16 to 19 */
} UnderlyingValueBidAndOfferMessage;

/* any Underlying Value Bid And Offer Message at all: every byte one the checker chooses */
static void any_underlying_value_bid_and_offer_message(UnderlyingValueBidAndOfferMessage *record) {
  record->session_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->index_value_denominator_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->bid_index_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->offer_index_value[i] = arbitrary(); }
}

/* Underlying Value Bid And Offer Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_underlying_value_bid_and_offer_message(const UnderlyingValueBidAndOfferMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->session_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->index_value_denominator_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_index_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->offer_index_value[i]; }

  return at;
}

/* Underlying Value Bid And Offer Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_underlying_value_bid_and_offer_message(UnderlyingValueBidAndOfferMessage *record, const uint8_t *wire, size_t at) {
  record->session_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->index_value_denominator_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->bid_index_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->offer_index_value[i] = wire[at++]; }

  return at;
}

/* what was read of Underlying Value Bid And Offer Message is what was written, byte for byte */
static void equal_underlying_value_bid_and_offer_message(const UnderlyingValueBidAndOfferMessage *read, const UnderlyingValueBidAndOfferMessage *written) {
  assert(read->session_indicator == written->session_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->reserved_1 == written->reserved_1);
  assert(read->index_value_denominator_code == written->index_value_denominator_code);
  for (size_t i = 0; i < 4; i++) { assert(read->bid_index_value[i] == written->bid_index_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->offer_index_value[i] == written->offer_index_value[i]); }
}

/* Underlying Value Bid And Offer Message: written and read back, then read and written back */
static void check_underlying_value_bid_and_offer_message(void) {
  UnderlyingValueBidAndOfferMessage sent;
  UnderlyingValueBidAndOfferMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_underlying_value_bid_and_offer_message(&sent);
  assert(encode_underlying_value_bid_and_offer_message(&sent, wire, 0) == 20);
  assert(decode_underlying_value_bid_and_offer_message(&got, wire, 0) == 20);
  equal_underlying_value_bid_and_offer_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_value_bid_and_offer_message(&got, wire, 0) == 20);
  assert(encode_underlying_value_bid_and_offer_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_block_timestamp();
  check_block_header();
  check_message_header();
  check_expiration_block();
  check_equity_and_index_last_sale_message();
  check_equity_and_index_end_of_day_summary_message();
  check_long_equity_and_index_quote_message();
  check_short_equity_and_index_quote_message();
  check_control_message();
  check_block_sequence_number_status_inquiry_request_message();
  check_block_sequence_number_status_response_message();
  check_message_count_status_inquiry_request_message();
  check_message_count_status_response_message();
  check_underlying_value_last_sale_message();
  check_underlying_value_bid_and_offer_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
