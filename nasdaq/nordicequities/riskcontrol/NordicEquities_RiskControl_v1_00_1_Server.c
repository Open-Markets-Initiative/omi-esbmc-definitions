// nasdaq/nordicequities/riskcontrol/NordicEquities_RiskControl_v1_00_1_Server.c
/*
 * National Association of Securities Dealers Automated Quotations (Nasdaq) Nordic Pre-Trade Risk Management
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

/* ---- Account Query Response Message: 4 bytes --------------------------------- */

/* Provides the PRM API port's next expected user reference number */
typedef struct {
  uint8_t user_ref_num[4];  /* bytes 0 to 3 */
} AccountQueryResponseMessage;

/* any Account Query Response Message at all: every byte one the checker chooses */
static void any_account_query_response_message(AccountQueryResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = arbitrary(); }
}

/* Account Query Response Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_account_query_response_message(const AccountQueryResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_ref_num[i]; }

  return at;
}

/* Account Query Response Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_account_query_response_message(AccountQueryResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = wire[at++]; }

  return at;
}

/* what was read of Account Query Response Message is what was written, byte for byte */
static void equal_account_query_response_message(const AccountQueryResponseMessage *read, const AccountQueryResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_ref_num[i] == written->user_ref_num[i]); }
}

/* Account Query Response Message: written and read back, then read and written back */
static void check_account_query_response_message(void) {
  AccountQueryResponseMessage sent;
  AccountQueryResponseMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_account_query_response_message(&sent);
  assert(encode_account_query_response_message(&sent, wire, 0) == 4);
  assert(decode_account_query_response_message(&got, wire, 0) == 4);
  equal_account_query_response_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_account_query_response_message(&got, wire, 0) == 4);
  assert(encode_account_query_response_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Account Settings Response Message: 19 bytes ----------------------------- */

/* Indicates that the settings for a given PRM Account have been updated */
typedef struct {
  uint8_t user_ref_num[4];                                       /* bytes 0 to 3 */
  uint8_t prm_account[6];                                        /* bytes 4 to 9 */
  uint8_t repeated_order_generation[4];                          /* bytes 10 to 13 */
  uint8_t trigger_restrict_symbol_on_repeated_order_generation;  /* byte 14 */
  uint8_t in_auction_market_order_prevention;                    /* byte 15 */
  uint8_t in_auction_fat_finger_protection;                      /* byte 16 */
  uint8_t in_auction_market_order_protection;                    /* byte 17 */
  uint8_t block_and_cancel;                                      /* byte 18 */
} AccountSettingsResponseMessage;

/* any Account Settings Response Message at all: every byte one the checker chooses */
static void any_account_settings_response_message(AccountSettingsResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->repeated_order_generation[i] = arbitrary(); }
  record->trigger_restrict_symbol_on_repeated_order_generation = arbitrary();
  record->in_auction_market_order_prevention = arbitrary();
  record->in_auction_fat_finger_protection = arbitrary();
  record->in_auction_market_order_protection = arbitrary();
  record->block_and_cancel = arbitrary();
}

/* Account Settings Response Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_account_settings_response_message(const AccountSettingsResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_ref_num[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->prm_account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->repeated_order_generation[i]; }
  wire[at++] = record->trigger_restrict_symbol_on_repeated_order_generation;
  wire[at++] = record->in_auction_market_order_prevention;
  wire[at++] = record->in_auction_fat_finger_protection;
  wire[at++] = record->in_auction_market_order_protection;
  wire[at++] = record->block_and_cancel;

  return at;
}

/* Account Settings Response Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_account_settings_response_message(AccountSettingsResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->repeated_order_generation[i] = wire[at++]; }
  record->trigger_restrict_symbol_on_repeated_order_generation = wire[at++];
  record->in_auction_market_order_prevention = wire[at++];
  record->in_auction_fat_finger_protection = wire[at++];
  record->in_auction_market_order_protection = wire[at++];
  record->block_and_cancel = wire[at++];

  return at;
}

/* what was read of Account Settings Response Message is what was written, byte for byte */
static void equal_account_settings_response_message(const AccountSettingsResponseMessage *read, const AccountSettingsResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_ref_num[i] == written->user_ref_num[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->prm_account[i] == written->prm_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->repeated_order_generation[i] == written->repeated_order_generation[i]); }
  assert(read->trigger_restrict_symbol_on_repeated_order_generation == written->trigger_restrict_symbol_on_repeated_order_generation);
  assert(read->in_auction_market_order_prevention == written->in_auction_market_order_prevention);
  assert(read->in_auction_fat_finger_protection == written->in_auction_fat_finger_protection);
  assert(read->in_auction_market_order_protection == written->in_auction_market_order_protection);
  assert(read->block_and_cancel == written->block_and_cancel);
}

