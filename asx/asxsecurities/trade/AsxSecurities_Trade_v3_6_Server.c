// asx/asxsecurities/trade/AsxSecurities_Trade_v3_6_Server.c
/*
 * Australian Securities Exchange Asx Trade
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
 *   - a length prefix framing what follows
 *   - a field read in bits
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

/* ---- Server Packet Header: 3 bytes ------------------------------------------- */

/* Packet header of a packet sent by the server */
typedef struct {
  uint8_t packet_length[2];    /* bytes 0 to 1 */
  uint8_t server_packet_type;  /* byte 2 */
} ServerPacketHeader;

/* any Server Packet Header at all: every byte one the checker chooses */
static void any_server_packet_header(ServerPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  record->server_packet_type = arbitrary();
}

/* Server Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_server_packet_header(const ServerPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  wire[at++] = record->server_packet_type;

  return at;
}

/* Server Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_server_packet_header(ServerPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  record->server_packet_type = wire[at++];

  return at;
}

/* what was read of Server Packet Header is what was written, byte for byte */
static void equal_server_packet_header(const ServerPacketHeader *read, const ServerPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  assert(read->server_packet_type == written->server_packet_type);
}

/* Server Packet Header: written and read back, then read and written back */
static void check_server_packet_header(void) {
  ServerPacketHeader sent;
  ServerPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_server_packet_header(&sent);
  assert(encode_server_packet_header(&sent, wire, 0) == 3);
  assert(decode_server_packet_header(&got, wire, 0) == 3);
  equal_server_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_server_packet_header(&got, wire, 0) == 3);
  assert(encode_server_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Accepted Packet: 30 bytes ----------------------------------------- */

/* The SoupBinTCP server sends a Login Accepted Packet in response to receiving a valid Login Request from the client */
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

/* The SoupBinTCP server sends this packet in response to an invalid Login Request Packet from the client */
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

/* ---- Regulatory Data: 44 bytes ----------------------------------------------- */

/* Regulatory Data */
typedef struct {
  uint8_t capacity_of_participant;  /* byte 0 */
  uint8_t directed_wholesale;       /* byte 1 */
  uint8_t execution_venue[4];       /* bytes 2 to 5 */
  uint8_t intermediary_id[10];      /* bytes 6 to 15 */
  uint8_t order_origin[20];         /* bytes 16 to 35 */
  uint8_t filler[8];                /* bytes 36 to 43 */
} RegulatoryData;

/* any Regulatory Data at all: every byte one the checker chooses */
static void any_regulatory_data(RegulatoryData *record) {
  record->capacity_of_participant = arbitrary();
  record->directed_wholesale = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->intermediary_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->order_origin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->filler[i] = arbitrary(); }
}

