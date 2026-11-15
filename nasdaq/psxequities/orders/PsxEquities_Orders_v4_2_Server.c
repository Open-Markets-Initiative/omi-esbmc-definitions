// nasdaq/psxequities/orders/PsxEquities_Orders_v4_2_Server.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Orders
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

typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
  uint8_t event_code;    /* byte 8 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->event_code == written->event_code);
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

/* ---- Accepted Message: 65 bytes ---------------------------------------------- */

typedef struct {
  uint8_t timestamp[8];                   /* bytes 0 to 7 */
  uint8_t order_token[14];                /* bytes 8 to 21 */
  uint8_t buy_sell_indicator;             /* byte 22 */
  uint8_t shares[4];                      /* bytes 23 to 26 */
  uint8_t stock[8];                       /* bytes 27 to 34 */
  uint8_t price[4];                       /* bytes 35 to 38 */
  uint8_t time_in_force[4];               /* bytes 39 to 42 */
  uint8_t firm[4];                        /* bytes 43 to 46 */
  uint8_t display;                        /* byte 47 */
  uint8_t order_reference_number[8];      /* bytes 48 to 55 */
  uint8_t capacity;                       /* byte 56 */
  uint8_t intermarket_sweep_eligibility;  /* byte 57 */
  uint8_t minimum_quantity[4];            /* bytes 58 to 61 */
  uint8_t cross_type;                     /* byte 62 */
  uint8_t order_state;                    /* byte 63 */
  uint8_t bbo_weight_indicator;           /* byte 64 */
} AcceptedMessage;

/* any Accepted Message at all: every byte one the checker chooses */
static void any_accepted_message(AcceptedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm[i] = arbitrary(); }
  record->display = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->capacity = arbitrary();
  record->intermarket_sweep_eligibility = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = arbitrary(); }
  record->cross_type = arbitrary();
  record->order_state = arbitrary();
  record->bbo_weight_indicator = arbitrary();
}

/* Accepted Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_accepted_message(const AcceptedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_in_force[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->display;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->capacity;
  wire[at++] = record->intermarket_sweep_eligibility;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity[i]; }
  wire[at++] = record->cross_type;
  wire[at++] = record->order_state;
  wire[at++] = record->bbo_weight_indicator;

  return at;
}

/* Accepted Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_accepted_message(AcceptedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm[i] = wire[at++]; }
  record->display = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->capacity = wire[at++];
  record->intermarket_sweep_eligibility = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = wire[at++]; }
  record->cross_type = wire[at++];
  record->order_state = wire[at++];
  record->bbo_weight_indicator = wire[at++];

  return at;
}

/* what was read of Accepted Message is what was written, byte for byte */
static void equal_accepted_message(const AcceptedMessage *read, const AcceptedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->display == written->display);
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->capacity == written->capacity);
  assert(read->intermarket_sweep_eligibility == written->intermarket_sweep_eligibility);
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
  assert(read->cross_type == written->cross_type);
  assert(read->order_state == written->order_state);
  assert(read->bbo_weight_indicator == written->bbo_weight_indicator);
}

/* Accepted Message: written and read back, then read and written back */
static void check_accepted_message(void) {
  AcceptedMessage sent;
  AcceptedMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_accepted_message(&sent);
  assert(encode_accepted_message(&sent, wire, 0) == 65);
  assert(decode_accepted_message(&got, wire, 0) == 65);
  equal_accepted_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_accepted_message(&got, wire, 0) == 65);
  assert(encode_accepted_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replaced Message: 79 bytes ---------------------------------------------- */

typedef struct {
  uint8_t timestamp[8];                                 /* bytes 0 to 7 */
  uint8_t replacement_order_token_alphanumeric_14[14];  /* bytes 8 to 21 */
  uint8_t buy_sell_indicator;                           /* byte 22 */
  uint8_t shares[4];                                    /* bytes 23 to 26 */
  uint8_t stock[8];                                     /* bytes 27 to 34 */
  uint8_t price[4];                                     /* bytes 35 to 38 */
  uint8_t time_in_force[4];                             /* bytes 39 to 42 */
  uint8_t firm[4];                                      /* bytes 43 to 46 */
  uint8_t display;                                      /* byte 47 */
  uint8_t order_reference_number[8];                    /* bytes 48 to 55 */
  uint8_t capacity;                                     /* byte 56 */
  uint8_t intermarket_sweep_eligibility;                /* byte 57 */
  uint8_t minimum_quantity[4];                          /* bytes 58 to 61 */
  uint8_t cross_type;                                   /* byte 62 */
  uint8_t order_state;                                  /* byte 63 */
  uint8_t previous_order_token[14];                     /* bytes 64 to 77 */
  uint8_t bbo_weight_indicator;                         /* byte 78 */
} ReplacedMessage;

/* any Replaced Message at all: every byte one the checker chooses */
static void any_replaced_message(ReplacedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->replacement_order_token_alphanumeric_14[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm[i] = arbitrary(); }
  record->display = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
  record->capacity = arbitrary();
  record->intermarket_sweep_eligibility = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = arbitrary(); }
  record->cross_type = arbitrary();
  record->order_state = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->previous_order_token[i] = arbitrary(); }
  record->bbo_weight_indicator = arbitrary();
}

