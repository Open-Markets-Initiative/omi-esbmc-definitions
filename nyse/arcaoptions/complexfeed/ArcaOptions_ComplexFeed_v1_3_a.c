// nyse/arcaoptions/complexfeed/ArcaOptions_ComplexFeed_v1_3_a.c
/*
 * New York Stock Exchange Complex Feed
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

/* ---- Complex Quote Message: 36 bytes ----------------------------------------- */

/* The Complex Quote message is a two-sided message providing best bid and offer limits of orders on complex symbols with aggregated volumes at each limit. */
typedef struct {
  uint8_t source_time[4];          /* bytes 0 to 3 */
  uint8_t source_time_ns[4];       /* bytes 4 to 7 */
  uint8_t complex_index[4];        /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];       /* bytes 12 to 15 */
  uint8_t ask_price[4];            /* bytes 16 to 19 */
  uint8_t bid_price[4];            /* bytes 20 to 23 */
  uint8_t ask_volume[2];           /* bytes 24 to 25 */
  uint8_t bid_volume[2];           /* bytes 26 to 27 */
  uint8_t ask_customer_volume[2];  /* bytes 28 to 29 */
  uint8_t bid_customer_volume[2];  /* bytes 30 to 31 */
  uint8_t quote_condition;         /* byte 32 */
  uint8_t reserved_1;              /* byte 33 */
  uint8_t reserved_2[2];           /* bytes 34 to 35 */
} ComplexQuoteMessage;

/* any Complex Quote Message at all: every byte one the checker chooses */
static void any_complex_quote_message(ComplexQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->complex_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_customer_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_customer_volume[i] = arbitrary(); }
  record->quote_condition = arbitrary();
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Complex Quote Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_complex_quote_message(const ComplexQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->complex_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_customer_volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_customer_volume[i]; }
  wire[at++] = record->quote_condition;
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Complex Quote Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_complex_quote_message(ComplexQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->complex_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_customer_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_customer_volume[i] = wire[at++]; }
  record->quote_condition = wire[at++];
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Quote Message is what was written, byte for byte */
static void equal_complex_quote_message(const ComplexQuoteMessage *read, const ComplexQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->complex_index[i] == written->complex_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_volume[i] == written->ask_volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_volume[i] == written->bid_volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_customer_volume[i] == written->ask_customer_volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_customer_volume[i] == written->bid_customer_volume[i]); }
  assert(read->quote_condition == written->quote_condition);
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Complex Quote Message: written and read back, then read and written back */
static void check_complex_quote_message(void) {
  ComplexQuoteMessage sent;
  ComplexQuoteMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_complex_quote_message(&sent);
  assert(encode_complex_quote_message(&sent, wire, 0) == 36);
  assert(decode_complex_quote_message(&got, wire, 0) == 36);
  equal_complex_quote_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_quote_message(&got, wire, 0) == 36);
  assert(encode_complex_quote_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Trade Message: 32 bytes ----------------------------------------- */

/* The Complex Trade message is used to publish all complex Last Sales. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_time_ns[4];  /* bytes 4 to 7 */
  uint8_t complex_index[4];   /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];  /* bytes 12 to 15 */
  uint8_t trade_id[4];        /* bytes 16 to 19 */
  uint8_t price[4];           /* bytes 20 to 23 */
  uint8_t volume_4[4];        /* bytes 24 to 27 */
  uint8_t trade_cond_1;       /* byte 28 */
  uint8_t trade_cond_2;       /* byte 29 */
  uint8_t reserved_2[2];      /* bytes 30 to 31 */
} ComplexTradeMessage;

/* any Complex Trade Message at all: every byte one the checker chooses */
static void any_complex_trade_message(ComplexTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->complex_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_4[i] = arbitrary(); }
  record->trade_cond_1 = arbitrary();
  record->trade_cond_2 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Complex Trade Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_complex_trade_message(const ComplexTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->complex_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_4[i]; }
  wire[at++] = record->trade_cond_1;
  wire[at++] = record->trade_cond_2;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Complex Trade Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_complex_trade_message(ComplexTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->complex_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_4[i] = wire[at++]; }
  record->trade_cond_1 = wire[at++];
  record->trade_cond_2 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Trade Message is what was written, byte for byte */
