// miax/miaxoptions/expressinterface/MiaxOptions_ExpressInterface_v1_3_c.c
/*
 * Miami International Holdings Express Interface
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

/* ---- Series Update: 76 bytes ------------------------------------------------- */

/* This is the message format that will be used to disseminate all Option series traded on MIAX for the current session on the cloud associated for this connection. */
typedef struct {
  uint8_t product_add_update_time[8];            /* bytes 0 to 7 */
  uint8_t product_id[4];                         /* bytes 8 to 11 */
  uint8_t underlying_symbol[11];                 /* bytes 12 to 22 */
  uint8_t security_symbol[6];                    /* bytes 23 to 28 */
  uint8_t expiration_date[8];                    /* bytes 29 to 36 */
  uint8_t strike_price[4];                       /* bytes 37 to 40 */
  uint8_t call_or_put;                           /* byte 41 */
  uint8_t opening_time[8];                       /* bytes 42 to 49 */
  uint8_t closing_time[8];                       /* bytes 50 to 57 */
  uint8_t restricted_option;                     /* byte 58 */
  uint8_t long_term_option;                      /* byte 59 */
  uint8_t active_on_miax;                        /* byte 60 */
  uint8_t miax_bbo_posting_increment_indicator;  /* byte 61 */
  uint8_t quote_acceptance_increment_indicator;  /* byte 62 */
  uint8_t opening_underlying_market_code;        /* byte 63 */
  uint8_t priority_quote_width[4];               /* bytes 64 to 67 */
  uint8_t reserved_8[8];                         /* bytes 68 to 75 */
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
  record->active_on_miax = arbitrary();
  record->miax_bbo_posting_increment_indicator = arbitrary();
  record->quote_acceptance_increment_indicator = arbitrary();
  record->opening_underlying_market_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->priority_quote_width[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
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
  wire[at++] = record->active_on_miax;
  wire[at++] = record->miax_bbo_posting_increment_indicator;
  wire[at++] = record->quote_acceptance_increment_indicator;
  wire[at++] = record->opening_underlying_market_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority_quote_width[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

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
  record->active_on_miax = wire[at++];
  record->miax_bbo_posting_increment_indicator = wire[at++];
  record->quote_acceptance_increment_indicator = wire[at++];
  record->opening_underlying_market_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->priority_quote_width[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

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
  assert(read->active_on_miax == written->active_on_miax);
  assert(read->miax_bbo_posting_increment_indicator == written->miax_bbo_posting_increment_indicator);
  assert(read->quote_acceptance_increment_indicator == written->quote_acceptance_increment_indicator);
  assert(read->opening_underlying_market_code == written->opening_underlying_market_code);
  for (size_t i = 0; i < 4; i++) { assert(read->priority_quote_width[i] == written->priority_quote_width[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
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

/* ---- Valid Quote Width For Opening: 21 bytes --------------------------------- */

/* This message format will be used to convey to the firms the Valid Quote Width settings applicable to the Opening process of MIAX Options market. Each message describes a row of the Valid Quote Width table with a low end of the applicable price range and corresponding maximum quote width. The high end of the applicable price range is up to, but not including the next row's low end applicable price range if provided or infinity for the last row. If the table has to be reloaded, all rows will be resent. Refer to Appendix C for an example. */
typedef struct {
  uint8_t notification_time[8];            /* bytes 0 to 7 */
  uint8_t mpv_class;                       /* byte 8 */
  uint8_t low_end_of_applicable_range[4];  /* bytes 9 to 12 */
  uint8_t maximum_quote_width[4];          /* bytes 13 to 16 */
  uint8_t long_term_option_multiplier[4];  /* bytes 17 to 20 */
} ValidQuoteWidthForOpening;

/* any Valid Quote Width For Opening at all: every byte one the checker chooses */
static void any_valid_quote_width_for_opening(ValidQuoteWidthForOpening *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  record->mpv_class = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->low_end_of_applicable_range[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maximum_quote_width[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->long_term_option_multiplier[i] = arbitrary(); }
}

/* Valid Quote Width For Opening to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_valid_quote_width_for_opening(const ValidQuoteWidthForOpening *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  wire[at++] = record->mpv_class;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low_end_of_applicable_range[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maximum_quote_width[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->long_term_option_multiplier[i]; }

  return at;
}

/* Valid Quote Width For Opening off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_valid_quote_width_for_opening(ValidQuoteWidthForOpening *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  record->mpv_class = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->low_end_of_applicable_range[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maximum_quote_width[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->long_term_option_multiplier[i] = wire[at++]; }

  return at;
}

/* what was read of Valid Quote Width For Opening is what was written, byte for byte */
static void equal_valid_quote_width_for_opening(const ValidQuoteWidthForOpening *read, const ValidQuoteWidthForOpening *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  assert(read->mpv_class == written->mpv_class);
  for (size_t i = 0; i < 4; i++) { assert(read->low_end_of_applicable_range[i] == written->low_end_of_applicable_range[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maximum_quote_width[i] == written->maximum_quote_width[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->long_term_option_multiplier[i] == written->long_term_option_multiplier[i]); }
}

/* Valid Quote Width For Opening: written and read back, then read and written back */
static void check_valid_quote_width_for_opening(void) {
  ValidQuoteWidthForOpening sent;
  ValidQuoteWidthForOpening got;
  uint8_t wire[21];
  uint8_t again[21];

  any_valid_quote_width_for_opening(&sent);
  assert(encode_valid_quote_width_for_opening(&sent, wire, 0) == 21);
  assert(decode_valid_quote_width_for_opening(&got, wire, 0) == 21);
  equal_valid_quote_width_for_opening(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_valid_quote_width_for_opening(&got, wire, 0) == 21);
  assert(encode_valid_quote_width_for_opening(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Enhanced Quote E Quote Response: 17 bytes ------------------------------- */

/* This message indicates if the eQuote was accepted or rejected. Note that this message does not report executions. For executions, please refer to the Execution notification. For the unexecuted part that gets canceled, please refer to the Cancel notification. */
typedef struct {
  uint8_t client_message_id[4];    /* bytes 0 to 3 */
  uint8_t mpid[4];                 /* bytes 4 to 7 */
  uint8_t e_quote_id[8];           /* bytes 8 to 15 */
  uint8_t e_quote_request_status;  /* byte 16 */
} EnhancedQuoteEQuoteResponse;

/* any Enhanced Quote E Quote Response at all: every byte one the checker chooses */
static void any_enhanced_quote_e_quote_response(EnhancedQuoteEQuoteResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->e_quote_id[i] = arbitrary(); }
  record->e_quote_request_status = arbitrary();
}

/* Enhanced Quote E Quote Response to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_enhanced_quote_e_quote_response(const EnhancedQuoteEQuoteResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->e_quote_id[i]; }
  wire[at++] = record->e_quote_request_status;

  return at;
}

/* Enhanced Quote E Quote Response off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_enhanced_quote_e_quote_response(EnhancedQuoteEQuoteResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->e_quote_id[i] = wire[at++]; }
  record->e_quote_request_status = wire[at++];

  return at;
}

/* what was read of Enhanced Quote E Quote Response is what was written, byte for byte */
static void equal_enhanced_quote_e_quote_response(const EnhancedQuoteEQuoteResponse *read, const EnhancedQuoteEQuoteResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->e_quote_id[i] == written->e_quote_id[i]); }
  assert(read->e_quote_request_status == written->e_quote_request_status);
}

/* Enhanced Quote E Quote Response: written and read back, then read and written back */
static void check_enhanced_quote_e_quote_response(void) {
  EnhancedQuoteEQuoteResponse sent;
  EnhancedQuoteEQuoteResponse got;
  uint8_t wire[17];
  uint8_t again[17];

  any_enhanced_quote_e_quote_response(&sent);
  assert(encode_enhanced_quote_e_quote_response(&sent, wire, 0) == 17);
  assert(decode_enhanced_quote_e_quote_response(&got, wire, 0) == 17);
  equal_enhanced_quote_e_quote_response(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_enhanced_quote_e_quote_response(&got, wire, 0) == 17);
  assert(encode_enhanced_quote_e_quote_response(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- System State Notification: 18 bytes ------------------------------------- */

/* This message format is used to notify the firms of the state changes of the system. This is an exchange-wide notification and not a symbol or member based notification. */
typedef struct {
  uint8_t notification_time[8];  /* bytes 0 to 7 */
  uint8_t mei_version[8];        /* bytes 8 to 15 */
  uint8_t session_id;            /* byte 16 */
  uint8_t system_status;         /* byte 17 */
} SystemStateNotification;

/* any System State Notification at all: every byte one the checker chooses */
static void any_system_state_notification(SystemStateNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mei_version[i] = arbitrary(); }
  record->session_id = arbitrary();
  record->system_status = arbitrary();
}

/* System State Notification to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_system_state_notification(const SystemStateNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mei_version[i]; }
  wire[at++] = record->session_id;
  wire[at++] = record->system_status;

  return at;
}

/* System State Notification off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_system_state_notification(SystemStateNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mei_version[i] = wire[at++]; }
  record->session_id = wire[at++];
  record->system_status = wire[at++];

  return at;
}

/* what was read of System State Notification is what was written, byte for byte */
static void equal_system_state_notification(const SystemStateNotification *read, const SystemStateNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mei_version[i] == written->mei_version[i]); }
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

/* ---- Trading Status Notification: 21 bytes ----------------------------------- */

/* This message format will be used to notify the firms of changes to the trading status of an option or trigger of market-wide circuit breakers on the MIAX Options market. */
typedef struct {
  uint8_t notification_time[8];    /* bytes 0 to 7 */
  uint8_t product_id[4];           /* bytes 8 to 11 */
  uint8_t trading_status;          /* byte 12 */
  uint8_t expected_event_time[8];  /* bytes 13 to 20 */
} TradingStatusNotification;

/* any Trading Status Notification at all: every byte one the checker chooses */
static void any_trading_status_notification(TradingStatusNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->expected_event_time[i] = arbitrary(); }
}

/* Trading Status Notification to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_notification(const TradingStatusNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expected_event_time[i]; }

  return at;
}

/* Trading Status Notification off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_notification(TradingStatusNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->expected_event_time[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Status Notification is what was written, byte for byte */
static void equal_trading_status_notification(const TradingStatusNotification *read, const TradingStatusNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 8; i++) { assert(read->expected_event_time[i] == written->expected_event_time[i]); }
}

/* Trading Status Notification: written and read back, then read and written back */
static void check_trading_status_notification(void) {
  TradingStatusNotification sent;
  TradingStatusNotification got;
  uint8_t wire[21];
  uint8_t again[21];

  any_trading_status_notification(&sent);
  assert(encode_trading_status_notification(&sent, wire, 0) == 21);
  assert(decode_trading_status_notification(&got, wire, 0) == 21);
  equal_trading_status_notification(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_notification(&got, wire, 0) == 21);
  assert(encode_trading_status_notification(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Width Relief Notification: 23 bytes ------------------------------- */

/* This message format will be used to notify the firms if and when MIAX grants relief to the valid quote width parameters for Opening as specified in the rules and regulatory circulars of MIAX Options market. */
typedef struct {
  uint8_t notification_time[8];   /* bytes 0 to 7 */
  uint8_t underlying_symbol[11];  /* bytes 8 to 18 */
  uint8_t relief_multiplier[4];   /* bytes 19 to 22 */
} QuoteWidthReliefNotification;

/* any Quote Width Relief Notification at all: every byte one the checker chooses */
static void any_quote_width_relief_notification(QuoteWidthReliefNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->relief_multiplier[i] = arbitrary(); }
}

/* Quote Width Relief Notification to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_quote_width_relief_notification(const QuoteWidthReliefNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->relief_multiplier[i]; }

  return at;
}

/* Quote Width Relief Notification off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_quote_width_relief_notification(QuoteWidthReliefNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->relief_multiplier[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Width Relief Notification is what was written, byte for byte */
static void equal_quote_width_relief_notification(const QuoteWidthReliefNotification *read, const QuoteWidthReliefNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->relief_multiplier[i] == written->relief_multiplier[i]); }
}

/* Quote Width Relief Notification: written and read back, then read and written back */
static void check_quote_width_relief_notification(void) {
  QuoteWidthReliefNotification sent;
  QuoteWidthReliefNotification got;
  uint8_t wire[23];
  uint8_t again[23];

  any_quote_width_relief_notification(&sent);
  assert(encode_quote_width_relief_notification(&sent, wire, 0) == 23);
  assert(decode_quote_width_relief_notification(&got, wire, 0) == 23);
  equal_quote_width_relief_notification(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_width_relief_notification(&got, wire, 0) == 23);
  assert(encode_quote_width_relief_notification(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Arm Protection Settings Notification: 31 bytes -------------------------- */

/* This message format will be used to notify firms of their ARM settings. All the ARM settings will be published upon system initialization and each subsequent change will also be published. */
typedef struct {
  uint8_t notification_time[8];                /* bytes 0 to 7 */
  uint8_t mpid[4];                             /* bytes 8 to 11 */
  uint8_t underlying_symbol[11];               /* bytes 12 to 22 */
  uint8_t allowable_engagement_percentage[4];  /* bytes 23 to 26 */
  uint8_t counting_period[2];                  /* bytes 27 to 28 */
  uint8_t action;                              /* byte 29 */
  uint8_t source;                              /* byte 30 */
} ArmProtectionSettingsNotification;

/* any Arm Protection Settings Notification at all: every byte one the checker chooses */
static void any_arm_protection_settings_notification(ArmProtectionSettingsNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->allowable_engagement_percentage[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counting_period[i] = arbitrary(); }
  record->action = arbitrary();
  record->source = arbitrary();
}

/* Arm Protection Settings Notification to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_arm_protection_settings_notification(const ArmProtectionSettingsNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->allowable_engagement_percentage[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counting_period[i]; }
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
  for (size_t i = 0; i < 2; i++) { record->counting_period[i] = wire[at++]; }
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
  for (size_t i = 0; i < 2; i++) { assert(read->counting_period[i] == written->counting_period[i]); }
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

/* ---- Cancel Notification: 36 bytes ------------------------------------------- */

/* This is the message format that will be used to notify firms about system generated or firm requested quote and eQuote cancels. */
typedef struct {
  uint8_t notification_time[8];       /* bytes 0 to 7 */
  uint8_t mpid[4];                    /* bytes 8 to 11 */
  uint8_t product_id[4];              /* bytes 12 to 15 */
  uint8_t liquidity_type;             /* byte 16 */
  uint8_t client_message_id[4];       /* bytes 17 to 20 */
  uint8_t bulk_quote_index;           /* byte 21 */
  uint8_t quotee_quote_side;          /* byte 22 */
  uint8_t size[4];                    /* bytes 23 to 26 */
  uint8_t engine_sequence_number[8];  /* bytes 27 to 34 */
  uint8_t cancel_reason;              /* byte 35 */
} CancelNotification;

/* any Cancel Notification at all: every byte one the checker chooses */
static void any_cancel_notification(CancelNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  record->liquidity_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  record->bulk_quote_index = arbitrary();
  record->quotee_quote_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->engine_sequence_number[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
}

/* Cancel Notification to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_cancel_notification(const CancelNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  wire[at++] = record->liquidity_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  wire[at++] = record->bulk_quote_index;
  wire[at++] = record->quotee_quote_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->engine_sequence_number[i]; }
  wire[at++] = record->cancel_reason;

  return at;
}

/* Cancel Notification off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_cancel_notification(CancelNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  record->liquidity_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  record->bulk_quote_index = wire[at++];
  record->quotee_quote_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->engine_sequence_number[i] = wire[at++]; }
  record->cancel_reason = wire[at++];

  return at;
}

/* what was read of Cancel Notification is what was written, byte for byte */
static void equal_cancel_notification(const CancelNotification *read, const CancelNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  assert(read->liquidity_type == written->liquidity_type);
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  assert(read->bulk_quote_index == written->bulk_quote_index);
  assert(read->quotee_quote_side == written->quotee_quote_side);
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->engine_sequence_number[i] == written->engine_sequence_number[i]); }
  assert(read->cancel_reason == written->cancel_reason);
}

/* Cancel Notification: written and read back, then read and written back */
static void check_cancel_notification(void) {
  CancelNotification sent;
  CancelNotification got;
  uint8_t wire[36];
  uint8_t again[36];

  any_cancel_notification(&sent);
  assert(encode_cancel_notification(&sent, wire, 0) == 36);
  assert(decode_cancel_notification(&got, wire, 0) == 36);
  equal_cancel_notification(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_notification(&got, wire, 0) == 36);
  assert(encode_cancel_notification(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Notification: 49 bytes ---------------------------------------- */

/* This message format will be used to notify the firms of executions of their quotes and eQuotes. */
typedef struct {
  uint8_t notification_time[8];  /* bytes 0 to 7 */
  uint8_t mpid[4];               /* bytes 8 to 11 */
  uint8_t product_id[4];         /* bytes 12 to 15 */
  uint8_t liquidity_type;        /* byte 16 */
  uint8_t client_message_id[4];  /* bytes 17 to 20 */
  uint8_t bulk_quote_index;      /* byte 21 */
  uint8_t event_id[4];           /* bytes 22 to 25 */
  uint8_t trade_id[4];           /* bytes 26 to 29 */
  uint8_t execution_id[8];       /* bytes 30 to 37 */
  uint8_t reserved_1;            /* byte 38 */
  uint8_t trade_status;          /* byte 39 */
  uint8_t last_price[4];         /* bytes 40 to 43 */
  uint8_t side;                  /* byte 44 */
  uint8_t last_size[4];          /* bytes 45 to 48 */
} ExecutionNotification;

/* any Execution Notification at all: every byte one the checker chooses */
static void any_execution_notification(ExecutionNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  record->liquidity_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  record->bulk_quote_index = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->trade_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_size[i] = arbitrary(); }
}

/* Execution Notification to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_execution_notification(const ExecutionNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  wire[at++] = record->liquidity_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  wire[at++] = record->bulk_quote_index;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->trade_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_price[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_size[i]; }

  return at;
}

/* Execution Notification off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_execution_notification(ExecutionNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  record->liquidity_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  record->bulk_quote_index = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->trade_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_size[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Notification is what was written, byte for byte */
static void equal_execution_notification(const ExecutionNotification *read, const ExecutionNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  assert(read->liquidity_type == written->liquidity_type);
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  assert(read->bulk_quote_index == written->bulk_quote_index);
  for (size_t i = 0; i < 4; i++) { assert(read->event_id[i] == written->event_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->reserved_1 == written->reserved_1);
  assert(read->trade_status == written->trade_status);
  for (size_t i = 0; i < 4; i++) { assert(read->last_price[i] == written->last_price[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->last_size[i] == written->last_size[i]); }
}

/* Execution Notification: written and read back, then read and written back */
static void check_execution_notification(void) {
  ExecutionNotification sent;
  ExecutionNotification got;
  uint8_t wire[49];
  uint8_t again[49];

  any_execution_notification(&sent);
  assert(encode_execution_notification(&sent, wire, 0) == 49);
  assert(decode_execution_notification(&got, wire, 0) == 49);
  equal_execution_notification(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_notification(&got, wire, 0) == 49);
  assert(encode_execution_notification(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- Arm Settings Update Request: 26 bytes ----------------------------------- */

/* Firms can use this message format to set up their ARM protection settings for each session. Changes to these settings can be made throughout the day. */
typedef struct {
  uint8_t client_message_id[4];                /* bytes 0 to 3 */
  uint8_t mpid[4];                             /* bytes 4 to 7 */
  uint8_t action;                              /* byte 8 */
  uint8_t underlying_symbol[11];               /* bytes 9 to 19 */
  uint8_t allowable_engagement_percentage[4];  /* bytes 20 to 23 */
  uint8_t counting_period[2];                  /* bytes 24 to 25 */
} ArmSettingsUpdateRequest;

/* any Arm Settings Update Request at all: every byte one the checker chooses */
static void any_arm_settings_update_request(ArmSettingsUpdateRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->action = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->allowable_engagement_percentage[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counting_period[i] = arbitrary(); }
}

/* Arm Settings Update Request to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_arm_settings_update_request(const ArmSettingsUpdateRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->action;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->allowable_engagement_percentage[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counting_period[i]; }

  return at;
}

/* Arm Settings Update Request off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_arm_settings_update_request(ArmSettingsUpdateRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->action = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->allowable_engagement_percentage[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counting_period[i] = wire[at++]; }

  return at;
}

/* what was read of Arm Settings Update Request is what was written, byte for byte */
static void equal_arm_settings_update_request(const ArmSettingsUpdateRequest *read, const ArmSettingsUpdateRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->action == written->action);
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->allowable_engagement_percentage[i] == written->allowable_engagement_percentage[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counting_period[i] == written->counting_period[i]); }
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

/* MIAX uses this format to respond to the firm with a status of their ARM protection settings request. */
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

/* ---- Enhanced Quote E Quote Message: 31 bytes -------------------------------- */

/* This is the format for an eQuote message that can be sent either to match with orders and quotes on the MIAX book or when responding to a liquidity seeking event. */
typedef struct {
  uint8_t client_message_id[4];  /* bytes 0 to 3 */
  uint8_t mpid[4];               /* bytes 4 to 7 */
  uint8_t product_id[4];         /* bytes 8 to 11 */
  uint8_t e_quote_action;        /* byte 12 */
  uint8_t e_quote_type;          /* byte 13 */
  uint8_t event_id[4];           /* bytes 14 to 17 */
  uint8_t target_message_id[4];  /* bytes 18 to 21 */
  uint8_t price[4];              /* bytes 22 to 25 */
  uint8_t size[4];               /* bytes 26 to 29 */
  uint8_t side;                  /* byte 30 */
} EnhancedQuoteEQuoteMessage;

/* any Enhanced Quote E Quote Message at all: every byte one the checker chooses */
static void any_enhanced_quote_e_quote_message(EnhancedQuoteEQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  record->e_quote_action = arbitrary();
  record->e_quote_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->target_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  record->side = arbitrary();
}

/* Enhanced Quote E Quote Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_enhanced_quote_e_quote_message(const EnhancedQuoteEQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  wire[at++] = record->e_quote_action;
  wire[at++] = record->e_quote_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->target_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  wire[at++] = record->side;

  return at;
}

/* Enhanced Quote E Quote Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_enhanced_quote_e_quote_message(EnhancedQuoteEQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  record->e_quote_action = wire[at++];
  record->e_quote_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->target_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  record->side = wire[at++];

  return at;
}

/* what was read of Enhanced Quote E Quote Message is what was written, byte for byte */
static void equal_enhanced_quote_e_quote_message(const EnhancedQuoteEQuoteMessage *read, const EnhancedQuoteEQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  assert(read->e_quote_action == written->e_quote_action);
  assert(read->e_quote_type == written->e_quote_type);
  for (size_t i = 0; i < 4; i++) { assert(read->event_id[i] == written->event_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->target_message_id[i] == written->target_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  assert(read->side == written->side);
}

/* Enhanced Quote E Quote Message: written and read back, then read and written back */
static void check_enhanced_quote_e_quote_message(void) {
  EnhancedQuoteEQuoteMessage sent;
  EnhancedQuoteEQuoteMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_enhanced_quote_e_quote_message(&sent);
  assert(encode_enhanced_quote_e_quote_message(&sent, wire, 0) == 31);
  assert(decode_enhanced_quote_e_quote_message(&got, wire, 0) == 31);
  equal_enhanced_quote_e_quote_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_enhanced_quote_e_quote_message(&got, wire, 0) == 31);
  assert(encode_enhanced_quote_e_quote_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Quote Cancel Request: 19 bytes ------------------------------------- */

/* Firms can use this message format to request the cancelation of all quotes and eQuotes for an MPID, or all quotes and eQuotes for an MPID for all series for an underlying */
typedef struct {
  uint8_t client_message_id[4];   /* bytes 0 to 3 */
  uint8_t mpid[4];                /* bytes 4 to 7 */
  uint8_t underlying_symbol[11];  /* bytes 8 to 18 */
} MassQuoteCancelRequest;

/* any Mass Quote Cancel Request at all: every byte one the checker chooses */
static void any_mass_quote_cancel_request(MassQuoteCancelRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
}

/* Mass Quote Cancel Request to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_mass_quote_cancel_request(const MassQuoteCancelRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }

  return at;
}

/* Mass Quote Cancel Request off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_mass_quote_cancel_request(MassQuoteCancelRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Quote Cancel Request is what was written, byte for byte */
static void equal_mass_quote_cancel_request(const MassQuoteCancelRequest *read, const MassQuoteCancelRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
}

/* Mass Quote Cancel Request: written and read back, then read and written back */
static void check_mass_quote_cancel_request(void) {
  MassQuoteCancelRequest sent;
  MassQuoteCancelRequest got;
  uint8_t wire[19];
  uint8_t again[19];

  any_mass_quote_cancel_request(&sent);
  assert(encode_mass_quote_cancel_request(&sent, wire, 0) == 19);
  assert(decode_mass_quote_cancel_request(&got, wire, 0) == 19);
  equal_mass_quote_cancel_request(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_quote_cancel_request(&got, wire, 0) == 19);
  assert(encode_mass_quote_cancel_request(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Quote Cancel Response: 9 bytes ------------------------------------- */

/* This message format will be used to inform the firm about the status of their previous mass quote cancel request. */
typedef struct {
  uint8_t client_message_id[4];      /* bytes 0 to 3 */
  uint8_t mpid[4];                   /* bytes 4 to 7 */
  uint8_t mass_quote_cancel_status;  /* byte 8 */
} MassQuoteCancelResponse;

/* any Mass Quote Cancel Response at all: every byte one the checker chooses */
static void any_mass_quote_cancel_response(MassQuoteCancelResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->mass_quote_cancel_status = arbitrary();
}

/* Mass Quote Cancel Response to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_mass_quote_cancel_response(const MassQuoteCancelResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->mass_quote_cancel_status;

  return at;
}

/* Mass Quote Cancel Response off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_mass_quote_cancel_response(MassQuoteCancelResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->mass_quote_cancel_status = wire[at++];

  return at;
}

/* what was read of Mass Quote Cancel Response is what was written, byte for byte */
static void equal_mass_quote_cancel_response(const MassQuoteCancelResponse *read, const MassQuoteCancelResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->mass_quote_cancel_status == written->mass_quote_cancel_status);
}

/* Mass Quote Cancel Response: written and read back, then read and written back */
static void check_mass_quote_cancel_response(void) {
  MassQuoteCancelResponse sent;
  MassQuoteCancelResponse got;
  uint8_t wire[9];
  uint8_t again[9];

  any_mass_quote_cancel_response(&sent);
  assert(encode_mass_quote_cancel_response(&sent, wire, 0) == 9);
  assert(decode_mass_quote_cancel_response(&got, wire, 0) == 9);
  equal_mass_quote_cancel_response(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_quote_cancel_response(&got, wire, 0) == 9);
  assert(encode_mass_quote_cancel_response(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Protection Reset Request: 19 bytes -------------------------------- */

/* Following a quote protection being engaged for a given MPID and underlying, firms must use this message format to reset their Quote Protection in order to start quoting for any option of the specified underlying. */
typedef struct {
  uint8_t client_message_id[4];   /* bytes 0 to 3 */
  uint8_t mpid[4];                /* bytes 4 to 7 */
  uint8_t underlying_symbol[11];  /* bytes 8 to 18 */
} QuoteProtectionResetRequest;

/* any Quote Protection Reset Request at all: every byte one the checker chooses */
static void any_quote_protection_reset_request(QuoteProtectionResetRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
}

/* Quote Protection Reset Request to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_quote_protection_reset_request(const QuoteProtectionResetRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }

  return at;
}

/* Quote Protection Reset Request off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_quote_protection_reset_request(QuoteProtectionResetRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Protection Reset Request is what was written, byte for byte */
static void equal_quote_protection_reset_request(const QuoteProtectionResetRequest *read, const QuoteProtectionResetRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
}

/* Quote Protection Reset Request: written and read back, then read and written back */
static void check_quote_protection_reset_request(void) {
  QuoteProtectionResetRequest sent;
  QuoteProtectionResetRequest got;
  uint8_t wire[19];
  uint8_t again[19];

  any_quote_protection_reset_request(&sent);
  assert(encode_quote_protection_reset_request(&sent, wire, 0) == 19);
  assert(decode_quote_protection_reset_request(&got, wire, 0) == 19);
  equal_quote_protection_reset_request(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_protection_reset_request(&got, wire, 0) == 19);
  assert(encode_quote_protection_reset_request(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Protection Reset Response: 9 bytes -------------------------------- */

/* This message format is used to inform the firms of the status of their Quote Protection Reset request. */
typedef struct {
  uint8_t client_message_id[4];           /* bytes 0 to 3 */
  uint8_t mpid[4];                        /* bytes 4 to 7 */
  uint8_t quote_protection_reset_status;  /* byte 8 */
} QuoteProtectionResetResponse;

/* any Quote Protection Reset Response at all: every byte one the checker chooses */
static void any_quote_protection_reset_response(QuoteProtectionResetResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->quote_protection_reset_status = arbitrary();
}

/* Quote Protection Reset Response to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_quote_protection_reset_response(const QuoteProtectionResetResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->quote_protection_reset_status;

  return at;
}

/* Quote Protection Reset Response off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_quote_protection_reset_response(QuoteProtectionResetResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->quote_protection_reset_status = wire[at++];

  return at;
}

/* what was read of Quote Protection Reset Response is what was written, byte for byte */
static void equal_quote_protection_reset_response(const QuoteProtectionResetResponse *read, const QuoteProtectionResetResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->quote_protection_reset_status == written->quote_protection_reset_status);
}

/* Quote Protection Reset Response: written and read back, then read and written back */
static void check_quote_protection_reset_response(void) {
  QuoteProtectionResetResponse sent;
  QuoteProtectionResetResponse got;
  uint8_t wire[9];
  uint8_t again[9];

  any_quote_protection_reset_response(&sent);
  assert(encode_quote_protection_reset_response(&sent, wire, 0) == 9);
  assert(decode_quote_protection_reset_response(&got, wire, 0) == 9);
  equal_quote_protection_reset_response(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_protection_reset_response(&got, wire, 0) == 9);
  assert(encode_quote_protection_reset_response(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Protection Trigger Notification: 24 bytes ------------------------- */

/* This message format will be used to notify firms when an MPID is placed under quote protection. Quote protection can be triggered due to any one of the reasons listed in the message below. */
typedef struct {
  uint8_t notification_time[8];   /* bytes 0 to 7 */
  uint8_t mpid[4];                /* bytes 8 to 11 */
  uint8_t underlying_symbol[11];  /* bytes 12 to 22 */
  uint8_t trigger_reason;         /* byte 23 */
} QuoteProtectionTriggerNotification;

/* any Quote Protection Trigger Notification at all: every byte one the checker chooses */
static void any_quote_protection_trigger_notification(QuoteProtectionTriggerNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->trigger_reason = arbitrary();
}

/* Quote Protection Trigger Notification to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_quote_protection_trigger_notification(const QuoteProtectionTriggerNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->trigger_reason;

  return at;
}

/* Quote Protection Trigger Notification off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_quote_protection_trigger_notification(QuoteProtectionTriggerNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->trigger_reason = wire[at++];

  return at;
}

/* what was read of Quote Protection Trigger Notification is what was written, byte for byte */
static void equal_quote_protection_trigger_notification(const QuoteProtectionTriggerNotification *read, const QuoteProtectionTriggerNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->trigger_reason == written->trigger_reason);
}

/* Quote Protection Trigger Notification: written and read back, then read and written back */
static void check_quote_protection_trigger_notification(void) {
  QuoteProtectionTriggerNotification sent;
  QuoteProtectionTriggerNotification got;
  uint8_t wire[24];
  uint8_t again[24];

  any_quote_protection_trigger_notification(&sent);
  assert(encode_quote_protection_trigger_notification(&sent, wire, 0) == 24);
  assert(decode_quote_protection_trigger_notification(&got, wire, 0) == 24);
  equal_quote_protection_trigger_notification(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_protection_trigger_notification(&got, wire, 0) == 24);
  assert(encode_quote_protection_trigger_notification(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Liquidity Seeking Event Notification: 50 bytes -------------------------- */

/* This message format will be used to notify firms of opening imbalances and auction initiation. */
typedef struct {
  uint8_t notification_time[8];  /* bytes 0 to 7 */
  uint8_t product_id[4];         /* bytes 8 to 11 */
  uint8_t event_type;            /* byte 12 */
  uint8_t event_id[4];           /* bytes 13 to 16 */
  uint8_t price[4];              /* bytes 17 to 20 */
  uint8_t imbalance_side;        /* byte 21 */
  uint8_t quantity_1[4];         /* bytes 22 to 25 */
  uint8_t quantity_2[4];         /* bytes 26 to 29 */
  uint8_t quantity_3[4];         /* bytes 30 to 33 */
  uint8_t quantity_4[4];         /* bytes 34 to 37 */
  uint8_t reserved_12[12];       /* bytes 38 to 49 */
} LiquiditySeekingEventNotification;

/* any Liquidity Seeking Event Notification at all: every byte one the checker chooses */
static void any_liquidity_seeking_event_notification(LiquiditySeekingEventNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
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

/* Liquidity Seeking Event Notification to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_liquidity_seeking_event_notification(const LiquiditySeekingEventNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
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

/* Liquidity Seeking Event Notification off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_liquidity_seeking_event_notification(LiquiditySeekingEventNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
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

/* what was read of Liquidity Seeking Event Notification is what was written, byte for byte */
static void equal_liquidity_seeking_event_notification(const LiquiditySeekingEventNotification *read, const LiquiditySeekingEventNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
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

/* Liquidity Seeking Event Notification: written and read back, then read and written back */
static void check_liquidity_seeking_event_notification(void) {
  LiquiditySeekingEventNotification sent;
  LiquiditySeekingEventNotification got;
  uint8_t wire[50];
  uint8_t again[50];

  any_liquidity_seeking_event_notification(&sent);
  assert(encode_liquidity_seeking_event_notification(&sent, wire, 0) == 50);
  assert(decode_liquidity_seeking_event_notification(&got, wire, 0) == 50);
  equal_liquidity_seeking_event_notification(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_liquidity_seeking_event_notification(&got, wire, 0) == 50);
  assert(encode_liquidity_seeking_event_notification(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
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
  check_valid_quote_width_for_opening();
  check_enhanced_quote_e_quote_response();
  check_system_state_notification();
  check_trading_status_notification();
  check_quote_width_relief_notification();
  check_arm_protection_settings_notification();
  check_cancel_notification();
  check_execution_notification();
  check_arm_settings_update_request();
  check_arm_settings_update_response();
  check_enhanced_quote_e_quote_message();
  check_mass_quote_cancel_request();
  check_mass_quote_cancel_response();
  check_quote_protection_reset_request();
  check_quote_protection_reset_response();
  check_quote_protection_trigger_notification();
  check_liquidity_seeking_event_notification();
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
