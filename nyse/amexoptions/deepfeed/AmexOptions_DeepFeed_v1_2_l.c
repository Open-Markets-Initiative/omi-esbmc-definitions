// nyse/amexoptions/deepfeed/AmexOptions_DeepFeed_v1_2_l.c
/*
 * New York Stock Exchange Deep Feed
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
 *   - a run counted by a field
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

/* Sent to reset the Message Sequence Number at start of day, or in response to failure recoveries. */
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

/* ---- Source Time Reference Message: 12 bytes --------------------------------- */

/* Sent at the start of every second during periods of active data publication. */
typedef struct {
  uint8_t id[4];              /* bytes 0 to 3 */
  uint8_t symbol_seq_num[4];  /* bytes 4 to 7 */
  uint8_t source_time[4];     /* bytes 8 to 11 */
} SourceTimeReferenceMessage;

/* any Source Time Reference Message at all: every byte one the checker chooses */
static void any_source_time_reference_message(SourceTimeReferenceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
}

/* Source Time Reference Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_source_time_reference_message(const SourceTimeReferenceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }

  return at;
}

/* Source Time Reference Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_source_time_reference_message(SourceTimeReferenceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }

  return at;
}

/* what was read of Source Time Reference Message is what was written, byte for byte */
static void equal_source_time_reference_message(const SourceTimeReferenceMessage *read, const SourceTimeReferenceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->id[i] == written->id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
}

/* Source Time Reference Message: written and read back, then read and written back */
static void check_source_time_reference_message(void) {
  SourceTimeReferenceMessage sent;
  SourceTimeReferenceMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_source_time_reference_message(&sent);
  assert(encode_source_time_reference_message(&sent, wire, 0) == 12);
  assert(decode_source_time_reference_message(&got, wire, 0) == 12);
  equal_source_time_reference_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_source_time_reference_message(&got, wire, 0) == 12);
  assert(encode_source_time_reference_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Index Mapping Message: 40 bytes ---------------------------------- */

/* Published over the real-time data channels at system startup or in the context of a refresh sequence. Provides referential data for a single specified symbol or underlying symbol. */
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
  uint8_t reserved_2[2];         /* bytes 34 to 35 */
  uint8_t second_reserved_2[2];  /* bytes 36 to 37 */
  uint8_t third_reserved_2[2];   /* bytes 38 to 39 */
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
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->second_reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->third_reserved_2[i] = arbitrary(); }
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
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->second_reserved_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->third_reserved_2[i]; }

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
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->second_reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->third_reserved_2[i] = wire[at++]; }

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
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->second_reserved_2[i] == written->second_reserved_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->third_reserved_2[i] == written->third_reserved_2[i]); }
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

/* ---- Symbol Clear Message: 16 bytes ------------------------------------------ */

/* In case of a failure and recovery, the publisher may send a full state refresh for every symbol or series affected, preceded by a Symbol Clear message. */
typedef struct {
  uint8_t source_time[4];          /* bytes 0 to 3 */
  uint8_t source_time_ns[4];       /* bytes 4 to 7 */
  uint8_t symbol_index[4];         /* bytes 8 to 11 */
  uint8_t next_source_seq_num[4];  /* bytes 12 to 15 */
} SymbolClearMessage;

/* any Symbol Clear Message at all: every byte one the checker chooses */
static void any_symbol_clear_message(SymbolClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->next_source_seq_num[i] = arbitrary(); }
}

/* Symbol Clear Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_symbol_clear_message(const SymbolClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_source_seq_num[i]; }

  return at;
}

/* Symbol Clear Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_symbol_clear_message(SymbolClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->next_source_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Clear Message is what was written, byte for byte */
static void equal_symbol_clear_message(const SymbolClearMessage *read, const SymbolClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->next_source_seq_num[i] == written->next_source_seq_num[i]); }
}

/* Symbol Clear Message: written and read back, then read and written back */
static void check_symbol_clear_message(void) {
  SymbolClearMessage sent;
  SymbolClearMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_symbol_clear_message(&sent);
  assert(encode_symbol_clear_message(&sent, wire, 0) == 16);
  assert(decode_symbol_clear_message(&got, wire, 0) == 16);
  equal_symbol_clear_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_clear_message(&got, wire, 0) == 16);
  assert(encode_symbol_clear_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Status Message: 42 bytes --------------------------------------- */

/* Informs clients of changes in the status of a specific security or underlying symbol, such as Trading Halts, Short Sale Restriction state changes, etc. */
typedef struct {
  uint8_t source_time[4];              /* bytes 0 to 3 */
  uint8_t source_time_ns[4];           /* bytes 4 to 7 */
  uint8_t symbol_index[4];             /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];           /* bytes 12 to 15 */
  uint8_t security_status;             /* byte 16 */
  uint8_t halt_condition;              /* byte 17 */
  uint8_t reserved_4[4];               /* bytes 18 to 21 */
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
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
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
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
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
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
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

/* ---- Outright Series Index Mapping Message: 51 bytes ------------------------- */

/* Published over the real-time data channels at system startup or in the context of a refresh sequence. Provides referential data for a single specified options outright series. */
typedef struct {
  uint8_t series_index[4];         /* bytes 0 to 3 */
  uint8_t series_type;             /* byte 4 */
  uint8_t market_id[2];            /* bytes 5 to 6 */
  uint8_t system_id;               /* byte 7 */
  uint8_t option_symbol_root[6];   /* bytes 8 to 13 */
  uint8_t underlying_symbol[11];   /* bytes 14 to 24 */
  uint8_t underlying_index[4];     /* bytes 25 to 28 */
  uint8_t price_scale_code;        /* byte 29 */
  uint8_t contract_multiplier[2];  /* bytes 30 to 31 */
  uint8_t maturity_date[6];        /* bytes 32 to 37 */
  uint8_t put_or_call;             /* byte 38 */
  uint8_t strike_price[10];        /* bytes 39 to 48 */
  uint8_t closing_only_indicator;  /* byte 49 */
  uint8_t reserved_1;              /* byte 50 */
} OutrightSeriesIndexMappingMessage;

/* any Outright Series Index Mapping Message at all: every byte one the checker chooses */
static void any_outright_series_index_mapping_message(OutrightSeriesIndexMappingMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  record->series_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = arbitrary(); }
  record->system_id = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->option_symbol_root[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_index[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->contract_multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->maturity_date[i] = arbitrary(); }
  record->put_or_call = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->strike_price[i] = arbitrary(); }
  record->closing_only_indicator = arbitrary();
  record->reserved_1 = arbitrary();
}

