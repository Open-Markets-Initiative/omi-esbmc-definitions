// lseg/lse/mifid2posttrade/Lse_Mifid2PostTrade_v27_3.c
/*
 * London Stock Exchange MiFID II Post Trade
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

/* ---- Unit Header: 8 bytes ---------------------------------------------------- */

typedef struct {
  uint8_t length[2];           /* bytes 0 to 1 */
  uint8_t message_count;       /* byte 2 */
  uint8_t market_data_group;   /* byte 3 */
  uint8_t sequence_number[4];  /* bytes 4 to 7 */
} UnitHeader;

/* any Unit Header at all: every byte one the checker chooses */
static void any_unit_header(UnitHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->message_count = arbitrary();
  record->market_data_group = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Unit Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_unit_header(const UnitHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->message_count;
  wire[at++] = record->market_data_group;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Unit Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_unit_header(UnitHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->message_count = wire[at++];
  record->market_data_group = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Unit Header is what was written, byte for byte */
static void equal_unit_header(const UnitHeader *read, const UnitHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->message_count == written->message_count);
  assert(read->market_data_group == written->market_data_group);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Unit Header: written and read back, then read and written back */
static void check_unit_header(void) {
  UnitHeader sent;
  UnitHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_unit_header(&sent);
  assert(encode_unit_header(&sent, wire, 0) == 8);
  assert(decode_unit_header(&got, wire, 0) == 8);
  equal_unit_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_unit_header(&got, wire, 0) == 8);
  assert(encode_unit_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* Gtp Udp Message Header */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t message_type;       /* byte 2 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 3);
  assert(decode_message_header(&got, wire, 0) == 3);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 3);
  assert(encode_message_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 11 bytes ------------------------------------------ */

/* Sent to indicate the start and end of the day. */
typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t event_code;       /* byte 8 */
  uint8_t source_venue[2];  /* bytes 9 to 10 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
}

/* System Event Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }

  return at;
}

/* System Event Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event_code == written->event_code);
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 11);
  assert(decode_system_event_message(&got, wire, 0) == 11);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 11);
  assert(encode_system_event_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Status Message: 27 bytes ------------------------------------- */

/* Used to communicate scheduled and unscheduled session changes. When sent in the recovery channel, used to indicate the current trading status of an instrument. */
typedef struct {
  uint8_t timestamp[8];           /* bytes 0 to 7 */
  uint8_t instrument[8];          /* bytes 8 to 15 */
  uint8_t source_venue[2];        /* bytes 16 to 17 */
  uint8_t trading_status;         /* byte 18 */
  uint8_t session_change_reason;  /* byte 19 */
  uint8_t new_end_time[6];        /* bytes 20 to 25 */
  uint8_t order_book_type;        /* byte 26 */
} InstrumentStatusMessage;

/* any Instrument Status Message at all: every byte one the checker chooses */
static void any_instrument_status_message(InstrumentStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->session_change_reason = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->new_end_time[i] = arbitrary(); }
  record->order_book_type = arbitrary();
}

/* Instrument Status Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_instrument_status_message(const InstrumentStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->session_change_reason;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->new_end_time[i]; }
  wire[at++] = record->order_book_type;

  return at;
}

/* Instrument Status Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_instrument_status_message(InstrumentStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->session_change_reason = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->new_end_time[i] = wire[at++]; }
  record->order_book_type = wire[at++];

  return at;
}

/* what was read of Instrument Status Message is what was written, byte for byte */
static void equal_instrument_status_message(const InstrumentStatusMessage *read, const InstrumentStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->session_change_reason == written->session_change_reason);
  for (size_t i = 0; i < 6; i++) { assert(read->new_end_time[i] == written->new_end_time[i]); }
  assert(read->order_book_type == written->order_book_type);
}

/* Instrument Status Message: written and read back, then read and written back */
static void check_instrument_status_message(void) {
  InstrumentStatusMessage sent;
  InstrumentStatusMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_instrument_status_message(&sent);
  assert(encode_instrument_status_message(&sent, wire, 0) == 27);
  assert(decode_instrument_status_message(&got, wire, 0) == 27);
  equal_instrument_status_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_status_message(&got, wire, 0) == 27);
  assert(encode_instrument_status_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mifid Ii Trade Message: 289 bytes --------------------------------------- */

/* Sent to represent different types of MiFID compliant trades published by markets. */
typedef struct {
  uint8_t timestamp[8];                            /* bytes 0 to 7 */
  uint8_t source_venue[2];                         /* bytes 8 to 9 */
  uint8_t instrument[8];                           /* bytes 10 to 17 */
  uint8_t transaction_identification_code[52];     /* bytes 18 to 69 */
  uint8_t mifid_trade_type;                        /* byte 70 */
  uint8_t auction_type;                            /* byte 71 */
  uint8_t mifid_price[20];                         /* bytes 72 to 91 */
  uint8_t mifid_quantity[20];                      /* bytes 92 to 111 */
  uint8_t trading_date_and_time[30];               /* bytes 112 to 141 */
  uint8_t instrument_identification_code_type[4];  /* bytes 142 to 145 */
  uint8_t instrument_identification_code[12];      /* bytes 146 to 157 */
  uint8_t price_notation[4];                       /* bytes 158 to 161 */
  uint8_t price_major_currency[3];                 /* bytes 162 to 164 */
  uint8_t notional_amount[20];                     /* bytes 165 to 184 */
  uint8_t notional_currency[3];                    /* bytes 185 to 187 */
  uint8_t venue_of_execution[4];                   /* bytes 188 to 191 */
  uint8_t publication_date_and_time[30];           /* bytes 192 to 221 */
  uint8_t pt_ref_price_waiver_flag[4];             /* bytes 222 to 225 */
  uint8_t trading_system[4];                       /* bytes 226 to 229 */
  uint8_t market_closing_price_flag[4];            /* bytes 230 to 233 */
  uint8_t pt_algo_trade[4];                        /* bytes 234 to 237 */
  uint8_t pt_cancellation_flag[4];                 /* bytes 238 to 241 */
  uint8_t pt_amendment_flag[4];                    /* bytes 242 to 245 */
  uint8_t reserved_1;                              /* byte 246 */
  uint8_t reserved_3[3];                           /* bytes 247 to 249 */
  uint8_t reserved_20[20];                         /* bytes 250 to 269 */
  uint8_t reserved_4[4];                           /* bytes 270 to 273 */
  uint8_t trade_qualifier;                         /* byte 274 */
  uint8_t market_mechanism;                        /* byte 275 */
  uint8_t trading_mode;                            /* byte 276 */
  uint8_t transaction_category;                    /* byte 277 */
  uint8_t negotiation_indicator;                   /* byte 278 */
  uint8_t agency_cross_indicator;                  /* byte 279 */
  uint8_t modification_indicator;                  /* byte 280 */
  uint8_t reference_price_indicator;               /* byte 281 */
  uint8_t special_dividend_indicator;              /* byte 282 */
  uint8_t off_book_automated_indicator;            /* byte 283 */
  uint8_t price_formation_indicator;               /* byte 284 */
  uint8_t algorithmic_indicator;                   /* byte 285 */
  uint8_t post_trade_deferral_reason;              /* byte 286 */
  uint8_t deferral_enrichment_type;                /* byte 287 */
  uint8_t duplicative_indicator;                   /* byte 288 */
} MifidIiTradeMessage;

/* any Mifid Ii Trade Message at all: every byte one the checker chooses */
static void any_mifid_ii_trade_message(MifidIiTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->transaction_identification_code[i] = arbitrary(); }
  record->mifid_trade_type = arbitrary();
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->mifid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mifid_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->trading_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_identification_code_type[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->instrument_identification_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->price_major_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->notional_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->publication_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_ref_price_waiver_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_system[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_closing_price_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_algo_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_cancellation_flag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pt_amendment_flag[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->reserved_20[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  record->trade_qualifier = arbitrary();
  record->market_mechanism = arbitrary();
  record->trading_mode = arbitrary();
  record->transaction_category = arbitrary();
  record->negotiation_indicator = arbitrary();
  record->agency_cross_indicator = arbitrary();
  record->modification_indicator = arbitrary();
  record->reference_price_indicator = arbitrary();
  record->special_dividend_indicator = arbitrary();
  record->off_book_automated_indicator = arbitrary();
  record->price_formation_indicator = arbitrary();
  record->algorithmic_indicator = arbitrary();
  record->post_trade_deferral_reason = arbitrary();
  record->deferral_enrichment_type = arbitrary();
  record->duplicative_indicator = arbitrary();
}

/* Mifid Ii Trade Message to the wire: 289 bytes from at, returning where the next byte goes */
static size_t encode_mifid_ii_trade_message(const MifidIiTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->transaction_identification_code[i]; }
  wire[at++] = record->mifid_trade_type;
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mifid_price[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mifid_quantity[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->trading_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_identification_code_type[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->instrument_identification_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_notation[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->price_major_currency[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->notional_amount[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->notional_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->venue_of_execution[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->publication_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_ref_price_waiver_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_system[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_closing_price_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_algo_trade[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_cancellation_flag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pt_amendment_flag[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->reserved_20[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  wire[at++] = record->trade_qualifier;
  wire[at++] = record->market_mechanism;
  wire[at++] = record->trading_mode;
  wire[at++] = record->transaction_category;
  wire[at++] = record->negotiation_indicator;
  wire[at++] = record->agency_cross_indicator;
  wire[at++] = record->modification_indicator;
  wire[at++] = record->reference_price_indicator;
  wire[at++] = record->special_dividend_indicator;
  wire[at++] = record->off_book_automated_indicator;
  wire[at++] = record->price_formation_indicator;
  wire[at++] = record->algorithmic_indicator;
  wire[at++] = record->post_trade_deferral_reason;
  wire[at++] = record->deferral_enrichment_type;
  wire[at++] = record->duplicative_indicator;

  return at;
}

/* Mifid Ii Trade Message off the wire: 289 bytes from at, returning where the next byte lies */
static size_t decode_mifid_ii_trade_message(MifidIiTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->transaction_identification_code[i] = wire[at++]; }
  record->mifid_trade_type = wire[at++];
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->mifid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mifid_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->trading_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_identification_code_type[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->instrument_identification_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->price_major_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->notional_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->notional_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->venue_of_execution[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->publication_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_ref_price_waiver_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_system[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_closing_price_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_algo_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_cancellation_flag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pt_amendment_flag[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->reserved_20[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  record->trade_qualifier = wire[at++];
  record->market_mechanism = wire[at++];
  record->trading_mode = wire[at++];
  record->transaction_category = wire[at++];
  record->negotiation_indicator = wire[at++];
  record->agency_cross_indicator = wire[at++];
  record->modification_indicator = wire[at++];
  record->reference_price_indicator = wire[at++];
  record->special_dividend_indicator = wire[at++];
  record->off_book_automated_indicator = wire[at++];
  record->price_formation_indicator = wire[at++];
  record->algorithmic_indicator = wire[at++];
  record->post_trade_deferral_reason = wire[at++];
  record->deferral_enrichment_type = wire[at++];
  record->duplicative_indicator = wire[at++];

  return at;
}

/* what was read of Mifid Ii Trade Message is what was written, byte for byte */
static void equal_mifid_ii_trade_message(const MifidIiTradeMessage *read, const MifidIiTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->transaction_identification_code[i] == written->transaction_identification_code[i]); }
  assert(read->mifid_trade_type == written->mifid_trade_type);
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 20; i++) { assert(read->mifid_price[i] == written->mifid_price[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mifid_quantity[i] == written->mifid_quantity[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->trading_date_and_time[i] == written->trading_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_identification_code_type[i] == written->instrument_identification_code_type[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->instrument_identification_code[i] == written->instrument_identification_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_notation[i] == written->price_notation[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->price_major_currency[i] == written->price_major_currency[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->notional_amount[i] == written->notional_amount[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->notional_currency[i] == written->notional_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->venue_of_execution[i] == written->venue_of_execution[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->publication_date_and_time[i] == written->publication_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_ref_price_waiver_flag[i] == written->pt_ref_price_waiver_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_system[i] == written->trading_system[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_closing_price_flag[i] == written->market_closing_price_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_algo_trade[i] == written->pt_algo_trade[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_cancellation_flag[i] == written->pt_cancellation_flag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pt_amendment_flag[i] == written->pt_amendment_flag[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->reserved_20[i] == written->reserved_20[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  assert(read->trade_qualifier == written->trade_qualifier);
  assert(read->market_mechanism == written->market_mechanism);
  assert(read->trading_mode == written->trading_mode);
  assert(read->transaction_category == written->transaction_category);
  assert(read->negotiation_indicator == written->negotiation_indicator);
  assert(read->agency_cross_indicator == written->agency_cross_indicator);
  assert(read->modification_indicator == written->modification_indicator);
  assert(read->reference_price_indicator == written->reference_price_indicator);
  assert(read->special_dividend_indicator == written->special_dividend_indicator);
  assert(read->off_book_automated_indicator == written->off_book_automated_indicator);
  assert(read->price_formation_indicator == written->price_formation_indicator);
  assert(read->algorithmic_indicator == written->algorithmic_indicator);
  assert(read->post_trade_deferral_reason == written->post_trade_deferral_reason);
  assert(read->deferral_enrichment_type == written->deferral_enrichment_type);
  assert(read->duplicative_indicator == written->duplicative_indicator);
}

/* Mifid Ii Trade Message: written and read back, then read and written back */
static void check_mifid_ii_trade_message(void) {
  MifidIiTradeMessage sent;
  MifidIiTradeMessage got;
  uint8_t wire[289];
  uint8_t again[289];

  any_mifid_ii_trade_message(&sent);
  assert(encode_mifid_ii_trade_message(&sent, wire, 0) == 289);
  assert(decode_mifid_ii_trade_message(&got, wire, 0) == 289);
  equal_mifid_ii_trade_message(&got, &sent);

  for (size_t i = 0; i < 289; i++) { wire[i] = arbitrary(); }
  assert(decode_mifid_ii_trade_message(&got, wire, 0) == 289);
  assert(encode_mifid_ii_trade_message(&got, again, 0) == 289);
  for (size_t i = 0; i < 289; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_unit_header();
  check_message_header();
  check_system_event_message();
  check_instrument_status_message();
  check_mifid_ii_trade_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
