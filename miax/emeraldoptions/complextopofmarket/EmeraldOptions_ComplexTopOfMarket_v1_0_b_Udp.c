// miax/emeraldoptions/complextopofmarket/EmeraldOptions_ComplexTopOfMarket_v1_0_b_Udp.c
/*
 * Miami International Holdings Complex Top of Market
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

/* This is the message format that will be used to disseminate the "seconds" part of the timestamp that is applicable to all messages that are sent in the current second. */
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

/* ---- Simple Series Update Message: 72 bytes ---------------------------------- */

/* This is the message format that will be used to disseminate all Option series traded on Emerald for the current session. */
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
  uint8_t active_on_emerald;                         /* byte 56 */
  uint8_t emerald_bbo_posting_increment_indicator;   /* byte 57 */
  uint8_t liquidity_acceptance_increment_indicator;  /* byte 58 */
  uint8_t opening_underlying_market_code;            /* byte 59 */
  uint8_t priority_quote_width[4];                   /* bytes 60 to 63 */
  uint8_t reserved_8[8];                             /* bytes 64 to 71 */
} SimpleSeriesUpdateMessage;

/* any Simple Series Update Message at all: every byte one the checker chooses */
static void any_simple_series_update_message(SimpleSeriesUpdateMessage *record) {
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
  record->active_on_emerald = arbitrary();
  record->emerald_bbo_posting_increment_indicator = arbitrary();
  record->liquidity_acceptance_increment_indicator = arbitrary();
  record->opening_underlying_market_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->priority_quote_width[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Simple Series Update Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_simple_series_update_message(const SimpleSeriesUpdateMessage *record, uint8_t *wire, size_t at) {
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
  wire[at++] = record->active_on_emerald;
  wire[at++] = record->emerald_bbo_posting_increment_indicator;
  wire[at++] = record->liquidity_acceptance_increment_indicator;
  wire[at++] = record->opening_underlying_market_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority_quote_width[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Simple Series Update Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_simple_series_update_message(SimpleSeriesUpdateMessage *record, const uint8_t *wire, size_t at) {
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
  record->active_on_emerald = wire[at++];
  record->emerald_bbo_posting_increment_indicator = wire[at++];
  record->liquidity_acceptance_increment_indicator = wire[at++];
  record->opening_underlying_market_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->priority_quote_width[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Series Update Message is what was written, byte for byte */
static void equal_simple_series_update_message(const SimpleSeriesUpdateMessage *read, const SimpleSeriesUpdateMessage *written) {
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
  assert(read->active_on_emerald == written->active_on_emerald);
  assert(read->emerald_bbo_posting_increment_indicator == written->emerald_bbo_posting_increment_indicator);
  assert(read->liquidity_acceptance_increment_indicator == written->liquidity_acceptance_increment_indicator);
  assert(read->opening_underlying_market_code == written->opening_underlying_market_code);
  for (size_t i = 0; i < 4; i++) { assert(read->priority_quote_width[i] == written->priority_quote_width[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Simple Series Update Message: written and read back, then read and written back */
static void check_simple_series_update_message(void) {
  SimpleSeriesUpdateMessage sent;
  SimpleSeriesUpdateMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_simple_series_update_message(&sent);
  assert(encode_simple_series_update_message(&sent, wire, 0) == 72);
  assert(decode_simple_series_update_message(&got, wire, 0) == 72);
  equal_simple_series_update_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_series_update_message(&got, wire, 0) == 72);
  assert(encode_simple_series_update_message(&got, again, 0) == 72);
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

/* ---- Complex Top Of Market Best Bid Or Offer Compact Format Bid Message: 15 bytes ---- */

/* This is the message format that will be used to disseminate each side of the Emerald Complex Top of Market for strategies with low Net Price and small aggregate Emerald Best Bid or Offer (MBBO) size. Emerald Complex Top of Market on Bid side. */
typedef struct {
  uint8_t nanoseconds[4];                   /* bytes 0 to 3 */
  uint8_t strategy_id[4];                   /* bytes 4 to 7 */
  uint8_t price_short[2];                   /* bytes 8 to 9 */
  uint8_t size_short[2];                    /* bytes 10 to 11 */
  uint8_t priority_customer_size_short[2];  /* bytes 12 to 13 */
  uint8_t condition;                        /* byte 14 */
} ComplexTopOfMarketBestBidOrOfferCompactFormatBidMessage;

/* any Complex Top Of Market Best Bid Or Offer Compact Format Bid Message at all: every byte one the checker chooses */
static void any_complex_top_of_market_best_bid_or_offer_compact_format_bid_message(ComplexTopOfMarketBestBidOrOfferCompactFormatBidMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->size_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->priority_customer_size_short[i] = arbitrary(); }
  record->condition = arbitrary();
}

/* Complex Top Of Market Best Bid Or Offer Compact Format Bid Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_complex_top_of_market_best_bid_or_offer_compact_format_bid_message(const ComplexTopOfMarketBestBidOrOfferCompactFormatBidMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->size_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->priority_customer_size_short[i]; }
  wire[at++] = record->condition;

  return at;
}

/* Complex Top Of Market Best Bid Or Offer Compact Format Bid Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_complex_top_of_market_best_bid_or_offer_compact_format_bid_message(ComplexTopOfMarketBestBidOrOfferCompactFormatBidMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->size_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->priority_customer_size_short[i] = wire[at++]; }
  record->condition = wire[at++];

  return at;
}

/* what was read of Complex Top Of Market Best Bid Or Offer Compact Format Bid Message is what was written, byte for byte */
static void equal_complex_top_of_market_best_bid_or_offer_compact_format_bid_message(const ComplexTopOfMarketBestBidOrOfferCompactFormatBidMessage *read, const ComplexTopOfMarketBestBidOrOfferCompactFormatBidMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->size_short[i] == written->size_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->priority_customer_size_short[i] == written->priority_customer_size_short[i]); }
  assert(read->condition == written->condition);
}

/* Complex Top Of Market Best Bid Or Offer Compact Format Bid Message: written and read back, then read and written back */
static void check_complex_top_of_market_best_bid_or_offer_compact_format_bid_message(void) {
  ComplexTopOfMarketBestBidOrOfferCompactFormatBidMessage sent;
  ComplexTopOfMarketBestBidOrOfferCompactFormatBidMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_complex_top_of_market_best_bid_or_offer_compact_format_bid_message(&sent);
  assert(encode_complex_top_of_market_best_bid_or_offer_compact_format_bid_message(&sent, wire, 0) == 15);
  assert(decode_complex_top_of_market_best_bid_or_offer_compact_format_bid_message(&got, wire, 0) == 15);
  equal_complex_top_of_market_best_bid_or_offer_compact_format_bid_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_top_of_market_best_bid_or_offer_compact_format_bid_message(&got, wire, 0) == 15);
  assert(encode_complex_top_of_market_best_bid_or_offer_compact_format_bid_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Top Of Market Best Bid Or Offer Compact Format Offer Message: 15 bytes ---- */

/* This is the message format that will be used to disseminate each side of the Emerald Complex Top of Market for strategies with low Net Price and small aggregate Emerald Best Bid or Offer (MBBO) size. Emerald Complex Top of Market on Offer side. */
typedef struct {
  uint8_t nanoseconds[4];                   /* bytes 0 to 3 */
  uint8_t strategy_id[4];                   /* bytes 4 to 7 */
  uint8_t price_short[2];                   /* bytes 8 to 9 */
  uint8_t size_short[2];                    /* bytes 10 to 11 */
  uint8_t priority_customer_size_short[2];  /* bytes 12 to 13 */
  uint8_t condition;                        /* byte 14 */
} ComplexTopOfMarketBestBidOrOfferCompactFormatOfferMessage;

/* any Complex Top Of Market Best Bid Or Offer Compact Format Offer Message at all: every byte one the checker chooses */
static void any_complex_top_of_market_best_bid_or_offer_compact_format_offer_message(ComplexTopOfMarketBestBidOrOfferCompactFormatOfferMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->size_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->priority_customer_size_short[i] = arbitrary(); }
  record->condition = arbitrary();
}

/* Complex Top Of Market Best Bid Or Offer Compact Format Offer Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_complex_top_of_market_best_bid_or_offer_compact_format_offer_message(const ComplexTopOfMarketBestBidOrOfferCompactFormatOfferMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->size_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->priority_customer_size_short[i]; }
  wire[at++] = record->condition;

  return at;
}

/* Complex Top Of Market Best Bid Or Offer Compact Format Offer Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_complex_top_of_market_best_bid_or_offer_compact_format_offer_message(ComplexTopOfMarketBestBidOrOfferCompactFormatOfferMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->size_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->priority_customer_size_short[i] = wire[at++]; }
  record->condition = wire[at++];

  return at;
}

/* what was read of Complex Top Of Market Best Bid Or Offer Compact Format Offer Message is what was written, byte for byte */
static void equal_complex_top_of_market_best_bid_or_offer_compact_format_offer_message(const ComplexTopOfMarketBestBidOrOfferCompactFormatOfferMessage *read, const ComplexTopOfMarketBestBidOrOfferCompactFormatOfferMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->size_short[i] == written->size_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->priority_customer_size_short[i] == written->priority_customer_size_short[i]); }
  assert(read->condition == written->condition);
}

/* Complex Top Of Market Best Bid Or Offer Compact Format Offer Message: written and read back, then read and written back */
static void check_complex_top_of_market_best_bid_or_offer_compact_format_offer_message(void) {
  ComplexTopOfMarketBestBidOrOfferCompactFormatOfferMessage sent;
  ComplexTopOfMarketBestBidOrOfferCompactFormatOfferMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_complex_top_of_market_best_bid_or_offer_compact_format_offer_message(&sent);
  assert(encode_complex_top_of_market_best_bid_or_offer_compact_format_offer_message(&sent, wire, 0) == 15);
  assert(decode_complex_top_of_market_best_bid_or_offer_compact_format_offer_message(&got, wire, 0) == 15);
  equal_complex_top_of_market_best_bid_or_offer_compact_format_offer_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_top_of_market_best_bid_or_offer_compact_format_offer_message(&got, wire, 0) == 15);
  assert(encode_complex_top_of_market_best_bid_or_offer_compact_format_offer_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Top Of Market Best Bid Or Offer Wide Format Bid Message: 25 bytes ---- */

/* This is the message format that will be used to disseminate Emerald Complex Top of Market for strategies with high net price or large aggregate Emerald Best Bid or Offer (EBBO) size. Emerald Complex Top of Market on Bid side. */
typedef struct {
  uint8_t nanoseconds[4];                  /* bytes 0 to 3 */
  uint8_t strategy_id[4];                  /* bytes 4 to 7 */
  uint8_t price_long[8];                   /* bytes 8 to 15 */
  uint8_t size_long[4];                    /* bytes 16 to 19 */
  uint8_t priority_customer_size_long[4];  /* bytes 20 to 23 */
  uint8_t condition;                       /* byte 24 */
} ComplexTopOfMarketBestBidOrOfferWideFormatBidMessage;

/* any Complex Top Of Market Best Bid Or Offer Wide Format Bid Message at all: every byte one the checker chooses */
static void any_complex_top_of_market_best_bid_or_offer_wide_format_bid_message(ComplexTopOfMarketBestBidOrOfferWideFormatBidMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority_customer_size_long[i] = arbitrary(); }
  record->condition = arbitrary();
}

/* Complex Top Of Market Best Bid Or Offer Wide Format Bid Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_complex_top_of_market_best_bid_or_offer_wide_format_bid_message(const ComplexTopOfMarketBestBidOrOfferWideFormatBidMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority_customer_size_long[i]; }
  wire[at++] = record->condition;

  return at;
}

/* Complex Top Of Market Best Bid Or Offer Wide Format Bid Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_complex_top_of_market_best_bid_or_offer_wide_format_bid_message(ComplexTopOfMarketBestBidOrOfferWideFormatBidMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority_customer_size_long[i] = wire[at++]; }
  record->condition = wire[at++];

  return at;
}

/* what was read of Complex Top Of Market Best Bid Or Offer Wide Format Bid Message is what was written, byte for byte */
static void equal_complex_top_of_market_best_bid_or_offer_wide_format_bid_message(const ComplexTopOfMarketBestBidOrOfferWideFormatBidMessage *read, const ComplexTopOfMarketBestBidOrOfferWideFormatBidMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size_long[i] == written->size_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority_customer_size_long[i] == written->priority_customer_size_long[i]); }
  assert(read->condition == written->condition);
}

/* Complex Top Of Market Best Bid Or Offer Wide Format Bid Message: written and read back, then read and written back */
static void check_complex_top_of_market_best_bid_or_offer_wide_format_bid_message(void) {
  ComplexTopOfMarketBestBidOrOfferWideFormatBidMessage sent;
  ComplexTopOfMarketBestBidOrOfferWideFormatBidMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_complex_top_of_market_best_bid_or_offer_wide_format_bid_message(&sent);
  assert(encode_complex_top_of_market_best_bid_or_offer_wide_format_bid_message(&sent, wire, 0) == 25);
  assert(decode_complex_top_of_market_best_bid_or_offer_wide_format_bid_message(&got, wire, 0) == 25);
  equal_complex_top_of_market_best_bid_or_offer_wide_format_bid_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_top_of_market_best_bid_or_offer_wide_format_bid_message(&got, wire, 0) == 25);
  assert(encode_complex_top_of_market_best_bid_or_offer_wide_format_bid_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Top Of Market Best Bid Or Offer Wide Format Offer Message: 25 bytes ---- */

/* This is the message format that will be used to disseminate Emerald Complex Top of Market for strategies with high net price or large aggregate Emerald Best Bid or Offer (EBBO) size. Emerald Complex Top of Market on Offer side. */
typedef struct {
  uint8_t nanoseconds[4];                  /* bytes 0 to 3 */
  uint8_t strategy_id[4];                  /* bytes 4 to 7 */
  uint8_t price_long[8];                   /* bytes 8 to 15 */
  uint8_t size_long[4];                    /* bytes 16 to 19 */
  uint8_t priority_customer_size_long[4];  /* bytes 20 to 23 */
  uint8_t condition;                       /* byte 24 */
} ComplexTopOfMarketBestBidOrOfferWideFormatOfferMessage;

/* any Complex Top Of Market Best Bid Or Offer Wide Format Offer Message at all: every byte one the checker chooses */
static void any_complex_top_of_market_best_bid_or_offer_wide_format_offer_message(ComplexTopOfMarketBestBidOrOfferWideFormatOfferMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority_customer_size_long[i] = arbitrary(); }
  record->condition = arbitrary();
}

/* Complex Top Of Market Best Bid Or Offer Wide Format Offer Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_complex_top_of_market_best_bid_or_offer_wide_format_offer_message(const ComplexTopOfMarketBestBidOrOfferWideFormatOfferMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority_customer_size_long[i]; }
  wire[at++] = record->condition;

  return at;
}

/* Complex Top Of Market Best Bid Or Offer Wide Format Offer Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_complex_top_of_market_best_bid_or_offer_wide_format_offer_message(ComplexTopOfMarketBestBidOrOfferWideFormatOfferMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority_customer_size_long[i] = wire[at++]; }
  record->condition = wire[at++];

  return at;
}

/* what was read of Complex Top Of Market Best Bid Or Offer Wide Format Offer Message is what was written, byte for byte */
static void equal_complex_top_of_market_best_bid_or_offer_wide_format_offer_message(const ComplexTopOfMarketBestBidOrOfferWideFormatOfferMessage *read, const ComplexTopOfMarketBestBidOrOfferWideFormatOfferMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size_long[i] == written->size_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority_customer_size_long[i] == written->priority_customer_size_long[i]); }
  assert(read->condition == written->condition);
}

/* Complex Top Of Market Best Bid Or Offer Wide Format Offer Message: written and read back, then read and written back */
static void check_complex_top_of_market_best_bid_or_offer_wide_format_offer_message(void) {
  ComplexTopOfMarketBestBidOrOfferWideFormatOfferMessage sent;
  ComplexTopOfMarketBestBidOrOfferWideFormatOfferMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_complex_top_of_market_best_bid_or_offer_wide_format_offer_message(&sent);
  assert(encode_complex_top_of_market_best_bid_or_offer_wide_format_offer_message(&sent, wire, 0) == 25);
  assert(decode_complex_top_of_market_best_bid_or_offer_wide_format_offer_message(&got, wire, 0) == 25);
  equal_complex_top_of_market_best_bid_or_offer_wide_format_offer_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_top_of_market_best_bid_or_offer_wide_format_offer_message(&got, wire, 0) == 25);
  assert(encode_complex_top_of_market_best_bid_or_offer_wide_format_offer_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Double Sided Top Of Market Best Bid And Offer Compact Format Message: 22 bytes ---- */

/* This is the message format that will be used to disseminate both sides of the Emerald top of market for strategies (cEBBO) with low net price and small aggregate size. */
typedef struct {
  uint8_t nanoseconds[4];                         /* bytes 0 to 3 */
  uint8_t strategy_id[4];                         /* bytes 4 to 7 */
  uint8_t bid_price_short[2];                     /* bytes 8 to 9 */
  uint8_t bid_size_short[2];                      /* bytes 10 to 11 */
  uint8_t bid_priority_customer_size_short[2];    /* bytes 12 to 13 */
  uint8_t bid_condition;                          /* byte 14 */
  uint8_t offer_price_short[2];                   /* bytes 15 to 16 */
  uint8_t offer_size_short[2];                    /* bytes 17 to 18 */
  uint8_t offer_priority_customer_size_short[2];  /* bytes 19 to 20 */
  uint8_t offer_condition;                        /* byte 21 */
} ComplexDoubleSidedTopOfMarketBestBidAndOfferCompactFormatMessage;

/* any Complex Double Sided Top Of Market Best Bid And Offer Compact Format Message at all: every byte one the checker chooses */
static void any_complex_double_sided_top_of_market_best_bid_and_offer_compact_format_message(ComplexDoubleSidedTopOfMarketBestBidAndOfferCompactFormatMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_priority_customer_size_short[i] = arbitrary(); }
  record->bid_condition = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->offer_price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->offer_size_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->offer_priority_customer_size_short[i] = arbitrary(); }
  record->offer_condition = arbitrary();
}