/* Regulatory Data to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_regulatory_data(const RegulatoryData *record, uint8_t *wire, size_t at) {
  wire[at++] = record->capacity_of_participant;
  wire[at++] = record->directed_wholesale;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_venue[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->intermediary_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->order_origin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->filler[i]; }

  return at;
}

/* Regulatory Data off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_regulatory_data(RegulatoryData *record, const uint8_t *wire, size_t at) {
  record->capacity_of_participant = wire[at++];
  record->directed_wholesale = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->intermediary_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->order_origin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->filler[i] = wire[at++]; }

  return at;
}

/* what was read of Regulatory Data is what was written, byte for byte */
static void equal_regulatory_data(const RegulatoryData *read, const RegulatoryData *written) {
  assert(read->capacity_of_participant == written->capacity_of_participant);
  assert(read->directed_wholesale == written->directed_wholesale);
  for (size_t i = 0; i < 4; i++) { assert(read->execution_venue[i] == written->execution_venue[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->intermediary_id[i] == written->intermediary_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->order_origin[i] == written->order_origin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->filler[i] == written->filler[i]); }
}

/* Regulatory Data: written and read back, then read and written back */
static void check_regulatory_data(void) {
  RegulatoryData sent;
  RegulatoryData got;
  uint8_t wire[44];
  uint8_t again[44];

  any_regulatory_data(&sent);
  assert(encode_regulatory_data(&sent, wire, 0) == 44);
  assert(decode_regulatory_data(&got, wire, 0) == 44);
  equal_regulatory_data(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_regulatory_data(&got, wire, 0) == 44);
  assert(encode_regulatory_data(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Accepted Message: 173 bytes --------------------------------------- */

/* The Order Accepted message acknowledges the receipt and acceptance of a valid Enter Order message. The data fields from the Enter Order message are echoed back in the Order Accepted message, but some of the accepted values may differ from the entered values for some fields, depending on the state of the order. If the order for example traded immediately at entry, the Order Accepted message will show the state of the order after the trade. */
typedef struct {
  uint8_t timestamp_nanoseconds[8];        /* bytes 0 to 7 */
  uint8_t order_token[14];                 /* bytes 8 to 21 */
  uint8_t order_book_id[4];                /* bytes 22 to 25 */
  uint8_t side;                            /* byte 26 */
  uint8_t order_id[8];                     /* bytes 27 to 34 */
  uint8_t quantity[8];                     /* bytes 35 to 42 */
  uint8_t price[4];                        /* bytes 43 to 46 */
  uint8_t time_in_force;                   /* byte 47 */
  uint8_t open_close;                      /* byte 48 */
  uint8_t client_account[10];              /* bytes 49 to 58 */
  uint8_t order_state;                     /* byte 59 */
  uint8_t customer_info[15];               /* bytes 60 to 74 */
  uint8_t exchange_info[32];               /* bytes 75 to 106 */
  uint8_t clearing_participant;            /* byte 107 */
  uint8_t crossing_key[4];                 /* bytes 108 to 111 */
  RegulatoryData regulatory_data;          /* bytes 112 to 155 */
  uint8_t ouch_order_type;                 /* byte 156 */
  uint8_t short_sell_quantity[8];          /* bytes 157 to 164 */
  uint8_t minimum_acceptable_quantity[8];  /* bytes 165 to 172 */
} OrderAcceptedMessage;

/* any Order Accepted Message at all: every byte one the checker chooses */
static void any_order_accepted_message(OrderAcceptedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->open_close = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->client_account[i] = arbitrary(); }
  record->order_state = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->exchange_info[i] = arbitrary(); }
  record->clearing_participant = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->crossing_key[i] = arbitrary(); }
  any_regulatory_data(&record->regulatory_data);
  record->ouch_order_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->short_sell_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_acceptable_quantity[i] = arbitrary(); }
}

/* Order Accepted Message to the wire: 173 bytes from at, returning where the next byte goes */
static size_t encode_order_accepted_message(const OrderAcceptedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->client_account[i]; }
  wire[at++] = record->order_state;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->customer_info[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->exchange_info[i]; }
  wire[at++] = record->clearing_participant;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->crossing_key[i]; }
  at = encode_regulatory_data(&record->regulatory_data, wire, at);
  wire[at++] = record->ouch_order_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->short_sell_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_acceptable_quantity[i]; }

  return at;
}

/* Order Accepted Message off the wire: 173 bytes from at, returning where the next byte lies */
static size_t decode_order_accepted_message(OrderAcceptedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->open_close = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->client_account[i] = wire[at++]; }
  record->order_state = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->exchange_info[i] = wire[at++]; }
  record->clearing_participant = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->crossing_key[i] = wire[at++]; }
  at = decode_regulatory_data(&record->regulatory_data, wire, at);
  record->ouch_order_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->short_sell_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_acceptable_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Order Accepted Message is what was written, byte for byte */
static void equal_order_accepted_message(const OrderAcceptedMessage *read, const OrderAcceptedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 10; i++) { assert(read->client_account[i] == written->client_account[i]); }
  assert(read->order_state == written->order_state);
  for (size_t i = 0; i < 15; i++) { assert(read->customer_info[i] == written->customer_info[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->exchange_info[i] == written->exchange_info[i]); }
  assert(read->clearing_participant == written->clearing_participant);
  for (size_t i = 0; i < 4; i++) { assert(read->crossing_key[i] == written->crossing_key[i]); }
  equal_regulatory_data(&read->regulatory_data, &written->regulatory_data);
  assert(read->ouch_order_type == written->ouch_order_type);
  for (size_t i = 0; i < 8; i++) { assert(read->short_sell_quantity[i] == written->short_sell_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_acceptable_quantity[i] == written->minimum_acceptable_quantity[i]); }
}

