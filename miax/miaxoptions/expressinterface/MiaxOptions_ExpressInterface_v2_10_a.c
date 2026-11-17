// miax/miaxoptions/expressinterface/MiaxOptions_ExpressInterface_v2_10_a.c
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

/* ---- Simple Series Update: 76 bytes ------------------------------------------ */

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
} SimpleSeriesUpdate;

/* any Simple Series Update at all: every byte one the checker chooses */
static void any_simple_series_update(SimpleSeriesUpdate *record) {
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

/* Simple Series Update to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_simple_series_update(const SimpleSeriesUpdate *record, uint8_t *wire, size_t at) {
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

/* Simple Series Update off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_simple_series_update(SimpleSeriesUpdate *record, const uint8_t *wire, size_t at) {
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

/* what was read of Simple Series Update is what was written, byte for byte */
static void equal_simple_series_update(const SimpleSeriesUpdate *read, const SimpleSeriesUpdate *written) {
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

/* Simple Series Update: written and read back, then read and written back */
static void check_simple_series_update(void) {
  SimpleSeriesUpdate sent;
  SimpleSeriesUpdate got;
  uint8_t wire[76];
  uint8_t again[76];

  any_simple_series_update(&sent);
  assert(encode_simple_series_update(&sent, wire, 0) == 76);
  assert(decode_simple_series_update(&got, wire, 0) == 76);
  equal_simple_series_update(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_series_update(&got, wire, 0) == 76);
  assert(encode_simple_series_update(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Valid Quote Width For Opening: 21 bytes --------------------------------- */

/* This message format will be used to convey to the firms the Valid Quote Width settings applicable to the Opening process of MIAX Options market. Each message describes a row of the Valid Quote Width table with a low end of the applicable price range and corresponding maximum quote width. The high end of the applicable price range is up to, but not including the next row’s low end applicable price range if provided or infinity for the last row. If the table has to be reloaded, all rows will be resent. Refer to Appendix C for an example. */
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

/* ---- Simple Enhanced Quote E Quote Response: 17 bytes ------------------------ */

/* This message indicates if the eQuote was accepted or rejected. Note that this message does not report executions. For executions, please refer to the Execution notification. For the unexecuted part that gets canceled, please refer to the Cancel notification. */
typedef struct {
  uint8_t client_message_id[4];    /* bytes 0 to 3 */
  uint8_t mpid[4];                 /* bytes 4 to 7 */
  uint8_t e_quote_id[8];           /* bytes 8 to 15 */
  uint8_t e_quote_request_status;  /* byte 16 */
} SimpleEnhancedQuoteEQuoteResponse;

/* any Simple Enhanced Quote E Quote Response at all: every byte one the checker chooses */
static void any_simple_enhanced_quote_e_quote_response(SimpleEnhancedQuoteEQuoteResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->e_quote_id[i] = arbitrary(); }
  record->e_quote_request_status = arbitrary();
}

/* Simple Enhanced Quote E Quote Response to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_simple_enhanced_quote_e_quote_response(const SimpleEnhancedQuoteEQuoteResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->e_quote_id[i]; }
  wire[at++] = record->e_quote_request_status;

  return at;
}

/* Simple Enhanced Quote E Quote Response off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_simple_enhanced_quote_e_quote_response(SimpleEnhancedQuoteEQuoteResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->e_quote_id[i] = wire[at++]; }
  record->e_quote_request_status = wire[at++];

  return at;
}

/* what was read of Simple Enhanced Quote E Quote Response is what was written, byte for byte */
static void equal_simple_enhanced_quote_e_quote_response(const SimpleEnhancedQuoteEQuoteResponse *read, const SimpleEnhancedQuoteEQuoteResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->e_quote_id[i] == written->e_quote_id[i]); }
  assert(read->e_quote_request_status == written->e_quote_request_status);
}

/* Simple Enhanced Quote E Quote Response: written and read back, then read and written back */
static void check_simple_enhanced_quote_e_quote_response(void) {
  SimpleEnhancedQuoteEQuoteResponse sent;
  SimpleEnhancedQuoteEQuoteResponse got;
  uint8_t wire[17];
  uint8_t again[17];

  any_simple_enhanced_quote_e_quote_response(&sent);
  assert(encode_simple_enhanced_quote_e_quote_response(&sent, wire, 0) == 17);
  assert(decode_simple_enhanced_quote_e_quote_response(&got, wire, 0) == 17);
  equal_simple_enhanced_quote_e_quote_response(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_enhanced_quote_e_quote_response(&got, wire, 0) == 17);
  assert(encode_simple_enhanced_quote_e_quote_response(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Enhanced Quote E Quote Response: 17 bytes ----------------------- */

/* This message indicates if the complex eQuote was accepted or rejected. Note that this message does not report executions. For executions, please refer to the Execution notification. For the handling of any unexecuted portion that was canceled, please refer to the Cancel notification. */
typedef struct {
  uint8_t client_message_id[4];    /* bytes 0 to 3 */
  uint8_t mpid[4];                 /* bytes 4 to 7 */
  uint8_t e_quote_id[8];           /* bytes 8 to 15 */
  uint8_t e_quote_request_status;  /* byte 16 */
} ComplexEnhancedQuoteEQuoteResponse;

/* any Complex Enhanced Quote E Quote Response at all: every byte one the checker chooses */
static void any_complex_enhanced_quote_e_quote_response(ComplexEnhancedQuoteEQuoteResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->e_quote_id[i] = arbitrary(); }
  record->e_quote_request_status = arbitrary();
}

/* Complex Enhanced Quote E Quote Response to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_complex_enhanced_quote_e_quote_response(const ComplexEnhancedQuoteEQuoteResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->e_quote_id[i]; }
  wire[at++] = record->e_quote_request_status;

  return at;
}

/* Complex Enhanced Quote E Quote Response off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_complex_enhanced_quote_e_quote_response(ComplexEnhancedQuoteEQuoteResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->e_quote_id[i] = wire[at++]; }
  record->e_quote_request_status = wire[at++];

  return at;
}

/* what was read of Complex Enhanced Quote E Quote Response is what was written, byte for byte */
static void equal_complex_enhanced_quote_e_quote_response(const ComplexEnhancedQuoteEQuoteResponse *read, const ComplexEnhancedQuoteEQuoteResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->e_quote_id[i] == written->e_quote_id[i]); }
  assert(read->e_quote_request_status == written->e_quote_request_status);
}

/* Complex Enhanced Quote E Quote Response: written and read back, then read and written back */
static void check_complex_enhanced_quote_e_quote_response(void) {
  ComplexEnhancedQuoteEQuoteResponse sent;
  ComplexEnhancedQuoteEQuoteResponse got;
  uint8_t wire[17];
  uint8_t again[17];

  any_complex_enhanced_quote_e_quote_response(&sent);
  assert(encode_complex_enhanced_quote_e_quote_response(&sent, wire, 0) == 17);
  assert(decode_complex_enhanced_quote_e_quote_response(&got, wire, 0) == 17);
  equal_complex_enhanced_quote_e_quote_response(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_enhanced_quote_e_quote_response(&got, wire, 0) == 17);
  assert(encode_complex_enhanced_quote_e_quote_response(&got, again, 0) == 17);
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

/* ---- Product Trading Status Notification: 21 bytes --------------------------- */

/* This message format will be used to notify the firms of changes to the trading status of an option. */
typedef struct {
  uint8_t notification_time[8];    /* bytes 0 to 7 */
  uint8_t product_id[4];           /* bytes 8 to 11 */
  uint8_t trading_status;          /* byte 12 */
  uint8_t expected_event_time[8];  /* bytes 13 to 20 */
} ProductTradingStatusNotification;

/* any Product Trading Status Notification at all: every byte one the checker chooses */
static void any_product_trading_status_notification(ProductTradingStatusNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->expected_event_time[i] = arbitrary(); }
}

/* Product Trading Status Notification to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_product_trading_status_notification(const ProductTradingStatusNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expected_event_time[i]; }

  return at;
}

/* Product Trading Status Notification off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_product_trading_status_notification(ProductTradingStatusNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->expected_event_time[i] = wire[at++]; }

  return at;
}

/* what was read of Product Trading Status Notification is what was written, byte for byte */
static void equal_product_trading_status_notification(const ProductTradingStatusNotification *read, const ProductTradingStatusNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 8; i++) { assert(read->expected_event_time[i] == written->expected_event_time[i]); }
}

/* Product Trading Status Notification: written and read back, then read and written back */
static void check_product_trading_status_notification(void) {
  ProductTradingStatusNotification sent;
  ProductTradingStatusNotification got;
  uint8_t wire[21];
  uint8_t again[21];

  any_product_trading_status_notification(&sent);
  assert(encode_product_trading_status_notification(&sent, wire, 0) == 21);
  assert(decode_product_trading_status_notification(&got, wire, 0) == 21);
  equal_product_trading_status_notification(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_product_trading_status_notification(&got, wire, 0) == 21);
  assert(encode_product_trading_status_notification(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Trading Status Notification: 29 bytes ------------------------ */

/* This message format will be used to notify the firms of changes to the trading status of all the options of an underlying. */
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

/* ---- Simple Arm Protection Settings Notification: 31 bytes ------------------- */

/* This message format will be used to notify firms of their ARM settings. All the ARM settings will be published upon system initialization and each subsequent change will also be published. */
typedef struct {
  uint8_t notification_time[8];                /* bytes 0 to 7 */
  uint8_t mpid[4];                             /* bytes 8 to 11 */
  uint8_t underlying_symbol[11];               /* bytes 12 to 22 */
  uint8_t allowable_engagement_percentage[4];  /* bytes 23 to 26 */
  uint8_t counting_period[2];                  /* bytes 27 to 28 */
  uint8_t action;                              /* byte 29 */
  uint8_t source;                              /* byte 30 */
} SimpleArmProtectionSettingsNotification;

/* any Simple Arm Protection Settings Notification at all: every byte one the checker chooses */
static void any_simple_arm_protection_settings_notification(SimpleArmProtectionSettingsNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->allowable_engagement_percentage[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counting_period[i] = arbitrary(); }
  record->action = arbitrary();
  record->source = arbitrary();
}

/* Simple Arm Protection Settings Notification to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_simple_arm_protection_settings_notification(const SimpleArmProtectionSettingsNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->allowable_engagement_percentage[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counting_period[i]; }
  wire[at++] = record->action;
  wire[at++] = record->source;

  return at;
}

/* Simple Arm Protection Settings Notification off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_simple_arm_protection_settings_notification(SimpleArmProtectionSettingsNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->allowable_engagement_percentage[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counting_period[i] = wire[at++]; }
  record->action = wire[at++];
  record->source = wire[at++];

  return at;
}

/* what was read of Simple Arm Protection Settings Notification is what was written, byte for byte */
static void equal_simple_arm_protection_settings_notification(const SimpleArmProtectionSettingsNotification *read, const SimpleArmProtectionSettingsNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->allowable_engagement_percentage[i] == written->allowable_engagement_percentage[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counting_period[i] == written->counting_period[i]); }
  assert(read->action == written->action);
  assert(read->source == written->source);
}

/* Simple Arm Protection Settings Notification: written and read back, then read and written back */
static void check_simple_arm_protection_settings_notification(void) {
  SimpleArmProtectionSettingsNotification sent;
  SimpleArmProtectionSettingsNotification got;
  uint8_t wire[31];
  uint8_t again[31];

  any_simple_arm_protection_settings_notification(&sent);
  assert(encode_simple_arm_protection_settings_notification(&sent, wire, 0) == 31);
  assert(decode_simple_arm_protection_settings_notification(&got, wire, 0) == 31);
  equal_simple_arm_protection_settings_notification(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_arm_protection_settings_notification(&got, wire, 0) == 31);
  assert(encode_simple_arm_protection_settings_notification(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Arm 2 Underlying Level Protection Settings Notification: 48 bytes ------- */

/* This message format will be used to notify firms of their ARM2 Underlying Level protection settings. */
typedef struct {
  uint8_t notification_time[8];      /* bytes 0 to 7 */
  uint8_t mpid[4];                   /* bytes 8 to 11 */
  uint8_t action;                    /* byte 12 */
  uint8_t underlying_symbol[11];     /* bytes 13 to 23 */
  uint8_t arm_threshold_count[4];    /* bytes 24 to 27 */
  uint8_t arm_2_counting_period[4];  /* bytes 28 to 31 */
  uint8_t reserved_16[16];           /* bytes 32 to 47 */
} Arm2UnderlyingLevelProtectionSettingsNotification;

/* any Arm 2 Underlying Level Protection Settings Notification at all: every byte one the checker chooses */
static void any_arm2_underlying_level_protection_settings_notification(Arm2UnderlyingLevelProtectionSettingsNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->action = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->arm_2_counting_period[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Arm 2 Underlying Level Protection Settings Notification to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_arm2_underlying_level_protection_settings_notification(const Arm2UnderlyingLevelProtectionSettingsNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->action;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->arm_threshold_count[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->arm_2_counting_period[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Arm 2 Underlying Level Protection Settings Notification off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_arm2_underlying_level_protection_settings_notification(Arm2UnderlyingLevelProtectionSettingsNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->action = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->arm_2_counting_period[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Arm 2 Underlying Level Protection Settings Notification is what was written, byte for byte */
static void equal_arm2_underlying_level_protection_settings_notification(const Arm2UnderlyingLevelProtectionSettingsNotification *read, const Arm2UnderlyingLevelProtectionSettingsNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->action == written->action);
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->arm_threshold_count[i] == written->arm_threshold_count[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->arm_2_counting_period[i] == written->arm_2_counting_period[i]); }
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

/* This message format will be used to notify firms when a Single Side Liquidity Protection is triggered for a MIAX Option or Complex Strategy. */
typedef struct {
  uint8_t notification_time[8];             /* bytes 0 to 7 */
  uint8_t mpid[4];                          /* bytes 8 to 11 */
  uint8_t security_id_scope;                /* byte 12 */
  uint8_t security_id[4];                   /* bytes 13 to 16 */
  uint8_t side;                             /* byte 17 */
  uint8_t triggering_client_message_id[4];  /* bytes 18 to 21 */
  uint8_t triggering_bulk_quote_index;      /* byte 22 */
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
  record->triggering_bulk_quote_index = arbitrary();
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
  wire[at++] = record->triggering_bulk_quote_index;
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
  record->triggering_bulk_quote_index = wire[at++];
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
  assert(read->triggering_bulk_quote_index == written->triggering_bulk_quote_index);
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

/* This message format will be used to notify firms about ARM2 Underlying Level protection events. */
typedef struct {
  uint8_t notification_time[8];      /* bytes 0 to 7 */
  uint8_t mpid[4];                   /* bytes 8 to 11 */
  uint8_t underlying_symbol[11];     /* bytes 12 to 22 */
  uint8_t notification_type;         /* byte 23 */
  uint8_t arm_threshold_count[4];    /* bytes 24 to 27 */
  uint8_t arm_2_counting_period[4];  /* bytes 28 to 31 */
  uint8_t reserved_16[16];           /* bytes 32 to 47 */
} Arm2UnderlyingLevelProtectionNotification;

/* any Arm 2 Underlying Level Protection Notification at all: every byte one the checker chooses */
static void any_arm2_underlying_level_protection_notification(Arm2UnderlyingLevelProtectionNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->notification_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->arm_2_counting_period[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Arm 2 Underlying Level Protection Notification to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_arm2_underlying_level_protection_notification(const Arm2UnderlyingLevelProtectionNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->notification_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->arm_threshold_count[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->arm_2_counting_period[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Arm 2 Underlying Level Protection Notification off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_arm2_underlying_level_protection_notification(Arm2UnderlyingLevelProtectionNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->notification_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->arm_2_counting_period[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Arm 2 Underlying Level Protection Notification is what was written, byte for byte */
static void equal_arm2_underlying_level_protection_notification(const Arm2UnderlyingLevelProtectionNotification *read, const Arm2UnderlyingLevelProtectionNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->notification_type == written->notification_type);
  for (size_t i = 0; i < 4; i++) { assert(read->arm_threshold_count[i] == written->arm_threshold_count[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->arm_2_counting_period[i] == written->arm_2_counting_period[i]); }
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

/* This message format will be used to notify firms about ARM2 Firm Level protection events. */
typedef struct {
  uint8_t notification_time[8];      /* bytes 0 to 7 */
  uint8_t arm_threshold_count[4];    /* bytes 8 to 11 */
  uint8_t arm_2_counting_period[4];  /* bytes 12 to 15 */
  uint8_t notification_type;         /* byte 16 */
  uint8_t reserved_16[16];           /* bytes 17 to 32 */
} Arm2FirmLevelProtectionNotification;

/* any Arm 2 Firm Level Protection Notification at all: every byte one the checker chooses */
static void any_arm2_firm_level_protection_notification(Arm2FirmLevelProtectionNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->arm_2_counting_period[i] = arbitrary(); }
  record->notification_type = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Arm 2 Firm Level Protection Notification to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_arm2_firm_level_protection_notification(const Arm2FirmLevelProtectionNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->arm_threshold_count[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->arm_2_counting_period[i]; }
  wire[at++] = record->notification_type;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Arm 2 Firm Level Protection Notification off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_arm2_firm_level_protection_notification(Arm2FirmLevelProtectionNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->arm_2_counting_period[i] = wire[at++]; }
  record->notification_type = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Arm 2 Firm Level Protection Notification is what was written, byte for byte */
static void equal_arm2_firm_level_protection_notification(const Arm2FirmLevelProtectionNotification *read, const Arm2FirmLevelProtectionNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->arm_threshold_count[i] == written->arm_threshold_count[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->arm_2_counting_period[i] == written->arm_2_counting_period[i]); }
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

/* ---- Cancel Notification: 36 bytes ------------------------------------------- */

/* This is the message format that will be used to notify firms about system generated or firm requested simple quote and simple or complex eQuote cancels. */
typedef struct {
  uint8_t notification_time[8];          /* bytes 0 to 7 */
  uint8_t mpid[4];                       /* bytes 8 to 11 */
  uint8_t product_id_or_strategy_id[4];  /* bytes 12 to 15 */
  uint8_t liquidity_type;                /* byte 16 */
  uint8_t client_message_id[4];          /* bytes 17 to 20 */
  uint8_t bulk_quote_index;              /* byte 21 */
  uint8_t quotee_quote_side;             /* byte 22 */
  uint8_t size[4];                       /* bytes 23 to 26 */
  uint8_t engine_sequence_number[8];     /* bytes 27 to 34 */
  uint8_t cancel_reason;                 /* byte 35 */
} CancelNotification;

/* any Cancel Notification at all: every byte one the checker chooses */
static void any_cancel_notification(CancelNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id_or_strategy_id[i] = arbitrary(); }
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id_or_strategy_id[i]; }
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
  for (size_t i = 0; i < 4; i++) { record->product_id_or_strategy_id[i] = wire[at++]; }
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
  for (size_t i = 0; i < 4; i++) { assert(read->product_id_or_strategy_id[i] == written->product_id_or_strategy_id[i]); }
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

/* ---- Option Execution Notification: 49 bytes --------------------------------- */

/* This message format will be used to notify the firms of executions of their simple quotes and simple or complex eQuotes. */
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
} OptionExecutionNotification;

/* any Option Execution Notification at all: every byte one the checker chooses */
static void any_option_execution_notification(OptionExecutionNotification *record) {
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

/* Option Execution Notification to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_option_execution_notification(const OptionExecutionNotification *record, uint8_t *wire, size_t at) {
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

/* Option Execution Notification off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_option_execution_notification(OptionExecutionNotification *record, const uint8_t *wire, size_t at) {
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

/* what was read of Option Execution Notification is what was written, byte for byte */
static void equal_option_execution_notification(const OptionExecutionNotification *read, const OptionExecutionNotification *written) {
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

/* Option Execution Notification: written and read back, then read and written back */
static void check_option_execution_notification(void) {
  OptionExecutionNotification sent;
  OptionExecutionNotification got;
  uint8_t wire[49];
  uint8_t again[49];

  any_option_execution_notification(&sent);
  assert(encode_option_execution_notification(&sent, wire, 0) == 49);
  assert(decode_option_execution_notification(&got, wire, 0) == 49);
  equal_option_execution_notification(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_option_execution_notification(&got, wire, 0) == 49);
  assert(encode_option_execution_notification(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Leg Execution Notification: 71 bytes ------------------------------ */

/* This message format will be used to notify the firm of a stock leg execution from a stock-tied complex eQuote. */
typedef struct {
  uint8_t notification_time[8];        /* bytes 0 to 7 */
  uint8_t mpid[4];                     /* bytes 8 to 11 */
  uint8_t underlying_symbol[11];       /* bytes 12 to 22 */
  uint8_t liquidity_type;              /* byte 23 */
  uint8_t client_message_id[4];        /* bytes 24 to 27 */
  uint8_t event_id[4];                 /* bytes 28 to 31 */
  uint8_t trade_id[4];                 /* bytes 32 to 35 */
  uint8_t execution_id[8];             /* bytes 36 to 43 */
  uint8_t trade_status;                /* byte 44 */
  uint8_t last_price[4];               /* bytes 45 to 48 */
  uint8_t side;                        /* byte 49 */
  uint8_t stock_sell_short_indicator;  /* byte 50 */
  uint8_t last_size[4];                /* bytes 51 to 54 */
  uint8_t reserved_16[16];             /* bytes 55 to 70 */
} StockLegExecutionNotification;

/* any Stock Leg Execution Notification at all: every byte one the checker chooses */
static void any_stock_leg_execution_notification(StockLegExecutionNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->liquidity_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->trade_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = arbitrary(); }
  record->side = arbitrary();
  record->stock_sell_short_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_size[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Stock Leg Execution Notification to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_stock_leg_execution_notification(const StockLegExecutionNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->liquidity_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_id[i]; }
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

/* Stock Leg Execution Notification off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_stock_leg_execution_notification(StockLegExecutionNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->liquidity_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = wire[at++]; }
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
  for (size_t i = 0; i < 4; i++) { assert(read->event_id[i] == written->event_id[i]); }
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
  uint8_t wire[71];
  uint8_t again[71];

  any_stock_leg_execution_notification(&sent);
  assert(encode_stock_leg_execution_notification(&sent, wire, 0) == 71);
  assert(decode_stock_leg_execution_notification(&got, wire, 0) == 71);
  equal_stock_leg_execution_notification(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_leg_execution_notification(&got, wire, 0) == 71);
  assert(encode_stock_leg_execution_notification(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Arm Settings Update Request: 26 bytes ---------------------------- */

/* Firms can use this message format to set up their ARM protection settings for each session. Changes to these settings can be made throughout the day. */
typedef struct {
  uint8_t client_message_id[4];                /* bytes 0 to 3 */
  uint8_t mpid[4];                             /* bytes 4 to 7 */
  uint8_t action;                              /* byte 8 */
  uint8_t underlying_symbol[11];               /* bytes 9 to 19 */
  uint8_t allowable_engagement_percentage[4];  /* bytes 20 to 23 */
  uint8_t counting_period[2];                  /* bytes 24 to 25 */
} SimpleArmSettingsUpdateRequest;

/* any Simple Arm Settings Update Request at all: every byte one the checker chooses */
static void any_simple_arm_settings_update_request(SimpleArmSettingsUpdateRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->action = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->allowable_engagement_percentage[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counting_period[i] = arbitrary(); }
}

/* Simple Arm Settings Update Request to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_simple_arm_settings_update_request(const SimpleArmSettingsUpdateRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->action;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->allowable_engagement_percentage[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counting_period[i]; }

  return at;
}

/* Simple Arm Settings Update Request off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_simple_arm_settings_update_request(SimpleArmSettingsUpdateRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->action = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->allowable_engagement_percentage[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counting_period[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Arm Settings Update Request is what was written, byte for byte */
static void equal_simple_arm_settings_update_request(const SimpleArmSettingsUpdateRequest *read, const SimpleArmSettingsUpdateRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->action == written->action);
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->allowable_engagement_percentage[i] == written->allowable_engagement_percentage[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counting_period[i] == written->counting_period[i]); }
}

/* Simple Arm Settings Update Request: written and read back, then read and written back */
static void check_simple_arm_settings_update_request(void) {
  SimpleArmSettingsUpdateRequest sent;
  SimpleArmSettingsUpdateRequest got;
  uint8_t wire[26];
  uint8_t again[26];

  any_simple_arm_settings_update_request(&sent);
  assert(encode_simple_arm_settings_update_request(&sent, wire, 0) == 26);
  assert(decode_simple_arm_settings_update_request(&got, wire, 0) == 26);
  equal_simple_arm_settings_update_request(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_arm_settings_update_request(&got, wire, 0) == 26);
  assert(encode_simple_arm_settings_update_request(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Arm Settings Update Response: 20 bytes --------------------------- */

/* MIAX uses this format to respond to the firm with a status of their ARM protection settings request. */
typedef struct {
  uint8_t client_message_id[4];        /* bytes 0 to 3 */
  uint8_t mpid[4];                     /* bytes 4 to 7 */
  uint8_t underlying_symbol[11];       /* bytes 8 to 18 */
  uint8_t arm_settings_update_status;  /* byte 19 */
} SimpleArmSettingsUpdateResponse;

/* any Simple Arm Settings Update Response at all: every byte one the checker chooses */
static void any_simple_arm_settings_update_response(SimpleArmSettingsUpdateResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->arm_settings_update_status = arbitrary();
}

/* Simple Arm Settings Update Response to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_simple_arm_settings_update_response(const SimpleArmSettingsUpdateResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->arm_settings_update_status;

  return at;
}

/* Simple Arm Settings Update Response off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_simple_arm_settings_update_response(SimpleArmSettingsUpdateResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->arm_settings_update_status = wire[at++];

  return at;
}

/* what was read of Simple Arm Settings Update Response is what was written, byte for byte */
static void equal_simple_arm_settings_update_response(const SimpleArmSettingsUpdateResponse *read, const SimpleArmSettingsUpdateResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->arm_settings_update_status == written->arm_settings_update_status);
}

/* Simple Arm Settings Update Response: written and read back, then read and written back */
static void check_simple_arm_settings_update_response(void) {
  SimpleArmSettingsUpdateResponse sent;
  SimpleArmSettingsUpdateResponse got;
  uint8_t wire[20];
  uint8_t again[20];

  any_simple_arm_settings_update_response(&sent);
  assert(encode_simple_arm_settings_update_response(&sent, wire, 0) == 20);
  assert(decode_simple_arm_settings_update_response(&got, wire, 0) == 20);
  equal_simple_arm_settings_update_response(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_arm_settings_update_response(&got, wire, 0) == 20);
  assert(encode_simple_arm_settings_update_response(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Arm 2 Underlying Level Protection Settings Update Request: 28 bytes ----- */

/* Firms can use this message format to set up their ARM2 Underlying Level protection settings for each session. Changes to these settings can be made throughout the day. */
typedef struct {
  uint8_t client_message_id[4];      /* bytes 0 to 3 */
  uint8_t mpid[4];                   /* bytes 4 to 7 */
  uint8_t action;                    /* byte 8 */
  uint8_t underlying_symbol[11];     /* bytes 9 to 19 */
  uint8_t arm_threshold_count[4];    /* bytes 20 to 23 */
  uint8_t arm_2_counting_period[4];  /* bytes 24 to 27 */
} Arm2UnderlyingLevelProtectionSettingsUpdateRequest;

/* any Arm 2 Underlying Level Protection Settings Update Request at all: every byte one the checker chooses */
static void any_arm2_underlying_level_protection_settings_update_request(Arm2UnderlyingLevelProtectionSettingsUpdateRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->action = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->arm_2_counting_period[i] = arbitrary(); }
}

/* Arm 2 Underlying Level Protection Settings Update Request to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_arm2_underlying_level_protection_settings_update_request(const Arm2UnderlyingLevelProtectionSettingsUpdateRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->action;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->arm_threshold_count[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->arm_2_counting_period[i]; }

  return at;
}

/* Arm 2 Underlying Level Protection Settings Update Request off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_arm2_underlying_level_protection_settings_update_request(Arm2UnderlyingLevelProtectionSettingsUpdateRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->action = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->arm_threshold_count[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->arm_2_counting_period[i] = wire[at++]; }

  return at;
}

/* what was read of Arm 2 Underlying Level Protection Settings Update Request is what was written, byte for byte */
static void equal_arm2_underlying_level_protection_settings_update_request(const Arm2UnderlyingLevelProtectionSettingsUpdateRequest *read, const Arm2UnderlyingLevelProtectionSettingsUpdateRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->action == written->action);
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->arm_threshold_count[i] == written->arm_threshold_count[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->arm_2_counting_period[i] == written->arm_2_counting_period[i]); }
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

/* MIAX uses this format to respond to the firm with a status of their ARM2 Underlying level protection Settings Update Request. */
typedef struct {
  uint8_t client_message_id[4];        /* bytes 0 to 3 */
  uint8_t mpid[4];                     /* bytes 4 to 7 */
  uint8_t underlying_symbol[11];       /* bytes 8 to 18 */
  uint8_t arm_settings_update_status;  /* byte 19 */
} Arm2UnderlyingLevelProtectionSettingsUpdateResponse;

/* any Arm 2 Underlying Level Protection Settings Update Response at all: every byte one the checker chooses */
static void any_arm2_underlying_level_protection_settings_update_response(Arm2UnderlyingLevelProtectionSettingsUpdateResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->arm_settings_update_status = arbitrary();
}

/* Arm 2 Underlying Level Protection Settings Update Response to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_arm2_underlying_level_protection_settings_update_response(const Arm2UnderlyingLevelProtectionSettingsUpdateResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->arm_settings_update_status;

  return at;
}

/* Arm 2 Underlying Level Protection Settings Update Response off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_arm2_underlying_level_protection_settings_update_response(Arm2UnderlyingLevelProtectionSettingsUpdateResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->arm_settings_update_status = wire[at++];

  return at;
}

/* what was read of Arm 2 Underlying Level Protection Settings Update Response is what was written, byte for byte */
static void equal_arm2_underlying_level_protection_settings_update_response(const Arm2UnderlyingLevelProtectionSettingsUpdateResponse *read, const Arm2UnderlyingLevelProtectionSettingsUpdateResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->arm_settings_update_status == written->arm_settings_update_status);
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

/* ---- Simple Enhanced Quote E Quote Message: 43 bytes ------------------------- */

/* This is the format for an eQuote message that can be sent either to match with orders and quotes on the MIAX book or when responding to a liquidity seeking event. */
typedef struct {
  uint8_t client_message_id[4];  /* bytes 0 to 3 */
  uint8_t mpid[4];               /* bytes 4 to 7 */
  uint8_t client_send_time[8];   /* bytes 8 to 15 */
  uint8_t product_id[4];         /* bytes 16 to 19 */
  uint8_t e_quote_action;        /* byte 20 */
  uint8_t e_quote_type;          /* byte 21 */
  uint8_t event_id[4];           /* bytes 22 to 25 */
  uint8_t target_message_id[4];  /* bytes 26 to 29 */
  uint8_t price[4];              /* bytes 30 to 33 */
  uint8_t size[4];               /* bytes 34 to 37 */
  uint8_t side;                  /* byte 38 */
  uint8_t reserved_4[4];         /* bytes 39 to 42 */
} SimpleEnhancedQuoteEQuoteMessage;

/* any Simple Enhanced Quote E Quote Message at all: every byte one the checker chooses */
static void any_simple_enhanced_quote_e_quote_message(SimpleEnhancedQuoteEQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  record->e_quote_action = arbitrary();
  record->e_quote_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->target_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Simple Enhanced Quote E Quote Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_simple_enhanced_quote_e_quote_message(const SimpleEnhancedQuoteEQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_send_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  wire[at++] = record->e_quote_action;
  wire[at++] = record->e_quote_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->target_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Simple Enhanced Quote E Quote Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_simple_enhanced_quote_e_quote_message(SimpleEnhancedQuoteEQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  record->e_quote_action = wire[at++];
  record->e_quote_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->target_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Enhanced Quote E Quote Message is what was written, byte for byte */
static void equal_simple_enhanced_quote_e_quote_message(const SimpleEnhancedQuoteEQuoteMessage *read, const SimpleEnhancedQuoteEQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_send_time[i] == written->client_send_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  assert(read->e_quote_action == written->e_quote_action);
  assert(read->e_quote_type == written->e_quote_type);
  for (size_t i = 0; i < 4; i++) { assert(read->event_id[i] == written->event_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->target_message_id[i] == written->target_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Simple Enhanced Quote E Quote Message: written and read back, then read and written back */
static void check_simple_enhanced_quote_e_quote_message(void) {
  SimpleEnhancedQuoteEQuoteMessage sent;
  SimpleEnhancedQuoteEQuoteMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_simple_enhanced_quote_e_quote_message(&sent);
  assert(encode_simple_enhanced_quote_e_quote_message(&sent, wire, 0) == 43);
  assert(decode_simple_enhanced_quote_e_quote_message(&got, wire, 0) == 43);
  equal_simple_enhanced_quote_e_quote_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_enhanced_quote_e_quote_message(&got, wire, 0) == 43);
  assert(encode_simple_enhanced_quote_e_quote_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Enhanced Quote E Quote Message: 59 bytes ------------------------ */

/* This is the format for a Complex eQuote message that can be sent either to match with complex book or when responding to a complex auction liquidity seeking event. */
typedef struct {
  uint8_t client_message_id[4];        /* bytes 0 to 3 */
  uint8_t mpid[4];                     /* bytes 4 to 7 */
  uint8_t client_send_time[8];         /* bytes 8 to 15 */
  uint8_t strategy_id[4];              /* bytes 16 to 19 */
  uint8_t e_quote_action;              /* byte 20 */
  uint8_t e_quote_type;                /* byte 21 */
  uint8_t complex_event_id[4];         /* bytes 22 to 25 */
  uint8_t target_message_id[4];        /* bytes 26 to 29 */
  uint8_t net_price[8];                /* bytes 30 to 37 */
  uint8_t size[4];                     /* bytes 38 to 41 */
  uint8_t side;                        /* byte 42 */
  uint8_t stock_sell_short_indicator;  /* byte 43 */
  uint8_t reserved_15[15];             /* bytes 44 to 58 */
} ComplexEnhancedQuoteEQuoteMessage;

/* any Complex Enhanced Quote E Quote Message at all: every byte one the checker chooses */
static void any_complex_enhanced_quote_e_quote_message(ComplexEnhancedQuoteEQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  record->e_quote_action = arbitrary();
  record->e_quote_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->complex_event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->target_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->net_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  record->side = arbitrary();
  record->stock_sell_short_indicator = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->reserved_15[i] = arbitrary(); }
}

/* Complex Enhanced Quote E Quote Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_complex_enhanced_quote_e_quote_message(const ComplexEnhancedQuoteEQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_send_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  wire[at++] = record->e_quote_action;
  wire[at++] = record->e_quote_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->complex_event_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->target_message_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->net_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  wire[at++] = record->side;
  wire[at++] = record->stock_sell_short_indicator;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->reserved_15[i]; }

  return at;
}

/* Complex Enhanced Quote E Quote Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_complex_enhanced_quote_e_quote_message(ComplexEnhancedQuoteEQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  record->e_quote_action = wire[at++];
  record->e_quote_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->complex_event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->target_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->net_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  record->side = wire[at++];
  record->stock_sell_short_indicator = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->reserved_15[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Enhanced Quote E Quote Message is what was written, byte for byte */
static void equal_complex_enhanced_quote_e_quote_message(const ComplexEnhancedQuoteEQuoteMessage *read, const ComplexEnhancedQuoteEQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_send_time[i] == written->client_send_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  assert(read->e_quote_action == written->e_quote_action);
  assert(read->e_quote_type == written->e_quote_type);
  for (size_t i = 0; i < 4; i++) { assert(read->complex_event_id[i] == written->complex_event_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->target_message_id[i] == written->target_message_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->net_price[i] == written->net_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  assert(read->side == written->side);
  assert(read->stock_sell_short_indicator == written->stock_sell_short_indicator);
  for (size_t i = 0; i < 15; i++) { assert(read->reserved_15[i] == written->reserved_15[i]); }
}

/* Complex Enhanced Quote E Quote Message: written and read back, then read and written back */
static void check_complex_enhanced_quote_e_quote_message(void) {
  ComplexEnhancedQuoteEQuoteMessage sent;
  ComplexEnhancedQuoteEQuoteMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_complex_enhanced_quote_e_quote_message(&sent);
  assert(encode_complex_enhanced_quote_e_quote_message(&sent, wire, 0) == 59);
  assert(decode_complex_enhanced_quote_e_quote_message(&got, wire, 0) == 59);
  equal_complex_enhanced_quote_e_quote_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_enhanced_quote_e_quote_message(&got, wire, 0) == 59);
  assert(encode_complex_enhanced_quote_e_quote_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Mass Quote Cancel Request: 31 bytes ------------------------------ */

/* Firms can use this message format to request the cancelation of all simple quotes and eQuotes for an MPID, or all simple quotes and eQuotes for an MPID for all series for an underlying */
typedef struct {
  uint8_t client_message_id[4];   /* bytes 0 to 3 */
  uint8_t mpid[4];                /* bytes 4 to 7 */
  uint8_t client_send_time[8];    /* bytes 8 to 15 */
  uint8_t underlying_symbol[11];  /* bytes 16 to 26 */
  uint8_t reserved_4[4];          /* bytes 27 to 30 */
} SimpleMassQuoteCancelRequest;

/* any Simple Mass Quote Cancel Request at all: every byte one the checker chooses */
static void any_simple_mass_quote_cancel_request(SimpleMassQuoteCancelRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Simple Mass Quote Cancel Request to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_simple_mass_quote_cancel_request(const SimpleMassQuoteCancelRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_send_time[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Simple Mass Quote Cancel Request off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_simple_mass_quote_cancel_request(SimpleMassQuoteCancelRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Mass Quote Cancel Request is what was written, byte for byte */
static void equal_simple_mass_quote_cancel_request(const SimpleMassQuoteCancelRequest *read, const SimpleMassQuoteCancelRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_send_time[i] == written->client_send_time[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Simple Mass Quote Cancel Request: written and read back, then read and written back */
static void check_simple_mass_quote_cancel_request(void) {
  SimpleMassQuoteCancelRequest sent;
  SimpleMassQuoteCancelRequest got;
  uint8_t wire[31];
  uint8_t again[31];

  any_simple_mass_quote_cancel_request(&sent);
  assert(encode_simple_mass_quote_cancel_request(&sent, wire, 0) == 31);
  assert(decode_simple_mass_quote_cancel_request(&got, wire, 0) == 31);
  equal_simple_mass_quote_cancel_request(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_mass_quote_cancel_request(&got, wire, 0) == 31);
  assert(encode_simple_mass_quote_cancel_request(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Mass Quote Cancel Response: 9 bytes ------------------------------ */

/* This message format will be used to inform the firm about the status of their previous simple mass quote cancel request. */
typedef struct {
  uint8_t client_message_id[4];             /* bytes 0 to 3 */
  uint8_t mpid[4];                          /* bytes 4 to 7 */
  uint8_t simple_mass_quote_cancel_status;  /* byte 8 */
} SimpleMassQuoteCancelResponse;

/* any Simple Mass Quote Cancel Response at all: every byte one the checker chooses */
static void any_simple_mass_quote_cancel_response(SimpleMassQuoteCancelResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->simple_mass_quote_cancel_status = arbitrary();
}

/* Simple Mass Quote Cancel Response to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_simple_mass_quote_cancel_response(const SimpleMassQuoteCancelResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->simple_mass_quote_cancel_status;

  return at;
}

/* Simple Mass Quote Cancel Response off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_simple_mass_quote_cancel_response(SimpleMassQuoteCancelResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->simple_mass_quote_cancel_status = wire[at++];

  return at;
}

/* what was read of Simple Mass Quote Cancel Response is what was written, byte for byte */
static void equal_simple_mass_quote_cancel_response(const SimpleMassQuoteCancelResponse *read, const SimpleMassQuoteCancelResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->simple_mass_quote_cancel_status == written->simple_mass_quote_cancel_status);
}

/* Simple Mass Quote Cancel Response: written and read back, then read and written back */
static void check_simple_mass_quote_cancel_response(void) {
  SimpleMassQuoteCancelResponse sent;
  SimpleMassQuoteCancelResponse got;
  uint8_t wire[9];
  uint8_t again[9];

  any_simple_mass_quote_cancel_response(&sent);
  assert(encode_simple_mass_quote_cancel_response(&sent, wire, 0) == 9);
  assert(decode_simple_mass_quote_cancel_response(&got, wire, 0) == 9);
  equal_simple_mass_quote_cancel_response(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_mass_quote_cancel_response(&got, wire, 0) == 9);
  assert(encode_simple_mass_quote_cancel_response(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Liquidity Cancel Request Simple And Complex: 37 bytes -------------- */

/* Firms can use this message format to request the cancelation of all simple quotes and simple/complex eQuotes for an MPID, or all simple quotes and simple/complex eQuotes for an MPID for all series and/or strategies for an underlying */
typedef struct {
  uint8_t client_message_id[4];   /* bytes 0 to 3 */
  uint8_t mpid[4];                /* bytes 4 to 7 */
  uint8_t client_send_time[8];    /* bytes 8 to 15 */
  uint8_t underlying_symbol[11];  /* bytes 16 to 26 */
  uint8_t simple_mass_cancel;     /* byte 27 */
  uint8_t complex_mass_cancel;    /* byte 28 */
  uint8_t reserved_8[8];          /* bytes 29 to 36 */
} MassLiquidityCancelRequestSimpleAndComplex;

/* any Mass Liquidity Cancel Request Simple And Complex at all: every byte one the checker chooses */
static void any_mass_liquidity_cancel_request_simple_and_complex(MassLiquidityCancelRequestSimpleAndComplex *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->simple_mass_cancel = arbitrary();
  record->complex_mass_cancel = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Mass Liquidity Cancel Request Simple And Complex to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_mass_liquidity_cancel_request_simple_and_complex(const MassLiquidityCancelRequestSimpleAndComplex *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_send_time[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->simple_mass_cancel;
  wire[at++] = record->complex_mass_cancel;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Mass Liquidity Cancel Request Simple And Complex off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_mass_liquidity_cancel_request_simple_and_complex(MassLiquidityCancelRequestSimpleAndComplex *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->simple_mass_cancel = wire[at++];
  record->complex_mass_cancel = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Liquidity Cancel Request Simple And Complex is what was written, byte for byte */
static void equal_mass_liquidity_cancel_request_simple_and_complex(const MassLiquidityCancelRequestSimpleAndComplex *read, const MassLiquidityCancelRequestSimpleAndComplex *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_send_time[i] == written->client_send_time[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->simple_mass_cancel == written->simple_mass_cancel);
  assert(read->complex_mass_cancel == written->complex_mass_cancel);
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Mass Liquidity Cancel Request Simple And Complex: written and read back, then read and written back */
static void check_mass_liquidity_cancel_request_simple_and_complex(void) {
  MassLiquidityCancelRequestSimpleAndComplex sent;
  MassLiquidityCancelRequestSimpleAndComplex got;
  uint8_t wire[37];
  uint8_t again[37];

  any_mass_liquidity_cancel_request_simple_and_complex(&sent);
  assert(encode_mass_liquidity_cancel_request_simple_and_complex(&sent, wire, 0) == 37);
  assert(decode_mass_liquidity_cancel_request_simple_and_complex(&got, wire, 0) == 37);
  equal_mass_liquidity_cancel_request_simple_and_complex(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_liquidity_cancel_request_simple_and_complex(&got, wire, 0) == 37);
  assert(encode_mass_liquidity_cancel_request_simple_and_complex(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Liquidity Cancel Response: 10 bytes -------------------------------- */

/* This message format will be used to inform the firm about the status of their previous Mass Liquidity Cancel Request. */
typedef struct {
  uint8_t client_message_id[4];                  /* bytes 0 to 3 */
  uint8_t mpid[4];                               /* bytes 4 to 7 */
  uint8_t simple_mass_liquidity_cancel_status;   /* byte 8 */
  uint8_t complex_mass_liquidity_cancel_status;  /* byte 9 */
} MassLiquidityCancelResponse;

/* any Mass Liquidity Cancel Response at all: every byte one the checker chooses */
static void any_mass_liquidity_cancel_response(MassLiquidityCancelResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->simple_mass_liquidity_cancel_status = arbitrary();
  record->complex_mass_liquidity_cancel_status = arbitrary();
}

/* Mass Liquidity Cancel Response to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_mass_liquidity_cancel_response(const MassLiquidityCancelResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->simple_mass_liquidity_cancel_status;
  wire[at++] = record->complex_mass_liquidity_cancel_status;

  return at;
}

/* Mass Liquidity Cancel Response off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_mass_liquidity_cancel_response(MassLiquidityCancelResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->simple_mass_liquidity_cancel_status = wire[at++];
  record->complex_mass_liquidity_cancel_status = wire[at++];

  return at;
}

/* what was read of Mass Liquidity Cancel Response is what was written, byte for byte */
static void equal_mass_liquidity_cancel_response(const MassLiquidityCancelResponse *read, const MassLiquidityCancelResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->simple_mass_liquidity_cancel_status == written->simple_mass_liquidity_cancel_status);
  assert(read->complex_mass_liquidity_cancel_status == written->complex_mass_liquidity_cancel_status);
}

/* Mass Liquidity Cancel Response: written and read back, then read and written back */
static void check_mass_liquidity_cancel_response(void) {
  MassLiquidityCancelResponse sent;
  MassLiquidityCancelResponse got;
  uint8_t wire[10];
  uint8_t again[10];

  any_mass_liquidity_cancel_response(&sent);
  assert(encode_mass_liquidity_cancel_response(&sent, wire, 0) == 10);
  assert(decode_mass_liquidity_cancel_response(&got, wire, 0) == 10);
  equal_mass_liquidity_cancel_response(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_liquidity_cancel_response(&got, wire, 0) == 10);
  assert(encode_mass_liquidity_cancel_response(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Quote Protection Reset Request: 19 bytes ------------------------- */

/* Following a quote protection being engaged for a given MPID and underlying, firms must use this message format to reset their Quote Protection in order to start quoting for any option of the specified underlying. */
typedef struct {
  uint8_t client_message_id[4];   /* bytes 0 to 3 */
  uint8_t mpid[4];                /* bytes 4 to 7 */
  uint8_t underlying_symbol[11];  /* bytes 8 to 18 */
} SimpleQuoteProtectionResetRequest;

/* any Simple Quote Protection Reset Request at all: every byte one the checker chooses */
static void any_simple_quote_protection_reset_request(SimpleQuoteProtectionResetRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
}

/* Simple Quote Protection Reset Request to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_simple_quote_protection_reset_request(const SimpleQuoteProtectionResetRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }

  return at;
}

/* Simple Quote Protection Reset Request off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_simple_quote_protection_reset_request(SimpleQuoteProtectionResetRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Quote Protection Reset Request is what was written, byte for byte */
static void equal_simple_quote_protection_reset_request(const SimpleQuoteProtectionResetRequest *read, const SimpleQuoteProtectionResetRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
}

/* Simple Quote Protection Reset Request: written and read back, then read and written back */
static void check_simple_quote_protection_reset_request(void) {
  SimpleQuoteProtectionResetRequest sent;
  SimpleQuoteProtectionResetRequest got;
  uint8_t wire[19];
  uint8_t again[19];

  any_simple_quote_protection_reset_request(&sent);
  assert(encode_simple_quote_protection_reset_request(&sent, wire, 0) == 19);
  assert(decode_simple_quote_protection_reset_request(&got, wire, 0) == 19);
  equal_simple_quote_protection_reset_request(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_quote_protection_reset_request(&got, wire, 0) == 19);
  assert(encode_simple_quote_protection_reset_request(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Quote Protection Reset Response: 9 bytes ------------------------- */

/* This message format is used to inform the firms of the status of their Simple Quote Protection Reset Request. */
typedef struct {
  uint8_t client_message_id[4];           /* bytes 0 to 3 */
  uint8_t mpid[4];                        /* bytes 4 to 7 */
  uint8_t quote_protection_reset_status;  /* byte 8 */
} SimpleQuoteProtectionResetResponse;

/* any Simple Quote Protection Reset Response at all: every byte one the checker chooses */
static void any_simple_quote_protection_reset_response(SimpleQuoteProtectionResetResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->quote_protection_reset_status = arbitrary();
}

/* Simple Quote Protection Reset Response to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_simple_quote_protection_reset_response(const SimpleQuoteProtectionResetResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->quote_protection_reset_status;

  return at;
}

/* Simple Quote Protection Reset Response off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_simple_quote_protection_reset_response(SimpleQuoteProtectionResetResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->quote_protection_reset_status = wire[at++];

  return at;
}

/* what was read of Simple Quote Protection Reset Response is what was written, byte for byte */
static void equal_simple_quote_protection_reset_response(const SimpleQuoteProtectionResetResponse *read, const SimpleQuoteProtectionResetResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->quote_protection_reset_status == written->quote_protection_reset_status);
}

/* Simple Quote Protection Reset Response: written and read back, then read and written back */
static void check_simple_quote_protection_reset_response(void) {
  SimpleQuoteProtectionResetResponse sent;
  SimpleQuoteProtectionResetResponse got;
  uint8_t wire[9];
  uint8_t again[9];

  any_simple_quote_protection_reset_response(&sent);
  assert(encode_simple_quote_protection_reset_response(&sent, wire, 0) == 9);
  assert(decode_simple_quote_protection_reset_response(&got, wire, 0) == 9);
  equal_simple_quote_protection_reset_response(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_quote_protection_reset_response(&got, wire, 0) == 9);
  assert(encode_simple_quote_protection_reset_response(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Liquidity Protection Reset Request: 29 bytes ---------------------------- */

/* Following a quote protection being engaged for a given MPID and underlying, firms must use this message format to reset their Complex Liquidity Protection and/or Simple Liquidity Protection in order to start submitting new simple or complex liquidities for any strategy of the specified underlying and/or products of the specified underlying. */
typedef struct {
  uint8_t client_message_id[4];     /* bytes 0 to 3 */
  uint8_t mpid[4];                  /* bytes 4 to 7 */
  uint8_t underlying_symbol[11];    /* bytes 8 to 18 */
  uint8_t simple_liquidity_reset;   /* byte 19 */
  uint8_t complex_liquidity_reset;  /* byte 20 */
  uint8_t reserved_8[8];            /* bytes 21 to 28 */
} LiquidityProtectionResetRequest;

/* any Liquidity Protection Reset Request at all: every byte one the checker chooses */
static void any_liquidity_protection_reset_request(LiquidityProtectionResetRequest *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->simple_liquidity_reset = arbitrary();
  record->complex_liquidity_reset = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Liquidity Protection Reset Request to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_liquidity_protection_reset_request(const LiquidityProtectionResetRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->simple_liquidity_reset;
  wire[at++] = record->complex_liquidity_reset;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Liquidity Protection Reset Request off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_liquidity_protection_reset_request(LiquidityProtectionResetRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->simple_liquidity_reset = wire[at++];
  record->complex_liquidity_reset = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Liquidity Protection Reset Request is what was written, byte for byte */
static void equal_liquidity_protection_reset_request(const LiquidityProtectionResetRequest *read, const LiquidityProtectionResetRequest *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->simple_liquidity_reset == written->simple_liquidity_reset);
  assert(read->complex_liquidity_reset == written->complex_liquidity_reset);
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Liquidity Protection Reset Request: written and read back, then read and written back */
static void check_liquidity_protection_reset_request(void) {
  LiquidityProtectionResetRequest sent;
  LiquidityProtectionResetRequest got;
  uint8_t wire[29];
  uint8_t again[29];

  any_liquidity_protection_reset_request(&sent);
  assert(encode_liquidity_protection_reset_request(&sent, wire, 0) == 29);
  assert(decode_liquidity_protection_reset_request(&got, wire, 0) == 29);
  equal_liquidity_protection_reset_request(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_liquidity_protection_reset_request(&got, wire, 0) == 29);
  assert(encode_liquidity_protection_reset_request(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Liquidity Protection Reset Response: 10 bytes --------------------------- */

/* Response to the Liquidity Protection Reset Request */
typedef struct {
  uint8_t client_message_id[4];                       /* bytes 0 to 3 */
  uint8_t mpid[4];                                    /* bytes 4 to 7 */
  uint8_t simple_liquidity_protection_reset_status;   /* byte 8 */
  uint8_t complex_liquidity_protection_reset_status;  /* byte 9 */
} LiquidityProtectionResetResponse;

/* any Liquidity Protection Reset Response at all: every byte one the checker chooses */
static void any_liquidity_protection_reset_response(LiquidityProtectionResetResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->simple_liquidity_protection_reset_status = arbitrary();
  record->complex_liquidity_protection_reset_status = arbitrary();
}

/* Liquidity Protection Reset Response to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_liquidity_protection_reset_response(const LiquidityProtectionResetResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->simple_liquidity_protection_reset_status;
  wire[at++] = record->complex_liquidity_protection_reset_status;

  return at;
}

/* Liquidity Protection Reset Response off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_liquidity_protection_reset_response(LiquidityProtectionResetResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->simple_liquidity_protection_reset_status = wire[at++];
  record->complex_liquidity_protection_reset_status = wire[at++];

  return at;
}

/* what was read of Liquidity Protection Reset Response is what was written, byte for byte */
static void equal_liquidity_protection_reset_response(const LiquidityProtectionResetResponse *read, const LiquidityProtectionResetResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->simple_liquidity_protection_reset_status == written->simple_liquidity_protection_reset_status);
  assert(read->complex_liquidity_protection_reset_status == written->complex_liquidity_protection_reset_status);
}

/* Liquidity Protection Reset Response: written and read back, then read and written back */
static void check_liquidity_protection_reset_response(void) {
  LiquidityProtectionResetResponse sent;
  LiquidityProtectionResetResponse got;
  uint8_t wire[10];
  uint8_t again[10];

  any_liquidity_protection_reset_response(&sent);
  assert(encode_liquidity_protection_reset_response(&sent, wire, 0) == 10);
  assert(decode_liquidity_protection_reset_response(&got, wire, 0) == 10);
  equal_liquidity_protection_reset_response(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_liquidity_protection_reset_response(&got, wire, 0) == 10);
  assert(encode_liquidity_protection_reset_response(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Single Side Liquidity Protection Reset Request: 18 bytes ---------------- */

/* Request to reset Single Side Liquidity Protection for the specific Option or Complex Strategy. */
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

/* ---- Simple Quote Protection Trigger Notification: 24 bytes ------------------ */

/* This message format will be used to notify firms when an MPID is placed under simple quote protection. Simple Quote protection can be triggered due to any one of the reasons listed in the message below. */
typedef struct {
  uint8_t notification_time[8];   /* bytes 0 to 7 */
  uint8_t mpid[4];                /* bytes 8 to 11 */
  uint8_t underlying_symbol[11];  /* bytes 12 to 22 */
  uint8_t trigger_reason;         /* byte 23 */
} SimpleQuoteProtectionTriggerNotification;

/* any Simple Quote Protection Trigger Notification at all: every byte one the checker chooses */
static void any_simple_quote_protection_trigger_notification(SimpleQuoteProtectionTriggerNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->trigger_reason = arbitrary();
}

/* Simple Quote Protection Trigger Notification to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_simple_quote_protection_trigger_notification(const SimpleQuoteProtectionTriggerNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->trigger_reason;

  return at;
}

/* Simple Quote Protection Trigger Notification off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_simple_quote_protection_trigger_notification(SimpleQuoteProtectionTriggerNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->trigger_reason = wire[at++];

  return at;
}

/* what was read of Simple Quote Protection Trigger Notification is what was written, byte for byte */
static void equal_simple_quote_protection_trigger_notification(const SimpleQuoteProtectionTriggerNotification *read, const SimpleQuoteProtectionTriggerNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->trigger_reason == written->trigger_reason);
}

/* Simple Quote Protection Trigger Notification: written and read back, then read and written back */
static void check_simple_quote_protection_trigger_notification(void) {
  SimpleQuoteProtectionTriggerNotification sent;
  SimpleQuoteProtectionTriggerNotification got;
  uint8_t wire[24];
  uint8_t again[24];

  any_simple_quote_protection_trigger_notification(&sent);
  assert(encode_simple_quote_protection_trigger_notification(&sent, wire, 0) == 24);
  assert(decode_simple_quote_protection_trigger_notification(&got, wire, 0) == 24);
  equal_simple_quote_protection_trigger_notification(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_quote_protection_trigger_notification(&got, wire, 0) == 24);
  assert(encode_simple_quote_protection_trigger_notification(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Liquidity Protection Trigger Notification: 24 bytes ------------- */

/* This message format will be used to notify firms when an MPID is placed under complex liquidity protection. Complex Liquidity protection can be triggered due to any one of the reasons listed in the message below. */
typedef struct {
  uint8_t notification_time[8];   /* bytes 0 to 7 */
  uint8_t mpid[4];                /* bytes 8 to 11 */
  uint8_t underlying_symbol[11];  /* bytes 12 to 22 */
  uint8_t trigger_reason;         /* byte 23 */
} ComplexLiquidityProtectionTriggerNotification;

/* any Complex Liquidity Protection Trigger Notification at all: every byte one the checker chooses */
static void any_complex_liquidity_protection_trigger_notification(ComplexLiquidityProtectionTriggerNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->trigger_reason = arbitrary();
}

/* Complex Liquidity Protection Trigger Notification to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_complex_liquidity_protection_trigger_notification(const ComplexLiquidityProtectionTriggerNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->trigger_reason;

  return at;
}

/* Complex Liquidity Protection Trigger Notification off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_complex_liquidity_protection_trigger_notification(ComplexLiquidityProtectionTriggerNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->trigger_reason = wire[at++];

  return at;
}

/* what was read of Complex Liquidity Protection Trigger Notification is what was written, byte for byte */
static void equal_complex_liquidity_protection_trigger_notification(const ComplexLiquidityProtectionTriggerNotification *read, const ComplexLiquidityProtectionTriggerNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->trigger_reason == written->trigger_reason);
}

/* Complex Liquidity Protection Trigger Notification: written and read back, then read and written back */
static void check_complex_liquidity_protection_trigger_notification(void) {
  ComplexLiquidityProtectionTriggerNotification sent;
  ComplexLiquidityProtectionTriggerNotification got;
  uint8_t wire[24];
  uint8_t again[24];

  any_complex_liquidity_protection_trigger_notification(&sent);
  assert(encode_complex_liquidity_protection_trigger_notification(&sent, wire, 0) == 24);
  assert(decode_complex_liquidity_protection_trigger_notification(&got, wire, 0) == 24);
  equal_complex_liquidity_protection_trigger_notification(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_liquidity_protection_trigger_notification(&got, wire, 0) == 24);
  assert(encode_complex_liquidity_protection_trigger_notification(&got, again, 0) == 24);
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
  check_simple_series_update();
  check_valid_quote_width_for_opening();
  check_simple_enhanced_quote_e_quote_response();
  check_complex_enhanced_quote_e_quote_response();
  check_system_state_notification();
  check_product_trading_status_notification();
  check_underlying_trading_status_notification();
  check_quote_width_relief_notification();
  check_simple_arm_protection_settings_notification();
  check_arm2_underlying_level_protection_settings_notification();
  check_single_side_liquidity_protection_trigger_notification();
  check_arm2_underlying_level_protection_notification();
  check_arm2_firm_level_protection_notification();
  check_cancel_notification();
  check_option_execution_notification();
  check_stock_leg_execution_notification();
  check_simple_arm_settings_update_request();
  check_simple_arm_settings_update_response();
  check_arm2_underlying_level_protection_settings_update_request();
  check_arm2_underlying_level_protection_settings_update_response();
  check_simple_enhanced_quote_e_quote_message();
  check_complex_enhanced_quote_e_quote_message();
  check_simple_mass_quote_cancel_request();
  check_simple_mass_quote_cancel_response();
  check_mass_liquidity_cancel_request_simple_and_complex();
  check_mass_liquidity_cancel_response();
  check_simple_quote_protection_reset_request();
  check_simple_quote_protection_reset_response();
  check_liquidity_protection_reset_request();
  check_liquidity_protection_reset_response();
  check_single_side_liquidity_protection_reset_request();
  check_single_side_liquidity_protection_reset_response();
  check_simple_quote_protection_trigger_notification();
  check_complex_liquidity_protection_trigger_notification();
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
