// biva/bivaequities/lastsale/BivaEquities_LastSale_v1_12.c
/*
 * Bolsa Institucional de Valores Last Sale
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

/* ---- Time Stamp Seconds Message: 4 bytes ------------------------------------- */

/* Itch timestamp, number of seconds since midnight of the system start */
typedef struct {
  uint8_t second[4];  /* bytes 0 to 3 */
} TimeStampSecondsMessage;

/* any Time Stamp Seconds Message at all: every byte one the checker chooses */
static void any_time_stamp_seconds_message(TimeStampSecondsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = arbitrary(); }
}

/* Time Stamp Seconds Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_time_stamp_seconds_message(const TimeStampSecondsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second[i]; }

  return at;
}

/* Time Stamp Seconds Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_time_stamp_seconds_message(TimeStampSecondsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = wire[at++]; }

  return at;
}

/* what was read of Time Stamp Seconds Message is what was written, byte for byte */
static void equal_time_stamp_seconds_message(const TimeStampSecondsMessage *read, const TimeStampSecondsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->second[i] == written->second[i]); }
}

/* Time Stamp Seconds Message: written and read back, then read and written back */
static void check_time_stamp_seconds_message(void) {
  TimeStampSecondsMessage sent;
  TimeStampSecondsMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_time_stamp_seconds_message(&sent);
  assert(encode_time_stamp_seconds_message(&sent, wire, 0) == 4);
  assert(decode_time_stamp_seconds_message(&got, wire, 0) == 4);
  equal_time_stamp_seconds_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_time_stamp_seconds_message(&got, wire, 0) == 4);
  assert(encode_time_stamp_seconds_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 17 bytes ------------------------------------------ */

/* System event message */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t group[8];        /* bytes 4 to 11 */
  uint8_t event_code;      /* byte 12 */
  uint8_t orderbook[4];    /* bytes 13 to 16 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->group[i] = arbitrary(); }
  record->event_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
}

/* System Event Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->group[i]; }
  wire[at++] = record->event_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }

  return at;
}

/* System Event Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->group[i] = wire[at++]; }
  record->event_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->group[i] == written->group[i]); }
  assert(read->event_code == written->event_code);
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 17);
  assert(decode_system_event_message(&got, wire, 0) == 17);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 17);
  assert(encode_system_event_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Tick Size Message: 16 bytes --------------------------------------- */

/* Orderbook price tick table */
typedef struct {
  uint8_t nanoseconds[4];         /* bytes 0 to 3 */
  uint8_t tick_size_table_id[4];  /* bytes 4 to 7 */
  uint8_t price_tick_size[4];     /* bytes 8 to 11 */
  uint8_t price_start[4];         /* bytes 12 to 15 */
} PriceTickSizeMessage;

/* any Price Tick Size Message at all: every byte one the checker chooses */
static void any_price_tick_size_message(PriceTickSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tick_size_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_start[i] = arbitrary(); }
}

/* Price Tick Size Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_price_tick_size_message(const PriceTickSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tick_size_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_tick_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_start[i]; }

  return at;
}

/* Price Tick Size Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_price_tick_size_message(PriceTickSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tick_size_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_start[i] = wire[at++]; }

  return at;
}

/* what was read of Price Tick Size Message is what was written, byte for byte */
static void equal_price_tick_size_message(const PriceTickSizeMessage *read, const PriceTickSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tick_size_table_id[i] == written->tick_size_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_tick_size[i] == written->price_tick_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_start[i] == written->price_start[i]); }
}

/* Price Tick Size Message: written and read back, then read and written back */
static void check_price_tick_size_message(void) {
  PriceTickSizeMessage sent;
  PriceTickSizeMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_price_tick_size_message(&sent);
  assert(encode_price_tick_size_message(&sent, wire, 0) == 16);
  assert(decode_price_tick_size_message(&got, wire, 0) == 16);
  equal_price_tick_size_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_price_tick_size_message(&got, wire, 0) == 16);
  assert(encode_price_tick_size_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quantity Tick Size Message: 24 bytes ------------------------------------ */

/* Orderbook quantity tick table */
typedef struct {
  uint8_t nanoseconds[4];         /* bytes 0 to 3 */
  uint8_t tick_size_table_id[4];  /* bytes 4 to 7 */
  uint8_t quantity_tick_size[8];  /* bytes 8 to 15 */
  uint8_t quantity_start[8];      /* bytes 16 to 23 */
} QuantityTickSizeMessage;

/* any Quantity Tick Size Message at all: every byte one the checker chooses */
static void any_quantity_tick_size_message(QuantityTickSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->tick_size_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_start[i] = arbitrary(); }
}

