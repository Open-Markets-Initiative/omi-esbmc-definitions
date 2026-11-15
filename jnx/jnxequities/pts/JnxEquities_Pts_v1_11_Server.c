// jnx/jnxequities/pts/JnxEquities_Pts_v1_11_Server.c
/*
 * Japannext Securities
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

/* ---- System Event Message: 9 bytes ------------------------------------------- */

/* A System Event Message signals a Japannext PTS system-wide event */
typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t system_event;  /* byte 8 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->system_event = arbitrary();
}

/* System Event Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->system_event;

  return at;
}

/* System Event Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->system_event = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->system_event == written->system_event);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 9);
  assert(decode_system_event_message(&got, wire, 0) == 9);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 9);
  assert(encode_system_event_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Accepted Message: 64 bytes ---------------------------------------- */

/* An Order Accepted Message acknowledges the receipt and acceptance of a valid Enter Order Message */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t order_token[4];        /* bytes 8 to 11 */
  uint8_t client_reference[10];  /* bytes 12 to 21 */
  uint8_t buy_sell_indicator;    /* byte 22 */
  uint8_t quantity[4];           /* bytes 23 to 26 */
  uint8_t orderbook_id[4];       /* bytes 27 to 30 */
  uint8_t group[4];              /* bytes 31 to 34 */
  uint8_t price[4];              /* bytes 35 to 38 */
  uint8_t time_in_force[4];      /* bytes 39 to 42 */
  uint8_t firm_id[4];            /* bytes 43 to 46 */
  uint8_t display;               /* byte 47 */
  uint8_t capacity;              /* byte 48 */
  uint8_t order_number[8];       /* bytes 49 to 56 */
  uint8_t minimum_quantity[4];   /* bytes 57 to 60 */
  uint8_t order_state;           /* byte 61 */
  uint8_t order_classification;  /* byte 62 */
  uint8_t cash_margin_type;      /* byte 63 */
} OrderAcceptedMessage;

/* any Order Accepted Message at all: every byte one the checker chooses */
static void any_order_accepted_message(OrderAcceptedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->client_reference[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  record->display = arbitrary();
  record->capacity = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = arbitrary(); }
  record->order_state = arbitrary();
  record->order_classification = arbitrary();
  record->cash_margin_type = arbitrary();
}

/* Order Accepted Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_order_accepted_message(const OrderAcceptedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->client_reference[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_in_force[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  wire[at++] = record->display;
  wire[at++] = record->capacity;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity[i]; }
  wire[at++] = record->order_state;
  wire[at++] = record->order_classification;
  wire[at++] = record->cash_margin_type;

  return at;
}

/* Order Accepted Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_order_accepted_message(OrderAcceptedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->client_reference[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  record->display = wire[at++];
  record->capacity = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = wire[at++]; }
  record->order_state = wire[at++];
  record->order_classification = wire[at++];
  record->cash_margin_type = wire[at++];

  return at;
}

/* what was read of Order Accepted Message is what was written, byte for byte */
static void equal_order_accepted_message(const OrderAcceptedMessage *read, const OrderAcceptedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->client_reference[i] == written->client_reference[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  assert(read->display == written->display);
  assert(read->capacity == written->capacity);
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
  assert(read->order_state == written->order_state);
  assert(read->order_classification == written->order_classification);
  assert(read->cash_margin_type == written->cash_margin_type);
}

/* Order Accepted Message: written and read back, then read and written back */
static void check_order_accepted_message(void) {
  OrderAcceptedMessage sent;
  OrderAcceptedMessage got;
  uint8_t wire[64];
  uint8_t again[64];

  any_order_accepted_message(&sent);
  assert(encode_order_accepted_message(&sent, wire, 0) == 64);
  assert(decode_order_accepted_message(&got, wire, 0) == 64);
  equal_order_accepted_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_order_accepted_message(&got, wire, 0) == 64);
  assert(encode_order_accepted_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replaced Message: 51 bytes ---------------------------------------- */

/* An Order Replaced Message acknowledges the receipt and acceptance of a valid Replace Order Message */
typedef struct {
  uint8_t timestamp[8];                /* bytes 0 to 7 */
  uint8_t replacement_order_token[4];  /* bytes 8 to 11 */
  uint8_t buy_sell_indicator;          /* byte 12 */
  uint8_t quantity[4];                 /* bytes 13 to 16 */
  uint8_t orderbook_id[4];             /* bytes 17 to 20 */
  uint8_t group[4];                    /* bytes 21 to 24 */
  uint8_t price[4];                    /* bytes 25 to 28 */
  uint8_t time_in_force[4];            /* bytes 29 to 32 */
  uint8_t display;                     /* byte 33 */
  uint8_t order_number[8];             /* bytes 34 to 41 */
  uint8_t minimum_quantity[4];         /* bytes 42 to 45 */
  uint8_t order_state;                 /* byte 46 */
  uint8_t previous_order_token[4];     /* bytes 47 to 50 */
} OrderReplacedMessage;

/* any Order Replaced Message at all: every byte one the checker chooses */
static void any_order_replaced_message(OrderReplacedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->replacement_order_token[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = arbitrary(); }
  record->display = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = arbitrary(); }
  record->order_state = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->previous_order_token[i] = arbitrary(); }
}

