// sgx/titandt/depthofbook/Sgx_TitanDt_DepthOfBook_Glimpse_v1_4_Server.c
/*
 * Singapore Exchange Depth Of Book
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

/* ---- Seconds Message: 4 bytes ------------------------------------------------ */

/* Sent every second for which at least one Itch message is generated */
typedef struct {
  uint8_t second[4];  /* bytes 0 to 3 */
} SecondsMessage;

/* any Seconds Message at all: every byte one the checker chooses */
static void any_seconds_message(SecondsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = arbitrary(); }
}

/* Seconds Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_seconds_message(const SecondsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second[i]; }

  return at;
}

/* Seconds Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_seconds_message(SecondsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->second[i] = wire[at++]; }

  return at;
}

/* what was read of Seconds Message is what was written, byte for byte */
static void equal_seconds_message(const SecondsMessage *read, const SecondsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->second[i] == written->second[i]); }
}

/* Seconds Message: written and read back, then read and written back */
static void check_seconds_message(void) {
  SecondsMessage sent;
  SecondsMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_seconds_message(&sent);
  assert(encode_seconds_message(&sent, wire, 0) == 4);
  assert(decode_seconds_message(&got, wire, 0) == 4);
  equal_seconds_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_seconds_message(&got, wire, 0) == 4);
  assert(encode_seconds_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book Directory Message: 112 bytes --------------------------------- */

/* Disseminated at the start of each trading day for all active instruments */
typedef struct {
  uint8_t nanoseconds[4];                          /* bytes 0 to 3 */
  uint8_t order_book_id[4];                        /* bytes 4 to 7 */
  uint8_t symbol[32];                              /* bytes 8 to 39 */
  uint8_t long_name[32];                           /* bytes 40 to 71 */
  uint8_t reserved_12[12];                         /* bytes 72 to 83 */
  uint8_t financial_product;                       /* byte 84 */
  uint8_t trading_currency[3];                     /* bytes 85 to 87 */
  uint8_t number_of_decimals_in_price[2];          /* bytes 88 to 89 */
  uint8_t number_of_decimals_in_nominal_value[2];  /* bytes 90 to 91 */
  uint8_t reserved_4_a[4];                         /* bytes 92 to 95 */
  uint8_t reserved_4_b[4];                         /* bytes 96 to 99 */
  uint8_t reserved_4_c[4];                         /* bytes 100 to 103 */
  uint8_t nominal_value[8];                        /* bytes 104 to 111 */
} OrderBookDirectoryMessage;

/* any Order Book Directory Message at all: every byte one the checker chooses */
static void any_order_book_directory_message(OrderBookDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->long_name[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = arbitrary(); }
  record->financial_product = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_a[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_b[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_c[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = arbitrary(); }
}

/* Order Book Directory Message to the wire: 112 bytes from at, returning where the next byte goes */
static size_t encode_order_book_directory_message(const OrderBookDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->long_name[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reserved_12[i]; }
  wire[at++] = record->financial_product;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_currency[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_in_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_in_nominal_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4_a[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4_b[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4_c[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nominal_value[i]; }

  return at;
}

/* Order Book Directory Message off the wire: 112 bytes from at, returning where the next byte lies */
static size_t decode_order_book_directory_message(OrderBookDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->long_name[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = wire[at++]; }
  record->financial_product = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_nominal_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_a[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_b[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_c[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = wire[at++]; }

  return at;
}

/* what was read of Order Book Directory Message is what was written, byte for byte */
static void equal_order_book_directory_message(const OrderBookDirectoryMessage *read, const OrderBookDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->long_name[i] == written->long_name[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->reserved_12[i] == written->reserved_12[i]); }
  assert(read->financial_product == written->financial_product);
  for (size_t i = 0; i < 3; i++) { assert(read->trading_currency[i] == written->trading_currency[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_price[i] == written->number_of_decimals_in_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_nominal_value[i] == written->number_of_decimals_in_nominal_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4_a[i] == written->reserved_4_a[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4_b[i] == written->reserved_4_b[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4_c[i] == written->reserved_4_c[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nominal_value[i] == written->nominal_value[i]); }
}

/* Order Book Directory Message: written and read back, then read and written back */
static void check_order_book_directory_message(void) {
  OrderBookDirectoryMessage sent;
  OrderBookDirectoryMessage got;
  uint8_t wire[112];
  uint8_t again[112];

  any_order_book_directory_message(&sent);
  assert(encode_order_book_directory_message(&sent, wire, 0) == 112);
  assert(decode_order_book_directory_message(&got, wire, 0) == 112);
  equal_order_book_directory_message(&got, &sent);

  for (size_t i = 0; i < 112; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_directory_message(&got, wire, 0) == 112);
  assert(encode_order_book_directory_message(&got, again, 0) == 112);
  for (size_t i = 0; i < 112; i++) { assert(again[i] == wire[i]); }
}

/* ---- Combination Order Book Directory Message: 260 bytes --------------------- */

/* Specialized directory message used when Combination Order Books are traded */
typedef struct {
  uint8_t nanoseconds[4];                          /* bytes 0 to 3 */
  uint8_t order_book_id[4];                        /* bytes 4 to 7 */
  uint8_t symbol[32];                              /* bytes 8 to 39 */
  uint8_t long_name[32];                           /* bytes 40 to 71 */
  uint8_t reserved_12[12];                         /* bytes 72 to 83 */
  uint8_t financial_product;                       /* byte 84 */
  uint8_t trading_currency[3];                     /* bytes 85 to 87 */
  uint8_t number_of_decimals_in_price[2];          /* bytes 88 to 89 */
  uint8_t number_of_decimals_in_nominal_value[2];  /* bytes 90 to 91 */
  uint8_t reserved_4_a[4];                         /* bytes 92 to 95 */
  uint8_t reserved_4_b[4];                         /* bytes 96 to 99 */
  uint8_t reserved_4_c[4];                         /* bytes 100 to 103 */
  uint8_t nominal_value[8];                        /* bytes 104 to 111 */
  uint8_t leg_1_symbol[32];                        /* bytes 112 to 143 */
  uint8_t leg_1_side;                              /* byte 144 */
  uint8_t leg_1_ratio[4];                          /* bytes 145 to 148 */
  uint8_t leg_2_symbol[32];                        /* bytes 149 to 180 */
  uint8_t leg_2_side;                              /* byte 181 */
  uint8_t leg_2_ratio[4];                          /* bytes 182 to 185 */
  uint8_t leg_3_symbol[32];                        /* bytes 186 to 217 */
  uint8_t leg_3_side;                              /* byte 218 */
  uint8_t leg_3_ratio[4];                          /* bytes 219 to 222 */
  uint8_t leg_4_symbol[32];                        /* bytes 223 to 254 */
  uint8_t leg_4_side;                              /* byte 255 */
  uint8_t leg_4_ratio[4];                          /* bytes 256 to 259 */
} CombinationOrderBookDirectoryMessage;

/* any Combination Order Book Directory Message at all: every byte one the checker chooses */
static void any_combination_order_book_directory_message(CombinationOrderBookDirectoryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->long_name[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = arbitrary(); }
  record->financial_product = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_a[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_b[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_c[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->leg_1_symbol[i] = arbitrary(); }
  record->leg_1_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_1_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->leg_2_symbol[i] = arbitrary(); }
  record->leg_2_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_2_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->leg_3_symbol[i] = arbitrary(); }
  record->leg_3_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_3_ratio[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->leg_4_symbol[i] = arbitrary(); }
  record->leg_4_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_4_ratio[i] = arbitrary(); }
}

/* Combination Order Book Directory Message to the wire: 260 bytes from at, returning where the next byte goes */
static size_t encode_combination_order_book_directory_message(const CombinationOrderBookDirectoryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->long_name[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reserved_12[i]; }
  wire[at++] = record->financial_product;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_currency[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_in_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_in_nominal_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4_a[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4_b[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4_c[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nominal_value[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->leg_1_symbol[i]; }
  wire[at++] = record->leg_1_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_1_ratio[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->leg_2_symbol[i]; }
  wire[at++] = record->leg_2_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_2_ratio[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->leg_3_symbol[i]; }
  wire[at++] = record->leg_3_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_3_ratio[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->leg_4_symbol[i]; }
  wire[at++] = record->leg_4_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_4_ratio[i]; }

  return at;
}

/* Combination Order Book Directory Message off the wire: 260 bytes from at, returning where the next byte lies */
static size_t decode_combination_order_book_directory_message(CombinationOrderBookDirectoryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->long_name[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = wire[at++]; }
  record->financial_product = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_nominal_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_a[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_b[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_c[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->leg_1_symbol[i] = wire[at++]; }
  record->leg_1_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_1_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->leg_2_symbol[i] = wire[at++]; }
  record->leg_2_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_2_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->leg_3_symbol[i] = wire[at++]; }
  record->leg_3_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_3_ratio[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->leg_4_symbol[i] = wire[at++]; }
  record->leg_4_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_4_ratio[i] = wire[at++]; }

  return at;
}

/* what was read of Combination Order Book Directory Message is what was written, byte for byte */
static void equal_combination_order_book_directory_message(const CombinationOrderBookDirectoryMessage *read, const CombinationOrderBookDirectoryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->long_name[i] == written->long_name[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->reserved_12[i] == written->reserved_12[i]); }
  assert(read->financial_product == written->financial_product);
  for (size_t i = 0; i < 3; i++) { assert(read->trading_currency[i] == written->trading_currency[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_price[i] == written->number_of_decimals_in_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_nominal_value[i] == written->number_of_decimals_in_nominal_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4_a[i] == written->reserved_4_a[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4_b[i] == written->reserved_4_b[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4_c[i] == written->reserved_4_c[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nominal_value[i] == written->nominal_value[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->leg_1_symbol[i] == written->leg_1_symbol[i]); }
  assert(read->leg_1_side == written->leg_1_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_1_ratio[i] == written->leg_1_ratio[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->leg_2_symbol[i] == written->leg_2_symbol[i]); }
  assert(read->leg_2_side == written->leg_2_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_2_ratio[i] == written->leg_2_ratio[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->leg_3_symbol[i] == written->leg_3_symbol[i]); }
  assert(read->leg_3_side == written->leg_3_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_3_ratio[i] == written->leg_3_ratio[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->leg_4_symbol[i] == written->leg_4_symbol[i]); }
  assert(read->leg_4_side == written->leg_4_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_4_ratio[i] == written->leg_4_ratio[i]); }
}

/* Combination Order Book Directory Message: written and read back, then read and written back */
static void check_combination_order_book_directory_message(void) {
  CombinationOrderBookDirectoryMessage sent;
  CombinationOrderBookDirectoryMessage got;
  uint8_t wire[260];
  uint8_t again[260];

  any_combination_order_book_directory_message(&sent);
  assert(encode_combination_order_book_directory_message(&sent, wire, 0) == 260);
  assert(decode_combination_order_book_directory_message(&got, wire, 0) == 260);
  equal_combination_order_book_directory_message(&got, &sent);

  for (size_t i = 0; i < 260; i++) { wire[i] = arbitrary(); }
  assert(decode_combination_order_book_directory_message(&got, wire, 0) == 260);
  assert(encode_combination_order_book_directory_message(&got, again, 0) == 260);
  for (size_t i = 0; i < 260; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Size Table Entry Message: 24 bytes --------------------------------- */

/* Contains information on a tick size for a price range */
typedef struct {
  uint8_t nanoseconds[4];    /* bytes 0 to 3 */
  uint8_t order_book_id[4];  /* bytes 4 to 7 */
  uint8_t tick_size[8];      /* bytes 8 to 15 */
  uint8_t price_from[4];     /* bytes 16 to 19 */
  uint8_t price_to[4];       /* bytes 20 to 23 */
} TickSizeTableEntryMessage;

/* any Tick Size Table Entry Message at all: every byte one the checker chooses */
static void any_tick_size_table_entry_message(TickSizeTableEntryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_from[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_to[i] = arbitrary(); }
}

/* Tick Size Table Entry Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_tick_size_table_entry_message(const TickSizeTableEntryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_from[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_to[i]; }

  return at;
}

/* Tick Size Table Entry Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_tick_size_table_entry_message(TickSizeTableEntryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_from[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_to[i] = wire[at++]; }

  return at;
}

/* what was read of Tick Size Table Entry Message is what was written, byte for byte */
static void equal_tick_size_table_entry_message(const TickSizeTableEntryMessage *read, const TickSizeTableEntryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tick_size[i] == written->tick_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_from[i] == written->price_from[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_to[i] == written->price_to[i]); }
}

/* Tick Size Table Entry Message: written and read back, then read and written back */
static void check_tick_size_table_entry_message(void) {
  TickSizeTableEntryMessage sent;
  TickSizeTableEntryMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_tick_size_table_entry_message(&sent);
  assert(encode_tick_size_table_entry_message(&sent, wire, 0) == 24);
  assert(decode_tick_size_table_entry_message(&got, wire, 0) == 24);
  equal_tick_size_table_entry_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_size_table_entry_message(&got, wire, 0) == 24);
  assert(encode_tick_size_table_entry_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book State Message: 28 bytes -------------------------------------- */

/* Relays information on state changes */
typedef struct {
  uint8_t nanoseconds[4];    /* bytes 0 to 3 */
  uint8_t order_book_id[4];  /* bytes 4 to 7 */
  uint8_t state_name[20];    /* bytes 8 to 27 */
} OrderBookStateMessage;

/* any Order Book State Message at all: every byte one the checker chooses */
static void any_order_book_state_message(OrderBookStateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->state_name[i] = arbitrary(); }
}

/* Order Book State Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_order_book_state_message(const OrderBookStateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->state_name[i]; }

  return at;
}

/* Order Book State Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_order_book_state_message(OrderBookStateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->state_name[i] = wire[at++]; }

  return at;
}

/* what was read of Order Book State Message is what was written, byte for byte */
static void equal_order_book_state_message(const OrderBookStateMessage *read, const OrderBookStateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->state_name[i] == written->state_name[i]); }
}

/* Order Book State Message: written and read back, then read and written back */
static void check_order_book_state_message(void) {
  OrderBookStateMessage sent;
  OrderBookStateMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_order_book_state_message(&sent);
  assert(encode_order_book_state_message(&sent, wire, 0) == 28);
  assert(decode_order_book_state_message(&got, wire, 0) == 28);
  equal_order_book_state_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_state_message(&got, wire, 0) == 28);
  assert(encode_order_book_state_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Snapshot Message: 20 bytes --------------------------------------- */

/* Returns the Itch sequence number to be used when connecting to the Itch feed */
typedef struct {
  uint8_t itch_sequence_number[20];  /* bytes 0 to 19 */
} EndOfSnapshotMessage;

/* any End Of Snapshot Message at all: every byte one the checker chooses */
static void any_end_of_snapshot_message(EndOfSnapshotMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->itch_sequence_number[i] = arbitrary(); }
}

/* End Of Snapshot Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_end_of_snapshot_message(const EndOfSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->itch_sequence_number[i]; }

  return at;
}

/* End Of Snapshot Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_end_of_snapshot_message(EndOfSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->itch_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Snapshot Message is what was written, byte for byte */
static void equal_end_of_snapshot_message(const EndOfSnapshotMessage *read, const EndOfSnapshotMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->itch_sequence_number[i] == written->itch_sequence_number[i]); }
}

/* End Of Snapshot Message: written and read back, then read and written back */
static void check_end_of_snapshot_message(void) {
  EndOfSnapshotMessage sent;
  EndOfSnapshotMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_end_of_snapshot_message(&sent);
  assert(encode_end_of_snapshot_message(&sent, wire, 0) == 20);
  assert(decode_end_of_snapshot_message(&got, wire, 0) == 20);
  equal_end_of_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_snapshot_message(&got, wire, 0) == 20);
  assert(encode_end_of_snapshot_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_seconds_message();
  check_order_book_directory_message();
  check_combination_order_book_directory_message();
  check_tick_size_table_entry_message();
  check_order_book_state_message();
  check_end_of_snapshot_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
