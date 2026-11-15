// miax/miaxoptions/topofmarket/MiaxOptions_TopOfMarket_v1_3.c
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

/* ---- Series Update Message: 72 bytes ----------------------------------------- */

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
} SeriesUpdateMessage;

/* any Series Update Message at all: every byte one the checker chooses */
static void any_series_update_message(SeriesUpdateMessage *record) {
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

/* Series Update Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_series_update_message(const SeriesUpdateMessage *record, uint8_t *wire, size_t at) {
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

/* Series Update Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_series_update_message(SeriesUpdateMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Series Update Message is what was written, byte for byte */
static void equal_series_update_message(const SeriesUpdateMessage *read, const SeriesUpdateMessage *written) {
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

/* Series Update Message: written and read back, then read and written back */
static void check_series_update_message(void) {
  SeriesUpdateMessage sent;
  SeriesUpdateMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_series_update_message(&sent);
  assert(encode_series_update_message(&sent, wire, 0) == 72);
  assert(decode_series_update_message(&got, wire, 0) == 72);
  equal_series_update_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_series_update_message(&got, wire, 0) == 72);
  assert(encode_series_update_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- System State Message: 17 bytes ------------------------------------------ */

/* This message format is used to notify the firms of the state changes of the system. This is a notification that applies to each Underlying group. Firms can use notifications as triggers in their system to ensure electronic synchronization of systems. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t to_m_version[8];  /* bytes 4 to 11 */
  uint8_t session_id[4];    /* bytes 12 to 15 */
  uint8_t system_status;    /* byte 16 */
} SystemStateMessage;

/* any System State Message at all: every byte one the checker chooses */
static void any_system_state_message(SystemStateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->to_m_version[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  record->system_status = arbitrary();
}

/* System State Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_system_state_message(const SystemStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->to_m_version[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  wire[at++] = record->system_status;

  return at;
}

/* System State Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_system_state_message(SystemStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->to_m_version[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  record->system_status = wire[at++];

  return at;
}

/* what was read of System State Message is what was written, byte for byte */
static void equal_system_state_message(const SystemStateMessage *read, const SystemStateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->to_m_version[i] == written->to_m_version[i]); }
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

/* ---- Top Of Market Bid Compact Message: 15 bytes ----------------------------- */

/* This is the message format that will be used to disseminate each side of the MIAX Top of Market for options with low premiums and small aggregate MIAX Best Bid or Offer (MBBO) size. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t product_id[4];    /* bytes 4 to 7 */
  uint8_t mbbo_price_2[2];  /* bytes 8 to 9 */
  uint8_t mbbo_size_2[2];   /* bytes 10 to 11 */
  uint8_t reserved_2[2];    /* bytes 12 to 13 */
  uint8_t mbbo_condition;   /* byte 14 */
} TopOfMarketBidCompactMessage;

/* any Top Of Market Bid Compact Message at all: every byte one the checker chooses */
static void any_top_of_market_bid_compact_message(TopOfMarketBidCompactMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->mbbo_price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->mbbo_size_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->mbbo_condition = arbitrary();
}

/* Top Of Market Bid Compact Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_top_of_market_bid_compact_message(const TopOfMarketBidCompactMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->mbbo_price_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->mbbo_size_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->mbbo_condition;

  return at;
}

/* Top Of Market Bid Compact Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_top_of_market_bid_compact_message(TopOfMarketBidCompactMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->mbbo_price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->mbbo_size_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->mbbo_condition = wire[at++];

  return at;
}

/* what was read of Top Of Market Bid Compact Message is what was written, byte for byte */
static void equal_top_of_market_bid_compact_message(const TopOfMarketBidCompactMessage *read, const TopOfMarketBidCompactMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->mbbo_price_2[i] == written->mbbo_price_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->mbbo_size_2[i] == written->mbbo_size_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->mbbo_condition == written->mbbo_condition);
}

/* Top Of Market Bid Compact Message: written and read back, then read and written back */
static void check_top_of_market_bid_compact_message(void) {
  TopOfMarketBidCompactMessage sent;
  TopOfMarketBidCompactMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_top_of_market_bid_compact_message(&sent);
  assert(encode_top_of_market_bid_compact_message(&sent, wire, 0) == 15);
  assert(decode_top_of_market_bid_compact_message(&got, wire, 0) == 15);
  equal_top_of_market_bid_compact_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_top_of_market_bid_compact_message(&got, wire, 0) == 15);
  assert(encode_top_of_market_bid_compact_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Of Market Offer Compact Message: 15 bytes --------------------------- */

/* This is the message format that will be used to disseminate each side of the MIAX Top of Market for options with low premiums and small aggregate MIAX Best Bid or Offer (MBBO) size. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t product_id[4];    /* bytes 4 to 7 */
  uint8_t mbbo_price_2[2];  /* bytes 8 to 9 */
  uint8_t mbbo_size_2[2];   /* bytes 10 to 11 */
  uint8_t reserved_2[2];    /* bytes 12 to 13 */
  uint8_t mbbo_condition;   /* byte 14 */
} TopOfMarketOfferCompactMessage;

