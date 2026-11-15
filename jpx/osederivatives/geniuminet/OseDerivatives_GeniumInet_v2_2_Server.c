// jpx/osederivatives/geniuminet/OseDerivatives_GeniumInet_v2_2_Server.c
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

/* Provides data on the seconds when each message is disseminated. */
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

/* ---- Series Information Basic Message: 128 bytes ----------------------------- */

/* Provides detailed data about the series that can be traded on a given business day. */
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
  uint8_t odd_lot_size[4];                         /* bytes 92 to 95 */
  uint8_t round_lot_size[4];                       /* bytes 96 to 99 */
  uint8_t block_lot_size[4];                       /* bytes 100 to 103 */
  uint8_t nominal_value[8];                        /* bytes 104 to 111 */
  uint8_t number_of_legs;                          /* byte 112 */
  uint8_t underlying_order_book_id[4];             /* bytes 113 to 116 */
  uint8_t strike_price[4];                         /* bytes 117 to 120 */
  uint8_t expiration_date[4];                      /* bytes 121 to 124 */
  uint8_t number_of_decimals_in_strike_price[2];   /* bytes 125 to 126 */
  uint8_t put_or_call;                             /* byte 127 */
} SeriesInformationBasicMessage;

/* any Series Information Basic Message at all: every byte one the checker chooses */
static void any_series_information_basic_message(SeriesInformationBasicMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->long_name[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = arbitrary(); }
  record->financial_product = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_nominal_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->odd_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->round_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->block_lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = arbitrary(); }
  record->number_of_legs = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->underlying_order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_strike_price[i] = arbitrary(); }
  record->put_or_call = arbitrary();
}

/* Series Information Basic Message to the wire: 128 bytes from at, returning where the next byte goes */
static size_t encode_series_information_basic_message(const SeriesInformationBasicMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->long_name[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reserved_12[i]; }
  wire[at++] = record->financial_product;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_currency[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_in_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_in_nominal_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->odd_lot_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->round_lot_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_lot_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nominal_value[i]; }
  wire[at++] = record->number_of_legs;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_decimals_in_strike_price[i]; }
  wire[at++] = record->put_or_call;

  return at;
}

/* Series Information Basic Message off the wire: 128 bytes from at, returning where the next byte lies */
static size_t decode_series_information_basic_message(SeriesInformationBasicMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->long_name[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = wire[at++]; }
  record->financial_product = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_nominal_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->odd_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->round_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->block_lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nominal_value[i] = wire[at++]; }
  record->number_of_legs = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->underlying_order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_decimals_in_strike_price[i] = wire[at++]; }
  record->put_or_call = wire[at++];

  return at;
}

/* what was read of Series Information Basic Message is what was written, byte for byte */
static void equal_series_information_basic_message(const SeriesInformationBasicMessage *read, const SeriesInformationBasicMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->long_name[i] == written->long_name[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->reserved_12[i] == written->reserved_12[i]); }
  assert(read->financial_product == written->financial_product);
  for (size_t i = 0; i < 3; i++) { assert(read->trading_currency[i] == written->trading_currency[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_price[i] == written->number_of_decimals_in_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_nominal_value[i] == written->number_of_decimals_in_nominal_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->odd_lot_size[i] == written->odd_lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->round_lot_size[i] == written->round_lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->block_lot_size[i] == written->block_lot_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nominal_value[i] == written->nominal_value[i]); }
  assert(read->number_of_legs == written->number_of_legs);
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_order_book_id[i] == written->underlying_order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_decimals_in_strike_price[i] == written->number_of_decimals_in_strike_price[i]); }
  assert(read->put_or_call == written->put_or_call);
}

