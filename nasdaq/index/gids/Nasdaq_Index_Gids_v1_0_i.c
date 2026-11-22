// nasdaq/index/gids/Nasdaq_Index_Gids_v1_0_i.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Global Index Data Service
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
 *   - the dispatch that chooses a message by its type
 *   - a run counted by a field
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

/* ---- Packet Header: 20 bytes ------------------------------------------------- */

/* Itch Mold Udp 64 Packet Header */
typedef struct {
  uint8_t session[10];         /* bytes 0 to 9 */
  uint8_t sequence_number[8];  /* bytes 10 to 17 */
  uint8_t message_count[2];    /* bytes 18 to 19 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = arbitrary(); }
}

/* Packet Header to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_count[i]; }

  return at;
}

/* Packet Header off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_count[i] == written->message_count[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[20];
  uint8_t again[20];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 20);
  assert(decode_packet_header(&got, wire, 0) == 20);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 20);
  assert(encode_packet_header(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* Mold Udp 64 Message Header */
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

/* ---- Timestamp Seconds Message: 4 bytes -------------------------------------- */

/* For every second during which there is at least one payload message, the seconds since the Unix epoch. */
typedef struct {
  uint8_t second[4];  /* bytes 0 to 3 */
} TimestampSecondsMessage;

/* any Timestamp Seconds Message at all: every byte one the checker chooses */
static void any_timestamp_seconds_message(TimestampSecondsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = arbitrary(); }
}

/* Timestamp Seconds Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_timestamp_seconds_message(const TimestampSecondsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second[i]; }

  return at;
}

/* Timestamp Seconds Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_timestamp_seconds_message(TimestampSecondsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = wire[at++]; }

  return at;
}

/* what was read of Timestamp Seconds Message is what was written, byte for byte */
static void equal_timestamp_seconds_message(const TimestampSecondsMessage *read, const TimestampSecondsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->second[i] == written->second[i]); }
}

/* Timestamp Seconds Message: written and read back, then read and written back */
static void check_timestamp_seconds_message(void) {
  TimestampSecondsMessage sent;
  TimestampSecondsMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_timestamp_seconds_message(&sent);
  assert(encode_timestamp_seconds_message(&sent, wire, 0) == 4);
  assert(decode_timestamp_seconds_message(&got, wire, 0) == 4);
  equal_timestamp_seconds_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_timestamp_seconds_message(&got, wire, 0) == 4);
  assert(encode_timestamp_seconds_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 8 bytes ------------------------------------------- */

/* Signals a data feed handler event. */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t event_code;      /* byte 4 */
  uint8_t schedule[3];     /* bytes 5 to 7 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  record->event_code = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->schedule[i] = arbitrary(); }
}

/* System Event Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  wire[at++] = record->event_code;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->schedule[i]; }

  return at;
}

/* System Event Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  record->event_code = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->schedule[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  assert(read->event_code == written->event_code);
  for (size_t i = 0; i < 3; i++) { assert(read->schedule[i] == written->schedule[i]); }
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 8);
  assert(decode_system_event_message(&got, wire, 0) == 8);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 8);
  assert(encode_system_event_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Intraday Index Value Message: 40 bytes ---------------------------------- */

/* The Intraday Index Value for a given instrument, disseminated at a defined frequency and schedule. */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t financial_product_type;  /* byte 4 */
  uint8_t brand[2];                /* bytes 5 to 6 */
  uint8_t series[3];               /* bytes 7 to 9 */
  uint8_t instrument_id[18];       /* bytes 10 to 27 */
  uint8_t tick_value[8];           /* bytes 28 to 35 */
  uint8_t tick_direction;          /* byte 36 */
  uint8_t currency[3];             /* bytes 37 to 39 */
} IntradayIndexValueMessage;

/* any Intraday Index Value Message at all: every byte one the checker chooses */
static void any_intraday_index_value_message(IntradayIndexValueMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  record->financial_product_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->brand[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tick_value[i] = arbitrary(); }
  record->tick_direction = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
}

