// nasdaq/nordicequities/riskcontrol/NordicEquities_RiskControl_v1_00_1_Client.c
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

/* ---- Modify Account Settings Message: 19 bytes ------------------------------- */

/* Updates the settings for a given PRM Account */
typedef struct {
  uint8_t user_ref_num[4];                                       /* bytes 0 to 3 */
  uint8_t prm_account[6];                                        /* bytes 4 to 9 */
  uint8_t repeated_order_generation[4];                          /* bytes 10 to 13 */
  uint8_t trigger_restrict_symbol_on_repeated_order_generation;  /* byte 14 */
  uint8_t in_auction_market_order_prevention;                    /* byte 15 */
  uint8_t in_auction_fat_finger_protection;                      /* byte 16 */
  uint8_t in_auction_market_order_protection;                    /* byte 17 */
  uint8_t block_and_cancel;                                      /* byte 18 */
} ModifyAccountSettingsMessage;

/* any Modify Account Settings Message at all: every byte one the checker chooses */
static void any_modify_account_settings_message(ModifyAccountSettingsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->repeated_order_generation[i] = arbitrary(); }
  record->trigger_restrict_symbol_on_repeated_order_generation = arbitrary();
  record->in_auction_market_order_prevention = arbitrary();
  record->in_auction_fat_finger_protection = arbitrary();
  record->in_auction_market_order_protection = arbitrary();
  record->block_and_cancel = arbitrary();
}

/* Modify Account Settings Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_modify_account_settings_message(const ModifyAccountSettingsMessage *record, uint8_t *wire, size_t at) {
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

/* Modify Account Settings Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_modify_account_settings_message(ModifyAccountSettingsMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Modify Account Settings Message is what was written, byte for byte */
static void equal_modify_account_settings_message(const ModifyAccountSettingsMessage *read, const ModifyAccountSettingsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_ref_num[i] == written->user_ref_num[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->prm_account[i] == written->prm_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->repeated_order_generation[i] == written->repeated_order_generation[i]); }
  assert(read->trigger_restrict_symbol_on_repeated_order_generation == written->trigger_restrict_symbol_on_repeated_order_generation);
  assert(read->in_auction_market_order_prevention == written->in_auction_market_order_prevention);
  assert(read->in_auction_fat_finger_protection == written->in_auction_fat_finger_protection);
  assert(read->in_auction_market_order_protection == written->in_auction_market_order_protection);
  assert(read->block_and_cancel == written->block_and_cancel);
}

/* Modify Account Settings Message: written and read back, then read and written back */
static void check_modify_account_settings_message(void) {
  ModifyAccountSettingsMessage sent;
  ModifyAccountSettingsMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_modify_account_settings_message(&sent);
  assert(encode_modify_account_settings_message(&sent, wire, 0) == 19);
  assert(decode_modify_account_settings_message(&got, wire, 0) == 19);
  equal_modify_account_settings_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_account_settings_message(&got, wire, 0) == 19);
  assert(encode_modify_account_settings_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Book Restriction Message: 15 bytes ------------------------- */

/* Marks an Order Book as restricted or non-restricted for a given PRM Account */
typedef struct {
  uint8_t user_ref_num[4];  /* bytes 0 to 3 */
  uint8_t prm_account[6];   /* bytes 4 to 9 */
  uint8_t order_book[4];    /* bytes 10 to 13 */
  uint8_t state;            /* byte 14 */
} ModifyOrderBookRestrictionMessage;

/* any Modify Order Book Restriction Message at all: every byte one the checker chooses */
static void any_modify_order_book_restriction_message(ModifyOrderBookRestrictionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = arbitrary(); }
  record->state = arbitrary();
}

/* Modify Order Book Restriction Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_book_restriction_message(const ModifyOrderBookRestrictionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_ref_num[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->prm_account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_book[i]; }
  wire[at++] = record->state;

  return at;
}

/* Modify Order Book Restriction Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_book_restriction_message(ModifyOrderBookRestrictionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_book[i] = wire[at++]; }
  record->state = wire[at++];

  return at;
}

/* what was read of Modify Order Book Restriction Message is what was written, byte for byte */
static void equal_modify_order_book_restriction_message(const ModifyOrderBookRestrictionMessage *read, const ModifyOrderBookRestrictionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_ref_num[i] == written->user_ref_num[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->prm_account[i] == written->prm_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_book[i] == written->order_book[i]); }
  assert(read->state == written->state);
}

/* Modify Order Book Restriction Message: written and read back, then read and written back */
static void check_modify_order_book_restriction_message(void) {
  ModifyOrderBookRestrictionMessage sent;
  ModifyOrderBookRestrictionMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_modify_order_book_restriction_message(&sent);
  assert(encode_modify_order_book_restriction_message(&sent, wire, 0) == 15);
  assert(decode_modify_order_book_restriction_message(&got, wire, 0) == 15);
  equal_modify_order_book_restriction_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_book_restriction_message(&got, wire, 0) == 15);
  assert(encode_modify_order_book_restriction_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Market Segment Restriction Message: 13 bytes --------------------- */

/* Marks a Market Segment as restricted or non-restricted for a given PRM Account */
typedef struct {
  uint8_t user_ref_num[4];    /* bytes 0 to 3 */
  uint8_t prm_account[6];     /* bytes 4 to 9 */
  uint8_t market_segment[2];  /* bytes 10 to 11 */
  uint8_t state;              /* byte 12 */
} ModifyMarketSegmentRestrictionMessage;

/* any Modify Market Segment Restriction Message at all: every byte one the checker chooses */
static void any_modify_market_segment_restriction_message(ModifyMarketSegmentRestrictionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_segment[i] = arbitrary(); }
  record->state = arbitrary();
}

