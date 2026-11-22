// asx/asxsecurities/mdf/AsxSecurities_Mdf_v1_0.c
/*
 * Australian Securities Exchange Trade Market Data Feed
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

/* Sent every second for which at least one MDF message is being generated. */
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

/* ---- Order Book Directory Message: 366 bytes --------------------------------- */

/* Disseminated at the start of each trading day for all active securities, including halted securities. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];                   /* bytes 0 to 3 */
  uint8_t order_book_id[4];                           /* bytes 4 to 7 */
  uint8_t partition_id;                               /* byte 8 */
  uint8_t symbol[32];                                 /* bytes 9 to 40 */
  uint8_t long_name[32];                              /* bytes 41 to 72 */
  uint8_t isin[12];                                   /* bytes 73 to 84 */
  uint8_t asset_name[32];                             /* bytes 85 to 116 */
  uint8_t financial_product;                          /* byte 117 */
  uint8_t trading_currency[3];                        /* bytes 118 to 120 */
  uint8_t number_of_decimals_in_price[2];             /* bytes 121 to 122 */
  uint8_t number_of_decimals_in_nominal_value[2];     /* bytes 123 to 124 */
  uint8_t round_lot_size[4];                          /* bytes 125 to 128 */
  uint8_t nominal_value[8];                           /* bytes 129 to 136 */
  uint8_t number_of_legs;                             /* byte 137 */
  uint8_t commodity_code[4];                          /* bytes 138 to 141 */
  uint8_t strike_price[8];                            /* bytes 142 to 149 */
  uint8_t expiration_date[4];                         /* bytes 150 to 153 */
  uint8_t number_of_decimals_in_strike_price[2];      /* bytes 154 to 155 */
  uint8_t option_type;                                /* byte 156 */
  uint8_t market_id[4];                               /* bytes 157 to 160 */
  uint8_t exchange_id[4];                             /* bytes 161 to 164 */
  uint8_t number_of_decimals_in[2];                   /* bytes 165 to 166 */
  uint8_t sector_code[4];                             /* bytes 167 to 170 */
  uint8_t number_of_tradable_equities[8];             /* bytes 171 to 178 */
  uint8_t number_of_outstanding_equities[8];          /* bytes 179 to 186 */
  uint8_t last_traded_date[4];                        /* bytes 187 to 190 */
  uint8_t contract_multiplier[8];                     /* bytes 191 to 198 */
  uint8_t multiplier[8];                              /* bytes 199 to 206 */
  uint8_t decimals_in_multiplier[2];                  /* bytes 207 to 208 */
  uint8_t min_order_quantity[8];                      /* bytes 209 to 216 */
  uint8_t max_order_quantity[8];                      /* bytes 217 to 224 */
  uint8_t number_of_settlement_days[4];               /* bytes 225 to 228 */
  uint8_t primary;                                    /* byte 229 */
  uint8_t test_order_book;                            /* byte 230 */
  uint8_t alias_name[32];                             /* bytes 231 to 262 */
  uint8_t settlement_date[4];                         /* bytes 263 to 266 */
  uint8_t tradable;                                   /* byte 267 */
  uint8_t externally_price_sourced;                   /* byte 268 */
  uint8_t deliverable;                                /* byte 269 */
  uint8_t price_unit;                                 /* byte 270 */
  uint8_t issuer[32];                                 /* bytes 271 to 302 */
  uint8_t foreign_ownership_restriction;              /* byte 303 */
  uint8_t last_trading_time[6];                       /* bytes 304 to 309 */
  uint8_t option_style;                               /* byte 310 */
  uint8_t minimum_value_for_initial_trade_report[8];  /* bytes 311 to 318 */
  uint8_t cfi_code[6];                                /* bytes 319 to 324 */
  uint8_t upper_level_series[32];                     /* bytes 325 to 356 */
  uint8_t upper_series_level_order_book_id[4];        /* bytes 357 to 360 */
  uint8_t instrument_type[4];                         /* bytes 361 to 364 */
  uint8_t status;                                     /* byte 365 */
} OrderBookDirectoryMessage;