/* Order Replaced Message to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_order_replaced_message(const OrderReplacedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->replacement_order_token[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orderbook_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_in_force[i]; }
  wire[at++] = record->display;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity[i]; }
  wire[at++] = record->order_state;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_order_token[i]; }

  return at;
}

/* Order Replaced Message off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_order_replaced_message(OrderReplacedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->replacement_order_token[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orderbook_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = wire[at++]; }
  record->display = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = wire[at++]; }
  record->order_state = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->previous_order_token[i] = wire[at++]; }

  return at;
}

/* what was read of Order Replaced Message is what was written, byte for byte */
static void equal_order_replaced_message(const OrderReplacedMessage *read, const OrderReplacedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->replacement_order_token[i] == written->replacement_order_token[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orderbook_id[i] == written->orderbook_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  assert(read->display == written->display);
  for (size_t i = 0; i < 8; i++) { assert(read->order_number[i] == written->order_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
  assert(read->order_state == written->order_state);
  for (size_t i = 0; i < 4; i++) { assert(read->previous_order_token[i] == written->previous_order_token[i]); }
}

/* Order Replaced Message: written and read back, then read and written back */
static void check_order_replaced_message(void) {
  OrderReplacedMessage sent;
  OrderReplacedMessage got;
  uint8_t wire[51];
  uint8_t again[51];

  any_order_replaced_message(&sent);
  assert(encode_order_replaced_message(&sent, wire, 0) == 51);
  assert(decode_order_replaced_message(&got, wire, 0) == 51);
  equal_order_replaced_message(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replaced_message(&got, wire, 0) == 51);
  assert(encode_order_replaced_message(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Canceled Message: 17 bytes ---------------------------------------- */

/* An Order Canceled Message denotes that an order has been canceled */
typedef struct {
  uint8_t timestamp[8];           /* bytes 0 to 7 */
  uint8_t order_token[4];         /* bytes 8 to 11 */
  uint8_t decrement_quantity[4];  /* bytes 12 to 15 */
  uint8_t order_canceled_reason;  /* byte 16 */
} OrderCanceledMessage;

/* any Order Canceled Message at all: every byte one the checker chooses */
static void any_order_canceled_message(OrderCanceledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->decrement_quantity[i] = arbitrary(); }
  record->order_canceled_reason = arbitrary();
}

/* Order Canceled Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_order_canceled_message(const OrderCanceledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decrement_quantity[i]; }
  wire[at++] = record->order_canceled_reason;

  return at;
}

/* Order Canceled Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_order_canceled_message(OrderCanceledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->decrement_quantity[i] = wire[at++]; }
  record->order_canceled_reason = wire[at++];

  return at;
}

/* what was read of Order Canceled Message is what was written, byte for byte */
static void equal_order_canceled_message(const OrderCanceledMessage *read, const OrderCanceledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->decrement_quantity[i] == written->decrement_quantity[i]); }
  assert(read->order_canceled_reason == written->order_canceled_reason);
}

/* Order Canceled Message: written and read back, then read and written back */
static void check_order_canceled_message(void) {
  OrderCanceledMessage sent;
  OrderCanceledMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_order_canceled_message(&sent);
  assert(encode_order_canceled_message(&sent, wire, 0) == 17);
  assert(decode_order_canceled_message(&got, wire, 0) == 17);
  equal_order_canceled_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_order_canceled_message(&got, wire, 0) == 17);
  assert(encode_order_canceled_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Aiq Canceled Message: 26 bytes ------------------------------------ */

/* An Order AIQ Canceled Message denotes that an order has been canceled by Japannext PTS to prevent a self-trade */
typedef struct {
  uint8_t timestamp[8];                        /* bytes 0 to 7 */
  uint8_t order_token[4];                      /* bytes 8 to 11 */
  uint8_t decrement_quantity[4];               /* bytes 12 to 15 */
  uint8_t order_canceled_reason;               /* byte 16 */
  uint8_t quantity_prevented_from_trading[4];  /* bytes 17 to 20 */
  uint8_t execution_price[4];                  /* bytes 21 to 24 */
  uint8_t liquidity_indicator;                 /* byte 25 */
} OrderAiqCanceledMessage;

/* any Order Aiq Canceled Message at all: every byte one the checker chooses */
static void any_order_aiq_canceled_message(OrderAiqCanceledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->decrement_quantity[i] = arbitrary(); }
  record->order_canceled_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_prevented_from_trading[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = arbitrary(); }
  record->liquidity_indicator = arbitrary();
}

/* Order Aiq Canceled Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_order_aiq_canceled_message(const OrderAiqCanceledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decrement_quantity[i]; }
  wire[at++] = record->order_canceled_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_prevented_from_trading[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_price[i]; }
  wire[at++] = record->liquidity_indicator;

  return at;
}

/* Order Aiq Canceled Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_order_aiq_canceled_message(OrderAiqCanceledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->decrement_quantity[i] = wire[at++]; }
  record->order_canceled_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_prevented_from_trading[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = wire[at++]; }
  record->liquidity_indicator = wire[at++];

  return at;
}

/* what was read of Order Aiq Canceled Message is what was written, byte for byte */
static void equal_order_aiq_canceled_message(const OrderAiqCanceledMessage *read, const OrderAiqCanceledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->decrement_quantity[i] == written->decrement_quantity[i]); }
  assert(read->order_canceled_reason == written->order_canceled_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_prevented_from_trading[i] == written->quantity_prevented_from_trading[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
  assert(read->liquidity_indicator == written->liquidity_indicator);
}

/* Order Aiq Canceled Message: written and read back, then read and written back */
static void check_order_aiq_canceled_message(void) {
  OrderAiqCanceledMessage sent;
  OrderAiqCanceledMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_order_aiq_canceled_message(&sent);
  assert(encode_order_aiq_canceled_message(&sent, wire, 0) == 26);
  assert(decode_order_aiq_canceled_message(&got, wire, 0) == 26);
  equal_order_aiq_canceled_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_order_aiq_canceled_message(&got, wire, 0) == 26);
  assert(encode_order_aiq_canceled_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 29 bytes ---------------------------------------- */

/* An Order Executed Message denotes that all or part of an order has been executed */
typedef struct {
  uint8_t timestamp[8];          /* bytes 0 to 7 */
  uint8_t order_token[4];        /* bytes 8 to 11 */
  uint8_t executed_quantity[4];  /* bytes 12 to 15 */
  uint8_t execution_price[4];    /* bytes 16 to 19 */
  uint8_t liquidity_indicator;   /* byte 20 */
  uint8_t match_number[8];       /* bytes 21 to 28 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = arbitrary(); }
  record->liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_price[i]; }
  wire[at++] = record->liquidity_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Order Executed Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = wire[at++]; }
  record->liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
  assert(read->liquidity_indicator == written->liquidity_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 29);
  assert(decode_order_executed_message(&got, wire, 0) == 29);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 29);
  assert(encode_order_executed_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Rejected Message: 13 bytes ---------------------------------------- */

/* An Order Rejected Message may be sent in response to an Enter Order Message if the order cannot be accepted */
typedef struct {
  uint8_t timestamp[8];           /* bytes 0 to 7 */
  uint8_t order_token[4];         /* bytes 8 to 11 */
  uint8_t order_rejected_reason;  /* byte 12 */
} OrderRejectedMessage;

/* any Order Rejected Message at all: every byte one the checker chooses */
static void any_order_rejected_message(OrderRejectedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = arbitrary(); }
  record->order_rejected_reason = arbitrary();
}

/* Order Rejected Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_order_rejected_message(const OrderRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_token[i]; }
  wire[at++] = record->order_rejected_reason;

  return at;
}

/* Order Rejected Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_order_rejected_message(OrderRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = wire[at++]; }
  record->order_rejected_reason = wire[at++];

  return at;
}

/* what was read of Order Rejected Message is what was written, byte for byte */
static void equal_order_rejected_message(const OrderRejectedMessage *read, const OrderRejectedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_token[i] == written->order_token[i]); }
  assert(read->order_rejected_reason == written->order_rejected_reason);
}

/* Order Rejected Message: written and read back, then read and written back */
static void check_order_rejected_message(void) {
  OrderRejectedMessage sent;
  OrderRejectedMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_order_rejected_message(&sent);
  assert(encode_order_rejected_message(&sent, wire, 0) == 13);
  assert(decode_order_rejected_message(&got, wire, 0) == 13);
  equal_order_rejected_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_order_rejected_message(&got, wire, 0) == 13);
  assert(encode_order_rejected_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_system_event_message();
  check_order_accepted_message();
  check_order_replaced_message();
  check_order_canceled_message();
  check_order_aiq_canceled_message();
  check_order_executed_message();
  check_order_rejected_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
