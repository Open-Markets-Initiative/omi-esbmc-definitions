// miax/onyxfutures/depthofmarket/OnyxFutures_DepthOfMarket_v1_1_a.c
/*
 * Miami International Holdings Depth Of Market
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

/* ---- Mach Packet Header: 12 bytes -------------------------------------------- */

/* Mach packet header (12 bytes) */
typedef struct {
  uint8_t sequence_number[8];  /* bytes 0 to 7 */
  uint8_t packet_length[2];    /* bytes 8 to 9 */
  uint8_t packet_type;         /* byte 10 */
  uint8_t session_number;      /* byte 11 */
} MachPacketHeader;

/* any Mach Packet Header at all: every byte one the checker chooses */
static void any_mach_packet_header(MachPacketHeader *record) {
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  record->packet_type = arbitrary();
  record->session_number = arbitrary();
}

/* Mach Packet Header to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_mach_packet_header(const MachPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  wire[at++] = record->packet_type;
  wire[at++] = record->session_number;

  return at;
}

/* Mach Packet Header off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_mach_packet_header(MachPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  record->packet_type = wire[at++];
  record->session_number = wire[at++];

  return at;
}

/* what was read of Mach Packet Header is what was written, byte for byte */
static void equal_mach_packet_header(const MachPacketHeader *read, const MachPacketHeader *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  assert(read->packet_type == written->packet_type);
  assert(read->session_number == written->session_number);
}

/* Mach Packet Header: written and read back, then read and written back */
static void check_mach_packet_header(void) {
  MachPacketHeader sent;
  MachPacketHeader got;
  uint8_t wire[12];
  uint8_t again[12];

  any_mach_packet_header(&sent);
  assert(encode_mach_packet_header(&sent, wire, 0) == 12);
  assert(decode_mach_packet_header(&got, wire, 0) == 12);
  equal_mach_packet_header(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_mach_packet_header(&got, wire, 0) == 12);
  assert(encode_mach_packet_header(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Instrument Definition Message: 138 bytes ------------------------- */

/* Simple Instrument Definition */
typedef struct {
  uint8_t timestamp[8];                        /* bytes 0 to 7 */
  uint8_t instrument_id[4];                    /* bytes 8 to 11 */
  uint8_t underlying_asset_type;               /* byte 12 */
  uint8_t underlying_asset[4];                 /* bytes 13 to 16 */
  uint8_t product_group_code[6];               /* bytes 17 to 22 */
  uint8_t exchange[4];                         /* bytes 23 to 26 */
  uint8_t instrument_id_source;                /* byte 27 */
  uint8_t instrument_type;                     /* byte 28 */
  uint8_t reserved_4[4];                       /* bytes 29 to 32 */
  uint8_t currency;                            /* byte 33 */
  uint8_t settlement_currency;                 /* byte 34 */
  uint8_t match_algorithm;                     /* byte 35 */
  uint8_t minimum_size[4];                     /* bytes 36 to 39 */
  uint8_t maximum_size[4];                     /* bytes 40 to 43 */
  uint8_t tick[8];                             /* bytes 44 to 51 */
  uint8_t unit_of_measure[5];                  /* bytes 52 to 56 */
  uint8_t unit_of_measure_quantity[4];         /* bytes 57 to 60 */
  uint8_t settlement_price[8];                 /* bytes 61 to 68 */
  uint8_t settlement_price_type_calc_method;   /* byte 69 */
  uint8_t total_volume[4];                     /* bytes 70 to 73 */
  uint8_t open_interest_quantity[4];           /* bytes 74 to 77 */
  uint8_t high_limit_price[8];                 /* bytes 78 to 85 */
  uint8_t low_limit_price[8];                  /* bytes 86 to 93 */
  uint8_t trading_collar_variation_type;       /* byte 94 */
  uint8_t trading_collar_variation[8];         /* bytes 95 to 102 */
  uint8_t contract_date[4];                    /* bytes 103 to 106 */
  uint8_t maturity_date[2];                    /* bytes 107 to 108 */
  uint8_t valuation_date[2];                   /* bytes 109 to 110 */
  uint8_t first_trade_date[2];                 /* bytes 111 to 112 */
  uint8_t last_trade_date[2];                  /* bytes 113 to 114 */
  uint8_t first_notice_date[2];                /* bytes 115 to 116 */
  uint8_t last_notice_date[2];                 /* bytes 117 to 118 */
  uint8_t first_delivery_date[2];              /* bytes 119 to 120 */
  uint8_t last_delivery_date[2];               /* bytes 121 to 122 */
  uint8_t option_strike_price[8];              /* bytes 123 to 130 */
  uint8_t option_strike_currency;              /* byte 131 */
  uint8_t option_type;                         /* byte 132 */
  uint8_t option_expiration_type;              /* byte 133 */
  uint8_t underlying_future_instrument_id[4];  /* bytes 134 to 137 */
} SimpleInstrumentDefinitionMessage;

/* any Simple Instrument Definition Message at all: every byte one the checker chooses */
static void any_simple_instrument_definition_message(SimpleInstrumentDefinitionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->underlying_asset_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->underlying_asset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->product_group_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->exchange[i] = arbitrary(); }
  record->instrument_id_source = arbitrary();
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_asset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->product_group_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange[i]; }
  wire[at++] = record->instrument_id_source;
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
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
  for (size_t i = 0; i < 4; i++) { record->underlying_asset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->product_group_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->exchange[i] = wire[at++]; }
  record->instrument_id_source = wire[at++];
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
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
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_asset[i] == written->underlying_asset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->product_group_code[i] == written->product_group_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->exchange[i] == written->exchange[i]); }
  assert(read->instrument_id_source == written->instrument_id_source);
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
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
  uint8_t do_m_version[8];  /* bytes 8 to 15 */
  uint8_t session_id;       /* byte 16 */
  uint8_t system_status;    /* byte 17 */
} SystemStateMessage;

