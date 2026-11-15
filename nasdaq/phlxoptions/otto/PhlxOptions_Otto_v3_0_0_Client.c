// nasdaq/phlxoptions/otto/PhlxOptions_Otto_v3_0_0_Client.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Ouch to Trade Options
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
 *   - a run counted by a field
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

/* ---- New Order Short Form Message: 49 bytes ---------------------------------- */

/* Short format of the New Order request is a compact message (50 bytes) with limited flexibility: simple and multi-leg instruments, quantity up to 65535, auction responses, default clearing configuration for the Firm. Acknowledged by Order Accepted (Short Form). */
typedef struct {
  uint8_t firm_id[4];               /* bytes 0 to 3 */
  uint8_t instrument_id[4];         /* bytes 4 to 7 */
  uint8_t cl_ord_id[16];            /* bytes 8 to 23 */
  uint8_t alo_inst;                 /* byte 24 */
  uint8_t iso;                      /* byte 25 */
  uint8_t side;                     /* byte 26 */
  uint8_t order_type;               /* byte 27 */
  uint8_t price[8];                 /* bytes 28 to 35 */
  uint8_t quantity_short[2];        /* bytes 36 to 37 */
  uint8_t tif;                      /* byte 38 */
  uint8_t capacity;                 /* byte 39 */
  uint8_t auction_type;             /* byte 40 */
  uint8_t auction_id[4];            /* bytes 41 to 44 */
  uint8_t price_protection;         /* byte 45 */
  uint8_t position_effect_mask[2];  /* bytes 46 to 47 */
  uint8_t stock_capacity;           /* byte 48 */
} NewOrderShortFormMessage;

/* any New Order Short Form Message at all: every byte one the checker chooses */
static void any_new_order_short_form_message(NewOrderShortFormMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->alo_inst = arbitrary();
  record->iso = arbitrary();
  record->side = arbitrary();
  record->order_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = arbitrary(); }
  record->tif = arbitrary();
  record->capacity = arbitrary();
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  record->price_protection = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->position_effect_mask[i] = arbitrary(); }
  record->stock_capacity = arbitrary();
}

/* New Order Short Form Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_new_order_short_form_message(const NewOrderShortFormMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->alo_inst;
  wire[at++] = record->iso;
  wire[at++] = record->side;
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity_short[i]; }
  wire[at++] = record->tif;
  wire[at++] = record->capacity;
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  wire[at++] = record->price_protection;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->position_effect_mask[i]; }
  wire[at++] = record->stock_capacity;

  return at;
}

/* New Order Short Form Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_new_order_short_form_message(NewOrderShortFormMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->alo_inst = wire[at++];
  record->iso = wire[at++];
  record->side = wire[at++];
  record->order_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = wire[at++]; }
  record->tif = wire[at++];
  record->capacity = wire[at++];
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  record->price_protection = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->position_effect_mask[i] = wire[at++]; }
  record->stock_capacity = wire[at++];

  return at;
}

/* what was read of New Order Short Form Message is what was written, byte for byte */
static void equal_new_order_short_form_message(const NewOrderShortFormMessage *read, const NewOrderShortFormMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->alo_inst == written->alo_inst);
  assert(read->iso == written->iso);
  assert(read->side == written->side);
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
  assert(read->tif == written->tif);
  assert(read->capacity == written->capacity);
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  assert(read->price_protection == written->price_protection);
  for (size_t i = 0; i < 2; i++) { assert(read->position_effect_mask[i] == written->position_effect_mask[i]); }
  assert(read->stock_capacity == written->stock_capacity);
}