/* Modify Market Segment Restriction Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_modify_market_segment_restriction_message(const ModifyMarketSegmentRestrictionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_ref_num[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->prm_account[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_segment[i]; }
  wire[at++] = record->state;

  return at;
}

/* Modify Market Segment Restriction Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_modify_market_segment_restriction_message(ModifyMarketSegmentRestrictionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_segment[i] = wire[at++]; }
  record->state = wire[at++];

  return at;
}

/* what was read of Modify Market Segment Restriction Message is what was written, byte for byte */
static void equal_modify_market_segment_restriction_message(const ModifyMarketSegmentRestrictionMessage *read, const ModifyMarketSegmentRestrictionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_ref_num[i] == written->user_ref_num[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->prm_account[i] == written->prm_account[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_segment[i] == written->market_segment[i]); }
  assert(read->state == written->state);
}

/* Modify Market Segment Restriction Message: written and read back, then read and written back */
static void check_modify_market_segment_restriction_message(void) {
  ModifyMarketSegmentRestrictionMessage sent;
  ModifyMarketSegmentRestrictionMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_modify_market_segment_restriction_message(&sent);
  assert(encode_modify_market_segment_restriction_message(&sent, wire, 0) == 13);
  assert(decode_modify_market_segment_restriction_message(&got, wire, 0) == 13);
  equal_modify_market_segment_restriction_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_market_segment_restriction_message(&got, wire, 0) == 13);
  assert(encode_modify_market_segment_restriction_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Limit Settings Message: 109 bytes -------------------------------- */

/* Updates the Limit settings for a given PRM Account and Currency */
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
} ModifyLimitSettingsMessage;

/* any Modify Limit Settings Message at all: every byte one the checker chooses */
static void any_modify_limit_settings_message(ModifyLimitSettingsMessage *record) {
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

/* Modify Limit Settings Message to the wire: 109 bytes from at, returning where the next byte goes */
static size_t encode_modify_limit_settings_message(const ModifyLimitSettingsMessage *record, uint8_t *wire, size_t at) {
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

/* Modify Limit Settings Message off the wire: 109 bytes from at, returning where the next byte lies */
static size_t decode_modify_limit_settings_message(ModifyLimitSettingsMessage *record, const uint8_t *wire, size_t at) {
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

/* what was read of Modify Limit Settings Message is what was written, byte for byte */
static void equal_modify_limit_settings_message(const ModifyLimitSettingsMessage *read, const ModifyLimitSettingsMessage *written) {
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

/* Modify Limit Settings Message: written and read back, then read and written back */
static void check_modify_limit_settings_message(void) {
  ModifyLimitSettingsMessage sent;
  ModifyLimitSettingsMessage got;
  uint8_t wire[109];
  uint8_t again[109];

  any_modify_limit_settings_message(&sent);
  assert(encode_modify_limit_settings_message(&sent, wire, 0) == 109);
  assert(decode_modify_limit_settings_message(&got, wire, 0) == 109);
  equal_modify_limit_settings_message(&got, &sent);

  for (size_t i = 0; i < 109; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_limit_settings_message(&got, wire, 0) == 109);
  assert(encode_modify_limit_settings_message(&got, again, 0) == 109);
  for (size_t i = 0; i < 109; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Account Currency Setting Message: 15 bytes ----------------------- */

/* Updates the settings for a given PRM Account's currency */
typedef struct {
  uint8_t user_ref_num[4];          /* bytes 0 to 3 */
  uint8_t prm_account[6];           /* bytes 4 to 9 */
  uint8_t currency[3];              /* bytes 10 to 12 */
  uint8_t reject_all_flag;          /* byte 13 */
  uint8_t blow_through_protection;  /* byte 14 */
} ModifyAccountCurrencySettingMessage;

/* any Modify Account Currency Setting Message at all: every byte one the checker chooses */
static void any_modify_account_currency_setting_message(ModifyAccountCurrencySettingMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  record->reject_all_flag = arbitrary();
  record->blow_through_protection = arbitrary();
}

/* Modify Account Currency Setting Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_modify_account_currency_setting_message(const ModifyAccountCurrencySettingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_ref_num[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->prm_account[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  wire[at++] = record->reject_all_flag;
  wire[at++] = record->blow_through_protection;

  return at;
}

/* Modify Account Currency Setting Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_modify_account_currency_setting_message(ModifyAccountCurrencySettingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_ref_num[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->prm_account[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  record->reject_all_flag = wire[at++];
  record->blow_through_protection = wire[at++];

  return at;
}

/* what was read of Modify Account Currency Setting Message is what was written, byte for byte */
static void equal_modify_account_currency_setting_message(const ModifyAccountCurrencySettingMessage *read, const ModifyAccountCurrencySettingMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_ref_num[i] == written->user_ref_num[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->prm_account[i] == written->prm_account[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  assert(read->reject_all_flag == written->reject_all_flag);
  assert(read->blow_through_protection == written->blow_through_protection);
}

/* Modify Account Currency Setting Message: written and read back, then read and written back */
static void check_modify_account_currency_setting_message(void) {
  ModifyAccountCurrencySettingMessage sent;
  ModifyAccountCurrencySettingMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_modify_account_currency_setting_message(&sent);
  assert(encode_modify_account_currency_setting_message(&sent, wire, 0) == 15);
  assert(decode_modify_account_currency_setting_message(&got, wire, 0) == 15);
  equal_modify_account_currency_setting_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_account_currency_setting_message(&got, wire, 0) == 15);
  assert(encode_modify_account_currency_setting_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_client_packet_header();
  check_login_request_packet();
  check_modify_account_settings_message();
  check_modify_order_book_restriction_message();
  check_modify_market_segment_restriction_message();
  check_modify_limit_settings_message();
  check_modify_account_currency_setting_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
