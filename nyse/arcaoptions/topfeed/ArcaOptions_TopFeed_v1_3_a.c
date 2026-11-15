// nyse/arcaoptions/topfeed/ArcaOptions_TopFeed_v1_3_a.c
/*
 * New York Stock Exchange Top Feed
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

/* ---- Outright Quote Message: 36 bytes ---------------------------------------- */

/* The Outright Quote message provides the price and aggregated volume for the best bid and best offer. Volumes aggregate quote and order interest. The message also indicates aggregated Customer volumes within the overall volumes. */
typedef struct {
  uint8_t source_time[4];          /* bytes 0 to 3 */
  uint8_t source_time_ns[4];       /* bytes 4 to 7 */
  uint8_t series_index[4];         /* bytes 8 to 11 */
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
} OutrightQuoteMessage;

/* any Outright Quote Message at all: every byte one the checker chooses */
static void any_outright_quote_message(OutrightQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
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

/* Outright Quote Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_outright_quote_message(const OutrightQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
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

/* Outright Quote Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_outright_quote_message(OutrightQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
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

/* what was read of Outright Quote Message is what was written, byte for byte */
static void equal_outright_quote_message(const OutrightQuoteMessage *read, const OutrightQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
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

/* Outright Quote Message: written and read back, then read and written back */
static void check_outright_quote_message(void) {
  OutrightQuoteMessage sent;
  OutrightQuoteMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_outright_quote_message(&sent);
  assert(encode_outright_quote_message(&sent, wire, 0) == 36);
  assert(decode_outright_quote_message(&got, wire, 0) == 36);
  equal_outright_quote_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_outright_quote_message(&got, wire, 0) == 36);
  assert(encode_outright_quote_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Outright Trade Message: 32 bytes ---------------------------------------- */

/* The Outright Trade message is used to publish all Last Sales for outright symbols. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_time_ns[4];  /* bytes 4 to 7 */
  uint8_t series_index[4];    /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];  /* bytes 12 to 15 */
  uint8_t trade_id[4];        /* bytes 16 to 19 */
  uint8_t price[4];           /* bytes 20 to 23 */
  uint8_t volume_4[4];        /* bytes 24 to 27 */
  uint8_t trade_cond_1;       /* byte 28 */
  uint8_t trade_cond_2;       /* byte 29 */
  uint8_t reserved_2[2];      /* bytes 30 to 31 */
} OutrightTradeMessage;

/* any Outright Trade Message at all: every byte one the checker chooses */
static void any_outright_trade_message(OutrightTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_4[i] = arbitrary(); }
  record->trade_cond_1 = arbitrary();
  record->trade_cond_2 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Outright Trade Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_outright_trade_message(const OutrightTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_4[i]; }
  wire[at++] = record->trade_cond_1;
  wire[at++] = record->trade_cond_2;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Outright Trade Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_outright_trade_message(OutrightTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_4[i] = wire[at++]; }
  record->trade_cond_1 = wire[at++];
  record->trade_cond_2 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Outright Trade Message is what was written, byte for byte */
static void equal_outright_trade_message(const OutrightTradeMessage *read, const OutrightTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_4[i] == written->volume_4[i]); }
  assert(read->trade_cond_1 == written->trade_cond_1);
  assert(read->trade_cond_2 == written->trade_cond_2);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Outright Trade Message: written and read back, then read and written back */
static void check_outright_trade_message(void) {
  OutrightTradeMessage sent;
  OutrightTradeMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_outright_trade_message(&sent);
  assert(encode_outright_trade_message(&sent, wire, 0) == 32);
  assert(decode_outright_trade_message(&got, wire, 0) == 32);
  equal_outright_trade_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_outright_trade_message(&got, wire, 0) == 32);
  assert(encode_outright_trade_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Outright Trade Cancel Message: 20 bytes --------------------------------- */

/* The Trade Cancel message is used to cancel or bust a trade. */
typedef struct {
  uint8_t source_time[4];        /* bytes 0 to 3 */
  uint8_t source_time_ns[4];     /* bytes 4 to 7 */
  uint8_t series_index[4];       /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];     /* bytes 12 to 15 */
  uint8_t original_trade_id[4];  /* bytes 16 to 19 */
} OutrightTradeCancelMessage;

/* any Outright Trade Cancel Message at all: every byte one the checker chooses */
static void any_outright_trade_cancel_message(OutrightTradeCancelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_id[i] = arbitrary(); }
}

