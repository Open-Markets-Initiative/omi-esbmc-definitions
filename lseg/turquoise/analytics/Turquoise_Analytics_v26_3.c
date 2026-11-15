// lseg/turquoise/analytics/Turquoise_Analytics_v26_3.c
/*
 * London Stock Exchange Analytics
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

/* Used to communicate scheduled and unscheduled session changes */
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

/* ---- Analytics Message: 106 bytes -------------------------------------------- */

/* Used to disseminate additional statistics including order book activity statistics */
typedef struct {
  uint8_t timestamp[8];                        /* bytes 0 to 7 */
  uint8_t instrument[8];                       /* bytes 8 to 15 */
  uint8_t source_venue[2];                     /* bytes 16 to 17 */
  uint8_t start_time[8];                       /* bytes 18 to 25 */
  uint8_t end_time[8];                         /* bytes 26 to 33 */
  uint8_t buy_order_count[4];                  /* bytes 34 to 37 */
  uint8_t sell_order_count[4];                 /* bytes 38 to 41 */
  uint8_t buy_order_size[8];                   /* bytes 42 to 49 */
  uint8_t sell_order_size[8];                  /* bytes 50 to 57 */
  uint8_t buy_order_cancellations[4];          /* bytes 58 to 61 */
  uint8_t sell_order_cancellations[4];         /* bytes 62 to 65 */
  uint8_t buy_limit_order_cancellations[4];    /* bytes 66 to 69 */
  uint8_t buy_market_order_cancellations[4];   /* bytes 70 to 73 */
  uint8_t sell_limit_order_cancellations[4];   /* bytes 74 to 77 */
  uint8_t sell_market_order_cancellations[4];  /* bytes 78 to 81 */
  uint8_t bid_ask_spread[8];                   /* bytes 82 to 89 */
  uint8_t vwap_buy[8];                         /* bytes 90 to 97 */
  uint8_t vwap_sell[8];                        /* bytes 98 to 105 */
} AnalyticsMessage;

/* any Analytics Message at all: every byte one the checker chooses */
static void any_analytics_message(AnalyticsMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->start_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buy_order_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sell_order_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_order_cancellations[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_order_cancellations[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_limit_order_cancellations[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_market_order_cancellations[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_limit_order_cancellations[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_market_order_cancellations[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_ask_spread[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap_buy[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap_sell[i] = arbitrary(); }
}

/* Analytics Message to the wire: 106 bytes from at, returning where the next byte goes */
static size_t encode_analytics_message(const AnalyticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_venue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->start_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_order_count[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_order_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buy_order_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sell_order_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_order_cancellations[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_order_cancellations[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_limit_order_cancellations[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_market_order_cancellations[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_limit_order_cancellations[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_market_order_cancellations[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_ask_spread[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap_buy[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap_sell[i]; }

  return at;
}

/* Analytics Message off the wire: 106 bytes from at, returning where the next byte lies */
static size_t decode_analytics_message(AnalyticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->start_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buy_order_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sell_order_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_order_cancellations[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_order_cancellations[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_limit_order_cancellations[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_market_order_cancellations[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_limit_order_cancellations[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_market_order_cancellations[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_ask_spread[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap_buy[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap_sell[i] = wire[at++]; }

  return at;
}

/* what was read of Analytics Message is what was written, byte for byte */
static void equal_analytics_message(const AnalyticsMessage *read, const AnalyticsMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_venue[i] == written->source_venue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->start_time[i] == written->start_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_time[i] == written->end_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_order_count[i] == written->buy_order_count[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_order_count[i] == written->sell_order_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buy_order_size[i] == written->buy_order_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sell_order_size[i] == written->sell_order_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_order_cancellations[i] == written->buy_order_cancellations[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_order_cancellations[i] == written->sell_order_cancellations[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_limit_order_cancellations[i] == written->buy_limit_order_cancellations[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_market_order_cancellations[i] == written->buy_market_order_cancellations[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_limit_order_cancellations[i] == written->sell_limit_order_cancellations[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_market_order_cancellations[i] == written->sell_market_order_cancellations[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_ask_spread[i] == written->bid_ask_spread[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap_buy[i] == written->vwap_buy[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap_sell[i] == written->vwap_sell[i]); }
}

/* Analytics Message: written and read back, then read and written back */
static void check_analytics_message(void) {
  AnalyticsMessage sent;
  AnalyticsMessage got;
  uint8_t wire[106];
  uint8_t again[106];

  any_analytics_message(&sent);
  assert(encode_analytics_message(&sent, wire, 0) == 106);
  assert(decode_analytics_message(&got, wire, 0) == 106);
  equal_analytics_message(&got, &sent);

  for (size_t i = 0; i < 106; i++) { wire[i] = arbitrary(); }
  assert(decode_analytics_message(&got, wire, 0) == 106);
  assert(encode_analytics_message(&got, again, 0) == 106);
  for (size_t i = 0; i < 106; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_unit_header();
  check_message_header();
  check_system_event_message();
  check_instrument_status_message();
  check_analytics_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
