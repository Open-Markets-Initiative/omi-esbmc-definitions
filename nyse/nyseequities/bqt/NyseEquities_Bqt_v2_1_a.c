// nyse/nyseequities/bqt/NyseEquities_Bqt_v2_1_a.c
/*
 * New York Stock Exchange Best Quote And Trade
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
 *   - a run filling what frames it
 *   - a field read in bits
 *   - a field present only on a condition
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

typedef struct {
  uint8_t packet_size[2];      /* bytes 0 to 1 */
  uint8_t delivery_flag;       /* byte 2 */
  uint8_t message_count;       /* byte 3 */
  uint8_t sequence_number[4];  /* bytes 4 to 7 */
  SendTime send_time;          /* bytes 8 to 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_size[i] = arbitrary(); }
  record->delivery_flag = arbitrary();
  record->message_count = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  any_send_time(&record->send_time);
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_size[i]; }
  wire[at++] = record->delivery_flag;
  wire[at++] = record->message_count;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  at = encode_send_time(&record->send_time, wire, at);

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_size[i] = wire[at++]; }
  record->delivery_flag = wire[at++];
  record->message_count = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  at = decode_send_time(&record->send_time, wire, at);

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_size[i] == written->packet_size[i]); }
  assert(read->delivery_flag == written->delivery_flag);
  assert(read->message_count == written->message_count);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
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

/* This message is published over the real-time data channels at system startup or in the context of a refresh sequence after a Matching Engine or XDP Publisher failover. It provides referential data for a single specified symbol. */
typedef struct {
  uint8_t symbol_index[4];       /* bytes 0 to 3 */
  uint8_t symbol[11];            /* bytes 4 to 14 */
  uint8_t reserved_binary_1;     /* byte 15 */
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
  uint8_t reserved_binary_2[2];  /* bytes 38 to 39 */
} SymbolIndexMappingMessage;

/* any Symbol Index Mapping Message at all: every byte one the checker chooses */
static void any_symbol_index_mapping_message(SymbolIndexMappingMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = arbitrary(); }
  record->reserved_binary_1 = arbitrary();
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
  for (size_t i = 0; i < 2; i++) { record->reserved_binary_2[i] = arbitrary(); }
}

/* Symbol Index Mapping Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_symbol_index_mapping_message(const SymbolIndexMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->reserved_binary_1;
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
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_binary_2[i]; }

  return at;
}

/* Symbol Index Mapping Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_symbol_index_mapping_message(SymbolIndexMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->symbol[i] = wire[at++]; }
  record->reserved_binary_1 = wire[at++];
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
  for (size_t i = 0; i < 2; i++) { record->reserved_binary_2[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Index Mapping Message is what was written, byte for byte */
static void equal_symbol_index_mapping_message(const SymbolIndexMappingMessage *read, const SymbolIndexMappingMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->reserved_binary_1 == written->reserved_binary_1);
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
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_binary_2[i] == written->reserved_binary_2[i]); }
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

/* ---- Retransmission Request Message: 20 bytes -------------------------------- */

/* Clients who have experienced a sequence number gap and need a retransmission of the missed messages should send a Retransmission Request message via TCP to the Request Controller. A Request Response message will be sent over the TCP connection back to the client, and if the request was valid, the requested message(s) will be re-published over the relevant Retransmission multicast channel. */
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

/* ---- Request Response Message: 25 bytes -------------------------------------- */

/* This message will be sent immediately via TCP/IP in response to the client’s request for retransmission, refresh or Symbol Mapping messages. */
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

/* Clients who remain connected to the Retransmission Server intraday must respond to a Heartbeat with a Heartbeat Response message within 5 seconds. If no timely client response is received, the connection will be closed. */
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

/* ---- Symbol Index Mapping Request Message: 17 bytes -------------------------- */

/* This message is sent by clients via TCP/IP requesting the Symbol Index Mapping messages for one or all symbols in a specified channel. */
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

/* ---- Refresh Request Message: 16 bytes --------------------------------------- */

/* Clients who have experienced a failure and need a refresh of the state of one or all symbols in a specific channel should send a Retransmission Request message via TCP to the Request Controller. A Request Response message will be sent over the TCP connection back to the client, and if the request was valid, the requested message(s) will be published over the relevant Refresh multicast channel. */
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

/* ---- Message Unavailable Message: 10 bytes ----------------------------------- */

