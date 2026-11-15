// nasdaq/nordicequities/orderentry/NordicEquities_OrderEntry_v5_02_6_Client.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Nordic Ouch 5 Order Entry
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
 *   - a field read in bits
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

/* ---- Clearing Account: 12 bytes ---------------------------------------------- */

/* Clearing Account */
typedef struct {
  uint8_t clearing_account_value[12];  /* bytes 0 to 11 */
} ClearingAccount;

/* any Clearing Account at all: every byte one the checker chooses */
static void any_clearing_account(ClearingAccount *record) {
  for (size_t i = 0; i < 12; i++) { record->clearing_account_value[i] = arbitrary(); }
}

/* Clearing Account to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_clearing_account(const ClearingAccount *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->clearing_account_value[i]; }

  return at;
}

/* Clearing Account off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_clearing_account(ClearingAccount *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->clearing_account_value[i] = wire[at++]; }

  return at;
}

/* what was read of Clearing Account is what was written, byte for byte */
static void equal_clearing_account(const ClearingAccount *read, const ClearingAccount *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->clearing_account_value[i] == written->clearing_account_value[i]); }
}

/* Clearing Account: written and read back, then read and written back */
static void check_clearing_account(void) {
  ClearingAccount sent;
  ClearingAccount got;
  uint8_t wire[12];
  uint8_t again[12];

  any_clearing_account(&sent);
  assert(encode_clearing_account(&sent, wire, 0) == 12);
  assert(decode_clearing_account(&got, wire, 0) == 12);
  equal_clearing_account(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_clearing_account(&got, wire, 0) == 12);
  assert(encode_clearing_account(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clearing Account Type: 1 byte ------------------------------------------- */

/* Clearing Account Type */
typedef struct {
  uint8_t clearing_account_type_value;  /* byte 0 */
} ClearingAccountType;

/* any Clearing Account Type at all: every byte one the checker chooses */
static void any_clearing_account_type(ClearingAccountType *record) {
  record->clearing_account_type_value = arbitrary();
}

/* Clearing Account Type to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_clearing_account_type(const ClearingAccountType *record, uint8_t *wire, size_t at) {
  wire[at++] = record->clearing_account_type_value;

  return at;
}

/* Clearing Account Type off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_clearing_account_type(ClearingAccountType *record, const uint8_t *wire, size_t at) {
  record->clearing_account_type_value = wire[at++];

  return at;
}

/* what was read of Clearing Account Type is what was written, byte for byte */
static void equal_clearing_account_type(const ClearingAccountType *read, const ClearingAccountType *written) {
  assert(read->clearing_account_type_value == written->clearing_account_type_value);
}

/* Clearing Account Type: written and read back, then read and written back */
static void check_clearing_account_type(void) {
  ClearingAccountType sent;
  ClearingAccountType got;
  uint8_t wire[1];
  uint8_t again[1];

  any_clearing_account_type(&sent);
  assert(encode_clearing_account_type(&sent, wire, 0) == 1);
  assert(decode_clearing_account_type(&got, wire, 0) == 1);
  equal_clearing_account_type(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_clearing_account_type(&got, wire, 0) == 1);
  assert(encode_clearing_account_type(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clearing Firm: 4 bytes -------------------------------------------------- */

/* Clearing Firm */
typedef struct {
  uint8_t clearing_firm_value[4];  /* bytes 0 to 3 */
} ClearingFirm;

/* any Clearing Firm at all: every byte one the checker chooses */
static void any_clearing_firm(ClearingFirm *record) {
  for (size_t i = 0; i < 4; i++) { record->clearing_firm_value[i] = arbitrary(); }
}

/* Clearing Firm to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_clearing_firm(const ClearingFirm *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm_value[i]; }

  return at;
}

/* Clearing Firm off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_clearing_firm(ClearingFirm *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->clearing_firm_value[i] = wire[at++]; }

  return at;
}

/* what was read of Clearing Firm is what was written, byte for byte */
static void equal_clearing_firm(const ClearingFirm *read, const ClearingFirm *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm_value[i] == written->clearing_firm_value[i]); }
}

/* Clearing Firm: written and read back, then read and written back */
static void check_clearing_firm(void) {
  ClearingFirm sent;
  ClearingFirm got;
  uint8_t wire[4];
  uint8_t again[4];

  any_clearing_firm(&sent);
  assert(encode_clearing_firm(&sent, wire, 0) == 4);
  assert(decode_clearing_firm(&got, wire, 0) == 4);
  equal_clearing_firm(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_clearing_firm(&got, wire, 0) == 4);
  assert(encode_clearing_firm(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Client Reference: 15 bytes ---------------------------------------------- */

/* Client Reference */
typedef struct {
  uint8_t client_reference_value[15];  /* bytes 0 to 14 */
} ClientReference;

/* any Client Reference at all: every byte one the checker chooses */
static void any_client_reference(ClientReference *record) {
  for (size_t i = 0; i < 15; i++) { record->client_reference_value[i] = arbitrary(); }
}

/* Client Reference to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_client_reference(const ClientReference *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_reference_value[i]; }

  return at;
}

/* Client Reference off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_client_reference(ClientReference *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->client_reference_value[i] = wire[at++]; }

  return at;
}

/* what was read of Client Reference is what was written, byte for byte */
static void equal_client_reference(const ClientReference *read, const ClientReference *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->client_reference_value[i] == written->client_reference_value[i]); }
}

/* Client Reference: written and read back, then read and written back */
static void check_client_reference(void) {
  ClientReference sent;
  ClientReference got;
  uint8_t wire[15];
  uint8_t again[15];

  any_client_reference(&sent);
  assert(encode_client_reference(&sent, wire, 0) == 15);
  assert(decode_client_reference(&got, wire, 0) == 15);
  equal_client_reference(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_client_reference(&got, wire, 0) == 15);
  assert(encode_client_reference(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cross Type: 1 byte ------------------------------------------------------ */

/* Cross Type */
typedef struct {
  uint8_t cross_type_value;  /* byte 0 */
} CrossType;

/* any Cross Type at all: every byte one the checker chooses */
static void any_cross_type(CrossType *record) {
  record->cross_type_value = arbitrary();
}

/* Cross Type to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_cross_type(const CrossType *record, uint8_t *wire, size_t at) {
  wire[at++] = record->cross_type_value;

  return at;
}

/* Cross Type off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_cross_type(CrossType *record, const uint8_t *wire, size_t at) {
  record->cross_type_value = wire[at++];

  return at;
}

/* what was read of Cross Type is what was written, byte for byte */
static void equal_cross_type(const CrossType *read, const CrossType *written) {
  assert(read->cross_type_value == written->cross_type_value);
}

/* Cross Type: written and read back, then read and written back */
static void check_cross_type(void) {
  CrossType sent;
  CrossType got;
  uint8_t wire[1];
  uint8_t again[1];

  any_cross_type(&sent);
  assert(encode_cross_type(&sent, wire, 0) == 1);
  assert(decode_cross_type(&got, wire, 0) == 1);
  equal_cross_type(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_cross_type(&got, wire, 0) == 1);
  assert(encode_cross_type(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Dea Indicator: 1 byte --------------------------------------------------- */

/* DEA Indicator */
typedef struct {
  uint8_t dea_indicator_value;  /* byte 0 */
} DeaIndicator;

/* any Dea Indicator at all: every byte one the checker chooses */
static void any_dea_indicator(DeaIndicator *record) {
  record->dea_indicator_value = arbitrary();
}

/* Dea Indicator to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_dea_indicator(const DeaIndicator *record, uint8_t *wire, size_t at) {
  wire[at++] = record->dea_indicator_value;

  return at;
}

/* Dea Indicator off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_dea_indicator(DeaIndicator *record, const uint8_t *wire, size_t at) {
  record->dea_indicator_value = wire[at++];

  return at;
}

/* what was read of Dea Indicator is what was written, byte for byte */
static void equal_dea_indicator(const DeaIndicator *read, const DeaIndicator *written) {
  assert(read->dea_indicator_value == written->dea_indicator_value);
}

/* Dea Indicator: written and read back, then read and written back */
static void check_dea_indicator(void) {
  DeaIndicator sent;
  DeaIndicator got;
  uint8_t wire[1];
  uint8_t again[1];

  any_dea_indicator(&sent);
  assert(encode_dea_indicator(&sent, wire, 0) == 1);
  assert(decode_dea_indicator(&got, wire, 0) == 1);
  equal_dea_indicator(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_dea_indicator(&got, wire, 0) == 1);
  assert(encode_dea_indicator(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Display: 1 byte --------------------------------------------------------- */

/* Display */
typedef struct {
  uint8_t display_value;  /* byte 0 */
} Display;

/* any Display at all: every byte one the checker chooses */
static void any_display(Display *record) {
  record->display_value = arbitrary();
}

/* Display to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_display(const Display *record, uint8_t *wire, size_t at) {
  wire[at++] = record->display_value;

  return at;
}

/* Display off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_display(Display *record, const uint8_t *wire, size_t at) {
  record->display_value = wire[at++];

  return at;
}

/* what was read of Display is what was written, byte for byte */
static void equal_display(const Display *read, const Display *written) {
  assert(read->display_value == written->display_value);
}

/* Display: written and read back, then read and written back */
static void check_display(void) {
  Display sent;
  Display got;
  uint8_t wire[1];
  uint8_t again[1];

  any_display(&sent);
  assert(encode_display(&sent, wire, 0) == 1);
  assert(decode_display(&got, wire, 0) == 1);
  equal_display(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_display(&got, wire, 0) == 1);
  assert(encode_display(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Display Price: 4 bytes -------------------------------------------------- */

/* Display Price */
typedef struct {
  uint8_t display_price_value[4];  /* bytes 0 to 3 */
} DisplayPrice;

/* any Display Price at all: every byte one the checker chooses */
static void any_display_price(DisplayPrice *record) {
  for (size_t i = 0; i < 4; i++) { record->display_price_value[i] = arbitrary(); }
}

/* Display Price to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_display_price(const DisplayPrice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_price_value[i]; }

  return at;
}

/* Display Price off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_display_price(DisplayPrice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->display_price_value[i] = wire[at++]; }

  return at;
}

/* what was read of Display Price is what was written, byte for byte */
static void equal_display_price(const DisplayPrice *read, const DisplayPrice *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->display_price_value[i] == written->display_price_value[i]); }
}

/* Display Price: written and read back, then read and written back */
static void check_display_price(void) {
  DisplayPrice sent;
  DisplayPrice got;
  uint8_t wire[4];
  uint8_t again[4];

  any_display_price(&sent);
  assert(encode_display_price(&sent, wire, 0) == 4);
  assert(decode_display_price(&got, wire, 0) == 4);
  equal_display_price(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_display_price(&got, wire, 0) == 4);
  assert(encode_display_price(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Display Quantity: 4 bytes ----------------------------------------------- */

/* Display Quantity */
typedef struct {
  uint8_t display_quantity_value[4];  /* bytes 0 to 3 */
} DisplayQuantity;

/* any Display Quantity at all: every byte one the checker chooses */
static void any_display_quantity(DisplayQuantity *record) {
  for (size_t i = 0; i < 4; i++) { record->display_quantity_value[i] = arbitrary(); }
}

/* Display Quantity to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_display_quantity(const DisplayQuantity *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_quantity_value[i]; }

  return at;
}

/* Display Quantity off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_display_quantity(DisplayQuantity *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->display_quantity_value[i] = wire[at++]; }

  return at;
}

/* what was read of Display Quantity is what was written, byte for byte */
static void equal_display_quantity(const DisplayQuantity *read, const DisplayQuantity *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->display_quantity_value[i] == written->display_quantity_value[i]); }
}

/* Display Quantity: written and read back, then read and written back */
static void check_display_quantity(void) {
  DisplayQuantity sent;
  DisplayQuantity got;
  uint8_t wire[4];
  uint8_t again[4];

  any_display_quantity(&sent);
  assert(encode_display_quantity(&sent, wire, 0) == 4);
  assert(decode_display_quantity(&got, wire, 0) == 4);
  equal_display_quantity(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_display_quantity(&got, wire, 0) == 4);
  assert(encode_display_quantity(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Expire Time: 2 bytes ---------------------------------------------------- */

/* Expire Time */
typedef struct {
  uint8_t expire_time_value[2];  /* bytes 0 to 1 */
} ExpireTime;

/* any Expire Time at all: every byte one the checker chooses */
static void any_expire_time(ExpireTime *record) {
  for (size_t i = 0; i < 2; i++) { record->expire_time_value[i] = arbitrary(); }
}

/* Expire Time to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_expire_time(const ExpireTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expire_time_value[i]; }

  return at;
}

/* Expire Time off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_expire_time(ExpireTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->expire_time_value[i] = wire[at++]; }

  return at;
}

/* what was read of Expire Time is what was written, byte for byte */
static void equal_expire_time(const ExpireTime *read, const ExpireTime *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->expire_time_value[i] == written->expire_time_value[i]); }
}

/* Expire Time: written and read back, then read and written back */
static void check_expire_time(void) {
  ExpireTime sent;
  ExpireTime got;
  uint8_t wire[2];
  uint8_t again[2];

  any_expire_time(&sent);
  assert(encode_expire_time(&sent, wire, 0) == 2);
  assert(decode_expire_time(&got, wire, 0) == 2);
  equal_expire_time(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_expire_time(&got, wire, 0) == 2);
  assert(encode_expire_time(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Firm: 4 bytes ----------------------------------------------------------- */

/* Firm */
typedef struct {
  uint8_t firm_value[4];  /* bytes 0 to 3 */
} Firm;

/* any Firm at all: every byte one the checker chooses */
static void any_firm(Firm *record) {
  for (size_t i = 0; i < 4; i++) { record->firm_value[i] = arbitrary(); }
}

/* Firm to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_firm(const Firm *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_value[i]; }

  return at;
}

/* Firm off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_firm(Firm *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->firm_value[i] = wire[at++]; }

  return at;
}

/* what was read of Firm is what was written, byte for byte */
static void equal_firm(const Firm *read, const Firm *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->firm_value[i] == written->firm_value[i]); }
}

/* Firm: written and read back, then read and written back */
static void check_firm(void) {
  Firm sent;
  Firm got;
  uint8_t wire[4];
  uint8_t again[4];

  any_firm(&sent);
  assert(encode_firm(&sent, wire, 0) == 4);
  assert(decode_firm(&got, wire, 0) == 4);
  equal_firm(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_firm(&got, wire, 0) == 4);
  assert(encode_firm(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Liquidity Provision Indicator: 1 byte ----------------------------------- */

/* Liquidity Provision Indicator */
typedef struct {
  uint8_t liquidity_provision_indicator_value;  /* byte 0 */
} LiquidityProvisionIndicator;

/* any Liquidity Provision Indicator at all: every byte one the checker chooses */
static void any_liquidity_provision_indicator(LiquidityProvisionIndicator *record) {
  record->liquidity_provision_indicator_value = arbitrary();
}

/* Liquidity Provision Indicator to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_liquidity_provision_indicator(const LiquidityProvisionIndicator *record, uint8_t *wire, size_t at) {
  wire[at++] = record->liquidity_provision_indicator_value;

  return at;
}

/* Liquidity Provision Indicator off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_liquidity_provision_indicator(LiquidityProvisionIndicator *record, const uint8_t *wire, size_t at) {
  record->liquidity_provision_indicator_value = wire[at++];

  return at;
}

/* what was read of Liquidity Provision Indicator is what was written, byte for byte */
static void equal_liquidity_provision_indicator(const LiquidityProvisionIndicator *read, const LiquidityProvisionIndicator *written) {
  assert(read->liquidity_provision_indicator_value == written->liquidity_provision_indicator_value);
}

/* Liquidity Provision Indicator: written and read back, then read and written back */
static void check_liquidity_provision_indicator(void) {
  LiquidityProvisionIndicator sent;
  LiquidityProvisionIndicator got;
  uint8_t wire[1];
  uint8_t again[1];

  any_liquidity_provision_indicator(&sent);
  assert(encode_liquidity_provision_indicator(&sent, wire, 0) == 1);
  assert(decode_liquidity_provision_indicator(&got, wire, 0) == 1);
  equal_liquidity_provision_indicator(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_liquidity_provision_indicator(&got, wire, 0) == 1);
  assert(encode_liquidity_provision_indicator(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Max Floor: 4 bytes ------------------------------------------------------ */

/* Max Floor */
typedef struct {
  uint8_t max_floor_value[4];  /* bytes 0 to 3 */
} MaxFloor;

/* any Max Floor at all: every byte one the checker chooses */
static void any_max_floor(MaxFloor *record) {
  for (size_t i = 0; i < 4; i++) { record->max_floor_value[i] = arbitrary(); }
}

/* Max Floor to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_max_floor(const MaxFloor *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor_value[i]; }

  return at;
}

/* Max Floor off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_max_floor(MaxFloor *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->max_floor_value[i] = wire[at++]; }

  return at;
}

/* what was read of Max Floor is what was written, byte for byte */
static void equal_max_floor(const MaxFloor *read, const MaxFloor *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor_value[i] == written->max_floor_value[i]); }
}

/* Max Floor: written and read back, then read and written back */
static void check_max_floor(void) {
  MaxFloor sent;
  MaxFloor got;
  uint8_t wire[4];
  uint8_t again[4];

  any_max_floor(&sent);
  assert(encode_max_floor(&sent, wire, 0) == 4);
  assert(decode_max_floor(&got, wire, 0) == 4);
  equal_max_floor(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_max_floor(&got, wire, 0) == 4);
  assert(encode_max_floor(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Minimum Quantity: 4 bytes ----------------------------------------------- */

/* Minimum Quantity */
typedef struct {
  uint8_t minimum_quantity_value[4];  /* bytes 0 to 3 */
} MinimumQuantity;

/* any Minimum Quantity at all: every byte one the checker chooses */
static void any_minimum_quantity(MinimumQuantity *record) {
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity_value[i] = arbitrary(); }
}

/* Minimum Quantity to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_minimum_quantity(const MinimumQuantity *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity_value[i]; }

  return at;
}

/* Minimum Quantity off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_minimum_quantity(MinimumQuantity *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity_value[i] = wire[at++]; }

  return at;
}

/* what was read of Minimum Quantity is what was written, byte for byte */
static void equal_minimum_quantity(const MinimumQuantity *read, const MinimumQuantity *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity_value[i] == written->minimum_quantity_value[i]); }
}

/* Minimum Quantity: written and read back, then read and written back */
static void check_minimum_quantity(void) {
  MinimumQuantity sent;
  MinimumQuantity got;
  uint8_t wire[4];
  uint8_t again[4];

  any_minimum_quantity(&sent);
  assert(encode_minimum_quantity(&sent, wire, 0) == 4);
  assert(decode_minimum_quantity(&got, wire, 0) == 4);
  equal_minimum_quantity(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_minimum_quantity(&got, wire, 0) == 4);
  assert(encode_minimum_quantity(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Reference: 10 bytes ----------------------------------------------- */

/* Order Reference */
typedef struct {
  uint8_t order_reference_value[10];  /* bytes 0 to 9 */
} OrderReference;

/* any Order Reference at all: every byte one the checker chooses */
static void any_order_reference(OrderReference *record) {
  for (size_t i = 0; i < 10; i++) { record->order_reference_value[i] = arbitrary(); }
}

/* Order Reference to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_order_reference(const OrderReference *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->order_reference_value[i]; }

  return at;
}

/* Order Reference off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_order_reference(OrderReference *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->order_reference_value[i] = wire[at++]; }

  return at;
}

/* what was read of Order Reference is what was written, byte for byte */
static void equal_order_reference(const OrderReference *read, const OrderReference *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->order_reference_value[i] == written->order_reference_value[i]); }
}

/* Order Reference: written and read back, then read and written back */
static void check_order_reference(void) {
  OrderReference sent;
  OrderReference got;
  uint8_t wire[10];
  uint8_t again[10];

  any_order_reference(&sent);
  assert(encode_order_reference(&sent, wire, 0) == 10);
  assert(decode_order_reference(&got, wire, 0) == 10);
  equal_order_reference(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_order_reference(&got, wire, 0) == 10);
  assert(encode_order_reference(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Original Order Entry Date: 4 bytes -------------------------------------- */

/* Original Order Entry Date */
typedef struct {
  uint8_t original_order_entry_date_value[4];  /* bytes 0 to 3 */
} OriginalOrderEntryDate;

/* any Original Order Entry Date at all: every byte one the checker chooses */
static void any_original_order_entry_date(OriginalOrderEntryDate *record) {
  for (size_t i = 0; i < 4; i++) { record->original_order_entry_date_value[i] = arbitrary(); }
}

/* Original Order Entry Date to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_original_order_entry_date(const OriginalOrderEntryDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_order_entry_date_value[i]; }

  return at;
}

/* Original Order Entry Date off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_original_order_entry_date(OriginalOrderEntryDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->original_order_entry_date_value[i] = wire[at++]; }

  return at;
}

/* what was read of Original Order Entry Date is what was written, byte for byte */
static void equal_original_order_entry_date(const OriginalOrderEntryDate *read, const OriginalOrderEntryDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->original_order_entry_date_value[i] == written->original_order_entry_date_value[i]); }
}

/* Original Order Entry Date: written and read back, then read and written back */
static void check_original_order_entry_date(void) {
  OriginalOrderEntryDate sent;
  OriginalOrderEntryDate got;
  uint8_t wire[4];
  uint8_t again[4];

  any_original_order_entry_date(&sent);
  assert(encode_original_order_entry_date(&sent, wire, 0) == 4);
  assert(decode_original_order_entry_date(&got, wire, 0) == 4);
  equal_original_order_entry_date(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_original_order_entry_date(&got, wire, 0) == 4);
  assert(encode_original_order_entry_date(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Original Order Reference Number: 8 bytes -------------------------------- */

/* Original Order Reference Number */
typedef struct {
  uint8_t original_order_reference_number_value[8];  /* bytes 0 to 7 */
} OriginalOrderReferenceNumber;

/* any Original Order Reference Number at all: every byte one the checker chooses */
static void any_original_order_reference_number(OriginalOrderReferenceNumber *record) {
  for (size_t i = 0; i < 8; i++) { record->original_order_reference_number_value[i] = arbitrary(); }
}

/* Original Order Reference Number to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_original_order_reference_number(const OriginalOrderReferenceNumber *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_reference_number_value[i]; }

  return at;
}

/* Original Order Reference Number off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_original_order_reference_number(OriginalOrderReferenceNumber *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->original_order_reference_number_value[i] = wire[at++]; }

  return at;
}

/* what was read of Original Order Reference Number is what was written, byte for byte */
static void equal_original_order_reference_number(const OriginalOrderReferenceNumber *read, const OriginalOrderReferenceNumber *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_reference_number_value[i] == written->original_order_reference_number_value[i]); }
}

/* Original Order Reference Number: written and read back, then read and written back */
static void check_original_order_reference_number(void) {
  OriginalOrderReferenceNumber sent;
  OriginalOrderReferenceNumber got;
  uint8_t wire[8];
  uint8_t again[8];

  any_original_order_reference_number(&sent);
  assert(encode_original_order_reference_number(&sent, wire, 0) == 8);
  assert(decode_original_order_reference_number(&got, wire, 0) == 8);
  equal_original_order_reference_number(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_original_order_reference_number(&got, wire, 0) == 8);
  assert(encode_original_order_reference_number(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Peg Difference: 4 bytes ------------------------------------------------- */

/* Peg Difference */
typedef struct {
  uint8_t peg_difference_value[4];  /* bytes 0 to 3 */
} PegDifference;

/* any Peg Difference at all: every byte one the checker chooses */
static void any_peg_difference(PegDifference *record) {
  for (size_t i = 0; i < 4; i++) { record->peg_difference_value[i] = arbitrary(); }
}

/* Peg Difference to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_peg_difference(const PegDifference *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->peg_difference_value[i]; }

  return at;
}

/* Peg Difference off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_peg_difference(PegDifference *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->peg_difference_value[i] = wire[at++]; }

  return at;
}

/* what was read of Peg Difference is what was written, byte for byte */
static void equal_peg_difference(const PegDifference *read, const PegDifference *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->peg_difference_value[i] == written->peg_difference_value[i]); }
}

/* Peg Difference: written and read back, then read and written back */
static void check_peg_difference(void) {
  PegDifference sent;
  PegDifference got;
  uint8_t wire[4];
  uint8_t again[4];

  any_peg_difference(&sent);
  assert(encode_peg_difference(&sent, wire, 0) == 4);
  assert(decode_peg_difference(&got, wire, 0) == 4);
  equal_peg_difference(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_peg_difference(&got, wire, 0) == 4);
  assert(encode_peg_difference(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Peg Type: 1 byte -------------------------------------------------------- */

/* Peg Type */
typedef struct {
  uint8_t peg_type_value;  /* byte 0 */
} PegType;

/* any Peg Type at all: every byte one the checker chooses */
static void any_peg_type(PegType *record) {
  record->peg_type_value = arbitrary();
}

/* Peg Type to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_peg_type(const PegType *record, uint8_t *wire, size_t at) {
  wire[at++] = record->peg_type_value;

  return at;
}

/* Peg Type off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_peg_type(PegType *record, const uint8_t *wire, size_t at) {
  record->peg_type_value = wire[at++];

  return at;
}

/* what was read of Peg Type is what was written, byte for byte */
static void equal_peg_type(const PegType *read, const PegType *written) {
  assert(read->peg_type_value == written->peg_type_value);
}

/* Peg Type: written and read back, then read and written back */
static void check_peg_type(void) {
  PegType sent;
  PegType got;
  uint8_t wire[1];
  uint8_t again[1];

  any_peg_type(&sent);
  assert(encode_peg_type(&sent, wire, 0) == 1);
  assert(decode_peg_type(&got, wire, 0) == 1);
  equal_peg_type(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_peg_type(&got, wire, 0) == 1);
  assert(encode_peg_type(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Random Reserve: 4 bytes ------------------------------------------------- */

/* Random Reserve */
typedef struct {
  uint8_t random_reserve_value[4];  /* bytes 0 to 3 */
} RandomReserve;

/* any Random Reserve at all: every byte one the checker chooses */
static void any_random_reserve(RandomReserve *record) {
  for (size_t i = 0; i < 4; i++) { record->random_reserve_value[i] = arbitrary(); }
}

/* Random Reserve to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_random_reserve(const RandomReserve *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->random_reserve_value[i]; }

  return at;
}

/* Random Reserve off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_random_reserve(RandomReserve *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->random_reserve_value[i] = wire[at++]; }

  return at;
}

/* what was read of Random Reserve is what was written, byte for byte */
static void equal_random_reserve(const RandomReserve *read, const RandomReserve *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->random_reserve_value[i] == written->random_reserve_value[i]); }
}

/* Random Reserve: written and read back, then read and written back */
static void check_random_reserve(void) {
  RandomReserve sent;
  RandomReserve got;
  uint8_t wire[4];
  uint8_t again[4];

  any_random_reserve(&sent);
  assert(encode_random_reserve(&sent, wire, 0) == 4);
  assert(decode_random_reserve(&got, wire, 0) == 4);
  equal_random_reserve(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_random_reserve(&got, wire, 0) == 4);
  assert(encode_random_reserve(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Secondary Order Reference Number: 8 bytes ------------------------------- */

/* Secondary Order Reference Number */
typedef struct {
  uint8_t secondary_order_reference_number_value[8];  /* bytes 0 to 7 */
} SecondaryOrderReferenceNumber;

/* any Secondary Order Reference Number at all: every byte one the checker chooses */
static void any_secondary_order_reference_number(SecondaryOrderReferenceNumber *record) {
  for (size_t i = 0; i < 8; i++) { record->secondary_order_reference_number_value[i] = arbitrary(); }
}

/* Secondary Order Reference Number to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_secondary_order_reference_number(const SecondaryOrderReferenceNumber *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_order_reference_number_value[i]; }

  return at;
}

/* Secondary Order Reference Number off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_secondary_order_reference_number(SecondaryOrderReferenceNumber *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->secondary_order_reference_number_value[i] = wire[at++]; }

  return at;
}

/* what was read of Secondary Order Reference Number is what was written, byte for byte */
static void equal_secondary_order_reference_number(const SecondaryOrderReferenceNumber *read, const SecondaryOrderReferenceNumber *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_order_reference_number_value[i] == written->secondary_order_reference_number_value[i]); }
}

/* Secondary Order Reference Number: written and read back, then read and written back */
static void check_secondary_order_reference_number(void) {
  SecondaryOrderReferenceNumber sent;
  SecondaryOrderReferenceNumber got;
  uint8_t wire[8];
  uint8_t again[8];

  any_secondary_order_reference_number(&sent);
  assert(encode_secondary_order_reference_number(&sent, wire, 0) == 8);
  assert(decode_secondary_order_reference_number(&got, wire, 0) == 8);
  equal_secondary_order_reference_number(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_secondary_order_reference_number(&got, wire, 0) == 8);
  assert(encode_secondary_order_reference_number(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stp Action: 1 byte ------------------------------------------------------ */

/* STP Action */
typedef struct {
  uint8_t stp_action_value;  /* byte 0 */
} StpAction;

/* any Stp Action at all: every byte one the checker chooses */
static void any_stp_action(StpAction *record) {
  record->stp_action_value = arbitrary();
}

/* Stp Action to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_stp_action(const StpAction *record, uint8_t *wire, size_t at) {
  wire[at++] = record->stp_action_value;

  return at;
}

/* Stp Action off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_stp_action(StpAction *record, const uint8_t *wire, size_t at) {
  record->stp_action_value = wire[at++];

  return at;
}

/* what was read of Stp Action is what was written, byte for byte */
static void equal_stp_action(const StpAction *read, const StpAction *written) {
  assert(read->stp_action_value == written->stp_action_value);
}

/* Stp Action: written and read back, then read and written back */
static void check_stp_action(void) {
  StpAction sent;
  StpAction got;
  uint8_t wire[1];
  uint8_t again[1];

  any_stp_action(&sent);
  assert(encode_stp_action(&sent, wire, 0) == 1);
  assert(decode_stp_action(&got, wire, 0) == 1);
  equal_stp_action(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_stp_action(&got, wire, 0) == 1);
  assert(encode_stp_action(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stp Level: 1 byte ------------------------------------------------------- */

/* STP Level */
typedef struct {
  uint8_t stp_level_value;  /* byte 0 */
} StpLevel;

/* any Stp Level at all: every byte one the checker chooses */
static void any_stp_level(StpLevel *record) {
  record->stp_level_value = arbitrary();
}

/* Stp Level to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_stp_level(const StpLevel *record, uint8_t *wire, size_t at) {
  wire[at++] = record->stp_level_value;

  return at;
}

/* Stp Level off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_stp_level(StpLevel *record, const uint8_t *wire, size_t at) {
  record->stp_level_value = wire[at++];

  return at;
}

/* what was read of Stp Level is what was written, byte for byte */
static void equal_stp_level(const StpLevel *read, const StpLevel *written) {
  assert(read->stp_level_value == written->stp_level_value);
}

/* Stp Level: written and read back, then read and written back */
static void check_stp_level(void) {
  StpLevel sent;
  StpLevel got;
  uint8_t wire[1];
  uint8_t again[1];

  any_stp_level(&sent);
  assert(encode_stp_level(&sent, wire, 0) == 1);
  assert(decode_stp_level(&got, wire, 0) == 1);
  equal_stp_level(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_stp_level(&got, wire, 0) == 1);
  assert(encode_stp_level(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stp Trader Group: 2 bytes ----------------------------------------------- */

/* STP Trader Group */
typedef struct {
  uint8_t stp_trader_group_value[2];  /* bytes 0 to 1 */
} StpTraderGroup;

/* any Stp Trader Group at all: every byte one the checker chooses */
static void any_stp_trader_group(StpTraderGroup *record) {
  for (size_t i = 0; i < 2; i++) { record->stp_trader_group_value[i] = arbitrary(); }
}

/* Stp Trader Group to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_stp_trader_group(const StpTraderGroup *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stp_trader_group_value[i]; }

  return at;
}

/* Stp Trader Group off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_stp_trader_group(StpTraderGroup *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stp_trader_group_value[i] = wire[at++]; }

  return at;
}

/* what was read of Stp Trader Group is what was written, byte for byte */
static void equal_stp_trader_group(const StpTraderGroup *read, const StpTraderGroup *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stp_trader_group_value[i] == written->stp_trader_group_value[i]); }
}

/* Stp Trader Group: written and read back, then read and written back */
static void check_stp_trader_group(void) {
  StpTraderGroup sent;
  StpTraderGroup got;
  uint8_t wire[2];
  uint8_t again[2];

  any_stp_trader_group(&sent);
  assert(encode_stp_trader_group(&sent, wire, 0) == 2);
  assert(decode_stp_trader_group(&got, wire, 0) == 2);
  equal_stp_trader_group(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_stp_trader_group(&got, wire, 0) == 2);
  assert(encode_stp_trader_group(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Time In Force: 1 byte --------------------------------------------------- */

/* Time in Force */
typedef struct {
  uint8_t time_in_force_value;  /* byte 0 */
} TimeInForce;

/* any Time In Force at all: every byte one the checker chooses */
static void any_time_in_force(TimeInForce *record) {
  record->time_in_force_value = arbitrary();
}

/* Time In Force to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_time_in_force(const TimeInForce *record, uint8_t *wire, size_t at) {
  wire[at++] = record->time_in_force_value;

  return at;
}

/* Time In Force off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_time_in_force(TimeInForce *record, const uint8_t *wire, size_t at) {
  record->time_in_force_value = wire[at++];

  return at;
}

/* what was read of Time In Force is what was written, byte for byte */
static void equal_time_in_force(const TimeInForce *read, const TimeInForce *written) {
  assert(read->time_in_force_value == written->time_in_force_value);
}

/* Time In Force: written and read back, then read and written back */
static void check_time_in_force(void) {
  TimeInForce sent;
  TimeInForce got;
  uint8_t wire[1];
  uint8_t again[1];

  any_time_in_force(&sent);
  assert(encode_time_in_force(&sent, wire, 0) == 1);
  assert(decode_time_in_force(&got, wire, 0) == 1);
  equal_time_in_force(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_time_in_force(&got, wire, 0) == 1);
  assert(encode_time_in_force(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading At Closing Price: 1 byte ---------------------------------------- */

/* Trading at Closing price */
typedef struct {
  uint8_t trading_at_closing_price_value;  /* byte 0 */
} TradingAtClosingPrice;

/* any Trading At Closing Price at all: every byte one the checker chooses */
static void any_trading_at_closing_price(TradingAtClosingPrice *record) {
  record->trading_at_closing_price_value = arbitrary();
}

/* Trading At Closing Price to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_trading_at_closing_price(const TradingAtClosingPrice *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_at_closing_price_value;

  return at;
}

/* Trading At Closing Price off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_trading_at_closing_price(TradingAtClosingPrice *record, const uint8_t *wire, size_t at) {
  record->trading_at_closing_price_value = wire[at++];

  return at;
}

/* what was read of Trading At Closing Price is what was written, byte for byte */
static void equal_trading_at_closing_price(const TradingAtClosingPrice *read, const TradingAtClosingPrice *written) {
  assert(read->trading_at_closing_price_value == written->trading_at_closing_price_value);
}

/* Trading At Closing Price: written and read back, then read and written back */
static void check_trading_at_closing_price(void) {
  TradingAtClosingPrice sent;
  TradingAtClosingPrice got;
  uint8_t wire[1];
  uint8_t again[1];

  any_trading_at_closing_price(&sent);
  assert(encode_trading_at_closing_price(&sent, wire, 0) == 1);
  assert(decode_trading_at_closing_price(&got, wire, 0) == 1);
  equal_trading_at_closing_price(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_at_closing_price(&got, wire, 0) == 1);
  assert(encode_trading_at_closing_price(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Condition: 1 byte ------------------------------------------------- */

/* Order Condition */
typedef struct {
  uint8_t order_condition_value;  /* byte 0 */
} OrderCondition;

/* any Order Condition at all: every byte one the checker chooses */
static void any_order_condition(OrderCondition *record) {
  record->order_condition_value = arbitrary();
}

/* Order Condition to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_order_condition(const OrderCondition *record, uint8_t *wire, size_t at) {
  wire[at++] = record->order_condition_value;

  return at;
}

/* Order Condition off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_order_condition(OrderCondition *record, const uint8_t *wire, size_t at) {
  record->order_condition_value = wire[at++];

  return at;
}

/* what was read of Order Condition is what was written, byte for byte */
static void equal_order_condition(const OrderCondition *read, const OrderCondition *written) {
  assert(read->order_condition_value == written->order_condition_value);
}

/* Order Condition: written and read back, then read and written back */
static void check_order_condition(void) {
  OrderCondition sent;
  OrderCondition got;
  uint8_t wire[1];
  uint8_t again[1];

  any_order_condition(&sent);
  assert(encode_order_condition(&sent, wire, 0) == 1);
  assert(decode_order_condition(&got, wire, 0) == 1);
  equal_order_condition(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_order_condition(&got, wire, 0) == 1);
  assert(encode_order_condition(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cumulative Quantity: 4 bytes -------------------------------------------- */

/* Cumulative Quantity */
typedef struct {
  uint8_t cumulative_quantity_value[4];  /* bytes 0 to 3 */
} CumulativeQuantity;

/* any Cumulative Quantity at all: every byte one the checker chooses */
static void any_cumulative_quantity(CumulativeQuantity *record) {
  for (size_t i = 0; i < 4; i++) { record->cumulative_quantity_value[i] = arbitrary(); }
}

/* Cumulative Quantity to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_cumulative_quantity(const CumulativeQuantity *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cumulative_quantity_value[i]; }

  return at;
}

/* Cumulative Quantity off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_cumulative_quantity(CumulativeQuantity *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->cumulative_quantity_value[i] = wire[at++]; }

  return at;
}

/* what was read of Cumulative Quantity is what was written, byte for byte */
static void equal_cumulative_quantity(const CumulativeQuantity *read, const CumulativeQuantity *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->cumulative_quantity_value[i] == written->cumulative_quantity_value[i]); }
}

/* Cumulative Quantity: written and read back, then read and written back */
static void check_cumulative_quantity(void) {
  CumulativeQuantity sent;
  CumulativeQuantity got;
  uint8_t wire[4];
  uint8_t again[4];

  any_cumulative_quantity(&sent);
  assert(encode_cumulative_quantity(&sent, wire, 0) == 4);
  assert(decode_cumulative_quantity(&got, wire, 0) == 4);
  equal_cumulative_quantity(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_cumulative_quantity(&got, wire, 0) == 4);
  assert(encode_cumulative_quantity(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Customer Order Capacity: 1 byte ----------------------------------------- */

/* Customer Order Capacity */
typedef struct {
  uint8_t customer_order_capacity_value;  /* byte 0 */
} CustomerOrderCapacity;

/* any Customer Order Capacity at all: every byte one the checker chooses */
static void any_customer_order_capacity(CustomerOrderCapacity *record) {
  record->customer_order_capacity_value = arbitrary();
}

/* Customer Order Capacity to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_customer_order_capacity(const CustomerOrderCapacity *record, uint8_t *wire, size_t at) {
  wire[at++] = record->customer_order_capacity_value;

  return at;
}

/* Customer Order Capacity off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_customer_order_capacity(CustomerOrderCapacity *record, const uint8_t *wire, size_t at) {
  record->customer_order_capacity_value = wire[at++];

  return at;
}

/* what was read of Customer Order Capacity is what was written, byte for byte */
static void equal_customer_order_capacity(const CustomerOrderCapacity *read, const CustomerOrderCapacity *written) {
  assert(read->customer_order_capacity_value == written->customer_order_capacity_value);
}

/* Customer Order Capacity: written and read back, then read and written back */
static void check_customer_order_capacity(void) {
  CustomerOrderCapacity sent;
  CustomerOrderCapacity got;
  uint8_t wire[1];
  uint8_t again[1];

  any_customer_order_capacity(&sent);
  assert(encode_customer_order_capacity(&sent, wire, 0) == 1);
  assert(decode_customer_order_capacity(&got, wire, 0) == 1);
  equal_customer_order_capacity(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_customer_order_capacity(&got, wire, 0) == 1);
  assert(encode_customer_order_capacity(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Target Strategy: 1 byte ------------------------------------------------- */

/* Target Strategy */
typedef struct {
  uint8_t target_strategy_value;  /* byte 0 */
} TargetStrategy;

/* any Target Strategy at all: every byte one the checker chooses */
static void any_target_strategy(TargetStrategy *record) {
  record->target_strategy_value = arbitrary();
}

/* Target Strategy to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_target_strategy(const TargetStrategy *record, uint8_t *wire, size_t at) {
  wire[at++] = record->target_strategy_value;

  return at;
}

/* Target Strategy off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_target_strategy(TargetStrategy *record, const uint8_t *wire, size_t at) {
  record->target_strategy_value = wire[at++];

  return at;
}

/* what was read of Target Strategy is what was written, byte for byte */
static void equal_target_strategy(const TargetStrategy *read, const TargetStrategy *written) {
  assert(read->target_strategy_value == written->target_strategy_value);
}

/* Target Strategy: written and read back, then read and written back */
static void check_target_strategy(void) {
  TargetStrategy sent;
  TargetStrategy got;
  uint8_t wire[1];
  uint8_t again[1];

  any_target_strategy(&sent);
  assert(encode_target_strategy(&sent, wire, 0) == 1);
  assert(decode_target_strategy(&got, wire, 0) == 1);
  equal_target_strategy(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_target_strategy(&got, wire, 0) == 1);
  assert(encode_target_strategy(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Min Rate: 2 bytes ------------------------------------------------------- */

/* Min Rate */
typedef struct {
  uint8_t min_rate_value[2];  /* bytes 0 to 1 */
} MinRate;

/* any Min Rate at all: every byte one the checker chooses */
static void any_min_rate(MinRate *record) {
  for (size_t i = 0; i < 2; i++) { record->min_rate_value[i] = arbitrary(); }
}

/* Min Rate to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_min_rate(const MinRate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->min_rate_value[i]; }

  return at;
}

/* Min Rate off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_min_rate(MinRate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->min_rate_value[i] = wire[at++]; }

  return at;
}

/* what was read of Min Rate is what was written, byte for byte */
static void equal_min_rate(const MinRate *read, const MinRate *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->min_rate_value[i] == written->min_rate_value[i]); }
}

/* Min Rate: written and read back, then read and written back */
static void check_min_rate(void) {
  MinRate sent;
  MinRate got;
  uint8_t wire[2];
  uint8_t again[2];

  any_min_rate(&sent);
  assert(encode_min_rate(&sent, wire, 0) == 2);
  assert(decode_min_rate(&got, wire, 0) == 2);
  equal_min_rate(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_min_rate(&got, wire, 0) == 2);
  assert(encode_min_rate(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Max Rate: 2 bytes ------------------------------------------------------- */

/* Max Rate */
typedef struct {
  uint8_t max_rate_value[2];  /* bytes 0 to 1 */
} MaxRate;

/* any Max Rate at all: every byte one the checker chooses */
static void any_max_rate(MaxRate *record) {
  for (size_t i = 0; i < 2; i++) { record->max_rate_value[i] = arbitrary(); }
}

/* Max Rate to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_max_rate(const MaxRate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->max_rate_value[i]; }

  return at;
}

/* Max Rate off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_max_rate(MaxRate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->max_rate_value[i] = wire[at++]; }

  return at;
}

/* what was read of Max Rate is what was written, byte for byte */
static void equal_max_rate(const MaxRate *read, const MaxRate *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->max_rate_value[i] == written->max_rate_value[i]); }
}

/* Max Rate: written and read back, then read and written back */
static void check_max_rate(void) {
  MaxRate sent;
  MaxRate got;
  uint8_t wire[2];
  uint8_t again[2];

  any_max_rate(&sent);
  assert(encode_max_rate(&sent, wire, 0) == 2);
  assert(decode_max_rate(&got, wire, 0) == 2);
  equal_max_rate(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_max_rate(&got, wire, 0) == 2);
  assert(encode_max_rate(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Conditional Type: 1 byte ------------------------------------------------ */

/* Conditional Type */
typedef struct {
  uint8_t conditional_type_value;  /* byte 0 */
} ConditionalType;

/* any Conditional Type at all: every byte one the checker chooses */
static void any_conditional_type(ConditionalType *record) {
  record->conditional_type_value = arbitrary();
}

/* Conditional Type to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_conditional_type(const ConditionalType *record, uint8_t *wire, size_t at) {
  wire[at++] = record->conditional_type_value;

  return at;
}

/* Conditional Type off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_conditional_type(ConditionalType *record, const uint8_t *wire, size_t at) {
  record->conditional_type_value = wire[at++];

  return at;
}

/* what was read of Conditional Type is what was written, byte for byte */
static void equal_conditional_type(const ConditionalType *read, const ConditionalType *written) {
  assert(read->conditional_type_value == written->conditional_type_value);
}

/* Conditional Type: written and read back, then read and written back */
static void check_conditional_type(void) {
  ConditionalType sent;
  ConditionalType got;
  uint8_t wire[1];
  uint8_t again[1];

  any_conditional_type(&sent);
  assert(encode_conditional_type(&sent, wire, 0) == 1);
  assert(decode_conditional_type(&got, wire, 0) == 1);
  equal_conditional_type(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_conditional_type(&got, wire, 0) == 1);
  assert(encode_conditional_type(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Firm Up Id: 4 bytes ----------------------------------------------------- */

/* Firm-Up ID */
typedef struct {
  uint8_t firm_up_id_value[4];  /* bytes 0 to 3 */
} FirmUpId;

/* any Firm Up Id at all: every byte one the checker chooses */
static void any_firm_up_id(FirmUpId *record) {
  for (size_t i = 0; i < 4; i++) { record->firm_up_id_value[i] = arbitrary(); }
}

/* Firm Up Id to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_firm_up_id(const FirmUpId *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_up_id_value[i]; }

  return at;
}

/* Firm Up Id off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_firm_up_id(FirmUpId *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->firm_up_id_value[i] = wire[at++]; }

  return at;
}

/* what was read of Firm Up Id is what was written, byte for byte */
static void equal_firm_up_id(const FirmUpId *read, const FirmUpId *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->firm_up_id_value[i] == written->firm_up_id_value[i]); }
}

/* Firm Up Id: written and read back, then read and written back */
static void check_firm_up_id(void) {
  FirmUpId sent;
  FirmUpId got;
  uint8_t wire[4];
  uint8_t again[4];

  any_firm_up_id(&sent);
  assert(encode_firm_up_id(&sent, wire, 0) == 4);
  assert(decode_firm_up_id(&got, wire, 0) == 4);
  equal_firm_up_id(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_firm_up_id(&got, wire, 0) == 4);
  assert(encode_firm_up_id(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Message: 14 bytes ------------------------------------------ */

/* Requests that an order be cancelled or reduced */
typedef struct {
  uint8_t user_ref_num[4];  /* bytes 0 to 3 */
  uint8_t quantity[4];      /* bytes 4 to 7 */
  uint8_t user[6];          /* bytes 8 to 13 */
} CancelOrderMessage;

/* any Cancel Order Message at all: every byte one the checker chooses */
static void any_cancel_order_message(CancelOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->user[i] = arbitrary(); }
}

/* Cancel Order Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_message(const CancelOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_ref_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->user[i]; }

  return at;
}

/* Cancel Order Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_message(CancelOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->user[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Message is what was written, byte for byte */
static void equal_cancel_order_message(const CancelOrderMessage *read, const CancelOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_ref_num[i] == written->user_ref_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->user[i] == written->user[i]); }
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

/* ---- Mmi Notification Request Message: 20 bytes ------------------------------ */

/* Requests a market making instruction notification */
typedef struct {
  uint8_t user_ref_num[4];  /* bytes 0 to 3 */
  uint8_t order_book[4];    /* bytes 4 to 7 */
  uint8_t instruction;      /* byte 8 */
  uint8_t add_or_remove;    /* byte 9 */
  Firm firm;                /* bytes 10 to 13 */
  uint8_t user[6];          /* bytes 14 to 19 */
} MmiNotificationRequestMessage;

/* any Mmi Notification Request Message at all: every byte one the checker chooses */
static void any_mmi_notification_request_message(MmiNotificationRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = arbitrary(); }
  record->instruction = arbitrary();
  record->add_or_remove = arbitrary();
  any_firm(&record->firm);
  for (size_t i = 0; i < 6; i++) { record->user[i] = arbitrary(); }
}

/* Mmi Notification Request Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_mmi_notification_request_message(const MmiNotificationRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_ref_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book[i]; }
  wire[at++] = record->instruction;
  wire[at++] = record->add_or_remove;
  at = encode_firm(&record->firm, wire, at);
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->user[i]; }

  return at;
}

/* Mmi Notification Request Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_mmi_notification_request_message(MmiNotificationRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = wire[at++]; }
  record->instruction = wire[at++];
  record->add_or_remove = wire[at++];
  at = decode_firm(&record->firm, wire, at);
  for (size_t i = 0; i < 6; i++) { record->user[i] = wire[at++]; }

  return at;
}

/* what was read of Mmi Notification Request Message is what was written, byte for byte */
static void equal_mmi_notification_request_message(const MmiNotificationRequestMessage *read, const MmiNotificationRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_ref_num[i] == written->user_ref_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book[i] == written->order_book[i]); }
  assert(read->instruction == written->instruction);
  assert(read->add_or_remove == written->add_or_remove);
  equal_firm(&read->firm, &written->firm);
  for (size_t i = 0; i < 6; i++) { assert(read->user[i] == written->user[i]); }
}

/* Mmi Notification Request Message: written and read back, then read and written back */
static void check_mmi_notification_request_message(void) {
  MmiNotificationRequestMessage sent;
  MmiNotificationRequestMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_mmi_notification_request_message(&sent);
  assert(encode_mmi_notification_request_message(&sent, wire, 0) == 20);
  assert(decode_mmi_notification_request_message(&got, wire, 0) == 20);
  equal_mmi_notification_request_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_mmi_notification_request_message(&got, wire, 0) == 20);
  assert(encode_mmi_notification_request_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_client_packet_header();
  check_login_request_packet();
  check_clearing_account();
  check_clearing_account_type();
  check_clearing_firm();
  check_client_reference();
  check_cross_type();
  check_dea_indicator();
  check_display();
  check_display_price();
  check_display_quantity();
  check_expire_time();
  check_firm();
  check_liquidity_provision_indicator();
  check_max_floor();
  check_minimum_quantity();
  check_order_reference();
  check_original_order_entry_date();
  check_original_order_reference_number();
  check_peg_difference();
  check_peg_type();
  check_random_reserve();
  check_secondary_order_reference_number();
  check_stp_action();
  check_stp_level();
  check_stp_trader_group();
  check_time_in_force();
  check_trading_at_closing_price();
  check_order_condition();
  check_cumulative_quantity();
  check_customer_order_capacity();
  check_target_strategy();
  check_min_rate();
  check_max_rate();
  check_conditional_type();
  check_firm_up_id();
  check_cancel_order_message();
  check_mmi_notification_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
