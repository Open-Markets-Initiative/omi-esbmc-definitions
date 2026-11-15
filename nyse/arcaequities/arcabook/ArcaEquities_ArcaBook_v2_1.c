// nyse/arcaequities/arcabook/ArcaEquities_ArcaBook_v2_1.c
/*
 * New York Stock Exchange ArcaBook
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

/* ArcaBook common client udp packet header */
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

/* ArcaBook message header */
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

/* ---- Add Order Message: 27 bytes --------------------------------------------- */

/* ArcaBook Add Order Message */
typedef struct {
  uint8_t source_time_ns[4];      /* bytes 0 to 3 */
  uint8_t symbol_index[4];        /* bytes 4 to 7 */
  uint8_t symbol_seq_num[4];      /* bytes 8 to 11 */
  uint8_t order_id[4];            /* bytes 12 to 15 */
  uint8_t price[4];               /* bytes 16 to 19 */
  uint8_t volume[4];              /* bytes 20 to 23 */
  uint8_t side;                   /* byte 24 */
  uint8_t order_idgtc_indicator;  /* byte 25 */
  uint8_t trade_session;          /* byte 26 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->side = arbitrary();
  record->order_idgtc_indicator = arbitrary();
  record->trade_session = arbitrary();
}

/* Add Order Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->side;
  wire[at++] = record->order_idgtc_indicator;
  wire[at++] = record->trade_session;

  return at;
}

/* Add Order Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->side = wire[at++];
  record->order_idgtc_indicator = wire[at++];
  record->trade_session = wire[at++];

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->side == written->side);
  assert(read->order_idgtc_indicator == written->order_idgtc_indicator);
  assert(read->trade_session == written->trade_session);
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 27);
  assert(decode_add_order_message(&got, wire, 0) == 27);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 27);
  assert(encode_add_order_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Message: 27 bytes ------------------------------------------ */

/* ArcaBook Modify Order Message */
typedef struct {
  uint8_t source_time_ns[4];      /* bytes 0 to 3 */
  uint8_t symbol_index[4];        /* bytes 4 to 7 */
  uint8_t symbol_seq_num[4];      /* bytes 8 to 11 */
  uint8_t order_id[4];            /* bytes 12 to 15 */
  uint8_t price[4];               /* bytes 16 to 19 */
  uint8_t volume[4];              /* bytes 20 to 23 */
  uint8_t side;                   /* byte 24 */
  uint8_t order_idgtc_indicator;  /* byte 25 */
  uint8_t reason_code;            /* byte 26 */
} ModifyOrderMessage;

/* any Modify Order Message at all: every byte one the checker chooses */
static void any_modify_order_message(ModifyOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->side = arbitrary();
  record->order_idgtc_indicator = arbitrary();
  record->reason_code = arbitrary();
}

/* Modify Order Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_message(const ModifyOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->side;
  wire[at++] = record->order_idgtc_indicator;
  wire[at++] = record->reason_code;

  return at;
}

/* Modify Order Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_message(ModifyOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->side = wire[at++];
  record->order_idgtc_indicator = wire[at++];
  record->reason_code = wire[at++];

  return at;
}

/* what was read of Modify Order Message is what was written, byte for byte */
static void equal_modify_order_message(const ModifyOrderMessage *read, const ModifyOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->side == written->side);
  assert(read->order_idgtc_indicator == written->order_idgtc_indicator);
  assert(read->reason_code == written->reason_code);
}