/* any Order Book Directory Message at all: every byte one the checker chooses */
static void any_order_book_directory_message(OrderBookDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->partition_id = arbitrary();
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->long_name[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->asset_name[i] = arbitrary(); }
  record->financial_product = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->round_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = arbitrary(); }
  record->number_of_legs = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->commodity_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_strike_price[i] = arbitrary(); }
  record->option_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->exchange_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sector_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->number_of_tradable_equities[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->number_of_outstanding_equities[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_traded_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->contract_multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->decimals_in_multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_order_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_order_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_settlement_days[i] = arbitrary(); }
  record->primary = arbitrary();
  record->test_order_book = arbitrary();
  for (size_t i = 0; i < 32; i++) { record->alias_name[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->settlement_date[i] = arbitrary(); }
  record->tradable = arbitrary();
  record->externally_price_sourced = arbitrary();
  record->deliverable = arbitrary();
  record->price_unit = arbitrary();
  for (size_t i = 0; i < 32; i++) { record->issuer[i] = arbitrary(); }
  record->foreign_ownership_restriction = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->last_trading_time[i] = arbitrary(); }
  record->option_style = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->minimum_value_for_initial_trade_report[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->upper_level_series[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->upper_series_level_order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_type[i] = arbitrary(); }
  record->status = arbitrary();
}

/* Order Book Directory Message to the wire: 366 bytes from at, returning where the next byte goes */
static size_t encode_order_book_directory_message(const OrderBookDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->partition_id;
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->long_name[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->asset_name[i]; }
  wire[at++] = record->financial_product;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_currency[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_in_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_in_nominal_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->round_lot_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nominal_value[i]; }
  wire[at++] = record->number_of_legs;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->commodity_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_in_strike_price[i]; }
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_in[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sector_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->number_of_tradable_equities[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->number_of_outstanding_equities[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_traded_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->contract_multiplier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->multiplier[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->decimals_in_multiplier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_order_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_order_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_settlement_days[i]; }
  wire[at++] = record->primary;
  wire[at++] = record->test_order_book;
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->alias_name[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settlement_date[i]; }
  wire[at++] = record->tradable;
  wire[at++] = record->externally_price_sourced;
  wire[at++] = record->deliverable;
  wire[at++] = record->price_unit;
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->issuer[i]; }
  wire[at++] = record->foreign_ownership_restriction;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->last_trading_time[i]; }
  wire[at++] = record->option_style;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_value_for_initial_trade_report[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cfi_code[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->upper_level_series[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->upper_series_level_order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_type[i]; }
  wire[at++] = record->status;

  return at;
}

/* Order Book Directory Message off the wire: 366 bytes from at, returning where the next byte lies */
static size_t decode_order_book_directory_message(OrderBookDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->partition_id = wire[at++];
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->long_name[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->asset_name[i] = wire[at++]; }
  record->financial_product = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_nominal_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->round_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = wire[at++]; }
  record->number_of_legs = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->commodity_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_strike_price[i] = wire[at++]; }
  record->option_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->exchange_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sector_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->number_of_tradable_equities[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->number_of_outstanding_equities[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_traded_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->contract_multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->decimals_in_multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_order_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_order_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_settlement_days[i] = wire[at++]; }
  record->primary = wire[at++];
  record->test_order_book = wire[at++];
  for (size_t i = 0; i < 32; i++) { record->alias_name[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->settlement_date[i] = wire[at++]; }
  record->tradable = wire[at++];
  record->externally_price_sourced = wire[at++];
  record->deliverable = wire[at++];
  record->price_unit = wire[at++];
  for (size_t i = 0; i < 32; i++) { record->issuer[i] = wire[at++]; }
  record->foreign_ownership_restriction = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->last_trading_time[i] = wire[at++]; }
  record->option_style = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->minimum_value_for_initial_trade_report[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->upper_level_series[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->upper_series_level_order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_type[i] = wire[at++]; }
  record->status = wire[at++];

  return at;
}

/* what was read of Order Book Directory Message is what was written, byte for byte */
static void equal_order_book_directory_message(const OrderBookDirectoryMessage *read, const OrderBookDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->partition_id == written->partition_id);
  for (size_t i = 0; i < 32; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->long_name[i] == written->long_name[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->asset_name[i] == written->asset_name[i]); }
  assert(read->financial_product == written->financial_product);
  for (size_t i = 0; i < 3; i++) { assert(read->trading_currency[i] == written->trading_currency[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_price[i] == written->number_of_decimals_in_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_nominal_value[i] == written->number_of_decimals_in_nominal_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->round_lot_size[i] == written->round_lot_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nominal_value[i] == written->nominal_value[i]); }
  assert(read->number_of_legs == written->number_of_legs);
  for (size_t i = 0; i < 4; i++) { assert(read->commodity_code[i] == written->commodity_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_strike_price[i] == written->number_of_decimals_in_strike_price[i]); }
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_id[i] == written->exchange_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in[i] == written->number_of_decimals_in[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sector_code[i] == written->sector_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->number_of_tradable_equities[i] == written->number_of_tradable_equities[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->number_of_outstanding_equities[i] == written->number_of_outstanding_equities[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_traded_date[i] == written->last_traded_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->contract_multiplier[i] == written->contract_multiplier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->multiplier[i] == written->multiplier[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->decimals_in_multiplier[i] == written->decimals_in_multiplier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_order_quantity[i] == written->min_order_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_order_quantity[i] == written->max_order_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_settlement_days[i] == written->number_of_settlement_days[i]); }
  assert(read->primary == written->primary);
  assert(read->test_order_book == written->test_order_book);
  for (size_t i = 0; i < 32; i++) { assert(read->alias_name[i] == written->alias_name[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
  assert(read->tradable == written->tradable);
  assert(read->externally_price_sourced == written->externally_price_sourced);
  assert(read->deliverable == written->deliverable);
  assert(read->price_unit == written->price_unit);
  for (size_t i = 0; i < 32; i++) { assert(read->issuer[i] == written->issuer[i]); }
  assert(read->foreign_ownership_restriction == written->foreign_ownership_restriction);
  for (size_t i = 0; i < 6; i++) { assert(read->last_trading_time[i] == written->last_trading_time[i]); }
  assert(read->option_style == written->option_style);
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_value_for_initial_trade_report[i] == written->minimum_value_for_initial_trade_report[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cfi_code[i] == written->cfi_code[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->upper_level_series[i] == written->upper_level_series[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->upper_series_level_order_book_id[i] == written->upper_series_level_order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_type[i] == written->instrument_type[i]); }
  assert(read->status == written->status);
}

/* Order Book Directory Message: written and read back, then read and written back */
static void check_order_book_directory_message(void) {
  OrderBookDirectoryMessage sent;
  OrderBookDirectoryMessage got;
  uint8_t wire[366];
  uint8_t again[366];

  any_order_book_directory_message(&sent);
  assert(encode_order_book_directory_message(&sent, wire, 0) == 366);
  assert(decode_order_book_directory_message(&got, wire, 0) == 366);
  equal_order_book_directory_message(&got, &sent);

  for (size_t i = 0; i < 366; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_directory_message(&got, wire, 0) == 366);
  assert(encode_order_book_directory_message(&got, again, 0) == 366);
  for (size_t i = 0; i < 366; i++) { assert(again[i] == wire[i]); }
}

/* ---- Exchange Directory Message: 40 bytes ------------------------------------ */

/* Disseminated at the start of each trading day for all active Exchanges in the system. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t exchange_id[4];            /* bytes 4 to 7 */
  uint8_t exchange_name[32];         /* bytes 8 to 39 */
} ExchangeDirectoryMessage;

/* any Exchange Directory Message at all: every byte one the checker chooses */
static void any_exchange_directory_message(ExchangeDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->exchange_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->exchange_name[i] = arbitrary(); }
}

/* Exchange Directory Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_exchange_directory_message(const ExchangeDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->exchange_name[i]; }

  return at;
}

/* Exchange Directory Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_exchange_directory_message(ExchangeDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->exchange_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->exchange_name[i] = wire[at++]; }

  return at;
}

/* what was read of Exchange Directory Message is what was written, byte for byte */
static void equal_exchange_directory_message(const ExchangeDirectoryMessage *read, const ExchangeDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_id[i] == written->exchange_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->exchange_name[i] == written->exchange_name[i]); }
}

/* Exchange Directory Message: written and read back, then read and written back */
static void check_exchange_directory_message(void) {
  ExchangeDirectoryMessage sent;
  ExchangeDirectoryMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_exchange_directory_message(&sent);
  assert(encode_exchange_directory_message(&sent, wire, 0) == 40);
  assert(decode_exchange_directory_message(&got, wire, 0) == 40);
  equal_exchange_directory_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_exchange_directory_message(&got, wire, 0) == 40);
  assert(encode_exchange_directory_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Directory Message: 42 bytes -------------------------------------- */

/* Disseminated at the start of each trading day for all active Markets in the system. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t market_id[4];              /* bytes 4 to 7 */
  uint8_t market_name[32];           /* bytes 8 to 39 */
  uint8_t market_type;               /* byte 40 */
  uint8_t index_market;              /* byte 41 */
} MarketDirectoryMessage;

/* any Market Directory Message at all: every byte one the checker chooses */
static void any_market_directory_message(MarketDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->market_name[i] = arbitrary(); }
  record->market_type = arbitrary();
  record->index_market = arbitrary();
}

/* Market Directory Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_market_directory_message(const MarketDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->market_name[i]; }
  wire[at++] = record->market_type;
  wire[at++] = record->index_market;

  return at;
}

/* Market Directory Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_market_directory_message(MarketDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->market_name[i] = wire[at++]; }
  record->market_type = wire[at++];
  record->index_market = wire[at++];

  return at;
}

/* what was read of Market Directory Message is what was written, byte for byte */
static void equal_market_directory_message(const MarketDirectoryMessage *read, const MarketDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->market_name[i] == written->market_name[i]); }
  assert(read->market_type == written->market_type);
  assert(read->index_market == written->index_market);
}

/* Market Directory Message: written and read back, then read and written back */
static void check_market_directory_message(void) {
  MarketDirectoryMessage sent;
  MarketDirectoryMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_market_directory_message(&sent);
  assert(encode_market_directory_message(&sent, wire, 0) == 42);
  assert(decode_market_directory_message(&got, wire, 0) == 42);
  equal_market_directory_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_market_directory_message(&got, wire, 0) == 42);
  assert(encode_market_directory_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Combination Order Book Leg Directory Message: 17 bytes ------------------ */

/* Provides a mapping between a combination order book and one of the combination leg order books. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];      /* bytes 0 to 3 */
  uint8_t combination_order_book_id[4];  /* bytes 4 to 7 */
  uint8_t leg_order_book_id[4];          /* bytes 8 to 11 */
  uint8_t leg_side;                      /* byte 12 */
  uint8_t leg_ratio[4];                  /* bytes 13 to 16 */
} CombinationOrderBookLegDirectoryMessage;

/* any Combination Order Book Leg Directory Message at all: every byte one the checker chooses */
static void any_combination_order_book_leg_directory_message(CombinationOrderBookLegDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->combination_order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_order_book_id[i] = arbitrary(); }
  record->leg_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_ratio[i] = arbitrary(); }
}

