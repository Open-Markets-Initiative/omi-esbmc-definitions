// miax/onyxfutures/topofmarketretransmission/OnyxFutures_TopOfMarketRetransmission_v1_3_a.c
/*
 * Miami International Holdings Top Of Market Retransmission
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
 *   - a length prefix framing what follows
 *   - a run counted by a field
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

/* ---- Sesm Packet Header: 3 bytes --------------------------------------------- */

/* SesM packet header */
typedef struct {
  uint8_t sesm_packet_length[2];  /* bytes 0 to 1 */
  uint8_t sesm_packet_type;       /* byte 2 */
} SesmPacketHeader;

/* any Sesm Packet Header at all: every byte one the checker chooses */
static void any_sesm_packet_header(SesmPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->sesm_packet_length[i] = arbitrary(); }
  record->sesm_packet_type = arbitrary();
}

/* Sesm Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_sesm_packet_header(const SesmPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sesm_packet_length[i]; }
  wire[at++] = record->sesm_packet_type;

  return at;
}

/* Sesm Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_sesm_packet_header(SesmPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->sesm_packet_length[i] = wire[at++]; }
  record->sesm_packet_type = wire[at++];

  return at;
}

/* what was read of Sesm Packet Header is what was written, byte for byte */
static void equal_sesm_packet_header(const SesmPacketHeader *read, const SesmPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->sesm_packet_length[i] == written->sesm_packet_length[i]); }
  assert(read->sesm_packet_type == written->sesm_packet_type);
}