/* any System State Message at all: every byte one the checker chooses */
static void any_system_state_message(SystemStateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->do_m_version[i] = arbitrary(); }
  record->session_id = arbitrary();
  record->system_status = arbitrary();
}

/* System State Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_system_state_message(const SystemStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->do_m_version[i]; }
  wire[at++] = record->session_id;
  wire[at++] = record->system_status;

  return at;
}

/* System State Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_system_state_message(SystemStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->do_m_version[i] = wire[at++]; }
  record->session_id = wire[at++];
  record->system_status = wire[at++];

  return at;
}

/* what was read of System State Message is what was written, byte for byte */
static void equal_system_state_message(const SystemStateMessage *read, const SystemStateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->do_m_version[i] == written->do_m_version[i]); }
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

/* ---- Anticipated Opening Price Message: 25 bytes ----------------------------- */

/* Anticipated Opening Price */
typedef struct {
  uint8_t timestamp[8];                  /* bytes 0 to 7 */
  uint8_t instrument_id[4];              /* bytes 8 to 11 */
  uint8_t anticipated_opening_price[8];  /* bytes 12 to 19 */
  uint8_t opening_match_quantity[4];     /* bytes 20 to 23 */
  uint8_t instrument_type;               /* byte 24 */
} AnticipatedOpeningPriceMessage;

/* any Anticipated Opening Price Message at all: every byte one the checker chooses */
static void any_anticipated_opening_price_message(AnticipatedOpeningPriceMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->anticipated_opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opening_match_quantity[i] = arbitrary(); }
  record->instrument_type = arbitrary();
}

/* Anticipated Opening Price Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_anticipated_opening_price_message(const AnticipatedOpeningPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->anticipated_opening_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opening_match_quantity[i]; }
  wire[at++] = record->instrument_type;

  return at;
}

/* Anticipated Opening Price Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_anticipated_opening_price_message(AnticipatedOpeningPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->anticipated_opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opening_match_quantity[i] = wire[at++]; }
  record->instrument_type = wire[at++];

  return at;
}

/* what was read of Anticipated Opening Price Message is what was written, byte for byte */
static void equal_anticipated_opening_price_message(const AnticipatedOpeningPriceMessage *read, const AnticipatedOpeningPriceMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->anticipated_opening_price[i] == written->anticipated_opening_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opening_match_quantity[i] == written->opening_match_quantity[i]); }
  assert(read->instrument_type == written->instrument_type);
}