/* Replaced Message to the wire: 79 bytes from at, returning where the next byte goes */
static size_t encode_replaced_message(const ReplacedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->replacement_order_token_alphanumeric_14[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_in_force[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->display;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->capacity;
  wire[at++] = record->intermarket_sweep_eligibility;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity[i]; }
  wire[at++] = record->cross_type;
  wire[at++] = record->order_state;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->previous_order_token[i]; }
  wire[at++] = record->bbo_weight_indicator;

  return at;
}

/* Replaced Message off the wire: 79 bytes from at, returning where the next byte lies */
static size_t decode_replaced_message(ReplacedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->replacement_order_token_alphanumeric_14[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm[i] = wire[at++]; }
  record->display = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }
  record->capacity = wire[at++];
  record->intermarket_sweep_eligibility = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = wire[at++]; }
  record->cross_type = wire[at++];
  record->order_state = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->previous_order_token[i] = wire[at++]; }
  record->bbo_weight_indicator = wire[at++];

  return at;
}

/* what was read of Replaced Message is what was written, byte for byte */
static void equal_replaced_message(const ReplacedMessage *read, const ReplacedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->replacement_order_token_alphanumeric_14[i] == written->replacement_order_token_alphanumeric_14[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->display == written->display);
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->capacity == written->capacity);
  assert(read->intermarket_sweep_eligibility == written->intermarket_sweep_eligibility);
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
  assert(read->cross_type == written->cross_type);
  assert(read->order_state == written->order_state);
  for (size_t i = 0; i < 14; i++) { assert(read->previous_order_token[i] == written->previous_order_token[i]); }
  assert(read->bbo_weight_indicator == written->bbo_weight_indicator);
}

/* Replaced Message: written and read back, then read and written back */
static void check_replaced_message(void) {
  ReplacedMessage sent;
  ReplacedMessage got;
  uint8_t wire[79];
  uint8_t again[79];

  any_replaced_message(&sent);
  assert(encode_replaced_message(&sent, wire, 0) == 79);
  assert(decode_replaced_message(&got, wire, 0) == 79);
  equal_replaced_message(&got, &sent);

  for (size_t i = 0; i < 79; i++) { wire[i] = arbitrary(); }
  assert(decode_replaced_message(&got, wire, 0) == 79);
  assert(encode_replaced_message(&got, again, 0) == 79);
  for (size_t i = 0; i < 79; i++) { assert(again[i] == wire[i]); }
}

/* ---- Canceled Message: 27 bytes ---------------------------------------------- */

typedef struct {
  uint8_t timestamp[8];         /* bytes 0 to 7 */
  uint8_t order_token[14];      /* bytes 8 to 21 */
  uint8_t decrement_shares[4];  /* bytes 22 to 25 */
  uint8_t canceled_reason;      /* byte 26 */
} CanceledMessage;

/* any Canceled Message at all: every byte one the checker chooses */
static void any_canceled_message(CanceledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->decrement_shares[i] = arbitrary(); }
  record->canceled_reason = arbitrary();
}