/* Sesm Packet Header: written and read back, then read and written back */
static void check_sesm_packet_header(void) {
  SesmPacketHeader sent;
  SesmPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_sesm_packet_header(&sent);
  assert(encode_sesm_packet_header(&sent, wire, 0) == 3);
  assert(decode_sesm_packet_header(&got, wire, 0) == 3);
  equal_sesm_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_sesm_packet_header(&got, wire, 0) == 3);
  assert(encode_sesm_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Instrument Definition Message: 138 bytes ------------------------- */

/* Simple Instrument Definition */
typedef struct {
  uint8_t timestamp[8];                          /* bytes 0 to 7 */
  uint8_t instrument_id[4];                      /* bytes 8 to 11 */
  uint8_t underlying_asset_type;                 /* byte 12 */
  uint8_t underlying_asset_alphanumeric_4[4];    /* bytes 13 to 16 */
  uint8_t product_group_code_alphanumeric_6[6];  /* bytes 17 to 22 */
  uint8_t exchange[4];                           /* bytes 23 to 26 */
  uint8_t instrument_id_source;                  /* byte 27 */
  uint8_t instrument_type;                       /* byte 28 */
  uint8_t instrument_listing_status;             /* byte 29 */
  uint8_t reserved_3[3];                         /* bytes 30 to 32 */
  uint8_t currency;                              /* byte 33 */
  uint8_t settlement_currency;                   /* byte 34 */
  uint8_t match_algorithm;                       /* byte 35 */
  uint8_t minimum_size[4];                       /* bytes 36 to 39 */
  uint8_t maximum_size[4];                       /* bytes 40 to 43 */
  uint8_t tick[8];                               /* bytes 44 to 51 */
  uint8_t unit_of_measure[5];                    /* bytes 52 to 56 */
  uint8_t unit_of_measure_quantity[4];           /* bytes 57 to 60 */
  uint8_t settlement_price[8];                   /* bytes 61 to 68 */
  uint8_t settlement_price_type_calc_method;     /* byte 69 */
  uint8_t total_volume[4];                       /* bytes 70 to 73 */
  uint8_t open_interest_quantity[4];             /* bytes 74 to 77 */
  uint8_t high_limit_price[8];                   /* bytes 78 to 85 */
  uint8_t low_limit_price[8];                    /* bytes 86 to 93 */
  uint8_t trading_collar_variation_type;         /* byte 94 */
  uint8_t trading_collar_variation[8];           /* bytes 95 to 102 */
  uint8_t contract_date[4];                      /* bytes 103 to 106 */
  uint8_t maturity_date[2];                      /* bytes 107 to 108 */
  uint8_t valuation_date[2];                     /* bytes 109 to 110 */
  uint8_t first_trade_date[2];                   /* bytes 111 to 112 */
  uint8_t last_trade_date[2];                    /* bytes 113 to 114 */
  uint8_t first_notice_date[2];                  /* bytes 115 to 116 */
  uint8_t last_notice_date[2];                   /* bytes 117 to 118 */
  uint8_t first_delivery_date[2];                /* bytes 119 to 120 */
  uint8_t last_delivery_date[2];                 /* bytes 121 to 122 */
  uint8_t option_strike_price[8];                /* bytes 123 to 130 */
  uint8_t option_strike_currency;                /* byte 131 */
  uint8_t option_type;                           /* byte 132 */
  uint8_t option_expiration_type;                /* byte 133 */
  uint8_t underlying_future_instrument_id[4];    /* bytes 134 to 137 */
} SimpleInstrumentDefinitionMessage;

/* any Simple Instrument Definition Message at all: every byte one the checker chooses */
static void any_simple_instrument_definition_message(SimpleInstrumentDefinitionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->underlying_asset_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->underlying_asset_alphanumeric_4[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->product_group_code_alphanumeric_6[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->exchange[i] = arbitrary(); }
  record->instrument_id_source = arbitrary();
  record->instrument_type = arbitrary();
  record->instrument_listing_status = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
  record->currency = arbitrary();
  record->settlement_currency = arbitrary();
  record->match_algorithm = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->minimum_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maximum_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tick[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->unit_of_measure[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->unit_of_measure_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = arbitrary(); }
  record->settlement_price_type_calc_method = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_interest_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_limit_price[i] = arbitrary(); }
  record->trading_collar_variation_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trading_collar_variation[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->valuation_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->first_trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->last_trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->first_notice_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->last_notice_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->first_delivery_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->last_delivery_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->option_strike_price[i] = arbitrary(); }
  record->option_strike_currency = arbitrary();
  record->option_type = arbitrary();
  record->option_expiration_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->underlying_future_instrument_id[i] = arbitrary(); }
}

/* Simple Instrument Definition Message to the wire: 138 bytes from at, returning where the next byte goes */
static size_t encode_simple_instrument_definition_message(const SimpleInstrumentDefinitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->underlying_asset_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_asset_alphanumeric_4[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->product_group_code_alphanumeric_6[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange[i]; }
  wire[at++] = record->instrument_id_source;
  wire[at++] = record->instrument_type;
  wire[at++] = record->instrument_listing_status;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }
  wire[at++] = record->currency;
  wire[at++] = record->settlement_currency;
  wire[at++] = record->match_algorithm;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maximum_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->unit_of_measure[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unit_of_measure_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price[i]; }
  wire[at++] = record->settlement_price_type_calc_method;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_interest_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_limit_price[i]; }
  wire[at++] = record->trading_collar_variation_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_collar_variation[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->valuation_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->first_trade_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->last_trade_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->first_notice_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->last_notice_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->first_delivery_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->last_delivery_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->option_strike_price[i]; }
  wire[at++] = record->option_strike_currency;
  wire[at++] = record->option_type;
  wire[at++] = record->option_expiration_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_future_instrument_id[i]; }

  return at;
}