/* Anticipated Opening Price Message: written and read back, then read and written back */
static void check_anticipated_opening_price_message(void) {
  AnticipatedOpeningPriceMessage sent;
  AnticipatedOpeningPriceMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_anticipated_opening_price_message(&sent);
  assert(encode_anticipated_opening_price_message(&sent, wire, 0) == 25);
  assert(decode_anticipated_opening_price_message(&got, wire, 0) == 25);
  equal_anticipated_opening_price_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_anticipated_opening_price_message(&got, wire, 0) == 25);
  assert(encode_anticipated_opening_price_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Price Update Message: 24 bytes ------------------------------- */

/* Settlement Price Update */
typedef struct {
  uint8_t timestamp[8];                       /* bytes 0 to 7 */
  uint8_t trade_date[2];                      /* bytes 8 to 9 */
  uint8_t instrument_id[4];                   /* bytes 10 to 13 */
  uint8_t settlement_price[8];                /* bytes 14 to 21 */
  uint8_t settlement_price_type;              /* byte 22 */
  uint8_t settlement_price_type_calc_method;  /* byte 23 */
} SettlementPriceUpdateMessage;

/* any Settlement Price Update Message at all: every byte one the checker chooses */
static void any_settlement_price_update_message(SettlementPriceUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = arbitrary(); }
  record->settlement_price_type = arbitrary();
  record->settlement_price_type_calc_method = arbitrary();
}

/* Settlement Price Update Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_settlement_price_update_message(const SettlementPriceUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_price[i]; }
  wire[at++] = record->settlement_price_type;
  wire[at++] = record->settlement_price_type_calc_method;

  return at;
}

/* Settlement Price Update Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_settlement_price_update_message(SettlementPriceUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_price[i] = wire[at++]; }
  record->settlement_price_type = wire[at++];
  record->settlement_price_type_calc_method = wire[at++];

  return at;
}

/* what was read of Settlement Price Update Message is what was written, byte for byte */
static void equal_settlement_price_update_message(const SettlementPriceUpdateMessage *read, const SettlementPriceUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  assert(read->settlement_price_type == written->settlement_price_type);
  assert(read->settlement_price_type_calc_method == written->settlement_price_type_calc_method);
}

/* Settlement Price Update Message: written and read back, then read and written back */
static void check_settlement_price_update_message(void) {
  SettlementPriceUpdateMessage sent;
  SettlementPriceUpdateMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_settlement_price_update_message(&sent);
  assert(encode_settlement_price_update_message(&sent, wire, 0) == 24);
  assert(decode_settlement_price_update_message(&got, wire, 0) == 24);
  equal_settlement_price_update_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_price_update_message(&got, wire, 0) == 24);
  assert(encode_settlement_price_update_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Interest Update Message: 18 bytes ---------------------------------- */

/* Open Interest Update */
typedef struct {
  uint8_t timestamp[8];               /* bytes 0 to 7 */
  uint8_t trade_date[2];              /* bytes 8 to 9 */
  uint8_t instrument_id[4];           /* bytes 10 to 13 */
  uint8_t open_interest_quantity[4];  /* bytes 14 to 17 */
} OpenInterestUpdateMessage;

/* any Open Interest Update Message at all: every byte one the checker chooses */
static void any_open_interest_update_message(OpenInterestUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_interest_quantity[i] = arbitrary(); }
}

/* Open Interest Update Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_open_interest_update_message(const OpenInterestUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_interest_quantity[i]; }

  return at;
}

/* Open Interest Update Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_open_interest_update_message(OpenInterestUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_interest_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Open Interest Update Message is what was written, byte for byte */
static void equal_open_interest_update_message(const OpenInterestUpdateMessage *read, const OpenInterestUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_interest_quantity[i] == written->open_interest_quantity[i]); }
}

/* Open Interest Update Message: written and read back, then read and written back */
static void check_open_interest_update_message(void) {
  OpenInterestUpdateMessage sent;
  OpenInterestUpdateMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_open_interest_update_message(&sent);
  assert(encode_open_interest_update_message(&sent, wire, 0) == 18);
  assert(decode_open_interest_update_message(&got, wire, 0) == 18);
  equal_open_interest_update_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_open_interest_update_message(&got, wire, 0) == 18);
  assert(encode_open_interest_update_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Total Volume Update Message: 18 bytes ----------------------------------- */

/* Total Volume Update */
typedef struct {
  uint8_t timestamp[8];      /* bytes 0 to 7 */
  uint8_t trade_date[2];     /* bytes 8 to 9 */
  uint8_t instrument_id[4];  /* bytes 10 to 13 */
  uint8_t total_volume[4];   /* bytes 14 to 17 */
} TotalVolumeUpdateMessage;

/* any Total Volume Update Message at all: every byte one the checker chooses */
static void any_total_volume_update_message(TotalVolumeUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = arbitrary(); }
}

/* Total Volume Update Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_total_volume_update_message(const TotalVolumeUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_volume[i]; }

  return at;
}

/* Total Volume Update Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_total_volume_update_message(TotalVolumeUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Total Volume Update Message is what was written, byte for byte */
static void equal_total_volume_update_message(const TotalVolumeUpdateMessage *read, const TotalVolumeUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
}

