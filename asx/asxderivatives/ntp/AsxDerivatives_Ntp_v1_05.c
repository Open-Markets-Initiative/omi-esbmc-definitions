// asx/asxderivatives/ntp/AsxDerivatives_Ntp_v1_05.c
/*
 * Australian Securities Exchange New Trading Platform
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

/* ---- Seconds Message: 4 bytes ------------------------------------------------ */

/* A ‘seconds’ Nanoseconds is issued every second and any message thereafter will be stamped with the number of nanoseconds past the last Time message received as a time reference point */
typedef struct {
  uint8_t second[4];  /* bytes 0 to 3 */
} SecondsMessage;

/* any Seconds Message at all: every byte one the checker chooses */
static void any_seconds_message(SecondsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = arbitrary(); }
}

/* Seconds Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_seconds_message(const SecondsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second[i]; }

  return at;
}

/* Seconds Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_seconds_message(SecondsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = wire[at++]; }

  return at;
}

/* what was read of Seconds Message is what was written, byte for byte */
static void equal_seconds_message(const SecondsMessage *read, const SecondsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->second[i] == written->second[i]); }
}

/* Seconds Message: written and read back, then read and written back */
static void check_seconds_message(void) {
  SecondsMessage sent;
  SecondsMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_seconds_message(&sent);
  assert(encode_seconds_message(&sent, wire, 0) == 4);
  assert(decode_seconds_message(&got, wire, 0) == 4);
  equal_seconds_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_seconds_message(&got, wire, 0) == 4);
  assert(encode_seconds_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Business Trade Date Message: 7 bytes ----------------------------- */

/* This message will be sent as the last message for a Business Trade Date to signal no further messages will be disseminated for that date. */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t trade_date[2];   /* bytes 4 to 5 */
  uint8_t event_code;      /* byte 6 */
} EndOfBusinessTradeDateMessage;