/* any Top Of Market Offer Compact Message at all: every byte one the checker chooses */
static void any_top_of_market_offer_compact_message(TopOfMarketOfferCompactMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->mbbo_price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->mbbo_size_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->mbbo_condition = arbitrary();
}

/* Top Of Market Offer Compact Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_top_of_market_offer_compact_message(const TopOfMarketOfferCompactMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->mbbo_price_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->mbbo_size_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->mbbo_condition;

  return at;
}

/* Top Of Market Offer Compact Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_top_of_market_offer_compact_message(TopOfMarketOfferCompactMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->mbbo_price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->mbbo_size_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->mbbo_condition = wire[at++];

  return at;
}

/* what was read of Top Of Market Offer Compact Message is what was written, byte for byte */
static void equal_top_of_market_offer_compact_message(const TopOfMarketOfferCompactMessage *read, const TopOfMarketOfferCompactMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->mbbo_price_2[i] == written->mbbo_price_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->mbbo_size_2[i] == written->mbbo_size_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->mbbo_condition == written->mbbo_condition);
}

/* Top Of Market Offer Compact Message: written and read back, then read and written back */
static void check_top_of_market_offer_compact_message(void) {
  TopOfMarketOfferCompactMessage sent;
  TopOfMarketOfferCompactMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_top_of_market_offer_compact_message(&sent);
  assert(encode_top_of_market_offer_compact_message(&sent, wire, 0) == 15);
  assert(decode_top_of_market_offer_compact_message(&got, wire, 0) == 15);
  equal_top_of_market_offer_compact_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_top_of_market_offer_compact_message(&got, wire, 0) == 15);
  assert(encode_top_of_market_offer_compact_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Of Market Bid Wide Message: 21 bytes -------------------------------- */

/* This is the message format that will be used to disseminate MIAX Top of Market for options with high premiums or large aggregate MIAX Best Bid or Offer (MBBO) size. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t product_id[4];    /* bytes 4 to 7 */
  uint8_t mbbo_price_4[4];  /* bytes 8 to 11 */
  uint8_t mbbo_size_4[4];   /* bytes 12 to 15 */
  uint8_t reserved_4[4];    /* bytes 16 to 19 */
  uint8_t mbbo_condition;   /* byte 20 */
} TopOfMarketBidWideMessage;

/* any Top Of Market Bid Wide Message at all: every byte one the checker chooses */
static void any_top_of_market_bid_wide_message(TopOfMarketBidWideMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mbbo_price_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mbbo_size_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  record->mbbo_condition = arbitrary();
}

/* Top Of Market Bid Wide Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_top_of_market_bid_wide_message(const TopOfMarketBidWideMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mbbo_price_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mbbo_size_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  wire[at++] = record->mbbo_condition;

  return at;
}

/* Top Of Market Bid Wide Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_top_of_market_bid_wide_message(TopOfMarketBidWideMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mbbo_price_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mbbo_size_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  record->mbbo_condition = wire[at++];

  return at;
}

/* what was read of Top Of Market Bid Wide Message is what was written, byte for byte */
static void equal_top_of_market_bid_wide_message(const TopOfMarketBidWideMessage *read, const TopOfMarketBidWideMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mbbo_price_4[i] == written->mbbo_price_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mbbo_size_4[i] == written->mbbo_size_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  assert(read->mbbo_condition == written->mbbo_condition);
}

/* Top Of Market Bid Wide Message: written and read back, then read and written back */
static void check_top_of_market_bid_wide_message(void) {
  TopOfMarketBidWideMessage sent;
  TopOfMarketBidWideMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_top_of_market_bid_wide_message(&sent);
  assert(encode_top_of_market_bid_wide_message(&sent, wire, 0) == 21);
  assert(decode_top_of_market_bid_wide_message(&got, wire, 0) == 21);
  equal_top_of_market_bid_wide_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_top_of_market_bid_wide_message(&got, wire, 0) == 21);
  assert(encode_top_of_market_bid_wide_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Of Market Offer Wide Message: 21 bytes ------------------------------ */

/* This is the message format that will be used to disseminate MIAX Top of Market for options with high premiums or large aggregate MIAX Best Bid or Offer (MBBO) size. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t product_id[4];    /* bytes 4 to 7 */
  uint8_t mbbo_price_4[4];  /* bytes 8 to 11 */
  uint8_t mbbo_size_4[4];   /* bytes 12 to 15 */
  uint8_t reserved_4[4];    /* bytes 16 to 19 */
  uint8_t mbbo_condition;   /* byte 20 */
} TopOfMarketOfferWideMessage;