/* Complex Double Sided Top Of Market Best Bid And Offer Compact Format Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_complex_double_sided_top_of_market_best_bid_and_offer_compact_format_message(const ComplexDoubleSidedTopOfMarketBestBidAndOfferCompactFormatMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_size_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_priority_customer_size_short[i]; }
  wire[at++] = record->bid_condition;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->offer_price_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->offer_size_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->offer_priority_customer_size_short[i]; }
  wire[at++] = record->offer_condition;

  return at;
}

/* Complex Double Sided Top Of Market Best Bid And Offer Compact Format Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_complex_double_sided_top_of_market_best_bid_and_offer_compact_format_message(ComplexDoubleSidedTopOfMarketBestBidAndOfferCompactFormatMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_size_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_priority_customer_size_short[i] = wire[at++]; }
  record->bid_condition = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->offer_price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->offer_size_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->offer_priority_customer_size_short[i] = wire[at++]; }
  record->offer_condition = wire[at++];

  return at;
}

/* what was read of Complex Double Sided Top Of Market Best Bid And Offer Compact Format Message is what was written, byte for byte */
static void equal_complex_double_sided_top_of_market_best_bid_and_offer_compact_format_message(const ComplexDoubleSidedTopOfMarketBestBidAndOfferCompactFormatMessage *read, const ComplexDoubleSidedTopOfMarketBestBidAndOfferCompactFormatMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_price_short[i] == written->bid_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_size_short[i] == written->bid_size_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_priority_customer_size_short[i] == written->bid_priority_customer_size_short[i]); }
  assert(read->bid_condition == written->bid_condition);
  for (size_t i = 0; i < 2; i++) { assert(read->offer_price_short[i] == written->offer_price_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->offer_size_short[i] == written->offer_size_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->offer_priority_customer_size_short[i] == written->offer_priority_customer_size_short[i]); }
  assert(read->offer_condition == written->offer_condition);
}

