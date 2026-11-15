// jpx/osederivatives/geniuminet/OseDerivatives_GeniumInet_v5_0_Client.c
/*
 * Japan Exchange Group Genium Inet
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

/* ---- Enter Order: 96 bytes --------------------------------------------------- */

/* Client-generated enter order request. */
typedef struct {
  uint8_t order_token[14];     /* bytes 0 to 13 */
  uint8_t order_book_id[4];    /* bytes 14 to 17 */
  uint8_t side;                /* byte 18 */
  uint8_t quantity[8];         /* bytes 19 to 26 */
  uint8_t price[4];            /* bytes 27 to 30 */
  uint8_t time_in_force;       /* byte 31 */
  uint8_t open_close;          /* byte 32 */
  uint8_t client_account[16];  /* bytes 33 to 48 */
  uint8_t customer_info[15];   /* bytes 49 to 63 */
  uint8_t exchange_info[32];   /* bytes 64 to 95 */
} EnterOrder;

/* any Enter Order at all: every byte one the checker chooses */
static void any_enter_order(EnterOrder *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->open_close = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->client_account[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->exchange_info[i] = arbitrary(); }
}

/* Enter Order to the wire: 96 bytes from at, returning where the next byte goes */
static size_t encode_enter_order(const EnterOrder *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_account[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->customer_info[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->exchange_info[i]; }

  return at;
}

/* Enter Order off the wire: 96 bytes from at, returning where the next byte lies */
static size_t decode_enter_order(EnterOrder *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->open_close = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->client_account[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->exchange_info[i] = wire[at++]; }

  return at;
}

/* what was read of Enter Order is what was written, byte for byte */
static void equal_enter_order(const EnterOrder *read, const EnterOrder *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 16; i++) { assert(read->client_account[i] == written->client_account[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->customer_info[i] == written->customer_info[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->exchange_info[i] == written->exchange_info[i]); }
}

/* Enter Order: written and read back, then read and written back */
static void check_enter_order(void) {
  EnterOrder sent;
  EnterOrder got;
  uint8_t wire[96];
  uint8_t again[96];

  any_enter_order(&sent);
  assert(encode_enter_order(&sent, wire, 0) == 96);
  assert(decode_enter_order(&got, wire, 0) == 96);
  equal_enter_order(&got, &sent);

  for (size_t i = 0; i < 96; i++) { wire[i] = arbitrary(); }
  assert(decode_enter_order(&got, wire, 0) == 96);
  assert(encode_enter_order(&got, again, 0) == 96);
  for (size_t i = 0; i < 96; i++) { assert(again[i] == wire[i]); }
}

/* ---- Enter Mm Order: 79 bytes ------------------------------------------------ */

/* Client-generated enter market maker order request. */
typedef struct {
  uint8_t order_token[14];     /* bytes 0 to 13 */
  uint8_t order_book_id[4];    /* bytes 14 to 17 */
  uint8_t side;                /* byte 18 */
  uint8_t quantity[8];         /* bytes 19 to 26 */
  uint8_t price[4];            /* bytes 27 to 30 */
  uint8_t client_account[16];  /* bytes 31 to 46 */
  uint8_t exchange_info[32];   /* bytes 47 to 78 */
} EnterMmOrder;

/* any Enter Mm Order at all: every byte one the checker chooses */
static void any_enter_mm_order(EnterMmOrder *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->client_account[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->exchange_info[i] = arbitrary(); }
}

/* Enter Mm Order to the wire: 79 bytes from at, returning where the next byte goes */
static size_t encode_enter_mm_order(const EnterMmOrder *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_account[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->exchange_info[i]; }

  return at;
}

/* Enter Mm Order off the wire: 79 bytes from at, returning where the next byte lies */
static size_t decode_enter_mm_order(EnterMmOrder *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->client_account[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->exchange_info[i] = wire[at++]; }

  return at;
}

/* what was read of Enter Mm Order is what was written, byte for byte */
static void equal_enter_mm_order(const EnterMmOrder *read, const EnterMmOrder *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->client_account[i] == written->client_account[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->exchange_info[i] == written->exchange_info[i]); }
}

/* Enter Mm Order: written and read back, then read and written back */
static void check_enter_mm_order(void) {
  EnterMmOrder sent;
  EnterMmOrder got;
  uint8_t wire[79];
  uint8_t again[79];

  any_enter_mm_order(&sent);
  assert(encode_enter_mm_order(&sent, wire, 0) == 79);
  assert(decode_enter_mm_order(&got, wire, 0) == 79);
  equal_enter_mm_order(&got, &sent);

  for (size_t i = 0; i < 79; i++) { wire[i] = arbitrary(); }
  assert(decode_enter_mm_order(&got, wire, 0) == 79);
  assert(encode_enter_mm_order(&got, again, 0) == 79);
  for (size_t i = 0; i < 79; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replace Order: 104 bytes ------------------------------------------------ */

/* Client-generated replace order request. */
typedef struct {
  uint8_t existing_order_token[14];     /* bytes 0 to 13 */
  uint8_t replacement_order_token[14];  /* bytes 14 to 27 */
  uint8_t quantity[8];                  /* bytes 28 to 35 */
  uint8_t price[4];                     /* bytes 36 to 39 */
  uint8_t open_close;                   /* byte 40 */
  uint8_t client_account[16];           /* bytes 41 to 56 */
  uint8_t customer_info[15];            /* bytes 57 to 71 */
  uint8_t exchange_info[32];            /* bytes 72 to 103 */
} ReplaceOrder;

/* any Replace Order at all: every byte one the checker chooses */
static void any_replace_order(ReplaceOrder *record) {
  for (size_t i = 0; i < 14; i++) { record->existing_order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->replacement_order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->open_close = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->client_account[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->exchange_info[i] = arbitrary(); }
}

/* Replace Order to the wire: 104 bytes from at, returning where the next byte goes */
static size_t encode_replace_order(const ReplaceOrder *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->existing_order_token[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->replacement_order_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_account[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->customer_info[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->exchange_info[i]; }

  return at;
}

/* Replace Order off the wire: 104 bytes from at, returning where the next byte lies */
static size_t decode_replace_order(ReplaceOrder *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->existing_order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->replacement_order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->open_close = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->client_account[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->exchange_info[i] = wire[at++]; }

  return at;
}

/* what was read of Replace Order is what was written, byte for byte */
static void equal_replace_order(const ReplaceOrder *read, const ReplaceOrder *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->existing_order_token[i] == written->existing_order_token[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->replacement_order_token[i] == written->replacement_order_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 16; i++) { assert(read->client_account[i] == written->client_account[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->customer_info[i] == written->customer_info[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->exchange_info[i] == written->exchange_info[i]); }
}

/* Replace Order: written and read back, then read and written back */
static void check_replace_order(void) {
  ReplaceOrder sent;
  ReplaceOrder got;
  uint8_t wire[104];
  uint8_t again[104];

  any_replace_order(&sent);
  assert(encode_replace_order(&sent, wire, 0) == 104);
  assert(decode_replace_order(&got, wire, 0) == 104);
  equal_replace_order(&got, &sent);

  for (size_t i = 0; i < 104; i++) { wire[i] = arbitrary(); }
  assert(decode_replace_order(&got, wire, 0) == 104);
  assert(encode_replace_order(&got, again, 0) == 104);
  for (size_t i = 0; i < 104; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order: 14 bytes -------------------------------------------------- */

/* Client-generated cancel order request. */
typedef struct {
  uint8_t order_token[14];  /* bytes 0 to 13 */
} CancelOrder;

/* any Cancel Order at all: every byte one the checker chooses */
static void any_cancel_order(CancelOrder *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
}

/* Cancel Order to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order(const CancelOrder *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }

  return at;
}

/* Cancel Order off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order(CancelOrder *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order is what was written, byte for byte */
static void equal_cancel_order(const CancelOrder *read, const CancelOrder *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
}

/* Cancel Order: written and read back, then read and written back */
static void check_cancel_order(void) {
  CancelOrder sent;
  CancelOrder got;
  uint8_t wire[14];
  uint8_t again[14];

  any_cancel_order(&sent);
  assert(encode_cancel_order(&sent, wire, 0) == 14);
  assert(decode_cancel_order(&got, wire, 0) == 14);
  equal_cancel_order(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order(&got, wire, 0) == 14);
  assert(encode_cancel_order(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel By Order Id: 13 bytes -------------------------------------------- */

/* Client-generated request to cancel an order by system-assigned order ID. */
typedef struct {
  uint8_t order_book_id[4];  /* bytes 0 to 3 */
  uint8_t side;              /* byte 4 */
  uint8_t order_id[8];       /* bytes 5 to 12 */
} CancelByOrderId;

/* any Cancel By Order Id at all: every byte one the checker chooses */
static void any_cancel_by_order_id(CancelByOrderId *record) {
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Cancel By Order Id to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_cancel_by_order_id(const CancelByOrderId *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Cancel By Order Id off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_cancel_by_order_id(CancelByOrderId *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel By Order Id is what was written, byte for byte */
static void equal_cancel_by_order_id(const CancelByOrderId *read, const CancelByOrderId *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Cancel By Order Id: written and read back, then read and written back */
static void check_cancel_by_order_id(void) {
  CancelByOrderId sent;
  CancelByOrderId got;
  uint8_t wire[13];
  uint8_t again[13];

  any_cancel_by_order_id(&sent);
  assert(encode_cancel_by_order_id(&sent, wire, 0) == 13);
  assert(decode_cancel_by_order_id(&got, wire, 0) == 13);
  equal_cancel_by_order_id(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_by_order_id(&got, wire, 0) == 13);
  assert(encode_cancel_by_order_id(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel: 35 bytes --------------------------------------------------- */

/* Client-generated request to cancel multiple orders. */
typedef struct {
  uint8_t order_token[14];     /* bytes 0 to 13 */
  uint8_t underlying_id[4];    /* bytes 14 to 17 */
  uint8_t scope;               /* byte 18 */
  uint8_t client_account[16];  /* bytes 19 to 34 */
} MassCancel;

/* any Mass Cancel at all: every byte one the checker chooses */
static void any_mass_cancel(MassCancel *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = arbitrary(); }
  record->scope = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->client_account[i] = arbitrary(); }
}

/* Mass Cancel to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel(const MassCancel *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id[i]; }
  wire[at++] = record->scope;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_account[i]; }

  return at;
}

/* Mass Cancel off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel(MassCancel *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = wire[at++]; }
  record->scope = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->client_account[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel is what was written, byte for byte */
static void equal_mass_cancel(const MassCancel *read, const MassCancel *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id[i] == written->underlying_id[i]); }
  assert(read->scope == written->scope);
  for (size_t i = 0; i < 16; i++) { assert(read->client_account[i] == written->client_account[i]); }
}

/* Mass Cancel: written and read back, then read and written back */
static void check_mass_cancel(void) {
  MassCancel sent;
  MassCancel got;
  uint8_t wire[35];
  uint8_t again[35];

  any_mass_cancel(&sent);
  assert(encode_mass_cancel(&sent, wire, 0) == 35);
  assert(decode_mass_cancel(&got, wire, 0) == 35);
  equal_mass_cancel(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel(&got, wire, 0) == 35);
  assert(encode_mass_cancel(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_client_packet_header();
  check_login_request_packet();
  check_enter_order();
  check_enter_mm_order();
  check_replace_order();
  check_cancel_order();
  check_cancel_by_order_id();
  check_mass_cancel();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
