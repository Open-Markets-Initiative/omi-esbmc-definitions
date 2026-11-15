// nasdaq/ntxequities/drop/NtxEquities_Drop_v2_3_Server.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Drop
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
 *   - a field filling what is left of what holds it
 *   - the dispatch that chooses a message by its type
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

/* ---- Server Packet Header: 1 byte -------------------------------------------- */

/* SoupTcp Packet Header sent by the server */
typedef struct {
  uint8_t server_packet_type;  /* byte 0 */
} ServerPacketHeader;

/* any Server Packet Header at all: every byte one the checker chooses */
static void any_server_packet_header(ServerPacketHeader *record) {
  record->server_packet_type = arbitrary();
}

/* Server Packet Header to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_server_packet_header(const ServerPacketHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->server_packet_type;

  return at;
}

/* Server Packet Header off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_server_packet_header(ServerPacketHeader *record, const uint8_t *wire, size_t at) {
  record->server_packet_type = wire[at++];

  return at;
}

/* what was read of Server Packet Header is what was written, byte for byte */
static void equal_server_packet_header(const ServerPacketHeader *read, const ServerPacketHeader *written) {
  assert(read->server_packet_type == written->server_packet_type);
}

/* Server Packet Header: written and read back, then read and written back */
static void check_server_packet_header(void) {
  ServerPacketHeader sent;
  ServerPacketHeader got;
  uint8_t wire[1];
  uint8_t again[1];

  any_server_packet_header(&sent);
  assert(encode_server_packet_header(&sent, wire, 0) == 1);
  assert(decode_server_packet_header(&got, wire, 0) == 1);
  equal_server_packet_header(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_server_packet_header(&got, wire, 0) == 1);
  assert(encode_server_packet_header(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Accepted Packet: 30 bytes ----------------------------------------- */

/* The SoupTcp server sends a Login Accepted Packet in response to receiving a valid Login Request  from the client. */
typedef struct {
  uint8_t accepted_session[10];          /* bytes 0 to 9 */
  uint8_t accepted_sequence_number[20];  /* bytes 10 to 29 */
} LoginAcceptedPacket;

/* any Login Accepted Packet at all: every byte one the checker chooses */
static void any_login_accepted_packet(LoginAcceptedPacket *record) {
  for (size_t i = 0; i < 10; i++) { record->accepted_session[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->accepted_sequence_number[i] = arbitrary(); }
}

/* Login Accepted Packet to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_login_accepted_packet(const LoginAcceptedPacket *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->accepted_session[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->accepted_sequence_number[i]; }

  return at;
}

/* Login Accepted Packet off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_login_accepted_packet(LoginAcceptedPacket *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->accepted_session[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->accepted_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Accepted Packet is what was written, byte for byte */
static void equal_login_accepted_packet(const LoginAcceptedPacket *read, const LoginAcceptedPacket *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->accepted_session[i] == written->accepted_session[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->accepted_sequence_number[i] == written->accepted_sequence_number[i]); }
}

/* Login Accepted Packet: written and read back, then read and written back */
static void check_login_accepted_packet(void) {
  LoginAcceptedPacket sent;
  LoginAcceptedPacket got;
  uint8_t wire[30];
  uint8_t again[30];

  any_login_accepted_packet(&sent);
  assert(encode_login_accepted_packet(&sent, wire, 0) == 30);
  assert(decode_login_accepted_packet(&got, wire, 0) == 30);
  equal_login_accepted_packet(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_login_accepted_packet(&got, wire, 0) == 30);
  assert(encode_login_accepted_packet(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Rejected Packet: 1 byte ------------------------------------------- */

/* The SoupTcp server sends this packet in response to an invalid Login Request Packet from the client. */
typedef struct {
  uint8_t reject_reason_code;  /* byte 0 */
} LoginRejectedPacket;

/* any Login Rejected Packet at all: every byte one the checker chooses */
static void any_login_rejected_packet(LoginRejectedPacket *record) {
  record->reject_reason_code = arbitrary();
}

/* Login Rejected Packet to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_login_rejected_packet(const LoginRejectedPacket *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reject_reason_code;

  return at;
}

/* Login Rejected Packet off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_login_rejected_packet(LoginRejectedPacket *record, const uint8_t *wire, size_t at) {
  record->reject_reason_code = wire[at++];

  return at;
}

/* what was read of Login Rejected Packet is what was written, byte for byte */
static void equal_login_rejected_packet(const LoginRejectedPacket *read, const LoginRejectedPacket *written) {
  assert(read->reject_reason_code == written->reject_reason_code);
}

/* Login Rejected Packet: written and read back, then read and written back */
static void check_login_rejected_packet(void) {
  LoginRejectedPacket sent;
  LoginRejectedPacket got;
  uint8_t wire[1];
  uint8_t again[1];

  any_login_rejected_packet(&sent);
  assert(encode_login_rejected_packet(&sent, wire, 0) == 1);
  assert(decode_login_rejected_packet(&got, wire, 0) == 1);
  equal_login_rejected_packet(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_login_rejected_packet(&got, wire, 0) == 1);
  assert(encode_login_rejected_packet(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequenced Message Header: 11 bytes -------------------------------------- */

/* Time Stamp and Type opening every Drop message line */
typedef struct {
  uint8_t time_stamp[9];  /* bytes 0 to 8 */
  uint8_t comma;          /* byte 9 */
  uint8_t message_type;   /* byte 10 */
} SequencedMessageHeader;

/* any Sequenced Message Header at all: every byte one the checker chooses */
static void any_sequenced_message_header(SequencedMessageHeader *record) {
  for (size_t i = 0; i < 9; i++) { record->time_stamp[i] = arbitrary(); }
  record->comma = arbitrary();
  record->message_type = arbitrary();
}

/* Sequenced Message Header to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_sequenced_message_header(const SequencedMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->time_stamp[i]; }
  wire[at++] = record->comma;
  wire[at++] = record->message_type;

  return at;
}

/* Sequenced Message Header off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_sequenced_message_header(SequencedMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 9; i++) { record->time_stamp[i] = wire[at++]; }
  record->comma = wire[at++];
  record->message_type = wire[at++];

  return at;
}

/* what was read of Sequenced Message Header is what was written, byte for byte */
static void equal_sequenced_message_header(const SequencedMessageHeader *read, const SequencedMessageHeader *written) {
  for (size_t i = 0; i < 9; i++) { assert(read->time_stamp[i] == written->time_stamp[i]); }
  assert(read->comma == written->comma);
  assert(read->message_type == written->message_type);
}

/* Sequenced Message Header: written and read back, then read and written back */
static void check_sequenced_message_header(void) {
  SequencedMessageHeader sent;
  SequencedMessageHeader got;
  uint8_t wire[11];
  uint8_t again[11];

  any_sequenced_message_header(&sent);
  assert(encode_sequenced_message_header(&sent, wire, 0) == 11);
  assert(decode_sequenced_message_header(&got, wire, 0) == 11);
  equal_sequenced_message_header(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_sequenced_message_header(&got, wire, 0) == 11);
  assert(encode_sequenced_message_header(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Accepted Message: 114 bytes ----------------------------------- */

/* New order accepted. */
typedef struct {
  uint8_t separator_1;              /* byte 0 */
  uint8_t source[6];                /* bytes 1 to 6 */
  uint8_t separator_2;              /* byte 7 */
  uint8_t user[4];                  /* bytes 8 to 11 */
  uint8_t separator_3;              /* byte 12 */
  uint8_t token[10];                /* bytes 13 to 22 */
  uint8_t separator_4;              /* byte 23 */
  uint8_t replaced_token[10];       /* bytes 24 to 33 */
  uint8_t separator_5;              /* byte 34 */
  uint8_t buy_sell;                 /* byte 35 */
  uint8_t separator_6;              /* byte 36 */
  uint8_t shares[6];                /* bytes 37 to 42 */
  uint8_t separator_7;              /* byte 43 */
  uint8_t stock[8];                 /* bytes 44 to 51 */
  uint8_t separator_8;              /* byte 52 */
  uint8_t price[11];                /* bytes 53 to 63 */
  uint8_t separator_9;              /* byte 64 */
  uint8_t firm[4];                  /* bytes 65 to 68 */
  uint8_t separator_10;             /* byte 69 */
  uint8_t reference[12];            /* bytes 70 to 81 */
  uint8_t separator_11;             /* byte 82 */
  uint8_t time_in_force[12];        /* bytes 83 to 94 */
  uint8_t separator_12;             /* byte 95 */
  uint8_t capacity;                 /* byte 96 */
  uint8_t separator_13;             /* byte 97 */
  uint8_t liquidity_code;           /* byte 98 */
  uint8_t separator_14;             /* byte 99 */
  uint8_t clearing_code;            /* byte 100 */
  uint8_t separator_15;             /* byte 101 */
  uint8_t iso_flag;                 /* byte 102 */
  uint8_t separator_16;             /* byte 103 */
  uint8_t display;                  /* byte 104 */
  uint8_t separator_17;             /* byte 105 */
  uint8_t bbo_weighting_indicator;  /* byte 106 */
  uint8_t separator_18;             /* byte 107 */
  uint8_t minimum_quantity[6];      /* bytes 108 to 113 */
} NewOrderAcceptedMessage;

/* any New Order Accepted Message at all: every byte one the checker chooses */
static void any_new_order_accepted_message(NewOrderAcceptedMessage *record) {
  record->separator_1 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->source[i] = arbitrary(); }
  record->separator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->user[i] = arbitrary(); }
  record->separator_3 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->token[i] = arbitrary(); }
  record->separator_4 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = arbitrary(); }
  record->separator_5 = arbitrary();
  record->buy_sell = arbitrary();
  record->separator_6 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  record->separator_7 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->separator_8 = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->price[i] = arbitrary(); }
  record->separator_9 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->firm[i] = arbitrary(); }
  record->separator_10 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->reference[i] = arbitrary(); }
  record->separator_11 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->time_in_force[i] = arbitrary(); }
  record->separator_12 = arbitrary();
  record->capacity = arbitrary();
  record->separator_13 = arbitrary();
  record->liquidity_code = arbitrary();
  record->separator_14 = arbitrary();
  record->clearing_code = arbitrary();
  record->separator_15 = arbitrary();
  record->iso_flag = arbitrary();
  record->separator_16 = arbitrary();
  record->display = arbitrary();
  record->separator_17 = arbitrary();
  record->bbo_weighting_indicator = arbitrary();
  record->separator_18 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->minimum_quantity[i] = arbitrary(); }
}

/* New Order Accepted Message to the wire: 114 bytes from at, returning where the next byte goes */
static size_t encode_new_order_accepted_message(const NewOrderAcceptedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->separator_1;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->source[i]; }
  wire[at++] = record->separator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user[i]; }
  wire[at++] = record->separator_3;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->token[i]; }
  wire[at++] = record->separator_4;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->replaced_token[i]; }
  wire[at++] = record->separator_5;
  wire[at++] = record->buy_sell;
  wire[at++] = record->separator_6;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  wire[at++] = record->separator_7;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->separator_8;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->separator_9;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->separator_10;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reference[i]; }
  wire[at++] = record->separator_11;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_in_force[i]; }
  wire[at++] = record->separator_12;
  wire[at++] = record->capacity;
  wire[at++] = record->separator_13;
  wire[at++] = record->liquidity_code;
  wire[at++] = record->separator_14;
  wire[at++] = record->clearing_code;
  wire[at++] = record->separator_15;
  wire[at++] = record->iso_flag;
  wire[at++] = record->separator_16;
  wire[at++] = record->display;
  wire[at++] = record->separator_17;
  wire[at++] = record->bbo_weighting_indicator;
  wire[at++] = record->separator_18;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->minimum_quantity[i]; }

  return at;
}