/* any Top Of Market Offer Wide Message at all: every byte one the checker chooses */
static void any_top_of_market_offer_wide_message(TopOfMarketOfferWideMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mbbo_price_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mbbo_size_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  record->mbbo_condition = arbitrary();
}

/* Top Of Market Offer Wide Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_top_of_market_offer_wide_message(const TopOfMarketOfferWideMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mbbo_price_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mbbo_size_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  wire[at++] = record->mbbo_condition;

  return at;
}

/* Top Of Market Offer Wide Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_top_of_market_offer_wide_message(TopOfMarketOfferWideMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mbbo_price_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mbbo_size_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  record->mbbo_condition = wire[at++];

  return at;
}

/* what was read of Top Of Market Offer Wide Message is what was written, byte for byte */
static void equal_top_of_market_offer_wide_message(const TopOfMarketOfferWideMessage *read, const TopOfMarketOfferWideMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mbbo_price_4[i] == written->mbbo_price_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mbbo_size_4[i] == written->mbbo_size_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  assert(read->mbbo_condition == written->mbbo_condition);
}

/* Top Of Market Offer Wide Message: written and read back, then read and written back */
static void check_top_of_market_offer_wide_message(void) {
  TopOfMarketOfferWideMessage sent;
  TopOfMarketOfferWideMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_top_of_market_offer_wide_message(&sent);
  assert(encode_top_of_market_offer_wide_message(&sent, wire, 0) == 21);
  assert(decode_top_of_market_offer_wide_message(&got, wire, 0) == 21);
  equal_top_of_market_offer_wide_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_top_of_market_offer_wide_message(&got, wire, 0) == 21);
  assert(encode_top_of_market_offer_wide_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Sale Message: 27 bytes --------------------------------------------- */

/* This is the message format that will be used to disseminate Trades that are resulting from executions on MIAX during the current trading session. */
typedef struct {
  uint8_t nanoseconds[4];               /* bytes 0 to 3 */
  uint8_t product_id[4];                /* bytes 4 to 7 */
  uint8_t trade_id[4];                  /* bytes 8 to 11 */
  uint8_t correction_number;            /* byte 12 */
  uint8_t reference_trade_id[4];        /* bytes 13 to 16 */
  uint8_t reference_correction_number;  /* byte 17 */
  uint8_t trade_price[4];               /* bytes 18 to 21 */
  uint8_t trade_size[4];                /* bytes 22 to 25 */
  uint8_t trade_condition;              /* byte 26 */
} LastSaleMessage;

/* any Last Sale Message at all: every byte one the checker chooses */
static void any_last_sale_message(LastSaleMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  record->correction_number = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reference_trade_id[i] = arbitrary(); }
  record->reference_correction_number = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Last Sale Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_last_sale_message(const LastSaleMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->correction_number;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_trade_id[i]; }
  wire[at++] = record->reference_correction_number;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_size[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Last Sale Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_last_sale_message(LastSaleMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  record->correction_number = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reference_trade_id[i] = wire[at++]; }
  record->reference_correction_number = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Last Sale Message is what was written, byte for byte */
static void equal_last_sale_message(const LastSaleMessage *read, const LastSaleMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->correction_number == written->correction_number);
  for (size_t i = 0; i < 4; i++) { assert(read->reference_trade_id[i] == written->reference_trade_id[i]); }
  assert(read->reference_correction_number == written->reference_correction_number);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_size[i] == written->trade_size[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Last Sale Message: written and read back, then read and written back */
static void check_last_sale_message(void) {
  LastSaleMessage sent;
  LastSaleMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_last_sale_message(&sent);
  assert(encode_last_sale_message(&sent, wire, 0) == 27);
  assert(decode_last_sale_message(&got, wire, 0) == 27);
  equal_last_sale_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_last_sale_message(&got, wire, 0) == 27);
  assert(encode_last_sale_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Message: 22 bytes ------------------------------------------ */

/* This is the message format that will be used to disseminate canceled Trades that are resulting from Trade cancellations or corrections on MIAX during the current trading session */
typedef struct {
  uint8_t nanoseconds[4];     /* bytes 0 to 3 */
  uint8_t product_id[4];      /* bytes 4 to 7 */
  uint8_t trade_id[4];        /* bytes 8 to 11 */
  uint8_t correction_number;  /* byte 12 */
  uint8_t trade_price[4];     /* bytes 13 to 16 */
  uint8_t trade_size[4];      /* bytes 17 to 20 */
  uint8_t trade_condition;    /* byte 21 */
} TradeCancelMessage;

/* any Trade Cancel Message at all: every byte one the checker chooses */
static void any_trade_cancel_message(TradeCancelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  record->correction_number = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Trade Cancel Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_message(const TradeCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  wire[at++] = record->correction_number;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_size[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Trade Cancel Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_message(TradeCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  record->correction_number = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_size[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Trade Cancel Message is what was written, byte for byte */
static void equal_trade_cancel_message(const TradeCancelMessage *read, const TradeCancelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  assert(read->correction_number == written->correction_number);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_size[i] == written->trade_size[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Trade Cancel Message: written and read back, then read and written back */
static void check_trade_cancel_message(void) {
  TradeCancelMessage sent;
  TradeCancelMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_trade_cancel_message(&sent);
  assert(encode_trade_cancel_message(&sent, wire, 0) == 22);
  assert(decode_trade_cancel_message(&got, wire, 0) == 22);
  equal_trade_cancel_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_message(&got, wire, 0) == 22);
  assert(encode_trade_cancel_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Liquidity Seeking Event Notification Message: 46 bytes ------------------ */

/* This is the message format that will be used to disseminate information each time a Liquidity seeking event (defined in Event Type field below) starts at MIAX. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t product_id[4];    /* bytes 4 to 7 */
  uint8_t event_type;       /* byte 8 */
  uint8_t event_id[4];      /* bytes 9 to 12 */
  uint8_t price[4];         /* bytes 13 to 16 */
  uint8_t imbalance_side;   /* byte 17 */
  uint8_t quantity_1[4];    /* bytes 18 to 21 */
  uint8_t quantity_2[4];    /* bytes 22 to 25 */
  uint8_t quantity_3[4];    /* bytes 26 to 29 */
  uint8_t quantity_4[4];    /* bytes 30 to 33 */
  uint8_t reserved_12[12];  /* bytes 34 to 45 */
} LiquiditySeekingEventNotificationMessage;

/* any Liquidity Seeking Event Notification Message at all: every byte one the checker chooses */
static void any_liquidity_seeking_event_notification_message(LiquiditySeekingEventNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  record->event_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->imbalance_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_4[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = arbitrary(); }
}

/* Liquidity Seeking Event Notification Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_liquidity_seeking_event_notification_message(const LiquiditySeekingEventNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  wire[at++] = record->event_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->imbalance_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_4[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reserved_12[i]; }

  return at;
}

/* Liquidity Seeking Event Notification Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_liquidity_seeking_event_notification_message(LiquiditySeekingEventNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  record->event_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->imbalance_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_4[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = wire[at++]; }

  return at;
}

/* what was read of Liquidity Seeking Event Notification Message is what was written, byte for byte */
static void equal_liquidity_seeking_event_notification_message(const LiquiditySeekingEventNotificationMessage *read, const LiquiditySeekingEventNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  assert(read->event_type == written->event_type);
  for (size_t i = 0; i < 4; i++) { assert(read->event_id[i] == written->event_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->imbalance_side == written->imbalance_side);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_1[i] == written->quantity_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_2[i] == written->quantity_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_3[i] == written->quantity_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_4[i] == written->quantity_4[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->reserved_12[i] == written->reserved_12[i]); }
}

/* Liquidity Seeking Event Notification Message: written and read back, then read and written back */
static void check_liquidity_seeking_event_notification_message(void) {
  LiquiditySeekingEventNotificationMessage sent;
  LiquiditySeekingEventNotificationMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_liquidity_seeking_event_notification_message(&sent);
  assert(encode_liquidity_seeking_event_notification_message(&sent, wire, 0) == 46);
  assert(decode_liquidity_seeking_event_notification_message(&got, wire, 0) == 46);
  equal_liquidity_seeking_event_notification_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_liquidity_seeking_event_notification_message(&got, wire, 0) == 46);
  assert(encode_liquidity_seeking_event_notification_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_mach_packet_header();
  check_system_time_message();
  check_series_update_message();
  check_system_state_message();
  check_top_of_market_bid_compact_message();
  check_top_of_market_offer_compact_message();
  check_top_of_market_bid_wide_message();
  check_top_of_market_offer_wide_message();
  check_last_sale_message();
  check_trade_cancel_message();
  check_liquidity_seeking_event_notification_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