/* Series Information Basic Message: written and read back, then read and written back */
static void check_series_information_basic_message(void) {
  SeriesInformationBasicMessage sent;
  SeriesInformationBasicMessage got;
  uint8_t wire[128];
  uint8_t again[128];

  any_series_information_basic_message(&sent);
  assert(encode_series_information_basic_message(&sent, wire, 0) == 128);
  assert(decode_series_information_basic_message(&got, wire, 0) == 128);
  equal_series_information_basic_message(&got, &sent);

  for (size_t i = 0; i < 128; i++) { wire[i] = arbitrary(); }
  assert(decode_series_information_basic_message(&got, wire, 0) == 128);
  assert(encode_series_information_basic_message(&got, again, 0) == 128);
  for (size_t i = 0; i < 128; i++) { assert(again[i] == wire[i]); }
}

/* ---- Series Information Basic Combination Message: 17 bytes ------------------ */

/* Provides detailed data about the legs of combination trading instruments that can be traded on a given trading day. */
typedef struct {
  uint8_t nanoseconds[4];                /* bytes 0 to 3 */
  uint8_t combination_order_book_id[4];  /* bytes 4 to 7 */
  uint8_t leg_order_book_id[4];          /* bytes 8 to 11 */
  uint8_t leg_side;                      /* byte 12 */
  uint8_t leg_ratio[4];                  /* bytes 13 to 16 */
} SeriesInformationBasicCombinationMessage;

/* any Series Information Basic Combination Message at all: every byte one the checker chooses */
static void any_series_information_basic_combination_message(SeriesInformationBasicCombinationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->combination_order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_order_book_id[i] = arbitrary(); }
  record->leg_side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leg_ratio[i] = arbitrary(); }
}

/* Series Information Basic Combination Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_series_information_basic_combination_message(const SeriesInformationBasicCombinationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->combination_order_book_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_order_book_id[i]; }
  wire[at++] = record->leg_side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio[i]; }

  return at;
}

/* Series Information Basic Combination Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_series_information_basic_combination_message(SeriesInformationBasicCombinationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->combination_order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_order_book_id[i] = wire[at++]; }
  record->leg_side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leg_ratio[i] = wire[at++]; }

  return at;
}

/* what was read of Series Information Basic Combination Message is what was written, byte for byte */
static void equal_series_information_basic_combination_message(const SeriesInformationBasicCombinationMessage *read, const SeriesInformationBasicCombinationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->combination_order_book_id[i] == written->combination_order_book_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_order_book_id[i] == written->leg_order_book_id[i]); }
  assert(read->leg_side == written->leg_side);
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio[i] == written->leg_ratio[i]); }
}

/* Series Information Basic Combination Message: written and read back, then read and written back */
static void check_series_information_basic_combination_message(void) {
  SeriesInformationBasicCombinationMessage sent;
  SeriesInformationBasicCombinationMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_series_information_basic_combination_message(&sent);
  assert(encode_series_information_basic_combination_message(&sent, wire, 0) == 17);
  assert(decode_series_information_basic_combination_message(&got, wire, 0) == 17);
  equal_series_information_basic_combination_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_series_information_basic_combination_message(&got, wire, 0) == 17);
  assert(encode_series_information_basic_combination_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tick Size Data Message: 24 bytes ---------------------------------------- */

/* Provides the tick size of a trading instrument. */
typedef struct {
  uint8_t nanoseconds[4];    /* bytes 0 to 3 */
  uint8_t order_book_id[4];  /* bytes 4 to 7 */
  uint8_t tick_size[8];      /* bytes 8 to 15 */
  uint8_t price_from[4];     /* bytes 16 to 19 */
  uint8_t price_to[4];       /* bytes 20 to 23 */
} TickSizeDataMessage;

/* any Tick Size Data Message at all: every byte one the checker chooses */
static void any_tick_size_data_message(TickSizeDataMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_from[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_to[i] = arbitrary(); }
}

/* Tick Size Data Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_tick_size_data_message(const TickSizeDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->tick_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_from[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_to[i]; }

  return at;
}

/* Tick Size Data Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_tick_size_data_message(TickSizeDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_from[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_to[i] = wire[at++]; }

  return at;
}

/* what was read of Tick Size Data Message is what was written, byte for byte */
static void equal_tick_size_data_message(const TickSizeDataMessage *read, const TickSizeDataMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->tick_size[i] == written->tick_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_from[i] == written->price_from[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_to[i] == written->price_to[i]); }
}