/* Complex Double Sided Top Of Market Best Bid And Offer Compact Format Message: written and read back, then read and written back */
static void check_complex_double_sided_top_of_market_best_bid_and_offer_compact_format_message(void) {
  ComplexDoubleSidedTopOfMarketBestBidAndOfferCompactFormatMessage sent;
  ComplexDoubleSidedTopOfMarketBestBidAndOfferCompactFormatMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_complex_double_sided_top_of_market_best_bid_and_offer_compact_format_message(&sent);
  assert(encode_complex_double_sided_top_of_market_best_bid_and_offer_compact_format_message(&sent, wire, 0) == 22);
  assert(decode_complex_double_sided_top_of_market_best_bid_and_offer_compact_format_message(&got, wire, 0) == 22);
  equal_complex_double_sided_top_of_market_best_bid_and_offer_compact_format_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_double_sided_top_of_market_best_bid_and_offer_compact_format_message(&got, wire, 0) == 22);
  assert(encode_complex_double_sided_top_of_market_best_bid_and_offer_compact_format_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Double Sided Top Of Market Best Bid And Offer Wide Format Message: 42 bytes ---- */

/* This is the message format that will be used to disseminate both sides of the Emerald top of market for strategies (cEBBO) with net prices or aggregate sizes which cannot be specified in the compact format. */
typedef struct {
  uint8_t nanoseconds[4];                        /* bytes 0 to 3 */
  uint8_t strategy_id[4];                        /* bytes 4 to 7 */
  uint8_t bid_price_long[8];                     /* bytes 8 to 15 */
  uint8_t bid_size_long[4];                      /* bytes 16 to 19 */
  uint8_t bid_priority_customer_size_long[4];    /* bytes 20 to 23 */
  uint8_t bid_condition;                         /* byte 24 */
  uint8_t offer_price_long[8];                   /* bytes 25 to 32 */
  uint8_t offer_size_long[4];                    /* bytes 33 to 36 */
  uint8_t offer_priority_customer_size_long[4];  /* bytes 37 to 40 */
  uint8_t offer_condition;                       /* byte 41 */
} ComplexDoubleSidedTopOfMarketBestBidAndOfferWideFormatMessage;

/* any Complex Double Sided Top Of Market Best Bid And Offer Wide Format Message at all: every byte one the checker chooses */
static void any_complex_double_sided_top_of_market_best_bid_and_offer_wide_format_message(ComplexDoubleSidedTopOfMarketBestBidAndOfferWideFormatMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_priority_customer_size_long[i] = arbitrary(); }
  record->bid_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->offer_price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->offer_size_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->offer_priority_customer_size_long[i] = arbitrary(); }
  record->offer_condition = arbitrary();
}