/* This message will be sent over the Retransmission multicast channels to inform clients of unavailability of a range of messages (or part of a range) for which they may have requested a retransmission. */
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

/* ---- Consolidated Symbol Clear Message: 18 bytes ----------------------------- */

/* In case of a failure and recovery of a Matching Engine or an XDP Publisher, the publisher may send a full state refresh for every symbol affected. This kind of unrequested refresh is preceded by a Symbol Clear message. The client should react to receipt of a Symbol Clear message by clearing all state information for the specified symbol in anticipation of receiving a full state refresh. */
typedef struct {
  uint8_t source_time[4];          /* bytes 0 to 3 */
  uint8_t source_time_ns[4];       /* bytes 4 to 7 */
  uint8_t symbol_index[4];         /* bytes 8 to 11 */
  uint8_t next_source_seq_num[4];  /* bytes 12 to 15 */
  uint8_t market_id[2];            /* bytes 16 to 17 */
} ConsolidatedSymbolClearMessage;

/* any Consolidated Symbol Clear Message at all: every byte one the checker chooses */
static void any_consolidated_symbol_clear_message(ConsolidatedSymbolClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->next_source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = arbitrary(); }
}

/* Consolidated Symbol Clear Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_symbol_clear_message(const ConsolidatedSymbolClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_source_seq_num[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id[i]; }

  return at;
}

/* Consolidated Symbol Clear Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_symbol_clear_message(ConsolidatedSymbolClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->next_source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = wire[at++]; }

  return at;
}

/* what was read of Consolidated Symbol Clear Message is what was written, byte for byte */
static void equal_consolidated_symbol_clear_message(const ConsolidatedSymbolClearMessage *read, const ConsolidatedSymbolClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->next_source_seq_num[i] == written->next_source_seq_num[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_id[i] == written->market_id[i]); }
}

/* Consolidated Symbol Clear Message: written and read back, then read and written back */
static void check_consolidated_symbol_clear_message(void) {
  ConsolidatedSymbolClearMessage sent;
  ConsolidatedSymbolClearMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_consolidated_symbol_clear_message(&sent);
  assert(encode_consolidated_symbol_clear_message(&sent, wire, 0) == 18);
  assert(decode_consolidated_symbol_clear_message(&got, wire, 0) == 18);
  equal_consolidated_symbol_clear_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_symbol_clear_message(&got, wire, 0) == 18);
  assert(encode_consolidated_symbol_clear_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Security Status Message: 42 bytes -------------------------- */

/* This message informs clients of changes in the status of a specific security, such as Trading Halts, Short Sale Restriction state changes, etc. */
typedef struct {
  uint8_t source_time[4];              /* bytes 0 to 3 */
  uint8_t source_time_ns[4];           /* bytes 4 to 7 */
  uint8_t symbol_index[4];             /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];           /* bytes 12 to 15 */
  uint8_t security_status;             /* byte 16 */
  uint8_t halt_condition;              /* byte 17 */
  uint8_t market_id[2];                /* bytes 18 to 19 */
  uint8_t reserved_binary_2[2];        /* bytes 20 to 21 */
  uint8_t price_1[4];                  /* bytes 22 to 25 */
  uint8_t price_2[4];                  /* bytes 26 to 29 */
  uint8_t ssr_triggering_exchange_id;  /* byte 30 */
  uint8_t ssr_triggering_volume[4];    /* bytes 31 to 34 */
  uint8_t time[4];                     /* bytes 35 to 38 */
  uint8_t ssr_state;                   /* byte 39 */
  uint8_t market_state;                /* byte 40 */
  uint8_t session_state;               /* byte 41 */
} ConsolidatedSecurityStatusMessage;

/* any Consolidated Security Status Message at all: every byte one the checker chooses */
static void any_consolidated_security_status_message(ConsolidatedSecurityStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  record->security_status = arbitrary();
  record->halt_condition = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_binary_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_2[i] = arbitrary(); }
  record->ssr_triggering_exchange_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->ssr_triggering_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  record->ssr_state = arbitrary();
  record->market_state = arbitrary();
  record->session_state = arbitrary();
}

