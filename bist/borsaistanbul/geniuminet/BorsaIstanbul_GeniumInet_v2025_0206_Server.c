// bist/borsaistanbul/geniuminet/BorsaIstanbul_GeniumInet_v2025_0206_Server.c
/*
 * Borsa İstanbul A.Ş. Genium Inet
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

/* ---- Order Accepted: 136 bytes ----------------------------------------------- */

/* Acknowledges the receipt and acceptance of a valid Enter Order message. The data fields from the Enter Order message are echoed back, though accepted values may differ from entered values for some fields. Accepted messages are guaranteed to come before any Executed or Canceled messages for an order. */
typedef struct {
  uint8_t nanoseconds[8];              /* bytes 0 to 7 */
  uint8_t order_token[14];             /* bytes 8 to 21 */
  uint8_t order_book_id[4];            /* bytes 22 to 25 */
  uint8_t side;                        /* byte 26 */
  uint8_t order_id[8];                 /* bytes 27 to 34 */
  uint8_t quantity[8];                 /* bytes 35 to 42 */
  uint8_t price[4];                    /* bytes 43 to 46 */
  uint8_t time_in_force;               /* byte 47 */
  uint8_t open_close;                  /* byte 48 */
  uint8_t client_account[16];          /* bytes 49 to 64 */
  uint8_t order_state;                 /* byte 65 */
  uint8_t customer_info[15];           /* bytes 66 to 80 */
  uint8_t exchange_info_alpha_32[32];  /* bytes 81 to 112 */
  uint8_t pre_trade_quantity[8];       /* bytes 113 to 120 */
  uint8_t display_quantity[8];         /* bytes 121 to 128 */
  uint8_t client_category;             /* byte 129 */
  uint8_t off_hours;                   /* byte 130 */
  uint8_t smp_level;                   /* byte 131 */
  uint8_t smp_method;                  /* byte 132 */
  uint8_t smp_id[3];                   /* bytes 133 to 135 */
} OrderAccepted;

/* any Order Accepted at all: every byte one the checker chooses */
static void any_order_accepted(OrderAccepted *record) {
  for (size_t i = 0; i < 8; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->open_close = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->client_account[i] = arbitrary(); }
  record->order_state = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->exchange_info_alpha_32[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pre_trade_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->display_quantity[i] = arbitrary(); }
  record->client_category = arbitrary();
  record->off_hours = arbitrary();
  record->smp_level = arbitrary();
  record->smp_method = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->smp_id[i] = arbitrary(); }
}

/* Order Accepted to the wire: 136 bytes from at, returning where the next byte goes */
static size_t encode_order_accepted(const OrderAccepted *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_account[i]; }
  wire[at++] = record->order_state;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->customer_info[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->exchange_info_alpha_32[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pre_trade_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->display_quantity[i]; }
  wire[at++] = record->client_category;
  wire[at++] = record->off_hours;
  wire[at++] = record->smp_level;
  wire[at++] = record->smp_method;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->smp_id[i]; }

  return at;
}

/* Order Accepted off the wire: 136 bytes from at, returning where the next byte lies */
static size_t decode_order_accepted(OrderAccepted *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->open_close = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->client_account[i] = wire[at++]; }
  record->order_state = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->exchange_info_alpha_32[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pre_trade_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->display_quantity[i] = wire[at++]; }
  record->client_category = wire[at++];
  record->off_hours = wire[at++];
  record->smp_level = wire[at++];
  record->smp_method = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->smp_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Accepted is what was written, byte for byte */
