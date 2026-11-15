// nasdaq/psxequities/rash/PsxEquities_Rash_v1_0_Server.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Rash
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

/* ---- Sequenced Message Header: 9 bytes --------------------------------------- */

/* Time Stamp and type carried ahead of every RASH outbound sequenced message */
typedef struct {
  uint8_t timestamp[8];            /* bytes 0 to 7 */
  uint8_t sequenced_message_type;  /* byte 8 */
} SequencedMessageHeader;

/* any Sequenced Message Header at all: every byte one the checker chooses */
static void any_sequenced_message_header(SequencedMessageHeader *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->sequenced_message_type = arbitrary();
}

/* Sequenced Message Header to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_sequenced_message_header(const SequencedMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->sequenced_message_type;

  return at;
}

/* Sequenced Message Header off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_sequenced_message_header(SequencedMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->sequenced_message_type = wire[at++];

  return at;
}

/* what was read of Sequenced Message Header is what was written, byte for byte */
static void equal_sequenced_message_header(const SequencedMessageHeader *read, const SequencedMessageHeader *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->sequenced_message_type == written->sequenced_message_type);
}

/* Sequenced Message Header: written and read back, then read and written back */
static void check_sequenced_message_header(void) {
  SequencedMessageHeader sent;
  SequencedMessageHeader got;
  uint8_t wire[9];
  uint8_t again[9];

  any_sequenced_message_header(&sent);
  assert(encode_sequenced_message_header(&sent, wire, 0) == 9);
  assert(decode_sequenced_message_header(&got, wire, 0) == 9);
  equal_sequenced_message_header(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_sequenced_message_header(&got, wire, 0) == 9);
  assert(encode_sequenced_message_header(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 1 byte -------------------------------------------- */

/* System Event Messages signal events that affect the entire system. */
typedef struct {
  uint8_t event_code;  /* byte 0 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  record->event_code = arbitrary();
}

/* System Event Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->event_code;

  return at;
}

/* System Event Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  assert(read->event_code == written->event_code);
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 1);
  assert(decode_system_event_message(&got, wire, 0) == 1);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 1);
  assert(encode_system_event_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Accepted Order Message: 145 bytes --------------------------------------- */

/* An Accepted Order Message acknowledges the receipt of a valid Enter Order Message. The data fields from the Enter Order Message are echoed back; the accepted values may differ from the entered values for some fields. */
typedef struct {
  uint8_t order_token_client_order_id[14];     /* bytes 0 to 13 */
  uint8_t side;                                /* byte 14 */
  uint8_t shares_order_qty[6];                 /* bytes 15 to 20 */
  uint8_t stock_symbol[6];                     /* bytes 21 to 26 */
  uint8_t price[10];                           /* bytes 27 to 36 */
  uint8_t time_in_force[5];                    /* bytes 37 to 41 */
  uint8_t firm_client_id[4];                   /* bytes 42 to 45 */
  uint8_t display;                             /* byte 46 */
  uint8_t order_reference_number[9];           /* bytes 47 to 55 */
  uint8_t min_qty[6];                          /* bytes 56 to 61 */
  uint8_t max_floor[6];                        /* bytes 62 to 67 */
  uint8_t peg_type;                            /* byte 68 */
  uint8_t peg_difference_sign;                 /* byte 69 */
  uint8_t peg_difference[10];                  /* bytes 70 to 79 */
  uint8_t discretion_price[10];                /* bytes 80 to 89 */
  uint8_t discretion_peg_type;                 /* byte 90 */
  uint8_t discretion_peg_difference_sign;      /* byte 91 */
  uint8_t discretion_peg_difference[10];       /* bytes 92 to 101 */
  uint8_t capacity_rule_80_a_indicator;        /* byte 102 */
  uint8_t random_reserve[6];                   /* bytes 103 to 108 */
  uint8_t route_dest_exec_broker[4];           /* bytes 109 to 112 */
  uint8_t cust_terminal_id_sender_sub_id[32];  /* bytes 113 to 144 */
} AcceptedOrderMessage;

/* any Accepted Order Message at all: every byte one the checker chooses */
static void any_accepted_order_message(AcceptedOrderMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->time_in_force[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_client_id[i] = arbitrary(); }
  record->display = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->max_floor[i] = arbitrary(); }
  record->peg_type = arbitrary();
  record->peg_difference_sign = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->peg_difference[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->discretion_price[i] = arbitrary(); }
  record->discretion_peg_type = arbitrary();
  record->discretion_peg_difference_sign = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->discretion_peg_difference[i] = arbitrary(); }
  record->capacity_rule_80_a_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->random_reserve[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->route_dest_exec_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->cust_terminal_id_sender_sub_id[i] = arbitrary(); }
}

/* Accepted Order Message to the wire: 145 bytes from at, returning where the next byte goes */
static size_t encode_accepted_order_message(const AcceptedOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token_client_order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_order_qty[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock_symbol[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->time_in_force[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_client_id[i]; }
  wire[at++] = record->display;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->max_floor[i]; }
  wire[at++] = record->peg_type;
  wire[at++] = record->peg_difference_sign;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->peg_difference[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->discretion_price[i]; }
  wire[at++] = record->discretion_peg_type;
  wire[at++] = record->discretion_peg_difference_sign;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->discretion_peg_difference[i]; }
  wire[at++] = record->capacity_rule_80_a_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->random_reserve[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->route_dest_exec_broker[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->cust_terminal_id_sender_sub_id[i]; }

  return at;
}

/* Accepted Order Message off the wire: 145 bytes from at, returning where the next byte lies */
static size_t decode_accepted_order_message(AcceptedOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->time_in_force[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_client_id[i] = wire[at++]; }
  record->display = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->max_floor[i] = wire[at++]; }
  record->peg_type = wire[at++];
  record->peg_difference_sign = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->peg_difference[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->discretion_price[i] = wire[at++]; }
  record->discretion_peg_type = wire[at++];
  record->discretion_peg_difference_sign = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->discretion_peg_difference[i] = wire[at++]; }
  record->capacity_rule_80_a_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->random_reserve[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->route_dest_exec_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->cust_terminal_id_sender_sub_id[i] = wire[at++]; }

  return at;
}

/* what was read of Accepted Order Message is what was written, byte for byte */
static void equal_accepted_order_message(const AcceptedOrderMessage *read, const AcceptedOrderMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token_client_order_id[i] == written->order_token_client_order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_order_qty[i] == written->shares_order_qty[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_client_id[i] == written->firm_client_id[i]); }
  assert(read->display == written->display);
  for (size_t i = 0; i < 9; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  assert(read->peg_type == written->peg_type);
  assert(read->peg_difference_sign == written->peg_difference_sign);
  for (size_t i = 0; i < 10; i++) { assert(read->peg_difference[i] == written->peg_difference[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->discretion_price[i] == written->discretion_price[i]); }
  assert(read->discretion_peg_type == written->discretion_peg_type);
  assert(read->discretion_peg_difference_sign == written->discretion_peg_difference_sign);
  for (size_t i = 0; i < 10; i++) { assert(read->discretion_peg_difference[i] == written->discretion_peg_difference[i]); }
  assert(read->capacity_rule_80_a_indicator == written->capacity_rule_80_a_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->random_reserve[i] == written->random_reserve[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->route_dest_exec_broker[i] == written->route_dest_exec_broker[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->cust_terminal_id_sender_sub_id[i] == written->cust_terminal_id_sender_sub_id[i]); }
}

/* Accepted Order Message: written and read back, then read and written back */
static void check_accepted_order_message(void) {
  AcceptedOrderMessage sent;
  AcceptedOrderMessage got;
  uint8_t wire[145];
  uint8_t again[145];

  any_accepted_order_message(&sent);
  assert(encode_accepted_order_message(&sent, wire, 0) == 145);
  assert(decode_accepted_order_message(&got, wire, 0) == 145);
  equal_accepted_order_message(&got, &sent);

  for (size_t i = 0; i < 145; i++) { wire[i] = arbitrary(); }
  assert(decode_accepted_order_message(&got, wire, 0) == 145);
  assert(encode_accepted_order_message(&got, again, 0) == 145);
  for (size_t i = 0; i < 145; i++) { assert(again[i] == wire[i]); }
}

/* ---- Accepted Order Message With Cross Functionality: 147 bytes -------------- */

/* Similar to the regular Accepted Order Message, with the additional information provided upon order entry using the Enter Order Message with Cross Functionality. */
typedef struct {
  uint8_t order_token_client_order_id[14];     /* bytes 0 to 13 */
  uint8_t side;                                /* byte 14 */
  uint8_t shares_order_qty[6];                 /* bytes 15 to 20 */
  uint8_t stock_symbol[6];                     /* bytes 21 to 26 */
  uint8_t price[10];                           /* bytes 27 to 36 */
  uint8_t time_in_force[5];                    /* bytes 37 to 41 */
  uint8_t firm_client_id[4];                   /* bytes 42 to 45 */
  uint8_t display;                             /* byte 46 */
  uint8_t order_reference_number[9];           /* bytes 47 to 55 */
  uint8_t min_qty[6];                          /* bytes 56 to 61 */
  uint8_t max_floor[6];                        /* bytes 62 to 67 */
  uint8_t peg_type;                            /* byte 68 */
  uint8_t peg_difference_sign;                 /* byte 69 */
  uint8_t peg_difference[10];                  /* bytes 70 to 79 */
  uint8_t discretion_price[10];                /* bytes 80 to 89 */
  uint8_t discretion_peg_type;                 /* byte 90 */
  uint8_t discretion_peg_difference_sign;      /* byte 91 */
  uint8_t discretion_peg_difference[10];       /* bytes 92 to 101 */
  uint8_t capacity_rule_80_a_indicator;        /* byte 102 */
  uint8_t random_reserve[6];                   /* bytes 103 to 108 */
  uint8_t route_dest_exec_broker[4];           /* bytes 109 to 112 */
  uint8_t cust_terminal_id_sender_sub_id[32];  /* bytes 113 to 144 */
  uint8_t inter_market_sweep_eligibility;      /* byte 145 */
  uint8_t cross_type;                          /* byte 146 */
} AcceptedOrderMessageWithCrossFunctionality;

/* any Accepted Order Message With Cross Functionality at all: every byte one the checker chooses */
static void any_accepted_order_message_with_cross_functionality(AcceptedOrderMessageWithCrossFunctionality *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->time_in_force[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_client_id[i] = arbitrary(); }
  record->display = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->max_floor[i] = arbitrary(); }
  record->peg_type = arbitrary();
  record->peg_difference_sign = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->peg_difference[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->discretion_price[i] = arbitrary(); }
  record->discretion_peg_type = arbitrary();
  record->discretion_peg_difference_sign = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->discretion_peg_difference[i] = arbitrary(); }
  record->capacity_rule_80_a_indicator = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->random_reserve[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->route_dest_exec_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->cust_terminal_id_sender_sub_id[i] = arbitrary(); }
  record->inter_market_sweep_eligibility = arbitrary();
  record->cross_type = arbitrary();
}

/* Accepted Order Message With Cross Functionality to the wire: 147 bytes from at, returning where the next byte goes */
static size_t encode_accepted_order_message_with_cross_functionality(const AcceptedOrderMessageWithCrossFunctionality *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token_client_order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_order_qty[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock_symbol[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->time_in_force[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_client_id[i]; }
  wire[at++] = record->display;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->max_floor[i]; }
  wire[at++] = record->peg_type;
  wire[at++] = record->peg_difference_sign;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->peg_difference[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->discretion_price[i]; }
  wire[at++] = record->discretion_peg_type;
  wire[at++] = record->discretion_peg_difference_sign;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->discretion_peg_difference[i]; }
  wire[at++] = record->capacity_rule_80_a_indicator;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->random_reserve[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->route_dest_exec_broker[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->cust_terminal_id_sender_sub_id[i]; }
  wire[at++] = record->inter_market_sweep_eligibility;
  wire[at++] = record->cross_type;

  return at;
}

/* Accepted Order Message With Cross Functionality off the wire: 147 bytes from at, returning where the next byte lies */
static size_t decode_accepted_order_message_with_cross_functionality(AcceptedOrderMessageWithCrossFunctionality *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->time_in_force[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_client_id[i] = wire[at++]; }
  record->display = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->max_floor[i] = wire[at++]; }
  record->peg_type = wire[at++];
  record->peg_difference_sign = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->peg_difference[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->discretion_price[i] = wire[at++]; }
  record->discretion_peg_type = wire[at++];
  record->discretion_peg_difference_sign = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->discretion_peg_difference[i] = wire[at++]; }
  record->capacity_rule_80_a_indicator = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->random_reserve[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->route_dest_exec_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->cust_terminal_id_sender_sub_id[i] = wire[at++]; }
  record->inter_market_sweep_eligibility = wire[at++];
  record->cross_type = wire[at++];

  return at;
}

