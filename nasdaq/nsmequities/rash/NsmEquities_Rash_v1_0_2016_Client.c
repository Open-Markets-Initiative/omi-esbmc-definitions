// nasdaq/nsmequities/rash/NsmEquities_Rash_v1_0_2016_Client.c
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

/* ---- Client Packet Header: 3 bytes ------------------------------------------- */

/* Packet header of a packet sent by the client */
typedef struct {
  uint8_t packet_length[2];    /* bytes 0 to 1 */
  uint8_t client_packet_type;  /* byte 2 */
} ClientPacketHeader;

/* any Client Packet Header at all: every byte one the checker chooses */
static void any_client_packet_header(ClientPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  record->client_packet_type = arbitrary();
}

/* Client Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_client_packet_header(const ClientPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  wire[at++] = record->client_packet_type;

  return at;
}

/* Client Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_client_packet_header(ClientPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  record->client_packet_type = wire[at++];

  return at;
}

/* what was read of Client Packet Header is what was written, byte for byte */
static void equal_client_packet_header(const ClientPacketHeader *read, const ClientPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  assert(read->client_packet_type == written->client_packet_type);
}

/* Client Packet Header: written and read back, then read and written back */
static void check_client_packet_header(void) {
  ClientPacketHeader sent;
  ClientPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_client_packet_header(&sent);
  assert(encode_client_packet_header(&sent, wire, 0) == 3);
  assert(decode_client_packet_header(&got, wire, 0) == 3);
  equal_client_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_client_packet_header(&got, wire, 0) == 3);
  assert(encode_client_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request Packet: 46 bytes ------------------------------------------ */

/* The SoupBinTCP client must send a Login Request Packet immediately upon establishing a new TCP/IP socket connection to the server */
typedef struct {
  uint8_t username[6];                    /* bytes 0 to 5 */
  uint8_t password[10];                   /* bytes 6 to 15 */
  uint8_t requested_session[10];          /* bytes 16 to 25 */
  uint8_t requested_sequence_number[20];  /* bytes 26 to 45 */
} LoginRequestPacket;

/* any Login Request Packet at all: every byte one the checker chooses */
static void any_login_request_packet(LoginRequestPacket *record) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->requested_session[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->requested_sequence_number[i] = arbitrary(); }
}

/* Login Request Packet to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_login_request_packet(const LoginRequestPacket *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->requested_session[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->requested_sequence_number[i]; }

  return at;
}

/* Login Request Packet off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_login_request_packet(LoginRequestPacket *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->requested_session[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->requested_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request Packet is what was written, byte for byte */
static void equal_login_request_packet(const LoginRequestPacket *read, const LoginRequestPacket *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->requested_session[i] == written->requested_session[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->requested_sequence_number[i] == written->requested_sequence_number[i]); }
}

