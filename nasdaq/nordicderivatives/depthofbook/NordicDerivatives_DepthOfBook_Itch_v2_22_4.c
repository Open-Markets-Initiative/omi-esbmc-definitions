// nasdaq/nordicderivatives/depthofbook/NordicDerivatives_DepthOfBook_Itch_v2_22_4.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Genium INET Depth Of Book
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

/* This message is sent every second for which at least one ITCH message is being generated. The message contains the number of seconds since the start of 1970-01-01 00:00:00 UTC, also called Unix Time */
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

/* ---- Order Book Directory: 112 bytes ----------------------------------------- */

/* At the start of each trading day, Order book directory messages are disseminated for all active securities, including halted securities, in the Genium INET Trading system. Intra-day transmissions of this message may occur when new order books are added to the system; updates to existing order books may also be represented by intra-day Order book Directory messages */
typedef struct {
  uint8_t nanoseconds[4];                          /* bytes 0 to 3 */
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
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->odd_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->round_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->block_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = arbitrary(); }
}

/* Order Book Directory to the wire: 112 bytes from at, returning where the next byte goes */
static size_t encode_order_book_directory(const OrderBookDirectory *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
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

  return at;
}

/* Order Book Directory off the wire: 112 bytes from at, returning where the next byte lies */
static size_t decode_order_book_directory(OrderBookDirectory *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
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
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_price[i] == written->number_of_decimals_in_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_nominal_value[i] == written->number_of_decimals_in_nominal_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->odd_lot_size[i] == written->odd_lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->round_lot_size[i] == written->round_lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->block_lot_size[i] == written->block_lot_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nominal_value[i] == written->nominal_value[i]); }
}

/* Order Book Directory: written and read back, then read and written back */
static void check_order_book_directory(void) {
  OrderBookDirectory sent;
  OrderBookDirectory got;
  uint8_t wire[112];
  uint8_t again[112];

  any_order_book_directory(&sent);
  assert(encode_order_book_directory(&sent, wire, 0) == 112);
  assert(decode_order_book_directory(&got, wire, 0) == 112);
  equal_order_book_directory(&got, &sent);

  for (size_t i = 0; i < 112; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_directory(&got, wire, 0) == 112);
  assert(encode_order_book_directory(&got, again, 0) == 112);
  for (size_t i = 0; i < 112; i++) { assert(again[i] == wire[i]); }
}

/* ---- Combination Order Book Directory: 260 bytes ----------------------------- */

/* Specialized directory message used when Combination order books are traded in the marketplace. It represents both standard combinations defined by the exchange and tailor-made combinations created by members. Intra-day transmissions may occur when new combination order books are added, typically for tailor-made combinations */
typedef struct {
  uint8_t nanoseconds[4];                          /* bytes 0 to 3 */
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
  uint8_t leg_1_symbol[32];                        /* bytes 112 to 143 */
  uint8_t leg_1_side;                              /* byte 144 */
  uint8_t leg_1_ratio[4];                          /* bytes 145 to 148 */
  uint8_t leg_2_symbol[32];                        /* bytes 149 to 180 */
  uint8_t leg_2_side;                              /* byte 181 */
  uint8_t leg_2_ratio[4];                          /* bytes 182 to 185 */
  uint8_t leg_3_symbol[32];                        /* bytes 186 to 217 */
  uint8_t leg_3_side;                              /* byte 218 */
  uint8_t leg_3_ratio[4];                          /* bytes 219 to 222 */
  uint8_t leg_4_symbol[32];                        /* bytes 223 to 254 */
  uint8_t leg_4_side;                              /* byte 255 */
  uint8_t leg_4_ratio[4];                          /* bytes 256 to 259 */
} CombinationOrderBookDirectory;

/* any Combination Order Book Directory at all: every byte one the checker chooses */
static void any_combination_order_book_directory(CombinationOrderBookDirectory *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
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
  for (size_t i = 0; i < 32; i++) { record->leg_1_symbol[i] = arbitrary(); }
  record->leg_1_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_1_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->leg_2_symbol[i] = arbitrary(); }
  record->leg_2_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_2_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->leg_3_symbol[i] = arbitrary(); }
  record->leg_3_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_3_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->leg_4_symbol[i] = arbitrary(); }
  record->leg_4_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_4_ratio[i] = arbitrary(); }
}

/* Combination Order Book Directory to the wire: 260 bytes from at, returning where the next byte goes */
static size_t encode_combination_order_book_directory(const CombinationOrderBookDirectory *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
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
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->leg_1_symbol[i]; }
  wire[at++] = record->leg_1_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_1_ratio[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->leg_2_symbol[i]; }
  wire[at++] = record->leg_2_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_2_ratio[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->leg_3_symbol[i]; }
  wire[at++] = record->leg_3_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_3_ratio[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->leg_4_symbol[i]; }
  wire[at++] = record->leg_4_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_4_ratio[i]; }

  return at;
}