/* Simple Instrument Definition Message off the wire: 138 bytes from at, returning where the next byte lies */
static size_t decode_simple_instrument_definition_message(SimpleInstrumentDefinitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->underlying_asset_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->underlying_asset_alphanumeric_4[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->product_group_code_alphanumeric_6[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->exchange[i] = wire[at++]; }
  record->instrument_id_source = wire[at++];
  record->instrument_type = wire[at++];
  record->instrument_listing_status = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }
  record->currency = wire[at++];
  record->settlement_currency = wire[at++];
  record->match_algorithm = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->minimum_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maximum_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tick[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->unit_of_measure[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->unit_of_measure_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = wire[at++]; }
  record->settlement_price_type_calc_method = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_interest_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_limit_price[i] = wire[at++]; }
  record->trading_collar_variation_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trading_collar_variation[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->valuation_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->first_trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->last_trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->first_notice_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->last_notice_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->first_delivery_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->last_delivery_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->option_strike_price[i] = wire[at++]; }
  record->option_strike_currency = wire[at++];
  record->option_type = wire[at++];
  record->option_expiration_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->underlying_future_instrument_id[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Instrument Definition Message is what was written, byte for byte */
static void equal_simple_instrument_definition_message(const SimpleInstrumentDefinitionMessage *read, const SimpleInstrumentDefinitionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->underlying_asset_type == written->underlying_asset_type);
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_asset_alphanumeric_4[i] == written->underlying_asset_alphanumeric_4[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->product_group_code_alphanumeric_6[i] == written->product_group_code_alphanumeric_6[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->exchange[i] == written->exchange[i]); }
  assert(read->instrument_id_source == written->instrument_id_source);
  assert(read->instrument_type == written->instrument_type);
  assert(read->instrument_listing_status == written->instrument_listing_status);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
  assert(read->currency == written->currency);
  assert(read->settlement_currency == written->settlement_currency);
  assert(read->match_algorithm == written->match_algorithm);
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_size[i] == written->minimum_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maximum_size[i] == written->maximum_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tick[i] == written->tick[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->unit_of_measure[i] == written->unit_of_measure[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->unit_of_measure_quantity[i] == written->unit_of_measure_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  assert(read->settlement_price_type_calc_method == written->settlement_price_type_calc_method);
  for (size_t i = 0; i < 4; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_interest_quantity[i] == written->open_interest_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_limit_price[i] == written->high_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_limit_price[i] == written->low_limit_price[i]); }
  assert(read->trading_collar_variation_type == written->trading_collar_variation_type);
  for (size_t i = 0; i < 8; i++) { assert(read->trading_collar_variation[i] == written->trading_collar_variation[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_date[i] == written->contract_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->valuation_date[i] == written->valuation_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->first_trade_date[i] == written->first_trade_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->last_trade_date[i] == written->last_trade_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->first_notice_date[i] == written->first_notice_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->last_notice_date[i] == written->last_notice_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->first_delivery_date[i] == written->first_delivery_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->last_delivery_date[i] == written->last_delivery_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->option_strike_price[i] == written->option_strike_price[i]); }
  assert(read->option_strike_currency == written->option_strike_currency);
  assert(read->option_type == written->option_type);
  assert(read->option_expiration_type == written->option_expiration_type);
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_future_instrument_id[i] == written->underlying_future_instrument_id[i]); }
}

/* Simple Instrument Definition Message: written and read back, then read and written back */
static void check_simple_instrument_definition_message(void) {
  SimpleInstrumentDefinitionMessage sent;
  SimpleInstrumentDefinitionMessage got;
  uint8_t wire[138];
  uint8_t again[138];

  any_simple_instrument_definition_message(&sent);
  assert(encode_simple_instrument_definition_message(&sent, wire, 0) == 138);
  assert(decode_simple_instrument_definition_message(&got, wire, 0) == 138);
  equal_simple_instrument_definition_message(&got, &sent);

  for (size_t i = 0; i < 138; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_instrument_definition_message(&got, wire, 0) == 138);
  assert(encode_simple_instrument_definition_message(&got, again, 0) == 138);
  for (size_t i = 0; i < 138; i++) { assert(again[i] == wire[i]); }
}

/* ---- System State Message: 18 bytes ------------------------------------------ */

/* System State */
typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t to_m_version[8];  /* bytes 8 to 15 */
  uint8_t session_id;       /* byte 16 */
  uint8_t system_status;    /* byte 17 */
} SystemStateMessage;

/* any System State Message at all: every byte one the checker chooses */
static void any_system_state_message(SystemStateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->to_m_version[i] = arbitrary(); }
  record->session_id = arbitrary();
  record->system_status = arbitrary();
}

/* System State Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_system_state_message(const SystemStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->to_m_version[i]; }
  wire[at++] = record->session_id;
  wire[at++] = record->system_status;

  return at;
}

/* System State Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_system_state_message(SystemStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->to_m_version[i] = wire[at++]; }
  record->session_id = wire[at++];
  record->system_status = wire[at++];

  return at;
}

/* what was read of System State Message is what was written, byte for byte */
static void equal_system_state_message(const SystemStateMessage *read, const SystemStateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->to_m_version[i] == written->to_m_version[i]); }
  assert(read->session_id == written->session_id);
  assert(read->system_status == written->system_status);
}

