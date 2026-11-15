// nasdaq/nordicderivatives/marketdata/NordicDerivatives_MarketData_v2_28_7.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Genium INET Auxiliary Market Data
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

/* ---- Order Book Directory: 153 bytes ----------------------------------------- */

typedef struct {
  uint8_t timestamp_nanoseconds[4];                /* bytes 0 to 3 */
  uint8_t order_book_id[4];                        /* bytes 4 to 7 */
  uint8_t symbol[32];                              /* bytes 8 to 39 */
  uint8_t long_name[32];                           /* bytes 40 to 71 */
  uint8_t isin[12];                                /* bytes 72 to 83 */
  uint8_t financial_product;                       /* byte 84 */
  uint8_t trading_currency[3];                     /* bytes 85 to 87 */
  uint8_t number_of_decimals_in_price[2];          /* bytes 88 to 89 */
  uint8_t number_of_decimals_in_nominal_value[2];  /* bytes 90 to 91 */
  uint8_t odd_lot_size[4];                         /* bytes 92 to 95 */
  uint8_t round_lot_size[4];                       /* bytes 96 to 99 */
  uint8_t block_lot_size[4];                       /* bytes 100 to 103 */
  uint8_t nominal_value[8];                        /* bytes 104 to 111 */
  uint8_t number_of_legs;                          /* byte 112 */
  uint8_t underlying_order_book_id[4];             /* bytes 113 to 116 */
  uint8_t strike_price[4];                         /* bytes 117 to 120 */
  uint8_t expiration_date[4];                      /* bytes 121 to 124 */
  uint8_t number_of_decimals_in_strike_price[2];   /* bytes 125 to 126 */
  uint8_t put_or_call;                             /* byte 127 */
  uint8_t notation_date[4];                        /* bytes 128 to 131 */
  uint8_t first_trading_date_and_time[8];          /* bytes 132 to 139 */
  uint8_t last_trading_date_and_time[8];           /* bytes 140 to 147 */
  uint8_t country_id;                              /* byte 148 */
  uint8_t market_id;                               /* byte 149 */
  uint8_t physical_delivery;                       /* byte 150 */
  uint8_t option_style[2];                         /* bytes 151 to 152 */
} OrderBookDirectory;

/* any Order Book Directory at all: every byte one the checker chooses */
static void any_order_book_directory(OrderBookDirectory *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->long_name[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  record->financial_product = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->odd_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->round_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->block_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = arbitrary(); }
  record->number_of_legs = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->underlying_order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_strike_price[i] = arbitrary(); }
  record->put_or_call = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->notation_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->first_trading_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_trading_date_and_time[i] = arbitrary(); }
  record->country_id = arbitrary();
  record->market_id = arbitrary();
  record->physical_delivery = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->option_style[i] = arbitrary(); }
}

/* Order Book Directory to the wire: 153 bytes from at, returning where the next byte goes */
static size_t encode_order_book_directory(const OrderBookDirectory *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->long_name[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  wire[at++] = record->financial_product;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_currency[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_in_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_in_nominal_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->odd_lot_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->round_lot_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_lot_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nominal_value[i]; }
  wire[at++] = record->number_of_legs;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_in_strike_price[i]; }
  wire[at++] = record->put_or_call;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->notation_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->first_trading_date_and_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_trading_date_and_time[i]; }
  wire[at++] = record->country_id;
  wire[at++] = record->market_id;
  wire[at++] = record->physical_delivery;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->option_style[i]; }

  return at;
}

/* Order Book Directory off the wire: 153 bytes from at, returning where the next byte lies */
static size_t decode_order_book_directory(OrderBookDirectory *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->long_name[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  record->financial_product = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_nominal_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->odd_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->round_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->block_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = wire[at++]; }
  record->number_of_legs = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->underlying_order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_strike_price[i] = wire[at++]; }
  record->put_or_call = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->notation_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->first_trading_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_trading_date_and_time[i] = wire[at++]; }
  record->country_id = wire[at++];
  record->market_id = wire[at++];
  record->physical_delivery = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->option_style[i] = wire[at++]; }

  return at;
}