static void equal_order_accepted(const OrderAccepted *read, const OrderAccepted *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 16; i++) { assert(read->client_account[i] == written->client_account[i]); }
  assert(read->order_state == written->order_state);
  for (size_t i = 0; i < 15; i++) { assert(read->customer_info[i] == written->customer_info[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->exchange_info_alpha_32[i] == written->exchange_info_alpha_32[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pre_trade_quantity[i] == written->pre_trade_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->display_quantity[i] == written->display_quantity[i]); }
  assert(read->client_category == written->client_category);
  assert(read->off_hours == written->off_hours);
  assert(read->smp_level == written->smp_level);
  assert(read->smp_method == written->smp_method);
  for (size_t i = 0; i < 3; i++) { assert(read->smp_id[i] == written->smp_id[i]); }
}

/* Order Accepted: written and read back, then read and written back */
static void check_order_accepted(void) {
  OrderAccepted sent;
  OrderAccepted got;
  uint8_t wire[136];
  uint8_t again[136];

  any_order_accepted(&sent);
  assert(encode_order_accepted(&sent, wire, 0) == 136);
  assert(decode_order_accepted(&got, wire, 0) == 136);
  equal_order_accepted(&got, &sent);

  for (size_t i = 0; i < 136; i++) { wire[i] = arbitrary(); }
  assert(decode_order_accepted(&got, wire, 0) == 136);
  assert(encode_order_accepted(&got, again, 0) == 136);
  for (size_t i = 0; i < 136; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Rejected: 26 bytes ------------------------------------------------ */

/* Used to reject Enter Order messages, Cancel Order messages, and Replace Order messages. */
typedef struct {
  uint8_t nanoseconds[8];   /* bytes 0 to 7 */
  uint8_t order_token[14];  /* bytes 8 to 21 */
  uint8_t reject_code[4];   /* bytes 22 to 25 */
} OrderRejected;

/* any Order Rejected at all: every byte one the checker chooses */
static void any_order_rejected(OrderRejected *record) {
  for (size_t i = 0; i < 8; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = arbitrary(); }
}

/* Order Rejected to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_order_rejected(const OrderRejected *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reject_code[i]; }

  return at;
}

/* Order Rejected off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_order_rejected(OrderRejected *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = wire[at++]; }

  return at;
}

/* what was read of Order Rejected is what was written, byte for byte */
static void equal_order_rejected(const OrderRejected *read, const OrderRejected *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
}

/* Order Rejected: written and read back, then read and written back */
static void check_order_rejected(void) {
  OrderRejected sent;
  OrderRejected got;
  uint8_t wire[26];
  uint8_t again[26];

  any_order_rejected(&sent);
  assert(encode_order_rejected(&sent, wire, 0) == 26);
  assert(decode_order_rejected(&got, wire, 0) == 26);
  equal_order_rejected(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_order_rejected(&got, wire, 0) == 26);
  assert(encode_order_rejected(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Replaced: 144 bytes ----------------------------------------------- */

/* Acknowledges the receipt and acceptance of a valid Replace Order message. The data fields from the Replace Order message are echoed back, though accepted values may differ from entered values for some fields. Uses the Order State field to denote that a replace was accepted and then automatically canceled when the Order State is Not on book. */
typedef struct {
  uint8_t nanoseconds[8];               /* bytes 0 to 7 */
  uint8_t replacement_order_token[14];  /* bytes 8 to 21 */
  uint8_t previous_order_token[14];     /* bytes 22 to 35 */
  uint8_t order_book_id[4];             /* bytes 36 to 39 */
  uint8_t side;                         /* byte 40 */
  uint8_t order_id[8];                  /* bytes 41 to 48 */
  uint8_t quantity[8];                  /* bytes 49 to 56 */
  uint8_t price[4];                     /* bytes 57 to 60 */
  uint8_t time_in_force;                /* byte 61 */
  uint8_t replace_open_close;           /* byte 62 */
  uint8_t client_account[16];           /* bytes 63 to 78 */
  uint8_t order_state;                  /* byte 79 */
  uint8_t customer_info[15];            /* bytes 80 to 94 */
  uint8_t exchange_info_alpha_32[32];   /* bytes 95 to 126 */
  uint8_t pre_trade_quantity[8];        /* bytes 127 to 134 */
  uint8_t display_quantity[8];          /* bytes 135 to 142 */
  uint8_t client_category;              /* byte 143 */
} OrderReplaced;

/* any Order Replaced at all: every byte one the checker chooses */
static void any_order_replaced(OrderReplaced *record) {
  for (size_t i = 0; i < 8; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->replacement_order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->previous_order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->replace_open_close = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->client_account[i] = arbitrary(); }
  record->order_state = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->exchange_info_alpha_32[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pre_trade_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->display_quantity[i] = arbitrary(); }
  record->client_category = arbitrary();
}

/* Order Replaced to the wire: 144 bytes from at, returning where the next byte goes */
static size_t encode_order_replaced(const OrderReplaced *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->replacement_order_token[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->previous_order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->replace_open_close;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_account[i]; }
  wire[at++] = record->order_state;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->customer_info[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->exchange_info_alpha_32[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pre_trade_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->display_quantity[i]; }
  wire[at++] = record->client_category;

  return at;
}

/* Order Replaced off the wire: 144 bytes from at, returning where the next byte lies */
static size_t decode_order_replaced(OrderReplaced *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->replacement_order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->previous_order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->replace_open_close = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->client_account[i] = wire[at++]; }
  record->order_state = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->exchange_info_alpha_32[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pre_trade_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->display_quantity[i] = wire[at++]; }
  record->client_category = wire[at++];

  return at;
}

/* what was read of Order Replaced is what was written, byte for byte */
static void equal_order_replaced(const OrderReplaced *read, const OrderReplaced *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->replacement_order_token[i] == written->replacement_order_token[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->previous_order_token[i] == written->previous_order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->replace_open_close == written->replace_open_close);
  for (size_t i = 0; i < 16; i++) { assert(read->client_account[i] == written->client_account[i]); }
  assert(read->order_state == written->order_state);
  for (size_t i = 0; i < 15; i++) { assert(read->customer_info[i] == written->customer_info[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->exchange_info_alpha_32[i] == written->exchange_info_alpha_32[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pre_trade_quantity[i] == written->pre_trade_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->display_quantity[i] == written->display_quantity[i]); }
  assert(read->client_category == written->client_category);
}

/* Order Replaced: written and read back, then read and written back */
static void check_order_replaced(void) {
  OrderReplaced sent;
  OrderReplaced got;
  uint8_t wire[144];
  uint8_t again[144];

  any_order_replaced(&sent);
  assert(encode_order_replaced(&sent, wire, 0) == 144);
  assert(decode_order_replaced(&got, wire, 0) == 144);
  equal_order_replaced(&got, &sent);

  for (size_t i = 0; i < 144; i++) { wire[i] = arbitrary(); }
  assert(decode_order_replaced(&got, wire, 0) == 144);
  assert(encode_order_replaced(&got, again, 0) == 144);
  for (size_t i = 0; i < 144; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Canceled: 36 bytes ------------------------------------------------ */

/* Informs that an order has been canceled. This could be acknowledging a Cancel Order message, or the result of system cancellation. Order Canceled messages are sent when orders are suspended due to connection loss; more than one Order Canceled message may be received for the same order. */
typedef struct {
  uint8_t nanoseconds[8];    /* bytes 0 to 7 */
  uint8_t order_token[14];   /* bytes 8 to 21 */
  uint8_t order_book_id[4];  /* bytes 22 to 25 */
  uint8_t side;              /* byte 26 */
  uint8_t order_id[8];       /* bytes 27 to 34 */
  uint8_t reason;            /* byte 35 */
} OrderCanceled;

/* any Order Canceled at all: every byte one the checker chooses */
static void any_order_canceled(OrderCanceled *record) {
  for (size_t i = 0; i < 8; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->reason = arbitrary();
}

/* Order Canceled to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_order_canceled(const OrderCanceled *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->reason;

  return at;
}

/* Order Canceled off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_order_canceled(OrderCanceled *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->reason = wire[at++];

  return at;
}

/* what was read of Order Canceled is what was written, byte for byte */
static void equal_order_canceled(const OrderCanceled *read, const OrderCanceled *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->reason == written->reason);
}

/* Order Canceled: written and read back, then read and written back */
static void check_order_canceled(void) {
  OrderCanceled sent;
  OrderCanceled got;
  uint8_t wire[36];
  uint8_t again[36];

  any_order_canceled(&sent);
  assert(encode_order_canceled(&sent, wire, 0) == 36);
  assert(decode_order_canceled(&got, wire, 0) == 36);
  equal_order_canceled(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_order_canceled(&got, wire, 0) == 36);
  assert(encode_order_canceled(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed: 67 bytes ------------------------------------------------ */

/* Returned when a partial or full fill occurs. In case of a combination order fill, one Order Executed message will be received per leg. */
typedef struct {
  uint8_t nanoseconds[8];                    /* bytes 0 to 7 */
  uint8_t order_token[14];                   /* bytes 8 to 21 */
  uint8_t order_book_id[4];                  /* bytes 22 to 25 */
  uint8_t traded_quantity[8];                /* bytes 26 to 33 */
  uint8_t trade_price[4];                    /* bytes 34 to 37 */
  uint8_t match_id[12];                      /* bytes 38 to 49 */
  uint8_t client_category;                   /* byte 50 */
  uint8_t reserved_numeric_unsigned_16[16];  /* bytes 51 to 66 */
} OrderExecuted;

/* any Order Executed at all: every byte one the checker chooses */
static void any_order_executed(OrderExecuted *record) {
  for (size_t i = 0; i < 8; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->traded_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->match_id[i] = arbitrary(); }
  record->client_category = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reserved_numeric_unsigned_16[i] = arbitrary(); }
}

/* Order Executed to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_order_executed(const OrderExecuted *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->traded_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->match_id[i]; }
  wire[at++] = record->client_category;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_numeric_unsigned_16[i]; }

  return at;
}

/* Order Executed off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_order_executed(OrderExecuted *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->traded_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->match_id[i] = wire[at++]; }
  record->client_category = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reserved_numeric_unsigned_16[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed is what was written, byte for byte */
static void equal_order_executed(const OrderExecuted *read, const OrderExecuted *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->traded_quantity[i] == written->traded_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->match_id[i] == written->match_id[i]); }
  assert(read->client_category == written->client_category);
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_numeric_unsigned_16[i] == written->reserved_numeric_unsigned_16[i]); }
}

/* Order Executed: written and read back, then read and written back */
static void check_order_executed(void) {
  OrderExecuted sent;
  OrderExecuted got;
  uint8_t wire[67];
  uint8_t again[67];

  any_order_executed(&sent);
  assert(encode_order_executed(&sent, wire, 0) == 67);
  assert(decode_order_executed(&got, wire, 0) == 67);
  equal_order_executed(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed(&got, wire, 0) == 67);
  assert(encode_order_executed(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Quote Acknowledgement: 51 bytes ------------------------------------ */

/* A positive response to a Mass Quote message. Every quote in a mass quote message must be responded to with an individual message (Mass Quote Acknowledgement or Mass Quote Rejection). If the individual quote in mass quote is accepted, the system sends two Mass Quote Acknowledgement messages, for bid and offer side. */
typedef struct {
  uint8_t nanoseconds[8];      /* bytes 0 to 7 */
  uint8_t order_token[14];     /* bytes 8 to 21 */
  uint8_t order_book_id[4];    /* bytes 22 to 25 */
  uint8_t quantity[8];         /* bytes 26 to 33 */
  uint8_t traded_quantity[8];  /* bytes 34 to 41 */
  uint8_t price[4];            /* bytes 42 to 45 */
  uint8_t quote_side;          /* byte 46 */
  uint8_t quote_status[4];     /* bytes 47 to 50 */
} MassQuoteAcknowledgement;

/* any Mass Quote Acknowledgement at all: every byte one the checker chooses */
static void any_mass_quote_acknowledgement(MassQuoteAcknowledgement *record) {
  for (size_t i = 0; i < 8; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->traded_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->quote_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quote_status[i] = arbitrary(); }
}

/* Mass Quote Acknowledgement to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_mass_quote_acknowledgement(const MassQuoteAcknowledgement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->traded_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->quote_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quote_status[i]; }

  return at;
}

/* Mass Quote Acknowledgement off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_mass_quote_acknowledgement(MassQuoteAcknowledgement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->traded_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->quote_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quote_status[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Quote Acknowledgement is what was written, byte for byte */
static void equal_mass_quote_acknowledgement(const MassQuoteAcknowledgement *read, const MassQuoteAcknowledgement *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->traded_quantity[i] == written->traded_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->quote_side == written->quote_side);
  for (size_t i = 0; i < 4; i++) { assert(read->quote_status[i] == written->quote_status[i]); }
}

/* Mass Quote Acknowledgement: written and read back, then read and written back */
static void check_mass_quote_acknowledgement(void) {
  MassQuoteAcknowledgement sent;
  MassQuoteAcknowledgement got;
  uint8_t wire[51];
  uint8_t again[51];

  any_mass_quote_acknowledgement(&sent);
  assert(encode_mass_quote_acknowledgement(&sent, wire, 0) == 51);
  assert(decode_mass_quote_acknowledgement(&got, wire, 0) == 51);
  equal_mass_quote_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_quote_acknowledgement(&got, wire, 0) == 51);
  assert(encode_mass_quote_acknowledgement(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Quote Rejection: 30 bytes ------------------------------------------ */

/* A negative response to a Mass Quote message. If an individual quote in the mass quote is rejected, a single Mass Quote Rejection is sent for that quote with the Order Book Id populated. If all quotes in the mass quote message are rejected, only one Mass Quote Rejection is sent for the whole request, without an Order Book Id. */
typedef struct {
  uint8_t nanoseconds[8];    /* bytes 0 to 7 */
  uint8_t order_token[14];   /* bytes 8 to 21 */
  uint8_t order_book_id[4];  /* bytes 22 to 25 */
  uint8_t reject_code[4];    /* bytes 26 to 29 */
} MassQuoteRejection;

/* any Mass Quote Rejection at all: every byte one the checker chooses */
static void any_mass_quote_rejection(MassQuoteRejection *record) {
  for (size_t i = 0; i < 8; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = arbitrary(); }
}

/* Mass Quote Rejection to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_mass_quote_rejection(const MassQuoteRejection *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reject_code[i]; }

  return at;
}

/* Mass Quote Rejection off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_mass_quote_rejection(MassQuoteRejection *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Quote Rejection is what was written, byte for byte */
static void equal_mass_quote_rejection(const MassQuoteRejection *read, const MassQuoteRejection *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
}

/* Mass Quote Rejection: written and read back, then read and written back */
static void check_mass_quote_rejection(void) {
  MassQuoteRejection sent;
  MassQuoteRejection got;
  uint8_t wire[30];
  uint8_t again[30];

  any_mass_quote_rejection(&sent);
  assert(encode_mass_quote_rejection(&sent, wire, 0) == 30);
  assert(decode_mass_quote_rejection(&got, wire, 0) == 30);
  equal_mass_quote_rejection(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_quote_rejection(&got, wire, 0) == 30);
  assert(encode_mass_quote_rejection(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_order_accepted();
  check_order_rejected();
  check_order_replaced();
  check_order_canceled();
  check_order_executed();
  check_mass_quote_acknowledgement();
  check_mass_quote_rejection();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
