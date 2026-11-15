// odx/odxequities/pts/OdxEquities_Pts_Ouch_v1_0_Client.c
/*
 * Osaka Digital Exchange Proprietary Trading System
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

/* An Enter Order Message is used to enter a new order into the ODX PTS execution system */
typedef struct {
  uint8_t order_token[4];        /* bytes 0 to 3 */
  uint8_t client_reference[10];  /* bytes 4 to 13 */
  uint8_t buy_sell_indicator;    /* byte 14 */
  uint8_t quantity[4];           /* bytes 15 to 18 */
  uint8_t orderbook_id[4];       /* bytes 19 to 22 */
  uint8_t group[4];              /* bytes 23 to 26 */
  uint8_t price[4];              /* bytes 27 to 30 */
  uint8_t time_in_force[4];      /* bytes 31 to 34 */
  uint8_t firm_id[4];            /* bytes 35 to 38 */
  uint8_t display;               /* byte 39 */
  uint8_t capacity;              /* byte 40 */
  uint8_t minimum_quantity[4];   /* bytes 41 to 44 */
  uint8_t order_classification;  /* byte 45 */
  uint8_t cash_margin_type;      /* byte 46 */
} EnterOrderMessage;

/* any Enter Order Message at all: every byte one the checker chooses */
static void any_enter_order_message(EnterOrderMessage *record) {
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
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = arbitrary(); }
  record->order_classification = arbitrary();
  record->cash_margin_type = arbitrary();
}

/* Enter Order Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_enter_order_message(const EnterOrderMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity[i]; }
  wire[at++] = record->order_classification;
  wire[at++] = record->cash_margin_type;

  return at;
}

/* Enter Order Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_enter_order_message(EnterOrderMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = wire[at++]; }
  record->order_classification = wire[at++];
  record->cash_margin_type = wire[at++];

  return at;
}

/* what was read of Enter Order Message is what was written, byte for byte */
static void equal_enter_order_message(const EnterOrderMessage *read, const EnterOrderMessage *written) {
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
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
  assert(read->order_classification == written->order_classification);
  assert(read->cash_margin_type == written->cash_margin_type);
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

/* ---- Replace Order Message: 25 bytes ----------------------------------------- */

/* A Replace Order Message is used to modify an existing order */
typedef struct {
  uint8_t existing_order_token[4];     /* bytes 0 to 3 */
  uint8_t replacement_order_token[4];  /* bytes 4 to 7 */
  uint8_t quantity[4];                 /* bytes 8 to 11 */
  uint8_t price[4];                    /* bytes 12 to 15 */
  uint8_t time_in_force[4];            /* bytes 16 to 19 */
  uint8_t display;                     /* byte 20 */
  uint8_t minimum_quantity[4];         /* bytes 21 to 24 */
} ReplaceOrderMessage;

/* any Replace Order Message at all: every byte one the checker chooses */
static void any_replace_order_message(ReplaceOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->existing_order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->replacement_order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = arbitrary(); }
  record->display = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = arbitrary(); }
}

/* Replace Order Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_replace_order_message(const ReplaceOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->existing_order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->replacement_order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_in_force[i]; }
  wire[at++] = record->display;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity[i]; }

  return at;
}

/* Replace Order Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_replace_order_message(ReplaceOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->existing_order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->replacement_order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->time_in_force[i] = wire[at++]; }
  record->display = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Replace Order Message is what was written, byte for byte */
static void equal_replace_order_message(const ReplaceOrderMessage *read, const ReplaceOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->existing_order_token[i] == written->existing_order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->replacement_order_token[i] == written->replacement_order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->time_in_force[i] == written->time_in_force[i]); }
  assert(read->display == written->display);
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
}

/* Replace Order Message: written and read back, then read and written back */
static void check_replace_order_message(void) {
  ReplaceOrderMessage sent;
  ReplaceOrderMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_replace_order_message(&sent);
  assert(encode_replace_order_message(&sent, wire, 0) == 25);
  assert(decode_replace_order_message(&got, wire, 0) == 25);
  equal_replace_order_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_replace_order_message(&got, wire, 0) == 25);
  assert(encode_replace_order_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Message: 8 bytes ------------------------------------------- */

/* A Cancel Order Message is used to request that an order be canceled */
typedef struct {
  uint8_t order_token[4];  /* bytes 0 to 3 */
  uint8_t quantity[4];     /* bytes 4 to 7 */
} CancelOrderMessage;

/* any Cancel Order Message at all: every byte one the checker chooses */
static void any_cancel_order_message(CancelOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
}

/* Cancel Order Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_message(const CancelOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Cancel Order Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_message(CancelOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Message is what was written, byte for byte */
static void equal_cancel_order_message(const CancelOrderMessage *read, const CancelOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Cancel Order Message: written and read back, then read and written back */
static void check_cancel_order_message(void) {
  CancelOrderMessage sent;
  CancelOrderMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_cancel_order_message(&sent);
  assert(encode_cancel_order_message(&sent, wire, 0) == 8);
  assert(decode_cancel_order_message(&got, wire, 0) == 8);
  equal_cancel_order_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_message(&got, wire, 0) == 8);
  assert(encode_cancel_order_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_client_packet_header();
  check_login_request_packet();
  check_enter_order_message();
  check_replace_order_message();
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