/* what was read of Order Book Directory is what was written, byte for byte */
static void equal_order_book_directory(const OrderBookDirectory *read, const OrderBookDirectory *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->long_name[i] == written->long_name[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  assert(read->financial_product == written->financial_product);
  for (size_t i = 0; i < 3; i++) { assert(read->trading_currency[i] == written->trading_currency[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_price[i] == written->number_of_decimals_in_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_nominal_value[i] == written->number_of_decimals_in_nominal_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->odd_lot_size[i] == written->odd_lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->round_lot_size[i] == written->round_lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->block_lot_size[i] == written->block_lot_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nominal_value[i] == written->nominal_value[i]); }
  assert(read->number_of_legs == written->number_of_legs);
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_order_book_id[i] == written->underlying_order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_strike_price[i] == written->number_of_decimals_in_strike_price[i]); }
  assert(read->put_or_call == written->put_or_call);
  for (size_t i = 0; i < 4; i++) { assert(read->notation_date[i] == written->notation_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->first_trading_date_and_time[i] == written->first_trading_date_and_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_trading_date_and_time[i] == written->last_trading_date_and_time[i]); }
  assert(read->country_id == written->country_id);
  assert(read->market_id == written->market_id);
  assert(read->physical_delivery == written->physical_delivery);
  for (size_t i = 0; i < 2; i++) { assert(read->option_style[i] == written->option_style[i]); }
}

/* Order Book Directory: written and read back, then read and written back */
static void check_order_book_directory(void) {
  OrderBookDirectory sent;
  OrderBookDirectory got;
  uint8_t wire[153];
  uint8_t again[153];

  any_order_book_directory(&sent);
  assert(encode_order_book_directory(&sent, wire, 0) == 153);
  assert(decode_order_book_directory(&got, wire, 0) == 153);
  equal_order_book_directory(&got, &sent);

  for (size_t i = 0; i < 153; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_directory(&got, wire, 0) == 153);
  assert(encode_order_book_directory(&got, again, 0) == 153);
  for (size_t i = 0; i < 153; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Directory: 38 bytes ---------------------------------------------- */

typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t country_id;                /* byte 4 */
  uint8_t market_id;                 /* byte 5 */
  uint8_t market_name[32];           /* bytes 6 to 37 */
} MarketDirectory;

/* any Market Directory at all: every byte one the checker chooses */
static void any_market_directory(MarketDirectory *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  record->country_id = arbitrary();
  record->market_id = arbitrary();
  for (size_t i = 0; i < 32; i++) { record->market_name[i] = arbitrary(); }
}

/* Market Directory to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_market_directory(const MarketDirectory *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  wire[at++] = record->country_id;
  wire[at++] = record->market_id;
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->market_name[i]; }

  return at;
}

/* Market Directory off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_market_directory(MarketDirectory *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  record->country_id = wire[at++];
  record->market_id = wire[at++];
  for (size_t i = 0; i < 32; i++) { record->market_name[i] = wire[at++]; }

  return at;
}

/* what was read of Market Directory is what was written, byte for byte */
static void equal_market_directory(const MarketDirectory *read, const MarketDirectory *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  assert(read->country_id == written->country_id);
  assert(read->market_id == written->market_id);
  for (size_t i = 0; i < 32; i++) { assert(read->market_name[i] == written->market_name[i]); }
}

/* Market Directory: written and read back, then read and written back */
static void check_market_directory(void) {
  MarketDirectory sent;
  MarketDirectory got;
  uint8_t wire[38];
  uint8_t again[38];

  any_market_directory(&sent);
  assert(encode_market_directory(&sent, wire, 0) == 38);
  assert(decode_market_directory(&got, wire, 0) == 38);
  equal_market_directory(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_market_directory(&got, wire, 0) == 38);
  assert(encode_market_directory(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Combination Order Book Leg Directory: 17 bytes -------------------------- */

/* Combination Order book Directory Message */
typedef struct {
  uint8_t timestamp_nanoseconds[4];      /* bytes 0 to 3 */
  uint8_t combination_order_book_id[4];  /* bytes 4 to 7 */
  uint8_t leg_order_book_id[4];          /* bytes 8 to 11 */
  uint8_t leg_side;                      /* byte 12 */
  uint8_t leg_ratio[4];                  /* bytes 13 to 16 */
} CombinationOrderBookLegDirectory;

/* any Combination Order Book Leg Directory at all: every byte one the checker chooses */
static void any_combination_order_book_leg_directory(CombinationOrderBookLegDirectory *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->combination_order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_order_book_id[i] = arbitrary(); }
  record->leg_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_ratio[i] = arbitrary(); }
}

/* Combination Order Book Leg Directory to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_combination_order_book_leg_directory(const CombinationOrderBookLegDirectory *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->combination_order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_order_book_id[i]; }
  wire[at++] = record->leg_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio[i]; }

  return at;
}

/* Combination Order Book Leg Directory off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_combination_order_book_leg_directory(CombinationOrderBookLegDirectory *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->combination_order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_order_book_id[i] = wire[at++]; }
  record->leg_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_ratio[i] = wire[at++]; }

  return at;
}

/* what was read of Combination Order Book Leg Directory is what was written, byte for byte */
static void equal_combination_order_book_leg_directory(const CombinationOrderBookLegDirectory *read, const CombinationOrderBookLegDirectory *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->combination_order_book_id[i] == written->combination_order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_order_book_id[i] == written->leg_order_book_id[i]); }
  assert(read->leg_side == written->leg_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio[i] == written->leg_ratio[i]); }
}