/* Modify Order Message: written and read back, then read and written back */
static void check_modify_order_message(void) {
  ModifyOrderMessage sent;
  ModifyOrderMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_modify_order_message(&sent);
  assert(encode_modify_order_message(&sent, wire, 0) == 27);
  assert(decode_modify_order_message(&got, wire, 0) == 27);
  equal_modify_order_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_message(&got, wire, 0) == 27);
  assert(encode_modify_order_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Order Message: 19 bytes ------------------------------------------ */

/* ArcaBook Delete Order Message */
typedef struct {
  uint8_t source_time_ns[4];      /* bytes 0 to 3 */
  uint8_t symbol_index[4];        /* bytes 4 to 7 */
  uint8_t symbol_seq_num[4];      /* bytes 8 to 11 */
  uint8_t order_id[4];            /* bytes 12 to 15 */
  uint8_t side;                   /* byte 16 */
  uint8_t order_idgtc_indicator;  /* byte 17 */
  uint8_t reason_code;            /* byte 18 */
} DeleteOrderMessage;

/* any Delete Order Message at all: every byte one the checker chooses */
static void any_delete_order_message(DeleteOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  record->order_idgtc_indicator = arbitrary();
  record->reason_code = arbitrary();
}

/* Delete Order Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_delete_order_message(const DeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  wire[at++] = record->order_idgtc_indicator;
  wire[at++] = record->reason_code;

  return at;
}

/* Delete Order Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_delete_order_message(DeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  record->order_idgtc_indicator = wire[at++];
  record->reason_code = wire[at++];

  return at;
}

/* what was read of Delete Order Message is what was written, byte for byte */
static void equal_delete_order_message(const DeleteOrderMessage *read, const DeleteOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  assert(read->order_idgtc_indicator == written->order_idgtc_indicator);
  assert(read->reason_code == written->reason_code);
}

/* Delete Order Message: written and read back, then read and written back */
static void check_delete_order_message(void) {
  DeleteOrderMessage sent;
  DeleteOrderMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_delete_order_message(&sent);
  assert(encode_delete_order_message(&sent, wire, 0) == 19);
  assert(decode_delete_order_message(&got, wire, 0) == 19);
  equal_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_order_message(&got, wire, 0) == 19);
  assert(encode_delete_order_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Message: 30 bytes --------------------------------------------- */

/* ArcaBook Execution Message */
typedef struct {
  uint8_t source_time_ns[4];      /* bytes 0 to 3 */
  uint8_t symbol_index[4];        /* bytes 4 to 7 */
  uint8_t symbol_seq_num[4];      /* bytes 8 to 11 */
  uint8_t order_id[4];            /* bytes 12 to 15 */
  uint8_t price[4];               /* bytes 16 to 19 */
  uint8_t volume[4];              /* bytes 20 to 23 */
  uint8_t order_idgtc_indicator;  /* byte 24 */
  uint8_t reason_code;            /* byte 25 */
  uint8_t trade_id[4];            /* bytes 26 to 29 */
} ExecutionMessage;

/* any Execution Message at all: every byte one the checker chooses */
static void any_execution_message(ExecutionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->order_idgtc_indicator = arbitrary();
  record->reason_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
}

/* Execution Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_execution_message(const ExecutionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->order_idgtc_indicator;
  wire[at++] = record->reason_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }

  return at;
}

/* Execution Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_execution_message(ExecutionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->order_idgtc_indicator = wire[at++];
  record->reason_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Message is what was written, byte for byte */
static void equal_execution_message(const ExecutionMessage *read, const ExecutionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->order_idgtc_indicator == written->order_idgtc_indicator);
  assert(read->reason_code == written->reason_code);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
}

/* Execution Message: written and read back, then read and written back */
static void check_execution_message(void) {
  ExecutionMessage sent;
  ExecutionMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_execution_message(&sent);
  assert(encode_execution_message(&sent, wire, 0) == 30);
  assert(decode_execution_message(&got, wire, 0) == 30);
  equal_execution_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_message(&got, wire, 0) == 30);
  assert(encode_execution_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Imbalance Message: 48 bytes --------------------------------------------- */

/* ArcaBook Imbalance Message */
typedef struct {
  uint8_t source_time[4];                     /* bytes 0 to 3 */
  uint8_t source_time_ns[4];                  /* bytes 4 to 7 */
  uint8_t symbol_index[4];                    /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];                  /* bytes 12 to 15 */
  uint8_t indicative_match_price[4];          /* bytes 16 to 19 */
  uint8_t paired_qty[4];                      /* bytes 20 to 23 */
  uint8_t total_imbalance_qty[4];             /* bytes 24 to 27 */
  uint8_t market_imbalance_qty[4];            /* bytes 28 to 31 */
  uint8_t auction_time[2];                    /* bytes 32 to 33 */
  uint8_t auction_type;                       /* byte 34 */
  uint8_t imbalance_side;                     /* byte 35 */
  uint8_t continuous_book_clearing_price[4];  /* bytes 36 to 39 */
  uint8_t closing_only_clearing_price[4];     /* bytes 40 to 43 */
  uint8_t ssr_filing_price[4];                /* bytes 44 to 47 */
} ImbalanceMessage;

/* any Imbalance Message at all: every byte one the checker chooses */
static void any_imbalance_message(ImbalanceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->indicative_match_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->paired_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_imbalance_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_imbalance_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->auction_time[i] = arbitrary(); }
  record->auction_type = arbitrary();
  record->imbalance_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->continuous_book_clearing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->closing_only_clearing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ssr_filing_price[i] = arbitrary(); }
}