/* Account Settings Response Message: written and read back, then read and written back */
static void check_account_settings_response_message(void) {
  AccountSettingsResponseMessage sent;
  AccountSettingsResponseMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_account_settings_response_message(&sent);
  assert(encode_account_settings_response_message(&sent, wire, 0) == 19);
  assert(decode_account_settings_response_message(&got, wire, 0) == 19);
  equal_account_settings_response_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_account_settings_response_message(&got, wire, 0) == 19);
  assert(encode_account_settings_response_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book Restriction Response Message: 23 bytes ----------------------- */

/* Indicates that an Order Book has been restricted or non-restricted for a given PRM Account */
typedef struct {
  uint8_t user_ref_num[4];  /* bytes 0 to 3 */
  uint8_t timestamp[8];     /* bytes 4 to 11 */
  uint8_t prm_account[6];   /* bytes 12 to 17 */
  uint8_t order_book[4];    /* bytes 18 to 21 */
  uint8_t state;            /* byte 22 */
} OrderBookRestrictionResponseMessage;

/* any Order Book Restriction Response Message at all: every byte one the checker chooses */
static void any_order_book_restriction_response_message(OrderBookRestrictionResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = arbitrary(); }
  record->state = arbitrary();
}

/* Order Book Restriction Response Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_order_book_restriction_response_message(const OrderBookRestrictionResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_ref_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->prm_account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book[i]; }
  wire[at++] = record->state;

  return at;
}

/* Order Book Restriction Response Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_order_book_restriction_response_message(OrderBookRestrictionResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = wire[at++]; }
  record->state = wire[at++];

  return at;
}

/* what was read of Order Book Restriction Response Message is what was written, byte for byte */
static void equal_order_book_restriction_response_message(const OrderBookRestrictionResponseMessage *read, const OrderBookRestrictionResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_ref_num[i] == written->user_ref_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->prm_account[i] == written->prm_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book[i] == written->order_book[i]); }
  assert(read->state == written->state);
}

/* Order Book Restriction Response Message: written and read back, then read and written back */
static void check_order_book_restriction_response_message(void) {
  OrderBookRestrictionResponseMessage sent;
  OrderBookRestrictionResponseMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_order_book_restriction_response_message(&sent);
  assert(encode_order_book_restriction_response_message(&sent, wire, 0) == 23);
  assert(decode_order_book_restriction_response_message(&got, wire, 0) == 23);
  equal_order_book_restriction_response_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_restriction_response_message(&got, wire, 0) == 23);
  assert(encode_order_book_restriction_response_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Segment Restriction Response Message: 21 bytes ------------------- */

/* Indicates that a Market Segment has been restricted or non-restricted for a given PRM Account */
typedef struct {
  uint8_t user_ref_num[4];    /* bytes 0 to 3 */
  uint8_t timestamp[8];       /* bytes 4 to 11 */
  uint8_t prm_account[6];     /* bytes 12 to 17 */
  uint8_t market_segment[2];  /* bytes 18 to 19 */
  uint8_t state;              /* byte 20 */
} MarketSegmentRestrictionResponseMessage;

/* any Market Segment Restriction Response Message at all: every byte one the checker chooses */
static void any_market_segment_restriction_response_message(MarketSegmentRestrictionResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_segment[i] = arbitrary(); }
  record->state = arbitrary();
}

