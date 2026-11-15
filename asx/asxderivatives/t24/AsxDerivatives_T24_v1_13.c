// asx/asxderivatives/t24/AsxDerivatives_T24_v1_13.c
/*
 * Australian Securities Exchange 24 Itch
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
 *   - a run of a stated number of entries
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

/* ---- Session: 10 bytes ------------------------------------------------------- */

typedef struct {
  uint8_t protocol_version[3];  /* bytes 0 to 2 */
  uint8_t session_year[2];      /* bytes 3 to 4 */
  uint8_t session_week[2];      /* bytes 5 to 6 */
  uint8_t trading_service[3];   /* bytes 7 to 9 */
} Session;

/* any Session at all: every byte one the checker chooses */
static void any_session(Session *record) {
  for (size_t i = 0; i < 3; i++) { record->protocol_version[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_year[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_week[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trading_service[i] = arbitrary(); }
}

/* Session to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_session(const Session *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->protocol_version[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_year[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_week[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_service[i]; }

  return at;
}

/* Session off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_session(Session *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->protocol_version[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_year[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_week[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trading_service[i] = wire[at++]; }

  return at;
}

/* what was read of Session is what was written, byte for byte */
static void equal_session(const Session *read, const Session *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->protocol_version[i] == written->protocol_version[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_year[i] == written->session_year[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_week[i] == written->session_week[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trading_service[i] == written->trading_service[i]); }
}

/* Session: written and read back, then read and written back */
static void check_session(void) {
  Session sent;
  Session got;
  uint8_t wire[10];
  uint8_t again[10];

  any_session(&sent);
  assert(encode_session(&sent, wire, 0) == 10);
  assert(decode_session(&got, wire, 0) == 10);
  equal_session(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_session(&got, wire, 0) == 10);
  assert(encode_session(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Packet Header: 20 bytes ------------------------------------------------- */

/* Itch Mold Udp 64 Packet Header */
typedef struct {
  Session session;             /* bytes 0 to 9 */
  uint8_t sequence_number[8];  /* bytes 10 to 17 */
  uint8_t message_count[2];    /* bytes 18 to 19 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  any_session(&record->session);
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = arbitrary(); }
}

/* Packet Header to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  at = encode_session(&record->session, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_count[i]; }

  return at;
}

/* Packet Header off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  at = decode_session(&record->session, wire, at);
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_count[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  equal_session(&read->session, &written->session);
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

/* ---- Time Message: 4 bytes --------------------------------------------------- */

/* The server will, on each packet multicast, transmit this message for every second for which at least one application message is generated */
typedef struct {
  uint8_t second[4];  /* bytes 0 to 3 */
} TimeMessage;

/* any Time Message at all: every byte one the checker chooses */
static void any_time_message(TimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = arbitrary(); }
}

/* Time Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_time_message(const TimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second[i]; }

  return at;
}

/* Time Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_time_message(TimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = wire[at++]; }

  return at;
}

/* what was read of Time Message is what was written, byte for byte */
static void equal_time_message(const TimeMessage *read, const TimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->second[i] == written->second[i]); }
}

/* Time Message: written and read back, then read and written back */
static void check_time_message(void) {
  TimeMessage sent;
  TimeMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_time_message(&sent);
  assert(encode_time_message(&sent, wire, 0) == 4);
  assert(decode_time_message(&got, wire, 0) == 4);
  equal_time_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_time_message(&got, wire, 0) == 4);
  assert(encode_time_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 7 bytes ------------------------------------------- */

/* The system event message is used to signal a market or trading period event. */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t trade_date[2];   /* bytes 4 to 5 */
  uint8_t event_code;      /* byte 6 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  assert(read->event_code == written->event_code);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[7];
  uint8_t again[7];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 7);
  assert(decode_system_event_message(&got, wire, 0) == 7);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 7);
  assert(encode_system_event_message(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Future Symbol Directory Message: 53 bytes ------------------------------- */

/* As each product moves to the new Trade Date, ASX Trade24 will disseminate the future symbol messages defining the available futures, CFDs and Share Future contracts for each instrument. The action of disseminating this message will automatically imply the contract is in a “Pending” session state. */
typedef struct {
  uint8_t nanoseconds[4];                   /* bytes 0 to 3 */
  uint8_t trade_date[2];                    /* bytes 4 to 5 */
  uint8_t contract_number[4];               /* bytes 6 to 9 */
  uint8_t exchange[6];                      /* bytes 10 to 15 */
  uint8_t instrument[6];                    /* bytes 16 to 21 */
  uint8_t contract_type;                    /* byte 22 */
  uint8_t expiry_year[2];                   /* bytes 23 to 24 */
  uint8_t expiry_month;                     /* byte 25 */
  uint8_t price_decimal_position;           /* byte 26 */
  uint8_t price_fractional_denominator[4];  /* bytes 27 to 30 */
  uint8_t price_minimum_tick[2];            /* bytes 31 to 32 */
  uint8_t last_trading_date[4];             /* bytes 33 to 36 */
  uint8_t prior_day_settlement[4];          /* bytes 37 to 40 */
  uint8_t financial_type;                   /* byte 41 */
  uint8_t currency[3];                      /* bytes 42 to 44 */
  uint8_t lot_size_or_face_value[4];        /* bytes 45 to 48 */
  uint8_t maturity_value;                   /* byte 49 */
  uint8_t coupon_rate[2];                   /* bytes 50 to 51 */
  uint8_t payments_per_year;                /* byte 52 */
} FutureSymbolDirectoryMessage;

/* any Future Symbol Directory Message at all: every byte one the checker chooses */
static void any_future_symbol_directory_message(FutureSymbolDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->exchange[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->instrument[i] = arbitrary(); }
  record->contract_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->expiry_year[i] = arbitrary(); }
  record->expiry_month = arbitrary();
  record->price_decimal_position = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_fractional_denominator[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_minimum_tick[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->prior_day_settlement[i] = arbitrary(); }
  record->financial_type = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lot_size_or_face_value[i] = arbitrary(); }
  record->maturity_value = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->coupon_rate[i] = arbitrary(); }
  record->payments_per_year = arbitrary();
}

/* Future Symbol Directory Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_future_symbol_directory_message(const FutureSymbolDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->exchange[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->instrument[i]; }
  wire[at++] = record->contract_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiry_year[i]; }
  wire[at++] = record->expiry_month;
  wire[at++] = record->price_decimal_position;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_fractional_denominator[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_minimum_tick[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trading_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->prior_day_settlement[i]; }
  wire[at++] = record->financial_type;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lot_size_or_face_value[i]; }
  wire[at++] = record->maturity_value;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->coupon_rate[i]; }
  wire[at++] = record->payments_per_year;

  return at;
}

/* Future Symbol Directory Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_future_symbol_directory_message(FutureSymbolDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->exchange[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->instrument[i] = wire[at++]; }
  record->contract_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->expiry_year[i] = wire[at++]; }
  record->expiry_month = wire[at++];
  record->price_decimal_position = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_fractional_denominator[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_minimum_tick[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->prior_day_settlement[i] = wire[at++]; }
  record->financial_type = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lot_size_or_face_value[i] = wire[at++]; }
  record->maturity_value = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->coupon_rate[i] = wire[at++]; }
  record->payments_per_year = wire[at++];

  return at;
}

/* what was read of Future Symbol Directory Message is what was written, byte for byte */
static void equal_future_symbol_directory_message(const FutureSymbolDirectoryMessage *read, const FutureSymbolDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->exchange[i] == written->exchange[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->instrument[i] == written->instrument[i]); }
  assert(read->contract_type == written->contract_type);
  for (size_t i = 0; i < 2; i++) { assert(read->expiry_year[i] == written->expiry_year[i]); }
  assert(read->expiry_month == written->expiry_month);
  assert(read->price_decimal_position == written->price_decimal_position);
  for (size_t i = 0; i < 4; i++) { assert(read->price_fractional_denominator[i] == written->price_fractional_denominator[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_minimum_tick[i] == written->price_minimum_tick[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trading_date[i] == written->last_trading_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->prior_day_settlement[i] == written->prior_day_settlement[i]); }
  assert(read->financial_type == written->financial_type);
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lot_size_or_face_value[i] == written->lot_size_or_face_value[i]); }
  assert(read->maturity_value == written->maturity_value);
  for (size_t i = 0; i < 2; i++) { assert(read->coupon_rate[i] == written->coupon_rate[i]); }
  assert(read->payments_per_year == written->payments_per_year);
}

/* Future Symbol Directory Message: written and read back, then read and written back */
static void check_future_symbol_directory_message(void) {
  FutureSymbolDirectoryMessage sent;
  FutureSymbolDirectoryMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_future_symbol_directory_message(&sent);
  assert(encode_future_symbol_directory_message(&sent, wire, 0) == 53);
  assert(decode_future_symbol_directory_message(&got, wire, 0) == 53);
  equal_future_symbol_directory_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_future_symbol_directory_message(&got, wire, 0) == 53);
  assert(encode_future_symbol_directory_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spread Symbol Directory Message: 34 bytes ------------------------------- */

/* As each product moves to the new Trade Date, ASX Trade24 will disseminate the spread symbol messages defining the available calendar spread and inter-spread contracts. For contracts that are inter-spreads, the underlying legs are in the same Trade Date. */
typedef struct {
  uint8_t nanoseconds[4];                   /* bytes 0 to 3 */
  uint8_t trade_date[2];                    /* bytes 4 to 5 */
  uint8_t contract_number[4];               /* bytes 6 to 9 */
  uint8_t exchange[6];                      /* bytes 10 to 15 */
  uint8_t contract_type;                    /* byte 16 */
  uint8_t first_leg_contract_number[4];     /* bytes 17 to 20 */
  uint8_t second_leg_contract_number[4];    /* bytes 21 to 24 */
  uint8_t primary_ratio;                    /* byte 25 */
  uint8_t secondary_ratio;                  /* byte 26 */
  uint8_t price_decimal_position;           /* byte 27 */
  uint8_t price_fractional_denominator[4];  /* bytes 28 to 31 */
  uint8_t price_minimum_tick[2];            /* bytes 32 to 33 */
} SpreadSymbolDirectoryMessage;

/* any Spread Symbol Directory Message at all: every byte one the checker chooses */
static void any_spread_symbol_directory_message(SpreadSymbolDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->exchange[i] = arbitrary(); }
  record->contract_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->first_leg_contract_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->second_leg_contract_number[i] = arbitrary(); }
  record->primary_ratio = arbitrary();
  record->secondary_ratio = arbitrary();
  record->price_decimal_position = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_fractional_denominator[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_minimum_tick[i] = arbitrary(); }
}

/* Spread Symbol Directory Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_spread_symbol_directory_message(const SpreadSymbolDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->exchange[i]; }
  wire[at++] = record->contract_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_leg_contract_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second_leg_contract_number[i]; }
  wire[at++] = record->primary_ratio;
  wire[at++] = record->secondary_ratio;
  wire[at++] = record->price_decimal_position;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_fractional_denominator[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_minimum_tick[i]; }

  return at;
}

/* Spread Symbol Directory Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_spread_symbol_directory_message(SpreadSymbolDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->exchange[i] = wire[at++]; }
  record->contract_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->first_leg_contract_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->second_leg_contract_number[i] = wire[at++]; }
  record->primary_ratio = wire[at++];
  record->secondary_ratio = wire[at++];
  record->price_decimal_position = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_fractional_denominator[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_minimum_tick[i] = wire[at++]; }

  return at;
}

/* what was read of Spread Symbol Directory Message is what was written, byte for byte */
static void equal_spread_symbol_directory_message(const SpreadSymbolDirectoryMessage *read, const SpreadSymbolDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->exchange[i] == written->exchange[i]); }
  assert(read->contract_type == written->contract_type);
  for (size_t i = 0; i < 4; i++) { assert(read->first_leg_contract_number[i] == written->first_leg_contract_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->second_leg_contract_number[i] == written->second_leg_contract_number[i]); }
  assert(read->primary_ratio == written->primary_ratio);
  assert(read->secondary_ratio == written->secondary_ratio);
  assert(read->price_decimal_position == written->price_decimal_position);
  for (size_t i = 0; i < 4; i++) { assert(read->price_fractional_denominator[i] == written->price_fractional_denominator[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_minimum_tick[i] == written->price_minimum_tick[i]); }
}

/* Spread Symbol Directory Message: written and read back, then read and written back */
static void check_spread_symbol_directory_message(void) {
  SpreadSymbolDirectoryMessage sent;
  SpreadSymbolDirectoryMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_spread_symbol_directory_message(&sent);
  assert(encode_spread_symbol_directory_message(&sent, wire, 0) == 34);
  assert(decode_spread_symbol_directory_message(&got, wire, 0) == 34);
  equal_spread_symbol_directory_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_spread_symbol_directory_message(&got, wire, 0) == 34);
  assert(encode_spread_symbol_directory_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Option Symbol Directory Message: 74 bytes ------------------------------- */

/* As each product moves to the new Trade Date, ASX Trade24 will disseminate the option symbol messages defining all the available options contracts. For Single Session Options only, the exchange can activate or de-activate option symbols during the course of trading by issuing Order Book State messages for affected option contracts. If an option symbol is not active (Activated field is ‘N’) or is de-activated (Trading Status is “I”), reference to that option contract should be removed from the list of actively traded contracts. If an option symbol is active (Activated field is ‘Y’) or is activated (Trading Status is “A”), reference to that option contract should be added to the list of actively traded contracts. */
typedef struct {
  uint8_t nanoseconds[4];                          /* bytes 0 to 3 */
  uint8_t trade_date[2];                           /* bytes 4 to 5 */
  uint8_t contract_number[4];                      /* bytes 6 to 9 */
  uint8_t exchange[6];                             /* bytes 10 to 15 */
  uint8_t instrument[6];                           /* bytes 16 to 21 */
  uint8_t contract_type;                           /* byte 22 */
  uint8_t expiry_year[2];                          /* bytes 23 to 24 */
  uint8_t expiry_month;                            /* byte 25 */
  uint8_t option_type;                             /* byte 26 */
  uint8_t strike[4];                               /* bytes 27 to 30 */
  uint8_t underlying_contract_number[4];           /* bytes 31 to 34 */
  uint8_t price_decimal_position;                  /* byte 35 */
  uint8_t price_fractional_denominator[4];         /* bytes 36 to 39 */
  uint8_t price_minimum_tick[2];                   /* bytes 40 to 41 */
  uint8_t strike_price_decimal_position;           /* byte 42 */
  uint8_t strike_price_fractional_denominator[4];  /* bytes 43 to 46 */
  uint8_t strike_price_minimum_tick[2];            /* bytes 47 to 48 */
  uint8_t last_trading_date[4];                    /* bytes 49 to 52 */
  uint8_t prior_day_settlement[4];                 /* bytes 53 to 56 */
  uint8_t volatility[4];                           /* bytes 57 to 60 */
  uint8_t financial_type;                          /* byte 61 */
  uint8_t currency[3];                             /* bytes 62 to 64 */
  uint8_t lot_size_or_face_value[4];               /* bytes 65 to 68 */
  uint8_t maturity_value;                          /* byte 69 */
  uint8_t coupon_rate[2];                          /* bytes 70 to 71 */
  uint8_t payments_per_year;                       /* byte 72 */
  uint8_t activated;                               /* byte 73 */
} OptionSymbolDirectoryMessage;

/* any Option Symbol Directory Message at all: every byte one the checker chooses */
static void any_option_symbol_directory_message(OptionSymbolDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->exchange[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->instrument[i] = arbitrary(); }
  record->contract_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->expiry_year[i] = arbitrary(); }
  record->expiry_month = arbitrary();
  record->option_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strike[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_contract_number[i] = arbitrary(); }
  record->price_decimal_position = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_fractional_denominator[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_minimum_tick[i] = arbitrary(); }
  record->strike_price_decimal_position = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strike_price_fractional_denominator[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->strike_price_minimum_tick[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->prior_day_settlement[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volatility[i] = arbitrary(); }
  record->financial_type = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lot_size_or_face_value[i] = arbitrary(); }
  record->maturity_value = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->coupon_rate[i] = arbitrary(); }
  record->payments_per_year = arbitrary();
  record->activated = arbitrary();
}

/* Option Symbol Directory Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_option_symbol_directory_message(const OptionSymbolDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->exchange[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->instrument[i]; }
  wire[at++] = record->contract_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiry_year[i]; }
  wire[at++] = record->expiry_month;
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_contract_number[i]; }
  wire[at++] = record->price_decimal_position;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_fractional_denominator[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_minimum_tick[i]; }
  wire[at++] = record->strike_price_decimal_position;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price_fractional_denominator[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->strike_price_minimum_tick[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trading_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->prior_day_settlement[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volatility[i]; }
  wire[at++] = record->financial_type;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lot_size_or_face_value[i]; }
  wire[at++] = record->maturity_value;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->coupon_rate[i]; }
  wire[at++] = record->payments_per_year;
  wire[at++] = record->activated;

  return at;
}

/* Option Symbol Directory Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_option_symbol_directory_message(OptionSymbolDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->exchange[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->instrument[i] = wire[at++]; }
  record->contract_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->expiry_year[i] = wire[at++]; }
  record->expiry_month = wire[at++];
  record->option_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strike[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_contract_number[i] = wire[at++]; }
  record->price_decimal_position = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_fractional_denominator[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_minimum_tick[i] = wire[at++]; }
  record->strike_price_decimal_position = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strike_price_fractional_denominator[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->strike_price_minimum_tick[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->prior_day_settlement[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volatility[i] = wire[at++]; }
  record->financial_type = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lot_size_or_face_value[i] = wire[at++]; }
  record->maturity_value = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->coupon_rate[i] = wire[at++]; }
  record->payments_per_year = wire[at++];
  record->activated = wire[at++];

  return at;
}

/* what was read of Option Symbol Directory Message is what was written, byte for byte */
static void equal_option_symbol_directory_message(const OptionSymbolDirectoryMessage *read, const OptionSymbolDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->exchange[i] == written->exchange[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->instrument[i] == written->instrument[i]); }
  assert(read->contract_type == written->contract_type);
  for (size_t i = 0; i < 2; i++) { assert(read->expiry_year[i] == written->expiry_year[i]); }
  assert(read->expiry_month == written->expiry_month);
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 4; i++) { assert(read->strike[i] == written->strike[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_contract_number[i] == written->underlying_contract_number[i]); }
  assert(read->price_decimal_position == written->price_decimal_position);
  for (size_t i = 0; i < 4; i++) { assert(read->price_fractional_denominator[i] == written->price_fractional_denominator[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_minimum_tick[i] == written->price_minimum_tick[i]); }
  assert(read->strike_price_decimal_position == written->strike_price_decimal_position);
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price_fractional_denominator[i] == written->strike_price_fractional_denominator[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->strike_price_minimum_tick[i] == written->strike_price_minimum_tick[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trading_date[i] == written->last_trading_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->prior_day_settlement[i] == written->prior_day_settlement[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volatility[i] == written->volatility[i]); }
  assert(read->financial_type == written->financial_type);
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lot_size_or_face_value[i] == written->lot_size_or_face_value[i]); }
  assert(read->maturity_value == written->maturity_value);
  for (size_t i = 0; i < 2; i++) { assert(read->coupon_rate[i] == written->coupon_rate[i]); }
  assert(read->payments_per_year == written->payments_per_year);
  assert(read->activated == written->activated);
}