/* New Order Short Form Message: written and read back, then read and written back */
static void check_new_order_short_form_message(void) {
  NewOrderShortFormMessage sent;
  NewOrderShortFormMessage got;
  uint8_t wire[49];
  uint8_t again[49];

  any_new_order_short_form_message(&sent);
  assert(encode_new_order_short_form_message(&sent, wire, 0) == 49);
  assert(decode_new_order_short_form_message(&got, wire, 0) == 49);
  equal_new_order_short_form_message(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_short_form_message(&got, wire, 0) == 49);
  assert(encode_new_order_short_form_message(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replace Order Message: 61 bytes ----------------------------------------- */

/* Replace Order message is used to modify an existing order for both simple and complex instruments. It can also be used to alter price of the contra side of Cross Orders. The order to be replaced is identified by OrigClOrdId. */
typedef struct {
  uint8_t firm_id[4];          /* bytes 0 to 3 */
  uint8_t orig_cl_ord_id[16];  /* bytes 4 to 19 */
  uint8_t cl_ord_id[16];       /* bytes 20 to 35 */
  uint8_t quantity[4];         /* bytes 36 to 39 */
  uint8_t order_type;          /* byte 40 */
  uint8_t price[8];            /* bytes 41 to 48 */
  uint8_t tif;                 /* byte 49 */
  uint8_t cust_acct[10];       /* bytes 50 to 59 */
  uint8_t price_protection;    /* byte 60 */
} ReplaceOrderMessage;

/* any Replace Order Message at all: every byte one the checker chooses */
static void any_replace_order_message(ReplaceOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->order_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->tif = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->cust_acct[i] = arbitrary(); }
  record->price_protection = arbitrary();
}

/* Replace Order Message to the wire: 61 bytes from at, returning where the next byte goes */
static size_t encode_replace_order_message(const ReplaceOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->tif;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cust_acct[i]; }
  wire[at++] = record->price_protection;

  return at;
}

/* Replace Order Message off the wire: 61 bytes from at, returning where the next byte lies */
static size_t decode_replace_order_message(ReplaceOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->order_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->tif = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->cust_acct[i] = wire[at++]; }
  record->price_protection = wire[at++];

  return at;
}

/* what was read of Replace Order Message is what was written, byte for byte */
static void equal_replace_order_message(const ReplaceOrderMessage *read, const ReplaceOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->tif == written->tif);
  for (size_t i = 0; i < 10; i++) { assert(read->cust_acct[i] == written->cust_acct[i]); }
  assert(read->price_protection == written->price_protection);
}

/* Replace Order Message: written and read back, then read and written back */
static void check_replace_order_message(void) {
  ReplaceOrderMessage sent;
  ReplaceOrderMessage got;
  uint8_t wire[61];
  uint8_t again[61];

  any_replace_order_message(&sent);
  assert(encode_replace_order_message(&sent, wire, 0) == 61);
  assert(decode_replace_order_message(&got, wire, 0) == 61);
  equal_replace_order_message(&got, &sent);

  for (size_t i = 0; i < 61; i++) { wire[i] = arbitrary(); }
  assert(decode_replace_order_message(&got, wire, 0) == 61);
  assert(encode_replace_order_message(&got, again, 0) == 61);
  for (size_t i = 0; i < 61; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Message: 20 bytes ------------------------------------------ */

/* Cancel Order by Client ID. Deletes a single simple order, a single complex order, or a Cross Order (terminating an ongoing auction). The order to be deleted is identified by the ClOrdId field. */
typedef struct {
  uint8_t firm_id[4];     /* bytes 0 to 3 */
  uint8_t cl_ord_id[16];  /* bytes 4 to 19 */
} CancelOrderMessage;

/* any Cancel Order Message at all: every byte one the checker chooses */
static void any_cancel_order_message(CancelOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = arbitrary(); }
}

/* Cancel Order Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_message(const CancelOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_ord_id[i]; }

  return at;
}

/* Cancel Order Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_message(CancelOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_ord_id[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Message is what was written, byte for byte */
static void equal_cancel_order_message(const CancelOrderMessage *read, const CancelOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
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

/* ---- Mass Cancel Message: 41 bytes ------------------------------------------- */

/* This message is used to mass-delete multiple open orders based on the specified Scope. The sequence of Order Canceled messages is terminated with a single Mass Cancel Response. */
typedef struct {
  uint8_t firm_id[4];             /* bytes 0 to 3 */
  uint8_t cl_request_id[16];      /* bytes 4 to 19 */
  uint8_t instrument_type;        /* byte 20 */
  uint8_t scope;                  /* byte 21 */
  uint8_t product_id[2];          /* bytes 22 to 23 */
  uint8_t instrument_id[4];       /* bytes 24 to 27 */
  uint8_t underlying_symbol[13];  /* bytes 28 to 40 */
} MassCancelMessage;

/* any Mass Cancel Message at all: every byte one the checker chooses */
static void any_mass_cancel_message(MassCancelMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_request_id[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  record->scope = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = arbitrary(); }
}

/* Mass Cancel Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_message(const MassCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_request_id[i]; }
  wire[at++] = record->instrument_type;
  wire[at++] = record->scope;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->underlying_symbol[i]; }

  return at;
}

/* Mass Cancel Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_message(MassCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_request_id[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  record->scope = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->underlying_symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Message is what was written, byte for byte */
static void equal_mass_cancel_message(const MassCancelMessage *read, const MassCancelMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_request_id[i] == written->cl_request_id[i]); }
  assert(read->instrument_type == written->instrument_type);
  assert(read->scope == written->scope);
  for (size_t i = 0; i < 2; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
}

/* Mass Cancel Message: written and read back, then read and written back */
static void check_mass_cancel_message(void) {
  MassCancelMessage sent;
  MassCancelMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_mass_cancel_message(&sent);
  assert(encode_mass_cancel_message(&sent, wire, 0) == 41);
  assert(decode_mass_cancel_message(&got, wire, 0) == 41);
  equal_mass_cancel_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_message(&got, wire, 0) == 41);
  assert(encode_mass_cancel_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Member Kill Switch Request Message: 25 bytes ---------------------------- */

/* The Member Kill Switch Request is used to block ability to enter new orders, alter existing orders, delete orders, and create complex instruments. Scope of the Kill Switch Request is one firm per request. Answered by Member Kill Switch Notification or Reject. */
typedef struct {
  uint8_t firm_id[4];         /* bytes 0 to 3 */
  uint8_t cl_request_id[16];  /* bytes 4 to 19 */
  uint8_t target_firm_id[4];  /* bytes 20 to 23 */
  uint8_t kill_action;        /* byte 24 */
} MemberKillSwitchRequestMessage;

/* any Member Kill Switch Request Message at all: every byte one the checker chooses */
static void any_member_kill_switch_request_message(MemberKillSwitchRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->target_firm_id[i] = arbitrary(); }
  record->kill_action = arbitrary();
}

/* Member Kill Switch Request Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_member_kill_switch_request_message(const MemberKillSwitchRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->target_firm_id[i]; }
  wire[at++] = record->kill_action;

  return at;
}

/* Member Kill Switch Request Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_member_kill_switch_request_message(MemberKillSwitchRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->target_firm_id[i] = wire[at++]; }
  record->kill_action = wire[at++];

  return at;
}

/* what was read of Member Kill Switch Request Message is what was written, byte for byte */
static void equal_member_kill_switch_request_message(const MemberKillSwitchRequestMessage *read, const MemberKillSwitchRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_request_id[i] == written->cl_request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->target_firm_id[i] == written->target_firm_id[i]); }
  assert(read->kill_action == written->kill_action);
}

