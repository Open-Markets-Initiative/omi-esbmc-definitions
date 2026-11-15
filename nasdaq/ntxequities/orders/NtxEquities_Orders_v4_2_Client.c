// nasdaq/ntxequities/orders/NtxEquities_Orders_v4_2_Client.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) BX Orders
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

/* ---- Enter Order Message: 47 bytes ------------------------------------------- */

typedef struct {
  uint8_t order_token[14];                /* bytes 0 to 13 */
  uint8_t buy_sell_indicator;             /* byte 14 */
  uint8_t shares[4];                      /* bytes 15 to 18 */
  uint8_t stock[8];                       /* bytes 19 to 26 */
  uint8_t price[4];                       /* bytes 27 to 30 */
  uint8_t time_in_force[4];               /* bytes 31 to 34 */
  uint8_t firm[4];                        /* bytes 35 to 38 */
  uint8_t display;                        /* byte 39 */
  uint8_t capacity;                       /* byte 40 */
  uint8_t intermarket_sweep_eligibility;  /* byte 41 */
  uint8_t minimum_quantity[4];            /* bytes 42 to 45 */
  uint8_t cross_type;                     /* byte 46 */
} EnterOrderMessage;

/* any Enter Order Message at all: every byte one the checker chooses */
static void any_enter_order_message(EnterOrderMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm[i] = arbitrary(); }
  record->display = arbitrary();
  record->capacity = arbitrary();
  record->intermarket_sweep_eligibility = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = arbitrary(); }
  record->cross_type = arbitrary();
}

/* Enter Order Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_enter_order_message(const EnterOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_in_force[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm[i]; }
  wire[at++] = record->display;
  wire[at++] = record->capacity;
  wire[at++] = record->intermarket_sweep_eligibility;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity[i]; }
  wire[at++] = record->cross_type;

  return at;
}

/* Enter Order Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_enter_order_message(EnterOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm[i] = wire[at++]; }
  record->display = wire[at++];
  record->capacity = wire[at++];
  record->intermarket_sweep_eligibility = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = wire[at++]; }
  record->cross_type = wire[at++];

  return at;
}

/* what was read of Enter Order Message is what was written, byte for byte */
static void equal_enter_order_message(const EnterOrderMessage *read, const EnterOrderMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock[i] == written->stock[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm[i] == written->firm[i]); }
  assert(read->display == written->display);
  assert(read->capacity == written->capacity);
  assert(read->intermarket_sweep_eligibility == written->intermarket_sweep_eligibility);
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
  assert(read->cross_type == written->cross_type);
}

/* Enter Order Message: written and read back, then read and written back */
static void check_enter_order_message(void) {
  EnterOrderMessage sent;
  EnterOrderMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_enter_order_message(&sent);
  assert(encode_enter_order_message(&sent, wire, 0) == 47);
  assert(decode_enter_order_message(&got, wire, 0) == 47);
  equal_enter_order_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_enter_order_message(&got, wire, 0) == 47);
  assert(encode_enter_order_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replace Order Message: 46 bytes ----------------------------------------- */

typedef struct {
  uint8_t existing_order_token[14];       /* bytes 0 to 13 */
  uint8_t replacement_order_token[14];    /* bytes 14 to 27 */
  uint8_t shares[4];                      /* bytes 28 to 31 */
  uint8_t price[4];                       /* bytes 32 to 35 */
  uint8_t time_in_force[4];               /* bytes 36 to 39 */
  uint8_t display;                        /* byte 40 */
  uint8_t intermarket_sweep_eligibility;  /* byte 41 */
  uint8_t minimum_quantity[4];            /* bytes 42 to 45 */
} ReplaceOrderMessage;

/* any Replace Order Message at all: every byte one the checker chooses */
static void any_replace_order_message(ReplaceOrderMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->existing_order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->replacement_order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = arbitrary(); }
  record->display = arbitrary();
  record->intermarket_sweep_eligibility = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = arbitrary(); }
}

/* Replace Order Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_replace_order_message(const ReplaceOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->existing_order_token[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->replacement_order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_in_force[i]; }
  wire[at++] = record->display;
  wire[at++] = record->intermarket_sweep_eligibility;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity[i]; }

  return at;
}

/* Replace Order Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_replace_order_message(ReplaceOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->existing_order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->replacement_order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = wire[at++]; }
  record->display = wire[at++];
  record->intermarket_sweep_eligibility = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Replace Order Message is what was written, byte for byte */