/* Combination Order Book Leg Directory Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_combination_order_book_leg_directory_message(const CombinationOrderBookLegDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->combination_order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_order_book_id[i]; }
  wire[at++] = record->leg_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio[i]; }

  return at;
}

/* Combination Order Book Leg Directory Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_combination_order_book_leg_directory_message(CombinationOrderBookLegDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->combination_order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_order_book_id[i] = wire[at++]; }
  record->leg_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_ratio[i] = wire[at++]; }

  return at;
}

/* what was read of Combination Order Book Leg Directory Message is what was written, byte for byte */
static void equal_combination_order_book_leg_directory_message(const CombinationOrderBookLegDirectoryMessage *read, const CombinationOrderBookLegDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->combination_order_book_id[i] == written->combination_order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_order_book_id[i] == written->leg_order_book_id[i]); }
  assert(read->leg_side == written->leg_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio[i] == written->leg_ratio[i]); }
}

/* Combination Order Book Leg Directory Message: written and read back, then read and written back */
static void check_combination_order_book_leg_directory_message(void) {
  CombinationOrderBookLegDirectoryMessage sent;
  CombinationOrderBookLegDirectoryMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_combination_order_book_leg_directory_message(&sent);
  assert(encode_combination_order_book_leg_directory_message(&sent, wire, 0) == 17);
  assert(decode_combination_order_book_leg_directory_message(&got, wire, 0) == 17);
  equal_combination_order_book_leg_directory_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_combination_order_book_leg_directory_message(&got, wire, 0) == 17);
  assert(encode_combination_order_book_leg_directory_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Size Table Entry Message: 32 bytes --------------------------------- */

/* Contains information on a tick size for a price range. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t order_book_id[4];          /* bytes 4 to 7 */
  uint8_t tick_size[8];              /* bytes 8 to 15 */
  uint8_t price_from[8];             /* bytes 16 to 23 */
  uint8_t price_to[8];               /* bytes 24 to 31 */
} TickSizeTableEntryMessage;

/* any Tick Size Table Entry Message at all: every byte one the checker chooses */
static void any_tick_size_table_entry_message(TickSizeTableEntryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_from[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_to[i] = arbitrary(); }
}

/* Tick Size Table Entry Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_tick_size_table_entry_message(const TickSizeTableEntryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_from[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_to[i]; }

  return at;
}

/* Tick Size Table Entry Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_tick_size_table_entry_message(TickSizeTableEntryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_from[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_to[i] = wire[at++]; }

  return at;
}

/* what was read of Tick Size Table Entry Message is what was written, byte for byte */
static void equal_tick_size_table_entry_message(const TickSizeTableEntryMessage *read, const TickSizeTableEntryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tick_size[i] == written->tick_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_from[i] == written->price_from[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_to[i] == written->price_to[i]); }
}

/* Tick Size Table Entry Message: written and read back, then read and written back */
static void check_tick_size_table_entry_message(void) {
  TickSizeTableEntryMessage sent;
  TickSizeTableEntryMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_tick_size_table_entry_message(&sent);
  assert(encode_tick_size_table_entry_message(&sent, wire, 0) == 32);
  assert(decode_tick_size_table_entry_message(&got, wire, 0) == 32);
  equal_tick_size_table_entry_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_size_table_entry_message(&got, wire, 0) == 32);
  assert(encode_tick_size_table_entry_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Corporate Action Entry Message: 31 bytes -------------------------------- */

/* Displays the entries of assigned Corporate Action Codes to Order Books. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t corporate_action_id[4];    /* bytes 4 to 7 */
  uint8_t order_book_id[4];          /* bytes 8 to 11 */
  uint8_t corporate_action_code[4];  /* bytes 12 to 15 */
  uint8_t corporate_action_type;     /* byte 16 */
  uint8_t start_date[4];             /* bytes 17 to 20 */
  uint8_t end_date[4];               /* bytes 21 to 24 */
  uint8_t record_date[4];            /* bytes 25 to 28 */
  uint8_t corporate_action_status;   /* byte 29 */
  uint8_t action;                    /* byte 30 */
} CorporateActionEntryMessage;

/* any Corporate Action Entry Message at all: every byte one the checker chooses */
static void any_corporate_action_entry_message(CorporateActionEntryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corporate_action_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corporate_action_code[i] = arbitrary(); }
  record->corporate_action_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->record_date[i] = arbitrary(); }
  record->corporate_action_status = arbitrary();
  record->action = arbitrary();
}

