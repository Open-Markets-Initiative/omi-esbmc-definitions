// asx/asxsecurities/trade/AsxSecurities_Trade_Ouch_v2_0_Client.c
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

/* ---- Enter Order Message: 156 bytes ------------------------------------------ */

/* The Enter Order message is used to enter a new order into the market. The response to a successful Enter Order message is an Order Accepted message. If the order is rejected, the Order Rejected message will be returned. */
typedef struct {
  uint8_t order_token[14];                 /* bytes 0 to 13 */
  uint8_t order_book_id[4];                /* bytes 14 to 17 */
  uint8_t side;                            /* byte 18 */
  uint8_t quantity[8];                     /* bytes 19 to 26 */
  uint8_t price[4];                        /* bytes 27 to 30 */
  uint8_t time_in_force;                   /* byte 31 */
  uint8_t open_close;                      /* byte 32 */
  uint8_t client_account[10];              /* bytes 33 to 42 */
  uint8_t customer_info[15];               /* bytes 43 to 57 */
  uint8_t exchange_info[32];               /* bytes 58 to 89 */
  uint8_t clearing_participant;            /* byte 90 */
  uint8_t crossing_key[4];                 /* bytes 91 to 94 */
  uint8_t capacity_of_participant;         /* byte 95 */
  uint8_t directed_wholesale;              /* byte 96 */
  uint8_t execution_venue[4];              /* bytes 97 to 100 */
  uint8_t intermediary_id[10];             /* bytes 101 to 110 */
  uint8_t order_origin[20];                /* bytes 111 to 130 */
  uint8_t filler[8];                       /* bytes 131 to 138 */
  uint8_t ouch_order_type;                 /* byte 139 */
  uint8_t short_sell_quantity[8];          /* bytes 140 to 147 */
  uint8_t minimum_acceptable_quantity[8];  /* bytes 148 to 155 */
} EnterOrderMessage;

/* any Enter Order Message at all: every byte one the checker chooses */
static void any_enter_order_message(EnterOrderMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->open_close = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->client_account[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->exchange_info[i] = arbitrary(); }
  record->clearing_participant = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->crossing_key[i] = arbitrary(); }
  record->capacity_of_participant = arbitrary();
  record->directed_wholesale = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->intermediary_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->order_origin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->filler[i] = arbitrary(); }
  record->ouch_order_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->short_sell_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_acceptable_quantity[i] = arbitrary(); }
}

/* Enter Order Message to the wire: 156 bytes from at, returning where the next byte goes */
static size_t encode_enter_order_message(const EnterOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->client_account[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->customer_info[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->exchange_info[i]; }
  wire[at++] = record->clearing_participant;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->crossing_key[i]; }
  wire[at++] = record->capacity_of_participant;
  wire[at++] = record->directed_wholesale;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_venue[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->intermediary_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->order_origin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->filler[i]; }
  wire[at++] = record->ouch_order_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->short_sell_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_acceptable_quantity[i]; }

  return at;
}

/* Enter Order Message off the wire: 156 bytes from at, returning where the next byte lies */
static size_t decode_enter_order_message(EnterOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->open_close = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->client_account[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->exchange_info[i] = wire[at++]; }
  record->clearing_participant = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->crossing_key[i] = wire[at++]; }
  record->capacity_of_participant = wire[at++];
  record->directed_wholesale = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->intermediary_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->order_origin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->filler[i] = wire[at++]; }
  record->ouch_order_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->short_sell_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_acceptable_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Enter Order Message is what was written, byte for byte */
