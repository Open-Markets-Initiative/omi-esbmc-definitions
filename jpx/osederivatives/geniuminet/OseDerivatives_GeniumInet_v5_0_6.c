// jpx/osederivatives/geniuminet/OseDerivatives_GeniumInet_v5_0_6.c
/*
 * Japan Exchange Group Genium Inet
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

/* Sent every second for which at least one ITCH message is being generated */
typedef struct {
  uint8_t seconds[4];  /* bytes 0 to 3 */
} SecondsMessage;

/* any Seconds Message at all: every byte one the checker chooses */
static void any_seconds_message(SecondsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
}

/* Seconds Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_seconds_message(const SecondsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }

  return at;
}

/* Seconds Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_seconds_message(SecondsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }

  return at;
}

/* what was read of Seconds Message is what was written, byte for byte */
static void equal_seconds_message(const SecondsMessage *read, const SecondsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
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

/* ---- Order Book Directory: 128 bytes ----------------------------------------- */

/* Disseminated for all active securities at start of day or intra-day. */
typedef struct {
  uint8_t nanoseconds[4];                /* bytes 0 to 3 */
  uint8_t order_book_id[4];              /* bytes 4 to 7 */
  uint8_t symbol[32];                    /* bytes 8 to 39 */
  uint8_t long_name[32];                 /* bytes 40 to 71 */
  uint8_t isin[12];                      /* bytes 72 to 83 */
  uint8_t financial_product;             /* byte 84 */
  uint8_t trading_currency[3];           /* bytes 85 to 87 */
  uint8_t decimals_in_price[2];          /* bytes 88 to 89 */
  uint8_t decimals_in_nominal_value[2];  /* bytes 90 to 91 */
  uint8_t odd_lot_size[4];               /* bytes 92 to 95 */
  uint8_t round_lot_size[4];             /* bytes 96 to 99 */
  uint8_t block_lot_size[4];             /* bytes 100 to 103 */
  uint8_t nominal_value[8];              /* bytes 104 to 111 */
  uint8_t number_of_legs;                /* byte 112 */
  uint8_t underlying_orderbook_id[4];    /* bytes 113 to 116 */
  uint8_t strike_price[4];               /* bytes 117 to 120 */
  uint8_t expiration_date[4];            /* bytes 121 to 124 */
  uint8_t decimals_in_strike_price[2];   /* bytes 125 to 126 */
  uint8_t put_or_call;                   /* byte 127 */
} OrderBookDirectory;

/* any Order Book Directory at all: every byte one the checker chooses */
static void any_order_book_directory(OrderBookDirectory *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->long_name[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  record->financial_product = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->decimals_in_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->decimals_in_nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->odd_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->round_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->block_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = arbitrary(); }
  record->number_of_legs = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->underlying_orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->decimals_in_strike_price[i] = arbitrary(); }
  record->put_or_call = arbitrary();
}

/* Order Book Directory to the wire: 128 bytes from at, returning where the next byte goes */
static size_t encode_order_book_directory(const OrderBookDirectory *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->long_name[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  wire[at++] = record->financial_product;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_currency[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->decimals_in_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->decimals_in_nominal_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->odd_lot_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->round_lot_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_lot_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nominal_value[i]; }
  wire[at++] = record->number_of_legs;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_orderbook_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->decimals_in_strike_price[i]; }
  wire[at++] = record->put_or_call;

  return at;
}

/* Order Book Directory off the wire: 128 bytes from at, returning where the next byte lies */
static size_t decode_order_book_directory(OrderBookDirectory *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->long_name[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  record->financial_product = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->decimals_in_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->decimals_in_nominal_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->odd_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->round_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->block_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = wire[at++]; }
  record->number_of_legs = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->underlying_orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->decimals_in_strike_price[i] = wire[at++]; }
  record->put_or_call = wire[at++];

  return at;
}