/* Tick Size Data Message: written and read back, then read and written back */
static void check_tick_size_data_message(void) {
  TickSizeDataMessage sent;
  TickSizeDataMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_tick_size_data_message(&sent);
  assert(encode_tick_size_data_message(&sent, wire, 0) == 24);
  assert(decode_tick_size_data_message(&got, wire, 0) == 24);
  equal_tick_size_data_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_tick_size_data_message(&got, wire, 0) == 24);
  assert(encode_tick_size_data_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Data Message: 5 bytes -------------------------------------- */

/* Provides system event update data. */
typedef struct {
  uint8_t nanoseconds[4];  /* bytes 0 to 3 */
  uint8_t event_code;      /* byte 4 */
} SystemEventDataMessage;

/* any System Event Data Message at all: every byte one the checker chooses */
static void any_system_event_data_message(SystemEventDataMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  record->event_code = arbitrary();
}

/* System Event Data Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_system_event_data_message(const SystemEventDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  wire[at++] = record->event_code;

  return at;
}

/* System Event Data Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_system_event_data_message(SystemEventDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  record->event_code = wire[at++];

  return at;
}

/* what was read of System Event Data Message is what was written, byte for byte */
static void equal_system_event_data_message(const SystemEventDataMessage *read, const SystemEventDataMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  assert(read->event_code == written->event_code);
}

/* System Event Data Message: written and read back, then read and written back */
static void check_system_event_data_message(void) {
  SystemEventDataMessage sent;
  SystemEventDataMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_system_event_data_message(&sent);
  assert(encode_system_event_data_message(&sent, wire, 0) == 5);
  assert(decode_system_event_data_message(&got, wire, 0) == 5);
  equal_system_event_data_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_data_message(&got, wire, 0) == 5);
  assert(encode_system_event_data_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Data Message: 28 bytes ----------------------------------- */

/* Provides the trading status data of a trading instrument. */
typedef struct {
  uint8_t nanoseconds[4];    /* bytes 0 to 3 */
  uint8_t order_book_id[4];  /* bytes 4 to 7 */
  uint8_t state_name[20];    /* bytes 8 to 27 */
} TradingStatusDataMessage;

/* any Trading Status Data Message at all: every byte one the checker chooses */
static void any_trading_status_data_message(TradingStatusDataMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->state_name[i] = arbitrary(); }
}

/* Trading Status Data Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_data_message(const TradingStatusDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->state_name[i]; }

  return at;
}

/* Trading Status Data Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_data_message(TradingStatusDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->state_name[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Status Data Message is what was written, byte for byte */
static void equal_trading_status_data_message(const TradingStatusDataMessage *read, const TradingStatusDataMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->state_name[i] == written->state_name[i]); }
}

/* Trading Status Data Message: written and read back, then read and written back */
static void check_trading_status_data_message(void) {
  TradingStatusDataMessage sent;
  TradingStatusDataMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_trading_status_data_message(&sent);
  assert(encode_trading_status_data_message(&sent, wire, 0) == 28);
  assert(decode_trading_status_data_message(&got, wire, 0) == 28);
  equal_trading_status_data_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_data_message(&got, wire, 0) == 28);
  assert(encode_trading_status_data_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Message: 36 bytes --------------------------------------------- */

/* Provides quote data related to a new order. */
typedef struct {
  uint8_t nanoseconds[4];          /* bytes 0 to 3 */
  uint8_t order_id[8];             /* bytes 4 to 11 */
  uint8_t order_book_id[4];        /* bytes 12 to 15 */
  uint8_t side;                    /* byte 16 */
  uint8_t order_book_position[4];  /* bytes 17 to 20 */
  uint8_t quantity[8];             /* bytes 21 to 28 */
  uint8_t price[4];                /* bytes 29 to 32 */
  uint8_t order_attributes[2];     /* bytes 33 to 34 */
  uint8_t lot_type;                /* byte 35 */
} NewOrderMessage;

/* any New Order Message at all: every byte one the checker chooses */
static void any_new_order_message(NewOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_book_position[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->order_attributes[i] = arbitrary(); }
  record->lot_type = arbitrary();
}

/* New Order Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_new_order_message(const NewOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_position[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->order_attributes[i]; }
  wire[at++] = record->lot_type;

  return at;
}

/* New Order Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_new_order_message(NewOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_book_position[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->order_attributes[i] = wire[at++]; }
  record->lot_type = wire[at++];

  return at;
}

/* what was read of New Order Message is what was written, byte for byte */
static void equal_new_order_message(const NewOrderMessage *read, const NewOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_position[i] == written->order_book_position[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->order_attributes[i] == written->order_attributes[i]); }
  assert(read->lot_type == written->lot_type);
}