/* Quantity Tick Size Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_quantity_tick_size_message(const QuantityTickSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->tick_size_table_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_tick_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_start[i]; }

  return at;
}

/* Quantity Tick Size Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_quantity_tick_size_message(QuantityTickSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->tick_size_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_start[i] = wire[at++]; }

  return at;
}

/* what was read of Quantity Tick Size Message is what was written, byte for byte */
static void equal_quantity_tick_size_message(const QuantityTickSizeMessage *read, const QuantityTickSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->tick_size_table_id[i] == written->tick_size_table_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_tick_size[i] == written->quantity_tick_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_start[i] == written->quantity_start[i]); }
}

/* Quantity Tick Size Message: written and read back, then read and written back */
static void check_quantity_tick_size_message(void) {
  QuantityTickSizeMessage sent;
  QuantityTickSizeMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_quantity_tick_size_message(&sent);
  assert(encode_quantity_tick_size_message(&sent, wire, 0) == 24);
  assert(decode_quantity_tick_size_message(&got, wire, 0) == 24);
  equal_quantity_tick_size_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_quantity_tick_size_message(&got, wire, 0) == 24);
  assert(encode_quantity_tick_size_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Orderbook Directory Message: 99 bytes ----------------------------------- */

/* Orderbook directory */
typedef struct {
  uint8_t nanoseconds[4];                  /* bytes 0 to 3 */
  uint8_t orderbook[4];                    /* bytes 4 to 7 */
  uint8_t isin[12];                        /* bytes 8 to 19 */
  uint8_t sec_code[15];                    /* bytes 20 to 34 */
  uint8_t currency[3];                     /* bytes 35 to 37 */
  uint8_t group[8];                        /* bytes 38 to 45 */
  uint8_t minimum_quantity[8];             /* bytes 46 to 53 */
  uint8_t quantity_tick_size_table_id[4];  /* bytes 54 to 57 */
  uint8_t quantity_decimals[4];            /* bytes 58 to 61 */
  uint8_t price_tick_size_table_id[4];     /* bytes 62 to 65 */
  uint8_t price_decimals[4];               /* bytes 66 to 69 */
  uint8_t delisting_or_maturity_date[4];   /* bytes 70 to 73 */
  uint8_t delisting_time[4];               /* bytes 74 to 77 */
  uint8_t turnover_ratio;                  /* byte 78 */
  uint8_t quotation_basis[3];              /* bytes 79 to 81 */
  uint8_t instrument[12];                  /* bytes 82 to 93 */
  uint8_t listing_type;                    /* byte 94 */
  uint8_t listing_exchange[4];             /* bytes 95 to 98 */
} OrderbookDirectoryMessage;

/* any Orderbook Directory Message at all: every byte one the checker chooses */
static void any_orderbook_directory_message(OrderbookDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->sec_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_size_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_decimals[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_decimals[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->delisting_or_maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->delisting_time[i] = arbitrary(); }
  record->turnover_ratio = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->quotation_basis[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->instrument[i] = arbitrary(); }
  record->listing_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->listing_exchange[i] = arbitrary(); }
}

/* Orderbook Directory Message to the wire: 99 bytes from at, returning where the next byte goes */
static size_t encode_orderbook_directory_message(const OrderbookDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->sec_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_tick_size_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_decimals[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_tick_size_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_decimals[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delisting_or_maturity_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delisting_time[i]; }
  wire[at++] = record->turnover_ratio;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->quotation_basis[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->instrument[i]; }
  wire[at++] = record->listing_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->listing_exchange[i]; }

  return at;
}

/* Orderbook Directory Message off the wire: 99 bytes from at, returning where the next byte lies */
static size_t decode_orderbook_directory_message(OrderbookDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->sec_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_size_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_decimals[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_decimals[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->delisting_or_maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->delisting_time[i] = wire[at++]; }
  record->turnover_ratio = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->quotation_basis[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->instrument[i] = wire[at++]; }
  record->listing_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->listing_exchange[i] = wire[at++]; }

  return at;
}

/* what was read of Orderbook Directory Message is what was written, byte for byte */
static void equal_orderbook_directory_message(const OrderbookDirectoryMessage *read, const OrderbookDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->sec_code[i] == written->sec_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_tick_size_table_id[i] == written->quantity_tick_size_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_decimals[i] == written->quantity_decimals[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_tick_size_table_id[i] == written->price_tick_size_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_decimals[i] == written->price_decimals[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->delisting_or_maturity_date[i] == written->delisting_or_maturity_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->delisting_time[i] == written->delisting_time[i]); }
  assert(read->turnover_ratio == written->turnover_ratio);
  for (size_t i = 0; i < 3; i++) { assert(read->quotation_basis[i] == written->quotation_basis[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->instrument[i] == written->instrument[i]); }
  assert(read->listing_type == written->listing_type);
  for (size_t i = 0; i < 4; i++) { assert(read->listing_exchange[i] == written->listing_exchange[i]); }
}

/* Orderbook Directory Message: written and read back, then read and written back */
static void check_orderbook_directory_message(void) {
  OrderbookDirectoryMessage sent;
  OrderbookDirectoryMessage got;
  uint8_t wire[99];
  uint8_t again[99];

  any_orderbook_directory_message(&sent);
  assert(encode_orderbook_directory_message(&sent, wire, 0) == 99);
  assert(decode_orderbook_directory_message(&got, wire, 0) == 99);
  equal_orderbook_directory_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_orderbook_directory_message(&got, wire, 0) == 99);
  assert(encode_orderbook_directory_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- Participant Directory Message: 20 bytes --------------------------------- */

/* Participant directory */
typedef struct {
  uint8_t nanoseconds[4];        /* bytes 0 to 3 */
  uint8_t participant_id[4];     /* bytes 4 to 7 */
  uint8_t participant_code[12];  /* bytes 8 to 19 */
} ParticipantDirectoryMessage;

/* any Participant Directory Message at all: every byte one the checker chooses */
static void any_participant_directory_message(ParticipantDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->participant_code[i] = arbitrary(); }
}

/* Participant Directory Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_participant_directory_message(const ParticipantDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->participant_code[i]; }

  return at;
}

/* Participant Directory Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_participant_directory_message(ParticipantDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->participant_code[i] = wire[at++]; }

  return at;
}

/* what was read of Participant Directory Message is what was written, byte for byte */
static void equal_participant_directory_message(const ParticipantDirectoryMessage *read, const ParticipantDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->participant_id[i] == written->participant_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->participant_code[i] == written->participant_code[i]); }
}