/* Member Kill Switch Request Message: written and read back, then read and written back */
static void check_member_kill_switch_request_message(void) {
  MemberKillSwitchRequestMessage sent;
  MemberKillSwitchRequestMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_member_kill_switch_request_message(&sent);
  assert(encode_member_kill_switch_request_message(&sent, wire, 0) == 25);
  assert(decode_member_kill_switch_request_message(&got, wire, 0) == 25);
  equal_member_kill_switch_request_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_member_kill_switch_request_message(&got, wire, 0) == 25);
  assert(encode_member_kill_switch_request_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Subscription Request Message: 36 bytes ---------------------------------- */

/* Subscription Request message allows client to modify the set of optional notification types it receives on the OTTO connection for the current session. Supported on PHLX, ISE, GEMX and MRX. Answered by Subscription Response or Reject. */
typedef struct {
  uint8_t firm_id[4];         /* bytes 0 to 3 */
  uint8_t cl_request_id[16];  /* bytes 4 to 19 */
  uint8_t subscription[16];   /* bytes 20 to 35 */
} SubscriptionRequestMessage;

/* any Subscription Request Message at all: every byte one the checker chooses */
static void any_subscription_request_message(SubscriptionRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->cl_request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->subscription[i] = arbitrary(); }
}

/* Subscription Request Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_subscription_request_message(const SubscriptionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cl_request_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->subscription[i]; }

  return at;
}

/* Subscription Request Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_subscription_request_message(SubscriptionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->cl_request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->subscription[i] = wire[at++]; }

  return at;
}

/* what was read of Subscription Request Message is what was written, byte for byte */
static void equal_subscription_request_message(const SubscriptionRequestMessage *read, const SubscriptionRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->cl_request_id[i] == written->cl_request_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->subscription[i] == written->subscription[i]); }
}

/* Subscription Request Message: written and read back, then read and written back */
static void check_subscription_request_message(void) {
  SubscriptionRequestMessage sent;
  SubscriptionRequestMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_subscription_request_message(&sent);
  assert(encode_subscription_request_message(&sent, wire, 0) == 36);
  assert(decode_subscription_request_message(&got, wire, 0) == 36);
  equal_subscription_request_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_subscription_request_message(&got, wire, 0) == 36);
  assert(encode_subscription_request_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_client_packet_header();
  check_login_request_packet();
  check_new_order_short_form_message();
  check_replace_order_message();
  check_cancel_order_message();
  check_mass_cancel_message();
  check_member_kill_switch_request_message();
  check_subscription_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