/* Outright Trade Cancel Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_outright_trade_cancel_message(const OutrightTradeCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_id[i]; }

  return at;
}

/* Outright Trade Cancel Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_outright_trade_cancel_message(OutrightTradeCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_id[i] = wire[at++]; }

  return at;
}

/* what was read of Outright Trade Cancel Message is what was written, byte for byte */
static void equal_outright_trade_cancel_message(const OutrightTradeCancelMessage *read, const OutrightTradeCancelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_id[i] == written->original_trade_id[i]); }
}

/* Outright Trade Cancel Message: written and read back, then read and written back */
static void check_outright_trade_cancel_message(void) {
  OutrightTradeCancelMessage sent;
  OutrightTradeCancelMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_outright_trade_cancel_message(&sent);
  assert(encode_outright_trade_cancel_message(&sent, wire, 0) == 20);
  assert(decode_outright_trade_cancel_message(&got, wire, 0) == 20);
  equal_outright_trade_cancel_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_outright_trade_cancel_message(&got, wire, 0) == 20);
  assert(encode_outright_trade_cancel_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Outright Trade Correction Message: 36 bytes ----------------------------- */

/* The Trade Correction message is used to correct a trade. */
typedef struct {
  uint8_t source_time[4];        /* bytes 0 to 3 */
  uint8_t source_time_ns[4];     /* bytes 4 to 7 */
  uint8_t series_index[4];       /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];     /* bytes 12 to 15 */
  uint8_t original_trade_id[4];  /* bytes 16 to 19 */
  uint8_t trade_id[4];           /* bytes 20 to 23 */
  uint8_t price[4];              /* bytes 24 to 27 */
  uint8_t volume_4[4];           /* bytes 28 to 31 */
  uint8_t trade_cond_1;          /* byte 32 */
  uint8_t trade_cond_2;          /* byte 33 */
  uint8_t reserved_2[2];         /* bytes 34 to 35 */
} OutrightTradeCorrectionMessage;

/* any Outright Trade Correction Message at all: every byte one the checker chooses */
static void any_outright_trade_correction_message(OutrightTradeCorrectionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_4[i] = arbitrary(); }
  record->trade_cond_1 = arbitrary();
  record->trade_cond_2 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Outright Trade Correction Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_outright_trade_correction_message(const OutrightTradeCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_4[i]; }
  wire[at++] = record->trade_cond_1;
  wire[at++] = record->trade_cond_2;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Outright Trade Correction Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_outright_trade_correction_message(OutrightTradeCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_4[i] = wire[at++]; }
  record->trade_cond_1 = wire[at++];
  record->trade_cond_2 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Outright Trade Correction Message is what was written, byte for byte */
static void equal_outright_trade_correction_message(const OutrightTradeCorrectionMessage *read, const OutrightTradeCorrectionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_id[i] == written->original_trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_4[i] == written->volume_4[i]); }
  assert(read->trade_cond_1 == written->trade_cond_1);
  assert(read->trade_cond_2 == written->trade_cond_2);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Outright Trade Correction Message: written and read back, then read and written back */
static void check_outright_trade_correction_message(void) {
  OutrightTradeCorrectionMessage sent;
  OutrightTradeCorrectionMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_outright_trade_correction_message(&sent);
  assert(encode_outright_trade_correction_message(&sent, wire, 0) == 36);
  assert(decode_outright_trade_correction_message(&got, wire, 0) == 36);
  equal_outright_trade_correction_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_outright_trade_correction_message(&got, wire, 0) == 36);
  assert(encode_outright_trade_correction_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Outright Imbalance Message: 32 bytes ------------------------------------ */

/* The Outright Imbalance message is sent during the Pre-opening phase or a symbol Halt to provide indicative opening price and net imbalance of all orders at that price which are orders eligible for next Auction. */
typedef struct {
  uint8_t source_time[4];           /* bytes 0 to 3 */
  uint8_t source_time_ns[4];        /* bytes 4 to 7 */
  uint8_t series_index[4];          /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];        /* bytes 12 to 15 */
  uint8_t reference_price[4];       /* bytes 16 to 19 */
  uint8_t paired_qty[2];            /* bytes 20 to 21 */
  uint8_t total_imbalance_qty[2];   /* bytes 22 to 23 */
  uint8_t market_imbalance_qty[2];  /* bytes 24 to 25 */
  uint8_t auction_type;             /* byte 26 */
  uint8_t imbalance_side;           /* byte 27 */
  uint8_t market_imbalance_side;    /* byte 28 */
  uint8_t reserved_3[3];            /* bytes 29 to 31 */
} OutrightImbalanceMessage;