static void equal_complex_trade_message(const ComplexTradeMessage *read, const ComplexTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->complex_index[i] == written->complex_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_4[i] == written->volume_4[i]); }
  assert(read->trade_cond_1 == written->trade_cond_1);
  assert(read->trade_cond_2 == written->trade_cond_2);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Complex Trade Message: written and read back, then read and written back */
static void check_complex_trade_message(void) {
  ComplexTradeMessage sent;
  ComplexTradeMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_complex_trade_message(&sent);
  assert(encode_complex_trade_message(&sent, wire, 0) == 32);
  assert(decode_complex_trade_message(&got, wire, 0) == 32);
  equal_complex_trade_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_trade_message(&got, wire, 0) == 32);
  assert(encode_complex_trade_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Crossing Rfq Message: 24 bytes ---------------------------------- */

/* The Complex Crossing RFQ (Request for Quote) message is sent out in the event of a COA auction on a complex order. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_ns[4];       /* bytes 4 to 7 */
  uint8_t complex_index[4];   /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];  /* bytes 12 to 15 */
  uint8_t side;               /* byte 16 */
  uint8_t reserved_1;         /* byte 17 */
  uint8_t volume_2[2];        /* bytes 18 to 19 */
  uint8_t price[4];           /* bytes 20 to 23 */
} ComplexCrossingRfqMessage;