/* Consolidated Security Status Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_security_status_message(const ConsolidatedSecurityStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  wire[at++] = record->security_status;
  wire[at++] = record->halt_condition;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_binary_2[i]; }
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

/* Consolidated Security Status Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_security_status_message(ConsolidatedSecurityStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  record->security_status = wire[at++];
  record->halt_condition = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_binary_2[i] = wire[at++]; }
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

/* what was read of Consolidated Security Status Message is what was written, byte for byte */
static void equal_consolidated_security_status_message(const ConsolidatedSecurityStatusMessage *read, const ConsolidatedSecurityStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  assert(read->security_status == written->security_status);
  assert(read->halt_condition == written->halt_condition);
  for (size_t i = 0; i < 2; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_binary_2[i] == written->reserved_binary_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_1[i] == written->price_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_2[i] == written->price_2[i]); }
  assert(read->ssr_triggering_exchange_id == written->ssr_triggering_exchange_id);
  for (size_t i = 0; i < 4; i++) { assert(read->ssr_triggering_volume[i] == written->ssr_triggering_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  assert(read->ssr_state == written->ssr_state);
  assert(read->market_state == written->market_state);
  assert(read->session_state == written->session_state);
}

/* Consolidated Security Status Message: written and read back, then read and written back */
static void check_consolidated_security_status_message(void) {
  ConsolidatedSecurityStatusMessage sent;
  ConsolidatedSecurityStatusMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_consolidated_security_status_message(&sent);
  assert(encode_consolidated_security_status_message(&sent, wire, 0) == 42);
  assert(decode_consolidated_security_status_message(&got, wire, 0) == 42);
  equal_consolidated_security_status_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_security_status_message(&got, wire, 0) == 42);
  assert(encode_consolidated_security_status_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bqt Message: 31 bytes --------------------------------------------------- */

/* This message is sent when an event causes a change in one or both sides of the BBO. */
typedef struct {
  uint8_t symbol_index[4];           /* bytes 0 to 3 */
  uint8_t symbol_seq_number[4];      /* bytes 4 to 7 */
  uint8_t ask_price[4];              /* bytes 8 to 11 */
  uint8_t ask_volume[4];             /* bytes 12 to 15 */
  uint8_t bid_price[4];              /* bytes 16 to 19 */
  uint8_t bid_volume[4];             /* bytes 20 to 23 */
  uint8_t ask_quote_condition;       /* byte 24 */
  uint8_t bid_quote_condition;       /* byte 25 */
  uint8_t retail_pricing_indicator;  /* byte 26 */
  uint8_t market_id_of_best_ask[2];  /* bytes 27 to 28 */
  uint8_t market_id_of_best_bid[2];  /* bytes 29 to 30 */
} BqtMessage;

/* any Bqt Message at all: every byte one the checker chooses */
static void any_bqt_message(BqtMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_volume[i] = arbitrary(); }
  record->ask_quote_condition = arbitrary();
  record->bid_quote_condition = arbitrary();
  record->retail_pricing_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->market_id_of_best_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_id_of_best_bid[i] = arbitrary(); }
}

/* Bqt Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_bqt_message(const BqtMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_volume[i]; }
  wire[at++] = record->ask_quote_condition;
  wire[at++] = record->bid_quote_condition;
  wire[at++] = record->retail_pricing_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id_of_best_ask[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id_of_best_bid[i]; }

  return at;
}

/* Bqt Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_bqt_message(BqtMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_volume[i] = wire[at++]; }
  record->ask_quote_condition = wire[at++];
  record->bid_quote_condition = wire[at++];
  record->retail_pricing_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->market_id_of_best_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_id_of_best_bid[i] = wire[at++]; }

  return at;
}

/* what was read of Bqt Message is what was written, byte for byte */
static void equal_bqt_message(const BqtMessage *read, const BqtMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_number[i] == written->symbol_seq_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_volume[i] == written->ask_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_volume[i] == written->bid_volume[i]); }
  assert(read->ask_quote_condition == written->ask_quote_condition);
  assert(read->bid_quote_condition == written->bid_quote_condition);
  assert(read->retail_pricing_indicator == written->retail_pricing_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->market_id_of_best_ask[i] == written->market_id_of_best_ask[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_id_of_best_bid[i] == written->market_id_of_best_bid[i]); }
}