/* System State Message: written and read back, then read and written back */
static void check_system_state_message(void) {
  SystemStateMessage sent;
  SystemStateMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_system_state_message(&sent);
  assert(encode_system_state_message(&sent, wire, 0) == 18);
  assert(decode_system_state_message(&got, wire, 0) == 18);
  equal_system_state_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_system_state_message(&got, wire, 0) == 18);
  assert(encode_system_state_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Trading Status Notification Message: 14 bytes ---------------- */

/* Instrument Trading Status Notification */
typedef struct {
  uint8_t timestamp[8];      /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t trading_status;    /* byte 12 */
  uint8_t market_state;      /* byte 13 */
} InstrumentTradingStatusNotificationMessage;

/* any Instrument Trading Status Notification Message at all: every byte one the checker chooses */
static void any_instrument_trading_status_notification_message(InstrumentTradingStatusNotificationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->market_state = arbitrary();
}

/* Instrument Trading Status Notification Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_instrument_trading_status_notification_message(const InstrumentTradingStatusNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->market_state;

  return at;
}

/* Instrument Trading Status Notification Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_instrument_trading_status_notification_message(InstrumentTradingStatusNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->market_state = wire[at++];

  return at;
}

/* what was read of Instrument Trading Status Notification Message is what was written, byte for byte */
static void equal_instrument_trading_status_notification_message(const InstrumentTradingStatusNotificationMessage *read, const InstrumentTradingStatusNotificationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->market_state == written->market_state);
}

/* Instrument Trading Status Notification Message: written and read back, then read and written back */
static void check_instrument_trading_status_notification_message(void) {
  InstrumentTradingStatusNotificationMessage sent;
  InstrumentTradingStatusNotificationMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_instrument_trading_status_notification_message(&sent);
  assert(encode_instrument_trading_status_notification_message(&sent, wire, 0) == 14);
  assert(decode_instrument_trading_status_notification_message(&got, wire, 0) == 14);
  equal_instrument_trading_status_notification_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_trading_status_notification_message(&got, wire, 0) == 14);
  assert(encode_instrument_trading_status_notification_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Best Bid And Offer Message: 36 bytes ------------------------------------ */

/* Top of Market (Best Bid and Offer) Message */
typedef struct {
  uint8_t timestamp[8];      /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t mbb_price[8];      /* bytes 12 to 19 */
  uint8_t mbb_size[4];       /* bytes 20 to 23 */
  uint8_t mbo_price[8];      /* bytes 24 to 31 */
  uint8_t mbo_size[4];       /* bytes 32 to 35 */
} BestBidAndOfferMessage;

/* any Best Bid And Offer Message at all: every byte one the checker chooses */
static void any_best_bid_and_offer_message(BestBidAndOfferMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mbb_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mbb_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mbo_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mbo_size[i] = arbitrary(); }
}

/* Best Bid And Offer Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_best_bid_and_offer_message(const BestBidAndOfferMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mbb_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mbb_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mbo_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mbo_size[i]; }

  return at;
}

/* Best Bid And Offer Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_best_bid_and_offer_message(BestBidAndOfferMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mbb_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mbb_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mbo_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mbo_size[i] = wire[at++]; }

  return at;
}

/* what was read of Best Bid And Offer Message is what was written, byte for byte */
static void equal_best_bid_and_offer_message(const BestBidAndOfferMessage *read, const BestBidAndOfferMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mbb_price[i] == written->mbb_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mbb_size[i] == written->mbb_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mbo_price[i] == written->mbo_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mbo_size[i] == written->mbo_size[i]); }
}