/* Participant Directory Message: written and read back, then read and written back */
static void check_participant_directory_message(void) {
  ParticipantDirectoryMessage sent;
  ParticipantDirectoryMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_participant_directory_message(&sent);
  assert(encode_participant_directory_message(&sent, wire, 0) == 20);
  assert(decode_participant_directory_message(&got, wire, 0) == 20);
  equal_participant_directory_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_participant_directory_message(&got, wire, 0) == 20);
  assert(encode_participant_directory_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Orderbook Trading Action Message: 10 bytes ------------------------------ */

/* Trading action message */
typedef struct {
  uint8_t nanoseconds[4];         /* bytes 0 to 3 */
  uint8_t orderbook[4];           /* bytes 4 to 7 */
  uint8_t trading_state;          /* byte 8 */
  uint8_t trading_action_reason;  /* byte 9 */
} OrderbookTradingActionMessage;

/* any Orderbook Trading Action Message at all: every byte one the checker chooses */
static void any_orderbook_trading_action_message(OrderbookTradingActionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  record->trading_state = arbitrary();
  record->trading_action_reason = arbitrary();
}

/* Orderbook Trading Action Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_orderbook_trading_action_message(const OrderbookTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  wire[at++] = record->trading_state;
  wire[at++] = record->trading_action_reason;

  return at;
}

/* Orderbook Trading Action Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_orderbook_trading_action_message(OrderbookTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  record->trading_state = wire[at++];
  record->trading_action_reason = wire[at++];

  return at;
}

/* what was read of Orderbook Trading Action Message is what was written, byte for byte */
static void equal_orderbook_trading_action_message(const OrderbookTradingActionMessage *read, const OrderbookTradingActionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  assert(read->trading_state == written->trading_state);
  assert(read->trading_action_reason == written->trading_action_reason);
}

/* Orderbook Trading Action Message: written and read back, then read and written back */
static void check_orderbook_trading_action_message(void) {
  OrderbookTradingActionMessage sent;
  OrderbookTradingActionMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_orderbook_trading_action_message(&sent);
  assert(encode_orderbook_trading_action_message(&sent, wire, 0) == 10);
  assert(decode_orderbook_trading_action_message(&got, wire, 0) == 10);
  equal_orderbook_trading_action_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_orderbook_trading_action_message(&got, wire, 0) == 10);
  assert(encode_orderbook_trading_action_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 39 bytes ------------------------------------------------- */

/* Trade message */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t executed_quantity[8];    /* bytes 4 to 11 */
  uint8_t orderbook[4];            /* bytes 12 to 15 */
  uint8_t printable;               /* byte 16 */
  uint8_t execution_price[4];      /* bytes 17 to 20 */
  uint8_t match_number[8];         /* bytes 21 to 28 */
  uint8_t trade_indicator;         /* byte 29 */
  uint8_t stat_update;             /* byte 30 */
  uint8_t buy_participant_id[4];   /* bytes 31 to 34 */
  uint8_t sell_participant_id[4];  /* bytes 35 to 38 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
  record->trade_indicator = arbitrary();
  record->stat_update = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->buy_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_participant_id[i] = arbitrary(); }
}

/* Trade Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->trade_indicator;
  wire[at++] = record->stat_update;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_participant_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_participant_id[i]; }

  return at;
}

/* Trade Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }
  record->trade_indicator = wire[at++];
  record->stat_update = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->buy_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_participant_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  assert(read->printable == written->printable);
  for (size_t i = 0; i < 4; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->trade_indicator == written->trade_indicator);
  assert(read->stat_update == written->stat_update);
  for (size_t i = 0; i < 4; i++) { assert(read->buy_participant_id[i] == written->buy_participant_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_participant_id[i] == written->sell_participant_id[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 39);
  assert(decode_trade_message(&got, wire, 0) == 39);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 39);
  assert(encode_trade_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Orderbook Reference Price Message: 14 bytes ----------------------------- */

/* Orderbook reference price message */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t orderbook[4];            /* bytes 4 to 7 */
  uint8_t reference_price[4];      /* bytes 8 to 11 */
  uint8_t price_type;              /* byte 12 */
  uint8_t reference_price_reason;  /* byte 13 */
} OrderbookReferencePriceMessage;

/* any Orderbook Reference Price Message at all: every byte one the checker chooses */
static void any_orderbook_reference_price_message(OrderbookReferencePriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_price[i] = arbitrary(); }
  record->price_type = arbitrary();
  record->reference_price_reason = arbitrary();
}

