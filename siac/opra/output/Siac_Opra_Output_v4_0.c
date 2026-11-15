// siac/opra/output/Siac_Opra_Output_v4_0.c
/*
 * The Securities Industry Automation Corporation Output
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
 *   - a run counted by a field
 *   - the dispatch that chooses a message by its type
 *   - a field present only on a condition
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

/* Block Timestamp */
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

/* Opra packet header */
typedef struct {
  uint8_t version;                   /* byte 0 */
  uint8_t block_size[2];             /* bytes 1 to 2 */
  uint8_t data_feed_indicator;       /* byte 3 */
  uint8_t retransmission_indicator;  /* byte 4 */
  uint8_t session_indicator;         /* byte 5 */
  uint8_t block_sequence_number[4];  /* bytes 6 to 9 */
  uint8_t messages_in_block;         /* byte 10 */
  BlockTimestamp block_timestamp;    /* bytes 11 to 18 */
  uint8_t block_checksum[2];         /* bytes 19 to 20 */
} BlockHeader;

/* any Block Header at all: every byte one the checker chooses */
static void any_block_header(BlockHeader *record) {
  record->version = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->block_size[i] = arbitrary(); }
  record->data_feed_indicator = arbitrary();
  record->retransmission_indicator = arbitrary();
  record->session_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->block_sequence_number[i] = arbitrary(); }
  record->messages_in_block = arbitrary();
  any_block_timestamp(&record->block_timestamp);
  for (size_t i = 0; i < 2; i++) { record->block_checksum[i] = arbitrary(); }
}

/* Block Header to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_block_header(const BlockHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->version;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_size[i]; }
  wire[at++] = record->data_feed_indicator;
  wire[at++] = record->retransmission_indicator;
  wire[at++] = record->session_indicator;
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
  record->data_feed_indicator = wire[at++];
  record->retransmission_indicator = wire[at++];
  record->session_indicator = wire[at++];
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
  assert(read->data_feed_indicator == written->data_feed_indicator);
  assert(read->retransmission_indicator == written->retransmission_indicator);
  assert(read->session_indicator == written->session_indicator);
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

/* ---- Equity And Index Last Sale Message: 40 bytes ---------------------------- */

/* The Equity and Index Last Sale message is used to report equity and index options last sale information. */
typedef struct {
  uint8_t message_indicator;               /* byte 0 */
  uint8_t transaction_id[8];               /* bytes 1 to 8 */
  uint8_t security_symbol[5];              /* bytes 9 to 13 */
  uint8_t reserved_1;                      /* byte 14 */
  ExpirationBlock expiration_block;        /* bytes 15 to 17 */
  uint8_t strike_price_denominator_code;   /* byte 18 */
  uint8_t strike_price[4];                 /* bytes 19 to 22 */
  uint8_t volume[4];                       /* bytes 23 to 26 */
  uint8_t premium_price_denominator_code;  /* byte 27 */
  uint8_t premium_price[4];                /* bytes 28 to 31 */
  uint8_t trade_identifier[4];             /* bytes 32 to 35 */
  uint8_t reserved_4[4];                   /* bytes 36 to 39 */
} EquityAndIndexLastSaleMessage;

/* any Equity And Index Last Sale Message at all: every byte one the checker chooses */
static void any_equity_and_index_last_sale_message(EquityAndIndexLastSaleMessage *record) {
  record->message_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transaction_id[i] = arbitrary(); }
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

/* Equity And Index Last Sale Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_equity_and_index_last_sale_message(const EquityAndIndexLastSaleMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_id[i]; }
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

/* Equity And Index Last Sale Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_equity_and_index_last_sale_message(EquityAndIndexLastSaleMessage *record, const uint8_t *wire, size_t at) {
  record->message_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transaction_id[i] = wire[at++]; }
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
  assert(read->message_indicator == written->message_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
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
  uint8_t wire[40];
  uint8_t again[40];

  any_equity_and_index_last_sale_message(&sent);
  assert(encode_equity_and_index_last_sale_message(&sent, wire, 0) == 40);
  assert(decode_equity_and_index_last_sale_message(&got, wire, 0) == 40);
  equal_equity_and_index_last_sale_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_equity_and_index_last_sale_message(&got, wire, 0) == 40);
  assert(encode_equity_and_index_last_sale_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Interest Message: 27 bytes ----------------------------------------- */

/* The Open Interest message is used to report contract volume on current options that have not been exercised and have not yet reached expiration. */
typedef struct {
  uint8_t message_indicator;              /* byte 0 */
  uint8_t transaction_id[8];              /* bytes 1 to 8 */
  uint8_t security_symbol[5];             /* bytes 9 to 13 */
  uint8_t reserved_1;                     /* byte 14 */
  ExpirationBlock expiration_block;       /* bytes 15 to 17 */
  uint8_t strike_price_denominator_code;  /* byte 18 */
  uint8_t strike_price[4];                /* bytes 19 to 22 */
  uint8_t open_interest_volume[4];        /* bytes 23 to 26 */
} OpenInterestMessage;