/* Bqt Message: written and read back, then read and written back */
static void check_bqt_message(void) {
  BqtMessage sent;
  BqtMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_bqt_message(&sent);
  assert(encode_bqt_message(&sent, wire, 0) == 31);
  assert(decode_bqt_message(&got, wire, 0) == 31);
  equal_bqt_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_bqt_message(&got, wire, 0) == 31);
  assert(encode_bqt_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Single Sided Quote Message: 21 bytes ----------------------- */

/* This message is sent when an event causes a change in only one side of a BBO. */
typedef struct {
  uint8_t symbol_index[4];       /* bytes 0 to 3 */
  uint8_t symbol_seq_number[4];  /* bytes 4 to 7 */
  uint8_t side;                  /* byte 8 */
  uint8_t price[4];              /* bytes 9 to 12 */
  uint8_t volume[4];             /* bytes 13 to 16 */
  uint8_t quote_condition;       /* byte 17 */
  uint8_t rpi_indicator;         /* byte 18 */
  uint8_t market_id[2];          /* bytes 19 to 20 */
} ConsolidatedSingleSidedQuoteMessage;

/* any Consolidated Single Sided Quote Message at all: every byte one the checker chooses */
static void any_consolidated_single_sided_quote_message(ConsolidatedSingleSidedQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_number[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->quote_condition = arbitrary();
  record->rpi_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = arbitrary(); }
}

/* Consolidated Single Sided Quote Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_single_sided_quote_message(const ConsolidatedSingleSidedQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_number[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->quote_condition;
  wire[at++] = record->rpi_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id[i]; }

  return at;
}

/* Consolidated Single Sided Quote Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_single_sided_quote_message(ConsolidatedSingleSidedQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_number[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->quote_condition = wire[at++];
  record->rpi_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = wire[at++]; }

  return at;
}

/* what was read of Consolidated Single Sided Quote Message is what was written, byte for byte */
static void equal_consolidated_single_sided_quote_message(const ConsolidatedSingleSidedQuoteMessage *read, const ConsolidatedSingleSidedQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_number[i] == written->symbol_seq_number[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->quote_condition == written->quote_condition);
  assert(read->rpi_indicator == written->rpi_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->market_id[i] == written->market_id[i]); }
}

/* Consolidated Single Sided Quote Message: written and read back, then read and written back */
static void check_consolidated_single_sided_quote_message(void) {
  ConsolidatedSingleSidedQuoteMessage sent;
  ConsolidatedSingleSidedQuoteMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_consolidated_single_sided_quote_message(&sent);
  assert(encode_consolidated_single_sided_quote_message(&sent, wire, 0) == 21);
  assert(decode_consolidated_single_sided_quote_message(&got, wire, 0) == 21);
  equal_consolidated_single_sided_quote_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_single_sided_quote_message(&got, wire, 0) == 21);
  assert(encode_consolidated_single_sided_quote_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Trade Message: 34 bytes ------------------------------------ */

/* The Trade messages provided on the Trades feed are the same Trade messages provided to the Cta. All Trades are passed through and marked with the originating Market ID. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_time_ns[4];  /* bytes 4 to 7 */
  uint8_t symbol_index[4];    /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];  /* bytes 12 to 15 */
  uint8_t trade_id[4];        /* bytes 16 to 19 */
  uint8_t price[4];           /* bytes 20 to 23 */
  uint8_t volume[4];          /* bytes 24 to 27 */
  uint8_t trade_condition_1;  /* byte 28 */
  uint8_t trade_condition_2;  /* byte 29 */
  uint8_t trade_condition_3;  /* byte 30 */
  uint8_t trade_condition_4;  /* byte 31 */
  uint8_t market_id[2];       /* bytes 32 to 33 */
} ConsolidatedTradeMessage;

/* any Consolidated Trade Message at all: every byte one the checker chooses */
static void any_consolidated_trade_message(ConsolidatedTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->trade_condition_1 = arbitrary();
  record->trade_condition_2 = arbitrary();
  record->trade_condition_3 = arbitrary();
  record->trade_condition_4 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = arbitrary(); }
}

/* Consolidated Trade Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_trade_message(const ConsolidatedTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->trade_condition_1;
  wire[at++] = record->trade_condition_2;
  wire[at++] = record->trade_condition_3;
  wire[at++] = record->trade_condition_4;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id[i]; }

  return at;
}

/* Consolidated Trade Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_trade_message(ConsolidatedTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->trade_condition_1 = wire[at++];
  record->trade_condition_2 = wire[at++];
  record->trade_condition_3 = wire[at++];
  record->trade_condition_4 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = wire[at++]; }

  return at;
}

/* what was read of Consolidated Trade Message is what was written, byte for byte */
static void equal_consolidated_trade_message(const ConsolidatedTradeMessage *read, const ConsolidatedTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->trade_condition_1 == written->trade_condition_1);
  assert(read->trade_condition_2 == written->trade_condition_2);
  assert(read->trade_condition_3 == written->trade_condition_3);
  assert(read->trade_condition_4 == written->trade_condition_4);
  for (size_t i = 0; i < 2; i++) { assert(read->market_id[i] == written->market_id[i]); }
}