/* Canceled Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_canceled_message(const CanceledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decrement_shares[i]; }
  wire[at++] = record->canceled_reason;

  return at;
}

/* Canceled Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_canceled_message(CanceledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->decrement_shares[i] = wire[at++]; }
  record->canceled_reason = wire[at++];

  return at;
}

/* what was read of Canceled Message is what was written, byte for byte */
static void equal_canceled_message(const CanceledMessage *read, const CanceledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->decrement_shares[i] == written->decrement_shares[i]); }
  assert(read->canceled_reason == written->canceled_reason);
}

/* Canceled Message: written and read back, then read and written back */
static void check_canceled_message(void) {
  CanceledMessage sent;
  CanceledMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_canceled_message(&sent);
  assert(encode_canceled_message(&sent, wire, 0) == 27);
  assert(decode_canceled_message(&got, wire, 0) == 27);
  equal_canceled_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_canceled_message(&got, wire, 0) == 27);
  assert(encode_canceled_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Aiq Canceled Message: 37 bytes ------------------------------------------ */

typedef struct {
  uint8_t timestamp[8];                        /* bytes 0 to 7 */
  uint8_t order_token[14];                     /* bytes 8 to 21 */
  uint8_t decrement_shares[4];                 /* bytes 22 to 25 */
  uint8_t aiq_canceled_reason;                 /* byte 26 */
  uint8_t quantity_prevented_from_trading[4];  /* bytes 27 to 30 */
  uint8_t execution_price[4];                  /* bytes 31 to 34 */
  uint8_t liquidity_flag;                      /* byte 35 */
  uint8_t aiq_strategy;                        /* byte 36 */
} AiqCanceledMessage;

/* any Aiq Canceled Message at all: every byte one the checker chooses */
static void any_aiq_canceled_message(AiqCanceledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->decrement_shares[i] = arbitrary(); }
  record->aiq_canceled_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_prevented_from_trading[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = arbitrary(); }
  record->liquidity_flag = arbitrary();
  record->aiq_strategy = arbitrary();
}

/* Aiq Canceled Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_aiq_canceled_message(const AiqCanceledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decrement_shares[i]; }
  wire[at++] = record->aiq_canceled_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_prevented_from_trading[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_price[i]; }
  wire[at++] = record->liquidity_flag;
  wire[at++] = record->aiq_strategy;

  return at;
}

/* Aiq Canceled Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_aiq_canceled_message(AiqCanceledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->decrement_shares[i] = wire[at++]; }
  record->aiq_canceled_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_prevented_from_trading[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = wire[at++]; }
  record->liquidity_flag = wire[at++];
  record->aiq_strategy = wire[at++];

  return at;
}

/* what was read of Aiq Canceled Message is what was written, byte for byte */
static void equal_aiq_canceled_message(const AiqCanceledMessage *read, const AiqCanceledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->decrement_shares[i] == written->decrement_shares[i]); }
  assert(read->aiq_canceled_reason == written->aiq_canceled_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_prevented_from_trading[i] == written->quantity_prevented_from_trading[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
  assert(read->liquidity_flag == written->liquidity_flag);
  assert(read->aiq_strategy == written->aiq_strategy);
}

/* Aiq Canceled Message: written and read back, then read and written back */
static void check_aiq_canceled_message(void) {
  AiqCanceledMessage sent;
  AiqCanceledMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_aiq_canceled_message(&sent);
  assert(encode_aiq_canceled_message(&sent, wire, 0) == 37);
  assert(decode_aiq_canceled_message(&got, wire, 0) == 37);
  equal_aiq_canceled_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_aiq_canceled_message(&got, wire, 0) == 37);
  assert(encode_aiq_canceled_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Executed Message: 39 bytes ---------------------------------------------- */

typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t order_token[14];     /* bytes 8 to 21 */
  uint8_t executed_shares[4];  /* bytes 22 to 25 */
  uint8_t execution_price[4];  /* bytes 26 to 29 */
  uint8_t liquidity_flag;      /* byte 30 */
  uint8_t match_number[8];     /* bytes 31 to 38 */
} ExecutedMessage;

/* any Executed Message at all: every byte one the checker chooses */
static void any_executed_message(ExecutedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = arbitrary(); }
  record->liquidity_flag = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
}

/* Executed Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_executed_message(const ExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_price[i]; }
  wire[at++] = record->liquidity_flag;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Executed Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_executed_message(ExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_price[i] = wire[at++]; }
  record->liquidity_flag = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Executed Message is what was written, byte for byte */