/* Complex Double Sided Top Of Market Best Bid And Offer Wide Format Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_complex_double_sided_top_of_market_best_bid_and_offer_wide_format_message(const ComplexDoubleSidedTopOfMarketBestBidAndOfferWideFormatMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_priority_customer_size_long[i]; }
  wire[at++] = record->bid_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->offer_size_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->offer_priority_customer_size_long[i]; }
  wire[at++] = record->offer_condition;

  return at;
}

/* Complex Double Sided Top Of Market Best Bid And Offer Wide Format Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_complex_double_sided_top_of_market_best_bid_and_offer_wide_format_message(ComplexDoubleSidedTopOfMarketBestBidAndOfferWideFormatMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_priority_customer_size_long[i] = wire[at++]; }
  record->bid_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->offer_price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->offer_size_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->offer_priority_customer_size_long[i] = wire[at++]; }
  record->offer_condition = wire[at++];

  return at;
}

/* what was read of Complex Double Sided Top Of Market Best Bid And Offer Wide Format Message is what was written, byte for byte */
static void equal_complex_double_sided_top_of_market_best_bid_and_offer_wide_format_message(const ComplexDoubleSidedTopOfMarketBestBidAndOfferWideFormatMessage *read, const ComplexDoubleSidedTopOfMarketBestBidAndOfferWideFormatMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_price_long[i] == written->bid_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_long[i] == written->bid_size_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_priority_customer_size_long[i] == written->bid_priority_customer_size_long[i]); }
  assert(read->bid_condition == written->bid_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->offer_price_long[i] == written->offer_price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->offer_size_long[i] == written->offer_size_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->offer_priority_customer_size_long[i] == written->offer_priority_customer_size_long[i]); }
  assert(read->offer_condition == written->offer_condition);
}

