// nasdaq/nfxfutures/marketdata/NfxFutures_MarketData_v2_30_7.c
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

/* ---- Order Book Directory: 135 bytes ----------------------------------------- */

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
  uint8_t market_id[2];                            /* bytes 128 to 129 */
  uint8_t strategy_subtype;                        /* byte 130 */
  uint8_t minimum_quantity_and_multiple[4];        /* bytes 131 to 134 */
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
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = arbitrary(); }
  record->strategy_subtype = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity_and_multiple[i] = arbitrary(); }
}

/* Order Book Directory to the wire: 135 bytes from at, returning where the next byte goes */
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
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id[i]; }
  wire[at++] = record->strategy_subtype;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity_and_multiple[i]; }

  return at;
}

/* Order Book Directory off the wire: 135 bytes from at, returning where the next byte lies */
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
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = wire[at++]; }
  record->strategy_subtype = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity_and_multiple[i] = wire[at++]; }

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
  for (size_t i = 0; i < 2; i++) { assert(read->market_id[i] == written->market_id[i]); }
  assert(read->strategy_subtype == written->strategy_subtype);
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity_and_multiple[i] == written->minimum_quantity_and_multiple[i]); }
}

/* Order Book Directory: written and read back, then read and written back */
static void check_order_book_directory(void) {
  OrderBookDirectory sent;
  OrderBookDirectory got;
  uint8_t wire[135];
  uint8_t again[135];

  any_order_book_directory(&sent);
  assert(encode_order_book_directory(&sent, wire, 0) == 135);
  assert(decode_order_book_directory(&got, wire, 0) == 135);
  equal_order_book_directory(&got, &sent);

  for (size_t i = 0; i < 135; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_directory(&got, wire, 0) == 135);
  assert(encode_order_book_directory(&got, again, 0) == 135);
  for (size_t i = 0; i < 135; i++) { assert(again[i] == wire[i]); }
}

/* ---- Combination Order Book Leg: 29 bytes ------------------------------------ */

/* Combination Order book Directory Message */
typedef struct {
  uint8_t timestamp_nanoseconds[4];      /* bytes 0 to 3 */
  uint8_t combination_order_book_id[4];  /* bytes 4 to 7 */
  uint8_t leg_order_book_id[4];          /* bytes 8 to 11 */
  uint8_t leg_side;                      /* byte 12 */
  uint8_t leg_ratio[4];                  /* bytes 13 to 16 */
  uint8_t leg_price_future[4];           /* bytes 17 to 20 */
  uint8_t leg_delta[4];                  /* bytes 21 to 24 */
  uint8_t leg_quantity_future[4];        /* bytes 25 to 28 */
} CombinationOrderBookLeg;

/* any Combination Order Book Leg at all: every byte one the checker chooses */
static void any_combination_order_book_leg(CombinationOrderBookLeg *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->combination_order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_order_book_id[i] = arbitrary(); }
  record->leg_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_price_future[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_quantity_future[i] = arbitrary(); }
}

/* Combination Order Book Leg to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_combination_order_book_leg(const CombinationOrderBookLeg *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->combination_order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_order_book_id[i]; }
  wire[at++] = record->leg_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_price_future[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_quantity_future[i]; }

  return at;
}

/* Combination Order Book Leg off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_combination_order_book_leg(CombinationOrderBookLeg *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->combination_order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_order_book_id[i] = wire[at++]; }
  record->leg_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_price_future[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_quantity_future[i] = wire[at++]; }

  return at;
}

/* what was read of Combination Order Book Leg is what was written, byte for byte */
static void equal_combination_order_book_leg(const CombinationOrderBookLeg *read, const CombinationOrderBookLeg *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->combination_order_book_id[i] == written->combination_order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_order_book_id[i] == written->leg_order_book_id[i]); }
  assert(read->leg_side == written->leg_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio[i] == written->leg_ratio[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_price_future[i] == written->leg_price_future[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_delta[i] == written->leg_delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_quantity_future[i] == written->leg_quantity_future[i]); }
}