/* any Outright Imbalance Message at all: every byte one the checker chooses */
static void any_outright_imbalance_message(OutrightImbalanceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->paired_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->total_imbalance_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_imbalance_qty[i] = arbitrary(); }
  record->auction_type = arbitrary();
  record->imbalance_side = arbitrary();
  record->market_imbalance_side = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Outright Imbalance Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_outright_imbalance_message(const OutrightImbalanceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->paired_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->total_imbalance_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_imbalance_qty[i]; }
  wire[at++] = record->auction_type;
  wire[at++] = record->imbalance_side;
  wire[at++] = record->market_imbalance_side;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Outright Imbalance Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_outright_imbalance_message(OutrightImbalanceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->paired_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->total_imbalance_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_imbalance_qty[i] = wire[at++]; }
  record->auction_type = wire[at++];
  record->imbalance_side = wire[at++];
  record->market_imbalance_side = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Outright Imbalance Message is what was written, byte for byte */
static void equal_outright_imbalance_message(const OutrightImbalanceMessage *read, const OutrightImbalanceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->paired_qty[i] == written->paired_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->total_imbalance_qty[i] == written->total_imbalance_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_imbalance_qty[i] == written->market_imbalance_qty[i]); }
  assert(read->auction_type == written->auction_type);
  assert(read->imbalance_side == written->imbalance_side);
  assert(read->market_imbalance_side == written->market_imbalance_side);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Outright Imbalance Message: written and read back, then read and written back */
static void check_outright_imbalance_message(void) {
  OutrightImbalanceMessage sent;
  OutrightImbalanceMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_outright_imbalance_message(&sent);
  assert(encode_outright_imbalance_message(&sent, wire, 0) == 32);
  assert(decode_outright_imbalance_message(&got, wire, 0) == 32);
  equal_outright_imbalance_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_outright_imbalance_message(&got, wire, 0) == 32);
  assert(encode_outright_imbalance_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Outright Crossing Rfq Message: 24 bytes --------------------------------- */

/* The Outright Crossing RFQ (Request for Quote) message is sent out in the event of an auction on an outright order. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_ns[4];       /* bytes 4 to 7 */
  uint8_t series_index[4];    /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];  /* bytes 12 to 15 */
  uint8_t side;               /* byte 16 */
  uint8_t reserved_1;         /* byte 17 */
  uint8_t volume_2[2];        /* bytes 18 to 19 */
  uint8_t price[4];           /* bytes 20 to 23 */
} OutrightCrossingRfqMessage;

/* any Outright Crossing Rfq Message at all: every byte one the checker chooses */
static void any_outright_crossing_rfq_message(OutrightCrossingRfqMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  record->side = arbitrary();
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->volume_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
}

/* Outright Crossing Rfq Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_outright_crossing_rfq_message(const OutrightCrossingRfqMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  wire[at++] = record->side;
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->volume_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Outright Crossing Rfq Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_outright_crossing_rfq_message(OutrightCrossingRfqMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  record->side = wire[at++];
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->volume_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Outright Crossing Rfq Message is what was written, byte for byte */
static void equal_outright_crossing_rfq_message(const OutrightCrossingRfqMessage *read, const OutrightCrossingRfqMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_ns[i] == written->source_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  assert(read->side == written->side);
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->volume_2[i] == written->volume_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
}

/* Outright Crossing Rfq Message: written and read back, then read and written back */
static void check_outright_crossing_rfq_message(void) {
  OutrightCrossingRfqMessage sent;
  OutrightCrossingRfqMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_outright_crossing_rfq_message(&sent);
  assert(encode_outright_crossing_rfq_message(&sent, wire, 0) == 24);
  assert(decode_outright_crossing_rfq_message(&got, wire, 0) == 24);
  equal_outright_crossing_rfq_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_outright_crossing_rfq_message(&got, wire, 0) == 24);
  assert(encode_outright_crossing_rfq_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Outright Bold Rfq Message: 28 bytes ------------------------------------- */

/* The Outright BOLD RFQ (Request for Quote) message notifies clients of a special exposure order (a BOLD order) available for execution on a first-come first-served basis. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_ns[4];       /* bytes 4 to 7 */
  uint8_t series_index[4];    /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];  /* bytes 12 to 15 */
  uint8_t side;               /* byte 16 */
  uint8_t capacity;           /* byte 17 */
  uint8_t contracts[2];       /* bytes 18 to 19 */
  uint8_t price[4];           /* bytes 20 to 23 */
  uint8_t participant[4];     /* bytes 24 to 27 */
} OutrightBoldRfqMessage;