static void equal_enter_order_message(const EnterOrderMessage *read, const EnterOrderMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 10; i++) { assert(read->client_account[i] == written->client_account[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->customer_info[i] == written->customer_info[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->exchange_info[i] == written->exchange_info[i]); }
  assert(read->clearing_participant == written->clearing_participant);
  for (size_t i = 0; i < 4; i++) { assert(read->crossing_key[i] == written->crossing_key[i]); }
  assert(read->capacity_of_participant == written->capacity_of_participant);
  assert(read->directed_wholesale == written->directed_wholesale);
  for (size_t i = 0; i < 4; i++) { assert(read->execution_venue[i] == written->execution_venue[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->intermediary_id[i] == written->intermediary_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->order_origin[i] == written->order_origin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->filler[i] == written->filler[i]); }
  assert(read->ouch_order_type == written->ouch_order_type);
  for (size_t i = 0; i < 8; i++) { assert(read->short_sell_quantity[i] == written->short_sell_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_acceptable_quantity[i] == written->minimum_acceptable_quantity[i]); }
}

/* Enter Order Message: written and read back, then read and written back */
static void check_enter_order_message(void) {
  EnterOrderMessage sent;
  EnterOrderMessage got;
  uint8_t wire[156];
  uint8_t again[156];

  any_enter_order_message(&sent);
  assert(encode_enter_order_message(&sent, wire, 0) == 156);
  assert(decode_enter_order_message(&got, wire, 0) == 156);
  equal_enter_order_message(&got, &sent);

  for (size_t i = 0; i < 156; i++) { wire[i] = arbitrary(); }
  assert(decode_enter_order_message(&got, wire, 0) == 156);
  assert(encode_enter_order_message(&got, again, 0) == 156);
  for (size_t i = 0; i < 156; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replace Order Message: 158 bytes ---------------------------------------- */

/* The Replace Order message is used to amend an existing order that was entered with ASX Trade OUCH. The response to a successful Replace Order message is an Order Replaced message. If the amendment is rejected, the Order Rejected message will be returned. */
typedef struct {
  uint8_t existing_order_token[14];        /* bytes 0 to 13 */
  uint8_t replacement_order_token[14];     /* bytes 14 to 27 */
  uint8_t quantity[8];                     /* bytes 28 to 35 */
  uint8_t price[4];                        /* bytes 36 to 39 */
  uint8_t open_close;                      /* byte 40 */
  uint8_t client_account[10];              /* bytes 41 to 50 */
  uint8_t customer_info[15];               /* bytes 51 to 65 */
  uint8_t exchange_info[32];               /* bytes 66 to 97 */
  uint8_t capacity_of_participant;         /* byte 98 */
  uint8_t directed_wholesale;              /* byte 99 */
  uint8_t execution_venue[4];              /* bytes 100 to 103 */
  uint8_t intermediary_id[10];             /* bytes 104 to 113 */
  uint8_t order_origin[20];                /* bytes 114 to 133 */
  uint8_t filler[8];                       /* bytes 134 to 141 */
  uint8_t short_sell_quantity[8];          /* bytes 142 to 149 */
  uint8_t minimum_acceptable_quantity[8];  /* bytes 150 to 157 */
} ReplaceOrderMessage;

/* any Replace Order Message at all: every byte one the checker chooses */
static void any_replace_order_message(ReplaceOrderMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->existing_order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->replacement_order_token[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->open_close = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->client_account[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->exchange_info[i] = arbitrary(); }
  record->capacity_of_participant = arbitrary();
  record->directed_wholesale = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->intermediary_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->order_origin[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->filler[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->short_sell_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_acceptable_quantity[i] = arbitrary(); }
}

/* Replace Order Message to the wire: 158 bytes from at, returning where the next byte goes */
static size_t encode_replace_order_message(const ReplaceOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->existing_order_token[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->replacement_order_token[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->client_account[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->customer_info[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->exchange_info[i]; }
  wire[at++] = record->capacity_of_participant;
  wire[at++] = record->directed_wholesale;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_venue[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->intermediary_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->order_origin[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->filler[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->short_sell_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_acceptable_quantity[i]; }

  return at;
}

/* Replace Order Message off the wire: 158 bytes from at, returning where the next byte lies */
static size_t decode_replace_order_message(ReplaceOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->existing_order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->replacement_order_token[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->open_close = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->client_account[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->customer_info[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->exchange_info[i] = wire[at++]; }
  record->capacity_of_participant = wire[at++];
  record->directed_wholesale = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->execution_venue[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->intermediary_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->order_origin[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->filler[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->short_sell_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_acceptable_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Replace Order Message is what was written, byte for byte */
static void equal_replace_order_message(const ReplaceOrderMessage *read, const ReplaceOrderMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->existing_order_token[i] == written->existing_order_token[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->replacement_order_token[i] == written->replacement_order_token[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 10; i++) { assert(read->client_account[i] == written->client_account[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->customer_info[i] == written->customer_info[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->exchange_info[i] == written->exchange_info[i]); }
  assert(read->capacity_of_participant == written->capacity_of_participant);
  assert(read->directed_wholesale == written->directed_wholesale);
  for (size_t i = 0; i < 4; i++) { assert(read->execution_venue[i] == written->execution_venue[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->intermediary_id[i] == written->intermediary_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->order_origin[i] == written->order_origin[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->filler[i] == written->filler[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->short_sell_quantity[i] == written->short_sell_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_acceptable_quantity[i] == written->minimum_acceptable_quantity[i]); }
}

/* Replace Order Message: written and read back, then read and written back */
static void check_replace_order_message(void) {
  ReplaceOrderMessage sent;
  ReplaceOrderMessage got;
  uint8_t wire[158];
  uint8_t again[158];

  any_replace_order_message(&sent);
  assert(encode_replace_order_message(&sent, wire, 0) == 158);
  assert(decode_replace_order_message(&got, wire, 0) == 158);
  equal_replace_order_message(&got, &sent);

  for (size_t i = 0; i < 158; i++) { wire[i] = arbitrary(); }
  assert(decode_replace_order_message(&got, wire, 0) == 158);
  assert(encode_replace_order_message(&got, again, 0) == 158);
  for (size_t i = 0; i < 158; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Message: 14 bytes ------------------------------------------ */

/* The Cancel Order message is used to cancel an existing order that was entered with ASX Trade OUCH, using the order token to identify the order being cancelled. The response to a successful Cancel Order message is an Order Cancelled message. If the cancellation is rejected, the Order Rejected message will be returned. */
typedef struct {
  uint8_t order_token[14];  /* bytes 0 to 13 */
} CancelOrderMessage;

/* any Cancel Order Message at all: every byte one the checker chooses */
static void any_cancel_order_message(CancelOrderMessage *record) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = arbitrary(); }
}

/* Cancel Order Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_message(const CancelOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->order_token[i]; }

  return at;
}

/* Cancel Order Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_message(CancelOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 14; i++) { record->order_token[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Message is what was written, byte for byte */
static void equal_cancel_order_message(const CancelOrderMessage *read, const CancelOrderMessage *written) {
  for (size_t i = 0; i < 14; i++) { assert(read->order_token[i] == written->order_token[i]); }
}

/* Cancel Order Message: written and read back, then read and written back */
static void check_cancel_order_message(void) {
  CancelOrderMessage sent;
  CancelOrderMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_cancel_order_message(&sent);
  assert(encode_cancel_order_message(&sent, wire, 0) == 14);
  assert(decode_cancel_order_message(&got, wire, 0) == 14);
  equal_cancel_order_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_message(&got, wire, 0) == 14);
  assert(encode_cancel_order_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel By Order Id Message: 13 bytes ------------------------------------ */

/* The Cancel By Order ID message is used to cancel an existing own customer order that was entered with ASX Trade OUCH or another protocol (for example the OMNet API), using the order ID to identify the order being cancelled. The response to a successful Cancel By Order ID message is an Order Cancelled message. If the cancellation is rejected, the Order Rejected message will be returned. */
typedef struct {
  uint8_t order_book_id[4];  /* bytes 0 to 3 */
  uint8_t side;              /* byte 4 */
  uint8_t order_id[8];       /* bytes 5 to 12 */
} CancelByOrderIdMessage;

/* any Cancel By Order Id Message at all: every byte one the checker chooses */
static void any_cancel_by_order_id_message(CancelByOrderIdMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Cancel By Order Id Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_cancel_by_order_id_message(const CancelByOrderIdMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Cancel By Order Id Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_cancel_by_order_id_message(CancelByOrderIdMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel By Order Id Message is what was written, byte for byte */
static void equal_cancel_by_order_id_message(const CancelByOrderIdMessage *read, const CancelByOrderIdMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Cancel By Order Id Message: written and read back, then read and written back */
static void check_cancel_by_order_id_message(void) {
  CancelByOrderIdMessage sent;
  CancelByOrderIdMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_cancel_by_order_id_message(&sent);
  assert(encode_cancel_by_order_id_message(&sent, wire, 0) == 13);
  assert(decode_cancel_by_order_id_message(&got, wire, 0) == 13);
  equal_cancel_by_order_id_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_by_order_id_message(&got, wire, 0) == 13);
  assert(encode_cancel_by_order_id_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_client_packet_header();
  check_login_request_packet();
  check_enter_order_message();
  check_replace_order_message();
  check_cancel_order_message();
  check_cancel_by_order_id_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
