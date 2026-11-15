// miax/emeraldoptions/ais/EmeraldOptions_Ais_v1_0_Tcp.c
/*
 * Miami International Holdings Administrative Information Subscriber
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

/* Sent by the firm over the AIS Retransmission Interface (SesM Unsequenced Data Packet) to request a Last Value Refresh of a particular data set identified by Refresh Message Type. */
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
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t ais_version[8];  /* bytes 4 to 11 */
  uint8_t session_id[4];   /* bytes 12 to 15 */
  uint8_t system_status;   /* byte 16 */
} SystemStateMessage;

/* any System State Message at all: every byte one the checker chooses */
static void any_system_state_message(SystemStateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ais_version[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  record->system_status = arbitrary();
}

/* System State Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_system_state_message(const SystemStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ais_version[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  wire[at++] = record->system_status;

  return at;
}

/* System State Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_system_state_message(SystemStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ais_version[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  record->system_status = wire[at++];

  return at;
}

/* what was read of System State Message is what was written, byte for byte */
static void equal_system_state_message(const SystemStateMessage *read, const SystemStateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ais_version[i] == written->ais_version[i]); }
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

/* ---- Simple Liquidity Seeking Event Notification Message: 46 bytes ----------- */

/* This is the message format that will be used to disseminate information each time a Liquidity seeking event (defined in Event Type field below) starts at Emerald. */
typedef struct {
  uint8_t nanoseconds[4];      /* bytes 0 to 3 */
  uint8_t product_id[4];       /* bytes 4 to 7 */
  uint8_t event_type;          /* byte 8 */
  uint8_t event_id[4];         /* bytes 9 to 12 */
  uint8_t price_short[4];      /* bytes 13 to 16 */
  uint8_t imbalance_side;      /* byte 17 */
  uint8_t quantity_1[4];       /* bytes 18 to 21 */
  uint8_t quantity_2[4];       /* bytes 22 to 25 */
  uint8_t quantity_3[4];       /* bytes 26 to 29 */
  uint8_t quantity_4[4];       /* bytes 30 to 33 */
  uint8_t attributable_id[4];  /* bytes 34 to 37 */
  uint8_t reserved_8[8];       /* bytes 38 to 45 */
} SimpleLiquiditySeekingEventNotificationMessage;

/* any Simple Liquidity Seeking Event Notification Message at all: every byte one the checker chooses */
static void any_simple_liquidity_seeking_event_notification_message(SimpleLiquiditySeekingEventNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  record->event_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_short[i] = arbitrary(); }
  record->imbalance_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->attributable_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Simple Liquidity Seeking Event Notification Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_simple_liquidity_seeking_event_notification_message(const SimpleLiquiditySeekingEventNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  wire[at++] = record->event_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_short[i]; }
  wire[at++] = record->imbalance_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->attributable_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Simple Liquidity Seeking Event Notification Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_simple_liquidity_seeking_event_notification_message(SimpleLiquiditySeekingEventNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  record->event_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_short[i] = wire[at++]; }
  record->imbalance_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->attributable_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Liquidity Seeking Event Notification Message is what was written, byte for byte */
static void equal_simple_liquidity_seeking_event_notification_message(const SimpleLiquiditySeekingEventNotificationMessage *read, const SimpleLiquiditySeekingEventNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  assert(read->event_type == written->event_type);
  for (size_t i = 0; i < 4; i++) { assert(read->event_id[i] == written->event_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_short[i] == written->price_short[i]); }
  assert(read->imbalance_side == written->imbalance_side);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_1[i] == written->quantity_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_2[i] == written->quantity_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_3[i] == written->quantity_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_4[i] == written->quantity_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->attributable_id[i] == written->attributable_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Simple Liquidity Seeking Event Notification Message: written and read back, then read and written back */
static void check_simple_liquidity_seeking_event_notification_message(void) {
  SimpleLiquiditySeekingEventNotificationMessage sent;
  SimpleLiquiditySeekingEventNotificationMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_simple_liquidity_seeking_event_notification_message(&sent);
  assert(encode_simple_liquidity_seeking_event_notification_message(&sent, wire, 0) == 46);
  assert(decode_simple_liquidity_seeking_event_notification_message(&got, wire, 0) == 46);
  equal_simple_liquidity_seeking_event_notification_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_liquidity_seeking_event_notification_message(&got, wire, 0) == 46);
  assert(encode_simple_liquidity_seeking_event_notification_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Liquidity Seeking Event Notification Message: 42 bytes ---------- */

/* This is the message format that will be used to disseminate information each time a Liquidity seeking event (defined in Event Type field below) starts at Emerald */
typedef struct {
  uint8_t nanoseconds[4];         /* bytes 0 to 3 */
  uint8_t strategy_id[4];         /* bytes 4 to 7 */
  uint8_t event_type;             /* byte 8 */
  uint8_t event_id[4];            /* bytes 9 to 12 */
  uint8_t side;                   /* byte 13 */
  uint8_t price_long[8];          /* bytes 14 to 21 */
  uint8_t matched_quantity[4];    /* bytes 22 to 25 */
  uint8_t imbalance_quantity[4];  /* bytes 26 to 29 */
  uint8_t attributable_id[4];     /* bytes 30 to 33 */
  uint8_t reserved_8[8];          /* bytes 34 to 41 */
} ComplexLiquiditySeekingEventNotificationMessage;

/* any Complex Liquidity Seeking Event Notification Message at all: every byte one the checker chooses */
static void any_complex_liquidity_seeking_event_notification_message(ComplexLiquiditySeekingEventNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  record->event_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->matched_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->imbalance_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->attributable_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Complex Liquidity Seeking Event Notification Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_complex_liquidity_seeking_event_notification_message(const ComplexLiquiditySeekingEventNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  wire[at++] = record->event_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->matched_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->imbalance_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->attributable_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Complex Liquidity Seeking Event Notification Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_complex_liquidity_seeking_event_notification_message(ComplexLiquiditySeekingEventNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  record->event_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->matched_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->imbalance_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->attributable_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Liquidity Seeking Event Notification Message is what was written, byte for byte */
static void equal_complex_liquidity_seeking_event_notification_message(const ComplexLiquiditySeekingEventNotificationMessage *read, const ComplexLiquiditySeekingEventNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  assert(read->event_type == written->event_type);
  for (size_t i = 0; i < 4; i++) { assert(read->event_id[i] == written->event_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->matched_quantity[i] == written->matched_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->imbalance_quantity[i] == written->imbalance_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->attributable_id[i] == written->attributable_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Complex Liquidity Seeking Event Notification Message: written and read back, then read and written back */
static void check_complex_liquidity_seeking_event_notification_message(void) {
  ComplexLiquiditySeekingEventNotificationMessage sent;
  ComplexLiquiditySeekingEventNotificationMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_complex_liquidity_seeking_event_notification_message(&sent);
  assert(encode_complex_liquidity_seeking_event_notification_message(&sent, wire, 0) == 42);
  assert(decode_complex_liquidity_seeking_event_notification_message(&got, wire, 0) == 42);
  equal_complex_liquidity_seeking_event_notification_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_liquidity_seeking_event_notification_message(&got, wire, 0) == 42);
  assert(encode_complex_liquidity_seeking_event_notification_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
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

/* Sent by MIAX Emerald over the AIS Retransmission Interface (SesM Unsequenced Data Packet) when the refresh response is complete. */
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
  check_simple_liquidity_seeking_event_notification_message();
  check_complex_liquidity_seeking_event_notification_message();
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