/* what was read of Accepted Order Message With Cross Functionality is what was written, byte for byte */
static void equal_accepted_order_message_with_cross_functionality(const AcceptedOrderMessageWithCrossFunctionality *read, const AcceptedOrderMessageWithCrossFunctionality *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token_client_order_id[i] == written->order_token_client_order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_order_qty[i] == written->shares_order_qty[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_client_id[i] == written->firm_client_id[i]); }
  assert(read->display == written->display);
  for (size_t i = 0; i < 9; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  assert(read->peg_type == written->peg_type);
  assert(read->peg_difference_sign == written->peg_difference_sign);
  for (size_t i = 0; i < 10; i++) { assert(read->peg_difference[i] == written->peg_difference[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->discretion_price[i] == written->discretion_price[i]); }
  assert(read->discretion_peg_type == written->discretion_peg_type);
  assert(read->discretion_peg_difference_sign == written->discretion_peg_difference_sign);
  for (size_t i = 0; i < 10; i++) { assert(read->discretion_peg_difference[i] == written->discretion_peg_difference[i]); }
  assert(read->capacity_rule_80_a_indicator == written->capacity_rule_80_a_indicator);
  for (size_t i = 0; i < 6; i++) { assert(read->random_reserve[i] == written->random_reserve[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->route_dest_exec_broker[i] == written->route_dest_exec_broker[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->cust_terminal_id_sender_sub_id[i] == written->cust_terminal_id_sender_sub_id[i]); }
  assert(read->inter_market_sweep_eligibility == written->inter_market_sweep_eligibility);
  assert(read->cross_type == written->cross_type);
}

/* Accepted Order Message With Cross Functionality: written and read back, then read and written back */
static void check_accepted_order_message_with_cross_functionality(void) {
  AcceptedOrderMessageWithCrossFunctionality sent;
  AcceptedOrderMessageWithCrossFunctionality got;
  uint8_t wire[147];
  uint8_t again[147];

  any_accepted_order_message_with_cross_functionality(&sent);
  assert(encode_accepted_order_message_with_cross_functionality(&sent, wire, 0) == 147);
  assert(decode_accepted_order_message_with_cross_functionality(&got, wire, 0) == 147);
  equal_accepted_order_message_with_cross_functionality(&got, &sent);

  for (size_t i = 0; i < 147; i++) { wire[i] = arbitrary(); }
  assert(decode_accepted_order_message_with_cross_functionality(&got, wire, 0) == 147);
  assert(encode_accepted_order_message_with_cross_functionality(&got, again, 0) == 147);
  for (size_t i = 0; i < 147; i++) { assert(again[i] == wire[i]); }
}

/* ---- Canceled Order Message: 21 bytes ---------------------------------------- */

/* A Canceled Order Message informs you that an order has been reduced or canceled. Canceled shares reflect the number of shares that are out. */
typedef struct {
  uint8_t order_token_client_order_id[14];  /* bytes 0 to 13 */
  uint8_t shares[6];                        /* bytes 14 to 19 */
  uint8_t cancel_reason;                    /* byte 20 */
} CanceledOrderMessage;

/* any Canceled Order Message at all: every byte one the checker chooses */
static void any_canceled_order_message(CanceledOrderMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
}

/* Canceled Order Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_canceled_order_message(const CanceledOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token_client_order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  wire[at++] = record->cancel_reason;

  return at;
}

/* Canceled Order Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_canceled_order_message(CanceledOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  record->cancel_reason = wire[at++];

  return at;
}

/* what was read of Canceled Order Message is what was written, byte for byte */
static void equal_canceled_order_message(const CanceledOrderMessage *read, const CanceledOrderMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token_client_order_id[i] == written->order_token_client_order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  assert(read->cancel_reason == written->cancel_reason);
}

/* Canceled Order Message: written and read back, then read and written back */
static void check_canceled_order_message(void) {
  CanceledOrderMessage sent;
  CanceledOrderMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_canceled_order_message(&sent);
  assert(encode_canceled_order_message(&sent, wire, 0) == 21);
  assert(decode_canceled_order_message(&got, wire, 0) == 21);
  equal_canceled_order_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_canceled_order_message(&got, wire, 0) == 21);
  assert(encode_canceled_order_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rejected Order Message: 15 bytes ---------------------------------------- */

/* A Rejected Order Message may be sent in response to an Enter Order Message if the order cannot be accepted at this time. The Token of a rejected order cannot be re-used. */
typedef struct {
  uint8_t order_token_client_order_id[14];  /* bytes 0 to 13 */
  uint8_t reject_reason;                    /* byte 14 */
} RejectedOrderMessage;

/* any Rejected Order Message at all: every byte one the checker chooses */
static void any_rejected_order_message(RejectedOrderMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = arbitrary(); }
  record->reject_reason = arbitrary();
}

/* Rejected Order Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_rejected_order_message(const RejectedOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token_client_order_id[i]; }
  wire[at++] = record->reject_reason;

  return at;
}

/* Rejected Order Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_rejected_order_message(RejectedOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = wire[at++]; }
  record->reject_reason = wire[at++];

  return at;
}

/* what was read of Rejected Order Message is what was written, byte for byte */
static void equal_rejected_order_message(const RejectedOrderMessage *read, const RejectedOrderMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token_client_order_id[i] == written->order_token_client_order_id[i]); }
  assert(read->reject_reason == written->reject_reason);
}

/* Rejected Order Message: written and read back, then read and written back */
static void check_rejected_order_message(void) {
  RejectedOrderMessage sent;
  RejectedOrderMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_rejected_order_message(&sent);
  assert(encode_rejected_order_message(&sent, wire, 0) == 15);
  assert(decode_rejected_order_message(&got, wire, 0) == 15);
  equal_rejected_order_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_rejected_order_message(&got, wire, 0) == 15);
  assert(encode_rejected_order_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Executed Order Message: 40 bytes ---------------------------------------- */

/* An Executed Order Message informs you that all or part of an order has been executed. */
typedef struct {
  uint8_t order_token_client_order_id[14];  /* bytes 0 to 13 */
  uint8_t shares[6];                        /* bytes 14 to 19 */
  uint8_t price[10];                        /* bytes 20 to 29 */
  uint8_t liquidity;                        /* byte 30 */
  uint8_t match_number[9];                  /* bytes 31 to 39 */
} ExecutedOrderMessage;

/* any Executed Order Message at all: every byte one the checker chooses */
static void any_executed_order_message(ExecutedOrderMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  record->liquidity = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->match_number[i] = arbitrary(); }
}

/* Executed Order Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_executed_order_message(const ExecutedOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token_client_order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->liquidity;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->match_number[i]; }

  return at;
}

/* Executed Order Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_executed_order_message(ExecutedOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  record->liquidity = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->match_number[i] = wire[at++]; }

  return at;
}

/* what was read of Executed Order Message is what was written, byte for byte */
static void equal_executed_order_message(const ExecutedOrderMessage *read, const ExecutedOrderMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token_client_order_id[i] == written->order_token_client_order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->liquidity == written->liquidity);
  for (size_t i = 0; i < 9; i++) { assert(read->match_number[i] == written->match_number[i]); }
}