/* Best Bid And Offer Message: written and read back, then read and written back */
static void check_best_bid_and_offer_message(void) {
  BestBidAndOfferMessage sent;
  BestBidAndOfferMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_best_bid_and_offer_message(&sent);
  assert(encode_best_bid_and_offer_message(&sent, wire, 0) == 36);
  assert(decode_best_bid_and_offer_message(&got, wire, 0) == 36);
  equal_best_bid_and_offer_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_best_bid_and_offer_message(&got, wire, 0) == 36);
  assert(encode_best_bid_and_offer_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Sale Message: 45 bytes --------------------------------------------- */

/* Last Sale (Trade) Message */
typedef struct {
  uint8_t timestamp[8];         /* bytes 0 to 7 */
  uint8_t trade_date[2];        /* bytes 8 to 9 */
  uint8_t instrument_id[4];     /* bytes 10 to 13 */
  uint8_t trade_id[8];          /* bytes 14 to 21 */
  uint8_t correction_number;    /* byte 22 */
  uint8_t price[8];             /* bytes 23 to 30 */
  uint8_t size[4];              /* bytes 31 to 34 */
  uint8_t trade_type;           /* byte 35 */
  uint8_t complex_trade_id[8];  /* bytes 36 to 43 */
  uint8_t instrument_type;      /* byte 44 */
} LastSaleMessage;

/* any Last Sale Message at all: every byte one the checker chooses */
static void any_last_sale_message(LastSaleMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  record->correction_number = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->complex_trade_id[i] = arbitrary(); }
  record->instrument_type = arbitrary();
}

/* Last Sale Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_last_sale_message(const LastSaleMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->correction_number;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->complex_trade_id[i]; }
  wire[at++] = record->instrument_type;

  return at;
}

/* Last Sale Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_last_sale_message(LastSaleMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  record->correction_number = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->complex_trade_id[i] = wire[at++]; }
  record->instrument_type = wire[at++];

  return at;
}

/* what was read of Last Sale Message is what was written, byte for byte */
static void equal_last_sale_message(const LastSaleMessage *read, const LastSaleMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->correction_number == written->correction_number);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 8; i++) { assert(read->complex_trade_id[i] == written->complex_trade_id[i]); }
  assert(read->instrument_type == written->instrument_type);
}

/* Last Sale Message: written and read back, then read and written back */
static void check_last_sale_message(void) {
  LastSaleMessage sent;
  LastSaleMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_last_sale_message(&sent);
  assert(encode_last_sale_message(&sent, wire, 0) == 45);
  assert(decode_last_sale_message(&got, wire, 0) == 45);
  equal_last_sale_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_last_sale_message(&got, wire, 0) == 45);
  assert(encode_last_sale_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Message: 36 bytes ------------------------------------------ */

/* Trade Cancel Message */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t trade_date[2];      /* bytes 8 to 9 */
  uint8_t instrument_id[4];   /* bytes 10 to 13 */
  uint8_t trade_id[8];        /* bytes 14 to 21 */
  uint8_t correction_number;  /* byte 22 */
  uint8_t price[8];           /* bytes 23 to 30 */
  uint8_t size[4];            /* bytes 31 to 34 */
  uint8_t instrument_type;    /* byte 35 */
} TradeCancelMessage;

/* any Trade Cancel Message at all: every byte one the checker chooses */
static void any_trade_cancel_message(TradeCancelMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  record->correction_number = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  record->instrument_type = arbitrary();
}

/* Trade Cancel Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_message(const TradeCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->correction_number;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  wire[at++] = record->instrument_type;

  return at;
}

/* Trade Cancel Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_message(TradeCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  record->correction_number = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  record->instrument_type = wire[at++];

  return at;
}

/* what was read of Trade Cancel Message is what was written, byte for byte */
static void equal_trade_cancel_message(const TradeCancelMessage *read, const TradeCancelMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->correction_number == written->correction_number);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  assert(read->instrument_type == written->instrument_type);
}

