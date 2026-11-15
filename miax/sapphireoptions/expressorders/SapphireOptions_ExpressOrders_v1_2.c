// miax/sapphireoptions/expressorders/SapphireOptions_ExpressOrders_v1_2.c
/*
 * Miami International Holdings Express Orders
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
 *   - a field read in bits
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

/* ---- Series Update: 76 bytes ------------------------------------------------- */

/* This is the message format that will be used to disseminate all Option series traded on Sapphire for the current session on the cloud associated for this connection */
typedef struct {
  uint8_t product_add_update_time[8];                /* bytes 0 to 7 */
  uint8_t product_id[4];                             /* bytes 8 to 11 */
  uint8_t underlying_symbol[11];                     /* bytes 12 to 22 */
  uint8_t security_symbol[6];                        /* bytes 23 to 28 */
  uint8_t expiration_date[8];                        /* bytes 29 to 36 */
  uint8_t strike_price[4];                           /* bytes 37 to 40 */
  uint8_t call_or_put;                               /* byte 41 */
  uint8_t opening_time[8];                           /* bytes 42 to 49 */
  uint8_t closing_time[8];                           /* bytes 50 to 57 */
  uint8_t restricted_option;                         /* byte 58 */
  uint8_t long_term_option;                          /* byte 59 */
  uint8_t active_on_sapphire;                        /* byte 60 */
  uint8_t sapphire_bbo_posting_increment_indicator;  /* byte 61 */
  uint8_t order_acceptance_increment_indicator;      /* byte 62 */
  uint8_t opening_underlying_market_code;            /* byte 63 */
  uint8_t reserved_12[12];                           /* bytes 64 to 75 */
} SeriesUpdate;

/* any Series Update at all: every byte one the checker chooses */
static void any_series_update(SeriesUpdate *record) {
  for (size_t i = 0; i < 8; i++) { record->product_add_update_time[i] = arbitrary(); }
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
  record->active_on_sapphire = arbitrary();
  record->sapphire_bbo_posting_increment_indicator = arbitrary();
  record->order_acceptance_increment_indicator = arbitrary();
  record->opening_underlying_market_code = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = arbitrary(); }
}

/* Series Update to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_series_update(const SeriesUpdate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->product_add_update_time[i]; }
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
  wire[at++] = record->active_on_sapphire;
  wire[at++] = record->sapphire_bbo_posting_increment_indicator;
  wire[at++] = record->order_acceptance_increment_indicator;
  wire[at++] = record->opening_underlying_market_code;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reserved_12[i]; }

  return at;
}

/* Series Update off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_series_update(SeriesUpdate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->product_add_update_time[i] = wire[at++]; }
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
  record->active_on_sapphire = wire[at++];
  record->sapphire_bbo_posting_increment_indicator = wire[at++];
  record->order_acceptance_increment_indicator = wire[at++];
  record->opening_underlying_market_code = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = wire[at++]; }

  return at;
}

/* what was read of Series Update is what was written, byte for byte */
static void equal_series_update(const SeriesUpdate *read, const SeriesUpdate *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->product_add_update_time[i] == written->product_add_update_time[i]); }
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
  assert(read->active_on_sapphire == written->active_on_sapphire);
  assert(read->sapphire_bbo_posting_increment_indicator == written->sapphire_bbo_posting_increment_indicator);
  assert(read->order_acceptance_increment_indicator == written->order_acceptance_increment_indicator);
  assert(read->opening_underlying_market_code == written->opening_underlying_market_code);
  for (size_t i = 0; i < 12; i++) { assert(read->reserved_12[i] == written->reserved_12[i]); }
}