/* New Order Accepted Message off the wire: 114 bytes from at, returning where the next byte lies */
static size_t decode_new_order_accepted_message(NewOrderAcceptedMessage *record, const uint8_t *wire, size_t at) {
  record->separator_1 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->source[i] = wire[at++]; }
  record->separator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->user[i] = wire[at++]; }
  record->separator_3 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->token[i] = wire[at++]; }
  record->separator_4 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = wire[at++]; }
  record->separator_5 = wire[at++];
  record->buy_sell = wire[at++];
  record->separator_6 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  record->separator_7 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->separator_8 = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->price[i] = wire[at++]; }
  record->separator_9 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->firm[i] = wire[at++]; }
  record->separator_10 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->reference[i] = wire[at++]; }
  record->separator_11 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->time_in_force[i] = wire[at++]; }
  record->separator_12 = wire[at++];
  record->capacity = wire[at++];
  record->separator_13 = wire[at++];
  record->liquidity_code = wire[at++];
  record->separator_14 = wire[at++];
  record->clearing_code = wire[at++];
  record->separator_15 = wire[at++];
  record->iso_flag = wire[at++];
  record->separator_16 = wire[at++];
  record->display = wire[at++];
  record->separator_17 = wire[at++];
  record->bbo_weighting_indicator = wire[at++];
  record->separator_18 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->minimum_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of New Order Accepted Message is what was written, byte for byte */