/* Complex Double Sided Top Of Market Best Bid And Offer Wide Format Message: written and read back, then read and written back */
static void check_complex_double_sided_top_of_market_best_bid_and_offer_wide_format_message(void) {
  ComplexDoubleSidedTopOfMarketBestBidAndOfferWideFormatMessage sent;
  ComplexDoubleSidedTopOfMarketBestBidAndOfferWideFormatMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_complex_double_sided_top_of_market_best_bid_and_offer_wide_format_message(&sent);
  assert(encode_complex_double_sided_top_of_market_best_bid_and_offer_wide_format_message(&sent, wire, 0) == 42);
  assert(decode_complex_double_sided_top_of_market_best_bid_and_offer_wide_format_message(&got, wire, 0) == 42);
  equal_complex_double_sided_top_of_market_best_bid_and_offer_wide_format_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_double_sided_top_of_market_best_bid_and_offer_wide_format_message(&got, wire, 0) == 42);
  assert(encode_complex_double_sided_top_of_market_best_bid_and_offer_wide_format_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strategy Last Sale Message: 41 bytes ------------------------------------ */

/* This is the message format that will be used to disseminate Trades that are resulting from executions on Emerald during the current trading session. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t strategy_id[4];   /* bytes 4 to 7 */
  uint8_t trade_id[4];      /* bytes 8 to 11 */
  uint8_t net_price[8];     /* bytes 12 to 19 */
  uint8_t size_long[4];     /* bytes 20 to 23 */
  uint8_t condition;        /* byte 24 */
  uint8_t reserved_16[16];  /* bytes 25 to 40 */
} StrategyLastSaleMessage;