/* Consolidated Trade Message: written and read back, then read and written back */
static void check_consolidated_trade_message(void) {
  ConsolidatedTradeMessage sent;
  ConsolidatedTradeMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_consolidated_trade_message(&sent);
  assert(encode_consolidated_trade_message(&sent, wire, 0) == 34);
  assert(decode_consolidated_trade_message(&got, wire, 0) == 34);
  equal_consolidated_trade_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_trade_message(&got, wire, 0) == 34);
  assert(encode_consolidated_trade_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Trade Cancel Message: 22 bytes ----------------------------- */

/* This message is sent when a trade is cancelled */
typedef struct {
  uint8_t source_time[4];        /* bytes 0 to 3 */
  uint8_t source_time_ns[4];     /* bytes 4 to 7 */
  uint8_t symbol_index[4];       /* bytes 8 to 11 */
  uint8_t symbol_seq_number[4];  /* bytes 12 to 15 */
  uint8_t trade_id[4];           /* bytes 16 to 19 */
  uint8_t market_id[2];          /* bytes 20 to 21 */
} ConsolidatedTradeCancelMessage;

/* any Consolidated Trade Cancel Message at all: every byte one the checker chooses */
static void any_consolidated_trade_cancel_message(ConsolidatedTradeCancelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = arbitrary(); }
}

/* Consolidated Trade Cancel Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_trade_cancel_message(const ConsolidatedTradeCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id[i]; }

  return at;
}

/* Consolidated Trade Cancel Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_trade_cancel_message(ConsolidatedTradeCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = wire[at++]; }

  return at;
}

/* what was read of Consolidated Trade Cancel Message is what was written, byte for byte */
static void equal_consolidated_trade_cancel_message(const ConsolidatedTradeCancelMessage *read, const ConsolidatedTradeCancelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_number[i] == written->symbol_seq_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_id[i] == written->market_id[i]); }
}

/* Consolidated Trade Cancel Message: written and read back, then read and written back */
static void check_consolidated_trade_cancel_message(void) {
  ConsolidatedTradeCancelMessage sent;
  ConsolidatedTradeCancelMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_consolidated_trade_cancel_message(&sent);
  assert(encode_consolidated_trade_cancel_message(&sent, wire, 0) == 22);
  assert(decode_consolidated_trade_cancel_message(&got, wire, 0) == 22);
  equal_consolidated_trade_cancel_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_trade_cancel_message(&got, wire, 0) == 22);
  assert(encode_consolidated_trade_cancel_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Trade Correction Message: 38 bytes ------------------------- */

/* This message is sent when a trade is corrected */
typedef struct {
  uint8_t source_time[4];        /* bytes 0 to 3 */
  uint8_t source_time_ns[4];     /* bytes 4 to 7 */
  uint8_t symbol_index[4];       /* bytes 8 to 11 */
  uint8_t symbol_seq_number[4];  /* bytes 12 to 15 */
  uint8_t original_trade_id[4];  /* bytes 16 to 19 */
  uint8_t trade_id[4];           /* bytes 20 to 23 */
  uint8_t price[4];              /* bytes 24 to 27 */
  uint8_t volume[4];             /* bytes 28 to 31 */
  uint8_t trade_condition_1;     /* byte 32 */
  uint8_t trade_condition_2;     /* byte 33 */
  uint8_t trade_condition_3;     /* byte 34 */
  uint8_t trade_condition_4;     /* byte 35 */
  uint8_t market_id[2];          /* bytes 36 to 37 */
} ConsolidatedTradeCorrectionMessage;

/* any Consolidated Trade Correction Message at all: every byte one the checker chooses */
static void any_consolidated_trade_correction_message(ConsolidatedTradeCorrectionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->trade_condition_1 = arbitrary();
  record->trade_condition_2 = arbitrary();
  record->trade_condition_3 = arbitrary();
  record->trade_condition_4 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = arbitrary(); }
}