/* Total Volume Update Message: written and read back, then read and written back */
static void check_total_volume_update_message(void) {
  TotalVolumeUpdateMessage sent;
  TotalVolumeUpdateMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_total_volume_update_message(&sent);
  assert(encode_total_volume_update_message(&sent, wire, 0) == 18);
  assert(decode_total_volume_update_message(&got, wire, 0) == 18);
  equal_total_volume_update_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_total_volume_update_message(&got, wire, 0) == 18);
  assert(encode_total_volume_update_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Clear Message: 12 bytes -------------------------------------- */

/* Instrument Clear Message */
typedef struct {
  uint8_t timestamp[8];      /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
} InstrumentClearMessage;

/* any Instrument Clear Message at all: every byte one the checker chooses */
static void any_instrument_clear_message(InstrumentClearMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
}

/* Instrument Clear Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_instrument_clear_message(const InstrumentClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }

  return at;
}

/* Instrument Clear Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_instrument_clear_message(InstrumentClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Clear Message is what was written, byte for byte */
static void equal_instrument_clear_message(const InstrumentClearMessage *read, const InstrumentClearMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
}

/* Instrument Clear Message: written and read back, then read and written back */
static void check_instrument_clear_message(void) {
  InstrumentClearMessage sent;
  InstrumentClearMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_instrument_clear_message(&sent);
  assert(encode_instrument_clear_message(&sent, wire, 0) == 12);
  assert(decode_instrument_clear_message(&got, wire, 0) == 12);
  equal_instrument_clear_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_clear_message(&got, wire, 0) == 12);
  assert(encode_instrument_clear_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 35 bytes --------------------------------------------- */

/* Add Order Message */
typedef struct {
  uint8_t timestamp[8];      /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t order_type;        /* byte 12 */
  uint8_t order_id[8];       /* bytes 13 to 20 */
  uint8_t order_side;        /* byte 21 */
  uint8_t price[8];          /* bytes 22 to 29 */
  uint8_t size[4];           /* bytes 30 to 33 */
  uint8_t instrument_type;   /* byte 34 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->order_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->order_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  record->instrument_type = arbitrary();
}

/* Add Order Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->order_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  wire[at++] = record->instrument_type;

  return at;
}

/* Add Order Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->order_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->order_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  record->instrument_type = wire[at++];

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->order_side == written->order_side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  assert(read->instrument_type == written->instrument_type);
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 35);
  assert(decode_add_order_message(&got, wire, 0) == 35);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 35);
  assert(encode_add_order_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Message: 34 bytes ------------------------------------------ */

/* Modify Order Message */
typedef struct {
  uint8_t timestamp[8];      /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t order_id[8];       /* bytes 12 to 19 */
  uint8_t price[8];          /* bytes 20 to 27 */
  uint8_t size_flags[4];     /* bytes 28 to 31 */
  uint8_t order_side;        /* byte 32 */
  uint8_t instrument_type;   /* byte 33 */
} ModifyOrderMessage;

/* any Modify Order Message at all: every byte one the checker chooses */
static void any_modify_order_message(ModifyOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size_flags[i] = arbitrary(); }
  record->order_side = arbitrary();
  record->instrument_type = arbitrary();
}

/* Modify Order Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_message(const ModifyOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size_flags[i]; }
  wire[at++] = record->order_side;
  wire[at++] = record->instrument_type;

  return at;
}

/* Modify Order Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_message(ModifyOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size_flags[i] = wire[at++]; }
  record->order_side = wire[at++];
  record->instrument_type = wire[at++];

  return at;
}

/* what was read of Modify Order Message is what was written, byte for byte */
static void equal_modify_order_message(const ModifyOrderMessage *read, const ModifyOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size_flags[i] == written->size_flags[i]); }
  assert(read->order_side == written->order_side);
  assert(read->instrument_type == written->instrument_type);
}