/* any Strategy Last Sale Message at all: every byte one the checker chooses */
static void any_strategy_last_sale_message(StrategyLastSaleMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->net_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size_long[i] = arbitrary(); }
  record->condition = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Strategy Last Sale Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_strategy_last_sale_message(const StrategyLastSaleMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->net_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size_long[i]; }
  wire[at++] = record->condition;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Strategy Last Sale Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_strategy_last_sale_message(StrategyLastSaleMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->net_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size_long[i] = wire[at++]; }
  record->condition = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Strategy Last Sale Message is what was written, byte for byte */
static void equal_strategy_last_sale_message(const StrategyLastSaleMessage *read, const StrategyLastSaleMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->net_price[i] == written->net_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size_long[i] == written->size_long[i]); }
  assert(read->condition == written->condition);
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Strategy Last Sale Message: written and read back, then read and written back */
static void check_strategy_last_sale_message(void) {
  StrategyLastSaleMessage sent;
  StrategyLastSaleMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_strategy_last_sale_message(&sent);
  assert(encode_strategy_last_sale_message(&sent, wire, 0) == 41);
  assert(decode_strategy_last_sale_message(&got, wire, 0) == 41);
  equal_strategy_last_sale_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_strategy_last_sale_message(&got, wire, 0) == 41);
  assert(encode_strategy_last_sale_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Trading Status Notification Message: 25 bytes ---------------- */

/* This message format will be used to notify firms of changes to the trading status of all the options of an underlying. */
typedef struct {
  uint8_t nanoseconds[4];                            /* bytes 0 to 3 */
  uint8_t underlying_symbol[11];                     /* bytes 4 to 14 */
  uint8_t trading_status;                            /* byte 15 */
  uint8_t event_reason;                              /* byte 16 */
  uint8_t expected_event_time_seconds_part[4];       /* bytes 17 to 20 */
  uint8_t expected_event_time_nano_seconds_part[4];  /* bytes 21 to 24 */
} UnderlyingTradingStatusNotificationMessage;

/* any Underlying Trading Status Notification Message at all: every byte one the checker chooses */
static void any_underlying_trading_status_notification_message(UnderlyingTradingStatusNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->event_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->expected_event_time_seconds_part[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expected_event_time_nano_seconds_part[i] = arbitrary(); }
}

/* Underlying Trading Status Notification Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_underlying_trading_status_notification_message(const UnderlyingTradingStatusNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->event_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expected_event_time_seconds_part[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expected_event_time_nano_seconds_part[i]; }

  return at;
}

/* Underlying Trading Status Notification Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_underlying_trading_status_notification_message(UnderlyingTradingStatusNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->event_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->expected_event_time_seconds_part[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expected_event_time_nano_seconds_part[i] = wire[at++]; }

  return at;
}

/* what was read of Underlying Trading Status Notification Message is what was written, byte for byte */
static void equal_underlying_trading_status_notification_message(const UnderlyingTradingStatusNotificationMessage *read, const UnderlyingTradingStatusNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->event_reason == written->event_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->expected_event_time_seconds_part[i] == written->expected_event_time_seconds_part[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expected_event_time_nano_seconds_part[i] == written->expected_event_time_nano_seconds_part[i]); }
}