/* Trade Cancel Message: written and read back, then read and written back */
static void check_trade_cancel_message(void) {
  TradeCancelMessage sent;
  TradeCancelMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_trade_cancel_message(&sent);
  assert(encode_trade_cancel_message(&sent, wire, 0) == 36);
  assert(decode_trade_cancel_message(&got, wire, 0) == 36);
  equal_trade_cancel_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_message(&got, wire, 0) == 36);
  assert(encode_trade_cancel_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Request: 1 byte ------------------------------------------------- */

/* Firms request a last value refresh of market data and status information */
typedef struct {
  uint8_t refresh_message_type;  /* byte 0 */
} RefreshRequest;

/* any Refresh Request at all: every byte one the checker chooses */
static void any_refresh_request(RefreshRequest *record) {
  record->refresh_message_type = arbitrary();
}

/* Refresh Request to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_refresh_request(const RefreshRequest *record, uint8_t *wire, size_t at) {
  wire[at++] = record->refresh_message_type;

  return at;
}

/* Refresh Request off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_refresh_request(RefreshRequest *record, const uint8_t *wire, size_t at) {
  record->refresh_message_type = wire[at++];

  return at;
}

/* what was read of Refresh Request is what was written, byte for byte */
static void equal_refresh_request(const RefreshRequest *read, const RefreshRequest *written) {
  assert(read->refresh_message_type == written->refresh_message_type);
}

/* Refresh Request: written and read back, then read and written back */
static void check_refresh_request(void) {
  RefreshRequest sent;
  RefreshRequest got;
  uint8_t wire[1];
  uint8_t again[1];

  any_refresh_request(&sent);
  assert(encode_refresh_request(&sent, wire, 0) == 1);
  assert(decode_refresh_request(&got, wire, 0) == 1);
  equal_refresh_request(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_request(&got, wire, 0) == 1);
  assert(encode_refresh_request(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Refresh: 1 byte -------------------------------------------------- */

/* Sent when the refresh of the requested message type is complete */
typedef struct {
  uint8_t refresh_message_type;  /* byte 0 */
} EndOfRefresh;

/* any End Of Refresh at all: every byte one the checker chooses */
static void any_end_of_refresh(EndOfRefresh *record) {
  record->refresh_message_type = arbitrary();
}

/* End Of Refresh to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_end_of_refresh(const EndOfRefresh *record, uint8_t *wire, size_t at) {
  wire[at++] = record->refresh_message_type;

  return at;
}

/* End Of Refresh off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_end_of_refresh(EndOfRefresh *record, const uint8_t *wire, size_t at) {
  record->refresh_message_type = wire[at++];

  return at;
}

/* what was read of End Of Refresh is what was written, byte for byte */
static void equal_end_of_refresh(const EndOfRefresh *read, const EndOfRefresh *written) {
  assert(read->refresh_message_type == written->refresh_message_type);
}

/* End Of Refresh: written and read back, then read and written back */
static void check_end_of_refresh(void) {
  EndOfRefresh sent;
  EndOfRefresh got;
  uint8_t wire[1];
  uint8_t again[1];

  any_end_of_refresh(&sent);
  assert(encode_end_of_refresh(&sent, wire, 0) == 1);
  assert(decode_end_of_refresh(&got, wire, 0) == 1);
  equal_end_of_refresh(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_refresh(&got, wire, 0) == 1);
  assert(encode_end_of_refresh(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request: 35 bytes ------------------------------------------------- */

/* The SesM client must send a Login request packet immediately upon establishing a new TCP/IP socket connection to the server */
typedef struct {
  uint8_t sesm_version[5];               /* bytes 0 to 4 */
  uint8_t username[5];                   /* bytes 5 to 9 */
  uint8_t computer_id[8];                /* bytes 10 to 17 */
  uint8_t application_protocol[8];       /* bytes 18 to 25 */
  uint8_t requested_session;             /* byte 26 */
  uint8_t requested_sequence_number[8];  /* bytes 27 to 34 */
} LoginRequest;

/* any Login Request at all: every byte one the checker chooses */
static void any_login_request(LoginRequest *record) {
  for (size_t i = 0; i < 5; i++) { record->sesm_version[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->computer_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->application_protocol[i] = arbitrary(); }
  record->requested_session = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->requested_sequence_number[i] = arbitrary(); }
}

/* Login Request to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_login_request(const LoginRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sesm_version[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->computer_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->application_protocol[i]; }
  wire[at++] = record->requested_session;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->requested_sequence_number[i]; }

  return at;
}

/* Login Request off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_login_request(LoginRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->sesm_version[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->computer_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->application_protocol[i] = wire[at++]; }
  record->requested_session = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->requested_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request is what was written, byte for byte */
static void equal_login_request(const LoginRequest *read, const LoginRequest *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->sesm_version[i] == written->sesm_version[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->computer_id[i] == written->computer_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->application_protocol[i] == written->application_protocol[i]); }
  assert(read->requested_session == written->requested_session);
  for (size_t i = 0; i < 8; i++) { assert(read->requested_sequence_number[i] == written->requested_sequence_number[i]); }
}

/* Login Request: written and read back, then read and written back */
static void check_login_request(void) {
  LoginRequest sent;
  LoginRequest got;
  uint8_t wire[35];
  uint8_t again[35];

  any_login_request(&sent);
  assert(encode_login_request(&sent, wire, 0) == 35);
  assert(decode_login_request(&got, wire, 0) == 35);
  equal_login_request(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request(&got, wire, 0) == 35);
  assert(encode_login_request(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response: 10 bytes ------------------------------------------------ */

/* The SesM server sends a Login response packet in response a Login request packet from the client */
typedef struct {
  uint8_t login_status;                /* byte 0 */
  uint8_t session_id;                  /* byte 1 */
  uint8_t highest_sequence_number[8];  /* bytes 2 to 9 */
} LoginResponse;

/* any Login Response at all: every byte one the checker chooses */
static void any_login_response(LoginResponse *record) {
  record->login_status = arbitrary();
  record->session_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->highest_sequence_number[i] = arbitrary(); }
}

/* Login Response to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_login_response(const LoginResponse *record, uint8_t *wire, size_t at) {
  wire[at++] = record->login_status;
  wire[at++] = record->session_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->highest_sequence_number[i]; }

  return at;
}

/* Login Response off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_login_response(LoginResponse *record, const uint8_t *wire, size_t at) {
  record->login_status = wire[at++];
  record->session_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->highest_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Response is what was written, byte for byte */
static void equal_login_response(const LoginResponse *read, const LoginResponse *written) {
  assert(read->login_status == written->login_status);
  assert(read->session_id == written->session_id);
  for (size_t i = 0; i < 8; i++) { assert(read->highest_sequence_number[i] == written->highest_sequence_number[i]); }
}

/* Login Response: written and read back, then read and written back */
static void check_login_response(void) {
  LoginResponse sent;
  LoginResponse got;
  uint8_t wire[10];
  uint8_t again[10];

  any_login_response(&sent);
  assert(encode_login_response(&sent, wire, 0) == 10);
  assert(decode_login_response(&got, wire, 0) == 10);
  equal_login_response(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response(&got, wire, 0) == 10);
  assert(encode_login_response(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Request: 16 bytes ---------------------------------------- */

/* The SesM client uses this packet to request the server to retransmit a range of packets */
typedef struct {
  uint8_t start_sequence_number[8];  /* bytes 0 to 7 */
  uint8_t end_sequence_number[8];    /* bytes 8 to 15 */
} RetransmissionRequest;

/* any Retransmission Request at all: every byte one the checker chooses */
static void any_retransmission_request(RetransmissionRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->start_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_sequence_number[i] = arbitrary(); }
}

/* Retransmission Request to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_request(const RetransmissionRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->start_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_sequence_number[i]; }

  return at;
}

/* Retransmission Request off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_request(RetransmissionRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->start_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmission Request is what was written, byte for byte */
static void equal_retransmission_request(const RetransmissionRequest *read, const RetransmissionRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->start_sequence_number[i] == written->start_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_sequence_number[i] == written->end_sequence_number[i]); }
}

/* Retransmission Request: written and read back, then read and written back */
static void check_retransmission_request(void) {
  RetransmissionRequest sent;
  RetransmissionRequest got;
  uint8_t wire[16];
  uint8_t again[16];

  any_retransmission_request(&sent);
  assert(encode_retransmission_request(&sent, wire, 0) == 16);
  assert(decode_retransmission_request(&got, wire, 0) == 16);
  equal_retransmission_request(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_request(&got, wire, 0) == 16);
  assert(encode_retransmission_request(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_sesm_packet_header();
  check_simple_instrument_definition_message();
  check_system_state_message();
  check_instrument_trading_status_notification_message();
  check_best_bid_and_offer_message();
  check_last_sale_message();
  check_trade_cancel_message();
  check_refresh_request();
  check_end_of_refresh();
  check_login_request();
  check_login_response();
  check_retransmission_request();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
