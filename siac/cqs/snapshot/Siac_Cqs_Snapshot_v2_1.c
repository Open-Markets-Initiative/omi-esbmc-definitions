// siac/cqs/snapshot/Siac_Cqs_Snapshot_v2_1.c
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
 *   - a Integrity rule
 *   - a run counted by a field
 *   - the dispatch that chooses a message by its type
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

/* ---- Sip Block Timestamp: 8 bytes -------------------------------------------- */

/* Cqs packet timestamp */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} SipBlockTimestamp;

/* any Sip Block Timestamp at all: every byte one the checker chooses */
static void any_sip_block_timestamp(SipBlockTimestamp *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Sip Block Timestamp to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_sip_block_timestamp(const SipBlockTimestamp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Sip Block Timestamp off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_sip_block_timestamp(SipBlockTimestamp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Sip Block Timestamp is what was written, byte for byte */
static void equal_sip_block_timestamp(const SipBlockTimestamp *read, const SipBlockTimestamp *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Sip Block Timestamp: written and read back, then read and written back */
static void check_sip_block_timestamp(void) {
  SipBlockTimestamp sent;
  SipBlockTimestamp got;
  uint8_t wire[8];
  uint8_t again[8];

  any_sip_block_timestamp(&sent);
  assert(encode_sip_block_timestamp(&sent, wire, 0) == 8);
  assert(decode_sip_block_timestamp(&got, wire, 0) == 8);
  equal_sip_block_timestamp(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_sip_block_timestamp(&got, wire, 0) == 8);
  assert(encode_sip_block_timestamp(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Line Integrity Message: 1 byte ------------------------------------------ */

/* Sent to verify continued integrity of multicast transmission */
typedef struct {
  uint8_t participant_id;  /* byte 0 */
} LineIntegrityMessage;

/* any Line Integrity Message at all: every byte one the checker chooses */
static void any_line_integrity_message(LineIntegrityMessage *record) {
  record->participant_id = arbitrary();
}

/* Line Integrity Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_line_integrity_message(const LineIntegrityMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;

  return at;
}

/* Line Integrity Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_line_integrity_message(LineIntegrityMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];

  return at;
}

/* what was read of Line Integrity Message is what was written, byte for byte */
static void equal_line_integrity_message(const LineIntegrityMessage *read, const LineIntegrityMessage *written) {
  assert(read->participant_id == written->participant_id);
}

/* Line Integrity Message: written and read back, then read and written back */
static void check_line_integrity_message(void) {
  LineIntegrityMessage sent;
  LineIntegrityMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_line_integrity_message(&sent);
  assert(encode_line_integrity_message(&sent, wire, 0) == 1);
  assert(decode_line_integrity_message(&got, wire, 0) == 1);
  equal_line_integrity_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_line_integrity_message(&got, wire, 0) == 1);
  assert(encode_line_integrity_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Reference Data Message: 57 bytes --------------------------------- */

/* Contains the latest symbol configuration details at the time Snapshot is generated */
typedef struct {
  uint8_t participant_id;                                    /* byte 0 */
  uint8_t security_symbol[11];                               /* bytes 1 to 11 */
  uint8_t prior_security_symbol[11];                         /* bytes 12 to 22 */
  uint8_t primary_listing_market_participant_id;             /* byte 23 */
  uint8_t primary_listing_market_previous_closing_price[8];  /* bytes 24 to 31 */
  uint8_t consolidated_closing_price[8];                     /* bytes 32 to 39 */
  uint8_t round_lot_size[2];                                 /* bytes 40 to 41 */
  uint8_t reserved;                                          /* byte 42 */
  uint8_t luld_tier;                                         /* byte 43 */
  uint8_t luld_leverage_ratio[4];                            /* bytes 44 to 47 */
  uint8_t test;                                              /* byte 48 */
  uint8_t ipo;                                               /* byte 49 */
  uint8_t financial_status_indicator;                        /* byte 50 */
  uint8_t short_sale_restriction_indicator;                  /* byte 51 */
  uint8_t halt_reason;                                       /* byte 52 */
  uint8_t instrument_type;                                   /* byte 53 */
  uint8_t second_reserved;                                   /* byte 54 */
  uint8_t third_reserved;                                    /* byte 55 */
  uint8_t fourth_reserved;                                   /* byte 56 */
} SymbolReferenceDataMessage;

/* any Symbol Reference Data Message at all: every byte one the checker chooses */
static void any_symbol_reference_data_message(SymbolReferenceDataMessage *record) {
  record->participant_id = arbitrary();
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
  record->fourth_reserved = arbitrary();
}

/* Symbol Reference Data Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_symbol_reference_data_message(const SymbolReferenceDataMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
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
  wire[at++] = record->fourth_reserved;

  return at;
}

/* Symbol Reference Data Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_symbol_reference_data_message(SymbolReferenceDataMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
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
  record->fourth_reserved = wire[at++];

  return at;
}

/* what was read of Symbol Reference Data Message is what was written, byte for byte */
static void equal_symbol_reference_data_message(const SymbolReferenceDataMessage *read, const SymbolReferenceDataMessage *written) {
  assert(read->participant_id == written->participant_id);
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
  assert(read->fourth_reserved == written->fourth_reserved);
}

/* Symbol Reference Data Message: written and read back, then read and written back */
static void check_symbol_reference_data_message(void) {
  SymbolReferenceDataMessage sent;
  SymbolReferenceDataMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_symbol_reference_data_message(&sent);
  assert(encode_symbol_reference_data_message(&sent, wire, 0) == 57);
  assert(decode_symbol_reference_data_message(&got, wire, 0) == 57);
  equal_symbol_reference_data_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_reference_data_message(&got, wire, 0) == 57);
  assert(encode_symbol_reference_data_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Wide Circuit Breaker Decline Level Status Snapshot Message: 26 bytes ---- */

/* Reports the calculated Level 1, Level 2 and Level 3 threshold values for the current trading day necessary to trigger a circuit breaker */
typedef struct {
  uint8_t participant_id;   /* byte 0 */
  uint8_t mwcb_level_1[8];  /* bytes 1 to 8 */
  uint8_t mwcb_level_2[8];  /* bytes 9 to 16 */
  uint8_t mwcb_level_3[8];  /* bytes 17 to 24 */
  uint8_t reserved;         /* byte 25 */
} MarketWideCircuitBreakerDeclineLevelStatusSnapshotMessage;

/* any Market Wide Circuit Breaker Decline Level Status Snapshot Message at all: every byte one the checker chooses */
static void any_market_wide_circuit_breaker_decline_level_status_snapshot_message(MarketWideCircuitBreakerDeclineLevelStatusSnapshotMessage *record) {
  record->participant_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_3[i] = arbitrary(); }
  record->reserved = arbitrary();
}

/* Market Wide Circuit Breaker Decline Level Status Snapshot Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_market_wide_circuit_breaker_decline_level_status_snapshot_message(const MarketWideCircuitBreakerDeclineLevelStatusSnapshotMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mwcb_level_3[i]; }
  wire[at++] = record->reserved;

  return at;
}

/* Market Wide Circuit Breaker Decline Level Status Snapshot Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_market_wide_circuit_breaker_decline_level_status_snapshot_message(MarketWideCircuitBreakerDeclineLevelStatusSnapshotMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mwcb_level_3[i] = wire[at++]; }
  record->reserved = wire[at++];

  return at;
}

/* what was read of Market Wide Circuit Breaker Decline Level Status Snapshot Message is what was written, byte for byte */
static void equal_market_wide_circuit_breaker_decline_level_status_snapshot_message(const MarketWideCircuitBreakerDeclineLevelStatusSnapshotMessage *read, const MarketWideCircuitBreakerDeclineLevelStatusSnapshotMessage *written) {
  assert(read->participant_id == written->participant_id);
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_1[i] == written->mwcb_level_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_2[i] == written->mwcb_level_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mwcb_level_3[i] == written->mwcb_level_3[i]); }
  assert(read->reserved == written->reserved);
}

/* Market Wide Circuit Breaker Decline Level Status Snapshot Message: written and read back, then read and written back */
static void check_market_wide_circuit_breaker_decline_level_status_snapshot_message(void) {
  MarketWideCircuitBreakerDeclineLevelStatusSnapshotMessage sent;
  MarketWideCircuitBreakerDeclineLevelStatusSnapshotMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_market_wide_circuit_breaker_decline_level_status_snapshot_message(&sent);
  assert(encode_market_wide_circuit_breaker_decline_level_status_snapshot_message(&sent, wire, 0) == 26);
  assert(decode_market_wide_circuit_breaker_decline_level_status_snapshot_message(&got, wire, 0) == 26);
  equal_market_wide_circuit_breaker_decline_level_status_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_market_wide_circuit_breaker_decline_level_status_snapshot_message(&got, wire, 0) == 26);
  assert(encode_market_wide_circuit_breaker_decline_level_status_snapshot_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Snapshot Message: 96 bytes --------------------------------- */

/* SIP generated message reporting latest LULD price bands, auction information, NBBO, and other per-symbol data at the time Snapshot is generated */
typedef struct {
  uint8_t participant_id;                           /* byte 0 */
  uint8_t security_symbol[11];                      /* bytes 1 to 11 */
  uint8_t instrument_type;                          /* byte 12 */
  uint8_t lower_limit_price_band[8];                /* bytes 13 to 20 */
  uint8_t upper_limit_price_band[8];                /* bytes 21 to 28 */
  uint8_t auction_collar_reference_price[8];        /* bytes 29 to 36 */
  uint8_t auction_collar_upper_threshold_price[8];  /* bytes 37 to 44 */
  uint8_t auction_collar_lower_threshold_price[8];  /* bytes 45 to 52 */
  uint8_t number_of_extensions;                     /* byte 53 */
  uint8_t national_best_bid_participant_id;         /* byte 54 */
  uint8_t national_best_bid_quote_condition;        /* byte 55 */
  uint8_t national_best_bid_price[8];               /* bytes 56 to 63 */
  uint8_t national_best_bid_size[4];                /* bytes 64 to 67 */
  uint8_t finra_best_bid_market_maker_id[4];        /* bytes 68 to 71 */
  uint8_t national_best_offer_participant_id;       /* byte 72 */
  uint8_t national_best_offer_quote_condition;      /* byte 73 */
  uint8_t national_best_offer_price[8];             /* bytes 74 to 81 */
  uint8_t national_best_offer_size[4];              /* bytes 82 to 85 */
  uint8_t finra_best_offer_market_maker_id[4];      /* bytes 86 to 89 */
  uint8_t national_bbo_luld_indicator;              /* byte 90 */
  uint8_t primary_listing_market_participant_id;    /* byte 91 */
  uint8_t financial_status_indicator;               /* byte 92 */
  uint8_t short_sale_restriction_indicator;         /* byte 93 */
  uint8_t halt_reason;                              /* byte 94 */
  uint8_t reserved;                                 /* byte 95 */
} ConsolidatedSnapshotMessage;

/* any Consolidated Snapshot Message at all: every byte one the checker chooses */
static void any_consolidated_snapshot_message(ConsolidatedSnapshotMessage *record) {
  record->participant_id = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->lower_limit_price_band[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->upper_limit_price_band[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_upper_threshold_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_lower_threshold_price[i] = arbitrary(); }
  record->number_of_extensions = arbitrary();
  record->national_best_bid_participant_id = arbitrary();
  record->national_best_bid_quote_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->national_best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->national_best_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->finra_best_bid_market_maker_id[i] = arbitrary(); }
  record->national_best_offer_participant_id = arbitrary();
  record->national_best_offer_quote_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->national_best_offer_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->national_best_offer_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->finra_best_offer_market_maker_id[i] = arbitrary(); }
  record->national_bbo_luld_indicator = arbitrary();
  record->primary_listing_market_participant_id = arbitrary();
  record->financial_status_indicator = arbitrary();
  record->short_sale_restriction_indicator = arbitrary();
  record->halt_reason = arbitrary();
  record->reserved = arbitrary();
}

/* Consolidated Snapshot Message to the wire: 96 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_snapshot_message(const ConsolidatedSnapshotMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_limit_price_band[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper_limit_price_band[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_upper_threshold_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_collar_lower_threshold_price[i]; }
  wire[at++] = record->number_of_extensions;
  wire[at++] = record->national_best_bid_participant_id;
  wire[at++] = record->national_best_bid_quote_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->national_best_bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->national_best_bid_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->finra_best_bid_market_maker_id[i]; }
  wire[at++] = record->national_best_offer_participant_id;
  wire[at++] = record->national_best_offer_quote_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->national_best_offer_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->national_best_offer_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->finra_best_offer_market_maker_id[i]; }
  wire[at++] = record->national_bbo_luld_indicator;
  wire[at++] = record->primary_listing_market_participant_id;
  wire[at++] = record->financial_status_indicator;
  wire[at++] = record->short_sale_restriction_indicator;
  wire[at++] = record->halt_reason;
  wire[at++] = record->reserved;

  return at;
}

/* Consolidated Snapshot Message off the wire: 96 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_snapshot_message(ConsolidatedSnapshotMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->lower_limit_price_band[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->upper_limit_price_band[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_upper_threshold_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_collar_lower_threshold_price[i] = wire[at++]; }
  record->number_of_extensions = wire[at++];
  record->national_best_bid_participant_id = wire[at++];
  record->national_best_bid_quote_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->national_best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->national_best_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->finra_best_bid_market_maker_id[i] = wire[at++]; }
  record->national_best_offer_participant_id = wire[at++];
  record->national_best_offer_quote_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->national_best_offer_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->national_best_offer_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->finra_best_offer_market_maker_id[i] = wire[at++]; }
  record->national_bbo_luld_indicator = wire[at++];
  record->primary_listing_market_participant_id = wire[at++];
  record->financial_status_indicator = wire[at++];
  record->short_sale_restriction_indicator = wire[at++];
  record->halt_reason = wire[at++];
  record->reserved = wire[at++];

  return at;
}

/* what was read of Consolidated Snapshot Message is what was written, byte for byte */
static void equal_consolidated_snapshot_message(const ConsolidatedSnapshotMessage *read, const ConsolidatedSnapshotMessage *written) {
  assert(read->participant_id == written->participant_id);
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 8; i++) { assert(read->lower_limit_price_band[i] == written->lower_limit_price_band[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->upper_limit_price_band[i] == written->upper_limit_price_band[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_reference_price[i] == written->auction_collar_reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_upper_threshold_price[i] == written->auction_collar_upper_threshold_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_collar_lower_threshold_price[i] == written->auction_collar_lower_threshold_price[i]); }
  assert(read->number_of_extensions == written->number_of_extensions);
  assert(read->national_best_bid_participant_id == written->national_best_bid_participant_id);
  assert(read->national_best_bid_quote_condition == written->national_best_bid_quote_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->national_best_bid_price[i] == written->national_best_bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->national_best_bid_size[i] == written->national_best_bid_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->finra_best_bid_market_maker_id[i] == written->finra_best_bid_market_maker_id[i]); }
  assert(read->national_best_offer_participant_id == written->national_best_offer_participant_id);
  assert(read->national_best_offer_quote_condition == written->national_best_offer_quote_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->national_best_offer_price[i] == written->national_best_offer_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->national_best_offer_size[i] == written->national_best_offer_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->finra_best_offer_market_maker_id[i] == written->finra_best_offer_market_maker_id[i]); }
  assert(read->national_bbo_luld_indicator == written->national_bbo_luld_indicator);
  assert(read->primary_listing_market_participant_id == written->primary_listing_market_participant_id);
  assert(read->financial_status_indicator == written->financial_status_indicator);
  assert(read->short_sale_restriction_indicator == written->short_sale_restriction_indicator);
  assert(read->halt_reason == written->halt_reason);
  assert(read->reserved == written->reserved);
}

/* Consolidated Snapshot Message: written and read back, then read and written back */
static void check_consolidated_snapshot_message(void) {
  ConsolidatedSnapshotMessage sent;
  ConsolidatedSnapshotMessage got;
  uint8_t wire[96];
  uint8_t again[96];

  any_consolidated_snapshot_message(&sent);
  assert(encode_consolidated_snapshot_message(&sent, wire, 0) == 96);
  assert(decode_consolidated_snapshot_message(&got, wire, 0) == 96);
  equal_consolidated_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 96; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_snapshot_message(&got, wire, 0) == 96);
  assert(encode_consolidated_snapshot_message(&got, again, 0) == 96);
  for (size_t i = 0; i < 96; i++) { assert(again[i] == wire[i]); }
}

/* ---- Participant Snapshot Message: 58 bytes ---------------------------------- */

/* SIP generated message reporting latest participant quote, LULD indicator, price and trading range indications, and halt reason per symbol */
typedef struct {
  uint8_t participant_id;                      /* byte 0 */
  uint8_t security_symbol[11];                 /* bytes 1 to 11 */
  uint8_t quote_condition;                     /* byte 12 */
  uint8_t bid_price[8];                        /* bytes 13 to 20 */
  uint8_t bid_size[4];                         /* bytes 21 to 24 */
  uint8_t offer_price[8];                      /* bytes 25 to 32 */
  uint8_t offer_size[4];                       /* bytes 33 to 36 */
  uint8_t retail_interest_indicator;           /* byte 37 */
  uint8_t settlement_condition;                /* byte 38 */
  uint8_t market_condition;                    /* byte 39 */
  uint8_t limit_up_limit_down_luld_indicator;  /* byte 40 */
  uint8_t high_indication_price[8];            /* bytes 41 to 48 */
  uint8_t low_indication_price[8];             /* bytes 49 to 56 */
  uint8_t halt_reason;                         /* byte 57 */
} ParticipantSnapshotMessage;

/* any Participant Snapshot Message at all: every byte one the checker chooses */
static void any_participant_snapshot_message(ParticipantSnapshotMessage *record) {
  record->participant_id = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->quote_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->offer_size[i] = arbitrary(); }
  record->retail_interest_indicator = arbitrary();
  record->settlement_condition = arbitrary();
  record->market_condition = arbitrary();
  record->limit_up_limit_down_luld_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->high_indication_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_indication_price[i] = arbitrary(); }
  record->halt_reason = arbitrary();
}

/* Participant Snapshot Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_participant_snapshot_message(const ParticipantSnapshotMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->quote_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->offer_size[i]; }
  wire[at++] = record->retail_interest_indicator;
  wire[at++] = record->settlement_condition;
  wire[at++] = record->market_condition;
  wire[at++] = record->limit_up_limit_down_luld_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_indication_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_indication_price[i]; }
  wire[at++] = record->halt_reason;

  return at;
}

/* Participant Snapshot Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_participant_snapshot_message(ParticipantSnapshotMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->quote_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->offer_size[i] = wire[at++]; }
  record->retail_interest_indicator = wire[at++];
  record->settlement_condition = wire[at++];
  record->market_condition = wire[at++];
  record->limit_up_limit_down_luld_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->high_indication_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_indication_price[i] = wire[at++]; }
  record->halt_reason = wire[at++];

  return at;
}

/* what was read of Participant Snapshot Message is what was written, byte for byte */
static void equal_participant_snapshot_message(const ParticipantSnapshotMessage *read, const ParticipantSnapshotMessage *written) {
  assert(read->participant_id == written->participant_id);
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->quote_condition == written->quote_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size[i] == written->bid_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_price[i] == written->offer_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->offer_size[i] == written->offer_size[i]); }
  assert(read->retail_interest_indicator == written->retail_interest_indicator);
  assert(read->settlement_condition == written->settlement_condition);
  assert(read->market_condition == written->market_condition);
  assert(read->limit_up_limit_down_luld_indicator == written->limit_up_limit_down_luld_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->high_indication_price[i] == written->high_indication_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_indication_price[i] == written->low_indication_price[i]); }
  assert(read->halt_reason == written->halt_reason);
}