/* Intraday Index Value Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_intraday_index_value_message(const IntradayIndexValueMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  wire[at++] = record->financial_product_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->brand[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_value[i]; }
  wire[at++] = record->tick_direction;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }

  return at;
}

/* Intraday Index Value Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_intraday_index_value_message(IntradayIndexValueMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  record->financial_product_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->brand[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tick_value[i] = wire[at++]; }
  record->tick_direction = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }

  return at;
}

/* what was read of Intraday Index Value Message is what was written, byte for byte */
static void equal_intraday_index_value_message(const IntradayIndexValueMessage *read, const IntradayIndexValueMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  assert(read->financial_product_type == written->financial_product_type);
  for (size_t i = 0; i < 2; i++) { assert(read->brand[i] == written->brand[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tick_value[i] == written->tick_value[i]); }
  assert(read->tick_direction == written->tick_direction);
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
}

/* Intraday Index Value Message: written and read back, then read and written back */
static void check_intraday_index_value_message(void) {
  IntradayIndexValueMessage sent;
  IntradayIndexValueMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_intraday_index_value_message(&sent);
  assert(encode_intraday_index_value_message(&sent, wire, 0) == 40);
  assert(decode_intraday_index_value_message(&got, wire, 0) == 40);
  equal_intraday_index_value_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_intraday_index_value_message(&got, wire, 0) == 40);
  assert(encode_intraday_index_value_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Settlement Value Message: 40 bytes -------------------------------------- */

/* Sends the official settlement price and settlement session used to settle cash derivatives on financial products when they expire. */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t financial_product_type;  /* byte 4 */
  uint8_t brand[2];                /* bytes 5 to 6 */
  uint8_t series[3];               /* bytes 7 to 9 */
  uint8_t instrument_id[18];       /* bytes 10 to 27 */
  uint8_t settlement_value[8];     /* bytes 28 to 35 */
  uint8_t settlement_type;         /* byte 36 */
  uint8_t currency[3];             /* bytes 37 to 39 */
} SettlementValueMessage;

/* any Settlement Value Message at all: every byte one the checker chooses */
static void any_settlement_value_message(SettlementValueMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  record->financial_product_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->brand[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_value[i] = arbitrary(); }
  record->settlement_type = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
}

/* Settlement Value Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_settlement_value_message(const SettlementValueMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  wire[at++] = record->financial_product_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->brand[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_value[i]; }
  wire[at++] = record->settlement_type;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }

  return at;
}

/* Settlement Value Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_settlement_value_message(SettlementValueMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  record->financial_product_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->brand[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_value[i] = wire[at++]; }
  record->settlement_type = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }

  return at;
}

/* what was read of Settlement Value Message is what was written, byte for byte */
static void equal_settlement_value_message(const SettlementValueMessage *read, const SettlementValueMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  assert(read->financial_product_type == written->financial_product_type);
  for (size_t i = 0; i < 2; i++) { assert(read->brand[i] == written->brand[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_value[i] == written->settlement_value[i]); }
  assert(read->settlement_type == written->settlement_type);
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
}

/* Settlement Value Message: written and read back, then read and written back */
static void check_settlement_value_message(void) {
  SettlementValueMessage sent;
  SettlementValueMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_settlement_value_message(&sent);
  assert(encode_settlement_value_message(&sent, wire, 0) == 40);
  assert(decode_settlement_value_message(&got, wire, 0) == 40);
  equal_settlement_value_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_settlement_value_message(&got, wire, 0) == 40);
  assert(encode_settlement_value_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Equities Summary Message: 78 bytes -------------------------------------- */

/* Relays the summary of the current trading day's activity for an equity index. */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t financial_product_type;  /* byte 4 */
  uint8_t brand[2];                /* bytes 5 to 6 */
  uint8_t series[3];               /* bytes 7 to 9 */
  uint8_t instrument_id[18];       /* bytes 10 to 27 */
  uint8_t summary_type[3];         /* bytes 28 to 30 */
  uint8_t sod_value[8];            /* bytes 31 to 38 */
  uint8_t high[8];                 /* bytes 39 to 46 */
  uint8_t low[8];                  /* bytes 47 to 54 */
  uint8_t eod_value[8];            /* bytes 55 to 62 */
  uint8_t net_change[8];           /* bytes 63 to 70 */
  uint8_t effective_date[4];       /* bytes 71 to 74 */
  uint8_t currency[3];             /* bytes 75 to 77 */
} EquitiesSummaryMessage;

/* any Equities Summary Message at all: every byte one the checker chooses */
static void any_equities_summary_message(EquitiesSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  record->financial_product_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->brand[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->summary_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sod_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->eod_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->net_change[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->effective_date[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
}

/* Equities Summary Message to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_equities_summary_message(const EquitiesSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  wire[at++] = record->financial_product_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->brand[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->summary_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sod_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->eod_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->net_change[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->effective_date[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }

  return at;
}

/* Equities Summary Message off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_equities_summary_message(EquitiesSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  record->financial_product_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->brand[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->summary_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sod_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->eod_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->net_change[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->effective_date[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }

  return at;
}

/* what was read of Equities Summary Message is what was written, byte for byte */
static void equal_equities_summary_message(const EquitiesSummaryMessage *read, const EquitiesSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  assert(read->financial_product_type == written->financial_product_type);
  for (size_t i = 0; i < 2; i++) { assert(read->brand[i] == written->brand[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->summary_type[i] == written->summary_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sod_value[i] == written->sod_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->eod_value[i] == written->eod_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->net_change[i] == written->net_change[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->effective_date[i] == written->effective_date[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
}

/* Equities Summary Message: written and read back, then read and written back */
static void check_equities_summary_message(void) {
  EquitiesSummaryMessage sent;
  EquitiesSummaryMessage got;
  uint8_t wire[78];
  uint8_t again[78];

  any_equities_summary_message(&sent);
  assert(encode_equities_summary_message(&sent, wire, 0) == 78);
  assert(decode_equities_summary_message(&got, wire, 0) == 78);
  equal_equities_summary_message(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_equities_summary_message(&got, wire, 0) == 78);
  assert(encode_equities_summary_message(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fixed Income Summary Message: 102 bytes --------------------------------- */

/* Relays the summary of the current trading day's activity for a fixed income index. */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t financial_product_type;  /* byte 4 */
  uint8_t brand[2];                /* bytes 5 to 6 */
  uint8_t series[3];               /* bytes 7 to 9 */
  uint8_t instrument_id[18];       /* bytes 10 to 27 */
  uint8_t summary_type[3];         /* bytes 28 to 30 */
  uint8_t sod_value[8];            /* bytes 31 to 38 */
  uint8_t high[8];                 /* bytes 39 to 46 */
  uint8_t low[8];                  /* bytes 47 to 54 */
  uint8_t eod_value[8];            /* bytes 55 to 62 */
  uint8_t net_change[8];           /* bytes 63 to 70 */
  uint8_t effective_date[4];       /* bytes 71 to 74 */
  uint8_t yield[8];                /* bytes 75 to 82 */
  uint8_t duration[8];             /* bytes 83 to 90 */
  uint8_t coupon[8];               /* bytes 91 to 98 */
  uint8_t currency[3];             /* bytes 99 to 101 */
} FixedIncomeSummaryMessage;

/* any Fixed Income Summary Message at all: every byte one the checker chooses */
static void any_fixed_income_summary_message(FixedIncomeSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  record->financial_product_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->brand[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->summary_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sod_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->eod_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->net_change[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->effective_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->yield[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->duration[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->coupon[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
}

/* Fixed Income Summary Message to the wire: 102 bytes from at, returning where the next byte goes */
static size_t encode_fixed_income_summary_message(const FixedIncomeSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  wire[at++] = record->financial_product_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->brand[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->summary_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sod_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->eod_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->net_change[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->effective_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->yield[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->duration[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->coupon[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }

  return at;
}

/* Fixed Income Summary Message off the wire: 102 bytes from at, returning where the next byte lies */
static size_t decode_fixed_income_summary_message(FixedIncomeSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  record->financial_product_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->brand[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->summary_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sod_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->eod_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->net_change[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->effective_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->yield[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->duration[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->coupon[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }

  return at;
}

/* what was read of Fixed Income Summary Message is what was written, byte for byte */
static void equal_fixed_income_summary_message(const FixedIncomeSummaryMessage *read, const FixedIncomeSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  assert(read->financial_product_type == written->financial_product_type);
  for (size_t i = 0; i < 2; i++) { assert(read->brand[i] == written->brand[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->summary_type[i] == written->summary_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sod_value[i] == written->sod_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->eod_value[i] == written->eod_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->net_change[i] == written->net_change[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->effective_date[i] == written->effective_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->yield[i] == written->yield[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->duration[i] == written->duration[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->coupon[i] == written->coupon[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
}

/* Fixed Income Summary Message: written and read back, then read and written back */
static void check_fixed_income_summary_message(void) {
  FixedIncomeSummaryMessage sent;
  FixedIncomeSummaryMessage got;
  uint8_t wire[102];
  uint8_t again[102];

  any_fixed_income_summary_message(&sent);
  assert(encode_fixed_income_summary_message(&sent, wire, 0) == 102);
  assert(decode_fixed_income_summary_message(&got, wire, 0) == 102);
  equal_fixed_income_summary_message(&got, &sent);

  for (size_t i = 0; i < 102; i++) { wire[i] = arbitrary(); }
  assert(decode_fixed_income_summary_message(&got, wire, 0) == 102);
  assert(encode_fixed_income_summary_message(&got, again, 0) == 102);
  for (size_t i = 0; i < 102; i++) { assert(again[i] == wire[i]); }
}

/* ---- Commodity Summary Message: 78 bytes ------------------------------------- */

/* Relays the summary of the current trading day's activity for a commodity index. */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t financial_product_type;  /* byte 4 */
  uint8_t brand[2];                /* bytes 5 to 6 */
  uint8_t series[3];               /* bytes 7 to 9 */
  uint8_t instrument_id[18];       /* bytes 10 to 27 */
  uint8_t summary_type[3];         /* bytes 28 to 30 */
  uint8_t sod_value[8];            /* bytes 31 to 38 */
  uint8_t high[8];                 /* bytes 39 to 46 */
  uint8_t low[8];                  /* bytes 47 to 54 */
  uint8_t eod_value[8];            /* bytes 55 to 62 */
  uint8_t net_change[8];           /* bytes 63 to 70 */
  uint8_t effective_date[4];       /* bytes 71 to 74 */
  uint8_t currency[3];             /* bytes 75 to 77 */
} CommoditySummaryMessage;

/* any Commodity Summary Message at all: every byte one the checker chooses */
static void any_commodity_summary_message(CommoditySummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  record->financial_product_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->brand[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->summary_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sod_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->eod_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->net_change[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->effective_date[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
}

/* Commodity Summary Message to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_commodity_summary_message(const CommoditySummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  wire[at++] = record->financial_product_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->brand[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->summary_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sod_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->eod_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->net_change[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->effective_date[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }

  return at;
}

/* Commodity Summary Message off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_commodity_summary_message(CommoditySummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  record->financial_product_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->brand[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->summary_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sod_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->eod_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->net_change[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->effective_date[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }

  return at;
}

/* what was read of Commodity Summary Message is what was written, byte for byte */
static void equal_commodity_summary_message(const CommoditySummaryMessage *read, const CommoditySummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  assert(read->financial_product_type == written->financial_product_type);
  for (size_t i = 0; i < 2; i++) { assert(read->brand[i] == written->brand[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->summary_type[i] == written->summary_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sod_value[i] == written->sod_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->eod_value[i] == written->eod_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->net_change[i] == written->net_change[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->effective_date[i] == written->effective_date[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
}

/* Commodity Summary Message: written and read back, then read and written back */
static void check_commodity_summary_message(void) {
  CommoditySummaryMessage sent;
  CommoditySummaryMessage got;
  uint8_t wire[78];
  uint8_t again[78];

  any_commodity_summary_message(&sent);
  assert(encode_commodity_summary_message(&sent, wire, 0) == 78);
  assert(decode_commodity_summary_message(&got, wire, 0) == 78);
  equal_commodity_summary_message(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_commodity_summary_message(&got, wire, 0) == 78);
  assert(encode_commodity_summary_message(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Etp Intra Day Valuation Message: 34 bytes ------------------------------- */

/* Disseminates the Intraday Portfolio Value (IPV) of an ETF or the Intra-Day Indicative Value (IIV) of an ETMF. */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t financial_product_type;  /* byte 4 */
  uint8_t ipv_symbol[18];          /* bytes 5 to 22 */
  uint8_t ipv_value[8];            /* bytes 23 to 30 */
  uint8_t currency[3];             /* bytes 31 to 33 */
} EtpIntraDayValuationMessage;

/* any Etp Intra Day Valuation Message at all: every byte one the checker chooses */
static void any_etp_intra_day_valuation_message(EtpIntraDayValuationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  record->financial_product_type = arbitrary();
  for (size_t i = 0; i < 18; i++) { record->ipv_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ipv_value[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
}

/* Etp Intra Day Valuation Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_etp_intra_day_valuation_message(const EtpIntraDayValuationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  wire[at++] = record->financial_product_type;
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->ipv_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ipv_value[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }

  return at;
}

/* Etp Intra Day Valuation Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_etp_intra_day_valuation_message(EtpIntraDayValuationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  record->financial_product_type = wire[at++];
  for (size_t i = 0; i < 18; i++) { record->ipv_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ipv_value[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }

  return at;
}

/* what was read of Etp Intra Day Valuation Message is what was written, byte for byte */
static void equal_etp_intra_day_valuation_message(const EtpIntraDayValuationMessage *read, const EtpIntraDayValuationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  assert(read->financial_product_type == written->financial_product_type);
  for (size_t i = 0; i < 18; i++) { assert(read->ipv_symbol[i] == written->ipv_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ipv_value[i] == written->ipv_value[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
}

/* Etp Intra Day Valuation Message: written and read back, then read and written back */
static void check_etp_intra_day_valuation_message(void) {
  EtpIntraDayValuationMessage sent;
  EtpIntraDayValuationMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_etp_intra_day_valuation_message(&sent);
  assert(encode_etp_intra_day_valuation_message(&sent, wire, 0) == 34);
  assert(decode_etp_intra_day_valuation_message(&got, wire, 0) == 34);
  equal_etp_intra_day_valuation_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_etp_intra_day_valuation_message(&got, wire, 0) == 34);
  assert(encode_etp_intra_day_valuation_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Etp Summary Message: 73 bytes ------------------------------------------- */

/* Relays the summary of the current trading day's IPV activity for an ETF or the IIV activity for an ETMF. */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t financial_product_type;  /* byte 4 */
  uint8_t summary_type[3];         /* bytes 5 to 7 */
  uint8_t ipv_or_iiv_symbol[18];   /* bytes 8 to 25 */
  uint8_t sod_value[8];            /* bytes 26 to 33 */
  uint8_t high[8];                 /* bytes 34 to 41 */
  uint8_t low[8];                  /* bytes 42 to 49 */
  uint8_t eod_value[8];            /* bytes 50 to 57 */
  uint8_t net_change[8];           /* bytes 58 to 65 */
  uint8_t effective_date[4];       /* bytes 66 to 69 */
  uint8_t currency[3];             /* bytes 70 to 72 */
} EtpSummaryMessage;

/* any Etp Summary Message at all: every byte one the checker chooses */
static void any_etp_summary_message(EtpSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  record->financial_product_type = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->summary_type[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->ipv_or_iiv_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sod_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->eod_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->net_change[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->effective_date[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
}

/* Etp Summary Message to the wire: 73 bytes from at, returning where the next byte goes */
static size_t encode_etp_summary_message(const EtpSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  wire[at++] = record->financial_product_type;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->summary_type[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->ipv_or_iiv_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sod_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->eod_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->net_change[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->effective_date[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }

  return at;
}

/* Etp Summary Message off the wire: 73 bytes from at, returning where the next byte lies */
static size_t decode_etp_summary_message(EtpSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  record->financial_product_type = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->summary_type[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->ipv_or_iiv_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sod_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->eod_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->net_change[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->effective_date[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }

  return at;
}

/* what was read of Etp Summary Message is what was written, byte for byte */
static void equal_etp_summary_message(const EtpSummaryMessage *read, const EtpSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  assert(read->financial_product_type == written->financial_product_type);
  for (size_t i = 0; i < 3; i++) { assert(read->summary_type[i] == written->summary_type[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->ipv_or_iiv_symbol[i] == written->ipv_or_iiv_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sod_value[i] == written->sod_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->eod_value[i] == written->eod_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->net_change[i] == written->net_change[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->effective_date[i] == written->effective_date[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
}

/* Etp Summary Message: written and read back, then read and written back */
static void check_etp_summary_message(void) {
  EtpSummaryMessage sent;
  EtpSummaryMessage got;
  uint8_t wire[73];
  uint8_t again[73];

  any_etp_summary_message(&sent);
  assert(encode_etp_summary_message(&sent, wire, 0) == 73);
  assert(decode_etp_summary_message(&got, wire, 0) == 73);
  equal_etp_summary_message(&got, &sent);

  for (size_t i = 0; i < 73; i++) { wire[i] = arbitrary(); }
  assert(decode_etp_summary_message(&got, wire, 0) == 73);
  assert(encode_etp_summary_message(&got, again, 0) == 73);
  for (size_t i = 0; i < 73; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_timestamp_seconds_message();
  check_system_event_message();
  check_intraday_index_value_message();
  check_settlement_value_message();
  check_equities_summary_message();
  check_fixed_income_summary_message();
  check_commodity_summary_message();
  check_etp_intra_day_valuation_message();
  check_etp_summary_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
