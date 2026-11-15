// miax/miaxoptions/complextopofmarket/MiaxOptions_ComplexTopOfMarket_v1_3_a_Tcp.c
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

/* ---- Refresh Request Message: 1 byte ----------------------------------------- */

/* Sent by the firm over the cToM Retransmission Interface (SesM Unsequenced Data Packet) to request a Last Value Refresh of a particular data set identified by Refresh Message Type. */
typedef struct {
  uint8_t refresh_message_type;  /* byte 0 */
} RefreshRequestMessage;

/* any Refresh Request Message at all: every byte one the checker chooses */
static void any_refresh_request_message(RefreshRequestMessage *record) {
  record->refresh_message_type = arbitrary();
}

/* Refresh Request Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_refresh_request_message(const RefreshRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->refresh_message_type;

  return at;
}

/* Refresh Request Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_refresh_request_message(RefreshRequestMessage *record, const uint8_t *wire, size_t at) {
  record->refresh_message_type = wire[at++];

  return at;
}

/* what was read of Refresh Request Message is what was written, byte for byte */
static void equal_refresh_request_message(const RefreshRequestMessage *read, const RefreshRequestMessage *written) {
  assert(read->refresh_message_type == written->refresh_message_type);
}

/* Refresh Request Message: written and read back, then read and written back */
static void check_refresh_request_message(void) {
  RefreshRequestMessage sent;
  RefreshRequestMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_refresh_request_message(&sent);
  assert(encode_refresh_request_message(&sent, wire, 0) == 1);
  assert(decode_refresh_request_message(&got, wire, 0) == 1);
  equal_refresh_request_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_request_message(&got, wire, 0) == 1);
  assert(encode_refresh_request_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
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

/* This is the message format that will be used to disseminate all Option series traded on MIAX for the current session. */
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
  record->active_on_miax = arbitrary();
  record->miax_bbo_posting_increment_indicator = arbitrary();
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
  wire[at++] = record->active_on_miax;
  wire[at++] = record->miax_bbo_posting_increment_indicator;
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
  record->active_on_miax = wire[at++];
  record->miax_bbo_posting_increment_indicator = wire[at++];
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
  assert(read->active_on_miax == written->active_on_miax);
  assert(read->miax_bbo_posting_increment_indicator == written->miax_bbo_posting_increment_indicator);
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

/* This is the message format that will be used to disseminate each side of the MIAX Complex Top of Market for strategies with low Net Price and small aggregate MIAX Best Bid or Offer (MBBO) size. MIAX Complex Top of Market on Bid side. */
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

/* This is the message format that will be used to disseminate each side of the MIAX Complex Top of Market for strategies with low Net Price and small aggregate MIAX Best Bid or Offer (MBBO) size. MIAX Complex Top of Market on Offer side. */
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

/* This is the message format that will be used to disseminate MIAX Complex Top of Market for strategies with high net price or large aggregate MIAX Best Bid or Offer (MBBO) size. MIAX Complex Top of Market on Bid side. */
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

/* This is the message format that will be used to disseminate MIAX Complex Top of Market for strategies with high net price or large aggregate MIAX Best Bid or Offer (MBBO) size. MIAX Complex Top of Market on Offer side. */
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

/* This is the message format that will be used to disseminate both sides of the MIAX top of market for strategies (cMBBO) with low net price and small aggregate size. */
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

/* This is the message format that will be used to disseminate both sides of the MIAX top of market for strategies (cMBBO) with net prices or aggregate sizes which cannot be specified in the compact format. */
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

/* This is the message format that will be used to disseminate Trades that are resulting from executions on MIAX during the current trading session. */
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

/* ---- End Of Refresh Notification Message: 1 byte ----------------------------- */

/* Sent by MIAX Options over the cToM Retransmission Interface (SesM Unsequenced Data Packet) when the refresh response is complete. */
typedef struct {
  uint8_t refresh_message_type;  /* byte 0 */
} EndOfRefreshNotificationMessage;

/* any End Of Refresh Notification Message at all: every byte one the checker chooses */
static void any_end_of_refresh_notification_message(EndOfRefreshNotificationMessage *record) {
  record->refresh_message_type = arbitrary();
}

/* End Of Refresh Notification Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_end_of_refresh_notification_message(const EndOfRefreshNotificationMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->refresh_message_type;

  return at;
}

/* End Of Refresh Notification Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_end_of_refresh_notification_message(EndOfRefreshNotificationMessage *record, const uint8_t *wire, size_t at) {
  record->refresh_message_type = wire[at++];

  return at;
}

/* what was read of End Of Refresh Notification Message is what was written, byte for byte */
static void equal_end_of_refresh_notification_message(const EndOfRefreshNotificationMessage *read, const EndOfRefreshNotificationMessage *written) {
  assert(read->refresh_message_type == written->refresh_message_type);
}

/* End Of Refresh Notification Message: written and read back, then read and written back */
static void check_end_of_refresh_notification_message(void) {
  EndOfRefreshNotificationMessage sent;
  EndOfRefreshNotificationMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_end_of_refresh_notification_message(&sent);
  assert(encode_end_of_refresh_notification_message(&sent, wire, 0) == 1);
  assert(decode_end_of_refresh_notification_message(&got, wire, 0) == 1);
  equal_end_of_refresh_notification_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_refresh_notification_message(&got, wire, 0) == 1);
  assert(encode_end_of_refresh_notification_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request: 35 bytes ------------------------------------------------- */

/* The SesM client must send a Login request packet immediately upon establishing a new TCP/IP socket connection to the server */
typedef struct {
  uint8_t sesm_version[5];               /* bytes 0 to 4 */
  uint8_t username[5];                   /* bytes 5 to 9 */
  uint8_t computer_id[8];                /* bytes 10 to 17 */
  uint8_t application_protocol[8];       /* bytes 18 to 25 */
  uint8_t requested_trading_session_id;  /* byte 26 */
  uint8_t requested_sequence_number[8];  /* bytes 27 to 34 */
} LoginRequest;

/* any Login Request at all: every byte one the checker chooses */
static void any_login_request(LoginRequest *record) {
  for (size_t i = 0; i < 5; i++) { record->sesm_version[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->computer_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->application_protocol[i] = arbitrary(); }
  record->requested_trading_session_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->requested_sequence_number[i] = arbitrary(); }
}

/* Login Request to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_login_request(const LoginRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sesm_version[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->computer_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->application_protocol[i]; }
  wire[at++] = record->requested_trading_session_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->requested_sequence_number[i]; }

  return at;
}

/* Login Request off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_login_request(LoginRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->sesm_version[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->computer_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->application_protocol[i] = wire[at++]; }
  record->requested_trading_session_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->requested_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request is what was written, byte for byte */
static void equal_login_request(const LoginRequest *read, const LoginRequest *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->sesm_version[i] == written->sesm_version[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->computer_id[i] == written->computer_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->application_protocol[i] == written->application_protocol[i]); }
  assert(read->requested_trading_session_id == written->requested_trading_session_id);
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

/* ---- Login Response: 11 bytes ------------------------------------------------ */

/* The SesM server sends a Login response packet in response a Login request packet from the client */
typedef struct {
  uint8_t number_of_matching_engines;  /* byte 0 */
  uint8_t login_status;                /* byte 1 */
  uint8_t trading_session_id;          /* byte 2 */
  uint8_t highest_sequence_number[8];  /* bytes 3 to 10 */
} LoginResponse;

/* any Login Response at all: every byte one the checker chooses */
static void any_login_response(LoginResponse *record) {
  record->number_of_matching_engines = arbitrary();
  record->login_status = arbitrary();
  record->trading_session_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->highest_sequence_number[i] = arbitrary(); }
}

/* Login Response to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_login_response(const LoginResponse *record, uint8_t *wire, size_t at) {
  wire[at++] = record->number_of_matching_engines;
  wire[at++] = record->login_status;
  wire[at++] = record->trading_session_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->highest_sequence_number[i]; }

  return at;
}

/* Login Response off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_login_response(LoginResponse *record, const uint8_t *wire, size_t at) {
  record->number_of_matching_engines = wire[at++];
  record->login_status = wire[at++];
  record->trading_session_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->highest_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Response is what was written, byte for byte */
static void equal_login_response(const LoginResponse *read, const LoginResponse *written) {
  assert(read->number_of_matching_engines == written->number_of_matching_engines);
  assert(read->login_status == written->login_status);
  assert(read->trading_session_id == written->trading_session_id);
  for (size_t i = 0; i < 8; i++) { assert(read->highest_sequence_number[i] == written->highest_sequence_number[i]); }
}

/* Login Response: written and read back, then read and written back */
static void check_login_response(void) {
  LoginResponse sent;
  LoginResponse got;
  uint8_t wire[11];
  uint8_t again[11];

  any_login_response(&sent);
  assert(encode_login_response(&sent, wire, 0) == 11);
  assert(decode_login_response(&got, wire, 0) == 11);
  equal_login_response(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response(&got, wire, 0) == 11);
  assert(encode_login_response(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Synchronization Complete: 1 byte ---------------------------------------- */

/* The SesM server sends a Login response packet in response a Login request packet from the client */
typedef struct {
  uint8_t number_of_matching_engines;  /* byte 0 */
} SynchronizationComplete;

/* any Synchronization Complete at all: every byte one the checker chooses */
static void any_synchronization_complete(SynchronizationComplete *record) {
  record->number_of_matching_engines = arbitrary();
}

/* Synchronization Complete to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_synchronization_complete(const SynchronizationComplete *record, uint8_t *wire, size_t at) {
  wire[at++] = record->number_of_matching_engines;

  return at;
}

/* Synchronization Complete off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_synchronization_complete(SynchronizationComplete *record, const uint8_t *wire, size_t at) {
  record->number_of_matching_engines = wire[at++];

  return at;
}

/* what was read of Synchronization Complete is what was written, byte for byte */
static void equal_synchronization_complete(const SynchronizationComplete *read, const SynchronizationComplete *written) {
  assert(read->number_of_matching_engines == written->number_of_matching_engines);
}

/* Synchronization Complete: written and read back, then read and written back */
static void check_synchronization_complete(void) {
  SynchronizationComplete sent;
  SynchronizationComplete got;
  uint8_t wire[1];
  uint8_t again[1];

  any_synchronization_complete(&sent);
  assert(encode_synchronization_complete(&sent, wire, 0) == 1);
  assert(decode_synchronization_complete(&got, wire, 0) == 1);
  equal_synchronization_complete(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_synchronization_complete(&got, wire, 0) == 1);
  assert(encode_synchronization_complete(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Request: 16 bytes ---------------------------------------- */

/* The SesM client uses this packet to request a retransmission server to retransmit a range of packets */
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
  check_refresh_request_message();
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
  check_end_of_refresh_notification_message();
  check_login_request();
  check_login_response();
  check_synchronization_complete();
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