/* Corporate Action Entry Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_corporate_action_entry_message(const CorporateActionEntryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corporate_action_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corporate_action_code[i]; }
  wire[at++] = record->corporate_action_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->start_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->record_date[i]; }
  wire[at++] = record->corporate_action_status;
  wire[at++] = record->action;

  return at;
}

/* Corporate Action Entry Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_corporate_action_entry_message(CorporateActionEntryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corporate_action_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corporate_action_code[i] = wire[at++]; }
  record->corporate_action_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->record_date[i] = wire[at++]; }
  record->corporate_action_status = wire[at++];
  record->action = wire[at++];

  return at;
}

/* what was read of Corporate Action Entry Message is what was written, byte for byte */
static void equal_corporate_action_entry_message(const CorporateActionEntryMessage *read, const CorporateActionEntryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corporate_action_id[i] == written->corporate_action_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corporate_action_code[i] == written->corporate_action_code[i]); }
  assert(read->corporate_action_type == written->corporate_action_type);
  for (size_t i = 0; i < 4; i++) { assert(read->start_date[i] == written->start_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_date[i] == written->end_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->record_date[i] == written->record_date[i]); }
  assert(read->corporate_action_status == written->corporate_action_status);
  assert(read->action == written->action);
}

/* Corporate Action Entry Message: written and read back, then read and written back */
static void check_corporate_action_entry_message(void) {
  CorporateActionEntryMessage sent;
  CorporateActionEntryMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_corporate_action_entry_message(&sent);
  assert(encode_corporate_action_entry_message(&sent, wire, 0) == 31);
  assert(decode_corporate_action_entry_message(&got, wire, 0) == 31);
  equal_corporate_action_entry_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_corporate_action_entry_message(&got, wire, 0) == 31);
  assert(encode_corporate_action_entry_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book Directory Extension Message: 92 bytes ------------------------ */

/* Provides additional information that are valid only for Fixed Income instruments; sent for all instruments. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t order_book_id[4];                  /* bytes 4 to 7 */
  uint8_t accrued_interest_rounding[4];      /* bytes 8 to 11 */
  uint8_t accrued_interest_updown;           /* byte 12 */
  uint8_t calculation_convention;            /* byte 13 */
  uint8_t clean_price_rounding[4];           /* bytes 14 to 17 */
  uint8_t clean_price_updown;                /* byte 18 */
  uint8_t coupon_frequency[4];               /* bytes 19 to 22 */
  uint8_t coupon_interest[8];                /* bytes 23 to 30 */
  uint8_t coupon_from_date[4];               /* bytes 31 to 34 */
  uint8_t issue_date[4];                     /* bytes 35 to 38 */
  uint8_t maturity_date[4];                  /* bytes 39 to 42 */
  uint8_t day_calculation_rule;              /* byte 43 */
  uint8_t day_count_convention;              /* byte 44 */
  uint8_t ex_coupon_period[4];               /* bytes 45 to 48 */
  uint8_t dividend[8];                       /* bytes 49 to 56 */
  uint8_t fixed_income_type;                 /* byte 57 */
  uint8_t rate_determination_days[4];        /* bytes 58 to 61 */
  uint8_t yield_convention[4];               /* bytes 62 to 65 */
  uint8_t end_of_month_count_convention[4];  /* bytes 66 to 69 */
  uint8_t first_settlement_date[4];          /* bytes 70 to 73 */
  uint8_t coupon_div_date[4];                /* bytes 74 to 77 */
  uint8_t date_books_close[4];               /* bytes 78 to 81 */
  uint8_t effective_expiration_date[4];      /* bytes 82 to 85 */
  uint8_t proceed_date[4];                   /* bytes 86 to 89 */
  uint8_t set_end_consideration;             /* byte 90 */
  uint8_t set_start_consideration;           /* byte 91 */
} OrderBookDirectoryExtensionMessage;