static void equal_executed_message(const ExecutedMessage *read, const ExecutedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_shares[i] == written->executed_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_price[i] == written->execution_price[i]); }
  assert(read->liquidity_flag == written->liquidity_flag);
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Executed Message: written and read back, then read and written back */
static void check_executed_message(void) {
  ExecutedMessage sent;
  ExecutedMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_executed_message(&sent);
  assert(encode_executed_message(&sent, wire, 0) == 39);
  assert(decode_executed_message(&got, wire, 0) == 39);
  equal_executed_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_executed_message(&got, wire, 0) == 39);
  assert(encode_executed_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Message: 31 bytes ------------------------------------------ */

typedef struct {
  uint8_t timestamp[8];         /* bytes 0 to 7 */
  uint8_t order_token[14];      /* bytes 8 to 21 */
  uint8_t match_number[8];      /* bytes 22 to 29 */
  uint8_t broken_trade_reason;  /* byte 30 */
} BrokenTradeMessage;

/* any Broken Trade Message at all: every byte one the checker chooses */
static void any_broken_trade_message(BrokenTradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = arbitrary(); }
  record->broken_trade_reason = arbitrary();
}

/* Broken Trade Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_message(const BrokenTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->broken_trade_reason;

  return at;
}

/* Broken Trade Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_message(BrokenTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_number[i] = wire[at++]; }
  record->broken_trade_reason = wire[at++];

  return at;
}

/* what was read of Broken Trade Message is what was written, byte for byte */
static void equal_broken_trade_message(const BrokenTradeMessage *read, const BrokenTradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->broken_trade_reason == written->broken_trade_reason);
}

/* Broken Trade Message: written and read back, then read and written back */
static void check_broken_trade_message(void) {
  BrokenTradeMessage sent;
  BrokenTradeMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_broken_trade_message(&sent);
  assert(encode_broken_trade_message(&sent, wire, 0) == 31);
  assert(decode_broken_trade_message(&got, wire, 0) == 31);
  equal_broken_trade_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_message(&got, wire, 0) == 31);
  assert(encode_broken_trade_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rejected Message: 23 bytes ---------------------------------------------- */

typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t order_token[14];  /* bytes 8 to 21 */
  uint8_t rejected_reason;  /* byte 22 */
} RejectedMessage;

/* any Rejected Message at all: every byte one the checker chooses */
static void any_rejected_message(RejectedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  record->rejected_reason = arbitrary();
}

/* Rejected Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_rejected_message(const RejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  wire[at++] = record->rejected_reason;

  return at;
}

/* Rejected Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_rejected_message(RejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  record->rejected_reason = wire[at++];

  return at;
}

/* what was read of Rejected Message is what was written, byte for byte */
static void equal_rejected_message(const RejectedMessage *read, const RejectedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  assert(read->rejected_reason == written->rejected_reason);
}

/* Rejected Message: written and read back, then read and written back */
static void check_rejected_message(void) {
  RejectedMessage sent;
  RejectedMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_rejected_message(&sent);
  assert(encode_rejected_message(&sent, wire, 0) == 23);
  assert(decode_rejected_message(&got, wire, 0) == 23);
  equal_rejected_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_rejected_message(&got, wire, 0) == 23);
  assert(encode_rejected_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Pending Message: 22 bytes ---------------------------------------- */

typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t order_token[14];  /* bytes 8 to 21 */
} CancelPendingMessage;

/* any Cancel Pending Message at all: every byte one the checker chooses */
static void any_cancel_pending_message(CancelPendingMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
}

/* Cancel Pending Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_cancel_pending_message(const CancelPendingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }

  return at;
}

/* Cancel Pending Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_cancel_pending_message(CancelPendingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Pending Message is what was written, byte for byte */
static void equal_cancel_pending_message(const CancelPendingMessage *read, const CancelPendingMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
}