/* Login Request Packet: written and read back, then read and written back */
static void check_login_request_packet(void) {
  LoginRequestPacket sent;
  LoginRequestPacket got;
  uint8_t wire[46];
  uint8_t again[46];

  any_login_request_packet(&sent);
  assert(encode_login_request_packet(&sent, wire, 0) == 46);
  assert(decode_login_request_packet(&got, wire, 0) == 46);
  equal_login_request_packet(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_packet(&got, wire, 0) == 46);
  assert(encode_login_request_packet(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Enter Order Message: 137 bytes ------------------------------------------ */

/* The Enter Order Message lets you enter a new order. Each new order must have a Token that is unique to the day and that logical RASH Port account. If you send a valid order, you should receive an Accepted Order Message. */
typedef struct {
  uint8_t order_token_client_order_id[14];     /* bytes 0 to 13 */
  uint8_t side;                                /* byte 14 */
  uint8_t shares_order_qty[6];                 /* bytes 15 to 20 */
  uint8_t stock_symbol[6];                     /* bytes 21 to 26 */
  uint8_t price[10];                           /* bytes 27 to 36 */
  uint8_t time_in_force[5];                    /* bytes 37 to 41 */
  uint8_t firm_client_id[4];                   /* bytes 42 to 45 */
  uint8_t display;                             /* byte 46 */
  uint8_t min_qty[6];                          /* bytes 47 to 52 */
  uint8_t max_floor[6];                        /* bytes 53 to 58 */
  uint8_t peg_type;                            /* byte 59 */
  uint8_t peg_difference_sign;                 /* byte 60 */
  uint8_t peg_difference[10];                  /* bytes 61 to 70 */
  uint8_t discretion_price[10];                /* bytes 71 to 80 */
  uint8_t discretion_peg_type;                 /* byte 81 */
  uint8_t discretion_peg_difference_sign;      /* byte 82 */
  uint8_t discretion_peg_difference[10];       /* bytes 83 to 92 */
  uint8_t capacity_rule_80_a_indicator;        /* byte 93 */
  uint8_t random_reserve[6];                   /* bytes 94 to 99 */
  uint8_t route_dest_exec_broker[4];           /* bytes 100 to 103 */
  uint8_t cust_terminal_id_sender_sub_id[32];  /* bytes 104 to 135 */
  uint8_t customer_type;                       /* byte 136 */
} EnterOrderMessage;

/* any Enter Order Message at all: every byte one the checker chooses */
static void any_enter_order_message(EnterOrderMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->time_in_force[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_client_id[i] = arbitrary(); }
  record->display = arbitrary();
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
  record->customer_type = arbitrary();
}

/* Enter Order Message to the wire: 137 bytes from at, returning where the next byte goes */
static size_t encode_enter_order_message(const EnterOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token_client_order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_order_qty[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock_symbol[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->time_in_force[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_client_id[i]; }
  wire[at++] = record->display;
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
  wire[at++] = record->customer_type;

  return at;
}

/* Enter Order Message off the wire: 137 bytes from at, returning where the next byte lies */
static size_t decode_enter_order_message(EnterOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->time_in_force[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_client_id[i] = wire[at++]; }
  record->display = wire[at++];
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
  record->customer_type = wire[at++];

  return at;
}

/* what was read of Enter Order Message is what was written, byte for byte */
static void equal_enter_order_message(const EnterOrderMessage *read, const EnterOrderMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token_client_order_id[i] == written->order_token_client_order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_order_qty[i] == written->shares_order_qty[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_client_id[i] == written->firm_client_id[i]); }
  assert(read->display == written->display);
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
  assert(read->customer_type == written->customer_type);
}

/* Enter Order Message: written and read back, then read and written back */
static void check_enter_order_message(void) {
  EnterOrderMessage sent;
  EnterOrderMessage got;
  uint8_t wire[137];
  uint8_t again[137];

  any_enter_order_message(&sent);
  assert(encode_enter_order_message(&sent, wire, 0) == 137);
  assert(decode_enter_order_message(&got, wire, 0) == 137);
  equal_enter_order_message(&got, &sent);

  for (size_t i = 0; i < 137; i++) { wire[i] = arbitrary(); }
  assert(decode_enter_order_message(&got, wire, 0) == 137);
  assert(encode_enter_order_message(&got, again, 0) == 137);
  for (size_t i = 0; i < 137; i++) { assert(again[i] == wire[i]); }
}

/* ---- Enter Order Message With Cross Functionality: 139 bytes ----------------- */

/* Enters orders in much the same way as the Enter Order Message, with a few additional fields. Notably, the Cross Type Flag allows you to specify that an order begins participation in a cross. */
typedef struct {
  uint8_t order_token_client_order_id[14];     /* bytes 0 to 13 */
  uint8_t side;                                /* byte 14 */
  uint8_t shares_order_qty[6];                 /* bytes 15 to 20 */
  uint8_t stock_symbol[6];                     /* bytes 21 to 26 */
  uint8_t price[10];                           /* bytes 27 to 36 */
  uint8_t time_in_force[5];                    /* bytes 37 to 41 */
  uint8_t firm_client_id[4];                   /* bytes 42 to 45 */
  uint8_t display;                             /* byte 46 */
  uint8_t min_qty[6];                          /* bytes 47 to 52 */
  uint8_t max_floor[6];                        /* bytes 53 to 58 */
  uint8_t peg_type;                            /* byte 59 */
  uint8_t peg_difference_sign;                 /* byte 60 */
  uint8_t peg_difference[10];                  /* bytes 61 to 70 */
  uint8_t discretion_price[10];                /* bytes 71 to 80 */
  uint8_t discretion_peg_type;                 /* byte 81 */
  uint8_t discretion_peg_difference_sign;      /* byte 82 */
  uint8_t discretion_peg_difference[10];       /* bytes 83 to 92 */
  uint8_t capacity_rule_80_a_indicator;        /* byte 93 */
  uint8_t random_reserve[6];                   /* bytes 94 to 99 */
  uint8_t route_dest_exec_broker[4];           /* bytes 100 to 103 */
  uint8_t cust_terminal_id_sender_sub_id[32];  /* bytes 104 to 135 */
  uint8_t inter_market_sweep_eligibility;      /* byte 136 */
  uint8_t cross_type;                          /* byte 137 */
  uint8_t customer_type;                       /* byte 138 */
} EnterOrderMessageWithCrossFunctionality;

/* any Enter Order Message With Cross Functionality at all: every byte one the checker chooses */
static void any_enter_order_message_with_cross_functionality(EnterOrderMessageWithCrossFunctionality *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->shares_order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->stock_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->time_in_force[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_client_id[i] = arbitrary(); }
  record->display = arbitrary();
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
  record->customer_type = arbitrary();
}

/* Enter Order Message With Cross Functionality to the wire: 139 bytes from at, returning where the next byte goes */
static size_t encode_enter_order_message_with_cross_functionality(const EnterOrderMessageWithCrossFunctionality *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token_client_order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares_order_qty[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->stock_symbol[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->time_in_force[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_client_id[i]; }
  wire[at++] = record->display;
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
  wire[at++] = record->customer_type;

  return at;
}

/* Enter Order Message With Cross Functionality off the wire: 139 bytes from at, returning where the next byte lies */
static size_t decode_enter_order_message_with_cross_functionality(EnterOrderMessageWithCrossFunctionality *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->shares_order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->stock_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->time_in_force[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_client_id[i] = wire[at++]; }
  record->display = wire[at++];
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
  record->customer_type = wire[at++];

  return at;
}

/* what was read of Enter Order Message With Cross Functionality is what was written, byte for byte */
static void equal_enter_order_message_with_cross_functionality(const EnterOrderMessageWithCrossFunctionality *read, const EnterOrderMessageWithCrossFunctionality *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token_client_order_id[i] == written->order_token_client_order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->shares_order_qty[i] == written->shares_order_qty[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_client_id[i] == written->firm_client_id[i]); }
  assert(read->display == written->display);
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
  assert(read->customer_type == written->customer_type);
}

/* Enter Order Message With Cross Functionality: written and read back, then read and written back */
static void check_enter_order_message_with_cross_functionality(void) {
  EnterOrderMessageWithCrossFunctionality sent;
  EnterOrderMessageWithCrossFunctionality got;
  uint8_t wire[139];
  uint8_t again[139];

  any_enter_order_message_with_cross_functionality(&sent);
  assert(encode_enter_order_message_with_cross_functionality(&sent, wire, 0) == 139);
  assert(decode_enter_order_message_with_cross_functionality(&got, wire, 0) == 139);
  equal_enter_order_message_with_cross_functionality(&got, &sent);

  for (size_t i = 0; i < 139; i++) { wire[i] = arbitrary(); }
  assert(decode_enter_order_message_with_cross_functionality(&got, wire, 0) == 139);
  assert(encode_enter_order_message_with_cross_functionality(&got, again, 0) == 139);
  for (size_t i = 0; i < 139; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Message: 20 bytes ------------------------------------------ */

/* Requests that an order be canceled. A Shares field of zero cancels the entire balance of the order; otherwise Shares is the new intended order size. */
typedef struct {
  uint8_t order_token_client_order_id[14];  /* bytes 0 to 13 */
  uint8_t shares[6];                        /* bytes 14 to 19 */
} CancelOrderMessage;

/* any Cancel Order Message at all: every byte one the checker chooses */
static void any_cancel_order_message(CancelOrderMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->shares[i] = arbitrary(); }
}

/* Cancel Order Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_message(const CancelOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token_client_order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->shares[i]; }

  return at;
}

/* Cancel Order Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_message(CancelOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token_client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->shares[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Message is what was written, byte for byte */
static void equal_cancel_order_message(const CancelOrderMessage *read, const CancelOrderMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token_client_order_id[i] == written->order_token_client_order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->shares[i] == written->shares[i]); }
}

/* Cancel Order Message: written and read back, then read and written back */
static void check_cancel_order_message(void) {
  CancelOrderMessage sent;
  CancelOrderMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_cancel_order_message(&sent);
  assert(encode_cancel_order_message(&sent, wire, 0) == 20);
  assert(decode_cancel_order_message(&got, wire, 0) == 20);
  equal_cancel_order_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_message(&got, wire, 0) == 20);
  assert(encode_cancel_order_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_client_packet_header();
  check_login_request_packet();
  check_enter_order_message();
  check_enter_order_message_with_cross_functionality();
  check_cancel_order_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