static void equal_new_order_accepted_message(const NewOrderAcceptedMessage *read, const NewOrderAcceptedMessage *written) {
  assert(read->separator_1 == written->separator_1);
  for (size_t i = 0; i < 6; i++) { assert(read->source[i] == written->source[i]); }
  assert(read->separator_2 == written->separator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->user[i] == written->user[i]); }
  assert(read->separator_3 == written->separator_3);
  for (size_t i = 0; i < 10; i++) { assert(read->token[i] == written->token[i]); }
  assert(read->separator_4 == written->separator_4);
  for (size_t i = 0; i < 10; i++) { assert(read->replaced_token[i] == written->replaced_token[i]); }
  assert(read->separator_5 == written->separator_5);
  assert(read->buy_sell == written->buy_sell);
  assert(read->separator_6 == written->separator_6);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  assert(read->separator_7 == written->separator_7);
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->separator_8 == written->separator_8);
  for (size_t i = 0; i < 11; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->separator_9 == written->separator_9);
  for (size_t i = 0; i < 4; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->separator_10 == written->separator_10);
  for (size_t i = 0; i < 12; i++) { assert(read->reference[i] == written->reference[i]); }
  assert(read->separator_11 == written->separator_11);
  for (size_t i = 0; i < 12; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  assert(read->separator_12 == written->separator_12);
  assert(read->capacity == written->capacity);
  assert(read->separator_13 == written->separator_13);
  assert(read->liquidity_code == written->liquidity_code);
  assert(read->separator_14 == written->separator_14);
  assert(read->clearing_code == written->clearing_code);
  assert(read->separator_15 == written->separator_15);
  assert(read->iso_flag == written->iso_flag);
  assert(read->separator_16 == written->separator_16);
  assert(read->display == written->display);
  assert(read->separator_17 == written->separator_17);
  assert(read->bbo_weighting_indicator == written->bbo_weighting_indicator);
  assert(read->separator_18 == written->separator_18);
  for (size_t i = 0; i < 6; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
}

/* New Order Accepted Message: written and read back, then read and written back */
static void check_new_order_accepted_message(void) {
  NewOrderAcceptedMessage sent;
  NewOrderAcceptedMessage got;
  uint8_t wire[114];
  uint8_t again[114];

  any_new_order_accepted_message(&sent);
  assert(encode_new_order_accepted_message(&sent, wire, 0) == 114);
  assert(decode_new_order_accepted_message(&got, wire, 0) == 114);
  equal_new_order_accepted_message(&got, &sent);

  for (size_t i = 0; i < 114; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_accepted_message(&got, wire, 0) == 114);
  assert(encode_new_order_accepted_message(&got, again, 0) == 114);
  for (size_t i = 0; i < 114; i++) { assert(again[i] == wire[i]); }
}

/* ---- Existing Order Executed Message: 114 bytes ------------------------------ */

/* Existing order executed. */
typedef struct {
  uint8_t separator_1;              /* byte 0 */
  uint8_t source[6];                /* bytes 1 to 6 */
  uint8_t separator_2;              /* byte 7 */
  uint8_t user[4];                  /* bytes 8 to 11 */
  uint8_t separator_3;              /* byte 12 */
  uint8_t token[10];                /* bytes 13 to 22 */
  uint8_t separator_4;              /* byte 23 */
  uint8_t replaced_token[10];       /* bytes 24 to 33 */
  uint8_t separator_5;              /* byte 34 */
  uint8_t buy_sell;                 /* byte 35 */
  uint8_t separator_6;              /* byte 36 */
  uint8_t shares[6];                /* bytes 37 to 42 */
  uint8_t separator_7;              /* byte 43 */
  uint8_t stock[8];                 /* bytes 44 to 51 */
  uint8_t separator_8;              /* byte 52 */
  uint8_t price[11];                /* bytes 53 to 63 */
  uint8_t separator_9;              /* byte 64 */
  uint8_t firm[4];                  /* bytes 65 to 68 */
  uint8_t separator_10;             /* byte 69 */
  uint8_t reference[12];            /* bytes 70 to 81 */
  uint8_t separator_11;             /* byte 82 */
  uint8_t match_number[12];         /* bytes 83 to 94 */
  uint8_t separator_12;             /* byte 95 */
  uint8_t capacity;                 /* byte 96 */
  uint8_t separator_13;             /* byte 97 */
  uint8_t liquidity_code;           /* byte 98 */
  uint8_t separator_14;             /* byte 99 */
  uint8_t clearing_code;            /* byte 100 */
  uint8_t separator_15;             /* byte 101 */
  uint8_t iso_flag;                 /* byte 102 */
  uint8_t separator_16;             /* byte 103 */
  uint8_t display;                  /* byte 104 */
  uint8_t separator_17;             /* byte 105 */
  uint8_t bbo_weighting_indicator;  /* byte 106 */
  uint8_t separator_18;             /* byte 107 */
  uint8_t minimum_quantity[6];      /* bytes 108 to 113 */
} ExistingOrderExecutedMessage;

/* any Existing Order Executed Message at all: every byte one the checker chooses */
static void any_existing_order_executed_message(ExistingOrderExecutedMessage *record) {
  record->separator_1 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->source[i] = arbitrary(); }
  record->separator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->user[i] = arbitrary(); }
  record->separator_3 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->token[i] = arbitrary(); }
  record->separator_4 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = arbitrary(); }
  record->separator_5 = arbitrary();
  record->buy_sell = arbitrary();
  record->separator_6 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  record->separator_7 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->separator_8 = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->price[i] = arbitrary(); }
  record->separator_9 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->firm[i] = arbitrary(); }
  record->separator_10 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->reference[i] = arbitrary(); }
  record->separator_11 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = arbitrary(); }
  record->separator_12 = arbitrary();
  record->capacity = arbitrary();
  record->separator_13 = arbitrary();
  record->liquidity_code = arbitrary();
  record->separator_14 = arbitrary();
  record->clearing_code = arbitrary();
  record->separator_15 = arbitrary();
  record->iso_flag = arbitrary();
  record->separator_16 = arbitrary();
  record->display = arbitrary();
  record->separator_17 = arbitrary();
  record->bbo_weighting_indicator = arbitrary();
  record->separator_18 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->minimum_quantity[i] = arbitrary(); }
}

/* Existing Order Executed Message to the wire: 114 bytes from at, returning where the next byte goes */
static size_t encode_existing_order_executed_message(const ExistingOrderExecutedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->separator_1;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->source[i]; }
  wire[at++] = record->separator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user[i]; }
  wire[at++] = record->separator_3;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->token[i]; }
  wire[at++] = record->separator_4;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->replaced_token[i]; }
  wire[at++] = record->separator_5;
  wire[at++] = record->buy_sell;
  wire[at++] = record->separator_6;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  wire[at++] = record->separator_7;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->separator_8;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->separator_9;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->separator_10;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reference[i]; }
  wire[at++] = record->separator_11;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->separator_12;
  wire[at++] = record->capacity;
  wire[at++] = record->separator_13;
  wire[at++] = record->liquidity_code;
  wire[at++] = record->separator_14;
  wire[at++] = record->clearing_code;
  wire[at++] = record->separator_15;
  wire[at++] = record->iso_flag;
  wire[at++] = record->separator_16;
  wire[at++] = record->display;
  wire[at++] = record->separator_17;
  wire[at++] = record->bbo_weighting_indicator;
  wire[at++] = record->separator_18;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->minimum_quantity[i]; }

  return at;
}

/* Existing Order Executed Message off the wire: 114 bytes from at, returning where the next byte lies */
static size_t decode_existing_order_executed_message(ExistingOrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  record->separator_1 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->source[i] = wire[at++]; }
  record->separator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->user[i] = wire[at++]; }
  record->separator_3 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->token[i] = wire[at++]; }
  record->separator_4 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = wire[at++]; }
  record->separator_5 = wire[at++];
  record->buy_sell = wire[at++];
  record->separator_6 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  record->separator_7 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->separator_8 = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->price[i] = wire[at++]; }
  record->separator_9 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->firm[i] = wire[at++]; }
  record->separator_10 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->reference[i] = wire[at++]; }
  record->separator_11 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = wire[at++]; }
  record->separator_12 = wire[at++];
  record->capacity = wire[at++];
  record->separator_13 = wire[at++];
  record->liquidity_code = wire[at++];
  record->separator_14 = wire[at++];
  record->clearing_code = wire[at++];
  record->separator_15 = wire[at++];
  record->iso_flag = wire[at++];
  record->separator_16 = wire[at++];
  record->display = wire[at++];
  record->separator_17 = wire[at++];
  record->bbo_weighting_indicator = wire[at++];
  record->separator_18 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->minimum_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Existing Order Executed Message is what was written, byte for byte */