/* Combination Order Book Leg Directory: written and read back, then read and written back */
static void check_combination_order_book_leg_directory(void) {
  CombinationOrderBookLegDirectory sent;
  CombinationOrderBookLegDirectory got;
  uint8_t wire[17];
  uint8_t again[17];

  any_combination_order_book_leg_directory(&sent);
  assert(encode_combination_order_book_leg_directory(&sent, wire, 0) == 17);
  assert(decode_combination_order_book_leg_directory(&got, wire, 0) == 17);
  equal_combination_order_book_leg_directory(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_combination_order_book_leg_directory(&got, wire, 0) == 17);
  assert(encode_combination_order_book_leg_directory(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Size Table Entry: 24 bytes ----------------------------------------- */

/* L - Tick Size Message. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t order_book_id[4];          /* bytes 4 to 7 */
  uint8_t tick_size[8];              /* bytes 8 to 15 */
  uint8_t price_from[4];             /* bytes 16 to 19 */
  uint8_t price_to[4];               /* bytes 20 to 23 */
} TickSizeTableEntry;

/* any Tick Size Table Entry at all: every byte one the checker chooses */
static void any_tick_size_table_entry(TickSizeTableEntry *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_from[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_to[i] = arbitrary(); }
}

/* Tick Size Table Entry to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_tick_size_table_entry(const TickSizeTableEntry *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_from[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_to[i]; }

  return at;
}

/* Tick Size Table Entry off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_tick_size_table_entry(TickSizeTableEntry *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_from[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_to[i] = wire[at++]; }

  return at;
}

/* what was read of Tick Size Table Entry is what was written, byte for byte */
static void equal_tick_size_table_entry(const TickSizeTableEntry *read, const TickSizeTableEntry *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tick_size[i] == written->tick_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_from[i] == written->price_from[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_to[i] == written->price_to[i]); }
}

/* Tick Size Table Entry: written and read back, then read and written back */
static void check_tick_size_table_entry(void) {
  TickSizeTableEntry sent;
  TickSizeTableEntry got;
  uint8_t wire[24];
  uint8_t again[24];

  any_tick_size_table_entry(&sent);
  assert(encode_tick_size_table_entry(&sent, wire, 0) == 24);
  assert(decode_tick_size_table_entry(&got, wire, 0) == 24);
  equal_tick_size_table_entry(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_size_table_entry(&got, wire, 0) == 24);
  assert(encode_tick_size_table_entry(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 5 bytes ------------------------------------------- */

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

/* ---- Reported Trade: 72 bytes ------------------------------------------------ */

typedef struct {
  uint8_t timestamp_nanoseconds[4];        /* bytes 0 to 3 */
  uint8_t order_book_id[4];                /* bytes 4 to 7 */
  uint8_t traded_quantity[8];              /* bytes 8 to 15 */
  uint8_t match_id[8];                     /* bytes 16 to 23 */
  uint8_t combo_group_id[4];               /* bytes 24 to 27 */
  uint8_t time_of_trade_execution[8];      /* bytes 28 to 35 */
  uint8_t time_of_trade_agreement[8];      /* bytes 36 to 43 */
  uint8_t time_of_trade_dissemination[8];  /* bytes 44 to 51 */
  uint8_t trade_price[4];                  /* bytes 52 to 55 */
  uint8_t trade_type[2];                   /* bytes 56 to 57 */
  uint8_t reserved_alpha_7[7];             /* bytes 58 to 64 */
  uint8_t second_reserved[7];              /* bytes 65 to 71 */
} ReportedTrade;

/* any Reported Trade at all: every byte one the checker chooses */
static void any_reported_trade(ReportedTrade *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->traded_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->combo_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_of_trade_execution[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_of_trade_agreement[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_of_trade_dissemination[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trade_type[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->reserved_alpha_7[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->second_reserved[i] = arbitrary(); }
}

/* Reported Trade to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_reported_trade(const ReportedTrade *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->traded_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->combo_group_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_of_trade_execution[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_of_trade_agreement[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_of_trade_dissemination[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_type[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->reserved_alpha_7[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->second_reserved[i]; }

  return at;
}

/* Reported Trade off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_reported_trade(ReportedTrade *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->traded_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->combo_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_of_trade_execution[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_of_trade_agreement[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_of_trade_dissemination[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trade_type[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->reserved_alpha_7[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->second_reserved[i] = wire[at++]; }

  return at;
}

/* what was read of Reported Trade is what was written, byte for byte */
static void equal_reported_trade(const ReportedTrade *read, const ReportedTrade *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->traded_quantity[i] == written->traded_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->combo_group_id[i] == written->combo_group_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_of_trade_execution[i] == written->time_of_trade_execution[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_of_trade_agreement[i] == written->time_of_trade_agreement[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_of_trade_dissemination[i] == written->time_of_trade_dissemination[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trade_type[i] == written->trade_type[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->reserved_alpha_7[i] == written->reserved_alpha_7[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->second_reserved[i] == written->second_reserved[i]); }
}

/* Reported Trade: written and read back, then read and written back */
static void check_reported_trade(void) {
  ReportedTrade sent;
  ReportedTrade got;
  uint8_t wire[72];
  uint8_t again[72];

  any_reported_trade(&sent);
  assert(encode_reported_trade(&sent, wire, 0) == 72);
  assert(decode_reported_trade(&got, wire, 0) == 72);
  equal_reported_trade(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_reported_trade(&got, wire, 0) == 72);
  assert(encode_reported_trade(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Message: 12 bytes ------------------------------------------ */

typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t match_id[8];               /* bytes 4 to 11 */
} BrokenTradeMessage;

/* any Broken Trade Message at all: every byte one the checker chooses */
static void any_broken_trade_message(BrokenTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = arbitrary(); }
}

/* Broken Trade Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_message(const BrokenTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_id[i]; }

  return at;
}

/* Broken Trade Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_message(BrokenTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = wire[at++]; }

  return at;
}

/* what was read of Broken Trade Message is what was written, byte for byte */
static void equal_broken_trade_message(const BrokenTradeMessage *read, const BrokenTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_id[i] == written->match_id[i]); }
}

/* Broken Trade Message: written and read back, then read and written back */
static void check_broken_trade_message(void) {
  BrokenTradeMessage sent;
  BrokenTradeMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_broken_trade_message(&sent);
  assert(encode_broken_trade_message(&sent, wire, 0) == 12);
  assert(decode_broken_trade_message(&got, wire, 0) == 12);
  equal_broken_trade_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_message(&got, wire, 0) == 12);
  assert(encode_broken_trade_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Request Message: 30 bytes ----------------------------------------- */

typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t order_book_id[4];          /* bytes 4 to 7 */
  uint8_t reserved_alpha_7[7];       /* bytes 8 to 14 */
  uint8_t reserved_alpha_5[5];       /* bytes 15 to 19 */
  uint8_t reserved_alpha_1;          /* byte 20 */
  uint8_t side;                      /* byte 21 */
  uint8_t quantity[8];               /* bytes 22 to 29 */
} QuoteRequestMessage;

/* any Quote Request Message at all: every byte one the checker chooses */
static void any_quote_request_message(QuoteRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->reserved_alpha_7[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->reserved_alpha_5[i] = arbitrary(); }
  record->reserved_alpha_1 = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
}

/* Quote Request Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_quote_request_message(const QuoteRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->reserved_alpha_7[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->reserved_alpha_5[i]; }
  wire[at++] = record->reserved_alpha_1;
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Quote Request Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_quote_request_message(QuoteRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->reserved_alpha_7[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->reserved_alpha_5[i] = wire[at++]; }
  record->reserved_alpha_1 = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Request Message is what was written, byte for byte */
static void equal_quote_request_message(const QuoteRequestMessage *read, const QuoteRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->reserved_alpha_7[i] == written->reserved_alpha_7[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->reserved_alpha_5[i] == written->reserved_alpha_5[i]); }
  assert(read->reserved_alpha_1 == written->reserved_alpha_1);
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Quote Request Message: written and read back, then read and written back */
static void check_quote_request_message(void) {
  QuoteRequestMessage sent;
  QuoteRequestMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_quote_request_message(&sent);
  assert(encode_quote_request_message(&sent, wire, 0) == 30);
  assert(decode_quote_request_message(&got, wire, 0) == 30);
  equal_quote_request_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_request_message(&got, wire, 0) == 30);
  assert(encode_quote_request_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Interest Messsage: 20 bytes ---------------------------------------- */

/* o - Open Interest Message. */
typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t order_book_id[4];          /* bytes 4 to 7 */
  uint8_t open_interest[8];          /* bytes 8 to 15 */
  uint8_t previous_trading_date[4];  /* bytes 16 to 19 */
} OpenInterestMesssage;

/* any Open Interest Messsage at all: every byte one the checker chooses */
static void any_open_interest_messsage(OpenInterestMesssage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->previous_trading_date[i] = arbitrary(); }
}

/* Open Interest Messsage to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_open_interest_messsage(const OpenInterestMesssage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_interest[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_trading_date[i]; }

  return at;
}

/* Open Interest Messsage off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_open_interest_messsage(OpenInterestMesssage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->previous_trading_date[i] = wire[at++]; }

  return at;
}

/* what was read of Open Interest Messsage is what was written, byte for byte */
static void equal_open_interest_messsage(const OpenInterestMesssage *read, const OpenInterestMesssage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->previous_trading_date[i] == written->previous_trading_date[i]); }
}

/* Open Interest Messsage: written and read back, then read and written back */
static void check_open_interest_messsage(void) {
  OpenInterestMesssage sent;
  OpenInterestMesssage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_open_interest_messsage(&sent);
  assert(encode_open_interest_messsage(&sent, wire, 0) == 20);
  assert(decode_open_interest_messsage(&got, wire, 0) == 20);
  equal_open_interest_messsage(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_open_interest_messsage(&got, wire, 0) == 20);
  assert(encode_open_interest_messsage(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Message: 14 bytes ------------------------------------------------- */

typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t price_type;                /* byte 4 */
  uint8_t order_book_id[4];          /* bytes 5 to 8 */
  uint8_t price_price_4[4];          /* bytes 9 to 12 */
  uint8_t price_source;              /* byte 13 */
} PriceMessage;

/* any Price Message at all: every byte one the checker chooses */
static void any_price_message(PriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  record->price_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_price_4[i] = arbitrary(); }
  record->price_source = arbitrary();
}

/* Price Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_price_message(const PriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  wire[at++] = record->price_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_price_4[i]; }
  wire[at++] = record->price_source;

  return at;
}

/* Price Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_price_message(PriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  record->price_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_price_4[i] = wire[at++]; }
  record->price_source = wire[at++];

  return at;
}

/* what was read of Price Message is what was written, byte for byte */
static void equal_price_message(const PriceMessage *read, const PriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  assert(read->price_type == written->price_type);
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_price_4[i] == written->price_price_4[i]); }
  assert(read->price_source == written->price_source);
}

/* Price Message: written and read back, then read and written back */
static void check_price_message(void) {
  PriceMessage sent;
  PriceMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_price_message(&sent);
  assert(encode_price_message(&sent, wire, 0) == 14);
  assert(decode_price_message(&got, wire, 0) == 14);
  equal_price_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_price_message(&got, wire, 0) == 14);
  assert(encode_price_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market By Level Message: 27 bytes --------------------------------------- */

typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t order_book_id[4];          /* bytes 4 to 7 */
  uint8_t last_message;              /* byte 8 */
  uint8_t level_update_action;       /* byte 9 */
  uint8_t max_depth[2];              /* bytes 10 to 11 */
  uint8_t level_update[2];           /* bytes 12 to 13 */
  uint8_t entry_type;                /* byte 14 */
  uint8_t market_by_level_price[4];  /* bytes 15 to 18 */
  uint8_t quantity[8];               /* bytes 19 to 26 */
} MarketByLevelMessage;

/* any Market By Level Message at all: every byte one the checker chooses */
static void any_market_by_level_message(MarketByLevelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->last_message = arbitrary();
  record->level_update_action = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->max_depth[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->level_update[i] = arbitrary(); }
  record->entry_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->market_by_level_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
}

/* Market By Level Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_market_by_level_message(const MarketByLevelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->last_message;
  wire[at++] = record->level_update_action;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->max_depth[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->level_update[i]; }
  wire[at++] = record->entry_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_by_level_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Market By Level Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_market_by_level_message(MarketByLevelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->last_message = wire[at++];
  record->level_update_action = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->max_depth[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->level_update[i] = wire[at++]; }
  record->entry_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->market_by_level_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Market By Level Message is what was written, byte for byte */
static void equal_market_by_level_message(const MarketByLevelMessage *read, const MarketByLevelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->last_message == written->last_message);
  assert(read->level_update_action == written->level_update_action);
  for (size_t i = 0; i < 2; i++) { assert(read->max_depth[i] == written->max_depth[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->level_update[i] == written->level_update[i]); }
  assert(read->entry_type == written->entry_type);
  for (size_t i = 0; i < 4; i++) { assert(read->market_by_level_price[i] == written->market_by_level_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Market By Level Message: written and read back, then read and written back */
static void check_market_by_level_message(void) {
  MarketByLevelMessage sent;
  MarketByLevelMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_market_by_level_message(&sent);
  assert(encode_market_by_level_message(&sent, wire, 0) == 27);
  assert(decode_market_by_level_message(&got, wire, 0) == 27);
  equal_market_by_level_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_market_by_level_message(&got, wire, 0) == 27);
  assert(encode_market_by_level_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Price Message: 60 bytes -------------------------------------- */

typedef struct {
  uint8_t timestamp_nanoseconds[4];     /* bytes 0 to 3 */
  uint8_t underlying_order_book_id[4];  /* bytes 4 to 7 */
  uint8_t bid_price[4];                 /* bytes 8 to 11 */
  uint8_t ask_price[4];                 /* bytes 12 to 15 */
  uint8_t closing_price[4];             /* bytes 16 to 19 */
  uint8_t opening_price[4];             /* bytes 20 to 23 */
  uint8_t high_price[4];                /* bytes 24 to 27 */
  uint8_t low_price[4];                 /* bytes 28 to 31 */
  uint8_t last_price[4];                /* bytes 32 to 35 */
  uint8_t turnover[8];                  /* bytes 36 to 43 */
  uint8_t best_bid_volume[8];           /* bytes 44 to 51 */
  uint8_t best_ask_volume[8];           /* bytes 52 to 59 */
} UnderlyingPriceMessage;

/* any Underlying Price Message at all: every byte one the checker chooses */
static void any_underlying_price_message(UnderlyingPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->best_ask_volume[i] = arbitrary(); }
}

/* Underlying Price Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_underlying_price_message(const UnderlyingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->turnover[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_bid_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->best_ask_volume[i]; }

  return at;
}

/* Underlying Price Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_underlying_price_message(UnderlyingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->turnover[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_bid_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->best_ask_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Underlying Price Message is what was written, byte for byte */
static void equal_underlying_price_message(const UnderlyingPriceMessage *read, const UnderlyingPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_order_book_id[i] == written->underlying_order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->turnover[i] == written->turnover[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_bid_volume[i] == written->best_bid_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->best_ask_volume[i] == written->best_ask_volume[i]); }
}

/* Underlying Price Message: written and read back, then read and written back */
static void check_underlying_price_message(void) {
  UnderlyingPriceMessage sent;
  UnderlyingPriceMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_underlying_price_message(&sent);
  assert(encode_underlying_price_message(&sent, wire, 0) == 60);
  assert(decode_underlying_price_message(&got, wire, 0) == 60);
  equal_underlying_price_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_price_message(&got, wire, 0) == 60);
  assert(encode_underlying_price_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_seconds_message();
  check_order_book_directory();
  check_market_directory();
  check_combination_order_book_leg_directory();
  check_tick_size_table_entry();
  check_system_event_message();
  check_reported_trade();
  check_broken_trade_message();
  check_quote_request_message();
  check_open_interest_messsage();
  check_price_message();
  check_market_by_level_message();
  check_underlying_price_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