/* any Open Interest Message at all: every byte one the checker chooses */
static void any_open_interest_message(OpenInterestMessage *record) {
  record->message_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  any_expiration_block(&record->expiration_block);
  record->strike_price_denominator_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_interest_volume[i] = arbitrary(); }
}

/* Open Interest Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_open_interest_message(const OpenInterestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->reserved_1;
  at = encode_expiration_block(&record->expiration_block, wire, at);
  wire[at++] = record->strike_price_denominator_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_interest_volume[i]; }

  return at;
}

/* Open Interest Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_open_interest_message(OpenInterestMessage *record, const uint8_t *wire, size_t at) {
  record->message_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  at = decode_expiration_block(&record->expiration_block, wire, at);
  record->strike_price_denominator_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_interest_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Open Interest Message is what was written, byte for byte */
static void equal_open_interest_message(const OpenInterestMessage *read, const OpenInterestMessage *written) {
  assert(read->message_indicator == written->message_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->reserved_1 == written->reserved_1);
  equal_expiration_block(&read->expiration_block, &written->expiration_block);
  assert(read->strike_price_denominator_code == written->strike_price_denominator_code);
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_interest_volume[i] == written->open_interest_volume[i]); }
}

/* Open Interest Message: written and read back, then read and written back */
static void check_open_interest_message(void) {
  OpenInterestMessage sent;
  OpenInterestMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_open_interest_message(&sent);
  assert(encode_open_interest_message(&sent, wire, 0) == 27);
  assert(decode_open_interest_message(&got, wire, 0) == 27);
  equal_open_interest_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_open_interest_message(&got, wire, 0) == 27);
  assert(encode_open_interest_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Equity And Index End Of Day Summary Message: 69 bytes ------------------- */

/* The Equity and Index End of Day Summary messages are transmitted shortly before the Good Night messages. */
typedef struct {
  uint8_t message_indicator;                  /* byte 0 */
  uint8_t transaction_id[8];                  /* bytes 1 to 8 */
  uint8_t security_symbol[5];                 /* bytes 9 to 13 */
  uint8_t reserved_1;                         /* byte 14 */
  ExpirationBlock expiration_block;           /* bytes 15 to 17 */
  uint8_t strike_price_denominator_code;      /* byte 18 */
  uint8_t strike_price[4];                    /* bytes 19 to 22 */
  uint8_t volume[4];                          /* bytes 23 to 26 */
  uint8_t open_interest_volume[4];            /* bytes 27 to 30 */
  uint8_t premium_price_denominator_code;     /* byte 31 */
  uint8_t open_price[4];                      /* bytes 32 to 35 */
  uint8_t high_price[4];                      /* bytes 36 to 39 */
  uint8_t low_price[4];                       /* bytes 40 to 43 */
  uint8_t last_price[4];                      /* bytes 44 to 47 */
  uint8_t net_change[4];                      /* bytes 48 to 51 */
  uint8_t underlying_price_denominator_code;  /* byte 52 */
  uint8_t underlying_price[8];                /* bytes 53 to 60 */
  uint8_t bid_price[4];                       /* bytes 61 to 64 */
  uint8_t offer_price[4];                     /* bytes 65 to 68 */
} EquityAndIndexEndOfDaySummaryMessage;

/* any Equity And Index End Of Day Summary Message at all: every byte one the checker chooses */
static void any_equity_and_index_end_of_day_summary_message(EquityAndIndexEndOfDaySummaryMessage *record) {
  record->message_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transaction_id[i] = arbitrary(); }
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

/* Equity And Index End Of Day Summary Message to the wire: 69 bytes from at, returning where the next byte goes */
static size_t encode_equity_and_index_end_of_day_summary_message(const EquityAndIndexEndOfDaySummaryMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_id[i]; }
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

/* Equity And Index End Of Day Summary Message off the wire: 69 bytes from at, returning where the next byte lies */
static size_t decode_equity_and_index_end_of_day_summary_message(EquityAndIndexEndOfDaySummaryMessage *record, const uint8_t *wire, size_t at) {
  record->message_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transaction_id[i] = wire[at++]; }
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
  assert(read->message_indicator == written->message_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
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
  uint8_t wire[69];
  uint8_t again[69];

  any_equity_and_index_end_of_day_summary_message(&sent);
  assert(encode_equity_and_index_end_of_day_summary_message(&sent, wire, 0) == 69);
  assert(decode_equity_and_index_end_of_day_summary_message(&got, wire, 0) == 69);
  equal_equity_and_index_end_of_day_summary_message(&got, &sent);

  for (size_t i = 0; i < 69; i++) { wire[i] = arbitrary(); }
  assert(decode_equity_and_index_end_of_day_summary_message(&got, wire, 0) == 69);
  assert(encode_equity_and_index_end_of_day_summary_message(&got, again, 0) == 69);
  for (size_t i = 0; i < 69; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Value Last Sale Message: 24 bytes ---------------------------- */

/* Underlying Value last sale Message */
typedef struct {
  uint8_t message_indicator;             /* byte 0 */
  uint8_t transaction_id[8];             /* bytes 1 to 8 */
  uint8_t security_symbol[5];            /* bytes 9 to 13 */
  uint8_t reserved_1;                    /* byte 14 */
  uint8_t index_value_denominator_code;  /* byte 15 */
  uint8_t index_value[4];                /* bytes 16 to 19 */
  uint8_t reserved_4[4];                 /* bytes 20 to 23 */
} UnderlyingValueLastSaleMessage;

/* any Underlying Value Last Sale Message at all: every byte one the checker chooses */
static void any_underlying_value_last_sale_message(UnderlyingValueLastSaleMessage *record) {
  record->message_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->index_value_denominator_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->index_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Underlying Value Last Sale Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_underlying_value_last_sale_message(const UnderlyingValueLastSaleMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->index_value_denominator_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Underlying Value Last Sale Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_underlying_value_last_sale_message(UnderlyingValueLastSaleMessage *record, const uint8_t *wire, size_t at) {
  record->message_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->index_value_denominator_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->index_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Underlying Value Last Sale Message is what was written, byte for byte */
static void equal_underlying_value_last_sale_message(const UnderlyingValueLastSaleMessage *read, const UnderlyingValueLastSaleMessage *written) {
  assert(read->message_indicator == written->message_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
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
  uint8_t wire[24];
  uint8_t again[24];

  any_underlying_value_last_sale_message(&sent);
  assert(encode_underlying_value_last_sale_message(&sent, wire, 0) == 24);
  assert(decode_underlying_value_last_sale_message(&got, wire, 0) == 24);
  equal_underlying_value_last_sale_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_value_last_sale_message(&got, wire, 0) == 24);
  assert(encode_underlying_value_last_sale_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Value Bid And Offer Message: 28 bytes ------------------------ */

/* Underlying value bid and offer message */
typedef struct {
  uint8_t message_indicator;             /* byte 0 */
  uint8_t transaction_id[8];             /* bytes 1 to 8 */
  uint8_t security_symbol[5];            /* bytes 9 to 13 */
  uint8_t reserved_1;                    /* byte 14 */
  uint8_t index_value_denominator_code;  /* byte 15 */
  uint8_t bid_index_value[4];            /* bytes 16 to 19 */
  uint8_t offer_index_value[8];          /* bytes 20 to 27 */
} UnderlyingValueBidAndOfferMessage;

/* any Underlying Value Bid And Offer Message at all: every byte one the checker chooses */
static void any_underlying_value_bid_and_offer_message(UnderlyingValueBidAndOfferMessage *record) {
  record->message_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->index_value_denominator_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->bid_index_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_index_value[i] = arbitrary(); }
}

/* Underlying Value Bid And Offer Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_underlying_value_bid_and_offer_message(const UnderlyingValueBidAndOfferMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->index_value_denominator_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_index_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_index_value[i]; }

  return at;
}

/* Underlying Value Bid And Offer Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_underlying_value_bid_and_offer_message(UnderlyingValueBidAndOfferMessage *record, const uint8_t *wire, size_t at) {
  record->message_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->security_symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->index_value_denominator_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->bid_index_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_index_value[i] = wire[at++]; }

  return at;
}

/* what was read of Underlying Value Bid And Offer Message is what was written, byte for byte */
static void equal_underlying_value_bid_and_offer_message(const UnderlyingValueBidAndOfferMessage *read, const UnderlyingValueBidAndOfferMessage *written) {
  assert(read->message_indicator == written->message_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->reserved_1 == written->reserved_1);
  assert(read->index_value_denominator_code == written->index_value_denominator_code);
  for (size_t i = 0; i < 4; i++) { assert(read->bid_index_value[i] == written->bid_index_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_index_value[i] == written->offer_index_value[i]); }
}

/* Underlying Value Bid And Offer Message: written and read back, then read and written back */
static void check_underlying_value_bid_and_offer_message(void) {
  UnderlyingValueBidAndOfferMessage sent;
  UnderlyingValueBidAndOfferMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_underlying_value_bid_and_offer_message(&sent);
  assert(encode_underlying_value_bid_and_offer_message(&sent, wire, 0) == 28);
  assert(decode_underlying_value_bid_and_offer_message(&got, wire, 0) == 28);
  equal_underlying_value_bid_and_offer_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_value_bid_and_offer_message(&got, wire, 0) == 28);
  assert(encode_underlying_value_bid_and_offer_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_block_timestamp();
  check_block_header();
  check_message_header();
  check_expiration_block();
  check_equity_and_index_last_sale_message();
  check_open_interest_message();
  check_equity_and_index_end_of_day_summary_message();
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