/* Combination Order Book Directory off the wire: 260 bytes from at, returning where the next byte lies */
static size_t decode_combination_order_book_directory(CombinationOrderBookDirectory *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
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
  for (size_t i = 0; i < 32; i++) { record->leg_1_symbol[i] = wire[at++]; }
  record->leg_1_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_1_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->leg_2_symbol[i] = wire[at++]; }
  record->leg_2_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_2_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->leg_3_symbol[i] = wire[at++]; }
  record->leg_3_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_3_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->leg_4_symbol[i] = wire[at++]; }
  record->leg_4_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_4_ratio[i] = wire[at++]; }

  return at;
}

/* what was read of Combination Order Book Directory is what was written, byte for byte */
static void equal_combination_order_book_directory(const CombinationOrderBookDirectory *read, const CombinationOrderBookDirectory *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
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
  for (size_t i = 0; i < 32; i++) { assert(read->leg_1_symbol[i] == written->leg_1_symbol[i]); }
  assert(read->leg_1_side == written->leg_1_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_1_ratio[i] == written->leg_1_ratio[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->leg_2_symbol[i] == written->leg_2_symbol[i]); }
  assert(read->leg_2_side == written->leg_2_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_2_ratio[i] == written->leg_2_ratio[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->leg_3_symbol[i] == written->leg_3_symbol[i]); }
  assert(read->leg_3_side == written->leg_3_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_3_ratio[i] == written->leg_3_ratio[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->leg_4_symbol[i] == written->leg_4_symbol[i]); }
  assert(read->leg_4_side == written->leg_4_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_4_ratio[i] == written->leg_4_ratio[i]); }
}

