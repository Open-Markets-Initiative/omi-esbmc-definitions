// six/sixswissexchange/totalview/SixSwissExchange_TotalView_v1_24_0.c
/*
 * SIX Swiss Exchange SIX Swiss Exchange ITCH Market Data Interface Total View
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

/* Timestamp of seconds since midnight, used in combination with the nanoseconds timestamp of each message */
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

/* Sent as a result of trade events at the system, group and Orderbook level */
typedef struct {
  uint8_t timestamp[4];  /* bytes 0 to 3 */
  uint8_t group[8];      /* bytes 4 to 11 */
  uint8_t event_code;    /* byte 12 */
  uint8_t orderbook[4];  /* bytes 13 to 16 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->group[i] = arbitrary(); }
  record->event_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
}

/* System Event Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->group[i]; }
  wire[at++] = record->event_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }

  return at;
}

/* System Event Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->group[i] = wire[at++]; }
  record->event_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
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

/* ---- Quantity Tick Size Message: 16 bytes ------------------------------------ */

/* Shows the Quantity Tick (Category) of a Security */
typedef struct {
  uint8_t timestamp[4];               /* bytes 0 to 3 */
  uint8_t quantity_tick_table_id[4];  /* bytes 4 to 7 */
  uint8_t quantity_tick_size[4];      /* bytes 8 to 11 */
  uint8_t quantity_start[4];          /* bytes 12 to 15 */
} QuantityTickSizeMessage;

/* any Quantity Tick Size Message at all: every byte one the checker chooses */
static void any_quantity_tick_size_message(QuantityTickSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_start[i] = arbitrary(); }
}

/* Quantity Tick Size Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_quantity_tick_size_message(const QuantityTickSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_tick_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_tick_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_start[i]; }

  return at;
}

/* Quantity Tick Size Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_quantity_tick_size_message(QuantityTickSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_start[i] = wire[at++]; }

  return at;
}

/* what was read of Quantity Tick Size Message is what was written, byte for byte */
static void equal_quantity_tick_size_message(const QuantityTickSizeMessage *read, const QuantityTickSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_tick_table_id[i] == written->quantity_tick_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_tick_size[i] == written->quantity_tick_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_start[i] == written->quantity_start[i]); }
}

/* Quantity Tick Size Message: written and read back, then read and written back */
static void check_quantity_tick_size_message(void) {
  QuantityTickSizeMessage sent;
  QuantityTickSizeMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_quantity_tick_size_message(&sent);
  assert(encode_quantity_tick_size_message(&sent, wire, 0) == 16);
  assert(decode_quantity_tick_size_message(&got, wire, 0) == 16);
  equal_quantity_tick_size_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_quantity_tick_size_message(&got, wire, 0) == 16);
  assert(encode_quantity_tick_size_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Tick Size Message: 16 bytes --------------------------------------- */

/* Shows the Price Tick (Category) of a Security */
typedef struct {
  uint8_t timestamp[4];            /* bytes 0 to 3 */
  uint8_t price_tick_table_id[4];  /* bytes 4 to 7 */
  uint8_t price_tick_size[4];      /* bytes 8 to 11 */
  uint8_t price_start[4];          /* bytes 12 to 15 */
} PriceTickSizeMessage;

/* any Price Tick Size Message at all: every byte one the checker chooses */
static void any_price_tick_size_message(PriceTickSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_tick_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_start[i] = arbitrary(); }
}

/* Price Tick Size Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_price_tick_size_message(const PriceTickSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_tick_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_tick_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_start[i]; }

  return at;
}

/* Price Tick Size Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_price_tick_size_message(PriceTickSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_tick_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_start[i] = wire[at++]; }

  return at;
}

/* what was read of Price Tick Size Message is what was written, byte for byte */
static void equal_price_tick_size_message(const PriceTickSizeMessage *read, const PriceTickSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_tick_table_id[i] == written->price_tick_table_id[i]); }
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

/* ---- Orderbook Directory Message: 68 bytes ----------------------------------- */