/* Imbalance Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_imbalance_message(const ImbalanceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indicative_match_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->paired_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_imbalance_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_imbalance_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->auction_time[i]; }
  wire[at++] = record->auction_type;
  wire[at++] = record->imbalance_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->continuous_book_clearing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_only_clearing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ssr_filing_price[i]; }

  return at;
}

/* Imbalance Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_imbalance_message(ImbalanceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->indicative_match_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->paired_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_imbalance_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_imbalance_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->auction_time[i] = wire[at++]; }
  record->auction_type = wire[at++];
  record->imbalance_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->continuous_book_clearing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->closing_only_clearing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ssr_filing_price[i] = wire[at++]; }

  return at;
}

/* what was read of Imbalance Message is what was written, byte for byte */
static void equal_imbalance_message(const ImbalanceMessage *read, const ImbalanceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->indicative_match_price[i] == written->indicative_match_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->paired_qty[i] == written->paired_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_imbalance_qty[i] == written->total_imbalance_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_imbalance_qty[i] == written->market_imbalance_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->auction_time[i] == written->auction_time[i]); }
  assert(read->auction_type == written->auction_type);
  assert(read->imbalance_side == written->imbalance_side);
  for (size_t i = 0; i < 4; i++) { assert(read->continuous_book_clearing_price[i] == written->continuous_book_clearing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->closing_only_clearing_price[i] == written->closing_only_clearing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ssr_filing_price[i] == written->ssr_filing_price[i]); }
}

/* Imbalance Message: written and read back, then read and written back */
static void check_imbalance_message(void) {
  ImbalanceMessage sent;
  ImbalanceMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_imbalance_message(&sent);
  assert(encode_imbalance_message(&sent, wire, 0) == 48);
  assert(decode_imbalance_message(&got, wire, 0) == 48);
  equal_imbalance_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_imbalance_message(&got, wire, 0) == 48);
  assert(encode_imbalance_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Refresh Message: 31 bytes ------------------------------------- */

/* ArcaBook Add Order Refresh Message */
typedef struct {
  uint8_t source_time[4];         /* bytes 0 to 3 */
  uint8_t source_time_ns[4];      /* bytes 4 to 7 */
  uint8_t symbol_index[4];        /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];      /* bytes 12 to 15 */
  uint8_t order_id[4];            /* bytes 16 to 19 */
  uint8_t price[4];               /* bytes 20 to 23 */
  uint8_t volume[4];              /* bytes 24 to 27 */
  uint8_t side;                   /* byte 28 */
  uint8_t order_idgtc_indicator;  /* byte 29 */
  uint8_t trade_session;          /* byte 30 */
} AddOrderRefreshMessage;

/* any Add Order Refresh Message at all: every byte one the checker chooses */
static void any_add_order_refresh_message(AddOrderRefreshMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->side = arbitrary();
  record->order_idgtc_indicator = arbitrary();
  record->trade_session = arbitrary();
}

/* Add Order Refresh Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_add_order_refresh_message(const AddOrderRefreshMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->side;
  wire[at++] = record->order_idgtc_indicator;
  wire[at++] = record->trade_session;

  return at;
}

/* Add Order Refresh Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_add_order_refresh_message(AddOrderRefreshMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->side = wire[at++];
  record->order_idgtc_indicator = wire[at++];
  record->trade_session = wire[at++];

  return at;
}

/* what was read of Add Order Refresh Message is what was written, byte for byte */
static void equal_add_order_refresh_message(const AddOrderRefreshMessage *read, const AddOrderRefreshMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->side == written->side);
  assert(read->order_idgtc_indicator == written->order_idgtc_indicator);
  assert(read->trade_session == written->trade_session);
}

/* Add Order Refresh Message: written and read back, then read and written back */
static void check_add_order_refresh_message(void) {
  AddOrderRefreshMessage sent;
  AddOrderRefreshMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_add_order_refresh_message(&sent);
  assert(encode_add_order_refresh_message(&sent, wire, 0) == 31);
  assert(decode_add_order_refresh_message(&got, wire, 0) == 31);
  equal_add_order_refresh_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_refresh_message(&got, wire, 0) == 31);
  assert(encode_add_order_refresh_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Attributed Add Order Message: 32 bytes ---------------------------------- */

/* ArcaBook Attributed Add Order Message */
typedef struct {
  uint8_t source_time_ns[4];      /* bytes 0 to 3 */
  uint8_t symbol_index[4];        /* bytes 4 to 7 */
  uint8_t symbol_seq_num[4];      /* bytes 8 to 11 */
  uint8_t order_id[4];            /* bytes 12 to 15 */
  uint8_t price[4];               /* bytes 16 to 19 */
  uint8_t volume[4];              /* bytes 20 to 23 */
  uint8_t side;                   /* byte 24 */
  uint8_t order_idgtc_indicator;  /* byte 25 */
  uint8_t trade_session;          /* byte 26 */
  uint8_t firm_id[5];             /* bytes 27 to 31 */
} AttributedAddOrderMessage;

/* any Attributed Add Order Message at all: every byte one the checker chooses */
static void any_attributed_add_order_message(AttributedAddOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->side = arbitrary();
  record->order_idgtc_indicator = arbitrary();
  record->trade_session = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->firm_id[i] = arbitrary(); }
}

