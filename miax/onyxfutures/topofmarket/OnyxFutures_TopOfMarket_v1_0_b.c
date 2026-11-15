// miax/onyxfutures/topofmarket/OnyxFutures_TopOfMarket_v1_0_b.c
/*
 * Miami International Holdings Top Of Market
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

/* ---- Simple Instrument Definition Message: 119 bytes ------------------------- */

/* used to disseminate all Simple Instruments traded on MIAX FuturesOnyx for the current trading session */
typedef struct {
  uint8_t timestamp[8];                       /* bytes 0 to 7 */
  uint8_t instrument_id[4];                   /* bytes 8 to 11 */
  uint8_t underlying_asset_type;              /* byte 12 */
  uint8_t underlying_asset[4];                /* bytes 13 to 16 */
  uint8_t product_group_code[6];              /* bytes 17 to 22 */
  uint8_t exchange[4];                        /* bytes 23 to 26 */
  uint8_t instrument_id_source;               /* byte 27 */
  uint8_t instrument_type;                    /* byte 28 */
  uint8_t maturity_month_year[4];             /* bytes 29 to 32 */
  uint8_t currency;                           /* byte 33 */
  uint8_t settlement_currency;                /* byte 34 */
  uint8_t match_algorithm;                    /* byte 35 */
  uint8_t minimum_size[4];                    /* bytes 36 to 39 */
  uint8_t maximum_size[4];                    /* bytes 40 to 43 */
  uint8_t tick[8];                            /* bytes 44 to 51 */
  uint8_t unit_of_measure[5];                 /* bytes 52 to 56 */
  uint8_t unit_of_measure_quantity[4];        /* bytes 57 to 60 */
  uint8_t settlement_price[8];                /* bytes 61 to 68 */
  uint8_t settlement_price_type_calc_method;  /* byte 69 */
  uint8_t total_volume[4];                    /* bytes 70 to 73 */
  uint8_t open_interest_quantity[4];          /* bytes 74 to 77 */
  uint8_t high_limit_price[8];                /* bytes 78 to 85 */
  uint8_t low_limit_price[8];                 /* bytes 86 to 93 */
  uint8_t trading_collar_variation_type;      /* byte 94 */
  uint8_t trading_collar_variation[8];        /* bytes 95 to 102 */
  uint8_t reserved_16[16];                    /* bytes 103 to 118 */
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
  for (size_t i = 0; i < 4; i++) { record->maturity_month_year[i] = arbitrary(); }
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
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Simple Instrument Definition Message to the wire: 119 bytes from at, returning where the next byte goes */
static size_t encode_simple_instrument_definition_message(const SimpleInstrumentDefinitionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->underlying_asset_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_asset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->product_group_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange[i]; }
  wire[at++] = record->instrument_id_source;
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_month_year[i]; }
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
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Simple Instrument Definition Message off the wire: 119 bytes from at, returning where the next byte lies */
static size_t decode_simple_instrument_definition_message(SimpleInstrumentDefinitionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->underlying_asset_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->underlying_asset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->product_group_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->exchange[i] = wire[at++]; }
  record->instrument_id_source = wire[at++];
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->maturity_month_year[i] = wire[at++]; }
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
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

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
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_month_year[i] == written->maturity_month_year[i]); }
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
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Simple Instrument Definition Message: written and read back, then read and written back */
static void check_simple_instrument_definition_message(void) {
  SimpleInstrumentDefinitionMessage sent;
  SimpleInstrumentDefinitionMessage got;
  uint8_t wire[119];
  uint8_t again[119];

  any_simple_instrument_definition_message(&sent);
  assert(encode_simple_instrument_definition_message(&sent, wire, 0) == 119);
  assert(decode_simple_instrument_definition_message(&got, wire, 0) == 119);
  equal_simple_instrument_definition_message(&got, &sent);

  for (size_t i = 0; i < 119; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_instrument_definition_message(&got, wire, 0) == 119);
  assert(encode_simple_instrument_definition_message(&got, again, 0) == 119);
  for (size_t i = 0; i < 119; i++) { assert(again[i] == wire[i]); }
}