/* any Order Book Directory Extension Message at all: every byte one the checker chooses */
static void any_order_book_directory_extension_message(OrderBookDirectoryExtensionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->accrued_interest_rounding[i] = arbitrary(); }
  record->accrued_interest_updown = arbitrary();
  record->calculation_convention = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->clean_price_rounding[i] = arbitrary(); }
  record->clean_price_updown = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->coupon_frequency[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->coupon_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->coupon_from_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->issue_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  record->day_calculation_rule = arbitrary();
  record->day_count_convention = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->ex_coupon_period[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->dividend[i] = arbitrary(); }
  record->fixed_income_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->rate_determination_days[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->yield_convention[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_of_month_count_convention[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->first_settlement_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->coupon_div_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->date_books_close[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->effective_expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->proceed_date[i] = arbitrary(); }
  record->set_end_consideration = arbitrary();
  record->set_start_consideration = arbitrary();
}

/* Order Book Directory Extension Message to the wire: 92 bytes from at, returning where the next byte goes */
static size_t encode_order_book_directory_extension_message(const OrderBookDirectoryExtensionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->accrued_interest_rounding[i]; }
  wire[at++] = record->accrued_interest_updown;
  wire[at++] = record->calculation_convention;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clean_price_rounding[i]; }
  wire[at++] = record->clean_price_updown;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->coupon_frequency[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->coupon_interest[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->coupon_from_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->issue_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  wire[at++] = record->day_calculation_rule;
  wire[at++] = record->day_count_convention;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ex_coupon_period[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->dividend[i]; }
  wire[at++] = record->fixed_income_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rate_determination_days[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->yield_convention[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_of_month_count_convention[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_settlement_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->coupon_div_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->date_books_close[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->effective_expiration_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->proceed_date[i]; }
  wire[at++] = record->set_end_consideration;
  wire[at++] = record->set_start_consideration;

  return at;
}

/* Order Book Directory Extension Message off the wire: 92 bytes from at, returning where the next byte lies */
static size_t decode_order_book_directory_extension_message(OrderBookDirectoryExtensionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->accrued_interest_rounding[i] = wire[at++]; }
  record->accrued_interest_updown = wire[at++];
  record->calculation_convention = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->clean_price_rounding[i] = wire[at++]; }
  record->clean_price_updown = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->coupon_frequency[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->coupon_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->coupon_from_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->issue_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  record->day_calculation_rule = wire[at++];
  record->day_count_convention = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->ex_coupon_period[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->dividend[i] = wire[at++]; }
  record->fixed_income_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->rate_determination_days[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->yield_convention[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_of_month_count_convention[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->first_settlement_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->coupon_div_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->date_books_close[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->effective_expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->proceed_date[i] = wire[at++]; }
  record->set_end_consideration = wire[at++];
  record->set_start_consideration = wire[at++];

  return at;
}

/* what was read of Order Book Directory Extension Message is what was written, byte for byte */
static void equal_order_book_directory_extension_message(const OrderBookDirectoryExtensionMessage *read, const OrderBookDirectoryExtensionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->accrued_interest_rounding[i] == written->accrued_interest_rounding[i]); }
  assert(read->accrued_interest_updown == written->accrued_interest_updown);
  assert(read->calculation_convention == written->calculation_convention);
  for (size_t i = 0; i < 4; i++) { assert(read->clean_price_rounding[i] == written->clean_price_rounding[i]); }
  assert(read->clean_price_updown == written->clean_price_updown);
  for (size_t i = 0; i < 4; i++) { assert(read->coupon_frequency[i] == written->coupon_frequency[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->coupon_interest[i] == written->coupon_interest[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->coupon_from_date[i] == written->coupon_from_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->issue_date[i] == written->issue_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  assert(read->day_calculation_rule == written->day_calculation_rule);
  assert(read->day_count_convention == written->day_count_convention);
  for (size_t i = 0; i < 4; i++) { assert(read->ex_coupon_period[i] == written->ex_coupon_period[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->dividend[i] == written->dividend[i]); }
  assert(read->fixed_income_type == written->fixed_income_type);
  for (size_t i = 0; i < 4; i++) { assert(read->rate_determination_days[i] == written->rate_determination_days[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->yield_convention[i] == written->yield_convention[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_of_month_count_convention[i] == written->end_of_month_count_convention[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->first_settlement_date[i] == written->first_settlement_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->coupon_div_date[i] == written->coupon_div_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->date_books_close[i] == written->date_books_close[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->effective_expiration_date[i] == written->effective_expiration_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->proceed_date[i] == written->proceed_date[i]); }
  assert(read->set_end_consideration == written->set_end_consideration);
  assert(read->set_start_consideration == written->set_start_consideration);
}

/* Order Book Directory Extension Message: written and read back, then read and written back */
static void check_order_book_directory_extension_message(void) {
  OrderBookDirectoryExtensionMessage sent;
  OrderBookDirectoryExtensionMessage got;
  uint8_t wire[92];
  uint8_t again[92];

  any_order_book_directory_extension_message(&sent);
  assert(encode_order_book_directory_extension_message(&sent, wire, 0) == 92);
  assert(decode_order_book_directory_extension_message(&got, wire, 0) == 92);
  equal_order_book_directory_extension_message(&got, &sent);

  for (size_t i = 0; i < 92; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_directory_extension_message(&got, wire, 0) == 92);
  assert(encode_order_book_directory_extension_message(&got, again, 0) == 92);
  for (size_t i = 0; i < 92; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 5 bytes ------------------------------------------- */

/* Used to signal a market or data feed handler event. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t event_code;                /* byte 4 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  assert(read->event_code == written->event_code);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 5);
  assert(decode_system_event_message(&got, wire, 0) == 5);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 5);
  assert(encode_system_event_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book State Message: 48 bytes -------------------------------------- */

/* Relays information on state changes. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t order_book_id[4];          /* bytes 4 to 7 */
  uint8_t state_name[20];            /* bytes 8 to 27 */
  uint8_t display_name[20];          /* bytes 28 to 47 */
} OrderBookStateMessage;

/* any Order Book State Message at all: every byte one the checker chooses */
static void any_order_book_state_message(OrderBookStateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->state_name[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->display_name[i] = arbitrary(); }
}

/* Order Book State Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_order_book_state_message(const OrderBookStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->state_name[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->display_name[i]; }

  return at;
}

/* Order Book State Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_order_book_state_message(OrderBookStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->state_name[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->display_name[i] = wire[at++]; }

  return at;
}

/* what was read of Order Book State Message is what was written, byte for byte */
static void equal_order_book_state_message(const OrderBookStateMessage *read, const OrderBookStateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->state_name[i] == written->state_name[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->display_name[i] == written->display_name[i]); }
}

/* Order Book State Message: written and read back, then read and written back */
static void check_order_book_state_message(void) {
  OrderBookStateMessage sent;
  OrderBookStateMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_order_book_state_message(&sent);
  assert(encode_order_book_state_message(&sent, wire, 0) == 48);
  assert(decode_order_book_state_message(&got, wire, 0) == 48);
  equal_order_book_state_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_state_message(&got, wire, 0) == 48);
  assert(encode_order_book_state_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Business Date Message: 8 bytes ------------------------------------------ */

/* Relays information on the current business date. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t business_date[4];          /* bytes 4 to 7 */
} BusinessDateMessage;

/* any Business Date Message at all: every byte one the checker chooses */
static void any_business_date_message(BusinessDateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->business_date[i] = arbitrary(); }
}

/* Business Date Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_business_date_message(const BusinessDateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->business_date[i]; }

  return at;
}

/* Business Date Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_business_date_message(BusinessDateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->business_date[i] = wire[at++]; }

  return at;
}

/* what was read of Business Date Message is what was written, byte for byte */
static void equal_business_date_message(const BusinessDateMessage *read, const BusinessDateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->business_date[i] == written->business_date[i]); }
}

/* Business Date Message: written and read back, then read and written back */
static void check_business_date_message(void) {
  BusinessDateMessage sent;
  BusinessDateMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_business_date_message(&sent);
  assert(encode_business_date_message(&sent, wire, 0) == 8);
  assert(decode_business_date_message(&got, wire, 0) == 8);
  equal_business_date_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_business_date_message(&got, wire, 0) == 8);
  assert(encode_business_date_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Status Message: 65 bytes ------------------------------------- */

/* Received when the State of an Instrument is changed at any of the applicable levels. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];                /* bytes 0 to 3 */
  uint8_t trading_state_name[20];                  /* bytes 4 to 23 */
  uint8_t instrument_state_level;                  /* byte 24 */
  uint8_t name_of_the_instrument_state_level[32];  /* bytes 25 to 56 */
  uint8_t start_date[4];                           /* bytes 57 to 60 */
  uint8_t start_time[4];                           /* bytes 61 to 64 */
} InstrumentStatusMessage;

/* any Instrument Status Message at all: every byte one the checker chooses */
static void any_instrument_status_message(InstrumentStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->trading_state_name[i] = arbitrary(); }
  record->instrument_state_level = arbitrary();
  for (size_t i = 0; i < 32; i++) { record->name_of_the_instrument_state_level[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->start_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->start_time[i] = arbitrary(); }
}

/* Instrument Status Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_instrument_status_message(const InstrumentStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->trading_state_name[i]; }
  wire[at++] = record->instrument_state_level;
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->name_of_the_instrument_state_level[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->start_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->start_time[i]; }

  return at;
}

/* Instrument Status Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_instrument_status_message(InstrumentStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->trading_state_name[i] = wire[at++]; }
  record->instrument_state_level = wire[at++];
  for (size_t i = 0; i < 32; i++) { record->name_of_the_instrument_state_level[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->start_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->start_time[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Status Message is what was written, byte for byte */
static void equal_instrument_status_message(const InstrumentStatusMessage *read, const InstrumentStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->trading_state_name[i] == written->trading_state_name[i]); }
  assert(read->instrument_state_level == written->instrument_state_level);
  for (size_t i = 0; i < 32; i++) { assert(read->name_of_the_instrument_state_level[i] == written->name_of_the_instrument_state_level[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->start_date[i] == written->start_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->start_time[i] == written->start_time[i]); }
}

/* Instrument Status Message: written and read back, then read and written back */
static void check_instrument_status_message(void) {
  InstrumentStatusMessage sent;
  InstrumentStatusMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_instrument_status_message(&sent);
  assert(encode_instrument_status_message(&sent, wire, 0) == 65);
  assert(decode_instrument_status_message(&got, wire, 0) == 65);
  equal_instrument_status_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_status_message(&got, wire, 0) == 65);
  assert(encode_instrument_status_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Equilibrium Price Message: 72 bytes ------------------------------------- */

/* Used when auctions occur; provides the changes in equilibrium price. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];                        /* bytes 0 to 3 */
  uint8_t order_book_id[4];                                /* bytes 4 to 7 */
  uint8_t available_bid_quantity_at_equilibrium_price[8];  /* bytes 8 to 15 */
  uint8_t available_ask_quantity_at_equilibrium_price[8];  /* bytes 16 to 23 */
  uint8_t equilibrium_price[8];                            /* bytes 24 to 31 */
  uint8_t best_bid_price[8];                               /* bytes 32 to 39 */
  uint8_t best_ask_price[8];                               /* bytes 40 to 47 */
  uint8_t best_bid_quantity[8];                            /* bytes 48 to 55 */
  uint8_t best_ask_quantity[8];                            /* bytes 56 to 63 */
  uint8_t equilibrium_quantity[8];                         /* bytes 64 to 71 */
} EquilibriumPriceMessage;

/* any Equilibrium Price Message at all: every byte one the checker chooses */
static void any_equilibrium_price_message(EquilibriumPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->available_bid_quantity_at_equilibrium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->available_ask_quantity_at_equilibrium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->equilibrium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_bid_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_ask_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->equilibrium_quantity[i] = arbitrary(); }
}

/* Equilibrium Price Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_equilibrium_price_message(const EquilibriumPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->available_bid_quantity_at_equilibrium_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->available_ask_quantity_at_equilibrium_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->equilibrium_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_bid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_ask_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_bid_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_ask_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->equilibrium_quantity[i]; }

  return at;
}

/* Equilibrium Price Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_equilibrium_price_message(EquilibriumPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->available_bid_quantity_at_equilibrium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->available_ask_quantity_at_equilibrium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->equilibrium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_bid_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_ask_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->equilibrium_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Equilibrium Price Message is what was written, byte for byte */
static void equal_equilibrium_price_message(const EquilibriumPriceMessage *read, const EquilibriumPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->available_bid_quantity_at_equilibrium_price[i] == written->available_bid_quantity_at_equilibrium_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->available_ask_quantity_at_equilibrium_price[i] == written->available_ask_quantity_at_equilibrium_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->equilibrium_price[i] == written->equilibrium_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_bid_price[i] == written->best_bid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_ask_price[i] == written->best_ask_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_bid_quantity[i] == written->best_bid_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_ask_quantity[i] == written->best_ask_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->equilibrium_quantity[i] == written->equilibrium_quantity[i]); }
}

/* Equilibrium Price Message: written and read back, then read and written back */
static void check_equilibrium_price_message(void) {
  EquilibriumPriceMessage sent;
  EquilibriumPriceMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_equilibrium_price_message(&sent);
  assert(encode_equilibrium_price_message(&sent, wire, 0) == 72);
  assert(decode_equilibrium_price_message(&got, wire, 0) == 72);
  equal_equilibrium_price_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_equilibrium_price_message(&got, wire, 0) == 72);
  assert(encode_equilibrium_price_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Statistics Message: 89 bytes -------------------------------------- */

/* Publishes Trade Statistics per Orderbook ID for the current Trading Day. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];              /* bytes 0 to 3 */
  uint8_t order_book_id[4];                      /* bytes 4 to 7 */
  uint8_t open_price[8];                         /* bytes 8 to 15 */
  uint8_t high_price[8];                         /* bytes 16 to 23 */
  uint8_t low_price[8];                          /* bytes 24 to 31 */
  uint8_t last_price[8];                         /* bytes 32 to 39 */
  uint8_t last_auction_price[8];                 /* bytes 40 to 47 */
  uint8_t last_quantity[8];                      /* bytes 48 to 55 */
  uint8_t turnover_quantity[8];                  /* bytes 56 to 63 */
  uint8_t reported_trades_turnover_quantity[8];  /* bytes 64 to 71 */
  uint8_t turnover_value[8];                     /* bytes 72 to 79 */
  uint8_t number_of_trades[8];                   /* bytes 80 to 87 */
  uint8_t trend_indicator;                       /* byte 88 */
} TradeStatisticsMessage;

/* any Trade Statistics Message at all: every byte one the checker chooses */
static void any_trade_statistics_message(TradeStatisticsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_auction_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reported_trades_turnover_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->number_of_trades[i] = arbitrary(); }
  record->trend_indicator = arbitrary();
}

/* Trade Statistics Message to the wire: 89 bytes from at, returning where the next byte goes */
static size_t encode_trade_statistics_message(const TradeStatisticsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_auction_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reported_trades_turnover_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->number_of_trades[i]; }
  wire[at++] = record->trend_indicator;

  return at;
}

/* Trade Statistics Message off the wire: 89 bytes from at, returning where the next byte lies */
static size_t decode_trade_statistics_message(TradeStatisticsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_auction_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reported_trades_turnover_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->number_of_trades[i] = wire[at++]; }
  record->trend_indicator = wire[at++];

  return at;
}

/* what was read of Trade Statistics Message is what was written, byte for byte */
static void equal_trade_statistics_message(const TradeStatisticsMessage *read, const TradeStatisticsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_price[i] == written->open_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_auction_price[i] == written->last_auction_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_quantity[i] == written->last_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover_quantity[i] == written->turnover_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reported_trades_turnover_quantity[i] == written->reported_trades_turnover_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover_value[i] == written->turnover_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->number_of_trades[i] == written->number_of_trades[i]); }
  assert(read->trend_indicator == written->trend_indicator);
}

/* Trade Statistics Message: written and read back, then read and written back */
static void check_trade_statistics_message(void) {
  TradeStatisticsMessage sent;
  TradeStatisticsMessage got;
  uint8_t wire[89];
  uint8_t again[89];

  any_trade_statistics_message(&sent);
  assert(encode_trade_statistics_message(&sent, wire, 0) == 89);
  assert(decode_trade_statistics_message(&got, wire, 0) == 89);
  equal_trade_statistics_message(&got, &sent);

  for (size_t i = 0; i < 89; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_statistics_message(&got, wire, 0) == 89);
  assert(encode_trade_statistics_message(&got, again, 0) == 89);
  for (size_t i = 0; i < 89; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reference Price Message: 29 bytes --------------------------------------- */

/* Publishes Reference Prices per Price Types. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t order_book_id[4];          /* bytes 4 to 7 */
  uint8_t price_type;                /* byte 8 */
  uint8_t price[8];                  /* bytes 9 to 16 */
  uint8_t timestamp[8];              /* bytes 17 to 24 */
  uint8_t price_date[4];             /* bytes 25 to 28 */
} ReferencePriceMessage;

/* any Reference Price Message at all: every byte one the checker chooses */
static void any_reference_price_message(ReferencePriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->price_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_date[i] = arbitrary(); }
}

/* Reference Price Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_reference_price_message(const ReferencePriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->price_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_date[i]; }

  return at;
}

/* Reference Price Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_reference_price_message(ReferencePriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->price_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_date[i] = wire[at++]; }

  return at;
}

/* what was read of Reference Price Message is what was written, byte for byte */
static void equal_reference_price_message(const ReferencePriceMessage *read, const ReferencePriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->price_type == written->price_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_date[i] == written->price_date[i]); }
}

/* Reference Price Message: written and read back, then read and written back */
static void check_reference_price_message(void) {
  ReferencePriceMessage sent;
  ReferencePriceMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_reference_price_message(&sent);
  assert(encode_reference_price_message(&sent, wire, 0) == 29);
  assert(decode_reference_price_message(&got, wire, 0) == 29);
  equal_reference_price_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_reference_price_message(&got, wire, 0) == 29);
  assert(encode_reference_price_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Message: 37 bytes ------------------------------------------------- */

/* Used for sending index price information. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t order_book_id[4];          /* bytes 4 to 7 */
  uint8_t last_price[8];             /* bytes 8 to 15 */
  uint8_t timestamp[8];              /* bytes 16 to 23 */
  uint8_t change_previous[4];        /* bytes 24 to 27 */
  uint8_t change_yesterday[4];       /* bytes 28 to 31 */
  uint8_t trend_indicator;           /* byte 32 */
  uint8_t point_of_movement[4];      /* bytes 33 to 36 */
} IndexMessage;

/* any Index Message at all: every byte one the checker chooses */
static void any_index_message(IndexMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->change_previous[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->change_yesterday[i] = arbitrary(); }
  record->trend_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->point_of_movement[i] = arbitrary(); }
}