static void equal_replace_order_message(const ReplaceOrderMessage *read, const ReplaceOrderMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->existing_order_token[i] == written->existing_order_token[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->replacement_order_token[i] == written->replacement_order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  assert(read->display == written->display);
  assert(read->intermarket_sweep_eligibility == written->intermarket_sweep_eligibility);
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
}

/* Replace Order Message: written and read back, then read and written back */
static void check_replace_order_message(void) {
  ReplaceOrderMessage sent;
  ReplaceOrderMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_replace_order_message(&sent);
  assert(encode_replace_order_message(&sent, wire, 0) == 46);
  assert(decode_replace_order_message(&got, wire, 0) == 46);
  equal_replace_order_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_replace_order_message(&got, wire, 0) == 46);
  assert(encode_replace_order_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Message: 18 bytes ------------------------------------------ */

typedef struct {
  uint8_t order_token[14];  /* bytes 0 to 13 */
  uint8_t shares[4];        /* bytes 14 to 17 */
} CancelOrderMessage;

/* any Cancel Order Message at all: every byte one the checker chooses */
static void any_cancel_order_message(CancelOrderMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
}

/* Cancel Order Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_message(const CancelOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }

  return at;
}

/* Cancel Order Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_message(CancelOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Message is what was written, byte for byte */
static void equal_cancel_order_message(const CancelOrderMessage *read, const CancelOrderMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
}

/* Cancel Order Message: written and read back, then read and written back */
static void check_cancel_order_message(void) {
  CancelOrderMessage sent;
  CancelOrderMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_cancel_order_message(&sent);
  assert(encode_cancel_order_message(&sent, wire, 0) == 18);
  assert(decode_cancel_order_message(&got, wire, 0) == 18);
  equal_cancel_order_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_message(&got, wire, 0) == 18);
  assert(encode_cancel_order_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Message: 19 bytes ------------------------------------------ */

typedef struct {
  uint8_t order_token[14];     /* bytes 0 to 13 */
  uint8_t buy_sell_indicator;  /* byte 14 */
  uint8_t shares[4];           /* bytes 15 to 18 */
} ModifyOrderMessage;

/* any Modify Order Message at all: every byte one the checker chooses */
static void any_modify_order_message(ModifyOrderMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  record->buy_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
}

/* Modify Order Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_message(const ModifyOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  wire[at++] = record->buy_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }

  return at;
}

/* Modify Order Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_message(ModifyOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  record->buy_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Order Message is what was written, byte for byte */
static void equal_modify_order_message(const ModifyOrderMessage *read, const ModifyOrderMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
}

/* Modify Order Message: written and read back, then read and written back */
static void check_modify_order_message(void) {
  ModifyOrderMessage sent;
  ModifyOrderMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_modify_order_message(&sent);
  assert(encode_modify_order_message(&sent, wire, 0) == 19);
  assert(decode_modify_order_message(&got, wire, 0) == 19);
  equal_modify_order_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_message(&got, wire, 0) == 19);
  assert(encode_modify_order_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Now Message: 14 bytes --------------------------------------------- */

typedef struct {
  uint8_t order_token[14];  /* bytes 0 to 13 */
} TradeNowMessage;

/* any Trade Now Message at all: every byte one the checker chooses */
static void any_trade_now_message(TradeNowMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
}

/* Trade Now Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_trade_now_message(const TradeNowMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }

  return at;
}

/* Trade Now Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_trade_now_message(TradeNowMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Now Message is what was written, byte for byte */
static void equal_trade_now_message(const TradeNowMessage *read, const TradeNowMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
}

/* Trade Now Message: written and read back, then read and written back */
static void check_trade_now_message(void) {
  TradeNowMessage sent;
  TradeNowMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_trade_now_message(&sent);
  assert(encode_trade_now_message(&sent, wire, 0) == 14);
  assert(decode_trade_now_message(&got, wire, 0) == 14);
  equal_trade_now_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_now_message(&got, wire, 0) == 14);
  assert(encode_trade_now_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_client_packet_header();
  check_login_request_packet();
  check_enter_order_message();
  check_replace_order_message();
  check_cancel_order_message();
  check_modify_order_message();
  check_trade_now_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