/* Option Symbol Directory Message: written and read back, then read and written back */
static void check_option_symbol_directory_message(void) {
  OptionSymbolDirectoryMessage sent;
  OptionSymbolDirectoryMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_option_symbol_directory_message(&sent);
  assert(encode_option_symbol_directory_message(&sent, wire, 0) == 74);
  assert(decode_option_symbol_directory_message(&got, wire, 0) == 74);
  equal_option_symbol_directory_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_option_symbol_directory_message(&got, wire, 0) == 74);
  assert(encode_option_symbol_directory_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book State Message: 11 bytes -------------------------------------- */

/* ASX Trade24 uses this message to indicate the current session state of a contract to the market. */
typedef struct {
  uint8_t nanoseconds[4];      /* bytes 0 to 3 */
  uint8_t trade_date[2];       /* bytes 4 to 5 */
  uint8_t contract_number[4];  /* bytes 6 to 9 */
  uint8_t trading_status;      /* byte 10 */
} OrderBookStateMessage;

/* any Order Book State Message at all: every byte one the checker chooses */
static void any_order_book_state_message(OrderBookStateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  record->trading_status = arbitrary();
}

/* Order Book State Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_order_book_state_message(const OrderBookStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  wire[at++] = record->trading_status;

  return at;
}

/* Order Book State Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_order_book_state_message(OrderBookStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  record->trading_status = wire[at++];

  return at;
}

/* what was read of Order Book State Message is what was written, byte for byte */
static void equal_order_book_state_message(const OrderBookStateMessage *read, const OrderBookStateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  assert(read->trading_status == written->trading_status);
}

/* Order Book State Message: written and read back, then read and written back */
static void check_order_book_state_message(void) {
  OrderBookStateMessage sent;
  OrderBookStateMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_order_book_state_message(&sent);
  assert(encode_order_book_state_message(&sent, wire, 0) == 11);
  assert(decode_order_book_state_message(&got, wire, 0) == 11);
  equal_order_book_state_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_state_message(&got, wire, 0) == 11);
  assert(encode_order_book_state_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Added Message: 31 bytes ------------------------------------------- */

/* An Order Added message indicates a new order has been accepted by the ASX Trade24 system and was added to the order book. All orders in ASX Trade24 are anonymous and one “Add” type is supported for “real” orders that are not custom market orders. The message is referenced by an Order Number assigned by ASX Trade24 and is unique for the life of the order. */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t trade_date[2];           /* bytes 4 to 5 */
  uint8_t contract_number[4];      /* bytes 6 to 9 */
  uint8_t side;                    /* byte 10 */
  uint8_t order_number[8];         /* bytes 11 to 18 */
  uint8_t order_book_priority[4];  /* bytes 19 to 22 */
  uint8_t quantity[4];             /* bytes 23 to 26 */
  uint8_t price[4];                /* bytes 27 to 30 */
} OrderAddedMessage;

/* any Order Added Message at all: every byte one the checker chooses */
static void any_order_added_message(OrderAddedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_priority[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Order Added Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_order_added_message(const OrderAddedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_priority[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Added Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_order_added_message(OrderAddedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_priority[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Added Message is what was written, byte for byte */
static void equal_order_added_message(const OrderAddedMessage *read, const OrderAddedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_priority[i] == written->order_book_priority[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Added Message: written and read back, then read and written back */
static void check_order_added_message(void) {
  OrderAddedMessage sent;
  OrderAddedMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_order_added_message(&sent);
  assert(encode_order_added_message(&sent, wire, 0) == 31);
  assert(decode_order_added_message(&got, wire, 0) == 31);
  equal_order_added_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_order_added_message(&got, wire, 0) == 31);
  assert(encode_order_added_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replaced Message: 31 bytes ---------------------------------------- */

/* This message is sent whenever an order in the book has been modified for price or volume where the priority changes. Even though the side and contract number cannot be changed, these fields are included in the message to provide fast look-up. */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t trade_date[2];           /* bytes 4 to 5 */
  uint8_t contract_number[4];      /* bytes 6 to 9 */
  uint8_t side;                    /* byte 10 */
  uint8_t order_number[8];         /* bytes 11 to 18 */
  uint8_t order_book_priority[4];  /* bytes 19 to 22 */
  uint8_t quantity[4];             /* bytes 23 to 26 */
  uint8_t price[4];                /* bytes 27 to 30 */
} OrderReplacedMessage;

/* any Order Replaced Message at all: every byte one the checker chooses */
static void any_order_replaced_message(OrderReplacedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_priority[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Order Replaced Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_order_replaced_message(const OrderReplacedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_priority[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Replaced Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_order_replaced_message(OrderReplacedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_priority[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replaced Message is what was written, byte for byte */
static void equal_order_replaced_message(const OrderReplacedMessage *read, const OrderReplacedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_priority[i] == written->order_book_priority[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Replaced Message: written and read back, then read and written back */
static void check_order_replaced_message(void) {
  OrderReplacedMessage sent;
  OrderReplacedMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_order_replaced_message(&sent);
  assert(encode_order_replaced_message(&sent, wire, 0) == 31);
  assert(decode_order_replaced_message(&got, wire, 0) == 31);
  equal_order_replaced_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replaced_message(&got, wire, 0) == 31);
  assert(encode_order_replaced_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Volume Cancelled Message: 23 bytes -------------------------------- */

/* This message is sent whenever an order in the book is modified as a result of a partial cancellation of volume. The difference between this message and the Order Replaced is an Order Replaced will always show a change of order book priority in regards to the order’s position in the queue. An Order Volume Cancelled message is not sent when an order has partially traded. */
typedef struct {
  uint8_t nanoseconds[4];      /* bytes 0 to 3 */
  uint8_t trade_date[2];       /* bytes 4 to 5 */
  uint8_t contract_number[4];  /* bytes 6 to 9 */
  uint8_t side;                /* byte 10 */
  uint8_t order_number[8];     /* bytes 11 to 18 */
  uint8_t quantity[4];         /* bytes 19 to 22 */
} OrderVolumeCancelledMessage;

/* any Order Volume Cancelled Message at all: every byte one the checker chooses */
static void any_order_volume_cancelled_message(OrderVolumeCancelledMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
}

/* Order Volume Cancelled Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_order_volume_cancelled_message(const OrderVolumeCancelledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Order Volume Cancelled Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_order_volume_cancelled_message(OrderVolumeCancelledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Order Volume Cancelled Message is what was written, byte for byte */
static void equal_order_volume_cancelled_message(const OrderVolumeCancelledMessage *read, const OrderVolumeCancelledMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Order Volume Cancelled Message: written and read back, then read and written back */
static void check_order_volume_cancelled_message(void) {
  OrderVolumeCancelledMessage sent;
  OrderVolumeCancelledMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_order_volume_cancelled_message(&sent);
  assert(encode_order_volume_cancelled_message(&sent, wire, 0) == 23);
  assert(decode_order_volume_cancelled_message(&got, wire, 0) == 23);
  equal_order_volume_cancelled_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_order_volume_cancelled_message(&got, wire, 0) == 23);
  assert(encode_order_volume_cancelled_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Deleted Message: 19 bytes ----------------------------------------- */

/* This message is sent whenever an order in the book is cancelled by the owner, expired, cancelled by the exchange, purged or volume cancelled. All remaining volume is no longer accessible so the order must be removed from the book. */
typedef struct {
  uint8_t nanoseconds[4];      /* bytes 0 to 3 */
  uint8_t trade_date[2];       /* bytes 4 to 5 */
  uint8_t contract_number[4];  /* bytes 6 to 9 */
  uint8_t side;                /* byte 10 */
  uint8_t order_number[8];     /* bytes 11 to 18 */
} OrderDeletedMessage;

/* any Order Deleted Message at all: every byte one the checker chooses */
static void any_order_deleted_message(OrderDeletedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
}

/* Order Deleted Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_order_deleted_message(const OrderDeletedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }

  return at;
}

/* Order Deleted Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_order_deleted_message(OrderDeletedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Deleted Message is what was written, byte for byte */
static void equal_order_deleted_message(const OrderDeletedMessage *read, const OrderDeletedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
}

/* Order Deleted Message: written and read back, then read and written back */
static void check_order_deleted_message(void) {
  OrderDeletedMessage sent;
  OrderDeletedMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_order_deleted_message(&sent);
  assert(encode_order_deleted_message(&sent, wire, 0) == 19);
  assert(decode_order_deleted_message(&got, wire, 0) == 19);
  equal_order_deleted_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_order_deleted_message(&got, wire, 0) == 19);
  assert(encode_order_deleted_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Implied Order Added Message: 31 bytes ----------------------------------- */

/* This message is the same format as the Order Added message, except the nature of this order is it has an implied price, implied volume and a priority that is derived from two or more spreadable “real” orders. */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t trade_date[2];           /* bytes 4 to 5 */
  uint8_t contract_number[4];      /* bytes 6 to 9 */
  uint8_t side;                    /* byte 10 */
  uint8_t order_number[8];         /* bytes 11 to 18 */
  uint8_t order_book_priority[4];  /* bytes 19 to 22 */
  uint8_t quantity[4];             /* bytes 23 to 26 */
  uint8_t price[4];                /* bytes 27 to 30 */
} ImpliedOrderAddedMessage;

/* any Implied Order Added Message at all: every byte one the checker chooses */
static void any_implied_order_added_message(ImpliedOrderAddedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_priority[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Implied Order Added Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_implied_order_added_message(const ImpliedOrderAddedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_priority[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Implied Order Added Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_implied_order_added_message(ImpliedOrderAddedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_priority[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Implied Order Added Message is what was written, byte for byte */
static void equal_implied_order_added_message(const ImpliedOrderAddedMessage *read, const ImpliedOrderAddedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_priority[i] == written->order_book_priority[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Implied Order Added Message: written and read back, then read and written back */
static void check_implied_order_added_message(void) {
  ImpliedOrderAddedMessage sent;
  ImpliedOrderAddedMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_implied_order_added_message(&sent);
  assert(encode_implied_order_added_message(&sent, wire, 0) == 31);
  assert(decode_implied_order_added_message(&got, wire, 0) == 31);
  equal_implied_order_added_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_implied_order_added_message(&got, wire, 0) == 31);
  assert(encode_implied_order_added_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Implied Order Replaced Message: 31 bytes -------------------------------- */

/* This message is the same format as the Order Replaced message, except this replacement refers to an implied order and is sent whenever the implied pricing or volume has changed due to a price or volume movement of “real” orders for a side of a single contract number. */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t trade_date[2];           /* bytes 4 to 5 */
  uint8_t contract_number[4];      /* bytes 6 to 9 */
  uint8_t side;                    /* byte 10 */
  uint8_t order_number[8];         /* bytes 11 to 18 */
  uint8_t order_book_priority[4];  /* bytes 19 to 22 */
  uint8_t quantity[4];             /* bytes 23 to 26 */
  uint8_t price[4];                /* bytes 27 to 30 */
} ImpliedOrderReplacedMessage;

/* any Implied Order Replaced Message at all: every byte one the checker chooses */
static void any_implied_order_replaced_message(ImpliedOrderReplacedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_priority[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Implied Order Replaced Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_implied_order_replaced_message(const ImpliedOrderReplacedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_priority[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Implied Order Replaced Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_implied_order_replaced_message(ImpliedOrderReplacedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_priority[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Implied Order Replaced Message is what was written, byte for byte */
static void equal_implied_order_replaced_message(const ImpliedOrderReplacedMessage *read, const ImpliedOrderReplacedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_priority[i] == written->order_book_priority[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Implied Order Replaced Message: written and read back, then read and written back */
static void check_implied_order_replaced_message(void) {
  ImpliedOrderReplacedMessage sent;
  ImpliedOrderReplacedMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_implied_order_replaced_message(&sent);
  assert(encode_implied_order_replaced_message(&sent, wire, 0) == 31);
  assert(decode_implied_order_replaced_message(&got, wire, 0) == 31);
  equal_implied_order_replaced_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_implied_order_replaced_message(&got, wire, 0) == 31);
  assert(encode_implied_order_replaced_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Implied Order Deleted Message: 19 bytes --------------------------------- */

/* This message is the same format as the Order Deleted message, except this deletion refers to an implied order. When received, any implied volume is no longer accessible so the “implied” order of the indicated side must be removed from the book. */
typedef struct {
  uint8_t nanoseconds[4];      /* bytes 0 to 3 */
  uint8_t trade_date[2];       /* bytes 4 to 5 */
  uint8_t contract_number[4];  /* bytes 6 to 9 */
  uint8_t side;                /* byte 10 */
  uint8_t order_number[8];     /* bytes 11 to 18 */
} ImpliedOrderDeletedMessage;

/* any Implied Order Deleted Message at all: every byte one the checker chooses */
static void any_implied_order_deleted_message(ImpliedOrderDeletedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
}

/* Implied Order Deleted Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_implied_order_deleted_message(const ImpliedOrderDeletedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }

  return at;
}

/* Implied Order Deleted Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_implied_order_deleted_message(ImpliedOrderDeletedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }

  return at;
}

/* what was read of Implied Order Deleted Message is what was written, byte for byte */
static void equal_implied_order_deleted_message(const ImpliedOrderDeletedMessage *read, const ImpliedOrderDeletedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
}

/* Implied Order Deleted Message: written and read back, then read and written back */
static void check_implied_order_deleted_message(void) {
  ImpliedOrderDeletedMessage sent;
  ImpliedOrderDeletedMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_implied_order_deleted_message(&sent);
  assert(encode_implied_order_deleted_message(&sent, wire, 0) == 19);
  assert(decode_implied_order_deleted_message(&got, wire, 0) == 19);
  equal_implied_order_deleted_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_implied_order_deleted_message(&got, wire, 0) == 19);
  assert(encode_implied_order_deleted_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Custom Market Order Replaced Message: 22 bytes -------------------------- */

/* This message is sent whenever an order in the custom market book has been modified for volume. Custom market order modification messages always include the Order Number of the Custom Market Order Added to which the update applies. To determine the current display volume for an order, subscribers must replace the original volume stated in the Custom Market Order Added message with the quantity stated in the Custom Market Order Replaced message of the same order number. */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t trade_date[2];           /* bytes 4 to 5 */
  uint8_t order_number[8];         /* bytes 6 to 13 */
  uint8_t order_book_priority[4];  /* bytes 14 to 17 */
  uint8_t quantity[4];             /* bytes 18 to 21 */
} CustomMarketOrderReplacedMessage;

/* any Custom Market Order Replaced Message at all: every byte one the checker chooses */
static void any_custom_market_order_replaced_message(CustomMarketOrderReplacedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_priority[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
}

/* Custom Market Order Replaced Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_custom_market_order_replaced_message(const CustomMarketOrderReplacedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_priority[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Custom Market Order Replaced Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_custom_market_order_replaced_message(CustomMarketOrderReplacedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_priority[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Custom Market Order Replaced Message is what was written, byte for byte */
static void equal_custom_market_order_replaced_message(const CustomMarketOrderReplacedMessage *read, const CustomMarketOrderReplacedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_priority[i] == written->order_book_priority[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Custom Market Order Replaced Message: written and read back, then read and written back */
static void check_custom_market_order_replaced_message(void) {
  CustomMarketOrderReplacedMessage sent;
  CustomMarketOrderReplacedMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_custom_market_order_replaced_message(&sent);
  assert(encode_custom_market_order_replaced_message(&sent, wire, 0) == 22);
  assert(decode_custom_market_order_replaced_message(&got, wire, 0) == 22);
  equal_custom_market_order_replaced_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_custom_market_order_replaced_message(&got, wire, 0) == 22);
  assert(encode_custom_market_order_replaced_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Custom Market Order Deleted Message: 14 bytes --------------------------- */

/* This message is sent whenever an order in the custom market book is cancelled by the owner, expired, cancelled by the exchange or purged. All remaining volume is no longer accessible so the order must be removed from the book. A Custom Market Order Deleted message is not sent when an order has traded out. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t trade_date[2];    /* bytes 4 to 5 */
  uint8_t order_number[8];  /* bytes 6 to 13 */
} CustomMarketOrderDeletedMessage;

/* any Custom Market Order Deleted Message at all: every byte one the checker chooses */
static void any_custom_market_order_deleted_message(CustomMarketOrderDeletedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
}

/* Custom Market Order Deleted Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_custom_market_order_deleted_message(const CustomMarketOrderDeletedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }

  return at;
}

/* Custom Market Order Deleted Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_custom_market_order_deleted_message(CustomMarketOrderDeletedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }

  return at;
}

/* what was read of Custom Market Order Deleted Message is what was written, byte for byte */
static void equal_custom_market_order_deleted_message(const CustomMarketOrderDeletedMessage *read, const CustomMarketOrderDeletedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
}

/* Custom Market Order Deleted Message: written and read back, then read and written back */
static void check_custom_market_order_deleted_message(void) {
  CustomMarketOrderDeletedMessage sent;
  CustomMarketOrderDeletedMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_custom_market_order_deleted_message(&sent);
  assert(encode_custom_market_order_deleted_message(&sent, wire, 0) == 14);
  assert(decode_custom_market_order_deleted_message(&got, wire, 0) == 14);
  equal_custom_market_order_deleted_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_custom_market_order_deleted_message(&got, wire, 0) == 14);
  assert(encode_custom_market_order_deleted_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 36 bytes ---------------------------------------- */

/* This message is sent whenever a resting order of the book is executed in whole or in part where the price and contract number of the order and trade are the same. It is possible to receive several Order Executed messages for the same order reference number if that order is executed in several parts. */
typedef struct {
  uint8_t nanoseconds[4];         /* bytes 0 to 3 */
  uint8_t trade_date[2];          /* bytes 4 to 5 */
  uint8_t contract_number[4];     /* bytes 6 to 9 */
  uint8_t side;                   /* byte 10 */
  uint8_t order_number[8];        /* bytes 11 to 18 */
  uint8_t quantity_remaining[4];  /* bytes 19 to 22 */
  uint8_t trade_type;             /* byte 23 */
  uint8_t match_number[4];        /* bytes 24 to 27 */
  uint8_t executed_quantity[4];   /* bytes 28 to 31 */
  uint8_t trade_price[4];         /* bytes 32 to 35 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_remaining[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_remaining[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }

  return at;
}

/* Order Executed Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_remaining[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_remaining[i] == written->quantity_remaining[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 36);
  assert(decode_order_executed_message(&got, wire, 0) == 36);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 36);
  assert(encode_order_executed_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed With Price Message: 47 bytes ----------------------------- */

/* This message is sent whenever two resting orders of the same contract are executed. This can occur in two circumstances: During levelling in whole or in part at a price that could be different from one or both resting order prices. */
typedef struct {
  uint8_t nanoseconds[4];                /* bytes 0 to 3 */
  uint8_t trade_date[2];                 /* bytes 4 to 5 */
  uint8_t contract_number[4];            /* bytes 6 to 9 */
  uint8_t buying_order_number[8];        /* bytes 10 to 17 */
  uint8_t buyer_quantity_remaining[4];   /* bytes 18 to 21 */
  uint8_t selling_order_number[8];       /* bytes 22 to 29 */
  uint8_t seller_quantity_remaining[4];  /* bytes 30 to 33 */
  uint8_t trade_type;                    /* byte 34 */
  uint8_t match_number[4];               /* bytes 35 to 38 */
  uint8_t executed_quantity[4];          /* bytes 39 to 42 */
  uint8_t trade_price[4];                /* bytes 43 to 46 */
} OrderExecutedWithPriceMessage;

/* any Order Executed With Price Message at all: every byte one the checker chooses */
static void any_order_executed_with_price_message(OrderExecutedWithPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buying_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buyer_quantity_remaining[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->selling_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->seller_quantity_remaining[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
}

/* Order Executed With Price Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_with_price_message(const OrderExecutedWithPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buying_order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buyer_quantity_remaining[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->selling_order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seller_quantity_remaining[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }

  return at;
}

/* Order Executed With Price Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_with_price_message(OrderExecutedWithPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buying_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buyer_quantity_remaining[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->selling_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->seller_quantity_remaining[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed With Price Message is what was written, byte for byte */
static void equal_order_executed_with_price_message(const OrderExecutedWithPriceMessage *read, const OrderExecutedWithPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buying_order_number[i] == written->buying_order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buyer_quantity_remaining[i] == written->buyer_quantity_remaining[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->selling_order_number[i] == written->selling_order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->seller_quantity_remaining[i] == written->seller_quantity_remaining[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
}

/* Order Executed With Price Message: written and read back, then read and written back */
static void check_order_executed_with_price_message(void) {
  OrderExecutedWithPriceMessage sent;
  OrderExecutedWithPriceMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_order_executed_with_price_message(&sent);
  assert(encode_order_executed_with_price_message(&sent, wire, 0) == 47);
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 47);
  equal_order_executed_with_price_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 47);
  assert(encode_order_executed_with_price_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spread Executed Message: 46 bytes --------------------------------------- */

/* This message is sent whenever the open leg of a resting spread order is traded in whole or in part where the price and the contract number will be different than the traded contract number. It is possible to receive several Spread Executed messages for the same order number if that order is executed in several parts. */
typedef struct {
  uint8_t nanoseconds[4];             /* bytes 0 to 3 */
  uint8_t trade_date[2];              /* bytes 4 to 5 */
  uint8_t contract_number[4];         /* bytes 6 to 9 */
  uint8_t side;                       /* byte 10 */
  uint8_t order_number[8];            /* bytes 11 to 18 */
  uint8_t quantity_remaining[4];      /* bytes 19 to 22 */
  uint8_t trade_type;                 /* byte 23 */
  uint8_t match_number[4];            /* bytes 24 to 27 */
  uint8_t executed_quantity[4];       /* bytes 28 to 31 */
  uint8_t trade_price[4];             /* bytes 32 to 35 */
  uint8_t traded_contract_number[4];  /* bytes 36 to 39 */
  uint8_t spread_trade_price[4];      /* bytes 40 to 43 */
  uint8_t trade_side_of_leg;          /* byte 44 */
  uint8_t printable;                  /* byte 45 */
} SpreadExecutedMessage;

/* any Spread Executed Message at all: every byte one the checker chooses */
static void any_spread_executed_message(SpreadExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_remaining[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->traded_contract_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->spread_trade_price[i] = arbitrary(); }
  record->trade_side_of_leg = arbitrary();
  record->printable = arbitrary();
}

/* Spread Executed Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_spread_executed_message(const SpreadExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_remaining[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->traded_contract_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->spread_trade_price[i]; }
  wire[at++] = record->trade_side_of_leg;
  wire[at++] = record->printable;

  return at;
}

/* Spread Executed Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_spread_executed_message(SpreadExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_remaining[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->traded_contract_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->spread_trade_price[i] = wire[at++]; }
  record->trade_side_of_leg = wire[at++];
  record->printable = wire[at++];

  return at;
}

/* what was read of Spread Executed Message is what was written, byte for byte */
static void equal_spread_executed_message(const SpreadExecutedMessage *read, const SpreadExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_remaining[i] == written->quantity_remaining[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->traded_contract_number[i] == written->traded_contract_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->spread_trade_price[i] == written->spread_trade_price[i]); }
  assert(read->trade_side_of_leg == written->trade_side_of_leg);
  assert(read->printable == written->printable);
}

/* Spread Executed Message: written and read back, then read and written back */
static void check_spread_executed_message(void) {
  SpreadExecutedMessage sent;
  SpreadExecutedMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_spread_executed_message(&sent);
  assert(encode_spread_executed_message(&sent, wire, 0) == 46);
  assert(decode_spread_executed_message(&got, wire, 0) == 46);
  equal_spread_executed_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_spread_executed_message(&got, wire, 0) == 46);
  assert(encode_spread_executed_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Spread Execution Chain Message: 62 bytes -------------------------- */

/* This message is sent whenever two resting orders of different contracts are executed in whole or in part at a price different from the initial display price(s) such as sweeping or spreading orders. Since the execution price is different than the display price of the original Add Order, a trade price field is included within the execution message. */
typedef struct {
  uint8_t nanoseconds[4];                /* bytes 0 to 3 */
  uint8_t trade_date[2];                 /* bytes 4 to 5 */
  uint8_t buyer[4];                      /* bytes 6 to 9 */
  uint8_t side_of_buyer;                 /* byte 10 */
  uint8_t buyer_order_number[8];         /* bytes 11 to 18 */
  uint8_t buyer_quantity_remaining[4];   /* bytes 19 to 22 */
  uint8_t seller_contract_number[4];     /* bytes 23 to 26 */
  uint8_t side_of_seller;                /* byte 27 */
  uint8_t selling_order_number[8];       /* bytes 28 to 35 */
  uint8_t seller_quantity_remaining[4];  /* bytes 36 to 39 */
  uint8_t trade_type;                    /* byte 40 */
  uint8_t match_number[4];               /* bytes 41 to 44 */
  uint8_t executed_quantity[4];          /* bytes 45 to 48 */
  uint8_t trade_price[4];                /* bytes 49 to 52 */
  uint8_t traded_contract_number[4];     /* bytes 53 to 56 */
  uint8_t spread_trade_price[4];         /* bytes 57 to 60 */
  uint8_t printable;                     /* byte 61 */
} TradeSpreadExecutionChainMessage;

/* any Trade Spread Execution Chain Message at all: every byte one the checker chooses */
static void any_trade_spread_execution_chain_message(TradeSpreadExecutionChainMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buyer[i] = arbitrary(); }
  record->side_of_buyer = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->buyer_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buyer_quantity_remaining[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->seller_contract_number[i] = arbitrary(); }
  record->side_of_seller = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->selling_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->seller_quantity_remaining[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->traded_contract_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->spread_trade_price[i] = arbitrary(); }
  record->printable = arbitrary();
}

/* Trade Spread Execution Chain Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_trade_spread_execution_chain_message(const TradeSpreadExecutionChainMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buyer[i]; }
  wire[at++] = record->side_of_buyer;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buyer_order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buyer_quantity_remaining[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seller_contract_number[i]; }
  wire[at++] = record->side_of_seller;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->selling_order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seller_quantity_remaining[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->traded_contract_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->spread_trade_price[i]; }
  wire[at++] = record->printable;

  return at;
}

/* Trade Spread Execution Chain Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_trade_spread_execution_chain_message(TradeSpreadExecutionChainMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buyer[i] = wire[at++]; }
  record->side_of_buyer = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->buyer_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buyer_quantity_remaining[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->seller_contract_number[i] = wire[at++]; }
  record->side_of_seller = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->selling_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->seller_quantity_remaining[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->traded_contract_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->spread_trade_price[i] = wire[at++]; }
  record->printable = wire[at++];

  return at;
}

/* what was read of Trade Spread Execution Chain Message is what was written, byte for byte */
static void equal_trade_spread_execution_chain_message(const TradeSpreadExecutionChainMessage *read, const TradeSpreadExecutionChainMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buyer[i] == written->buyer[i]); }
  assert(read->side_of_buyer == written->side_of_buyer);
  for (size_t i = 0; i < 8; i++) { assert(read->buyer_order_number[i] == written->buyer_order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buyer_quantity_remaining[i] == written->buyer_quantity_remaining[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->seller_contract_number[i] == written->seller_contract_number[i]); }
  assert(read->side_of_seller == written->side_of_seller);
  for (size_t i = 0; i < 8; i++) { assert(read->selling_order_number[i] == written->selling_order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->seller_quantity_remaining[i] == written->seller_quantity_remaining[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->traded_contract_number[i] == written->traded_contract_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->spread_trade_price[i] == written->spread_trade_price[i]); }
  assert(read->printable == written->printable);
}

/* Trade Spread Execution Chain Message: written and read back, then read and written back */
static void check_trade_spread_execution_chain_message(void) {
  TradeSpreadExecutionChainMessage sent;
  TradeSpreadExecutionChainMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_trade_spread_execution_chain_message(&sent);
  assert(encode_trade_spread_execution_chain_message(&sent, wire, 0) == 62);
  assert(decode_trade_spread_execution_chain_message(&got, wire, 0) == 62);
  equal_trade_spread_execution_chain_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_spread_execution_chain_message(&got, wire, 0) == 62);
  assert(encode_trade_spread_execution_chain_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Custom Market Executed Message: 37 bytes -------------------------------- */

/* This message is sent whenever the open leg of a resting custom market order is traded in whole or in part. */
typedef struct {
  uint8_t nanoseconds[4];             /* bytes 0 to 3 */
  uint8_t trade_date[2];              /* bytes 4 to 5 */
  uint8_t order_number[8];            /* bytes 6 to 13 */
  uint8_t quantity_remaining[4];      /* bytes 14 to 17 */
  uint8_t trade_type;                 /* byte 18 */
  uint8_t match_number[4];            /* bytes 19 to 22 */
  uint8_t executed_quantity[4];       /* bytes 23 to 26 */
  uint8_t trade_price[4];             /* bytes 27 to 30 */
  uint8_t traded_contract_number[4];  /* bytes 31 to 34 */
  uint8_t trade_side_of_leg;          /* byte 35 */
  uint8_t printable;                  /* byte 36 */
} CustomMarketExecutedMessage;

/* any Custom Market Executed Message at all: every byte one the checker chooses */
static void any_custom_market_executed_message(CustomMarketExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_remaining[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->traded_contract_number[i] = arbitrary(); }
  record->trade_side_of_leg = arbitrary();
  record->printable = arbitrary();
}

/* Custom Market Executed Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_custom_market_executed_message(const CustomMarketExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_remaining[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->traded_contract_number[i]; }
  wire[at++] = record->trade_side_of_leg;
  wire[at++] = record->printable;

  return at;
}

/* Custom Market Executed Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_custom_market_executed_message(CustomMarketExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_remaining[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->traded_contract_number[i] = wire[at++]; }
  record->trade_side_of_leg = wire[at++];
  record->printable = wire[at++];

  return at;
}

/* what was read of Custom Market Executed Message is what was written, byte for byte */
static void equal_custom_market_executed_message(const CustomMarketExecutedMessage *read, const CustomMarketExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_remaining[i] == written->quantity_remaining[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->traded_contract_number[i] == written->traded_contract_number[i]); }
  assert(read->trade_side_of_leg == written->trade_side_of_leg);
  assert(read->printable == written->printable);
}

/* Custom Market Executed Message: written and read back, then read and written back */
static void check_custom_market_executed_message(void) {
  CustomMarketExecutedMessage sent;
  CustomMarketExecutedMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_custom_market_executed_message(&sent);
  assert(encode_custom_market_executed_message(&sent, wire, 0) == 37);
  assert(decode_custom_market_executed_message(&got, wire, 0) == 37);
  equal_custom_market_executed_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_custom_market_executed_message(&got, wire, 0) == 37);
  assert(encode_custom_market_executed_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Custom Market Trade Message: 54 bytes ----------------------------------- */

/* This message is sent whenever a resting custom market order is matched with a resting non-custom market order executed in whole or in part at a price that could be different from the initial display price(s) such as spreading orders. Since the execution price could be different than the display price of the original Order Added, a trade price field is included within the execution message. */
typedef struct {
  uint8_t nanoseconds[4];                       /* bytes 0 to 3 */
  uint8_t trade_date[2];                        /* bytes 4 to 5 */
  uint8_t contract_number[4];                   /* bytes 6 to 9 */
  uint8_t side;                                 /* byte 10 */
  uint8_t order_number[8];                      /* bytes 11 to 18 */
  uint8_t quantity_remaining[4];                /* bytes 19 to 22 */
  uint8_t custom_market_order_number[8];        /* bytes 23 to 30 */
  uint8_t custom_market_quantity_remaining[4];  /* bytes 31 to 34 */
  uint8_t trade_type;                           /* byte 35 */
  uint8_t match_number[4];                      /* bytes 36 to 39 */
  uint8_t executed_quantity[4];                 /* bytes 40 to 43 */
  uint8_t trade_price[4];                       /* bytes 44 to 47 */
  uint8_t traded_contract_number[4];            /* bytes 48 to 51 */
  uint8_t trade_side_of_non_custom_order;       /* byte 52 */
  uint8_t printable;                            /* byte 53 */
} CustomMarketTradeMessage;

/* any Custom Market Trade Message at all: every byte one the checker chooses */
static void any_custom_market_trade_message(CustomMarketTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_remaining[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->custom_market_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->custom_market_quantity_remaining[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->traded_contract_number[i] = arbitrary(); }
  record->trade_side_of_non_custom_order = arbitrary();
  record->printable = arbitrary();
}

/* Custom Market Trade Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_custom_market_trade_message(const CustomMarketTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_remaining[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->custom_market_order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->custom_market_quantity_remaining[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->traded_contract_number[i]; }
  wire[at++] = record->trade_side_of_non_custom_order;
  wire[at++] = record->printable;

  return at;
}

/* Custom Market Trade Message off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_custom_market_trade_message(CustomMarketTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_remaining[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->custom_market_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->custom_market_quantity_remaining[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->traded_contract_number[i] = wire[at++]; }
  record->trade_side_of_non_custom_order = wire[at++];
  record->printable = wire[at++];

  return at;
}

/* what was read of Custom Market Trade Message is what was written, byte for byte */
static void equal_custom_market_trade_message(const CustomMarketTradeMessage *read, const CustomMarketTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_remaining[i] == written->quantity_remaining[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->custom_market_order_number[i] == written->custom_market_order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->custom_market_quantity_remaining[i] == written->custom_market_quantity_remaining[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->traded_contract_number[i] == written->traded_contract_number[i]); }
  assert(read->trade_side_of_non_custom_order == written->trade_side_of_non_custom_order);
  assert(read->printable == written->printable);
}

/* Custom Market Trade Message: written and read back, then read and written back */
static void check_custom_market_trade_message(void) {
  CustomMarketTradeMessage sent;
  CustomMarketTradeMessage got;
  uint8_t wire[54];
  uint8_t again[54];

  any_custom_market_trade_message(&sent);
  assert(encode_custom_market_trade_message(&sent, wire, 0) == 54);
  assert(decode_custom_market_trade_message(&got, wire, 0) == 54);
  equal_custom_market_trade_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_custom_market_trade_message(&got, wire, 0) == 54);
  assert(encode_custom_market_trade_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancellation Message: 10 bytes ------------------------------------ */

/* This message is sent whenever a trade is cancelled by exchange operations. This message does not affect any resting orders and is more for Information purposes. Adjustments to the Open, High, Low, Last will be performed as separate action using the Open, High, Low, Last Trade Adjustment message. */
typedef struct {
  uint8_t nanoseconds[4];   /* bytes 0 to 3 */
  uint8_t trade_date[2];    /* bytes 4 to 5 */
  uint8_t match_number[4];  /* bytes 6 to 9 */
} TradeCancellationMessage;

/* any Trade Cancellation Message at all: every byte one the checker chooses */
static void any_trade_cancellation_message(TradeCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = arbitrary(); }
}

/* Trade Cancellation Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancellation_message(const TradeCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Trade Cancellation Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancellation_message(TradeCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancellation Message is what was written, byte for byte */
static void equal_trade_cancellation_message(const TradeCancellationMessage *read, const TradeCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Trade Cancellation Message: written and read back, then read and written back */
static void check_trade_cancellation_message(void) {
  TradeCancellationMessage sent;
  TradeCancellationMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_trade_cancellation_message(&sent);
  assert(encode_trade_cancellation_message(&sent, wire, 0) == 10);
  assert(decode_trade_cancellation_message(&got, wire, 0) == 10);
  equal_trade_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancellation_message(&got, wire, 0) == 10);
  assert(encode_trade_cancellation_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Equilibrium Price Auction Info Message: 30 bytes ------------------------ */

/* ASX Trade24 disseminates equilibrium prices during a price discovery period. As orders are added, modified, cancelled or deleted a message will be reported informing the market the potential opening price. */
typedef struct {
  uint8_t nanoseconds[4];        /* bytes 0 to 3 */
  uint8_t trade_date[2];         /* bytes 4 to 5 */
  uint8_t contract_number[4];    /* bytes 6 to 9 */
  uint8_t equilibrium_price[4];  /* bytes 10 to 13 */
  uint8_t best_bid_price[4];     /* bytes 14 to 17 */
  uint8_t best_ask_price[4];     /* bytes 18 to 21 */
  uint8_t best_bid_quantity[4];  /* bytes 22 to 25 */
  uint8_t best_ask_quantity[4];  /* bytes 26 to 29 */
} EquilibriumPriceAuctionInfoMessage;

/* any Equilibrium Price Auction Info Message at all: every byte one the checker chooses */
static void any_equilibrium_price_auction_info_message(EquilibriumPriceAuctionInfoMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->equilibrium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_bid_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_ask_quantity[i] = arbitrary(); }
}

/* Equilibrium Price Auction Info Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_equilibrium_price_auction_info_message(const EquilibriumPriceAuctionInfoMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->equilibrium_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_ask_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_bid_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_ask_quantity[i]; }

  return at;
}

/* Equilibrium Price Auction Info Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_equilibrium_price_auction_info_message(EquilibriumPriceAuctionInfoMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->equilibrium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_bid_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_ask_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Equilibrium Price Auction Info Message is what was written, byte for byte */
static void equal_equilibrium_price_auction_info_message(const EquilibriumPriceAuctionInfoMessage *read, const EquilibriumPriceAuctionInfoMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->equilibrium_price[i] == written->equilibrium_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_bid_price[i] == written->best_bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_ask_price[i] == written->best_ask_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_bid_quantity[i] == written->best_bid_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_ask_quantity[i] == written->best_ask_quantity[i]); }
}

/* Equilibrium Price Auction Info Message: written and read back, then read and written back */
static void check_equilibrium_price_auction_info_message(void) {
  EquilibriumPriceAuctionInfoMessage sent;
  EquilibriumPriceAuctionInfoMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_equilibrium_price_auction_info_message(&sent);
  assert(encode_equilibrium_price_auction_info_message(&sent, wire, 0) == 30);
  assert(decode_equilibrium_price_auction_info_message(&got, wire, 0) == 30);
  equal_equilibrium_price_auction_info_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_equilibrium_price_auction_info_message(&got, wire, 0) == 30);
  assert(encode_equilibrium_price_auction_info_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Settlement Message: 19 bytes ------------------------------------- */

/* ASX Trade24 disseminates settlement prices for all future and option contracts in two instalments, an interim and then a final. When the contract moves to the next trade date, the Future Symbol Directory or Option Symbol Directory message will reflect the final settlement price reported from the previous trade date in the prior day settlement field. */
typedef struct {
  uint8_t nanoseconds[4];       /* bytes 0 to 3 */
  uint8_t trade_date[2];        /* bytes 4 to 5 */
  uint8_t contract_number[4];   /* bytes 6 to 9 */
  uint8_t settlement_price[4];  /* bytes 10 to 13 */
  uint8_t volatility[4];        /* bytes 14 to 17 */
  uint8_t settlement_type;      /* byte 18 */
} MarketSettlementMessage;

/* any Market Settlement Message at all: every byte one the checker chooses */
static void any_market_settlement_message(MarketSettlementMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->settlement_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volatility[i] = arbitrary(); }
  record->settlement_type = arbitrary();
}

/* Market Settlement Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_market_settlement_message(const MarketSettlementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settlement_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volatility[i]; }
  wire[at++] = record->settlement_type;

  return at;
}

/* Market Settlement Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_market_settlement_message(MarketSettlementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->settlement_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volatility[i] = wire[at++]; }
  record->settlement_type = wire[at++];

  return at;
}

/* what was read of Market Settlement Message is what was written, byte for byte */
static void equal_market_settlement_message(const MarketSettlementMessage *read, const MarketSettlementMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volatility[i] == written->volatility[i]); }
  assert(read->settlement_type == written->settlement_type);
}

/* Market Settlement Message: written and read back, then read and written back */
static void check_market_settlement_message(void) {
  MarketSettlementMessage sent;
  MarketSettlementMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_market_settlement_message(&sent);
  assert(encode_market_settlement_message(&sent, wire, 0) == 19);
  assert(decode_market_settlement_message(&got, wire, 0) == 19);
  equal_market_settlement_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_market_settlement_message(&got, wire, 0) == 19);
  assert(encode_market_settlement_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ad Hoc Text Message: 112 bytes ------------------------------------------ */

/* ASX Trade24 disseminates text messages to inform the market of ad hoc events. */
typedef struct {
  uint8_t nanoseconds[4];     /* bytes 0 to 3 */
  uint8_t trade_date[2];      /* bytes 4 to 5 */
  uint8_t source_id[6];       /* bytes 6 to 11 */
  uint8_t text_message[100];  /* bytes 12 to 111 */
} AdHocTextMessage;

/* any Ad Hoc Text Message at all: every byte one the checker chooses */
static void any_ad_hoc_text_message(AdHocTextMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->source_id[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->text_message[i] = arbitrary(); }
}

/* Ad Hoc Text Message to the wire: 112 bytes from at, returning where the next byte goes */
static size_t encode_ad_hoc_text_message(const AdHocTextMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->source_id[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->text_message[i]; }

  return at;
}

/* Ad Hoc Text Message off the wire: 112 bytes from at, returning where the next byte lies */
static size_t decode_ad_hoc_text_message(AdHocTextMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->source_id[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->text_message[i] = wire[at++]; }

  return at;
}

/* what was read of Ad Hoc Text Message is what was written, byte for byte */
static void equal_ad_hoc_text_message(const AdHocTextMessage *read, const AdHocTextMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->source_id[i] == written->source_id[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->text_message[i] == written->text_message[i]); }
}

/* Ad Hoc Text Message: written and read back, then read and written back */
static void check_ad_hoc_text_message(void) {
  AdHocTextMessage sent;
  AdHocTextMessage got;
  uint8_t wire[112];
  uint8_t again[112];

  any_ad_hoc_text_message(&sent);
  assert(encode_ad_hoc_text_message(&sent, wire, 0) == 112);
  assert(decode_ad_hoc_text_message(&got, wire, 0) == 112);
  equal_ad_hoc_text_message(&got, &sent);

  for (size_t i = 0; i < 112; i++) { wire[i] = arbitrary(); }
  assert(decode_ad_hoc_text_message(&got, wire, 0) == 112);
  assert(encode_ad_hoc_text_message(&got, again, 0) == 112);
  for (size_t i = 0; i < 112; i++) { assert(again[i] == wire[i]); }
}

/* ---- Request For Quote Message: 18 bytes ------------------------------------- */

/* ASX Trade24 disseminates anonymous non-custom RFQs from the market. */
typedef struct {
  uint8_t nanoseconds[4];      /* bytes 0 to 3 */
  uint8_t trade_date[2];       /* bytes 4 to 5 */
  uint8_t contract_number[4];  /* bytes 6 to 9 */
  uint8_t price[4];            /* bytes 10 to 13 */
  uint8_t quantity[4];         /* bytes 14 to 17 */
} RequestForQuoteMessage;

/* any Request For Quote Message at all: every byte one the checker chooses */
static void any_request_for_quote_message(RequestForQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
}

/* Request For Quote Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_request_for_quote_message(const RequestForQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Request For Quote Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_request_for_quote_message(RequestForQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Request For Quote Message is what was written, byte for byte */
static void equal_request_for_quote_message(const RequestForQuoteMessage *read, const RequestForQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Request For Quote Message: written and read back, then read and written back */
static void check_request_for_quote_message(void) {
  RequestForQuoteMessage sent;
  RequestForQuoteMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_request_for_quote_message(&sent);
  assert(encode_request_for_quote_message(&sent, wire, 0) == 18);
  assert(decode_request_for_quote_message(&got, wire, 0) == 18);
  equal_request_for_quote_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_request_for_quote_message(&got, wire, 0) == 18);
  assert(encode_request_for_quote_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Anomalous Order Threshold Publish Message: 34 bytes --------------------- */

/* ASX Trade24 reports this message to inform the market of setting, zeroing or adjusting the Extreme Trade Range price (ETR), the Anomalous Order Threshold price (AOT) and the associated ranges for a contract that requires Market Integrity Rules enforcement. */
typedef struct {
  uint8_t nanoseconds[4];      /* bytes 0 to 3 */
  uint8_t trade_date[2];       /* bytes 4 to 5 */
  uint8_t contract_number[4];  /* bytes 6 to 9 */
  uint8_t aot_price[4];        /* bytes 10 to 13 */
  uint8_t aot_upper_price[4];  /* bytes 14 to 17 */
  uint8_t aot_lower_price[4];  /* bytes 18 to 21 */
  uint8_t etr_price[4];        /* bytes 22 to 25 */
  uint8_t etr_upper_price[4];  /* bytes 26 to 29 */
  uint8_t etr_lower_price[4];  /* bytes 30 to 33 */
} AnomalousOrderThresholdPublishMessage;

/* any Anomalous Order Threshold Publish Message at all: every byte one the checker chooses */
static void any_anomalous_order_threshold_publish_message(AnomalousOrderThresholdPublishMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->aot_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->aot_upper_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->aot_lower_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->etr_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->etr_upper_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->etr_lower_price[i] = arbitrary(); }
}

/* Anomalous Order Threshold Publish Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_anomalous_order_threshold_publish_message(const AnomalousOrderThresholdPublishMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->aot_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->aot_upper_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->aot_lower_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->etr_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->etr_upper_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->etr_lower_price[i]; }

  return at;
}

/* Anomalous Order Threshold Publish Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_anomalous_order_threshold_publish_message(AnomalousOrderThresholdPublishMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->aot_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->aot_upper_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->aot_lower_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->etr_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->etr_upper_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->etr_lower_price[i] = wire[at++]; }

  return at;
}

/* what was read of Anomalous Order Threshold Publish Message is what was written, byte for byte */
static void equal_anomalous_order_threshold_publish_message(const AnomalousOrderThresholdPublishMessage *read, const AnomalousOrderThresholdPublishMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->aot_price[i] == written->aot_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->aot_upper_price[i] == written->aot_upper_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->aot_lower_price[i] == written->aot_lower_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->etr_price[i] == written->etr_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->etr_upper_price[i] == written->etr_upper_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->etr_lower_price[i] == written->etr_lower_price[i]); }
}

/* Anomalous Order Threshold Publish Message: written and read back, then read and written back */
static void check_anomalous_order_threshold_publish_message(void) {
  AnomalousOrderThresholdPublishMessage sent;
  AnomalousOrderThresholdPublishMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_anomalous_order_threshold_publish_message(&sent);
  assert(encode_anomalous_order_threshold_publish_message(&sent, wire, 0) == 34);
  assert(decode_anomalous_order_threshold_publish_message(&got, wire, 0) == 34);
  equal_anomalous_order_threshold_publish_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_anomalous_order_threshold_publish_message(&got, wire, 0) == 34);
  assert(encode_anomalous_order_threshold_publish_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Volume And Open Interest Message: 20 bytes ------------------------------ */

/* ASX Trade24 disseminates volume and open interest information for each trade date. The VOI Trade Date indicates the trade date to which the information applies. */
typedef struct {
  uint8_t nanoseconds[4];        /* bytes 0 to 3 */
  uint8_t trade_date[2];         /* bytes 4 to 5 */
  uint8_t contract_number[4];    /* bytes 6 to 9 */
  uint8_t cumulative_volume[4];  /* bytes 10 to 13 */
  uint8_t open_interest[4];      /* bytes 14 to 17 */
  uint8_t voi_trade_date[2];     /* bytes 18 to 19 */
} VolumeAndOpenInterestMessage;

/* any Volume And Open Interest Message at all: every byte one the checker chooses */
static void any_volume_and_open_interest_message(VolumeAndOpenInterestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cumulative_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->voi_trade_date[i] = arbitrary(); }
}

/* Volume And Open Interest Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_volume_and_open_interest_message(const VolumeAndOpenInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cumulative_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_interest[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->voi_trade_date[i]; }

  return at;
}

/* Volume And Open Interest Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_volume_and_open_interest_message(VolumeAndOpenInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cumulative_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->voi_trade_date[i] = wire[at++]; }

  return at;
}

/* what was read of Volume And Open Interest Message is what was written, byte for byte */
static void equal_volume_and_open_interest_message(const VolumeAndOpenInterestMessage *read, const VolumeAndOpenInterestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_number[i] == written->contract_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cumulative_volume[i] == written->cumulative_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->voi_trade_date[i] == written->voi_trade_date[i]); }
}

/* Volume And Open Interest Message: written and read back, then read and written back */
static void check_volume_and_open_interest_message(void) {
  VolumeAndOpenInterestMessage sent;
  VolumeAndOpenInterestMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_volume_and_open_interest_message(&sent);
  assert(encode_volume_and_open_interest_message(&sent, wire, 0) == 20);
  assert(decode_volume_and_open_interest_message(&got, wire, 0) == 20);
  equal_volume_and_open_interest_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_volume_and_open_interest_message(&got, wire, 0) == 20);
  assert(encode_volume_and_open_interest_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_session();
  check_packet_header();
  check_message_header();
  check_time_message();
  check_system_event_message();
  check_future_symbol_directory_message();
  check_spread_symbol_directory_message();
  check_option_symbol_directory_message();
  check_order_book_state_message();
  check_order_added_message();
  check_order_replaced_message();
  check_order_volume_cancelled_message();
  check_order_deleted_message();
  check_implied_order_added_message();
  check_implied_order_replaced_message();
  check_implied_order_deleted_message();
  check_custom_market_order_replaced_message();
  check_custom_market_order_deleted_message();
  check_order_executed_message();
  check_order_executed_with_price_message();
  check_spread_executed_message();
  check_trade_spread_execution_chain_message();
  check_custom_market_executed_message();
  check_custom_market_trade_message();
  check_trade_cancellation_message();
  check_equilibrium_price_auction_info_message();
  check_market_settlement_message();
  check_ad_hoc_text_message();
  check_request_for_quote_message();
  check_anomalous_order_threshold_publish_message();
  check_volume_and_open_interest_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