/* Index Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_index_message(const IndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->change_previous[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->change_yesterday[i]; }
  wire[at++] = record->trend_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->point_of_movement[i]; }

  return at;
}

/* Index Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_index_message(IndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->change_previous[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->change_yesterday[i] = wire[at++]; }
  record->trend_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->point_of_movement[i] = wire[at++]; }

  return at;
}

/* what was read of Index Message is what was written, byte for byte */
static void equal_index_message(const IndexMessage *read, const IndexMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->change_previous[i] == written->change_previous[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->change_yesterday[i] == written->change_yesterday[i]); }
  assert(read->trend_indicator == written->trend_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->point_of_movement[i] == written->point_of_movement[i]); }
}

/* Index Message: written and read back, then read and written back */
static void check_index_message(void) {
  IndexMessage sent;
  IndexMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_index_message(&sent);
  assert(encode_index_message(&sent, wire, 0) == 37);
  assert(decode_index_message(&got, wire, 0) == 37);
  equal_index_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_index_message(&got, wire, 0) == 37);
  assert(encode_index_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Interest Message: 24 bytes ----------------------------------------- */

/* Publishes Open Interest. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t order_book_id[4];          /* bytes 4 to 7 */
  uint8_t open_interest[8];          /* bytes 8 to 15 */
  uint8_t transact_time[8];          /* bytes 16 to 23 */
} OpenInterestMessage;