/* Outright Series Index Mapping Message to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_outright_series_index_mapping_message(const OutrightSeriesIndexMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  wire[at++] = record->series_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id[i]; }
  wire[at++] = record->system_id;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->option_symbol_root[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_index[i]; }
  wire[at++] = record->price_scale_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->contract_multiplier[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->maturity_date[i]; }
  wire[at++] = record->put_or_call;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->closing_only_indicator;
  wire[at++] = record->reserved_1;

  return at;
}

/* Outright Series Index Mapping Message off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_outright_series_index_mapping_message(OutrightSeriesIndexMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  record->series_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = wire[at++]; }
  record->system_id = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->option_symbol_root[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_index[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->contract_multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->maturity_date[i] = wire[at++]; }
  record->put_or_call = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->strike_price[i] = wire[at++]; }
  record->closing_only_indicator = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Outright Series Index Mapping Message is what was written, byte for byte */
static void equal_outright_series_index_mapping_message(const OutrightSeriesIndexMappingMessage *read, const OutrightSeriesIndexMappingMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  assert(read->series_type == written->series_type);
  for (size_t i = 0; i < 2; i++) { assert(read->market_id[i] == written->market_id[i]); }
  assert(read->system_id == written->system_id);
  for (size_t i = 0; i < 6; i++) { assert(read->option_symbol_root[i] == written->option_symbol_root[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_index[i] == written->underlying_index[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  for (size_t i = 0; i < 2; i++) { assert(read->contract_multiplier[i] == written->contract_multiplier[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  assert(read->put_or_call == written->put_or_call);
  for (size_t i = 0; i < 10; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->closing_only_indicator == written->closing_only_indicator);
  assert(read->reserved_1 == written->reserved_1);
}

/* Outright Series Index Mapping Message: written and read back, then read and written back */
static void check_outright_series_index_mapping_message(void) {
  OutrightSeriesIndexMappingMessage sent;
  OutrightSeriesIndexMappingMessage got;
  uint8_t wire[51];
  uint8_t again[51];

  any_outright_series_index_mapping_message(&sent);
  assert(encode_outright_series_index_mapping_message(&sent, wire, 0) == 51);
  assert(decode_outright_series_index_mapping_message(&got, wire, 0) == 51);
  equal_outright_series_index_mapping_message(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_outright_series_index_mapping_message(&got, wire, 0) == 51);
  assert(encode_outright_series_index_mapping_message(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Status Message: 19 bytes ---------------------------------------- */

/* Informs clients of changes in the status of a specific option outright series and complex series, such as Trading Halts. */
typedef struct {
  uint8_t source_time[4];                 /* bytes 0 to 3 */
  uint8_t source_time_ns[4];              /* bytes 4 to 7 */
  uint8_t series_index[4];                /* bytes 8 to 11 */
  uint8_t series_seq_num[4];              /* bytes 12 to 15 */
  uint8_t series_status;                  /* byte 16 */
  uint8_t market_state;                   /* byte 17 */
  uint8_t options_status_halt_condition;  /* byte 18 */
} OptionsStatusMessage;

/* any Options Status Message at all: every byte one the checker chooses */
static void any_options_status_message(OptionsStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = arbitrary(); }
  record->series_status = arbitrary();
  record->market_state = arbitrary();
  record->options_status_halt_condition = arbitrary();
}

/* Options Status Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_options_status_message(const OptionsStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_seq_num[i]; }
  wire[at++] = record->series_status;
  wire[at++] = record->market_state;
  wire[at++] = record->options_status_halt_condition;

  return at;
}

/* Options Status Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_options_status_message(OptionsStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = wire[at++]; }
  record->series_status = wire[at++];
  record->market_state = wire[at++];
  record->options_status_halt_condition = wire[at++];

  return at;
}

/* what was read of Options Status Message is what was written, byte for byte */
static void equal_options_status_message(const OptionsStatusMessage *read, const OptionsStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_seq_num[i] == written->series_seq_num[i]); }
  assert(read->series_status == written->series_status);
  assert(read->market_state == written->market_state);
  assert(read->options_status_halt_condition == written->options_status_halt_condition);
}

/* Options Status Message: written and read back, then read and written back */
static void check_options_status_message(void) {
  OptionsStatusMessage sent;
  OptionsStatusMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_options_status_message(&sent);
  assert(encode_options_status_message(&sent, wire, 0) == 19);
  assert(decode_options_status_message(&got, wire, 0) == 19);
  equal_options_status_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_options_status_message(&got, wire, 0) == 19);
  assert(encode_options_status_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Request Message: 20 bytes -------------------------------- */

/* Sent by clients via TCP/IP to request retransmission of missed messages. */
typedef struct {
  uint8_t begin_seq_num[4];  /* bytes 0 to 3 */
  uint8_t end_seq_num[4];    /* bytes 4 to 7 */
  uint8_t source_id[10];     /* bytes 8 to 17 */
  uint8_t product_id;        /* byte 18 */
  uint8_t channel_id;        /* byte 19 */
} RetransmissionRequestMessage;

/* any Retransmission Request Message at all: every byte one the checker chooses */
static void any_retransmission_request_message(RetransmissionRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = arbitrary(); }
  record->product_id = arbitrary();
  record->channel_id = arbitrary();
}

/* Retransmission Request Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_request_message(const RetransmissionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->begin_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_seq_num[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->source_id[i]; }
  wire[at++] = record->product_id;
  wire[at++] = record->channel_id;

  return at;
}

/* Retransmission Request Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_request_message(RetransmissionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = wire[at++]; }
  record->product_id = wire[at++];
  record->channel_id = wire[at++];

  return at;
}

/* what was read of Retransmission Request Message is what was written, byte for byte */
static void equal_retransmission_request_message(const RetransmissionRequestMessage *read, const RetransmissionRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->begin_seq_num[i] == written->begin_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_seq_num[i] == written->end_seq_num[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->source_id[i] == written->source_id[i]); }
  assert(read->product_id == written->product_id);
  assert(read->channel_id == written->channel_id);
}

/* Retransmission Request Message: written and read back, then read and written back */
static void check_retransmission_request_message(void) {
  RetransmissionRequestMessage sent;
  RetransmissionRequestMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_retransmission_request_message(&sent);
  assert(encode_retransmission_request_message(&sent, wire, 0) == 20);
  assert(decode_retransmission_request_message(&got, wire, 0) == 20);
  equal_retransmission_request_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_request_message(&got, wire, 0) == 20);
  assert(encode_retransmission_request_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Request Message: 16 bytes --------------------------------------- */

/* Sent by clients via TCP/IP to request a refresh of the state of one or all symbols in a specific channel. */
typedef struct {
  uint8_t symbol_index[4];  /* bytes 0 to 3 */
  uint8_t source_id[10];    /* bytes 4 to 13 */
  uint8_t product_id;       /* byte 14 */
  uint8_t channel_id;       /* byte 15 */
} RefreshRequestMessage;

/* any Refresh Request Message at all: every byte one the checker chooses */
static void any_refresh_request_message(RefreshRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = arbitrary(); }
  record->product_id = arbitrary();
  record->channel_id = arbitrary();
}

/* Refresh Request Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_refresh_request_message(const RefreshRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->source_id[i]; }
  wire[at++] = record->product_id;
  wire[at++] = record->channel_id;

  return at;
}

/* Refresh Request Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_refresh_request_message(RefreshRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = wire[at++]; }
  record->product_id = wire[at++];
  record->channel_id = wire[at++];

  return at;
}

/* what was read of Refresh Request Message is what was written, byte for byte */
static void equal_refresh_request_message(const RefreshRequestMessage *read, const RefreshRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->source_id[i] == written->source_id[i]); }
  assert(read->product_id == written->product_id);
  assert(read->channel_id == written->channel_id);
}

/* Refresh Request Message: written and read back, then read and written back */
static void check_refresh_request_message(void) {
  RefreshRequestMessage sent;
  RefreshRequestMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_refresh_request_message(&sent);
  assert(encode_refresh_request_message(&sent, wire, 0) == 16);
  assert(decode_refresh_request_message(&got, wire, 0) == 16);
  equal_refresh_request_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_request_message(&got, wire, 0) == 16);
  assert(encode_refresh_request_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Index Mapping Request Message: 17 bytes -------------------------- */

/* Sent by clients via TCP/IP requesting the Symbol Index Mapping messages for one or all symbols in a specified channel. */
typedef struct {
  uint8_t symbol_index[4];    /* bytes 0 to 3 */
  uint8_t source_id[10];      /* bytes 4 to 13 */
  uint8_t product_id;         /* byte 14 */
  uint8_t channel_id;         /* byte 15 */
  uint8_t retransmit_method;  /* byte 16 */
} SymbolIndexMappingRequestMessage;

/* any Symbol Index Mapping Request Message at all: every byte one the checker chooses */
static void any_symbol_index_mapping_request_message(SymbolIndexMappingRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = arbitrary(); }
  record->product_id = arbitrary();
  record->channel_id = arbitrary();
  record->retransmit_method = arbitrary();
}

/* Symbol Index Mapping Request Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_symbol_index_mapping_request_message(const SymbolIndexMappingRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->source_id[i]; }
  wire[at++] = record->product_id;
  wire[at++] = record->channel_id;
  wire[at++] = record->retransmit_method;

  return at;
}

/* Symbol Index Mapping Request Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_symbol_index_mapping_request_message(SymbolIndexMappingRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = wire[at++]; }
  record->product_id = wire[at++];
  record->channel_id = wire[at++];
  record->retransmit_method = wire[at++];

  return at;
}

/* what was read of Symbol Index Mapping Request Message is what was written, byte for byte */
static void equal_symbol_index_mapping_request_message(const SymbolIndexMappingRequestMessage *read, const SymbolIndexMappingRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->source_id[i] == written->source_id[i]); }
  assert(read->product_id == written->product_id);
  assert(read->channel_id == written->channel_id);
  assert(read->retransmit_method == written->retransmit_method);
}

/* Symbol Index Mapping Request Message: written and read back, then read and written back */
static void check_symbol_index_mapping_request_message(void) {
  SymbolIndexMappingRequestMessage sent;
  SymbolIndexMappingRequestMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_symbol_index_mapping_request_message(&sent);
  assert(encode_symbol_index_mapping_request_message(&sent, wire, 0) == 17);
  assert(decode_symbol_index_mapping_request_message(&got, wire, 0) == 17);
  equal_symbol_index_mapping_request_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_index_mapping_request_message(&got, wire, 0) == 17);
  assert(encode_symbol_index_mapping_request_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Unavailable Message: 10 bytes ----------------------------------- */

/* Sent over the Retransmission multicast channels to inform clients of unavailability of a range of messages. */
typedef struct {
  uint8_t begin_seq_num[4];  /* bytes 0 to 3 */
  uint8_t end_seq_num[4];    /* bytes 4 to 7 */
  uint8_t product_id;        /* byte 8 */
  uint8_t channel_id;        /* byte 9 */
} MessageUnavailableMessage;

/* any Message Unavailable Message at all: every byte one the checker chooses */
static void any_message_unavailable_message(MessageUnavailableMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = arbitrary(); }
  record->product_id = arbitrary();
  record->channel_id = arbitrary();
}

/* Message Unavailable Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_message_unavailable_message(const MessageUnavailableMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->begin_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_seq_num[i]; }
  wire[at++] = record->product_id;
  wire[at++] = record->channel_id;

  return at;
}

/* Message Unavailable Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_message_unavailable_message(MessageUnavailableMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = wire[at++]; }
  record->product_id = wire[at++];
  record->channel_id = wire[at++];

  return at;
}

/* what was read of Message Unavailable Message is what was written, byte for byte */
static void equal_message_unavailable_message(const MessageUnavailableMessage *read, const MessageUnavailableMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->begin_seq_num[i] == written->begin_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_seq_num[i] == written->end_seq_num[i]); }
  assert(read->product_id == written->product_id);
  assert(read->channel_id == written->channel_id);
}