static void equal_existing_order_executed_message(const ExistingOrderExecutedMessage *read, const ExistingOrderExecutedMessage *written) {
  assert(read->separator_1 == written->separator_1);
  for (size_t i = 0; i < 6; i++) { assert(read->source[i] == written->source[i]); }
  assert(read->separator_2 == written->separator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->user[i] == written->user[i]); }
  assert(read->separator_3 == written->separator_3);
  for (size_t i = 0; i < 10; i++) { assert(read->token[i] == written->token[i]); }
  assert(read->separator_4 == written->separator_4);
  for (size_t i = 0; i < 10; i++) { assert(read->replaced_token[i] == written->replaced_token[i]); }
  assert(read->separator_5 == written->separator_5);
  assert(read->buy_sell == written->buy_sell);
  assert(read->separator_6 == written->separator_6);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  assert(read->separator_7 == written->separator_7);
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->separator_8 == written->separator_8);
  for (size_t i = 0; i < 11; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->separator_9 == written->separator_9);
  for (size_t i = 0; i < 4; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->separator_10 == written->separator_10);
  for (size_t i = 0; i < 12; i++) { assert(read->reference[i] == written->reference[i]); }
  assert(read->separator_11 == written->separator_11);
  for (size_t i = 0; i < 12; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->separator_12 == written->separator_12);
  assert(read->capacity == written->capacity);
  assert(read->separator_13 == written->separator_13);
  assert(read->liquidity_code == written->liquidity_code);
  assert(read->separator_14 == written->separator_14);
  assert(read->clearing_code == written->clearing_code);
  assert(read->separator_15 == written->separator_15);
  assert(read->iso_flag == written->iso_flag);
  assert(read->separator_16 == written->separator_16);
  assert(read->display == written->display);
  assert(read->separator_17 == written->separator_17);
  assert(read->bbo_weighting_indicator == written->bbo_weighting_indicator);
  assert(read->separator_18 == written->separator_18);
  for (size_t i = 0; i < 6; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
}

/* Existing Order Executed Message: written and read back, then read and written back */
static void check_existing_order_executed_message(void) {
  ExistingOrderExecutedMessage sent;
  ExistingOrderExecutedMessage got;
  uint8_t wire[114];
  uint8_t again[114];

  any_existing_order_executed_message(&sent);
  assert(encode_existing_order_executed_message(&sent, wire, 0) == 114);
  assert(decode_existing_order_executed_message(&got, wire, 0) == 114);
  equal_existing_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 114; i++) { wire[i] = arbitrary(); }
  assert(decode_existing_order_executed_message(&got, wire, 0) == 114);
  assert(encode_existing_order_executed_message(&got, again, 0) == 114);
  for (size_t i = 0; i < 114; i++) { assert(again[i] == wire[i]); }
}

/* ---- Existing Order Canceled Message: 114 bytes ------------------------------ */

/* Existing order canceled. */
typedef struct {
  uint8_t separator_1;              /* byte 0 */
  uint8_t source[6];                /* bytes 1 to 6 */
  uint8_t separator_2;              /* byte 7 */
  uint8_t user[4];                  /* bytes 8 to 11 */
  uint8_t separator_3;              /* byte 12 */
  uint8_t token[10];                /* bytes 13 to 22 */
  uint8_t separator_4;              /* byte 23 */
  uint8_t replaced_token[10];       /* bytes 24 to 33 */
  uint8_t separator_5;              /* byte 34 */
  uint8_t buy_sell;                 /* byte 35 */
  uint8_t separator_6;              /* byte 36 */
  uint8_t shares[6];                /* bytes 37 to 42 */
  uint8_t separator_7;              /* byte 43 */
  uint8_t stock[8];                 /* bytes 44 to 51 */
  uint8_t separator_8;              /* byte 52 */
  uint8_t price[11];                /* bytes 53 to 63 */
  uint8_t separator_9;              /* byte 64 */
  uint8_t firm[4];                  /* bytes 65 to 68 */
  uint8_t separator_10;             /* byte 69 */
  uint8_t reference[12];            /* bytes 70 to 81 */
  uint8_t separator_11;             /* byte 82 */
  uint8_t time_in_force[12];        /* bytes 83 to 94 */
  uint8_t separator_12;             /* byte 95 */
  uint8_t capacity;                 /* byte 96 */
  uint8_t separator_13;             /* byte 97 */
  uint8_t liquidity_code;           /* byte 98 */
  uint8_t separator_14;             /* byte 99 */
  uint8_t clearing_code;            /* byte 100 */
  uint8_t separator_15;             /* byte 101 */
  uint8_t iso_flag;                 /* byte 102 */
  uint8_t separator_16;             /* byte 103 */
  uint8_t display;                  /* byte 104 */
  uint8_t separator_17;             /* byte 105 */
  uint8_t bbo_weighting_indicator;  /* byte 106 */
  uint8_t separator_18;             /* byte 107 */
  uint8_t minimum_quantity[6];      /* bytes 108 to 113 */
} ExistingOrderCanceledMessage;

/* any Existing Order Canceled Message at all: every byte one the checker chooses */
static void any_existing_order_canceled_message(ExistingOrderCanceledMessage *record) {
  record->separator_1 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->source[i] = arbitrary(); }
  record->separator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->user[i] = arbitrary(); }
  record->separator_3 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->token[i] = arbitrary(); }
  record->separator_4 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = arbitrary(); }
  record->separator_5 = arbitrary();
  record->buy_sell = arbitrary();
  record->separator_6 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  record->separator_7 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->separator_8 = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->price[i] = arbitrary(); }
  record->separator_9 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->firm[i] = arbitrary(); }
  record->separator_10 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->reference[i] = arbitrary(); }
  record->separator_11 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->time_in_force[i] = arbitrary(); }
  record->separator_12 = arbitrary();
  record->capacity = arbitrary();
  record->separator_13 = arbitrary();
  record->liquidity_code = arbitrary();
  record->separator_14 = arbitrary();
  record->clearing_code = arbitrary();
  record->separator_15 = arbitrary();
  record->iso_flag = arbitrary();
  record->separator_16 = arbitrary();
  record->display = arbitrary();
  record->separator_17 = arbitrary();
  record->bbo_weighting_indicator = arbitrary();
  record->separator_18 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->minimum_quantity[i] = arbitrary(); }
}

/* Existing Order Canceled Message to the wire: 114 bytes from at, returning where the next byte goes */
static size_t encode_existing_order_canceled_message(const ExistingOrderCanceledMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->separator_1;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->source[i]; }
  wire[at++] = record->separator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user[i]; }
  wire[at++] = record->separator_3;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->token[i]; }
  wire[at++] = record->separator_4;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->replaced_token[i]; }
  wire[at++] = record->separator_5;
  wire[at++] = record->buy_sell;
  wire[at++] = record->separator_6;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  wire[at++] = record->separator_7;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->separator_8;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->separator_9;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->separator_10;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reference[i]; }
  wire[at++] = record->separator_11;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_in_force[i]; }
  wire[at++] = record->separator_12;
  wire[at++] = record->capacity;
  wire[at++] = record->separator_13;
  wire[at++] = record->liquidity_code;
  wire[at++] = record->separator_14;
  wire[at++] = record->clearing_code;
  wire[at++] = record->separator_15;
  wire[at++] = record->iso_flag;
  wire[at++] = record->separator_16;
  wire[at++] = record->display;
  wire[at++] = record->separator_17;
  wire[at++] = record->bbo_weighting_indicator;
  wire[at++] = record->separator_18;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->minimum_quantity[i]; }

  return at;
}

/* Existing Order Canceled Message off the wire: 114 bytes from at, returning where the next byte lies */
static size_t decode_existing_order_canceled_message(ExistingOrderCanceledMessage *record, const uint8_t *wire, size_t at) {
  record->separator_1 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->source[i] = wire[at++]; }
  record->separator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->user[i] = wire[at++]; }
  record->separator_3 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->token[i] = wire[at++]; }
  record->separator_4 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = wire[at++]; }
  record->separator_5 = wire[at++];
  record->buy_sell = wire[at++];
  record->separator_6 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  record->separator_7 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->separator_8 = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->price[i] = wire[at++]; }
  record->separator_9 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->firm[i] = wire[at++]; }
  record->separator_10 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->reference[i] = wire[at++]; }
  record->separator_11 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->time_in_force[i] = wire[at++]; }
  record->separator_12 = wire[at++];
  record->capacity = wire[at++];
  record->separator_13 = wire[at++];
  record->liquidity_code = wire[at++];
  record->separator_14 = wire[at++];
  record->clearing_code = wire[at++];
  record->separator_15 = wire[at++];
  record->iso_flag = wire[at++];
  record->separator_16 = wire[at++];
  record->display = wire[at++];
  record->separator_17 = wire[at++];
  record->bbo_weighting_indicator = wire[at++];
  record->separator_18 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->minimum_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Existing Order Canceled Message is what was written, byte for byte */