/* any End Of Business Trade Date Message at all: every byte one the checker chooses */
static void any_end_of_business_trade_date_message(EndOfBusinessTradeDateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* End Of Business Trade Date Message to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_end_of_business_trade_date_message(const EndOfBusinessTradeDateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* End Of Business Trade Date Message off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_end_of_business_trade_date_message(EndOfBusinessTradeDateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of End Of Business Trade Date Message is what was written, byte for byte */
static void equal_end_of_business_trade_date_message(const EndOfBusinessTradeDateMessage *read, const EndOfBusinessTradeDateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  assert(read->event_code == written->event_code);
}

/* End Of Business Trade Date Message: written and read back, then read and written back */
static void check_end_of_business_trade_date_message(void) {
  EndOfBusinessTradeDateMessage sent;
  EndOfBusinessTradeDateMessage got;
  uint8_t wire[7];
  uint8_t again[7];

  any_end_of_business_trade_date_message(&sent);
  assert(encode_end_of_business_trade_date_message(&sent, wire, 0) == 7);
  assert(decode_end_of_business_trade_date_message(&got, wire, 0) == 7);
  equal_end_of_business_trade_date_message(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_business_trade_date_message(&got, wire, 0) == 7);
  assert(encode_end_of_business_trade_date_message(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Future Symbol Directory Message: 179 bytes ------------------------------ */

/* The Future Symbol Directory message describes futures contract */
typedef struct {
  uint8_t nanoseconds[4];                   /* bytes 0 to 3 */
  uint8_t trade_date[2];                    /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];       /* bytes 6 to 9 */
  uint8_t symbol_name[32];                  /* bytes 10 to 41 */
  uint8_t long_name[60];                    /* bytes 42 to 101 */
  uint8_t isin[12];                         /* bytes 102 to 113 */
  uint8_t exchange[6];                      /* bytes 114 to 119 */
  uint8_t instrument[6];                    /* bytes 120 to 125 */
  uint8_t cfi_code[6];                      /* bytes 126 to 131 */
  uint8_t expiry_year[2];                   /* bytes 132 to 133 */
  uint8_t expiry_month;                     /* byte 134 */
  uint8_t price_display_decimals;           /* byte 135 */
  uint8_t price_fractional_denominator[4];  /* bytes 136 to 139 */
  uint8_t price_minimum_tick[4];            /* bytes 140 to 143 */
  uint8_t last_trading_date[4];             /* bytes 144 to 147 */
  uint8_t prior_day_settlement[8];          /* bytes 148 to 155 */
  uint8_t currency[3];                      /* bytes 156 to 158 */
  uint8_t lot_size_or_face_value[8];        /* bytes 159 to 166 */
  uint8_t maturity_value;                   /* byte 167 */
  uint8_t coupon_rate[2];                   /* bytes 168 to 169 */
  uint8_t payments_per_year;                /* byte 170 */
  uint8_t block_lot_size[4];                /* bytes 171 to 174 */
  uint8_t expiry_date[4];                   /* bytes 175 to 178 */
} FutureSymbolDirectoryMessage;

/* any Future Symbol Directory Message at all: every byte one the checker chooses */
static void any_future_symbol_directory_message(FutureSymbolDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->symbol_name[i] = arbitrary(); }
  for (size_t i = 0; i < 60; i++) { record->long_name[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->exchange[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiry_year[i] = arbitrary(); }
  record->expiry_month = arbitrary();
  record->price_display_decimals = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_fractional_denominator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_minimum_tick[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->prior_day_settlement[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lot_size_or_face_value[i] = arbitrary(); }
  record->maturity_value = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->coupon_rate[i] = arbitrary(); }
  record->payments_per_year = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->block_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = arbitrary(); }
}

/* Future Symbol Directory Message to the wire: 179 bytes from at, returning where the next byte goes */
static size_t encode_future_symbol_directory_message(const FutureSymbolDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->symbol_name[i]; }
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->long_name[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->exchange[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cfi_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiry_year[i]; }
  wire[at++] = record->expiry_month;
  wire[at++] = record->price_display_decimals;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_fractional_denominator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_minimum_tick[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trading_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->prior_day_settlement[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lot_size_or_face_value[i]; }
  wire[at++] = record->maturity_value;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->coupon_rate[i]; }
  wire[at++] = record->payments_per_year;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_lot_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expiry_date[i]; }

  return at;
}

/* Future Symbol Directory Message off the wire: 179 bytes from at, returning where the next byte lies */
static size_t decode_future_symbol_directory_message(FutureSymbolDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->symbol_name[i] = wire[at++]; }
  for (size_t i = 0; i < 60; i++) { record->long_name[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->exchange[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiry_year[i] = wire[at++]; }
  record->expiry_month = wire[at++];
  record->price_display_decimals = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_fractional_denominator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_minimum_tick[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->prior_day_settlement[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lot_size_or_face_value[i] = wire[at++]; }
  record->maturity_value = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->coupon_rate[i] = wire[at++]; }
  record->payments_per_year = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->block_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = wire[at++]; }

  return at;
}

/* what was read of Future Symbol Directory Message is what was written, byte for byte */
static void equal_future_symbol_directory_message(const FutureSymbolDirectoryMessage *read, const FutureSymbolDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->symbol_name[i] == written->symbol_name[i]); }
  for (size_t i = 0; i < 60; i++) { assert(read->long_name[i] == written->long_name[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->exchange[i] == written->exchange[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cfi_code[i] == written->cfi_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiry_year[i] == written->expiry_year[i]); }
  assert(read->expiry_month == written->expiry_month);
  assert(read->price_display_decimals == written->price_display_decimals);
  for (size_t i = 0; i < 4; i++) { assert(read->price_fractional_denominator[i] == written->price_fractional_denominator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_minimum_tick[i] == written->price_minimum_tick[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trading_date[i] == written->last_trading_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->prior_day_settlement[i] == written->prior_day_settlement[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lot_size_or_face_value[i] == written->lot_size_or_face_value[i]); }
  assert(read->maturity_value == written->maturity_value);
  for (size_t i = 0; i < 2; i++) { assert(read->coupon_rate[i] == written->coupon_rate[i]); }
  assert(read->payments_per_year == written->payments_per_year);
  for (size_t i = 0; i < 4; i++) { assert(read->block_lot_size[i] == written->block_lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
}

/* Future Symbol Directory Message: written and read back, then read and written back */
static void check_future_symbol_directory_message(void) {
  FutureSymbolDirectoryMessage sent;
  FutureSymbolDirectoryMessage got;
  uint8_t wire[179];
  uint8_t again[179];

  any_future_symbol_directory_message(&sent);
  assert(encode_future_symbol_directory_message(&sent, wire, 0) == 179);
  assert(decode_future_symbol_directory_message(&got, wire, 0) == 179);
  equal_future_symbol_directory_message(&got, &sent);

  for (size_t i = 0; i < 179; i++) { wire[i] = arbitrary(); }
  assert(decode_future_symbol_directory_message(&got, wire, 0) == 179);
  assert(encode_future_symbol_directory_message(&got, again, 0) == 179);
  for (size_t i = 0; i < 179; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Symbol Directory Message: 219 bytes ----------------------------- */

/* The Options Symbol Directory message describes options and warrants contracts. */
typedef struct {
  uint8_t nanoseconds[4];                          /* bytes 0 to 3 */
  uint8_t trade_date[2];                           /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];              /* bytes 6 to 9 */
  uint8_t symbol_name[32];                         /* bytes 10 to 41 */
  uint8_t long_name[60];                           /* bytes 42 to 101 */
  uint8_t isin[12];                                /* bytes 102 to 113 */
  uint8_t exchange[6];                             /* bytes 114 to 119 */
  uint8_t instrument[6];                           /* bytes 120 to 125 */
  uint8_t cfi_code[6];                             /* bytes 126 to 131 */
  uint8_t expiry_year[2];                          /* bytes 132 to 133 */
  uint8_t expiry_month;                            /* byte 134 */
  uint8_t option_type;                             /* byte 135 */
  uint8_t strike[8];                               /* bytes 136 to 143 */
  uint8_t underlying_tradeable_instrument_id[4];   /* bytes 144 to 147 */
  uint8_t price_display_decimals;                  /* byte 148 */
  uint8_t price_fractional_denominator[4];         /* bytes 149 to 152 */
  uint8_t price_minimum_tick[4];                   /* bytes 153 to 156 */
  uint8_t strike_price_decimal_position;           /* byte 157 */
  uint8_t strike_price_fractional_denominator[4];  /* bytes 158 to 161 */
  uint8_t strike_price_minimum_tick[4];            /* bytes 162 to 165 */
  uint8_t last_trading_date[4];                    /* bytes 166 to 169 */
  uint8_t prior_day_settlement[8];                 /* bytes 170 to 177 */
  uint8_t volatility[8];                           /* bytes 178 to 185 */
  uint8_t currency[3];                             /* bytes 186 to 188 */
  uint8_t lot_size_or_face_value[8];               /* bytes 189 to 196 */
  uint8_t maturity_value;                          /* byte 197 */
  uint8_t coupon_rate[2];                          /* bytes 198 to 199 */
  uint8_t payments_per_year;                       /* byte 200 */
  uint8_t block_lot_size[4];                       /* bytes 201 to 204 */
  uint8_t expiry_date[4];                          /* bytes 205 to 208 */
  uint8_t basis_of_quotation[10];                  /* bytes 209 to 218 */
} OptionsSymbolDirectoryMessage;

/* any Options Symbol Directory Message at all: every byte one the checker chooses */
static void any_options_symbol_directory_message(OptionsSymbolDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->symbol_name[i] = arbitrary(); }
  for (size_t i = 0; i < 60; i++) { record->long_name[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->exchange[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiry_year[i] = arbitrary(); }
  record->expiry_month = arbitrary();
  record->option_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_tradeable_instrument_id[i] = arbitrary(); }
  record->price_display_decimals = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_fractional_denominator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_minimum_tick[i] = arbitrary(); }
  record->strike_price_decimal_position = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strike_price_fractional_denominator[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price_minimum_tick[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->prior_day_settlement[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lot_size_or_face_value[i] = arbitrary(); }
  record->maturity_value = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->coupon_rate[i] = arbitrary(); }
  record->payments_per_year = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->block_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->basis_of_quotation[i] = arbitrary(); }
}

/* Options Symbol Directory Message to the wire: 219 bytes from at, returning where the next byte goes */
static size_t encode_options_symbol_directory_message(const OptionsSymbolDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->symbol_name[i]; }
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->long_name[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->exchange[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cfi_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiry_year[i]; }
  wire[at++] = record->expiry_month;
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_tradeable_instrument_id[i]; }
  wire[at++] = record->price_display_decimals;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_fractional_denominator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_minimum_tick[i]; }
  wire[at++] = record->strike_price_decimal_position;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price_fractional_denominator[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price_minimum_tick[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trading_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->prior_day_settlement[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lot_size_or_face_value[i]; }
  wire[at++] = record->maturity_value;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->coupon_rate[i]; }
  wire[at++] = record->payments_per_year;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_lot_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expiry_date[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->basis_of_quotation[i]; }

  return at;
}

/* Options Symbol Directory Message off the wire: 219 bytes from at, returning where the next byte lies */
static size_t decode_options_symbol_directory_message(OptionsSymbolDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->symbol_name[i] = wire[at++]; }
  for (size_t i = 0; i < 60; i++) { record->long_name[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->exchange[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiry_year[i] = wire[at++]; }
  record->expiry_month = wire[at++];
  record->option_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_tradeable_instrument_id[i] = wire[at++]; }
  record->price_display_decimals = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_fractional_denominator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_minimum_tick[i] = wire[at++]; }
  record->strike_price_decimal_position = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strike_price_fractional_denominator[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price_minimum_tick[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->prior_day_settlement[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lot_size_or_face_value[i] = wire[at++]; }
  record->maturity_value = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->coupon_rate[i] = wire[at++]; }
  record->payments_per_year = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->block_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->basis_of_quotation[i] = wire[at++]; }

  return at;
}

/* what was read of Options Symbol Directory Message is what was written, byte for byte */
static void equal_options_symbol_directory_message(const OptionsSymbolDirectoryMessage *read, const OptionsSymbolDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->symbol_name[i] == written->symbol_name[i]); }
  for (size_t i = 0; i < 60; i++) { assert(read->long_name[i] == written->long_name[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->exchange[i] == written->exchange[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cfi_code[i] == written->cfi_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiry_year[i] == written->expiry_year[i]); }
  assert(read->expiry_month == written->expiry_month);
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 8; i++) { assert(read->strike[i] == written->strike[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_tradeable_instrument_id[i] == written->underlying_tradeable_instrument_id[i]); }
  assert(read->price_display_decimals == written->price_display_decimals);
  for (size_t i = 0; i < 4; i++) { assert(read->price_fractional_denominator[i] == written->price_fractional_denominator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_minimum_tick[i] == written->price_minimum_tick[i]); }
  assert(read->strike_price_decimal_position == written->strike_price_decimal_position);
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price_fractional_denominator[i] == written->strike_price_fractional_denominator[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price_minimum_tick[i] == written->strike_price_minimum_tick[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trading_date[i] == written->last_trading_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->prior_day_settlement[i] == written->prior_day_settlement[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lot_size_or_face_value[i] == written->lot_size_or_face_value[i]); }
  assert(read->maturity_value == written->maturity_value);
  for (size_t i = 0; i < 2; i++) { assert(read->coupon_rate[i] == written->coupon_rate[i]); }
  assert(read->payments_per_year == written->payments_per_year);
  for (size_t i = 0; i < 4; i++) { assert(read->block_lot_size[i] == written->block_lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->basis_of_quotation[i] == written->basis_of_quotation[i]); }
}

/* Options Symbol Directory Message: written and read back, then read and written back */
static void check_options_symbol_directory_message(void) {
  OptionsSymbolDirectoryMessage sent;
  OptionsSymbolDirectoryMessage got;
  uint8_t wire[219];
  uint8_t again[219];

  any_options_symbol_directory_message(&sent);
  assert(encode_options_symbol_directory_message(&sent, wire, 0) == 219);
  assert(decode_options_symbol_directory_message(&got, wire, 0) == 219);
  equal_options_symbol_directory_message(&got, &sent);

  for (size_t i = 0; i < 219; i++) { wire[i] = arbitrary(); }
  assert(decode_options_symbol_directory_message(&got, wire, 0) == 219);
  assert(encode_options_symbol_directory_message(&got, again, 0) == 219);
  for (size_t i = 0; i < 219; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book State Message: 11 bytes -------------------------------------- */

/* This message indicates the current session state of a contract to the market */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t session_state;               /* byte 10 */
} OrderBookStateMessage;

/* any Order Book State Message at all: every byte one the checker chooses */
static void any_order_book_state_message(OrderBookStateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  record->session_state = arbitrary();
}

/* Order Book State Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_order_book_state_message(const OrderBookStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  wire[at++] = record->session_state;

  return at;
}

/* Order Book State Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_order_book_state_message(OrderBookStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  record->session_state = wire[at++];

  return at;
}

/* what was read of Order Book State Message is what was written, byte for byte */
static void equal_order_book_state_message(const OrderBookStateMessage *read, const OrderBookStateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  assert(read->session_state == written->session_state);
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

/* ---- Add Order Message: 39 bytes --------------------------------------------- */

/* An Order Added message indicates a new order or a restated order that has been accepted by the matching engine and added to the order book */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t side;                        /* byte 10 */
  uint8_t order_id[8];                 /* bytes 11 to 18 */
  uint8_t order_book_priority[8];      /* bytes 19 to 26 */
  uint8_t quantity[4];                 /* bytes 27 to 30 */
  uint8_t price[8];                    /* bytes 31 to 38 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_book_priority[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Add Order Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_book_priority[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Add Order Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_book_priority[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_book_priority[i] == written->order_book_priority[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 39);
  assert(decode_add_order_message(&got, wire, 0) == 39);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 39);
  assert(encode_add_order_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Volume Cancelled Message: 23 bytes -------------------------------- */

/* An Order Volume Cancelled message is sent when an order is modified as a result of partial cancellation of volume */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t side;                        /* byte 10 */
  uint8_t order_id[8];                 /* bytes 11 to 18 */
  uint8_t quantity[4];                 /* bytes 19 to 22 */
} OrderVolumeCancelledMessage;

/* any Order Volume Cancelled Message at all: every byte one the checker chooses */
static void any_order_volume_cancelled_message(OrderVolumeCancelledMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
}

/* Order Volume Cancelled Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_order_volume_cancelled_message(const OrderVolumeCancelledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Order Volume Cancelled Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_order_volume_cancelled_message(OrderVolumeCancelledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Order Volume Cancelled Message is what was written, byte for byte */
static void equal_order_volume_cancelled_message(const OrderVolumeCancelledMessage *read, const OrderVolumeCancelledMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
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

/* This message is sent whenever an order in the book is cancelled by the owner, expired, cancelled by the exchange, purged or volume cancelled */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t side;                        /* byte 10 */
  uint8_t order_id[8];                 /* bytes 11 to 18 */
} OrderDeletedMessage;

/* any Order Deleted Message at all: every byte one the checker chooses */
static void any_order_deleted_message(OrderDeletedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Order Deleted Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_order_deleted_message(const OrderDeletedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Order Deleted Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_order_deleted_message(OrderDeletedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Deleted Message is what was written, byte for byte */
static void equal_order_deleted_message(const OrderDeletedMessage *read, const OrderDeletedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
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

/* ---- Order Executed Message: 55 bytes ---------------------------------------- */

/* This message is sent whenever a resting order of the book is executed in whole or in part and the counterparty to the trade is an aggressive order */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t side;                        /* byte 10 */
  uint8_t order_id[8];                 /* bytes 11 to 18 */
  uint8_t quantity_remaining[4];       /* bytes 19 to 22 */
  uint8_t trade_type;                  /* byte 23 */
  uint8_t trade_id[8];                 /* bytes 24 to 31 */
  uint8_t executed_quantity[4];        /* bytes 32 to 35 */
  uint8_t trade_price[8];              /* bytes 36 to 43 */
  uint8_t combination_trade_id[8];     /* bytes 44 to 51 */
  uint8_t counter_party_id[3];         /* bytes 52 to 54 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_remaining[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->combination_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->counter_party_id[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_remaining[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->combination_trade_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->counter_party_id[i]; }

  return at;
}

/* Order Executed Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_remaining[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->combination_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->counter_party_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_remaining[i] == written->quantity_remaining[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->combination_trade_id[i] == written->combination_trade_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->counter_party_id[i] == written->counter_party_id[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 55);
  assert(decode_order_executed_message(&got, wire, 0) == 55);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 55);
  assert(encode_order_executed_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Order Executed Message: 52 bytes -------------------------------- */

/* This message is sent when orders are executed in the auction at the open of the market */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t side;                        /* byte 10 */
  uint8_t order_id[8];                 /* bytes 11 to 18 */
  uint8_t quantity_remaining[4];       /* bytes 19 to 22 */
  uint8_t trade_type;                  /* byte 23 */
  uint8_t trade_id[8];                 /* bytes 24 to 31 */
  uint8_t executed_quantity[4];        /* bytes 32 to 35 */
  uint8_t trade_price[8];              /* bytes 36 to 43 */
  uint8_t opposite_order_id[8];        /* bytes 44 to 51 */
} AuctionOrderExecutedMessage;

/* any Auction Order Executed Message at all: every byte one the checker chooses */
static void any_auction_order_executed_message(AuctionOrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_remaining[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opposite_order_id[i] = arbitrary(); }
}

/* Auction Order Executed Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_auction_order_executed_message(const AuctionOrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_remaining[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opposite_order_id[i]; }

  return at;
}

/* Auction Order Executed Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_auction_order_executed_message(AuctionOrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_remaining[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opposite_order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Order Executed Message is what was written, byte for byte */
static void equal_auction_order_executed_message(const AuctionOrderExecutedMessage *read, const AuctionOrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_remaining[i] == written->quantity_remaining[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opposite_order_id[i] == written->opposite_order_id[i]); }
}

/* Auction Order Executed Message: written and read back, then read and written back */
static void check_auction_order_executed_message(void) {
  AuctionOrderExecutedMessage sent;
  AuctionOrderExecutedMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_auction_order_executed_message(&sent);
  assert(encode_auction_order_executed_message(&sent, wire, 0) == 52);
  assert(decode_auction_order_executed_message(&got, wire, 0) == 52);
  equal_auction_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_order_executed_message(&got, wire, 0) == 52);
  assert(encode_auction_order_executed_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Combination Order Executed Message: 65 bytes ---------------------------- */

/* This message is sent whenever a resting order is matched with an open leg of a resting combination order in whole or in part */
typedef struct {
  uint8_t nanoseconds[4];                       /* bytes 0 to 3 */
  uint8_t trade_date[2];                        /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];           /* bytes 6 to 9 */
  uint8_t side;                                 /* byte 10 */
  uint8_t order_id[8];                          /* bytes 11 to 18 */
  uint8_t quantity_remaining[4];                /* bytes 19 to 22 */
  uint8_t trade_type;                           /* byte 23 */
  uint8_t trade_id[8];                          /* bytes 24 to 31 */
  uint8_t executed_quantity[4];                 /* bytes 32 to 35 */
  uint8_t trade_price[8];                       /* bytes 36 to 43 */
  uint8_t opposite_tradeable_instrument_id[4];  /* bytes 44 to 47 */
  uint8_t opposite_side;                        /* byte 48 */
  uint8_t opposite_order_id[8];                 /* bytes 49 to 56 */
  uint8_t combination_trade_id[8];              /* bytes 57 to 64 */
} CombinationOrderExecutedMessage;

/* any Combination Order Executed Message at all: every byte one the checker chooses */
static void any_combination_order_executed_message(CombinationOrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_remaining[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opposite_tradeable_instrument_id[i] = arbitrary(); }
  record->opposite_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->opposite_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->combination_trade_id[i] = arbitrary(); }
}

/* Combination Order Executed Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_combination_order_executed_message(const CombinationOrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_remaining[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opposite_tradeable_instrument_id[i]; }
  wire[at++] = record->opposite_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opposite_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->combination_trade_id[i]; }

  return at;
}

/* Combination Order Executed Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_combination_order_executed_message(CombinationOrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_remaining[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opposite_tradeable_instrument_id[i] = wire[at++]; }
  record->opposite_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->opposite_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->combination_trade_id[i] = wire[at++]; }

  return at;
}

/* what was read of Combination Order Executed Message is what was written, byte for byte */
static void equal_combination_order_executed_message(const CombinationOrderExecutedMessage *read, const CombinationOrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_remaining[i] == written->quantity_remaining[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opposite_tradeable_instrument_id[i] == written->opposite_tradeable_instrument_id[i]); }
  assert(read->opposite_side == written->opposite_side);
  for (size_t i = 0; i < 8; i++) { assert(read->opposite_order_id[i] == written->opposite_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->combination_trade_id[i] == written->combination_trade_id[i]); }
}

/* Combination Order Executed Message: written and read back, then read and written back */
static void check_combination_order_executed_message(void) {
  CombinationOrderExecutedMessage sent;
  CombinationOrderExecutedMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_combination_order_executed_message(&sent);
  assert(encode_combination_order_executed_message(&sent, wire, 0) == 65);
  assert(decode_combination_order_executed_message(&got, wire, 0) == 65);
  equal_combination_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_combination_order_executed_message(&got, wire, 0) == 65);
  assert(encode_combination_order_executed_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Implied Order Added Message: 39 bytes ----------------------------------- */

/* This message is a similar format to the Order Added message, except the nature of this order is it has an implied price, implied volume and a priority that is derived from two or more “real” orders deriving the implied price */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t side;                        /* byte 10 */
  uint8_t order_id[8];                 /* bytes 11 to 18 */
  uint8_t order_book_priority[8];      /* bytes 19 to 26 */
  uint8_t quantity[4];                 /* bytes 27 to 30 */
  uint8_t price[8];                    /* bytes 31 to 38 */
} ImpliedOrderAddedMessage;

/* any Implied Order Added Message at all: every byte one the checker chooses */
static void any_implied_order_added_message(ImpliedOrderAddedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_book_priority[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Implied Order Added Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_implied_order_added_message(const ImpliedOrderAddedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_book_priority[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Implied Order Added Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_implied_order_added_message(ImpliedOrderAddedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_book_priority[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Implied Order Added Message is what was written, byte for byte */
static void equal_implied_order_added_message(const ImpliedOrderAddedMessage *read, const ImpliedOrderAddedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_book_priority[i] == written->order_book_priority[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Implied Order Added Message: written and read back, then read and written back */
static void check_implied_order_added_message(void) {
  ImpliedOrderAddedMessage sent;
  ImpliedOrderAddedMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_implied_order_added_message(&sent);
  assert(encode_implied_order_added_message(&sent, wire, 0) == 39);
  assert(decode_implied_order_added_message(&got, wire, 0) == 39);
  equal_implied_order_added_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_implied_order_added_message(&got, wire, 0) == 39);
  assert(encode_implied_order_added_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Implied Order Replaced Message: 39 bytes -------------------------------- */

/* This message notifies the subscriber that an existing implied order is to be replaced when the implied price, volume or priority has changed due to a price or volume movement of “real” orders for a side of a single Tradeable Instrument Id */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t side;                        /* byte 10 */
  uint8_t order_id[8];                 /* bytes 11 to 18 */
  uint8_t order_book_priority[8];      /* bytes 19 to 26 */
  uint8_t quantity[4];                 /* bytes 27 to 30 */
  uint8_t price[8];                    /* bytes 31 to 38 */
} ImpliedOrderReplacedMessage;

/* any Implied Order Replaced Message at all: every byte one the checker chooses */
static void any_implied_order_replaced_message(ImpliedOrderReplacedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_book_priority[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Implied Order Replaced Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_implied_order_replaced_message(const ImpliedOrderReplacedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_book_priority[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Implied Order Replaced Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_implied_order_replaced_message(ImpliedOrderReplacedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_book_priority[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Implied Order Replaced Message is what was written, byte for byte */
static void equal_implied_order_replaced_message(const ImpliedOrderReplacedMessage *read, const ImpliedOrderReplacedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_book_priority[i] == written->order_book_priority[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Implied Order Replaced Message: written and read back, then read and written back */
static void check_implied_order_replaced_message(void) {
  ImpliedOrderReplacedMessage sent;
  ImpliedOrderReplacedMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_implied_order_replaced_message(&sent);
  assert(encode_implied_order_replaced_message(&sent, wire, 0) == 39);
  assert(decode_implied_order_replaced_message(&got, wire, 0) == 39);
  equal_implied_order_replaced_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_implied_order_replaced_message(&got, wire, 0) == 39);
  assert(encode_implied_order_replaced_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Implied Order Deleted Message: 19 bytes --------------------------------- */

/* This message is sent whenever the implied pricing or volume has changed due to price or volume movement of “real” orders for a side of a single contract number. When received, any implied volume is no longer accessible so the “implied” order of the indicated side must be removed from the book */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t side;                        /* byte 10 */
  uint8_t order_id[8];                 /* bytes 11 to 18 */
} ImpliedOrderDeletedMessage;

/* any Implied Order Deleted Message at all: every byte one the checker chooses */
static void any_implied_order_deleted_message(ImpliedOrderDeletedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Implied Order Deleted Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_implied_order_deleted_message(const ImpliedOrderDeletedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Implied Order Deleted Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_implied_order_deleted_message(ImpliedOrderDeletedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Implied Order Deleted Message is what was written, byte for byte */
static void equal_implied_order_deleted_message(const ImpliedOrderDeletedMessage *read, const ImpliedOrderDeletedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
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

/* ---- Trade Executed Message: 45 bytes ---------------------------------------- */

/* The Trade Message is designed to provide details for executions in combination order books. Trade Executed messages are reported in the same sequence as order execution messages are reported */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t trade_type;                  /* byte 10 */
  uint8_t trade_id[8];                 /* bytes 11 to 18 */
  uint8_t executed_quantity[4];        /* bytes 19 to 22 */
  uint8_t trade_price[8];              /* bytes 23 to 30 */
  uint8_t combination_trade_id[8];     /* bytes 31 to 38 */
  uint8_t participant_id_buyer[3];     /* bytes 39 to 41 */
  uint8_t participant_id_seller[3];    /* bytes 42 to 44 */
} TradeExecutedMessage;

/* any Trade Executed Message at all: every byte one the checker chooses */
static void any_trade_executed_message(TradeExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->combination_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->participant_id_buyer[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->participant_id_seller[i] = arbitrary(); }
}

/* Trade Executed Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_trade_executed_message(const TradeExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->combination_trade_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->participant_id_buyer[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->participant_id_seller[i]; }

  return at;
}

/* Trade Executed Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_trade_executed_message(TradeExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->combination_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->participant_id_buyer[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->participant_id_seller[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Executed Message is what was written, byte for byte */
static void equal_trade_executed_message(const TradeExecutedMessage *read, const TradeExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->combination_trade_id[i] == written->combination_trade_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->participant_id_buyer[i] == written->participant_id_buyer[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->participant_id_seller[i] == written->participant_id_seller[i]); }
}

/* Trade Executed Message: written and read back, then read and written back */
static void check_trade_executed_message(void) {
  TradeExecutedMessage sent;
  TradeExecutedMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_trade_executed_message(&sent);
  assert(encode_trade_executed_message(&sent, wire, 0) == 45);
  assert(decode_trade_executed_message(&got, wire, 0) == 45);
  equal_trade_executed_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_executed_message(&got, wire, 0) == 45);
  assert(encode_trade_executed_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Combination Trade Executed Message: 79 bytes ---------------------------- */

/* The Combination Trade Executed Message is designed to provide details for executions where one or both orders are resting from a different order book id from the order book id of the trade */
typedef struct {
  uint8_t nanoseconds[4];                     /* bytes 0 to 3 */
  uint8_t trade_date[2];                      /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];         /* bytes 6 to 9 */
  uint8_t trade_type;                         /* byte 10 */
  uint8_t trade_id[8];                        /* bytes 11 to 18 */
  uint8_t executed_quantity[4];               /* bytes 19 to 22 */
  uint8_t trade_price[8];                     /* bytes 23 to 30 */
  uint8_t buyer_tradeable_instrument_id[4];   /* bytes 31 to 34 */
  uint8_t buyer_side;                         /* byte 35 */
  uint8_t buyer_order_id[8];                  /* bytes 36 to 43 */
  uint8_t buyer_combination_trade_id[8];      /* bytes 44 to 51 */
  uint8_t buyer_participant_id[3];            /* bytes 52 to 54 */
  uint8_t seller_tradeable_instrument_id[4];  /* bytes 55 to 58 */
  uint8_t seller_side;                        /* byte 59 */
  uint8_t seller_order_id[8];                 /* bytes 60 to 67 */
  uint8_t seller_combination_trade_id[8];     /* bytes 68 to 75 */
  uint8_t seller_participant_id[3];           /* bytes 76 to 78 */
} CombinationTradeExecutedMessage;

/* any Combination Trade Executed Message at all: every byte one the checker chooses */
static void any_combination_trade_executed_message(CombinationTradeExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buyer_tradeable_instrument_id[i] = arbitrary(); }
  record->buyer_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->buyer_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->buyer_combination_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->buyer_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->seller_tradeable_instrument_id[i] = arbitrary(); }
  record->seller_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->seller_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->seller_combination_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->seller_participant_id[i] = arbitrary(); }
}

/* Combination Trade Executed Message to the wire: 79 bytes from at, returning where the next byte goes */
static size_t encode_combination_trade_executed_message(const CombinationTradeExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buyer_tradeable_instrument_id[i]; }
  wire[at++] = record->buyer_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buyer_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->buyer_combination_trade_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->buyer_participant_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seller_tradeable_instrument_id[i]; }
  wire[at++] = record->seller_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->seller_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->seller_combination_trade_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->seller_participant_id[i]; }

  return at;
}

/* Combination Trade Executed Message off the wire: 79 bytes from at, returning where the next byte lies */
static size_t decode_combination_trade_executed_message(CombinationTradeExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buyer_tradeable_instrument_id[i] = wire[at++]; }
  record->buyer_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->buyer_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->buyer_combination_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->buyer_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->seller_tradeable_instrument_id[i] = wire[at++]; }
  record->seller_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->seller_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->seller_combination_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->seller_participant_id[i] = wire[at++]; }

  return at;
}

/* what was read of Combination Trade Executed Message is what was written, byte for byte */
static void equal_combination_trade_executed_message(const CombinationTradeExecutedMessage *read, const CombinationTradeExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buyer_tradeable_instrument_id[i] == written->buyer_tradeable_instrument_id[i]); }
  assert(read->buyer_side == written->buyer_side);
  for (size_t i = 0; i < 8; i++) { assert(read->buyer_order_id[i] == written->buyer_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->buyer_combination_trade_id[i] == written->buyer_combination_trade_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->buyer_participant_id[i] == written->buyer_participant_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->seller_tradeable_instrument_id[i] == written->seller_tradeable_instrument_id[i]); }
  assert(read->seller_side == written->seller_side);
  for (size_t i = 0; i < 8; i++) { assert(read->seller_order_id[i] == written->seller_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->seller_combination_trade_id[i] == written->seller_combination_trade_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->seller_participant_id[i] == written->seller_participant_id[i]); }
}

/* Combination Trade Executed Message: written and read back, then read and written back */
static void check_combination_trade_executed_message(void) {
  CombinationTradeExecutedMessage sent;
  CombinationTradeExecutedMessage got;
  uint8_t wire[79];
  uint8_t again[79];

  any_combination_trade_executed_message(&sent);
  assert(encode_combination_trade_executed_message(&sent, wire, 0) == 79);
  assert(decode_combination_trade_executed_message(&got, wire, 0) == 79);
  equal_combination_trade_executed_message(&got, &sent);

  for (size_t i = 0; i < 79; i++) { wire[i] = arbitrary(); }
  assert(decode_combination_trade_executed_message(&got, wire, 0) == 79);
  assert(encode_combination_trade_executed_message(&got, again, 0) == 79);
  for (size_t i = 0; i < 79; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancellation Message: 18 bytes ------------------------------------ */

/* This message is sent whenever a trade is cancelled by ASX */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t trade_id[8];                 /* bytes 10 to 17 */
} TradeCancellationMessage;

/* any Trade Cancellation Message at all: every byte one the checker chooses */
static void any_trade_cancellation_message(TradeCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
}

/* Trade Cancellation Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancellation_message(const TradeCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }

  return at;
}

/* Trade Cancellation Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancellation_message(TradeCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancellation Message is what was written, byte for byte */
static void equal_trade_cancellation_message(const TradeCancellationMessage *read, const TradeCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
}

/* Trade Cancellation Message: written and read back, then read and written back */
static void check_trade_cancellation_message(void) {
  TradeCancellationMessage sent;
  TradeCancellationMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_trade_cancellation_message(&sent);
  assert(encode_trade_cancellation_message(&sent, wire, 0) == 18);
  assert(decode_trade_cancellation_message(&got, wire, 0) == 18);
  equal_trade_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancellation_message(&got, wire, 0) == 18);
  assert(encode_trade_cancellation_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Equilibrium Price Message: 42 bytes ------------------------------------- */

/* This message is disseminated in response to changes in the equilibrium price for an order book during a pre-open period */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t equilibrium_price[8];        /* bytes 10 to 17 */
  uint8_t matched_quantity[8];         /* bytes 18 to 25 */
  uint8_t bid_quantity[8];             /* bytes 26 to 33 */
  uint8_t ask_quantity[8];             /* bytes 34 to 41 */
} EquilibriumPriceMessage;

/* any Equilibrium Price Message at all: every byte one the checker chooses */
static void any_equilibrium_price_message(EquilibriumPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->equilibrium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->matched_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_quantity[i] = arbitrary(); }
}

/* Equilibrium Price Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_equilibrium_price_message(const EquilibriumPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->equilibrium_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matched_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_quantity[i]; }

  return at;
}

/* Equilibrium Price Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_equilibrium_price_message(EquilibriumPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->equilibrium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->matched_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Equilibrium Price Message is what was written, byte for byte */
static void equal_equilibrium_price_message(const EquilibriumPriceMessage *read, const EquilibriumPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->equilibrium_price[i] == written->equilibrium_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->matched_quantity[i] == written->matched_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_quantity[i] == written->bid_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_quantity[i] == written->ask_quantity[i]); }
}

/* Equilibrium Price Message: written and read back, then read and written back */
static void check_equilibrium_price_message(void) {
  EquilibriumPriceMessage sent;
  EquilibriumPriceMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_equilibrium_price_message(&sent);
  assert(encode_equilibrium_price_message(&sent, wire, 0) == 42);
  assert(decode_equilibrium_price_message(&got, wire, 0) == 42);
  equal_equilibrium_price_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_equilibrium_price_message(&got, wire, 0) == 42);
  assert(encode_equilibrium_price_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open High Low Last Trade Adjustment Message: 54 bytes ------------------- */

/* Market trade price adjustments are sent resulting from modifications of Open, High, Low, Last and volume statistics due to market operations, prior to the instrument moving to the next session within the trade date, or at the close of instrument */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t opening_trade[8];            /* bytes 10 to 17 */
  uint8_t highest_trade[8];            /* bytes 18 to 25 */
  uint8_t lowest_trade[8];             /* bytes 26 to 33 */
  uint8_t last_trade[8];               /* bytes 34 to 41 */
  uint8_t last_volume[4];              /* bytes 42 to 45 */
  uint8_t total_traded_volume[8];      /* bytes 46 to 53 */
} OpenHighLowLastTradeAdjustmentMessage;

/* any Open High Low Last Trade Adjustment Message at all: every byte one the checker chooses */
static void any_open_high_low_last_trade_adjustment_message(OpenHighLowLastTradeAdjustmentMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->highest_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lowest_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_traded_volume[i] = arbitrary(); }
}

/* Open High Low Last Trade Adjustment Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_open_high_low_last_trade_adjustment_message(const OpenHighLowLastTradeAdjustmentMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_trade[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->highest_trade[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lowest_trade[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_trade[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_traded_volume[i]; }

  return at;
}

/* Open High Low Last Trade Adjustment Message off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_open_high_low_last_trade_adjustment_message(OpenHighLowLastTradeAdjustmentMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->highest_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lowest_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_traded_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Open High Low Last Trade Adjustment Message is what was written, byte for byte */
static void equal_open_high_low_last_trade_adjustment_message(const OpenHighLowLastTradeAdjustmentMessage *read, const OpenHighLowLastTradeAdjustmentMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_trade[i] == written->opening_trade[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->highest_trade[i] == written->highest_trade[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lowest_trade[i] == written->lowest_trade[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_trade[i] == written->last_trade[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_volume[i] == written->last_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_traded_volume[i] == written->total_traded_volume[i]); }
}

/* Open High Low Last Trade Adjustment Message: written and read back, then read and written back */
static void check_open_high_low_last_trade_adjustment_message(void) {
  OpenHighLowLastTradeAdjustmentMessage sent;
  OpenHighLowLastTradeAdjustmentMessage got;
  uint8_t wire[54];
  uint8_t again[54];

  any_open_high_low_last_trade_adjustment_message(&sent);
  assert(encode_open_high_low_last_trade_adjustment_message(&sent, wire, 0) == 54);
  assert(decode_open_high_low_last_trade_adjustment_message(&got, wire, 0) == 54);
  equal_open_high_low_last_trade_adjustment_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_open_high_low_last_trade_adjustment_message(&got, wire, 0) == 54);
  assert(encode_open_high_low_last_trade_adjustment_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Settlement Message: 54 bytes ------------------------------------- */

/* This message disseminates the final settlement price of a future or option contracts order book for the trade date it pertains to */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t opening_trade[8];            /* bytes 10 to 17 */
  uint8_t highest_trade[8];            /* bytes 18 to 25 */
  uint8_t lowest_trade[8];             /* bytes 26 to 33 */
  uint8_t last_trade[8];               /* bytes 34 to 41 */
  uint8_t last_volume[4];              /* bytes 42 to 45 */
  uint8_t total_traded_volume[8];      /* bytes 46 to 53 */
} MarketSettlementMessage;

/* any Market Settlement Message at all: every byte one the checker chooses */
static void any_market_settlement_message(MarketSettlementMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->highest_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lowest_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_traded_volume[i] = arbitrary(); }
}

/* Market Settlement Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_market_settlement_message(const MarketSettlementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_trade[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->highest_trade[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lowest_trade[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_trade[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_traded_volume[i]; }

  return at;
}

/* Market Settlement Message off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_market_settlement_message(MarketSettlementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->highest_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lowest_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_traded_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Market Settlement Message is what was written, byte for byte */
static void equal_market_settlement_message(const MarketSettlementMessage *read, const MarketSettlementMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_trade[i] == written->opening_trade[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->highest_trade[i] == written->highest_trade[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lowest_trade[i] == written->lowest_trade[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_trade[i] == written->last_trade[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_volume[i] == written->last_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_traded_volume[i] == written->total_traded_volume[i]); }
}

/* Market Settlement Message: written and read back, then read and written back */
static void check_market_settlement_message(void) {
  MarketSettlementMessage sent;
  MarketSettlementMessage got;
  uint8_t wire[54];
  uint8_t again[54];

  any_market_settlement_message(&sent);
  assert(encode_market_settlement_message(&sent, wire, 0) == 54);
  assert(decode_market_settlement_message(&got, wire, 0) == 54);
  equal_market_settlement_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_market_settlement_message(&got, wire, 0) == 54);
  assert(encode_market_settlement_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Text Message: 112 bytes ------------------------------------------------- */

/* This message disseminates free text information describing ad-hoc market events */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t trade_date[2];   /* bytes 4 to 5 */
  uint8_t source_id[6];    /* bytes 6 to 11 */
  uint8_t text[100];       /* bytes 12 to 111 */
} TextMessage;

/* any Text Message at all: every byte one the checker chooses */
static void any_text_message(TextMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->source_id[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->text[i] = arbitrary(); }
}

/* Text Message to the wire: 112 bytes from at, returning where the next byte goes */
static size_t encode_text_message(const TextMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->source_id[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Text Message off the wire: 112 bytes from at, returning where the next byte lies */
static size_t decode_text_message(TextMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->source_id[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Text Message is what was written, byte for byte */
static void equal_text_message(const TextMessage *read, const TextMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->source_id[i] == written->source_id[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->text[i] == written->text[i]); }
}

/* Text Message: written and read back, then read and written back */
static void check_text_message(void) {
  TextMessage sent;
  TextMessage got;
  uint8_t wire[112];
  uint8_t again[112];

  any_text_message(&sent);
  assert(encode_text_message(&sent, wire, 0) == 112);
  assert(decode_text_message(&got, wire, 0) == 112);
  equal_text_message(&got, &sent);

  for (size_t i = 0; i < 112; i++) { wire[i] = arbitrary(); }
  assert(decode_text_message(&got, wire, 0) == 112);
  assert(encode_text_message(&got, again, 0) == 112);
  for (size_t i = 0; i < 112; i++) { assert(again[i] == wire[i]); }
}

/* ---- Request For Quote Message: 15 bytes ------------------------------------- */

/* This message is disseminated for anonymous Request for Quotes (RFQs) from the market */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t rfq_side;                    /* byte 10 */
  uint8_t quantity[4];                 /* bytes 11 to 14 */
} RequestForQuoteMessage;

/* any Request For Quote Message at all: every byte one the checker chooses */
static void any_request_for_quote_message(RequestForQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  record->rfq_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
}

/* Request For Quote Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_request_for_quote_message(const RequestForQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  wire[at++] = record->rfq_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Request For Quote Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_request_for_quote_message(RequestForQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  record->rfq_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Request For Quote Message is what was written, byte for byte */
static void equal_request_for_quote_message(const RequestForQuoteMessage *read, const RequestForQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  assert(read->rfq_side == written->rfq_side);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Request For Quote Message: written and read back, then read and written back */
static void check_request_for_quote_message(void) {
  RequestForQuoteMessage sent;
  RequestForQuoteMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_request_for_quote_message(&sent);
  assert(encode_request_for_quote_message(&sent, wire, 0) == 15);
  assert(decode_request_for_quote_message(&got, wire, 0) == 15);
  equal_request_for_quote_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_request_for_quote_message(&got, wire, 0) == 15);
  assert(encode_request_for_quote_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Anomalous Order Threshold Publish Message: 58 bytes --------------------- */

/* This message disseminates price band information to the market advising the setting, zeroing or adjusting of the Extreme Trade Range price, the Anomalous Order Threshold price and the associated ranges for a contract that requires Market Integrity Rules enforcement */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t aot_price[8];                /* bytes 10 to 17 */
  uint8_t aot_upper_price[8];          /* bytes 18 to 25 */
  uint8_t aot_lower_price[8];          /* bytes 26 to 33 */
  uint8_t etr_price[8];                /* bytes 34 to 41 */
  uint8_t etr_upper_price[8];          /* bytes 42 to 49 */
  uint8_t etr_lower_price[8];          /* bytes 50 to 57 */
} AnomalousOrderThresholdPublishMessage;

/* any Anomalous Order Threshold Publish Message at all: every byte one the checker chooses */
static void any_anomalous_order_threshold_publish_message(AnomalousOrderThresholdPublishMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->aot_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->aot_upper_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->aot_lower_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->etr_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->etr_upper_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->etr_lower_price[i] = arbitrary(); }
}

/* Anomalous Order Threshold Publish Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_anomalous_order_threshold_publish_message(const AnomalousOrderThresholdPublishMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aot_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aot_upper_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aot_lower_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->etr_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->etr_upper_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->etr_lower_price[i]; }

  return at;
}

/* Anomalous Order Threshold Publish Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_anomalous_order_threshold_publish_message(AnomalousOrderThresholdPublishMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->aot_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->aot_upper_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->aot_lower_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->etr_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->etr_upper_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->etr_lower_price[i] = wire[at++]; }

  return at;
}

/* what was read of Anomalous Order Threshold Publish Message is what was written, byte for byte */
static void equal_anomalous_order_threshold_publish_message(const AnomalousOrderThresholdPublishMessage *read, const AnomalousOrderThresholdPublishMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->aot_price[i] == written->aot_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->aot_upper_price[i] == written->aot_upper_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->aot_lower_price[i] == written->aot_lower_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->etr_price[i] == written->etr_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->etr_upper_price[i] == written->etr_upper_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->etr_lower_price[i] == written->etr_lower_price[i]); }
}

/* Anomalous Order Threshold Publish Message: written and read back, then read and written back */
static void check_anomalous_order_threshold_publish_message(void) {
  AnomalousOrderThresholdPublishMessage sent;
  AnomalousOrderThresholdPublishMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_anomalous_order_threshold_publish_message(&sent);
  assert(encode_anomalous_order_threshold_publish_message(&sent, wire, 0) == 58);
  assert(decode_anomalous_order_threshold_publish_message(&got, wire, 0) == 58);
  equal_anomalous_order_threshold_publish_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_anomalous_order_threshold_publish_message(&got, wire, 0) == 58);
  assert(encode_anomalous_order_threshold_publish_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Volume And Open Interest Message: 28 bytes ------------------------------ */

/* This message disseminates Volume and Open Interest (VOI) information for each trade date */
typedef struct {
  uint8_t nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t trade_date[2];               /* bytes 4 to 5 */
  uint8_t tradeable_instrument_id[4];  /* bytes 6 to 9 */
  uint8_t cumulative_volume[8];        /* bytes 10 to 17 */
  uint8_t open_interest[8];            /* bytes 18 to 25 */
  uint8_t voi_trade_date[2];           /* bytes 26 to 27 */
} VolumeAndOpenInterestMessage;

/* any Volume And Open Interest Message at all: every byte one the checker chooses */
static void any_volume_and_open_interest_message(VolumeAndOpenInterestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cumulative_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->voi_trade_date[i] = arbitrary(); }
}

/* Volume And Open Interest Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_volume_and_open_interest_message(const VolumeAndOpenInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tradeable_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cumulative_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_interest[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->voi_trade_date[i]; }

  return at;
}

/* Volume And Open Interest Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_volume_and_open_interest_message(VolumeAndOpenInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tradeable_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cumulative_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->voi_trade_date[i] = wire[at++]; }

  return at;
}

/* what was read of Volume And Open Interest Message is what was written, byte for byte */
static void equal_volume_and_open_interest_message(const VolumeAndOpenInterestMessage *read, const VolumeAndOpenInterestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tradeable_instrument_id[i] == written->tradeable_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cumulative_volume[i] == written->cumulative_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->voi_trade_date[i] == written->voi_trade_date[i]); }
}

/* Volume And Open Interest Message: written and read back, then read and written back */
static void check_volume_and_open_interest_message(void) {
  VolumeAndOpenInterestMessage sent;
  VolumeAndOpenInterestMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_volume_and_open_interest_message(&sent);
  assert(encode_volume_and_open_interest_message(&sent, wire, 0) == 28);
  assert(decode_volume_and_open_interest_message(&got, wire, 0) == 28);
  equal_volume_and_open_interest_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_volume_and_open_interest_message(&got, wire, 0) == 28);
  assert(encode_volume_and_open_interest_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_seconds_message();
  check_end_of_business_trade_date_message();
  check_future_symbol_directory_message();
  check_options_symbol_directory_message();
  check_order_book_state_message();
  check_add_order_message();
  check_order_volume_cancelled_message();
  check_order_deleted_message();
  check_order_executed_message();
  check_auction_order_executed_message();
  check_combination_order_executed_message();
  check_implied_order_added_message();
  check_implied_order_replaced_message();
  check_implied_order_deleted_message();
  check_trade_executed_message();
  check_combination_trade_executed_message();
  check_trade_cancellation_message();
  check_equilibrium_price_message();
  check_open_high_low_last_trade_adjustment_message();
  check_market_settlement_message();
  check_text_message();
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