/* any Complex Crossing Rfq Message at all: every byte one the checker chooses */
static void any_complex_crossing_rfq_message(ComplexCrossingRfqMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->complex_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  record->side = arbitrary();
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->volume_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Complex Crossing Rfq Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_complex_crossing_rfq_message(const ComplexCrossingRfqMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->complex_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  wire[at++] = record->side;
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->volume_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Complex Crossing Rfq Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_complex_crossing_rfq_message(ComplexCrossingRfqMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->complex_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  record->side = wire[at++];
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->volume_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Crossing Rfq Message is what was written, byte for byte */
static void equal_complex_crossing_rfq_message(const ComplexCrossingRfqMessage *read, const ComplexCrossingRfqMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_ns[i] == written->source_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->complex_index[i] == written->complex_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  assert(read->side == written->side);
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->volume_2[i] == written->volume_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Complex Crossing Rfq Message: written and read back, then read and written back */
static void check_complex_crossing_rfq_message(void) {
  ComplexCrossingRfqMessage sent;
  ComplexCrossingRfqMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_complex_crossing_rfq_message(&sent);
  assert(encode_complex_crossing_rfq_message(&sent, wire, 0) == 24);
  assert(decode_complex_crossing_rfq_message(&got, wire, 0) == 24);
  equal_complex_crossing_rfq_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_crossing_rfq_message(&got, wire, 0) == 24);
  assert(encode_complex_crossing_rfq_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Cube Rfq Message: 24 bytes -------------------------------------- */

typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_ns[4];       /* bytes 4 to 7 */
  uint8_t complex_index[4];   /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];  /* bytes 12 to 15 */
  uint8_t side;               /* byte 16 */
  uint8_t reserved_1;         /* byte 17 */
  uint8_t volume_2[2];        /* bytes 18 to 19 */
  uint8_t price[4];           /* bytes 20 to 23 */
} ComplexCubeRfqMessage;

/* any Complex Cube Rfq Message at all: every byte one the checker chooses */
static void any_complex_cube_rfq_message(ComplexCubeRfqMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->complex_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  record->side = arbitrary();
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->volume_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Complex Cube Rfq Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_complex_cube_rfq_message(const ComplexCubeRfqMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->complex_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  wire[at++] = record->side;
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->volume_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Complex Cube Rfq Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_complex_cube_rfq_message(ComplexCubeRfqMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->complex_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  record->side = wire[at++];
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->volume_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Cube Rfq Message is what was written, byte for byte */
static void equal_complex_cube_rfq_message(const ComplexCubeRfqMessage *read, const ComplexCubeRfqMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_ns[i] == written->source_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->complex_index[i] == written->complex_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  assert(read->side == written->side);
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->volume_2[i] == written->volume_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Complex Cube Rfq Message: written and read back, then read and written back */
static void check_complex_cube_rfq_message(void) {
  ComplexCubeRfqMessage sent;
  ComplexCubeRfqMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_complex_cube_rfq_message(&sent);
  assert(encode_complex_cube_rfq_message(&sent, wire, 0) == 24);
  assert(decode_complex_cube_rfq_message(&got, wire, 0) == 24);
  equal_complex_cube_rfq_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_cube_rfq_message(&got, wire, 0) == 24);
  assert(encode_complex_cube_rfq_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Status Message: 20 bytes ---------------------------------------- */

/* The Complex Status message is used to inform the subscribers of changes in symbol status of a complex symbol. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_time_ns[4];  /* bytes 4 to 7 */
  uint8_t complex_index[4];   /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];  /* bytes 12 to 15 */
  uint8_t security_status;    /* byte 16 */
  uint8_t halt_condition;     /* byte 17 */
  uint8_t reserved_2[2];      /* bytes 18 to 19 */
} ComplexStatusMessage;

/* any Complex Status Message at all: every byte one the checker chooses */
static void any_complex_status_message(ComplexStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->complex_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  record->security_status = arbitrary();
  record->halt_condition = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Complex Status Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_complex_status_message(const ComplexStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->complex_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  wire[at++] = record->security_status;
  wire[at++] = record->halt_condition;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Complex Status Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_complex_status_message(ComplexStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->complex_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  record->security_status = wire[at++];
  record->halt_condition = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Status Message is what was written, byte for byte */
static void equal_complex_status_message(const ComplexStatusMessage *read, const ComplexStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->complex_index[i] == written->complex_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  assert(read->security_status == written->security_status);
  assert(read->halt_condition == written->halt_condition);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Complex Status Message: written and read back, then read and written back */
static void check_complex_status_message(void) {
  ComplexStatusMessage sent;
  ComplexStatusMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_complex_status_message(&sent);
  assert(encode_complex_status_message(&sent, wire, 0) == 20);
  assert(decode_complex_status_message(&got, wire, 0) == 20);
  equal_complex_status_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_status_message(&got, wire, 0) == 20);
  assert(encode_complex_status_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Complex Quote Message: 36 bytes --------------------------------- */

/* The Refresh Complex Quote message is sent in the event no quote messages are published for the symbol for 2 consecutive minutes. */
typedef struct {
  uint8_t source_time[4];          /* bytes 0 to 3 */
  uint8_t source_time_ns[4];       /* bytes 4 to 7 */
  uint8_t complex_index[4];        /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];       /* bytes 12 to 15 */
  uint8_t ask_price[4];            /* bytes 16 to 19 */
  uint8_t bid_price[4];            /* bytes 20 to 23 */
  uint8_t ask_volume[2];           /* bytes 24 to 25 */
  uint8_t bid_volume[2];           /* bytes 26 to 27 */
  uint8_t ask_customer_volume[2];  /* bytes 28 to 29 */
  uint8_t bid_customer_volume[2];  /* bytes 30 to 31 */
  uint8_t quote_condition;         /* byte 32 */
  uint8_t reserved_1;              /* byte 33 */
  uint8_t reserved_2[2];           /* bytes 34 to 35 */
} RefreshComplexQuoteMessage;

/* any Refresh Complex Quote Message at all: every byte one the checker chooses */
static void any_refresh_complex_quote_message(RefreshComplexQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->complex_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_customer_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_customer_volume[i] = arbitrary(); }
  record->quote_condition = arbitrary();
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Refresh Complex Quote Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_refresh_complex_quote_message(const RefreshComplexQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->complex_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_customer_volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_customer_volume[i]; }
  wire[at++] = record->quote_condition;
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Refresh Complex Quote Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_refresh_complex_quote_message(RefreshComplexQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->complex_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_customer_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_customer_volume[i] = wire[at++]; }
  record->quote_condition = wire[at++];
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Refresh Complex Quote Message is what was written, byte for byte */
static void equal_refresh_complex_quote_message(const RefreshComplexQuoteMessage *read, const RefreshComplexQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->complex_index[i] == written->complex_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_volume[i] == written->ask_volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_volume[i] == written->bid_volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_customer_volume[i] == written->ask_customer_volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_customer_volume[i] == written->bid_customer_volume[i]); }
  assert(read->quote_condition == written->quote_condition);
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Refresh Complex Quote Message: written and read back, then read and written back */
static void check_refresh_complex_quote_message(void) {
  RefreshComplexQuoteMessage sent;
  RefreshComplexQuoteMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_refresh_complex_quote_message(&sent);
  assert(encode_refresh_complex_quote_message(&sent, wire, 0) == 36);
  assert(decode_refresh_complex_quote_message(&got, wire, 0) == 36);
  equal_refresh_complex_quote_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_complex_quote_message(&got, wire, 0) == 36);
  assert(encode_refresh_complex_quote_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Complex Trade Message: 32 bytes --------------------------------- */

/* The Refresh Complex Trade message is sent in the event no Complex Trade messages are published for the symbol for 2 consecutive minutes. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_time_ns[4];  /* bytes 4 to 7 */
  uint8_t complex_index[4];   /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];  /* bytes 12 to 15 */
  uint8_t trade_id[4];        /* bytes 16 to 19 */
  uint8_t price[4];           /* bytes 20 to 23 */
  uint8_t volume_4[4];        /* bytes 24 to 27 */
  uint8_t trade_cond_1;       /* byte 28 */
  uint8_t trade_cond_2;       /* byte 29 */
  uint8_t reserved_2[2];      /* bytes 30 to 31 */
} RefreshComplexTradeMessage;

/* any Refresh Complex Trade Message at all: every byte one the checker chooses */
static void any_refresh_complex_trade_message(RefreshComplexTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->complex_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_4[i] = arbitrary(); }
  record->trade_cond_1 = arbitrary();
  record->trade_cond_2 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Refresh Complex Trade Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_refresh_complex_trade_message(const RefreshComplexTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->complex_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_4[i]; }
  wire[at++] = record->trade_cond_1;
  wire[at++] = record->trade_cond_2;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Refresh Complex Trade Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_refresh_complex_trade_message(RefreshComplexTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->complex_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_4[i] = wire[at++]; }
  record->trade_cond_1 = wire[at++];
  record->trade_cond_2 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Refresh Complex Trade Message is what was written, byte for byte */
static void equal_refresh_complex_trade_message(const RefreshComplexTradeMessage *read, const RefreshComplexTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->complex_index[i] == written->complex_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_4[i] == written->volume_4[i]); }
  assert(read->trade_cond_1 == written->trade_cond_1);
  assert(read->trade_cond_2 == written->trade_cond_2);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Refresh Complex Trade Message: written and read back, then read and written back */
static void check_refresh_complex_trade_message(void) {
  RefreshComplexTradeMessage sent;
  RefreshComplexTradeMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_refresh_complex_trade_message(&sent);
  assert(encode_refresh_complex_trade_message(&sent, wire, 0) == 32);
  assert(decode_refresh_complex_trade_message(&got, wire, 0) == 32);
  equal_refresh_complex_trade_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_complex_trade_message(&got, wire, 0) == 32);
  assert(encode_refresh_complex_trade_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stream Id Message: 4 bytes ---------------------------------------------- */

/* In all multicast channels, a Stream ID Message is sent immediately after each packet header to uniquely identify the source or Stream ID of the data in the packet. */
typedef struct {
  uint8_t stream_id[2];   /* bytes 0 to 1 */
  uint8_t reserved_2[2];  /* bytes 2 to 3 */
} StreamIdMessage;

/* any Stream Id Message at all: every byte one the checker chooses */
static void any_stream_id_message(StreamIdMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Stream Id Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_stream_id_message(const StreamIdMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stream_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Stream Id Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_stream_id_message(StreamIdMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Stream Id Message is what was written, byte for byte */
static void equal_stream_id_message(const StreamIdMessage *read, const StreamIdMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stream_id[i] == written->stream_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Stream Id Message: written and read back, then read and written back */
static void check_stream_id_message(void) {
  StreamIdMessage sent;
  StreamIdMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_stream_id_message(&sent);
  assert(encode_stream_id_message(&sent, wire, 0) == 4);
  assert(decode_stream_id_message(&got, wire, 0) == 4);
  equal_stream_id_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_stream_id_message(&got, wire, 0) == 4);
  assert(encode_stream_id_message(&got, again, 0) == 4);
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_send_time();
  check_packet_header();
  check_message_header();
  check_complex_quote_message();
  check_complex_trade_message();
  check_complex_crossing_rfq_message();
  check_complex_cube_rfq_message();
  check_complex_status_message();
  check_refresh_complex_quote_message();
  check_refresh_complex_trade_message();
  check_stream_id_message();
  check_sequence_number_reset_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