static void equal_existing_order_canceled_message(const ExistingOrderCanceledMessage *read, const ExistingOrderCanceledMessage *written) {
  assert(read->separator_1 == written->separator_1);
  for (size_t i = 0; i < 6; i++) { assert(read->source[i] == written->source[i]); }
  assert(read->separator_2 == written->separator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->user[i] == written->user[i]); }
  assert(read->separator_3 == written->separator_3);
  for (size_t i = 0; i < 10; i++) { assert(read->token[i] == written->token[i]); }
  assert(read->separator_4 == written->separator_4);
  for (size_t i = 0; i < 10; i++) { assert(read->replaced_token[i] == written->replaced_token[i]); }
  assert(read->separator_5 == written->separator_5);
  assert(read->buy_sell == written->buy_sell);
  assert(read->separator_6 == written->separator_6);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  assert(read->separator_7 == written->separator_7);
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->separator_8 == written->separator_8);
  for (size_t i = 0; i < 11; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->separator_9 == written->separator_9);
  for (size_t i = 0; i < 4; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->separator_10 == written->separator_10);
  for (size_t i = 0; i < 12; i++) { assert(read->reference[i] == written->reference[i]); }
  assert(read->separator_11 == written->separator_11);
  for (size_t i = 0; i < 12; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  assert(read->separator_12 == written->separator_12);
  assert(read->capacity == written->capacity);
  assert(read->separator_13 == written->separator_13);
  assert(read->liquidity_code == written->liquidity_code);
  assert(read->separator_14 == written->separator_14);
  assert(read->clearing_code == written->clearing_code);
  assert(read->separator_15 == written->separator_15);
  assert(read->iso_flag == written->iso_flag);
  assert(read->separator_16 == written->separator_16);
  assert(read->display == written->display);
  assert(read->separator_17 == written->separator_17);
  assert(read->bbo_weighting_indicator == written->bbo_weighting_indicator);
  assert(read->separator_18 == written->separator_18);
  for (size_t i = 0; i < 6; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
}

/* Existing Order Canceled Message: written and read back, then read and written back */
static void check_existing_order_canceled_message(void) {
  ExistingOrderCanceledMessage sent;
  ExistingOrderCanceledMessage got;
  uint8_t wire[114];
  uint8_t again[114];

  any_existing_order_canceled_message(&sent);
  assert(encode_existing_order_canceled_message(&sent, wire, 0) == 114);
  assert(decode_existing_order_canceled_message(&got, wire, 0) == 114);
  equal_existing_order_canceled_message(&got, &sent);

  for (size_t i = 0; i < 114; i++) { wire[i] = arbitrary(); }
  assert(decode_existing_order_canceled_message(&got, wire, 0) == 114);
  assert(encode_existing_order_canceled_message(&got, again, 0) == 114);
  for (size_t i = 0; i < 114; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Execution Broken Message: 114 bytes ---------------------------- */

/* Previous execution broken. */
typedef struct {
  uint8_t separator_1;              /* byte 0 */
  uint8_t source[6];                /* bytes 1 to 6 */
  uint8_t separator_2;              /* byte 7 */
  uint8_t user[4];                  /* bytes 8 to 11 */
  uint8_t separator_3;              /* byte 12 */
  uint8_t token[10];                /* bytes 13 to 22 */
  uint8_t separator_4;              /* byte 23 */
  uint8_t replaced_token[10];       /* bytes 24 to 33 */
  uint8_t separator_5;              /* byte 34 */
  uint8_t buy_sell;                 /* byte 35 */
  uint8_t separator_6;              /* byte 36 */
  uint8_t shares[6];                /* bytes 37 to 42 */
  uint8_t separator_7;              /* byte 43 */
  uint8_t stock[8];                 /* bytes 44 to 51 */
  uint8_t separator_8;              /* byte 52 */
  uint8_t price[11];                /* bytes 53 to 63 */
  uint8_t separator_9;              /* byte 64 */
  uint8_t firm[4];                  /* bytes 65 to 68 */
  uint8_t separator_10;             /* byte 69 */
  uint8_t reference[12];            /* bytes 70 to 81 */
  uint8_t separator_11;             /* byte 82 */
  uint8_t match_number[12];         /* bytes 83 to 94 */
  uint8_t separator_12;             /* byte 95 */
  uint8_t capacity;                 /* byte 96 */
  uint8_t separator_13;             /* byte 97 */
  uint8_t liquidity_code;           /* byte 98 */
  uint8_t separator_14;             /* byte 99 */
  uint8_t clearing_code;            /* byte 100 */
  uint8_t separator_15;             /* byte 101 */
  uint8_t iso_flag;                 /* byte 102 */
  uint8_t separator_16;             /* byte 103 */
  uint8_t display;                  /* byte 104 */
  uint8_t separator_17;             /* byte 105 */
  uint8_t bbo_weighting_indicator;  /* byte 106 */
  uint8_t separator_18;             /* byte 107 */
  uint8_t minimum_quantity[6];      /* bytes 108 to 113 */
} PreviousExecutionBrokenMessage;

/* any Previous Execution Broken Message at all: every byte one the checker chooses */
static void any_previous_execution_broken_message(PreviousExecutionBrokenMessage *record) {
  record->separator_1 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->source[i] = arbitrary(); }
  record->separator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->user[i] = arbitrary(); }
  record->separator_3 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->token[i] = arbitrary(); }
  record->separator_4 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = arbitrary(); }
  record->separator_5 = arbitrary();
  record->buy_sell = arbitrary();
  record->separator_6 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  record->separator_7 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->separator_8 = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->price[i] = arbitrary(); }
  record->separator_9 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->firm[i] = arbitrary(); }
  record->separator_10 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->reference[i] = arbitrary(); }
  record->separator_11 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = arbitrary(); }
  record->separator_12 = arbitrary();
  record->capacity = arbitrary();
  record->separator_13 = arbitrary();
  record->liquidity_code = arbitrary();
  record->separator_14 = arbitrary();
  record->clearing_code = arbitrary();
  record->separator_15 = arbitrary();
  record->iso_flag = arbitrary();
  record->separator_16 = arbitrary();
  record->display = arbitrary();
  record->separator_17 = arbitrary();
  record->bbo_weighting_indicator = arbitrary();
  record->separator_18 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->minimum_quantity[i] = arbitrary(); }
}

/* Previous Execution Broken Message to the wire: 114 bytes from at, returning where the next byte goes */
static size_t encode_previous_execution_broken_message(const PreviousExecutionBrokenMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->separator_1;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->source[i]; }
  wire[at++] = record->separator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user[i]; }
  wire[at++] = record->separator_3;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->token[i]; }
  wire[at++] = record->separator_4;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->replaced_token[i]; }
  wire[at++] = record->separator_5;
  wire[at++] = record->buy_sell;
  wire[at++] = record->separator_6;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  wire[at++] = record->separator_7;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->separator_8;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->separator_9;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->separator_10;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reference[i]; }
  wire[at++] = record->separator_11;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->separator_12;
  wire[at++] = record->capacity;
  wire[at++] = record->separator_13;
  wire[at++] = record->liquidity_code;
  wire[at++] = record->separator_14;
  wire[at++] = record->clearing_code;
  wire[at++] = record->separator_15;
  wire[at++] = record->iso_flag;
  wire[at++] = record->separator_16;
  wire[at++] = record->display;
  wire[at++] = record->separator_17;
  wire[at++] = record->bbo_weighting_indicator;
  wire[at++] = record->separator_18;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->minimum_quantity[i]; }

  return at;
}