/* Participant Snapshot Message: written and read back, then read and written back */
static void check_participant_snapshot_message(void) {
  ParticipantSnapshotMessage sent;
  ParticipantSnapshotMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_participant_snapshot_message(&sent);
  assert(encode_participant_snapshot_message(&sent, wire, 0) == 58);
  assert(decode_participant_snapshot_message(&got, wire, 0) == 58);
  equal_participant_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_participant_snapshot_message(&got, wire, 0) == 58);
  assert(encode_participant_snapshot_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Finra Snapshot Message: 64 bytes ---------------------------------------- */

/* SIP generated message reporting FINRA Best Bid and Offer (FBBO) */
typedef struct {
  uint8_t participant_id;                       /* byte 0 */
  uint8_t security_symbol[11];                  /* bytes 1 to 11 */
  uint8_t finra_best_bid_quote_condition;       /* byte 12 */
  uint8_t finra_best_bid_price[8];              /* bytes 13 to 20 */
  uint8_t finra_best_bid_size[4];               /* bytes 21 to 24 */
  uint8_t finra_best_bid_market_maker_id[4];    /* bytes 25 to 28 */
  uint8_t finra_best_offer_quote_condition;     /* byte 29 */
  uint8_t finra_best_offer_price[8];            /* bytes 30 to 37 */
  uint8_t finra_best_offer_size[4];             /* bytes 38 to 41 */
  uint8_t finra_best_offer_market_maker_id[4];  /* bytes 42 to 45 */
  uint8_t finra_bbo_luld_indicator;             /* byte 46 */
  uint8_t high_indication_price[8];             /* bytes 47 to 54 */
  uint8_t low_indication_price[8];              /* bytes 55 to 62 */
  uint8_t halt_reason;                          /* byte 63 */
} FinraSnapshotMessage;

/* any Finra Snapshot Message at all: every byte one the checker chooses */
static void any_finra_snapshot_message(FinraSnapshotMessage *record) {
  record->participant_id = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = arbitrary(); }
  record->finra_best_bid_quote_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->finra_best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->finra_best_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->finra_best_bid_market_maker_id[i] = arbitrary(); }
  record->finra_best_offer_quote_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->finra_best_offer_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->finra_best_offer_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->finra_best_offer_market_maker_id[i] = arbitrary(); }
  record->finra_bbo_luld_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->high_indication_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_indication_price[i] = arbitrary(); }
  record->halt_reason = arbitrary();
}