/* Provides the basic reference data for the active Orderbooks for a specific OBM partition */
typedef struct {
  uint8_t timestamp[4];               /* bytes 0 to 3 */
  uint8_t orderbook[4];               /* bytes 4 to 7 */
  uint8_t price_type;                 /* byte 8 */
  uint8_t isin[12];                   /* bytes 9 to 20 */
  uint8_t currency[3];                /* bytes 21 to 23 */
  uint8_t group[8];                   /* bytes 24 to 31 */
  uint8_t minimum_quantity[4];        /* bytes 32 to 35 */
  uint8_t quantity_tick_table_id[4];  /* bytes 36 to 39 */
  uint8_t price_tick_table_id[4];     /* bytes 40 to 43 */
  uint8_t price_decimals[4];          /* bytes 44 to 47 */
  uint8_t delisting_date[4];          /* bytes 48 to 51 */
  uint8_t delisting_time[4];          /* bytes 52 to 55 */
  uint8_t qod_price_decimals[4];      /* bytes 56 to 59 */
  uint8_t security_exchange[4];       /* bytes 60 to 63 */
  uint8_t reference_exchange[4];      /* bytes 64 to 67 */
} OrderbookDirectoryMessage;

/* any Orderbook Directory Message at all: every byte one the checker chooses */
static void any_orderbook_directory_message(OrderbookDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  record->price_type = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_tick_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_decimals[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->delisting_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->delisting_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->qod_price_decimals[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_exchange[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_exchange[i] = arbitrary(); }
}

/* Orderbook Directory Message to the wire: 68 bytes from at, returning where the next byte goes */
static size_t encode_orderbook_directory_message(const OrderbookDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  wire[at++] = record->price_type;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_tick_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_tick_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_decimals[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delisting_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delisting_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->qod_price_decimals[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_exchange[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_exchange[i]; }

  return at;
}

/* Orderbook Directory Message off the wire: 68 bytes from at, returning where the next byte lies */
static size_t decode_orderbook_directory_message(OrderbookDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  record->price_type = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_tick_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_decimals[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->delisting_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->delisting_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->qod_price_decimals[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_exchange[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_exchange[i] = wire[at++]; }

  return at;
}

/* what was read of Orderbook Directory Message is what was written, byte for byte */
static void equal_orderbook_directory_message(const OrderbookDirectoryMessage *read, const OrderbookDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  assert(read->price_type == written->price_type);
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_tick_table_id[i] == written->quantity_tick_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_tick_table_id[i] == written->price_tick_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_decimals[i] == written->price_decimals[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->delisting_date[i] == written->delisting_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->delisting_time[i] == written->delisting_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->qod_price_decimals[i] == written->qod_price_decimals[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_exchange[i] == written->security_exchange[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_exchange[i] == written->reference_exchange[i]); }
}

/* Orderbook Directory Message: written and read back, then read and written back */
static void check_orderbook_directory_message(void) {
  OrderbookDirectoryMessage sent;
  OrderbookDirectoryMessage got;
  uint8_t wire[68];
  uint8_t again[68];

  any_orderbook_directory_message(&sent);
  assert(encode_orderbook_directory_message(&sent, wire, 0) == 68);
  assert(decode_orderbook_directory_message(&got, wire, 0) == 68);
  equal_orderbook_directory_message(&got, &sent);

  for (size_t i = 0; i < 68; i++) { wire[i] = arbitrary(); }
  assert(decode_orderbook_directory_message(&got, wire, 0) == 68);
  assert(encode_orderbook_directory_message(&got, again, 0) == 68);
  for (size_t i = 0; i < 68; i++) { assert(again[i] == wire[i]); }
}

/* ---- Orderbook Trading Action Message: 10 bytes ------------------------------ */

/* Sent as a result of an Orderbook state or condition change */
typedef struct {
  uint8_t timestamp[4];    /* bytes 0 to 3 */
  uint8_t orderbook[4];    /* bytes 4 to 7 */
  uint8_t trading_state;   /* byte 8 */
  uint8_t book_condition;  /* byte 9 */
} OrderbookTradingActionMessage;

/* any Orderbook Trading Action Message at all: every byte one the checker chooses */
static void any_orderbook_trading_action_message(OrderbookTradingActionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  record->trading_state = arbitrary();
  record->book_condition = arbitrary();
}

/* Orderbook Trading Action Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_orderbook_trading_action_message(const OrderbookTradingActionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  wire[at++] = record->trading_state;
  wire[at++] = record->book_condition;

  return at;
}

/* Orderbook Trading Action Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_orderbook_trading_action_message(OrderbookTradingActionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  record->trading_state = wire[at++];
  record->book_condition = wire[at++];

  return at;
}

/* what was read of Orderbook Trading Action Message is what was written, byte for byte */
static void equal_orderbook_trading_action_message(const OrderbookTradingActionMessage *read, const OrderbookTradingActionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  assert(read->trading_state == written->trading_state);
  assert(read->book_condition == written->book_condition);
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

/* ---- Add Order Message: 25 bytes --------------------------------------------- */

/* A new order has been accepted and added to the book; an Order Number and Quantity of zero carries the reference price */
typedef struct {
  uint8_t timestamp[4];       /* bytes 0 to 3 */
  uint8_t order_number[8];    /* bytes 4 to 11 */
  uint8_t order_verb;         /* byte 12 */
  uint8_t order_quantity[4];  /* bytes 13 to 16 */
  uint8_t orderbook[4];       /* bytes 17 to 20 */
  uint8_t order_price[4];     /* bytes 21 to 24 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  record->order_verb = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_price[i] = arbitrary(); }
}

/* Add Order Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  wire[at++] = record->order_verb;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_price[i]; }

  return at;
}

/* Add Order Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  record->order_verb = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_price[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  assert(read->order_verb == written->order_verb);
  for (size_t i = 0; i < 4; i++) { assert(read->order_quantity[i] == written->order_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_price[i] == written->order_price[i]); }
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 25);
  assert(decode_add_order_message(&got, wire, 0) == 25);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 25);
  assert(encode_add_order_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 24 bytes ---------------------------------------- */

/* An order on the book has been executed in whole or in part */
typedef struct {
  uint8_t timestamp[4];          /* bytes 0 to 3 */
  uint8_t order_number[8];       /* bytes 4 to 11 */
  uint8_t executed_quantity[4];  /* bytes 12 to 15 */
  uint8_t match_number[8];       /* bytes 16 to 23 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Order Executed Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 24);
  assert(decode_order_executed_message(&got, wire, 0) == 24);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 24);
  assert(encode_order_executed_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed With Price Message: 29 bytes ----------------------------- */

/* An order on the book has been executed at a price different from its initial display price */
typedef struct {
  uint8_t timestamp[4];          /* bytes 0 to 3 */
  uint8_t order_number[8];       /* bytes 4 to 11 */
  uint8_t executed_quantity[4];  /* bytes 12 to 15 */
  uint8_t match_number[8];       /* bytes 16 to 23 */
  uint8_t printable;             /* byte 24 */
  uint8_t execution_price[4];    /* bytes 25 to 28 */
} OrderExecutedWithPriceMessage;

/* any Order Executed With Price Message at all: every byte one the checker chooses */
static void any_order_executed_with_price_message(OrderExecutedWithPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
  record->printable = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = arbitrary(); }
}

/* Order Executed With Price Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_with_price_message(const OrderExecutedWithPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->printable;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_price[i]; }

  return at;
}

/* Order Executed With Price Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_with_price_message(OrderExecutedWithPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }
  record->printable = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed With Price Message is what was written, byte for byte */
static void equal_order_executed_with_price_message(const OrderExecutedWithPriceMessage *read, const OrderExecutedWithPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->printable == written->printable);
  for (size_t i = 0; i < 4; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
}

/* Order Executed With Price Message: written and read back, then read and written back */
static void check_order_executed_with_price_message(void) {
  OrderExecutedWithPriceMessage sent;
  OrderExecutedWithPriceMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_order_executed_with_price_message(&sent);
  assert(encode_order_executed_with_price_message(&sent, wire, 0) == 29);
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 29);
  equal_order_executed_with_price_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_with_price_message(&got, wire, 0) == 29);
  assert(encode_order_executed_with_price_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Summary Message: 40 bytes ------------------------------------- */

/* Sent prior to the individual order execution and trade messages for an incoming order that executes in the CLOB or QDM order book */
typedef struct {
  uint8_t timestamp[4];                   /* bytes 0 to 3 */
  uint8_t orderbook[4];                   /* bytes 4 to 7 */
  uint8_t aggressor_side;                 /* byte 8 */
  uint8_t total_mpob_quantity[4];         /* bytes 9 to 12 */
  uint8_t total_ebbo_book_quantity[4];    /* bytes 13 to 16 */
  uint8_t total_clobqdm_quantity[4];      /* bytes 17 to 20 */
  uint8_t resting_hidden_quantity[4];     /* bytes 21 to 24 */
  uint8_t resting_cancelled_quantity[4];  /* bytes 25 to 28 */
  uint8_t far_side;                       /* byte 29 */
  uint8_t far_price[4];                   /* bytes 30 to 33 */
  uint8_t far_quantity_remaining[4];      /* bytes 34 to 37 */
  uint8_t number_of_executions[2];        /* bytes 38 to 39 */
} ExecutionSummaryMessage;

/* any Execution Summary Message at all: every byte one the checker chooses */
static void any_execution_summary_message(ExecutionSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  record->aggressor_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->total_mpob_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_ebbo_book_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_clobqdm_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->resting_hidden_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->resting_cancelled_quantity[i] = arbitrary(); }
  record->far_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->far_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->far_quantity_remaining[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_executions[i] = arbitrary(); }
}

/* Execution Summary Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_execution_summary_message(const ExecutionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  wire[at++] = record->aggressor_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_mpob_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_ebbo_book_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_clobqdm_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->resting_hidden_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->resting_cancelled_quantity[i]; }
  wire[at++] = record->far_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->far_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->far_quantity_remaining[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_executions[i]; }

  return at;
}

/* Execution Summary Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_execution_summary_message(ExecutionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  record->aggressor_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->total_mpob_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_ebbo_book_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_clobqdm_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->resting_hidden_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->resting_cancelled_quantity[i] = wire[at++]; }
  record->far_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->far_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->far_quantity_remaining[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_executions[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Summary Message is what was written, byte for byte */
static void equal_execution_summary_message(const ExecutionSummaryMessage *read, const ExecutionSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  assert(read->aggressor_side == written->aggressor_side);
  for (size_t i = 0; i < 4; i++) { assert(read->total_mpob_quantity[i] == written->total_mpob_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_ebbo_book_quantity[i] == written->total_ebbo_book_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_clobqdm_quantity[i] == written->total_clobqdm_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->resting_hidden_quantity[i] == written->resting_hidden_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->resting_cancelled_quantity[i] == written->resting_cancelled_quantity[i]); }
  assert(read->far_side == written->far_side);
  for (size_t i = 0; i < 4; i++) { assert(read->far_price[i] == written->far_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->far_quantity_remaining[i] == written->far_quantity_remaining[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_executions[i] == written->number_of_executions[i]); }
}

/* Execution Summary Message: written and read back, then read and written back */
static void check_execution_summary_message(void) {
  ExecutionSummaryMessage sent;
  ExecutionSummaryMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_execution_summary_message(&sent);
  assert(encode_execution_summary_message(&sent, wire, 0) == 40);
  assert(decode_execution_summary_message(&got, wire, 0) == 40);
  equal_execution_summary_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_summary_message(&got, wire, 0) == 40);
  assert(encode_execution_summary_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 34 bytes ------------------------------------------------- */

/* Informs about a trade without pre-trade transparency */
typedef struct {
  uint8_t timestamp[4];          /* bytes 0 to 3 */
  uint8_t execution_time[8];     /* bytes 4 to 11 */
  uint8_t orderbook[4];          /* bytes 12 to 15 */
  uint8_t executed_quantity[4];  /* bytes 16 to 19 */
  uint8_t execution_price[4];    /* bytes 20 to 23 */
  uint8_t match_number[8];       /* bytes 24 to 31 */
  uint8_t book_type;             /* byte 32 */
  uint8_t trading_session_id;    /* byte 33 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
  record->book_type = arbitrary();
  record->trading_session_id = arbitrary();
}

/* Trade Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->book_type;
  wire[at++] = record->trading_session_id;

  return at;
}

/* Trade Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }
  record->book_type = wire[at++];
  record->trading_session_id = wire[at++];

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_time[i] == written->execution_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->book_type == written->book_type);
  assert(read->trading_session_id == written->trading_session_id);
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 34);
  assert(decode_trade_message(&got, wire, 0) == 34);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 34);
  assert(encode_trade_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Message: 13 bytes ------------------------------------------ */

/* Informs about a SIX Swiss Exchange mistrade decision */
typedef struct {
  uint8_t timestamp[4];     /* bytes 0 to 3 */
  uint8_t match_number[8];  /* bytes 4 to 11 */
  uint8_t reason;           /* byte 12 */
} BrokenTradeMessage;

/* any Broken Trade Message at all: every byte one the checker chooses */
static void any_broken_trade_message(BrokenTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
  record->reason = arbitrary();
}

/* Broken Trade Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_message(const BrokenTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->reason;

  return at;
}

/* Broken Trade Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_message(BrokenTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }
  record->reason = wire[at++];

  return at;
}

/* what was read of Broken Trade Message is what was written, byte for byte */
static void equal_broken_trade_message(const BrokenTradeMessage *read, const BrokenTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->reason == written->reason);
}

/* Broken Trade Message: written and read back, then read and written back */
static void check_broken_trade_message(void) {
  BrokenTradeMessage sent;
  BrokenTradeMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_broken_trade_message(&sent);
  assert(encode_broken_trade_message(&sent, wire, 0) == 13);
  assert(decode_broken_trade_message(&got, wire, 0) == 13);
  equal_broken_trade_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_message(&got, wire, 0) == 13);
  assert(encode_broken_trade_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Delete Message: 12 bytes ------------------------------------------ */

/* Sent whenever an order on the Orderbook is being cancelled */
typedef struct {
  uint8_t timestamp[4];     /* bytes 0 to 3 */
  uint8_t order_number[8];  /* bytes 4 to 11 */
} OrderDeleteMessage;

/* any Order Delete Message at all: every byte one the checker chooses */
static void any_order_delete_message(OrderDeleteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
}

/* Order Delete Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_order_delete_message(const OrderDeleteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }

  return at;
}

/* Order Delete Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_order_delete_message(OrderDeleteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Delete Message is what was written, byte for byte */
static void equal_order_delete_message(const OrderDeleteMessage *read, const OrderDeleteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
}

/* Order Delete Message: written and read back, then read and written back */
static void check_order_delete_message(void) {
  OrderDeleteMessage sent;
  OrderDeleteMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_order_delete_message(&sent);
  assert(encode_order_delete_message(&sent, wire, 0) == 12);
  assert(decode_order_delete_message(&got, wire, 0) == 12);
  equal_order_delete_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_order_delete_message(&got, wire, 0) == 12);
  assert(encode_order_delete_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replace Message: 28 bytes ----------------------------------------- */

/* Sent whenever an order on the Orderbook has been cancel-replaced */
typedef struct {
  uint8_t timestamp[4];              /* bytes 0 to 3 */
  uint8_t original_order_number[8];  /* bytes 4 to 11 */
  uint8_t new_order_number[8];       /* bytes 12 to 19 */
  uint8_t order_quantity[4];         /* bytes 20 to 23 */
  uint8_t order_price[4];            /* bytes 24 to 27 */
} OrderReplaceMessage;

/* any Order Replace Message at all: every byte one the checker chooses */
static void any_order_replace_message(OrderReplaceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_price[i] = arbitrary(); }
}

/* Order Replace Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_order_replace_message(const OrderReplaceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_price[i]; }

  return at;
}

/* Order Replace Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_order_replace_message(OrderReplaceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replace Message is what was written, byte for byte */
static void equal_order_replace_message(const OrderReplaceMessage *read, const OrderReplaceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_number[i] == written->original_order_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_order_number[i] == written->new_order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_quantity[i] == written->order_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_price[i] == written->order_price[i]); }
}

/* Order Replace Message: written and read back, then read and written back */
static void check_order_replace_message(void) {
  OrderReplaceMessage sent;
  OrderReplaceMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_order_replace_message(&sent);
  assert(encode_order_replace_message(&sent, wire, 0) == 28);
  assert(decode_order_replace_message(&got, wire, 0) == 28);
  equal_order_replace_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replace_message(&got, wire, 0) == 28);
  assert(encode_order_replace_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indicative Price Quantity Message: 29 bytes ----------------------------- */

/* Sent during non-automatic matching periods telling the users what would happen if the book was uncrossed now */
typedef struct {
  uint8_t timestamp[4];                     /* bytes 0 to 3 */
  uint8_t theoretical_opening_quantity[8];  /* bytes 4 to 11 */
  uint8_t orderbook[4];                     /* bytes 12 to 15 */
  uint8_t best_bid[4];                      /* bytes 16 to 19 */
  uint8_t best_offer[4];                    /* bytes 20 to 23 */
  uint8_t theoretical_opening_price[4];     /* bytes 24 to 27 */
  uint8_t cross_type;                       /* byte 28 */
} IndicativePriceQuantityMessage;

/* any Indicative Price Quantity Message at all: every byte one the checker chooses */
static void any_indicative_price_quantity_message(IndicativePriceQuantityMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->theoretical_opening_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_offer[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->theoretical_opening_price[i] = arbitrary(); }
  record->cross_type = arbitrary();
}

/* Indicative Price Quantity Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_indicative_price_quantity_message(const IndicativePriceQuantityMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->theoretical_opening_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_bid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_offer[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->theoretical_opening_price[i]; }
  wire[at++] = record->cross_type;

  return at;
}

/* Indicative Price Quantity Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_indicative_price_quantity_message(IndicativePriceQuantityMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->theoretical_opening_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_offer[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->theoretical_opening_price[i] = wire[at++]; }
  record->cross_type = wire[at++];

  return at;
}

/* what was read of Indicative Price Quantity Message is what was written, byte for byte */
static void equal_indicative_price_quantity_message(const IndicativePriceQuantityMessage *read, const IndicativePriceQuantityMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->theoretical_opening_quantity[i] == written->theoretical_opening_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_bid[i] == written->best_bid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_offer[i] == written->best_offer[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->theoretical_opening_price[i] == written->theoretical_opening_price[i]); }
  assert(read->cross_type == written->cross_type);
}

/* Indicative Price Quantity Message: written and read back, then read and written back */
static void check_indicative_price_quantity_message(void) {
  IndicativePriceQuantityMessage sent;
  IndicativePriceQuantityMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_indicative_price_quantity_message(&sent);
  assert(encode_indicative_price_quantity_message(&sent, wire, 0) == 29);
  assert(decode_indicative_price_quantity_message(&got, wire, 0) == 29);
  equal_indicative_price_quantity_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_indicative_price_quantity_message(&got, wire, 0) == 29);
  assert(encode_indicative_price_quantity_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_time_stamp_seconds_message();
  check_system_event_message();
  check_quantity_tick_size_message();
  check_price_tick_size_message();
  check_orderbook_directory_message();
  check_orderbook_trading_action_message();
  check_add_order_message();
  check_order_executed_message();
  check_order_executed_with_price_message();
  check_execution_summary_message();
  check_trade_message();
  check_broken_trade_message();
  check_order_delete_message();
  check_order_replace_message();
  check_indicative_price_quantity_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