/* Message Unavailable Message: written and read back, then read and written back */
static void check_message_unavailable_message(void) {
  MessageUnavailableMessage sent;
  MessageUnavailableMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_message_unavailable_message(&sent);
  assert(encode_message_unavailable_message(&sent, wire, 0) == 10);
  assert(decode_message_unavailable_message(&got, wire, 0) == 10);
  equal_message_unavailable_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_message_unavailable_message(&got, wire, 0) == 10);
  assert(encode_message_unavailable_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Request Response Message: 25 bytes -------------------------------------- */

/* Sent immediately via TCP/IP in response to the client's request for retransmission, refresh or Symbol Mapping messages. */
typedef struct {
  uint8_t request_seq_num[4];  /* bytes 0 to 3 */
  uint8_t begin_seq_num[4];    /* bytes 4 to 7 */
  uint8_t end_seq_num[4];      /* bytes 8 to 11 */
  uint8_t source_id[10];       /* bytes 12 to 21 */
  uint8_t product_id;          /* byte 22 */
  uint8_t channel_id;          /* byte 23 */
  uint8_t status;              /* byte 24 */
} RequestResponseMessage;

/* any Request Response Message at all: every byte one the checker chooses */
static void any_request_response_message(RequestResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = arbitrary(); }
  record->product_id = arbitrary();
  record->channel_id = arbitrary();
  record->status = arbitrary();
}