/* Attributed Add Order Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_attributed_add_order_message(const AttributedAddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->side;
  wire[at++] = record->order_idgtc_indicator;
  wire[at++] = record->trade_session;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->firm_id[i]; }

  return at;
}

/* Attributed Add Order Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_attributed_add_order_message(AttributedAddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->side = wire[at++];
  record->order_idgtc_indicator = wire[at++];
  record->trade_session = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->firm_id[i] = wire[at++]; }

  return at;
}

/* what was read of Attributed Add Order Message is what was written, byte for byte */
static void equal_attributed_add_order_message(const AttributedAddOrderMessage *read, const AttributedAddOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->side == written->side);
  assert(read->order_idgtc_indicator == written->order_idgtc_indicator);
  assert(read->trade_session == written->trade_session);
  for (size_t i = 0; i < 5; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
}

/* Attributed Add Order Message: written and read back, then read and written back */
static void check_attributed_add_order_message(void) {
  AttributedAddOrderMessage sent;
  AttributedAddOrderMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_attributed_add_order_message(&sent);
  assert(encode_attributed_add_order_message(&sent, wire, 0) == 32);
  assert(decode_attributed_add_order_message(&got, wire, 0) == 32);
  equal_attributed_add_order_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_attributed_add_order_message(&got, wire, 0) == 32);
  assert(encode_attributed_add_order_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Attributed Add Order Refresh Message: 36 bytes -------------------------- */

/* ArcaBook Attributed Add Order Refresh Message */
typedef struct {
  uint8_t source_time[4];         /* bytes 0 to 3 */
  uint8_t source_time_ns[4];      /* bytes 4 to 7 */
  uint8_t symbol_index[4];        /* bytes 8 to 11 */
  uint8_t symbol_seq_num[4];      /* bytes 12 to 15 */
  uint8_t order_id[4];            /* bytes 16 to 19 */
  uint8_t price[4];               /* bytes 20 to 23 */
  uint8_t volume[4];              /* bytes 24 to 27 */
  uint8_t side;                   /* byte 28 */
  uint8_t order_idgtc_indicator;  /* byte 29 */
  uint8_t trade_session;          /* byte 30 */
  uint8_t firm_id[5];             /* bytes 31 to 35 */
} AttributedAddOrderRefreshMessage;

/* any Attributed Add Order Refresh Message at all: every byte one the checker chooses */
static void any_attributed_add_order_refresh_message(AttributedAddOrderRefreshMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  record->side = arbitrary();
  record->order_idgtc_indicator = arbitrary();
  record->trade_session = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->firm_id[i] = arbitrary(); }
}

/* Attributed Add Order Refresh Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_attributed_add_order_refresh_message(const AttributedAddOrderRefreshMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time_ns[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->side;
  wire[at++] = record->order_idgtc_indicator;
  wire[at++] = record->trade_session;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->firm_id[i]; }

  return at;
}

/* Attributed Add Order Refresh Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_attributed_add_order_refresh_message(AttributedAddOrderRefreshMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time_ns[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  record->side = wire[at++];
  record->order_idgtc_indicator = wire[at++];
  record->trade_session = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->firm_id[i] = wire[at++]; }

  return at;
}

/* what was read of Attributed Add Order Refresh Message is what was written, byte for byte */
static void equal_attributed_add_order_refresh_message(const AttributedAddOrderRefreshMessage *read, const AttributedAddOrderRefreshMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time_ns[i] == written->source_time_ns[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_seq_num[i] == written->symbol_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->side == written->side);
  assert(read->order_idgtc_indicator == written->order_idgtc_indicator);
  assert(read->trade_session == written->trade_session);
  for (size_t i = 0; i < 5; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
}

/* Attributed Add Order Refresh Message: written and read back, then read and written back */
static void check_attributed_add_order_refresh_message(void) {
  AttributedAddOrderRefreshMessage sent;
  AttributedAddOrderRefreshMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_attributed_add_order_refresh_message(&sent);
  assert(encode_attributed_add_order_refresh_message(&sent, wire, 0) == 36);
  assert(decode_attributed_add_order_refresh_message(&got, wire, 0) == 36);
  equal_attributed_add_order_refresh_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_attributed_add_order_refresh_message(&got, wire, 0) == 36);
  assert(encode_attributed_add_order_refresh_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_send_time();
  check_packet_header();
  check_message_header();
  check_add_order_message();
  check_modify_order_message();
  check_delete_order_message();
  check_execution_message();
  check_imbalance_message();
  check_add_order_refresh_message();
  check_attributed_add_order_message();
  check_attributed_add_order_refresh_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