/* Finra Snapshot Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_finra_snapshot_message(const FinraSnapshotMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->participant_id;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->security_symbol[i]; }
  wire[at++] = record->finra_best_bid_quote_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->finra_best_bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->finra_best_bid_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->finra_best_bid_market_maker_id[i]; }
  wire[at++] = record->finra_best_offer_quote_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->finra_best_offer_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->finra_best_offer_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->finra_best_offer_market_maker_id[i]; }
  wire[at++] = record->finra_bbo_luld_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_indication_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_indication_price[i]; }
  wire[at++] = record->halt_reason;

  return at;
}

/* Finra Snapshot Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_finra_snapshot_message(FinraSnapshotMessage *record, const uint8_t *wire, size_t at) {
  record->participant_id = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->security_symbol[i] = wire[at++]; }
  record->finra_best_bid_quote_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->finra_best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->finra_best_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->finra_best_bid_market_maker_id[i] = wire[at++]; }
  record->finra_best_offer_quote_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->finra_best_offer_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->finra_best_offer_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->finra_best_offer_market_maker_id[i] = wire[at++]; }
  record->finra_bbo_luld_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->high_indication_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_indication_price[i] = wire[at++]; }
  record->halt_reason = wire[at++];

  return at;
}

/* what was read of Finra Snapshot Message is what was written, byte for byte */
static void equal_finra_snapshot_message(const FinraSnapshotMessage *read, const FinraSnapshotMessage *written) {
  assert(read->participant_id == written->participant_id);
  for (size_t i = 0; i < 11; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  assert(read->finra_best_bid_quote_condition == written->finra_best_bid_quote_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->finra_best_bid_price[i] == written->finra_best_bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->finra_best_bid_size[i] == written->finra_best_bid_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->finra_best_bid_market_maker_id[i] == written->finra_best_bid_market_maker_id[i]); }
  assert(read->finra_best_offer_quote_condition == written->finra_best_offer_quote_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->finra_best_offer_price[i] == written->finra_best_offer_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->finra_best_offer_size[i] == written->finra_best_offer_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->finra_best_offer_market_maker_id[i] == written->finra_best_offer_market_maker_id[i]); }
  assert(read->finra_bbo_luld_indicator == written->finra_bbo_luld_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->high_indication_price[i] == written->high_indication_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_indication_price[i] == written->low_indication_price[i]); }
  assert(read->halt_reason == written->halt_reason);
}

/* Finra Snapshot Message: written and read back, then read and written back */
static void check_finra_snapshot_message(void) {
  FinraSnapshotMessage sent;
  FinraSnapshotMessage got;
  uint8_t wire[64];
  uint8_t again[64];

  any_finra_snapshot_message(&sent);
  assert(encode_finra_snapshot_message(&sent, wire, 0) == 64);
  assert(decode_finra_snapshot_message(&got, wire, 0) == 64);
  equal_finra_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_finra_snapshot_message(&got, wire, 0) == 64);
  assert(encode_finra_snapshot_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_sip_block_timestamp();
  check_line_integrity_message();
  check_symbol_reference_data_message();
  check_market_wide_circuit_breaker_decline_level_status_snapshot_message();
  check_consolidated_snapshot_message();
  check_participant_snapshot_message();
  check_finra_snapshot_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
