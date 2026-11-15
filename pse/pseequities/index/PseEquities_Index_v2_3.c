// pse/pseequities/index/PseEquities_Index_v2_3.c
/*
 * Philippine Stock Exchange Pse Equities Itch Index
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

/* Time Stamp - Seconds Message. */
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

/* System Event Message. */
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

/* ---- Orderbook Directory Message: 89 bytes ----------------------------------- */

/* Orderbook Directory Message. */
typedef struct {
  uint8_t timestamp[4];                    /* bytes 0 to 3 */
  uint8_t orderbook[4];                    /* bytes 4 to 7 */
  uint8_t price_type;                      /* byte 8 */
  uint8_t isin[12];                        /* bytes 9 to 20 */
  uint8_t sec_code[12];                    /* bytes 21 to 32 */
  uint8_t currency[3];                     /* bytes 33 to 35 */
  uint8_t group[8];                        /* bytes 36 to 43 */
  uint8_t lot_size[8];                     /* bytes 44 to 51 */
  uint8_t quantity_tick_size_table_id[4];  /* bytes 52 to 55 */
  uint8_t price_tick_size_table_id[4];     /* bytes 56 to 59 */
  uint8_t price_decimals[4];               /* bytes 60 to 63 */
  uint8_t delisting_date[4];               /* bytes 64 to 67 */
  uint8_t delisting_time[4];               /* bytes 68 to 71 */
  uint8_t instrument_type;                 /* byte 72 */
  uint8_t shares[8];                       /* bytes 73 to 80 */
  uint8_t product_code[8];                 /* bytes 81 to 88 */
} OrderbookDirectoryMessage;

/* any Orderbook Directory Message at all: every byte one the checker chooses */
static void any_orderbook_directory_message(OrderbookDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = arbitrary(); }
  record->price_type = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->isin[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->sec_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_size_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size_table_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_decimals[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->delisting_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->delisting_time[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->product_code[i] = arbitrary(); }
}

/* Orderbook Directory Message to the wire: 89 bytes from at, returning where the next byte goes */
static size_t encode_orderbook_directory_message(const OrderbookDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook[i]; }
  wire[at++] = record->price_type;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->sec_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lot_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_tick_size_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_tick_size_table_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_decimals[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delisting_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delisting_time[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->product_code[i]; }

  return at;
}

/* Orderbook Directory Message off the wire: 89 bytes from at, returning where the next byte lies */
static size_t decode_orderbook_directory_message(OrderbookDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook[i] = wire[at++]; }
  record->price_type = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->isin[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->sec_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_size_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_tick_size_table_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_decimals[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->delisting_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->delisting_time[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->product_code[i] = wire[at++]; }

  return at;
}

/* what was read of Orderbook Directory Message is what was written, byte for byte */
static void equal_orderbook_directory_message(const OrderbookDirectoryMessage *read, const OrderbookDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook[i] == written->orderbook[i]); }
  assert(read->price_type == written->price_type);
  for (size_t i = 0; i < 12; i++) { assert(read->isin[i] == written->isin[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->sec_code[i] == written->sec_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lot_size[i] == written->lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_tick_size_table_id[i] == written->quantity_tick_size_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_tick_size_table_id[i] == written->price_tick_size_table_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_decimals[i] == written->price_decimals[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->delisting_date[i] == written->delisting_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->delisting_time[i] == written->delisting_time[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 8; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->product_code[i] == written->product_code[i]); }
}

/* Orderbook Directory Message: written and read back, then read and written back */
static void check_orderbook_directory_message(void) {
  OrderbookDirectoryMessage sent;
  OrderbookDirectoryMessage got;
  uint8_t wire[89];
  uint8_t again[89];

  any_orderbook_directory_message(&sent);
  assert(encode_orderbook_directory_message(&sent, wire, 0) == 89);
  assert(decode_orderbook_directory_message(&got, wire, 0) == 89);
  equal_orderbook_directory_message(&got, &sent);

  for (size_t i = 0; i < 89; i++) { wire[i] = arbitrary(); }
  assert(decode_orderbook_directory_message(&got, wire, 0) == 89);
  assert(encode_orderbook_directory_message(&got, again, 0) == 89);
  for (size_t i = 0; i < 89; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Member Directory Message: 20 bytes -------------------------------- */

/* Index Member Directory Message. */
typedef struct {
  uint8_t timestamp[4];            /* bytes 0 to 3 */
  uint8_t index_orderbook[4];      /* bytes 4 to 7 */
  uint8_t member_orderbook[4];     /* bytes 8 to 11 */
  uint8_t index_member_weight[8];  /* bytes 12 to 19 */
} IndexMemberDirectoryMessage;

/* any Index Member Directory Message at all: every byte one the checker chooses */
static void any_index_member_directory_message(IndexMemberDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->index_orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->member_orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_member_weight[i] = arbitrary(); }
}

/* Index Member Directory Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_index_member_directory_message(const IndexMemberDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_orderbook[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member_orderbook[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_member_weight[i]; }

  return at;
}

/* Index Member Directory Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_index_member_directory_message(IndexMemberDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->index_orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->member_orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_member_weight[i] = wire[at++]; }

  return at;
}

/* what was read of Index Member Directory Message is what was written, byte for byte */
static void equal_index_member_directory_message(const IndexMemberDirectoryMessage *read, const IndexMemberDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->index_orderbook[i] == written->index_orderbook[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->member_orderbook[i] == written->member_orderbook[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_member_weight[i] == written->index_member_weight[i]); }
}

/* Index Member Directory Message: written and read back, then read and written back */
static void check_index_member_directory_message(void) {
  IndexMemberDirectoryMessage sent;
  IndexMemberDirectoryMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_index_member_directory_message(&sent);
  assert(encode_index_member_directory_message(&sent, wire, 0) == 20);
  assert(decode_index_member_directory_message(&got, wire, 0) == 20);
  equal_index_member_directory_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_index_member_directory_message(&got, wire, 0) == 20);
  assert(encode_index_member_directory_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Value Message: 16 bytes ------------------------------------------- */

/* Index Value Message. */
typedef struct {
  uint8_t timestamp[4];        /* bytes 0 to 3 */
  uint8_t index_orderbook[4];  /* bytes 4 to 7 */
  uint8_t value[8];            /* bytes 8 to 15 */
} IndexValueMessage;

/* any Index Value Message at all: every byte one the checker chooses */
static void any_index_value_message(IndexValueMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->index_orderbook[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->value[i] = arbitrary(); }
}

/* Index Value Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_index_value_message(const IndexValueMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_orderbook[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->value[i]; }

  return at;
}

/* Index Value Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_index_value_message(IndexValueMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->index_orderbook[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->value[i] = wire[at++]; }

  return at;
}

/* what was read of Index Value Message is what was written, byte for byte */
static void equal_index_value_message(const IndexValueMessage *read, const IndexValueMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->index_orderbook[i] == written->index_orderbook[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->value[i] == written->value[i]); }
}

/* Index Value Message: written and read back, then read and written back */
static void check_index_value_message(void) {
  IndexValueMessage sent;
  IndexValueMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_index_value_message(&sent);
  assert(encode_index_value_message(&sent, wire, 0) == 16);
  assert(decode_index_value_message(&got, wire, 0) == 16);
  equal_index_value_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_index_value_message(&got, wire, 0) == 16);
  assert(encode_index_value_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_time_stamp_seconds_message();
  check_system_event_message();
  check_orderbook_directory_message();
  check_index_member_directory_message();
  check_index_value_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