/* Previous Execution Broken Message off the wire: 114 bytes from at, returning where the next byte lies */
static size_t decode_previous_execution_broken_message(PreviousExecutionBrokenMessage *record, const uint8_t *wire, size_t at) {
  record->separator_1 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->source[i] = wire[at++]; }
  record->separator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->user[i] = wire[at++]; }
  record->separator_3 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->token[i] = wire[at++]; }
  record->separator_4 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = wire[at++]; }
  record->separator_5 = wire[at++];
  record->buy_sell = wire[at++];
  record->separator_6 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  record->separator_7 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->separator_8 = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->price[i] = wire[at++]; }
  record->separator_9 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->firm[i] = wire[at++]; }
  record->separator_10 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->reference[i] = wire[at++]; }
  record->separator_11 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->match_number[i] = wire[at++]; }
  record->separator_12 = wire[at++];
  record->capacity = wire[at++];
  record->separator_13 = wire[at++];
  record->liquidity_code = wire[at++];
  record->separator_14 = wire[at++];
  record->clearing_code = wire[at++];
  record->separator_15 = wire[at++];
  record->iso_flag = wire[at++];
  record->separator_16 = wire[at++];
  record->display = wire[at++];
  record->separator_17 = wire[at++];
  record->bbo_weighting_indicator = wire[at++];
  record->separator_18 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->minimum_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Previous Execution Broken Message is what was written, byte for byte */
static void equal_previous_execution_broken_message(const PreviousExecutionBrokenMessage *read, const PreviousExecutionBrokenMessage *written) {
  assert(read->separator_1 == written->separator_1);
  for (size_t i = 0; i < 6; i++) { assert(read->source[i] == written->source[i]); }
  assert(read->separator_2 == written->separator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->user[i] == written->user[i]); }
  assert(read->separator_3 == written->separator_3);
  for (size_t i = 0; i < 10; i++) { assert(read->token[i] == written->token[i]); }
  assert(read->separator_4 == written->separator_4);
  for (size_t i = 0; i < 10; i++) { assert(read->replaced_token[i] == written->replaced_token[i]); }
  assert(read->separator_5 == written->separator_5);
  assert(read->buy_sell == written->buy_sell);
  assert(read->separator_6 == written->separator_6);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  assert(read->separator_7 == written->separator_7);
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->separator_8 == written->separator_8);
  for (size_t i = 0; i < 11; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->separator_9 == written->separator_9);
  for (size_t i = 0; i < 4; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->separator_10 == written->separator_10);
  for (size_t i = 0; i < 12; i++) { assert(read->reference[i] == written->reference[i]); }
  assert(read->separator_11 == written->separator_11);
  for (size_t i = 0; i < 12; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->separator_12 == written->separator_12);
  assert(read->capacity == written->capacity);
  assert(read->separator_13 == written->separator_13);
  assert(read->liquidity_code == written->liquidity_code);
  assert(read->separator_14 == written->separator_14);
  assert(read->clearing_code == written->clearing_code);
  assert(read->separator_15 == written->separator_15);
  assert(read->iso_flag == written->iso_flag);
  assert(read->separator_16 == written->separator_16);
  assert(read->display == written->display);
  assert(read->separator_17 == written->separator_17);
  assert(read->bbo_weighting_indicator == written->bbo_weighting_indicator);
  assert(read->separator_18 == written->separator_18);
  for (size_t i = 0; i < 6; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
}

/* Previous Execution Broken Message: written and read back, then read and written back */
static void check_previous_execution_broken_message(void) {
  PreviousExecutionBrokenMessage sent;
  PreviousExecutionBrokenMessage got;
  uint8_t wire[114];
  uint8_t again[114];

  any_previous_execution_broken_message(&sent);
  assert(encode_previous_execution_broken_message(&sent, wire, 0) == 114);
  assert(decode_previous_execution_broken_message(&got, wire, 0) == 114);
  equal_previous_execution_broken_message(&got, &sent);

  for (size_t i = 0; i < 114; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_execution_broken_message(&got, wire, 0) == 114);
  assert(encode_previous_execution_broken_message(&got, again, 0) == 114);
  for (size_t i = 0; i < 114; i++) { assert(again[i] == wire[i]); }
}

/* ---- Existing Order Replaced Message: 114 bytes ------------------------------ */

/* Existing order replaced. */
typedef struct {
  uint8_t separator_1;              /* byte 0 */
  uint8_t source[6];                /* bytes 1 to 6 */
  uint8_t separator_2;              /* byte 7 */
  uint8_t user[4];                  /* bytes 8 to 11 */
  uint8_t separator_3;              /* byte 12 */
  uint8_t token[10];                /* bytes 13 to 22 */
  uint8_t separator_4;              /* byte 23 */
  uint8_t replaced_token[10];       /* bytes 24 to 33 */
  uint8_t separator_5;              /* byte 34 */
  uint8_t buy_sell;                 /* byte 35 */
  uint8_t separator_6;              /* byte 36 */
  uint8_t shares[6];                /* bytes 37 to 42 */
  uint8_t separator_7;              /* byte 43 */
  uint8_t stock[8];                 /* bytes 44 to 51 */
  uint8_t separator_8;              /* byte 52 */
  uint8_t price[11];                /* bytes 53 to 63 */
  uint8_t separator_9;              /* byte 64 */
  uint8_t firm[4];                  /* bytes 65 to 68 */
  uint8_t separator_10;             /* byte 69 */
  uint8_t reference[12];            /* bytes 70 to 81 */
  uint8_t separator_11;             /* byte 82 */
  uint8_t time_in_force[12];        /* bytes 83 to 94 */
  uint8_t separator_12;             /* byte 95 */
  uint8_t capacity;                 /* byte 96 */
  uint8_t separator_13;             /* byte 97 */
  uint8_t liquidity_code;           /* byte 98 */
  uint8_t separator_14;             /* byte 99 */
  uint8_t clearing_code;            /* byte 100 */
  uint8_t separator_15;             /* byte 101 */
  uint8_t iso_flag;                 /* byte 102 */
  uint8_t separator_16;             /* byte 103 */
  uint8_t display;                  /* byte 104 */
  uint8_t separator_17;             /* byte 105 */
  uint8_t bbo_weighting_indicator;  /* byte 106 */
  uint8_t separator_18;             /* byte 107 */
  uint8_t minimum_quantity[6];      /* bytes 108 to 113 */
} ExistingOrderReplacedMessage;

/* any Existing Order Replaced Message at all: every byte one the checker chooses */
static void any_existing_order_replaced_message(ExistingOrderReplacedMessage *record) {
  record->separator_1 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->source[i] = arbitrary(); }
  record->separator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->user[i] = arbitrary(); }
  record->separator_3 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->token[i] = arbitrary(); }
  record->separator_4 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = arbitrary(); }
  record->separator_5 = arbitrary();
  record->buy_sell = arbitrary();
  record->separator_6 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  record->separator_7 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->separator_8 = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->price[i] = arbitrary(); }
  record->separator_9 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->firm[i] = arbitrary(); }
  record->separator_10 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->reference[i] = arbitrary(); }
  record->separator_11 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->time_in_force[i] = arbitrary(); }
  record->separator_12 = arbitrary();
  record->capacity = arbitrary();
  record->separator_13 = arbitrary();
  record->liquidity_code = arbitrary();
  record->separator_14 = arbitrary();
  record->clearing_code = arbitrary();
  record->separator_15 = arbitrary();
  record->iso_flag = arbitrary();
  record->separator_16 = arbitrary();
  record->display = arbitrary();
  record->separator_17 = arbitrary();
  record->bbo_weighting_indicator = arbitrary();
  record->separator_18 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->minimum_quantity[i] = arbitrary(); }
}