/* Modify Order Message: written and read back, then read and written back */
static void check_modify_order_message(void) {
  ModifyOrderMessage sent;
  ModifyOrderMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_modify_order_message(&sent);
  assert(encode_modify_order_message(&sent, wire, 0) == 34);
  assert(decode_modify_order_message(&got, wire, 0) == 34);
  equal_modify_order_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_message(&got, wire, 0) == 34);
  assert(encode_modify_order_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Order Message: 22 bytes ------------------------------------------ */

/* Delete Order Message */
typedef struct {
  uint8_t timestamp[8];      /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t order_id[8];       /* bytes 12 to 19 */
  uint8_t order_side;        /* byte 20 */
  uint8_t instrument_type;   /* byte 21 */
} DeleteOrderMessage;

/* any Delete Order Message at all: every byte one the checker chooses */
static void any_delete_order_message(DeleteOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->order_side = arbitrary();
  record->instrument_type = arbitrary();
}

/* Delete Order Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_delete_order_message(const DeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->order_side;
  wire[at++] = record->instrument_type;

  return at;
}

/* Delete Order Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_delete_order_message(DeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->order_side = wire[at++];
  record->instrument_type = wire[at++];

  return at;
}

/* what was read of Delete Order Message is what was written, byte for byte */
static void equal_delete_order_message(const DeleteOrderMessage *read, const DeleteOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->order_side == written->order_side);
  assert(read->instrument_type == written->instrument_type);
}

/* Delete Order Message: written and read back, then read and written back */
static void check_delete_order_message(void) {
  DeleteOrderMessage sent;
  DeleteOrderMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_delete_order_message(&sent);
  assert(encode_delete_order_message(&sent, wire, 0) == 22);
  assert(decode_delete_order_message(&got, wire, 0) == 22);
  equal_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_order_message(&got, wire, 0) == 22);
  assert(encode_delete_order_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Execution Message: 62 bytes --------------------------------------- */

/* Order Execution Message */
typedef struct {
  uint8_t timestamp[8];         /* bytes 0 to 7 */
  uint8_t trade_date[2];        /* bytes 8 to 9 */
  uint8_t instrument_id[4];     /* bytes 10 to 13 */
  uint8_t buy_order_id[8];      /* bytes 14 to 21 */
  uint8_t sell_order_id[8];     /* bytes 22 to 29 */
  uint8_t aggressor_side;       /* byte 30 */
  uint8_t trade_id[8];          /* bytes 31 to 38 */
  uint8_t correction_number;    /* byte 39 */
  uint8_t price[8];             /* bytes 40 to 47 */
  uint8_t size[4];              /* bytes 48 to 51 */
  uint8_t trade_type;           /* byte 52 */
  uint8_t complex_trade_id[8];  /* bytes 53 to 60 */
  uint8_t instrument_type;      /* byte 61 */
} OrderExecutionMessage;

/* any Order Execution Message at all: every byte one the checker chooses */
static void any_order_execution_message(OrderExecutionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_order_id[i] = arbitrary(); }
  record->aggressor_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  record->correction_number = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->complex_trade_id[i] = arbitrary(); }
  record->instrument_type = arbitrary();
}

/* Order Execution Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_order_execution_message(const OrderExecutionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_order_id[i]; }
  wire[at++] = record->aggressor_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->correction_number;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->complex_trade_id[i]; }
  wire[at++] = record->instrument_type;

  return at;
}

/* Order Execution Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_order_execution_message(OrderExecutionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_order_id[i] = wire[at++]; }
  record->aggressor_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  record->correction_number = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->complex_trade_id[i] = wire[at++]; }
  record->instrument_type = wire[at++];

  return at;
}

/* what was read of Order Execution Message is what was written, byte for byte */
static void equal_order_execution_message(const OrderExecutionMessage *read, const OrderExecutionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_order_id[i] == written->buy_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_order_id[i] == written->sell_order_id[i]); }
  assert(read->aggressor_side == written->aggressor_side);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->correction_number == written->correction_number);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 8; i++) { assert(read->complex_trade_id[i] == written->complex_trade_id[i]); }
  assert(read->instrument_type == written->instrument_type);
}

/* Order Execution Message: written and read back, then read and written back */
static void check_order_execution_message(void) {
  OrderExecutionMessage sent;
  OrderExecutionMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_order_execution_message(&sent);
  assert(encode_order_execution_message(&sent, wire, 0) == 62);
  assert(decode_order_execution_message(&got, wire, 0) == 62);
  equal_order_execution_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_order_execution_message(&got, wire, 0) == 62);
  assert(encode_order_execution_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_mach_packet_header();
  check_simple_instrument_definition_message();
  check_system_state_message();
  check_instrument_trading_status_notification_message();
  check_anticipated_opening_price_message();
  check_settlement_price_update_message();
  check_open_interest_update_message();
  check_total_volume_update_message();
  check_instrument_clear_message();
  check_add_order_message();
  check_modify_order_message();
  check_delete_order_message();
  check_order_execution_message();
  check_trade_cancel_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