/* ---- System State Message: 18 bytes ------------------------------------------ */

typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t tom_version[8];  /* bytes 8 to 15 */
  uint8_t session_id;      /* byte 16 */
  uint8_t system_status;   /* byte 17 */
} SystemStateMessage;

/* any System State Message at all: every byte one the checker chooses */
static void any_system_state_message(SystemStateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tom_version[i] = arbitrary(); }
  record->session_id = arbitrary();
  record->system_status = arbitrary();
}

/* System State Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_system_state_message(const SystemStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tom_version[i]; }
  wire[at++] = record->session_id;
  wire[at++] = record->system_status;

  return at;
}

/* System State Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_system_state_message(SystemStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tom_version[i] = wire[at++]; }
  record->session_id = wire[at++];
  record->system_status = wire[at++];

  return at;
}

/* what was read of System State Message is what was written, byte for byte */
static void equal_system_state_message(const SystemStateMessage *read, const SystemStateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tom_version[i] == written->tom_version[i]); }
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

/* Used to notify firms of changes to the trading status of a particular Simple or Complex instrument */
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

/* used to publish MIAX Futures Onyx Best Bid and Offer (MBBO) of a Simple Instrument or Complex Instrument */
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

/* ---- Last Sale Message: 32 bytes --------------------------------------------- */

/* used to disseminate trades that are resulting from executions on MIAX Futures Onyx during the current trading session */
typedef struct {
  uint8_t timestamp[8];      /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t trade_id[8];       /* bytes 12 to 19 */
  uint8_t price[8];          /* bytes 20 to 27 */
  uint8_t size[4];           /* bytes 28 to 31 */
} LastSaleMessage;

/* any Last Sale Message at all: every byte one the checker chooses */
static void any_last_sale_message(LastSaleMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
}

/* Last Sale Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_last_sale_message(const LastSaleMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }

  return at;
}

/* Last Sale Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_last_sale_message(LastSaleMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }

  return at;
}

/* what was read of Last Sale Message is what was written, byte for byte */
static void equal_last_sale_message(const LastSaleMessage *read, const LastSaleMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
}

/* Last Sale Message: written and read back, then read and written back */
static void check_last_sale_message(void) {
  LastSaleMessage sent;
  LastSaleMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_last_sale_message(&sent);
  assert(encode_last_sale_message(&sent, wire, 0) == 32);
  assert(decode_last_sale_message(&got, wire, 0) == 32);
  equal_last_sale_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_last_sale_message(&got, wire, 0) == 32);
  assert(encode_last_sale_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Message: 35 bytes ------------------------------------------ */

/* used to publish cancellation of a Simple Instrument trade which was previously published via an Order Execution Message */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t trade_date[2];      /* bytes 8 to 9 */
  uint8_t instrument_id[4];   /* bytes 10 to 13 */
  uint8_t trade_id[8];        /* bytes 14 to 21 */
  uint8_t correction_number;  /* byte 22 */
  uint8_t price[8];           /* bytes 23 to 30 */
  uint8_t size[4];            /* bytes 31 to 34 */
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
}

/* Trade Cancel Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_message(const TradeCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->correction_number;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }

  return at;
}

/* Trade Cancel Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_message(TradeCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  record->correction_number = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }

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
}

/* Trade Cancel Message: written and read back, then read and written back */
static void check_trade_cancel_message(void) {
  TradeCancelMessage sent;
  TradeCancelMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_trade_cancel_message(&sent);
  assert(encode_trade_cancel_message(&sent, wire, 0) == 35);
  assert(decode_trade_cancel_message(&got, wire, 0) == 35);
  equal_trade_cancel_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_message(&got, wire, 0) == 35);
  assert(encode_trade_cancel_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_mach_packet_header();
  check_simple_instrument_definition_message();
  check_system_state_message();
  check_instrument_trading_status_notification_message();
  check_best_bid_and_offer_message();
  check_last_sale_message();
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