/* New Order Message: written and read back, then read and written back */
static void check_new_order_message(void) {
  NewOrderMessage sent;
  NewOrderMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_new_order_message(&sent);
  assert(encode_new_order_message(&sent, wire, 0) == 36);
  assert(decode_new_order_message(&got, wire, 0) == 36);
  equal_new_order_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_message(&got, wire, 0) == 36);
  assert(encode_new_order_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Notice Message: 51 bytes -------------------------------------- */

/* Provides an execution notice. The Order ID of the order which is already in the order book is set. */
typedef struct {
  uint8_t nanoseconds[4];        /* bytes 0 to 3 */
  uint8_t order_id[8];           /* bytes 4 to 11 */
  uint8_t order_book_id[4];      /* bytes 12 to 15 */
  uint8_t side;                  /* byte 16 */
  uint8_t executed_quantity[8];  /* bytes 17 to 24 */
  uint8_t match_id[8];           /* bytes 25 to 32 */
  uint8_t combo_group_id[4];     /* bytes 33 to 36 */
  uint8_t reserved_7_a[7];       /* bytes 37 to 43 */
  uint8_t reserved_7_b[7];       /* bytes 44 to 50 */
} ExecutionNoticeMessage;

/* any Execution Notice Message at all: every byte one the checker chooses */
static void any_execution_notice_message(ExecutionNoticeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->combo_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->reserved_7_a[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->reserved_7_b[i] = arbitrary(); }
}

/* Execution Notice Message to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_execution_notice_message(const ExecutionNoticeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->combo_group_id[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->reserved_7_a[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->reserved_7_b[i]; }

  return at;
}

/* Execution Notice Message off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_execution_notice_message(ExecutionNoticeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->combo_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->reserved_7_a[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->reserved_7_b[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Notice Message is what was written, byte for byte */
static void equal_execution_notice_message(const ExecutionNoticeMessage *read, const ExecutionNoticeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->combo_group_id[i] == written->combo_group_id[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->reserved_7_a[i] == written->reserved_7_a[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->reserved_7_b[i] == written->reserved_7_b[i]); }
}

/* Execution Notice Message: written and read back, then read and written back */
static void check_execution_notice_message(void) {
  ExecutionNoticeMessage sent;
  ExecutionNoticeMessage got;
  uint8_t wire[51];
  uint8_t again[51];

  any_execution_notice_message(&sent);
  assert(encode_execution_notice_message(&sent, wire, 0) == 51);
  assert(decode_execution_notice_message(&got, wire, 0) == 51);
  equal_execution_notice_message(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_notice_message(&got, wire, 0) == 51);
  assert(encode_execution_notice_message(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Notice With Trade Information Message: 57 bytes --------------- */

/* Provides an execution notice with trade information. */
typedef struct {
  uint8_t nanoseconds[4];        /* bytes 0 to 3 */
  uint8_t order_id[8];           /* bytes 4 to 11 */
  uint8_t order_book_id[4];      /* bytes 12 to 15 */
  uint8_t side;                  /* byte 16 */
  uint8_t executed_quantity[8];  /* bytes 17 to 24 */
  uint8_t match_id[8];           /* bytes 25 to 32 */
  uint8_t combo_group_id[4];     /* bytes 33 to 36 */
  uint8_t reserved_7_a[7];       /* bytes 37 to 43 */
  uint8_t reserved_7_b[7];       /* bytes 44 to 50 */
  uint8_t trade_price[4];        /* bytes 51 to 54 */
  uint8_t occurred_at_cross;     /* byte 55 */
  uint8_t printable;             /* byte 56 */
} ExecutionNoticeWithTradeInformationMessage;

/* any Execution Notice With Trade Information Message at all: every byte one the checker chooses */
static void any_execution_notice_with_trade_information_message(ExecutionNoticeWithTradeInformationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->combo_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->reserved_7_a[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->reserved_7_b[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  record->occurred_at_cross = arbitrary();
  record->printable = arbitrary();
}

/* Execution Notice With Trade Information Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_execution_notice_with_trade_information_message(const ExecutionNoticeWithTradeInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->match_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->combo_group_id[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->reserved_7_a[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->reserved_7_b[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  wire[at++] = record->occurred_at_cross;
  wire[at++] = record->printable;

  return at;
}

/* Execution Notice With Trade Information Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_execution_notice_with_trade_information_message(ExecutionNoticeWithTradeInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->combo_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->reserved_7_a[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->reserved_7_b[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  record->occurred_at_cross = wire[at++];
  record->printable = wire[at++];

  return at;
}

/* what was read of Execution Notice With Trade Information Message is what was written, byte for byte */
static void equal_execution_notice_with_trade_information_message(const ExecutionNoticeWithTradeInformationMessage *read, const ExecutionNoticeWithTradeInformationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->match_id[i] == written->match_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->combo_group_id[i] == written->combo_group_id[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->reserved_7_a[i] == written->reserved_7_a[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->reserved_7_b[i] == written->reserved_7_b[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  assert(read->occurred_at_cross == written->occurred_at_cross);
  assert(read->printable == written->printable);
}

/* Execution Notice With Trade Information Message: written and read back, then read and written back */
static void check_execution_notice_with_trade_information_message(void) {
  ExecutionNoticeWithTradeInformationMessage sent;
  ExecutionNoticeWithTradeInformationMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_execution_notice_with_trade_information_message(&sent);
  assert(encode_execution_notice_with_trade_information_message(&sent, wire, 0) == 57);
  assert(decode_execution_notice_with_trade_information_message(&got, wire, 0) == 57);
  equal_execution_notice_with_trade_information_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_notice_with_trade_information_message(&got, wire, 0) == 57);
  assert(encode_execution_notice_with_trade_information_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Deleted Order Message: 17 bytes ----------------------------------------- */

/* Provided when an order is deleted and does not exist in the order book. */
typedef struct {
  uint8_t nanoseconds[4];    /* bytes 0 to 3 */
  uint8_t order_id[8];       /* bytes 4 to 11 */
  uint8_t order_book_id[4];  /* bytes 12 to 15 */
  uint8_t side;              /* byte 16 */
} DeletedOrderMessage;

/* any Deleted Order Message at all: every byte one the checker chooses */
static void any_deleted_order_message(DeletedOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  record->side = arbitrary();
}

/* Deleted Order Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_deleted_order_message(const DeletedOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  wire[at++] = record->side;

  return at;
}

/* Deleted Order Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_deleted_order_message(DeletedOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  record->side = wire[at++];

  return at;
}

/* what was read of Deleted Order Message is what was written, byte for byte */
static void equal_deleted_order_message(const DeletedOrderMessage *read, const DeletedOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  assert(read->side == written->side);
}

/* Deleted Order Message: written and read back, then read and written back */
static void check_deleted_order_message(void) {
  DeletedOrderMessage sent;
  DeletedOrderMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_deleted_order_message(&sent);
  assert(encode_deleted_order_message(&sent, wire, 0) == 17);
  assert(decode_deleted_order_message(&got, wire, 0) == 17);
  equal_deleted_order_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_deleted_order_message(&got, wire, 0) == 17);
  assert(encode_deleted_order_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ep Message: 52 bytes ---------------------------------------------------- */

/* Provides the equilibrium price for the order reception hours. */
typedef struct {
  uint8_t nanoseconds[4];                                  /* bytes 0 to 3 */
  uint8_t order_book_id[4];                                /* bytes 4 to 7 */
  uint8_t available_bid_quantity_at_equilibrium_price[8];  /* bytes 8 to 15 */
  uint8_t available_ask_quantity_at_equilibrium_price[8];  /* bytes 16 to 23 */
  uint8_t equilibrium_price[4];                            /* bytes 24 to 27 */
  uint8_t reserved_4_a[4];                                 /* bytes 28 to 31 */
  uint8_t reserved_4_b[4];                                 /* bytes 32 to 35 */
  uint8_t reserved_8_a[8];                                 /* bytes 36 to 43 */
  uint8_t reserved_8_b[8];                                 /* bytes 44 to 51 */
} EpMessage;

/* any Ep Message at all: every byte one the checker chooses */
static void any_ep_message(EpMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->available_bid_quantity_at_equilibrium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->available_ask_quantity_at_equilibrium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->equilibrium_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_a[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_b[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8_a[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8_b[i] = arbitrary(); }
}

/* Ep Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_ep_message(const EpMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->available_bid_quantity_at_equilibrium_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->available_ask_quantity_at_equilibrium_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->equilibrium_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4_a[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4_b[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8_a[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8_b[i]; }

  return at;
}

/* Ep Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_ep_message(EpMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->available_bid_quantity_at_equilibrium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->available_ask_quantity_at_equilibrium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->equilibrium_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_a[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4_b[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8_a[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8_b[i] = wire[at++]; }

  return at;
}

/* what was read of Ep Message is what was written, byte for byte */
static void equal_ep_message(const EpMessage *read, const EpMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book_id[i] == written->order_book_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->available_bid_quantity_at_equilibrium_price[i] == written->available_bid_quantity_at_equilibrium_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->available_ask_quantity_at_equilibrium_price[i] == written->available_ask_quantity_at_equilibrium_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->equilibrium_price[i] == written->equilibrium_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4_a[i] == written->reserved_4_a[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4_b[i] == written->reserved_4_b[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8_a[i] == written->reserved_8_a[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8_b[i] == written->reserved_8_b[i]); }
}

/* Ep Message: written and read back, then read and written back */
static void check_ep_message(void) {
  EpMessage sent;
  EpMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_ep_message(&sent);
  assert(encode_ep_message(&sent, wire, 0) == 52);
  assert(decode_ep_message(&got, wire, 0) == 52);
  equal_ep_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_ep_message(&got, wire, 0) == 52);
  assert(encode_ep_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Completion Message: 20 bytes ----------------------------------- */

/* Sent after completing the transmission of snapshot data. */
typedef struct {
  uint8_t sequence[20];  /* bytes 0 to 19 */
} SnapshotCompletionMessage;

/* any Snapshot Completion Message at all: every byte one the checker chooses */
static void any_snapshot_completion_message(SnapshotCompletionMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->sequence[i] = arbitrary(); }
}

/* Snapshot Completion Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_completion_message(const SnapshotCompletionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Snapshot Completion Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_completion_message(SnapshotCompletionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Snapshot Completion Message is what was written, byte for byte */
static void equal_snapshot_completion_message(const SnapshotCompletionMessage *read, const SnapshotCompletionMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Snapshot Completion Message: written and read back, then read and written back */
static void check_snapshot_completion_message(void) {
  SnapshotCompletionMessage sent;
  SnapshotCompletionMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_snapshot_completion_message(&sent);
  assert(encode_snapshot_completion_message(&sent, wire, 0) == 20);
  assert(decode_snapshot_completion_message(&got, wire, 0) == 20);
  equal_snapshot_completion_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_completion_message(&got, wire, 0) == 20);
  assert(encode_snapshot_completion_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_seconds_message();
  check_series_information_basic_message();
  check_series_information_basic_combination_message();
  check_tick_size_data_message();
  check_system_event_data_message();
  check_trading_status_data_message();
  check_new_order_message();
  check_execution_notice_message();
  check_execution_notice_with_trade_information_message();
  check_deleted_order_message();
  check_ep_message();
  check_snapshot_completion_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