/* Executed Order Message: written and read back, then read and written back */
static void check_executed_order_message(void) {
  ExecutedOrderMessage sent;
  ExecutedOrderMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_executed_order_message(&sent);
  assert(encode_executed_order_message(&sent, wire, 0) == 40);
  assert(decode_executed_order_message(&got, wire, 0) == 40);
  equal_executed_order_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_executed_order_message(&got, wire, 0) == 40);
  assert(encode_executed_order_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broken Trade Message: 24 bytes ------------------------------------------ */

/* A Broken Trade Message informs you that an execution has been broken. The trade is no longer good and will not clear. */
typedef struct {
  uint8_t order_token[14];      /* bytes 0 to 13 */
  uint8_t match_number[9];      /* bytes 14 to 22 */
  uint8_t broken_trade_reason;  /* byte 23 */
} BrokenTradeMessage;

/* any Broken Trade Message at all: every byte one the checker chooses */
static void any_broken_trade_message(BrokenTradeMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->match_number[i] = arbitrary(); }
  record->broken_trade_reason = arbitrary();
}

/* Broken Trade Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_broken_trade_message(const BrokenTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->match_number[i]; }
  wire[at++] = record->broken_trade_reason;

  return at;
}

/* Broken Trade Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_broken_trade_message(BrokenTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->match_number[i] = wire[at++]; }
  record->broken_trade_reason = wire[at++];

  return at;
}

/* what was read of Broken Trade Message is what was written, byte for byte */
static void equal_broken_trade_message(const BrokenTradeMessage *read, const BrokenTradeMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->match_number[i] == written->match_number[i]); }
  assert(read->broken_trade_reason == written->broken_trade_reason);
}

/* Broken Trade Message: written and read back, then read and written back */
static void check_broken_trade_message(void) {
  BrokenTradeMessage sent;
  BrokenTradeMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_broken_trade_message(&sent);
  assert(encode_broken_trade_message(&sent, wire, 0) == 24);
  assert(decode_broken_trade_message(&got, wire, 0) == 24);
  equal_broken_trade_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_broken_trade_message(&got, wire, 0) == 24);
  assert(encode_broken_trade_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_sequenced_message_header();
  check_system_event_message();
  check_accepted_order_message();
  check_accepted_order_message_with_cross_functionality();
  check_canceled_order_message();
  check_rejected_order_message();
  check_executed_order_message();
  check_broken_trade_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