/* Existing Order Replaced Message to the wire: 114 bytes from at, returning where the next byte goes */
static size_t encode_existing_order_replaced_message(const ExistingOrderReplacedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->separator_1;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->source[i]; }
  wire[at++] = record->separator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user[i]; }
  wire[at++] = record->separator_3;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->token[i]; }
  wire[at++] = record->separator_4;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->replaced_token[i]; }
  wire[at++] = record->separator_5;
  wire[at++] = record->buy_sell;
  wire[at++] = record->separator_6;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  wire[at++] = record->separator_7;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->separator_8;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->separator_9;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->separator_10;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reference[i]; }
  wire[at++] = record->separator_11;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_in_force[i]; }
  wire[at++] = record->separator_12;
  wire[at++] = record->capacity;
  wire[at++] = record->separator_13;
  wire[at++] = record->liquidity_code;
  wire[at++] = record->separator_14;
  wire[at++] = record->clearing_code;
  wire[at++] = record->separator_15;
  wire[at++] = record->iso_flag;
  wire[at++] = record->separator_16;
  wire[at++] = record->display;
  wire[at++] = record->separator_17;
  wire[at++] = record->bbo_weighting_indicator;
  wire[at++] = record->separator_18;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->minimum_quantity[i]; }

  return at;
}

/* Existing Order Replaced Message off the wire: 114 bytes from at, returning where the next byte lies */
static size_t decode_existing_order_replaced_message(ExistingOrderReplacedMessage *record, const uint8_t *wire, size_t at) {
  record->separator_1 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->source[i] = wire[at++]; }
  record->separator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->user[i] = wire[at++]; }
  record->separator_3 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->token[i] = wire[at++]; }
  record->separator_4 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = wire[at++]; }
  record->separator_5 = wire[at++];
  record->buy_sell = wire[at++];
  record->separator_6 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  record->separator_7 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->separator_8 = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->price[i] = wire[at++]; }
  record->separator_9 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->firm[i] = wire[at++]; }
  record->separator_10 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->reference[i] = wire[at++]; }
  record->separator_11 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->time_in_force[i] = wire[at++]; }
  record->separator_12 = wire[at++];
  record->capacity = wire[at++];
  record->separator_13 = wire[at++];
  record->liquidity_code = wire[at++];
  record->separator_14 = wire[at++];
  record->clearing_code = wire[at++];
  record->separator_15 = wire[at++];
  record->iso_flag = wire[at++];
  record->separator_16 = wire[at++];
  record->display = wire[at++];
  record->separator_17 = wire[at++];
  record->bbo_weighting_indicator = wire[at++];
  record->separator_18 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->minimum_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Existing Order Replaced Message is what was written, byte for byte */
static void equal_existing_order_replaced_message(const ExistingOrderReplacedMessage *read, const ExistingOrderReplacedMessage *written) {
  assert(read->separator_1 == written->separator_1);
  for (size_t i = 0; i < 6; i++) { assert(read->source[i] == written->source[i]); }
  assert(read->separator_2 == written->separator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->user[i] == written->user[i]); }
  assert(read->separator_3 == written->separator_3);
  for (size_t i = 0; i < 10; i++) { assert(read->token[i] == written->token[i]); }
  assert(read->separator_4 == written->separator_4);
  for (size_t i = 0; i < 10; i++) { assert(read->replaced_token[i] == written->replaced_token[i]); }
  assert(read->separator_5 == written->separator_5);
  assert(read->buy_sell == written->buy_sell);
  assert(read->separator_6 == written->separator_6);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  assert(read->separator_7 == written->separator_7);
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->separator_8 == written->separator_8);
  for (size_t i = 0; i < 11; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->separator_9 == written->separator_9);
  for (size_t i = 0; i < 4; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->separator_10 == written->separator_10);
  for (size_t i = 0; i < 12; i++) { assert(read->reference[i] == written->reference[i]); }
  assert(read->separator_11 == written->separator_11);
  for (size_t i = 0; i < 12; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  assert(read->separator_12 == written->separator_12);
  assert(read->capacity == written->capacity);
  assert(read->separator_13 == written->separator_13);
  assert(read->liquidity_code == written->liquidity_code);
  assert(read->separator_14 == written->separator_14);
  assert(read->clearing_code == written->clearing_code);
  assert(read->separator_15 == written->separator_15);
  assert(read->iso_flag == written->iso_flag);
  assert(read->separator_16 == written->separator_16);
  assert(read->display == written->display);
  assert(read->separator_17 == written->separator_17);
  assert(read->bbo_weighting_indicator == written->bbo_weighting_indicator);
  assert(read->separator_18 == written->separator_18);
  for (size_t i = 0; i < 6; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
}

/* Existing Order Replaced Message: written and read back, then read and written back */
static void check_existing_order_replaced_message(void) {
  ExistingOrderReplacedMessage sent;
  ExistingOrderReplacedMessage got;
  uint8_t wire[114];
  uint8_t again[114];

  any_existing_order_replaced_message(&sent);
  assert(encode_existing_order_replaced_message(&sent, wire, 0) == 114);
  assert(decode_existing_order_replaced_message(&got, wire, 0) == 114);
  equal_existing_order_replaced_message(&got, &sent);

  for (size_t i = 0; i < 114; i++) { wire[i] = arbitrary(); }
  assert(decode_existing_order_replaced_message(&got, wire, 0) == 114);
  assert(encode_existing_order_replaced_message(&got, again, 0) == 114);
  for (size_t i = 0; i < 114; i++) { assert(again[i] == wire[i]); }
}

/* ---- Existing Order Modified Message: 114 bytes ------------------------------ */

/* Existing order modified. */
typedef struct {
  uint8_t separator_1;              /* byte 0 */
  uint8_t source[6];                /* bytes 1 to 6 */
  uint8_t separator_2;              /* byte 7 */
  uint8_t user[4];                  /* bytes 8 to 11 */
  uint8_t separator_3;              /* byte 12 */
  uint8_t token[10];                /* bytes 13 to 22 */
  uint8_t separator_4;              /* byte 23 */
  uint8_t replaced_token[10];       /* bytes 24 to 33 */
  uint8_t separator_5;              /* byte 34 */
  uint8_t buy_sell;                 /* byte 35 */
  uint8_t separator_6;              /* byte 36 */
  uint8_t shares[6];                /* bytes 37 to 42 */
  uint8_t separator_7;              /* byte 43 */
  uint8_t stock[8];                 /* bytes 44 to 51 */
  uint8_t separator_8;              /* byte 52 */
  uint8_t price[11];                /* bytes 53 to 63 */
  uint8_t separator_9;              /* byte 64 */
  uint8_t firm[4];                  /* bytes 65 to 68 */
  uint8_t separator_10;             /* byte 69 */
  uint8_t reference[12];            /* bytes 70 to 81 */
  uint8_t separator_11;             /* byte 82 */
  uint8_t time_in_force[12];        /* bytes 83 to 94 */
  uint8_t separator_12;             /* byte 95 */
  uint8_t capacity;                 /* byte 96 */
  uint8_t separator_13;             /* byte 97 */
  uint8_t liquidity_code;           /* byte 98 */
  uint8_t separator_14;             /* byte 99 */
  uint8_t clearing_code;            /* byte 100 */
  uint8_t separator_15;             /* byte 101 */
  uint8_t iso_flag;                 /* byte 102 */
  uint8_t separator_16;             /* byte 103 */
  uint8_t display;                  /* byte 104 */
  uint8_t separator_17;             /* byte 105 */
  uint8_t bbo_weighting_indicator;  /* byte 106 */
  uint8_t separator_18;             /* byte 107 */
  uint8_t minimum_quantity[6];      /* bytes 108 to 113 */
} ExistingOrderModifiedMessage;

/* any Existing Order Modified Message at all: every byte one the checker chooses */
static void any_existing_order_modified_message(ExistingOrderModifiedMessage *record) {
  record->separator_1 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->source[i] = arbitrary(); }
  record->separator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->user[i] = arbitrary(); }
  record->separator_3 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->token[i] = arbitrary(); }
  record->separator_4 = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = arbitrary(); }
  record->separator_5 = arbitrary();
  record->buy_sell = arbitrary();
  record->separator_6 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  record->separator_7 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  record->separator_8 = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->price[i] = arbitrary(); }
  record->separator_9 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->firm[i] = arbitrary(); }
  record->separator_10 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->reference[i] = arbitrary(); }
  record->separator_11 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->time_in_force[i] = arbitrary(); }
  record->separator_12 = arbitrary();
  record->capacity = arbitrary();
  record->separator_13 = arbitrary();
  record->liquidity_code = arbitrary();
  record->separator_14 = arbitrary();
  record->clearing_code = arbitrary();
  record->separator_15 = arbitrary();
  record->iso_flag = arbitrary();
  record->separator_16 = arbitrary();
  record->display = arbitrary();
  record->separator_17 = arbitrary();
  record->bbo_weighting_indicator = arbitrary();
  record->separator_18 = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->minimum_quantity[i] = arbitrary(); }
}

