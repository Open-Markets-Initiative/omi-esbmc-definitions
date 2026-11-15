// nyse/nyseequities/depthfeed/NyseEquities_DepthFeed_v1_1.c
/*
 * New York Stock Exchange Depth Feed
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
 *   - a run filling what frames it
 *   - a field present only on a condition
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

/* ---- Send Time: 8 bytes ------------------------------------------------------ */

/* The time when this packet was published to the multicast channel */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} SendTime;

/* any Send Time at all: every byte one the checker chooses */
static void any_send_time(SendTime *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Send Time to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_send_time(const SendTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Send Time off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_send_time(SendTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Send Time is what was written, byte for byte */
static void equal_send_time(const SendTime *read, const SendTime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Send Time: written and read back, then read and written back */
static void check_send_time(void) {
  SendTime sent;
  SendTime got;
  uint8_t wire[8];
  uint8_t again[8];

  any_send_time(&sent);
  assert(encode_send_time(&sent, wire, 0) == 8);
  assert(decode_send_time(&got, wire, 0) == 8);
  equal_send_time(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_send_time(&got, wire, 0) == 8);
  assert(encode_send_time(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Packet Header: 16 bytes ------------------------------------------------- */

/* Pillar common client udp packet header */
typedef struct {
  uint8_t pkt_size[2];    /* bytes 0 to 1 */
  uint8_t delivery_flag;  /* byte 2 */
  uint8_t number_msgs;    /* byte 3 */
  uint8_t seq_num[4];     /* bytes 4 to 7 */
  SendTime send_time;     /* bytes 8 to 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->pkt_size[i] = arbitrary(); }
  record->delivery_flag = arbitrary();
  record->number_msgs = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  any_send_time(&record->send_time);
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->pkt_size[i]; }
  wire[at++] = record->delivery_flag;
  wire[at++] = record->number_msgs;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  at = encode_send_time(&record->send_time, wire, at);

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->pkt_size[i] = wire[at++]; }
  record->delivery_flag = wire[at++];
  record->number_msgs = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  at = decode_send_time(&record->send_time, wire, at);

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->pkt_size[i] == written->pkt_size[i]); }
  assert(read->delivery_flag == written->delivery_flag);
  assert(read->number_msgs == written->number_msgs);
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  equal_send_time(&read->send_time, &written->send_time);
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[16];
  uint8_t again[16];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 16);
  assert(decode_packet_header(&got, wire, 0) == 16);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 16);
  assert(encode_packet_header(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 4 bytes ------------------------------------------------- */

/* Pillar message header */
typedef struct {
  uint8_t message_size[2];  /* bytes 0 to 1 */
  uint8_t message_type[2];  /* bytes 2 to 3 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
}

/* Message Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }

  return at;
}

/* Message Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_size[i] == written->message_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 4);
  assert(decode_message_header(&got, wire, 0) == 4);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 4);
  assert(encode_message_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Number Reset Message: 10 bytes --------------------------------- */

/* This message is sent to reset the Message Sequence Number at start of day, or in response to failures. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_time_ns[4];  /* bytes 4 to 7 */
  uint8_t product_id;         /* byte 8 */
  uint8_t channel_id;         /* byte 9 */
} SequenceNumberResetMessage;

/* any Sequence Number Reset Message at all: every byte one the checker chooses */
static void any_sequence_number_reset_message(SequenceNumberResetMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  record->product_id = arbitrary();
  record->channel_id = arbitrary();
}

/* Sequence Number Reset Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_sequence_number_reset_message(const SequenceNumberResetMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  wire[at++] = record->product_id;
  wire[at++] = record->channel_id;

  return at;
}

/* Sequence Number Reset Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_sequence_number_reset_message(SequenceNumberResetMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  record->product_id = wire[at++];
  record->channel_id = wire[at++];

  return at;
}

/* what was read of Sequence Number Reset Message is what was written, byte for byte */
static void equal_sequence_number_reset_message(const SequenceNumberResetMessage *read, const SequenceNumberResetMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  assert(read->product_id == written->product_id);
  assert(read->channel_id == written->channel_id);
}

/* Sequence Number Reset Message: written and read back, then read and written back */
static void check_sequence_number_reset_message(void) {
  SequenceNumberResetMessage sent;
  SequenceNumberResetMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_sequence_number_reset_message(&sent);
  assert(encode_sequence_number_reset_message(&sent, wire, 0) == 10);
  assert(decode_sequence_number_reset_message(&got, wire, 0) == 10);
  equal_sequence_number_reset_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_number_reset_message(&got, wire, 0) == 10);
  assert(encode_sequence_number_reset_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Index Mapping Message: 40 bytes ---------------------------------- */

/* This message is published over the real-time data channels at system startup or in the context of a refresh sequence after a Matching Engine or Pillar Publisher failover. It provides referential data for a single specified symbol. */
typedef struct {
  uint8_t symbol_index[4];       /* bytes 0 to 3 */
  uint8_t symbol[11];            /* bytes 4 to 14 */
  uint8_t reserved_1;            /* byte 15 */
  uint8_t market_id[2];          /* bytes 16 to 17 */
  uint8_t system_id;             /* byte 18 */
  uint8_t exchange_code;         /* byte 19 */
  uint8_t price_scale_code;      /* byte 20 */
  uint8_t security_type;         /* byte 21 */
  uint8_t lot_size[2];           /* bytes 22 to 23 */
  uint8_t prev_close_price[4];   /* bytes 24 to 27 */
  uint8_t prev_close_volume[4];  /* bytes 28 to 31 */
  uint8_t price_resolution;      /* byte 32 */
  uint8_t round_lot;             /* byte 33 */
  uint8_t mpv[2];                /* bytes 34 to 35 */
  uint8_t unit_of_trade[2];      /* bytes 36 to 37 */
  uint8_t reserved_2[2];         /* bytes 38 to 39 */
} SymbolIndexMappingMessage;

/* any Symbol Index Mapping Message at all: every byte one the checker chooses */
static void any_symbol_index_mapping_message(SymbolIndexMappingMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = arbitrary(); }
  record->system_id = arbitrary();
  record->exchange_code = arbitrary();
  record->price_scale_code = arbitrary();
  record->security_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->prev_close_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->prev_close_volume[i] = arbitrary(); }
  record->price_resolution = arbitrary();
  record->round_lot = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->mpv[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->unit_of_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Symbol Index Mapping Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_symbol_index_mapping_message(const SymbolIndexMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id[i]; }
  wire[at++] = record->system_id;
  wire[at++] = record->exchange_code;
  wire[at++] = record->price_scale_code;
  wire[at++] = record->security_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->lot_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->prev_close_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->prev_close_volume[i]; }
  wire[at++] = record->price_resolution;
  wire[at++] = record->round_lot;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->mpv[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->unit_of_trade[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Symbol Index Mapping Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_symbol_index_mapping_message(SymbolIndexMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = wire[at++]; }
  record->system_id = wire[at++];
  record->exchange_code = wire[at++];
  record->price_scale_code = wire[at++];
  record->security_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->prev_close_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->prev_close_volume[i] = wire[at++]; }
  record->price_resolution = wire[at++];
  record->round_lot = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->mpv[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->unit_of_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Index Mapping Message is what was written, byte for byte */
static void equal_symbol_index_mapping_message(const SymbolIndexMappingMessage *read, const SymbolIndexMappingMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->market_id[i] == written->market_id[i]); }
  assert(read->system_id == written->system_id);
  assert(read->exchange_code == written->exchange_code);
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->security_type == written->security_type);
  for (size_t i = 0; i < 2; i++) { assert(read->lot_size[i] == written->lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->prev_close_price[i] == written->prev_close_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->prev_close_volume[i] == written->prev_close_volume[i]); }
  assert(read->price_resolution == written->price_resolution);
  assert(read->round_lot == written->round_lot);
  for (size_t i = 0; i < 2; i++) { assert(read->mpv[i] == written->mpv[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->unit_of_trade[i] == written->unit_of_trade[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Symbol Index Mapping Message: written and read back, then read and written back */
static void check_symbol_index_mapping_message(void) {
  SymbolIndexMappingMessage sent;
  SymbolIndexMappingMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_symbol_index_mapping_message(&sent);
  assert(encode_symbol_index_mapping_message(&sent, wire, 0) == 40);
  assert(decode_symbol_index_mapping_message(&got, wire, 0) == 40);
  equal_symbol_index_mapping_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_index_mapping_message(&got, wire, 0) == 40);
  assert(encode_symbol_index_mapping_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Clear Message: 18 bytes ------------------------------------------ */

/* In case of a failure and recovery of a Matching Engine or an Pillar Publisher, the publisher may send a full state refresh for every symbol affected. This unrequested refresh is preceded by a Symbol Clear message. The client should react to receipt of a Symbol Clear message by clearing all state information for the specified symbol in anticipation of receiving a full state refresh. */
typedef struct {
  uint8_t source_time[4];          /* bytes 0 to 3 */
  uint8_t source_time_ns[4];       /* bytes 4 to 7 */
  uint8_t symbol_index[4];         /* bytes 8 to 11 */
  uint8_t next_source_seq_num[4];  /* bytes 12 to 15 */
  uint8_t market_id[2];            /* bytes 16 to 17 */
} SymbolClearMessage;

/* any Symbol Clear Message at all: every byte one the checker chooses */
static void any_symbol_clear_message(SymbolClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->next_source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = arbitrary(); }
}

/* Symbol Clear Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_symbol_clear_message(const SymbolClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_source_seq_num[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id[i]; }

  return at;
}

/* Symbol Clear Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_symbol_clear_message(SymbolClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->next_source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Clear Message is what was written, byte for byte */
static void equal_symbol_clear_message(const SymbolClearMessage *read, const SymbolClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->next_source_seq_num[i] == written->next_source_seq_num[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_id[i] == written->market_id[i]); }
}

/* Symbol Clear Message: written and read back, then read and written back */
static void check_symbol_clear_message(void) {
  SymbolClearMessage sent;
  SymbolClearMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_symbol_clear_message(&sent);
  assert(encode_symbol_clear_message(&sent, wire, 0) == 18);
  assert(decode_symbol_clear_message(&got, wire, 0) == 18);
  equal_symbol_clear_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_clear_message(&got, wire, 0) == 18);
  assert(encode_symbol_clear_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Status Message: 42 bytes --------------------------------------- */

/* This message informs clients of changes in the status of a specific security, such as Trading Halts, Short Sale Restriction state changes, etc. */
typedef struct {
  uint8_t source_time[4];              /* bytes 0 to 3 */
  uint8_t source_time_ns[4];           /* bytes 4 to 7 */
  uint8_t symbol_index[4];             /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];           /* bytes 12 to 15 */
  uint8_t security_status;             /* byte 16 */
  uint8_t halt_condition;              /* byte 17 */
  uint8_t market_id[2];                /* bytes 18 to 19 */
  uint8_t reserved_2[2];               /* bytes 20 to 21 */
  uint8_t price_1[4];                  /* bytes 22 to 25 */
  uint8_t price_2[4];                  /* bytes 26 to 29 */
  uint8_t ssr_triggering_exchange_id;  /* byte 30 */
  uint8_t ssr_triggering_volume[4];    /* bytes 31 to 34 */
  uint8_t time[4];                     /* bytes 35 to 38 */
  uint8_t ssr_state;                   /* byte 39 */
  uint8_t market_state;                /* byte 40 */
  uint8_t session_state;               /* byte 41 */
} SecurityStatusMessage;

/* any Security Status Message at all: every byte one the checker chooses */
static void any_security_status_message(SecurityStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  record->security_status = arbitrary();
  record->halt_condition = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_2[i] = arbitrary(); }
  record->ssr_triggering_exchange_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->ssr_triggering_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  record->ssr_state = arbitrary();
  record->market_state = arbitrary();
  record->session_state = arbitrary();
}

/* Security Status Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_security_status_message(const SecurityStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  wire[at++] = record->security_status;
  wire[at++] = record->halt_condition;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_2[i]; }
  wire[at++] = record->ssr_triggering_exchange_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ssr_triggering_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  wire[at++] = record->ssr_state;
  wire[at++] = record->market_state;
  wire[at++] = record->session_state;

  return at;
}

/* Security Status Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_security_status_message(SecurityStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  record->security_status = wire[at++];
  record->halt_condition = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_2[i] = wire[at++]; }
  record->ssr_triggering_exchange_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->ssr_triggering_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  record->ssr_state = wire[at++];
  record->market_state = wire[at++];
  record->session_state = wire[at++];

  return at;
}

/* what was read of Security Status Message is what was written, byte for byte */
static void equal_security_status_message(const SecurityStatusMessage *read, const SecurityStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  assert(read->security_status == written->security_status);
  assert(read->halt_condition == written->halt_condition);
  for (size_t i = 0; i < 2; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_1[i] == written->price_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_2[i] == written->price_2[i]); }
  assert(read->ssr_triggering_exchange_id == written->ssr_triggering_exchange_id);
  for (size_t i = 0; i < 4; i++) { assert(read->ssr_triggering_volume[i] == written->ssr_triggering_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  assert(read->ssr_state == written->ssr_state);
  assert(read->market_state == written->market_state);
  assert(read->session_state == written->session_state);
}

/* Security Status Message: written and read back, then read and written back */
static void check_security_status_message(void) {
  SecurityStatusMessage sent;
  SecurityStatusMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_security_status_message(&sent);
  assert(encode_security_status_message(&sent, wire, 0) == 42);
  assert(decode_security_status_message(&got, wire, 0) == 42);
  equal_security_status_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_security_status_message(&got, wire, 0) == 42);
  assert(encode_security_status_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Imbalance Message: 69 bytes --------------------------------------------- */

/* Imbalance messages are published once a second during auctions to update price and volume information. */
typedef struct {
  uint8_t source_time[4];                      /* bytes 0 to 3 */
  uint8_t source_time_ns[4];                   /* bytes 4 to 7 */
  uint8_t symbol_index[4];                     /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];                   /* bytes 12 to 15 */
  uint8_t reference_price[4];                  /* bytes 16 to 19 */
  uint8_t paired_qty[4];                       /* bytes 20 to 23 */
  uint8_t total_imbalance_qty[4];              /* bytes 24 to 27 */
  uint8_t market_imbalance_qty[4];             /* bytes 28 to 31 */
  uint8_t auction_time[2];                     /* bytes 32 to 33 */
  uint8_t auction_type;                        /* byte 34 */
  uint8_t imbalance_side;                      /* byte 35 */
  uint8_t continuous_book_clearing_price[4];   /* bytes 36 to 39 */
  uint8_t auction_interest_clearing_price[4];  /* bytes 40 to 43 */
  uint8_t ssr_filing_price[4];                 /* bytes 44 to 47 */
  uint8_t indicative_match_price[4];           /* bytes 48 to 51 */
  uint8_t upper_collar[4];                     /* bytes 52 to 55 */
  uint8_t lower_collar[4];                     /* bytes 56 to 59 */
  uint8_t auction_status;                      /* byte 60 */
  uint8_t freeze_status;                       /* byte 61 */
  uint8_t num_extensions;                      /* byte 62 */
  uint8_t unpaired_qty[4];                     /* bytes 63 to 66 */
  uint8_t unpaired_side;                       /* byte 67 */
  uint8_t significant_imbalance;               /* byte 68 */
} ImbalanceMessage;

/* any Imbalance Message at all: every byte one the checker chooses */
static void any_imbalance_message(ImbalanceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->paired_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_imbalance_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_imbalance_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->auction_time[i] = arbitrary(); }
  record->auction_type = arbitrary();
  record->imbalance_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->continuous_book_clearing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_interest_clearing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ssr_filing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->indicative_match_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->upper_collar[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lower_collar[i] = arbitrary(); }
  record->auction_status = arbitrary();
  record->freeze_status = arbitrary();
  record->num_extensions = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->unpaired_qty[i] = arbitrary(); }
  record->unpaired_side = arbitrary();
  record->significant_imbalance = arbitrary();
}

/* Imbalance Message to the wire: 69 bytes from at, returning where the next byte goes */
static size_t encode_imbalance_message(const ImbalanceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->paired_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_imbalance_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_imbalance_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->auction_time[i]; }
  wire[at++] = record->auction_type;
  wire[at++] = record->imbalance_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->continuous_book_clearing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_interest_clearing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ssr_filing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indicative_match_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->upper_collar[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lower_collar[i]; }
  wire[at++] = record->auction_status;
  wire[at++] = record->freeze_status;
  wire[at++] = record->num_extensions;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unpaired_qty[i]; }
  wire[at++] = record->unpaired_side;
  wire[at++] = record->significant_imbalance;

  return at;
}

/* Imbalance Message off the wire: 69 bytes from at, returning where the next byte lies */
static size_t decode_imbalance_message(ImbalanceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->paired_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_imbalance_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_imbalance_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->auction_time[i] = wire[at++]; }
  record->auction_type = wire[at++];
  record->imbalance_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->continuous_book_clearing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_interest_clearing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ssr_filing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->indicative_match_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->upper_collar[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lower_collar[i] = wire[at++]; }
  record->auction_status = wire[at++];
  record->freeze_status = wire[at++];
  record->num_extensions = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->unpaired_qty[i] = wire[at++]; }
  record->unpaired_side = wire[at++];
  record->significant_imbalance = wire[at++];

  return at;
}

/* what was read of Imbalance Message is what was written, byte for byte */
static void equal_imbalance_message(const ImbalanceMessage *read, const ImbalanceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->paired_qty[i] == written->paired_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_imbalance_qty[i] == written->total_imbalance_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_imbalance_qty[i] == written->market_imbalance_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->auction_time[i] == written->auction_time[i]); }
  assert(read->auction_type == written->auction_type);
  assert(read->imbalance_side == written->imbalance_side);
  for (size_t i = 0; i < 4; i++) { assert(read->continuous_book_clearing_price[i] == written->continuous_book_clearing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_interest_clearing_price[i] == written->auction_interest_clearing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ssr_filing_price[i] == written->ssr_filing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->indicative_match_price[i] == written->indicative_match_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->upper_collar[i] == written->upper_collar[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lower_collar[i] == written->lower_collar[i]); }
  assert(read->auction_status == written->auction_status);
  assert(read->freeze_status == written->freeze_status);
  assert(read->num_extensions == written->num_extensions);
  for (size_t i = 0; i < 4; i++) { assert(read->unpaired_qty[i] == written->unpaired_qty[i]); }
  assert(read->unpaired_side == written->unpaired_side);
  assert(read->significant_imbalance == written->significant_imbalance);
}

/* Imbalance Message: written and read back, then read and written back */
static void check_imbalance_message(void) {
  ImbalanceMessage sent;
  ImbalanceMessage got;
  uint8_t wire[69];
  uint8_t again[69];

  any_imbalance_message(&sent);
  assert(encode_imbalance_message(&sent, wire, 0) == 69);
  assert(decode_imbalance_message(&got, wire, 0) == 69);
  equal_imbalance_message(&got, &sent);

  for (size_t i = 0; i < 69; i++) { wire[i] = arbitrary(); }
  assert(decode_imbalance_message(&got, wire, 0) == 69);
  assert(encode_imbalance_message(&got, again, 0) == 69);
  for (size_t i = 0; i < 69; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_send_time();
  check_packet_header();
  check_message_header();
  check_sequence_number_reset_message();
  check_symbol_index_mapping_message();
  check_symbol_clear_message();
  check_security_status_message();
  check_imbalance_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