/* Market Segment Restriction Response Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_market_segment_restriction_response_message(const MarketSegmentRestrictionResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_ref_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->prm_account[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_segment[i]; }
  wire[at++] = record->state;

  return at;
}

/* Market Segment Restriction Response Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_market_segment_restriction_response_message(MarketSegmentRestrictionResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_segment[i] = wire[at++]; }
  record->state = wire[at++];

  return at;
}

/* what was read of Market Segment Restriction Response Message is what was written, byte for byte */
static void equal_market_segment_restriction_response_message(const MarketSegmentRestrictionResponseMessage *read, const MarketSegmentRestrictionResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_ref_num[i] == written->user_ref_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->prm_account[i] == written->prm_account[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_segment[i] == written->market_segment[i]); }
  assert(read->state == written->state);
}

/* Market Segment Restriction Response Message: written and read back, then read and written back */
static void check_market_segment_restriction_response_message(void) {
  MarketSegmentRestrictionResponseMessage sent;
  MarketSegmentRestrictionResponseMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_market_segment_restriction_response_message(&sent);
  assert(encode_market_segment_restriction_response_message(&sent, wire, 0) == 21);
  assert(decode_market_segment_restriction_response_message(&got, wire, 0) == 21);
  equal_market_segment_restriction_response_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_market_segment_restriction_response_message(&got, wire, 0) == 21);
  assert(encode_market_segment_restriction_response_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Limit Settings Response Message: 109 bytes ------------------------------ */

/* Indicates that the Limit settings for a given PRM Account and Currency have been updated */
typedef struct {
  uint8_t user_ref_num[4];           /* bytes 0 to 3 */
  uint8_t prm_account[6];            /* bytes 4 to 9 */
  uint8_t currency[3];               /* bytes 10 to 12 */
  uint8_t max_quantity[8];           /* bytes 13 to 20 */
  uint8_t max_value[8];              /* bytes 21 to 28 */
  uint8_t unused[8];                 /* bytes 29 to 36 */
  uint8_t total_risk_value[8];       /* bytes 37 to 44 */
  uint8_t trade_buy_value[8];        /* bytes 45 to 52 */
  uint8_t trade_sell_value[8];       /* bytes 53 to 60 */
  uint8_t trade_net_value[8];        /* bytes 61 to 68 */
  uint8_t open_order_buy_value[8];   /* bytes 69 to 76 */
  uint8_t open_order_sell_value[8];  /* bytes 77 to 84 */
  uint8_t open_order_net_value[8];   /* bytes 85 to 92 */
  uint8_t max_quantity_auction[8];   /* bytes 93 to 100 */
  uint8_t max_value_auction[8];      /* bytes 101 to 108 */
} LimitSettingsResponseMessage;

/* any Limit Settings Response Message at all: every byte one the checker chooses */
static void any_limit_settings_response_message(LimitSettingsResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->unused[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_risk_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_buy_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_sell_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_net_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_order_buy_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_order_sell_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_order_net_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_quantity_auction[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_value_auction[i] = arbitrary(); }
}

/* Limit Settings Response Message to the wire: 109 bytes from at, returning where the next byte goes */
static size_t encode_limit_settings_response_message(const LimitSettingsResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_ref_num[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->prm_account[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->unused[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_risk_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_buy_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_sell_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_net_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_order_buy_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_order_sell_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_order_net_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_quantity_auction[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_value_auction[i]; }

  return at;
}

/* Limit Settings Response Message off the wire: 109 bytes from at, returning where the next byte lies */
static size_t decode_limit_settings_response_message(LimitSettingsResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->unused[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_risk_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_buy_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_sell_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_net_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_order_buy_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_order_sell_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_order_net_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_quantity_auction[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_value_auction[i] = wire[at++]; }

  return at;
}

/* what was read of Limit Settings Response Message is what was written, byte for byte */
static void equal_limit_settings_response_message(const LimitSettingsResponseMessage *read, const LimitSettingsResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_ref_num[i] == written->user_ref_num[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->prm_account[i] == written->prm_account[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_quantity[i] == written->max_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_value[i] == written->max_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->unused[i] == written->unused[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_risk_value[i] == written->total_risk_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_buy_value[i] == written->trade_buy_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_sell_value[i] == written->trade_sell_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_net_value[i] == written->trade_net_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_order_buy_value[i] == written->open_order_buy_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_order_sell_value[i] == written->open_order_sell_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_order_net_value[i] == written->open_order_net_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_quantity_auction[i] == written->max_quantity_auction[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_value_auction[i] == written->max_value_auction[i]); }
}

/* Limit Settings Response Message: written and read back, then read and written back */
static void check_limit_settings_response_message(void) {
  LimitSettingsResponseMessage sent;
  LimitSettingsResponseMessage got;
  uint8_t wire[109];
  uint8_t again[109];

  any_limit_settings_response_message(&sent);
  assert(encode_limit_settings_response_message(&sent, wire, 0) == 109);
  assert(decode_limit_settings_response_message(&got, wire, 0) == 109);
  equal_limit_settings_response_message(&got, &sent);

  for (size_t i = 0; i < 109; i++) { wire[i] = arbitrary(); }
  assert(decode_limit_settings_response_message(&got, wire, 0) == 109);
  assert(encode_limit_settings_response_message(&got, again, 0) == 109);
  for (size_t i = 0; i < 109; i++) { assert(again[i] == wire[i]); }
}

/* ---- Account Currency Setting Response Message: 15 bytes --------------------- */

/* Indicates that the settings for a given PRM Account's currency have been updated */
typedef struct {
  uint8_t user_ref_num[4];          /* bytes 0 to 3 */
  uint8_t prm_account[6];           /* bytes 4 to 9 */
  uint8_t currency[3];              /* bytes 10 to 12 */
  uint8_t reject_all_flag;          /* byte 13 */
  uint8_t blow_through_protection;  /* byte 14 */
} AccountCurrencySettingResponseMessage;

/* any Account Currency Setting Response Message at all: every byte one the checker chooses */
static void any_account_currency_setting_response_message(AccountCurrencySettingResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  record->reject_all_flag = arbitrary();
  record->blow_through_protection = arbitrary();
}

/* Account Currency Setting Response Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_account_currency_setting_response_message(const AccountCurrencySettingResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_ref_num[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->prm_account[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->reject_all_flag;
  wire[at++] = record->blow_through_protection;

  return at;
}

/* Account Currency Setting Response Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_account_currency_setting_response_message(AccountCurrencySettingResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  record->reject_all_flag = wire[at++];
  record->blow_through_protection = wire[at++];

  return at;
}

/* what was read of Account Currency Setting Response Message is what was written, byte for byte */
static void equal_account_currency_setting_response_message(const AccountCurrencySettingResponseMessage *read, const AccountCurrencySettingResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_ref_num[i] == written->user_ref_num[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->prm_account[i] == written->prm_account[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->reject_all_flag == written->reject_all_flag);
  assert(read->blow_through_protection == written->blow_through_protection);
}

/* Account Currency Setting Response Message: written and read back, then read and written back */
static void check_account_currency_setting_response_message(void) {
  AccountCurrencySettingResponseMessage sent;
  AccountCurrencySettingResponseMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_account_currency_setting_response_message(&sent);
  assert(encode_account_currency_setting_response_message(&sent, wire, 0) == 15);
  assert(decode_account_currency_setting_response_message(&got, wire, 0) == 15);
  equal_account_currency_setting_response_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_account_currency_setting_response_message(&got, wire, 0) == 15);
  assert(encode_account_currency_setting_response_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reject Message: 5 bytes ------------------------------------------------- */

/* Indicates that an inbound message has been rejected */
typedef struct {
  uint8_t user_ref_num[4];  /* bytes 0 to 3 */
  uint8_t reason;           /* byte 4 */
} RejectMessage;

/* any Reject Message at all: every byte one the checker chooses */
static void any_reject_message(RejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = arbitrary(); }
  record->reason = arbitrary();
}

/* Reject Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_reject_message(const RejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_ref_num[i]; }
  wire[at++] = record->reason;

  return at;
}

/* Reject Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_reject_message(RejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = wire[at++]; }
  record->reason = wire[at++];

  return at;
}

/* what was read of Reject Message is what was written, byte for byte */
static void equal_reject_message(const RejectMessage *read, const RejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_ref_num[i] == written->user_ref_num[i]); }
  assert(read->reason == written->reason);
}

/* Reject Message: written and read back, then read and written back */
static void check_reject_message(void) {
  RejectMessage sent;
  RejectMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_reject_message(&sent);
  assert(encode_reject_message(&sent, wire, 0) == 5);
  assert(decode_reject_message(&got, wire, 0) == 5);
  equal_reject_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_reject_message(&got, wire, 0) == 5);
  assert(encode_reject_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Api Port Rate Breach Message: 8 bytes ----------------------------------- */

/* Indicates that the port's rate limit has been breached */
typedef struct {
  uint8_t timestamp[8];  /* bytes 0 to 7 */
} ApiPortRateBreachMessage;

/* any Api Port Rate Breach Message at all: every byte one the checker chooses */
static void any_api_port_rate_breach_message(ApiPortRateBreachMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* Api Port Rate Breach Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_api_port_rate_breach_message(const ApiPortRateBreachMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* Api Port Rate Breach Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_api_port_rate_breach_message(ApiPortRateBreachMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Api Port Rate Breach Message is what was written, byte for byte */
static void equal_api_port_rate_breach_message(const ApiPortRateBreachMessage *read, const ApiPortRateBreachMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
}

/* Api Port Rate Breach Message: written and read back, then read and written back */
static void check_api_port_rate_breach_message(void) {
  ApiPortRateBreachMessage sent;
  ApiPortRateBreachMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_api_port_rate_breach_message(&sent);
  assert(encode_api_port_rate_breach_message(&sent, wire, 0) == 8);
  assert(decode_api_port_rate_breach_message(&got, wire, 0) == 8);
  equal_api_port_rate_breach_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_api_port_rate_breach_message(&got, wire, 0) == 8);
  assert(encode_api_port_rate_breach_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Account Rate Breach Message: 15 bytes ----------------------------------- */

/* Indicates that a PRM Account's rate limit has been breached */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t state;           /* byte 8 */
  uint8_t prm_account[6];  /* bytes 9 to 14 */
} AccountRateBreachMessage;

/* any Account Rate Breach Message at all: every byte one the checker chooses */
static void any_account_rate_breach_message(AccountRateBreachMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  record->state = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = arbitrary(); }
}

/* Account Rate Breach Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_account_rate_breach_message(const AccountRateBreachMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->state;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->prm_account[i]; }

  return at;
}

/* Account Rate Breach Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_account_rate_breach_message(AccountRateBreachMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  record->state = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = wire[at++]; }

  return at;
}

/* what was read of Account Rate Breach Message is what was written, byte for byte */
static void equal_account_rate_breach_message(const AccountRateBreachMessage *read, const AccountRateBreachMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->state == written->state);
  for (size_t i = 0; i < 6; i++) { assert(read->prm_account[i] == written->prm_account[i]); }
}

/* Account Rate Breach Message: written and read back, then read and written back */
static void check_account_rate_breach_message(void) {
  AccountRateBreachMessage sent;
  AccountRateBreachMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_account_rate_breach_message(&sent);
  assert(encode_account_rate_breach_message(&sent, wire, 0) == 15);
  assert(decode_account_rate_breach_message(&got, wire, 0) == 15);
  equal_account_rate_breach_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_account_rate_breach_message(&got, wire, 0) == 15);
  assert(encode_account_rate_breach_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Accumulated Values Message: 73 bytes ------------------------------------ */

/* Indicates the current Accumulated Values for a PRM Account and Currency, sent after order or trade updates */
typedef struct {
  uint8_t prm_account[6];         /* bytes 0 to 5 */
  uint8_t currency[3];            /* bytes 6 to 8 */
  uint8_t last_update_time[8];    /* bytes 9 to 16 */
  uint8_t risk_total_value[8];    /* bytes 17 to 24 */
  uint8_t trades_buy_value[8];    /* bytes 25 to 32 */
  uint8_t trades_sell_value[8];   /* bytes 33 to 40 */
  uint8_t trades_total_value[8];  /* bytes 41 to 48 */
  uint8_t orders_buy_value[8];    /* bytes 49 to 56 */
  uint8_t orders_sell_value[8];   /* bytes 57 to 64 */
  uint8_t orders_total_value[8];  /* bytes 65 to 72 */
} AccumulatedValuesMessage;

/* any Accumulated Values Message at all: every byte one the checker chooses */
static void any_accumulated_values_message(AccumulatedValuesMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_update_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->risk_total_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trades_buy_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trades_sell_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trades_total_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orders_buy_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orders_sell_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orders_total_value[i] = arbitrary(); }
}

/* Accumulated Values Message to the wire: 73 bytes from at, returning where the next byte goes */
static size_t encode_accumulated_values_message(const AccumulatedValuesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->prm_account[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_update_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->risk_total_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trades_buy_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trades_sell_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trades_total_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orders_buy_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orders_sell_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orders_total_value[i]; }

  return at;
}

/* Accumulated Values Message off the wire: 73 bytes from at, returning where the next byte lies */
static size_t decode_accumulated_values_message(AccumulatedValuesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_update_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->risk_total_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trades_buy_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trades_sell_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trades_total_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orders_buy_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orders_sell_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orders_total_value[i] = wire[at++]; }

  return at;
}

/* what was read of Accumulated Values Message is what was written, byte for byte */
static void equal_accumulated_values_message(const AccumulatedValuesMessage *read, const AccumulatedValuesMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->prm_account[i] == written->prm_account[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_update_time[i] == written->last_update_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->risk_total_value[i] == written->risk_total_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trades_buy_value[i] == written->trades_buy_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trades_sell_value[i] == written->trades_sell_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trades_total_value[i] == written->trades_total_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orders_buy_value[i] == written->orders_buy_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orders_sell_value[i] == written->orders_sell_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orders_total_value[i] == written->orders_total_value[i]); }
}

/* Accumulated Values Message: written and read back, then read and written back */
static void check_accumulated_values_message(void) {
  AccumulatedValuesMessage sent;
  AccumulatedValuesMessage got;
  uint8_t wire[73];
  uint8_t again[73];

  any_accumulated_values_message(&sent);
  assert(encode_accumulated_values_message(&sent, wire, 0) == 73);
  assert(decode_accumulated_values_message(&got, wire, 0) == 73);
  equal_accumulated_values_message(&got, &sent);

  for (size_t i = 0; i < 73; i++) { wire[i] = arbitrary(); }
  assert(decode_accumulated_values_message(&got, wire, 0) == 73);
  assert(encode_accumulated_values_message(&got, again, 0) == 73);
  for (size_t i = 0; i < 73; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_server_packet_header();
  check_login_accepted_packet();
  check_login_rejected_packet();
  check_account_query_response_message();
  check_account_settings_response_message();
  check_order_book_restriction_response_message();
  check_market_segment_restriction_response_message();
  check_limit_settings_response_message();
  check_account_currency_setting_response_message();
  check_reject_message();
  check_api_port_rate_breach_message();
  check_account_rate_breach_message();
  check_accumulated_values_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