/* Existing Order Modified Message to the wire: 114 bytes from at, returning where the next byte goes */
static size_t encode_existing_order_modified_message(const ExistingOrderModifiedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->separator_1;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->source[i]; }
  wire[at++] = record->separator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user[i]; }
  wire[at++] = record->separator_3;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->token[i]; }
  wire[at++] = record->separator_4;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->replaced_token[i]; }
  wire[at++] = record->separator_5;
  wire[at++] = record->buy_sell;
  wire[at++] = record->separator_6;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  wire[at++] = record->separator_7;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  wire[at++] = record->separator_8;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->separator_9;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->separator_10;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reference[i]; }
  wire[at++] = record->separator_11;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_in_force[i]; }
  wire[at++] = record->separator_12;
  wire[at++] = record->capacity;
  wire[at++] = record->separator_13;
  wire[at++] = record->liquidity_code;
  wire[at++] = record->separator_14;
  wire[at++] = record->clearing_code;
  wire[at++] = record->separator_15;
  wire[at++] = record->iso_flag;
  wire[at++] = record->separator_16;
  wire[at++] = record->display;
  wire[at++] = record->separator_17;
  wire[at++] = record->bbo_weighting_indicator;
  wire[at++] = record->separator_18;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->minimum_quantity[i]; }

  return at;
}

/* Existing Order Modified Message off the wire: 114 bytes from at, returning where the next byte lies */
static size_t decode_existing_order_modified_message(ExistingOrderModifiedMessage *record, const uint8_t *wire, size_t at) {
  record->separator_1 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->source[i] = wire[at++]; }
  record->separator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->user[i] = wire[at++]; }
  record->separator_3 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->token[i] = wire[at++]; }
  record->separator_4 = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->replaced_token[i] = wire[at++]; }
  record->separator_5 = wire[at++];
  record->buy_sell = wire[at++];
  record->separator_6 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  record->separator_7 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  record->separator_8 = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->price[i] = wire[at++]; }
  record->separator_9 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->firm[i] = wire[at++]; }
  record->separator_10 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->reference[i] = wire[at++]; }
  record->separator_11 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->time_in_force[i] = wire[at++]; }
  record->separator_12 = wire[at++];
  record->capacity = wire[at++];
  record->separator_13 = wire[at++];
  record->liquidity_code = wire[at++];
  record->separator_14 = wire[at++];
  record->clearing_code = wire[at++];
  record->separator_15 = wire[at++];
  record->iso_flag = wire[at++];
  record->separator_16 = wire[at++];
  record->display = wire[at++];
  record->separator_17 = wire[at++];
  record->bbo_weighting_indicator = wire[at++];
  record->separator_18 = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->minimum_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Existing Order Modified Message is what was written, byte for byte */
static void equal_existing_order_modified_message(const ExistingOrderModifiedMessage *read, const ExistingOrderModifiedMessage *written) {
  assert(read->separator_1 == written->separator_1);
  for (size_t i = 0; i < 6; i++) { assert(read->source[i] == written->source[i]); }
  assert(read->separator_2 == written->separator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->user[i] == written->user[i]); }
  assert(read->separator_3 == written->separator_3);
  for (size_t i = 0; i < 10; i++) { assert(read->token[i] == written->token[i]); }
  assert(read->separator_4 == written->separator_4);
  for (size_t i = 0; i < 10; i++) { assert(read->replaced_token[i] == written->replaced_token[i]); }
  assert(read->separator_5 == written->separator_5);
  assert(read->buy_sell == written->buy_sell);
  assert(read->separator_6 == written->separator_6);
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  assert(read->separator_7 == written->separator_7);
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  assert(read->separator_8 == written->separator_8);
  for (size_t i = 0; i < 11; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->separator_9 == written->separator_9);
  for (size_t i = 0; i < 4; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->separator_10 == written->separator_10);
  for (size_t i = 0; i < 12; i++) { assert(read->reference[i] == written->reference[i]); }
  assert(read->separator_11 == written->separator_11);
  for (size_t i = 0; i < 12; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  assert(read->separator_12 == written->separator_12);
  assert(read->capacity == written->capacity);
  assert(read->separator_13 == written->separator_13);
  assert(read->liquidity_code == written->liquidity_code);
  assert(read->separator_14 == written->separator_14);
  assert(read->clearing_code == written->clearing_code);
  assert(read->separator_15 == written->separator_15);
  assert(read->iso_flag == written->iso_flag);
  assert(read->separator_16 == written->separator_16);
  assert(read->display == written->display);
  assert(read->separator_17 == written->separator_17);
  assert(read->bbo_weighting_indicator == written->bbo_weighting_indicator);
  assert(read->separator_18 == written->separator_18);
  for (size_t i = 0; i < 6; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
}

/* Existing Order Modified Message: written and read back, then read and written back */
static void check_existing_order_modified_message(void) {
  ExistingOrderModifiedMessage sent;
  ExistingOrderModifiedMessage got;
  uint8_t wire[114];
  uint8_t again[114];

  any_existing_order_modified_message(&sent);
  assert(encode_existing_order_modified_message(&sent, wire, 0) == 114);
  assert(decode_existing_order_modified_message(&got, wire, 0) == 114);
  equal_existing_order_modified_message(&got, &sent);

  for (size_t i = 0; i < 114; i++) { wire[i] = arbitrary(); }
  assert(decode_existing_order_modified_message(&got, wire, 0) == 114);
  assert(encode_existing_order_modified_message(&got, again, 0) == 114);
  for (size_t i = 0; i < 114; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_sequenced_message_header();
  check_new_order_accepted_message();
  check_existing_order_executed_message();
  check_existing_order_canceled_message();
  check_previous_execution_broken_message();
  check_existing_order_replaced_message();
  check_existing_order_modified_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