/* any Open Interest Message at all: every byte one the checker chooses */
static void any_open_interest_message(OpenInterestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Open Interest Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_open_interest_message(const OpenInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_interest[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Open Interest Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_open_interest_message(OpenInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Open Interest Message is what was written, byte for byte */
static void equal_open_interest_message(const OpenInterestMessage *read, const OpenInterestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Open Interest Message: written and read back, then read and written back */
static void check_open_interest_message(void) {
  OpenInterestMessage sent;
  OpenInterestMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_open_interest_message(&sent);
  assert(encode_open_interest_message(&sent, wire, 0) == 24);
  assert(decode_open_interest_message(&got, wire, 0) == 24);
  equal_open_interest_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_open_interest_message(&got, wire, 0) == 24);
  assert(encode_open_interest_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Ticker Message: 91 bytes ------------------------------------------ */

/* Publishes Trade Ticker. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t order_book_id[4];          /* bytes 4 to 7 */
  uint8_t deal_id[8];                /* bytes 8 to 15 */
  uint8_t deal_source;               /* byte 16 */
  uint8_t price[8];                  /* bytes 17 to 24 */
  uint8_t quantity[8];               /* bytes 25 to 32 */
  uint8_t deal_time[8];              /* bytes 33 to 40 */
  uint8_t action;                    /* byte 41 */
  uint8_t aggressor;                 /* byte 42 */
  uint8_t trade_report_type[2];      /* bytes 43 to 44 */
  uint8_t printable;                 /* byte 45 */
  uint8_t as_of_date[4];             /* bytes 46 to 49 */
  uint8_t boq_list[6];               /* bytes 50 to 55 */
  uint8_t participant_id_buy[5];     /* bytes 56 to 60 */
  uint8_t order_id_buy[8];           /* bytes 61 to 68 */
  uint8_t participant_id_sell[5];    /* bytes 69 to 73 */
  uint8_t order_id_sell[8];          /* bytes 74 to 81 */
  uint8_t trade_slip_number[4];      /* bytes 82 to 85 */
  uint8_t exchange_order_type[4];    /* bytes 86 to 89 */
  uint8_t trade_condition;           /* byte 90 */
} TradeTickerMessage;

/* any Trade Ticker Message at all: every byte one the checker chooses */
static void any_trade_ticker_message(TradeTickerMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->deal_id[i] = arbitrary(); }
  record->deal_source = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->deal_time[i] = arbitrary(); }
  record->action = arbitrary();
  record->aggressor = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->trade_report_type[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->as_of_date[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->boq_list[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->participant_id_buy[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id_buy[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->participant_id_sell[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id_sell[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_slip_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->exchange_order_type[i] = arbitrary(); }
  record->trade_condition = arbitrary();
}

/* Trade Ticker Message to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_trade_ticker_message(const TradeTickerMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->deal_id[i]; }
  wire[at++] = record->deal_source;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->deal_time[i]; }
  wire[at++] = record->action;
  wire[at++] = record->aggressor;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_report_type[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->as_of_date[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->boq_list[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->participant_id_buy[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id_buy[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->participant_id_sell[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id_sell[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_slip_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_order_type[i]; }
  wire[at++] = record->trade_condition;

  return at;
}

/* Trade Ticker Message off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_trade_ticker_message(TradeTickerMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->deal_id[i] = wire[at++]; }
  record->deal_source = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->deal_time[i] = wire[at++]; }
  record->action = wire[at++];
  record->aggressor = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->trade_report_type[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->as_of_date[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->boq_list[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->participant_id_buy[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id_buy[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->participant_id_sell[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id_sell[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_slip_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->exchange_order_type[i] = wire[at++]; }
  record->trade_condition = wire[at++];

  return at;
}

/* what was read of Trade Ticker Message is what was written, byte for byte */
static void equal_trade_ticker_message(const TradeTickerMessage *read, const TradeTickerMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->deal_id[i] == written->deal_id[i]); }
  assert(read->deal_source == written->deal_source);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->deal_time[i] == written->deal_time[i]); }
  assert(read->action == written->action);
  assert(read->aggressor == written->aggressor);
  for (size_t i = 0; i < 2; i++) { assert(read->trade_report_type[i] == written->trade_report_type[i]); }
  assert(read->printable == written->printable);
  for (size_t i = 0; i < 4; i++) { assert(read->as_of_date[i] == written->as_of_date[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->boq_list[i] == written->boq_list[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->participant_id_buy[i] == written->participant_id_buy[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id_buy[i] == written->order_id_buy[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->participant_id_sell[i] == written->participant_id_sell[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id_sell[i] == written->order_id_sell[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_slip_number[i] == written->trade_slip_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_order_type[i] == written->exchange_order_type[i]); }
  assert(read->trade_condition == written->trade_condition);
}

/* Trade Ticker Message: written and read back, then read and written back */
static void check_trade_ticker_message(void) {
  TradeTickerMessage sent;
  TradeTickerMessage got;
  uint8_t wire[91];
  uint8_t again[91];

  any_trade_ticker_message(&sent);
  assert(encode_trade_ticker_message(&sent, wire, 0) == 91);
  assert(decode_trade_ticker_message(&got, wire, 0) == 91);
  equal_trade_ticker_message(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_ticker_message(&got, wire, 0) == 91);
  assert(encode_trade_ticker_message(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Limits Message: 34 bytes ------------------------------------------ */

/* Provides an update to the price limits or circuit breaker limits for an order book. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t order_book_id[4];          /* bytes 4 to 7 */
  uint8_t upper_limit[8];            /* bytes 8 to 15 */
  uint8_t lower_limit[8];            /* bytes 16 to 23 */
  uint8_t type;                      /* byte 24 */
  uint8_t category;                  /* byte 25 */
  uint8_t reference_price[8];        /* bytes 26 to 33 */
} PriceLimitsMessage;

/* any Price Limits Message at all: every byte one the checker chooses */
static void any_price_limits_message(PriceLimitsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->upper_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lower_limit[i] = arbitrary(); }
  record->type = arbitrary();
  record->category = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
}

/* Price Limits Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_price_limits_message(const PriceLimitsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->upper_limit[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lower_limit[i]; }
  wire[at++] = record->type;
  wire[at++] = record->category;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }

  return at;
}

/* Price Limits Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_price_limits_message(PriceLimitsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->upper_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lower_limit[i] = wire[at++]; }
  record->type = wire[at++];
  record->category = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }

  return at;
}

/* what was read of Price Limits Message is what was written, byte for byte */
static void equal_price_limits_message(const PriceLimitsMessage *read, const PriceLimitsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->upper_limit[i] == written->upper_limit[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lower_limit[i] == written->lower_limit[i]); }
  assert(read->type == written->type);
  assert(read->category == written->category);
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
}

/* Price Limits Message: written and read back, then read and written back */
static void check_price_limits_message(void) {
  PriceLimitsMessage sent;
  PriceLimitsMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_price_limits_message(&sent);
  assert(encode_price_limits_message(&sent, wire, 0) == 34);
  assert(decode_price_limits_message(&got, wire, 0) == 34);
  equal_price_limits_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_price_limits_message(&got, wire, 0) == 34);
  assert(encode_price_limits_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Snapshot Message: 20 bytes --------------------------------------- */

/* Returns the current MDF sequence number to be used when connecting to the MDF feed (Glimpse). */
typedef struct {
  uint8_t snapshot_sequence_number[20];  /* bytes 0 to 19 */
} EndOfSnapshotMessage;

/* any End Of Snapshot Message at all: every byte one the checker chooses */
static void any_end_of_snapshot_message(EndOfSnapshotMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->snapshot_sequence_number[i] = arbitrary(); }
}

/* End Of Snapshot Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_end_of_snapshot_message(const EndOfSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->snapshot_sequence_number[i]; }

  return at;
}

/* End Of Snapshot Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_end_of_snapshot_message(EndOfSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->snapshot_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Snapshot Message is what was written, byte for byte */
static void equal_end_of_snapshot_message(const EndOfSnapshotMessage *read, const EndOfSnapshotMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->snapshot_sequence_number[i] == written->snapshot_sequence_number[i]); }
}

/* End Of Snapshot Message: written and read back, then read and written back */
static void check_end_of_snapshot_message(void) {
  EndOfSnapshotMessage sent;
  EndOfSnapshotMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_end_of_snapshot_message(&sent);
  assert(encode_end_of_snapshot_message(&sent, wire, 0) == 20);
  assert(decode_end_of_snapshot_message(&got, wire, 0) == 20);
  equal_end_of_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_snapshot_message(&got, wire, 0) == 20);
  assert(encode_end_of_snapshot_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_seconds_message();
  check_order_book_directory_message();
  check_exchange_directory_message();
  check_market_directory_message();
  check_combination_order_book_leg_directory_message();
  check_tick_size_table_entry_message();
  check_corporate_action_entry_message();
  check_order_book_directory_extension_message();
  check_system_event_message();
  check_order_book_state_message();
  check_business_date_message();
  check_instrument_status_message();
  check_equilibrium_price_message();
  check_trade_statistics_message();
  check_reference_price_message();
  check_index_message();
  check_open_interest_message();
  check_trade_ticker_message();
  check_price_limits_message();
  check_end_of_snapshot_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