/* Request Response Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_request_response_message(const RequestResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->begin_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_seq_num[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->source_id[i]; }
  wire[at++] = record->product_id;
  wire[at++] = record->channel_id;
  wire[at++] = record->status;

  return at;
}

/* Request Response Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_request_response_message(RequestResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->begin_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = wire[at++]; }
  record->product_id = wire[at++];
  record->channel_id = wire[at++];
  record->status = wire[at++];

  return at;
}

/* what was read of Request Response Message is what was written, byte for byte */
static void equal_request_response_message(const RequestResponseMessage *read, const RequestResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_seq_num[i] == written->request_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->begin_seq_num[i] == written->begin_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_seq_num[i] == written->end_seq_num[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->source_id[i] == written->source_id[i]); }
  assert(read->product_id == written->product_id);
  assert(read->channel_id == written->channel_id);
  assert(read->status == written->status);
}

/* Request Response Message: written and read back, then read and written back */
static void check_request_response_message(void) {
  RequestResponseMessage sent;
  RequestResponseMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_request_response_message(&sent);
  assert(encode_request_response_message(&sent, wire, 0) == 25);
  assert(decode_request_response_message(&got, wire, 0) == 25);
  equal_request_response_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_request_response_message(&got, wire, 0) == 25);
  assert(encode_request_response_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat Response Message: 10 bytes ------------------------------------ */

/* Clients who remain connected to the Retransmission Server intraday must respond to a Heartbeat with a Heartbeat Response message within 5 seconds. */
typedef struct {
  uint8_t source_id[10];  /* bytes 0 to 9 */
} HeartbeatResponseMessage;

/* any Heartbeat Response Message at all: every byte one the checker chooses */
static void any_heartbeat_response_message(HeartbeatResponseMessage *record) {
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = arbitrary(); }
}

/* Heartbeat Response Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat_response_message(const HeartbeatResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->source_id[i]; }

  return at;
}

/* Heartbeat Response Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat_response_message(HeartbeatResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->source_id[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat Response Message is what was written, byte for byte */
static void equal_heartbeat_response_message(const HeartbeatResponseMessage *read, const HeartbeatResponseMessage *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->source_id[i] == written->source_id[i]); }
}