/* Consolidated Trade Correction Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_trade_correction_message(const ConsolidatedTradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->trade_condition_1;
  wire[at++] = record->trade_condition_2;
  wire[at++] = record->trade_condition_3;
  wire[at++] = record->trade_condition_4;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id[i]; }

  return at;
}

/* Consolidated Trade Correction Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_trade_correction_message(ConsolidatedTradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->trade_condition_1 = wire[at++];
  record->trade_condition_2 = wire[at++];
  record->trade_condition_3 = wire[at++];
  record->trade_condition_4 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = wire[at++]; }

  return at;
}

/* what was read of Consolidated Trade Correction Message is what was written, byte for byte */
static void equal_consolidated_trade_correction_message(const ConsolidatedTradeCorrectionMessage *read, const ConsolidatedTradeCorrectionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_number[i] == written->symbol_seq_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_id[i] == written->original_trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->trade_condition_1 == written->trade_condition_1);
  assert(read->trade_condition_2 == written->trade_condition_2);
  assert(read->trade_condition_3 == written->trade_condition_3);
  assert(read->trade_condition_4 == written->trade_condition_4);
  for (size_t i = 0; i < 2; i++) { assert(read->market_id[i] == written->market_id[i]); }
}

/* Consolidated Trade Correction Message: written and read back, then read and written back */
static void check_consolidated_trade_correction_message(void) {
  ConsolidatedTradeCorrectionMessage sent;
  ConsolidatedTradeCorrectionMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_consolidated_trade_correction_message(&sent);
  assert(encode_consolidated_trade_correction_message(&sent, wire, 0) == 38);
  assert(decode_consolidated_trade_correction_message(&got, wire, 0) == 38);
  equal_consolidated_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_trade_correction_message(&got, wire, 0) == 38);
  assert(encode_consolidated_trade_correction_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Consolidated Volume Message: 14 bytes ----------------------------------- */

/* Published on consolidated volume channels */
typedef struct {
  uint8_t symbol_index[4];       /* bytes 0 to 3 */
  uint8_t symbol_seq_number[4];  /* bytes 4 to 7 */
  uint8_t total_volume[4];       /* bytes 8 to 11 */
  uint8_t reason;                /* byte 12 */
  uint8_t complete;              /* byte 13 */
} ConsolidatedVolumeMessage;

/* any Consolidated Volume Message at all: every byte one the checker chooses */
static void any_consolidated_volume_message(ConsolidatedVolumeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = arbitrary(); }
  record->reason = arbitrary();
  record->complete = arbitrary();
}

/* Consolidated Volume Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_consolidated_volume_message(const ConsolidatedVolumeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_volume[i]; }
  wire[at++] = record->reason;
  wire[at++] = record->complete;

  return at;
}

/* Consolidated Volume Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_consolidated_volume_message(ConsolidatedVolumeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = wire[at++]; }
  record->reason = wire[at++];
  record->complete = wire[at++];

  return at;
}

/* what was read of Consolidated Volume Message is what was written, byte for byte */
static void equal_consolidated_volume_message(const ConsolidatedVolumeMessage *read, const ConsolidatedVolumeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_number[i] == written->symbol_seq_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
  assert(read->reason == written->reason);
  assert(read->complete == written->complete);
}

/* Consolidated Volume Message: written and read back, then read and written back */
static void check_consolidated_volume_message(void) {
  ConsolidatedVolumeMessage sent;
  ConsolidatedVolumeMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_consolidated_volume_message(&sent);
  assert(encode_consolidated_volume_message(&sent, wire, 0) == 14);
  assert(decode_consolidated_volume_message(&got, wire, 0) == 14);
  equal_consolidated_volume_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_consolidated_volume_message(&got, wire, 0) == 14);
  assert(encode_consolidated_volume_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_send_time();
  check_packet_header();
  check_message_header();
  check_sequence_number_reset_message();
  check_symbol_index_mapping_message();
  check_retransmission_request_message();
  check_request_response_message();
  check_heartbeat_response_message();
  check_symbol_index_mapping_request_message();
  check_refresh_request_message();
  check_message_unavailable_message();
  check_consolidated_symbol_clear_message();
  check_consolidated_security_status_message();
  check_bqt_message();
  check_consolidated_single_sided_quote_message();
  check_consolidated_trade_message();
  check_consolidated_trade_cancel_message();
  check_consolidated_trade_correction_message();
  check_consolidated_volume_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