/* Combination Order Book Leg: written and read back, then read and written back */
static void check_combination_order_book_leg(void) {
  CombinationOrderBookLeg sent;
  CombinationOrderBookLeg got;
  uint8_t wire[29];
  uint8_t again[29];

  any_combination_order_book_leg(&sent);
  assert(encode_combination_order_book_leg(&sent, wire, 0) == 29);
  assert(decode_combination_order_book_leg(&got, wire, 0) == 29);
  equal_combination_order_book_leg(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_combination_order_book_leg(&got, wire, 0) == 29);
  assert(encode_combination_order_book_leg(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
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

/* ---- Order Book State Message: 28 bytes -------------------------------------- */

typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t order_book_id[4];          /* bytes 4 to 7 */
  uint8_t state_name[20];            /* bytes 8 to 27 */
} OrderBookStateMessage;

/* any Order Book State Message at all: every byte one the checker chooses */
static void any_order_book_state_message(OrderBookStateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->state_name[i] = arbitrary(); }
}

/* Order Book State Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_order_book_state_message(const OrderBookStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->state_name[i]; }

  return at;
}

/* Order Book State Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_order_book_state_message(OrderBookStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->state_name[i] = wire[at++]; }

  return at;
}

/* what was read of Order Book State Message is what was written, byte for byte */
static void equal_order_book_state_message(const OrderBookStateMessage *read, const OrderBookStateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->state_name[i] == written->state_name[i]); }
}

/* Order Book State Message: written and read back, then read and written back */
static void check_order_book_state_message(void) {
  OrderBookStateMessage sent;
  OrderBookStateMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_order_book_state_message(&sent);
  assert(encode_order_book_state_message(&sent, wire, 0) == 28);
  assert(decode_order_book_state_message(&got, wire, 0) == 28);
  equal_order_book_state_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_state_message(&got, wire, 0) == 28);
  assert(encode_order_book_state_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
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
  uint8_t reserved[7];                     /* bytes 58 to 64 */
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
  for (size_t i = 0; i < 7; i++) { record->reserved[i] = arbitrary(); }
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
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->reserved[i]; }
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
  for (size_t i = 0; i < 7; i++) { record->reserved[i] = wire[at++]; }
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
  for (size_t i = 0; i < 7; i++) { assert(read->reserved[i] == written->reserved[i]); }
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

/* ---- Open Interest Message: 16 bytes ----------------------------------------- */

typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t order_book_id[4];          /* bytes 4 to 7 */
  uint8_t open_interest[8];          /* bytes 8 to 15 */
} OpenInterestMessage;

/* any Open Interest Message at all: every byte one the checker chooses */
static void any_open_interest_message(OpenInterestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = arbitrary(); }
}

/* Open Interest Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_open_interest_message(const OpenInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_interest[i]; }

  return at;
}

/* Open Interest Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_open_interest_message(OpenInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = wire[at++]; }

  return at;
}

/* what was read of Open Interest Message is what was written, byte for byte */
static void equal_open_interest_message(const OpenInterestMessage *read, const OpenInterestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
}

/* Open Interest Message: written and read back, then read and written back */
static void check_open_interest_message(void) {
  OpenInterestMessage sent;
  OpenInterestMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_open_interest_message(&sent);
  assert(encode_open_interest_message(&sent, wire, 0) == 16);
  assert(decode_open_interest_message(&got, wire, 0) == 16);
  equal_open_interest_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_open_interest_message(&got, wire, 0) == 16);
  assert(encode_open_interest_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Message: 13 bytes ------------------------------------------------- */

typedef struct {
  uint8_t timestamp_nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t price_type;                /* byte 4 */
  uint8_t order_book_id[4];          /* bytes 5 to 8 */
  uint8_t price[4];                  /* bytes 9 to 12 */
} PriceMessage;

/* any Price Message at all: every byte one the checker chooses */
static void any_price_message(PriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  record->price_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Price Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_price_message(const PriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  wire[at++] = record->price_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Price Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_price_message(PriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  record->price_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Price Message is what was written, byte for byte */
static void equal_price_message(const PriceMessage *read, const PriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  assert(read->price_type == written->price_type);
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Price Message: written and read back, then read and written back */
static void check_price_message(void) {
  PriceMessage sent;
  PriceMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_price_message(&sent);
  assert(encode_price_message(&sent, wire, 0) == 13);
  assert(decode_price_message(&got, wire, 0) == 13);
  equal_price_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_price_message(&got, wire, 0) == 13);
  assert(encode_price_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_seconds_message();
  check_order_book_directory();
  check_combination_order_book_leg();
  check_tick_size_table_entry();
  check_system_event_message();
  check_order_book_state_message();
  check_reported_trade();
  check_broken_trade_message();
  check_open_interest_message();
  check_price_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
