// miax/miaxoptions/complextopofmarket/MiaxOptions_ComplexTopOfMarket_v1_1.c
/*
 * Miami International Holdings Complex Top Of Market
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

/* ---- System Time Message: 4 bytes -------------------------------------------- */

/* This is the message format that will be used to disseminate the “seconds” part of the timestamp that is applicable to all messages that are sent in the current second. */
typedef struct {
  uint8_t seconds[4];  /* bytes 0 to 3 */
} SystemTimeMessage;

/* any System Time Message at all: every byte one the checker chooses */
static void any_system_time_message(SystemTimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
}

/* System Time Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_system_time_message(const SystemTimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }

  return at;
}

/* System Time Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_system_time_message(SystemTimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }

  return at;
}

/* what was read of System Time Message is what was written, byte for byte */
static void equal_system_time_message(const SystemTimeMessage *read, const SystemTimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
}

/* System Time Message: written and read back, then read and written back */
static void check_system_time_message(void) {
  SystemTimeMessage sent;
  SystemTimeMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_system_time_message(&sent);
  assert(encode_system_time_message(&sent, wire, 0) == 4);
  assert(decode_system_time_message(&got, wire, 0) == 4);
  equal_system_time_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_system_time_message(&got, wire, 0) == 4);
  assert(encode_system_time_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Series Update: 72 bytes ------------------------------------------------- */

/* This is the message format that will be used to disseminate all Option series traded on MIAX for the current session. The product ID sent in this message is what will be disseminated in Top of Market BBO and Last Sale messages. */
typedef struct {
  uint8_t nanoseconds[4];                            /* bytes 0 to 3 */
  uint8_t product_id[4];                             /* bytes 4 to 7 */
  uint8_t underlying_symbol[11];                     /* bytes 8 to 18 */
  uint8_t security_symbol[6];                        /* bytes 19 to 24 */
  uint8_t expiration_date[8];                        /* bytes 25 to 32 */
  uint8_t strike_price[4];                           /* bytes 33 to 36 */
  uint8_t call_or_put;                               /* byte 37 */
  uint8_t opening_time[8];                           /* bytes 38 to 45 */
  uint8_t closing_time[8];                           /* bytes 46 to 53 */
  uint8_t restricted_option;                         /* byte 54 */
  uint8_t long_term_option;                          /* byte 55 */
  uint8_t active_on_miax;                            /* byte 56 */
  uint8_t miax_bbo_posting_increment_indicator;      /* byte 57 */
  uint8_t liquidity_acceptance_increment_indicator;  /* byte 58 */
  uint8_t opening_underlying_market_code;            /* byte 59 */
  uint8_t priority_quote_width[4];                   /* bytes 60 to 63 */
  uint8_t reserved_8[8];                             /* bytes 64 to 71 */
} SeriesUpdate;

/* any Series Update at all: every byte one the checker chooses */
static void any_series_update(SeriesUpdate *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->security_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  record->call_or_put = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->opening_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_time[i] = arbitrary(); }
  record->restricted_option = arbitrary();
  record->long_term_option = arbitrary();
  record->active_on_miax = arbitrary();
  record->miax_bbo_posting_increment_indicator = arbitrary();
  record->liquidity_acceptance_increment_indicator = arbitrary();
  record->opening_underlying_market_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->priority_quote_width[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Series Update to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_series_update(const SeriesUpdate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->security_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->call_or_put;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_time[i]; }
  wire[at++] = record->restricted_option;
  wire[at++] = record->long_term_option;
  wire[at++] = record->active_on_miax;
  wire[at++] = record->miax_bbo_posting_increment_indicator;
  wire[at++] = record->liquidity_acceptance_increment_indicator;
  wire[at++] = record->opening_underlying_market_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority_quote_width[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Series Update off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_series_update(SeriesUpdate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->security_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  record->call_or_put = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->opening_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_time[i] = wire[at++]; }
  record->restricted_option = wire[at++];
  record->long_term_option = wire[at++];
  record->active_on_miax = wire[at++];
  record->miax_bbo_posting_increment_indicator = wire[at++];
  record->liquidity_acceptance_increment_indicator = wire[at++];
  record->opening_underlying_market_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->priority_quote_width[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Series Update is what was written, byte for byte */
static void equal_series_update(const SeriesUpdate *read, const SeriesUpdate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->call_or_put == written->call_or_put);
  for (size_t i = 0; i < 8; i++) { assert(read->opening_time[i] == written->opening_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_time[i] == written->closing_time[i]); }
  assert(read->restricted_option == written->restricted_option);
  assert(read->long_term_option == written->long_term_option);
  assert(read->active_on_miax == written->active_on_miax);
  assert(read->miax_bbo_posting_increment_indicator == written->miax_bbo_posting_increment_indicator);
  assert(read->liquidity_acceptance_increment_indicator == written->liquidity_acceptance_increment_indicator);
  assert(read->opening_underlying_market_code == written->opening_underlying_market_code);
  for (size_t i = 0; i < 4; i++) { assert(read->priority_quote_width[i] == written->priority_quote_width[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Series Update: written and read back, then read and written back */
static void check_series_update(void) {
  SeriesUpdate sent;
  SeriesUpdate got;
  uint8_t wire[72];
  uint8_t again[72];

  any_series_update(&sent);
  assert(encode_series_update(&sent, wire, 0) == 72);
  assert(decode_series_update(&got, wire, 0) == 72);
  equal_series_update(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_series_update(&got, wire, 0) == 72);
  assert(encode_series_update(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- System State Message: 17 bytes ------------------------------------------ */

/* This message format is used to notify the firms of the state changes of the system. This is a notification that applies to each Underlying group. Firms can use notifications as triggers in their system to ensure electronic synchronization of systems. */
typedef struct {
  uint8_t nanoseconds[4];     /* bytes 0 to 3 */
  uint8_t c_to_m_version[8];  /* bytes 4 to 11 */
  uint8_t session_id[4];      /* bytes 12 to 15 */
  uint8_t system_status;      /* byte 16 */
} SystemStateMessage;

/* any System State Message at all: every byte one the checker chooses */
static void any_system_state_message(SystemStateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->c_to_m_version[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  record->system_status = arbitrary();
}

/* System State Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_system_state_message(const SystemStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->c_to_m_version[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  wire[at++] = record->system_status;

  return at;
}

/* System State Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_system_state_message(SystemStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->c_to_m_version[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  record->system_status = wire[at++];

  return at;
}

/* what was read of System State Message is what was written, byte for byte */
static void equal_system_state_message(const SystemStateMessage *read, const SystemStateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->c_to_m_version[i] == written->c_to_m_version[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  assert(read->system_status == written->system_status);
}

/* System State Message: written and read back, then read and written back */
static void check_system_state_message(void) {
  SystemStateMessage sent;
  SystemStateMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_system_state_message(&sent);
  assert(encode_system_state_message(&sent, wire, 0) == 17);
  assert(decode_system_state_message(&got, wire, 0) == 17);
  equal_system_state_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_system_state_message(&got, wire, 0) == 17);
  assert(encode_system_state_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Compact Complex Top Of Market Bid Message: 13 bytes --------------------- */

/* This is the message format that will be used to disseminate each side of the MIAX Complex Top of Market for options with low Net Price and small aggregate MIAX Best Bid or Offer (MBBO) size */
typedef struct {
  uint8_t nanoseconds[4];                 /* bytes 0 to 3 */
  uint8_t strategy_id[4];                 /* bytes 4 to 7 */
  uint8_t compact_price[2];               /* bytes 8 to 9 */
  uint8_t compact_size[2];                /* bytes 10 to 11 */
  uint8_t top_of_market_quote_condition;  /* byte 12 */
} CompactComplexTopOfMarketBidMessage;

/* any Compact Complex Top Of Market Bid Message at all: every byte one the checker chooses */
static void any_compact_complex_top_of_market_bid_message(CompactComplexTopOfMarketBidMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->compact_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->compact_size[i] = arbitrary(); }
  record->top_of_market_quote_condition = arbitrary();
}

/* Compact Complex Top Of Market Bid Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_compact_complex_top_of_market_bid_message(const CompactComplexTopOfMarketBidMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->compact_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->compact_size[i]; }
  wire[at++] = record->top_of_market_quote_condition;

  return at;
}

/* Compact Complex Top Of Market Bid Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_compact_complex_top_of_market_bid_message(CompactComplexTopOfMarketBidMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->compact_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->compact_size[i] = wire[at++]; }
  record->top_of_market_quote_condition = wire[at++];

  return at;
}

/* what was read of Compact Complex Top Of Market Bid Message is what was written, byte for byte */
static void equal_compact_complex_top_of_market_bid_message(const CompactComplexTopOfMarketBidMessage *read, const CompactComplexTopOfMarketBidMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->compact_price[i] == written->compact_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->compact_size[i] == written->compact_size[i]); }
  assert(read->top_of_market_quote_condition == written->top_of_market_quote_condition);
}

/* Compact Complex Top Of Market Bid Message: written and read back, then read and written back */
static void check_compact_complex_top_of_market_bid_message(void) {
  CompactComplexTopOfMarketBidMessage sent;
  CompactComplexTopOfMarketBidMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_compact_complex_top_of_market_bid_message(&sent);
  assert(encode_compact_complex_top_of_market_bid_message(&sent, wire, 0) == 13);
  assert(decode_compact_complex_top_of_market_bid_message(&got, wire, 0) == 13);
  equal_compact_complex_top_of_market_bid_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_compact_complex_top_of_market_bid_message(&got, wire, 0) == 13);
  assert(encode_compact_complex_top_of_market_bid_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Compact Complex Top Of Market Offer Message: 15 bytes ------------------- */

/* This is the message format that will be used to disseminate each side of the MIAX Top of Market for options with low premiums and small aggregate MIAX Best Bid or Offer (MBBO) size */
typedef struct {
  uint8_t nanoseconds[4];                 /* bytes 0 to 3 */
  uint8_t strategy_id[4];                 /* bytes 4 to 7 */
  uint8_t compact_price[2];               /* bytes 8 to 9 */
  uint8_t compact_size[2];                /* bytes 10 to 11 */
  uint8_t reserved_2[2];                  /* bytes 12 to 13 */
  uint8_t top_of_market_quote_condition;  /* byte 14 */
} CompactComplexTopOfMarketOfferMessage;

/* any Compact Complex Top Of Market Offer Message at all: every byte one the checker chooses */
static void any_compact_complex_top_of_market_offer_message(CompactComplexTopOfMarketOfferMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->compact_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->compact_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->top_of_market_quote_condition = arbitrary();
}

/* Compact Complex Top Of Market Offer Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_compact_complex_top_of_market_offer_message(const CompactComplexTopOfMarketOfferMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->compact_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->compact_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->top_of_market_quote_condition;

  return at;
}

/* Compact Complex Top Of Market Offer Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_compact_complex_top_of_market_offer_message(CompactComplexTopOfMarketOfferMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->compact_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->compact_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->top_of_market_quote_condition = wire[at++];

  return at;
}

/* what was read of Compact Complex Top Of Market Offer Message is what was written, byte for byte */
static void equal_compact_complex_top_of_market_offer_message(const CompactComplexTopOfMarketOfferMessage *read, const CompactComplexTopOfMarketOfferMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->compact_price[i] == written->compact_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->compact_size[i] == written->compact_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->top_of_market_quote_condition == written->top_of_market_quote_condition);
}

/* Compact Complex Top Of Market Offer Message: written and read back, then read and written back */
static void check_compact_complex_top_of_market_offer_message(void) {
  CompactComplexTopOfMarketOfferMessage sent;
  CompactComplexTopOfMarketOfferMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_compact_complex_top_of_market_offer_message(&sent);
  assert(encode_compact_complex_top_of_market_offer_message(&sent, wire, 0) == 15);
  assert(decode_compact_complex_top_of_market_offer_message(&got, wire, 0) == 15);
  equal_compact_complex_top_of_market_offer_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_compact_complex_top_of_market_offer_message(&got, wire, 0) == 15);
  assert(encode_compact_complex_top_of_market_offer_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Wide Complex Top Of Market Bid Message: 25 bytes ------------------------ */

/* This is the message format that will be used to disseminate MIAX Complex Top of Market for strategies with high net price or large aggregate MIAX Best Bid or Offer (MBBO) size. */
typedef struct {
  uint8_t nanoseconds[4];                 /* bytes 0 to 3 */
  uint8_t strategy_id[4];                 /* bytes 4 to 7 */
  uint8_t wide_price[8];                  /* bytes 8 to 15 */
  uint8_t wide_size[4];                   /* bytes 16 to 19 */
  uint8_t reserved_4[4];                  /* bytes 20 to 23 */
  uint8_t top_of_market_quote_condition;  /* byte 24 */
} WideComplexTopOfMarketBidMessage;

/* any Wide Complex Top Of Market Bid Message at all: every byte one the checker chooses */
static void any_wide_complex_top_of_market_bid_message(WideComplexTopOfMarketBidMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->wide_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->wide_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  record->top_of_market_quote_condition = arbitrary();
}

/* Wide Complex Top Of Market Bid Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_wide_complex_top_of_market_bid_message(const WideComplexTopOfMarketBidMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->wide_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->wide_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  wire[at++] = record->top_of_market_quote_condition;

  return at;
}

/* Wide Complex Top Of Market Bid Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_wide_complex_top_of_market_bid_message(WideComplexTopOfMarketBidMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->wide_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->wide_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  record->top_of_market_quote_condition = wire[at++];

  return at;
}

/* what was read of Wide Complex Top Of Market Bid Message is what was written, byte for byte */
static void equal_wide_complex_top_of_market_bid_message(const WideComplexTopOfMarketBidMessage *read, const WideComplexTopOfMarketBidMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->wide_price[i] == written->wide_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->wide_size[i] == written->wide_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  assert(read->top_of_market_quote_condition == written->top_of_market_quote_condition);
}

/* Wide Complex Top Of Market Bid Message: written and read back, then read and written back */
static void check_wide_complex_top_of_market_bid_message(void) {
  WideComplexTopOfMarketBidMessage sent;
  WideComplexTopOfMarketBidMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_wide_complex_top_of_market_bid_message(&sent);
  assert(encode_wide_complex_top_of_market_bid_message(&sent, wire, 0) == 25);
  assert(decode_wide_complex_top_of_market_bid_message(&got, wire, 0) == 25);
  equal_wide_complex_top_of_market_bid_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_wide_complex_top_of_market_bid_message(&got, wire, 0) == 25);
  assert(encode_wide_complex_top_of_market_bid_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Wide Complex Top Of Market Offer Message: 25 bytes ---------------------- */

/* This is the message format that will be used to disseminate MIAX Complex Top of Market for strategies with high net price or large aggregate MIAX Best Offer (MBBO) size. */
typedef struct {
  uint8_t nanoseconds[4];                 /* bytes 0 to 3 */
  uint8_t strategy_id[4];                 /* bytes 4 to 7 */
  uint8_t wide_price[8];                  /* bytes 8 to 15 */
  uint8_t wide_size[4];                   /* bytes 16 to 19 */
  uint8_t reserved_4[4];                  /* bytes 20 to 23 */
  uint8_t top_of_market_quote_condition;  /* byte 24 */
} WideComplexTopOfMarketOfferMessage;

/* any Wide Complex Top Of Market Offer Message at all: every byte one the checker chooses */
static void any_wide_complex_top_of_market_offer_message(WideComplexTopOfMarketOfferMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->wide_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->wide_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  record->top_of_market_quote_condition = arbitrary();
}

/* Wide Complex Top Of Market Offer Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_wide_complex_top_of_market_offer_message(const WideComplexTopOfMarketOfferMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->wide_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->wide_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  wire[at++] = record->top_of_market_quote_condition;

  return at;
}

/* Wide Complex Top Of Market Offer Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_wide_complex_top_of_market_offer_message(WideComplexTopOfMarketOfferMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->wide_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->wide_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  record->top_of_market_quote_condition = wire[at++];

  return at;
}

/* what was read of Wide Complex Top Of Market Offer Message is what was written, byte for byte */
static void equal_wide_complex_top_of_market_offer_message(const WideComplexTopOfMarketOfferMessage *read, const WideComplexTopOfMarketOfferMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->wide_price[i] == written->wide_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->wide_size[i] == written->wide_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  assert(read->top_of_market_quote_condition == written->top_of_market_quote_condition);
}

/* Wide Complex Top Of Market Offer Message: written and read back, then read and written back */
static void check_wide_complex_top_of_market_offer_message(void) {
  WideComplexTopOfMarketOfferMessage sent;
  WideComplexTopOfMarketOfferMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_wide_complex_top_of_market_offer_message(&sent);
  assert(encode_wide_complex_top_of_market_offer_message(&sent, wire, 0) == 25);
  assert(decode_wide_complex_top_of_market_offer_message(&got, wire, 0) == 25);
  equal_wide_complex_top_of_market_offer_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_wide_complex_top_of_market_offer_message(&got, wire, 0) == 25);
  assert(encode_wide_complex_top_of_market_offer_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Compact Bid: 7 bytes ---------------------------------------------------- */

/* Compact Bid */
typedef struct {
  uint8_t compact_bid_price[2];  /* bytes 0 to 1 */
  uint8_t compact_bid_size[2];   /* bytes 2 to 3 */
  uint8_t reserved_2[2];         /* bytes 4 to 5 */
  uint8_t bid_condition;         /* byte 6 */
} CompactBid;

/* any Compact Bid at all: every byte one the checker chooses */
static void any_compact_bid(CompactBid *record) {
  for (size_t i = 0; i < 2; i++) { record->compact_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->compact_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->bid_condition = arbitrary();
}

/* Compact Bid to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_compact_bid(const CompactBid *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->compact_bid_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->compact_bid_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->bid_condition;

  return at;
}

/* Compact Bid off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_compact_bid(CompactBid *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->compact_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->compact_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->bid_condition = wire[at++];

  return at;
}

/* what was read of Compact Bid is what was written, byte for byte */
static void equal_compact_bid(const CompactBid *read, const CompactBid *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->compact_bid_price[i] == written->compact_bid_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->compact_bid_size[i] == written->compact_bid_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->bid_condition == written->bid_condition);
}

/* Compact Bid: written and read back, then read and written back */
static void check_compact_bid(void) {
  CompactBid sent;
  CompactBid got;
  uint8_t wire[7];
  uint8_t again[7];

  any_compact_bid(&sent);
  assert(encode_compact_bid(&sent, wire, 0) == 7);
  assert(decode_compact_bid(&got, wire, 0) == 7);
  equal_compact_bid(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_compact_bid(&got, wire, 0) == 7);
  assert(encode_compact_bid(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Compact Offer: 7 bytes -------------------------------------------------- */

/* Compact Offer */
typedef struct {
  uint8_t compact_offer_price[2];  /* bytes 0 to 1 */
  uint8_t compact_offer_size[2];   /* bytes 2 to 3 */
  uint8_t reserved_2[2];           /* bytes 4 to 5 */
  uint8_t offer_condition;         /* byte 6 */
} CompactOffer;

/* any Compact Offer at all: every byte one the checker chooses */
static void any_compact_offer(CompactOffer *record) {
  for (size_t i = 0; i < 2; i++) { record->compact_offer_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->compact_offer_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->offer_condition = arbitrary();
}

/* Compact Offer to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_compact_offer(const CompactOffer *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->compact_offer_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->compact_offer_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->offer_condition;

  return at;
}

/* Compact Offer off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_compact_offer(CompactOffer *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->compact_offer_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->compact_offer_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->offer_condition = wire[at++];

  return at;
}

/* what was read of Compact Offer is what was written, byte for byte */
static void equal_compact_offer(const CompactOffer *read, const CompactOffer *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->compact_offer_price[i] == written->compact_offer_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->compact_offer_size[i] == written->compact_offer_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->offer_condition == written->offer_condition);
}

/* Compact Offer: written and read back, then read and written back */
static void check_compact_offer(void) {
  CompactOffer sent;
  CompactOffer got;
  uint8_t wire[7];
  uint8_t again[7];

  any_compact_offer(&sent);
  assert(encode_compact_offer(&sent, wire, 0) == 7);
  assert(decode_compact_offer(&got, wire, 0) == 7);
  equal_compact_offer(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_compact_offer(&got, wire, 0) == 7);
  assert(encode_compact_offer(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Compact Complex Double Sided Top Of Market Message: 22 bytes ------------ */

/* This is the message format that will be used to disseminate both sides of the MIAX top of market for strategies (cMBBO) with low net price and small aggregate size. */
typedef struct {
  uint8_t nanoseconds[4];      /* bytes 0 to 3 */
  uint8_t strategy_id[4];      /* bytes 4 to 7 */
  CompactBid compact_bid;      /* bytes 8 to 14 */
  CompactOffer compact_offer;  /* bytes 15 to 21 */
} CompactComplexDoubleSidedTopOfMarketMessage;

/* any Compact Complex Double Sided Top Of Market Message at all: every byte one the checker chooses */
static void any_compact_complex_double_sided_top_of_market_message(CompactComplexDoubleSidedTopOfMarketMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  any_compact_bid(&record->compact_bid);
  any_compact_offer(&record->compact_offer);
}

/* Compact Complex Double Sided Top Of Market Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_compact_complex_double_sided_top_of_market_message(const CompactComplexDoubleSidedTopOfMarketMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  at = encode_compact_bid(&record->compact_bid, wire, at);
  at = encode_compact_offer(&record->compact_offer, wire, at);

  return at;
}

/* Compact Complex Double Sided Top Of Market Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_compact_complex_double_sided_top_of_market_message(CompactComplexDoubleSidedTopOfMarketMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  at = decode_compact_bid(&record->compact_bid, wire, at);
  at = decode_compact_offer(&record->compact_offer, wire, at);

  return at;
}

/* what was read of Compact Complex Double Sided Top Of Market Message is what was written, byte for byte */
static void equal_compact_complex_double_sided_top_of_market_message(const CompactComplexDoubleSidedTopOfMarketMessage *read, const CompactComplexDoubleSidedTopOfMarketMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  equal_compact_bid(&read->compact_bid, &written->compact_bid);
  equal_compact_offer(&read->compact_offer, &written->compact_offer);
}

/* Compact Complex Double Sided Top Of Market Message: written and read back, then read and written back */
static void check_compact_complex_double_sided_top_of_market_message(void) {
  CompactComplexDoubleSidedTopOfMarketMessage sent;
  CompactComplexDoubleSidedTopOfMarketMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_compact_complex_double_sided_top_of_market_message(&sent);
  assert(encode_compact_complex_double_sided_top_of_market_message(&sent, wire, 0) == 22);
  assert(decode_compact_complex_double_sided_top_of_market_message(&got, wire, 0) == 22);
  equal_compact_complex_double_sided_top_of_market_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_compact_complex_double_sided_top_of_market_message(&got, wire, 0) == 22);
  assert(encode_compact_complex_double_sided_top_of_market_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Wide Bid: 17 bytes ------------------------------------------------------ */

/* Wide Bid */
typedef struct {
  uint8_t wide_bid_price[8];  /* bytes 0 to 7 */
  uint8_t wide_bid_size[4];   /* bytes 8 to 11 */
  uint8_t reserved_4[4];      /* bytes 12 to 15 */
  uint8_t bid_condition;      /* byte 16 */
} WideBid;

/* any Wide Bid at all: every byte one the checker chooses */
static void any_wide_bid(WideBid *record) {
  for (size_t i = 0; i < 8; i++) { record->wide_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->wide_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  record->bid_condition = arbitrary();
}

/* Wide Bid to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_wide_bid(const WideBid *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->wide_bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->wide_bid_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  wire[at++] = record->bid_condition;

  return at;
}

/* Wide Bid off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_wide_bid(WideBid *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->wide_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->wide_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  record->bid_condition = wire[at++];

  return at;
}

/* what was read of Wide Bid is what was written, byte for byte */
static void equal_wide_bid(const WideBid *read, const WideBid *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->wide_bid_price[i] == written->wide_bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->wide_bid_size[i] == written->wide_bid_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  assert(read->bid_condition == written->bid_condition);
}

/* Wide Bid: written and read back, then read and written back */
static void check_wide_bid(void) {
  WideBid sent;
  WideBid got;
  uint8_t wire[17];
  uint8_t again[17];

  any_wide_bid(&sent);
  assert(encode_wide_bid(&sent, wire, 0) == 17);
  assert(decode_wide_bid(&got, wire, 0) == 17);
  equal_wide_bid(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_wide_bid(&got, wire, 0) == 17);
  assert(encode_wide_bid(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Wide Offer: 17 bytes ---------------------------------------------------- */

/* Wide Offer */
typedef struct {
  uint8_t wide_offer_price[8];  /* bytes 0 to 7 */
  uint8_t wide_offer_size[4];   /* bytes 8 to 11 */
  uint8_t reserved_4[4];        /* bytes 12 to 15 */
  uint8_t offer_condition;      /* byte 16 */
} WideOffer;

/* any Wide Offer at all: every byte one the checker chooses */
static void any_wide_offer(WideOffer *record) {
  for (size_t i = 0; i < 8; i++) { record->wide_offer_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->wide_offer_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  record->offer_condition = arbitrary();
}

/* Wide Offer to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_wide_offer(const WideOffer *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->wide_offer_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->wide_offer_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  wire[at++] = record->offer_condition;

  return at;
}

/* Wide Offer off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_wide_offer(WideOffer *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->wide_offer_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->wide_offer_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  record->offer_condition = wire[at++];

  return at;
}

/* what was read of Wide Offer is what was written, byte for byte */
static void equal_wide_offer(const WideOffer *read, const WideOffer *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->wide_offer_price[i] == written->wide_offer_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->wide_offer_size[i] == written->wide_offer_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  assert(read->offer_condition == written->offer_condition);
}

/* Wide Offer: written and read back, then read and written back */
static void check_wide_offer(void) {
  WideOffer sent;
  WideOffer got;
  uint8_t wire[17];
  uint8_t again[17];

  any_wide_offer(&sent);
  assert(encode_wide_offer(&sent, wire, 0) == 17);
  assert(decode_wide_offer(&got, wire, 0) == 17);
  equal_wide_offer(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_wide_offer(&got, wire, 0) == 17);
  assert(encode_wide_offer(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Wide Complex Double Sided Top Of Market Message: 42 bytes --------------- */

/* This is the message format that will be used to disseminate both sides of the MIAX top of market for strategies (cMBBO) with net prices or aggregate sizes which cannot be specified in the compact format. */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t strategy_id[4];  /* bytes 4 to 7 */
  WideBid wide_bid;        /* bytes 8 to 24 */
  WideOffer wide_offer;    /* bytes 25 to 41 */
} WideComplexDoubleSidedTopOfMarketMessage;

/* any Wide Complex Double Sided Top Of Market Message at all: every byte one the checker chooses */
static void any_wide_complex_double_sided_top_of_market_message(WideComplexDoubleSidedTopOfMarketMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  any_wide_bid(&record->wide_bid);
  any_wide_offer(&record->wide_offer);
}

/* Wide Complex Double Sided Top Of Market Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_wide_complex_double_sided_top_of_market_message(const WideComplexDoubleSidedTopOfMarketMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  at = encode_wide_bid(&record->wide_bid, wire, at);
  at = encode_wide_offer(&record->wide_offer, wire, at);

  return at;
}

/* Wide Complex Double Sided Top Of Market Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_wide_complex_double_sided_top_of_market_message(WideComplexDoubleSidedTopOfMarketMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  at = decode_wide_bid(&record->wide_bid, wire, at);
  at = decode_wide_offer(&record->wide_offer, wire, at);

  return at;
}

/* what was read of Wide Complex Double Sided Top Of Market Message is what was written, byte for byte */
static void equal_wide_complex_double_sided_top_of_market_message(const WideComplexDoubleSidedTopOfMarketMessage *read, const WideComplexDoubleSidedTopOfMarketMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  equal_wide_bid(&read->wide_bid, &written->wide_bid);
  equal_wide_offer(&read->wide_offer, &written->wide_offer);
}

/* Wide Complex Double Sided Top Of Market Message: written and read back, then read and written back */
static void check_wide_complex_double_sided_top_of_market_message(void) {
  WideComplexDoubleSidedTopOfMarketMessage sent;
  WideComplexDoubleSidedTopOfMarketMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_wide_complex_double_sided_top_of_market_message(&sent);
  assert(encode_wide_complex_double_sided_top_of_market_message(&sent, wire, 0) == 42);
  assert(decode_wide_complex_double_sided_top_of_market_message(&got, wire, 0) == 42);
  equal_wide_complex_double_sided_top_of_market_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_wide_complex_double_sided_top_of_market_message(&got, wire, 0) == 42);
  assert(encode_wide_complex_double_sided_top_of_market_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strategy Trade Message: 41 bytes ---------------------------------------- */

/* This is the message format that will be used to disseminate Trades that are resulting from executions on MIAX during the current trading session */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t strategy_id[4];   /* bytes 4 to 7 */
  uint8_t trade_id[4];      /* bytes 8 to 11 */
  uint8_t net_price[8];     /* bytes 12 to 19 */
  uint8_t trade_size[4];    /* bytes 20 to 23 */
  uint8_t trade_condition;  /* byte 24 */
  uint8_t reserved_16[16];  /* bytes 25 to 40 */
} StrategyTradeMessage;

/* any Strategy Trade Message at all: every byte one the checker chooses */
static void any_strategy_trade_message(StrategyTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->net_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = arbitrary(); }
  record->trade_condition = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Strategy Trade Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_strategy_trade_message(const StrategyTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->net_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_size[i]; }
  wire[at++] = record->trade_condition;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Strategy Trade Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_strategy_trade_message(StrategyTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->net_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = wire[at++]; }
  record->trade_condition = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Strategy Trade Message is what was written, byte for byte */
static void equal_strategy_trade_message(const StrategyTradeMessage *read, const StrategyTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->net_price[i] == written->net_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_size[i] == written->trade_size[i]); }
  assert(read->trade_condition == written->trade_condition);
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Strategy Trade Message: written and read back, then read and written back */
static void check_strategy_trade_message(void) {
  StrategyTradeMessage sent;
  StrategyTradeMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_strategy_trade_message(&sent);
  assert(encode_strategy_trade_message(&sent, wire, 0) == 41);
  assert(decode_strategy_trade_message(&got, wire, 0) == 41);
  equal_strategy_trade_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_strategy_trade_message(&got, wire, 0) == 41);
  assert(encode_strategy_trade_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Trading Status Message: 25 bytes ----------------------------- */

/* This message format will be used to notify firms of changes to the trading status of all the options of an underlying */
typedef struct {
  uint8_t nanoseconds[4];                            /* bytes 0 to 3 */
  uint8_t underlying_symbol[11];                     /* bytes 4 to 14 */
  uint8_t trading_status;                            /* byte 15 */
  uint8_t event_reason;                              /* byte 16 */
  uint8_t expected_event_time_seconds_part[4];       /* bytes 17 to 20 */
  uint8_t expected_event_time_nano_seconds_part[4];  /* bytes 21 to 24 */
} UnderlyingTradingStatusMessage;

/* any Underlying Trading Status Message at all: every byte one the checker chooses */
static void any_underlying_trading_status_message(UnderlyingTradingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->event_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->expected_event_time_seconds_part[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expected_event_time_nano_seconds_part[i] = arbitrary(); }
}

/* Underlying Trading Status Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_underlying_trading_status_message(const UnderlyingTradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->event_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expected_event_time_seconds_part[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expected_event_time_nano_seconds_part[i]; }

  return at;
}

/* Underlying Trading Status Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_underlying_trading_status_message(UnderlyingTradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->event_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->expected_event_time_seconds_part[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expected_event_time_nano_seconds_part[i] = wire[at++]; }

  return at;
}

/* what was read of Underlying Trading Status Message is what was written, byte for byte */
static void equal_underlying_trading_status_message(const UnderlyingTradingStatusMessage *read, const UnderlyingTradingStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->event_reason == written->event_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->expected_event_time_seconds_part[i] == written->expected_event_time_seconds_part[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expected_event_time_nano_seconds_part[i] == written->expected_event_time_nano_seconds_part[i]); }
}

/* Underlying Trading Status Message: written and read back, then read and written back */
static void check_underlying_trading_status_message(void) {
  UnderlyingTradingStatusMessage sent;
  UnderlyingTradingStatusMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_underlying_trading_status_message(&sent);
  assert(encode_underlying_trading_status_message(&sent, wire, 0) == 25);
  assert(decode_underlying_trading_status_message(&got, wire, 0) == 25);
  equal_underlying_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_trading_status_message(&got, wire, 0) == 25);
  assert(encode_underlying_trading_status_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_mach_packet_header();
  check_system_time_message();
  check_series_update();
  check_system_state_message();
  check_compact_complex_top_of_market_bid_message();
  check_compact_complex_top_of_market_offer_message();
  check_wide_complex_top_of_market_bid_message();
  check_wide_complex_top_of_market_offer_message();
  check_compact_bid();
  check_compact_offer();
  check_compact_complex_double_sided_top_of_market_message();
  check_wide_bid();
  check_wide_offer();
  check_wide_complex_double_sided_top_of_market_message();
  check_strategy_trade_message();
  check_underlying_trading_status_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