/* Order Accepted Message: written and read back, then read and written back */
static void check_order_accepted_message(void) {
  OrderAcceptedMessage sent;
  OrderAcceptedMessage got;
  uint8_t wire[173];
  uint8_t again[173];

  any_order_accepted_message(&sent);
  assert(encode_order_accepted_message(&sent, wire, 0) == 173);
  assert(decode_order_accepted_message(&got, wire, 0) == 173);
  equal_order_accepted_message(&got, &sent);

  for (size_t i = 0; i < 173; i++) { wire[i] = arbitrary(); }
  assert(decode_order_accepted_message(&got, wire, 0) == 173);
  assert(encode_order_accepted_message(&got, again, 0) == 173);
  for (size_t i = 0; i < 173; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Rejected Message: 26 bytes ---------------------------------------- */

/* This message is returned when an Enter Order, Replace Order, Cancel Order or Cancel By Order ID message is rejected */
typedef struct {
  uint8_t timestamp_nanoseconds[8];  /* bytes 0 to 7 */
  uint8_t order_token[14];           /* bytes 8 to 21 */
  uint8_t reject_code[4];            /* bytes 22 to 25 */
} OrderRejectedMessage;

/* any Order Rejected Message at all: every byte one the checker chooses */
static void any_order_rejected_message(OrderRejectedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = arbitrary(); }
}

/* Order Rejected Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_order_rejected_message(const OrderRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reject_code[i]; }

  return at;
}

/* Order Rejected Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_order_rejected_message(OrderRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = wire[at++]; }

  return at;
}

/* what was read of Order Rejected Message is what was written, byte for byte */
static void equal_order_rejected_message(const OrderRejectedMessage *read, const OrderRejectedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
}

/* Order Rejected Message: written and read back, then read and written back */
static void check_order_rejected_message(void) {
  OrderRejectedMessage sent;
  OrderRejectedMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_order_rejected_message(&sent);
  assert(encode_order_rejected_message(&sent, wire, 0) == 26);
  assert(decode_order_rejected_message(&got, wire, 0) == 26);
  equal_order_rejected_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_order_rejected_message(&got, wire, 0) == 26);
  assert(encode_order_rejected_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replaced Message: 187 bytes --------------------------------------- */

/* The Order Replaced message acknowledges the receipt and acceptance of a valid Replace Order message. */
typedef struct {
  uint8_t timestamp_nanoseconds[8];        /* bytes 0 to 7 */
  uint8_t replacement_order_token[14];     /* bytes 8 to 21 */
  uint8_t previous_order_token[14];        /* bytes 22 to 35 */
  uint8_t order_book_id[4];                /* bytes 36 to 39 */
  uint8_t side;                            /* byte 40 */
  uint8_t order_id[8];                     /* bytes 41 to 48 */
  uint8_t quantity[8];                     /* bytes 49 to 56 */
  uint8_t price[4];                        /* bytes 57 to 60 */
  uint8_t time_in_force;                   /* byte 61 */
  uint8_t open_close;                      /* byte 62 */
  uint8_t client_account[10];              /* bytes 63 to 72 */
  uint8_t order_state;                     /* byte 73 */
  uint8_t customer_info[15];               /* bytes 74 to 88 */
  uint8_t exchange_info[32];               /* bytes 89 to 120 */
  uint8_t clearing_participant;            /* byte 121 */
  uint8_t crossing_key[4];                 /* bytes 122 to 125 */
  RegulatoryData regulatory_data;          /* bytes 126 to 169 */
  uint8_t ouch_order_type;                 /* byte 170 */
  uint8_t short_sell_quantity[8];          /* bytes 171 to 178 */
  uint8_t minimum_acceptable_quantity[8];  /* bytes 179 to 186 */
} OrderReplacedMessage;

/* any Order Replaced Message at all: every byte one the checker chooses */
static void any_order_replaced_message(OrderReplacedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->replacement_order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->previous_order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->open_close = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->client_account[i] = arbitrary(); }
  record->order_state = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->exchange_info[i] = arbitrary(); }
  record->clearing_participant = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->crossing_key[i] = arbitrary(); }
  any_regulatory_data(&record->regulatory_data);
  record->ouch_order_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->short_sell_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_acceptable_quantity[i] = arbitrary(); }
}

/* Order Replaced Message to the wire: 187 bytes from at, returning where the next byte goes */
static size_t encode_order_replaced_message(const OrderReplacedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->replacement_order_token[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->previous_order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->client_account[i]; }
  wire[at++] = record->order_state;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->customer_info[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->exchange_info[i]; }
  wire[at++] = record->clearing_participant;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->crossing_key[i]; }
  at = encode_regulatory_data(&record->regulatory_data, wire, at);
  wire[at++] = record->ouch_order_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->short_sell_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_acceptable_quantity[i]; }

  return at;
}