/* Combination Order Book Directory: written and read back, then read and written back */
static void check_combination_order_book_directory(void) {
  CombinationOrderBookDirectory sent;
  CombinationOrderBookDirectory got;
  uint8_t wire[260];
  uint8_t again[260];

  any_combination_order_book_directory(&sent);
  assert(encode_combination_order_book_directory(&sent, wire, 0) == 260);
  assert(decode_combination_order_book_directory(&got, wire, 0) == 260);
  equal_combination_order_book_directory(&got, &sent);

  for (size_t i = 0; i < 260; i++) { wire[i] = arbitrary(); }
  assert(decode_combination_order_book_directory(&got, wire, 0) == 260);
  assert(encode_combination_order_book_directory(&got, again, 0) == 260);
  for (size_t i = 0; i < 260; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Size Table Entry: 24 bytes ----------------------------------------- */

/* Contains information on a tick size for a price range. Together, all Tick Size messages with the same order book ID form a complete Tick Size Table. The number of decimals in prices are given by the Order Book Directory message for this order book */
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

/* The system event message type is used to signal a market or data feed handler event */
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

/* The Order book state message relays information on state changes */
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

/* ---- Stressed Market Message: 9 bytes ---------------------------------------- */

/* The Stressed Market Message is sent whenever the Stressed Market state has changed */
typedef struct {
  uint8_t nanoseconds[4];    /* bytes 0 to 3 */
  uint8_t order_book_id[4];  /* bytes 4 to 7 */
  uint8_t stressed_market;   /* byte 8 */
} StressedMarketMessage;

/* any Stressed Market Message at all: every byte one the checker chooses */
static void any_stressed_market_message(StressedMarketMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->stressed_market = arbitrary();
}

/* Stressed Market Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_stressed_market_message(const StressedMarketMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->stressed_market;

  return at;
}

/* Stressed Market Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_stressed_market_message(StressedMarketMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->stressed_market = wire[at++];

  return at;
}

/* what was read of Stressed Market Message is what was written, byte for byte */
static void equal_stressed_market_message(const StressedMarketMessage *read, const StressedMarketMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->stressed_market == written->stressed_market);
}

/* Stressed Market Message: written and read back, then read and written back */
static void check_stressed_market_message(void) {
  StressedMarketMessage sent;
  StressedMarketMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_stressed_market_message(&sent);
  assert(encode_stressed_market_message(&sent, wire, 0) == 9);
  assert(decode_stressed_market_message(&got, wire, 0) == 9);
  equal_stressed_market_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_stressed_market_message(&got, wire, 0) == 9);
  assert(encode_stressed_market_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Exceptional Market Message: 9 bytes ------------------------------------- */

/* The Exceptional Market Message is sent whenever the Exceptional Market state has changed */
typedef struct {
  uint8_t nanoseconds[4];      /* bytes 0 to 3 */
  uint8_t order_book_id[4];    /* bytes 4 to 7 */
  uint8_t exceptional_market;  /* byte 8 */
} ExceptionalMarketMessage;

/* any Exceptional Market Message at all: every byte one the checker chooses */
static void any_exceptional_market_message(ExceptionalMarketMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->exceptional_market = arbitrary();
}

/* Exceptional Market Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_exceptional_market_message(const ExceptionalMarketMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->exceptional_market;

  return at;
}

/* Exceptional Market Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_exceptional_market_message(ExceptionalMarketMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->exceptional_market = wire[at++];

  return at;
}

/* what was read of Exceptional Market Message is what was written, byte for byte */
static void equal_exceptional_market_message(const ExceptionalMarketMessage *read, const ExceptionalMarketMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->exceptional_market == written->exceptional_market);
}

/* Exceptional Market Message: written and read back, then read and written back */
static void check_exceptional_market_message(void) {
  ExceptionalMarketMessage sent;
  ExceptionalMarketMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_exceptional_market_message(&sent);
  assert(encode_exceptional_market_message(&sent, wire, 0) == 9);
  assert(decode_exceptional_market_message(&got, wire, 0) == 9);
  equal_exceptional_market_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_exceptional_market_message(&got, wire, 0) == 9);
  assert(encode_exceptional_market_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 51 bytes ---------------------------------------- */

/* Sent whenever an order on the book is executed in whole or in part. Multiple Order Executed Messages on the same order are cumulative */
typedef struct {
  uint8_t nanoseconds[4];                  /* bytes 0 to 3 */
  uint8_t order_id[8];                     /* bytes 4 to 11 */
  uint8_t order_book_id[4];                /* bytes 12 to 15 */
  uint8_t side;                            /* byte 16 */
  uint8_t executed_quantity[8];            /* bytes 17 to 24 */
  uint8_t match_id[12];                    /* bytes 25 to 36 */
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
  for (size_t i = 0; i < 12; i++) { record->match_id[i] = arbitrary(); }
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
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->match_id[i]; }
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
  for (size_t i = 0; i < 12; i++) { record->match_id[i] = wire[at++]; }
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
  for (size_t i = 0; i < 12; i++) { assert(read->match_id[i] == written->match_id[i]); }
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

/* Sent in the relatively rare event that an order on the book is executed in whole or in part with a price different than the initial display price. Combination orders on the book that execute are always represented by this message, with the Printable flag set to N */
typedef struct {
  uint8_t nanoseconds[4];                  /* bytes 0 to 3 */
  uint8_t order_id[8];                     /* bytes 4 to 11 */
  uint8_t order_book_id[4];                /* bytes 12 to 15 */
  uint8_t side;                            /* byte 16 */
  uint8_t executed_quantity[8];            /* bytes 17 to 24 */
  uint8_t match_id[12];                    /* bytes 25 to 36 */
  uint8_t participant_id_owner[7];         /* bytes 37 to 43 */
  uint8_t participant_id_counterparty[7];  /* bytes 44 to 50 */
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
  for (size_t i = 0; i < 12; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->participant_id_owner[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->participant_id_counterparty[i] = arbitrary(); }
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
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->participant_id_owner[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->participant_id_counterparty[i]; }
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
  for (size_t i = 0; i < 12; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->participant_id_owner[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->participant_id_counterparty[i] = wire[at++]; }
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
  for (size_t i = 0; i < 12; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->participant_id_owner[i] == written->participant_id_owner[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->participant_id_counterparty[i] == written->participant_id_counterparty[i]); }
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

/* Sent whenever an order on the book is being deleted. Order Deletes are also sent when an order with an undisclosed quantity is fully filled, when orders are suspended due to connection loss, and for all existing orders prior to an auction where market by order dissemination is disabled */
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

/* Provides execution details for normal match events involving non-displayable order types, and is also used to publish individual cross trades */
typedef struct {
  uint8_t nanoseconds[4];                  /* bytes 0 to 3 */
  uint8_t match_id[12];                    /* bytes 4 to 15 */
  uint8_t side;                            /* byte 16 */
  uint8_t quantity[8];                     /* bytes 17 to 24 */
  uint8_t order_book_id[4];                /* bytes 25 to 28 */
  uint8_t trade_price[4];                  /* bytes 29 to 32 */
  uint8_t participant_id_owner[7];         /* bytes 33 to 39 */
  uint8_t participant_id_counterparty[7];  /* bytes 40 to 46 */
  uint8_t printable;                       /* byte 47 */
  uint8_t occurred_at_cross;               /* byte 48 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->match_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->participant_id_owner[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->participant_id_counterparty[i] = arbitrary(); }
  record->printable = arbitrary();
  record->occurred_at_cross = arbitrary();
}

/* Trade Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->match_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->participant_id_owner[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->participant_id_counterparty[i]; }
  wire[at++] = record->printable;
  wire[at++] = record->occurred_at_cross;

  return at;
}

/* Trade Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->match_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->participant_id_owner[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->participant_id_counterparty[i] = wire[at++]; }
  record->printable = wire[at++];
  record->occurred_at_cross = wire[at++];

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->match_id[i] == written->match_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->participant_id_owner[i] == written->participant_id_owner[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->participant_id_counterparty[i] == written->participant_id_counterparty[i]); }
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

/* Used when auctions occur. The message provides the changes in equilibrium price. If any Price field has bit 31 set (the highest bit, MIN_INT) while all other bits are zero (decimal -2147483648), this means that no price is available */
typedef struct {
  uint8_t nanoseconds[4];                                  /* bytes 0 to 3 */
  uint8_t order_book_id[4];                                /* bytes 4 to 7 */
  uint8_t available_bid_quantity_at_equilibrium_price[8];  /* bytes 8 to 15 */
  uint8_t available_ask_quantity_at_equilibrium_price[8];  /* bytes 16 to 23 */
  uint8_t equilibrium_price[4];                            /* bytes 24 to 27 */
  uint8_t reserved_4_a[4];                                 /* bytes 28 to 31 */
  uint8_t reserved_4_b[4];                                 /* bytes 32 to 35 */
  uint8_t reserved_8_a[8];                                 /* bytes 36 to 43 */
  uint8_t reserved_8_b[8];                                 /* bytes 44 to 51 */
} EquilibriumPriceUpdate;

/* any Equilibrium Price Update at all: every byte one the checker chooses */
static void any_equilibrium_price_update(EquilibriumPriceUpdate *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->available_bid_quantity_at_equilibrium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->available_ask_quantity_at_equilibrium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->equilibrium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_a[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_b[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8_a[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8_b[i] = arbitrary(); }
}

/* Equilibrium Price Update to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_equilibrium_price_update(const EquilibriumPriceUpdate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->available_bid_quantity_at_equilibrium_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->available_ask_quantity_at_equilibrium_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->equilibrium_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4_a[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4_b[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8_a[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8_b[i]; }

  return at;
}

/* Equilibrium Price Update off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_equilibrium_price_update(EquilibriumPriceUpdate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->available_bid_quantity_at_equilibrium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->available_ask_quantity_at_equilibrium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->equilibrium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_a[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_b[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8_a[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8_b[i] = wire[at++]; }

  return at;
}

/* what was read of Equilibrium Price Update is what was written, byte for byte */
static void equal_equilibrium_price_update(const EquilibriumPriceUpdate *read, const EquilibriumPriceUpdate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->available_bid_quantity_at_equilibrium_price[i] == written->available_bid_quantity_at_equilibrium_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->available_ask_quantity_at_equilibrium_price[i] == written->available_ask_quantity_at_equilibrium_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->equilibrium_price[i] == written->equilibrium_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4_a[i] == written->reserved_4_a[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4_b[i] == written->reserved_4_b[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8_a[i] == written->reserved_8_a[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8_b[i] == written->reserved_8_b[i]); }
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

/* ---- Quote Request Message: 30 bytes ----------------------------------------- */

/* Used to publish Quote Requests from clients */
typedef struct {
  uint8_t nanoseconds[4];    /* bytes 0 to 3 */
  uint8_t order_book_id[4];  /* bytes 4 to 7 */
  uint8_t reserved_7[7];     /* bytes 8 to 14 */
  uint8_t reserved_5[5];     /* bytes 15 to 19 */
  uint8_t reserved_1;        /* byte 20 */
  uint8_t side;              /* byte 21 */
  uint8_t quantity[8];       /* bytes 22 to 29 */
} QuoteRequestMessage;

/* any Quote Request Message at all: every byte one the checker chooses */
static void any_quote_request_message(QuoteRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->reserved_7[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
}

/* Quote Request Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_quote_request_message(const QuoteRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->reserved_7[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->reserved_5[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Quote Request Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_quote_request_message(QuoteRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->reserved_7[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Request Message is what was written, byte for byte */
static void equal_quote_request_message(const QuoteRequestMessage *read, const QuoteRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->reserved_7[i] == written->reserved_7[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->reserved_5[i] == written->reserved_5[i]); }
  assert(read->reserved_1 == written->reserved_1);
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_seconds_message();
  check_order_book_directory();
  check_combination_order_book_directory();
  check_tick_size_table_entry();
  check_system_event_message();
  check_order_book_state_message();
  check_stressed_market_message();
  check_exceptional_market_message();
  check_order_executed_message();
  check_order_executed_with_price_message();
  check_order_delete_message();
  check_trade_message();
  check_equilibrium_price_update();
  check_quote_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