/* Underlying Trading Status Notification Message: written and read back, then read and written back */
static void check_underlying_trading_status_notification_message(void) {
  UnderlyingTradingStatusNotificationMessage sent;
  UnderlyingTradingStatusNotificationMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_underlying_trading_status_notification_message(&sent);
  assert(encode_underlying_trading_status_notification_message(&sent, wire, 0) == 25);
  assert(decode_underlying_trading_status_notification_message(&got, wire, 0) == 25);
  equal_underlying_trading_status_notification_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_trading_status_notification_message(&got, wire, 0) == 25);
  assert(encode_underlying_trading_status_notification_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_mach_packet_header();
  check_system_time_message();
  check_simple_series_update_message();
  check_system_state_message();
  check_complex_top_of_market_best_bid_or_offer_compact_format_bid_message();
  check_complex_top_of_market_best_bid_or_offer_compact_format_offer_message();
  check_complex_top_of_market_best_bid_or_offer_wide_format_bid_message();
  check_complex_top_of_market_best_bid_or_offer_wide_format_offer_message();
  check_complex_double_sided_top_of_market_best_bid_and_offer_compact_format_message();
  check_complex_double_sided_top_of_market_best_bid_and_offer_wide_format_message();
  check_strategy_last_sale_message();
  check_underlying_trading_status_notification_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