/* Series Update: written and read back, then read and written back */
static void check_series_update(void) {
  SeriesUpdate sent;
  SeriesUpdate got;
  uint8_t wire[76];
  uint8_t again[76];

  any_series_update(&sent);
  assert(encode_series_update(&sent, wire, 0) == 76);
  assert(decode_series_update(&got, wire, 0) == 76);
  equal_series_update(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_series_update(&got, wire, 0) == 76);
  assert(encode_series_update(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Binary Order Response: 33 bytes --------------------------------- */

/* This message indicates if the complex binary order is accepted or rejected. Note that this message does not report executions */
typedef struct {
  uint8_t client_message_id[4];  /* bytes 0 to 3 */
  uint8_t mpid[4];               /* bytes 4 to 7 */
  uint8_t order_id[8];           /* bytes 8 to 15 */
  uint8_t status;                /* byte 16 */
  uint8_t reserved_16[16];       /* bytes 17 to 32 */
} ComplexBinaryOrderResponse;

/* any Complex Binary Order Response at all: every byte one the checker chooses */
static void any_complex_binary_order_response(ComplexBinaryOrderResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->status = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Complex Binary Order Response to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_complex_binary_order_response(const ComplexBinaryOrderResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->status;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Complex Binary Order Response off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_complex_binary_order_response(ComplexBinaryOrderResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->status = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Binary Order Response is what was written, byte for byte */
static void equal_complex_binary_order_response(const ComplexBinaryOrderResponse *read, const ComplexBinaryOrderResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->status == written->status);
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Complex Binary Order Response: written and read back, then read and written back */
static void check_complex_binary_order_response(void) {
  ComplexBinaryOrderResponse sent;
  ComplexBinaryOrderResponse got;
  uint8_t wire[33];
  uint8_t again[33];

  any_complex_binary_order_response(&sent);
  assert(encode_complex_binary_order_response(&sent, wire, 0) == 33);
  assert(decode_complex_binary_order_response(&got, wire, 0) == 33);
  equal_complex_binary_order_response(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_binary_order_response(&got, wire, 0) == 33);
  assert(encode_complex_binary_order_response(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- System State Notification: 18 bytes ------------------------------------- */

/* This message format is used to notify the firms of the state changes of the system. This is an exchange-wide notification and not a symbol or member-based notification */
typedef struct {
  uint8_t notification_time[8];  /* bytes 0 to 7 */
  uint8_t meo_version[8];        /* bytes 8 to 15 */
  uint8_t session_id;            /* byte 16 */
  uint8_t system_status;         /* byte 17 */
} SystemStateNotification;

/* any System State Notification at all: every byte one the checker chooses */
static void any_system_state_notification(SystemStateNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->meo_version[i] = arbitrary(); }
  record->session_id = arbitrary();
  record->system_status = arbitrary();
}

/* System State Notification to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_system_state_notification(const SystemStateNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->meo_version[i]; }
  wire[at++] = record->session_id;
  wire[at++] = record->system_status;

  return at;
}

/* System State Notification off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_system_state_notification(SystemStateNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->meo_version[i] = wire[at++]; }
  record->session_id = wire[at++];
  record->system_status = wire[at++];

  return at;
}

/* what was read of System State Notification is what was written, byte for byte */
static void equal_system_state_notification(const SystemStateNotification *read, const SystemStateNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->meo_version[i] == written->meo_version[i]); }
  assert(read->session_id == written->session_id);
  assert(read->system_status == written->system_status);
}

/* System State Notification: written and read back, then read and written back */
static void check_system_state_notification(void) {
  SystemStateNotification sent;
  SystemStateNotification got;
  uint8_t wire[18];
  uint8_t again[18];

  any_system_state_notification(&sent);
  assert(encode_system_state_notification(&sent, wire, 0) == 18);
  assert(decode_system_state_notification(&got, wire, 0) == 18);
  equal_system_state_notification(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_system_state_notification(&got, wire, 0) == 18);
  assert(encode_system_state_notification(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Trading Status Notification: 29 bytes ------------------------ */

/* This message format will be used to notify the firms of changes to the trading status of all the options of an underlying */
typedef struct {
  uint8_t notification_time[8];    /* bytes 0 to 7 */
  uint8_t underlying_symbol[11];   /* bytes 8 to 18 */
  uint8_t trading_status;          /* byte 19 */
  uint8_t event_reason;            /* byte 20 */
  uint8_t expected_event_time[8];  /* bytes 21 to 28 */
} UnderlyingTradingStatusNotification;

/* any Underlying Trading Status Notification at all: every byte one the checker chooses */
static void any_underlying_trading_status_notification(UnderlyingTradingStatusNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->event_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->expected_event_time[i] = arbitrary(); }
}

/* Underlying Trading Status Notification to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_underlying_trading_status_notification(const UnderlyingTradingStatusNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->event_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expected_event_time[i]; }

  return at;
}

/* Underlying Trading Status Notification off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_underlying_trading_status_notification(UnderlyingTradingStatusNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->event_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->expected_event_time[i] = wire[at++]; }

  return at;
}

/* what was read of Underlying Trading Status Notification is what was written, byte for byte */
static void equal_underlying_trading_status_notification(const UnderlyingTradingStatusNotification *read, const UnderlyingTradingStatusNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->event_reason == written->event_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->expected_event_time[i] == written->expected_event_time[i]); }
}

/* Underlying Trading Status Notification: written and read back, then read and written back */
static void check_underlying_trading_status_notification(void) {
  UnderlyingTradingStatusNotification sent;
  UnderlyingTradingStatusNotification got;
  uint8_t wire[29];
  uint8_t again[29];

  any_underlying_trading_status_notification(&sent);
  assert(encode_underlying_trading_status_notification(&sent, wire, 0) == 29);
  assert(decode_underlying_trading_status_notification(&got, wire, 0) == 29);
  equal_underlying_trading_status_notification(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_trading_status_notification(&got, wire, 0) == 29);
  assert(encode_underlying_trading_status_notification(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Width Relief Notification: 23 bytes ----------------------------- */

/* This message format will be used to notify the firms if and when Sapphire grants relief from valid opening width parameters for Opening as specified by regulatory circulars of Sapphire */
typedef struct {
  uint8_t notification_time[8];   /* bytes 0 to 7 */
  uint8_t underlying_symbol[11];  /* bytes 8 to 18 */
  uint8_t relief_multiplier[4];   /* bytes 19 to 22 */
} OpeningWidthReliefNotification;

/* any Opening Width Relief Notification at all: every byte one the checker chooses */
static void any_opening_width_relief_notification(OpeningWidthReliefNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->relief_multiplier[i] = arbitrary(); }
}

/* Opening Width Relief Notification to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_opening_width_relief_notification(const OpeningWidthReliefNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->relief_multiplier[i]; }

  return at;
}

/* Opening Width Relief Notification off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_opening_width_relief_notification(OpeningWidthReliefNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->relief_multiplier[i] = wire[at++]; }

  return at;
}

/* what was read of Opening Width Relief Notification is what was written, byte for byte */
static void equal_opening_width_relief_notification(const OpeningWidthReliefNotification *read, const OpeningWidthReliefNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->relief_multiplier[i] == written->relief_multiplier[i]); }
}

/* Opening Width Relief Notification: written and read back, then read and written back */
static void check_opening_width_relief_notification(void) {
  OpeningWidthReliefNotification sent;
  OpeningWidthReliefNotification got;
  uint8_t wire[23];
  uint8_t again[23];

  any_opening_width_relief_notification(&sent);
  assert(encode_opening_width_relief_notification(&sent, wire, 0) == 23);
  assert(decode_opening_width_relief_notification(&got, wire, 0) == 23);
  equal_opening_width_relief_notification(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_width_relief_notification(&got, wire, 0) == 23);
  assert(encode_opening_width_relief_notification(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Arm Protection Settings Notification: 31 bytes -------------------------- */

/* This message format will be used to notify firms of their ARM settings */
typedef struct {
  uint8_t notification_time[8];                /* bytes 0 to 7 */
  uint8_t mpid[4];                             /* bytes 8 to 11 */
  uint8_t underlying_symbol[11];               /* bytes 12 to 22 */
  uint8_t allowable_engagement_percentage[4];  /* bytes 23 to 26 */
  uint8_t counting_period_binary_u_2[2];       /* bytes 27 to 28 */
  uint8_t action;                              /* byte 29 */
  uint8_t source;                              /* byte 30 */
} ArmProtectionSettingsNotification;

/* any Arm Protection Settings Notification at all: every byte one the checker chooses */
static void any_arm_protection_settings_notification(ArmProtectionSettingsNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->allowable_engagement_percentage[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counting_period_binary_u_2[i] = arbitrary(); }
  record->action = arbitrary();
  record->source = arbitrary();
}

/* Arm Protection Settings Notification to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_arm_protection_settings_notification(const ArmProtectionSettingsNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->allowable_engagement_percentage[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counting_period_binary_u_2[i]; }
  wire[at++] = record->action;
  wire[at++] = record->source;

  return at;
}

/* Arm Protection Settings Notification off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_arm_protection_settings_notification(ArmProtectionSettingsNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->allowable_engagement_percentage[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counting_period_binary_u_2[i] = wire[at++]; }
  record->action = wire[at++];
  record->source = wire[at++];

  return at;
}

/* what was read of Arm Protection Settings Notification is what was written, byte for byte */
static void equal_arm_protection_settings_notification(const ArmProtectionSettingsNotification *read, const ArmProtectionSettingsNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->allowable_engagement_percentage[i] == written->allowable_engagement_percentage[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counting_period_binary_u_2[i] == written->counting_period_binary_u_2[i]); }
  assert(read->action == written->action);
  assert(read->source == written->source);
}

/* Arm Protection Settings Notification: written and read back, then read and written back */
static void check_arm_protection_settings_notification(void) {
  ArmProtectionSettingsNotification sent;
  ArmProtectionSettingsNotification got;
  uint8_t wire[31];
  uint8_t again[31];

  any_arm_protection_settings_notification(&sent);
  assert(encode_arm_protection_settings_notification(&sent, wire, 0) == 31);
  assert(decode_arm_protection_settings_notification(&got, wire, 0) == 31);
  equal_arm_protection_settings_notification(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_arm_protection_settings_notification(&got, wire, 0) == 31);
  assert(encode_arm_protection_settings_notification(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Arm 2 Underlying Level Protection Settings Notification: 48 bytes ------- */

/* This message format will be used to notify firms of their ARM2 Underlying Level protection settings */
typedef struct {
  uint8_t notification_time[8];               /* bytes 0 to 7 */
  uint8_t mpid[4];                            /* bytes 8 to 11 */
  uint8_t action;                             /* byte 12 */
  uint8_t underlying_symbol[11];              /* bytes 13 to 23 */
  uint8_t arm_threshold_count_binary_u_4[4];  /* bytes 24 to 27 */
  uint8_t counting_period_binary_u_4[4];      /* bytes 28 to 31 */
  uint8_t reserved_16[16];                    /* bytes 32 to 47 */
} Arm2UnderlyingLevelProtectionSettingsNotification;

/* any Arm 2 Underlying Level Protection Settings Notification at all: every byte one the checker chooses */
static void any_arm2_underlying_level_protection_settings_notification(Arm2UnderlyingLevelProtectionSettingsNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->action = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count_binary_u_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->counting_period_binary_u_4[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Arm 2 Underlying Level Protection Settings Notification to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_arm2_underlying_level_protection_settings_notification(const Arm2UnderlyingLevelProtectionSettingsNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->action;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->arm_threshold_count_binary_u_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->counting_period_binary_u_4[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Arm 2 Underlying Level Protection Settings Notification off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_arm2_underlying_level_protection_settings_notification(Arm2UnderlyingLevelProtectionSettingsNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->action = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count_binary_u_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->counting_period_binary_u_4[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Arm 2 Underlying Level Protection Settings Notification is what was written, byte for byte */
static void equal_arm2_underlying_level_protection_settings_notification(const Arm2UnderlyingLevelProtectionSettingsNotification *read, const Arm2UnderlyingLevelProtectionSettingsNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->action == written->action);
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->arm_threshold_count_binary_u_4[i] == written->arm_threshold_count_binary_u_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->counting_period_binary_u_4[i] == written->counting_period_binary_u_4[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Arm 2 Underlying Level Protection Settings Notification: written and read back, then read and written back */
static void check_arm2_underlying_level_protection_settings_notification(void) {
  Arm2UnderlyingLevelProtectionSettingsNotification sent;
  Arm2UnderlyingLevelProtectionSettingsNotification got;
  uint8_t wire[48];
  uint8_t again[48];

  any_arm2_underlying_level_protection_settings_notification(&sent);
  assert(encode_arm2_underlying_level_protection_settings_notification(&sent, wire, 0) == 48);
  assert(decode_arm2_underlying_level_protection_settings_notification(&got, wire, 0) == 48);
  equal_arm2_underlying_level_protection_settings_notification(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_arm2_underlying_level_protection_settings_notification(&got, wire, 0) == 48);
  assert(encode_arm2_underlying_level_protection_settings_notification(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Liquidity Protection Trigger Notification: 27 bytes --------- */

/* This message format will be used to notify firms when a Single Side Liquidity Protection is triggered for an Option or Strategy */
typedef struct {
  uint8_t notification_time[8];             /* bytes 0 to 7 */
  uint8_t mpid[4];                          /* bytes 8 to 11 */
  uint8_t security_id_scope;                /* byte 12 */
  uint8_t security_id[4];                   /* bytes 13 to 16 */
  uint8_t side;                             /* byte 17 */
  uint8_t triggering_client_message_id[4];  /* bytes 18 to 21 */
  uint8_t triggering_bulk_order_index;      /* byte 22 */
  uint8_t reserved_4[4];                    /* bytes 23 to 26 */
} SingleSideLiquidityProtectionTriggerNotification;

/* any Single Side Liquidity Protection Trigger Notification at all: every byte one the checker chooses */
static void any_single_side_liquidity_protection_trigger_notification(SingleSideLiquidityProtectionTriggerNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->security_id_scope = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->security_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->triggering_client_message_id[i] = arbitrary(); }
  record->triggering_bulk_order_index = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Single Side Liquidity Protection Trigger Notification to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_single_side_liquidity_protection_trigger_notification(const SingleSideLiquidityProtectionTriggerNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->security_id_scope;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->triggering_client_message_id[i]; }
  wire[at++] = record->triggering_bulk_order_index;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Single Side Liquidity Protection Trigger Notification off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_single_side_liquidity_protection_trigger_notification(SingleSideLiquidityProtectionTriggerNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->security_id_scope = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->security_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->triggering_client_message_id[i] = wire[at++]; }
  record->triggering_bulk_order_index = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Liquidity Protection Trigger Notification is what was written, byte for byte */
static void equal_single_side_liquidity_protection_trigger_notification(const SingleSideLiquidityProtectionTriggerNotification *read, const SingleSideLiquidityProtectionTriggerNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->security_id_scope == written->security_id_scope);
  for (size_t i = 0; i < 4; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->triggering_client_message_id[i] == written->triggering_client_message_id[i]); }
  assert(read->triggering_bulk_order_index == written->triggering_bulk_order_index);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Single Side Liquidity Protection Trigger Notification: written and read back, then read and written back */
static void check_single_side_liquidity_protection_trigger_notification(void) {
  SingleSideLiquidityProtectionTriggerNotification sent;
  SingleSideLiquidityProtectionTriggerNotification got;
  uint8_t wire[27];
  uint8_t again[27];

  any_single_side_liquidity_protection_trigger_notification(&sent);
  assert(encode_single_side_liquidity_protection_trigger_notification(&sent, wire, 0) == 27);
  assert(decode_single_side_liquidity_protection_trigger_notification(&got, wire, 0) == 27);
  equal_single_side_liquidity_protection_trigger_notification(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_liquidity_protection_trigger_notification(&got, wire, 0) == 27);
  assert(encode_single_side_liquidity_protection_trigger_notification(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Arm 2 Underlying Level Protection Notification: 48 bytes ---------------- */

/* This message format will be used to notify firms about ARM2 Underlying Level protection events */
typedef struct {
  uint8_t notification_time[8];               /* bytes 0 to 7 */
  uint8_t mpid[4];                            /* bytes 8 to 11 */
  uint8_t underlying_symbol[11];              /* bytes 12 to 22 */
  uint8_t notification_type;                  /* byte 23 */
  uint8_t arm_threshold_count_binary_u_4[4];  /* bytes 24 to 27 */
  uint8_t counting_period_binary_u_4[4];      /* bytes 28 to 31 */
  uint8_t reserved_16[16];                    /* bytes 32 to 47 */
} Arm2UnderlyingLevelProtectionNotification;

/* any Arm 2 Underlying Level Protection Notification at all: every byte one the checker chooses */
static void any_arm2_underlying_level_protection_notification(Arm2UnderlyingLevelProtectionNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->notification_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count_binary_u_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->counting_period_binary_u_4[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Arm 2 Underlying Level Protection Notification to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_arm2_underlying_level_protection_notification(const Arm2UnderlyingLevelProtectionNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->notification_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->arm_threshold_count_binary_u_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->counting_period_binary_u_4[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Arm 2 Underlying Level Protection Notification off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_arm2_underlying_level_protection_notification(Arm2UnderlyingLevelProtectionNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->notification_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count_binary_u_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->counting_period_binary_u_4[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Arm 2 Underlying Level Protection Notification is what was written, byte for byte */
static void equal_arm2_underlying_level_protection_notification(const Arm2UnderlyingLevelProtectionNotification *read, const Arm2UnderlyingLevelProtectionNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->notification_type == written->notification_type);
  for (size_t i = 0; i < 4; i++) { assert(read->arm_threshold_count_binary_u_4[i] == written->arm_threshold_count_binary_u_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->counting_period_binary_u_4[i] == written->counting_period_binary_u_4[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Arm 2 Underlying Level Protection Notification: written and read back, then read and written back */
static void check_arm2_underlying_level_protection_notification(void) {
  Arm2UnderlyingLevelProtectionNotification sent;
  Arm2UnderlyingLevelProtectionNotification got;
  uint8_t wire[48];
  uint8_t again[48];

  any_arm2_underlying_level_protection_notification(&sent);
  assert(encode_arm2_underlying_level_protection_notification(&sent, wire, 0) == 48);
  assert(decode_arm2_underlying_level_protection_notification(&got, wire, 0) == 48);
  equal_arm2_underlying_level_protection_notification(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_arm2_underlying_level_protection_notification(&got, wire, 0) == 48);
  assert(encode_arm2_underlying_level_protection_notification(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Arm 2 Firm Level Protection Notification: 33 bytes ---------------------- */

/* This message format will be used to notify firms about ARM2 Firm Level protection events */
typedef struct {
  uint8_t notification_time[8];                /* bytes 0 to 7 */
  uint8_t arm_threshold_count_binary_4u_4[4];  /* bytes 8 to 11 */
  uint8_t counting_period_binary_4u_4[4];      /* bytes 12 to 15 */
  uint8_t notification_type;                   /* byte 16 */
  uint8_t reserved_16[16];                     /* bytes 17 to 32 */
} Arm2FirmLevelProtectionNotification;

/* any Arm 2 Firm Level Protection Notification at all: every byte one the checker chooses */
static void any_arm2_firm_level_protection_notification(Arm2FirmLevelProtectionNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count_binary_4u_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->counting_period_binary_4u_4[i] = arbitrary(); }
  record->notification_type = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Arm 2 Firm Level Protection Notification to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_arm2_firm_level_protection_notification(const Arm2FirmLevelProtectionNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->arm_threshold_count_binary_4u_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->counting_period_binary_4u_4[i]; }
  wire[at++] = record->notification_type;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Arm 2 Firm Level Protection Notification off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_arm2_firm_level_protection_notification(Arm2FirmLevelProtectionNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count_binary_4u_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->counting_period_binary_4u_4[i] = wire[at++]; }
  record->notification_type = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Arm 2 Firm Level Protection Notification is what was written, byte for byte */
static void equal_arm2_firm_level_protection_notification(const Arm2FirmLevelProtectionNotification *read, const Arm2FirmLevelProtectionNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->arm_threshold_count_binary_4u_4[i] == written->arm_threshold_count_binary_4u_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->counting_period_binary_4u_4[i] == written->counting_period_binary_4u_4[i]); }
  assert(read->notification_type == written->notification_type);
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Arm 2 Firm Level Protection Notification: written and read back, then read and written back */
static void check_arm2_firm_level_protection_notification(void) {
  Arm2FirmLevelProtectionNotification sent;
  Arm2FirmLevelProtectionNotification got;
  uint8_t wire[33];
  uint8_t again[33];

  any_arm2_firm_level_protection_notification(&sent);
  assert(encode_arm2_firm_level_protection_notification(&sent, wire, 0) == 33);
  assert(decode_arm2_firm_level_protection_notification(&got, wire, 0) == 33);
  equal_arm2_firm_level_protection_notification(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_arm2_firm_level_protection_notification(&got, wire, 0) == 33);
  assert(encode_arm2_firm_level_protection_notification(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Notification: 48 bytes ------------------------------------------- */

/* This is the message format that will be used to notify firms about Simple or Complex order cancels. By default this is not a sequenced message; firms can request it to be configured as a sequenced message */
typedef struct {
  uint8_t notification_time[8];       /* bytes 0 to 7 */
  uint8_t mpid[4];                    /* bytes 8 to 11 */
  uint8_t security_id_scope;          /* byte 12 */
  uint8_t security_id[4];             /* bytes 13 to 16 */
  uint8_t client_message_id[4];       /* bytes 17 to 20 */
  uint8_t client_order_id[4];         /* bytes 21 to 24 */
  uint8_t bulk_order_index;           /* byte 25 */
  uint8_t side;                       /* byte 26 */
  uint8_t size[4];                    /* bytes 27 to 30 */
  uint8_t engine_sequence_number[8];  /* bytes 31 to 38 */
  uint8_t cancel_reason;              /* byte 39 */
  uint8_t reserved_8[8];              /* bytes 40 to 47 */
} CancelNotification;

/* any Cancel Notification at all: every byte one the checker chooses */
static void any_cancel_notification(CancelNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->security_id_scope = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_order_id[i] = arbitrary(); }
  record->bulk_order_index = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->engine_sequence_number[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Cancel Notification to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_cancel_notification(const CancelNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->security_id_scope;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->bulk_order_index;
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->engine_sequence_number[i]; }
  wire[at++] = record->cancel_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Cancel Notification off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_cancel_notification(CancelNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->security_id_scope = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_order_id[i] = wire[at++]; }
  record->bulk_order_index = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->engine_sequence_number[i] = wire[at++]; }
  record->cancel_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Notification is what was written, byte for byte */
static void equal_cancel_notification(const CancelNotification *read, const CancelNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->security_id_scope == written->security_id_scope);
  for (size_t i = 0; i < 4; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->bulk_order_index == written->bulk_order_index);
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->engine_sequence_number[i] == written->engine_sequence_number[i]); }
  assert(read->cancel_reason == written->cancel_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Cancel Notification: written and read back, then read and written back */
static void check_cancel_notification(void) {
  CancelNotification sent;
  CancelNotification got;
  uint8_t wire[48];
  uint8_t again[48];

  any_cancel_notification(&sent);
  assert(encode_cancel_notification(&sent, wire, 0) == 48);
  assert(decode_cancel_notification(&got, wire, 0) == 48);
  equal_cancel_notification(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_notification(&got, wire, 0) == 48);
  assert(encode_cancel_notification(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Notification: 64 bytes ---------------------------------------- */

/* This message format will be used to notify the firms of executions of their orders */
typedef struct {
  uint8_t notification_time[8];  /* bytes 0 to 7 */
  uint8_t mpid[4];               /* bytes 8 to 11 */
  uint8_t liquidity_type;        /* byte 12 */
  uint8_t product_id[4];         /* bytes 13 to 16 */
  uint8_t client_message_id[4];  /* bytes 17 to 20 */
  uint8_t client_order_id[4];    /* bytes 21 to 24 */
  uint8_t bulk_order_index;      /* byte 25 */
  uint8_t trade_id[4];           /* bytes 26 to 29 */
  uint8_t execution_id[8];       /* bytes 30 to 37 */
  uint8_t trade_status;          /* byte 38 */
  uint8_t last_price[4];         /* bytes 39 to 42 */
  uint8_t side;                  /* byte 43 */
  uint8_t last_size[4];          /* bytes 44 to 47 */
  uint8_t liquidity_indicator;   /* byte 48 */
  uint8_t reserved_15[15];       /* bytes 49 to 63 */
} ExecutionNotification;

/* any Execution Notification at all: every byte one the checker chooses */
static void any_execution_notification(ExecutionNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->liquidity_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_order_id[i] = arbitrary(); }
  record->bulk_order_index = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->trade_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_size[i] = arbitrary(); }
  record->liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->reserved_15[i] = arbitrary(); }
}

/* Execution Notification to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_execution_notification(const ExecutionNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->liquidity_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->bulk_order_index;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->trade_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_price[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_size[i]; }
  wire[at++] = record->liquidity_indicator;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->reserved_15[i]; }

  return at;
}

/* Execution Notification off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_execution_notification(ExecutionNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->liquidity_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_order_id[i] = wire[at++]; }
  record->bulk_order_index = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->trade_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_size[i] = wire[at++]; }
  record->liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->reserved_15[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Notification is what was written, byte for byte */
static void equal_execution_notification(const ExecutionNotification *read, const ExecutionNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->liquidity_type == written->liquidity_type);
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->bulk_order_index == written->bulk_order_index);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->trade_status == written->trade_status);
  for (size_t i = 0; i < 4; i++) { assert(read->last_price[i] == written->last_price[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->last_size[i] == written->last_size[i]); }
  assert(read->liquidity_indicator == written->liquidity_indicator);
  for (size_t i = 0; i < 15; i++) { assert(read->reserved_15[i] == written->reserved_15[i]); }
}

/* Execution Notification: written and read back, then read and written back */
static void check_execution_notification(void) {
  ExecutionNotification sent;
  ExecutionNotification got;
  uint8_t wire[64];
  uint8_t again[64];

  any_execution_notification(&sent);
  assert(encode_execution_notification(&sent, wire, 0) == 64);
  assert(decode_execution_notification(&got, wire, 0) == 64);
  equal_execution_notification(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_notification(&got, wire, 0) == 64);
  assert(encode_execution_notification(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Leg Execution Notification: 67 bytes ------------------------------ */

/* This message format will be used to notify the firm of a stock leg execution from a stock-tied complex binary order */
typedef struct {
  uint8_t notification_time[8];        /* bytes 0 to 7 */
  uint8_t mpid[4];                     /* bytes 8 to 11 */
  uint8_t underlying_symbol[11];       /* bytes 12 to 22 */
  uint8_t liquidity_type;              /* byte 23 */
  uint8_t client_message_id[4];        /* bytes 24 to 27 */
  uint8_t trade_id[4];                 /* bytes 28 to 31 */
  uint8_t execution_id[8];             /* bytes 32 to 39 */
  uint8_t trade_status;                /* byte 40 */
  uint8_t last_price[4];               /* bytes 41 to 44 */
  uint8_t side;                        /* byte 45 */
  uint8_t stock_sell_short_indicator;  /* byte 46 */
  uint8_t last_size[4];                /* bytes 47 to 50 */
  uint8_t reserved_16[16];             /* bytes 51 to 66 */
} StockLegExecutionNotification;

/* any Stock Leg Execution Notification at all: every byte one the checker chooses */
static void any_stock_leg_execution_notification(StockLegExecutionNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->liquidity_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->trade_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = arbitrary(); }
  record->side = arbitrary();
  record->stock_sell_short_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_size[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Stock Leg Execution Notification to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_stock_leg_execution_notification(const StockLegExecutionNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->liquidity_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->trade_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_price[i]; }
  wire[at++] = record->side;
  wire[at++] = record->stock_sell_short_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_size[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Stock Leg Execution Notification off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_stock_leg_execution_notification(StockLegExecutionNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->liquidity_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->trade_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = wire[at++]; }
  record->side = wire[at++];
  record->stock_sell_short_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_size[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Stock Leg Execution Notification is what was written, byte for byte */
static void equal_stock_leg_execution_notification(const StockLegExecutionNotification *read, const StockLegExecutionNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->liquidity_type == written->liquidity_type);
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->trade_status == written->trade_status);
  for (size_t i = 0; i < 4; i++) { assert(read->last_price[i] == written->last_price[i]); }
  assert(read->side == written->side);
  assert(read->stock_sell_short_indicator == written->stock_sell_short_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->last_size[i] == written->last_size[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Stock Leg Execution Notification: written and read back, then read and written back */
static void check_stock_leg_execution_notification(void) {
  StockLegExecutionNotification sent;
  StockLegExecutionNotification got;
  uint8_t wire[67];
  uint8_t again[67];

  any_stock_leg_execution_notification(&sent);
  assert(encode_stock_leg_execution_notification(&sent, wire, 0) == 67);
  assert(decode_stock_leg_execution_notification(&got, wire, 0) == 67);
  equal_stock_leg_execution_notification(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_leg_execution_notification(&got, wire, 0) == 67);
  assert(encode_stock_leg_execution_notification(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Arm Settings Update Request: 26 bytes ----------------------------------- */

/* Firms can use this message format to set up their ARM protection settings for each session. Changes to these settings can be made throughout the day */
typedef struct {
  uint8_t client_message_id[4];                /* bytes 0 to 3 */
  uint8_t mpid[4];                             /* bytes 4 to 7 */
  uint8_t action;                              /* byte 8 */
  uint8_t underlying_symbol[11];               /* bytes 9 to 19 */
  uint8_t allowable_engagement_percentage[4];  /* bytes 20 to 23 */
  uint8_t counting_period_binary_u_2[2];       /* bytes 24 to 25 */
} ArmSettingsUpdateRequest;

/* any Arm Settings Update Request at all: every byte one the checker chooses */
static void any_arm_settings_update_request(ArmSettingsUpdateRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->action = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->allowable_engagement_percentage[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counting_period_binary_u_2[i] = arbitrary(); }
}

/* Arm Settings Update Request to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_arm_settings_update_request(const ArmSettingsUpdateRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->action;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->allowable_engagement_percentage[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counting_period_binary_u_2[i]; }

  return at;
}

/* Arm Settings Update Request off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_arm_settings_update_request(ArmSettingsUpdateRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->action = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->allowable_engagement_percentage[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counting_period_binary_u_2[i] = wire[at++]; }

  return at;
}

/* what was read of Arm Settings Update Request is what was written, byte for byte */
static void equal_arm_settings_update_request(const ArmSettingsUpdateRequest *read, const ArmSettingsUpdateRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->action == written->action);
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->allowable_engagement_percentage[i] == written->allowable_engagement_percentage[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counting_period_binary_u_2[i] == written->counting_period_binary_u_2[i]); }
}

/* Arm Settings Update Request: written and read back, then read and written back */
static void check_arm_settings_update_request(void) {
  ArmSettingsUpdateRequest sent;
  ArmSettingsUpdateRequest got;
  uint8_t wire[26];
  uint8_t again[26];

  any_arm_settings_update_request(&sent);
  assert(encode_arm_settings_update_request(&sent, wire, 0) == 26);
  assert(decode_arm_settings_update_request(&got, wire, 0) == 26);
  equal_arm_settings_update_request(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_arm_settings_update_request(&got, wire, 0) == 26);
  assert(encode_arm_settings_update_request(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Arm Settings Update Response: 20 bytes ---------------------------------- */

/* Sapphire uses this format to respond to the firm with a status of their ARM protection settings request */
typedef struct {
  uint8_t client_message_id[4];        /* bytes 0 to 3 */
  uint8_t mpid[4];                     /* bytes 4 to 7 */
  uint8_t underlying_symbol[11];       /* bytes 8 to 18 */
  uint8_t arm_settings_update_status;  /* byte 19 */
} ArmSettingsUpdateResponse;

/* any Arm Settings Update Response at all: every byte one the checker chooses */
static void any_arm_settings_update_response(ArmSettingsUpdateResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->arm_settings_update_status = arbitrary();
}

/* Arm Settings Update Response to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_arm_settings_update_response(const ArmSettingsUpdateResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->arm_settings_update_status;

  return at;
}

/* Arm Settings Update Response off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_arm_settings_update_response(ArmSettingsUpdateResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->arm_settings_update_status = wire[at++];

  return at;
}

/* what was read of Arm Settings Update Response is what was written, byte for byte */
static void equal_arm_settings_update_response(const ArmSettingsUpdateResponse *read, const ArmSettingsUpdateResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->arm_settings_update_status == written->arm_settings_update_status);
}

/* Arm Settings Update Response: written and read back, then read and written back */
static void check_arm_settings_update_response(void) {
  ArmSettingsUpdateResponse sent;
  ArmSettingsUpdateResponse got;
  uint8_t wire[20];
  uint8_t again[20];

  any_arm_settings_update_response(&sent);
  assert(encode_arm_settings_update_response(&sent, wire, 0) == 20);
  assert(decode_arm_settings_update_response(&got, wire, 0) == 20);
  equal_arm_settings_update_response(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_arm_settings_update_response(&got, wire, 0) == 20);
  assert(encode_arm_settings_update_response(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Arm 2 Underlying Level Protection Settings Update Request: 28 bytes ----- */

/* Firms can use this message format to set up their ARM2 Underlying Level protection settings for each session. Changes to these settings can be made throughout the day */
typedef struct {
  uint8_t client_message_id[4];               /* bytes 0 to 3 */
  uint8_t mpid[4];                            /* bytes 4 to 7 */
  uint8_t action;                             /* byte 8 */
  uint8_t underlying_symbol[11];              /* bytes 9 to 19 */
  uint8_t arm_threshold_count_binary_u_4[4];  /* bytes 20 to 23 */
  uint8_t counting_period_binary_u_4[4];      /* bytes 24 to 27 */
} Arm2UnderlyingLevelProtectionSettingsUpdateRequest;

/* any Arm 2 Underlying Level Protection Settings Update Request at all: every byte one the checker chooses */
static void any_arm2_underlying_level_protection_settings_update_request(Arm2UnderlyingLevelProtectionSettingsUpdateRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->action = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count_binary_u_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->counting_period_binary_u_4[i] = arbitrary(); }
}

/* Arm 2 Underlying Level Protection Settings Update Request to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_arm2_underlying_level_protection_settings_update_request(const Arm2UnderlyingLevelProtectionSettingsUpdateRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->action;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->arm_threshold_count_binary_u_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->counting_period_binary_u_4[i]; }

  return at;
}

/* Arm 2 Underlying Level Protection Settings Update Request off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_arm2_underlying_level_protection_settings_update_request(Arm2UnderlyingLevelProtectionSettingsUpdateRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->action = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count_binary_u_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->counting_period_binary_u_4[i] = wire[at++]; }

  return at;
}

/* what was read of Arm 2 Underlying Level Protection Settings Update Request is what was written, byte for byte */
static void equal_arm2_underlying_level_protection_settings_update_request(const Arm2UnderlyingLevelProtectionSettingsUpdateRequest *read, const Arm2UnderlyingLevelProtectionSettingsUpdateRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->action == written->action);
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->arm_threshold_count_binary_u_4[i] == written->arm_threshold_count_binary_u_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->counting_period_binary_u_4[i] == written->counting_period_binary_u_4[i]); }
}

/* Arm 2 Underlying Level Protection Settings Update Request: written and read back, then read and written back */
static void check_arm2_underlying_level_protection_settings_update_request(void) {
  Arm2UnderlyingLevelProtectionSettingsUpdateRequest sent;
  Arm2UnderlyingLevelProtectionSettingsUpdateRequest got;
  uint8_t wire[28];
  uint8_t again[28];

  any_arm2_underlying_level_protection_settings_update_request(&sent);
  assert(encode_arm2_underlying_level_protection_settings_update_request(&sent, wire, 0) == 28);
  assert(decode_arm2_underlying_level_protection_settings_update_request(&got, wire, 0) == 28);
  equal_arm2_underlying_level_protection_settings_update_request(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_arm2_underlying_level_protection_settings_update_request(&got, wire, 0) == 28);
  assert(encode_arm2_underlying_level_protection_settings_update_request(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Arm 2 Underlying Level Protection Settings Update Response: 20 bytes ---- */

/* Sapphire uses this format to respond to the firm with a status of their ARM2 Underlying level protection Settings Update Request */
typedef struct {
  uint8_t client_message_id[4];          /* bytes 0 to 3 */
  uint8_t mpid[4];                       /* bytes 4 to 7 */
  uint8_t underlying_symbol[11];         /* bytes 8 to 18 */
  uint8_t arm_2_settings_update_status;  /* byte 19 */
} Arm2UnderlyingLevelProtectionSettingsUpdateResponse;

/* any Arm 2 Underlying Level Protection Settings Update Response at all: every byte one the checker chooses */
static void any_arm2_underlying_level_protection_settings_update_response(Arm2UnderlyingLevelProtectionSettingsUpdateResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->arm_2_settings_update_status = arbitrary();
}

/* Arm 2 Underlying Level Protection Settings Update Response to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_arm2_underlying_level_protection_settings_update_response(const Arm2UnderlyingLevelProtectionSettingsUpdateResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->arm_2_settings_update_status;

  return at;
}

/* Arm 2 Underlying Level Protection Settings Update Response off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_arm2_underlying_level_protection_settings_update_response(Arm2UnderlyingLevelProtectionSettingsUpdateResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->arm_2_settings_update_status = wire[at++];

  return at;
}

/* what was read of Arm 2 Underlying Level Protection Settings Update Response is what was written, byte for byte */
static void equal_arm2_underlying_level_protection_settings_update_response(const Arm2UnderlyingLevelProtectionSettingsUpdateResponse *read, const Arm2UnderlyingLevelProtectionSettingsUpdateResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->arm_2_settings_update_status == written->arm_2_settings_update_status);
}

/* Arm 2 Underlying Level Protection Settings Update Response: written and read back, then read and written back */
static void check_arm2_underlying_level_protection_settings_update_response(void) {
  Arm2UnderlyingLevelProtectionSettingsUpdateResponse sent;
  Arm2UnderlyingLevelProtectionSettingsUpdateResponse got;
  uint8_t wire[20];
  uint8_t again[20];

  any_arm2_underlying_level_protection_settings_update_response(&sent);
  assert(encode_arm2_underlying_level_protection_settings_update_response(&sent, wire, 0) == 20);
  assert(decode_arm2_underlying_level_protection_settings_update_response(&got, wire, 0) == 20);
  equal_arm2_underlying_level_protection_settings_update_response(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_arm2_underlying_level_protection_settings_update_response(&got, wire, 0) == 20);
  assert(encode_arm2_underlying_level_protection_settings_update_response(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Series Assignment Request: 13 bytes ------------------------------------- */

/* Market Making firms can use this message format to communicate to Sapphire which of their MM MPIDs is assigned or unassigned in a product */
typedef struct {
  uint8_t client_message_id[4];  /* bytes 0 to 3 */
  uint8_t mpid[4];               /* bytes 4 to 7 */
  uint8_t product_id[4];         /* bytes 8 to 11 */
  uint8_t action;                /* byte 12 */
} SeriesAssignmentRequest;

/* any Series Assignment Request at all: every byte one the checker chooses */
static void any_series_assignment_request(SeriesAssignmentRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  record->action = arbitrary();
}

/* Series Assignment Request to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_series_assignment_request(const SeriesAssignmentRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  wire[at++] = record->action;

  return at;
}

/* Series Assignment Request off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_series_assignment_request(SeriesAssignmentRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  record->action = wire[at++];

  return at;
}

/* what was read of Series Assignment Request is what was written, byte for byte */
static void equal_series_assignment_request(const SeriesAssignmentRequest *read, const SeriesAssignmentRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  assert(read->action == written->action);
}

/* Series Assignment Request: written and read back, then read and written back */
static void check_series_assignment_request(void) {
  SeriesAssignmentRequest sent;
  SeriesAssignmentRequest got;
  uint8_t wire[13];
  uint8_t again[13];

  any_series_assignment_request(&sent);
  assert(encode_series_assignment_request(&sent, wire, 0) == 13);
  assert(decode_series_assignment_request(&got, wire, 0) == 13);
  equal_series_assignment_request(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_series_assignment_request(&got, wire, 0) == 13);
  assert(encode_series_assignment_request(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Series Assignment Response: 9 bytes ------------------------------------- */

/* Sapphire uses this format to respond to the firm assignment request */
typedef struct {
  uint8_t client_message_id[4];        /* bytes 0 to 3 */
  uint8_t mpid[4];                     /* bytes 4 to 7 */
  uint8_t assignment_settings_status;  /* byte 8 */
} SeriesAssignmentResponse;

/* any Series Assignment Response at all: every byte one the checker chooses */
static void any_series_assignment_response(SeriesAssignmentResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->assignment_settings_status = arbitrary();
}

/* Series Assignment Response to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_series_assignment_response(const SeriesAssignmentResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->assignment_settings_status;

  return at;
}

/* Series Assignment Response off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_series_assignment_response(SeriesAssignmentResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->assignment_settings_status = wire[at++];

  return at;
}

/* what was read of Series Assignment Response is what was written, byte for byte */
static void equal_series_assignment_response(const SeriesAssignmentResponse *read, const SeriesAssignmentResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->assignment_settings_status == written->assignment_settings_status);
}

/* Series Assignment Response: written and read back, then read and written back */
static void check_series_assignment_response(void) {
  SeriesAssignmentResponse sent;
  SeriesAssignmentResponse got;
  uint8_t wire[9];
  uint8_t again[9];

  any_series_assignment_response(&sent);
  assert(encode_series_assignment_response(&sent, wire, 0) == 9);
  assert(decode_series_assignment_response(&got, wire, 0) == 9);
  equal_series_assignment_response(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_series_assignment_response(&got, wire, 0) == 9);
  assert(encode_series_assignment_response(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Binary Order Request: 51 bytes ---------------------------------- */

/* This is the format for a Complex Binary Order message that can be sent to match with a resting Complex orders on the complex book */
typedef struct {
  uint8_t client_message_id[4];        /* bytes 0 to 3 */
  uint8_t mpid[4];                     /* bytes 4 to 7 */
  uint8_t client_send_time[8];         /* bytes 8 to 15 */
  uint8_t strategy_id[4];              /* bytes 16 to 19 */
  uint8_t time_in_force;               /* byte 20 */
  uint8_t price_binary_prc_4s_8[8];    /* bytes 21 to 28 */
  uint8_t size[4];                     /* bytes 29 to 32 */
  uint8_t side;                        /* byte 33 */
  uint8_t stock_sell_short_indicator;  /* byte 34 */
  uint8_t reserved_16[16];             /* bytes 35 to 50 */
} ComplexBinaryOrderRequest;

/* any Complex Binary Order Request at all: every byte one the checker chooses */
static void any_complex_binary_order_request(ComplexBinaryOrderRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_binary_prc_4s_8[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  record->side = arbitrary();
  record->stock_sell_short_indicator = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Complex Binary Order Request to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_complex_binary_order_request(const ComplexBinaryOrderRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_send_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_binary_prc_4s_8[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  wire[at++] = record->side;
  wire[at++] = record->stock_sell_short_indicator;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Complex Binary Order Request off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_complex_binary_order_request(ComplexBinaryOrderRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_binary_prc_4s_8[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  record->side = wire[at++];
  record->stock_sell_short_indicator = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Binary Order Request is what was written, byte for byte */
static void equal_complex_binary_order_request(const ComplexBinaryOrderRequest *read, const ComplexBinaryOrderRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_send_time[i] == written->client_send_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 8; i++) { assert(read->price_binary_prc_4s_8[i] == written->price_binary_prc_4s_8[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  assert(read->side == written->side);
  assert(read->stock_sell_short_indicator == written->stock_sell_short_indicator);
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Complex Binary Order Request: written and read back, then read and written back */
static void check_complex_binary_order_request(void) {
  ComplexBinaryOrderRequest sent;
  ComplexBinaryOrderRequest got;
  uint8_t wire[51];
  uint8_t again[51];

  any_complex_binary_order_request(&sent);
  assert(encode_complex_binary_order_request(&sent, wire, 0) == 51);
  assert(decode_complex_binary_order_request(&got, wire, 0) == 51);
  equal_complex_binary_order_request(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_binary_order_request(&got, wire, 0) == 51);
  assert(encode_complex_binary_order_request(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Liquidity Mass Cancel Response: 9 bytes --------------------------------- */

/* This message format will be used to inform the firm about the status of their previous Mass Cancel request */
typedef struct {
  uint8_t client_message_id[4];  /* bytes 0 to 3 */
  uint8_t mpid[4];               /* bytes 4 to 7 */
  uint8_t status;                /* byte 8 */
} LiquidityMassCancelResponse;

/* any Liquidity Mass Cancel Response at all: every byte one the checker chooses */
static void any_liquidity_mass_cancel_response(LiquidityMassCancelResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->status = arbitrary();
}

/* Liquidity Mass Cancel Response to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_liquidity_mass_cancel_response(const LiquidityMassCancelResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->status;

  return at;
}

/* Liquidity Mass Cancel Response off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_liquidity_mass_cancel_response(LiquidityMassCancelResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->status = wire[at++];

  return at;
}

/* what was read of Liquidity Mass Cancel Response is what was written, byte for byte */
static void equal_liquidity_mass_cancel_response(const LiquidityMassCancelResponse *read, const LiquidityMassCancelResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->status == written->status);
}

/* Liquidity Mass Cancel Response: written and read back, then read and written back */
static void check_liquidity_mass_cancel_response(void) {
  LiquidityMassCancelResponse sent;
  LiquidityMassCancelResponse got;
  uint8_t wire[9];
  uint8_t again[9];

  any_liquidity_mass_cancel_response(&sent);
  assert(encode_liquidity_mass_cancel_response(&sent, wire, 0) == 9);
  assert(decode_liquidity_mass_cancel_response(&got, wire, 0) == 9);
  equal_liquidity_mass_cancel_response(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_liquidity_mass_cancel_response(&got, wire, 0) == 9);
  assert(encode_liquidity_mass_cancel_response(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Liquidity Protection Reset Response: 9 bytes ---------------------------- */

/* This message format is used to inform the firms of the status of their Order Protection Reset Request */
typedef struct {
  uint8_t client_message_id[4];  /* bytes 0 to 3 */
  uint8_t mpid[4];               /* bytes 4 to 7 */
  uint8_t status;                /* byte 8 */
} LiquidityProtectionResetResponse;

/* any Liquidity Protection Reset Response at all: every byte one the checker chooses */
static void any_liquidity_protection_reset_response(LiquidityProtectionResetResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->status = arbitrary();
}

/* Liquidity Protection Reset Response to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_liquidity_protection_reset_response(const LiquidityProtectionResetResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->status;

  return at;
}

/* Liquidity Protection Reset Response off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_liquidity_protection_reset_response(LiquidityProtectionResetResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->status = wire[at++];

  return at;
}

/* what was read of Liquidity Protection Reset Response is what was written, byte for byte */
static void equal_liquidity_protection_reset_response(const LiquidityProtectionResetResponse *read, const LiquidityProtectionResetResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->status == written->status);
}

/* Liquidity Protection Reset Response: written and read back, then read and written back */
static void check_liquidity_protection_reset_response(void) {
  LiquidityProtectionResetResponse sent;
  LiquidityProtectionResetResponse got;
  uint8_t wire[9];
  uint8_t again[9];

  any_liquidity_protection_reset_response(&sent);
  assert(encode_liquidity_protection_reset_response(&sent, wire, 0) == 9);
  assert(decode_liquidity_protection_reset_response(&got, wire, 0) == 9);
  equal_liquidity_protection_reset_response(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_liquidity_protection_reset_response(&got, wire, 0) == 9);
  assert(encode_liquidity_protection_reset_response(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Liquidity Protection Reset Request: 18 bytes ---------------- */

/* Request to reset Single Side Liquidity Protection for the specific Option or Complex Strategy */
typedef struct {
  uint8_t client_message_id[4];  /* bytes 0 to 3 */
  uint8_t mpid[4];               /* bytes 4 to 7 */
  uint8_t security_id_scope;     /* byte 8 */
  uint8_t security_id[4];        /* bytes 9 to 12 */
  uint8_t side;                  /* byte 13 */
  uint8_t reserved_4[4];         /* bytes 14 to 17 */
} SingleSideLiquidityProtectionResetRequest;

/* any Single Side Liquidity Protection Reset Request at all: every byte one the checker chooses */
static void any_single_side_liquidity_protection_reset_request(SingleSideLiquidityProtectionResetRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->security_id_scope = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->security_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Single Side Liquidity Protection Reset Request to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_single_side_liquidity_protection_reset_request(const SingleSideLiquidityProtectionResetRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->security_id_scope;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Single Side Liquidity Protection Reset Request off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_single_side_liquidity_protection_reset_request(SingleSideLiquidityProtectionResetRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->security_id_scope = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->security_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Single Side Liquidity Protection Reset Request is what was written, byte for byte */
static void equal_single_side_liquidity_protection_reset_request(const SingleSideLiquidityProtectionResetRequest *read, const SingleSideLiquidityProtectionResetRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->security_id_scope == written->security_id_scope);
  for (size_t i = 0; i < 4; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Single Side Liquidity Protection Reset Request: written and read back, then read and written back */
static void check_single_side_liquidity_protection_reset_request(void) {
  SingleSideLiquidityProtectionResetRequest sent;
  SingleSideLiquidityProtectionResetRequest got;
  uint8_t wire[18];
  uint8_t again[18];

  any_single_side_liquidity_protection_reset_request(&sent);
  assert(encode_single_side_liquidity_protection_reset_request(&sent, wire, 0) == 18);
  assert(decode_single_side_liquidity_protection_reset_request(&got, wire, 0) == 18);
  equal_single_side_liquidity_protection_reset_request(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_liquidity_protection_reset_request(&got, wire, 0) == 18);
  assert(encode_single_side_liquidity_protection_reset_request(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Liquidity Protection Reset Response: 13 bytes --------------- */

/* Response to Single Side Liquidity Protection Reset Request */
typedef struct {
  uint8_t client_message_id[4];  /* bytes 0 to 3 */
  uint8_t mpid[4];               /* bytes 4 to 7 */
  uint8_t reserved_4[4];         /* bytes 8 to 11 */
  uint8_t status;                /* byte 12 */
} SingleSideLiquidityProtectionResetResponse;

/* any Single Side Liquidity Protection Reset Response at all: every byte one the checker chooses */
static void any_single_side_liquidity_protection_reset_response(SingleSideLiquidityProtectionResetResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  record->status = arbitrary();
}

/* Single Side Liquidity Protection Reset Response to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_single_side_liquidity_protection_reset_response(const SingleSideLiquidityProtectionResetResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  wire[at++] = record->status;

  return at;
}

/* Single Side Liquidity Protection Reset Response off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_single_side_liquidity_protection_reset_response(SingleSideLiquidityProtectionResetResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  record->status = wire[at++];

  return at;
}

/* what was read of Single Side Liquidity Protection Reset Response is what was written, byte for byte */
static void equal_single_side_liquidity_protection_reset_response(const SingleSideLiquidityProtectionResetResponse *read, const SingleSideLiquidityProtectionResetResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  assert(read->status == written->status);
}

/* Single Side Liquidity Protection Reset Response: written and read back, then read and written back */
static void check_single_side_liquidity_protection_reset_response(void) {
  SingleSideLiquidityProtectionResetResponse sent;
  SingleSideLiquidityProtectionResetResponse got;
  uint8_t wire[13];
  uint8_t again[13];

  any_single_side_liquidity_protection_reset_response(&sent);
  assert(encode_single_side_liquidity_protection_reset_response(&sent, wire, 0) == 13);
  assert(decode_single_side_liquidity_protection_reset_response(&got, wire, 0) == 13);
  equal_single_side_liquidity_protection_reset_response(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_single_side_liquidity_protection_reset_response(&got, wire, 0) == 13);
  assert(encode_single_side_liquidity_protection_reset_response(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Liquidity Protection Trigger Notification: 24 bytes --------------------- */

/* This message format will be used to notify firms when order protection is triggered for an MPID */
typedef struct {
  uint8_t notification_time[8];   /* bytes 0 to 7 */
  uint8_t mpid[4];                /* bytes 8 to 11 */
  uint8_t underlying_symbol[11];  /* bytes 12 to 22 */
  uint8_t trigger_reason;         /* byte 23 */
} LiquidityProtectionTriggerNotification;

/* any Liquidity Protection Trigger Notification at all: every byte one the checker chooses */
static void any_liquidity_protection_trigger_notification(LiquidityProtectionTriggerNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->trigger_reason = arbitrary();
}

/* Liquidity Protection Trigger Notification to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_liquidity_protection_trigger_notification(const LiquidityProtectionTriggerNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->trigger_reason;

  return at;
}

/* Liquidity Protection Trigger Notification off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_liquidity_protection_trigger_notification(LiquidityProtectionTriggerNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->trigger_reason = wire[at++];

  return at;
}

/* what was read of Liquidity Protection Trigger Notification is what was written, byte for byte */
static void equal_liquidity_protection_trigger_notification(const LiquidityProtectionTriggerNotification *read, const LiquidityProtectionTriggerNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->trigger_reason == written->trigger_reason);
}

/* Liquidity Protection Trigger Notification: written and read back, then read and written back */
static void check_liquidity_protection_trigger_notification(void) {
  LiquidityProtectionTriggerNotification sent;
  LiquidityProtectionTriggerNotification got;
  uint8_t wire[24];
  uint8_t again[24];

  any_liquidity_protection_trigger_notification(&sent);
  assert(encode_liquidity_protection_trigger_notification(&sent, wire, 0) == 24);
  assert(decode_liquidity_protection_trigger_notification(&got, wire, 0) == 24);
  equal_liquidity_protection_trigger_notification(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_liquidity_protection_trigger_notification(&got, wire, 0) == 24);
  assert(encode_liquidity_protection_trigger_notification(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request: 35 bytes ------------------------------------------------- */

/* The SesM client uses this packet to allow the server to authenticate the client and to convey to the server the last sequenced packet that the client received */
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

/* The SesM server sends a Login response packet in response to a Login request packet from the client */
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
  check_series_update();
  check_complex_binary_order_response();
  check_system_state_notification();
  check_underlying_trading_status_notification();
  check_opening_width_relief_notification();
  check_arm_protection_settings_notification();
  check_arm2_underlying_level_protection_settings_notification();
  check_single_side_liquidity_protection_trigger_notification();
  check_arm2_underlying_level_protection_notification();
  check_arm2_firm_level_protection_notification();
  check_cancel_notification();
  check_execution_notification();
  check_stock_leg_execution_notification();
  check_arm_settings_update_request();
  check_arm_settings_update_response();
  check_arm2_underlying_level_protection_settings_update_request();
  check_arm2_underlying_level_protection_settings_update_response();
  check_series_assignment_request();
  check_series_assignment_response();
  check_complex_binary_order_request();
  check_liquidity_mass_cancel_response();
  check_liquidity_protection_reset_response();
  check_single_side_liquidity_protection_reset_request();
  check_single_side_liquidity_protection_reset_response();
  check_liquidity_protection_trigger_notification();
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