/* Order Replaced Message off the wire: 187 bytes from at, returning where the next byte lies */
static size_t decode_order_replaced_message(OrderReplacedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->replacement_order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->previous_order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->open_close = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->client_account[i] = wire[at++]; }
  record->order_state = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->exchange_info[i] = wire[at++]; }
  record->clearing_participant = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->crossing_key[i] = wire[at++]; }
  at = decode_regulatory_data(&record->regulatory_data, wire, at);
  record->ouch_order_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->short_sell_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_acceptable_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replaced Message is what was written, byte for byte */
static void equal_order_replaced_message(const OrderReplacedMessage *read, const OrderReplacedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->replacement_order_token[i] == written->replacement_order_token[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->previous_order_token[i] == written->previous_order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 10; i++) { assert(read->client_account[i] == written->client_account[i]); }
  assert(read->order_state == written->order_state);
  for (size_t i = 0; i < 15; i++) { assert(read->customer_info[i] == written->customer_info[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->exchange_info[i] == written->exchange_info[i]); }
  assert(read->clearing_participant == written->clearing_participant);
  for (size_t i = 0; i < 4; i++) { assert(read->crossing_key[i] == written->crossing_key[i]); }
  equal_regulatory_data(&read->regulatory_data, &written->regulatory_data);
  assert(read->ouch_order_type == written->ouch_order_type);
  for (size_t i = 0; i < 8; i++) { assert(read->short_sell_quantity[i] == written->short_sell_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_acceptable_quantity[i] == written->minimum_acceptable_quantity[i]); }
}

/* Order Replaced Message: written and read back, then read and written back */
static void check_order_replaced_message(void) {
  OrderReplacedMessage sent;
  OrderReplacedMessage got;
  uint8_t wire[187];
  uint8_t again[187];

  any_order_replaced_message(&sent);
  assert(encode_order_replaced_message(&sent, wire, 0) == 187);
  assert(decode_order_replaced_message(&got, wire, 0) == 187);
  equal_order_replaced_message(&got, &sent);

  for (size_t i = 0; i < 187; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replaced_message(&got, wire, 0) == 187);
  assert(encode_order_replaced_message(&got, again, 0) == 187);
  for (size_t i = 0; i < 187; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancelled Message: 36 bytes --------------------------------------- */

/* The Order Cancelled message informs the ASX Trade OUCH user that an order has been cancelled. This could be to acknowledge a Cancel Order or Cancel By Order Id message, or it could be as a result of system cancellation of an order. */
typedef struct {
  uint8_t timestamp_nanoseconds[8];  /* bytes 0 to 7 */
  uint8_t order_token[14];           /* bytes 8 to 21 */
  uint8_t order_book_id[4];          /* bytes 22 to 25 */
  uint8_t side;                      /* byte 26 */
  uint8_t order_id[8];               /* bytes 27 to 34 */
  uint8_t reason;                    /* byte 35 */
} OrderCancelledMessage;

/* any Order Cancelled Message at all: every byte one the checker chooses */
static void any_order_cancelled_message(OrderCancelledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp_nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->reason = arbitrary();
}

/* Order Cancelled Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_order_cancelled_message(const OrderCancelledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp_nanoseconds[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->reason;

  return at;
}

/* Order Cancelled Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_order_cancelled_message(OrderCancelledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp_nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->reason = wire[at++];

  return at;
}

/* what was read of Order Cancelled Message is what was written, byte for byte */
static void equal_order_cancelled_message(const OrderCancelledMessage *read, const OrderCancelledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp_nanoseconds[i] == written->timestamp_nanoseconds[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->reason == written->reason);
}

/* Order Cancelled Message: written and read back, then read and written back */
static void check_order_cancelled_message(void) {
  OrderCancelledMessage sent;
  OrderCancelledMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_order_cancelled_message(&sent);
  assert(encode_order_cancelled_message(&sent, wire, 0) == 36);
  assert(decode_order_cancelled_message(&got, wire, 0) == 36);
  equal_order_cancelled_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancelled_message(&got, wire, 0) == 36);
  assert(encode_order_cancelled_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_regulatory_data();
  check_order_accepted_message();
  check_order_rejected_message();
  check_order_replaced_message();
  check_order_cancelled_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