/* any Outright Bold Rfq Message at all: every byte one the checker chooses */
static void any_outright_bold_rfq_message(OutrightBoldRfqMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  record->side = arbitrary();
  record->capacity = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->contracts[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->participant[i] = arbitrary(); }
}

/* Outright Bold Rfq Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_outright_bold_rfq_message(const OutrightBoldRfqMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  wire[at++] = record->side;
  wire[at++] = record->capacity;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->contracts[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant[i]; }

  return at;
}

/* Outright Bold Rfq Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_outright_bold_rfq_message(OutrightBoldRfqMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  record->side = wire[at++];
  record->capacity = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->contracts[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->participant[i] = wire[at++]; }

  return at;
}

/* what was read of Outright Bold Rfq Message is what was written, byte for byte */
static void equal_outright_bold_rfq_message(const OutrightBoldRfqMessage *read, const OutrightBoldRfqMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_ns[i] == written->source_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  assert(read->side == written->side);
  assert(read->capacity == written->capacity);
  for (size_t i = 0; i < 2; i++) { assert(read->contracts[i] == written->contracts[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->participant[i] == written->participant[i]); }
}

/* Outright Bold Rfq Message: written and read back, then read and written back */
static void check_outright_bold_rfq_message(void) {
  OutrightBoldRfqMessage sent;
  OutrightBoldRfqMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_outright_bold_rfq_message(&sent);
  assert(encode_outright_bold_rfq_message(&sent, wire, 0) == 28);
  assert(decode_outright_bold_rfq_message(&got, wire, 0) == 28);
  equal_outright_bold_rfq_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_outright_bold_rfq_message(&got, wire, 0) == 28);
  assert(encode_outright_bold_rfq_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Outright Summary Message: 36 bytes -------------------------------------- */

/* The Outright summary message provides trading highlights of the day. It is sent out once at the end of the trading day as soon as a symbol closes. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_time_ns[4];  /* bytes 4 to 7 */
  uint8_t series_index[4];    /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];  /* bytes 12 to 15 */
  uint8_t high_price[4];      /* bytes 16 to 19 */
  uint8_t low_price[4];       /* bytes 20 to 23 */
  uint8_t open[4];            /* bytes 24 to 27 */
  uint8_t close[4];           /* bytes 28 to 31 */
  uint8_t total_volume[4];    /* bytes 32 to 35 */
} OutrightSummaryMessage;

/* any Outright Summary Message at all: every byte one the checker chooses */
static void any_outright_summary_message(OutrightSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->close[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = arbitrary(); }
}

/* Outright Summary Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_outright_summary_message(const OutrightSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->close[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_volume[i]; }

  return at;
}

/* Outright Summary Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_outright_summary_message(OutrightSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->close[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Outright Summary Message is what was written, byte for byte */
static void equal_outright_summary_message(const OutrightSummaryMessage *read, const OutrightSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open[i] == written->open[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->close[i] == written->close[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_volume[i] == written->total_volume[i]); }
}

/* Outright Summary Message: written and read back, then read and written back */
static void check_outright_summary_message(void) {
  OutrightSummaryMessage sent;
  OutrightSummaryMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_outright_summary_message(&sent);
  assert(encode_outright_summary_message(&sent, wire, 0) == 36);
  assert(decode_outright_summary_message(&got, wire, 0) == 36);
  equal_outright_summary_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_outright_summary_message(&got, wire, 0) == 36);
  assert(encode_outright_summary_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Status Message: 20 bytes ------------------------------------- */

/* The Underlying Status message is used to inform the subscribers of changes in the status of an Underlying symbol. */
typedef struct {
  uint8_t source_time[4];         /* bytes 0 to 3 */
  uint8_t source_time_ns[4];      /* bytes 4 to 7 */
  uint8_t underlying_index[4];    /* bytes 8 to 11 */
  uint8_t underlying_seq_num[4];  /* bytes 12 to 15 */
  uint8_t security_status;        /* byte 16 */
  uint8_t halt_condition;         /* byte 17 */
  uint8_t reserved_2[2];          /* bytes 18 to 19 */
} UnderlyingStatusMessage;

/* any Underlying Status Message at all: every byte one the checker chooses */
static void any_underlying_status_message(UnderlyingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_seq_num[i] = arbitrary(); }
  record->security_status = arbitrary();
  record->halt_condition = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Underlying Status Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_underlying_status_message(const UnderlyingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_seq_num[i]; }
  wire[at++] = record->security_status;
  wire[at++] = record->halt_condition;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Underlying Status Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_underlying_status_message(UnderlyingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_seq_num[i] = wire[at++]; }
  record->security_status = wire[at++];
  record->halt_condition = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Underlying Status Message is what was written, byte for byte */
static void equal_underlying_status_message(const UnderlyingStatusMessage *read, const UnderlyingStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_index[i] == written->underlying_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_seq_num[i] == written->underlying_seq_num[i]); }
  assert(read->security_status == written->security_status);
  assert(read->halt_condition == written->halt_condition);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Underlying Status Message: written and read back, then read and written back */