/* Orderbook Reference Price Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_orderbook_reference_price_message(const OrderbookReferencePriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_price[i]; }
  wire[at++] = record->price_type;
  wire[at++] = record->reference_price_reason;

  return at;
}

/* Orderbook Reference Price Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_orderbook_reference_price_message(OrderbookReferencePriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_price[i] = wire[at++]; }
  record->price_type = wire[at++];
  record->reference_price_reason = wire[at++];

  return at;
}

/* what was read of Orderbook Reference Price Message is what was written, byte for byte */
static void equal_orderbook_reference_price_message(const OrderbookReferencePriceMessage *read, const OrderbookReferencePriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  assert(read->price_type == written->price_type);
  assert(read->reference_price_reason == written->reference_price_reason);
}

/* Orderbook Reference Price Message: written and read back, then read and written back */
static void check_orderbook_reference_price_message(void) {
  OrderbookReferencePriceMessage sent;
  OrderbookReferencePriceMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_orderbook_reference_price_message(&sent);
  assert(encode_orderbook_reference_price_message(&sent, wire, 0) == 14);
  assert(decode_orderbook_reference_price_message(&got, wire, 0) == 14);
  equal_orderbook_reference_price_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_orderbook_reference_price_message(&got, wire, 0) == 14);
  assert(encode_orderbook_reference_price_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_time_stamp_seconds_message();
  check_system_event_message();
  check_price_tick_size_message();
  check_quantity_tick_size_message();
  check_orderbook_directory_message();
  check_participant_directory_message();
  check_orderbook_trading_action_message();
  check_trade_message();
  check_orderbook_reference_price_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