/* what was read of Order Book Directory is what was written, byte for byte */
static void equal_order_book_directory(const OrderBookDirectory *read, const OrderBookDirectory *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->long_name[i] == written->long_name[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  assert(read->financial_product == written->financial_product);
  for (size_t i = 0; i < 3; i++) { assert(read->trading_currency[i] == written->trading_currency[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->decimals_in_price[i] == written->decimals_in_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->decimals_in_nominal_value[i] == written->decimals_in_nominal_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->odd_lot_size[i] == written->odd_lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->round_lot_size[i] == written->round_lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->block_lot_size[i] == written->block_lot_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nominal_value[i] == written->nominal_value[i]); }
  assert(read->number_of_legs == written->number_of_legs);
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_orderbook_id[i] == written->underlying_orderbook_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->decimals_in_strike_price[i] == written->decimals_in_strike_price[i]); }
  assert(read->put_or_call == written->put_or_call);
}

/* Order Book Directory: written and read back, then read and written back */
static void check_order_book_directory(void) {
  OrderBookDirectory sent;
  OrderBookDirectory got;
  uint8_t wire[128];
  uint8_t again[128];

  any_order_book_directory(&sent);
  assert(encode_order_book_directory(&sent, wire, 0) == 128);
  assert(decode_order_book_directory(&got, wire, 0) == 128);
  equal_order_book_directory(&got, &sent);

  for (size_t i = 0; i < 128; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_directory(&got, wire, 0) == 128);
  assert(encode_order_book_directory(&got, again, 0) == 128);
  for (size_t i = 0; i < 128; i++) { assert(again[i] == wire[i]); }
}

/* ---- Combination Orderbook Leg: 17 bytes ------------------------------------- */

/* Mapping between a combination orderbook and its leg orderbooks. */
typedef struct {
  uint8_t nanoseconds[4];               /* bytes 0 to 3 */
  uint8_t combination_orderbook_id[4];  /* bytes 4 to 7 */
  uint8_t leg_orderbook_id[4];          /* bytes 8 to 11 */
  uint8_t leg_side;                     /* byte 12 */
  uint8_t leg_ratio[4];                 /* bytes 13 to 16 */
} CombinationOrderbookLeg;

/* any Combination Orderbook Leg at all: every byte one the checker chooses */
static void any_combination_orderbook_leg(CombinationOrderbookLeg *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->combination_orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_orderbook_id[i] = arbitrary(); }
  record->leg_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_ratio[i] = arbitrary(); }
}

/* Combination Orderbook Leg to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_combination_orderbook_leg(const CombinationOrderbookLeg *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->combination_orderbook_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_orderbook_id[i]; }
  wire[at++] = record->leg_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio[i]; }

  return at;
}

/* Combination Orderbook Leg off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_combination_orderbook_leg(CombinationOrderbookLeg *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->combination_orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_orderbook_id[i] = wire[at++]; }
  record->leg_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_ratio[i] = wire[at++]; }

  return at;
}

/* what was read of Combination Orderbook Leg is what was written, byte for byte */
static void equal_combination_orderbook_leg(const CombinationOrderbookLeg *read, const CombinationOrderbookLeg *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->combination_orderbook_id[i] == written->combination_orderbook_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_orderbook_id[i] == written->leg_orderbook_id[i]); }
  assert(read->leg_side == written->leg_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio[i] == written->leg_ratio[i]); }
}