static void check_underlying_status_message(void) {
  UnderlyingStatusMessage sent;
  UnderlyingStatusMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_underlying_status_message(&sent);
  assert(encode_underlying_status_message(&sent, wire, 0) == 20);
  assert(decode_underlying_status_message(&got, wire, 0) == 20);
  equal_underlying_status_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_status_message(&got, wire, 0) == 20);
  assert(encode_underlying_status_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Outright Series Status Message: 20 bytes -------------------------------- */

/* The Series Status message is used to inform the subscribers of changes in symbol status of an outright symbol. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_time_ns[4];  /* bytes 4 to 7 */
  uint8_t series_index[4];    /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];  /* bytes 12 to 15 */
  uint8_t security_status;    /* byte 16 */
  uint8_t halt_condition;     /* byte 17 */
  uint8_t reserved_2[2];      /* bytes 18 to 19 */
} OutrightSeriesStatusMessage;

/* any Outright Series Status Message at all: every byte one the checker chooses */
static void any_outright_series_status_message(OutrightSeriesStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  record->security_status = arbitrary();
  record->halt_condition = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Outright Series Status Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_outright_series_status_message(const OutrightSeriesStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  wire[at++] = record->security_status;
  wire[at++] = record->halt_condition;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Outright Series Status Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_outright_series_status_message(OutrightSeriesStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  record->security_status = wire[at++];
  record->halt_condition = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Outright Series Status Message is what was written, byte for byte */
static void equal_outright_series_status_message(const OutrightSeriesStatusMessage *read, const OutrightSeriesStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  assert(read->security_status == written->security_status);
  assert(read->halt_condition == written->halt_condition);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Outright Series Status Message: written and read back, then read and written back */
static void check_outright_series_status_message(void) {
  OutrightSeriesStatusMessage sent;
  OutrightSeriesStatusMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_outright_series_status_message(&sent);
  assert(encode_outright_series_status_message(&sent, wire, 0) == 20);
  assert(decode_outright_series_status_message(&got, wire, 0) == 20);
  equal_outright_series_status_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_outright_series_status_message(&got, wire, 0) == 20);
  assert(encode_outright_series_status_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Outright Quote Message: 36 bytes -------------------------------- */

/* The Refresh Quote message is sent in the event no quote messages are published for the symbol for 2 consecutive minutes. */
typedef struct {
  uint8_t source_time[4];          /* bytes 0 to 3 */
  uint8_t source_time_ns[4];       /* bytes 4 to 7 */
  uint8_t series_index[4];         /* bytes 8 to 11 */
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
} RefreshOutrightQuoteMessage;

/* any Refresh Outright Quote Message at all: every byte one the checker chooses */
static void any_refresh_outright_quote_message(RefreshOutrightQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
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

/* Refresh Outright Quote Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_refresh_outright_quote_message(const RefreshOutrightQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
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

/* Refresh Outright Quote Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_refresh_outright_quote_message(RefreshOutrightQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
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

/* what was read of Refresh Outright Quote Message is what was written, byte for byte */
static void equal_refresh_outright_quote_message(const RefreshOutrightQuoteMessage *read, const RefreshOutrightQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
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

/* Refresh Outright Quote Message: written and read back, then read and written back */
static void check_refresh_outright_quote_message(void) {
  RefreshOutrightQuoteMessage sent;
  RefreshOutrightQuoteMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_refresh_outright_quote_message(&sent);
  assert(encode_refresh_outright_quote_message(&sent, wire, 0) == 36);
  assert(decode_refresh_outright_quote_message(&got, wire, 0) == 36);
  equal_refresh_outright_quote_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_outright_quote_message(&got, wire, 0) == 36);
  assert(encode_refresh_outright_quote_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Outright Trade Message: 32 bytes -------------------------------- */

/* The Refresh Outright Trade message is sent in the event no Outright Trade messages are published for the symbol for 2 consecutive minutes. */
typedef struct {
  uint8_t source_time[4];     /* bytes 0 to 3 */
  uint8_t source_time_ns[4];  /* bytes 4 to 7 */
  uint8_t series_index[4];    /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];  /* bytes 12 to 15 */
  uint8_t trade_id[4];        /* bytes 16 to 19 */
  uint8_t price[4];           /* bytes 20 to 23 */
  uint8_t volume_4[4];        /* bytes 24 to 27 */
  uint8_t trade_cond_1;       /* byte 28 */
  uint8_t trade_cond_2;       /* byte 29 */
  uint8_t reserved_2[2];      /* bytes 30 to 31 */
} RefreshOutrightTradeMessage;

/* any Refresh Outright Trade Message at all: every byte one the checker chooses */
static void any_refresh_outright_trade_message(RefreshOutrightTradeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_4[i] = arbitrary(); }
  record->trade_cond_1 = arbitrary();
  record->trade_cond_2 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Refresh Outright Trade Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_refresh_outright_trade_message(const RefreshOutrightTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_4[i]; }
  wire[at++] = record->trade_cond_1;
  wire[at++] = record->trade_cond_2;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Refresh Outright Trade Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_refresh_outright_trade_message(RefreshOutrightTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_4[i] = wire[at++]; }
  record->trade_cond_1 = wire[at++];
  record->trade_cond_2 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Refresh Outright Trade Message is what was written, byte for byte */
static void equal_refresh_outright_trade_message(const RefreshOutrightTradeMessage *read, const RefreshOutrightTradeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_4[i] == written->volume_4[i]); }
  assert(read->trade_cond_1 == written->trade_cond_1);
  assert(read->trade_cond_2 == written->trade_cond_2);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Refresh Outright Trade Message: written and read back, then read and written back */
static void check_refresh_outright_trade_message(void) {
  RefreshOutrightTradeMessage sent;
  RefreshOutrightTradeMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_refresh_outright_trade_message(&sent);
  assert(encode_refresh_outright_trade_message(&sent, wire, 0) == 32);
  assert(decode_refresh_outright_trade_message(&got, wire, 0) == 32);
  equal_refresh_outright_trade_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_outright_trade_message(&got, wire, 0) == 32);
  assert(encode_refresh_outright_trade_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refresh Outright Imbalance Message: 32 bytes ---------------------------- */

/* The Refresh Outright Imbalance message is sent in the event no Outright Imbalance messages are published for the symbol for 2 consecutive minutes during Pre-opening or a symbol Halt. */
typedef struct {
  uint8_t source_time[4];           /* bytes 0 to 3 */
  uint8_t source_time_ns[4];        /* bytes 4 to 7 */
  uint8_t series_index[4];          /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];        /* bytes 12 to 15 */
  uint8_t reference_price[4];       /* bytes 16 to 19 */
  uint8_t paired_qty[2];            /* bytes 20 to 21 */
  uint8_t total_imbalance_qty[2];   /* bytes 22 to 23 */
  uint8_t market_imbalance_qty[2];  /* bytes 24 to 25 */
  uint8_t auction_type;             /* byte 26 */
  uint8_t imbalance_side;           /* byte 27 */
  uint8_t market_imbalance_side;    /* byte 28 */
  uint8_t reserved_3[3];            /* bytes 29 to 31 */
} RefreshOutrightImbalanceMessage;

/* any Refresh Outright Imbalance Message at all: every byte one the checker chooses */
static void any_refresh_outright_imbalance_message(RefreshOutrightImbalanceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->paired_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->total_imbalance_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_imbalance_qty[i] = arbitrary(); }
  record->auction_type = arbitrary();
  record->imbalance_side = arbitrary();
  record->market_imbalance_side = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Refresh Outright Imbalance Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_refresh_outright_imbalance_message(const RefreshOutrightImbalanceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->paired_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->total_imbalance_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_imbalance_qty[i]; }
  wire[at++] = record->auction_type;
  wire[at++] = record->imbalance_side;
  wire[at++] = record->market_imbalance_side;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Refresh Outright Imbalance Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_refresh_outright_imbalance_message(RefreshOutrightImbalanceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->paired_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->total_imbalance_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_imbalance_qty[i] = wire[at++]; }
  record->auction_type = wire[at++];
  record->imbalance_side = wire[at++];
  record->market_imbalance_side = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Refresh Outright Imbalance Message is what was written, byte for byte */
static void equal_refresh_outright_imbalance_message(const RefreshOutrightImbalanceMessage *read, const RefreshOutrightImbalanceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->paired_qty[i] == written->paired_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->total_imbalance_qty[i] == written->total_imbalance_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_imbalance_qty[i] == written->market_imbalance_qty[i]); }
  assert(read->auction_type == written->auction_type);
  assert(read->imbalance_side == written->imbalance_side);
  assert(read->market_imbalance_side == written->market_imbalance_side);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Refresh Outright Imbalance Message: written and read back, then read and written back */
static void check_refresh_outright_imbalance_message(void) {
  RefreshOutrightImbalanceMessage sent;
  RefreshOutrightImbalanceMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_refresh_outright_imbalance_message(&sent);
  assert(encode_refresh_outright_imbalance_message(&sent, wire, 0) == 32);
  assert(decode_refresh_outright_imbalance_message(&got, wire, 0) == 32);
  equal_refresh_outright_imbalance_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_refresh_outright_imbalance_message(&got, wire, 0) == 32);
  assert(encode_refresh_outright_imbalance_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Index Mapping Message: 24 bytes ------------------------------ */

/* On system startup, each multicast channel sends all the symbols on its channel. Underlying Index Mapping messages are published first, followed by all Series Index Mapping messages, and for the Complex feed, Complex Symbol Definitions last of all. */
typedef struct {
  uint8_t underlying_index[4];    /* bytes 0 to 3 */
  uint8_t underlying_symbol[11];  /* bytes 4 to 14 */
  uint8_t channel_id;             /* byte 15 */
  uint8_t market_id[2];           /* bytes 16 to 17 */
  uint8_t system_id;              /* byte 18 */
  uint8_t exchange_code;          /* byte 19 */
  uint8_t price_scale_code;       /* byte 20 */
  uint8_t security_type;          /* byte 21 */
  uint8_t price_resolution;       /* byte 22 */
  uint8_t reserved_1;             /* byte 23 */
} UnderlyingIndexMappingMessage;

/* any Underlying Index Mapping Message at all: every byte one the checker chooses */
static void any_underlying_index_mapping_message(UnderlyingIndexMappingMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->underlying_index[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->channel_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = arbitrary(); }
  record->system_id = arbitrary();
  record->exchange_code = arbitrary();
  record->price_scale_code = arbitrary();
  record->security_type = arbitrary();
  record->price_resolution = arbitrary();
  record->reserved_1 = arbitrary();
}

/* Underlying Index Mapping Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_underlying_index_mapping_message(const UnderlyingIndexMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_index[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->channel_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id[i]; }
  wire[at++] = record->system_id;
  wire[at++] = record->exchange_code;
  wire[at++] = record->price_scale_code;
  wire[at++] = record->security_type;
  wire[at++] = record->price_resolution;
  wire[at++] = record->reserved_1;

  return at;
}

/* Underlying Index Mapping Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_underlying_index_mapping_message(UnderlyingIndexMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->underlying_index[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->channel_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = wire[at++]; }
  record->system_id = wire[at++];
  record->exchange_code = wire[at++];
  record->price_scale_code = wire[at++];
  record->security_type = wire[at++];
  record->price_resolution = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Underlying Index Mapping Message is what was written, byte for byte */
static void equal_underlying_index_mapping_message(const UnderlyingIndexMappingMessage *read, const UnderlyingIndexMappingMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_index[i] == written->underlying_index[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->channel_id == written->channel_id);
  for (size_t i = 0; i < 2; i++) { assert(read->market_id[i] == written->market_id[i]); }
  assert(read->system_id == written->system_id);
  assert(read->exchange_code == written->exchange_code);
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->security_type == written->security_type);
  assert(read->price_resolution == written->price_resolution);
  assert(read->reserved_1 == written->reserved_1);
}

/* Underlying Index Mapping Message: written and read back, then read and written back */
static void check_underlying_index_mapping_message(void) {
  UnderlyingIndexMappingMessage sent;
  UnderlyingIndexMappingMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_underlying_index_mapping_message(&sent);
  assert(encode_underlying_index_mapping_message(&sent, wire, 0) == 24);
  assert(decode_underlying_index_mapping_message(&got, wire, 0) == 24);
  equal_underlying_index_mapping_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_index_mapping_message(&got, wire, 0) == 24);
  assert(encode_underlying_index_mapping_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Series Index Mapping Message: 56 bytes ---------------------------------- */

/* On system startup, each multicast channel sends all the symbols on its channel. Underlying Index Mapping messages are published first, followed by all Series Index Mapping messages, and for the Complex feed, Complex Symbol Definitions last of all. */
typedef struct {
  uint8_t series_index[4];         /* bytes 0 to 3 */
  uint8_t channel_id;              /* byte 4 */
  uint8_t reserved_a_1;            /* byte 5 */
  uint8_t market_id[2];            /* bytes 6 to 7 */
  uint8_t system_id;               /* byte 8 */
  uint8_t reserved_b_1;            /* byte 9 */
  uint8_t stream_id[2];            /* bytes 10 to 11 */
  uint8_t underlying_index[4];     /* bytes 12 to 15 */
  uint8_t contract_multiplier[2];  /* bytes 16 to 17 */
  uint8_t maturity_date[6];        /* bytes 18 to 23 */
  uint8_t put_or_call;             /* byte 24 */
  uint8_t strike_price[10];        /* bytes 25 to 34 */
  uint8_t price_scale_code;        /* byte 35 */
  uint8_t underlying_symbol[11];   /* bytes 36 to 46 */
  uint8_t option_symbol_root[5];   /* bytes 47 to 51 */
  uint8_t group_id[4];             /* bytes 52 to 55 */
} SeriesIndexMappingMessage;

/* any Series Index Mapping Message at all: every byte one the checker chooses */
static void any_series_index_mapping_message(SeriesIndexMappingMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = arbitrary(); }
  record->channel_id = arbitrary();
  record->reserved_a_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = arbitrary(); }
  record->system_id = arbitrary();
  record->reserved_b_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_index[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->contract_multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->maturity_date[i] = arbitrary(); }
  record->put_or_call = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->strike_price[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->option_symbol_root[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->group_id[i] = arbitrary(); }
}

/* Series Index Mapping Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_series_index_mapping_message(const SeriesIndexMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->series_index[i]; }
  wire[at++] = record->channel_id;
  wire[at++] = record->reserved_a_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_id[i]; }
  wire[at++] = record->system_id;
  wire[at++] = record->reserved_b_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stream_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_index[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->contract_multiplier[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->maturity_date[i]; }
  wire[at++] = record->put_or_call;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->price_scale_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->option_symbol_root[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->group_id[i]; }

  return at;
}

/* Series Index Mapping Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_series_index_mapping_message(SeriesIndexMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->series_index[i] = wire[at++]; }
  record->channel_id = wire[at++];
  record->reserved_a_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->market_id[i] = wire[at++]; }
  record->system_id = wire[at++];
  record->reserved_b_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_index[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->contract_multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->maturity_date[i] = wire[at++]; }
  record->put_or_call = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->strike_price[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->option_symbol_root[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->group_id[i] = wire[at++]; }

  return at;
}

/* what was read of Series Index Mapping Message is what was written, byte for byte */
static void equal_series_index_mapping_message(const SeriesIndexMappingMessage *read, const SeriesIndexMappingMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->series_index[i] == written->series_index[i]); }
  assert(read->channel_id == written->channel_id);
  assert(read->reserved_a_1 == written->reserved_a_1);
  for (size_t i = 0; i < 2; i++) { assert(read->market_id[i] == written->market_id[i]); }
  assert(read->system_id == written->system_id);
  assert(read->reserved_b_1 == written->reserved_b_1);
  for (size_t i = 0; i < 2; i++) { assert(read->stream_id[i] == written->stream_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_index[i] == written->underlying_index[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->contract_multiplier[i] == written->contract_multiplier[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  assert(read->put_or_call == written->put_or_call);
  for (size_t i = 0; i < 10; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->option_symbol_root[i] == written->option_symbol_root[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->group_id[i] == written->group_id[i]); }
}

/* Series Index Mapping Message: written and read back, then read and written back */
static void check_series_index_mapping_message(void) {
  SeriesIndexMappingMessage sent;
  SeriesIndexMappingMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_series_index_mapping_message(&sent);
  assert(encode_series_index_mapping_message(&sent, wire, 0) == 56);
  assert(decode_series_index_mapping_message(&got, wire, 0) == 56);
  equal_series_index_mapping_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_series_index_mapping_message(&got, wire, 0) == 56);
  assert(encode_series_index_mapping_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
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
  check_outright_quote_message();
  check_outright_trade_message();
  check_outright_trade_cancel_message();
  check_outright_trade_correction_message();
  check_outright_imbalance_message();
  check_outright_crossing_rfq_message();
  check_outright_bold_rfq_message();
  check_outright_summary_message();
  check_underlying_status_message();
  check_outright_series_status_message();
  check_refresh_outright_quote_message();
  check_refresh_outright_trade_message();
  check_refresh_outright_imbalance_message();
  check_underlying_index_mapping_message();
  check_series_index_mapping_message();
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