/* Heartbeat Response Message: written and read back, then read and written back */
static void check_heartbeat_response_message(void) {
  HeartbeatResponseMessage sent;
  HeartbeatResponseMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_heartbeat_response_message(&sent);
  assert(encode_heartbeat_response_message(&sent, wire, 0) == 10);
  assert(decode_heartbeat_response_message(&got, wire, 0) == 10);
  equal_heartbeat_response_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat_response_message(&got, wire, 0) == 10);
  assert(encode_heartbeat_response_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Add Order Message: 36 bytes ------------------------------------- */

/* Published when a new visible order has been received and added to the book. */
typedef struct {
  uint8_t source_time_ns[4];  /* bytes 0 to 3 */
  uint8_t series_index[4];    /* bytes 4 to 7 */
  uint8_t series_seq_num[4];  /* bytes 8 to 11 */
  uint8_t order_id[8];        /* bytes 12 to 19 */
  uint8_t price[4];           /* bytes 20 to 23 */
  uint8_t volume[4];          /* bytes 24 to 27 */
  uint8_t side;               /* byte 28 */
  uint8_t firm_id[5];         /* bytes 29 to 33 */
  uint8_t reserved_1;         /* byte 34 */
  uint8_t cust_indicator;     /* byte 35 */
} OptionsAddOrderMessage;

/* any Options Add Order Message at all: every byte one the checker chooses */
static void any_options_add_order_message(OptionsAddOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->firm_id[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->cust_indicator = arbitrary();
}

/* Options Add Order Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_options_add_order_message(const OptionsAddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->firm_id[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->cust_indicator;

  return at;
}

/* Options Add Order Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_options_add_order_message(OptionsAddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->firm_id[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->cust_indicator = wire[at++];

  return at;
}

/* what was read of Options Add Order Message is what was written, byte for byte */
static void equal_options_add_order_message(const OptionsAddOrderMessage *read, const OptionsAddOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_seq_num[i] == written->series_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 5; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  assert(read->reserved_1 == written->reserved_1);
  assert(read->cust_indicator == written->cust_indicator);
}

/* Options Add Order Message: written and read back, then read and written back */
static void check_options_add_order_message(void) {
  OptionsAddOrderMessage sent;
  OptionsAddOrderMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_options_add_order_message(&sent);
  assert(encode_options_add_order_message(&sent, wire, 0) == 36);
  assert(decode_options_add_order_message(&got, wire, 0) == 36);
  equal_options_add_order_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_options_add_order_message(&got, wire, 0) == 36);
  assert(encode_options_add_order_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Modify Order Message: 31 bytes ---------------------------------- */

/* Sent when the price or volume of an order is changed due to an event other than a cancel-replace, or full or partial execution. */
typedef struct {
  uint8_t source_time_ns[4];  /* bytes 0 to 3 */
  uint8_t series_index[4];    /* bytes 4 to 7 */
  uint8_t series_seq_num[4];  /* bytes 8 to 11 */
  uint8_t order_id[8];        /* bytes 12 to 19 */
  uint8_t price[4];           /* bytes 20 to 23 */
  uint8_t volume[4];          /* bytes 24 to 27 */
  uint8_t position_change;    /* byte 28 */
  uint8_t side;               /* byte 29 */
  uint8_t cust_indicator;     /* byte 30 */
} OptionsModifyOrderMessage;

/* any Options Modify Order Message at all: every byte one the checker chooses */
static void any_options_modify_order_message(OptionsModifyOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->position_change = arbitrary();
  record->side = arbitrary();
  record->cust_indicator = arbitrary();
}

/* Options Modify Order Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_options_modify_order_message(const OptionsModifyOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->position_change;
  wire[at++] = record->side;
  wire[at++] = record->cust_indicator;

  return at;
}

/* Options Modify Order Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_options_modify_order_message(OptionsModifyOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->position_change = wire[at++];
  record->side = wire[at++];
  record->cust_indicator = wire[at++];

  return at;
}

/* what was read of Options Modify Order Message is what was written, byte for byte */
static void equal_options_modify_order_message(const OptionsModifyOrderMessage *read, const OptionsModifyOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_seq_num[i] == written->series_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->position_change == written->position_change);
  assert(read->side == written->side);
  assert(read->cust_indicator == written->cust_indicator);
}

/* Options Modify Order Message: written and read back, then read and written back */
static void check_options_modify_order_message(void) {
  OptionsModifyOrderMessage sent;
  OptionsModifyOrderMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_options_modify_order_message(&sent);
  assert(encode_options_modify_order_message(&sent, wire, 0) == 31);
  assert(decode_options_modify_order_message(&got, wire, 0) == 31);
  equal_options_modify_order_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_options_modify_order_message(&got, wire, 0) == 31);
  assert(encode_options_modify_order_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Delete Order Message: 21 bytes ---------------------------------- */

/* Published when an order is taken off of the book for any reason except for full execution. */
typedef struct {
  uint8_t source_time_ns[4];  /* bytes 0 to 3 */
  uint8_t series_index[4];    /* bytes 4 to 7 */
  uint8_t series_seq_num[4];  /* bytes 8 to 11 */
  uint8_t order_id[8];        /* bytes 12 to 19 */
  uint8_t reserved_1;         /* byte 20 */
} OptionsDeleteOrderMessage;

/* any Options Delete Order Message at all: every byte one the checker chooses */
static void any_options_delete_order_message(OptionsDeleteOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Options Delete Order Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_options_delete_order_message(const OptionsDeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Options Delete Order Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_options_delete_order_message(OptionsDeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Options Delete Order Message is what was written, byte for byte */
static void equal_options_delete_order_message(const OptionsDeleteOrderMessage *read, const OptionsDeleteOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_seq_num[i] == written->series_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Options Delete Order Message: written and read back, then read and written back */
static void check_options_delete_order_message(void) {
  OptionsDeleteOrderMessage sent;
  OptionsDeleteOrderMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_options_delete_order_message(&sent);
  assert(encode_options_delete_order_message(&sent, wire, 0) == 21);
  assert(decode_options_delete_order_message(&got, wire, 0) == 21);
  equal_options_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_options_delete_order_message(&got, wire, 0) == 21);
  assert(encode_options_delete_order_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Order Execution Message: 38 bytes ------------------------------- */

/* Sent when an order is partially or fully executed. */
typedef struct {
  uint8_t source_time_ns[4];  /* bytes 0 to 3 */
  uint8_t series_index[4];    /* bytes 4 to 7 */
  uint8_t series_seq_num[4];  /* bytes 8 to 11 */
  uint8_t order_id[8];        /* bytes 12 to 19 */
  uint8_t trade_id[4];        /* bytes 20 to 23 */
  uint8_t price[4];           /* bytes 24 to 27 */
  uint8_t volume[4];          /* bytes 28 to 31 */
  uint8_t printable_flag;     /* byte 32 */
  uint8_t reserved_1;         /* byte 33 */
  uint8_t trade_cond_1;       /* byte 34 */
  uint8_t reserved_3[3];      /* bytes 35 to 37 */
} OptionsOrderExecutionMessage;

/* any Options Order Execution Message at all: every byte one the checker chooses */
static void any_options_order_execution_message(OptionsOrderExecutionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->printable_flag = arbitrary();
  record->reserved_1 = arbitrary();
  record->trade_cond_1 = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Options Order Execution Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_options_order_execution_message(const OptionsOrderExecutionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->printable_flag;
  wire[at++] = record->reserved_1;
  wire[at++] = record->trade_cond_1;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Options Order Execution Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_options_order_execution_message(OptionsOrderExecutionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->printable_flag = wire[at++];
  record->reserved_1 = wire[at++];
  record->trade_cond_1 = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Options Order Execution Message is what was written, byte for byte */
static void equal_options_order_execution_message(const OptionsOrderExecutionMessage *read, const OptionsOrderExecutionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_seq_num[i] == written->series_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->printable_flag == written->printable_flag);
  assert(read->reserved_1 == written->reserved_1);
  assert(read->trade_cond_1 == written->trade_cond_1);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Options Order Execution Message: written and read back, then read and written back */
static void check_options_order_execution_message(void) {
  OptionsOrderExecutionMessage sent;
  OptionsOrderExecutionMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_options_order_execution_message(&sent);
  assert(encode_options_order_execution_message(&sent, wire, 0) == 38);
  assert(decode_options_order_execution_message(&got, wire, 0) == 38);
  equal_options_order_execution_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_options_order_execution_message(&got, wire, 0) == 38);
  assert(encode_options_order_execution_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Replace Order Message: 39 bytes --------------------------------- */

/* Published when a cancel/replace order is received. The resting order is replaced with a new order containing the same outright or complex series, side and attribution, a new Order ID, and the price and size specified. */
typedef struct {
  uint8_t source_time_ns[4];  /* bytes 0 to 3 */
  uint8_t series_index[4];    /* bytes 4 to 7 */
  uint8_t series_seq_num[4];  /* bytes 8 to 11 */
  uint8_t order_id[8];        /* bytes 12 to 19 */
  uint8_t new_order_id[8];    /* bytes 20 to 27 */
  uint8_t price[4];           /* bytes 28 to 31 */
  uint8_t volume[4];          /* bytes 32 to 35 */
  uint8_t side;               /* byte 36 */
  uint8_t reserved_1;         /* byte 37 */
  uint8_t cust_indicator;     /* byte 38 */
} OptionsReplaceOrderMessage;

/* any Options Replace Order Message at all: every byte one the checker chooses */
static void any_options_replace_order_message(OptionsReplaceOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->new_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->side = arbitrary();
  record->reserved_1 = arbitrary();
  record->cust_indicator = arbitrary();
}

/* Options Replace Order Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_options_replace_order_message(const OptionsReplaceOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->side;
  wire[at++] = record->reserved_1;
  wire[at++] = record->cust_indicator;

  return at;
}

/* Options Replace Order Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_options_replace_order_message(OptionsReplaceOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->new_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->side = wire[at++];
  record->reserved_1 = wire[at++];
  record->cust_indicator = wire[at++];

  return at;
}

/* what was read of Options Replace Order Message is what was written, byte for byte */
static void equal_options_replace_order_message(const OptionsReplaceOrderMessage *read, const OptionsReplaceOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_seq_num[i] == written->series_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->new_order_id[i] == written->new_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->side == written->side);
  assert(read->reserved_1 == written->reserved_1);
  assert(read->cust_indicator == written->cust_indicator);
}

/* Options Replace Order Message: written and read back, then read and written back */
static void check_options_replace_order_message(void) {
  OptionsReplaceOrderMessage sent;
  OptionsReplaceOrderMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_options_replace_order_message(&sent);
  assert(encode_options_replace_order_message(&sent, wire, 0) == 39);
  assert(decode_options_replace_order_message(&got, wire, 0) == 39);
  equal_options_replace_order_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_options_replace_order_message(&got, wire, 0) == 39);
  assert(encode_options_replace_order_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Imbalance Message: 61 bytes ------------------------------------- */

/* Published every 5 seconds, during opening and re-opening auctions to update price and volume information. */
typedef struct {
  uint8_t source_time[4];                      /* bytes 0 to 3 */
  uint8_t source_time_ns[4];                   /* bytes 4 to 7 */
  uint8_t series_index[4];                     /* bytes 8 to 11 */
  uint8_t series_seq_num[4];                   /* bytes 12 to 15 */
  uint8_t reserved_4[4];                       /* bytes 16 to 19 */
  uint8_t paired_qty[4];                       /* bytes 20 to 23 */
  uint8_t total_imbalance_qty[4];              /* bytes 24 to 27 */
  uint8_t market_imbalance_qty[4];             /* bytes 28 to 31 */
  uint8_t reserved_2[2];                       /* bytes 32 to 33 */
  uint8_t auction_type;                        /* byte 34 */
  uint8_t imbalance_side;                      /* byte 35 */
  uint8_t continuous_book_clearing_price[4];   /* bytes 36 to 39 */
  uint8_t auction_interest_clearing_price[4];  /* bytes 40 to 43 */
  uint8_t second_reserved_4[4];                /* bytes 44 to 47 */
  uint8_t indicative_match_price[4];           /* bytes 48 to 51 */
  uint8_t upper_collar[4];                     /* bytes 52 to 55 */
  uint8_t lower_collar[4];                     /* bytes 56 to 59 */
  uint8_t auction_status;                      /* byte 60 */
} OptionsImbalanceMessage;

/* any Options Imbalance Message at all: every byte one the checker chooses */
static void any_options_imbalance_message(OptionsImbalanceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->paired_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_imbalance_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_imbalance_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->auction_type = arbitrary();
  record->imbalance_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->continuous_book_clearing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_interest_clearing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->second_reserved_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->indicative_match_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->upper_collar[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lower_collar[i] = arbitrary(); }
  record->auction_status = arbitrary();
}

/* Options Imbalance Message to the wire: 61 bytes from at, returning where the next byte goes */
static size_t encode_options_imbalance_message(const OptionsImbalanceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->paired_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_imbalance_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_imbalance_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->auction_type;
  wire[at++] = record->imbalance_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->continuous_book_clearing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_interest_clearing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second_reserved_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indicative_match_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->upper_collar[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lower_collar[i]; }
  wire[at++] = record->auction_status;

  return at;
}

/* Options Imbalance Message off the wire: 61 bytes from at, returning where the next byte lies */
static size_t decode_options_imbalance_message(OptionsImbalanceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->paired_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_imbalance_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_imbalance_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->auction_type = wire[at++];
  record->imbalance_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->continuous_book_clearing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_interest_clearing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->second_reserved_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->indicative_match_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->upper_collar[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lower_collar[i] = wire[at++]; }
  record->auction_status = wire[at++];

  return at;
}

/* what was read of Options Imbalance Message is what was written, byte for byte */
static void equal_options_imbalance_message(const OptionsImbalanceMessage *read, const OptionsImbalanceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_seq_num[i] == written->series_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->paired_qty[i] == written->paired_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_imbalance_qty[i] == written->total_imbalance_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_imbalance_qty[i] == written->market_imbalance_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->auction_type == written->auction_type);
  assert(read->imbalance_side == written->imbalance_side);
  for (size_t i = 0; i < 4; i++) { assert(read->continuous_book_clearing_price[i] == written->continuous_book_clearing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_interest_clearing_price[i] == written->auction_interest_clearing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->second_reserved_4[i] == written->second_reserved_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->indicative_match_price[i] == written->indicative_match_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->upper_collar[i] == written->upper_collar[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lower_collar[i] == written->lower_collar[i]); }
  assert(read->auction_status == written->auction_status);
}

/* Options Imbalance Message: written and read back, then read and written back */
static void check_options_imbalance_message(void) {
  OptionsImbalanceMessage sent;
  OptionsImbalanceMessage got;
  uint8_t wire[61];
  uint8_t again[61];

  any_options_imbalance_message(&sent);
  assert(encode_options_imbalance_message(&sent, wire, 0) == 61);
  assert(decode_options_imbalance_message(&got, wire, 0) == 61);
  equal_options_imbalance_message(&got, &sent);

  for (size_t i = 0; i < 61; i++) { wire[i] = arbitrary(); }
  assert(decode_options_imbalance_message(&got, wire, 0) == 61);
  assert(encode_options_imbalance_message(&got, again, 0) == 61);
  for (size_t i = 0; i < 61; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Add Order Refresh Message: 40 bytes ----------------------------- */

/* Sent as part of a refresh response for every order currently resting on the book. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_time_ns[4];  /* bytes 4 to 7 */
  uint8_t series_index[4];    /* bytes 8 to 11 */
  uint8_t series_seq_num[4];  /* bytes 12 to 15 */
  uint8_t order_id[8];        /* bytes 16 to 23 */
  uint8_t price[4];           /* bytes 24 to 27 */
  uint8_t volume[4];          /* bytes 28 to 31 */
  uint8_t side;               /* byte 32 */
  uint8_t firm_id[5];         /* bytes 33 to 37 */
  uint8_t reserved_1;         /* byte 38 */
  uint8_t cust_indicator;     /* byte 39 */
} OptionsAddOrderRefreshMessage;

/* any Options Add Order Refresh Message at all: every byte one the checker chooses */
static void any_options_add_order_refresh_message(OptionsAddOrderRefreshMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->firm_id[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->cust_indicator = arbitrary();
}

/* Options Add Order Refresh Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_options_add_order_refresh_message(const OptionsAddOrderRefreshMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->firm_id[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->cust_indicator;

  return at;
}

/* Options Add Order Refresh Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_options_add_order_refresh_message(OptionsAddOrderRefreshMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->firm_id[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->cust_indicator = wire[at++];

  return at;
}

/* what was read of Options Add Order Refresh Message is what was written, byte for byte */
static void equal_options_add_order_refresh_message(const OptionsAddOrderRefreshMessage *read, const OptionsAddOrderRefreshMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_seq_num[i] == written->series_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 5; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  assert(read->reserved_1 == written->reserved_1);
  assert(read->cust_indicator == written->cust_indicator);
}

/* Options Add Order Refresh Message: written and read back, then read and written back */
static void check_options_add_order_refresh_message(void) {
  OptionsAddOrderRefreshMessage sent;
  OptionsAddOrderRefreshMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_options_add_order_refresh_message(&sent);
  assert(encode_options_add_order_refresh_message(&sent, wire, 0) == 40);
  assert(decode_options_add_order_refresh_message(&got, wire, 0) == 40);
  equal_options_add_order_refresh_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_options_add_order_refresh_message(&got, wire, 0) == 40);
  assert(encode_options_add_order_refresh_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Series Rfq Message: 40 bytes ------------------------------------ */

/* Published for outright series. Generated by the matching engine to solicit interest in an auction or order. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_time_ns[4];  /* bytes 4 to 7 */
  uint8_t series_index[4];    /* bytes 8 to 11 */
  uint8_t series_seq_num[4];  /* bytes 12 to 15 */
  uint8_t rfq_side;           /* byte 16 */
  uint8_t type;               /* byte 17 */
  uint8_t capacity;           /* byte 18 */
  uint8_t total_quantity[4];  /* bytes 19 to 22 */
  uint8_t working_price[4];   /* bytes 23 to 26 */
  uint8_t participant[4];     /* bytes 27 to 30 */
  uint8_t auction_id[8];      /* bytes 31 to 38 */
  uint8_t rfq_status;         /* byte 39 */
} OptionsSeriesRfqMessage;

/* any Options Series Rfq Message at all: every byte one the checker chooses */
static void any_options_series_rfq_message(OptionsSeriesRfqMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = arbitrary(); }
  record->rfq_side = arbitrary();
  record->type = arbitrary();
  record->capacity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->total_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->working_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->participant[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = arbitrary(); }
  record->rfq_status = arbitrary();
}

/* Options Series Rfq Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_options_series_rfq_message(const OptionsSeriesRfqMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_seq_num[i]; }
  wire[at++] = record->rfq_side;
  wire[at++] = record->type;
  wire[at++] = record->capacity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->working_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_id[i]; }
  wire[at++] = record->rfq_status;

  return at;
}

/* Options Series Rfq Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_options_series_rfq_message(OptionsSeriesRfqMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = wire[at++]; }
  record->rfq_side = wire[at++];
  record->type = wire[at++];
  record->capacity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->total_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->working_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->participant[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = wire[at++]; }
  record->rfq_status = wire[at++];

  return at;
}

/* what was read of Options Series Rfq Message is what was written, byte for byte */
static void equal_options_series_rfq_message(const OptionsSeriesRfqMessage *read, const OptionsSeriesRfqMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_seq_num[i] == written->series_seq_num[i]); }
  assert(read->rfq_side == written->rfq_side);
  assert(read->type == written->type);
  assert(read->capacity == written->capacity);
  for (size_t i = 0; i < 4; i++) { assert(read->total_quantity[i] == written->total_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->working_price[i] == written->working_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->participant[i] == written->participant[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  assert(read->rfq_status == written->rfq_status);
}

/* Options Series Rfq Message: written and read back, then read and written back */
static void check_options_series_rfq_message(void) {
  OptionsSeriesRfqMessage sent;
  OptionsSeriesRfqMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_options_series_rfq_message(&sent);
  assert(encode_options_series_rfq_message(&sent, wire, 0) == 40);
  assert(decode_options_series_rfq_message(&got, wire, 0) == 40);
  equal_options_series_rfq_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_options_series_rfq_message(&got, wire, 0) == 40);
  assert(encode_options_series_rfq_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Non Displayed Trade Message: 30 bytes --------------------------- */

/* Published as a result of a match between two non-displayed orders. */
typedef struct {
  uint8_t source_time_ns[4];                 /* bytes 0 to 3 */
  uint8_t series_index[4];                   /* bytes 4 to 7 */
  uint8_t series_seq_num[4];                 /* bytes 8 to 11 */
  uint8_t trade_id[4];                       /* bytes 12 to 15 */
  uint8_t price[4];                          /* bytes 16 to 19 */
  uint8_t volume[4];                         /* bytes 20 to 23 */
  uint8_t printable_flag;                    /* byte 24 */
  uint8_t non_displayed_trade_trade_cond_1;  /* byte 25 */
  uint8_t reserved_3[3];                     /* bytes 26 to 28 */
  uint8_t price_type;                        /* byte 29 */
} OptionsNonDisplayedTradeMessage;

/* any Options Non Displayed Trade Message at all: every byte one the checker chooses */
static void any_options_non_displayed_trade_message(OptionsNonDisplayedTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->printable_flag = arbitrary();
  record->non_displayed_trade_trade_cond_1 = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
  record->price_type = arbitrary();
}

/* Options Non Displayed Trade Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_options_non_displayed_trade_message(const OptionsNonDisplayedTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->printable_flag;
  wire[at++] = record->non_displayed_trade_trade_cond_1;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }
  wire[at++] = record->price_type;

  return at;
}

/* Options Non Displayed Trade Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_options_non_displayed_trade_message(OptionsNonDisplayedTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->printable_flag = wire[at++];
  record->non_displayed_trade_trade_cond_1 = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }
  record->price_type = wire[at++];

  return at;
}

/* what was read of Options Non Displayed Trade Message is what was written, byte for byte */
static void equal_options_non_displayed_trade_message(const OptionsNonDisplayedTradeMessage *read, const OptionsNonDisplayedTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_seq_num[i] == written->series_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->printable_flag == written->printable_flag);
  assert(read->non_displayed_trade_trade_cond_1 == written->non_displayed_trade_trade_cond_1);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
  assert(read->price_type == written->price_type);
}

/* Options Non Displayed Trade Message: written and read back, then read and written back */
static void check_options_non_displayed_trade_message(void) {
  OptionsNonDisplayedTradeMessage sent;
  OptionsNonDisplayedTradeMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_options_non_displayed_trade_message(&sent);
  assert(encode_options_non_displayed_trade_message(&sent, wire, 0) == 30);
  assert(decode_options_non_displayed_trade_message(&got, wire, 0) == 30);
  equal_options_non_displayed_trade_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_options_non_displayed_trade_message(&got, wire, 0) == 30);
  assert(encode_options_non_displayed_trade_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Cross Trade Message: 25 bytes ----------------------------------- */

/* Published on completion of a crossing from the opening and re-opening auction, showing the bulk volume that traded in the auction. */
typedef struct {
  uint8_t source_time_ns[4];  /* bytes 0 to 3 */
  uint8_t series_index[4];    /* bytes 4 to 7 */
  uint8_t series_seq_num[4];  /* bytes 8 to 11 */
  uint8_t cross_id[4];        /* bytes 12 to 15 */
  uint8_t price[4];           /* bytes 16 to 19 */
  uint8_t volume[4];          /* bytes 20 to 23 */
  uint8_t cross_type;         /* byte 24 */
} OptionsCrossTradeMessage;

/* any Options Cross Trade Message at all: every byte one the checker chooses */
static void any_options_cross_trade_message(OptionsCrossTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->cross_type = arbitrary();
}

/* Options Cross Trade Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_options_cross_trade_message(const OptionsCrossTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->cross_type;

  return at;
}

/* Options Cross Trade Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_options_cross_trade_message(OptionsCrossTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->cross_type = wire[at++];

  return at;
}

/* what was read of Options Cross Trade Message is what was written, byte for byte */
static void equal_options_cross_trade_message(const OptionsCrossTradeMessage *read, const OptionsCrossTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_seq_num[i] == written->series_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->cross_type == written->cross_type);
}

/* Options Cross Trade Message: written and read back, then read and written back */
static void check_options_cross_trade_message(void) {
  OptionsCrossTradeMessage sent;
  OptionsCrossTradeMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_options_cross_trade_message(&sent);
  assert(encode_options_cross_trade_message(&sent, wire, 0) == 25);
  assert(decode_options_cross_trade_message(&got, wire, 0) == 25);
  equal_options_cross_trade_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_options_cross_trade_message(&got, wire, 0) == 25);
  assert(encode_options_cross_trade_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Trade Cancel Message: 16 bytes ---------------------------------- */

/* Published when an earlier trade has been reported in error. */
typedef struct {
  uint8_t source_time_ns[4];  /* bytes 0 to 3 */
  uint8_t series_index[4];    /* bytes 4 to 7 */
  uint8_t series_seq_num[4];  /* bytes 8 to 11 */
  uint8_t trade_id[4];        /* bytes 12 to 15 */
} OptionsTradeCancelMessage;

/* any Options Trade Cancel Message at all: every byte one the checker chooses */
static void any_options_trade_cancel_message(OptionsTradeCancelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
}

/* Options Trade Cancel Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_options_trade_cancel_message(const OptionsTradeCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }

  return at;
}

/* Options Trade Cancel Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_options_trade_cancel_message(OptionsTradeCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }

  return at;
}

/* what was read of Options Trade Cancel Message is what was written, byte for byte */
static void equal_options_trade_cancel_message(const OptionsTradeCancelMessage *read, const OptionsTradeCancelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_seq_num[i] == written->series_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
}

/* Options Trade Cancel Message: written and read back, then read and written back */
static void check_options_trade_cancel_message(void) {
  OptionsTradeCancelMessage sent;
  OptionsTradeCancelMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_options_trade_cancel_message(&sent);
  assert(encode_options_trade_cancel_message(&sent, wire, 0) == 16);
  assert(decode_options_trade_cancel_message(&got, wire, 0) == 16);
  equal_options_trade_cancel_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_options_trade_cancel_message(&got, wire, 0) == 16);
  assert(encode_options_trade_cancel_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Options Outright Series Summary Message: 32 bytes ----------------------- */

/* Published every 60 seconds on a separate multicast channel. Provides high, low, open, close and total volume per series. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_time_ns[4];  /* bytes 4 to 7 */
  uint8_t series_index[4];    /* bytes 8 to 11 */
  uint8_t high_price[4];      /* bytes 12 to 15 */
  uint8_t low_price[4];       /* bytes 16 to 19 */
  uint8_t open[4];            /* bytes 20 to 23 */
  uint8_t close[4];           /* bytes 24 to 27 */
  uint8_t total_volume[4];    /* bytes 28 to 31 */
} OptionsOutrightSeriesSummaryMessage;

/* any Options Outright Series Summary Message at all: every byte one the checker chooses */
static void any_options_outright_series_summary_message(OptionsOutrightSeriesSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->close[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = arbitrary(); }
}

/* Options Outright Series Summary Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_options_outright_series_summary_message(const OptionsOutrightSeriesSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->close[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_volume[i]; }

  return at;
}

/* Options Outright Series Summary Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_options_outright_series_summary_message(OptionsOutrightSeriesSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->close[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Options Outright Series Summary Message is what was written, byte for byte */
static void equal_options_outright_series_summary_message(const OptionsOutrightSeriesSummaryMessage *read, const OptionsOutrightSeriesSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open[i] == written->open[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->close[i] == written->close[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
}

/* Options Outright Series Summary Message: written and read back, then read and written back */
static void check_options_outright_series_summary_message(void) {
  OptionsOutrightSeriesSummaryMessage sent;
  OptionsOutrightSeriesSummaryMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_options_outright_series_summary_message(&sent);
  assert(encode_options_outright_series_summary_message(&sent, wire, 0) == 32);
  assert(decode_options_outright_series_summary_message(&got, wire, 0) == 32);
  equal_options_outright_series_summary_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_options_outright_series_summary_message(&got, wire, 0) == 32);
  assert(encode_options_outright_series_summary_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_send_time();
  check_packet_header();
  check_message_header();
  check_sequence_number_reset_message();
  check_source_time_reference_message();
  check_symbol_index_mapping_message();
  check_symbol_clear_message();
  check_security_status_message();
  check_outright_series_index_mapping_message();
  check_options_status_message();
  check_retransmission_request_message();
  check_refresh_request_message();
  check_symbol_index_mapping_request_message();
  check_message_unavailable_message();
  check_request_response_message();
  check_heartbeat_response_message();
  check_options_add_order_message();
  check_options_modify_order_message();
  check_options_delete_order_message();
  check_options_order_execution_message();
  check_options_replace_order_message();
  check_options_imbalance_message();
  check_options_add_order_refresh_message();
  check_options_series_rfq_message();
  check_options_non_displayed_trade_message();
  check_options_cross_trade_message();
  check_options_trade_cancel_message();
  check_options_outright_series_summary_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