/* Combination Orderbook Leg: written and read back, then read and written back */
static void check_combination_orderbook_leg(void) {
  CombinationOrderbookLeg sent;
  CombinationOrderbookLeg got;
  uint8_t wire[17];
  uint8_t again[17];

  any_combination_orderbook_leg(&sent);
  assert(encode_combination_orderbook_leg(&sent, wire, 0) == 17);
  assert(decode_combination_orderbook_leg(&got, wire, 0) == 17);
  equal_combination_orderbook_leg(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_combination_orderbook_leg(&got, wire, 0) == 17);
  assert(encode_combination_orderbook_leg(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Size Table Entry: 24 bytes ----------------------------------------- */

/* Information on a tick size for a price range. */
typedef struct {
  uint8_t nanoseconds[4];    /* bytes 0 to 3 */
  uint8_t order_book_id[4];  /* bytes 4 to 7 */
  uint8_t tick_size[8];      /* bytes 8 to 15 */
  uint8_t price_from[4];     /* bytes 16 to 19 */
  uint8_t price_to[4];       /* bytes 20 to 23 */
} TickSizeTableEntry;

/* any Tick Size Table Entry at all: every byte one the checker chooses */
static void any_tick_size_table_entry(TickSizeTableEntry *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_from[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_to[i] = arbitrary(); }
}

/* Tick Size Table Entry to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_tick_size_table_entry(const TickSizeTableEntry *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_from[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_to[i]; }

  return at;
}

/* Tick Size Table Entry off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_tick_size_table_entry(TickSizeTableEntry *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_from[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_to[i] = wire[at++]; }

  return at;
}

/* what was read of Tick Size Table Entry is what was written, byte for byte */
static void equal_tick_size_table_entry(const TickSizeTableEntry *read, const TickSizeTableEntry *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
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

/* Signals a market or data feed handler event. */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t event_code;      /* byte 4 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
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

/* Relays information on state changes. */
typedef struct {
  uint8_t nanoseconds[4];    /* bytes 0 to 3 */
  uint8_t order_book_id[4];  /* bytes 4 to 7 */
  uint8_t state_name[20];    /* bytes 8 to 27 */
} OrderBookStateMessage;

/* any Order Book State Message at all: every byte one the checker chooses */
static void any_order_book_state_message(OrderBookStateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->state_name[i] = arbitrary(); }
}

/* Order Book State Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_order_book_state_message(const OrderBookStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->state_name[i]; }

  return at;
}

/* Order Book State Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_order_book_state_message(OrderBookStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->state_name[i] = wire[at++]; }

  return at;
}

/* what was read of Order Book State Message is what was written, byte for byte */
static void equal_order_book_state_message(const OrderBookStateMessage *read, const OrderBookStateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
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

/* ---- Order Executed Message: 51 bytes ---------------------------------------- */

/* Sent whenever an order on the book is executed in whole or in part. */
typedef struct {
  uint8_t nanoseconds[4];                  /* bytes 0 to 3 */
  uint8_t order_id[8];                     /* bytes 4 to 11 */
  uint8_t order_book_id[4];                /* bytes 12 to 15 */
  uint8_t side;                            /* byte 16 */
  uint8_t executed_quantity[8];            /* bytes 17 to 24 */
  uint8_t match_id[8];                     /* bytes 25 to 32 */
  uint8_t combo_group_id[4];               /* bytes 33 to 36 */
  uint8_t participant_id_owner[7];         /* bytes 37 to 43 */
  uint8_t participant_id_counterparty[7];  /* bytes 44 to 50 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->combo_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->participant_id_owner[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->participant_id_counterparty[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->combo_group_id[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->participant_id_owner[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->participant_id_counterparty[i]; }

  return at;
}

/* Order Executed Message off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->combo_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->participant_id_owner[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->participant_id_counterparty[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->combo_group_id[i] == written->combo_group_id[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->participant_id_owner[i] == written->participant_id_owner[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->participant_id_counterparty[i] == written->participant_id_counterparty[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[51];
  uint8_t again[51];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 51);
  assert(decode_order_executed_message(&got, wire, 0) == 51);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 51);
  assert(encode_order_executed_message(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed With Price Message: 57 bytes ----------------------------- */

/* Sent when an order is executed at a price different than the initial display price. */
typedef struct {
  uint8_t nanoseconds[4];                  /* bytes 0 to 3 */
  uint8_t order_id[8];                     /* bytes 4 to 11 */
  uint8_t order_book_id[4];                /* bytes 12 to 15 */
  uint8_t side;                            /* byte 16 */
  uint8_t executed_quantity[8];            /* bytes 17 to 24 */
  uint8_t match_id[8];                     /* bytes 25 to 32 */
  uint8_t combo_group_id[4];               /* bytes 33 to 36 */
  uint8_t owner_participant_id[7];         /* bytes 37 to 43 */
  uint8_t counterparty_participant_id[7];  /* bytes 44 to 50 */
  uint8_t trade_price[4];                  /* bytes 51 to 54 */
  uint8_t occurred_at_cross;               /* byte 55 */
  uint8_t printable;                       /* byte 56 */
} OrderExecutedWithPriceMessage;

/* any Order Executed With Price Message at all: every byte one the checker chooses */
static void any_order_executed_with_price_message(OrderExecutedWithPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->combo_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->owner_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->counterparty_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  record->occurred_at_cross = arbitrary();
  record->printable = arbitrary();
}

/* Order Executed With Price Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_with_price_message(const OrderExecutedWithPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->combo_group_id[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->owner_participant_id[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->counterparty_participant_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  wire[at++] = record->occurred_at_cross;
  wire[at++] = record->printable;

  return at;
}

/* Order Executed With Price Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_with_price_message(OrderExecutedWithPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->combo_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->owner_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->counterparty_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  record->occurred_at_cross = wire[at++];
  record->printable = wire[at++];

  return at;
}

/* what was read of Order Executed With Price Message is what was written, byte for byte */
static void equal_order_executed_with_price_message(const OrderExecutedWithPriceMessage *read, const OrderExecutedWithPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->combo_group_id[i] == written->combo_group_id[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->owner_participant_id[i] == written->owner_participant_id[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->counterparty_participant_id[i] == written->counterparty_participant_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  assert(read->occurred_at_cross == written->occurred_at_cross);
  assert(read->printable == written->printable);
}

/* Order Executed With Price Message: written and read back, then read and written back */
static void check_order_executed_with_price_message(void) {
  OrderExecutedWithPriceMessage sent;
  OrderExecutedWithPriceMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_order_executed_with_price_message(&sent);
  assert(encode_order_executed_with_price_message(&sent, wire, 0) == 57);
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 57);
  equal_order_executed_with_price_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 57);
  assert(encode_order_executed_with_price_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Delete Message: 17 bytes ------------------------------------------ */

/* Sent whenever an order on the book is being deleted. There will be no remaining quantity. */
typedef struct {
  uint8_t nanoseconds[4];    /* bytes 0 to 3 */
  uint8_t order_id[8];       /* bytes 4 to 11 */
  uint8_t order_book_id[4];  /* bytes 12 to 15 */
  uint8_t side;              /* byte 16 */
} OrderDeleteMessage;

/* any Order Delete Message at all: every byte one the checker chooses */
static void any_order_delete_message(OrderDeleteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
}

/* Order Delete Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_order_delete_message(const OrderDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;

  return at;
}

/* Order Delete Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_order_delete_message(OrderDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];

  return at;
}

/* what was read of Order Delete Message is what was written, byte for byte */
static void equal_order_delete_message(const OrderDeleteMessage *read, const OrderDeleteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
}

/* Order Delete Message: written and read back, then read and written back */
static void check_order_delete_message(void) {
  OrderDeleteMessage sent;
  OrderDeleteMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_order_delete_message(&sent);
  assert(encode_order_delete_message(&sent, wire, 0) == 17);
  assert(decode_order_delete_message(&got, wire, 0) == 17);
  equal_order_delete_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_order_delete_message(&got, wire, 0) == 17);
  assert(encode_order_delete_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 49 bytes ------------------------------------------------- */

/* Execution details for normal match events involving non-displayable order types or cross trades. */
typedef struct {
  uint8_t nanoseconds[4];                  /* bytes 0 to 3 */
  uint8_t match_id[8];                     /* bytes 4 to 11 */
  uint8_t combo_group_id[4];               /* bytes 12 to 15 */
  uint8_t side;                            /* byte 16 */
  uint8_t quantity[8];                     /* bytes 17 to 24 */
  uint8_t order_book_id[4];                /* bytes 25 to 28 */
  uint8_t trade_price[4];                  /* bytes 29 to 32 */
  uint8_t owner_participant_id[7];         /* bytes 33 to 39 */
  uint8_t counterparty_participant_id[7];  /* bytes 40 to 46 */
  uint8_t printable;                       /* byte 47 */
  uint8_t occurred_at_cross;               /* byte 48 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->combo_group_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->owner_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->counterparty_participant_id[i] = arbitrary(); }
  record->printable = arbitrary();
  record->occurred_at_cross = arbitrary();
}

/* Trade Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->combo_group_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->owner_participant_id[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->counterparty_participant_id[i]; }
  wire[at++] = record->printable;
  wire[at++] = record->occurred_at_cross;

  return at;
}

/* Trade Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->combo_group_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->owner_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->counterparty_participant_id[i] = wire[at++]; }
  record->printable = wire[at++];
  record->occurred_at_cross = wire[at++];

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->combo_group_id[i] == written->combo_group_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->owner_participant_id[i] == written->owner_participant_id[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->counterparty_participant_id[i] == written->counterparty_participant_id[i]); }
  assert(read->printable == written->printable);
  assert(read->occurred_at_cross == written->occurred_at_cross);
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[49];
  uint8_t again[49];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 49);
  assert(decode_trade_message(&got, wire, 0) == 49);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 49);
  assert(encode_trade_message(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- Equilibrium Price Update: 52 bytes -------------------------------------- */

/* Provides changes in equilibrium price during auctions. */
typedef struct {
  uint8_t nanoseconds[4];                                  /* bytes 0 to 3 */
  uint8_t order_book_id[4];                                /* bytes 4 to 7 */
  uint8_t available_bid_quantity_at_equilibrium_price[8];  /* bytes 8 to 15 */
  uint8_t available_ask_quantity_at_equilibrium_price[8];  /* bytes 16 to 23 */
  uint8_t equilibrium_price[4];                            /* bytes 24 to 27 */
  uint8_t reserved_24[24];                                 /* bytes 28 to 51 */
} EquilibriumPriceUpdate;

/* any Equilibrium Price Update at all: every byte one the checker chooses */
static void any_equilibrium_price_update(EquilibriumPriceUpdate *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->available_bid_quantity_at_equilibrium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->available_ask_quantity_at_equilibrium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->equilibrium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 24; i++) { record->reserved_24[i] = arbitrary(); }
}

/* Equilibrium Price Update to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_equilibrium_price_update(const EquilibriumPriceUpdate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->available_bid_quantity_at_equilibrium_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->available_ask_quantity_at_equilibrium_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->equilibrium_price[i]; }
  for (size_t i = 0; i < 24; i++) { wire[at++] = record->reserved_24[i]; }

  return at;
}

/* Equilibrium Price Update off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_equilibrium_price_update(EquilibriumPriceUpdate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->available_bid_quantity_at_equilibrium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->available_ask_quantity_at_equilibrium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->equilibrium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 24; i++) { record->reserved_24[i] = wire[at++]; }

  return at;
}

/* what was read of Equilibrium Price Update is what was written, byte for byte */
static void equal_equilibrium_price_update(const EquilibriumPriceUpdate *read, const EquilibriumPriceUpdate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->available_bid_quantity_at_equilibrium_price[i] == written->available_bid_quantity_at_equilibrium_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->available_ask_quantity_at_equilibrium_price[i] == written->available_ask_quantity_at_equilibrium_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->equilibrium_price[i] == written->equilibrium_price[i]); }
  for (size_t i = 0; i < 24; i++) { assert(read->reserved_24[i] == written->reserved_24[i]); }
}

/* Equilibrium Price Update: written and read back, then read and written back */
static void check_equilibrium_price_update(void) {
  EquilibriumPriceUpdate sent;
  EquilibriumPriceUpdate got;
  uint8_t wire[52];
  uint8_t again[52];

  any_equilibrium_price_update(&sent);
  assert(encode_equilibrium_price_update(&sent, wire, 0) == 52);
  assert(decode_equilibrium_price_update(&got, wire, 0) == 52);
  equal_equilibrium_price_update(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_equilibrium_price_update(&got, wire, 0) == 52);
  assert(encode_equilibrium_price_update(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_seconds_message();
  check_order_book_directory();
  check_combination_orderbook_leg();
  check_tick_size_table_entry();
  check_system_event_message();
  check_order_book_state_message();
  check_order_executed_message();
  check_order_executed_with_price_message();
  check_order_delete_message();
  check_trade_message();
  check_equilibrium_price_update();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
