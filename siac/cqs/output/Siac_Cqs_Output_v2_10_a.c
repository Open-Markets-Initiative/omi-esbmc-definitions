// siac/cqs/output/Siac_Cqs_Output_v2_10_a.c
/*
 * The Securities Industry Automation Corporation
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
 *   - a Checksum rule
 *   - a run counted by a field
 *   - the dispatch that chooses a message by its type
 *   - a field present only on a condition
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

/* ---- SIP Block Timestamp: 8 bytes -------------------------------------------- */

/* Cta packet timestamp */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} SIPBlockTimestamp;

/* any SIP Block Timestamp at all: every byte one the checker chooses */
static void any_s_i_p_block_timestamp(SIPBlockTimestamp *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* SIP Block Timestamp to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_s_i_p_block_timestamp(const SIPBlockTimestamp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* SIP Block Timestamp off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_s_i_p_block_timestamp(SIPBlockTimestamp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of SIP Block Timestamp is what was written, byte for byte */
static void equal_s_i_p_block_timestamp(const SIPBlockTimestamp *read, const SIPBlockTimestamp *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* SIP Block Timestamp: written and read back, then read and written back */
static void check_s_i_p_block_timestamp(void) {
  SIPBlockTimestamp sent;
  SIPBlockTimestamp got;
  uint8_t wire[8];
  uint8_t again[8];

  any_s_i_p_block_timestamp(&sent);
  assert(encode_s_i_p_block_timestamp(&sent, wire, 0) == 8);
  assert(decode_s_i_p_block_timestamp(&got, wire, 0) == 8);
  equal_s_i_p_block_timestamp(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_s_i_p_block_timestamp(&got, wire, 0) == 8);
  assert(encode_s_i_p_block_timestamp(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Timestamp 1: 8 bytes ---------------------------------------------------- */

/* Timestamp 1 */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} Timestamp1;

/* any Timestamp 1 at all: every byte one the checker chooses */
static void any_timestamp1(Timestamp1 *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Timestamp 1 to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_timestamp1(const Timestamp1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Timestamp 1 off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_timestamp1(Timestamp1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Timestamp 1 is what was written, byte for byte */
static void equal_timestamp1(const Timestamp1 *read, const Timestamp1 *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Timestamp 1: written and read back, then read and written back */
static void check_timestamp1(void) {
  Timestamp1 sent;
  Timestamp1 got;
  uint8_t wire[8];
  uint8_t again[8];

  any_timestamp1(&sent);
  assert(encode_timestamp1(&sent, wire, 0) == 8);
  assert(decode_timestamp1(&got, wire, 0) == 8);
  equal_timestamp1(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_timestamp1(&got, wire, 0) == 8);
  assert(encode_timestamp1(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Reference Data Message: 205 bytes -------------------------------- */

/* Symbol Reference Data Message */
typedef struct {
  uint8_t participant_id;                                    /* byte 0 */
  Timestamp1 timestamp_1;                                    /* bytes 1 to 8 */
  uint8_t message_id;                                        /* byte 9 */
  uint8_t transaction_id[4];                                 /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];                   /* bytes 14 to 21 */
  uint8_t security_symbol[11];                               /* bytes 22 to 32 */
  uint8_t prior_security_symbol[11];                         /* bytes 33 to 43 */
  uint8_t primary_listing_market_participant_id;             /* byte 44 */
  uint8_t primary_listing_market_previous_closing_price[8];  /* bytes 45 to 52 */
  uint8_t consolidated_closing_price[8];                     /* bytes 53 to 60 */
  uint8_t round_lot_size[2];                                 /* bytes 61 to 62 */
  uint8_t reserved;                                          /* byte 63 */
  uint8_t luld_tier;                                         /* byte 64 */
  uint8_t luld_leverage_ratio[4];                            /* bytes 65 to 68 */
  uint8_t test;                                              /* byte 69 */
  uint8_t ipo;                                               /* byte 70 */
  uint8_t financial_status_indicator;                        /* byte 71 */
  uint8_t short_sale_restriction_indicator;                  /* byte 72 */
  uint8_t halt_reason;                                       /* byte 73 */
  uint8_t instrument_type;                                   /* byte 74 */
  uint8_t second_reserved;                                   /* byte 75 */
  uint8_t third_reserved;                                    /* byte 76 */
  uint8_t reserved_128[128];                                 /* bytes 77 to 204 */
} SymbolReferenceDataMessage;

/* any Symbol Reference Data Message at all: every byte one the checker chooses */
static void any_symbol_reference_data_message(SymbolReferenceDataMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->prior_security_symbol[i] = arbitrary(); }
  record->primary_listing_market_participant_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->primary_listing_market_previous_closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->consolidated_closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->round_lot_size[i] = arbitrary(); }
  record->reserved = arbitrary();
  record->luld_tier = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->luld_leverage_ratio[i] = arbitrary(); }
  record->test = arbitrary();
  record->ipo = arbitrary();
  record->financial_status_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  record->halt_reason = arbitrary();
  record->instrument_type = arbitrary();
  record->second_reserved = arbitrary();
  record->third_reserved = arbitrary();
  for (size_t i = 0; i < 128; i++) { record->reserved_128[i] = arbitrary(); }
}

/* Symbol Reference Data Message to the wire: 205 bytes from at, returning where the next byte goes */
static size_t encode_symbol_reference_data_message(const SymbolReferenceDataMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->prior_security_symbol[i]; }
  wire[at++] = record->primary_listing_market_participant_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->primary_listing_market_previous_closing_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->consolidated_closing_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->round_lot_size[i]; }
  wire[at++] = record->reserved;
  wire[at++] = record->luld_tier;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->luld_leverage_ratio[i]; }
  wire[at++] = record->test;
  wire[at++] = record->ipo;
  wire[at++] = record->financial_status_indicator;
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->halt_reason;
  wire[at++] = record->instrument_type;
  wire[at++] = record->second_reserved;
  wire[at++] = record->third_reserved;
  for (size_t i = 0; i < 128; i++) { wire[at++] = record->reserved_128[i]; }

  return at;
}

/* Symbol Reference Data Message off the wire: 205 bytes from at, returning where the next byte lies */
static size_t decode_symbol_reference_data_message(SymbolReferenceDataMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->prior_security_symbol[i] = wire[at++]; }
  record->primary_listing_market_participant_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->primary_listing_market_previous_closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->consolidated_closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->round_lot_size[i] = wire[at++]; }
  record->reserved = wire[at++];
  record->luld_tier = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->luld_leverage_ratio[i] = wire[at++]; }
  record->test = wire[at++];
  record->ipo = wire[at++];
  record->financial_status_indicator = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  record->halt_reason = wire[at++];
  record->instrument_type = wire[at++];
  record->second_reserved = wire[at++];
  record->third_reserved = wire[at++];
  for (size_t i = 0; i < 128; i++) { record->reserved_128[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Reference Data Message is what was written, byte for byte */
static void equal_symbol_reference_data_message(const SymbolReferenceDataMessage *read, const SymbolReferenceDataMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->prior_security_symbol[i] == written->prior_security_symbol[i]); }
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  for (size_t i = 0; i < 8; i++) { assert(read->primary_listing_market_previous_closing_price[i] == written->primary_listing_market_previous_closing_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->consolidated_closing_price[i] == written->consolidated_closing_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->round_lot_size[i] == written->round_lot_size[i]); }
  assert(read->reserved == written->reserved);
  assert(read->luld_tier == written->luld_tier);
  for (size_t i = 0; i < 4; i++) { assert(read->luld_leverage_ratio[i] == written->luld_leverage_ratio[i]); }
  assert(read->test == written->test);
  assert(read->ipo == written->ipo);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->halt_reason == written->halt_reason);
  assert(read->instrument_type == written->instrument_type);
  assert(read->second_reserved == written->second_reserved);
  assert(read->third_reserved == written->third_reserved);
  for (size_t i = 0; i < 128; i++) { assert(read->reserved_128[i] == written->reserved_128[i]); }
}

/* Symbol Reference Data Message: written and read back, then read and written back */
static void check_symbol_reference_data_message(void) {
  SymbolReferenceDataMessage sent;
  SymbolReferenceDataMessage got;
  uint8_t wire[205];
  uint8_t again[205];

  any_symbol_reference_data_message(&sent);
  assert(encode_symbol_reference_data_message(&sent, wire, 0) == 205);
  assert(decode_symbol_reference_data_message(&got, wire, 0) == 205);
  equal_symbol_reference_data_message(&got, &sent);

  for (size_t i = 0; i < 205; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_reference_data_message(&got, wire, 0) == 205);
  assert(encode_symbol_reference_data_message(&got, again, 0) == 205);
  for (size_t i = 0; i < 205; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Of Day Message: 22 bytes ------------------------------------------ */

/* Start of Day Message */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} StartOfDayMessage;

/* any Start Of Day Message at all: every byte one the checker chooses */
static void any_start_of_day_message(StartOfDayMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Start Of Day Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_start_of_day_message(const StartOfDayMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Start Of Day Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_start_of_day_message(StartOfDayMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Start Of Day Message is what was written, byte for byte */
static void equal_start_of_day_message(const StartOfDayMessage *read, const StartOfDayMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Start Of Day Message: written and read back, then read and written back */
static void check_start_of_day_message(void) {
  StartOfDayMessage sent;
  StartOfDayMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_start_of_day_message(&sent);
  assert(encode_start_of_day_message(&sent, wire, 0) == 22);
  assert(decode_start_of_day_message(&got, wire, 0) == 22);
  equal_start_of_day_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_start_of_day_message(&got, wire, 0) == 22);
  assert(encode_start_of_day_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Finra Close Message: 22 bytes ------------------------------------------- */

/* FINRA Close Message */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} FinraCloseMessage;

/* any Finra Close Message at all: every byte one the checker chooses */
static void any_finra_close_message(FinraCloseMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Finra Close Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_finra_close_message(const FinraCloseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Finra Close Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_finra_close_message(FinraCloseMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Finra Close Message is what was written, byte for byte */
static void equal_finra_close_message(const FinraCloseMessage *read, const FinraCloseMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Finra Close Message: written and read back, then read and written back */
static void check_finra_close_message(void) {
  FinraCloseMessage sent;
  FinraCloseMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_finra_close_message(&sent);
  assert(encode_finra_close_message(&sent, wire, 0) == 22);
  assert(decode_finra_close_message(&got, wire, 0) == 22);
  equal_finra_close_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_finra_close_message(&got, wire, 0) == 22);
  assert(encode_finra_close_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reset Block Sequence Number Message: 22 bytes --------------------------- */

/* Reset Block Sequence Number Message */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} ResetBlockSequenceNumberMessage;

/* any Reset Block Sequence Number Message at all: every byte one the checker chooses */
static void any_reset_block_sequence_number_message(ResetBlockSequenceNumberMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Reset Block Sequence Number Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_reset_block_sequence_number_message(const ResetBlockSequenceNumberMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Reset Block Sequence Number Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_reset_block_sequence_number_message(ResetBlockSequenceNumberMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Reset Block Sequence Number Message is what was written, byte for byte */
static void equal_reset_block_sequence_number_message(const ResetBlockSequenceNumberMessage *read, const ResetBlockSequenceNumberMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Reset Block Sequence Number Message: written and read back, then read and written back */
static void check_reset_block_sequence_number_message(void) {
  ResetBlockSequenceNumberMessage sent;
  ResetBlockSequenceNumberMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_reset_block_sequence_number_message(&sent);
  assert(encode_reset_block_sequence_number_message(&sent, wire, 0) == 22);
  assert(decode_reset_block_sequence_number_message(&got, wire, 0) == 22);
  equal_reset_block_sequence_number_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_reset_block_sequence_number_message(&got, wire, 0) == 22);
  assert(encode_reset_block_sequence_number_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Finra Open Message: 22 bytes -------------------------------------------- */

/* FINRA Open Message */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} FinraOpenMessage;

/* any Finra Open Message at all: every byte one the checker chooses */
static void any_finra_open_message(FinraOpenMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Finra Open Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_finra_open_message(const FinraOpenMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Finra Open Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_finra_open_message(FinraOpenMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Finra Open Message is what was written, byte for byte */
static void equal_finra_open_message(const FinraOpenMessage *read, const FinraOpenMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Finra Open Message: written and read back, then read and written back */
static void check_finra_open_message(void) {
  FinraOpenMessage sent;
  FinraOpenMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_finra_open_message(&sent);
  assert(encode_finra_open_message(&sent, wire, 0) == 22);
  assert(decode_finra_open_message(&got, wire, 0) == 22);
  equal_finra_open_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_finra_open_message(&got, wire, 0) == 22);
  assert(encode_finra_open_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Disaster Recovery Data Center Activation Message: 22 bytes -------------- */

/* Disaster Recovery Data Center Activation Message */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} DisasterRecoveryDataCenterActivationMessage;

/* any Disaster Recovery Data Center Activation Message at all: every byte one the checker chooses */
static void any_disaster_recovery_data_center_activation_message(DisasterRecoveryDataCenterActivationMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Disaster Recovery Data Center Activation Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_disaster_recovery_data_center_activation_message(const DisasterRecoveryDataCenterActivationMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Disaster Recovery Data Center Activation Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_disaster_recovery_data_center_activation_message(DisasterRecoveryDataCenterActivationMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Disaster Recovery Data Center Activation Message is what was written, byte for byte */
static void equal_disaster_recovery_data_center_activation_message(const DisasterRecoveryDataCenterActivationMessage *read, const DisasterRecoveryDataCenterActivationMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Disaster Recovery Data Center Activation Message: written and read back, then read and written back */
static void check_disaster_recovery_data_center_activation_message(void) {
  DisasterRecoveryDataCenterActivationMessage sent;
  DisasterRecoveryDataCenterActivationMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_disaster_recovery_data_center_activation_message(&sent);
  assert(encode_disaster_recovery_data_center_activation_message(&sent, wire, 0) == 22);
  assert(decode_disaster_recovery_data_center_activation_message(&got, wire, 0) == 22);
  equal_disaster_recovery_data_center_activation_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_disaster_recovery_data_center_activation_message(&got, wire, 0) == 22);
  assert(encode_disaster_recovery_data_center_activation_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Line Integrity Message: 22 bytes ---------------------------------------- */

/* Line Integrity Message */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} LineIntegrityMessage;

/* any Line Integrity Message at all: every byte one the checker chooses */
static void any_line_integrity_message(LineIntegrityMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* Line Integrity Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_line_integrity_message(const LineIntegrityMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* Line Integrity Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_line_integrity_message(LineIntegrityMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Line Integrity Message is what was written, byte for byte */
static void equal_line_integrity_message(const LineIntegrityMessage *read, const LineIntegrityMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* Line Integrity Message: written and read back, then read and written back */
static void check_line_integrity_message(void) {
  LineIntegrityMessage sent;
  LineIntegrityMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_line_integrity_message(&sent);
  assert(encode_line_integrity_message(&sent, wire, 0) == 22);
  assert(decode_line_integrity_message(&got, wire, 0) == 22);
  equal_line_integrity_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_line_integrity_message(&got, wire, 0) == 22);
  assert(encode_line_integrity_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Day Message: 22 bytes -------------------------------------------- */

/* End of Day Message */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
} EndOfDayMessage;

/* any End Of Day Message at all: every byte one the checker chooses */
static void any_end_of_day_message(EndOfDayMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
}

/* End Of Day Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_end_of_day_message(const EndOfDayMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }

  return at;
}

/* End Of Day Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_end_of_day_message(EndOfDayMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Day Message is what was written, byte for byte */
static void equal_end_of_day_message(const EndOfDayMessage *read, const EndOfDayMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
}

/* End Of Day Message: written and read back, then read and written back */
static void check_end_of_day_message(void) {
  EndOfDayMessage sent;
  EndOfDayMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_end_of_day_message(&sent);
  assert(encode_end_of_day_message(&sent, wire, 0) == 22);
  assert(decode_end_of_day_message(&got, wire, 0) == 22);
  equal_end_of_day_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_day_message(&got, wire, 0) == 22);
  assert(encode_end_of_day_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Wide Circuit Breaker Decline Level Status Message: 47 bytes ------ */

/* Reports the calculated Level 1, Level 2 and Level 3 threshold values for the current trading day necessary to trigger a circuit breaker */
typedef struct {
  uint8_t participant_id;                   /* byte 0 */
  Timestamp1 timestamp_1;                   /* bytes 1 to 8 */
  uint8_t message_id;                       /* byte 9 */
  uint8_t transaction_id[4];                /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];  /* bytes 14 to 21 */
  uint8_t mwcb_level_1[8];                  /* bytes 22 to 29 */
  uint8_t mwcb_level_2[8];                  /* bytes 30 to 37 */
  uint8_t mwcb_level_3[8];                  /* bytes 38 to 45 */
  uint8_t reserved;                         /* byte 46 */
} MarketWideCircuitBreakerDeclineLevelStatusMessage;

/* any Market Wide Circuit Breaker Decline Level Status Message at all: every byte one the checker chooses */
static void any_market_wide_circuit_breaker_decline_level_status_message(MarketWideCircuitBreakerDeclineLevelStatusMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_3[i] = arbitrary(); }
  record->reserved = arbitrary();
}

/* Market Wide Circuit Breaker Decline Level Status Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_market_wide_circuit_breaker_decline_level_status_message(const MarketWideCircuitBreakerDeclineLevelStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_3[i]; }
  wire[at++] = record->reserved;

  return at;
}

/* Market Wide Circuit Breaker Decline Level Status Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_market_wide_circuit_breaker_decline_level_status_message(MarketWideCircuitBreakerDeclineLevelStatusMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_3[i] = wire[at++]; }
  record->reserved = wire[at++];

  return at;
}

/* what was read of Market Wide Circuit Breaker Decline Level Status Message is what was written, byte for byte */
static void equal_market_wide_circuit_breaker_decline_level_status_message(const MarketWideCircuitBreakerDeclineLevelStatusMessage *read, const MarketWideCircuitBreakerDeclineLevelStatusMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_1[i] == written->mwcb_level_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_2[i] == written->mwcb_level_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_3[i] == written->mwcb_level_3[i]); }
  assert(read->reserved == written->reserved);
}

/* Market Wide Circuit Breaker Decline Level Status Message: written and read back, then read and written back */
static void check_market_wide_circuit_breaker_decline_level_status_message(void) {
  MarketWideCircuitBreakerDeclineLevelStatusMessage sent;
  MarketWideCircuitBreakerDeclineLevelStatusMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_market_wide_circuit_breaker_decline_level_status_message(&sent);
  assert(encode_market_wide_circuit_breaker_decline_level_status_message(&sent, wire, 0) == 47);
  assert(decode_market_wide_circuit_breaker_decline_level_status_message(&got, wire, 0) == 47);
  equal_market_wide_circuit_breaker_decline_level_status_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_market_wide_circuit_breaker_decline_level_status_message(&got, wire, 0) == 47);
  assert(encode_market_wide_circuit_breaker_decline_level_status_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Wide Circuit Breaker Status Message: 24 bytes -------------------- */

/* Reports the Market-Wide Circuit Breaker threshold Level that has been breached */
typedef struct {
  uint8_t participant_id;                               /* byte 0 */
  Timestamp1 timestamp_1;                               /* bytes 1 to 8 */
  uint8_t message_id;                                   /* byte 9 */
  uint8_t transaction_id[4];                            /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];              /* bytes 14 to 21 */
  uint8_t market_wide_circuit_breaker_level_indicator;  /* byte 22 */
  uint8_t reserved;                                     /* byte 23 */
} MarketWideCircuitBreakerStatusMessage;

/* any Market Wide Circuit Breaker Status Message at all: every byte one the checker chooses */
static void any_market_wide_circuit_breaker_status_message(MarketWideCircuitBreakerStatusMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  record->market_wide_circuit_breaker_level_indicator = arbitrary();
  record->reserved = arbitrary();
}

/* Market Wide Circuit Breaker Status Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_market_wide_circuit_breaker_status_message(const MarketWideCircuitBreakerStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  wire[at++] = record->market_wide_circuit_breaker_level_indicator;
  wire[at++] = record->reserved;

  return at;
}

/* Market Wide Circuit Breaker Status Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_market_wide_circuit_breaker_status_message(MarketWideCircuitBreakerStatusMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  record->market_wide_circuit_breaker_level_indicator = wire[at++];
  record->reserved = wire[at++];

  return at;
}

/* what was read of Market Wide Circuit Breaker Status Message is what was written, byte for byte */
static void equal_market_wide_circuit_breaker_status_message(const MarketWideCircuitBreakerStatusMessage *read, const MarketWideCircuitBreakerStatusMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  assert(read->market_wide_circuit_breaker_level_indicator == written->market_wide_circuit_breaker_level_indicator);
  assert(read->reserved == written->reserved);
}

/* Market Wide Circuit Breaker Status Message: written and read back, then read and written back */
static void check_market_wide_circuit_breaker_status_message(void) {
  MarketWideCircuitBreakerStatusMessage sent;
  MarketWideCircuitBreakerStatusMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_market_wide_circuit_breaker_status_message(&sent);
  assert(encode_market_wide_circuit_breaker_status_message(&sent, wire, 0) == 24);
  assert(decode_market_wide_circuit_breaker_status_message(&got, wire, 0) == 24);
  equal_market_wide_circuit_breaker_status_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_market_wide_circuit_breaker_status_message(&got, wire, 0) == 24);
  assert(encode_market_wide_circuit_breaker_status_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Status Message: 124 bytes --------------------------------------- */

/* Used when a Participant in a CTA eligible security, Local Issue or Bonds reports requires Auction Information */
typedef struct {
  uint8_t participant_id;                           /* byte 0 */
  Timestamp1 timestamp_1;                           /* bytes 1 to 8 */
  uint8_t message_id;                               /* byte 9 */
  uint8_t transaction_id[4];                        /* bytes 10 to 13 */
  uint8_t participant_reference_number[8];          /* bytes 14 to 21 */
  uint8_t security_symbol[11];                      /* bytes 22 to 32 */
  uint8_t instrument_type;                          /* byte 33 */
  uint8_t auction_collar_reference_price[8];        /* bytes 34 to 41 */
  uint8_t auction_collar_upper_threshold_price[8];  /* bytes 42 to 49 */
  uint8_t auction_collar_lower_threshold_price[8];  /* bytes 50 to 57 */
  uint8_t number_of_extensions;                     /* byte 58 */
  uint8_t short_sale_restriction_indicator;         /* byte 59 */
  uint8_t primary_listing_market_participant_id;    /* byte 60 */
  uint8_t financial_status_indicator;               /* byte 61 */
  uint8_t reserved_62[62];                          /* bytes 62 to 123 */
} AuctionStatusMessage;

/* any Auction Status Message at all: every byte one the checker chooses */
static void any_auction_status_message(AuctionStatusMessage *record) {
  record->participant_id = arbitrary();
  any_timestamp1(&record->timestamp_1);
  record->message_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_collar_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_upper_threshold_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_lower_threshold_price[i] = arbitrary(); }
  record->number_of_extensions = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  record->primary_listing_market_participant_id = arbitrary();
  record->financial_status_indicator = arbitrary();
  for (size_t i = 0; i < 62; i++) { record->reserved_62[i] = arbitrary(); }
}

/* Auction Status Message to the wire: 124 bytes from at, returning where the next byte goes */
static size_t encode_auction_status_message(const AuctionStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  at = encode_timestamp1(&record->timestamp_1, wire, at);
  wire[at++] = record->message_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->participant_reference_number[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_upper_threshold_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_lower_threshold_price[i]; }
  wire[at++] = record->number_of_extensions;
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->financial_status_indicator;
  for (size_t i = 0; i < 62; i++) { wire[at++] = record->reserved_62[i]; }

  return at;
}

/* Auction Status Message off the wire: 124 bytes from at, returning where the next byte lies */
static size_t decode_auction_status_message(AuctionStatusMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  at = decode_timestamp1(&record->timestamp_1, wire, at);
  record->message_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->participant_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_collar_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_upper_threshold_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_lower_threshold_price[i] = wire[at++]; }
  record->number_of_extensions = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  record->primary_listing_market_participant_id = wire[at++];
  record->financial_status_indicator = wire[at++];
  for (size_t i = 0; i < 62; i++) { record->reserved_62[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Status Message is what was written, byte for byte */
static void equal_auction_status_message(const AuctionStatusMessage *read, const AuctionStatusMessage *written) {
  assert(read->participant_id == written->participant_id);
  equal_timestamp1(&read->timestamp_1, &written->timestamp_1);
  assert(read->message_id == written->message_id);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->participant_reference_number[i] == written->participant_reference_number[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_reference_price[i] == written->auction_collar_reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_upper_threshold_price[i] == written->auction_collar_upper_threshold_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_lower_threshold_price[i] == written->auction_collar_lower_threshold_price[i]); }
  assert(read->number_of_extensions == written->number_of_extensions);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  for (size_t i = 0; i < 62; i++) { assert(read->reserved_62[i] == written->reserved_62[i]); }
}

/* Auction Status Message: written and read back, then read and written back */
static void check_auction_status_message(void) {
  AuctionStatusMessage sent;
  AuctionStatusMessage got;
  uint8_t wire[124];
  uint8_t again[124];

  any_auction_status_message(&sent);
  assert(encode_auction_status_message(&sent, wire, 0) == 124);
  assert(decode_auction_status_message(&got, wire, 0) == 124);
  equal_auction_status_message(&got, &sent);

  for (size_t i = 0; i < 124; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_status_message(&got, wire, 0) == 124);
  assert(encode_auction_status_message(&got, again, 0) == 124);
  for (size_t i = 0; i < 124; i++) { assert(again[i] == wire[i]); }
}

/* ---- Timestamp 2: 8 bytes ---------------------------------------------------- */

/* Timestamp 2 */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} Timestamp2;

/* any Timestamp 2 at all: every byte one the checker chooses */
static void any_timestamp2(Timestamp2 *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Timestamp 2 to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_timestamp2(const Timestamp2 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Timestamp 2 off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_timestamp2(Timestamp2 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Timestamp 2 is what was written, byte for byte */
static void equal_timestamp2(const Timestamp2 *read, const Timestamp2 *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Timestamp 2: written and read back, then read and written back */
static void check_timestamp2(void) {
  Timestamp2 sent;
  Timestamp2 got;
  uint8_t wire[8];
  uint8_t again[8];

  any_timestamp2(&sent);
  assert(encode_timestamp2(&sent, wire, 0) == 8);
  assert(decode_timestamp2(&got, wire, 0) == 8);
  equal_timestamp2(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_timestamp2(&got, wire, 0) == 8);
  assert(encode_timestamp2(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_s_i_p_block_timestamp();
  check_timestamp1();
  check_symbol_reference_data_message();
  check_start_of_day_message();
  check_finra_close_message();
  check_reset_block_sequence_number_message();
  check_finra_open_message();
  check_disaster_recovery_data_center_activation_message();
  check_line_integrity_message();
  check_end_of_day_message();
  check_market_wide_circuit_breaker_decline_level_status_message();
  check_market_wide_circuit_breaker_status_message();
  check_auction_status_message();
  check_timestamp2();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