/* Cancel Pending Message: written and read back, then read and written back */
static void check_cancel_pending_message(void) {
  CancelPendingMessage sent;
  CancelPendingMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_cancel_pending_message(&sent);
  assert(encode_cancel_pending_message(&sent, wire, 0) == 22);
  assert(decode_cancel_pending_message(&got, wire, 0) == 22);
  equal_cancel_pending_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_pending_message(&got, wire, 0) == 22);
  assert(encode_cancel_pending_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Reject Message: 22 bytes ----------------------------------------- */

typedef struct {
  uint8_t timestamp[8];     /* bytes 0 to 7 */
  uint8_t order_token[14];  /* bytes 8 to 21 */
} CancelRejectMessage;

/* any Cancel Reject Message at all: every byte one the checker chooses */
static void any_cancel_reject_message(CancelRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
}

/* Cancel Reject Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_cancel_reject_message(const CancelRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }

  return at;
}

/* Cancel Reject Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_cancel_reject_message(CancelRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Reject Message is what was written, byte for byte */
static void equal_cancel_reject_message(const CancelRejectMessage *read, const CancelRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
}

/* Cancel Reject Message: written and read back, then read and written back */
static void check_cancel_reject_message(void) {
  CancelRejectMessage sent;
  CancelRejectMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_cancel_reject_message(&sent);
  assert(encode_cancel_reject_message(&sent, wire, 0) == 22);
  assert(decode_cancel_reject_message(&got, wire, 0) == 22);
  equal_cancel_reject_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_reject_message(&got, wire, 0) == 22);
  assert(encode_cancel_reject_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Priority Update Message: 35 bytes --------------------------------- */

typedef struct {
  uint8_t timestamp[8];               /* bytes 0 to 7 */
  uint8_t order_token[14];            /* bytes 8 to 21 */
  uint8_t price[4];                   /* bytes 22 to 25 */
  uint8_t display;                    /* byte 26 */
  uint8_t order_reference_number[8];  /* bytes 27 to 34 */
} OrderPriorityUpdateMessage;

/* any Order Priority Update Message at all: every byte one the checker chooses */
static void any_order_priority_update_message(OrderPriorityUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->display = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = arbitrary(); }
}

/* Order Priority Update Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_order_priority_update_message(const OrderPriorityUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->display;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_reference_number[i]; }

  return at;
}

/* Order Priority Update Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_order_priority_update_message(OrderPriorityUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->display = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_reference_number[i] = wire[at++]; }

  return at;
}

/* what was read of Order Priority Update Message is what was written, byte for byte */
static void equal_order_priority_update_message(const OrderPriorityUpdateMessage *read, const OrderPriorityUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->display == written->display);
  for (size_t i = 0; i < 8; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
}

/* Order Priority Update Message: written and read back, then read and written back */
static void check_order_priority_update_message(void) {
  OrderPriorityUpdateMessage sent;
  OrderPriorityUpdateMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_order_priority_update_message(&sent);
  assert(encode_order_priority_update_message(&sent, wire, 0) == 35);
  assert(decode_order_priority_update_message(&got, wire, 0) == 35);
  equal_order_priority_update_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_order_priority_update_message(&got, wire, 0) == 35);
  assert(encode_order_priority_update_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modified Message: 27 bytes ---------------------------------------- */

typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t order_token[14];     /* bytes 8 to 21 */
  uint8_t buy_sell_indicator;  /* byte 22 */
  uint8_t shares[4];           /* bytes 23 to 26 */
} OrderModifiedMessage;

/* any Order Modified Message at all: every byte one the checker chooses */
static void any_order_modified_message(OrderModifiedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
}

/* Order Modified Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_order_modified_message(const OrderModifiedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }

  return at;
}

/* Order Modified Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_order_modified_message(OrderModifiedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }

  return at;
}

/* what was read of Order Modified Message is what was written, byte for byte */
static void equal_order_modified_message(const OrderModifiedMessage *read, const OrderModifiedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
}

/* Order Modified Message: written and read back, then read and written back */
static void check_order_modified_message(void) {
  OrderModifiedMessage sent;
  OrderModifiedMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_order_modified_message(&sent);
  assert(encode_order_modified_message(&sent, wire, 0) == 27);
  assert(decode_order_modified_message(&got, wire, 0) == 27);
  equal_order_modified_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modified_message(&got, wire, 0) == 27);
  assert(encode_order_modified_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_system_event_message();
  check_accepted_message();
  check_replaced_message();
  check_canceled_message();
  check_aiq_canceled_message();
  check_executed_message();
  check_broken_trade_message();
  check_rejected_message();
  check_cancel_pending_message();
  check_cancel_reject_message();
  check_order_priority_update_message();
  check_order_modified_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
